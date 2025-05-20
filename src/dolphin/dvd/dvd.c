#include "dolphin/dvd.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os.h"
#include "dolphin/types.h"
#include "string.h"

#include "dolphin/private/__dvd.h"

// required to match
#define DVD_MIN(a, b) (((a) > (b)) ? (b) : (a))

extern OSThreadQueue __DVDThreadQueue;

#if IS_MQ
const char* __DVDVersion = "<< Dolphin SDK - DVD\trelease build: Sep  5 2002 05:34:06 (0x2301) >>";
#else
const char* __DVDVersion = "<< Dolphin SDK - DVD\trelease build: Jul 23 2003 11:27:57 (0x2301) >>";
#endif

static void AlarmHandler(OSAlarm* alarm, OSContext* context);
static void cbForCancelSync(s32 result, DVDCommandBlock* block);
static void cbForStateBusy(u32 p1);
static void cbForStateCheckID1(u32 p1);
static void cbForStateCheckID2(u32 p1);
static void cbForStateCheckID2a(u32 p1);
static void cbForStateCheckID3(u32 p1);
static void cbForStateCoverClosed(u32 p1);
static void cbForStateMotorStopped(u32 p1);
static void cbForStateReadingFST(u32 p1);
static void cbForStateGettingError(u32 p1);
static void cbForStateGoToRetry(u32 p1);
static void cbForUnrecoveredError(u32 p1);
static void cbForUnrecoveredErrorRetry(u32 p1);
static inline void cbForCancelStreamSync(s32 result, DVDCommandBlock* block);
static void cbForGetStreamErrorStatusSync(s32 result, DVDCommandBlock* block);
static void defaultOptionalCommandChecker(DVDCommandBlock* block, DVDLowCallback cb);
static void stateBusy(DVDCommandBlock*);
static void stateCheckID2(DVDCommandBlock*);
static void stateCheckID2a(DVDCommandBlock*);
static void stateCheckID3(DVDCommandBlock*);
static void stateCoverClosed();
static void stateCoverClosed_CMD(DVDCommandBlock*);
static void stateGettingError();
static void stateGoToRetry();
static void stateMotorStopped();
static void stateReady();
static void stateTimeout();

void __DVDInterruptHandler(__OSInterrupt interrupt, OSContext* context);
DVDCommandBlock* __DVDPopWaitingQueue();

typedef void (*stateFunc)(DVDCommandBlock* block);
stateFunc LastState;

static DVDBB2 BB2 ATTRIBUTE_ALIGN(32);
static DVDDiskID CurrDiskID ATTRIBUTE_ALIGN(32);
static DVDCommandBlock* executing;
static DVDDiskID* IDShouldBe;
static OSBootInfo* bootInfo;
static bool autoInvalidation = true;
static volatile bool PauseFlag = false;
static volatile bool PausingFlag = false;
static volatile bool AutoFinishing = false;
static volatile bool FatalErrorFlag = false;
static vu32 CurrCommand;
static vu32 Canceling = false;
static DVDCBCallback CancelCallback;
static vu32 ResumeFromHere = 0;
static vu32 CancelLastError;
static vu32 LastError;
static vs32 NumInternalRetry = 0;
static volatile bool ResetRequired;
static volatile bool FirstTimeInBootrom = false;

static DVDCommandBlock DummyCommandBlock;
static OSAlarm ResetAlarm;

static bool DVDInitialized = false;
static DVDCommandChecker checkOptionalCommand = defaultOptionalCommandChecker;

static void defaultOptionalCommandChecker(DVDCommandBlock* block, DVDLowCallback cb) {}

