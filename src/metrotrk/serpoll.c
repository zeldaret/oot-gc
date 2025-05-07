#include "metrotrk/serpoll.h"
#include "metrotrk/msgbuf.h"
#include "metrotrk/nubevent.h"

void* gTRKInputPendingPtr;
static FramingState gTRKFramingState;

MessageBufferID TRKTestForPacket() {
    u8 payloadBuf[0x880];
    u8 packetBuf[0x40];
    int bufID;
    MessageBuffer* msg;
    MessageBufferID result;

    if (TRKPollUART() <= 0) {
        return -1;
    }

    result = TRK_GetFreeBuffer(&bufID, &msg);
    TRK_SetBufferPosition(msg, 0);

    if (TRKReadUARTN(packetBuf, sizeof(packetBuf)) == kUARTNoError) {
        int readSize;
        TRKAppendBuffer_ui8(msg, packetBuf, sizeof(packetBuf));
        result = bufID;
        readSize = *(u32*)(packetBuf) - sizeof(packetBuf);

        if (readSize > 0) {
            if (TRKReadUARTN(payloadBuf, readSize) == kUARTNoError) {
                TRKAppendBuffer_ui8(msg, payloadBuf, *(u32*)(packetBuf));
            } else {
                TRK_ReleaseBuffer(result);
                result = -1;
            }
        }
    } else {
        TRK_ReleaseBuffer(result);
        result = -1;
    }

    return result;
}

void TRKGetInput() {
    MessageBufferID bufID = TRKTestForPacket();

    if (bufID != -1) {
        TRKGetBuffer(bufID);
        TRKProcessInput(bufID);
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
