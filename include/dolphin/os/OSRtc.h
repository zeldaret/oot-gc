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

bool WriteSram(void* buffer, u32 offset, u32 size);
void __OSInitSram();
OSSram* __OSLockSram();
OSSramEx* __OSLockSramEx();
bool __OSUnlockSram(bool commit);
bool __OSUnlockSramEx(bool commit);
bool __OSSyncSram();
u32 OSGetSoundMode();
void OSSetSoundMode(u32 mode);
u16 OSGetWirelessID(s32 channel);
void OSSetWirelessID(s32 channel, u16 id);
u16 OSGetGbsMode();
void OSSetGbsMode(u16 mode);

#endif