void DVDInit() {
    if (DVDInitialized) {
        return;
    }

    OSRegisterVersion(__DVDVersion);
    DVDInitialized = true;
    __DVDFSInit();
    __DVDClearWaitingQueue();
    __DVDInitWA();
    bootInfo = (OSBootInfo*)OSPhysicalToCached(0x0000);
    IDShouldBe = &(bootInfo->DVDDiskID);
    __OSSetInterruptHandler(21, __DVDInterruptHandler);
    __OSUnmaskInterrupts(0x400);
    OSInitThreadQueue(&__DVDThreadQueue);
    __DIRegs[DI_STATUS] = 42;
    __DIRegs[DI_COVER_STATUS] = 0;
    if (bootInfo->magic == OS_BOOTINFO_MAGIC_JTAG) {
        OSReport("load fst\n");
        __fstLoad();
    } else if (bootInfo->magic != OS_BOOTINFO_MAGIC) {
        FirstTimeInBootrom = true;
    }
}

static void stateReadingFST() {
    LastState = (stateFunc)stateReadingFST;

    if (bootInfo->FSTMaxLength < BB2.FSTLength) {
        OSPanic("dvd.c", IS_MQ ? 630 : 650, "DVDChangeDisk(): FST in the new disc is too big.   ");
    }

    DVDLowRead(bootInfo->FSTLocation, OSRoundUp32B(BB2.FSTLength), BB2.FSTPosition, cbForStateReadingFST);
}

static void cbForStateReadingFST(u32 p1) {
    DVDCommandBlock* cmdBlock;
    if (p1 == 0x10) {
        executing->state = -1;
        stateTimeout();
    } else if ((p1 & 1) != 0) {
        NumInternalRetry = 0;
        __DVDFSInit();
        cmdBlock = executing;
        executing = &DummyCommandBlock;
        cmdBlock->state = 0;
        if (cmdBlock->callback) {
            (cmdBlock->callback)(0, cmdBlock);
        }
        stateReady();
    } else {
        stateGettingError();
    }
}

static void cbForStateError(u32 intType) {
    DVDCommandBlock* finished;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    __DVDPrintFatalMessage();

    FatalErrorFlag = true;
    finished = executing;
    executing = &DummyCommandBlock;
    if (finished->callback) {
        (finished->callback)(-1, finished);
    }

    if (Canceling) {
        Canceling = false;
        if (CancelCallback) {
            (CancelCallback)(0, finished);
        }
    }

    stateReady();

    return;
}

static inline void stateError(u32 error) {
    __DVDStoreErrorCode(error);
    DVDLowStopMotor(cbForStateError);
}

static void stateTimeout() {
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
}

static void stateGettingError() { DVDLowRequestError(cbForStateGettingError); }

static u32 CategorizeError(u32 error) {
    if (error == 0x20400) {
        LastError = error;
        return 1;
    }

    error &= 0xFFFFFF;

    if ((error == 0x62800) || (error == 0x23A00) || (error == 0xB5A01)) {
        return 0;
    }

    ++NumInternalRetry;
    if (NumInternalRetry == 2) {
        if (error == LastError) {
            LastError = error;
            return 1;
        } else {
            LastError = error;
            return 2;
        }
    } else {
        LastError = error;

        if ((error == 0x31100) || (executing->command == 5)) {
            return 2;
        } else {
            return 3;
        }
    }
}

static inline bool CheckCancel(u32 resume) {
    DVDCommandBlock* finished;

    if (Canceling) {
        ResumeFromHere = resume;
        Canceling = false;

        finished = executing;
        executing = &DummyCommandBlock;

        finished->state = 10;
        if (finished->callback) {
            (*finished->callback)(-3, finished);
        }
        if (CancelCallback) {
            (CancelCallback)(0, finished);
        }
        stateReady();
        return true;
    }
    return false;
}

