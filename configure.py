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
    metavar="BINARY",
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
config.versions = [
    "ce-j",
    "ce-u",
]
config.default_version = "ce-j"
config.warn_missing_config = True
config.warn_missing_source = False
config.progress_all = False

config.build_dir = args.build_dir
config.dtk_path = args.dtk
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
    # TODO: remove and use VERSION instead
    "-DDOLPHIN_REV=2003",
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

def GenericLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "host": False,
        "objects": objects,
    }

### Link order

# Not matching for any version
NonMatching = {}

# Matching for all versions
Matching = config.versions

# Matching for specific versions
def MatchingFor(*versions):
    return versions

config.libs = [
    EmulatorLib(
        "emulator",
        [
            Object(MatchingFor("ce-j", "ce-u"), "emulator/xlCoreGCN.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/xlPostGCN.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/xlFileGCN.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/xlList.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/xlHeap.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/xlObject.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/simGCN.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/movie.c"),
            # THP files except for THPRead.c do not have -inline deferred
            Object(MatchingFor("ce-j", "ce-u"), "emulator/THPPlayer.c", cflags=cflags_base),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/THPAudioDecode.c", cflags=cflags_base),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/THPDraw.c", cflags=cflags_base),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/THPRead.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/THPVideoDecode.c", cflags=cflags_base),
            Object(MatchingFor("ce-j"), "emulator/mcardGCN.c", asm_processor=True),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/codeGCN.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/soundGCN.c"),
            Object(MatchingFor("ce-j"), "emulator/frame.c", asm_processor=True),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/system.c"),
            Object(MatchingFor("ce-j"), "emulator/cpu.c", asm_processor=True),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/pif.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/ram.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/rom.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/rdp.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/rdb.c"),
            Object(MatchingFor("ce-j"), "emulator/rsp.c", asm_processor=True),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/mips.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/disk.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/flash.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/sram.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/audio.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/video.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/serial.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/library.c"),
            Object(MatchingFor("ce-j", "ce-u"), "emulator/peripheral.c"),
            Object(MatchingFor("ce-j"), "emulator/_frameGCNcc.c", asm_processor=True),
            Object(MatchingFor("ce-j"), "emulator/_buildtev.c", asm_processor=True),
        ],
    ),
    DolphinLib(
        "base",
        [
            Object(NonMatching, "dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(MatchingFor("ce-j"), "dolphin/os/OS.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSAlarm.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSAlloc.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSArena.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSAudioSystem.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSCache.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSContext.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSError.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSFont.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSInterrupt.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSLink.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSMessage.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSMemory.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSMutex.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSReboot.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSReset.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSResetSW.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSRtc.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSSync.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSThread.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/OSTime.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/__start.c"),
            Object(MatchingFor("ce-j"), "dolphin/os/__ppc_eabi_init.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(NonMatching, "dolphin/exi/EXIBios.c"),
            Object(NonMatching, "dolphin/exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(NonMatching, "dolphin/si/SIBios.c"),
            Object(NonMatching, "dolphin/si/SISamplingRate.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(NonMatching, "dolphin/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(NonMatching, "dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(NonMatching, "dolphin/mtx/mtx.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "dolphin/mtx/mtxvec.c"),
            Object(NonMatching, "dolphin/mtx/mtx44.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(NonMatching, "dolphin/gx/GXInit.c"),
            Object(NonMatching, "dolphin/gx/GXFifo.c"),
            Object(NonMatching, "dolphin/gx/GXAttr.c"),
            Object(NonMatching, "dolphin/gx/GXMisc.c"),
            Object(NonMatching, "dolphin/gx/GXGeometry.c"),
            Object(NonMatching, "dolphin/gx/GXFrameBuf.c"),
            Object(NonMatching, "dolphin/gx/GXLight.c"),
            Object(NonMatching, "dolphin/gx/GXTexture.c"),
            Object(NonMatching, "dolphin/gx/GXBump.c"),
            Object(NonMatching, "dolphin/gx/GXTev.c"),
            Object(NonMatching, "dolphin/gx/GXPixel.c"),
            Object(NonMatching, "dolphin/gx/GXTransform.c"),
            Object(NonMatching, "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(NonMatching, "dolphin/pad/Padclamp.c"),
            Object(NonMatching, "dolphin/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(NonMatching, "dolphin/dvd/dvdlow.c"),
            Object(NonMatching, "dolphin/dvd/dvdfs.c"),
            Object(NonMatching, "dolphin/dvd/dvd.c"),
            Object(NonMatching, "dolphin/dvd/dvdqueue.c"),
            Object(NonMatching, "dolphin/dvd/dvderror.c"),
            Object(NonMatching, "dolphin/dvd/dvdidutils.c"),
            Object(NonMatching, "dolphin/dvd/dvdFatal.c"),
            Object(NonMatching, "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "demo",
        [
            Object(NonMatching, "dolphin/demo/DEMOInit.c"),
            Object(NonMatching, "dolphin/demo/DEMOPuts.c"),
            Object(NonMatching, "dolphin/demo/DEMOFont.c"),
            Object(NonMatching, "dolphin/demo/DEMOPad.c"),
            Object(NonMatching, "dolphin/demo/DEMOStats.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(NonMatching, "dolphin/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(NonMatching, "dolphin/ar/ar.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(NonMatching, "dolphin/dsp/dsp.c"),
            Object(NonMatching, "dolphin/dsp/dsp_debug.c"),
            Object(NonMatching, "dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(NonMatching, "dolphin/card/CARDBios.c"),
            Object(NonMatching, "dolphin/card/CARDUnlock.c"),
            Object(NonMatching, "dolphin/card/CARDRdwr.c"),
            Object(NonMatching, "dolphin/card/CARDBlock.c"),
            Object(NonMatching, "dolphin/card/CARDDir.c"),
            Object(NonMatching, "dolphin/card/CARDCheck.c"),
            Object(NonMatching, "dolphin/card/CARDMount.c"),
            Object(NonMatching, "dolphin/card/CARDFormat.c"),
            Object(NonMatching, "dolphin/card/CARDOpen.c"),
            Object(NonMatching, "dolphin/card/CARDCreate.c"),
            Object(NonMatching, "dolphin/card/CARDRead.c"),
            Object(NonMatching, "dolphin/card/CARDWrite.c"),
            Object(NonMatching, "dolphin/card/CARDDelete.c"),
            Object(NonMatching, "dolphin/card/CARDStat.c"),
            Object(NonMatching, "dolphin/card/CARDRename.c"),
            Object(NonMatching, "dolphin/card/CARDNet.c"),
        ],
    ),
    DolphinLib(
        "thp",
        [
            Object(NonMatching, "dolphin/thp/THPDec.c"),
            Object(NonMatching, "dolphin/thp/THPAudio.c"),
        ],
    ),
    DolphinLib(
        "tex",
        [
            Object(NonMatching, "dolphin/tex/texPalette.c"),
        ],
    ),
    GenericLib(
        "metrotrk",
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
        [
            Object(NonMatching, "runtime/__mem.c"),
            Object(NonMatching, "runtime/__va_arg.c"),
            Object(NonMatching, "runtime/global_destructor_chain.c"),
            Object(NonMatching, "runtime/runtime.c"),
        ]
    ),
    GenericLib(
        "libc",
        [
            Object(NonMatching, "libc/abort_exit.c"),
            Object(NonMatching, "libc/ansi_files.c"),
            Object(NonMatching, "libc/ansi_fp.c", extra_cflags=["-inline noauto"]),
            Object(NonMatching, "libc/buffer_io.c"),
            Object(NonMatching, "libc/critical_regions.ppc_eabi.c"),
            Object(NonMatching, "libc/ctype.c"),
            Object(NonMatching, "libc/direct_io.c"),
            Object(NonMatching, "libc/errno.c"),
            Object(NonMatching, "libc/mbstring.c", extra_cflags=["-inline noauto"]),
            Object(NonMatching, "libc/mem.c"),
            Object(NonMatching, "libc/mem_funcs.c"),
            Object(NonMatching, "libc/misc_io.c"),
            Object(NonMatching, "libc/printf.c"),
            Object(NonMatching, "libc/scanf.c"),
            Object(NonMatching, "libc/string.c"),
            Object(NonMatching, "libc/strtoul.c"),
            Object(NonMatching, "libc/uart_console_io.c"),
            Object(NonMatching, "libc/float.c"),
            Object(NonMatching, "libc/wchar_io.c"),
            Object(NonMatching, "libc/e_asin.c"),
            Object(NonMatching, "libc/e_pow.c"),
            Object(NonMatching, "libc/fminmaxdim.c"),
            Object(NonMatching, "libc/s_ceil.c"),
            Object(NonMatching, "libc/s_copysign.c"),
            Object(NonMatching, "libc/s_floor.c"),
            Object(NonMatching, "libc/s_frexp.c"),
            Object(NonMatching, "libc/s_ldexp.c"),
            Object(NonMatching, "libc/w_pow.c"),
            Object(NonMatching, "libc/hyperbolicsf.c"),
            Object(NonMatching, "libc/log10f.c"),
            Object(NonMatching, "libc/trigf.c"),
            Object(NonMatching, "libc/math_inlines.c"),
            Object(NonMatching, "libc/common_float_tables.c"),
        ]
    ),
    GenericLib(
        "debugger",
        [
            Object(NonMatching, "debugger/AmcExi2Stubs.c"),
            Object(NonMatching, "debugger/DebuggerDriver.c"),
            Object(NonMatching, "debugger/odenotstub.c"),
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