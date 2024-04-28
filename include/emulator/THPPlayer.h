#ifndef _THPPLAYER_H
#define _THPPLAYER_H

#include "dolphin.h"
#include "emulator/THPBuffer.h"
#include "emulator/THPFile.h"
#include "emulator/THPInfo.h"
#include "emulator/xlObject.h"

typedef struct THPPlayer {
    /* 0x000 */ DVDFileInfo fileInfo;
    /* 0x03C */ THPHeader header;
    /* 0x06C */ THPFrameCompInfo compInfo;
    /* 0x080 */ THPVideoInfo videoInfo;
    /* 0x08C */ THPAudioInfo audioInfo;
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
    /* 0x0F8 */ THPTextureSet* dispTextureSet;
    /* 0x0FC */ THPAudioBuffer* playAudioBuffer;
    /* 0x100 */ THPReadBuffer readBuffer[10];
    /* 0x178 */ THPTextureSet textureSet[3];
    /* 0x1A8 */ THPAudioBuffer audioBuffer[3];
} THPPlayer; // size = 0x1D0

s32 THPPlayerInit(s32 audioSystem);
void THPPlayerQuit(void);
s32 THPPlayerOpen(char* fileName, s32 onMemory);
s32 THPPlayerClose(void);
u32 THPPlayerCalcNeedMemory(void);
s32 THPPlayerSetBuffer(u8* buffer);
s32 THPPlayerPrepare(s32 frameNum, s32 playFlag, s32 audioTrack);
s32 THPPlayerPlay(void);
void THPPlayerStop(void);
s32 THPPlayerPause(void);
s32 THPPlayerSkip(void);
s32 THPPlayerDrawCurrentFrame(GXRenderModeObj* rmode, u32 x, u32 y, u32 polygonW, u32 polygonH);
s32 THPPlayerGetVideoInfo(THPVideoInfo* videoInfo);
s32 THPPlayerGetAudioInfo(THPAudioInfo* audioInfo);
f32 THPPlayerGetFrameRate(void);
u32 THPPlayerGetTotalFrame(void);
s32 THPPlayerGetState(void);
void THPPlayerDrawDone(void);
s32 THPPlayerSetVolume(s32 vol, s32 time);
s32 THPPlayerGetVolume(void);

extern THPPlayer ActivePlayer;

#endif
