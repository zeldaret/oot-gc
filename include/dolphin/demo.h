#ifndef _DOLPHIN_DEMOPUTS_H_
#define _DOLPHIN_DEMOPUTS_H_

#include "dolphin/gx.h"
#include "dolphin/types.h"

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
