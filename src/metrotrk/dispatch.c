#include "metrotrk/dispatch.h"
#include "metrotrk/msgcmd.h"
#include "metrotrk/msghndlr.h"

u32 gTRKDispatchTableSize;

DSError TRKDoCPUType(MessageBuffer* buf);
DSError TRKDoUnsupported(MessageBuffer* buf);
DSError TRKDoFlushCache(MessageBuffer* buf);

typedef DSError (*DispatchCallback)(MessageBuffer* buf);

DispatchCallback gTRKDispatchTable[] = {
    TRKDoUnsupported,
    TRKDoConnect,
    TRKDoDisconnect,
    TRKDoReset,
    TRKDoVersions,
    TRKDoSupportMask,
    TRKDoCPUType,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoReadMemory,
    TRKDoWriteMemory,
    TRKDoReadRegisters,
    TRKDoWriteRegisters,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoFlushCache,
    TRKDoUnsupported,
    TRKDoContinue,
    TRKDoStep,
    TRKDoStop,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    NULL,
    NULL,
};

DSError TRKInitializeDispatcher(void) {
    gTRKDispatchTableSize = ARRAY_COUNT(gTRKDispatchTable) - 2;
    return kNoError;
}

DSError TRKDispatchMessage(MessageBuffer* buffer) {
    DSError result = kDispatchError;
    u8 command;

    TRKSetBufferPosition(buffer, 0);
    TRKReadBuffer1_ui8(buffer, &command);

    if (command < gTRKDispatchTableSize) {
        result = gTRKDispatchTable[command](buffer);
    }

    return result;
}
