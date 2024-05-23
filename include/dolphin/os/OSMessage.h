#ifndef _DOLPHIN_OSMESSAGE
#define _DOLPHIN_OSMESSAGE

#include "dolphin/os/OSThread.h"
typedef struct OSMessageQueue OSMessageQueue;
typedef void* OSMessage;

struct OSMessageQueue {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage* msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
};

// Flags to turn blocking on/off when sending/receiving message
#define OS_MESSAGE_NOBLOCK 0
#define OS_MESSAGE_BLOCK 1

void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* msgArray, s32 msgCount);
bool OSSendMessage(OSMessageQueue* mq, OSMessage msg, s32 flags);
bool OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, s32 flags);

#endif // _DOLPHIN_OSMESSAGE
