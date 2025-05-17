#ifndef _DOLPHIN_OS_OSRESETSW_H
#define _DOLPHIN_OS_OSRESETSW_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*OSResetCallback)(void);

OSResetCallback OSSetResetCallback(OSResetCallback callback);
bool OSGetResetSwitchState(void);
bool OSGetResetButtonState(void);

#ifdef __cplusplus
}
#endif

#endif
