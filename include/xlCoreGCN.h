#ifndef _XL_CORE_GCN_H
#define _XL_CORE_GCN_H

#include "dolphin.h"

void xlCoreBeforeRender(void);
s32 xlCoreHiResolution(void);
s32 xlCoreGetArgument(s32 iArgument, char** pszArgument);
s32 xlCoreGetArgumentCount(void);
s32 xlCoreReset(void);

extern GXRenderModeObj* rmode;

#endif