static void cbForStateGettingError(u32 intType) {
    u32 error;
    u32 status;
    u32 errorCategory;
    u32 resume;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 2) {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    error = __DIRegs[DI_MM_BUF];
    status = error & 0xFF000000;

    errorCategory = CategorizeError(error);

    if (errorCategory == 1) {
        executing->state = -1;
        stateError(error);
        return;
    }

    if ((errorCategory == 2) || (errorCategory == 3)) {
        resume = 0;
    } else {
        if (status == 0x01000000) {
            resume = 4;
        } else if (status == 0x02000000) {
            resume = 6;
        } else if (status == 0x03000000) {
            resume = 3;
        } else {
            resume = 5;
        }
    }

    if (CheckCancel(resume)) {
        return;
    }

    if (errorCategory == 2) {
        __DVDStoreErrorCode(error);
        stateGoToRetry();
        return;
    }

    if (errorCategory == 3) {
        if ((error & 0x00FFFFFF) == 0x00031100) {
            DVDLowSeek(executing->offset, cbForUnrecoveredError);
        } else {
            LastState(executing);
        }
        return;
    }

    if (status == 0x01000000) {
        executing->state = 5;
        stateMotorStopped();
        return;
    } else if (status == 0x02000000) {
        executing->state = 3;
        stateCoverClosed();
        return;
    } else if (status == 0x03000000) {
        executing->state = 4;
        stateMotorStopped();
        return;
    } else {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }
}

