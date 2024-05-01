#include "dolphin/os.h"

void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* msgArray, s32 msgCount) {
    OSInitThreadQueue(&mq->queueSend);
    OSInitThreadQueue(&mq->queueReceive);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}

bool OSSendMessage(OSMessageQueue* mq, OSMessage msg, s32 flags) {
    bool enabled;
    s32 lastIndex;

    enabled = OSDisableInterrupts();

    while (mq->msgCount <= mq->usedCount) {
        if (!(flags & OS_MESSAGE_BLOCK)) {
            OSRestoreInterrupts(enabled);
            return false;
        } else {
            OSSleepThread(&mq->queueSend);
        }
    }

    lastIndex = (mq->firstIndex + mq->usedCount) % mq->msgCount;
    mq->msgArray[lastIndex] = msg;
    mq->usedCount++;

    OSWakeupThread(&mq->queueReceive);

    OSRestoreInterrupts(enabled);
    return true;
}

bool OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, s32 flags) {
    bool enabled;

    enabled = OSDisableInterrupts();

    while (mq->usedCount == 0) {
        if (!(flags & OS_MESSAGE_BLOCK)) {
            OSRestoreInterrupts(enabled);
            return false;
        } else {
            OSSleepThread(&mq->queueReceive);
        }
    }

    if (msg != NULL) {
        *msg = mq->msgArray[mq->firstIndex];
    }
    mq->firstIndex = (mq->firstIndex + 1) % mq->msgCount;
    mq->usedCount--;

    OSWakeupThread(&mq->queueSend);

    OSRestoreInterrupts(enabled);
    return true;
}
