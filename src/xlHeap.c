#include <dolphin/types.h>

#include "xlHeap.h"

static u32* gpHeap;
static u32* gpHeapBlockFirst;
static u32* gpHeapBlockLast;
static s32 gnHeapTakeCount;
static s32 gnHeapFreeCount;
static s32 gnHeapTakeCacheCount;
static u32* gapHeapBlockCache[11][32];
s32 gnSizeHeap;

#define PADDING_MAGIC 0x1234abcd

#define FLAG_FREE 0x01000000
#define FLAG_TAKEN 0x02000000

// Blocks have a 32-bit header:
//   copy low bits of size (6 bits) | flags (2 bits) | size (26 bits)
#define MAKE_BLOCK(size, flags) ((size) | ((size) << 26) | (flags))

#define BLOCK_IS_FREE(v) ((v)&FLAG_FREE)
#define BLOCK_IS_TAKEN(v) ((v)&FLAG_TAKEN)
#define BLOCK_SIZE(v) ((s32)((v)&0xFFFFFF))

//! TODO: these need better names
#define CHKSUM_HI(v) ((u32)((v) >> 26))
#define CHKSUM_LO(v) ((u32)((v)&0x3F))

static s32 xlHeapBlockCacheGet(s32 nSize, u32** ppBlock, s32* pnBlockSize) {
    s32 nBlockCachedSize;
    s32 nBlock;
    s32 nBlockSize;
    s32 nBlockBest;
    s32 nBlockBestSize;
    u32* pBlock;

    if (nSize < 8) {
        nBlockSize = 0;
    } else if (nSize < 16) {
        nBlockSize = 1;
    } else if (nSize < 32) {
        nBlockSize = 2;
    } else if (nSize < 64) {
        nBlockSize = 3;
    } else if (nSize < 128) {
        nBlockSize = 4;
    } else if (nSize < 256) {
        nBlockSize = 5;
    } else if (nSize < 512) {
        nBlockSize = 6;
    } else if (nSize < 1024) {
        nBlockSize = 7;
    } else if (nSize < 4096) {
        nBlockSize = 8;
    } else if (nSize < 8192) {
        nBlockSize = 9;
    } else {
        nBlockSize = 10;
    }

    for (; nBlockSize < 11; nBlockSize++) {
        nBlockBest = -1;
        nBlockBestSize = 0x1000000;
        for (nBlock = 0; nBlock < 32; nBlock++) {
            if ((pBlock = gapHeapBlockCache[nBlockSize][nBlock]) != NULL) {
                nBlockCachedSize = BLOCK_SIZE(*pBlock);
                if (nBlockCachedSize < nBlockBestSize && nBlockCachedSize >= nSize) {
                    nBlockBest = nBlock;
                    nBlockBestSize = nBlockCachedSize;
                }
            }
        }

        if (nBlockBest >= 0) {
            *pnBlockSize = nBlockBestSize;
            *ppBlock = gapHeapBlockCache[nBlockSize][nBlockBest];
            gapHeapBlockCache[nBlockSize][nBlockBest] = NULL;

            gnHeapTakeCacheCount++;
            return 1;
        }
    }

    *ppBlock = NULL;
    return 0;
}

static s32 xlHeapBlockCacheAdd(u32* pBlock) {
    s32 nSize;
    s32 nBlock;
    s32 nBlockSize;
    s32 nBlockCachedSize;
    u32* pBlockCached;

    nSize = BLOCK_SIZE(*pBlock);
    if (nSize == 0) {
        return 0;
    }

    if (nSize < 8) {
        nBlockSize = 0;
    } else if (nSize < 16) {
        nBlockSize = 1;
    } else if (nSize < 32) {
        nBlockSize = 2;
    } else if (nSize < 64) {
        nBlockSize = 3;
    } else if (nSize < 128) {
        nBlockSize = 4;
    } else if (nSize < 256) {
        nBlockSize = 5;
    } else if (nSize < 512) {
        nBlockSize = 6;
    } else if (nSize < 1024) {
        nBlockSize = 7;
    } else if (nSize < 4096) {
        nBlockSize = 8;
    } else if (nSize < 8192) {
        nBlockSize = 9;
    } else {
        nBlockSize = 10;
    }

    for (nBlock = 0; nBlock < 32; nBlock++) {
        if ((pBlockCached = gapHeapBlockCache[nBlockSize][nBlock]) == NULL ||
            (nBlockCachedSize = BLOCK_SIZE(*pBlockCached)) < nSize) {
            gapHeapBlockCache[nBlockSize][nBlock] = pBlock;
            return 1;
        }
    }

    return 0;
}