static void cbForUnrecoveredError(u32 p1) {
    if (p1 == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (p1 & 1) {
        stateGoToRetry();
        return;
    }

    DVDLowRequestError(cbForUnrecoveredErrorRetry);
}

void cbForUnrecoveredErrorRetry(u32 p1) {
    if (p1 == 0x10) {
        executing->state = -1;
        __DVDStoreErrorCode(0x1234568);
        DVDReset();
        cbForStateError(0);
        return;
    }

    executing->state = -1;

    if ((p1 & 2) != 0) {
        __DVDStoreErrorCode(0x1234567);
        DVDLowStopMotor(cbForStateError);
        return;
    }

    __DVDStoreErrorCode(__DIRegs[DI_MM_BUF]);
    DVDLowStopMotor(cbForStateError);
}

void stateGoToRetry() { DVDLowStopMotor(cbForStateGoToRetry); }

void cbForStateGoToRetry(u32 p1) {
    if (p1 == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (p1 & 2) {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    NumInternalRetry = 0;

    if ((CurrCommand == 4) || (CurrCommand == 5) || (CurrCommand == 13) || (CurrCommand == 15)) {
        ResetRequired = true;
    }

    if (!CheckCancel(2)) {
        executing->state = 11;
        stateMotorStopped();
    }
}

static void stateCheckID() {
    switch (CurrCommand) {
        case 3:
            if (DVDCompareDiskID(&CurrDiskID, executing->id) != false) {
                memcpy(IDShouldBe, &CurrDiskID, sizeof(DVDDiskID));
                executing->state = 1;
                DCInvalidateRange(&BB2, sizeof(DVDBB2));
                LastState = stateCheckID2a;
                stateCheckID2a(executing);
            } else {
                DVDLowStopMotor(cbForStateCheckID1);
            }
            break;
        default:
            if (memcmp(&CurrDiskID, IDShouldBe, sizeof(DVDDiskID)) != 0) {
                DVDLowStopMotor(cbForStateCheckID1);
            } else {
                LastState = stateCheckID3;
                stateCheckID3(executing);
            }
            break;
    }
}

static void stateCheckID3(DVDCommandBlock* cmdBlock) {
    DVDLowAudioBufferConfig(IDShouldBe->streaming, 10, cbForStateCheckID3);
}

static void stateCheckID2a(DVDCommandBlock* cmdBlock) {
    DVDLowAudioBufferConfig(IDShouldBe->streaming, 10, cbForStateCheckID2a);
}

void cbForStateCheckID2a(u32 p1) {
    if (p1 == 0x10) {
        executing->state = -1;
        __DVDStoreErrorCode(0x1234568);
        DVDReset();
        cbForStateError(0);
    } else if ((p1 & 1) != 0) {
        NumInternalRetry = 0;
        stateCheckID2(executing);
    } else {
        DVDLowRequestError(cbForStateGettingError);
    }
}

static void stateCheckID2(DVDCommandBlock* block) {
    DVDLowRead(&BB2, OSRoundUp32B(sizeof(DVDBB2)), 0x420, cbForStateCheckID2);
}

void cbForStateCheckID1(u32 p1) {
    if (p1 == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (p1 & 2) {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    NumInternalRetry = 0;

    if (!CheckCancel(1)) {
        executing->state = 6;
        stateMotorStopped();
    }
}

void cbForStateCheckID2(u32 p1) {
    if (p1 == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (p1 & 1) {
        NumInternalRetry = 0;
        stateReadingFST();

    } else {
        stateGettingError();
    }
}

static void cbForStateCheckID3(u32 p1) {
    if (p1 == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (p1 & 1) {
        NumInternalRetry = 0;

        if (!CheckCancel(0)) {
            executing->state = 1;
            stateBusy(executing);
        }

    } else {
        stateGettingError();
    }
}

static void AlarmHandler(OSAlarm* alarm, OSContext* context) {
    DVDReset();
    DCInvalidateRange(&CurrDiskID, sizeof(DVDDiskID));
    LastState = stateCoverClosed_CMD;
    stateCoverClosed_CMD(executing);
}

static void stateCoverClosed() {
    DVDCommandBlock* cmdBlock;
    switch (CurrCommand) {
        case 4:
        case 5:
        case 13:
        case 15:
            __DVDClearWaitingQueue();
            cmdBlock = executing;
            executing = &DummyCommandBlock;
            if (cmdBlock->callback) {
                (cmdBlock->callback)(-4, cmdBlock);
            }
            stateReady();
            break;
        default:
            DVDReset();
            OSCreateAlarm(&ResetAlarm);
            OSSetAlarm(&ResetAlarm, OSMillisecondsToTicks(1150), AlarmHandler);
            break;
    }
}

void stateCoverClosed_CMD(DVDCommandBlock* cmdBlock) { DVDLowReadDiskID(&CurrDiskID, cbForStateCoverClosed); }

void cbForStateCoverClosed(u32 p1) {
    if (p1 == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (p1 & 1) {
        NumInternalRetry = 0;
        stateCheckID();
    } else {
        stateGettingError();
    }
}

static void stateMotorStopped() { DVDLowWaitCoverClose(cbForStateMotorStopped); }

void cbForStateMotorStopped(u32 p1) {
    __DIRegs[DI_COVER_STATUS] = 0;
    executing->state = 3;
    stateCoverClosed();
}

void stateReady() {
    DVDCommandBlock* finished;

    if (!__DVDCheckWaitingQueue()) {
        executing = (DVDCommandBlock*)NULL;
        return;
    }

    if (PauseFlag) {
        PausingFlag = true;
        executing = (DVDCommandBlock*)NULL;
        return;
    }

    executing = __DVDPopWaitingQueue();

    if (FatalErrorFlag) {
        executing->state = -1;
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback) {
            (finished->callback)(-1, finished);
        }
        stateReady();
        return;
    }

    CurrCommand = executing->command;

    if (ResumeFromHere) {
        switch (ResumeFromHere) {
#if IS_MQ
            case 1:
                executing->state = 1;
                stateCoverClosed();
                break;
#endif
            case 2:
                executing->state = 11;
                stateMotorStopped();
                break;

            case 3:
                executing->state = 4;
                stateMotorStopped();
                break;

            case 4:
                executing->state = 5;
                stateMotorStopped();
                break;
#if IS_CE
            case 1:
#endif
            case 7:
            case 6:
                executing->state = 3;
                stateCoverClosed();
                break;

            case 5:
                executing->state = -1;
                stateError(CancelLastError);
                break;
        }

        ResumeFromHere = 0;

    } else {
        executing->state = 1;
        stateBusy(executing);
    }
}

void stateBusy(DVDCommandBlock* block) {
    DVDCommandBlock* finished;
    LastState = stateBusy;
    switch (block->command) {
        case 5:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            block->currTransferSize = sizeof(DVDDiskID);
            DVDLowReadDiskID(block->addr, cbForStateBusy);
            break;
        case 1:
        case 4:
            if (!block->length) {
                finished = executing;
                executing = &DummyCommandBlock;
                finished->state = 0;
                if (finished->callback) {
                    finished->callback(0, finished);
                }
                stateReady();
            } else {
                __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
                block->currTransferSize = DVD_MIN(block->length - block->transferredSize, 0x80000);
                DVDLowRead((void*)((u8*)block->addr + block->transferredSize), block->currTransferSize,
                           block->offset + block->transferredSize, cbForStateBusy);
            }
            break;

        case 2:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            DVDLowSeek(block->offset, cbForStateBusy);
            break;

        case 3:
            DVDLowStopMotor(cbForStateBusy);
            break;

        case 15:
            DVDLowStopMotor(cbForStateBusy);
            break;

        case 6:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            if (AutoFinishing) {
                executing->currTransferSize = 0;
                DVDLowRequestAudioStatus(0, cbForStateBusy);
            } else {
                executing->currTransferSize = 1;
                DVDLowAudioStream(0, block->length, block->offset, cbForStateBusy);
            }
            break;

        case 7:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            DVDLowAudioStream(0x10000, 0, 0, cbForStateBusy);
            break;

        case 8:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            AutoFinishing = true;
            DVDLowAudioStream(0, 0, 0, cbForStateBusy);
            break;

        case 9:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            DVDLowRequestAudioStatus(0, cbForStateBusy);
            break;

        case 10:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            DVDLowRequestAudioStatus(0x10000, cbForStateBusy);
            break;

        case 11:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            DVDLowRequestAudioStatus(0x20000, cbForStateBusy);
            break;

        case 12:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            DVDLowRequestAudioStatus(0x30000, cbForStateBusy);
            break;

        case 13:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            DVDLowAudioBufferConfig(block->offset, block->length, cbForStateBusy);
            break;

        case 14:
            __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
            block->currTransferSize = sizeof(DVDDriveInfo);
            DVDLowInquiry(block->addr, cbForStateBusy);
            break;

        default:
            checkOptionalCommand(block, cbForStateBusy);
            break;
    }
}

// these will be from one of the stripped functions.
static u32 ImmCommand[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
static char string_DVDChangeDiskAsyncMsg[] = "DVDChangeDiskAsync(): You can't specify NULL to company name.  \n";

static inline bool IsImmCommandWithResult(u32 command) {
    u32 i;

    if (command == 9 || command == 10 || command == 11 || command == 12) {
        return true;
    }

    for (i = 0; i < sizeof(ImmCommand) / sizeof(ImmCommand[0]); i++) {
        if (command == ImmCommand[i]) {
            return true;
        }
    }

    return false;
}

static u32 DmaCommand[] = {0xFFFFFFFF};

static inline bool IsDmaCommand(u32 command) {
    u32 i;

    if (command == 1 || command == 4 || command == 5 || command == 14) {
        return true;
    }

    for (i = 0; i < sizeof(DmaCommand) / sizeof(DmaCommand[0]); i++) {
        if (command == DmaCommand[i]) {
            return true;
        }
    }

    return false;
}

void cbForStateBusy(u32 p1) {
    DVDCommandBlock* finished;

    if (p1 == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if ((CurrCommand == 3) || (CurrCommand == 15)) {
        if (p1 & 2) {
            executing->state = -1;
            stateError(0x1234567);
            return;
        }

        NumInternalRetry = 0;

        if (CurrCommand == 15) {
            ResetRequired = true;
        }

        if (CheckCancel(7)) {
            return;
        }

        executing->state = 7;
        stateMotorStopped();
        return;
    }

    if (IsDmaCommand(CurrCommand)) {
        executing->transferredSize += executing->currTransferSize - __DIRegs[6];
    }

    if (p1 & 8) {
        Canceling = false;
        finished = executing;
        executing = &DummyCommandBlock;

        finished->state = 10;
        if (finished->callback) {
            (*finished->callback)(-3, finished);
        }
        if (CancelCallback) {
            (CancelCallback)(0, finished);
        }
        stateReady();

        return;
    }

    if (p1 & 1) {
        NumInternalRetry = 0;

        if (CheckCancel(0)) {
            return;
        }

        if (IsDmaCommand(CurrCommand)) {
            if (executing->transferredSize != executing->length) {
                stateBusy(executing);
                return;
            }

            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback) {
                (finished->callback)((s32)finished->transferredSize, finished);
            }
            stateReady();
        } else if (IsImmCommandWithResult(CurrCommand)) {
            s32 result;

            if ((CurrCommand == 11) || (CurrCommand == 10)) {
                result = (s32)(__DIRegs[DI_MM_BUF] << 2);
            } else {
                result = (s32)__DIRegs[DI_MM_BUF];
            }
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback) {
                (finished->callback)(result, finished);
            }
            stateReady();
        } else if (CurrCommand == 6) {
            if (executing->currTransferSize == 0) {
                if (__DIRegs[DI_MM_BUF] & 1) {
                    finished = executing;
                    executing = &DummyCommandBlock;

                    finished->state = 9;
                    if (finished->callback) {
                        (finished->callback)(-2, finished);
                    }
                    stateReady();
                } else {
                    AutoFinishing = false;
                    executing->currTransferSize = 1;
                    DVDLowAudioStream(0, executing->length, executing->offset, cbForStateBusy);
                }
            } else {
                finished = executing;
                executing = &DummyCommandBlock;

                finished->state = 0;
                if (finished->callback) {
                    (finished->callback)(0, finished);
                }
                stateReady();
            }
        } else {
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback) {
                (finished->callback)(0, finished);
            }
            stateReady();
        }

    } else {
        if (CurrCommand == 14) {
            executing->state = -1;
            stateError(0x01234567);
            return;
        }

        if ((CurrCommand == 1 || CurrCommand == 4 || CurrCommand == 5 || CurrCommand == 14) &&
            (executing->transferredSize == executing->length)) {

            if (CheckCancel(0)) {
                return;
            }
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback) {
                (finished->callback)((s32)finished->transferredSize, finished);
            }
            stateReady();
            return;
        }

        stateGettingError();
    }
}

static bool issueCommand(s32 prio, DVDCommandBlock* block) {
    bool level;
    bool result;

    if (autoInvalidation &&
        (block->command == 1 || block->command == 4 || block->command == 5 || block->command == 14)) {
        DCInvalidateRange(block->addr, block->length);
    }

    level = OSDisableInterrupts();

    block->state = 2;
    result = __DVDPushWaitingQueue(prio, block);

    if ((executing == (DVDCommandBlock*)NULL) && (PauseFlag == false)) {
        stateReady();
    }

    OSRestoreInterrupts(level);

    return result;
}

bool DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback, s32 prio) {
    bool idle;
    block->command = 1;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(prio, block);
    return idle;
}

#if IS_MM
int DVDSeekAbsAsyncPrio(DVDCommandBlock* block, s32 offset, DVDCBCallback callback, s32 prio) {
    int idle;

    block->command = DVD_COMMAND_SEEK;
    block->offset = offset;
    block->callback = callback;

    idle = issueCommand(prio, block);
    return idle;
}
#endif

bool DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback) {
    bool idle;
    block->command = 4;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    return idle;
}

bool DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* diskID, DVDCBCallback callback) {
    bool idle;
    block->command = 5;
    block->addr = diskID;
    block->length = sizeof(DVDDiskID);
    ;
    block->offset = 0;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    return idle;
}

#if IS_MM
int DVDPrepareStreamAbsAsync(DVDCommandBlock* block, u32 length, u32 offset, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_INITSTREAM;
    block->length = length;
    block->offset = offset;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}
#endif

bool DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    bool idle;
    block->command = 7;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

#if IS_MM
int DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    s32 idle;

    block->command = DVD_COMMAND_STOP_STREAM_AT_END;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

int DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    s32 idle;

    block->command = DVD_COMMAND_REQUEST_AUDIO_ERROR;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

s32 DVDGetStreamErrorStatus(DVDCommandBlock* block) {
    s32 result;
    s32 state;
    bool enabled;
    s32 retVal;

    result = DVDGetStreamErrorStatusAsync(block, cbForGetStreamErrorStatusSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR || state == DVD_STATE_CANCELED) {
            retVal = block->transferredSize;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForGetStreamErrorStatusSync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}
#endif

static inline void cbForCancelStreamSync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}

bool DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info, DVDCBCallback callback) {
    bool idle;

    block->command = 14;
    block->addr = (void*)info;
    block->length = sizeof(DVDDriveInfo);
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);

    return idle;
}

