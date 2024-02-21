/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\mips.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008D248 -> 0x8008D788
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x7322B; // size = 0x10

// size = 0x10, address = 0x800EE6D0
struct _XL_OBJECTTYPE gClassMips;

typedef struct __anon_0x7331D {
    /* 0x0 */ s32 nMask;
    /* 0x4 */ s32 nMode;
    /* 0x8 */ void* pHost;
    /* 0xC */ s32 nInterrupt;
} __anon_0x7331D; // size = 0x10

typedef enum __anon_0x736C0 {
    MIT_NONE = -1,
    MIT_SP = 0,
    MIT_SI = 1,
    MIT_AI = 2,
    MIT_VI = 3,
    MIT_PI = 4,
    MIT_DP = 5,
} __anon_0x736C0;

// Range: 0x8008D69C -> 0x8008D788
s32 mipsSetInterrupt(struct __anon_0x7331D* pMips, enum __anon_0x736C0 eType) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r1+0x0
    // enum __anon_0x736C0 eType; // r1+0x4

    // Local variables
    s32 nInterrupt; // r5
}

// Range: 0x8008D5F8 -> 0x8008D69C
s32 mipsResetInterrupt(struct __anon_0x7331D* pMips, enum __anon_0x736C0 eType) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r1+0x0
    // enum __anon_0x736C0 eType; // r1+0x4

    // Local variables
    s32 nInterrupt; // r5
}

// Range: 0x8008D5F0 -> 0x8008D5F8
s32 mipsPut8() {}

// Range: 0x8008D5E8 -> 0x8008D5F0
s32 mipsPut16() {}

// Range: 0x8008D3E0 -> 0x8008D5E8
s32 mipsPut32(struct __anon_0x7331D* pMips, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r30
    // u32 nAddress; // r1+0xC
    // s32* pData; // r1+0x10

    // Local variables
    s32 nData; // r31
}

// Range: 0x8008D3D8 -> 0x8008D3E0
s32 mipsPut64() {}

// Range: 0x8008D3D0 -> 0x8008D3D8
s32 mipsGet8() {}

// Range: 0x8008D3C8 -> 0x8008D3D0
s32 mipsGet16() {}

// Range: 0x8008D360 -> 0x8008D3C8
s32 mipsGet32(struct __anon_0x7331D* pMips, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s32* pData; // r1+0x8
}

// Range: 0x8008D358 -> 0x8008D360
s32 mipsGet64() {}

// Range: 0x8008D248 -> 0x8008D358
s32 mipsEvent(struct __anon_0x7331D* pMips, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
