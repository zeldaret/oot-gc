#ifndef _MEM_FUNCS_H_
#define _MEM_FUNCS_H_

#include "macros.h"
#include "stddef.h"

#define __min_bytes_for_long_copy 32

INIT int memcmp(void*, const void*, size_t);
INIT void* memcpy(void* dst, const void* src, size_t n);
INIT void* memset(void* dst, int val, size_t n);
INIT void __fill_mem(void* dst, int val, size_t n);

void __copy_mem(void* dst, const void* src, unsigned long n);
void __move_mem(void* dst, const void* src, unsigned long n);
void __copy_longs_aligned(void* dst, const void* src, unsigned long n);
void __copy_longs_rev_aligned(void* dst, const void* src, unsigned long n);
void __copy_longs_unaligned(void* dst, const void* src, unsigned long n);
void __copy_longs_rev_unaligned(void* dst, const void* src, unsigned long n);

#endif