void DVDReset(void) {
    DVDLowReset();
    __DIRegs[DI_STATUS] = 42;
    __DIRegs[DI_COVER_STATUS] = __DIRegs[DI_COVER_STATUS];
    ResetRequired = false;
    ResumeFromHere = 0;
}

s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block) {
    int interrupts = OSDisableInterrupts();
    int result;
    if (block->state == 3) {
        result = 1;
    } else {
        result = block->state;
    }
    OSRestoreInterrupts(interrupts);
    return result;
}

s32 DVDGetDriveStatus() {
    int interrupts = OSDisableInterrupts();
    int result;
    if (FatalErrorFlag != false) {
        result = DVD_STATE_FATAL_ERROR;
    } else {
        if (PausingFlag != false) {
            result = DVD_STATE_PAUSING;
        } else {
            if (executing == NULL) {
                result = DVD_STATE_END;
            } else if (executing == &DummyCommandBlock) {
                result = DVD_STATE_END;
            } else {
                result = DVDGetCommandBlockStatus((struct DVDCommandBlock*)executing);
            }
        }
    }
    OSRestoreInterrupts(interrupts);
    return result;
}

int DVDSetAutoInvalidation(int newValue) {
    int oldValue = autoInvalidation;
    autoInvalidation = newValue;
    return oldValue;
}

