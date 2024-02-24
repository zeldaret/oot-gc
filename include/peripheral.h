#ifndef _PERIPHERAL_H
#define _PERIPHERAL_H

#include "dolphin.h"

// __anon_0x83D15
typedef struct Peripheral {
    /* 0x00 */ void* pHost;
    /* 0x04 */ s32 nStatus;
    /* 0x08 */ s32 nSizeGet;
    /* 0x0C */ s32 nSizePut;
    /* 0x10 */ s32 nLatency1;
    /* 0x14 */ s32 nLatency2;
    /* 0x18 */ s32 nRelease1;
    /* 0x1C */ s32 nRelease2;
    /* 0x20 */ s32 nSizePage1;
    /* 0x24 */ s32 nSizePage2;
    /* 0x28 */ s32 nAddressRAM;
    /* 0x2C */ s32 nAddressROM;
    /* 0x30 */ s32 nWidthPulse1;
    /* 0x34 */ s32 nWidthPulse2;
} Peripheral; // size = 0x38

s32 peripheralEvent(Peripheral* pPeripheral, s32 nEvent, void* pArgument);

#endif
