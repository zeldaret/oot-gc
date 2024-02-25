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

INCLUDE_DIR = Path("include")
COMPILER_NAME = "mwcc_233_159"
# We don't set -inline deferred because otherwise the reversed function order
# would require manually deleting all previous function definitions from the
# context.
COMPILER_FLAGS = (
    "-Cpp_exceptions off -proc gekko -fp hard -fp_contract on -enum int -O4,p -inline auto -nodefaults -msgstyle gcc"
)

INCLUDE_PATTERN = re.compile(r'^#include\s*[<"](.+?)[>"]$')
DEFINE_PATTERN = re.compile(r'^#define\s+(\w+)(?:\s+(.*))?$')
IF_PATTERN = re.compile(r'^#if(n)?(?:def)?\s+(.*)$')
ELSE_PATTERN = re.compile(r'^#else$')
ENDIF_PATTERN = re.compile(r'^#endif$')
INCBIN_PATTERN = re.compile(r'^#pragma INCBIN\(.*\)$')

# Defined preprocessor macros
defines = {"__MWERKS__"}
# Stack of preprocessor conditions
condition_stack = [True]


def process_file(path: Path) -> str:
    lines = path.read_text().splitlines()
    out_text = ""
    for i, line in enumerate(lines):
        if (match := IF_PATTERN.match(line.strip())):
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

            if (match := DEFINE_PATTERN.match(line.strip())):
                defines.add(match[1])
                out_text += line
                out_text += "\n"
            elif (match := INCLUDE_PATTERN.match(line.strip())):
                out_text += f'/* "{path}" line {i + 1} "{match[1]}" */\n'
                out_text += process_file(INCLUDE_DIR / match[1])
                out_text += f'/* end "{match[1]}" */\n'
            elif INCBIN_PATTERN.match(line.strip()):
                out_text += "    0"
                out_text += "\n"
            else:
                out_text += line
                out_text += "\n"

    return out_text


def main():
    parser = argparse.ArgumentParser(description="Create a decomp.me scratch")
    parser.add_argument("c_file", metavar="C_FILE", type=Path, help="Input .c file")
    parser.add_argument("asm_file", metavar="ASM_FILE", type=Path, help="Input .s file")
    parser.add_argument("--print-context", action="store_true", help="Print the context and exit")

    args = parser.parse_args()

    func_name = args.asm_file.stem
    asm_cont = args.asm_file.read_text()
    context = process_file(args.c_file)
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
