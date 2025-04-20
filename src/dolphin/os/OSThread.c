#include "intrinsics.h"

#include "dolphin/private/__os.h"

static vu32 RunQueueBits;
static volatile bool RunQueueHint;
static vs32 Reschedule;

static OSThreadQueue RunQueue[32];
static OSThread IdleThread;
static OSThread DefaultThread;
static OSContext IdleContext;
static void DefaultSwitchThreadCallback(OSThread* from, OSThread* to);
static OSSwitchThreadCallback SwitchThreadCallback = DefaultSwitchThreadCallback;

static void DefaultSwitchThreadCallback(OSThread* from, OSThread* to) {}

extern u8 _stack_addr[];
extern u8 _stack_end[];
extern u32 __OSFpscrEnableBits;
extern OSErrorHandler __OSErrorTable[OS_ERROR_MAX];

#define AddTail(queue, thread, link)    \
    do {                                \
        OSThread* prev;                 \
                                        \
        prev = (queue)->tail;           \
        if (prev == NULL)               \
            (queue)->head = (thread);   \
        else                            \
            prev->link.next = (thread); \
        (thread)->link.prev = prev;     \
        (thread)->link.next = NULL;     \
        (queue)->tail = (thread);       \
    } while (0)

#define AddPrio(queue, thread, link)                                                                   \
    do {                                                                                               \
        OSThread *prev, *next;                                                                         \
                                                                                                       \
        for (next = (queue)->head; next && next->priority <= thread->priority; next = next->link.next) \
            ;                                                                                          \
        if (next == NULL)                                                                              \
            AddTail(queue, thread, link);                                                              \
        else {                                                                                         \
            (thread)->link.next = next;                                                                \
            prev = next->link.prev;                                                                    \
            next->link.prev = (thread);                                                                \
            (thread)->link.prev = prev;                                                                \
            if (prev == NULL)                                                                          \
                (queue)->head = (thread);                                                              \
            else                                                                                       \
                prev->link.next = (thread);                                                            \
        }                                                                                              \
    } while (0)

#define RemoveItem(queue, thread, link) \
    do {                                \
        OSThread *next, *prev;          \
        next = (thread)->link.next;     \
        prev = (thread)->link.prev;     \
        if (next == NULL)               \
            (queue)->tail = prev;       \
        else                            \
            next->link.prev = prev;     \
        if (prev == NULL)               \
            (queue)->head = next;       \
        else                            \
            prev->link.next = next;     \
    } while (0)

#define RemoveHead(queue, thread, link) \
    do {                                \
        OSThread* __next;               \
        (thread) = (queue)->head;       \
        __next = (thread)->link.next;   \
        if (__next == NULL)             \
            (queue)->tail = NULL;       \
        else                            \
            __next->link.prev = NULL;   \
        (queue)->head = __next;         \
    } while (0)

static inline void OSInitMutexQueue(OSMutexQueue* queue) { queue->head = queue->tail = NULL; }

static inline void OSSetCurrentThread(OSThread* thread) {
    SwitchThreadCallback(__OSCurrentThread, thread);
    __OSCurrentThread = thread;
}

void __OSThreadInit(void) {
    OSThread* thread = &DefaultThread;
    int prio;

    thread->state = OS_THREAD_STATE_RUNNING;
    thread->attr = OS_THREAD_ATTR_DETACH;
    thread->priority = thread->base = 16;
    thread->suspend = 0;
    thread->val = (void*)-1;
    thread->mutex = NULL;
    OSInitThreadQueue(&thread->queueJoin);
    OSInitMutexQueue(&thread->queueMutex);

    __OSFPUContext = &thread->context;

    OSClearContext(&thread->context);
    OSSetCurrentContext(&thread->context);
    thread->stackBase = (void*)_stack_addr;
    thread->stackEnd = (void*)_stack_end;
    *(thread->stackEnd) = OS_THREAD_STACK_MAGIC;

    OSSetCurrentThread(thread);
    OSClearStack(0);

    RunQueueBits = 0;
    RunQueueHint = false;
    for (prio = OS_PRIORITY_MIN; prio <= OS_PRIORITY_MAX; ++prio) {
        OSInitThreadQueue(&RunQueue[prio]);
    }

    OSInitThreadQueue(&__OSActiveThreadQueue);
    AddTail(&__OSActiveThreadQueue, thread, linkActive);
    OSClearContext(&IdleContext);
    Reschedule = 0;
}

