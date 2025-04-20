#include "dolphin/card.h"
#include "dolphin/exi.h"
#include "dolphin/types.h"

#include "dolphin/private/__card.h"

#if IS_MQ
const char* __CARDVersion = "<< Dolphin SDK - CARD\trelease build: Sep  5 2002 05:35:20 (0x2301) >>";
#else
const char* __CARDVersion = "<< Dolphin SDK - CARD\trelease build: Apr 17 2003 12:34:19 (0x2301) >>";
#endif

CARDControl __CARDBlock[2];
DVDDiskID __CARDDiskNone;

static u16 __CARDEncode;

s32 __CARDReadStatus(s32 chan, u8* status);
s32 __CARDClearStatus(s32 chan);
void __CARDSetDiskID(const DVDDiskID* id);
static s32 Retry(s32 chan);
bool OnReset(bool f);

static OSResetFunctionInfo ResetFunctionInfo = {OnReset, 127};

// bit manip stuff for __CARDReadSegment, __CARDWritePage, __CARDEraseSector
#define AD1(x) ((u8)(((x) >> 17) & 0x7F))
#define AD1EX(x) ((u8)(AD1(x) | 0x80));
#define AD2(x) ((u8)(((x) >> 9) & 0xFF))
#define AD3(x) ((u8)(((x) >> 7) & 0x03))
#define BA(x) ((u8)((x) & 0x7F))

void __CARDDefaultApiCallback(s32 channel, s32 result) {}

void __CARDSyncCallback(s32 channel, s32 result) { OSWakeupThread(&__CARDBlock[channel].threadQueue); }

void __CARDExtHandler(s32 channel, OSContext* context) {
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[channel];
    if (card->attached) {
        card->attached = false;
        EXISetExiCallback(channel, NULL);
        OSCancelAlarm(&card->alarm);
        callback = card->exiCallback;

        if (callback) {
            card->exiCallback = NULL;
            callback(channel, CARD_RESULT_NOCARD);
        }

        if (card->result != CARD_RESULT_BUSY) {
            card->result = CARD_RESULT_NOCARD;
        }

        callback = card->extCallback;
        if (callback && CARD_MAX_MOUNT_STEP <= card->mountStep) {
            card->extCallback = NULL;
            callback(channel, CARD_RESULT_NOCARD);
        }
    }
}

void __CARDExiHandler(s32 channel, OSContext* context) {

    CARDControl* card;
    CARDCallback callback;
    u8 status;
    s32 result;

    card = &__CARDBlock[channel];

    OSCancelAlarm(&card->alarm);

    if (!card->attached) {
        return;
    }

    if (!EXILock(channel, 0, 0)) {
        result = CARD_RESULT_FATAL_ERROR;
        goto fatal;
    }

    if ((result = __CARDReadStatus(channel, &status)) < 0 || (result = __CARDClearStatus(channel)) < 0) {
        goto error;
    }

    if ((result = (status & 0x18) ? CARD_RESULT_IOERROR : CARD_RESULT_READY) == CARD_RESULT_IOERROR &&
        --card->retry > 0) {
        result = Retry(channel);
        if (result >= 0) {
            return;
        }
        goto fatal;
    }

error:
    EXIUnlock(channel);

fatal:
    callback = card->exiCallback;
    if (callback) {
        card->exiCallback = NULL;
        callback(channel, result);
    }
}

void __CARDTxHandler(s32 channel, OSContext* context) {
    CARDControl* card;
    CARDCallback callback;
    bool err;

    card = &__CARDBlock[channel];
    err = !EXIDeselect(channel);
    EXIUnlock(channel);
    callback = card->txCallback;
    if (callback) {
        card->txCallback = NULL;
        callback(channel, (!err && EXIProbe(channel)) ? CARD_RESULT_READY : CARD_RESULT_NOCARD);
    }
}

void __CARDUnlockedHandler(s32 channel, OSContext* context) {
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[channel];
    callback = card->unlockCallback;
    if (callback) {
        card->unlockCallback = NULL;
        callback(channel, EXIProbe(channel) ? CARD_RESULT_UNLOCKED : CARD_RESULT_NOCARD);
    }
}

