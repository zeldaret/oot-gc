/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\mips.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008D248 -> 0x8008D788
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x7322B; // size = 0x10

// size = 0x10, address = 0x800EE6D0
struct _XL_OBJECTTYPE gClassMips;

typedef struct __anon_0x7331D {
    /* 0x0 */ int nMask;
    /* 0x4 */ int nMode;
    /* 0x8 */ void* pHost;
    /* 0xC */ int nInterrupt;
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
int mipsSetInterrupt(struct __anon_0x7331D* pMips, enum __anon_0x736C0 eType) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r1+0x0
    // enum __anon_0x736C0 eType; // r1+0x4

    // Local variables
    int nInterrupt; // r5
}

// Range: 0x8008D5F8 -> 0x8008D69C
int mipsResetInterrupt(struct __anon_0x7331D* pMips, enum __anon_0x736C0 eType) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r1+0x0
    // enum __anon_0x736C0 eType; // r1+0x4

    // Local variables
    int nInterrupt; // r5
}

// Range: 0x8008D5F0 -> 0x8008D5F8
int mipsPut8() {}

// Range: 0x8008D5E8 -> 0x8008D5F0
int mipsPut16() {}

// Range: 0x8008D3E0 -> 0x8008D5E8
int mipsPut32(struct __anon_0x7331D* pMips, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r30
    // unsigned int nAddress; // r1+0xC
    // int* pData; // r1+0x10

    // Local variables
    int nData; // r31
}

// Range: 0x8008D3D8 -> 0x8008D3E0
int mipsPut64() {}

// Range: 0x8008D3D0 -> 0x8008D3D8
int mipsGet8() {}

// Range: 0x8008D3C8 -> 0x8008D3D0
int mipsGet16() {}

// Range: 0x8008D360 -> 0x8008D3C8
int mipsGet32(struct __anon_0x7331D* pMips, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // int* pData; // r1+0x8
}

// Range: 0x8008D358 -> 0x8008D360
int mipsGet64() {}

// Range: 0x8008D248 -> 0x8008D358
int mipsEvent(struct __anon_0x7331D* pMips, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x7331D* pMips; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
