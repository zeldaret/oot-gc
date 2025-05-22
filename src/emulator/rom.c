#include "emulator/rom.h"
#include "dolphin.h"
#include "emulator/cpu.h"
#include "emulator/frame.h"
#include "emulator/ram.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"
#include "emulator/xlFile.h"
#include "emulator/xlHeap.h"
#include "macros.h"

static bool romMakeFreeCache(Rom* pROM, s32* piCache, RomCacheType eType);
static bool romSetBlockCache(Rom* pROM, s32 iBlock, RomCacheType eType);
static bool romCacheEnding_ZELDA(f32 rProgress);
static bool romCacheGame_OTHER(Rom* pROM, char* szName, f32 rProgress);

extern u8 greadingDisk[];
extern u8 gbar[];

_XL_OBJECTTYPE gClassROM = {
    "ROM",
    sizeof(Rom),
    NULL,
    (EventFunc)romEvent,
};

#include "emulator/rom_tables.h"

static bool gbProgress;
static void* gpImageBack;

#if IS_OOT_EU || IS_MM
static bool romGetTagToken(Rom* pROM, tXL_FILE* pFile, RomTokenType* peToken, char* acData) {
    u32 nChecksum;
    XlFileTokenType eTypeToken;
    char acToken[65];

    while (xlFileGetToken(pFile, &eTypeToken, acToken, sizeof(acToken) - 1)) {
        if (eTypeToken == XLFTT_SYMBOL) {
            if (acToken[0] == '#') {
                if (!xlFileSkipLine(pFile)) {
                    return false;
                }
            } else if (acToken[0] == '{') {
                pROM->tagFile.nMode++;
            } else if (acToken[0] == '}') {
                if ((pROM->tagFile.nMode & 0xFF) > 0) {
                    pROM->tagFile.nMode--;
                }
                if ((pROM->tagFile.nMode & 0xFF) == 0) {
                    *peToken = RTT_DONE;
                    *acData = 0;
                    return true;
                }
            } else if (acToken[0] == ',' && (pROM->tagFile.nMode & 0x200)) {
                pROM->tagFile.nMode &= ~0x400;
            } else if (acToken[0] == ';' && (pROM->tagFile.nMode & 0x200)) {
                pROM->tagFile.nMode &= ~0x600;
            }
        } else if (eTypeToken == XLFTT_NUMBER) {
            if (pROM->tagFile.nMode & 0x400) {
                return false;
            }
            pROM->tagFile.nMode |= 0x400;
            if (pROM->tagFile.nMode & 0x200) {
                *peToken = RTT_DATA_NUMBER;
                xlTextCopy(acData, acToken);
                return true;
            }
        } else if (eTypeToken == XLFTT_LABEL || eTypeToken == XLFTT_STRING) {
            if ((pROM->tagFile.nMode & 0xFF) == 0) {
                if (xlTextMatch("ROM", acToken) != 0) {
                    if (!xlFileMatchToken(pFile, XLFTT_SYMBOL, NULL, 0, "[")) {
                        return false;
                    }
                    *peToken = RTT_CODE_INVALID;
                    do {
                        if (!xlFileGetToken(pFile, &eTypeToken, acToken, sizeof(acToken) - 1)) {
                            return false;
                        }
                        if (eTypeToken == XLFTT_LABEL) {
                            if (romTestCode(pROM, acToken)) {
                                *peToken = RTT_CODE;
                            }
                        } else {
                            return false;
                        }
                        if (!xlFileGetToken(pFile, &eTypeToken, acToken, sizeof(acToken) - 1)) {
                            return false;
                        }
                        if (acToken[0] != ',' && acToken[0] != ']') {
                            return false;
                        }
                    } while (acToken[0] != ']');
                    continue;
                }
                return false;
            }
            if (pROM->tagFile.nMode & 0x200) {
                if (pROM->tagFile.nMode & 0x400) {
                    return false;
                }
                pROM->tagFile.nMode |= 0x400;
                *peToken = RTT_DATA_STRING;
                xlTextCopy(acData, acToken);
                return true;
            }
            pROM->tagFile.nMode |= 0x200;
            xlTextCopy(acData, acToken);
            if (!xlFileGetToken(pFile, &eTypeToken, acToken, sizeof(acToken) - 1)) {
                return false;
            }
            if (acToken[0] == '[') {
                *peToken = RTT_NAME_INVALID;

                do {
                    if (!xlFileGetToken(pFile, &eTypeToken, acToken, sizeof(acToken) - 1)) {
                        return false;
                    }

                    if (eTypeToken == XLFTT_LABEL && romTestCode(pROM, acToken) ||
                        eTypeToken == XLFTT_NUMBER && xlTokenGetInteger(acToken, &nChecksum) &&
                            (nChecksum == pROM->nChecksum)) {
                        *peToken = RTT_NAME;
                    }

                    if (!xlFileGetToken(pFile, &eTypeToken, acToken, sizeof(acToken) - 1)) {
                        return false;
                    }

                    if ((acToken[0] != ',') && (acToken[0] != ']')) {
                        return false;
                    }

                    if (acToken[0] == ']') {
                        if (!xlFileMatchToken(pFile, XLFTT_SYMBOL, NULL, 0, "=")) {
                            return false;
                        }
                        break;
                    }
                } while (true);
            } else {
                *peToken = RTT_NAME;
            }
            return true;
        } else {
            return false;
        }
    }

    return false;
}
#endif

static bool romFindFreeCache(Rom* pROM, s32* piCache, RomCacheType eType) {
    s32 iBlock;

    if (eType == RCT_RAM) {
        for (iBlock = 0; iBlock < pROM->nCountBlockRAM; iBlock++) {
            if (!(pROM->anBlockCachedRAM[iBlock >> 3] & (1 << (iBlock & 7)))) {
                *piCache = iBlock;
                return true;
            }
        }
    } else if (eType == RCT_ARAM) {
        for (iBlock = 0; iBlock < ARRAY_COUNT(pROM->anBlockCachedARAM); iBlock++) {
            if (!(pROM->anBlockCachedARAM[iBlock >> 3] & (1 << (iBlock & 7)))) {
                *piCache = -(iBlock + 1);
                return true;
            }
        }
    } else {
        return false;
    }

    return false;
}

static bool romFindOldestBlock(Rom* pROM, s32* piBlock, RomCacheType eTypeCache, s32 whichBlock) {
    RomBlock* pBlock;
    s32 iBlock;
    s32 iBlockOldest;
    u32 nTick;
    u32 nTickDelta;
    u32 nTickDeltaOldest;

    nTick = pROM->nTick;
    nTickDeltaOldest = 0;

    for (iBlock = 0; iBlock < ARRAY_COUNT(pROM->aBlock); iBlock++) {
        pBlock = &pROM->aBlock[iBlock];
        if (pBlock->nSize != 0 &&
            ((eTypeCache == RCT_RAM && pBlock->iCache >= 0) || (eTypeCache == RCT_ARAM && pBlock->iCache < 0))) {
            if (pBlock->nTickUsed > nTick) {
                nTickDelta = -1 - (pBlock->nTickUsed - nTick);
            } else {
                nTickDelta = nTick - pBlock->nTickUsed;
            }
            if (whichBlock == 0) {
                if (nTickDelta > nTickDeltaOldest && pBlock->keep == 0) {
                    iBlockOldest = iBlock;
                    nTickDeltaOldest = nTickDelta;
                }
            } else if (whichBlock == 1) {
                if (nTickDelta > nTickDeltaOldest && pBlock->keep == 1) {
                    iBlockOldest = iBlock;
                    nTickDeltaOldest = nTickDelta;
                }
            } else if (nTickDelta > nTickDeltaOldest) {
                iBlockOldest = iBlock;
                nTickDeltaOldest = nTickDelta;
            }
        }
    }

    if (nTickDeltaOldest != 0) {
        *piBlock = iBlockOldest;
        return true;
    }

    return false;
}

static inline void romMarkBlockAsFree(Rom* pROM, s32 iBlock) {
    RomBlock* pBlock;
    s32 iCache;

    pBlock = &pROM->aBlock[iBlock];

    if (pBlock->iCache < 0) {
        iCache = -(pBlock->iCache + 1);
        pROM->anBlockCachedARAM[iCache >> 3] &= ~(1 << (iCache & 7));
    } else {
        iCache = pBlock->iCache;
        pROM->anBlockCachedRAM[iCache >> 3] &= ~(1 << (iCache & 7));
    }
    pBlock->nSize = 0;
}

static bool romMakeFreeCache(Rom* pROM, s32* piCache, RomCacheType eType) {
    s32 iCache;
    s32 iBlockOldest;

    if (eType == RCT_RAM) {
        if (!romFindFreeCache(pROM, &iCache, RCT_RAM)) {
            if (romFindOldestBlock(pROM, &iBlockOldest, RCT_RAM, 2)) {
                iCache = pROM->aBlock[iBlockOldest].iCache;
                if (!romSetBlockCache(pROM, iBlockOldest, RCT_ARAM) &&
                    romFindOldestBlock(pROM, &iBlockOldest, RCT_RAM, 0)) {
                    iCache = pROM->aBlock[iBlockOldest].iCache;
                    romMarkBlockAsFree(pROM, iBlockOldest);
                }
            } else {
                return false;
            }
        }
    } else {
        if (!romFindFreeCache(pROM, &iCache, RCT_ARAM)) {
            if (romFindOldestBlock(pROM, &iBlockOldest, RCT_ARAM, 0)) {
                iCache = pROM->aBlock[iBlockOldest].iCache;
                romMarkBlockAsFree(pROM, iBlockOldest);
            } else {
                return false;
            }
        }
    }

    *piCache = iCache;
    return true;
}

