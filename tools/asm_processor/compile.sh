#!/bin/bash

set -euo pipefail

CC="$1"
shift
AS="$1"
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

tools/asm_processor/asm_processor.py "$IN" > "$TEMP/$STEM.c"
$CC "$TEMP/$STEM.c" -c -o "$TEMP"
tools/asm_processor/asm_processor.py "$IN" --post-process "$TEMP/$STEM.o" --assembler "$AS" --asm-prelude include/macros.inc
# Remove sections that don't work with our reloc hacks
build/binutils/powerpc-eabi-objcopy --remove-section .mwcats.text --remove-section .comment "$TEMP/$STEM.o" "$OUT"
# Copy depfile, replacing the first line with the correct input/output files
( echo "$OUT: $IN \\"; tail -n +2 "$TEMP/$STEM.d" ) > "${OUT%.*}.d"
