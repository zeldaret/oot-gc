#ifndef _DOLPHIN_GX_GXFIFO_H_
#define _DOLPHIN_GX_GXFIFO_H_

#include "dolphin/gx/GXEnum.h"

typedef void (*GXBreakPtCallback)(void);

typedef struct {
    u8 pad[128];
} GXFifoObj;

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size);
void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr);
GXFifoObj* GXGetCPUFifo(void);
GXFifoObj* GXGetGPFifo(void);
void GXSetCPUFifo(GXFifoObj* fifo);
void GXSetGPFifo(GXFifoObj* fifo);
void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle, GXBool* brkpt);
void GXInitFifoLimits(GXFifoObj* fifo, u32 hiWaterMark, u32 loWaterMark);
void* GXGetFifoBase(const GXFifoObj* fifo);
u32 GXGetFifoSize(const GXFifoObj* fifo);
GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb);

#endif