static s32 xlHeapBlockCacheClear(u32* pBlock) {
    s32 nSize;
    s32 nBlock;
    s32 nBlockSize;

    nSize = BLOCK_SIZE(*pBlock);
    if (nSize == 0) {
        return 0;
    }

    if (nSize < 8) {
        nBlockSize = 0;
    } else if (nSize < 16) {
        nBlockSize = 1;
    } else if (nSize < 32) {
        nBlockSize = 2;
    } else if (nSize < 64) {
        nBlockSize = 3;
    } else if (nSize < 128) {
        nBlockSize = 4;
    } else if (nSize < 256) {
        nBlockSize = 5;
    } else if (nSize < 512) {
        nBlockSize = 6;
    } else if (nSize < 1024) {
        nBlockSize = 7;
    } else if (nSize < 4096) {
        nBlockSize = 8;
    } else if (nSize < 8192) {
        nBlockSize = 9;
    } else {
        nBlockSize = 10;
    }

    for (nBlock = 0; nBlock < 32; nBlock++) {
        if (gapHeapBlockCache[nBlockSize][nBlock] == pBlock) {
            gapHeapBlockCache[nBlockSize][nBlock] = NULL;
            return 1;
        }
    }

    return 0;
}

static s32 xlHeapBlockCacheReset(void) {
    s32 nBlockSize;
    u32* pBlock;
    u32 nBlock;

    gnHeapTakeCacheCount = 0;
    gnHeapFreeCount = 0;
    gnHeapTakeCount = 0;

    for (nBlockSize = 0; nBlockSize < 11; nBlockSize++) {
        for (nBlock = 0; nBlock < 32; nBlock++) {
            gapHeapBlockCache[nBlockSize][nBlock] = NULL;
        }
    }

    pBlock = gpHeapBlockFirst;
    while ((nBlockSize = BLOCK_SIZE(*pBlock)) != 0) {
        if (BLOCK_IS_FREE(*pBlock)) {
            xlHeapBlockCacheAdd(pBlock);
        }
        pBlock += nBlockSize + 1;
    }

    return 1;
}

static s32 xlHeapFindUpperBlock(s32 nSize, u32** ppBlock, s32* pnBlockSize) {
    s32 nBlockSize;
    u32 nBlock;
    u32* pBlock;
    u32* pBlockBest;
    u32* pBlockNext;

    pBlockBest = NULL;
    pBlock = gpHeapBlockFirst;

    while ((u32)pBlock < (u32)gpHeapBlockLast) {
        nBlock = *pBlock;
        nBlockSize = BLOCK_SIZE(nBlock) & 0xFFFFFF;
        if (CHKSUM_LO(nBlock) != CHKSUM_HI(nBlock)) {
            return 0;
        }
        if (BLOCK_IS_FREE(nBlock) && nBlockSize >= nSize) {
            pBlockBest = pBlock;
        }
        pBlock += nBlockSize + 1;
    }

    if (pBlockBest == NULL) {
        return 0;
    }

    nBlockSize = BLOCK_SIZE(*pBlockBest);
    xlHeapBlockCacheClear(pBlockBest);

    if (nBlockSize > nSize + 0x20) {
        pBlockNext = pBlockBest + ((nBlockSize - nSize) - 1);
        *pBlockNext = MAKE_BLOCK(nSize, FLAG_FREE);
        xlHeapBlockCacheAdd(pBlockBest);
        *ppBlock = pBlockNext;
        *pnBlockSize = BLOCK_SIZE(*pBlockNext);
    } else {
        *ppBlock = pBlockBest;
        *pnBlockSize = BLOCK_SIZE(*pBlockBest);
    }
    return 1;
}