void OSInitThreadQueue(OSThreadQueue* queue) { queue->head = queue->tail = NULL; }

OSThread* OSGetCurrentThread(void) { return __OSCurrentThread; }

s32 OSDisableScheduler(void) {
    bool enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = Reschedule++;
    OSRestoreInterrupts(enabled);
    return count;
}

s32 OSEnableScheduler(void) {
    bool enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = Reschedule--;
    OSRestoreInterrupts(enabled);
    return count;
}

static inline void SetRun(OSThread* thread) {
    thread->queue = &RunQueue[thread->priority];
    AddTail(thread->queue, thread, link);
    RunQueueBits |= 1u << (OS_PRIORITY_MAX - thread->priority);
    RunQueueHint = true;
}

#pragma dont_inline on
static void UnsetRun(OSThread* thread) {
    OSThreadQueue* queue;
    queue = thread->queue;
    RemoveItem(queue, thread, link);
    if (queue->head == 0) {
        RunQueueBits &= ~(1u << (OS_PRIORITY_MAX - thread->priority));
    }
    thread->queue = NULL;
}
#pragma dont_inline reset

OSPriority __OSGetEffectivePriority(OSThread* thread) {
    OSPriority priority;
    OSMutex* mutex;
    OSThread* blocked;

    priority = thread->base;
    for (mutex = thread->queueMutex.head; mutex; mutex = mutex->link.next) {
        blocked = mutex->queue.head;
        if (blocked && blocked->priority < priority) {
            priority = blocked->priority;
        }
    }
    return priority;
}

static OSThread* SetEffectivePriority(OSThread* thread, OSPriority priority) {
    switch (thread->state) {
        case OS_THREAD_STATE_READY:
            UnsetRun(thread);
            thread->priority = priority;
            SetRun(thread);
            break;
        case OS_THREAD_STATE_WAITING:
            RemoveItem(thread->queue, thread, link);
            thread->priority = priority;
            AddPrio(thread->queue, thread, link);
            if (thread->mutex) {
                return thread->mutex->thread;
            }
            break;
        case OS_THREAD_STATE_RUNNING:
            RunQueueHint = true;
            thread->priority = priority;
            break;
    }
    return NULL;
}

static inline void UpdatePriority(OSThread* thread) {
    OSPriority priority;

    do {
        if (0 < thread->suspend) {
            break;
        }
        priority = __OSGetEffectivePriority(thread);
        if (thread->priority == priority) {
            break;
        }
        thread = SetEffectivePriority(thread, priority);
    } while (thread);
}

static inline void __OSSwitchThread(OSThread* nextThread) {
    OSSetCurrentThread(nextThread);
    OSSetCurrentContext(&nextThread->context);
    OSLoadContext(&nextThread->context);
}

