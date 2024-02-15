#!/usr/bin/env python3

# Adds line numbers from SIM_original.elf to objdump output for diff.py

from __future__ import annotations

from pathlib import Path
import re
import subprocess
import sys
from typing import BinaryIO

MAP_FILE = "expected/build/SIM/SIM.map"
ORIGINAL_ELF_FILE = "SIM_original.elf"
OBJDUMP_EXECUTABLE = "powerpc-eabi-objdump"


def find_start_address_from_map_file(object_name: str) -> int | None:
    pattern = re.compile(r"  \S+ \S+ (\S+) +\S+ .text \t" + re.escape(object_name))
    with open(MAP_FILE, "r") as f:
        for line in f:
            match = pattern.match(line)
            if match:
                return int(match[1], 16)
    return None


def find_elf_section(f: BinaryIO, section_name: str) -> tuple[int, int] | None:
    f.seek(0)
    elf_header = f.read(64)
    e_shoff = int.from_bytes(elf_header[0x20:0x24], byteorder="big")
    e_shentsize = int.from_bytes(elf_header[0x2E:0x30], byteorder="big")
    e_shnum = int.from_bytes(elf_header[0x30:0x32], byteorder="big")
    e_shstrndx = int.from_bytes(elf_header[0x32:0x34], byteorder="big")

    # find string table
    f.seek(e_shoff + e_shstrndx * e_shentsize)
    entry = f.read(e_shentsize)
    strtab_offset = int.from_bytes(entry[0x10:0x14], byteorder="big")

    # find section
    for i in range(e_shnum):
        f.seek(e_shoff + i * e_shentsize)
        entry = f.read(e_shentsize)
        sh_name = int.from_bytes(entry[0x00:0x04], byteorder="big")

        f.seek(strtab_offset + sh_name)
        current_name = bytearray()
        while c := f.read(1)[0]:
            current_name.append(c)

        if current_name.decode("utf-8") == section_name:
            sh_offset = int.from_bytes(entry[0x10:0x14], byteorder="big")
            sh_size = int.from_bytes(entry[0x14:0x18], byteorder="big")
            return sh_offset, sh_size

    return None


def read_line_numbers(elf_file: Path, start_address) -> list[tuple[int, int]]:
    line_numbers = []
    with open(elf_file, "rb") as f:
        section = find_elf_section(f, ".line")
        if section is None:
            return []

        offset, size = section
        f.seek(offset)
        while f.tell() < offset + size:
            start = f.tell()

            length = int.from_bytes(f.read(4), byteorder="big")
            address = int.from_bytes(f.read(4), byteorder="big")

            if address != start_address:
                f.seek(start + length)
                continue

            while f.tell() < start + length:
                line_info = f.read(10)
                line = int.from_bytes(line_info[0:4], byteorder="big")
                delta = int.from_bytes(line_info[6:10], byteorder="big")
                line_numbers.append((delta, line))

    return line_numbers


def main(objdump_args: list[str]):
    object_file = Path(objdump_args[-1])
    c_file = object_file.with_suffix(".c").name

    line_numbers = []
    if object_file.parts[0] == "expected":
        start_address = find_start_address_from_map_file(object_file.name)
        if start_address is not None:
            line_numbers = read_line_numbers(Path(ORIGINAL_ELF_FILE), start_address)
    else:
        line_numbers = read_line_numbers(object_file, 0)

    p = subprocess.Popen(
        [OBJDUMP_EXECUTABLE] + objdump_args, stdout=subprocess.PIPE, encoding="utf-8"
    )
    assert p.stdout is not None

    next_entry = 0
    pattern = re.compile(r"^\s+([0-9a-f]+):")
    for line in p.stdout:
        match = pattern.match(line)
        if match:
            delta = int(match[1], 16)
            if next_entry < len(line_numbers) and line_numbers[next_entry][0] == delta:
                print(f"{c_file}:{line_numbers[next_entry][1]}")
                next_entry += 1
        print(line, end="")

    p.wait()
    sys.exit(p.returncode)


if __name__ == "__main__":
    objdump_args = sys.argv[1:]
    main(objdump_args)
