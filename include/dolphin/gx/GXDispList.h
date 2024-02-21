#ifndef _DOLPHIN_GX_GXDISPLIST_H_
#define _DOLPHIN_GX_GXDISPLIST_H_

#include "dolphin/types.h"

void GXBeginDisplayList(void* list, u32 size);
u32 GXEndDisplayList(void);
void GXCallDisplayList(void* list, u32 nbytes);

#endif
