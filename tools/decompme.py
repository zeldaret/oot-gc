#!/usr/bin/env python3

# Script to upload a decomp.me. Usage example:
#
#   tools/decompme.py src/rom.c asm/non_matchings/rom/romGetPC.s
#
# Currently you must manually delete the function from the context and copy into
# the source if the function is already defined.

from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import urllib.parse
import urllib.request

COMPILER_NAME = "mwcc_233_159"
COMPILER_FLAGS = (
    "-Cpp_exceptions off -proc gekko -fp hard -O4,p -nodefaults -msgstyle gcc"
)
INCLUDE_PATTERN = re.compile(r'^#include\s*[<"](.+?)[>"]$')
GUARD_PATTERN = re.compile(r'^#ifndef\s+(.*)$')
INCLUDE_DIR = Path("include")

defines = set()


def process_file(path: Path) -> str:
    lines = path.read_text().splitlines()
    out_text = ""
    for i, line in enumerate(lines):
        guard_match = GUARD_PATTERN.match(line.strip())
        if i == 0 and guard_match:
            if guard_match[1] in defines:
                break
            defines.add(guard_match[1])
            continue

        if line.startswith("#if") or line.startswith("#endif"):
            continue

        include_match = INCLUDE_PATTERN.match(line.strip())
        if include_match:
            out_text += f'/* "{path}" line {i + 1} "{include_match[1]}" */\n'
            out_text += process_file(INCLUDE_DIR / include_match[1])
            out_text += f'/* end "{include_match[1]}" */\n'
        else:
            out_text += line
            out_text += "\n"

    return out_text


def main():
    parser = argparse.ArgumentParser(description="Create a decomp.me scratch")
    parser.add_argument("c_file", metavar="C_FILE", type=Path, help="Input .c file")
    parser.add_argument("asm_file", metavar="ASM_FILE", type=Path, help="Input .s file")

    args = parser.parse_args()

    func_name = args.asm_file.stem
    asm_cont = args.asm_file.read_text()
    context = process_file(args.c_file)
    source_code = ""  # TODO: separate source code from context automatically

    print("Uploading...")
    try:
        post_data = urllib.parse.urlencode(
            {
                "name": func_name,
                "target_asm": asm_cont,
                "context": context,
                "source_code": source_code,
                "compiler": COMPILER_NAME,
                "compiler_flags": COMPILER_FLAGS,
                "diff_label": func_name,
            }
        ).encode("ascii")
        with urllib.request.urlopen("https://decomp.me/api/scratch", post_data) as f:
            resp = f.read()
            json_data: Dict[str, str] = json.loads(resp)
            if "slug" in json_data:
                slug = json_data["slug"]
                token = json_data.get("claim_token")
                if token:
                    print(f"https://decomp.me/scratch/{slug}/claim?token={token}")
                else:
                    print(f"https://decomp.me/scratch/{slug}")
            else:
                error = json_data.get("error", resp)
                print(f"Server error: {error}")
    except Exception as e:
        print(e)


if __name__ == "__main__":
    main()
