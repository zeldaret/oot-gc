# oot-gc

This repo contains a WIP decompilation of the N64 Emulator ELF executable intended for use with the Gamecube releases of The Legend of Zelda Ocarina of Time. Currently the decompilation specifically targets the version shipped with the Japanese Zelda Collector's Edition disk as symbols and other debugging information was left unstripped.

It builds the following ELF executables:

SIM.elf   : `md5: 64428C7350B31E0AAD3DDE221C5B18A5`
SIM_S.elf : `md5: EDDD2DED9906AD2312F7EC585B3D72CE`

SIM_S is a version of the build with stripped symbols which when diffed against a similarly stripped original matches byte for byte if assembled and linked, which is the most realistic goal for verifying the accuracy of the decompilation.

## Building

### Requirements

You will need the following dependencies:
* gcc or clang
* make
* git
* python3
* wibo (Linux) or wine (macOS)
* wget
* unzip
* clang-format (optional)

#### Ubuntu/Debian

In order to install `wibo`, you will need to [download it](https://github.com/decompals/wibo/releases) and run:

```
sudo install wibo /usr/bin
```

You can install the dependencies with the following commands:

```
sudo apt-get update
sudo apt-get install build-essential git python3 wget unzip
```

#### macOS

You can install dependencies via Homebrew with the following command:

```
brew install coreutils python3 wget wine
```

### Instructions

1. Obtain the original ELF executable found in the `120903_zelda.tgc` file on the Japanese Collector's Edition disk and place it in the base working directory and name it `SIM_original.elf`
2. Run `make setup` and `make`

## Development

First, copy a matching build to the `expected/` directory to diff against:

```
mkdir expected
cp -r build expected/
```

### Diff tools

For locally diffing the current build against the expected build:

* `objdiff`: Start the objdiff GUI and open this directory as the project directory.
* `diff.py` (`asm-differ`): Run e.g. `./diff.py -mwo3 xlMain` to diff a function.
* `vbindiff`: Run `vbindiff SIM_S.elf build/SIM/SIM_S.elf` to directly diff the
  ELF files to debug tricky matching issues, using the ELF section headers and
  the linker map file to locate the diffs in the code.

### decomp.me

Run `tools/decompme.py <c-file> <asm-file>` (e.g. `tools/decompme.py src/emulator/cpu.c asm/non_matchings/cpu/cpuExecute.s`) to create a
[decomp.me](https://decomp.me/) scratch for a function. The C file and all of its included headers will be used as the context.

### Permuter

To import a function for [decomp-permuter](https://github.com/simonlindholm/decomp-permuter), ensure `powerpc-eabi-objdump` binary is on your `PATH`
(for instance by adding `tools/binutils` from this project) and run `path/to/permuter/import.py <c-file> <asm-file>`
(e.g. `path/to/permuter/import.py src/emulator/cpu.c asm/non_matchings/cpu/cpuExecute.s`). Sometimes you may need to tweak the source in
order for things to import correctly, for example by explicitly marking auto-inlined functions as `inline`.

### Debug Info

The files in the `debug/` directory contain a dump of the DWARF debugging information in the original ELF. Functions marked as `// Erased`
were present at one time but have been stripped by the linker, because they were either unused or inlined at all call sites.

### Migrating a file to C

All emulator files have been migrated to C, but some SDK and standard library files are still built from the disassembly. Before decompiling
one of these files:

* In `obj_files.mk`, replace `$(BUILD_DIR)/asm/<path>.o` with `$(BUILD_DIR)/src/<path>.o` to link the new object file
* Add an entry in `objdiff.json`
* Run `cp expected/build/SIM/asm/<path>.o expected/build/SIM/src/<path>.o` to create a base to diff against
