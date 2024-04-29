#ifndef _THPINFO_H
#define _THPINFO_H

#include "dolphin/types.h"

typedef struct THPFrameCompInfo {
    /* 0x0 */ u32 numComponents;
    /* 0x4 */ u8 frameComp[16];
} THPFrameCompInfo; // size = 0x14

typedef struct THPVideoInfo {
    /* 0x0 */ u32 xSize;
    /* 0x4 */ u32 ySize;
    /* 0x8 */ u32 videoType;
} THPVideoInfo; // size = 0xC

typedef struct THPAudioInfo {
    /* 0x0 */ u32 sndChannels;
    /* 0x4 */ u32 sndFrequency;
    /* 0x8 */ u32 sndNumSamples;
    /* 0xC */ u32 sndNumTracks;
} THPAudioInfo; // size = 0x10

#endif
