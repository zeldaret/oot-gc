#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object NotLinked status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
import glob
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
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


# Only configure versions for which an orig file exists
def version_exists(version: str) -> bool:
    return glob.glob(str(Path("orig") / version / "*")) != []


ALL_VERSIONS = [
    "mq-j",
    "mq-u",
    "mq-e",
    "ce-j",
    "ce-u",
    "ce-e",
    "mm-j",
    "mm-u",
    "mm-e",
]
config.versions = [
    version
    for version in ALL_VERSIONS
    if version_exists(version)
]

if not config.versions:
    sys.exit("Error: no orig files found for any version")

if "ce-j" in config.versions:
    config.default_version = "ce-j"
else:
    # Use the earliest version as default
    config.default_version = config.versions[0]

config.warn_missing_config = True
config.warn_missing_source = False
config.progress_all = True

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
config.compilers_tag = "20250520"
config.dtk_tag = "v1.4.1"
config.objdiff_tag = "v3.0.0-beta.8"
config.sjiswrap_tag = "v1.2.0"
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
    "-i src",
]

if config.non_matching:
    cflags_base.append("-DNON_MATCHING")

### Helper functions

def EmulatorLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.1",
        "cflags": [*cflags_base, "-inline deferred"],
        "progress_category": "emulator",
        "objects": objects,
    }

def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "dolphin",
        "objects": objects,
    }

def LibC(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5",
        "cflags": [*cflags_base, "-inline deferred", "-str pool,readonly"],
        "progress_category": "libc",
        "objects": objects,
    }

def RuntimeLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5",
        "cflags": [*cflags_base, "-inline deferred"],
        "progress_category": "runtime",
        "objects": objects,
    }

def MetroTRKLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.1p1",
        "cflags": [*cflags_base, "-rostr", "-sdata 0", "-sdata2 0", "-pool off", "-inline on,noauto", "-use_lmw_stmw on"],
        "progress_category": "metrotrk",
        "objects": objects,
    }

def DebuggerLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "debugger",
        "objects": objects,
    }

### Link order

# Not matching for any version
NotLinked: List[str] = []

# Linked for all versions
Linked = config.versions

# Linked for specific versions
def LinkedFor(*versions):
    return versions

