#include "cpu.h"
#include "rom.h"
#include "types.h"
#include "xlObject.h"

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

char D_800EDF28[] = "urazle.tpl";
char D_800EDF34[] = "urazlj.tpl";

char D_8013527C[5] = "CZLE";
char D_80135284[5] = "CZLJ";
char D_8013528C[8] = "zle.tpl";
char D_80135294[8] = "zlj.tpl";
char D_8013529C[1] = "";
char D_801352A0[5] = "NZSJ";
char D_801352A8[5] = "NZSE";

static int gbProgress;
static void* gpImageBack;
static int iImage;

const f32 D_80135FD0 = 1.0;
const f64 D_80135FD8 = 4503601774854144.0;
const f64 D_80135FE0 = 4503599627370496.0;
const f32 D_80135FE8 = 0.0f;
const f32 D_80135FEC = 640.0f;
const f32 D_80135FF0 = 480.0f;
const f32 D_80135FF4 = 479.0f;
const f32 D_80135FF8 = 639.0f;
const f32 D_80135FFC = 0.5f;
const f32 D_80136000 = 400.0f;

void __romLoadBlock_CompleteGCN(long nResult);

s32 romEvent(Rom* pROM, s32 nEvent, unknownDeviceStruct* pArgument) {
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
            switch (pArgument->unk) {
                case 0:
                    if (!cpuSetDevicePut(pROM->pHost->pDevice, pArgument, romPut8, romPut16, romPut32, romPut64)) {
                        return 0;
                    }
                    if (!cpuSetDeviceGet(pROM->pHost->pDevice, pArgument, romGet8, romGet16, romGet32, romGet64)) {
                        return 0;
                    }
                    break;
                case 1:
                    if (!cpuSetDevicePut(pROM->pHost->pDevice, pArgument, romPutDebug8, romPutDebug16, romPutDebug32, romPutDebug64)) {
                        return 0;
                    }
                    if (!cpuSetDeviceGet(pROM->pHost->pDevice, pArgument, romGetDebug8, romGetDebug16, romGetDebug32, romGetDebug64)) {
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

s32 romGetImage(Rom* pROM, char* acNameFile) {
    if (pROM->acNameFile[0] == '\x0') {
        return 0;
    }

    if (acNameFile != NULL) {
        s32 i;

        for (i = 0; pROM->acNameFile[i] != '\x0'; i++) {
            acNameFile[i] = pROM->acNameFile[i];
        }
    }

    return 1;
}

inline void romOpen(Rom* pROM, char *szNameFile) {
    s32 var_r30 = 0;
    int bFlip;

    if ((pROM->acHeader[0] == '\x37') && (pROM->acHeader[1] == 0x80)) {
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

s32 romSetImage(Rom* pROM, char *szNameFile) {
    tXL_FILE* file;
    s32 i;
    int size;

    for (i = 0; (szNameFile[i] != '\x0') && (i < 0x200); i++) {
        pROM->acNameFile[i] = szNameFile[i];
    }
    pROM->acNameFile[i] = '\x0';

    if (xlFileGetSize(&size, pROM->acNameFile)) {
        pROM->nSize = (u32)(size - pROM->offsetToRom);
    } else {
        return 0;
    }

    if (!xlFileOpen(&file, XLFT_BINARY, szNameFile)) {
        return 0;
    }

    if (!xlFileSetPosition(file, pROM->offsetToRom)) {
        return 0;
    }

    if (!xlFileGet(file, pROM->acHeader, sizeof(pROM->acHeader))) {
        return 0;
    }

    if (!xlFileClose(&file)) {
        return 0;
    }

    romOpen(pROM, szNameFile);
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

    pROM->pCacheRAM = (u8* ) pROM->pBuffer;

    return 1;
}

s32 romUpdate(Rom* pROM) {
    s32 cmdBlockStatus;

    if ((pROM->copy.bWait != 0) || (pROM->load.bWait != 0)) {
        if ((pROM->load.bDone != 0) && (pROM->load.nResult == pROM->load.nSizeRead)) {
            pROM->load.bDone = 0;
            if (!__romLoadBlock_Complete(pROM)) {
                return 0;
            }
        }

        cmdBlockStatus = DVDGetCommandBlockStatus(&pROM->fileInfo);
        if (cmdBlockStatus != 1) {
            if (!simulatorDVDShowError(cmdBlockStatus, pROM->load.anData, pROM->load.nSizeRead, pROM->offsetToRom + pROM->load.nOffset)) {
                return 0;
            }

            if ((cmdBlockStatus == 0xB) || (cmdBlockStatus == -1)) {
                DVDCancel(&pROM->fileInfo);
                if (!simulatorDVDRead(&pROM->fileInfo, pROM->load.anData, pROM->load.nSizeRead, pROM->offsetToRom + pROM->load.nOffset, &__romLoadBlock_CompleteGCN)) {
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

#pragma GLOBAL_ASM("asm/non_matchings/rom/romCopyImmediate.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romCopy.s")

static int romGetDebug64(Rom* pROM, u32 nAddress, s64* pData) {
    *pData = 0;
    return 1;
}

static int romGetDebug32(Rom* pROM, u32 nAddress, s32* pData) {
    *pData = 0;
    return 1;
}

static int romGetDebug16(Rom* pROM, u32 nAddress, s16* pData) {
    *pData = 0;
    return 1;
}

static int romGetDebug8(Rom* pROM, u32 nAddress, s8* pData) {
    *pData = 0;
    return 1;
}

static int romPutDebug64(Rom* pROM, u32 nAddress, s64* pData) { return 1; }
static int romPutDebug32(Rom* pROM, u32 nAddress, s32* pData) { return 1; }
static int romPutDebug16(Rom* pROM, u32 nAddress, s16* pData) { return 1; }
static int romPutDebug8(Rom* pROM, u32 nAddress, s8* pData) { return 1; }

static int romGet64(Rom* pROM, u32 nAddress, s64* pData) {
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

static int romGet32(Rom* pROM, u32 nAddress, s32* pData) {
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

static int romGet16(Rom* pROM, u32 nAddress, s16* pData) {
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

static int romGet8(Rom* pROM, u32 nAddress, s8* pData) {
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

static int romPut64(Rom* pROM, u32 nAddress, s64* pData) { return 1; }
static int romPut32(Rom* pROM, u32 nAddress, s32* pData) { return 1; }
static int romPut16(Rom* pROM, u32 nAddress, s16* pData) { return 1; }
static int romPut8(Rom* pROM, u32 nAddress, s8* pData) { return 1; }

int romTestCode(Rom* pROM, char* acCode) {
    int iCode;
    char acCodeCurrent[5];
    int iOffset = 0x3B;

    for (iCode = 0; iCode < 4; iCode++) {
        acCodeCurrent[iCode] = pROM->acHeader[iOffset + iCode];
    }
    acCodeCurrent[4] = '\0';

    for (iCode = 0; iCode < 4; iCode++) {
        if (acCode[iCode] != acCodeCurrent[iCode]) {
            return 0;
        }
    }
    return 1;
}

int romGetCode(Rom* pROM, char* acCode) {
    acCode[0] = pROM->acHeader[0x3B];
    acCode[1] = pROM->acHeader[0x3C];
    acCode[2] = pROM->acHeader[0x3D];
    acCode[3] = pROM->acHeader[0x3E];
    acCode[4] = '\0';
    return 1;
}

int romGetPC(Rom* pROM, u64* pnPC) {
    int nOffset;
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

#pragma GLOBAL_ASM("asm/non_matchings/rom/romLoadFullOrPart.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romCopyUpdate.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/__romCopyUpdate_Complete.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romLoadUpdate.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/__romLoadUpdate_Complete.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romCacheGame.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romCacheGame_ZELDA.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romLoadRange.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romLoadBlock.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/__romLoadBlock_CompleteGCN.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/__romLoadBlock_Complete.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romSetBlockCache.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romMakeFreeCache.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romFindOldestBlock.s")

#pragma GLOBAL_ASM("asm/non_matchings/rom/romFindFreeCache.s")
