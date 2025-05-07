#ifndef _METROTRK_FLUSH_CACHE_H
#define _METROTRK_FLUSH_CACHE_H

#include "dolphin/types.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

ASM void TRK_flush_cache(u32 addr, u32 length);

#ifdef __cplusplus
}
#endif

#endif
