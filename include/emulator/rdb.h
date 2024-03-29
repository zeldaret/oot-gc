#ifndef _RDB_H
#define _RDB_H

#include "dolphin.h"
#include "emulator/xlObject.h"

// __anon_0x56A0F
typedef struct Rdb {
    /* 0x000 */ s32 nHackCount;
    /* 0x004 */ char szString[256];
    /* 0x104 */ s32 nIndexString;
    /* 0x108 */ s32 nAddress;
    /* 0x10C */ void* pHost;
} Rdb; // size = 0x110

s32 rdbEvent(Rdb* pRDB, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassRdb;

#endif
