#ifndef _VIDEO_H
#define _VIDEO_H

#include "dolphin.h"
#include "xlObject.h"

// __anon_0x75B37
typedef struct Video {
    /* 0x00 */ s32 nScan;
    /* 0x04 */ s32 bBlack;
    /* 0x08 */ s32 nBurst;
    /* 0x0C */ s32 nSizeX;
    /* 0x10 */ void* pHost;
    /* 0x14 */ s32 nStatus;
    /* 0x18 */ s32 nTiming;
    /* 0x1C */ s32 nAddress;
    /* 0x20 */ s32 nScanInterrupt;
    /* 0x24 */ s32 nScaleX;
    /* 0x28 */ s32 nScaleY;
    /* 0x2C */ s32 nStartH;
    /* 0x30 */ s32 nStartV;
    /* 0x34 */ s32 nSyncH;
    /* 0x38 */ s32 nSyncV;
    /* 0x3C */ s32 nSyncLeap;
} Video; // size = 0x40

s32 videoForceRetrace(Video* pVideo, s32);
s32 videoEvent(Video* pVideo, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassVideo;

#endif
