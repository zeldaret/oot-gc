#ifndef _DOLPHIN_OS_OSALLOC_H_
#define _DOLPHIN_OS_OSALLOC_H_

#include "dolphin/types.h"

typedef s32 OSHeapHandle;

extern volatile OSHeapHandle __OSCurrHeap;

void* OSInitAlloc(void*, void*, s32);
OSHeapHandle OSCreateHeap(void*, void*);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle);
void* OSAllocFromHeap(OSHeapHandle, u32);
s32 OSCheckHeap(OSHeapHandle);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);

#define OSAlloc(size) OSAllocFromHeap(__OSCurrHeap, (size))
#define OSFree(ptr) OSFreeToHeap(__OSCurrHeap, (ptr))

#endif
