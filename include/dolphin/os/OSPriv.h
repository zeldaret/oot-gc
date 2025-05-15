#ifndef _DOLPHIN_OSPRIV
#define _DOLPHIN_OSPRIV

#include "dolphin/os/OSException.h"
#include "dolphin/os/OSTime.h"

__OSExceptionHandler __OSGetExceptionHandler(__OSException exception);
__OSExceptionHandler __OSSetExceptionHandler(__OSException exception, __OSExceptionHandler handler);
OSTime __OSGetSystemTime(void);
OSTime __OSTimeToSystemTime(OSTime);

#endif // _DOLPHIN_OSPRIV
