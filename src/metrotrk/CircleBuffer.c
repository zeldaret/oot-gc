#include "metrotrk/CircleBuffer.h"
#include "metrotrk/MWCriticalSection_gc.h"
#include "metrotrk/trk.h"

u32 CBGetBytesAvailableForRead(CircleBuffer* cb) { return cb->mBytesToRead; }

void CircleBufferInitialize(CircleBuffer* cb, u8* buf, u32 size) {
    cb->unk08 = buf;
    cb->unk0C = size;
    cb->unk00 = cb->unk08;
    cb->unk04 = cb->unk08;
    cb->mBytesToRead = 0;
    cb->mBytesToWrite = cb->unk0C;
    MWInitializeCriticalSection(&(cb->mSection));
}

int CircleBufferWriteBytes(CircleBuffer* cb, u8* buf, u32 size) {
    u32 r29;

    if (size > cb->mBytesToWrite) {
        return -1;
    }

    MWEnterCriticalSection(&(cb->mSection));

    r29 = cb->unk0C - (cb->unk04 - cb->unk08);

    if (r29 >= size) {
        memcpy(cb->unk04, buf, size);
        cb->unk04 += size;
    } else {
        memcpy(cb->unk04, buf, r29);
        memcpy(cb->unk08, buf + r29, size - r29);
        cb->unk04 = cb->unk08 + size - r29;
    }

    if (cb->unk0C == cb->unk04 - cb->unk08) {
        cb->unk04 = cb->unk08;
    }

    cb->mBytesToWrite -= size;
    cb->mBytesToRead += size;

    MWExitCriticalSection(&(cb->mSection));

    return 0;
}

int CircleBufferReadBytes(CircleBuffer* cb, u8* buf, u32 size) {
    u32 r29;

    if (size > cb->mBytesToRead) {
        return -1;
    }

    MWEnterCriticalSection(&(cb->mSection));

    r29 = cb->unk0C - (cb->unk00 - cb->unk08);

    if (size < r29) {
        memcpy(buf, cb->unk00, size);
        cb->unk00 += size;
    } else {
        memcpy(buf, cb->unk00, r29);
        memcpy(buf + r29, cb->unk08, size - r29);
        cb->unk00 = cb->unk08 + size - r29;
    }

    if (cb->unk0C == cb->unk00 - cb->unk08) {
        cb->unk00 = cb->unk08;
    }

    cb->mBytesToWrite += size;
    cb->mBytesToRead -= size;

    MWExitCriticalSection(&(cb->mSection));

    return 0;
}
