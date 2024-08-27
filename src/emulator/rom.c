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

_XL_OBJECTTYPE gClassROM = {
    "ROM",
    sizeof(Rom),
    NULL,
    (EventFunc)romEvent,
};

#if IS_JP
#include "ganOffsetBlock_ZLJ.inc"
#include "ganOffsetBlock_URAZLJ.inc"
#elif IS_US
#include "ganOffsetBlock_ZLE.inc"
#include "ganOffsetBlock_URAZLE.inc"
#elif IS_EU
#include "ganOffsetBlock_ZLP.inc"
#include "ganOffsetBlock_URAZLP.inc"
#endif

static bool gbProgress;
static void* gpImageBack;
static s32 iImage;

#if IS_EU
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
    iCache = pBlock->iCache;
    if (iCache < 0) {
        iCache = -(iCache + 1);
        pROM->anBlockCachedARAM[iCache >> 3] &= ~(1 << (iCache & 7));
    } else {
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
        if (pProgressCallback != NULL) {
            pProgressCallback((f32)(iBlock - (begin / 0x2000)) / (f32)((end - begin) / 0x2000));
        }

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

static bool romCacheGame_ZELDA(f32 rProgress) {
    s32 nSize;
    Mtx44 matrix44;
    GXTexObj textureObject;

    f32 var_f1;
    s32 temp_r31;

    if (gbDisplayedError) {
        gbDisplayedError = false;

        TEXGetGXTexObjFromPalette(gpImageBack, &textureObject, 0);
        xlCoreBeforeRender();
        GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        C_MTXOrtho(matrix44, 0.0f, 479.0f, 0.0f, 639.0f, 0.0f, 1.0f);
        GXSetProjection(matrix44, 1);
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

        DEMODoneRender();
    }

    if (!(iImage & 7)) {
        VIWaitForRetrace();

        if (gbProgress) {
            var_f1 = (rProgress / 2.0f) + 0.5f;
        } else {
            var_f1 = rProgress / 2.0f;
        }
        temp_r31 = (s32)(400.0f * var_f1);

        if (!_frameDrawRectangle(SYSTEM_FRAME(gpSystem), 0x4083407D, 120, 430, 400, 8)) {
            return false;
        }

        if (!_frameDrawRectangle(SYSTEM_FRAME(gpSystem), 0x8F9B8F7C, 120, 430, temp_r31, 8)) {
            return false;
        }
    }

    iImage += 1;
    if (rProgress == 1.0f) {
        gbProgress = true;
    }
    return true;
}

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
            pROM->anOffsetBlock = (u32*)ganOffsetBlock_ZLJ;
            pROM->nCountOffsetBlocks = 0xC6;
        } else {
            pROM->anOffsetBlock = (u32*)ganOffsetBlock_URAZLJ;
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
                pROM->anOffsetBlock = (u32*)ganOffsetBlock_ZLJ;
                pROM->nCountOffsetBlocks = 0xC6;
            }
        } else if (!bIsCZLE) {
            pROM->anOffsetBlock = (u32*)ganOffsetBlock_URAZLJ;
            pROM->nCountOffsetBlocks = 0xC6;
        }
#elif IS_US
        if (gnFlagZelda & 2) {
            if (bIsCZLE) {
                pROM->anOffsetBlock = (u32*)ganOffsetBlock_ZLE;
                pROM->nCountOffsetBlocks = 0xC6;
            }
        } else if (bIsCZLE) {
            pROM->anOffsetBlock = (u32*)ganOffsetBlock_URAZLE;
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

#elif IS_EU

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
                pROM->anOffsetBlock = (u32*)ganOffsetBlock_ZLP;
                pROM->nCountOffsetBlocks = 0xC6;
            }
        } else if (!bZeldaE && !bZeldaJ && (bZeldaE || bZeldaF || bZeldaG || bZeldaI || bZeldaS)) {
            pROM->anOffsetBlock = (u32*)ganOffsetBlock_URAZLP;
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
            if (pBlock->iCache < 0 && !romSetBlockCache(pROM, iBlock, 0)) {
                return false;
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

static inline bool romLoadFullOrPartLoop(Rom* pROM) {
    s32 i;
    s32 iCache;
    u32 temp_r27;
    u32 temp_r30;

    temp_r27 = (u32)(pROM->nSize - 1) / 0x2000;
    temp_r30 = pROM->nTick = temp_r27 + 1;

    for (i = 0; i < temp_r30; i++) {
        pROM->aBlock[i].nTickUsed = temp_r27 - i;

        if (!romMakeFreeCache(pROM, &iCache, RCT_RAM)) {
            return false;
        }

        if (!romLoadBlock(pROM, i, iCache, NULL)) {
            return false;
        }
    }

    return true;
}

static bool romLoadFullOrPart(Rom* pROM) {
    tXL_FILE* pFile;
    s32 pad;

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

        if ((s32)pROM->nSize < (pROM->nSizeCacheRAM + 0xFFA000) && !romLoadFullOrPartLoop(pROM)) {
            return false;
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
                simulatorShowLoad(0, pROM->acNameFile, (f32)i / (f32)pROM->nSize);
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

#if IS_EU
bool romTestCode(Rom* pROM, char* acCode) {
    s32 iCode;
    int nCode1;
    int nCode2;

    for (iCode = 0; iCode < 4; iCode++) {
        nCode1 = pROM->acHeader[iCode + 0x3B];
        if (nCode1 >= 0x61 && nCode1 <= 0x7A) {
            nCode1 -= 0x20;
        }

        nCode2 = acCode[iCode];
        if (nCode2 >= 0x61 && nCode2 <= 0x7A) {
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

        if ((pCallback != NULL) && !pCallback()) {
            return false;
        }

        return true;
    }

    if (pROM->bLoad && !romCopyLoad(pROM)) {
        return false;
    }

    if (((nOffset + nSize) > pROM->nSize) && ((nSize = pROM->nSize - nOffset) < 0)) {
        return true;
    }

    if (pROM->eModeLoad == RLM_PART) {
        if (romCopyLoop(pROM, pTarget, nOffset, nSize, pCallback) && !romLoadUpdate(pROM)) {
            return false;
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

        if ((pCallback != NULL) && !pCallback()) {
            return false;
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
    s32 pad;
    u8* pBuffer;
    u8 anBuffer[608];

    if (pROM->nSizeCacheRAM == 0) {
        return false;
    }

    if (pROM->bLoad && !romCopyLoad(pROM)) {
        return false;
    }

    nOffsetROM = nOffsetROM & 0x07FFFFFF;
    pBuffer = (u8*)(((s32)anBuffer + 0x1F) & 0xFFFFFFE0);

    if (nOffsetROM + nSize > pROM->nSize && (nSize = pROM->nSize - nOffsetROM) < 0) {
        return true;
    }

    if (pROM->eModeLoad == RLM_PART) {
        while (nSize != 0U) {
            pBlock = &pROM->aBlock[nOffsetROM / 0x2000];
            if (pBlock->nSize == 0) {
                return false;
            }

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
#if IS_EU
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

#if IS_EU
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

#if IS_EU
    for (pROM->nChecksum = 0, iCode = 0; iCode < ARRAY_COUNT(anData); iCode++) {
        pROM->nChecksum += anData[iCode];
    }
#endif

    romOpen(pROM, szNameFile);

#if IS_EU
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
#if IS_EU
            pROM->tagFile.nMode = 0;
#endif
            pROM->nSizeCacheRAM = 0;
            pROM->nCountBlockRAM = 0;
            pROM->pCacheRAM = NULL;
            break;
        case 3:
            if ((pROM->pBuffer != NULL) && (pROM->pBuffer != pROM->pCacheRAM) && (!xlHeapFree(&pROM->pBuffer))) {
                return false;
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