void DVDPause() {
    bool level;
    level = OSDisableInterrupts();
    PauseFlag = true;
    if (executing == (DVDCommandBlock*)NULL) {
        PausingFlag = true;
    }
    OSRestoreInterrupts(level);
}

void DVDResume() {
    bool level;
    level = OSDisableInterrupts();
    PauseFlag = false;
    if (PausingFlag) {
        PausingFlag = false;
        stateReady();
    }
    OSRestoreInterrupts(level);
}

bool DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    bool enabled;
    DVDLowCallback old;
#if IS_CE
    u32 tmp;
#endif

    enabled = OSDisableInterrupts();

    switch (block->state) {
        case -1:
        case 0:
        case 10:
            if (callback) {
                (*callback)(0, block);
            }
            break;

        case 1:
            if (Canceling) {
                OSRestoreInterrupts(enabled);
                return false;
            }

            Canceling = true;
            CancelCallback = callback;
            if (block->command == 4 || block->command == 1) {
                DVDLowBreak();
            }
            break;

        case 2:
            __DVDDequeueWaitingQueue(block);
            block->state = 10;
            if (block->callback) {
                (block->callback)(-3, block);
            }
            if (callback) {
                (*callback)(0, block);
            }
            break;

        case 3:
            switch (block->command) {
                case 5:
                case 4:
                case 13:
                case 15:
                    if (callback) {
                        (*callback)(0, block);
                    }
                    break;

                default:
                    if (Canceling) {
                        OSRestoreInterrupts(enabled);
                        return false;
                    }
                    Canceling = true;
                    CancelCallback = callback;
                    break;
            }
            break;

        case 4:
        case 5:
        case 6:
        case 7:
        case 11:
            old = DVDLowClearCallback();
            if (old != cbForStateMotorStopped) {
                OSRestoreInterrupts(enabled);
                return false;
            }

            if (block->state == 4) {
                ResumeFromHere = 3;
            }
            if (block->state == 5) {
                ResumeFromHere = 4;
            }
            if (block->state == 6) {
                ResumeFromHere = 1;
            }
            if (block->state == 11) {
                ResumeFromHere = 2;
            }
            if (block->state == 7) {
                ResumeFromHere = 7;
            }

#if IS_CE
            executing = &DummyCommandBlock;
#endif

            block->state = 10;
            if (block->callback) {
                (block->callback)(-3, block);
            }
            if (callback) {
                (callback)(0, block);
            }
            stateReady();
            break;
    }

    OSRestoreInterrupts(enabled);
    return true;
}

