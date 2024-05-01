#ifndef _XL_CORE_GCN_H
#define _XL_CORE_GCN_H

#include "dolphin.h"

extern GXRenderModeObj* rmode;

bool xlCoreReset(void);
s32 xlCoreGetArgumentCount(void);
bool xlCoreGetArgument(s32 iArgument, char** pszArgument);
bool xlCoreHiResolution(void);
void xlCoreBeforeRender(void);

#endif