s32 xlHeapTake(void** ppHeap, s32 nByteCount) {
    s32 bValid;
    u32 nSizeExtra;
    u32 iTry;
    s32 nSize;
    s32 nBlockSize;
    s32 nBlockNextSize;
    s32 nBlockNextNextSize;
    u32 nBlock;
    u32* pBlock;
    u32* pBlockNext;
    u32* pBlockNextNext;

    bValid = 0;
    *ppHeap = NULL;

    switch (nByteCount & 0x30000000) {
        case 0:
            nSizeExtra = 3;
            break;
        case 0x10000000:
            nSizeExtra = 7;
            break;
        case 0x20000000:
            nSizeExtra = 15;
            break;
        case 0x30000000:
            nSizeExtra = 31;
            break;
    }

    if ((nSize = ((nByteCount & 0x8FFFFFFF) + nSizeExtra) >> 2) < 1) {
        return 0;
    }
    if (nSize > 0x01000000) {
        return 0;
    }

    iTry = 0;
    while (iTry++ < 8) {
        if (nByteCount & 0x40000000) {
            bValid = xlHeapFindUpperBlock(nSize, &pBlock, &nBlockSize);
        } else if (xlHeapBlockCacheGet(nSize, &pBlock, &nBlockSize)) {
            bValid = 1;
        } else {
            pBlock = gpHeapBlockFirst;
            while ((u32)pBlock < (u32)gpHeapBlockLast) {
                nBlock = *pBlock;
                nBlockSize = BLOCK_SIZE(nBlock);

                if (CHKSUM_LO(nBlock) != CHKSUM_HI(nBlock)) {
                    return 0;
                }

                if (BLOCK_IS_FREE(nBlock) && nBlockSize >= nSize) {
                    bValid = 1;
                    break;
                }

                pBlock += nBlockSize + 1;
            }
        }

        if (bValid) {
            if (nSize == nBlockSize - 1) {
                nSize++;
            }

            if (nSize < nBlockSize) {
                pBlockNext = pBlock + nSize + 1;
                nBlockNextSize = nBlockSize - nSize - 1;

                pBlockNextNext = pBlock + nBlockSize + 1;
                if ((nBlockNextNextSize = BLOCK_SIZE(*pBlockNextNext)) != 0 && BLOCK_IS_FREE(*pBlockNextNext)) {
                    xlHeapBlockCacheClear(pBlockNextNext);
                    nBlockNextSize += nBlockNextNextSize + 1;
                }

                *pBlockNext = MAKE_BLOCK(nBlockNextSize, FLAG_FREE);
                xlHeapBlockCacheAdd(pBlockNext);
            }

            *pBlock = MAKE_BLOCK(nSize, FLAG_TAKEN);
            gnHeapTakeCount += 1;

            pBlock++;
            while (((u32)pBlock & nSizeExtra) != 0) {
                *pBlock++ = PADDING_MAGIC;
            }

            *ppHeap = pBlock;
            return 1;
        }

        if (!xlHeapCompact()) {
            return 0;
        }
    }

    return 0;
}

