ELF2DOL := elf2dol
ELF2DOL_CC := cc
ELF2DOL_CFLAGS := -O3 -Wall -s

all: $(ELF2DOL)

clean:
	$(RM) elf2dol

.PHONY: all clean

$(ELF2DOL):
	$(ELF2DOL_CC) $(ELF2DOL_CFLAGS) -o $(ELF2DOL) elf2dol.c
