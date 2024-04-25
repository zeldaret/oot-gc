#ifndef _RAM_H
#define _RAM_H

#include "dolphin.h"
#include "emulator/xlObject.h"

// __anon_0x4BFE7
typedef struct Ram {
    /* 0x00 */ void* pHost;
    /* 0x04 */ void* pBuffer;
    /* 0x08 */ u32 nSize;
} Ram; // size = 0x0C

bool ramGetBuffer(Ram* pRAM, void** ppRAM, u32 nOffset, u32* pnSize);
bool ramWipe(Ram* pRAM);
bool ramSetSize(Ram* pRAM, s32 nSize);
bool ramGetSize(Ram* pRAM, s32* nSize);
bool ramEvent(Ram* pRAM, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassRAM;

#endif
