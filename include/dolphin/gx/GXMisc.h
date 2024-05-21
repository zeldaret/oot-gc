#ifndef _DOLPHIN_GX_MISC_H
#define _DOLPHIN_GX_MISC_H

#include "dolphin/gx/GXFifo.h"
#include "dolphin/types.h"

GXFifoObj* GXInit(void* base, u32 size);
void __GXInitGX();
void __GXPEInit();

#endif
