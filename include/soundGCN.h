#ifndef _SOUNDGCN_H
#define _SOUNDGCN_H

#include "dolphin.h"

// __anon_0x20C8D
typedef enum SoundBeep {
    SOUND_BEEP_ACCEPT = 0,
    SOUND_BEEP_DECLINE = 1,
    SOUND_BEEP_SELECT = 2,
    SOUND_BEEP_COUNT = 3,
} SoundBeep;

//! TODO: Define this struct
// __anon_0x208BA
typedef struct Sound Sound;

s32 soundLoadBeep(Sound* pSound, SoundBeep iBeep, char* szNameFile);

#endif
