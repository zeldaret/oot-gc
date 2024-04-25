#ifndef _SERIAL_H
#define _SERIAL_H

#include "dolphin.h"
#include "emulator/xlObject.h"

// __anon_0x78791
typedef struct Serial {
    /* 0x00 */ void* pHost;
    /* 0x04 */ s32 nAddress;
} Serial; // size = 0x08

bool serialPut32(Serial* pSerial, u32 nAddress, s32* pData);
bool serialGet32(Serial* pSerial, u32 nAddress, s32* pData);
bool serialEvent(Serial* pSerial, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassSerial;

#endif
