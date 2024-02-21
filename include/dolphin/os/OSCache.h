#ifndef _DOLPHIN_OS_OSCACHE_H_
#define _DOLPHIN_OS_OSCACHE_H_

#include "dolphin/types.h"

void DCEnable(void);
void DCInvalidateRange(void* addr, u32 nBytes);
void DCFlushRange(void* addr, u32 nBytes);
void DCStoreRange(void* addr, u32 nBytes);
void DCFlushRangeNoSync(void* addr, u32 nBytes);
void DCZeroRange(void* addr, u32 nBytes);
void ICInvalidateRange(void* addr, u32 nBytes);
void ICFlashInvalidate(void);
void ICEnable(void);
void LCEnable(void);
void LCDisable(void);
void LCStoreBlocks(void* destAddr, void* srcTag, u32 numBlocks);
u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes);
void LCQueueWait(u32 len);
void L2GlobalInvalidate(void);
void __OSCacheInit(void);

#endif
