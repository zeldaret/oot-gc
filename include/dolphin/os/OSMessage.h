#ifndef _DOLPHIN_OS_OSMESSAGE_H
#define _DOLPHIN_OS_OSMESSAGE_H

#include "dolphin/os/OSThread.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    void* msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
} OSMessageQueue;

typedef void* OSMessage;

// Flags to turn blocking on/off when sending/receiving message
#define OS_MESSAGE_NOBLOCK 0
#define OS_MESSAGE_BLOCK 1

void OSInitMessageQueue(OSMessageQueue* mq, void* msgArray, s32 msgCount);
int OSSendMessage(OSMessageQueue* mq, void* msg, s32 flags);
int OSReceiveMessage(OSMessageQueue* mq, void* msg, s32 flags);
int OSJamMessage(OSMessageQueue* mq, void* msg, s32 flags);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSMESSAGE_H_
