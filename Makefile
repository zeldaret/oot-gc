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

# Programs
ifeq ($(WINDOWS),1)
	WINE := 
else
	WINE := wine
endif

PPC_BIN_PREFIX := tools/binutils/powerpc-eabi-
AS := $(PPC_BIN_PREFIX)as
OBJCOPY := $(PPC_BIN_PREFIX)objcopy
OBJDUMP := $(PPC_BIN_PREFIX)objdump

MWCC_DIR := tools/mwcc_compiler/$(MWCC_VERSION)
CC := $(WINE) $(MWCC_DIR)/mwcceppc.exe
LD := $(WINE) $(MWCC_DIR)/mwldeppc.exe

ASM_PROCESSOR := tools/asm_processor/asm_processor.py
ELF2DOL := tools/elf2dol/elf2dol

# Options
INCLUDES := -Iinclude

# Assembler Flags
ASFLAGS := -mgekko -I include

# Linker Flags
LDFLAGS := -map $(MAP) -fp hard -nodefaults -w off

# Compiler Flags
CFLAGS := -Cpp_exceptions off -proc gekko -fp hard -fp_contract on -enum int -O4,p -inline auto,deferred -sym on -nodefaults -msgstyle gcc $(INCLUDES)
ifneq ($(NON_MATCHING),0)
	CFLAGS += -DNON_MATCHING
endif

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
	$(LD) $(LDFLAGS) -o $@ -lcf ldscript.lcf $(O_FILES)
	$(OBJCOPY) $(ELF) $(COMPARE_TO) -S

$(DOL): $(ELF)
	$(ELF2DOL) $< $@ $(SDATA_PDHR) $(SBSS_PDHR) $(TARGET_COL)

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	$(ASM_PROCESSOR) --assembler "$(AS) $(ASFLAGS)" $< > $(@:.o=.asm_processor.c)
	$(CC) $(CFLAGS) -c $(@:.o=.asm_processor.c) -o $(@:.o=.asm_processor.o)
	$(OBJCOPY) --remove-section .mwcats.text --remove-section .comment $(@:.o=.asm_processor.o) $@
	$(ASM_PROCESSOR) --assembler "$(AS) $(ASFLAGS)" --asm-prelude include/macros.inc $< --post-process $@

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
