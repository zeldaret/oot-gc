#include "dolphin/dvd.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os.h"
#include "macros.h"

static bool FirstRead = true;
static volatile bool StopAtNextInt = false;
static u32 LastLength = 0;
static DVDLowCallback Callback = NULL;
static DVDLowCallback ResetCoverCallback = NULL;
static volatile OSTime LastResetEnd = 0;
static vu32 ResetOccurred = false;
static volatile bool WaitingCoverClose = false;
static bool Breaking = false;
static vu32 WorkAroundType = 0;
static u32 WorkAroundSeekLocation = 0;
static volatile OSTime LastReadFinished = 0;
static OSTime LastReadIssued = 0;
static volatile bool LastCommandWasRead = false;
static vu32 NextCommandNumber = 0;

typedef struct DVDBuffer {
    void* addr;
    u32 length;
    u32 offset;
} DVDBuffer;

typedef struct DVDCommand {
    s32 cmd;
    void* addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

static DVDCommand CommandList[3];
static OSAlarm AlarmForWA;
static OSAlarm AlarmForTimeout;
static OSAlarm AlarmForBreak;
static DVDBuffer Prev;
static DVDBuffer Curr;

WEAK void __DVDInitWA() {
    NextCommandNumber = 0;
    CommandList[0].cmd = -1;
    __DVDLowSetWAType(0, 0);
    OSInitAlarm();
}

static void Read(void* addr, u32 length, u32 offset, DVDLowCallback callback);

static inline bool ProcessNextCommand(void) {
    s32 n = NextCommandNumber;

    if (CommandList[n].cmd == 1) {
        ++NextCommandNumber;
        Read(CommandList[n].addr, CommandList[n].length, CommandList[n].offset, CommandList[n].callback);
        return true;
    } else if (CommandList[n].cmd == 2) {
        ++NextCommandNumber;
        DVDLowSeek(CommandList[n].offset, CommandList[n].callback);
        return true;
    }

    return false;
}

WEAK void __DVDInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    DVDLowCallback cb;
    OSContext exceptionContext;
    u32 cause = 0;
    u32 reg;
    u32 intr;
    u32 mask;

    if (LastCommandWasRead) {
        LastReadFinished = __OSGetSystemTime();
        FirstRead = false;
        Prev.addr = Curr.addr;
        Prev.length = Curr.length;
        Prev.offset = Curr.offset;
        if (StopAtNextInt == true) {
            cause |= 8;
        }
    }

    LastCommandWasRead = false;
    StopAtNextInt = false;
    reg = __DIRegs[0];
    mask = reg & 0x2A;
    intr = (reg & 0x54) & (mask << 1);

    if (intr & 0x40) {
        cause |= 8;
    }

    if (intr & 0x10) {
        cause |= 1;
    }

    if (intr & 4) {
        cause |= 2;
    }

    if (cause) {
        ResetOccurred = false;
        OSCancelAlarm(&AlarmForTimeout);
    }

    __DIRegs[0] = intr | mask;

    if (ResetOccurred && (__OSGetSystemTime() - LastResetEnd) < OSMillisecondsToTicks(200)) {
        reg = __DIRegs[1];
        mask = reg & 0x2;
        intr = (reg & 4) & (mask << 1);
        if (intr & 4) {
            if (ResetCoverCallback) {
                ResetCoverCallback(4);
            }
            ResetCoverCallback = NULL;
        }

        __DIRegs[1] = __DIRegs[1];
    } else if (WaitingCoverClose) {
        reg = __DIRegs[1];
        mask = reg & 2;
        intr = (reg & 4) & (mask << 1);

        if (intr & 4) {
            cause |= 4;
        }

        __DIRegs[1] = intr | mask;
        WaitingCoverClose = false;
    } else {
        __DIRegs[1] = 0;
    }

    if ((cause & 8) && !Breaking) {
        cause &= ~8;
    }

    if ((cause & 1)) {
        if (ProcessNextCommand()) {
            return;
        }
    } else {
        CommandList[0].cmd = -1;
        NextCommandNumber = 0;
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (cause) {
        cb = Callback;
        Callback = NULL;
        if (cb) {
            cb(cause);
        }

        Breaking = false;
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

static void AlarmHandler(OSAlarm* alarm, OSContext* context) { bool error = ProcessNextCommand(); }

static void AlarmHandlerForTimeout(OSAlarm* alarm, OSContext* context) {
    OSContext tmpContext;
    DVDLowCallback callback;
    __OSMaskInterrupts(0x400);
    OSClearContext(&tmpContext);
    OSSetCurrentContext(&tmpContext);
    callback = Callback;
    Callback = NULL;
    if (callback != NULL) {
        callback(0x10);
    }
    OSClearContext(&tmpContext);
    OSSetCurrentContext(context);
}

static inline void SetTimeoutAlarm(OSTime timeout) {
    OSCreateAlarm(&AlarmForTimeout);
    OSSetAlarm(&AlarmForTimeout, timeout, AlarmHandlerForTimeout);
}

static void Read(void* addr, u32 length, u32 offset, DVDLowCallback callback) {
    StopAtNextInt = false;
    LastCommandWasRead = true;
    Callback = callback;
    LastReadIssued = __OSGetSystemTime();

    __DIRegs[2] = 0xA8000000;
    __DIRegs[3] = offset / 4;
    __DIRegs[4] = length;
    __DIRegs[5] = (u32)addr;
    __DIRegs[6] = length;
    LastLength = length;
    __DIRegs[7] = 3;

    if (length > 0xA00000) {
        SetTimeoutAlarm(OSSecondsToTicks(20));
    } else {
        SetTimeoutAlarm(OSSecondsToTicks(10));
    }
}

inline bool HitCache(DVDBuffer* cur, DVDBuffer* prev) {
    u32 uVar1 = (prev->offset + prev->length - 1) >> 15;
    u32 uVar2 = (cur->offset >> 15);
    u32 iVar3 = (DVDGetCurrentDiskID()->streaming ? true : false) ? 5 : 15;

    if ((uVar2 > uVar1 - 2) || (uVar2 < uVar1 + iVar3 + 3)) {
        return true;
    }
    return false;
}

static inline void DoJustRead(void* addr, u32 length, u32 offset, DVDLowCallback callback) {
    CommandList[0].cmd = -1;
    NextCommandNumber = 0;
    Read(addr, length, offset, callback);
}

static void SeekTwiceBeforeRead(void* addr, u32 length, u32 offset, DVDLowCallback callback) {
    u32 newOffset = offset & ~0x7FFF;
    if (!newOffset) {
        newOffset = 0;
    } else {
        newOffset += WorkAroundSeekLocation;
    }
    CommandList[0].cmd = 2;
    CommandList[0].offset = newOffset;
    CommandList[0].callback = callback;
    CommandList[1].cmd = 1;
    CommandList[1].addr = addr;
    CommandList[1].length = length;
    CommandList[1].offset = offset;
    CommandList[1].callback = callback;
    CommandList[2].cmd = -1;
    NextCommandNumber = 0;
    DVDLowSeek(newOffset, callback);
}

static inline void WaitBeforeRead(void* addr, u32 length, u32 offset, DVDLowCallback callback, OSTime timeout) {
    CommandList[0].cmd = 1;
    CommandList[0].addr = addr;
    CommandList[0].length = length;
    CommandList[0].offset = offset;
    CommandList[0].callback = callback;
    CommandList[1].cmd = -1;
    NextCommandNumber = 0;
    OSCreateAlarm(&AlarmForWA);
    OSSetAlarm(&AlarmForWA, timeout, AlarmHandler);
}

WEAK bool DVDLowRead(void* addr, u32 length, u32 offset, DVDLowCallback callback) {
    OSTime diff;
    u32 prev;

    __DIRegs[6] = length;
    Curr.addr = addr;
    Curr.length = length;
    Curr.offset = offset;

    if (WorkAroundType == 0) {
        DoJustRead(addr, length, offset, callback);
    } else if (WorkAroundType == 1) {
        if (FirstRead) {
            SeekTwiceBeforeRead(addr, length, offset, callback);
        } else {
            if (!HitCache(&Curr, &Prev)) {
                DoJustRead(addr, length, offset, callback);
            } else {
                prev = (Prev.offset + Prev.length - 1) >> 15;
                if (prev == Curr.offset >> 15 || prev + 1 == Curr.offset >> 15) {
                    diff = __OSGetSystemTime() - LastReadFinished;
                    if (OSMillisecondsToTicks(5) < diff) {
                        DoJustRead(addr, length, offset, callback);
                    } else {
                        WaitBeforeRead(addr, length, offset, callback,
                                       OSMillisecondsToTicks(5) - diff + OSMicrosecondsToTicks(500));
                    }
                } else {
                    SeekTwiceBeforeRead(addr, length, offset, callback);
                }
            }
        }
    }
    return true;
}

WEAK bool DVDLowSeek(u32 offset, DVDLowCallback callback) {
    StopAtNextInt = false;
    Callback = callback;
    __DIRegs[2] = 0xAB000000;
    __DIRegs[3] = offset / 4;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return true;
}

WEAK bool DVDLowWaitCoverClose(DVDLowCallback callback) {
    Callback = callback;
    WaitingCoverClose = true;
    StopAtNextInt = false;
    __DIRegs[1] = 2;
    return true;
}

WEAK bool DVDLowReadDiskID(DVDDiskID* diskID, DVDLowCallback callback) {
    StopAtNextInt = false;
    Callback = callback;
    __DIRegs[2] = 0xA8000040;
    __DIRegs[3] = 0;
    __DIRegs[4] = sizeof(DVDDiskID);
    __DIRegs[5] = (u32)diskID;
    __DIRegs[6] = sizeof(DVDDiskID);
    __DIRegs[7] = 3;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return true;
}

WEAK bool DVDLowStopMotor(DVDLowCallback callback) {
    StopAtNextInt = false;
    Callback = callback;
    __DIRegs[2] = 0xE3000000;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return true;
}

WEAK bool DVDLowRequestError(DVDLowCallback callback) {
    StopAtNextInt = false;
    Callback = callback;
    __DIRegs[2] = 0xE0000000;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return true;
}

WEAK bool DVDLowInquiry(DVDDriveInfo* info, DVDLowCallback callback) {
    StopAtNextInt = false;
    Callback = callback;
    __DIRegs[2] = 0x12000000;
    __DIRegs[4] = sizeof(DVDDriveInfo);
    __DIRegs[5] = (u32)info;
    __DIRegs[6] = sizeof(DVDDriveInfo);
    __DIRegs[7] = 3;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return true;
}

WEAK bool DVDLowAudioStream(u32 subcmd, u32 length, u32 offset, DVDLowCallback callback) {
    StopAtNextInt = false;
    Callback = callback;
    __DIRegs[2] = subcmd | 0xE1000000;
    __DIRegs[3] = offset >> 2;
    __DIRegs[4] = length;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return true;
}

WEAK bool DVDLowRequestAudioStatus(u32 subcmd, DVDLowCallback callback) {
    StopAtNextInt = false;
    Callback = callback;
    __DIRegs[2] = subcmd | 0xE2000000;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return true;
}

WEAK bool DVDLowAudioBufferConfig(bool enable, u32 size, DVDLowCallback callback) {
    StopAtNextInt = false;
    Callback = callback;
    __DIRegs[2] = 0xE4000000 | (enable != 0 ? 0x10000 : 0) | size;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return true;
}

WEAK void DVDLowReset() {
    u32 reg;
    OSTime resetStart;

    __DIRegs[1] = 2;
    reg = __PIRegs[9];
    __PIRegs[9] = (reg & ~4) | 1;

    resetStart = __OSGetSystemTime();
    while ((__OSGetSystemTime() - resetStart) < OSMicrosecondsToTicks(12))
        ;

    __PIRegs[9] = reg | 5;
    ResetOccurred = true;
    LastResetEnd = __OSGetSystemTime();
}

WEAK bool DVDLowBreak() {
    StopAtNextInt = true;
    Breaking = true;
    return true;
}

WEAK DVDLowCallback DVDLowClearCallback() {
    DVDLowCallback old;
    __DIRegs[1] = 0;
    old = Callback;
    Callback = NULL;

#if IS_CE
    WaitingCoverClose = false;
#endif

    return old;
}

WEAK void __DVDLowSetWAType(u32 type, u32 location) {
    bool enabled;
    enabled = OSDisableInterrupts();
    WorkAroundType = type;
    WorkAroundSeekLocation = location;
    OSRestoreInterrupts(enabled);
}

bool __DVDLowTestAlarm(OSAlarm* alarm) {
    if (alarm == &AlarmForBreak) {
        return true;
    } else if (alarm == &AlarmForTimeout) {
        return true;
    } else {
        return false;
    }
}