s32 xlHeapFree(void** ppHeap) {
    s32 nBlockSize;
    s32 nBlockNextSize;
    u32* pBlock;
    u32* pBlockNext;

    if (ppHeap == NULL || (u32)*ppHeap < (u32)gpHeapBlockFirst || (u32)*ppHeap > (u32)gpHeapBlockLast) {
        return 0;
    }

    pBlock = (u32*)*ppHeap - 1;
    while (*pBlock == PADDING_MAGIC) {
        pBlock--;
    }

    nBlockSize = BLOCK_SIZE(*pBlock);
    if (BLOCK_IS_FREE(*pBlock)) {
        return 0;
    }

    if (!BLOCK_IS_TAKEN(*pBlock)) {
        return 0;
    }

    if (CHKSUM_HI(*pBlock) != CHKSUM_LO(nBlockSize)) {
        return 0;
    }

    pBlockNext = pBlock + nBlockSize + 1;
    if ((nBlockNextSize = BLOCK_SIZE(*pBlockNext)) != 0 && BLOCK_IS_FREE(*pBlockNext)) {
        xlHeapBlockCacheClear(pBlockNext);
        nBlockSize += nBlockNextSize + 1;
    }

    *pBlock = MAKE_BLOCK(nBlockSize, FLAG_FREE);
    xlHeapBlockCacheAdd(pBlock);

    gnHeapFreeCount++;
    *ppHeap = NULL;

    return 1;
}

s32 xlHeapCompact(void) {
    s32 nCount;
    s32 nBlockLarge;
    s32 nBlockSize;
    s32 nBlockNextSize;
    s32 anBlockLarge[6];
    u32 nBlock;
    u32* pBlock;
    u32* pBlockPrevious;
    u32 nBlockNext;
    u32* pBlockNext;

    pBlockPrevious = NULL;
    pBlock = gpHeapBlockFirst;
    while (nBlock = *pBlock, (nBlockSize = BLOCK_SIZE(*pBlock)) != 0) {
        pBlockNext = pBlock + nBlockSize + 1;
        nBlockNext = *pBlockNext;

        if (BLOCK_IS_FREE(nBlock)) {
            for (nCount = 0; nCount < 6; nCount++) {
                if (anBlockLarge[nCount] < nBlockSize) {
                    anBlockLarge[nCount] = nBlockSize;
                }
            }

            nBlockNextSize = BLOCK_SIZE(nBlockNext);
            if (nBlockNextSize != 0 && BLOCK_IS_FREE(nBlockNext)) {
                nBlockLarge = nBlockNextSize + 1;
                nBlockSize += nBlockLarge;
                pBlockNext += nBlockLarge;
            }

            if (pBlockPrevious != NULL && BLOCK_IS_FREE(*pBlockPrevious)) {
                nBlockSize += BLOCK_SIZE(*pBlockPrevious) + 1;
                *pBlockPrevious = MAKE_BLOCK(nBlockSize, FLAG_FREE);
            } else {
                *pBlock = MAKE_BLOCK(nBlockSize, FLAG_FREE);
                pBlockPrevious = pBlock;
            }
        } else {
            pBlockPrevious = pBlock;
        }
        pBlock = pBlockNext;
    }

    xlHeapBlockCacheReset();
    return 1;
}

s32 xlHeapCopy(void* pHeapTarget, void* pHeapSource, s32 nByteCount) {
    u8* pSource8;
    u8* pTarget8;
    u32* pSource32;
    u32* pTarget32;

    pSource32 = (u32*)pHeapSource;
    pTarget32 = (u32*)pHeapTarget;
    if ((u32)pSource32 % 4 == 0 && (u32)pTarget32 % 4 == 0) {
        for (; nByteCount >= 64; nByteCount -= 64) {
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
        }

        for (; nByteCount >= 32; nByteCount -= 32) {
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
            *pTarget32++ = *pSource32++;
        }

        for (; nByteCount >= 4; nByteCount -= 4) {
            *pTarget32++ = *pSource32++;
        }
    }

    pSource8 = (u8*)pSource32;
    pTarget8 = (u8*)pTarget32;
    for (; nByteCount >= 16; nByteCount -= 16) {
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
    }

    for (; nByteCount >= 8; nByteCount -= 8) {
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
        *pTarget8++ = *pSource8++;
    }

    for (; nByteCount > 0; nByteCount--) {
        *pTarget8++ = *pSource8++;
    }

    return 1;
}

