#ifndef _SOUNDGCN_H
#define _SOUNDGCN_H

#include "dolphin.h"
#include "emulator/xlObject.h"

// __anon_0x221A3
typedef enum SoundRamp {
    SR_NONE = -1,
    SR_DECREASE = 0,
    SR_INCREASE = 1,
} SoundRamp;

// __anon_0x20C8D
typedef enum SoundBeep {
    SOUND_BEEP_ACCEPT = 0,
    SOUND_BEEP_DECLINE = 1,
    SOUND_BEEP_SELECT = 2,
    SOUND_BEEP_COUNT = 3,
} SoundBeep;

typedef enum SoundPlayMode {
    SPM_NONE = -1,
    SPM_PLAY = 0,
    SPM_RAMPQUEUED = 1,
    SPM_RAMPPLAYED = 2,
} SoundPlayMode;

// __anon_0x208BA
typedef struct Sound {
    /* 0x00 */ void* pSrcData;
    /* 0x04 */ s32 nFrequency;
    /* 0x08 */ s32 nDacrate;
    /* 0x0C */ s32 nSndLen;
    /* 0x10 */ void* apBuffer[16];
    /* 0x50 */ s32 anSizeBuffer[16];
    /* 0x90 */ s32 nCountBeep;
    /* 0x94 */ s32 anSizeBeep[SOUND_BEEP_COUNT];
    /* 0xA0 */ void* apDataBeep[SOUND_BEEP_COUNT];
    /* 0xAC */ s32 iBufferPlay;
    /* 0xB0 */ s32 iBufferMake;
    /* 0xB4 */ volatile SoundPlayMode eMode;
    /* 0xB8 */ void* pBufferZero;
    /* 0xBC */ void* pBufferHold;
    /* 0xC0 */ void* pBufferRampUp;
    /* 0xC4 */ void* pBufferRampDown;
    /* 0xC8 */ s32 nSizePlay;
    /* 0xCC */ s32 nSizeZero;
    /* 0xD0 */ s32 nSizeHold;
    /* 0xD4 */ s32 nSizeRamp;
#if VERSION == MQ_J
    /* 0xD8 */ char pad[12];
#endif
} Sound; // size = 0xD8

bool soundWipeBuffers(Sound* pSound);
bool soundSetLength(Sound* pSound, s32 nSize);
bool soundSetDACRate(Sound* pSound, s32 nDacRate);
bool soundSetAddress(Sound* pSound, void* pData);
bool soundGetDMABuffer(Sound* pSound, u32* pnSize);
bool soundSetBufferSize(Sound* pSound, s32 nSize);
bool soundLoadBeep(Sound* pSound, SoundBeep iBeep, char* szNameFile);
bool soundPlayBeep(Sound* pSound, SoundBeep iBeep);
bool soundEvent(Sound* pSound, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassSound;

#endif
