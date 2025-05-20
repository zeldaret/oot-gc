#ifndef _METROTRK_MEM_TRK_H
#define _METROTRK_MEM_TRK_H

#include "dolphin/types.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

void* TRK_memset(void* dest, int val, size_t count);
void* TRK_memcpy(void* dest, const void* src, size_t count);
void TRK_fill_mem(void* dest, int val, size_t count);

#ifdef __cplusplus
}
#endif

#endif
