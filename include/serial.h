#ifndef _SERIAL_H
#define _SERIAL_H

#include <dolphin/types.h>

// __anon_0x78791
typedef struct Serial {
    /* 0x00 */ void* pHost;
    /* 0x04 */ s32 nAddress;
} Serial; // size = 0x08

s32 serialEvent(Serial* pSerial, s32 nEvent, void* pArgument);

#endif
