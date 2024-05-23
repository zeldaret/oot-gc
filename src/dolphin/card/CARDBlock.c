#include "dolphin/card.h"

void WriteCallback(s32 channel, s32 result);
void EraseCallback(s32 channel, s32 result);
s32 __CARDUpdateFatBlock(s32 channel, u16* fat, CARDCallback callback);

u16* __CARDGetFatBlock(CARDControl* card) { return card->currentFat; }

void WriteCallback(s32 channel, s32 result) {
    CARDControl* card;
    CARDCallback callback;
    u16* fat;
    u16* fatBack;

    card = &__CARDBlock[channel];

    if (result >= 0) {
        fat = (u16*)((u8*)card->workArea + 0x6000);
        fatBack = (u16*)((u8*)card->workArea + 0x8000);

        if (card->currentFat == fat) {
            card->currentFat = fatBack;
            memcpy(fatBack, fat, 0x2000);
        } else {
            card->currentFat = fat;
            memcpy(fat, fatBack, 0x2000);
        }
    }

    if (card->apiCallback == NULL) {
        __CARDPutControlBlock(card, result);
    }

    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = NULL;
        callback(channel, result);
    }
}

void EraseCallback(s32 channel, s32 result) {
    CARDControl* card;
    CARDCallback callback;
    u32 temp[2];
    u16* fat;
    u32 addr;

    card = &__CARDBlock[channel];
    if (result < 0) {
        goto error;
    }

    fat = __CARDGetFatBlock(card);
    addr = ((u32)fat - (u32)card->workArea) / CARD_SYSTEM_BLOCK_SIZE * card->sectorSize;
    result = __CARDWrite(channel, addr, CARD_SYSTEM_BLOCK_SIZE, fat, WriteCallback);
    if (result < 0) {
        goto error;
    }

    return;

error:
    if (card->apiCallback == NULL) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = NULL;
        callback(channel, result);
    }
}

s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback) {
    CARDControl* card;
    u16* fat;
    u16 iBlock;
    u16 startBlock;
    u16 prevBlock;
    u16 count;

    card = &__CARDBlock[chan];
    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    fat = __CARDGetFatBlock(card);
    if (fat[CARD_FAT_FREEBLOCKS] < cBlock) {
        return CARD_RESULT_INSSPACE;
    }

    fat[CARD_FAT_FREEBLOCKS] -= cBlock;
    startBlock = 0xFFFF;
    iBlock = fat[CARD_FAT_LASTSLOT];
    count = 0;
    while (0 < cBlock) {
        if (card->cBlock - 5 < ++count) {
            return CARD_RESULT_BROKEN;
        }

        iBlock++;
        if (!CARDIsValidBlockNo(card, iBlock)) {
            iBlock = 5;
        }

        if (((u16*)fat)[iBlock] == 0x0000u) {
            if (startBlock == 0xFFFF) {
                startBlock = iBlock;
            } else {
                ((u16*)fat)[prevBlock] = iBlock;
            }
            prevBlock = iBlock;
            ((u16*)fat)[iBlock] = 0xFFFF;
            --cBlock;
        }
    }
    fat[CARD_FAT_LASTSLOT] = iBlock;
    card->startBlock = startBlock;

    return __CARDUpdateFatBlock(chan, fat, callback);
}

s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback) {
    CARDControl* card;
    u16* fat;
    u16 nextBlock;

    card = card = &__CARDBlock[chan];
    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    fat = __CARDGetFatBlock(card);
    while (nBlock != 0xFFFF) {
        if (!CARDIsValidBlockNo(card, nBlock)) {
            return CARD_RESULT_BROKEN;
        }

        nextBlock = fat[nBlock];
        fat[nBlock] = 0;
        nBlock = nextBlock;
        ++fat[CARD_FAT_FREEBLOCKS];
    }

    return __CARDUpdateFatBlock(chan, fat, callback);
}

s32 __CARDUpdateFatBlock(s32 channel, u16* fat, CARDCallback callback) {
    CARDControl* card;

    card = &__CARDBlock[channel];
    ++fat[CARD_FAT_CHECKCODE];
    __CARDCheckSum(&fat[CARD_FAT_CHECKCODE], 0x1FFC, &fat[CARD_FAT_CHECKSUM], &fat[CARD_FAT_CHECKSUMINV]);
    DCStoreRange(fat, 0x2000);
    card->eraseCallback = callback;

    return __CARDEraseSector(channel, (((u32)fat - (u32)card->workArea) / CARD_SYSTEM_BLOCK_SIZE) * card->sectorSize,
                             EraseCallback);
}
