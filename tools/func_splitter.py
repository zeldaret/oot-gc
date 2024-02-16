#!/usr/bin/env python3

import argparse
import os

from typing import Optional


groupToFiles = {
    "Core": [
        "xlCoreGCN",
        "xlPostGCN",
        "xlFileGCN",
        "xlList",
        "xlHeap",
        "xlObject",
    ],
    "Fire": [
        "simGCN",
        "movie",
        "THPPlayer",
        "THPAudioDecode",
        "THPDraw",
        "THPRead",
        "THPVideoDecode",
        "mcardGCN",
        "codeGCN",
        "soundGCN",
        "frame",
        "system",
        "cpu",
        "pif",
        "ram",
        "rom",
        "rdp",
        "rdb",
        "rsp",
        "mips",
        "disk",
        "flash",
        "sram",
        "audio",
        "video",
        "serial",
        "library",
        "peripheral",
        "_frameGCNcc",
        "_buildtev",
    ],
    "Dolphin": [
        "PPCArch",
        "OS",
        "OSAlarm",
        "OSAlloc",
        "OSArena",
        "OSAudioSystem",
        "OSCache",
        "OSContext",
        "OSError",
        "OSFont",
        "OSInterrupt",
        "OSLink",
        "OSMessage",
        "OSMemory",
        "OSMutex",
        "OSReboot",
        "OSReset",
        "OSResetSW",
        "OSRtc",
        "OSSync",
        "OSThread",
        "OSTime",
        "__start",
        "__ppc_eabi_init",
        "EXIBios",
        "EXIUart",
        "SIBios",
        "SISamplingRate",
        "vi",
        "db",
        "mtx",
        "mtxvec",
        "mtx44",
        "GXInit",
        "GXFifo",
        "GXAttr",
        "GXMisc",
        "GXGeometry",
        "GXFrameBuf",
        "GXLight",
        "GXTexture",
        "GXBump",
        "GXTev",
        "GXPixel",
        "GXTransform",
        "GXPerf",
        "Padclamp",
        "Pad",
        "dvdlow",
        "dvdfs",
        "dvd",
        "dvdqueue",
        "dvderror",
        "dvdidutils",
        "dvdFatal",
        "fstload",
        "DEMOInit",
        "DEMOPuts",
        "DEMOFont",
        "DEMOPad",
        "DEMOStats",
        "ai",
        "ar",
        "dsp",
        "dsp_debug",
        "dsp_task",
        "CARDBios",
        "CARDUnlock",
        "CARDRdwr",
        "CARDBlock",
        "CARDDir",
        "CARDCheck",
        "CARDMount",
        "CARDFormat",
        "CARDOpen",
        "CARDCreate",
        "CARDRead",
        "CARDWrite",
        "CARDDelete",
        "CARDStat",
        "CARDNet",
        "THPDec",
        "THPAudio",
    ],
    "Undefined1": [
        "texPalette",
    ],
    "TRK": [
        "mainloop",
        "nubevent",
        "nubinit",
        "msg",
        "msgbuf",
        "serpoll",
        "usr_put",
        "dispatch",
        "msghndlr",
        "support",
        "mutex_TRK",
        "notify",
        "flush_cache",
        "mem_TRK",
        "__exception",
        "targimpl",
        "dolphin_trk",
        "mpc_7xx_603e",
        "main_TRK",
        "dolphin_trk_glue",
        "targcont",
    ],
    "Runtime": [
        "__mem",
        "__va_arg",
        "global_destructor_chain",
        "runtime",
    ],
    "MSL": [
        "abort_exit",
        "ansi_files",
        "ansi_fp",
        "buffer_io",
        "critical_regions.ppc_eabi",
        "ctype",
        "direct_io",
        "errno",
        "mbstring",
        "mem",
        "mem_funcs",
        "misc_io",
        "printf",
        "scanf",
        "string",
        "strtoul",
        "uart_console_io",
        "float",
        "wchar_io",
        "e_asin",
        "e_pow",
        "fminmaxdim",
        "s_ceil",
        "s_copysign",
        "s_floor",
        "s_frexp",
        "s_ldexp",
        "w_pow",
        "hyperbolicsf",
        "log10f",
        "trigf",
        "math_inlines",
        "common_float_tables",
    ],
    "Undefined2": [
        "AmcExi2Stubs",
        "DebuggerDriver",
        "odenotstub",
    ],
}


