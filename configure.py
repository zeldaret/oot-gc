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
    "--no-asm-processor",
    action="store_true",
    help="disable asm_processor for progress calculation",
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

if not config.versions:
    sys.exit("Error: no main.dol found for any version")

if "ce-j" in config.versions:
    config.default_version = "ce-j"
else:
    # Use the earliest version as default
    config.default_version = config.versions[0]

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
config.asm_processor = not args.no_asm_processor

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
            Object(LinkedFor("mq-e", "ce-e"), "emulator/xlText.c"),
            Object(Linked, "emulator/xlList.c"),
            Object(Linked, "emulator/xlHeap.c"),
            Object(LinkedFor("mq-e", "ce-e"), "emulator/xlFile.c"),
            Object(Linked, "emulator/xlObject.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "emulator/simGCN.c"),
            Object(Linked, "emulator/movie.c"),
            # THP files except for THPRead.c do not have -inline deferred
            Object(Linked, "emulator/THPPlayer.c", cflags=cflags_base),
            Object(Linked, "emulator/THPAudioDecode.c", cflags=cflags_base),
            Object(Linked, "emulator/THPDraw.c", cflags=cflags_base),
            Object(Linked, "emulator/THPRead.c"),
            Object(Linked, "emulator/THPVideoDecode.c", cflags=cflags_base),
            Object(LinkedFor("ce-j"), "emulator/mcardGCN.c"),
            Object(Linked, "emulator/codeGCN.c"),
            Object(Linked, "emulator/soundGCN.c"),
            Object(LinkedFor("ce-j"), "emulator/frame.c", asm_processor=True),
            Object(Linked, "emulator/system.c"),
            Object(LinkedFor("ce-j"), "emulator/cpu.c", asm_processor=True),
            Object(Linked, "emulator/pif.c"),
            Object(Linked, "emulator/ram.c"),
            Object(Linked, "emulator/rom.c"),
            Object(Linked, "emulator/rdp.c"),
            Object(Linked, "emulator/rdb.c"),
            Object(LinkedFor("ce-j"), "emulator/rsp.c", asm_processor=True),
            Object(Linked, "emulator/mips.c"),
            Object(Linked, "emulator/disk.c"),
            Object(Linked, "emulator/flash.c"),
            Object(Linked, "emulator/sram.c"),
            Object(Linked, "emulator/audio.c"),
            Object(Linked, "emulator/video.c"),
            Object(Linked, "emulator/serial.c"),
            Object(Linked, "emulator/library.c"),
            Object(Linked, "emulator/peripheral.c"),
            Object(LinkedFor("ce-j"), "emulator/_frameGCNcc.c", asm_processor=True),
            Object(LinkedFor("ce-j"), "emulator/_buildtev.c", asm_processor=True),
        ],
    ),
    DolphinLib(
        "base",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OS.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSAlarm.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSAlloc.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSArena.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSAudioSystem.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSCache.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSContext.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSError.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSFont.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSInterrupt.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSLink.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSMessage.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSMemory.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSMutex.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSReboot.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSReset.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSResetSW.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSRtc.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/os/OSSync.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSThread.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/OSTime.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/__start.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/os/__ppc_eabi_init.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/exi/EXIBios.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/si/SIBios.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/si/SISamplingRate.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/mtx/mtx.c", extra_cflags=["-fp_contract off"]),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/mtx/mtxvec.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/mtx/mtx44.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXInit.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXFifo.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXAttr.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXMisc.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXGeometry.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXFrameBuf.c"),
            Object(LinkedFor("ce-j", "ce-u"), "dolphin/gx/GXLight.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXTexture.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXBump.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXTev.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXPixel.c", extra_cflags=["-fp_contract off"]),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXTransform.c", extra_cflags=["-fp_contract off"]),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/pad/Padclamp.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/dvd/dvdlow.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/dvd/dvdfs.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/dvd/dvd.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/dvd/dvdqueue.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/dvd/dvderror.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/dvd/dvdidutils.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/dvd/dvdFatal.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "demo",
        [
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/demo/DEMOInit.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/demo/DEMOPuts.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/demo/DEMOFont.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/demo/DEMOPad.c"),
            Object(LinkedFor("mq-j", "mq-u", "mq-e", "ce-j", "ce-u"), "dolphin/demo/DEMOStats.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/ar/ar.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dsp/dsp.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dsp/dsp_debug.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDBios.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDUnlock.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDRdwr.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDBlock.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDDir.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDCheck.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDMount.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDFormat.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDOpen.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDCreate.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDRead.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDWrite.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDDelete.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDStat.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/card/CARDNet.c"),
        ],
    ),
    DolphinLib(
        "thp",
        [
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/thp/THPDec.c"),
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/thp/THPAudio.c"),
        ],
    ),
    DolphinLib(
        "tex",
        [
            Object(LinkedFor("mq-j", "mq-u", "ce-j", "ce-u"), "dolphin/tex/texPalette.c"),
        ],
    ),
    GenericLib(
        "metrotrk",
        cflags_base,
        [
            Object(NotLinked, "metrotrk/mainloop.c"),
            Object(NotLinked, "metrotrk/nubevent.c"),
            Object(NotLinked, "metrotrk/nubinit.c"),
            Object(NotLinked, "metrotrk/msg.c"),
            Object(NotLinked, "metrotrk/msgbuf.c"),
            Object(NotLinked, "metrotrk/serpoll.c"),
            Object(NotLinked, "metrotrk/usr_put.c"),
            Object(NotLinked, "metrotrk/dispatch.c"),
            Object(NotLinked, "metrotrk/msghndlr.c"),
            Object(NotLinked, "metrotrk/support.c"),
            Object(NotLinked, "metrotrk/mutex_TRK.c"),
            Object(NotLinked, "metrotrk/notify.c"),
            Object(NotLinked, "metrotrk/flush_cache.c"),
            Object(NotLinked, "metrotrk/mem_TRK.c"),
            Object(NotLinked, "metrotrk/__exception.c"),
            Object(NotLinked, "metrotrk/targimpl.c"),
            Object(NotLinked, "metrotrk/dolphin_trk.c"),
            Object(NotLinked, "metrotrk/mpc_7xx_603e.c"),
            Object(NotLinked, "metrotrk/main_TRK.c"),
            Object(NotLinked, "metrotrk/dolphin_trk_glue.c"),
            Object(NotLinked, "metrotrk/targcont.c"),
        ]
    ),
    GenericLib(
        "runtime",
        [*cflags_base, "-inline deferred"],
        [
            Object(Linked, "runtime/__mem.c"),
            Object(Linked, "runtime/__va_arg.c"),
            Object(Linked, "runtime/global_destructor_chain.c"),
            Object(Linked, "runtime/runtime.c"),
        ]
    ),
    GenericLib(
        "libc",
        [*cflags_base, "-inline deferred", "-str pool,readonly"],
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
    GenericLib(
        "debugger",
        cflags_base,
        [
            Object(Linked, "debugger/AmcExi2Stubs.c"),
            Object(NotLinked, "debugger/DebuggerDriver.c"),
            Object(Linked, "debugger/odenotstub.c"),
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
