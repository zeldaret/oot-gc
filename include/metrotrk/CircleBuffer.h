#ifndef _METROTRK_CIRCLE_BUFFER_H
#define _METROTRK_CIRCLE_BUFFER_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CircleBuffer {
    /* 0x00 */ u8* unk00;
    /* 0x04 */ u8* unk04;
    /* 0x08 */ u8* unk08;
    /* 0x0C */ u32 unk0C;
    /* 0x10 */ u32 mBytesToRead;
    /* 0x14 */ u32 mBytesToWrite;
    /* 0x18 */ unsigned int mSection;
} CircleBuffer; // size = 0x1C

u32 CBGetBytesAvailableForRead(CircleBuffer* cb);
u32 CBGetBytesAvailableForWrite(CircleBuffer* cb);
void CircleBufferInitialize(CircleBuffer* cb, u8* buf, u32 size);
void CircleBufferTerminate(CircleBuffer* cb);
int CircleBufferWriteBytes(CircleBuffer* cb, u8* buf, u32 size);
int CircleBufferReadBytes(CircleBuffer* cb, u8* buf, u32 size);
#ifdef __cplusplus
}
#endif

#endif
