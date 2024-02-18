#ifndef _DOLPHIN_OSMUTEX_H_
#define _DOLPHIN_OSMUTEX_H_

#include <dolphin/OSThread.h>

typedef struct OSMutex
{
    /*0x00*/ OSThreadQueue queue;
    /*0x08*/ OSThread *thread;
    /*0x0C*/ s32 count;
    /*0x10*/ OSMutexLink link;
} OSMutex;

#endif
