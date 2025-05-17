#include "dolphin/card.h"
#include "dolphin/hw_regs.h"

#include "dolphin/private/__card.h"
#include "dolphin/private/__os.h"

static void FormatCallback(s32 channel, s32 result) {
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[channel];
    if (result < 0) {
        goto error;
    }

    ++card->formatStep;
    if (card->formatStep < CARD_NUM_SYSTEM_BLOCK) {
        result = __CARDEraseSector(channel, (u32)card->sectorSize * card->formatStep, FormatCallback);
        if (0 <= result) {
            return;
        }
    } else if (card->formatStep < 2 * CARD_NUM_SYSTEM_BLOCK) {
        int step = card->formatStep - CARD_NUM_SYSTEM_BLOCK;
        result = __CARDWrite(channel, (u32)card->sectorSize * step, CARD_SYSTEM_BLOCK_SIZE,
                             (u8*)card->workArea + (CARD_SYSTEM_BLOCK_SIZE * step), FormatCallback);
        if (result >= 0) {
            return;
        }
    } else {
        card->currentDir = (CARDDir*)((u8*)card->workArea + 0x2000);
        memcpy(card->currentDir, (CARDDir*)((u8*)card->workArea + 0x4000), CARD_SYSTEM_BLOCK_SIZE);

        card->currentFat = (u16*)((u8*)card->workArea + 0x6000);
        memcpy(card->currentFat, (u16*)((u8*)card->workArea + 0x8000), CARD_SYSTEM_BLOCK_SIZE);
    }

error:
    callback = card->apiCallback;
    card->apiCallback = NULL;
    __CARDPutControlBlock(card, result);
    callback(channel, result);
}

s32 __CARDFormatRegionAsync(s32 channel, u16 encode, CARDCallback callback) {
    CARDControl* card;
    CARDID* id;
    CARDDir* dir;
    u16* fat;
    s16 i;
    s32 result;
    OSSram* sram;
    OSSramEx* sramEx;
    u16 viDTVStatus;
    OSTime time;
    OSTime rand;

    result = __CARDGetControlBlock(channel, &card);
    if (result < 0) {
        return result;
    }

    id = (CARDID*)card->workArea;
    memset(id, 0xFF, CARD_SYSTEM_BLOCK_SIZE);
    viDTVStatus = __VIRegs[55];

    id->encode = encode;

    sram = __OSLockSram();
    *(u32*)&id->serial[20] = sram->counterBias;
    *(u32*)&id->serial[24] = sram->language;
    __OSUnlockSram(false);

    rand = time = OSGetTime();

    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; i++) {
        rand = (rand * 1103515245 + 12345) >> 16;
        id->serial[i] = (u8)(sramEx->flashID[channel][i] + rand);
        rand = ((rand * 1103515245 + 12345) >> 16) & 0x7FFF;
    }
    __OSUnlockSramEx(false);

    *(u32*)&id->serial[28] = viDTVStatus;
    *(OSTime*)&id->serial[12] = time;

    id->deviceID = 0;
    id->size = card->size;
    __CARDCheckSum(id, sizeof(CARDID) - sizeof(u32), &id->checkSum, &id->checkSumInv);

    for (i = 0; i < 2; i++) {
        CARDDirCheck* check;

        dir = CARDGetDirectoryBlock(card, i);
        memset(dir, 0xFF, CARD_SYSTEM_BLOCK_SIZE);
        check = CARDGetDirCheck(dir);
        check->checkCode = i;
        __CARDCheckSum(dir, CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &check->checkSum, &check->checkSumInv);
    }
    for (i = 0; i < 2; i++) {
        fat = CARDGetFatBlock(card, i);
        memset(fat, 0x00, CARD_SYSTEM_BLOCK_SIZE);
        fat[CARD_FAT_CHECKCODE] = (u16)i;
        fat[CARD_FAT_FREEBLOCKS] = (u16)(card->cBlock - CARD_NUM_SYSTEM_BLOCK);
        fat[CARD_FAT_LASTSLOT] = CARD_NUM_SYSTEM_BLOCK - 1;
        __CARDCheckSum(&fat[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &fat[CARD_FAT_CHECKSUM],
                       &fat[CARD_FAT_CHECKSUMINV]);
    }

    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    DCStoreRange(card->workArea, CARD_WORKAREA_SIZE);

    card->formatStep = 0;
    result = __CARDEraseSector(channel, (u32)card->sectorSize * card->formatStep, FormatCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}

s32 CARDFormatAsync(s32 channel, CARDCallback callback) {
    return __CARDFormatRegionAsync(channel, __CARDGetFontEncode(), callback);
}
