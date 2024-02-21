#ifndef _DOLPHIN_VI_H_
#define _DOLPHIN_VI_H_

#include "dolphin/vi/vifuncs.h"
#include "dolphin/vi/vitypes.h"

#ifdef __MWERKS__
volatile u16 __VIRegs[59] : 0xCC002000;
#else
#define __VIRegs ((volatile u16*)0xCC002000)
#endif

#endif
