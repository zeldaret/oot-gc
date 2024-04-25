#ifndef _DOLPHIN_OSCACHE
#define _DOLPHIN_OSCACHE

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void DCInvalidateRange(void* addr, u32 nBytes);
void DCFlushRange(void* addr, u32 nBytes);
void DCStoreRange(void* addr, u32 nBytes);
void DCFlushRangeNoSync(void* addr, u32 nBytes);
void DCZeroRange(void* addr, u32 nBytes);
void ICInvalidateRange(void* addr, u32 nBytes);

#define LC_BASE_PREFIX 0xE000
#define LC_BASE (LC_BASE_PREFIX << 16)
#define LCGetBase() ((void*)LC_BASE)

void LCEnable(void);
void LCDisable(void);
void LCStoreBlocks(void* destAddr, void* srcTag, u32 numBlocks);
u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes);
void LCQueueWait(u32 len);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSCACHE
