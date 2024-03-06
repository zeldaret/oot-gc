#include "rom.h"
#include "cpu.h"
#include "dolphin.h"
#include "frame.h"
#include "macros.h"
#include "ram.h"
#include "simGCN.h"
#include "system.h"
#include "xlCoreGCN.h"

static s32 romMakeFreeCache(Rom* pROM, s32* piCache, RomCacheType eType);
static s32 romSetBlockCache(Rom* pROM, s32 iBlock, RomCacheType eType);

_XL_OBJECTTYPE gClassROM = {
    "ROM",
    sizeof(Rom),
    NULL,
    (EventFunc)romEvent,
};

static u32 ganOffsetBlock_ZLJ[198] = {
    0x01685160, 0x016D376F, 0x016D3770, 0x0172B78F, 0x0172B790, 0x0175E1CF, 0x0175E1D0, 0x017BE4FF, 0x017BE500,
    0x0182EA4F, 0x0182EA50, 0x0189A76F, 0x0189A770, 0x0191AD0F, 0x0191AD10, 0x0198436F, 0x01984370, 0x019CA5CF,
    0x019CA5D0, 0x01A0942F, 0x01A09430, 0x01A71DEF, 0x01A71DF0, 0x01A950EF, 0x01A950F0, 0x01AAC75F, 0x01AAC760,
    0x01AC6D2F, 0x01AC6D30, 0x01ADA7CF, 0x01ADA7D0, 0x01AFD5EF, 0x01AFD5F0, 0x01B0F1BF, 0x01B0F1C0, 0x01B26F1F,
    0x01B26F20, 0x01B3767F, 0x01B37680, 0x01B4864F, 0x01B48650, 0x01B5775F, 0x01B57760, 0x01B774EF, 0x01B774F0,
    0x01B8FB7F, 0x01B8FB80, 0x01BA9BDF, 0x01BA9BE0, 0x01BB94DF, 0x01BB94E0, 0x01BCF94F, 0x01BCF950, 0x01BEB27F,
    0x01BEB280, 0x01C023AF, 0x01C023B0, 0x01C3165F, 0x01C31660, 0x01C341FF, 0x01C34200, 0x01C36C9F, 0x01C36CA0,
    0x01C41BFF, 0x01C41C00, 0x01C545EF, 0x01C545F0, 0x01C5C85F, 0x01C5C860, 0x01C64A2F, 0x01C64A30, 0x01C6D8FF,
    0x01C6D900, 0x01CADDAF, 0x01CADDB0, 0x01CB559F, 0x01CB55A0, 0x01CC11FF, 0x01CC1200, 0x01CCAD9F, 0x01CCADA0,
    0x01CD06CF, 0x01CD06D0, 0x01CDF62F, 0x01CDF630, 0x01CEEF0F, 0x01CEEF10, 0x01D007FF, 0x01D00800, 0x01D0DFDF,
    0x01D0DFE0, 0x01D0F5FF, 0x01D0F600, 0x01D148AF, 0x01D148B0, 0x01D1B0FF, 0x01D1B100, 0x01D2870F, 0x01D28710,
    0x01D29FFF, 0x01D2A000, 0x01D35B2F, 0x01D35B30, 0x01D3D55F, 0x01D3D560, 0x01D4366F, 0x01D43670, 0x01D487DF,
    0x01D487E0, 0x01D5193F, 0x01D51940, 0x01D56E6F, 0x01D56E70, 0x01D5F1FF, 0x01D5F200, 0x01D63CEF, 0x01D63CF0,
    0x01D6B4EF, 0x01D6B4F0, 0x01D72DAF, 0x01D72DB0, 0x01D7797F, 0x01D77980, 0x01D7CE2F, 0x01D7CE30, 0x01D8342F,
    0x01D83430, 0x01D8845F, 0x01D88460, 0x01D8DCEF, 0x01D8DCF0, 0x01D92C6F, 0x01D92C70, 0x01D9A38F, 0x01D9A390,
    0x01DA39EF, 0x01DA39F0, 0x01DB34CF, 0x01DB34D0, 0x01DBA48F, 0x01DBA490, 0x01DC53FF, 0x01DC5400, 0x01DCBB3F,
    0x01DCBB40, 0x01DD524F, 0x01DD5250, 0x01E0A42F, 0x01E0A430, 0x01E1BCDF, 0x01E1BCE0, 0x01E296DF, 0x01E296E0,
    0x01E3398F, 0x01E33990, 0x01E45A6F, 0x01E45A70, 0x01E4C74F, 0x01E4C750, 0x01E72C6F, 0x01E72C70, 0x01E80F5F,
    0x01E80F60, 0x01E90CAF, 0x01E90CB0, 0x01E9BC2F, 0x01E9BC30, 0x01EA6E9F, 0x01EA6EA0, 0x01EB30BF, 0x01EB30C0,
    0x01ECADFF, 0x01ECAE00, 0x01ED259F, 0x01ED25A0, 0x01EDD1EF, 0x01EDD1F0, 0x01EEB1CF, 0x01EEB1D0, 0x01EF793F,
    0x01EF7940, 0x01F0A15F, 0x01F0A160, 0x01F12BFF, 0x01F12C00, 0x01F1C5AF, 0x01F1C5B0, 0x01F2D9DF, 0x01F2D9E0,
    0x01F440CF, 0x01F440D0, 0x01F4D90F, 0x01F4D910, 0x01F5623F, 0x01F56240, 0x01F60C1F, 0x01F60C20, 0x01F7209F,
};

static u32 ganOffsetBlock_URAZLJ[198] = {
    0x01684BD0, 0x016D355F, 0x016D3560, 0x0172B9AF, 0x0172B9B0, 0x0175E9CF, 0x0175E9D0, 0x017BEE5F, 0x017BEE60,
    0x0182F2AF, 0x0182F2B0, 0x0189B35F, 0x0189B360, 0x0191BC0F, 0x0191BC10, 0x01985B8F, 0x01985B90, 0x019CBE9F,
    0x019CBEA0, 0x01A0AC2F, 0x01A0AC30, 0x01A7371F, 0x01A73720, 0x01A96A1F, 0x01A96A20, 0x01AAE08F, 0x01AAE090,
    0x01AC865F, 0x01AC8660, 0x01ADC0EF, 0x01ADC0F0, 0x01AFEF0F, 0x01AFEF10, 0x01B10ADF, 0x01B10AE0, 0x01B2883F,
    0x01B28840, 0x01B38F9F, 0x01B38FA0, 0x01B49F6F, 0x01B49F70, 0x01B5907F, 0x01B59080, 0x01B78E0F, 0x01B78E10,
    0x01B9149F, 0x01B914A0, 0x01BAB4FF, 0x01BAB500, 0x01BBADFF, 0x01BBAE00, 0x01BD126F, 0x01BD1270, 0x01BECB9F,
    0x01BECBA0, 0x01C03CDF, 0x01C03CE0, 0x01C32F8F, 0x01C32F90, 0x01C35B2F, 0x01C35B30, 0x01C385CF, 0x01C385D0,
    0x01C4352F, 0x01C43530, 0x01C55F1F, 0x01C55F20, 0x01C5E18F, 0x01C5E190, 0x01C6635F, 0x01C66360, 0x01C6F22F,
    0x01C6F230, 0x01CAF6DF, 0x01CAF6E0, 0x01CB6ECF, 0x01CB6ED0, 0x01CC2B2F, 0x01CC2B30, 0x01CCC6CF, 0x01CCC6D0,
    0x01CD1FFF, 0x01CD2000, 0x01CE0F5F, 0x01CE0F60, 0x01CF083F, 0x01CF0840, 0x01D0212F, 0x01D02130, 0x01D0F90F,
    0x01D0F910, 0x01D10F2F, 0x01D10F30, 0x01D161DF, 0x01D161E0, 0x01D1CA2F, 0x01D1CA30, 0x01D2A03F, 0x01D2A040,
    0x01D2B92F, 0x01D2B930, 0x01D3745F, 0x01D37460, 0x01D3EE8F, 0x01D3EE90, 0x01D44FAF, 0x01D44FB0, 0x01D4A11F,
    0x01D4A120, 0x01D5327F, 0x01D53280, 0x01D587AF, 0x01D587B0, 0x01D60B3F, 0x01D60B40, 0x01D6562F, 0x01D65630,
    0x01D6CE2F, 0x01D6CE30, 0x01D746EF, 0x01D746F0, 0x01D792BF, 0x01D792C0, 0x01D7E76F, 0x01D7E770, 0x01D84D6F,
    0x01D84D70, 0x01D89D9F, 0x01D89DA0, 0x01D8F62F, 0x01D8F630, 0x01D945AF, 0x01D945B0, 0x01D9BCCF, 0x01D9BCD0,
    0x01DA532F, 0x01DA5330, 0x01DB4E0F, 0x01DB4E10, 0x01DBBDCF, 0x01DBBDD0, 0x01DC6D3F, 0x01DC6D40, 0x01DCD47F,
    0x01DCD480, 0x01DD6B8F, 0x01DD6B90, 0x01E0BD6F, 0x01E0BD70, 0x01E1D61F, 0x01E1D620, 0x01E2B01F, 0x01E2B020,
    0x01E352CF, 0x01E352D0, 0x01E473AF, 0x01E473B0, 0x01E4E08F, 0x01E4E090, 0x01E745AF, 0x01E745B0, 0x01E8289F,
    0x01E828A0, 0x01E925EF, 0x01E925F0, 0x01E9D56F, 0x01E9D570, 0x01EA87DF, 0x01EA87E0, 0x01EB49FF, 0x01EB4A00,
    0x01ECC73F, 0x01ECC740, 0x01ED3EDF, 0x01ED3EE0, 0x01EDEB2F, 0x01EDEB30, 0x01EECB0F, 0x01EECB10, 0x01EF927F,
    0x01EF9280, 0x01F0BA9F, 0x01F0BAA0, 0x01F1453F, 0x01F14540, 0x01F1DEEF, 0x01F1DEF0, 0x01F2F31F, 0x01F2F320,
    0x01F45A0F, 0x01F45A10, 0x01F4F24F, 0x01F4F250, 0x01F57B7F, 0x01F57B80, 0x01F6255F, 0x01F62560, 0x01F739DF,
};

static s32 gbProgress;
static void* gpImageBack;
static s32 iImage;

static s32 romFindFreeCache(Rom* pROM, s32* piCache, RomCacheType eType) {
    s32 iBlock;

    if (eType == RCT_RAM) {
        for (iBlock = 0; iBlock < pROM->nCountBlockRAM; iBlock++) {
            if (!(pROM->anBlockCachedRAM[iBlock >> 3] & (1 << (iBlock & 7)))) {
                *piCache = iBlock;
                return 1;
            }
        }
    } else if (eType == RCT_ARAM) {
        for (iBlock = 0; iBlock < ARRAY_COUNT(pROM->anBlockCachedARAM); iBlock++) {
            if (!(pROM->anBlockCachedARAM[iBlock >> 3] & (1 << (iBlock & 7)))) {
                *piCache = -(iBlock + 1);
                return 1;
            }
        }
    } else {
        return 0;
    }

    return 0;
}

static s32 romFindOldestBlock(Rom* pROM, s32* piBlock, RomCacheType eTypeCache, s32 whichBlock) {
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
        return 1;
    }

    return 0;
}

inline void romMarkBlockAsFree(Rom* pROM, s32 iBlock) {
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

static s32 romMakeFreeCache(Rom* pROM, s32* piCache, RomCacheType eType) {
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
                return 0;
            }
        }
    } else {
        if (!romFindFreeCache(pROM, &iCache, RCT_ARAM)) {
            if (romFindOldestBlock(pROM, &iBlockOldest, RCT_ARAM, 0)) {
                iCache = pROM->aBlock[iBlockOldest].iCache;
                romMarkBlockAsFree(pROM, iBlockOldest);
            } else {
                return 0;
            }
        }
    }

    *piCache = iCache;
    return 1;
}

static s32 romSetBlockCache(Rom* pROM, s32 iBlock, RomCacheType eType) {
    RomBlock* pBlock;
    s32 iCacheRAM;
    s32 iCacheARAM;
    s32 nOffsetRAM;
    s32 nOffsetARAM;

    pBlock = &pROM->aBlock[iBlock];
    if ((eType == RCT_RAM && pBlock->iCache >= 0) || (eType == RCT_ARAM && pBlock->iCache < 0)) {
        return 1;
    }

    if (eType == RCT_RAM) {
        iCacheARAM = -(pBlock->iCache + 1);
        if (!romMakeFreeCache(pROM, &iCacheRAM, RCT_RAM)) {
            return 0;
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
            return 0;
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
        return 0;
    }

    while (ARGetDMAStatus()) {}

    return 1;
}

static s32 __romLoadBlock_Complete(Rom* pROM) {
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
        return 0;
    }

    return 1;
}

static void __romLoadBlock_CompleteGCN(long nResult, DVDFileInfo* fileInfo) {
    Rom* pROM = SYSTEM_ROM(gpSystem);

    pROM->load.nResult = nResult;
    pROM->load.bDone = 1;
}

static s32 romLoadBlock(Rom* pROM, s32 iBlock, s32 iCache, UnknownCallbackFunc pCallback) {
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
            return 0;
        }
    } else {
        pROM->load.nOffset = nOffset;
        pROM->load.nSizeRead = nSizeRead;
        if (!simulatorDVDRead(&pROM->fileInfo, anData, nSizeRead, nOffset + pROM->offsetToRom,
                              &__romLoadBlock_CompleteGCN)) {
            return 0;
        }
        return 1;
    }

    if (!__romLoadBlock_Complete(pROM)) {
        return 0;
    }
    return 1;
}

static s32 romLoadRange(Rom* pROM, s32 begin, s32 end, s32* blockCount, s32 whichBlock,
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
                return 0;
            }

            if (!romLoadBlock(pROM, iBlock, iCache, NULL)) {
                return 0;
            }
        }

        pROM->aBlock[iBlock].keep = whichBlock;
        pROM->aBlock[iBlock].nTickUsed = ++pROM->nTick;

        if (blockCount != NULL) {
            *blockCount += 1;
        }
    }

    return 1;
}

static s32 romCacheGame_ZELDA(f32 rProgress) {
    s32 nSize;
    Mtx44 matrix44;
    GXTexObj textureObject;

    f32 var_f1;
    s32 temp_r31;

    if (gbDisplayedError != 0) {
        gbDisplayedError = 0;

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
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(0xD, 1);
        GXSetVtxAttrFmt(0, 9, 0, 4, 0);
        GXSetVtxAttrFmt(0, 0xD, 1, 0, 0);
        GXLoadTexObj(&textureObject, 0);
        GXBegin(0x80, 0, 4);

        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.s8 = 0;
        GXWGFifo.s8 = 0;
        GXWGFifo.f32 = 640.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.s8 = 1;
        GXWGFifo.s8 = 0;
        GXWGFifo.f32 = 640.0f;
        GXWGFifo.f32 = 480.0f;
        GXWGFifo.s8 = 1;
        GXWGFifo.s8 = 1;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 480.0f;
        GXWGFifo.s8 = 0;
        GXWGFifo.s8 = 1;

        DEMODoneRender();
    }

    if (!(iImage & 7)) {
        VIWaitForRetrace();

        if (gbProgress != 0) {
            var_f1 = (rProgress / 2.0f) + 0.5f;
        } else {
            var_f1 = rProgress / 2.0f;
        }
        temp_r31 = (s32)(400.0f * var_f1);

        if (!_frameDrawRectangle(SYSTEM_FRAME(gpSystem), 0x4083407D, 120, 430, 400, 8)) {
            return 0;
        }

        if (!_frameDrawRectangle(SYSTEM_FRAME(gpSystem), 0x8F9B8F7C, 120, 430, temp_r31, 8)) {
            return 0;
        }
    }

    iImage += 1;
    if (rProgress == 1.0f) {
        gbProgress = 1;
    }
    return 1;
}

static s32 romCacheGame(Rom* pROM) {
    s32 blockCount;
    s32 nSize;
    char* szName;
    s32 bIsCZLE;
    s32 bIsCZLJ;
    tXL_FILE* pFile;

    blockCount = 0;
    gDVDResetToggle = 1;

    bIsCZLE = romTestCode(pROM, "CZLE");
    bIsCZLJ = romTestCode(pROM, "CZLJ");
    if (bIsCZLE || bIsCZLJ) {
        if (gnFlagZelda & 2) {
            if (!bIsCZLE) {
                pROM->anOffsetBlock = ganOffsetBlock_ZLJ;
                pROM->nCountOffsetBlocks = 0xC6;
            }
        } else if (!bIsCZLE) {
            pROM->anOffsetBlock = ganOffsetBlock_URAZLJ;
            pROM->nCountOffsetBlocks = 0xC6;
        }

        if (bIsCZLE) {
            szName = gnFlagZelda & 2 ? "zle.tpl" : "urazle.tpl";
        } else if (bIsCZLJ) {
            szName = gnFlagZelda & 2 ? "zlj.tpl" : "urazlj.tpl";
        } else {
            szName = "";
        }
        if (xlFileOpen(&pFile, 1, szName) != 0) {
            nSize = pFile->nSize;
            gpImageBack = (u8*)SYSTEM_RAM(pROM->pHost)->pBuffer + 0x300000;
            if (xlFileGet(pFile, gpImageBack, nSize) == 0) {
                return 0;
            }
            if (xlFileClose(&pFile) == 0) {
                return 0;
            }
            simulatorUnpackTexPalette(gpImageBack);
            DCStoreRange(gpImageBack, nSize);
            gbProgress = 0;
            gbDisplayedError = 1;
        }
        if (gnFlagZelda & 2) {
            if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return 0;
            }
            if (!romLoadRange(pROM, 0xAFDAA0, 0x0168515F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return 0;
            }
        } else {
            if (!romLoadRange(pROM, 0, 0xA6251F, &blockCount, 1, &romCacheGame_ZELDA)) {
                return 0;
            }
            if (!romLoadRange(pROM, 0xAFDB00, 0x01684BCF, &blockCount, 1, &romCacheGame_ZELDA)) {
                return 0;
            }
        }
    } else if (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE")) {
        if (!romLoadRange(pROM, 0, 0xEFAB5F, &blockCount, 1, NULL)) {
            return 0;
        }
        if (!romLoadRange(pROM, 0x0167CE40, 0x016B4E8F, &blockCount, 1, NULL)) {
            return 0;
        }
        if (!romLoadRange(pROM, 0x01F82960, pROM->nSize - 1, &blockCount, 1, NULL)) {
            return 0;
        }
    }

    gDVDResetToggle = 0;
    return 1;
}

s32 __romLoadUpdate_Complete(void) {
    Rom* pROM = SYSTEM_ROM(gpSystem);

    pROM->load.bWait = 0;
    return 1;
}

static s32 romLoadUpdate(Rom* pROM) {
    s32 iCache;
    RomBlock* pBlock;
    u32 iBlock0;
    u32 iBlock1;
    Cpu* pCPU;

    pCPU = SYSTEM_CPU(pROM->pHost);
    if ((pROM->load.nOffset0 == 0 && pROM->load.nOffset1 == 0) || pROM->load.bWait) {
        return 1;
    }

    iBlock0 = pROM->load.nOffset0 >> 0xD;
    iBlock1 = pROM->load.nOffset1 >> 0xD;

    while (iBlock0 <= iBlock1) {
        if (pCPU->nRetrace != pCPU->nRetraceUsed) {
            return 1;
        }

        if (!simulatorTestReset(0, 0, 1, 0)) {
            return 0;
        }

        pBlock = &pROM->aBlock[iBlock0];
        pBlock->nTickUsed = ++pROM->nTick;
        if (pBlock->nSize == 0) {
            if (!romMakeFreeCache(pROM, &iCache, 0)) {
                return 0;
            }

            pROM->load.bWait = 1;
            if (!romLoadBlock(pROM, iBlock0, iCache, &__romLoadUpdate_Complete)) {
                return 0;
            }

            return 1;
        }

        pROM->load.nOffset0 = ++iBlock0 * 0x2000;
    }

    pROM->load.nOffset1 = 0U;
    pROM->load.nOffset0 = 0U;
    return 1;
}

static s32 __romCopyUpdate_Complete(void) {
    Rom* pROM = SYSTEM_ROM(gpSystem);

    pROM->copy.bWait = 0;
    return 1;
}

static s32 romCopyUpdate(Rom* pROM) {
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
        return 1;
    }

    while (pROM->copy.nSize != 0) {
        if (pROM->copy.pCallback != NULL && pCPU->nRetrace != pCPU->nRetraceUsed) {
            return 1;
        }

        if (!simulatorTestReset(0, 0, 1, 0)) {
            return 0;
        }

        iBlock = pROM->copy.nOffset / 0x2000;
        pBlock = &pROM->aBlock[iBlock];
        nTickLast = pBlock->nTickUsed;
        pBlock->nTickUsed = ++pROM->nTick;

        if (pBlock->nSize != 0) {
            if (pBlock->iCache < 0 && !romSetBlockCache(pROM, iBlock, 0)) {
                return 0;
            }
        } else {
            if (!romMakeFreeCache(pROM, &iCache, 0)) {
                return 0;
            }

            if (pROM->copy.pCallback == NULL) {
                if (!romLoadBlock(pROM, iBlock, iCache, NULL)) {
                    return 0;
                }
            } else {
                pBlock->nTickUsed = nTickLast;
                pROM->nTick--;
                pROM->copy.bWait = 1;
                if (!romLoadBlock(pROM, iBlock, iCache, &__romCopyUpdate_Complete)) {
                    return 0;
                } else {
                    return 1;
                }
            }
        }

        nOffsetBlock = pROM->copy.nOffset & 0x1FFF;
        if ((nSize = pBlock->nSize - nOffsetBlock) > pROM->copy.nSize) {
            nSize = pROM->copy.nSize;
        }

        anData = &pROM->pCacheRAM[pBlock->iCache * 0x2000];
        if (!xlHeapCopy(pROM->copy.pTarget, anData + nOffsetBlock, nSize)) {
            return 0;
        }

        pROM->copy.pTarget = (u8*)pROM->copy.pTarget + nSize;
        pROM->copy.nSize -= nSize;
        pROM->copy.nOffset += nSize;
    }

    if (pROM->copy.pCallback != NULL && !pROM->copy.pCallback()) {
        return 0;
    }
    return 1;
}

inline s32 romLoadFullOrPartLoop(Rom* pROM) {
    s32 i;
    s32 iCache;
    u32 temp_r27;
    u32 temp_r30;

    temp_r27 = (u32)(pROM->nSize - 1) / 0x2000;
    temp_r30 = pROM->nTick = temp_r27 + 1;

    for (i = 0; i < temp_r30; i++) {
        pROM->aBlock[i].nTickUsed = temp_r27 - i;

        if (!romMakeFreeCache(pROM, &iCache, RCT_RAM)) {
            return 0;
        }

        if (!romLoadBlock(pROM, i, iCache, NULL)) {
            return 0;
        }
    }

    return 1;
}

static s32 romLoadFullOrPart(Rom* pROM) {
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
            return 0;
        }
    } else {
        s32 i;
        u32 temp_r28;

        if (!xlFileOpen(&pFile, XLFT_BINARY, pROM->acNameFile)) {
            return 0;
        }

        pROM->pBuffer = (void*)pROM->pCacheRAM;

        if ((temp_r28 = (u32)pROM->nSize >> 5) == 0) {
            if (!xlFileSetPosition(pFile, pROM->offsetToRom)) {
                return 0;
            }

            xlFileGet(pFile, pROM->pBuffer, pROM->nSize);
            simulatorShowLoad(1, pROM->acNameFile, 1.0f);
        } else {
            for (i = 0; i < (s32)pROM->nSize;) {
                if (!simulatorTestReset(0, 0, 1, 0)) {
                    return 0;
                }

                xlFileGet(pFile, (void*)((u32)pROM->pBuffer + i), (s32)temp_r28);
                i += temp_r28;
                simulatorShowLoad(0, pROM->acNameFile, (f32)i / (f32)pROM->nSize);
            }
        }

        if (!xlFileClose(&pFile)) {
            return 0;
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

    return 1;
}

s32 romGetPC(Rom* pROM, u64* pnPC) {
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
                return 0;
        }

        *pnPC = anData[2] - nOffset;
        return 1;
    } else {
        return 0;
    }
}

s32 romGetCode(Rom* pROM, char* acCode) {
    s32 iCode;

    for (iCode = 0; iCode < 4; iCode++) {
        acCode[iCode] = pROM->acHeader[iCode + 0x3B];
    }
    acCode[4] = '\0';

    return 1;
}

s32 romTestCode(Rom* pROM, char* acCode) {
    s32 iCode;
    char acCodeCurrent[5];

    romGetCode(pROM, acCodeCurrent);

    for (iCode = 0; iCode < 4; iCode++) {
        if (acCode[iCode] != acCodeCurrent[iCode]) {
            return 0;
        }
    }

    return 1;
}

static s32 romPut8(Rom* pROM, u32 nAddress, s8* pData) { return 1; }
static s32 romPut16(Rom* pROM, u32 nAddress, s16* pData) { return 1; }
static s32 romPut32(Rom* pROM, u32 nAddress, s32* pData) { return 1; }
static s32 romPut64(Rom* pROM, u32 nAddress, s64* pData) { return 1; }

static s32 romGet8(Rom* pROM, u32 nAddress, s8* pData) {
    u8 nData;

    nAddress = nAddress & 0x07ffffff;
    if (nAddress < pROM->nSize && romCopy(pROM, &nData, nAddress, 1, 0)) {
        *pData = nData;
        return 1;
    } else {
        *pData = 0;
        return 1;
    }
}

static s32 romGet16(Rom* pROM, u32 nAddress, s16* pData) {
    u16 nData;

    nAddress = nAddress & 0x07ffffff;
    if (nAddress < pROM->nSize && romCopy(pROM, &nData, nAddress, 2, 0)) {
        *pData = nData;
        return 1;
    } else {
        *pData = 0;
        return 1;
    }
}

static s32 romGet32(Rom* pROM, u32 nAddress, s32* pData) {
    u32 nData;

    nAddress = nAddress & 0x07ffffff;
    if (nAddress < pROM->nSize && romCopy(pROM, &nData, nAddress, 4, 0)) {
        *pData = nData;
        return 1;
    } else {
        *pData = 0;
        return 1;
    }
}

static s32 romGet64(Rom* pROM, u32 nAddress, s64* pData) {
    u64 nData;

    nAddress = nAddress & 0x07ffffff;
    if (nAddress < pROM->nSize && romCopy(pROM, &nData, nAddress, 8, 0)) {
        *pData = nData;
        return 1;
    } else {
        *pData = 0;
        return 1;
    }
}

static s32 romPutDebug8(Rom* pROM, u32 nAddress, s8* pData) { return 1; }
static s32 romPutDebug16(Rom* pROM, u32 nAddress, s16* pData) { return 1; }
static s32 romPutDebug32(Rom* pROM, u32 nAddress, s32* pData) { return 1; }
static s32 romPutDebug64(Rom* pROM, u32 nAddress, s64* pData) { return 1; }

static s32 romGetDebug8(Rom* pROM, u32 nAddress, s8* pData) {
    *pData = 0;
    return 1;
}

static s32 romGetDebug16(Rom* pROM, u32 nAddress, s16* pData) {
    *pData = 0;
    return 1;
}

static s32 romGetDebug32(Rom* pROM, u32 nAddress, s32* pData) {
    *pData = 0;
    return 1;
}

static s32 romGetDebug64(Rom* pROM, u32 nAddress, s64* pData) {
    *pData = 0;
    return 1;
}

inline s32 romCopyLoad(Rom* pROM) {
    if (!romLoadFullOrPart(pROM)) {
        return 0;
    }

    if (!romCacheGame(pROM)) {
        return 0;
    }

    pROM->bLoad = 0;
    return 1;
}

inline s32 romCopyLoop(Rom* pROM, u8* pTarget, u32 nOffset, u32 nSize, UnknownCallbackFunc* pCallback) {
    s32 i;

    pROM->copy.bWait = 0;
    pROM->copy.nSize = nSize;
    pROM->copy.pTarget = pTarget;
    pROM->copy.nOffset = nOffset;
    pROM->copy.pCallback = pCallback;

    for (i = 0; i < pROM->nCountOffsetBlocks; i += 2) {
        if ((pROM->anOffsetBlock[i] <= nOffset) && (nOffset <= pROM->anOffsetBlock[i + 1])) {
            pROM->load.nOffset0 = pROM->anOffsetBlock[i];
            pROM->load.nOffset1 = pROM->anOffsetBlock[i + 1];
            return 1;
        }
    }

    return 0;
}

s32 romCopy(Rom* pROM, void* pTarget, s32 nOffset, s32 nSize, UnknownCallbackFunc* pCallback) {
    tXL_FILE* pFile;

    nOffset &= 0x07FFFFFF;

    if (!pROM->nSizeCacheRAM) {
        if (!xlFileOpen(&pFile, XLFT_BINARY, pROM->acNameFile)) {
            return 0;
        }

        if (!xlFileSetPosition(pFile, nOffset + pROM->offsetToRom)) {
            return 0;
        }

        if (!xlFileGet(pFile, pTarget, (s32)nSize)) {
            return 0;
        }

        if (!xlFileClose(&pFile)) {
            return 0;
        }

        if ((pCallback != NULL) && !pCallback()) {
            return 0;
        }

        return 1;
    }

    if (pROM->bLoad && !romCopyLoad(pROM)) {
        return 0;
    }

    if (((nOffset + nSize) > pROM->nSize) && ((nSize = pROM->nSize - nOffset) < 0)) {
        return 1;
    }

    if (pROM->eModeLoad == RLM_PART) {
        if (romCopyLoop(pROM, pTarget, nOffset, nSize, pCallback) && !romLoadUpdate(pROM)) {
            return 0;
        }

        if (!romCopyUpdate(pROM)) {
            return 0;
        }

        return 1;
    }

    if (pROM->eModeLoad == RLM_FULL) {
        if (!xlHeapCopy(pTarget, (void*)((u32)pROM->pBuffer + nOffset), nSize)) {
            return 0;
        }

        if ((pCallback != NULL) && !pCallback()) {
            return 0;
        }

        return 1;
    }

    return 0;
}

s32 romCopyImmediate(Rom* pROM, void* pTarget, s32 nOffsetROM, s32 nSize) {
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
        return 0;
    }

    if (pROM->bLoad && !romCopyLoad(pROM)) {
        return 0;
    }

    nOffsetROM = nOffsetROM & 0x07FFFFFF;
    pBuffer = (u8*)(((s32)anBuffer + 0x1F) & 0xFFFFFFE0);

    if (nOffsetROM + nSize > pROM->nSize && (nSize = pROM->nSize - nOffsetROM) < 0) {
        return 1;
    }

    if (pROM->eModeLoad == RLM_PART) {
        while (nSize != 0U) {
            pBlock = &pROM->aBlock[nOffsetROM / 0x2000];
            if (pBlock->nSize == 0) {
                return 0;
            }

            nOffsetBlock = nOffsetROM % 0x2000;
            if ((nSizeCopy = pBlock->nSize - nOffsetBlock) > nSize) {
                nSizeCopy = nSize;
            }

            if (pBlock->iCache >= 0) {
                pSource = &pROM->pCacheRAM[(pBlock->iCache * 0x2000)] + nOffsetBlock;
                if (!xlHeapCopy(pTarget, pSource, nSizeCopy)) {
                    return 0;
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
                        return 0;
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
        return 1;
    } else if (pROM->eModeLoad == RLM_FULL) {
        if (!xlHeapCopy(pTarget, (u8*)pROM->pBuffer + nOffsetROM, nSize)) {
            return 0;
        }
        return 1;
    }

    return 0;
}

s32 romUpdate(Rom* pROM) {
    s32 nStatus;

    if ((pROM->copy.bWait != 0) || (pROM->load.bWait != 0)) {
        if ((pROM->load.bDone != 0) && (pROM->load.nResult == pROM->load.nSizeRead)) {
            pROM->load.bDone = 0;
            if (!__romLoadBlock_Complete(pROM)) {
                return 0;
            }
        }

        nStatus = DVDGetCommandBlockStatus(&pROM->fileInfo.cb);
        if (nStatus != 1) {
            if (!simulatorDVDShowError(nStatus, pROM->load.anData, pROM->load.nSizeRead,
                                       pROM->offsetToRom + pROM->load.nOffset)) {
                return 0;
            }

            if ((nStatus == 0xB) || (nStatus == -1)) {
                DVDCancel(&pROM->fileInfo.cb);
                if (!simulatorDVDRead(&pROM->fileInfo, pROM->load.anData, pROM->load.nSizeRead,
                                      pROM->offsetToRom + pROM->load.nOffset, &__romLoadBlock_CompleteGCN)) {
                    return 0;
                }
            }
        }
    }

    if (!romLoadUpdate(pROM)) {
        return 0;
    }

    if (!romCopyUpdate(pROM)) {
        return 0;
    }

    return 1;
}

s32 romSetCacheSize(Rom* pROM, s32 nSize) {
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
        return 0;
    }

    pROM->pCacheRAM = (u8*)pROM->pBuffer;

    return 1;
}

inline void romOpen(Rom* pROM, char* szNameFile) {
    s32 var_r30 = 0;
    s32 bFlip;

    if ((pROM->acHeader[0] == 0x37) && (pROM->acHeader[1] == 0x80)) {
        var_r30 = 1;
    }

    if (var_r30 != 0) {
        bFlip = 1;
    } else {
        bFlip = 0;
    }

    pROM->bFlip = bFlip;
    simulatorDVDOpen(szNameFile, &pROM->fileInfo);
}

s32 romSetImage(Rom* pROM, char* szNameFile) {
    tXL_FILE* pFile;
    s32 iName;
    s32 nSize;

    for (iName = 0; (szNameFile[iName] != '\0') && (iName < 0x200); iName++) {
        pROM->acNameFile[iName] = szNameFile[iName];
    }
    pROM->acNameFile[iName] = '\0';

    if (xlFileGetSize(&nSize, pROM->acNameFile)) {
        pROM->nSize = (u32)(nSize - pROM->offsetToRom);
    } else {
        return 0;
    }

    if (!xlFileOpen(&pFile, XLFT_BINARY, szNameFile)) {
        return 0;
    }

    if (!xlFileSetPosition(pFile, pROM->offsetToRom)) {
        return 0;
    }

    if (!xlFileGet(pFile, pROM->acHeader, sizeof(pROM->acHeader))) {
        return 0;
    }

    if (!xlFileClose(&pFile)) {
        return 0;
    }

    romOpen(pROM, szNameFile);
    return 1;
}

s32 romGetImage(Rom* pROM, char* acNameFile) {
    if (pROM->acNameFile[0] == '\0') {
        return 0;
    }

    if (acNameFile != NULL) {
        s32 iName;

        for (iName = 0; pROM->acNameFile[iName] != '\0'; iName++) {
            acNameFile[iName] = pROM->acNameFile[iName];
        }
    }

    return 1;
}

s32 romEvent(Rom* pROM, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pROM->nSize = 0;
            pROM->nTick = 0;
            pROM->bLoad = 1;
            pROM->bFlip = 0;
            pROM->pHost = pArgument;
            pROM->acNameFile[0] = '\0';
            pROM->eModeLoad = RLM_NONE;
            pROM->pBuffer = NULL;
            pROM->offsetToRom = 0;
            pROM->anOffsetBlock = NULL;
            pROM->nCountOffsetBlocks = 0;
            pROM->copy.nSize = 0;
            pROM->copy.bWait = 0;
            pROM->load.bWait = 0;
            pROM->load.nOffset1 = 0;
            pROM->load.nOffset0 = 0;
            pROM->load.bDone = 0;
            pROM->nSizeCacheRAM = 0;
            pROM->nCountBlockRAM = 0;
            pROM->pCacheRAM = NULL;
            break;
        case 3:
            if ((pROM->pBuffer != NULL) && (pROM->pBuffer != pROM->pCacheRAM) && (!xlHeapFree(&pROM->pBuffer))) {
                return 0;
            }
            break;
        case 0x1002:
            switch (((CpuDevice*)pArgument)->nType) {
                case 0:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pROM->pHost), pArgument, (Put8Func)romPut8, (Put16Func)romPut16,
                                         (Put32Func)romPut32, (Put64Func)romPut64)) {
                        return 0;
                    }
                    if (!cpuSetDeviceGet(SYSTEM_CPU(pROM->pHost), pArgument, (Get8Func)romGet8, (Get16Func)romGet16,
                                         (Get32Func)romGet32, (Get64Func)romGet64)) {
                        return 0;
                    }
                    break;
                case 1:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pROM->pHost), pArgument, (Put8Func)romPutDebug8,
                                         (Put16Func)romPutDebug16, (Put32Func)romPutDebug32,
                                         (Put64Func)romPutDebug64)) {
                        return 0;
                    }
                    if (!cpuSetDeviceGet(SYSTEM_CPU(pROM->pHost), pArgument, (Get8Func)romGetDebug8,
                                         (Get16Func)romGetDebug16, (Get32Func)romGetDebug32,
                                         (Get64Func)romGetDebug64)) {
                        return 0;
                    }
                    break;
            }
            break;
        case 0:
        case 1:
        case 0x1003:
            break;
        default:
            return 0;
    }

    return 1;
}