s32 xlHeapFill32(void* pHeap, s32 nByteCount, u32 nData) {
    u32* pnTarget = pHeap;
    s32 nWordCount = nByteCount >> 2;

    for (; nWordCount > 16; nWordCount -= 16) {
        pnTarget[0] = nData;
        pnTarget[1] = nData;
        pnTarget[2] = nData;
        pnTarget[3] = nData;
        pnTarget[4] = nData;
        pnTarget[5] = nData;
        pnTarget[6] = nData;
        pnTarget[7] = nData;
        pnTarget[8] = nData;
        pnTarget[9] = nData;
        pnTarget[10] = nData;
        pnTarget[11] = nData;
        pnTarget[12] = nData;
        pnTarget[13] = nData;
        pnTarget[14] = nData;
        pnTarget[15] = nData;
        pnTarget += 16;
    }

    for (; nWordCount > 0; nWordCount--) {
        *pnTarget++ = nData;
    }

    return 1;
}

s32 xlHeapGetFree(s32* pnFreeBytes) {
    s32 nBlockSize;
    s32 nFree;
    s32 nCount;
    u32* pBlock;
    u32 nBlock;

    if (!xlHeapCompact()) {
        return 0;
    }

    pBlock = gpHeapBlockFirst;
    nFree = 0;
    while ((u32)pBlock < (u32)gpHeapBlockLast) {
        nBlock = *pBlock;
        nBlockSize = BLOCK_SIZE(nBlock);

        if (CHKSUM_LO(nBlock) != CHKSUM_HI(nBlock)) {
            return 0;
        }

        if (BLOCK_IS_FREE(nBlock)) {
            nFree += nBlockSize * 4;
        }

        pBlock += nBlockSize + 1;
    }

    *pnFreeBytes = nFree;
    return 1;
}

s32 xlHeapSetup(void* pHeap, s32 nSizeBytes) {
    s32 nSizeWords;

    nSizeWords = nSizeBytes >> 2;
    pHeap = (void*)(((u32)pHeap + 3) & 0xFFFFFFFC);

    gnSizeHeap = nSizeBytes;
    gpHeap = pHeap;

    for (; nSizeWords >= 8; nSizeWords -= 8) {
#ifdef __MWERKS__
        *((u32*)pHeap)++ = 0;
        *((u32*)pHeap)++ = 0;
        *((u32*)pHeap)++ = 0;
        *((u32*)pHeap)++ = 0;
        *((u32*)pHeap)++ = 0;
        *((u32*)pHeap)++ = 0;
        *((u32*)pHeap)++ = 0;
        *((u32*)pHeap)++ = 0;
#else
        ((u32*)pHeap)[0] = 0;
        ((u32*)pHeap)[1] = 0;
        ((u32*)pHeap)[2] = 0;
        ((u32*)pHeap)[3] = 0;
        ((u32*)pHeap)[4] = 0;
        ((u32*)pHeap)[5] = 0;
        ((u32*)pHeap)[6] = 0;
        ((u32*)pHeap)[7] = 0;
        pHeap = (u32*)pHeap + 8;
#endif
    }

    for (; nSizeWords > 0; nSizeWords--) {
#ifdef __MWERKS__
        *((u32*)pHeap)++ = 0;
#else
        *((u32*)pHeap) = 0;
        pHeap = (u32*)pHeap + 1;
#endif
    }

    return xlHeapReset();
}

s32 xlHeapReset(void) {
    s32 nBlockSize = (gnSizeHeap >> 2) - 2;

    gpHeapBlockFirst = gpHeap;
    gpHeapBlockLast = gpHeap + nBlockSize + 1;

    *gpHeapBlockFirst = MAKE_BLOCK(nBlockSize, FLAG_FREE);
    *gpHeapBlockLast = 0;

    xlHeapBlockCacheReset();
    return 1;
}
