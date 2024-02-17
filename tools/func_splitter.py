#!/usr/bin/env python3

import argparse
import os


def splitAsm(inputFile: str):
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

        # create the folders if necessary
        os.makedirs(os.path.dirname(f"asm/non_matchings/{inputFile}/"), exist_ok=True)

        # reverse function order for -inline deferred
        parsedFunctions.reverse()

        # write the files
        for i, (functionName, functionData) in enumerate(parsedFunctions):
            cPath = f"src/{inputFile}.c"
            cData = ""
            newline = "\n" * 2

            with open(f"asm/non_matchings/{inputFile}/{functionName}.s", "w") as asmFile:
                asmFile.write("".join(functionData))

            if os.path.isfile(cPath):
                with open(cPath, "r") as cFile:
                    cData = cFile.read()

                if i == len(parsedFunctions) - 1:
                    newline = "\n"

            with open(cPath, "w") as cFile:
                cFile.write(cData + f'#pragma GLOBAL_ASM("asm/non_matchings/{inputFile}/{functionName}.s")' + newline)

            with open("obj_files.mk", "w") as linkerFile:
                linkerFile.write(data.replace(f"/asm/{inputFile}.o", f"/src/{inputFile}.o"))


def main():
    parser = argparse.ArgumentParser(description="asm function splitter (creates C files and updates obj_files.mk)")
    parser.add_argument("file", help="asm file name")

    # get the original asm file's name
    args = parser.parse_args()
    inputFile: str = args.file

    # if it's a path, keep the filename part
    if "/" in inputFile:
        inputFile = inputFile.split("/")[-1]

    # remove the extension if present
    if inputFile.endswith(".s"):
        inputFile = inputFile[:-2]

    splitAsm(inputFile)


if __name__ == "__main__":
    main()
