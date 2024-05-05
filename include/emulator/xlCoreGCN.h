#ifndef _XL_CORE_GCN_H
#define _XL_CORE_GCN_H

#include "dolphin.h"

extern GXRenderModeObj* rmode;

void xlCoreBeforeRender(void);
bool xlCoreHiResolution(void);
bool xlCoreGetArgument(s32 iArgument, char** pszArgument);
s32 xlCoreGetArgumentCount(void);
bool xlCoreReset(void);
void xlCoreBeforeRender(void);

#endif
