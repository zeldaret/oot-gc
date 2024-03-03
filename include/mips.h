#ifndef _MIPS_H
#define _MIPS_H

#include "dolphin.h"
#include "xlObject.h"

// __anon_0x39384
typedef enum MipsInterruptType {
    MIT_NONE = -1,
    MIT_SP = 0,
    MIT_SI = 1,
    MIT_AI = 2,
    MIT_VI = 3,
    MIT_PI = 4,
    MIT_DP = 5,
} MipsInterruptType;

// __anon_0x7331D
typedef struct Mips {
    /* 0x0 */ s32 nMask;
    /* 0x4 */ s32 nMode;
    /* 0x8 */ void* pHost;
    /* 0xC */ s32 nInterrupt;
} Mips; // size = 0x10

s32 mipsSetInterrupt(Mips* pMips, MipsInterruptType eType);
s32 mipsResetInterrupt(Mips* pMips, MipsInterruptType eType);

s32 mipsPut8(Mips* pMips, u32 nAddress, s8* pData);
s32 mipsPut16(Mips* pMips, u32 nAddress, s16* pData);
s32 mipsPut32(Mips* pMips, u32 nAddress, s32* pData);
s32 mipsPut64(Mips* pMips, u32 nAddress, s64* pData);

s32 mipsGet8(Mips* pMips, u32 nAddress, s8* pData);
s32 mipsGet16(Mips* pMips, u32 nAddress, s16* pData);
s32 mipsGet32(Mips* pMips, u32 nAddress, s32* pData);
s32 mipsGet64(Mips* pMips, u32 nAddress, s64* pData);

s32 mipsEvent(Mips* pMips, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassMips;

#endif
