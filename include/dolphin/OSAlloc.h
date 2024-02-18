#ifndef _DOLPHIN_OSALLOC_H_
#define _DOLPHIN_OSALLOC_H_

#include <dolphin/types.h>

typedef int OSHeapHandle;

extern volatile OSHeapHandle __OSCurrHeap;

void *OSInitAlloc(void *, void *, int);
OSHeapHandle OSCreateHeap(void *, void *);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle);
void *OSAllocFromHeap(OSHeapHandle, u32);
long OSCheckHeap(OSHeapHandle);
void OSFreeToHeap(OSHeapHandle heap, void *ptr);

#define OSAlloc(size) OSAllocFromHeap(__OSCurrHeap, (size))
#define OSFree(ptr)   OSFreeToHeap(__OSCurrHeap, (ptr))

#endif