s32 __CARDEnableInterrupt(s32 channel, bool enable) {
    bool err;
    u32 cmd;

    if (!EXISelect(channel, 0, 4)) {
        return CARD_RESULT_NOCARD;
    }

    cmd = enable ? 0x81010000 : 0x81000000;
    err = false;
    err |= !EXIImm(channel, &cmd, 2, 1, NULL);
    err |= !EXISync(channel);
    err |= !EXIDeselect(channel);
    return err ? CARD_RESULT_NOCARD : CARD_RESULT_READY;
}

s32 __CARDReadStatus(s32 channel, u8* status) {
    bool err;
    u32 cmd;

    if (!EXISelect(channel, 0, 4)) {
        return CARD_RESULT_NOCARD;
    }

    cmd = 0x83000000;
    err = false;
    err |= !EXIImm(channel, &cmd, 2, 1, NULL);
    err |= !EXISync(channel);
    err |= !EXIImm(channel, status, 1, 0, NULL);
    err |= !EXISync(channel);
    err |= !EXIDeselect(channel);
    return err ? CARD_RESULT_NOCARD : CARD_RESULT_READY;
}

s32 __CARDClearStatus(s32 channel) {
    bool err;
    u32 cmd;

    if (!EXISelect(channel, 0, 4)) {
        return CARD_RESULT_NOCARD;
    }

    cmd = 0x89000000;
    err = false;
    err |= !EXIImm(channel, &cmd, 1, 1, NULL);
    err |= !EXISync(channel);
    err |= !EXIDeselect(channel);

    return err ? CARD_RESULT_NOCARD : CARD_RESULT_READY;
}

void TimeoutHandler(OSAlarm* alarm, OSContext* context) {
    s32 channel;
    CARDControl* card;
    CARDCallback callback;
    for (channel = 0; channel < 2; channel++) {
        card = &__CARDBlock[channel];
        if (alarm == &card->alarm) {
            break;
        }
    }

    if (!card->attached) {
        return;
    }

    EXISetExiCallback(channel, NULL);
    callback = card->exiCallback;
    if (callback) {
        card->exiCallback = NULL;
        callback(channel, CARD_RESULT_IOERROR);
    }
}

inline void SetupTimeoutAlarm(CARDControl* card) {
    OSCancelAlarm(&card->alarm);
    switch (card->cmd[0]) {
        case 0xF2:
            OSSetAlarm(&card->alarm, OSMillisecondsToTicks(100), TimeoutHandler);
            break;
        case 0xF3:
            break;
        case 0xF4:
        case 0xF1:
            OSSetAlarm(&card->alarm, OSSecondsToTicks((OSTime)2) * (card->sectorSize / 0x2000), TimeoutHandler);
            break;
    }
}

s32 Retry(s32 channel) {
    CARDControl* card;
    card = &__CARDBlock[channel];

    if (!EXISelect(channel, 0, 4)) {
        EXIUnlock(channel);
        return CARD_RESULT_NOCARD;
    }

    SetupTimeoutAlarm(card);

    if (!EXIImmEx(channel, card->cmd, card->cmdlen, 1)) {
        EXIDeselect(channel);
        EXIUnlock(channel);
        return CARD_RESULT_NOCARD;
    }

    if (card->cmd[0] == 0x52 && !EXIImmEx(channel, (u8*)card->workArea + sizeof(CARDID), card->latency, 1)) {
        EXIDeselect(channel);
        EXIUnlock(channel);
        return CARD_RESULT_NOCARD;
    }

    if (card->mode == 0xFFFFFFFF) {
        EXIDeselect(channel);
        EXIUnlock(channel);
        return CARD_RESULT_READY;
    }

    if (!EXIDma(channel, card->buffer, (s32)((card->cmd[0] == 0x52) ? 512 : 128), card->mode, __CARDTxHandler)) {
        EXIDeselect(channel);
        EXIUnlock(channel);
        return CARD_RESULT_NOCARD;
    }

    return CARD_RESULT_READY;
}

void UnlockedCallback(s32 channel, s32 result) {
    CARDCallback callback;
    CARDControl* card;

    card = &__CARDBlock[channel];
    if (result >= 0) {
        card->unlockCallback = UnlockedCallback;
        if (!EXILock(channel, 0, __CARDUnlockedHandler)) {
            result = CARD_RESULT_READY;
        } else {
            card->unlockCallback = NULL;
            result = Retry(channel);
        }
    }

    if (result < 0) {
        switch (card->cmd[0]) {
            case 0x52:
                callback = card->txCallback;
                if (callback) {
                    card->txCallback = NULL;
                    callback(channel, result);
                }

                break;
            case 0xF2:
            case 0xF4:
            case 0xF1:
                callback = card->exiCallback;
                if (callback) {
                    card->exiCallback = NULL;
                    callback(channel, result);
                }
                break;
        }
    }
}

