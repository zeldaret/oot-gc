/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Core\xlHeap.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80006648 -> 0x80007BC0
*/

#include "dolphin/types.h"

// size = 0x4, address = 0x801355A8
static unsigned int* gpHeap;

// size = 0x4, address = 0x801355AC
static unsigned int* gpHeapBlockFirst;

// size = 0x4, address = 0x801355B0
static unsigned int* gpHeapBlockLast;

// size = 0x4, address = 0x801355B4
static int gnHeapTakeCount;

// size = 0x4, address = 0x801355B8
static int gnHeapFreeCount;

// size = 0x4, address = 0x801355BC
static int gnHeapTakeCacheCount;

// size = 0x580, address = 0x800F3FB0
static unsigned int* gapHeapBlockCache[11][32];

// size = 0x4, address = 0x801355C0
int gnSizeHeap;

// Erased
static int xlHeapTestBlock(unsigned int nBlock) {
    // Parameters
    // unsigned int nBlock; // r1+0x0
}

// Erased
static void xlHeapShowStatistics() {}

// Erased
static void xlHeapStatisticsReset() {
    // References
    // -> static int gnHeapFreeCount;
    // -> static int gnHeapTakeCount;
    // -> static int gnHeapTakeCacheCount;
}

// Range: 0x800079C0 -> 0x80007BC0
static int xlHeapBlockCacheGet(int nSize, unsigned int** ppBlock, int* pnBlockSize) {
    // Parameters
    // int nSize; // r1+0x0
    // unsigned int** ppBlock; // r1+0x4
    // int* pnBlockSize; // r1+0x8

    // Local variables
    int nBlockCachedSize; // r1+0x0
    int nBlock; // r8
    int nBlockSize; // r9
    int nBlockBest; // r10
    int nBlockBestSize; // r11
    unsigned int* pBlock; // r12

    // References
    // -> static int gnHeapTakeCacheCount;
    // -> static unsigned int* gapHeapBlockCache[11][32];
}

// Range: 0x80007758 -> 0x800079C0
static int xlHeapBlockCacheAdd(unsigned int* pBlock) {
    // Parameters
    // unsigned int* pBlock; // r1+0x0

    // Local variables
    int nSize; // r6
    int nBlock; // r7
    int nBlockSize; // r1+0x0
    int nBlockCachedSize; // r1+0x0
    unsigned int* pBlockCached; // r8

    // References
    // -> static unsigned int* gapHeapBlockCache[11][32];
}

// Range: 0x8000764C -> 0x80007758
static int xlHeapBlockCacheClear(unsigned int* pBlock) {
    // Parameters
    // unsigned int* pBlock; // r1+0x0

    // Local variables
    int nSize; // r1+0x0
    int nBlock; // r6
    int nBlockSize; // r1+0x0

    // References
    // -> static unsigned int* gapHeapBlockCache[11][32];
}

// Range: 0x80007540 -> 0x8000764C
static int xlHeapBlockCacheReset() {
    // Local variables
    int nBlockSize; // r1+0x8
    unsigned int* pBlock; // r30
    unsigned int nBlock; // r1+0x8

    // References
    // -> static unsigned int* gpHeapBlockFirst;
    // -> static unsigned int* gapHeapBlockCache[11][32];
    // -> static int gnHeapFreeCount;
    // -> static int gnHeapTakeCount;
    // -> static int gnHeapTakeCacheCount;
}

// Range: 0x8000743C -> 0x80007540
static int xlHeapFindUpperBlock(int nSize, unsigned int** ppBlock, int* pnBlockSize) {
    // Parameters
    // int nSize; // r28
    // unsigned int** ppBlock; // r29
    // int* pnBlockSize; // r30

    // Local variables
    int nBlockSize; // r3
    unsigned int nBlock; // r4
    unsigned int* pBlock; // r7
    unsigned int* pBlockBest; // r31
    unsigned int* pBlockNext; // r27

    // References
    // -> static unsigned int* gpHeapBlockLast;
    // -> static unsigned int* gpHeapBlockFirst;
}

