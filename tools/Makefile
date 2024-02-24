
ifeq ($(OS),Windows_NT)
    BINUTILS_ZIP=windows-x86_64
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        BINUTILS_ZIP=linux-x86_64
    endif
    ifeq ($(UNAME_S),Darwin)
        BINUTILS_ZIP=macos-universal
    endif
endif

BINUTILS_TAG := 2.42-1
COMPILERS_TAG := 20231018

.PHONY: all clean

all: binutils mwcc_compiler
	$(MAKE) -C elf2dol

clean:
	rm -rf binutils
	rm -rf mwcc_compiler
	$(MAKE) -C elf2dol clean

binutils:
	mkdir -p binutils
	wget https://github.com/encounter/gc-wii-binutils/releases/download/$(BINUTILS_TAG)/$(BINUTILS_ZIP).zip -O binutils/$(BINUTILS_ZIP).zip
	unzip binutils/$(BINUTILS_ZIP).zip -d binutils
	rm binutils/$(BINUTILS_ZIP).zip
	chmod +x binutils/powerpc-eabi-*

mwcc_compiler:
	mkdir -p mwcc_compiler
	wget https://files.decomp.dev/compilers_$(COMPILERS_TAG).zip -O mwcc_compiler/compilers_$(COMPILERS_TAG).zip
	unzip mwcc_compiler/compilers_$(COMPILERS_TAG).zip -d mwcc_compiler
	rm mwcc_compiler/compilers_$(COMPILERS_TAG).zip
	find mwcc_compiler/ -name '*.exe' -exec chmod +x {} \;
