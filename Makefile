WINDOWS := $(shell which wine ; echo $$?)

NON_MATCHING := 0

#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------

TARGET_COL := gamecube

TARGET := SIM

BUILD_DIR := build/$(TARGET)

SRC_DIRS := $(shell find src -type d)
ASM_DIRS := $(shell find asm -type d -not -path "asm/non_matchings*")

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Inputs
LDSCRIPT := $(BUILD_DIR)/ldscript.lcf

# Outputs
ELF := $(BUILD_DIR)/$(TARGET).elf
MAP := $(ELF:.elf=.map)
DOL := $(ELF:.elf=.dol)
COMPARE_TO := $(ELF:.elf=_S.elf)

# Object files in link order
include obj_files.mk

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

MWCC_VERSION := GC/1.1

# revision build year, 2002 for MQ, 2003 for CE
DOLPHIN_REVISION := 2003

# Programs
ifeq ($(WINDOWS),1)
	WINE := 
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		WINE := wibo
	else ifeq ($(UNAME_S),Darwin)
		WINE := wine
	endif
endif

PPC_BIN_PREFIX := tools/binutils/powerpc-eabi-
AS := $(PPC_BIN_PREFIX)as
OBJCOPY := $(PPC_BIN_PREFIX)objcopy
OBJDUMP := $(PPC_BIN_PREFIX)objdump

MWCC_DIR := tools/mwcc_compiler/$(MWCC_VERSION)
CC := $(WINE) $(MWCC_DIR)/mwcceppc.exe
LD := $(WINE) $(MWCC_DIR)/mwldeppc.exe

DOLPHIN_MWCC_DIR := tools/mwcc_compiler/GC/1.2.5n
DOLPHIN_CC := $(WINE) $(DOLPHIN_MWCC_DIR)/mwcceppc.exe

SHA1SUM := sha1sum
PYTHON := python3
ELF2DOL := tools/elf2dol/elf2dol

ASM_PROCESSOR_DIR := tools/asm_processor
ASM_PROCESSOR := $(ASM_PROCESSOR_DIR)/compile.sh

POSTPROC := tools/postprocess.py

# Options
INCLUDES := -Iinclude -Ilibc

# Assembler Flags
ASFLAGS := -mgekko -I include -I libc

# Linker Flags
LDFLAGS := -map $(MAP) -fp hardware -nodefaults -warn off

# Compiler Flags
CFLAGS := -Cpp_exceptions off -proc gekko -fp hardware -fp_contract on -enum int -O4,p -sym on -nodefaults -msgstyle gcc $(INCLUDES) -DDOLPHIN_REV=$(DOLPHIN_REVISION)

ifneq ($(NON_MATCHING),0)
	CFLAGS += -DNON_MATCHING
endif

DOLPHIN_CFLAGS := $(CFLAGS) -align powerpc -maxerrors 1 -nosyspath -RTTI off -str reuse -multibyte -inline auto
EMULATOR_CFLAGS := $(CFLAGS) -inline auto,deferred

# elf2dol needs to know these in order to calculate sbss correctly.
SDATA_PDHR 	:= 9
SBSS_PDHR 	:= 10

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

### Default target ###

default: all

# Compare to the checksum of a stripped original
all: $(ELF)
ifneq ($(NON_MATCHING),1)
	@md5sum $(COMPARE_TO)
	@md5sum -c checksum.md5
endif

setup:
# Build/download tools
	$(MAKE) -C tools
# Patch linker
	tools/patch_linker.sh $(MWCC_DIR)/mwldeppc.exe
# Strip debugging sections and .mwcats.text section so only the important sections remain
# Tested to ensure it doesn't crash at least on Dolphin
	$(OBJCOPY) SIM_original.elf SIM.elf -R .mwcats.text -g
# Copy again to strip symbols since we don't want to diff those
	$(OBJCOPY) SIM.elf SIM_S.elf -S

clean:
	rm -f -d -r build

distclean:
	rm -f -r SIM.elf SIM_S.elf
	$(MAKE) -C tools clean

format:
	find include src -name '*.h' -o -name '*.c' | xargs clang-format -i

# Note: this is meant for testing/modding purposes as a dol is easier to package and run than the original elf
dol: all $(DOL)

.PHONY: all setup clean format dol distclean

ALL_DIRS := build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

$(ELF): $(O_FILES) ldscript.lcf
	$(RM) -rf $(ASM_PROCESSOR_DIR)/tmp
	$(LD) $(LDFLAGS) -o $@ -lcf ldscript.lcf $(O_FILES)
	$(OBJCOPY) $(ELF) $(COMPARE_TO) -S

$(DOL): $(ELF)
	$(ELF2DOL) $< $@ $(SDATA_PDHR) $(SBSS_PDHR) $(TARGET_COL)

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/src/dolphin/%.o: src/dolphin/%.c
	$(ASM_PROCESSOR) "$(DOLPHIN_CC) $(DOLPHIN_CFLAGS)" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/%.o: src/emulator/%.c
	$(ASM_PROCESSOR) "$(CC) $(EMULATOR_CFLAGS)" "$(AS) $(ASFLAGS)" $@ $<
