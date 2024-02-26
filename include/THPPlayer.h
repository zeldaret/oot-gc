#ifndef _THPPLAYER_H
#define _THPPLAYER_H

#include "dolphin.h"
#include "xlObject.h"

typedef struct __anon_0x10576 {
    /* 0x00 */ char magic[4];
    /* 0x04 */ u32 version;
    /* 0x08 */ u32 bufSize;
    /* 0x0C */ u32 audioMaxSamples;
    /* 0x10 */ f32 frameRate;
    /* 0x14 */ u32 numFrames;
    /* 0x18 */ u32 firstFrameSize;
    /* 0x1C */ u32 movieDataSize;
    /* 0x20 */ u32 compInfoDataOffsets;
    /* 0x24 */ u32 offsetDataOffsets;
    /* 0x28 */ u32 movieDataOffsets;
    /* 0x2C */ u32 finalFrameDataOffsets;
} __anon_0x10576; // size = 0x30

typedef struct __anon_0x107A2 {
    /* 0x0 */ u32 numComponents;
    /* 0x4 */ u8 frameComp[16];
} __anon_0x107A2; // size = 0x14

typedef struct __anon_0x1080A {
    /* 0x0 */ u32 xSize;
    /* 0x4 */ u32 ySize;
    /* 0x8 */ u32 videoType;
} __anon_0x1080A; // size = 0xC

typedef struct __anon_0x1088A {
    /* 0x0 */ u32 sndChannels;
    /* 0x4 */ u32 sndFrequency;
    /* 0x8 */ u32 sndNumSamples;
    /* 0xC */ u32 sndNumTracks;
} __anon_0x1088A; // size = 0x10

typedef struct __anon_0x10944 {
    /* 0x0 */ u8* ytexture;
    /* 0x4 */ u8* utexture;
    /* 0x8 */ u8* vtexture;
    /* 0xC */ s32 frameNumber;
} __anon_0x10944; // size = 0x10

typedef struct __anon_0x109FA {
    /* 0x0 */ s16* buffer;
    /* 0x4 */ s16* curPtr;
    /* 0x8 */ u32 validSample;
} __anon_0x109FA; // size = 0xC

typedef struct __anon_0x10A84 {
    /* 0x0 */ u8* ptr;
    /* 0x4 */ s32 frameNumber;
    /* 0x8 */ s32 isValid;
} __anon_0x10A84; // size = 0xC

typedef struct __anon_0x10B6F {
    /* 0x000 */ struct DVDFileInfo fileInfo;
    /* 0x03C */ __anon_0x10576 header;
    /* 0x06C */ __anon_0x107A2 compInfo;
    /* 0x080 */ __anon_0x1080A videoInfo;
    /* 0x08C */ __anon_0x1088A audioInfo;
    /* 0x09C */ void* thpWork;
    /* 0x0A0 */ s32 open;
    /* 0x0A4 */ u8 state;
    /* 0x0A5 */ u8 internalState;
    /* 0x0A6 */ u8 playFlag;
    /* 0x0A7 */ u8 audioExist;
    /* 0x0A8 */ s32 dvdError;
    /* 0x0AC */ s32 videoError;
    /* 0x0B0 */ s32 onMemory;
    /* 0x0B4 */ u8* movieData;
    /* 0x0B8 */ s32 initOffset;
    /* 0x0BC */ s32 initReadSize;
    /* 0x0C0 */ s32 initReadFrame;
    /* 0x0C8 */ s64 retraceCount;
    /* 0x0D0 */ s32 prevCount;
    /* 0x0D4 */ s32 curCount;
    /* 0x0D8 */ s32 videoAhead;
    /* 0x0DC */ f32 curVolume;
    /* 0x0E0 */ f32 targetVolume;
    /* 0x0E4 */ f32 deltaVolume;
    /* 0x0E8 */ s32 rampCount;
    /* 0x0EC */ s32 curAudioTrack;
    /* 0x0F0 */ s32 curVideoNumber;
    /* 0x0F4 */ s32 curAudioNumber;
    /* 0x0F8 */ __anon_0x10944* dispTextureSet;
    /* 0x0FC */ __anon_0x109FA* playAudioBuffer;
    /* 0x100 */ __anon_0x10A84 readBuffer[10];
    /* 0x178 */ __anon_0x10944 textureSet[3];
    /* 0x1A8 */ __anon_0x109FA audioBuffer[3];
} __anon_0x10B6F; // size = 0x1D0

extern char gpErrorMessageBuffer[20480];

#endif
