#!/bin/bash

# Patches a bug in CWParserSetOutputFileDirectory which causes the linker to
# read uninitialized data and possibly crash.

set -euo pipefail

LD="$1"
if [[ ! -f "$LD" ]]; then
    echo "Linker not found. Please place the MWCC compiler executables in the $(dirname "$LD") directory."
    exit 1
fi

ORIG_CHECKSUM="1e7752feb4e77e9338662e26cf09983b"
PATCHED_CHECKSUM="93835e361ba564c7f5d73fb10fc9cdfa"

CHECKSUM=$(md5sum "$LD" | cut -d ' ' -f 1)
if [[ "$CHECKSUM" = "$PATCHED_CHECKSUM" ]]; then
    : # Already patched
elif [[ "$CHECKSUM" = "$ORIG_CHECKSUM" ]]; then
    LD_ORIG="$LD".orig
    cp "$LD" "$LD_ORIG"

    printf '\x51' | dd of="$LD" bs=1 seek=130933 count=1 conv=notrunc 2>/dev/null

    CHECKSUM=$(md5sum "$LD" | cut -d ' ' -f 1)
    if [[ "$CHECKSUM" != "$PATCHED_CHECKSUM" ]]; then
        echo "Failed to patch linker! Checksum does not match."
        exit 1
    fi

    echo "Patched $(basename "$LD"), original saved as $(basename "$LD_ORIG")"
else
    echo "Unknown linker version. Ensure that the correct MWCC compiler executables are in the $(dirname "$LD") directory."
    exit 1
fi
