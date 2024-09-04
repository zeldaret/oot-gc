#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object NonMatching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

### Script's arguments

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "--non-matching",
    action="store_true",
    help="create non-matching build for modding",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="DIR",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
    default=True,
)
parser.add_argument(
    "--no-asm",
    action="store_true",
    help="don't incorporate .s files from asm directory",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--progress-version",
    metavar="VERSION",
    help="version to print progress for",
)

args = parser.parse_args()

### Project configuration

config = ProjectConfig()

# Only configure versions for which main.dol exists
ALL_VERSIONS = [
    "mq-j",
    "mq-u",
    "mq-e",
    "ce-j",
    "ce-u",
    "ce-e",
]
config.versions = [
    version
    for version in ALL_VERSIONS
    if (Path("orig") / version / "main.dol").exists()
]
if "ce-j" in config.versions:
    config.default_version = "ce-j"

config.warn_missing_config = True
config.warn_missing_source = False
config.progress_all = False

config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.sjiswrap_path = args.sjiswrap
config.non_matching = args.non_matching

if not is_windows():
    config.wrapper = args.wrapper

if args.no_asm:
    config.asm_dir = None

### Tool versions

config.binutils_tag = "2.42-1"
config.compilers_tag = "20231018"
config.dtk_tag = "v0.8.3"
config.objdiff_tag = "v2.0.0-beta.5"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.11"
config.linker_version = "GC/1.1"

### Flags

config.asflags = [
    "-mgekko",
    "-I include",
    "-I libc",
]

config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    "-warn off",
]

cflags_base = [
    "-Cpp_exceptions off",
    "-proc gekko",
    "-fp hardware",
    "-fp_contract on",
    "-enum int",
    "-align powerpc",
    "-nosyspath",
    "-RTTI off",
    "-str reuse",
    "-multibyte",
    "-O4,p",
    "-inline auto",
    "-nodefaults",
    "-msgstyle gcc",
    "-sym on",
    "-i include",
    "-i libc",
]

if config.non_matching:
    cflags_base.append("-DNON_MATCHING")

### Helper functions

def EmulatorLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.1",
        "cflags": [*cflags_base, "-inline deferred"],
        "host": False,
        "objects": objects,
    }

def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "host": False,
        "objects": objects,
    }

def GenericLib(lib_name: str, cflags: List[str], objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5",
        "cflags": cflags,
        "host": False,
        "objects": objects,
    }

### Link order

# Not matching for any version
NonMatching: List[str] = []

# Matching for all versions
Matching = config.versions

# Matching for specific versions
def MatchingFor(*versions):
    return versions

