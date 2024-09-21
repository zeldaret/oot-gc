#include "dolphin/OSRtcPriv.h"
#include "dolphin/exi.h"
#include "dolphin/os.h"
#include "macros.h"

#define RTC_CMD_READ 0x20000000
#define RTC_CMD_WRITE 0xA0000000

#define RTC_SRAM_ADDR 0x00000100
#define RTC_SRAM_SIZE 64

#define RTC_CHAN 0
#define RTC_DEV 1
#define RTC_FREQ 3 // EXI_FREQ_8M

typedef struct SramControlBlock {
    u8 sram[RTC_SRAM_SIZE];
    u32 offset;
    bool enabled;
    bool locked;
    bool sync;
    void (*callback)(void);
} SramControlBlock;

static SramControlBlock Scb ATTRIBUTE_ALIGN(32);

#if IS_CE
u16 OSGetGbsMode(void);
void OSSetGbsMode(u16 mode);
#endif

static inline bool ReadSram(void* buffer) {
    bool err;
    u32 cmd;

    DCInvalidateRange(buffer, RTC_SRAM_SIZE);

    if (!EXILock(RTC_CHAN, RTC_DEV, 0)) {
        return false;
    }
    if (!EXISelect(RTC_CHAN, RTC_DEV, RTC_FREQ)) {
        EXIUnlock(RTC_CHAN);
        return false;
    }

    cmd = RTC_CMD_READ | RTC_SRAM_ADDR;
    err = false;
    err |= !EXIImm(RTC_CHAN, &cmd, 4, 1, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIDma(RTC_CHAN, buffer, RTC_SRAM_SIZE, 0, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIDeselect(RTC_CHAN);
    EXIUnlock(RTC_CHAN);

    return !err;
}

bool WriteSram(void* buffer, u32 offset, u32 size);
static void WriteSramCallback(s32 chan, OSContext* context) {
    Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, RTC_SRAM_SIZE - Scb.offset);
    if (Scb.sync) {
        Scb.offset = RTC_SRAM_SIZE;
    }
}

bool WriteSram(void* buffer, u32 offset, u32 size) {
    bool err;
    u32 cmd;

    if (!EXILock(RTC_CHAN, RTC_DEV, WriteSramCallback)) {
        return false;
    }
    if (!EXISelect(RTC_CHAN, RTC_DEV, RTC_FREQ)) {
        EXIUnlock(RTC_CHAN);
        return false;
    }

    offset <<= 6;
    cmd = RTC_CMD_WRITE | (RTC_SRAM_ADDR + offset);
    err = false;
    err |= !EXIImm(RTC_CHAN, &cmd, 4, 1, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIImmEx(RTC_CHAN, buffer, (s32)size, 1);
    err |= !EXIDeselect(RTC_CHAN);
    EXIUnlock(RTC_CHAN);

    return !err;
}

void __OSInitSram(void) {
    Scb.locked = Scb.enabled = false;
    Scb.sync = ReadSram(Scb.sram);
    Scb.offset = RTC_SRAM_SIZE;
#if IS_CE
    OSSetGbsMode(OSGetGbsMode());
#endif
}

static inline void* LockSram(u32 offset) {
    bool enabled;
    enabled = OSDisableInterrupts();

    if (Scb.locked != false) {
        OSRestoreInterrupts(enabled);
        return NULL;
    }

    Scb.enabled = enabled;
    Scb.locked = true;

    return Scb.sram + offset;
}

OSSram* __OSLockSram(void) { return LockSram(0); }

OSSramEx* __OSLockSramEx(void) { return LockSram(sizeof(OSSram)); }

static bool UnlockSram(bool commit, u32 offset) {
    u16* p;

    if (commit) {
        if (offset == 0) {
            OSSram* sram = (OSSram*)Scb.sram;

            if (2u < (sram->flags & 3)) {
                sram->flags &= ~3;
            }

            sram->checkSum = sram->checkSumInv = 0;
            for (p = (u16*)&sram->counterBias; p < (u16*)(Scb.sram + sizeof(OSSram)); p++) {
                sram->checkSum += *p;
                sram->checkSumInv += ~*p;
            }
        }

        if (offset < Scb.offset) {
            Scb.offset = offset;
        }

#if IS_CE
        if (Scb.offset <= 20) {
            // this seems to work? esp. since we have GbsMode functions when prime doesn't
            // wacky tho
            OSSramEx* sramEx = (OSSramEx*)(&Scb.sram[20]);
            if ((u32)(sramEx->gbs & 0x7C00) == 0x5000 || (u32)(sramEx->gbs & 0xC0) == 0xC0) {
                sramEx->gbs = 0;
            }
        }
#endif

        Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, RTC_SRAM_SIZE - Scb.offset);
        if (Scb.sync) {
            Scb.offset = RTC_SRAM_SIZE;
        }
    }
    Scb.locked = false;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

bool __OSUnlockSram(bool commit) { return UnlockSram(commit, 0); }

bool __OSUnlockSramEx(bool commit) { return UnlockSram(commit, sizeof(OSSram)); }

bool __OSSyncSram(void) { return Scb.sync; }

static inline OSSram* __OSLockSramHACK(void) { return LockSram(0); }

u32 OSGetSoundMode(void) {
    OSSram* sram;
    u32 mode;

    sram = __OSLockSramHACK();
    mode = (sram->flags & 0x4) ? OS_SOUND_MODE_STEREO : OS_SOUND_MODE_MONO;
    __OSUnlockSram(false);
    return mode;
}

void OSSetSoundMode(u32 mode) {
    OSSram* sram;
    mode <<= 2;
    mode &= 4;

    sram = __OSLockSramHACK();
    if (mode == (sram->flags & 4)) {
        __OSUnlockSram(false);
        return;
    }

    sram->flags &= ~4;
    sram->flags |= mode;
    __OSUnlockSram(true);
}

#if IS_EU
u8 OSGetLanguage(void) {
    OSSram* sram = __OSLockSram();
    u8 language = sram->language;

    __OSUnlockSram(0);
    return language;
}
#endif

u16 OSGetWirelessID(s32 channel) {
    OSSramEx* sram;
    u16 id;

    sram = __OSLockSramEx();
    id = sram->wirelessPadID[channel];
    __OSUnlockSramEx(false);
    return id;
}

void OSSetWirelessID(s32 channel, u16 id) {
    OSSramEx* sram;

    sram = __OSLockSramEx();
    if (sram->wirelessPadID[channel] != id) {
        sram->wirelessPadID[channel] = id;
        __OSUnlockSramEx(true);
        return;
    }

    __OSUnlockSramEx(false);
}

#if IS_CE
u16 OSGetGbsMode(void) {
    OSSramEx* sram;
    u16 id;

    sram = __OSLockSramEx();
    id = sram->gbs;
    __OSUnlockSramEx(false);
    return id;
}

void OSSetGbsMode(u16 mode) {
    OSSramEx* sram;

    // same odd code as in UnlockSram?
    if ((u32)(mode & 0x7C00) == 0x5000 || (u32)(mode & 0xC0) == 0xC0) {
        mode = 0;
    }

    sram = __OSLockSramEx();
    if (mode == sram->gbs) {
        __OSUnlockSramEx(false);
        return;
    }

    sram->gbs = mode;
    __OSUnlockSramEx(true);
}
#endif
