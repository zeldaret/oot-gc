#ifndef _DOLPHIN_OS_OSSEMAPHORE_H
#define _DOLPHIN_OS_OSSEMAPHORE_H

#include "dolphin/os/OSThread.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSSemaphore {
    s32 count;
    OSThreadQueue queue;
} OSSemaphore;

void OSInitSemaphore(OSSemaphore* sem, s32 count);
s32 OSWaitSemaphore(OSSemaphore* sem);
s32 OSTryWaitSemaphore(OSSemaphore* sem);
s32 OSSignalSemaphore(OSSemaphore* sem);
s32 OSGetSemaphoreCount(OSSemaphore* sem);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSSEMAPHORE_H_
