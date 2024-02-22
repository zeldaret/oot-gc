#ifndef _SRAM_H
#define _SRAM_H

#include "dolphin.h"

// __anon_0x74AB9
typedef struct Sram {
    void* pHost; // 0x0
} Sram;

s32 sramEvent(Sram* pSram, s32 nEvent, void* pArgument);

#endif
