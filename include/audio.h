#ifndef _AUDIO_H
#define _AUDIO_H

#include <dolphin/types.h>

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

#endif
