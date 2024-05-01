#ifndef _THPBUFFER_H
#define _THPBUFFER_H

#include "dolphin/types.h"

typedef struct THPTextureSet {
    /* 0x0 */ u8* yTexture;
    /* 0x4 */ u8* uTexture;
    /* 0x8 */ u8* vTexture;
    /* 0xC */ s32 frameNumber;
} THPTextureSet; // size = 0x10

typedef struct THPAudioBuffer {
    /* 0x0 */ s16* buffer;
    /* 0x4 */ s16* curPtr;
    /* 0x8 */ u32 validSample;
} THPAudioBuffer; // size = 0xC

typedef struct THPReadBuffer {
    /* 0x0 */ u8* ptr;
    /* 0x4 */ s32 frameNumber;
    /* 0x8 */ bool isValid;
} THPReadBuffer; // size = 0xC

#endif
