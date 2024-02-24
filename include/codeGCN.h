#ifndef _CODEGCN_H
#define _CODEGCN_H

#include "dolphin.h"

// __anon_0x57A1
typedef struct Code {
    /* 0x0 */ s32 nMode;
} Code; // size = 0x4

s32 codeEvent(Code* pCode, s32 nEvent, void* pArgument);

#endif
