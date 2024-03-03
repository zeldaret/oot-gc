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
* 32-bit wine
* wget
* unzip
* clang-format (optional)

#### Ubuntu/Debian

In order to install the 32-bit version of Wine, you will need to run:

```
sudo dpkg --add-architecture i386
sudo apt-get update
```

You can install the dependencies with the following commands:

```
sudo apt-get update
sudo apt-get install build-essential git python3 wine32:i386 wget unzip
```

### macOS

You can install dependencies via Homebrew with the following command:

```
brew install coreutils python3 wget wine
```

### Instructions

1. Obtain the original ELF executable found in the `120903_zelda.tgc` file on the Japanese Collector's Edition disk and place it in the base working directory and name it `SIM_original.elf`
2. Run `make setup` and `make`
