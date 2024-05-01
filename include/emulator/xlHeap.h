#ifndef _XL_HEAP_H
#define _XL_HEAP_H

#include "dolphin.h"

extern s32 gnSizeHeap;

bool xlHeapTake(void** ppHeap, s32 nByteCount);
bool xlHeapFree(void** ppHeap);
bool xlHeapCompact(void);
bool xlHeapCopy(void* pHeapTarget, void* pHeapSource, s32 nByteCount);
bool xlHeapFill32(void* pHeap, s32 nByteCount, u32 nData);
bool xlHeapGetFree(s32* pnFreeBytes);
bool xlHeapSetup(void* pHeap, s32 nSizeBytes);
bool xlHeapReset(void);

#endif
