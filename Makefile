NON_MATCHING := 0
RUN_CC_CHECK := 1

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
ifeq ($(OS),Windows_NT)
	WINE := 
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		WINE := wibo
	else ifeq ($(UNAME_S),Darwin)
		WINE := wine
	else
		$(error Unknown OS: $(OS))
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

CC_CHECK := gcc
CC_CHECK_WARNINGS := \
	-Wall \
	-Wextra \
	-Werror=strict-prototypes \
	-Werror=implicit-function-declaration \
	-Wno-cast-function-type \
	-Wno-incompatible-pointer-types \
	-Wno-sequence-point \
	-Wno-sign-compare \
	-Wno-unknown-pragmas \
	-Wno-unused-but-set-variable \
	-Wno-unused-function \
	-Wno-unused-parameter \
	-Wno-unused-variable

SHA1SUM := sha1sum
PYTHON := python3
ELF2DOL := tools/elf2dol/elf2dol

ASM_PROCESSOR_DIR := tools/asm_processor
ASM_PROCESSOR := $(ASM_PROCESSOR_DIR)/compile.sh

POSTPROC := tools/postprocess.py

# Options
INCLUDES := -Iinclude -Ilibc
ASFLAGS := -mgekko -I include -I libc
LDFLAGS := -map $(MAP) -fp hardware -nodefaults -warn off
CFLAGS := -Cpp_exceptions off -proc gekko -fp hardware -fp_contract on -enum int  -align powerpc -nosyspath -RTTI off -str reuse -multibyte -O4,p -inline auto -sym on -nodefaults -msgstyle gcc $(INCLUDES) -DDOLPHIN_REV=$(DOLPHIN_REVISION)
CC_CHECK_FLAGS := -fno-builtin -fsyntax-only -std=gnu99 -I include -I libc $(CC_CHECK_WARNINGS) -DNON_MATCHING

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
	find include libc src -name '*.h' -o -name '*.c' | xargs clang-format -i

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
	$(CC) $(CFLAGS) -inline deferred $< -c -o $@
	$(OBJCOPY) --remove-section .mwcats.text --remove-section .comment $@

$(BUILD_DIR)/src/emulator/THPRead.o: src/emulator/THPRead.c
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/THP%.o: src/emulator/THP%.c
	$(CC) $(CFLAGS) -inline deferred $< -c -o $@
	$(OBJCOPY) --remove-section .mwcats.text --remove-section .comment $@

$(BUILD_DIR)/src/emulator/xlCoreGCN.o: src/emulator/xlCoreGCN.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/simGCN.o: src/emulator/simGCN.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/mcardGCN.o: src/emulator/mcardGCN.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/soundGCN.o: src/emulator/soundGCN.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/frame.o: src/emulator/frame.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/cpu.o: src/emulator/cpu.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/rsp.o: src/emulator/rsp.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/_buildtev.o: src/emulator/_buildtev.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/_frameGCNcc.o: src/emulator/_frameGCNcc.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(ASM_PROCESSOR) "$(CC) $(CFLAGS) -inline deferred" "$(AS) $(ASFLAGS)" $@ $<

$(BUILD_DIR)/src/emulator/%.o: src/emulator/%.c
ifeq ($(RUN_CC_CHECK),1)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $<
endif
	$(CC) $(CFLAGS) -inline deferred $< -c -o $@
	$(OBJCOPY) --remove-section .mwcats.text --remove-section .comment $@
