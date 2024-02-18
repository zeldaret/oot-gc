#ifndef _DOLPHIN_OSRESETSW_H_
#define _DOLPHIN_OSRESETSW_H_

#include <dolphin/types.h>
#include <dolphin/hw_regs.h>

void __OSResetSWInterruptHandler();
void (* OSSetResetCallback(void (* callback)()))();
int OSGetResetSwitchState();
BOOL OSGetResetButtonState(void);

#endif
