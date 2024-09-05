#!/bin/bash

set -euo pipefail

# bash scripts are executed with sh.exe, installed with Git for Windows, which is using MSYS
OS=$(uname -o)
PYTHON="python3"
if [ "$OS" == "Msys" ]; then 
    PYTHON="python"
fi

CC="$1"
shift
AS="$1"
shift
OBJCOPY="$1"
shift
IN="$1"
shift
OUT="$1"

# When running windows exes through wsl1 you can't give them linux paths
mkdir -p tools/asm_processor/tmp
TEMP="$(mktemp -d tools/asm_processor/tmp/XXXXXX)"
trap "rm -rf $TEMP" EXIT

STEM=$(basename "$IN")
STEM="${STEM%.*}"

$PYTHON tools/asm_processor/asm_processor.py "$IN" > "$TEMP/$STEM.c"
$CC "$TEMP/$STEM.c" -c -o "$TEMP"
$PYTHON tools/asm_processor/asm_processor.py "$IN" --post-process "$TEMP/$STEM.o" --assembler "$AS" --asm-prelude include/macros.inc
# Remove sections that don't work with our reloc hacks
$OBJCOPY --remove-section .mwcats.text --remove-section .comment "$TEMP/$STEM.o" "$OUT"
# Copy depfile, replacing the first line with the correct input/output files
( echo "$OUT: $IN \\"; tail -n +2 "$TEMP/$STEM.d" ) > "${OUT%.*}.d"
