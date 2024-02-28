#ifndef _AUDIO_H
#define _AUDIO_H

#include "dolphin.h"
#include "xlObject.h"

// __anon_0x753E7
typedef struct Audio {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 bEnable;
    /* 0x08 */ void* pHost;
    /* 0x0C */ s32 nControl;
    /* 0x10 */ s32 nAddress;
    /* 0x14 */ s32 nRateBit;
    /* 0x18 */ s32 nRateDAC;
    /* 0x1C */ s32 nStatus;
} Audio; // size = 0x20

s32 audioPut8(Audio* pAudio, u32 nAddress, s8* pData);
s32 audioPut16(Audio* pAudio, u32 nAddress, s16* pData);
s32 audioPut32(Audio* pAudio, u32 nAddress, s32* pData);
s32 audioPut64(Audio* pAudio, u32 nAddress, s64* pData);

s32 audioGet8(Audio* pAudio, u32 nAddress, s8* pData);
s32 audioGet16(Audio* pAudio, u32 nAddress, s16* pData);
s32 audioGet32(Audio* pAudio, u32 nAddress, s32* pData);
s32 audioGet64(Audio* pAudio, u32 nAddress, s64* pData);

s32 audioEnable(Audio* pAudio, s32 bEnable);
s32 audioEvent(Audio* pAudio, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassAudio;

#endif
