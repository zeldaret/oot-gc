#ifndef _RDP_H
#define _RDP_H

#include "dolphin.h"
#include "emulator/rsp.h"
#include "emulator/xlObject.h"

typedef struct Rdp {
    /* 0x00 */ s32 nBIST;
    /* 0x04 */ s32 nStatus;
    /* 0x08 */ void* pHost;
    /* 0x0C */ s32 nModeTest;
    /* 0x10 */ s32 nDataTest;
    /* 0x14 */ s32 nAddressTest;
    /* 0x18 */ s32 nAddress0;
    /* 0x1C */ s32 nAddress1;
    /* 0x20 */ s32 nClock;
    /* 0x24 */ s32 nClockCmd;
    /* 0x28 */ s32 nClockPipe;
    /* 0x2C */ s32 nClockTMEM;
} Rdp; // size = 0x30

bool rdpParseGBI(Rdp* pRDP, u64** ppnGBI, RspUCodeType eTypeUCode);
bool rdpEvent(Rdp* pRDP, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassRDP;

#endif
