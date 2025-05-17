#include "dolphin/os.h"

#include "dolphin/private/__os.h"

void OSInitMessageQueue(OSMessageQueue* mq, void* msgArray, s32 msgCount) {
    OSInitThreadQueue(&mq->queueSend);
    OSInitThreadQueue(&mq->queueReceive);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}

bool OSSendMessage(OSMessageQueue* mq, void* msg, s32 flags) {
    bool enabled;
    s32 lastIndex;

    enabled = OSDisableInterrupts();

    while (mq->msgCount <= mq->usedCount) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return false;
        } else {
            OSSleepThread(&mq->queueSend);
        }
    }

    lastIndex = (mq->firstIndex + mq->usedCount) % mq->msgCount;
    ((u32*)mq->msgArray)[lastIndex] = (u32)msg;
    mq->usedCount++;

    OSWakeupThread(&mq->queueReceive);

    OSRestoreInterrupts(enabled);
    return true;
}

bool OSReceiveMessage(OSMessageQueue* mq, void* msg, s32 flags) {
    bool enabled;

    enabled = OSDisableInterrupts();

    while (mq->usedCount == 0) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return false;
        } else {
            OSSleepThread(&mq->queueReceive);
        }
    }

    if (msg != NULL) {
        *(u32*)msg = ((u32*)mq->msgArray)[mq->firstIndex];
    }
    mq->firstIndex = (mq->firstIndex + 1) % mq->msgCount;
    mq->usedCount--;

    OSWakeupThread(&mq->queueSend);

    OSRestoreInterrupts(enabled);
    return true;
}
