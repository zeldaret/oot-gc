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
import os
from pathlib import Path
import platform
import re
import subprocess
import urllib.parse
import urllib.request

COMPILER_NAME = "mwcc_233_159"
COMPILER_FLAGS = (
    "-Cpp_exceptions off -proc gekko -fp hard -fp_contract on -enum int -O4,p -inline auto,deferred -sym on -nodefaults -msgstyle gcc"
)
CPP_ARGS = [
    "-P",
    "-I",
    "include",
    "-D",
    "__MWERKS__",
]


def homebrew_gcc_cpp() -> str:
    for lookup_path in ["/usr/local/bin", "/opt/homebrew/bin"]:
        try:
            return max(f for f in os.listdir(lookup_path) if f.startswith("cpp-"))
        except ValueError:
            pass
    print(
        "Error while looking up in " + ":".join(lookup_paths) + " for cpp- executable"
    )
    sys.exit(1)


def process_file(path: Path) -> str:
    is_macos = platform.system() == "Darwin"
    cpp = homebrew_gcc_cpp() if is_macos else "cpp"

    cpp_command = [cpp] + CPP_ARGS + [str(path)]
    cpp_output = subprocess.run(
        cpp_command, capture_output=True, text=True, check=True
    ).stdout
    return re.sub(r"#pragma INCBIN.*\n", "0", cpp_output)


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