s32 __CARDStart(s32 channel, CARDCallback txCallback, CARDCallback exiCallback) {
    bool enabled;
    CARDControl* card;
    s32 result;

    enabled = OSDisableInterrupts();

    card = &__CARDBlock[channel];
    if (!card->attached) {
        result = CARD_RESULT_NOCARD;
    } else {

        if (txCallback) {
            card->txCallback = txCallback;
        }
        if (exiCallback) {
            card->exiCallback = exiCallback;
        }
        card->unlockCallback = UnlockedCallback;
        if (!EXILock(channel, 0, __CARDUnlockedHandler)) {
            result = CARD_RESULT_BUSY;
        } else {
            card->unlockCallback = NULL;

            if (!EXISelect(channel, 0, 4)) {
                EXIUnlock(channel);
                result = CARD_RESULT_NOCARD;
            } else {
                SetupTimeoutAlarm(card);
                result = CARD_RESULT_READY;
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return result;
}

s32 __CARDReadSegment(s32 channel, CARDCallback callback) {
    CARDControl* card;
    s32 result;

    card = &__CARDBlock[channel];
    card->cmd[0] = 0x52;
    card->cmd[1] = AD1(card->addr);
    card->cmd[2] = AD2(card->addr);
    card->cmd[3] = AD3(card->addr);
    card->cmd[4] = BA(card->addr);
    card->cmdlen = 5;
    card->mode = 0;
    card->retry = 0;

    result = __CARDStart(channel, callback, 0);
    if (result == CARD_RESULT_BUSY) {
        result = CARD_RESULT_READY;
    } else if (result >= 0) {
        if (!EXIImmEx(channel, card->cmd, card->cmdlen, 1) ||
            !EXIImmEx(channel, (u8*)card->workArea + sizeof(CARDID), card->latency,
                      1) || // XXX use DMA if possible
            !EXIDma(channel, card->buffer, 512, card->mode, __CARDTxHandler)) {
            card->txCallback = 0;
            EXIDeselect(channel);
            EXIUnlock(channel);
            result = CARD_RESULT_NOCARD;
        } else {
            result = CARD_RESULT_READY;
        }
    }
    return result;
}

s32 __CARDWritePage(s32 channel, CARDCallback callback) {
    CARDControl* card;
    s32 result;

    card = &__CARDBlock[channel];
    card->cmd[0] = 0xF2;
    card->cmd[1] = AD1(card->addr);
    card->cmd[2] = AD2(card->addr);
    card->cmd[3] = AD3(card->addr);
    card->cmd[4] = BA(card->addr);
    card->cmdlen = 5;
    card->mode = 1;
    card->retry = 3;

    result = __CARDStart(channel, NULL, callback);
    if (result == CARD_RESULT_BUSY) {
        result = CARD_RESULT_READY;
    } else if (result >= 0) {
        if (!EXIImmEx(channel, card->cmd, card->cmdlen, 1) ||
            !EXIDma(channel, card->buffer, 128, card->mode, __CARDTxHandler)) {
            card->exiCallback = NULL;
            EXIDeselect(channel);
            EXIUnlock(channel);
            result = CARD_RESULT_NOCARD;
        } else {
            result = CARD_RESULT_READY;
        }
    }

    return result;
}

s32 __CARDEraseSector(s32 channel, u32 addr, CARDCallback callback) {
    CARDControl* card;
    s32 result;

    card = &__CARDBlock[channel];
    card->cmd[0] = 0xF1;
    card->cmd[1] = AD1(addr);
    card->cmd[2] = AD2(addr);
    card->cmdlen = 3;
    card->mode = -1;
    card->retry = 3;

    result = __CARDStart(channel, NULL, callback);

    if (result == CARD_RESULT_BUSY) {
        result = CARD_RESULT_READY;
    } else if (result >= 0) {
        if (!EXIImmEx(channel, card->cmd, card->cmdlen, 1)) {
            card->exiCallback = NULL;
            result = CARD_RESULT_NOCARD;
        } else {
            result = CARD_RESULT_READY;
        }

        EXIDeselect(channel);
        EXIUnlock(channel);
    }
    return result;
}

void CARDInit() {
    s32 channel;

    if (__CARDBlock[0].diskID && __CARDBlock[1].diskID) {
        return;
    }

    __CARDEncode = OSGetFontEncode();

    OSRegisterVersion(__CARDVersion);

    DSPInit();
    OSInitAlarm();

    for (channel = 0; channel < 2; channel++) {
        CARDControl* card = &__CARDBlock[channel];

        card->result = CARD_RESULT_NOCARD;
        OSInitThreadQueue(&card->threadQueue);
        OSCreateAlarm(&card->alarm);
    }

    __CARDSetDiskID((DVDDiskID*)OSPhysicalToCached(0x0));

    OSRegisterResetFunction(&ResetFunctionInfo);
}

u16 __CARDGetFontEncode() { return __CARDEncode; }

void __CARDSetDiskID(const DVDDiskID* diskID) {
    __CARDBlock[0].diskID = diskID ? diskID : &__CARDDiskNone;
    __CARDBlock[1].diskID = diskID ? diskID : &__CARDDiskNone;
}

s32 __CARDGetControlBlock(s32 channel, CARDControl** card) {
    bool enabled;
    s32 result;
    CARDControl* reqCard;

    reqCard = &__CARDBlock[channel];
    if (channel < 0 || channel >= 2 || reqCard->diskID == NULL) {
        return CARD_RESULT_FATAL_ERROR;
    }

    enabled = OSDisableInterrupts();
    if (!reqCard->attached) {
        result = CARD_RESULT_NOCARD;
    } else if (reqCard->result == CARD_RESULT_BUSY) {
        result = CARD_RESULT_BUSY;
    } else {
        reqCard->result = CARD_RESULT_BUSY;
        result = CARD_RESULT_READY;
        reqCard->apiCallback = NULL;
        *card = reqCard;
    }
    OSRestoreInterrupts(enabled);
    return result;
}

s32 __CARDPutControlBlock(CARDControl* card, s32 result) {
    bool enabled;

    enabled = OSDisableInterrupts();
    if (card->attached) {
        card->result = result;
    } else if (card->result == CARD_RESULT_BUSY) {
        card->result = result;
    }
    OSRestoreInterrupts(enabled);
    return result;
}

s32 CARDGetResultCode(s32 channel) {
    CARDControl* card;

    if (channel < 0 || channel >= 2) {
        return CARD_RESULT_FATAL_ERROR;
    }

    card = &__CARDBlock[channel];
    return card->result;
}

s32 CARDFreeBlocks(s32 channel, s32* byteNotUsed, s32* filesNotUsed) {
    CARDControl* card;
    s32 result;
    u16* fat;
    CARDDir* dir;
    CARDDir* ent;
    u16 fileNo;

    result = __CARDGetControlBlock(channel, &card);
    if (result < 0) {
        return result;
    }

    fat = __CARDGetFatBlock(card);
    dir = __CARDGetDirBlock(card);
    if (fat == NULL || dir == NULL) {
        return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
    }

    if (byteNotUsed) {
        *byteNotUsed = (s32)(card->sectorSize * fat[CARD_FAT_FREEBLOCKS]);
    }

    if (filesNotUsed) {
        *filesNotUsed = 0;
        for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
            ent = &dir[fileNo];
            if (ent->fileName[0] == 0xFF) {
                ++*filesNotUsed;
            }
        }
    }

    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

s32 __CARDSync(s32 channel) {
    CARDControl* card;
    s32 result;
    bool enabled;

    card = &__CARDBlock[channel];
    enabled = OSDisableInterrupts();

    while ((result = CARDGetResultCode(channel)) == CARD_RESULT_BUSY) {
        OSSleepThread(&card->threadQueue);
    }

    OSRestoreInterrupts(enabled);
    return result;
}

bool OnReset(bool f) {
    if (!f) {
        if (CARDUnmount(0) == CARD_RESULT_BUSY || CARDUnmount(1) == CARD_RESULT_BUSY) {
            return false;
        }
    }

    return true;
}
