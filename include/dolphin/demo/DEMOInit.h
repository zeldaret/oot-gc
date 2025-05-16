#ifndef _DOLPHIN_DEMO_DEMOINIT_H
#define _DOLPHIN_DEMO_DEMOINIT_H

#include "dolphin/gx.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void* DemoFrameBuffer1;
extern void* DemoFrameBuffer2;
extern void* DemoCurrentBuffer;

void DEMOInit(GXRenderModeObj* mode);
void DEMOBeforeRender(void);
void DEMODoneRender(void);
void DEMOSwapBuffers(void);
void DEMOSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void DEMOSetTevOp(GXTevStageID id, GXTevMode mode);
GXRenderModeObj* DEMOGetRenderModeObj(void);
u32 DEMOGetCurrentBuffer(void);
void DEMOSetGPHangMetric(u8 enable);
void DEMOEnableGPHangWorkaround(u32 timeoutFrames);
void DEMOReInit(GXRenderModeObj* mode);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_DEMOINIT_H_
