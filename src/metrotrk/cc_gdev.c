#include "metrotrk/cc_gdev.h"
#include "metrotrk/CircleBuffer.h"
#include "metrotrk/trk.h"

static bool gIsInitialized;
static CircleBuffer gRecvCB;
static u8 gRecvBuf[0x500];

void OutputData(u8* arg0, s32 arg1) {
    s32 var_r5 = 0;

    for (var_r5 = 0; var_r5 < arg1; var_r5++) {}
}

int gdev_cc_initialize(void* flagOut, __OSInterruptHandler handler) {
    DBInitComm((u8**)flagOut, handler);
    CircleBufferInitialize(&gRecvCB, gRecvBuf, sizeof(gRecvBuf));
    return 0;
}

int gdev_cc_shutdown() { return 0; }

int gdev_cc_open() {
    if (gIsInitialized) {
        return GDEV_RESULT_10005;
    } else {
        gIsInitialized = true;
        return 0;
    }
}

int gdev_cc_close() { return 0; }

int gdev_cc_read(u8* dest, int size) {
    int sizeTemp = size;
    u8* destTemp = dest;
    u8 buf[0x500];
    unsigned int r30 = 0;

    if (!gIsInitialized) {
        return GDEV_RESULT_10001;
    }

    while (CBGetBytesAvailableForRead(&gRecvCB) < size) {
        int r29;
        r30 = 0;
        r29 = DBQueryData();
        if (r29 != 0) {
            r30 = DBRead(buf, size);
            if (r30 == 0) {
                CircleBufferWriteBytes(&gRecvCB, buf, r29);
            }
        }
    }

    if (r30 == 0) {
        CircleBufferReadBytes(&gRecvCB, dest, size);
    }

    return r30;
}

int gdev_cc_write(const u8* src, int size) {
    int sizeTemp = size;
    u8* srcTemp = (u8*)src;

    if (!gIsInitialized) {
        return GDEV_RESULT_10001;
    }

    while (sizeTemp > 0) {
        int result = DBWrite(srcTemp, sizeTemp);
        if (result != 0) {
            srcTemp += result;
            sizeTemp -= result;
        } else {
            break;
        }
    }

    return 0;
}

int gdev_cc_pre_continue() {
    DBClose();
    return 0;
}

int gdev_cc_post_stop() {
    DBOpen();
    return 0;
}

int gdev_cc_peek() {
    int r3 = DBQueryData();
    u8 buf[0x500];

    if (r3 <= 0) {
        return 0;
    }

    if (!DBRead(buf, r3)) {
        CircleBufferWriteBytes(&gRecvCB, buf, r3);
    } else {
        return GDEV_RESULT_10009;
    }

    return r3;
}

int gdev_cc_initinterrupts() {
    DBInitInterrupts();
    return 0;
}