static OSThread* SelectThread(bool yield) {
    OSContext* currentContext;
    OSThread* currentThread;
    OSThread* nextThread;
    OSPriority priority;
    OSThreadQueue* queue;

    if (0 < Reschedule) {
        return 0;
    }

    currentContext = OSGetCurrentContext();
    currentThread = OSGetCurrentThread();
    if (currentContext != &currentThread->context) {
        return 0;
    }

    if (currentThread) {
        if (currentThread->state == OS_THREAD_STATE_RUNNING) {
            if (!yield) {
                priority = __cntlzw(RunQueueBits);
                if (currentThread->priority <= priority) {
                    return 0;
                }
            }
            currentThread->state = OS_THREAD_STATE_READY;
            SetRun(currentThread);
        }

        if (!(currentThread->context.state & OS_CONTEXT_STATE_EXC) && OSSaveContext(&currentThread->context)) {
            return 0;
        }
    }

#if IS_MQ
    OSSetCurrentThread(NULL);
#endif

    if (RunQueueBits == 0) {
#if IS_CE
        OSSetCurrentThread(NULL);
#endif

        OSSetCurrentContext(&IdleContext);
        do {
            OSEnableInterrupts();
            while (RunQueueBits == 0)
                ;
            OSDisableInterrupts();
        } while (RunQueueBits == 0);

        OSClearContext(&IdleContext);
    }

    RunQueueHint = false;

    priority = __cntlzw(RunQueueBits);
    queue = &RunQueue[priority];
    RemoveHead(queue, nextThread, link);
    if (queue->head == 0) {
        RunQueueBits &= ~(1u << (OS_PRIORITY_MAX - priority));
    }
    nextThread->queue = NULL;
    nextThread->state = OS_THREAD_STATE_RUNNING;
    __OSSwitchThread(nextThread);
    return nextThread;
}

void __OSReschedule(void) {
    if (!RunQueueHint) {
        return;
    }

    SelectThread(false);
}

bool OSCreateThread(OSThread* thread, void* (*func)(void*), void* param, void* stack, u32 stackSize,
                    OSPriority priority, u16 attr) {
    bool enable;
    u32 stackThing;
    int i;
    u32 tmp[2]; // DUMB compiler smfh.

    if (priority < OS_PRIORITY_MIN || priority > OS_PRIORITY_MAX) {
        return false;
    }

    stackThing = ((u32)stack & 0xFFFFFFF8); // ??
    thread->state = OS_THREAD_STATE_READY;
    thread->attr = attr & OS_THREAD_ATTR_DETACH;
    thread->base = priority;
    thread->priority = priority;
    thread->suspend = 1;
    thread->val = (void*)-1;
    thread->mutex = NULL;
    OSInitThreadQueue(&thread->queueJoin);
    OSInitMutexQueue(&thread->queueMutex);
    *(u32*)(stackThing - 8) = 0;
    *(u32*)(stackThing - 4) = 0;

    OSInitContext(&thread->context, (u32)func, (u32)(stackThing - 8));

    thread->context.lr = (u32)&OSExitThread;
    thread->context.gpr[3] = (u32)param;
    thread->stackBase = stack;
    thread->stackEnd = (u32*)((u32)stack - stackSize);
    *(thread->stackEnd) = OS_THREAD_STACK_MAGIC;
    thread->error = 0;
    thread->specific[0] = NULL;
    thread->specific[1] = NULL;

    enable = OSDisableInterrupts();

    if (__OSErrorTable[16] != NULL) {
        thread->context.srr1 |= 0x900; // ??
        thread->context.state |= OS_CONTEXT_STATE_FPSAVED;
        thread->context.fpscr = (__OSFpscrEnableBits & 0xF8) | 0x4; // ??

        for (i = 0; i < 32; i++) {
            *(u64*)&thread->context.fpr[i] = -1; // ???????
            *(u64*)&thread->context.psf[i] = -1; // ???????
        }
    }

    AddTail(&__OSActiveThreadQueue, thread, linkActive);
    OSRestoreInterrupts(enable);
    return true;
}

void OSExitThread(void* val) {
    OSThread* thread;
    bool enable;

    enable = OSDisableInterrupts();
    thread = __OSCurrentThread;
    OSClearContext(&thread->context);

    if (thread->attr & OS_THREAD_ATTR_DETACH) {
        RemoveItem(&__OSActiveThreadQueue, thread, linkActive);
        thread->state = 0;

    } else {
        thread->state = OS_THREAD_STATE_MORIBUND;
        thread->val = val;
    }

    __OSUnlockAllMutex(thread);
    OSWakeupThread(&thread->queueJoin);
    RunQueueHint = true;
    if (RunQueueHint != false) {
        SelectThread(false);
    }

    OSRestoreInterrupts(enable);
}

