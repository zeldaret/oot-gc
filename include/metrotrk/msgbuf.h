#ifndef _METROTRK_MSGBUF_H
#define _METROTRK_MSGBUF_H

#include "dolphin/types.h"
#include "metrotrk/mutex_TRK.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int MessageBufferID;

#define TRKMessageBufferGet(buf, type, offset) (*(type*)(buf->data + offset))
#define kMessageBufferSize 0x800 + 0x80
#define NUM_BUFFERS 3

typedef struct MessageBuffer {
    /* 0x00 */ DSMutex fMutex;
    /* 0x00 */ bool fInUse;
    /* 0x04 */ u32 fLength;
    /* 0x08 */ u32 fPosition;
    /* 0x0C */ u8 fData[kMessageBufferSize];
} MessageBuffer; // size = 0x88C

typedef struct TRKMsgBufs {
    /* 0x00 */ MessageBuffer buffers[NUM_BUFFERS];
} TRKMsgBufs; // size = 0x19A4

DSError TRK_InitializeMessageBuffers(void);
DSError TRKGetFreeBuffer(int*, MessageBuffer**);
MessageBuffer* TRKGetBuffer(int);
void TRKReleaseBuffer(int);
void TRKResetBuffer(MessageBuffer*, u8);
DSError TRKSetBufferPosition(MessageBuffer*, u32);
DSError TRKAppendBuffer(MessageBuffer*, const void*, size_t);
DSError TRKReadBuffer(MessageBuffer*, void*, size_t);
DSError TRKInitializeMessageBuffers(void);

DSError TRKAppendBuffer1_ui16(MessageBuffer* buffer, const u16 data);
DSError TRKAppendBuffer1_ui32(MessageBuffer* buffer, const u32 data);
DSError TRKAppendBuffer1_ui64(MessageBuffer* buffer, const u64 data);
DSError TRKAppendBuffer1_ui128(MessageBuffer* buffer, const u128 data);

DSError TRKAppendBuffer_ui8(MessageBuffer* buffer, const u8* data, int count);
DSError TRKAppendBuffer_ui16(MessageBuffer* buffer, const u16* data, int count);
DSError TRKAppendBuffer_ui32(MessageBuffer* buffer, const u32* data, int count);
DSError TRKAppendBuffer_ui64(MessageBuffer* buffer, const u64* data, int count);
DSError TRKAppendBuffer_ui128(MessageBuffer* buffer, const u128* data, int count);

DSError TRKReadBuffer1_ui8(MessageBuffer* buffer, u8* data);
DSError TRKReadBuffer1_ui16(MessageBuffer* buffer, u16* data);
DSError TRKReadBuffer1_ui32(MessageBuffer* buffer, u32* data);
DSError TRKReadBuffer1_ui64(MessageBuffer* buffer, u64* data);
DSError TRKReadBuffer1_ui128(MessageBuffer* buffer, u128 data);

DSError TRKReadBuffer_ui8(MessageBuffer* buffer, u8* data, int count);
DSError TRKReadBuffer_ui16(MessageBuffer* buffer, u16* data, int count);
DSError TRKReadBuffer_ui32(MessageBuffer* buffer, u32* data, int count);
DSError TRKReadBuffer_ui64(MessageBuffer* buffer, u64* data, int count);
DSError TRKReadBuffer_ui128(MessageBuffer* buffer, u128* data, int count);

static inline DSError TRKAppendBuffer1_ui8(MessageBuffer* buffer, const u8 data) {
    if (buffer->fPosition >= kMessageBufferSize) {
        return kMessageBufferOverflow;
    }

    buffer->fData[buffer->fPosition++] = data;
    buffer->fLength++;
    return kNoError;
}

extern TRKMsgBufs gTRKMsgBufs;

#ifdef __cplusplus
}
#endif

#endif
