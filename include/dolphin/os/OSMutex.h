#ifndef _DOLPHIN_OSMUTEX
#define _DOLPHIN_OSMUTEX

#include "dolphin/os/OSThread.h"
#include "dolphin/types.h"

struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread; // the current owner
    s32 count; // lock count
    OSMutexLink link; // for OSThread.queueMutex
};

struct OSCond {
    OSThreadQueue queue;
};

void __OSUnlockAllMutex(OSThread* thread);

#endif // _DOLPHIN_OSMUTEX
