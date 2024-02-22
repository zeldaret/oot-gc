#ifndef _FLASH_H
#define _FLASH_H

#include "dolphin.h"

// __anon_0x7428F
typedef struct Flash {
    /* 0x0 */ void* pHost;
    /* 0x4 */ s32 flashCommand;
    /* 0x8 */ char* flashBuffer;
    /* 0xC */ s32 flashStatus;
} Flash; // size = 0x10

#endif
