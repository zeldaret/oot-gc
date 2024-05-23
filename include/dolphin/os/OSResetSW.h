#ifndef _DOLPHIN_OSRESETSW
#define _DOLPHIN_OSRESETSW

#include "dolphin/os/OSContext.h"
#include "dolphin/types.h"

typedef void (*OSResetCallback)(void);

bool OSGetResetButtonState(void);

#endif // _DOLPHIN_OSRESETSW
