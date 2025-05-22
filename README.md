oot-gc  
[![Build Status]][actions] ![mq-j] ![mq-u] ![mq-e] ![ce-j] ![ce-u] ![ce-e] [![Discord Badge]][discord]
=============

[Build Status]: https://github.com/zeldaret/oot-gc/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/zeldaret/oot-gc/actions/workflows/build.yml

[mq-j]: https://decomp.dev/zeldaret/oot-gc/mq-j.svg?mode=shield&label=mq-j

[mq-u]: https://decomp.dev/zeldaret/oot-gc/mq-u.svg?mode=shield&label=mq-u

[mq-e]: https://decomp.dev/zeldaret/oot-gc/mq-e.svg?mode=shield&label=mq-e

[ce-j]: https://decomp.dev/zeldaret/oot-gc/ce-j.svg?mode=shield&label=ce-j

[ce-u]: https://decomp.dev/zeldaret/oot-gc/ce-u.svg?mode=shield&label=ce-u

[ce-e]: https://decomp.dev/zeldaret/oot-gc/ce-e.svg?mode=shield&label=ce-e

[Discord Badge]: https://img.shields.io/discord/688807550715560050?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.zelda.deco.mp/

A work-in-progress decompilation of the N64 emulator used in the GameCube releases of The Legend of Zelda: Ocarina of Time.

Supported versions:

- `mq-j`: Ocarina of Time (Master Quest) - Japan
- `mq-u`: Ocarina of Time (Master Quest) - North America
- `mq-e`: Ocarina of Time (Master Quest) - Europe/Australia
- `ce-j`: Ocarina of Time (Collector's Edition) - Japan
- `ce-u`: Ocarina of Time (Collector's Edition) - North America
- `ce-e`: Ocarina of Time (Collector's Edition) - Europe/Australia
- `mm-j`: Majora's Mask (Collector's Edition) - Japan
- `mm-u`: Majora's Mask (Collector's Edition) - North America
- `mm-e`: Majora's Mask (Collector's Edition) - Europe/Australia

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

2. Copy the disc image of the version you want to decompile into the appropriate `orig/*` directory. _(Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC)_

3. Run `python3 configure.py` to generate the build. (Note: on Windows you might need to run ``python configure.py``.)

4. Run `ninja` to build the `ce-j` version, or run `ninja <version>` to build another version.

5. After the initial build, you can delete the disc image(s) from the `orig/*` directories.

## Development Tools

### Scripts

* `./dol-diff <version>` will run `dtk dol diff` to show the first differing symbol if the build does not match.
* `./dol-apply <version>` will run `dtk dol apply` to sync symbols (e.g. if a function was renamed in the repo).
* `./format` will format all source files with `clang-format`.

### objdiff

For local decompilation testing, start the objdiff GUI and open this directory as the project directory.

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
is on your `PATH` (for instance by adding `build/binutils` from this project) and run something like

```sh
path/to/permuter/import.py src/emulator/THPRead.c asm/non_matchings/THPRead/Reader.s
path/to/permuter/permuter.py nonmatchings/Reader -j 8
```

Sometimes you may need to tweak the source in order for things to import
correctly, for example by explicitly marking auto-inlined functions as `inline`.

### Debug Info

The files in the `debug/` directory contain a dump of the DWARF debugging information in the original ELF. Functions marked as `// Erased`
were present at one time but have been stripped by the linker, because they were either unused or inlined at all call sites.