def splitAsm(inputFile: str, inputGroup: Optional[str]):
    # get the original asm file's data
    with open(f"asm/{inputFile}.s", "r") as asmFile:
        lines = asmFile.readlines()
        asmFile.seek(0)
        rawData = asmFile.read()

    # parse functions names and their data
    foundFunction = False
    functionName = ""
    functionData: list[str] = []
    parsedFunctions: list[tuple[str, list[str]]] = []

    # if the file has functions
    if ".section .text" in rawData or ".section .init" in rawData:
        for i, line in enumerate(lines):
            previousIsNewLine = lines[i - 1] == "\n"

            # if end of a section containing functions
            if (
                line.startswith(".section .")
                and not line.startswith(".section .text")
                and not line.startswith(".section .init")
                and previousIsNewLine
            ):
                break

            # if we found a new function
            if (
                not line.startswith("lbl_")
                and (line.startswith("glabel") or ":\n" in line)
                and not foundFunction
                and previousIsNewLine
            ):
                foundFunction = True
                if line.startswith("glabel"):
                    functionName = line.split(" ")[1].removesuffix("\n")
                else:
                    functionName = line.split(":")[0].removesuffix("\n")

            # if a function was found
            if foundFunction:
                if line == "\n" or i == (len(lines) - 1):
                    parsedFunctions.append((functionName, functionData))
                    functionData = []
                    functionName = ""
                    foundFunction = False
                else:
                    if line.startswith(f"{functionName}:"):
                        line = f"glabel {functionName}\n"
                    functionData.append(line)
        assert len(parsedFunctions) > 0

        # read the linker file
        with open("obj_files.mk", "r") as linkerFile:
            data = linkerFile.read()

        # get the folder path
        if inputGroup is None:
            inputGroup = ""
        folderPath = f"asm/non_matchings" + (f"/{inputGroup}" if len(inputGroup) > 0 else "")

        # create the folders if necessary
        os.makedirs(os.path.dirname(f"{folderPath}/{inputFile}/"), exist_ok=True)
        os.makedirs(os.path.dirname(f"src/{inputGroup}/"), exist_ok=True)

        # write the files
        for i, (functionName, functionData) in enumerate(parsedFunctions):
            cPath = f"src/{inputGroup}/{inputFile}.c"
            cData = ""
            newline = "\n" * 2

            with open(f"{folderPath}/{inputFile}/{functionName}.s", "w") as asmFile:
                asmFile.write("".join(functionData))

            if os.path.isfile(cPath):
                with open(cPath, "r") as cFile:
                    cData = cFile.read()

                if i == len(parsedFunctions) - 1:
                    newline = "\n"

            with open(cPath, "w") as cFile:
                cFile.write(cData + f'#pragma GLOBAL_ASM("{folderPath}/{inputFile}/{functionName}.s")' + newline)

            oPath = "/src/" + ((inputGroup + "/") if len(inputGroup) > 0 else "") + f"{inputFile}.o"
            with open("obj_files.mk", "w") as linkerFile:
                linkerFile.write(data.replace(f"/asm/{inputFile}.o", oPath))


def main():
    parser = argparse.ArgumentParser(description="asm function splitter (creates C files and updates obj_files.mk)")
    parser.add_argument("--file", "-f", help="asm file name", dest="file", required=False)
    parser.add_argument("--group", "-g", help="asm group name", dest="group", required=False)
    parser.add_argument("--all", "-a", help="split everything", dest="all", action="store_true", required=False)

    # get the original asm file's name
    args = parser.parse_args()
    inputFile: str = args.file
    inputGroup: str = args.group
    doSplitAll: bool = args.all

    if doSplitAll:
        for group, files in groupToFiles.items():
            if group in {"Undefined1", "Undefined2"}:
                group = None
            for file in files:
                splitAsm(file, group)
    elif inputFile is not None and os.path.isfile(inputFile):
        # if it's a path, keep the filename part
        if "/" in inputFile:
            inputFile = inputFile.split("/")[-1]

        # remove the extension if present
        if inputFile.endswith(".s"):
            inputFile = inputFile[:-2]

        splitAsm(inputFile, None)
    elif inputGroup is not None and len(inputGroup) > 0:
        files = groupToFiles.get(inputGroup)

        if files is None:
            raise ValueError(f"ERROR: can't find group named ``{repr(inputGroup)}``")

        for file in files:
            splitAsm(file, inputGroup)
    else:
        raise ValueError("ERROR: provide a group name or a file name")


if __name__ == "__main__":
    main()
