WINDOWS := $(shell which wine ; echo $$?)

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
MAP := $(BUILD_DIR)/$(TARGET).map
COMPARE_TO := $(BUILD_DIR)/$(TARGET)_S.elf

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

AS := $(DEVKITPPC)/bin/powerpc-eabi-as
OBJCOPY := $(DEVKITPPC)/bin/powerpc-eabi-objcopy
OBJDUMP := $(DEVKITPPC)/bin/powerpc-eabi-objdump
CPP := cpp
CC := $(WINE) tools/mwcc_compiler/$(MWCC_VERSION)/mwcceppc.exe
LD := $(WINE) tools/mwcc_compiler/$(MWCC_VERSION)/mwldeppc.exe
SHA1SUM := sha1sum
PYTHON := python3

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
CFLAGS := -Cpp_exceptions off -proc gekko -fp hard -enum int -O4,p -inline deferred -sym on -nodefaults -msgstyle gcc $(INCLUDES)

# postprocess
PROCFLAGS := -fprologue-fixup=old_stack

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

### Default target ###

default: all

# Compare to the checksum of a stripped original
all: $(ELF)
	@md5sum $(COMPARE_TO)
	@md5sum -c checksum.md5

# Strip debugging sections and .mwcats.text section so only the important sections remain
# Tested to ensure it doesn't crash at least on Dolphin
# Also copy again to strip symbols since we don't want to diff those
setup:
	$(OBJCOPY) SIM_original.elf SIM.elf -R .mwcats.text -g
	$(OBJCOPY) SIM.elf SIM_S.elf -S

clean:
	rm -f -d -r build

format:
	clang-format -i include/*.h src/*.c

.PHONY: all setup clean format

ALL_DIRS := build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

$(LDSCRIPT): ldscript.lcf
	$(CPP) -P -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(ELF): $(O_FILES) $(LDSCRIPT)
	$(RM) -rf $(ASM_PROCESSOR_DIR)/tmp
	$(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) $(O_FILES)
	$(OBJCOPY) $(ELF) $(COMPARE_TO) -S

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS)" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
