#ifndef _CODEGCN_H
#define _CODEGCN_H

#include "dolphin/types.h"

// based on how other "gClass" works, we can assume this was the struct used for Code
typedef struct Code {
    /* 0x00 */ void* pHost;
} Code; // size = 0x04

s32 codeEvent(Code* pCode, s32 nEvent, void* pArgument);

#endif
