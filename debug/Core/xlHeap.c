/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Core\xlHeap.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80006648 -> 0x80007BC0
*/

#include "dolphin/types.h"

// size = 0x4, address = 0x801355A8
static u32* gpHeap;

// size = 0x4, address = 0x801355AC
static u32* gpHeapBlockFirst;

// size = 0x4, address = 0x801355B0
static u32* gpHeapBlockLast;

// size = 0x4, address = 0x801355B4
static s32 gnHeapTakeCount;

// size = 0x4, address = 0x801355B8
static s32 gnHeapFreeCount;

// size = 0x4, address = 0x801355BC
static s32 gnHeapTakeCacheCount;

// size = 0x580, address = 0x800F3FB0
static u32* gapHeapBlockCache[11][32];

// size = 0x4, address = 0x801355C0
s32 gnSizeHeap;

// Erased
static s32 xlHeapTestBlock(u32 nBlock) {
    // Parameters
    // u32 nBlock; // r1+0x0
}

// Erased
static void xlHeapShowStatistics() {}

// Erased
static void xlHeapStatisticsReset() {
    // References
    // -> static s32 gnHeapFreeCount;
    // -> static s32 gnHeapTakeCount;
    // -> static s32 gnHeapTakeCacheCount;
}

// Range: 0x800079C0 -> 0x80007BC0
static s32 xlHeapBlockCacheGet(s32 nSize, u32** ppBlock, s32* pnBlockSize) {
    // Parameters
    // s32 nSize; // r1+0x0
    // u32** ppBlock; // r1+0x4
    // s32* pnBlockSize; // r1+0x8

    // Local variables
    s32 nBlockCachedSize; // r1+0x0
    s32 nBlock; // r8
    s32 nBlockSize; // r9
    s32 nBlockBest; // r10
    s32 nBlockBestSize; // r11
    u32* pBlock; // r12

    // References
    // -> static s32 gnHeapTakeCacheCount;
    // -> static u32* gapHeapBlockCache[11][32];
}

// Range: 0x80007758 -> 0x800079C0
static s32 xlHeapBlockCacheAdd(u32* pBlock) {
    // Parameters
    // u32* pBlock; // r1+0x0

    // Local variables
    s32 nSize; // r6
    s32 nBlock; // r7
    s32 nBlockSize; // r1+0x0
    s32 nBlockCachedSize; // r1+0x0
    u32* pBlockCached; // r8

    // References
    // -> static u32* gapHeapBlockCache[11][32];
}

// Range: 0x8000764C -> 0x80007758
static s32 xlHeapBlockCacheClear(u32* pBlock) {
    // Parameters
    // u32* pBlock; // r1+0x0

    // Local variables
    s32 nSize; // r1+0x0
    s32 nBlock; // r6
    s32 nBlockSize; // r1+0x0

    // References
    // -> static u32* gapHeapBlockCache[11][32];
}

// Range: 0x80007540 -> 0x8000764C
static s32 xlHeapBlockCacheReset() {
    // Local variables
    s32 nBlockSize; // r1+0x8
    u32* pBlock; // r30
    u32 nBlock; // r1+0x8

    // References
    // -> static u32* gpHeapBlockFirst;
    // -> static u32* gapHeapBlockCache[11][32];
    // -> static s32 gnHeapFreeCount;
    // -> static s32 gnHeapTakeCount;
    // -> static s32 gnHeapTakeCacheCount;
}

// Range: 0x8000743C -> 0x80007540
static s32 xlHeapFindUpperBlock(s32 nSize, u32** ppBlock, s32* pnBlockSize) {
    // Parameters
    // s32 nSize; // r28
    // u32** ppBlock; // r29
    // s32* pnBlockSize; // r30

    // Local variables
    s32 nBlockSize; // r3
    u32 nBlock; // r4
    u32* pBlock; // r7
    u32* pBlockBest; // r31
    u32* pBlockNext; // r27

    // References
    // -> static u32* gpHeapBlockLast;
    // -> static u32* gpHeapBlockFirst;
}

