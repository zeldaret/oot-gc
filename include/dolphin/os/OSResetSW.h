#ifndef _DOLPHIN_OS_OSRESETSW_H_
#define _DOLPHIN_OS_OSRESETSW_H_

#include "dolphin/types.h"

void __OSResetSWInterruptHandler(void);
BOOL OSGetResetButtonState(void);

#endif
