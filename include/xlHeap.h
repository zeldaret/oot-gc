#ifndef _XL_HEAP_H
#define _XL_HEAP_H

#include "dolphin.h"

extern s32 gnSizeHeap;

s32 xlHeapTake(void** ppHeap, s32 nByteCount);
s32 xlHeapFree(void** ppHeap);
s32 xlHeapCompact(void);
s32 xlHeapCopy(void* pHeapTarget, void* pHeapSource, s32 nByteCount);
s32 xlHeapFill32(void* pHeap, s32 nByteCount, u32 nData);
s32 xlHeapGetFree(s32* pnFreeBytes);
s32 xlHeapSetup(void* pHeap, s32 nSizeBytes);
s32 xlHeapReset(void);
s32 xlHeapBlockCacheAdd(u32* pBlock);

#endif
