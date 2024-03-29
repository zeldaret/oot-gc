#include "dolphin/os.h"

#define PopHead(queue, mutex, link)   \
    do {                              \
        OSMutex* __next;              \
                                      \
        (mutex) = (queue)->head;      \
        __next = (mutex)->link.next;  \
        if (__next == NULL)           \
            (queue)->tail = NULL;     \
        else                          \
            __next->link.prev = NULL; \
        (queue)->head = __next;       \
    } while (0)

void __OSUnlockAllMutex(OSThread* thread) {
    OSMutex* mutex;

    while (thread->queueMutex.head) {
        PopHead(&thread->queueMutex, mutex, link);
        mutex->count = 0;
        mutex->thread = NULL;
        OSWakeupThread(&mutex->queue);
    }
}