// Range: 0x800071B4 -> 0x8000743C
s32 xlHeapTake(void* ppHeap, s32 nByteCount) {
    // Parameters
    // void* ppHeap; // r26
    // s32 nByteCount; // r1+0xC

    // Local variables
    s32 bValid; // r30
    u32 nSizeExtra; // r29
    u32 iTry; // r28
    s32 nSize; // r27
    s32 nBlockSize; // r1+0x14
    s32 nBlockNextSize; // r28
    s32 nBlockNextNextSize; // r30
    u32 nBlock; // r6
    u32* pBlock; // r1+0x10
    u32* pBlockNext; // r31
    u32* pBlockNextNext; // r3

    // References
    // -> static s32 gnHeapTakeCount;
    // -> static u32* gpHeapBlockLast;
    // -> static u32* gpHeapBlockFirst;
}

// Range: 0x80007098 -> 0x800071B4
s32 xlHeapFree(void* ppHeap) {
    // Parameters
    // void* ppHeap; // r31

    // Local variables
    s32 nBlockSize; // r30
    s32 nBlockNextSize; // r29
    u32* pBlock; // r28
    u32* pBlockNext; // r3

    // References
    // -> static s32 gnHeapFreeCount;
    // -> static u32* gpHeapBlockLast;
    // -> static u32* gpHeapBlockFirst;
}

// Erased
static s32 xlHeapTest(void* pHeap) {
    // Parameters
    // void* pHeap; // r1+0x0

    // Local variables
    u32* pBlock; // r3
}

// Range: 0x80006F68 -> 0x80007098
s32 xlHeapCompact() {
    // Local variables
    s32 nCount; // r1+0x8
    s32 nBlockLarge; // r1+0x8
    s32 nBlockSize; // r4
    s32 nBlockNextSize; // r3
    s32 anBlockLarge[6]; // r1+0x8
    u32 nBlock; // r1+0x8
    u32* pBlock; // r5
    u32* pBlockPrevious; // r6
    u32 nBlockNext; // r7
    u32* pBlockNext; // r8

    // References
    // -> static u32* gpHeapBlockFirst;
}

// Range: 0x80006AF0 -> 0x80006F68
s32 xlHeapCopy(void* pHeapTarget, void* pHeapSource, s32 nByteCount) {
    // Parameters
    // void* pHeapTarget; // r3
    // void* pHeapSource; // r4
    // s32 nByteCount; // r5

    // Local variables
    u8* pSource8; // r4
    u8* pTarget8; // r3
    u32* pSource32; // r4
    u32* pTarget32; // r3
}

// Erased
static s32 xlHeapFill8(void* pHeap, s32 nByteCount, u8 nData) {
    // Parameters
    // void* pHeap; // r3
    // s32 nByteCount; // r4
    // u8 nData; // r1+0x8

    // Local variables
    u8* pnTarget; // r3
}

// Erased
static s32 xlHeapFill16(void* pHeap, s32 nByteCount, u16 nData) {
    // Parameters
    // void* pHeap; // r3
    // s32 nByteCount; // r6
    // u16 nData; // r1+0x8

    // Local variables
    u16* pnTarget; // r3
}

// Range: 0x80006908 -> 0x80006AF0
s32 xlHeapFill32(void* pHeap, s32 nByteCount, u32 nData) {
    // Parameters
    // void* pHeap; // r3
    // s32 nByteCount; // r6
    // u32 nData; // r1+0x8

    // Local variables
    u32* pnTarget; // r3
}

// Range: 0x80006870 -> 0x80006908
s32 xlHeapGetFree(s32* pnFreeBytes) {
    // Parameters
    // s32* pnFreeBytes; // r31

    // Local variables
    s32 nBlockSize; // r3
    s32 nFree; // r5
    s32 nCount; // r1+0x8
    u32* pBlock; // r6
    u32 nBlock; // r7

    // References
    // -> static u32* gpHeapBlockLast;
    // -> static u32* gpHeapBlockFirst;
}

// Range: 0x800066B0 -> 0x80006870
s32 xlHeapSetup(void* pHeap, s32 nSizeBytes) {
    // Parameters
    // void* pHeap; // r6
    // s32 nSizeBytes; // r1+0xC

    // Local variables
    s32 nSizeWords; // r5

    // References
    // -> static u32* gpHeapBlockLast;
    // -> static u32* gpHeapBlockFirst;
    // -> static u32* gpHeap;
    // -> s32 gnSizeHeap;
}

// Range: 0x80006648 -> 0x800066B0
s32 xlHeapReset() {
    // Local variables
    s32 nBlockSize; // r6

    // References
    // -> static u32* gpHeapBlockLast;
    // -> static u32* gpHeapBlockFirst;
    // -> static u32* gpHeap;
    // -> s32 gnSizeHeap;
}
