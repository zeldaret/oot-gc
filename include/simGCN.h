#ifndef _SIMGCN_H
#define _SIMGCN_H

#include "dolphin.h"
#include "system.h"

extern s32 gDVDResetToggle;
extern s32 gbDisplayedError;

extern System* gpSystem;

s32 simulatorShowLoad(s32 /* unknown */, char* szNameFile, f32 rProgress);

#endif
