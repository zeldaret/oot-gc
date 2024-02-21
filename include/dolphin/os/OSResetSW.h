#ifndef _DOLPHIN_OS_OSRESETSW_H_
#define _DOLPHIN_OS_OSRESETSW_H_

#include "dolphin/hw_regs.h"
#include "dolphin/types.h"

void __OSResetSWInterruptHandler();
void (*OSSetResetCallback(void (*callback)()))();
int OSGetResetSwitchState();
BOOL OSGetResetButtonState(void);

#endif
