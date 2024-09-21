#ifndef _DOLPHIN_OS_OSRTC_H_
#define _DOLPHIN_OS_OSRTC_H_

#include "dolphin/types.h"

bool WriteSram(void* buffer, u32 offset, u32 size);
void __OSInitSram(void);
bool __OSUnlockSram(bool commit);
bool __OSUnlockSramEx(bool commit);
bool __OSSyncSram(void);
u32 OSGetSoundMode(void);
void OSSetSoundMode(u32 mode);
u8 OSGetLanguage(void);
u16 OSGetWirelessID(s32 channel);
void OSSetWirelessID(s32 channel, u16 id);
u16 OSGetGbsMode(void);
void OSSetGbsMode(u16 mode);

#endif
