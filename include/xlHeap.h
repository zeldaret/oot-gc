#ifndef _XL_HEAP_H
#define _XL_HEAP_H

int xlHeapReset(void);
int xlHeapSetup(void* pHeap, int nSizeBytes);
int xlHeapGetFree(int* pnFreeBytes);
int xlHeapFill32(void* pHeap, int nByteCount, unsigned int nData);
int xlHeapCopy(void* pHeapTarget, void* pHeapSource, int nByteCount);
int xlHeapCompact(void);
int xlHeapFree(void** ppHeap);
int xlHeapTake(void** ppHeap, int nByteCount);

#endif
