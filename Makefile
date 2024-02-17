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
MAP := $(ELF:.elf=.map)/
DOL := $(ELF:.elf=.dol)
COMPARE_TO := $(ELF:.elf=_S.elf)

# Object files in link order
include obj_files.mk

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

MWCC_VERSION := 1.1

# Programs
ifeq ($(WINDOWS),1)
	WINE := 
else
	WINE := wine
endif

PPC_BIN_PREFIX := $(DEVKITPPC)/bin/powerpc-eabi-
AS := $(PPC_BIN_PREFIX)as
OBJCOPY := $(PPC_BIN_PREFIX)objcopy
OBJDUMP := $(PPC_BIN_PREFIX)objdump

MWCC_DIR := tools/mwcc_compiler/$(MWCC_VERSION)
CC := $(WINE) $(MWCC_DIR)/mwcceppc.exe
LD := $(WINE) $(MWCC_DIR)/mwldeppc.exe

CPP := cpp
SHA1SUM := sha1sum
PYTHON := python3
ELF2DOL := tools/elf2dol/elf2dol

ASM_PROCESSOR_DIR := tools/asm_processor
ASM_PROCESSOR := $(ASM_PROCESSOR_DIR)/compile.sh

POSTPROC := tools/postprocess.py

# Options
INCLUDES := -i include

# Assembler Flags
ASFLAGS := -mgekko -I include

# Linker Flags
LDFLAGS := -map $(MAP) -fp hard -nodefaults -w off

# Compiler Flags
CFLAGS := -Cpp_exceptions off -proc gekko -fp hard -enum int -O4,p -sym on -nodefaults -msgstyle gcc $(INCLUDES)
ifneq ($(NON_MATCHING),0)
	CFLAGS += -DNON_MATCHING
endif

# postprocess
PROCFLAGS := -fprologue-fixup=old_stack

# elf2dol needs to know these in order to calculate sbss correctly.
SDATA_PDHR 	:= 9
SBSS_PDHR 	:= 10

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

### Default target ###

default: all

# Compare to the checksum of a stripped original
all: $(ELF) compare

compare:
ifneq ($(NON_MATCHING),1)
	@md5sum $(COMPARE_TO)
	@md5sum -c checksum.md5
endif

# Strip debugging sections and .mwcats.text section so only the important sections remain
# Tested to ensure it doesn't crash at least on Dolphin
# Also copy again to strip symbols since we don't want to diff those
setup:
	$(OBJCOPY) SIM_original.elf SIM.elf -R .mwcats.text -g
	$(OBJCOPY) SIM.elf SIM_S.elf -S
	$(MAKE) -C tools/elf2dol

clean:
	rm -f -d -r build

distclean:
	rm -f -r SIM.elf SIM_S.elf
	$(MAKE) -C tools/elf2dol clean

format:
	clang-format -i include/*.h src/*.c

# Note: this is meant for testing/modding purposes as a dol is easier to package and run than the original elf
dol: $(DOL) compare

.PHONY: all setup clean format dol distclean

ALL_DIRS := build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

$(LDSCRIPT): ldscript.lcf
	$(CPP) -P -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(ELF): $(O_FILES) $(LDSCRIPT)
	$(RM) -rf $(ASM_PROCESSOR_DIR)/tmp
	$(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) $(O_FILES)
	$(OBJCOPY) $(ELF) $(COMPARE_TO) -S

$(DOL): $(ELF)
	$(ELF2DOL) $< $@ $(SDATA_PDHR) $(SBSS_PDHR) $(TARGET_COL)

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS)" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
