#include "metrotrk/serpoll.h"
#include "metrotrk/msgbuf.h"
#include "metrotrk/msghndlr.h"
#include "metrotrk/nubevent.h"
#include "metrotrk/dolphin_trk_glue.h"

void* gTRKInputPendingPtr;
static FramingState gTRKFramingState;

MessageBufferID TRKTestForPacket(void) {
    int bytes;
    int batch;
    int err;
    MessageBuffer* b;
    int id;

    bytes = TRKPollUART();

    if (bytes > 0) {
        TRKGetFreeBuffer(&id, &b);
        if (bytes > 0x880) {
            for (; bytes > 0; bytes -= batch) {
                batch = bytes > 0x880 ? 0x880 : bytes;
                TRK_ReadUARTN(b->fData, batch);
            }
            TRKStandardACK(b, 0xff, 6);
        } else {
            err = TRK_ReadUARTN(b->fData, bytes);
            if (err == 0) {
                b->fLength = bytes;
                return id;
            }
        }
    }

    if (id != -1) {
        TRKReleaseBuffer(id);
    }
    return -1;
}

void TRKGetInput() {
    MessageBuffer* msgbuffer;
    MessageBufferID bufID;
    u8 command;

    bufID = TRKTestForPacket();

    if (bufID != -1) {
        msgbuffer = TRKGetBuffer(bufID);
        TRKSetBufferPosition(msgbuffer, 0);
        TRKReadBuffer1_ui8(msgbuffer, &command);
        if (command < 0x80) {
            TRKProcessInput(bufID);
        } else {
            TRKReleaseBuffer(bufID);
        }
    }
}

void TRKProcessInput(MessageBufferID bufID) {
    NubEvent event;

    TRKConstructEvent(&event, 2);
    event.fMessageBufferID = bufID;
    gTRKFramingState.fBufferID = -1;
    TRKPostEvent(&event);
}

DSError TRKInitializeSerialHandler() {
    gTRKFramingState.fBufferID = -1;
    gTRKFramingState.fReceiveState = 0;
    gTRKFramingState.fEscape = 0;
    return kNoError;
}

DSError TRKTerminateSerialHandler() { return kNoError; }