static bool romSetBlockCache(Rom* pROM, s32 iBlock, RomCacheType eType) {
    RomBlock* pBlock;
    s32 iCacheRAM;
    s32 iCacheARAM;
    s32 nOffsetRAM;
    s32 nOffsetARAM;

    pBlock = &pROM->aBlock[iBlock];
    if ((eType == RCT_RAM && pBlock->iCache >= 0) || (eType == RCT_ARAM && pBlock->iCache < 0)) {
        return true;
    }

    if (eType == RCT_RAM) {
        iCacheARAM = -(pBlock->iCache + 1);
        if (!romMakeFreeCache(pROM, &iCacheRAM, RCT_RAM)) {
            return false;
        }

        nOffsetRAM = iCacheRAM * 0x2000;
        nOffsetARAM = iCacheARAM * 0x2000;
        nOffsetARAM += ARGetBaseAddress();

        while (ARGetDMAStatus()) {}

        ARStartDMARead((u32)&pROM->pCacheRAM[nOffsetRAM], nOffsetARAM, 0x2000);
        DCInvalidateRange(&pROM->pCacheRAM[nOffsetRAM], 0x2000);

        pROM->anBlockCachedARAM[iCacheARAM >> 3] &= ~(1 << (iCacheARAM & 7));
        pROM->anBlockCachedRAM[iCacheRAM >> 3] |= (1 << (iCacheRAM & 7));
        pBlock->iCache = iCacheRAM;
    } else if (eType == RCT_ARAM) {
        iCacheRAM = pBlock->iCache;
        if (!romMakeFreeCache(pROM, &iCacheARAM, RCT_ARAM)) {
            return false;
        }
        iCacheARAM = -(iCacheARAM + 1);

        nOffsetRAM = iCacheRAM * 0x2000;
        nOffsetARAM = iCacheARAM * 0x2000;
        nOffsetARAM += ARGetBaseAddress();

        DCStoreRange(&pROM->pCacheRAM[nOffsetRAM], 0x2000);

        while (ARGetDMAStatus()) {}

        ARStartDMAWrite((u32)&pROM->pCacheRAM[nOffsetRAM], nOffsetARAM, 0x2000);

        pROM->anBlockCachedRAM[iCacheRAM >> 3] &= ~(1 << (iCacheRAM & 7));
        pROM->anBlockCachedARAM[iCacheARAM >> 3] |= (1 << (iCacheARAM & 7));
        pBlock->iCache = -(iCacheARAM + 1);
    } else {
        return false;
    }

    while (ARGetDMAStatus()) {}

    return true;
}

static bool __romLoadBlock_Complete(Rom* pROM) {
    s32 iBlock;

    if (pROM->bFlip) {
        //! TODO: this might be an inline function, see ``romLoadFullOrPart``
        u32* anData = (u32*)pROM->load.anData;
        u32 i;

        for (i = 0; i < ((pROM->load.nSize + 3) >> 2); i++) {
            *anData++ = ((*anData >> 8) & 0x00FF00FF) | ((*anData << 8) & 0xFF00FF00);
        }
    }

    iBlock = pROM->load.iBlock;
    pROM->aBlock[iBlock].nSize = pROM->load.nSize;
    pROM->aBlock[iBlock].iCache = pROM->load.iCache;
    pROM->aBlock[iBlock].keep = 0;

    pROM->anBlockCachedRAM[pROM->load.iCache >> 3] |= (1 << (pROM->load.iCache & 7));

    if ((pROM->load.pCallback != NULL) && !pROM->load.pCallback()) {
        return false;
    }

    return true;
}

static void __romLoadBlock_CompleteGCN(long nResult, DVDFileInfo* fileInfo) {
    Rom* pROM = SYSTEM_ROM(gpSystem);

    pROM->load.nResult = nResult;
    pROM->load.bDone = true;
}

static bool romLoadBlock(Rom* pROM, s32 iBlock, s32 iCache, UnknownCallbackFunc pCallback) {
    u8* anData;
    s32 nSizeRead;
    u32 nSize;
    u32 nOffset;

    nOffset = iBlock * 0x2000;
    if ((nSize = pROM->nSize - nOffset) > 0x2000) {
        nSize = 0x2000;
    }
    anData = &pROM->pCacheRAM[iCache * 0x2000];
    nSizeRead = (nSize + 0x1F) & 0xFFFFFFE0;

    pROM->load.nSize = nSize;
    pROM->load.iBlock = iBlock;
    pROM->load.iCache = iCache;
    pROM->load.anData = anData;
    pROM->load.pCallback = pCallback;

    if (pCallback == NULL) {
        if (!simulatorDVDRead(&pROM->fileInfo, anData, nSizeRead, nOffset + pROM->offsetToRom, NULL)) {
            return false;
        }
    } else {
        pROM->load.nOffset = nOffset;
        pROM->load.nSizeRead = nSizeRead;
        if (!simulatorDVDRead(&pROM->fileInfo, anData, nSizeRead, nOffset + pROM->offsetToRom,
                              &__romLoadBlock_CompleteGCN)) {
            return false;
        }
        return true;
    }

    if (!__romLoadBlock_Complete(pROM)) {
        return false;
    }
    return true;
}

static bool romLoadRange(Rom* pROM, s32 begin, s32 end, s32* blockCount, s32 whichBlock,
                         ProgressCallbackFunc* pProgressCallback) {
    s32 iCache;
    u32 iBlock;
    u32 iBlockLast;

    iBlockLast = end / 0x2000;
    for (iBlock = begin / 0x2000; iBlock <= iBlockLast; iBlock++) {
#if IS_OOT
        if (pProgressCallback != NULL) {
            pProgressCallback((f32)(iBlock - (begin / 0x2000)) / (f32)((end - begin) / 0x2000));
        }
#else
        if (pProgressCallback != NULL) {
            pProgressCallback((f32)*blockCount / 2000.0);
        }
#endif

        if (pROM->aBlock[iBlock].nSize == 0) {
            if (!romMakeFreeCache(pROM, &iCache, RCT_RAM)) {
                return false;
            }

            if (!romLoadBlock(pROM, iBlock, iCache, NULL)) {
                return false;
            }
        }

        pROM->aBlock[iBlock].keep = whichBlock;
        pROM->aBlock[iBlock].nTickUsed = ++pROM->nTick;

        if (blockCount != NULL) {
            *blockCount += 1;
        }
    }

    return true;
}

#if IS_MM
static bool romLoadRangeBlock(Rom* pROM, s32 beginBlock, s32 endBlock, s32* blockCount, s32 whichBlock,
                              ProgressCallbackFunc pfProgress) {
    s32 iBlock;
    s32 iCache;

    for (iBlock = beginBlock; iBlock <= endBlock; iBlock++) {
        if (pfProgress != NULL) {
            pfProgress((f32)*blockCount / 1600.0);
        }

        if (!romMakeFreeCache(pROM, &iCache, RCT_RAM)) {
            return false;
        }

        if (!romLoadBlock(pROM, iBlock, iCache, NULL)) {
            return false;
        }

        pROM->aBlock[iBlock].keep = whichBlock;
        pROM->aBlock[iBlock].nTickUsed = ++pROM->nTick;

        if (blockCount != NULL) {
            *blockCount += 1;
        }
    }

    NO_INLINE();
    return true;
}