config.libs = [
    EmulatorLib(
        "emulator",
        [
            Object(Matching, "emulator/xlCoreGCN.c"),
            Object(Matching, "emulator/xlPostGCN.c"),
            Object(Matching, "emulator/xlFileGCN.c"),
            Object(MatchingFor("mq-e", "ce-e"), "emulator/xlText.c"),
            Object(Matching, "emulator/xlList.c"),
            Object(Matching, "emulator/xlHeap.c"),
            Object(MatchingFor("mq-e", "ce-e"), "emulator/xlFile.c"),
            Object(Matching, "emulator/xlObject.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "emulator/simGCN.c"),
            Object(Matching, "emulator/movie.c"),
            # THP files except for THPRead.c do not have -inline deferred
            Object(Matching, "emulator/THPPlayer.c", cflags=cflags_base),
            Object(Matching, "emulator/THPAudioDecode.c", cflags=cflags_base),
            Object(Matching, "emulator/THPDraw.c", cflags=cflags_base),
            Object(Matching, "emulator/THPRead.c"),
            Object(Matching, "emulator/THPVideoDecode.c", cflags=cflags_base),
            Object(MatchingFor("ce-j"), "emulator/mcardGCN.c", asm_processor=True),
            Object(Matching, "emulator/codeGCN.c"),
            Object(Matching, "emulator/soundGCN.c"),
            Object(MatchingFor("ce-j"), "emulator/frame.c", asm_processor=True),
            Object(Matching, "emulator/system.c"),
            Object(MatchingFor("ce-j"), "emulator/cpu.c", asm_processor=True),
            Object(Matching, "emulator/pif.c"),
            Object(Matching, "emulator/ram.c"),
            Object(Matching, "emulator/rom.c"),
            Object(Matching, "emulator/rdp.c"),
            Object(Matching, "emulator/rdb.c"),
            Object(MatchingFor("ce-j"), "emulator/rsp.c", asm_processor=True),
            Object(Matching, "emulator/mips.c"),
            Object(Matching, "emulator/disk.c"),
            Object(Matching, "emulator/flash.c"),
            Object(Matching, "emulator/sram.c"),
            Object(Matching, "emulator/audio.c"),
            Object(Matching, "emulator/video.c"),
            Object(Matching, "emulator/serial.c"),
            Object(Matching, "emulator/library.c"),
            Object(Matching, "emulator/peripheral.c"),
            Object(MatchingFor("ce-j"), "emulator/_frameGCNcc.c", asm_processor=True),
            Object(MatchingFor("ce-j"), "emulator/_buildtev.c", asm_processor=True),
        ],
    ),
    DolphinLib(
        "base",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OS.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSAlarm.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSAlloc.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSArena.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSAudioSystem.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSCache.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSContext.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSError.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSFont.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSInterrupt.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSLink.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSMessage.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSMemory.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSMutex.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSReboot.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSReset.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSResetSW.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSRtc.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSSync.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSThread.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSTime.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/__start.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/__ppc_eabi_init.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/exi/EXIBios.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/si/SIBios.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/si/SISamplingRate.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/mtx/mtx.c", extra_cflags=["-fp_contract off"]),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/mtx/mtxvec.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/mtx/mtx44.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXInit.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXFifo.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXAttr.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXMisc.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXGeometry.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXFrameBuf.c"),
            Object(MatchingFor("ce-j", "ce-u"), "dolphin/gx/GXLight.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXTexture.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXBump.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXTev.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXPixel.c", extra_cflags=["-fp_contract off"]),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXTransform.c", extra_cflags=["-fp_contract off"]),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/pad/Padclamp.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dvd/dvdlow.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dvd/dvdfs.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dvd/dvd.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dvd/dvdqueue.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dvd/dvderror.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dvd/dvdidutils.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dvd/dvdFatal.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "demo",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/demo/DEMOInit.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/demo/DEMOPuts.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/demo/DEMOFont.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/demo/DEMOPad.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/demo/DEMOStats.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/ar/ar.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dsp/dsp.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dsp/dsp_debug.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDBios.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDUnlock.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDRdwr.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDBlock.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDDir.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDCheck.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDMount.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDFormat.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDOpen.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDCreate.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDRead.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDWrite.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDDelete.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDStat.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDNet.c"),
        ],
    ),
    DolphinLib(
        "thp",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/thp/THPDec.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/thp/THPAudio.c"),
        ],
    ),
    DolphinLib(
        "tex",
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/tex/texPalette.c"),
        ],
    ),
    GenericLib(
        "metrotrk",
        cflags_base,
        [
            Object(NonMatching, "metrotrk/mainloop.c"),
            Object(NonMatching, "metrotrk/nubevent.c"),
            Object(NonMatching, "metrotrk/nubinit.c"),
            Object(NonMatching, "metrotrk/msg.c"),
            Object(NonMatching, "metrotrk/msgbuf.c"),
            Object(NonMatching, "metrotrk/serpoll.c"),
            Object(NonMatching, "metrotrk/usr_put.c"),
            Object(NonMatching, "metrotrk/dispatch.c"),
            Object(NonMatching, "metrotrk/msghndlr.c"),
            Object(NonMatching, "metrotrk/support.c"),
            Object(NonMatching, "metrotrk/mutex_TRK.c"),
            Object(NonMatching, "metrotrk/notify.c"),
            Object(NonMatching, "metrotrk/flush_cache.c"),
            Object(NonMatching, "metrotrk/mem_TRK.c"),
            Object(NonMatching, "metrotrk/__exception.c"),
            Object(NonMatching, "metrotrk/targimpl.c"),
            Object(NonMatching, "metrotrk/dolphin_trk.c"),
            Object(NonMatching, "metrotrk/mpc_7xx_603e.c"),
            Object(NonMatching, "metrotrk/main_TRK.c"),
            Object(NonMatching, "metrotrk/dolphin_trk_glue.c"),
            Object(NonMatching, "metrotrk/targcont.c"),
        ]
    ),
    GenericLib(
        "runtime",
        [*cflags_base, "-inline deferred"],
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "runtime/__mem.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "runtime/__va_arg.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "runtime/global_destructor_chain.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "runtime/runtime.c"),
        ]
    ),
    GenericLib(
        "libc",
        [*cflags_base, "-inline deferred"],
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/abort_exit.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/ansi_files.c"),
            Object(NonMatching, "libc/ansi_fp.c", extra_cflags=["-inline noauto"]),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/buffer_io.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/critical_regions.ppc_eabi.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/ctype.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/direct_io.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/errno.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/mbstring.c"),
            Object(NonMatching, "libc/mem.c"),
            Object(NonMatching, "libc/mem_funcs.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/misc_io.c"),
            Object(NonMatching, "libc/printf.c"),
            Object(NonMatching, "libc/scanf.c"),
            Object(NonMatching, "libc/string.c"),
            Object(NonMatching, "libc/strtoul.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/uart_console_io.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/float.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/wchar_io.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/e_asin.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/e_pow.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/fminmaxdim.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/s_ceil.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/s_copysign.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/s_floor.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/s_frexp.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/s_ldexp.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/w_pow.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/hyperbolicsf.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/log10f.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/trigf.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/math_inlines.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "libc/common_float_tables.c"),
        ]
    ),
    GenericLib(
        "debugger",
        cflags_base,
        [
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "debugger/AmcExi2Stubs.c"),
            Object(NonMatching, "debugger/DebuggerDriver.c"),
            Object(MatchingFor("mq-j", "mq-u", "ce-j", "ce-u"), "debugger/odenotstub.c"),
        ]
    ),
]

### Execute mode

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config, args.progress_version)
else:
    sys.exit("Unknown mode: " + args.mode)