// Range: 0x800071B4 -> 0x8000743C
int xlHeapTake(void* ppHeap, int nByteCount) {
    // Parameters
    // void* ppHeap; // r26
    // int nByteCount; // r1+0xC

    // Local variables
    int bValid; // r30
    unsigned int nSizeExtra; // r29
    unsigned int iTry; // r28
    int nSize; // r27
    int nBlockSize; // r1+0x14
    int nBlockNextSize; // r28
    int nBlockNextNextSize; // r30
    unsigned int nBlock; // r6
    unsigned int* pBlock; // r1+0x10
    unsigned int* pBlockNext; // r31
    unsigned int* pBlockNextNext; // r3

    // References
    // -> static int gnHeapTakeCount;
    // -> static unsigned int* gpHeapBlockLast;
    // -> static unsigned int* gpHeapBlockFirst;
}

// Range: 0x80007098 -> 0x800071B4
int xlHeapFree(void* ppHeap) {
    // Parameters
    // void* ppHeap; // r31

    // Local variables
    int nBlockSize; // r30
    int nBlockNextSize; // r29
    unsigned int* pBlock; // r28
    unsigned int* pBlockNext; // r3

    // References
    // -> static int gnHeapFreeCount;
    // -> static unsigned int* gpHeapBlockLast;
    // -> static unsigned int* gpHeapBlockFirst;
}

// Erased
static int xlHeapTest(void* pHeap) {
    // Parameters
    // void* pHeap; // r1+0x0

    // Local variables
    unsigned int* pBlock; // r3
}

// Range: 0x80006F68 -> 0x80007098
int xlHeapCompact() {
    // Local variables
    int nCount; // r1+0x8
    int nBlockLarge; // r1+0x8
    int nBlockSize; // r4
    int nBlockNextSize; // r3
    int anBlockLarge[6]; // r1+0x8
    unsigned int nBlock; // r1+0x8
    unsigned int* pBlock; // r5
    unsigned int* pBlockPrevious; // r6
    unsigned int nBlockNext; // r7
    unsigned int* pBlockNext; // r8

    // References
    // -> static unsigned int* gpHeapBlockFirst;
}

// Range: 0x80006AF0 -> 0x80006F68
int xlHeapCopy(void* pHeapTarget, void* pHeapSource, int nByteCount) {
    // Parameters
    // void* pHeapTarget; // r3
    // void* pHeapSource; // r4
    // int nByteCount; // r5

    // Local variables
    u8* pSource8; // r4
    u8* pTarget8; // r3
    unsigned int* pSource32; // r4
    unsigned int* pTarget32; // r3
}

// Erased
static int xlHeapFill8(void* pHeap, int nByteCount, u8 nData) {
    // Parameters
    // void* pHeap; // r3
    // int nByteCount; // r4
    // u8 nData; // r1+0x8

    // Local variables
    u8* pnTarget; // r3
}

// Erased
static int xlHeapFill16(void* pHeap, int nByteCount, u16 nData) {
    // Parameters
    // void* pHeap; // r3
    // int nByteCount; // r6
    // u16 nData; // r1+0x8

    // Local variables
    u16* pnTarget; // r3
}

// Range: 0x80006908 -> 0x80006AF0
int xlHeapFill32(void* pHeap, int nByteCount, unsigned int nData) {
    // Parameters
    // void* pHeap; // r3
    // int nByteCount; // r6
    // unsigned int nData; // r1+0x8

    // Local variables
    unsigned int* pnTarget; // r3
}

// Range: 0x80006870 -> 0x80006908
int xlHeapGetFree(int* pnFreeBytes) {
    // Parameters
    // int* pnFreeBytes; // r31

    // Local variables
    int nBlockSize; // r3
    int nFree; // r5
    int nCount; // r1+0x8
    unsigned int* pBlock; // r6
    unsigned int nBlock; // r7

    // References
    // -> static unsigned int* gpHeapBlockLast;
    // -> static unsigned int* gpHeapBlockFirst;
}

// Range: 0x800066B0 -> 0x80006870
int xlHeapSetup(void* pHeap, int nSizeBytes) {
    // Parameters
    // void* pHeap; // r6
    // int nSizeBytes; // r1+0xC

    // Local variables
    int nSizeWords; // r5

    // References
    // -> static unsigned int* gpHeapBlockLast;
    // -> static unsigned int* gpHeapBlockFirst;
    // -> static unsigned int* gpHeap;
    // -> int gnSizeHeap;
}

// Range: 0x80006648 -> 0x800066B0
int xlHeapReset() {
    // Local variables
    int nBlockSize; // r6

    // References
    // -> static unsigned int* gpHeapBlockLast;
    // -> static unsigned int* gpHeapBlockFirst;
    // -> static unsigned int* gpHeap;
    // -> int gnSizeHeap;
}