config.libs = [
    EmulatorLib(
        "emulator",
        [
            Object(Linked, "emulator/xlCoreGCN.c"),
            Object(Linked, "emulator/xlPostGCN.c"),
            Object(Linked, "emulator/xlFileGCN.c"),
            Object(LinkedFor("mq-e", "ce-e", "mm-j", "mm-u", "mm-e"), "emulator/xlText.c"),
            Object(Linked, "emulator/xlList.c"),
            Object(Linked, "emulator/xlHeap.c"),
            Object(LinkedFor("mq-e", "ce-e", "mm-j", "mm-u", "mm-e"), "emulator/xlFile.c"),
            Object(Linked, "emulator/xlObject.c"),
            Object(Linked, "emulator/simGCN.c"),
            Object(Linked, "emulator/movie.c"),
            # THP files except for THPRead.c do not have -inline deferred
            Object(Linked, "emulator/THPPlayer.c", cflags=cflags_base),
            Object(Linked, "emulator/THPAudioDecode.c", cflags=cflags_base),
            Object(Linked, "emulator/THPDraw.c", cflags=cflags_base),
            Object(Linked, "emulator/THPRead.c"),
            Object(Linked, "emulator/THPVideoDecode.c", cflags=cflags_base),
            Object(Linked, "emulator/mcardGCN.c"),
            Object(Linked, "emulator/codeGCN.c"),
            Object(Linked, "emulator/soundGCN.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u", "ce-e"), "emulator/frame.c"),
            Object(Linked, "emulator/system.c"),
            Object(Linked, "emulator/cpu.c"),
            Object(Linked, "emulator/pif.c"),
            Object(Linked, "emulator/ram.c"),
            Object(Linked, "emulator/rom.c"),
            Object(Linked, "emulator/rdp.c"),
            Object(Linked, "emulator/rdb.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u", "ce-e"), "emulator/rsp.c"),
            Object(Linked, "emulator/mips.c"),
            Object(Linked, "emulator/disk.c"),
            Object(Linked, "emulator/flash.c"),
            Object(Linked, "emulator/sram.c"),
            Object(Linked, "emulator/audio.c"),
            Object(Linked, "emulator/video.c"),
            Object(Linked, "emulator/serial.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u", "ce-e", "mm-j"), "emulator/library.c"),
            Object(Linked, "emulator/peripheral.c"),
            Object(Linked, "emulator/_frameGCNcc.c"),
            Object(Linked, "emulator/_buildtev.c"),
            Object(NotLinked, "emulator/snddvdtrk.c"),
            Object(LinkedFor("mm-j", "mm-u", "mm-e"), "emulator/sndspecial.c"),
        ],
    ),
    DolphinLib(
        "base",
        [
            Object(Linked, "dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(Linked, "dolphin/os/OS.c"),
            Object(Linked, "dolphin/os/OSAlarm.c"),
            Object(Linked, "dolphin/os/OSAlloc.c"),
            Object(Linked, "dolphin/os/OSArena.c"),
            Object(Linked, "dolphin/os/OSAudioSystem.c"),
            Object(Linked, "dolphin/os/OSCache.c"),
            Object(Linked, "dolphin/os/OSContext.c"),
            Object(Linked, "dolphin/os/OSError.c"),
            Object(Linked, "dolphin/os/OSFont.c"),
            Object(Linked, "dolphin/os/OSInterrupt.c"),
            Object(Linked, "dolphin/os/OSLink.c"),
            Object(Linked, "dolphin/os/OSMessage.c"),
            Object(Linked, "dolphin/os/OSMemory.c"),
            Object(Linked, "dolphin/os/OSMutex.c"),
            Object(Linked, "dolphin/os/OSReboot.c"),
            Object(Linked, "dolphin/os/OSReset.c"),
            Object(Linked, "dolphin/os/OSResetSW.c"),
            Object(Linked, "dolphin/os/OSRtc.c"),
            Object(Linked, "dolphin/os/OSSync.c"),
            Object(Linked, "dolphin/os/OSThread.c"),
            Object(Linked, "dolphin/os/OSTime.c"),
            Object(Linked, "dolphin/os/__start.c"),
            Object(Linked, "dolphin/os/__ppc_eabi_init.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(Linked, "dolphin/exi/EXIBios.c"),
            Object(Linked, "dolphin/exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(Linked, "dolphin/si/SIBios.c"),
            Object(Linked, "dolphin/si/SISamplingRate.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(Linked, "dolphin/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(Linked, "dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(Linked, "dolphin/mtx/mtx.c", extra_cflags=["-fp_contract off"]),
            Object(Linked, "dolphin/mtx/mtxvec.c"),
            Object(Linked, "dolphin/mtx/mtx44.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(Linked, "dolphin/gx/GXInit.c"),
            Object(Linked, "dolphin/gx/GXFifo.c"),
            Object(Linked, "dolphin/gx/GXAttr.c"),
            Object(Linked, "dolphin/gx/GXMisc.c"),
            Object(Linked, "dolphin/gx/GXGeometry.c"),
            Object(Linked, "dolphin/gx/GXFrameBuf.c"),
            Object(Linked, "dolphin/gx/GXLight.c"),
            Object(Linked, "dolphin/gx/GXTexture.c"),
            Object(Linked, "dolphin/gx/GXBump.c"),
            Object(Linked, "dolphin/gx/GXTev.c"),
            Object(Linked, "dolphin/gx/GXPixel.c", extra_cflags=["-fp_contract off"]),
            Object(Linked, "dolphin/gx/GXTransform.c", extra_cflags=["-fp_contract off"]),
            Object(Linked, "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(Linked, "dolphin/pad/Padclamp.c"),
            Object(Linked, "dolphin/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(Linked, "dolphin/dvd/dvdlow.c"),
            Object(Linked, "dolphin/dvd/dvdfs.c"),
            Object(Linked, "dolphin/dvd/dvd.c"),
            Object(Linked, "dolphin/dvd/dvdqueue.c"),
            Object(Linked, "dolphin/dvd/dvderror.c"),
            Object(Linked, "dolphin/dvd/dvdidutils.c"),
            Object(Linked, "dolphin/dvd/dvdFatal.c"),
            Object(Linked, "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "demo",
        [
            Object(Linked, "dolphin/demo/DEMOInit.c"),
            Object(Linked, "dolphin/demo/DEMOPuts.c"),
            Object(Linked, "dolphin/demo/DEMOFont.c"),
            Object(Linked, "dolphin/demo/DEMOPad.c"),
            Object(Linked, "dolphin/demo/DEMOStats.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(Linked, "dolphin/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(Linked, "dolphin/ar/ar.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(Linked, "dolphin/dsp/dsp.c"),
            Object(Linked, "dolphin/dsp/dsp_debug.c"),
            Object(Linked, "dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(Linked, "dolphin/card/CARDBios.c"),
            Object(Linked, "dolphin/card/CARDUnlock.c"),
            Object(Linked, "dolphin/card/CARDRdwr.c"),
            Object(Linked, "dolphin/card/CARDBlock.c"),
            Object(Linked, "dolphin/card/CARDDir.c"),
            Object(Linked, "dolphin/card/CARDCheck.c"),
            Object(Linked, "dolphin/card/CARDMount.c"),
            Object(Linked, "dolphin/card/CARDFormat.c"),
            Object(Linked, "dolphin/card/CARDOpen.c"),
            Object(Linked, "dolphin/card/CARDCreate.c"),
            Object(Linked, "dolphin/card/CARDRead.c"),
            Object(Linked, "dolphin/card/CARDWrite.c"),
            Object(Linked, "dolphin/card/CARDDelete.c"),
            Object(Linked, "dolphin/card/CARDStat.c"),
            Object(Linked, "dolphin/card/CARDNet.c"),
        ],
    ),
    DolphinLib(
        "thp",
        [
            Object(Linked, "dolphin/thp/THPDec.c"),
            Object(Linked, "dolphin/thp/THPAudio.c"),
        ],
    ),
    DolphinLib(
        "tex",
        [
            Object(Linked, "dolphin/tex/texPalette.c"),
        ],
    ),
    MetroTRKLib(
        "metrotrk",
        [
            Object(Linked, "metrotrk/mainloop.c"),
            Object(Linked, "metrotrk/nubevent.c"),
            Object(Linked, "metrotrk/nubinit.c"),
            Object(Linked, "metrotrk/msg.c"),
            Object(Linked, "metrotrk/msgbuf.c"),
            Object(Linked, "metrotrk/serpoll.c"),
            Object(Linked, "metrotrk/usr_put.c"),
            Object(Linked, "metrotrk/dispatch.c"),
            Object(Linked, "metrotrk/msghndlr.c"),
            Object(Linked, "metrotrk/support.c"),
            Object(Linked, "metrotrk/mutex_TRK.c"),
            Object(Linked, "metrotrk/notify.c"),
            Object(Linked, "metrotrk/flush_cache.c"),
            Object(Linked, "metrotrk/mem_TRK.c"),
            Object(Linked, "metrotrk/__exception.s"),
            Object(Linked, "metrotrk/targimpl.c"),
            Object(Linked, "metrotrk/dolphin_trk.c"),
            Object(Linked, "metrotrk/mpc_7xx_603e.c"),
            Object(Linked, "metrotrk/main_TRK.c"),
            Object(Linked, "metrotrk/dolphin_trk_glue.c"),
            Object(Linked, "metrotrk/targcont.c"),
        ]
    ),
    RuntimeLib(
        "runtime",
        [
            Object(Linked, "runtime/__mem.c"),
            Object(Linked, "runtime/__va_arg.c"),
            Object(Linked, "runtime/global_destructor_chain.c"),
            Object(Linked, "runtime/runtime.c"),
        ]
    ),
    LibC(
        "libc",
        [
            Object(Linked, "libc/abort_exit.c"),
            Object(Linked, "libc/ansi_files.c"),
            Object(Linked, "libc/ansi_fp.c", extra_cflags=["-inline noauto"]),
            Object(Linked, "libc/buffer_io.c"),
            Object(Linked, "libc/critical_regions.ppc_eabi.c"),
            Object(Linked, "libc/ctype.c"),
            Object(Linked, "libc/direct_io.c"),
            Object(Linked, "libc/errno.c"),
            Object(Linked, "libc/mbstring.c"),
            Object(Linked, "libc/mem.c"),
            Object(Linked, "libc/mem_funcs.c"),
            Object(Linked, "libc/misc_io.c"),
            Object(Linked, "libc/printf.c"),
            Object(Linked, "libc/scanf.c"),
            Object(Linked, "libc/string.c"),
            Object(Linked, "libc/strtoul.c"),
            Object(Linked, "libc/uart_console_io.c"),
            Object(Linked, "libc/float.c"),
            Object(Linked, "libc/wchar_io.c"),
            Object(Linked, "libc/e_asin.c"),
            Object(Linked, "libc/e_pow.c"),
            Object(Linked, "libc/fminmaxdim.c"),
            Object(Linked, "libc/s_ceil.c"),
            Object(Linked, "libc/s_copysign.c"),
            Object(Linked, "libc/s_floor.c"),
            Object(Linked, "libc/s_frexp.c"),
            Object(Linked, "libc/s_ldexp.c"),
            Object(Linked, "libc/w_pow.c"),
            Object(Linked, "libc/hyperbolicsf.c"),
            Object(Linked, "libc/log10f.c"),
            Object(Linked, "libc/trigf.c"),
            Object(Linked, "libc/math_inlines.c"),
            Object(Linked, "libc/common_float_tables.c"),
        ]
    ),
    DebuggerLib(
        "debugger",
        [
            Object(Linked, "debugger/AmcExi2Stubs.c"),
            Object(Linked, "debugger/DebuggerDriver.c", extra_cflags=["-inline deferred"]),
            Object(Linked, "debugger/odenotstub.c"),
        ]
    ),
]

# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("emulator", "Emulator"),
    ProgressCategory("dolphin", "Dolphin SDK"),
    ProgressCategory("metrotrk", "MetroTRK"),
    ProgressCategory("runtime", "Runtime"),
    ProgressCategory("libc", "Libc"),
    ProgressCategory("debugger", "Debugger"),
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
