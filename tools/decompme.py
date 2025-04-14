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

INCLUDE_DIRS = [
    Path("."),
    Path("include"),
    Path("libc"),
    Path("src"),
]
COMPILER_NAME = "mwcc_233_159"
# We don't set -inline deferred because otherwise the reversed function order
# would require manually deleting all previous function definitions from the
# context.
COMPILER_FLAGS = "-Cpp_exceptions off -proc gekko -fp hard -fp_contract on -enum int -O4,p -inline auto -nodefaults -msgstyle gcc"

INCLUDE_PATTERN = re.compile(r'^#include\s*[<"](.+?)[>"]')
DEFINE_PATTERN = re.compile(r"^#define\s+(\w+)(?:\s+(.*))?")
IF_PATTERN = re.compile(r"^#if(n)?(?:def)?\s+(.*)")
ELSE_PATTERN = re.compile(r"^#else")
ENDIF_PATTERN = re.compile(r"^#endif")
INCBIN_PATTERN = re.compile(r"^#pragma INCBIN\(.*\)")

MACROS: list[tuple[re.Pattern, str]] = [
    (re.compile(r"\bAT_ADDRESS\b\(.*\)"), ""),
    (re.compile(r"\b_GX_TF_CTF\b"), "0x20"),
    (re.compile(r"\b_GX_TF_ZTF\b"), "0x10"),
    (re.compile(r"\bOS_THREAD_SPECIFIC_MAX\b"), "2"),
    (re.compile(r"\bCARD_FILENAME_MAX\b"), "32"),
    (re.compile(r"\bCARD_ICON_MAX\b"), "8"),
    (re.compile(r"\bN64_FRAME_WIDTH\b"), "320"),
    (re.compile(r"\bN64_FRAME_HEIGHT\b"), "240"),
    (re.compile(r"\bATTRIBUTE_ALIGN\b\(.*\)"), ""),
    (re.compile(r"\b_MATH_INLINE\b"), "static inline"),
    (re.compile(r"\bINIT\b"), ""),
    (re.compile(r"\b__ungetc_buffer_size\b"), "2"),
]

# Defined preprocessor macros (for conditions)
defines = set()
# Stack of preprocessor conditions
condition_stack = [True]


def find_include_file(filename: str) -> Path:
    for include_dir in INCLUDE_DIRS:
        path = include_dir / filename
        if path.exists():
            return path
    raise FileNotFoundError(f"Could not find include file {filename}")


def process_c_file(path: Path) -> str:
    lines = path.read_text().splitlines()
    out_text = ""
    for i, line in enumerate(lines):
        if match := IF_PATTERN.match(line.strip()):
            condition = match[2] in defines
            if match[1] == "n":
                condition = not condition
            condition_stack.append(condition)
        elif ELSE_PATTERN.match(line.strip()):
            condition_stack[-1] = not condition_stack[-1]
        elif ENDIF_PATTERN.match(line.strip()):
            condition_stack.pop()
        else:
            if not all(condition_stack):
                continue

            if match := DEFINE_PATTERN.match(line.strip()):
                defines.add(match[1])
                out_text += line
                out_text += "\n"
            elif match := INCLUDE_PATTERN.match(line.strip()):
                include_file = find_include_file(match[1])
                out_text += f'/* "{path}" line {i + 1} "{include_file}" */\n'
                out_text += process_c_file(include_file)
                out_text += f'/* end "{include_file}" */\n'
            elif match := INCBIN_PATTERN.match(line.strip()):
                out_text += "    0"
                out_text += "\n"
            else:
                for pattern, replacement in MACROS:
                    line = pattern.sub(replacement, line)
                out_text += line
                out_text += "\n"

    return out_text


def process_asm_file(path: Path) -> str:
    lines = path.read_text().splitlines()
    out_text = ""
    for line in lines:
        if line.startswith(".global "):
            continue
        out_text += line
        out_text += "\n"

    return out_text


def main():
    parser = argparse.ArgumentParser(description="Create a decomp.me scratch")
    parser.add_argument("c_file", metavar="C_FILE", type=Path, help="Input .c file")
    parser.add_argument("asm_file", metavar="ASM_FILE", type=Path, help="Input .s file")
    parser.add_argument(
        "--print-context", action="store_true", help="Print the context and exit"
    )

    args = parser.parse_args()

    func_name = args.asm_file.stem
    context = process_c_file(args.c_file)
    asm_cont = process_asm_file(args.asm_file)
    source_code = ""  # TODO: separate source code from context automatically

    if args.print_context:
        print(context)
        return

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
            json_data: dict[str, str] = json.loads(resp)
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
