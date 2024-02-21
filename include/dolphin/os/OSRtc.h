#ifndef _DOLPHIN_OS_OSRTC_H_
#define _DOLPHIN_OS_OSRTC_H_

#include "dolphin/types.h"

#define OS_SOUND_MODE_MONO 0
#define OS_SOUND_MODE_STEREO 1

typedef struct SramControl {
    u8 sram[64];
    u32 offset;
    s32 enabled;
    s32 locked;
    s32 sync;
    void (*callback)(void);
} SramControl;

typedef struct OSSram {
    u16 checkSum;
    u16 checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    s8 displayOffsetH;
    u8 ntd;
    u8 language;
    u8 flags;
} OSSram;

typedef struct OSSramEx {
    u8 flashID[2][12];
    u32 wirelessKeyboardID;
    u16 wirelessPadID[4];
    u16 _padding0;
    u8 flashIDCheckSum[2];
    u8 _padding1[4];
} OSSramEx;

void __OSInitSram(void);
OSSram* __OSLockSram(void);
OSSramEx* __OSLockSramEx(void);
s32 __OSUnlockSram(s32 commit);
s32 __OSUnlockSramEx(s32 commit);
s32 __OSSyncSram(void);
u32 OSGetSoundMode(void);
void OSSetSoundMode(u32 mode);
u32 OSGetWirelessID(u32 chan);
void OSSetWirelessID(u32 chan, u16 id);

#endif
