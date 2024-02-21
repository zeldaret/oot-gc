#ifndef _DOLPHIN_DEMOPUTS_H_
#define _DOLPHIN_DEMOPUTS_H_

#include "dolphin/gx.h"
#include "dolphin/pad.h"
#include "dolphin/types.h"

typedef struct __anon_0xAD2F {
    /* 0x00 */ PADStatus pst;
    /* 0x0C */ u16 buttonDown;
    /* 0x0E */ u16 buttonUp;
    /* 0x10 */ u16 dirs;
    /* 0x12 */ u16 dirsNew;
    /* 0x14 */ u16 dirsReleased;
    /* 0x16 */ s16 stickDeltaX;
    /* 0x18 */ s16 stickDeltaY;
    /* 0x1A */ s16 substickDeltaX;
    /* 0x1C */ s16 substickDeltaY;
} __anon_0xAD2F; // size = 0x1E

extern void* DemoCurrentBuffer;
extern void* DemoFrameBuffer2;
extern void* DemoFrameBuffer1;

extern __anon_0xAD2F DemoPad[4];
extern u8 DemoStatEnable;

void DEMOInit(GXRenderModeObj* mode);
void DEMOBeforeRender(void);
void DEMODoneRender(void);
void DEMOSwapBuffers(void);
GXRenderModeObj* DEMOGetRenderModeObj(void);
void DEMOReInit(GXRenderModeObj* mode);
void DEMOInitCaption(s32, s32, s32);
void DEMOPuts(s16, s16, s16, char*);
void DEMOPrintf(s16, s16, s16, char*, ...);
void DEMOPadRead(void);
void DEMOPadInit(void);
void DEMOUpdateStats(s32);
void DEMOPrintStats(void);

#endif
