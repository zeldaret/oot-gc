oot-gc  
[![Build Status]][actions] ![mq-j] ![mq-u] ![mq-e] ![ce-j] ![ce-u] ![ce-e] [![Discord Badge]][discord]
=============

[Build Status]: https://github.com/zeldaret/oot-gc/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/zeldaret/oot-gc/actions/workflows/build.yml

[mq-j]: https://img.shields.io/endpoint?label=mq-j&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Foot-gc%2Fmq-j%2Fdol%2F%3Fmode%3Dshield%26measure%3Dcode

[mq-u]: https://img.shields.io/endpoint?label=mq-u&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Foot-gc%2Fmq-j%2Fdol%2F%3Fmode%3Dshield%26measure%3Dcode

[mq-e]: https://img.shields.io/endpoint?label=mq-e&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Foot-gc%2Fmq-j%2Fdol%2F%3Fmode%3Dshield%26measure%3Dcode

[ce-j]: https://img.shields.io/endpoint?label=ce-j&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Foot-gc%2Fce-j%2Fdol%2F%3Fmode%3Dshield%26measure%3Dcode

[ce-u]: https://img.shields.io/endpoint?label=ce-u&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Foot-gc%2Fce-u%2Fdol%2F%3Fmode%3Dshield%26measure%3Dcode

[ce-e]: https://img.shields.io/endpoint?label=ce-e&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Foot-gc%2Fce-e%2Fdol%2F%3Fmode%3Dshield%26measure%3Dcode

[Discord Badge]: https://img.shields.io/discord/688807550715560050?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.zelda.deco.mp/

A work-in-progress decompilation of the N64 emulator used in the GameCube releases of The Legend of Zelda: Ocarina of Time.

Supported versions:

- `mq-j`: Master Quest - Japan
- `mq-u`: Master Quest - North America
- `mq-e`: Master Quest - Europe/Australia
- `ce-j`: Collector's Edition - Japan
- `ce-u`: Collector's Edition - North America
- `ce-e`: Collector's Edition - Europe/Australia

Currently the decompilation mainly targets the `ce-j` version, as the
Collector's Edition disks also contain an ELF file where symbols and other
debugging information were left unstripped.

## Building

### Requirements

You will need the following dependencies:
* git
* ninja
* python3
* wine (for macOS or non-x86 Linux)
* clang-format (optional)

#### Ubuntu/Debian/Windows (WSL)

You can install the dependencies with the following commands:

```
sudo apt-get update
sudo apt-get install git ninja-build python3
```

#### macOS

You can install dependencies via Homebrew with the following command:

```
brew install git ninja python3
brew install --cask --no-quarantine gcenx/wine/wine-crossover
```

#### Windows (Native)

You will need the following dependencies:
- [ninja.exe](https://github.com/ninja-build/ninja/releases/latest)
- Python (make sure to add it to your PATH during the installation)
- [Git for Windows](https://www.git-scm.com/downloads)

You need to add ``C:\Program Files\Git\bin`` to your system's PATH (not the user one) in order to execute bash scripts properly.

To get objdiff to work properly you also need to add the path to the folder containing ``ninja.exe`` to the system's PATH.

### Instructions

1. Clone the repo using `git clone https://github.com/zeldaret/oot-gc`.

2. Extract the following TGC archive containing the N64 emulator from the disc of the version you want to build:

  * `mq-j`: `zlj_f.tgc`
  * `mq-u`: `zlj_f.tgc`
  * `mq-e`: `zlj_f.tgc`
  * `ce-j`: `120903_zelda.tgc`
  * `ce-u`: `zelda_ENG_090903.tgc`
  * `ce-e`: `zelda_PAL_093003.tgc`

  Then, extract the DOL file from the TGC archive and place it in the repo as `orig/<version>/main.dol`.

  You can use [Dolphin](https://dolphin-emu.org) to perform both of these extraction steps:
  first, right click on the `.iso` file, select "Properties", go to the "Filesystem" tab, find the correct
  `.tgc` file, then right-click and select "Extract File..." and extract it to your games folder.
  Then, right-click the extracted `.tgc` file in Dolphin, select "Properties", go to the "Filesystem" tab,
  right-click the "Disc" and select "Extract System Data..." to extract the DOL file.

3. Run `python3 configure.py` to generate the build. (Note: on Windows you might need to run ``python configure.py``.)

4. Run `ninja` to build the `ce-j` version, or run `ninja <version>` to build another version.

## Development Tools

### Scripts

* `./dol-diff <version>` will run `dtk dol diff` to show the first differing symbol if the build does not match.
* `./dol-apply <version>` will run `dtk dol apply` to sync symbols (e.g. if a function was renamed in the repo).
* `./format` will format all source files with `clang-format`.

### objdiff

For local decompilation testing, start the objdiff GUI and open this directory as the project directory.
Currently `objdiff` may not work properly on files using asm-processor (i.e. files with `asm_processor=True` in `configure.py`).

### asm-differ (diff.py)

First, copy a matching build to the `expected/` directory to diff against:

```
mkdir expected
cp -r build expected/
```

Then run e.g. `./diff.py -mwo3 xlMain` to diff a function for `ce-j`, or e.g. `./diff.py -mwo3 xlMain -v mq-j` to diff a function for another version.

### decomp.me

Run `tools/decompme.py <c-file> <asm-file>` (e.g. `tools/decompme.py src/emulator/cpu.c asm/non_matchings/cpu/cpuExecute.s`) to create a
[decomp.me](https://decomp.me/) scratch for a function. The C file and all of its included headers will be used as the context.

### Permuter

To import a function for [decomp-permuter](https://github.com/simonlindholm/decomp-permuter), ensure `powerpc-eabi-objdump` binary
is on your `PATH` (for instance by adding `tools/binutils` from this project) and run something like

```sh
path/to/permuter/import.py src/emulator/THPRead.c asm/non_matchings/THPRead/Reader.s
path/to/permuter/permuter.py nonmatchings/Reader -j 8
```

Sometimes you may need to tweak the source in order for things to import
correctly, for example by explicitly marking auto-inlined functions as `inline`.

### Debug Info

The files in the `debug/` directory contain a dump of the DWARF debugging information in the original ELF. Functions marked as `// Erased`
were present at one time but have been stripped by the linker, because they were either unused or inlined at all call sites.