s32 DVDCancel(volatile DVDCommandBlock* block) {
    bool result;
    s32 state;
    u32 command;
    bool enabled;

    result = DVDCancelAsync((void*)block, cbForCancelSync);

    if (result == false) {
        return -1;
    }

    enabled = OSDisableInterrupts();

    for (;;) {
        state = ((volatile DVDCommandBlock*)block)->state;

        if ((state == 0) || (state == -1) || (state == 10)) {
            break;
        }

        if (state == 3) {
            command = ((volatile DVDCommandBlock*)block)->command;

            if ((command == 4) || (command == 5) || (command == 13) || (command == 15)) {
                break;
            }
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return 0;
}

static void cbForCancelSync(s32 result, DVDCommandBlock* block) { OSWakeupThread(&__DVDThreadQueue); }

bool DVDCancelAllAsync(DVDCBCallback callback) {
    bool enabled;
    DVDCommandBlock* p;
    bool retVal;

    enabled = OSDisableInterrupts();
    DVDPause();

    while ((p = __DVDPopWaitingQueue()) != 0) {
        DVDCancelAsync(p, NULL);
    }

    if (executing) {
        retVal = DVDCancelAsync(executing, callback);
    } else {
        retVal = true;
        if (callback) {
            (*callback)(0, NULL);
        }
    }

    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

DVDDiskID* DVDGetCurrentDiskID() { return (DVDDiskID*)OSPhysicalToCached(0); }

bool DVDCheckDisk() {
    bool enabled;
    s32 result;
    s32 state;
    u32 coverReg;

    enabled = OSDisableInterrupts();

    if (FatalErrorFlag) {
        state = -1;
    } else if (PausingFlag) {
        state = 8;
    } else {
        if (executing == (DVDCommandBlock*)NULL) {
            state = 0;
        } else if (executing == &DummyCommandBlock) {
            state = 0;
        } else {
            state = executing->state;
        }
    }

    switch (state) {
        case 1:
        case 9:
        case 10:
        case 2:
            result = true;
            break;

        case -1:
        case 11:
        case 7:
        case 3:
        case 4:
        case 5:
        case 6:
            result = false;
            break;

        case 0:
        case 8:
            coverReg = __DIRegs[1];

            if (((coverReg >> 2) & 1) || (coverReg & 1)) {
                result = false;
            } else {
#if IS_MQ
                result = true;
#else
                if (ResumeFromHere != 0) {
                    result = false;
                } else {
                    result = true;
                }
#endif
            }
    }

    OSRestoreInterrupts(enabled);

    return result;
}

void __DVDPrepareResetAsync(DVDCBCallback callback) {
    bool enabled;

    enabled = OSDisableInterrupts();

    __DVDClearWaitingQueue();

    if (Canceling) {
        CancelCallback = callback;
    } else {
        if (executing) {
            executing->callback = NULL;
        }

        DVDCancelAllAsync(callback);
    }

    OSRestoreInterrupts(enabled);
}

bool __DVDTestAlarm(const OSAlarm* alarm) { return (alarm == &ResetAlarm) ? true : __DVDLowTestAlarm(alarm); }
