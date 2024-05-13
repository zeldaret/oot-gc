#ifndef __PPC_EABI_LINKER
#define __PPC_EABI_LINKER

#include "macros.h"

INIT extern char _stack_addr[];
INIT extern char _stack_end[];
INIT extern char _heap_addr[];
INIT extern char _heap_end[];
INIT extern const char _fextabindex_rom[];
INIT extern char _fextabindex[];
INIT extern char _eextabindex[];

INIT extern char _SDA_BASE_[];

INIT extern char _SDA2_BASE_[];

typedef struct __rom_copy_info {
    char* rom;
    char* addr;
    unsigned int size;
} __rom_copy_info;

INIT extern __rom_copy_info _rom_copy_info[];

typedef struct __bss_init_info {
    char* addr;
    unsigned int size;
} __bss_init_info;

INIT extern __bss_init_info _bss_init_info[];

typedef struct __eti_init_info {
    void* eti_start;
    void* eti_end;
    void* code_start;
    unsigned long code_size;
} __eti_init_info;

INIT extern __eti_init_info _eti_init_info[];
INIT extern const char _f_init_rom[];
INIT extern char _f_init[];
INIT extern char _e_init[];
INIT extern const char _f_text_rom[];
INIT extern char _f_text[];
INIT extern char _e_text[];
INIT extern const char _f_rodata_rom[];
INIT extern char _f_rodata[];
INIT extern char _e_rodata[];
INIT extern const char _fextab_rom[];
INIT extern char _fextab[];
INIT extern char _eextab[];
INIT extern const char _f_data_rom[];
INIT extern char _f_data[];
INIT extern char _e_data[];
INIT extern char _f_bss[];
INIT extern char _e_bss[];
INIT extern const char _f_sdata_rom[];
INIT extern char _f_sdata[];
INIT extern char _e_sdata[];
INIT extern char _f_sbss[];
INIT extern char _e_sbss[];
INIT extern const char _f_sdata2_rom[];
INIT extern char _f_sdata2[];
INIT extern char _e_sdata2[];
INIT extern char _f_sbss2[];
INIT extern char _e_sbss2[];
INIT extern const char _f_PPC_EMB_sdata0_rom[];
INIT extern char _f_PPC_EMB_sdata0[];
INIT extern char _e_PPC_EMB_sdata0[];
INIT extern char _f_PPC_EMB_sbss0[];
INIT extern char _e_PPC_EMB_sbss0[];

#endif // __PPC_EABI_LINKER