bool romReloadRange(Cpu* pCPU) {
    s32 iBlock;
    s32 blockCount;
    Rom* pROM;
    System* pSystem;

    blockCount = 0;
    pSystem = SYSTEM(pCPU->pHost);
    pROM = SYSTEM_ROM(pSystem);

    for (iBlock = 0; iBlock < ARRAY_COUNT(pROM->aBlock); iBlock++) {
        romMarkBlockAsFree(pROM, iBlock);
    }

#if IS_MM_EU
    if (!romLoadRangeBlock(pROM, 0x22, 0x23, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x4A, 0x4C, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x18A, 0x19E, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x22C, 0x236, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x245, 0x248, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x251, 0x263, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x317, 0x317, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x334, 0x345, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x366, 0x36F, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x38B, 0x38C, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x3A3, 0x3A3, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x3AC, 0x3B1, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x3C4, 0x3C4, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x457, 0x465, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x482, 0x484, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x4A5, 0x4A5, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x4B3, 0x4BA, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x4DE, 0x4E9, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x5C8, 0x5D2, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x63C, 0x679, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x690, 0x69D, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x6AA, 0x6C4, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x6D3, 0x6E1, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x6EA, 0x6F5, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x6FE, 0x702, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x70D, 0x72C, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x740, 0x745, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x75D, 0x7DC, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x7E8, 0x7FE, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x81F, 0x833, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x83D, 0x868, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x871, 0x877, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x883, 0x886, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x896, 0x8A8, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x8B0, 0x8C5, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x8DC, 0x8E6, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x8E9, 0x8ED, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x8F4, 0x8F8, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x900, 0x902, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x916, 0x925, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x95F, 0x96C, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x97F, 0x995, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x9BD, 0x9C7, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x9D1, 0x9DE, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x9F1, 0x9F1, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0x9F9, 0x9FF, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xA08, 0xA1A, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xA68, 0xA6C, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xA73, 0xA86, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xA9B, 0xAAA, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xAC0, 0xACC, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xADF, 0xB0B, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xB14, 0xB6B, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xB7B, 0xB83, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xB8A, 0xB8F, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xB9C, 0xBAD, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xBC3, 0xBE6, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xC11, 0xC59, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xC70, 0xC99, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xD17, 0xD2A, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xD6E, 0xD8D, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xDAE, 0xDE1, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xDF0, 0xE25, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xE4A, 0xE5F, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xEFD, 0xF11, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xF6C, 0xF8B, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xFA9, 0xFCA, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
    if (!romLoadRangeBlock(pROM, 0xFDA, 0xFE2, &blockCount, 1, &romCacheEnding_ZELDA)) {
        return false;
    }
#else
#if IS_MM_JP
    if (romTestCode(pROM, "NZSJ"))
#else
    if (pSystem->bJapaneseVersion)
#endif
    {
        if (!romLoadRangeBlock(pROM, 0x4, 0x23, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x46, 0x4C, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x54, 0x56, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x64, 0x65, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x74, 0x78, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x87, 0x8F, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x9A, 0x9C, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xAE, 0xB0, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xC1, 0xC7, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x102, 0x103, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x184, 0x1BB, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x228, 0x236, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x243, 0x263, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x2F0, 0x2F6, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x2FF, 0x32B, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x33E, 0x344, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x354, 0x356, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x371, 0x373, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x37D, 0x384, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3A4, 0x3AF, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3C9, 0x3CA, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3E1, 0x3E2, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3E9, 0x3EF, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3FE, 0x404, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x410, 0x412, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x494, 0x4A3, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x4BB, 0x4BE, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x4C8, 0x4CC, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x4D6, 0x4DE, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x4FE, 0x505, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x528, 0x529, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x538, 0x539, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x59D, 0x5DA, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x5F1, 0x5FF, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x60B, 0x619, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x621, 0x625, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x634, 0x635, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x63C, 0x663, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x66E, 0x679, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x67E, 0x690, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
#if IS_MM_JP
        if (!romLoadRangeBlock(pROM, 0x69B, 0x6A7, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
#else
        if (!romLoadRangeBlock(pROM, 0x69B, 0x6A6, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
#endif
        if (!romLoadRangeBlock(pROM, 0x6BE, 0x73D, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x749, 0x75F, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x781, 0x784, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x78C, 0x794, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x79E, 0x79F, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7A9, 0x7CA, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7D2, 0x7D8, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7E4, 0x7E7, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7F7, 0x809, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x811, 0x826, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x83D, 0x863, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x878, 0x886, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x8BF, 0x8CB, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x8DE, 0x8F4, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x912, 0x926, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x930, 0x984, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x9B8, 0x9BF, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x9C6, 0x9E5, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x9FA, 0xA09, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xA1F, 0xA2B, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xA3E, 0xA6A, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xA72, 0xA87, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xA8C, 0xACA, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xADA, 0xAEE, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xAF7, 0xB0B, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xB1C, 0xB3B, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xB6F, 0xBB5, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xBCB, 0xBFC, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xC71, 0xC7F, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xC8B, 0xC98, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xCC3, 0xCDD, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xCE2, 0xD01, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xD08, 0xD57, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xD68, 0xD81, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xD8C, 0xD9E, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xDA9, 0xDB4, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xDD1, 0xDDB, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xE5D, 0xE63, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xE8C, 0xE95, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xECD, 0xED7, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xEFE, 0xF18, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xF34, 0xF38, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xF45, 0xF57, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
    } else {
        if (!romLoadRangeBlock(pROM, 0x4, 0x23, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }

        if (!romLoadRangeBlock(pROM, 0x46, 0x4C, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x54, 0x56, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x64, 0x65, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x75, 0x77, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x87, 0x8F, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x99, 0x9C, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xAE, 0xB0, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xC1, 0xC7, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x102, 0x103, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x184, 0x1BC, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x228, 0x236, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x243, 0x263, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x33E, 0x343, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x354, 0x356, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x371, 0x373, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x37D, 0x384, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3A4, 0x3AE, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3C9, 0x3CA, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3E1, 0x3E2, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3E9, 0x3F0, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x3FE, 0x404, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x410, 0x412, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x494, 0x4A4, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x4BA, 0x4BD, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x4C7, 0x4CB, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x4D5, 0x4DD, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x4FE, 0x506, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x529, 0x53C, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x59F, 0x5DC, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x5F3, 0x601, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x60D, 0x627, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x636, 0x645, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x64D, 0x658, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x661, 0x665, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x670, 0x692, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x69C, 0x6A8, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x6C0, 0x6DF, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x6E5, 0x73F, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x74A, 0x761, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x782, 0x786, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x78E, 0x796, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x79F, 0x7A1, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7AA, 0x7CC, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7D4, 0x7DA, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7E6, 0x7E9, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7F9, 0x80B, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x813, 0x81B, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x822, 0x828, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x83F, 0x865, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x879, 0x887, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x8C0, 0x8CD, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x8E0, 0x8F6, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x914, 0x928, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x931, 0x93F, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x946, 0x95F, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x968, 0x985, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x9BA, 0x9E7, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x9FB, 0x9FD, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xA05, 0xA0A, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xA20, 0xA2C, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xA3F, 0xA89, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xA8D, 0xACC, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xADC, 0xAF0, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xAF8, 0xB0D, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xB1D, 0xB3B, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xB6F, 0xBB5, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xBCF, 0xBFC, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xC75, 0xC83, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xC8B, 0xC98, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xCC7, 0xD01, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xD0C, 0xD28, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xD29, 0xD57, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xD6C, 0xD81, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xD8C, 0xD9E, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xDAD, 0xDB8, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xDD1, 0xE01, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xE61, 0xE67, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xE8C, 0xEA0, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xED1, 0xEDB, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xEFE, 0xF1B, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xF38, 0xF3C, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xF45, 0xF57, &blockCount, 0x1, &romCacheEnding_ZELDA)) {
            return false;
        }
    }
#endif

    return true;
}
#endif

#if IS_MM
#define RECT_Y_OFFSET 10
#else
#define RECT_Y_OFFSET 0
#endif

static bool romCacheGame_ZELDA(f32 rProgress) {
    int nSize;
    Mtx44 matrix44;
#if IS_MM
    Mtx matrix;
#endif
    GXTexObj textureObject;

    static s32 iImage;

    if (gbDisplayedError) {
        gbDisplayedError = false;

        TEXGetGXTexObjFromPalette(gpImageBack, &textureObject, 0);
        xlCoreBeforeRender();
        GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        C_MTXOrtho(matrix44, 0.0f, 479.0f, 0.0f, 639.0f, 0.0f, 1.0f);
        GXSetProjection(matrix44, GX_ORTHOGRAPHIC);
#if IS_MM
        PSMTXTrans(matrix, 0.0f, 0.0f, 0.0f);
        GXLoadPosMtxImm(matrix, 0);
#endif
        GXSetCullMode(0);
        GXSetZMode(0, 3, 1);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOp(0, 3);
        GXSetTevOrder(0, 0, 0, 0xFF);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
        GXLoadTexObj(&textureObject, 0);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2f32(0.0f, 0.0f);
        GXTexCoord2u8(0, 0);
        GXPosition2f32(640.0f, 0.0f);
        GXTexCoord2u8(1, 0);
        GXPosition2f32(640.0f, 480.0f);
        GXTexCoord2u8(1, 1);
        GXPosition2f32(0.0f, 480.0f);
        GXTexCoord2u8(0, 1);
        GXEnd();

#if IS_MM
        GXPixModeSync();
#endif
        DEMODoneRender();
    }

    if (!(iImage & 7)) {
        VIWaitForRetrace();

#if IS_OOT
        nSize = 400.0f * (gbProgress ? (rProgress / 2.0f) + 0.5f : rProgress / 2.0f);
#else
        nSize = 400.0 * rProgress;

        if (nSize > 400) {
            nSize = 400;
        }
#endif

        if (!_frameDrawRectangle(SYSTEM_FRAME(gpSystem), 0x4083407D, 120, 430 + RECT_Y_OFFSET, 400, 8)) {
            return false;
        }

        if (!_frameDrawRectangle(SYSTEM_FRAME(gpSystem), 0x8F9B8F7C, 120, 430 + RECT_Y_OFFSET, nSize, 8)) {
            return false;
        }
    }

    iImage += 1;
    if (rProgress == 1.0f) {
        gbProgress = true;
    }
    return true;
}

#if IS_MM
static bool romCacheEnding_ZELDA(f32 rProgress) {
    GXColor color;
    Mtx matrix;
#if IS_MM_JP || IS_MM_EU
    s32 pad1;
#endif
    s32 width;
    s32 height;
    s32 nX0;
    s32 nY0;
    TEXPalette* tpl;
    Mtx g2DviewMtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };
    s32 percent;
    s32 pad2;

    static GXTexObj texObj;
    static GXTexObj texObj2;

#if IS_MM_EU
    //! TODO: fake match?
    tpl = (TEXPalette*)*(u32*)greadingDisk;
#else
    tpl = (TEXPalette*)greadingDisk;
#endif

    while (frameBeginOK(gpFrame) != 1) {}
    xlCoreBeforeRender();
    frameDrawSetup2D(gpFrame);
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXEnd();

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1EU, GX_MTX2x4);
    TEXGetGXTexObjFromPalette(tpl, &texObj, 0);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    width = tpl->descriptorArray->textureHeader->width / 2;
    height = tpl->descriptorArray->textureHeader->height / 2;
    nX0 = (N64_FRAME_WIDTH - width) / 2;
    nY0 = (N64_FRAME_HEIGHT - height) / 2;

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0, nY0, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX0 + width, nY0, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX0 + width, nY0 + height, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0, nY0 + height, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXPixModeSync();

    percent = (s32)(100.0 * rProgress);
    GXLoadPosMtxImm(g2DviewMtx, 0);

    Vert_s16Bar[0] = N64_FRAME_WIDTH / 2 - ((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2;
    Vert_s16Bar[1] = (nY0 + tpl->descriptorArray->textureHeader->height);
    Vert_s16Bar[3] = ((N64_FRAME_WIDTH / 2 - (((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2)) +
                      ((((TEXPalette*)gbar)->descriptorArray->textureHeader->width * percent) / 100));
    Vert_s16Bar[4] = (nY0 + tpl->descriptorArray->textureHeader->height);
    Vert_s16Bar[6] = ((N64_FRAME_WIDTH / 2 - (((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2)) +
                      ((((TEXPalette*)gbar)->descriptorArray->textureHeader->width * percent) / 100));
    Vert_s16Bar[7] = (nY0 + tpl->descriptorArray->textureHeader->height +
                      ((TEXPalette*)gbar)->descriptorArray->textureHeader->height);
    Vert_s16Bar[9] = N64_FRAME_WIDTH / 2 - ((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2;
    Vert_s16Bar[10] = (nY0 + tpl->descriptorArray->textureHeader->height +
                       ((TEXPalette*)gbar)->descriptorArray->textureHeader->height);

    DCStoreRange(Vert_s16Bar, sizeof(Vert_s16Bar));
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetArray(GX_VA_POS, Vert_s16Bar, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    TEXGetGXTexObjFromPalette((TEXPalette*)gbar, &texObj2, 0);
    GXLoadTexObj(&texObj2, GX_TEXMAP0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXTexCoord1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXTexCoord1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXTexCoord1x8(2);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXTexCoord1x8(3);
    GXEnd();

    gpFrame->nMode = 0;
    gpFrame->nModeVtx = -1;
    frameDrawReset(gpFrame, 0x5FFED);
    simulatorDEMODoneRender();

    PAD_STACK();
    return true;
}

#if IS_MM_JP
static bool romCacheGame_OTHER(Rom* pROM, char* szName, f32 rProgress) {
    int temp_r31;
    s32 nSize;
    Mtx44 matrix44;
    Mtx matrix;
    GXTexObj textureObject;
    tXL_FILE* pFile;

    static bool firstTime = true;

    if (firstTime) {
        firstTime = false;

        if (xlFileOpen(&pFile, XLFT_BINARY, szName)) {
            nSize = pFile->nSize;
            gpImageBack = (u8*)SYSTEM_RAM(pROM->pHost)->pBuffer + 0x00300000;

            if (!xlFileGet(pFile, gpImageBack, nSize)) {
                return false;
            }

            if (!xlFileClose(&pFile)) {
                return false;
            }

            simulatorUnpackTexPalette(gpImageBack);
            DCStoreRange(gpImageBack, nSize);
            gbProgress = false;
            gbDisplayedError = true;
        }
    }

    if (gbDisplayedError) {
        gbDisplayedError = false;

        TEXGetGXTexObjFromPalette(gpImageBack, &textureObject, 0);
        xlCoreBeforeRender();
        GXSetViewport(0.0f, 0.0f, GC_FRAME_WIDTH, GC_FRAME_HEIGHT, 0.0f, 1.0f);
        C_MTXOrtho(matrix44, 0.0f, GC_FRAME_HEIGHT - 1, 0.0f, GC_FRAME_WIDTH - 1, 0.0f, 1.0f);
        GXSetProjection(matrix44, GX_ORTHOGRAPHIC);
        PSMTXTrans(matrix, 0.0f, 0.0f, 0.0f);
        GXLoadPosMtxImm(matrix, 0);
        GXSetCullMode(GX_CULL_NONE);
        GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_ENABLE);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
        GXLoadTexObj(&textureObject, 0);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2f32(0.0f, 0.0f);
        GXTexCoord2u8(0, 0);
        GXPosition2f32(GC_FRAME_WIDTH, 0.0f);
        GXTexCoord2u8(1, 0);
        GXPosition2f32(GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
        GXTexCoord2u8(1, 1);
        GXPosition2f32(0.0f, GC_FRAME_HEIGHT);
        GXTexCoord2u8(0, 1);
        GXEnd();

        GXPixModeSync();
        DEMODoneRender();
    }

    VIWaitForRetrace();

    temp_r31 = 400.0 * rProgress;

    if (temp_r31 > 400) {
        temp_r31 = 400;
    }

    if (!_frameDrawRectangle(SYSTEM_FRAME(gpSystem), 0x4083407D, 120, 440, 400, 8)) {
        return false;
    }

    if (!_frameDrawRectangle(SYSTEM_FRAME(gpSystem), 0x8F9B8F7C, 120, 440, temp_r31, 8)) {
        return false;
    }

    if (rProgress == 1.0f) {
        gbProgress = true;
    }

    return true;
}
#endif

#endif

#if VERSION == MQ_J

static bool romCacheGame(Rom* pROM) {
    s32 blockCount;
    s32 nSize;
    char* szName;
    tXL_FILE* pFile;

    blockCount = 0;
    gDVDResetToggle = true;

    if (romTestCode(pROM, "CZLE") || romTestCode(pROM, "CZLJ")) {
        if (gnFlagZelda & 2) {
            pROM->anOffsetBlock = ganOffsetBlock_ZLJ;
            pROM->nCountOffsetBlocks = 0xC6;
        } else {
            pROM->anOffsetBlock = ganOffsetBlock_URAZLJ;
            pROM->nCountOffsetBlocks = 0xC6;
        }

        szName = gnFlagZelda & 2 ? "zlj.tpl" : "urazlj.tpl";

        if (xlFileOpen(&pFile, 1, szName)) {
            nSize = pFile->nSize;
            gpImageBack = (u8*)SYSTEM_RAM(pROM->pHost)->pBuffer + 0x300000;
            if (!xlFileGet(pFile, gpImageBack, nSize)) {
                return false;
            }
            if (!xlFileClose(&pFile)) {
                return false;
            }
            simulatorUnpackTexPalette(gpImageBack);
            DCStoreRange(gpImageBack, nSize);
            gbProgress = false;
            gbDisplayedError = true;
        }

        if (gnFlagZelda & 2) {
            if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xAFDAA0, 0x0168515F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
        } else {
            if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xAFDB00, 0x01684BCF, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
        }
    } else if (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE")) {
        if (!romLoadRange(pROM, 0, 0xEFAB5F, &blockCount, 1, NULL)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x0167CE40, 0x016B4E8F, &blockCount, 1, NULL)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x01F82960, pROM->nSize - 1, &blockCount, 1, NULL)) {
            return false;
        }
    }

    gDVDResetToggle = false;
    return true;
}

#elif VERSION == MQ_U || VERSION == CE_J || VERSION == CE_U

static bool romCacheGame(Rom* pROM) {
    s32 blockCount;
    bool bIsCZLE;
    bool bIsCZLJ;
    s32 nSize;
    char* szName;
    tXL_FILE* pFile;

    blockCount = 0;
    gDVDResetToggle = true;

    bIsCZLE = romTestCode(pROM, "CZLE");
    bIsCZLJ = romTestCode(pROM, "CZLJ");
    if (bIsCZLE || bIsCZLJ) {
#if VERSION == CE_J
        if (gnFlagZelda & 2) {
            if (!bIsCZLE) {
                pROM->anOffsetBlock = ganOffsetBlock_ZLJ;
                pROM->nCountOffsetBlocks = 0xC6;
            }
        } else if (!bIsCZLE) {
            pROM->anOffsetBlock = ganOffsetBlock_URAZLJ;
            pROM->nCountOffsetBlocks = 0xC6;
        }
#elif IS_OOT_US
        if (gnFlagZelda & 2) {
            if (bIsCZLE) {
                pROM->anOffsetBlock = ganOffsetBlock_ZLE;
                pROM->nCountOffsetBlocks = 0xC6;
            }
        } else if (bIsCZLE) {
            pROM->anOffsetBlock = ganOffsetBlock_URAZLE;
            pROM->nCountOffsetBlocks = 0xC6;
        }
#endif

        if (bIsCZLE) {
            szName = gnFlagZelda & 2 ? "zle.tpl" : "urazle.tpl";
        } else if (bIsCZLJ) {
            szName = gnFlagZelda & 2 ? "zlj.tpl" : "urazlj.tpl";
        } else {
            szName = "";
        }

        if (xlFileOpen(&pFile, 1, szName)) {
            nSize = pFile->nSize;
            gpImageBack = (u8*)SYSTEM_RAM(pROM->pHost)->pBuffer + 0x300000;
            if (!xlFileGet(pFile, gpImageBack, nSize)) {
                return false;
            }
            if (!xlFileClose(&pFile)) {
                return false;
            }
            simulatorUnpackTexPalette(gpImageBack);
            DCStoreRange(gpImageBack, nSize);
            gbProgress = false;
            gbDisplayedError = true;
        }

        if (gnFlagZelda & 2) {
            if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xAFDAA0, 0x0168515F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
        } else {
            if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xAFDB00, 0x01684BCF, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
        }
    } else if (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE")) {
        if (!romLoadRange(pROM, 0, 0xEFAB5F, &blockCount, 1, NULL)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x0167CE40, 0x016B4E8F, &blockCount, 1, NULL)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x01F82960, pROM->nSize - 1, &blockCount, 1, NULL)) {
            return false;
        }
    }

    gDVDResetToggle = false;
    return true;
}

#elif IS_OOT_EU

bool romCacheGame(Rom* pROM) {
    s32 blockCount;
    bool bZeldaJ;
    bool bZeldaE;
    bool bZeldaF;
    bool bZeldaG;
    bool bZeldaI;
    bool bZeldaS;
    s32 nSize;
    char* szName;
    tXL_FILE* pFile;

    blockCount = 0;
    gDVDResetToggle = true;

    bZeldaE = romTestCode(pROM, "CZLE");
    bZeldaJ = romTestCode(pROM, "CZLJ");

    bZeldaS = false;
    bZeldaI = false;
    bZeldaG = false;
    bZeldaF = false;

    if (gLanguage == 1) {
        bZeldaG = true;
    } else if (gLanguage == 2) {
        bZeldaF = true;
    } else if (gLanguage == 3) {
        bZeldaS = true;
    } else if (gLanguage == 4) {
        bZeldaI = true;
    } else {
        bZeldaE = true;
    }

    if (bZeldaE || bZeldaJ || bZeldaF || bZeldaG || bZeldaI || bZeldaS) {
        if (gnFlagZelda & 2) {
            if (!bZeldaE && !bZeldaJ && (bZeldaE || bZeldaF || bZeldaG || bZeldaI || bZeldaS)) {
                pROM->anOffsetBlock = ganOffsetBlock_ZLP;
                pROM->nCountOffsetBlocks = 0xC6;
            }
        } else if (!bZeldaE && !bZeldaJ && (bZeldaE || bZeldaF || bZeldaG || bZeldaI || bZeldaS)) {
            pROM->anOffsetBlock = ganOffsetBlock_URAZLP;
            pROM->nCountOffsetBlocks = 0xC6;
        }

        if (bZeldaE) {
            szName = gnFlagZelda & 2 ? "zle.tpl" : "urazle.tpl";
        } else if (bZeldaF) {
            szName = gnFlagZelda & 2 ? "zlf.tpl" : "urazlf.tpl";
        } else if (bZeldaG) {
            szName = gnFlagZelda & 2 ? "zlg.tpl" : "urazlg.tpl";
        } else if (bZeldaJ) {
            szName = gnFlagZelda & 2 ? "zlj.tpl" : "urazlj.tpl";
#if VERSION == CE_E
        } else if (bZeldaI) {
            szName = gnFlagZelda & 2 ? "zli.tpl" : "urazli.tpl";
        } else if (bZeldaS) {
            szName = gnFlagZelda & 2 ? "zls.tpl" : "urazls.tpl";
#else
        } else if (bZeldaI) {
            szName = gnFlagZelda & 2 ? "zle.tpl" : "urazle.tpl";
        } else if (bZeldaS) {
            szName = gnFlagZelda & 2 ? "zle.tpl" : "urazle.tpl";
#endif
        } else {
            szName = "";
        }

        if (xlFileOpen(&pFile, 1, szName)) {
            nSize = pFile->nSize;
            gpImageBack = (u8*)SYSTEM_RAM(pROM->pHost)->pBuffer + 0x300000;
            if (!xlFileGet(pFile, gpImageBack, nSize)) {
                return false;
            }
            if (!xlFileClose(&pFile)) {
                return false;
            }
            simulatorUnpackTexPalette(gpImageBack);
            DCStoreRange(gpImageBack, nSize);
            gbProgress = false;
            gbDisplayedError = true;
        }
        if (gnFlagZelda & 2) {
            if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xAFDAA0, 0x0168515F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
        } else {
            if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xAFDB00, 0x01684BCF, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
        }
    } else if (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE")) {
        if (!romLoadRange(pROM, 0, 0xEFAB5F, &blockCount, 1, NULL)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x0167CE40, 0x016B4E8F, &blockCount, 1, NULL)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x01F82960, pROM->nSize - 1, &blockCount, 1, NULL)) {
            return false;
        }
    }

    gDVDResetToggle = false;
    return true;
}

#elif IS_MM

#if IS_MM_JP || IS_MM_EU
#define CHECK_MM_PAL romTestCode(pROM, "NZSP")
#else
#define CHECK_MM_PAL false
#endif

bool romCacheGame(Rom* pROM) {
    s32 blockCount;
    bool bZeldaJ;
    bool bZeldaE;
    bool bZeldaF;
    bool bZeldaG;
    bool bZeldaI;
    bool bZeldaS;
    s32 nSize;
    char* szName;
    tXL_FILE* pFile;

    blockCount = 0;
    gDVDResetToggle = true;

    if (romTestCode(pROM, "CZLE") || romTestCode(pROM, "CZLJ") || romTestCode(pROM, "NZLP")) {
        bZeldaE = romTestCode(pROM, "CZLE");
        bZeldaJ = romTestCode(pROM, "CZLJ");

        bZeldaF = bZeldaG = bZeldaI = bZeldaS = false;

#if IS_MM_EU
        if (gLanguage == 1) {
            bZeldaG = true;
        } else if (gLanguage == 2) {
            bZeldaF = true;
        } else if (gLanguage == 3) {
            bZeldaS = true;
        } else if (gLanguage == 4) {
            bZeldaI = true;
        } else {
            bZeldaE = true;
        }
#endif

        if (bZeldaE || bZeldaJ || bZeldaF || bZeldaG || bZeldaI || bZeldaS) {
            // These if blocks contains code that was probably inside an ifdef,
            // since the empty if statements are required to match, we're keeping the removed instructions for clarity.
            if (gnFlagZelda & 2) {
                if (!bZeldaE && !bZeldaJ && (bZeldaE || bZeldaF || bZeldaG || bZeldaI || bZeldaS)) {
                    // pROM->anOffsetBlock = ganOffsetBlock_ZLP;
                    // pROM->nCountOffsetBlocks = 0xC6;
                }
            } else if (!bZeldaE && !bZeldaJ && (bZeldaE || bZeldaF || bZeldaG || bZeldaI || bZeldaS)) {
                // pROM->anOffsetBlock = ganOffsetBlock_URAZLP;
                // pROM->nCountOffsetBlocks = 0xC6;
            }

            if (bZeldaE) {
                szName = gnFlagZelda & 2 ? "zle.tpl" : "urazle.tpl";
            } else if (bZeldaF) {
                szName = gnFlagZelda & 2 ? "zlf.tpl" : "urazlf.tpl";
            } else if (bZeldaG) {
                szName = gnFlagZelda & 2 ? "zlg.tpl" : "urazlg.tpl";
            } else if (bZeldaJ) {
                szName = gnFlagZelda & 2 ? "zlj.tpl" : "urazlj.tpl";
            } else if (bZeldaI) {
                szName = gnFlagZelda & 2 ? "zle.tpl" : "urazle.tpl";
            } else if (bZeldaS) {
                szName = gnFlagZelda & 2 ? "zle.tpl" : "urazle.tpl";
            } else {
                szName = "";
            }

            if (xlFileOpen(&pFile, XLFT_BINARY, szName)) {
                nSize = pFile->nSize;
                gpImageBack = (u8*)SYSTEM_RAM(pROM->pHost)->pBuffer + 0x300000;
                if (!xlFileGet(pFile, gpImageBack, nSize)) {
                    return false;
                }
                if (!xlFileClose(&pFile)) {
                    return false;
                }
                simulatorUnpackTexPalette(gpImageBack);
                DCStoreRange(gpImageBack, nSize);
                gbProgress = false;
                gbDisplayedError = true;
            }

            if (gnFlagZelda & 2) {
                if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                    return false;
                }
                if (!romLoadRange(pROM, 0xAFDAA0, 0x0168515F, &blockCount, 1, &romCacheGame_ZELDA)) {
                    return false;
                }
            } else {
                if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                    return false;
                }
                if (!romLoadRange(pROM, 0xAFDB00, 0x01684BCF, &blockCount, 1, &romCacheGame_ZELDA)) {
                    return false;
                }
            }
        }
    } else if (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE") || CHECK_MM_PAL) {
#if IS_MM_EU
        if (gLanguage == 1) {
            szName = "zelda2g.tpl";
        } else if (gLanguage == 2) {
            szName = "zelda2f.tpl";
        } else if (gLanguage == 3) {
            szName = "zelda2s.tpl";
        } else if (gLanguage == 4) {
            szName = "zelda2i.tpl";
        } else {
            szName = "zelda2e.tpl";
        }
#else
        if (romTestCode(pROM, "NZSJ")) {
            szName = "zelda2j.tpl";
        } else {
            szName = "zelda2e.tpl";
        }
#endif

        if (xlFileOpen(&pFile, XLFT_BINARY, szName)) {
            nSize = pFile->nSize;
            gpImageBack = (u8*)SYSTEM_RAM(pROM->pHost)->pBuffer + 0x300000;
            if (!xlFileGet(pFile, gpImageBack, nSize)) {
                return false;
            }
            if (!xlFileClose(&pFile)) {
                return false;
            }
            simulatorUnpackTexPalette(gpImageBack);
            DCStoreRange(gpImageBack, nSize);
            gbProgress = false;
            gbDisplayedError = true;
        }

#if IS_MM_EU
        pROM->anOffsetBlock = ganOffsetBlock_ZELDA2P;
        pROM->nCountOffsetBlocks = 0xCA;

        if (!romLoadRange(pROM, 0, 0x99D630, &blockCount, 1, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x9B8AD0, 0xBB5CB0, &blockCount, 1, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0xC78F20, 0xF286F0, &blockCount, 1, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0xF8F920, 0x0103E570, &blockCount, 1, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x017440D0, 0x0175A0C0, &blockCount, 1, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x017877A0, 0x0179FB20, &blockCount, 0, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x018ED600, 0x0190C200, &blockCount, 0, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x01EC9EE0, 0x01EE3710, &blockCount, 0, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x01EEF5F0, 0x01F0BAD0, &blockCount, 1, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRange(pROM, 0x01F4B070, 0x01FC55C0, &blockCount, 0, &romCacheGame_ZELDA)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x7BB, 0x7BD, &blockCount, 0, 0)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x832, 0x83A, &blockCount, 0, 0)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x9C7, 0x9C8, &blockCount, 0, 0)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0x9D9, 0x9DE, &blockCount, 0, 0)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xB6A, 0xB6B, &blockCount, 0, 0)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xC70, 0xC75, &blockCount, 0, 0)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xF62, 0xF63, &blockCount, 0, 0)) {
            return false;
        }
        if (!romLoadRangeBlock(pROM, 0xF72, 0xF76, &blockCount, 0, 0)) {
            return false;
        }
#else
        if (romTestCode(pROM, "NZSJ")) {
            pROM->anOffsetBlock = ganOffsetBlock_ZELDA2J;
            pROM->nCountOffsetBlocks = 0xCA;

            if (!romLoadRange(pROM, 0x0, 0x9E2B50, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x9FDFF0, 0xA723B0, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
#if IS_MM_JP
            if (!romLoadRange(pROM, 0xB3B620, 0xDEAE50, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xE52080, 0x1053A00, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x1601C10, 0x1617C00, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x163A270, 0x166F3F0, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x17A3A00, 0x17C0AD0, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x1D82520, 0x1D90CA0, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x1DA7600, 0x1DBA130, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x1E1B6D0, 0x1E7CA30, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
#elif IS_MM_US
            if (!romLoadRange(pROM, 0xB3B570, 0xDEADA0, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xE51FD0, 0x01053990, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x01601BA0, 0x01617B90, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x0163A200, 0x01648BE0, &blockCount, 0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x017966D0, 0x017B52E0, &blockCount, 0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x01D72FB0, 0x01D8AB10, &blockCount, 0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x01D986C0, 0x01DB4B80, &blockCount, 1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x01DF4120, 0x01E6E630, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
#endif
            if (!romLoadRangeBlock(pROM, 0x71C, 0x71E, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0x938, 0x93E, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0xAC9, 0xACA, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0x926, 0x927, &blockCount, 0x0, NULL)) {
                return false;
            }
#if IS_MM_JP
            if (!romLoadRangeBlock(pROM, 0xBCB, 0xBD0, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0xEBA, 0xEC0, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0xECD, 0xED2, &blockCount, 0x0, NULL)) {
                return false;
            }
#endif
        } else {
            pROM->anOffsetBlock = ganOffsetBlock_ZELDA2E;
            pROM->nCountOffsetBlocks = 0xCA;

            if (!romLoadRange(pROM, 0x0, 0x9E22C0, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x9FD760, 0xA77120, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xB3F840, 0xDEEC10, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0xE55E40, 0x1056D50, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x16055F0, 0x161B5E0, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x163C3A0, 0x1650C50, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x179E730, 0x17BD330, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x1D7B020, 0x1D92B80, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x1DA0730, 0x1DBCC00, &blockCount, 0x1, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRange(pROM, 0x1DFC1A0, 0x1E766B0, &blockCount, 0x0, &romCacheGame_ZELDA)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0x71E, 0x720, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0x93A, 0x93F, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0xACB, 0xACC, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0x928, 0x929, &blockCount, 0x0, NULL)) {
                return false;
            }
            if (!romLoadRangeBlock(pROM, 0x98C, 0x98D, &blockCount, 0x0, NULL)) {
                return false;
            }
        }
#endif
    }

    gDVDResetToggle = false;
    return true;
}

#endif

bool __romLoadUpdate_Complete(void) {
    Rom* pROM = SYSTEM_ROM(gpSystem);

    pROM->load.bWait = false;
    return true;
}

static bool romLoadUpdate(Rom* pROM) {
    s32 iCache;
    RomBlock* pBlock;
    u32 iBlock0;
    u32 iBlock1;
    Cpu* pCPU;

    pCPU = SYSTEM_CPU(pROM->pHost);
    if ((pROM->load.nOffset0 == 0 && pROM->load.nOffset1 == 0) || pROM->load.bWait) {
        return true;
    }

    iBlock0 = pROM->load.nOffset0 >> 0xD;
    iBlock1 = pROM->load.nOffset1 >> 0xD;

    while (iBlock0 <= iBlock1) {
        if (pCPU->nRetrace != pCPU->nRetraceUsed) {
            return true;
        }

        if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
            return false;
        }

        pBlock = &pROM->aBlock[iBlock0];
        pBlock->nTickUsed = ++pROM->nTick;
        if (pBlock->nSize == 0) {
            if (!romMakeFreeCache(pROM, &iCache, 0)) {
                return false;
            }

            pROM->load.bWait = true;
            if (!romLoadBlock(pROM, iBlock0, iCache, &__romLoadUpdate_Complete)) {
                return false;
            }

            return true;
        }

        pROM->load.nOffset0 = ++iBlock0 * 0x2000;
    }

    pROM->load.nOffset1 = 0U;
    pROM->load.nOffset0 = 0U;
    return true;
}

static bool __romCopyUpdate_Complete(void) {
    Rom* pROM = SYSTEM_ROM(gpSystem);

    pROM->copy.bWait = false;
    return true;
}

static bool romCopyUpdate(Rom* pROM) {
    RomBlock* pBlock;
    s32 pad;
    s32 iCache;
    s32 nTickLast;
    u8* anData;
    u32 iBlock;
    u32 nSize;
    u32 nOffsetBlock;
    Cpu* pCPU;

    s32 var_r0;
    s32 var_r5;

    pCPU = SYSTEM_CPU(pROM->pHost);

    //! TODO: inline function?
    var_r5 = 0;
    if (pROM->load.nOffset0 == 0 && pROM->load.nOffset1 == 0) {
        var_r5 = 1;
    }
    if (var_r5 != 0) {
        var_r0 = 0;
    } else {
        var_r0 = 1;
    }
    if (var_r0 || pROM->copy.nSize == 0 || pROM->copy.bWait) {
        return true;
    }

    while (pROM->copy.nSize != 0) {
        if (pROM->copy.pCallback != NULL && pCPU->nRetrace != pCPU->nRetraceUsed) {
            return true;
        }

        if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
            return false;
        }

        iBlock = pROM->copy.nOffset / 0x2000;
        pBlock = &pROM->aBlock[iBlock];
        nTickLast = pBlock->nTickUsed;
        pBlock->nTickUsed = ++pROM->nTick;

        if (pBlock->nSize != 0) {
            if (pBlock->iCache < 0) {
                if (!romSetBlockCache(pROM, iBlock, 0)) {
                    return false;
                }
            }
        } else {
            if (!romMakeFreeCache(pROM, &iCache, 0)) {
                return false;
            }

            if (pROM->copy.pCallback == NULL) {
                if (!romLoadBlock(pROM, iBlock, iCache, NULL)) {
                    return false;
                }
            } else {
                pBlock->nTickUsed = nTickLast;
                pROM->nTick--;
                pROM->copy.bWait = true;
                if (!romLoadBlock(pROM, iBlock, iCache, &__romCopyUpdate_Complete)) {
                    return false;
                } else {
                    return true;
                }
            }
        }

        nOffsetBlock = pROM->copy.nOffset & 0x1FFF;
        if ((nSize = pBlock->nSize - nOffsetBlock) > pROM->copy.nSize) {
            nSize = pROM->copy.nSize;
        }

        anData = &pROM->pCacheRAM[pBlock->iCache * 0x2000];
        if (!xlHeapCopy(pROM->copy.pTarget, anData + nOffsetBlock, nSize)) {
            return false;
        }

        pROM->copy.pTarget = (u8*)pROM->copy.pTarget + nSize;
        pROM->copy.nSize -= nSize;
        pROM->copy.nOffset += nSize;
    }

    if (pROM->copy.pCallback != NULL && !pROM->copy.pCallback()) {
        return false;
    }
    return true;
}

#if IS_MM_JP
static bool romCacheAllBlocks(Rom* pROM, char* szName) {
    s32 iCache;
    u32 iBlock;
    u32 iBlockLast;

    iBlockLast = (u32)(pROM->nSize - 1) / 0x2000;
    pROM->nTick = iBlockLast + 1;

    for (iBlock = 0; iBlock < iBlockLast + 1; iBlock++) {
        pROM->aBlock[iBlock].nTickUsed = iBlockLast - iBlock;

        if (!romMakeFreeCache(pROM, &iCache, RCT_RAM)) {
            return false;
        }

        if (!romLoadBlock(pROM, iBlock, iCache, NULL)) {
            return false;
        }

        if (!(iBlock & 0xF)) {
            romCacheGame_OTHER(pROM, szName, (f32)iBlock / (f32)iBlockLast);
        }
    }

    NO_INLINE();
    return true;
}
#else
static bool romCacheAllBlocks(Rom* pROM) {
    s32 iCache;
    s32 iBlock;
    u32 iBlockLast;

    iBlockLast = (u32)(pROM->nSize - 1) / 0x2000;
    pROM->nTick = iBlockLast + 1;

    for (iBlock = 0; iBlock < iBlockLast + 1; iBlock++) {
        pROM->aBlock[iBlock].nTickUsed = iBlockLast - iBlock;

        if (!romMakeFreeCache(pROM, &iCache, RCT_RAM)) {
            return false;
        }

        if (!romLoadBlock(pROM, iBlock, iCache, NULL)) {
            return false;
        }
    }

    return true;
}
#endif

static bool romLoadFullOrPart(Rom* pROM) {
    tXL_FILE* pFile;
    s32 pad;

#if IS_MM_JP
    // s32 iBlock;
    // s32 nLoad;
    // s32 nStep;
    // s32 iData;
    // u32 nData;
    char szName[10];

    if (romTestCode(pROM, "NSME") || romTestCode(pROM, "NSMJ")) {
        strcpy(szName, "mario_j.tpl");
    } else if (romTestCode(pROM, "NKTE") || romTestCode(pROM, "NKTJ")) {
        strcpy(szName, "kart_j.tpl");
    } else if (romTestCode(pROM, "NFXE") || romTestCode(pROM, "NFXJ")) {
        strcpy(szName, "sf64_j.tpl");
    } else {
        strcpy(szName, " ");
    }
#endif

    if ((s32)pROM->nSize > pROM->nSizeCacheRAM) {
        s32 i;

        pROM->nTick = 0;
        pROM->eModeLoad = RLM_PART;

        for (i = 0; i < ARRAY_COUNT(pROM->aBlock); i++) {
            pROM->aBlock[i].nSize = 0;
            pROM->aBlock[i].iCache = 0;
            pROM->aBlock[i].nTickUsed = 0;
        }

        for (i = 0; i < ARRAY_COUNTU(pROM->anBlockCachedRAM); i++) {
            pROM->anBlockCachedRAM[i] = 0;
        }

        for (i = 0; i < ARRAY_COUNTU(pROM->anBlockCachedARAM); i++) {
            pROM->anBlockCachedARAM[i] = 0;
        }

        if ((s32)pROM->nSize < pROM->nSizeCacheRAM + 0xFFA000) {
#if IS_MM_JP
            if (!romCacheAllBlocks(pROM, szName)) {
                return false;
            }
#else
            if (!romCacheAllBlocks(pROM)) {
                return false;
            }
#endif
        }
    } else {
        s32 i;
        u32 temp_r28;

        if (!xlFileOpen(&pFile, XLFT_BINARY, pROM->acNameFile)) {
            return false;
        }

        pROM->pBuffer = (void*)pROM->pCacheRAM;

        if ((temp_r28 = (u32)pROM->nSize >> 5) == 0) {
            if (!xlFileSetPosition(pFile, pROM->offsetToRom)) {
                return false;
            }

            xlFileGet(pFile, pROM->pBuffer, pROM->nSize);
            simulatorShowLoad(1, pROM->acNameFile, 1.0f);
        } else {
            for (i = 0; i < (s32)pROM->nSize;) {
                if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
                    return false;
                }

                xlFileGet(pFile, (void*)((u32)pROM->pBuffer + i), (s32)temp_r28);
                i += temp_r28;

#if IS_MM_JP
                romCacheGame_OTHER(pROM, szName, (f32)i / (f32)pROM->nSize);
#else
                simulatorShowLoad(0, pROM->acNameFile, (f32)i / (f32)pROM->nSize);
#endif
            }
        }

        if (!xlFileClose(&pFile)) {
            return false;
        }

        pROM->eModeLoad = RLM_FULL;

        if (pROM->bFlip) {
            //! TODO: this might be an inline function, see ``__romLoadBlock_Complete``
            u32* pBuffer = (u32*)pROM->pBuffer;
            s32 j;

            for (j = 0; j < (((s32)pROM->nSize + 3) >> 2); j++) {
                *pBuffer++ = ((*pBuffer >> 8) & 0x00FF00FF) | ((*pBuffer << 8) & 0xFF00FF00);
            }
        }
    }

    return true;
}

bool romGetPC(Rom* pROM, u64* pnPC) {
    s32 nOffset;
    u32 nData;
    u32 iData;
    u32 anData[0x400];

    if (romCopy(pROM, &anData, 0, sizeof(anData), 0)) {
        nData = 0;
        for (iData = 0; iData < 0x400 - 0x10; iData++) {
            nData += anData[iData + 0x10];
        }

        switch (nData) {
            case 0x49F60E96:
            case 0xFB631223:
            case 0x2ADFE50A:
            case 0x57C85244:
                nOffset = 0;
                break;
            case 0x497E414B:
            case 0xE6DECB4B:
            case 0x27C4ED44:
                nOffset = 0x100000;
                break;
            case 0xD5BE5580:
                nOffset = 0x200000;
                break;
            default:
                return false;
        }

        *pnPC = anData[2] - nOffset;
        return true;
    } else {
        return false;
    }
}

bool romGetCode(Rom* pROM, char* acCode) {
    s32 iCode;

    for (iCode = 0; iCode < 4; iCode++) {
        acCode[iCode] = pROM->acHeader[iCode + 0x3B];
    }
    acCode[4] = '\0';

    return true;
}

#if IS_OOT_EU || IS_MM
bool romTestCode(Rom* pROM, char* acCode) {
    s32 iCode;
    int nCode1;
    int nCode2;

    for (iCode = 0; iCode < 4; iCode++) {
        nCode1 = pROM->acHeader[iCode + 0x3B];
        if (nCode1 >= 'a' && nCode1 <= 'z') {
            nCode1 -= 0x20;
        }

        nCode2 = acCode[iCode];
        if (nCode2 >= 'a' && nCode2 <= 'z') {
            nCode2 -= 0x20;
        }

        if (nCode1 != nCode2) {
            return false;
        }
    }

    return true;
}
#else
bool romTestCode(Rom* pROM, char* acCode) {
    s32 iCode;
    char acCodeCurrent[5];

    romGetCode(pROM, acCodeCurrent);

    for (iCode = 0; iCode < 4; iCode++) {
        if (acCode[iCode] != acCodeCurrent[iCode]) {
            return false;
        }
    }

    return true;
}
#endif

static bool romPut8(Rom* pROM, u32 nAddress, s8* pData) { return true; }
static bool romPut16(Rom* pROM, u32 nAddress, s16* pData) { return true; }
static bool romPut32(Rom* pROM, u32 nAddress, s32* pData) { return true; }
static bool romPut64(Rom* pROM, u32 nAddress, s64* pData) { return true; }

static bool romGet8(Rom* pROM, u32 nAddress, s8* pData) {
    u8 nData;

    nAddress = nAddress & 0x07FFFFFF;
    if (nAddress < pROM->nSize && romCopy(pROM, &nData, nAddress, 1, 0)) {
        *pData = nData;
        return true;
    } else {
        *pData = 0;
        return true;
    }
}

static bool romGet16(Rom* pROM, u32 nAddress, s16* pData) {
    u16 nData;

    nAddress = nAddress & 0x07FFFFFF;
    if (nAddress < pROM->nSize && romCopy(pROM, &nData, nAddress, 2, 0)) {
        *pData = nData;
        return true;
    } else {
        *pData = 0;
        return true;
    }
}

static bool romGet32(Rom* pROM, u32 nAddress, s32* pData) {
    u32 nData;

    nAddress = nAddress & 0x07FFFFFF;
    if (nAddress < pROM->nSize && romCopy(pROM, &nData, nAddress, 4, 0)) {
        *pData = nData;
        return true;
    } else {
        *pData = 0;
        return true;
    }
}

static bool romGet64(Rom* pROM, u32 nAddress, s64* pData) {
    u64 nData;

    nAddress = nAddress & 0x07FFFFFF;
    if (nAddress < pROM->nSize && romCopy(pROM, &nData, nAddress, 8, 0)) {
        *pData = nData;
        return true;
    } else {
        *pData = 0;
        return true;
    }
}

static bool romPutDebug8(Rom* pROM, u32 nAddress, s8* pData) { return true; }
static bool romPutDebug16(Rom* pROM, u32 nAddress, s16* pData) { return true; }
static bool romPutDebug32(Rom* pROM, u32 nAddress, s32* pData) { return true; }
static bool romPutDebug64(Rom* pROM, u32 nAddress, s64* pData) { return true; }

static bool romGetDebug8(Rom* pROM, u32 nAddress, s8* pData) {
    *pData = 0;
    return true;
}

static bool romGetDebug16(Rom* pROM, u32 nAddress, s16* pData) {
    *pData = 0;
    return true;
}

static bool romGetDebug32(Rom* pROM, u32 nAddress, s32* pData) {
    *pData = 0;
    return true;
}

static bool romGetDebug64(Rom* pROM, u32 nAddress, s64* pData) {
    *pData = 0;
    return true;
}

static inline bool romCopyLoad(Rom* pROM) {
    if (!romLoadFullOrPart(pROM)) {
        return false;
    }

    if (!romCacheGame(pROM)) {
        return false;
    }

    pROM->bLoad = false;
    return true;
}

static inline bool romCopyLoop(Rom* pROM, u8* pTarget, u32 nOffset, u32 nSize, UnknownCallbackFunc* pCallback) {
    s32 i;

    pROM->copy.bWait = false;
    pROM->copy.nSize = nSize;
    pROM->copy.pTarget = pTarget;
    pROM->copy.nOffset = nOffset;
    pROM->copy.pCallback = pCallback;

    for (i = 0; i < pROM->nCountOffsetBlocks; i += 2) {
        if ((pROM->anOffsetBlock[i] <= nOffset) && (nOffset <= pROM->anOffsetBlock[i + 1])) {
            pROM->load.nOffset0 = pROM->anOffsetBlock[i];
            pROM->load.nOffset1 = pROM->anOffsetBlock[i + 1];
            return true;
        }
    }

    return false;
}

bool romCopy(Rom* pROM, void* pTarget, s32 nOffset, s32 nSize, UnknownCallbackFunc* pCallback) {
    tXL_FILE* pFile;

    nOffset &= 0x07FFFFFF;

    if (!pROM->nSizeCacheRAM) {
        if (!xlFileOpen(&pFile, XLFT_BINARY, pROM->acNameFile)) {
            return false;
        }

        if (!xlFileSetPosition(pFile, nOffset + pROM->offsetToRom)) {
            return false;
        }

        if (!xlFileGet(pFile, pTarget, (s32)nSize)) {
            return false;
        }

        if (!xlFileClose(&pFile)) {
            return false;
        }

        if (pCallback != NULL) {
            if (!pCallback()) {
                return false;
            }
        }

        return true;
    }

    if (pROM->bLoad) {
        if (!romCopyLoad(pROM)) {
            return false;
        }
    }

    if (((nOffset + nSize) > pROM->nSize) && ((nSize = pROM->nSize - nOffset) < 0)) {
        return true;
    }

    if (pROM->eModeLoad == RLM_PART) {
        if (romCopyLoop(pROM, pTarget, nOffset, nSize, pCallback)) {
            if (!romLoadUpdate(pROM)) {
                return false;
            }
        }

        if (!romCopyUpdate(pROM)) {
            return false;
        }

        return true;
    }

    if (pROM->eModeLoad == RLM_FULL) {
        if (!xlHeapCopy(pTarget, (void*)((u32)pROM->pBuffer + nOffset), nSize)) {
            return false;
        }

        if (pCallback != NULL) {
            if (!pCallback()) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool romCopyImmediate(Rom* pROM, void* pTarget, s32 nOffsetROM, s32 nSize) {
    void* pSource;
    RomBlock* pBlock;
    s32 nOffsetARAM;
    s32 nSizeCopy;
    s32 nOffsetBlock;
    s32 nSizeCopyARAM;
    s32 nSizeDMA;
    s32 nOffset;
    s32 nOffsetTarget;
#if IS_OOT
    s32 pad;
#endif
    u8* pBuffer;
    u8 anBuffer[608];
#if IS_MM
    s32 iCache;
#endif

    if (pROM->nSizeCacheRAM == 0) {
        return false;
    }

    if (pROM->bLoad) {
        if (!romCopyLoad(pROM)) {
            return false;
        }
    }

    nOffsetROM = nOffsetROM & 0x07FFFFFF;
    pBuffer = (u8*)(((s32)anBuffer + 0x1F) & 0xFFFFFFE0);

    if (nOffsetROM + nSize > pROM->nSize && (nSize = pROM->nSize - nOffsetROM) < 0) {
        return true;
    }

    if (pROM->eModeLoad == RLM_PART) {
        while (nSize != 0U) {
            nOffsetBlock = nOffsetROM / 0x2000;
            pBlock = &pROM->aBlock[nOffsetBlock];

#if IS_OOT
            if (pBlock->nSize == 0) {
                return false;
            }
#else
            if (pBlock->nSize == 0) {
                if (!romMakeFreeCache(pROM, &iCache, 0)) {
                    return false;
                }

                if (!romLoadBlock(pROM, nOffsetBlock, iCache, NULL)) {
                    return false;
                }
            }
#endif

            nOffsetBlock = nOffsetROM % 0x2000;
            if ((nSizeCopy = pBlock->nSize - nOffsetBlock) > nSize) {
                nSizeCopy = nSize;
            }

            if (pBlock->iCache >= 0) {
                pSource = &pROM->pCacheRAM[(pBlock->iCache * 0x2000)] + nOffsetBlock;
                if (!xlHeapCopy(pTarget, pSource, nSizeCopy)) {
                    return false;
                }
            } else {
                nSizeCopyARAM = nSizeCopy;
                nOffsetTarget = 0;
                nOffsetARAM = nOffsetBlock + (-(pBlock->iCache + 1) * 0x2000);
                nOffsetARAM += ARGetBaseAddress();

                while (nSizeCopyARAM > 0) {
                    if ((nSizeDMA = nSizeCopyARAM) > 0x200) {
                        nSizeDMA = 0x200;
                    }

                    while (ARGetDMAStatus()) {}

                    nOffset = nOffsetARAM & 0x1F;
                    ARStartDMARead((u32)pBuffer, nOffsetARAM & 0xFFFFFFE0, (nSizeDMA + nOffset + 0x1F) & 0xFFFFFFE0);
                    DCInvalidateRange(pBuffer, nSizeDMA + nOffset);

                    while (ARGetDMAStatus()) {}

                    if (!xlHeapCopy((u8*)pTarget + nOffsetTarget, pBuffer + nOffset, nSizeDMA)) {
                        return false;
                    }

                    nOffsetARAM += nSizeDMA;
                    nOffsetTarget += nSizeDMA;
                    nSizeCopyARAM -= nSizeDMA;
                }
            }

            pTarget = (u8*)pTarget + nSizeCopy;
            nOffsetROM += nSizeCopy;
            nSize -= nSizeCopy;
        }
        return true;
    } else if (pROM->eModeLoad == RLM_FULL) {
        if (!xlHeapCopy(pTarget, (u8*)pROM->pBuffer + nOffsetROM, nSize)) {
            return false;
        }
        return true;
    }

    return false;
}

bool romUpdate(Rom* pROM) {
    s32 nStatus;

    if (pROM->copy.bWait || pROM->load.bWait) {
        if (pROM->load.bDone && pROM->load.nResult == pROM->load.nSizeRead) {
            pROM->load.bDone = false;
            if (!__romLoadBlock_Complete(pROM)) {
                return false;
            }
        }

        nStatus = DVDGetCommandBlockStatus(&pROM->fileInfo.cb);
        if (nStatus != 1) {
            if (!simulatorDVDShowError(nStatus, pROM->load.anData, pROM->load.nSizeRead,
                                       pROM->offsetToRom + pROM->load.nOffset)) {
                return false;
            }

            if ((nStatus == 0xB) || (nStatus == -1)) {
                DVDCancel(&pROM->fileInfo.cb);
                if (!simulatorDVDRead(&pROM->fileInfo, pROM->load.anData, pROM->load.nSizeRead,
                                      pROM->offsetToRom + pROM->load.nOffset, &__romLoadBlock_CompleteGCN)) {
                    return false;
                }
            }
        }
    }

    if (!romLoadUpdate(pROM)) {
        return false;
    }

    if (!romCopyUpdate(pROM)) {
        return false;
    }

    return true;
}

bool romSetCacheSize(Rom* pROM, s32 nSize) {
    s32 nSizeCacheRAM;

    if (nSize < 0x100000) {
        nSizeCacheRAM = 0x100000;
    } else if (nSize > 0x800000) {
        nSizeCacheRAM = 0x800000;
    } else {
        nSizeCacheRAM = (nSize + 0x1FFF) & 0xFFFFE000;
    }

    pROM->nSizeCacheRAM = nSizeCacheRAM;
    pROM->nCountBlockRAM = nSizeCacheRAM / 0x2000;

    if (!xlHeapTake(&pROM->pBuffer, nSizeCacheRAM | 0x30000000)) {
        return false;
    }

    pROM->pCacheRAM = (u8*)pROM->pBuffer;

    return true;
}

static inline void romOpen(Rom* pROM, char* szNameFile) {
    bool var_r30 = false;
    bool bFlip;

    if (pROM->acHeader[0] == 0x37 && pROM->acHeader[1] == 0x80) {
        var_r30 = true;
    }

    if (var_r30) {
        bFlip = true;
    } else {
        bFlip = false;
    }

    pROM->bFlip = bFlip;
    simulatorDVDOpen(szNameFile, &pROM->fileInfo);
}

bool romSetImage(Rom* pROM, char* szNameFile) {
#if IS_OOT_EU || IS_MM
    tXL_FILE* pFile;
    RomTokenType eToken;
    s32 iCode;
    s32 iName;
    s32 nSize;
    char acToken[65];
    u32 anData[256];
#else
    tXL_FILE* pFile;
    s32 iName;
    s32 nSize;
#endif

    for (iName = 0; (szNameFile[iName] != '\0') && (iName < 0x200); iName++) {
        pROM->acNameFile[iName] = szNameFile[iName];
    }
    pROM->acNameFile[iName] = '\0';

    if (xlFileGetSize(&nSize, pROM->acNameFile)) {
        pROM->nSize = (u32)(nSize - pROM->offsetToRom);
    } else {
        return false;
    }

    if (!xlFileOpen(&pFile, XLFT_BINARY, szNameFile)) {
        return false;
    }

    if (!xlFileSetPosition(pFile, pROM->offsetToRom)) {
        return false;
    }

    if (!xlFileGet(pFile, pROM->acHeader, sizeof(pROM->acHeader))) {
        return false;
    }

#if IS_OOT_EU || IS_MM
    if (!xlFileSetPosition(pFile, pROM->offsetToRom + 0x1000)) {
        return false;
    }

    if (!xlFileGet(pFile, anData, sizeof(anData))) {
        return false;
    }
#endif

    if (!xlFileClose(&pFile)) {
        return false;
    }

#if IS_OOT_EU || IS_MM
    for (pROM->nChecksum = 0, iCode = 0; iCode < ARRAY_COUNT(anData); iCode++) {
        pROM->nChecksum += anData[iCode];
    }
#endif

    romOpen(pROM, szNameFile);

#if IS_OOT_EU || IS_MM
    pROM->tagFile.nMode = 0;
    if (xlFileOpen(&pFile, XLFT_TEXT, "ROMS.TAG")) {
        while (romGetTagToken(pROM, pFile, &eToken, acToken)) {
            if (eToken == RTT_CODE) {
                s32 nMode = pROM->tagFile.nMode | 0x100;
                pROM->tagFile.nMode = nMode;
                pROM->tagFile.nModeSave = nMode;
                if (!xlFileGetLineSave(pFile, &pROM->tagFile.save)) {
                    return false;
                }
                break;
            }
        }

        if (!xlFileClose(&pFile)) {
            return false;
        }
    }
#endif

    return true;
}

bool romGetImage(Rom* pROM, char* acNameFile) {
    if (pROM->acNameFile[0] == '\0') {
        return false;
    }

    if (acNameFile != NULL) {
        s32 iName;

        for (iName = 0; pROM->acNameFile[iName] != '\0'; iName++) {
            acNameFile[iName] = pROM->acNameFile[iName];
        }
    }

    return true;
}

bool romEvent(Rom* pROM, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pROM->nSize = 0;
            pROM->nTick = 0;
            pROM->bLoad = true;
            pROM->bFlip = false;
            pROM->pHost = pArgument;
            pROM->acNameFile[0] = '\0';
            pROM->eModeLoad = RLM_NONE;
            pROM->pBuffer = NULL;
            pROM->offsetToRom = 0;
            pROM->anOffsetBlock = NULL;
            pROM->nCountOffsetBlocks = 0;
            pROM->copy.nSize = 0;
            pROM->copy.bWait = false;
            pROM->load.bWait = false;
            pROM->load.nOffset1 = 0;
            pROM->load.nOffset0 = 0;
            pROM->load.bDone = false;
#if IS_OOT_EU || IS_MM
            pROM->tagFile.nMode = 0;
#endif
            pROM->nSizeCacheRAM = 0;
            pROM->nCountBlockRAM = 0;
            pROM->pCacheRAM = NULL;
            break;
        case 3:
            if (pROM->pBuffer != NULL && pROM->pBuffer != pROM->pCacheRAM) {
                if (!xlHeapFree(&pROM->pBuffer)) {
                    return false;
                }
            }
            break;
        case 0x1002:
            switch (((CpuDevice*)pArgument)->nType) {
                case 0:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pROM->pHost), pArgument, (Put8Func)romPut8, (Put16Func)romPut16,
                                         (Put32Func)romPut32, (Put64Func)romPut64)) {
                        return false;
                    }
                    if (!cpuSetDeviceGet(SYSTEM_CPU(pROM->pHost), pArgument, (Get8Func)romGet8, (Get16Func)romGet16,
                                         (Get32Func)romGet32, (Get64Func)romGet64)) {
                        return false;
                    }
                    break;
                case 1:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pROM->pHost), pArgument, (Put8Func)romPutDebug8,
                                         (Put16Func)romPutDebug16, (Put32Func)romPutDebug32,
                                         (Put64Func)romPutDebug64)) {
                        return false;
                    }
                    if (!cpuSetDeviceGet(SYSTEM_CPU(pROM->pHost), pArgument, (Get8Func)romGetDebug8,
                                         (Get16Func)romGetDebug16, (Get32Func)romGetDebug32,
                                         (Get64Func)romGetDebug64)) {
                        return false;
                    }
                    break;
            }
            break;
        case 0:
        case 1:
            break;
#if VERSION != MQ_J
        case 0x1003:
            break;
#endif
        default:
            return false;
    }

    return true;
}
