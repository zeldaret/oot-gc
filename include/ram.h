#ifndef _RAM_H
#define _RAM_H

#include <dolphin/types.h>

// __anon_0x4BFE7
typedef struct Ram {
    /* 0x00 */ void* pHost;
    /* 0x04 */ void* pBuffer;
    /* 0x08 */ u32 nSize;
} Ram; // size = 0x0C

s32 ramGetBuffer(Ram* pRAM, void** ppRAM, u32 nOffset, u32* pnSize);

#endif
