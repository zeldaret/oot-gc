#ifndef _DOLPHIN_GX_GXMANAGE_H_
#define _DOLPHIN_GX_GXMANAGE_H_

#include "dolphin/gx/GXFifo.h"

typedef void (*GXDrawDoneCallback)(void);

GXFifoObj* GXInit(void* base, u32 size);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb);
void GXDrawDone(void);
void GXSetDrawDone(void);
void GXFlush(void);

#endif