void OSCancelThread(OSThread* thread) {
    bool enabled;

    enabled = OSDisableInterrupts();

    switch (thread->state) {
        case OS_THREAD_STATE_READY:
            if (!(0 < thread->suspend)) {
                UnsetRun(thread);
            }
            break;
        case OS_THREAD_STATE_RUNNING:
            RunQueueHint = true;
            break;
        case OS_THREAD_STATE_WAITING:
            RemoveItem(thread->queue, thread, link);
            thread->queue = NULL;
            if (!(0 < thread->suspend) && thread->mutex) {
                UpdatePriority(thread->mutex->thread);
            }
            break;
        default:
            OSRestoreInterrupts(enabled);
            return;
    }

    OSClearContext(&thread->context);
    if (thread->attr & OS_THREAD_ATTR_DETACH) {
        RemoveItem(&__OSActiveThreadQueue, thread, linkActive);
        thread->state = 0;
    } else {
        thread->state = OS_THREAD_STATE_MORIBUND;
    }

    __OSUnlockAllMutex(thread);

    OSWakeupThread(&thread->queueJoin);

    __OSReschedule();
    OSRestoreInterrupts(enabled);

    return;
}

s32 OSResumeThread(OSThread* thread) {
    bool enabled;
    s32 suspendCount;

    enabled = OSDisableInterrupts();
    suspendCount = thread->suspend--;
    if (thread->suspend < 0) {
        thread->suspend = 0;
    } else if (thread->suspend == 0) {
        switch (thread->state) {
            case OS_THREAD_STATE_READY:
                thread->priority = __OSGetEffectivePriority(thread);
                SetRun(thread);
                break;
            case OS_THREAD_STATE_WAITING:
                RemoveItem(thread->queue, thread, link);
                thread->priority = __OSGetEffectivePriority(thread);
                AddPrio(thread->queue, thread, link);
                if (thread->mutex) {
                    UpdatePriority(thread->mutex->thread);
                }
                break;
        }
        __OSReschedule();
    }
    OSRestoreInterrupts(enabled);
    return suspendCount;
}

s32 OSSuspendThread(OSThread* thread) {
    bool enabled;
    s32 suspendCount;

    enabled = OSDisableInterrupts();
    suspendCount = thread->suspend++;
    if (suspendCount == 0) {
        switch (thread->state) {
            case OS_THREAD_STATE_RUNNING:
                RunQueueHint = true;
                thread->state = OS_THREAD_STATE_READY;
                break;
            case OS_THREAD_STATE_READY:
                UnsetRun(thread);
                break;
            case OS_THREAD_STATE_WAITING:
                RemoveItem(thread->queue, thread, link);
                thread->priority = 32;
                AddTail(thread->queue, thread, link);
                if (thread->mutex) {
                    UpdatePriority(thread->mutex->thread);
                }
                break;
        }

        __OSReschedule();
    }
    OSRestoreInterrupts(enabled);
    return suspendCount;
}

void OSSleepThread(OSThreadQueue* queue) {
    bool enabled;
    OSThread* currentThread;

    enabled = OSDisableInterrupts();
    currentThread = OSGetCurrentThread();

    currentThread->state = OS_THREAD_STATE_WAITING;
    currentThread->queue = queue;
    AddPrio(queue, currentThread, link);
    RunQueueHint = true;
    __OSReschedule();
    OSRestoreInterrupts(enabled);
}

void OSWakeupThread(OSThreadQueue* queue) {
    bool enabled;
    OSThread* thread;

    enabled = OSDisableInterrupts();
    while (queue->head) {
        RemoveHead(queue, thread, link);
        thread->state = OS_THREAD_STATE_READY;
        if (!(0 < thread->suspend)) {
            SetRun(thread);
        }
    }
    __OSReschedule();
    OSRestoreInterrupts(enabled);
}

void OSClearStack(u8 val) {
    register u32 sp;
    register u32* p;
    register u32 pattern;

    pattern = ((u32)val << 24) | ((u32)val << 16) | ((u32)val << 8) | (u32)val;
    sp = OSGetStackPointer();
    for (p = __OSCurrentThread->stackEnd + 1; p < (u32*)sp; ++p) {
        *p = pattern;
    }
}
