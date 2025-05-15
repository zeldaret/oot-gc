// #include "metrotrk/notify.h"
#include "metrotrk/msgbuf.h"
#include "metrotrk/support.h"
#include "metrotrk/targimpl.h"

DSError TRKDoNotifyStopped(u8 cmdId) {
    int sp8;
    int spC;
    MessageBuffer* buffer;
    DSError result;

    result = TRK_GetFreeBuffer(&spC, &buffer);

    if (result == kNoError) {
        if (buffer->fPosition >= kMessageBufferSize) {
            result = kMessageBufferOverflow;
        } else {
            result = kNoError;
            buffer->fData[buffer->fPosition++] = cmdId;
            buffer->fLength++;
        }

        if (result == kNoError) {
            if (cmdId == kDSNotifyStopped) {
                TRKTargetAddStopInfo(buffer);
            } else {
                TRKTargetAddExceptionInfo(buffer);
            }
        }

        result = TRK_RequestSend(buffer, &sp8, 2, 3, 1);

        if (result == kNoError) {
            TRK_ReleaseBuffer(sp8);
        }

        TRK_ReleaseBuffer(spC);
    }

    return result;
}
