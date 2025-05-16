/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\ram.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8006CD98 -> 0x8006D3AC
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x4BEF6; // size = 0x10

// size = 0x10, address = 0x800ED6C8
struct _XL_OBJECTTYPE gClassRAM;

typedef struct __anon_0x4BFE7 {
    /* 0x0 */ void* pHost;
    /* 0x4 */ void* pBuffer;
    /* 0x8 */ unsigned int nSize;
} __anon_0x4BFE7; // size = 0xC

// Range: 0x8006D3A4 -> 0x8006D3AC
static int ramPutControl8() {}

// Range: 0x8006D39C -> 0x8006D3A4
static int ramPutControl16() {}

// Range: 0x8006D368 -> 0x8006D39C
static int ramPutControl32(unsigned int nAddress) {
    // Parameters
    // unsigned int nAddress; // r1+0x4
}

// Range: 0x8006D360 -> 0x8006D368
static int ramPutControl64() {}

// Range: 0x8006D358 -> 0x8006D360
static int ramGetControl8() {}

// Range: 0x8006D350 -> 0x8006D358
static int ramGetControl16() {}

// Range: 0x8006D31C -> 0x8006D350
static int ramGetControl32(unsigned int nAddress) {
    // Parameters
    // unsigned int nAddress; // r1+0x4
}

// Range: 0x8006D314 -> 0x8006D31C
static int ramGetControl64() {}

// Range: 0x8006D30C -> 0x8006D314
static int ramPutRI8() {}

// Range: 0x8006D304 -> 0x8006D30C
static int ramPutRI16() {}

// Range: 0x8006D2D0 -> 0x8006D304
static int ramPutRI32(unsigned int nAddress) {
    // Parameters
    // unsigned int nAddress; // r1+0x4
}

// Range: 0x8006D2C8 -> 0x8006D2D0
static int ramPutRI64() {}

// Range: 0x8006D2C0 -> 0x8006D2C8
static int ramGetRI8() {}

// Range: 0x8006D2B8 -> 0x8006D2C0
static int ramGetRI16() {}

// Range: 0x8006D284 -> 0x8006D2B8
static int ramGetRI32(unsigned int nAddress) {
    // Parameters
    // unsigned int nAddress; // r1+0x4
}

// Range: 0x8006D27C -> 0x8006D284
static int ramGetRI64() {}

// Range: 0x8006D258 -> 0x8006D27C
static int ramPut8(struct __anon_0x4BFE7* pRAM, unsigned int nAddress, char* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int nAddress; // r6
    // char* pData; // r1+0x8
}

// Range: 0x8006D230 -> 0x8006D258
static int ramPut16(struct __anon_0x4BFE7* pRAM, unsigned int nAddress, s16* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int nAddress; // r6
    // s16* pData; // r1+0x8
}

// Range: 0x8006D208 -> 0x8006D230
static int ramPut32(struct __anon_0x4BFE7* pRAM, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int nAddress; // r6
    // int* pData; // r1+0x8
}

// Range: 0x8006D1D4 -> 0x8006D208
static int ramPut64(struct __anon_0x4BFE7* pRAM, unsigned int nAddress, s64* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int nAddress; // r4
    // s64* pData; // r1+0x8
}

// Range: 0x8006D1A4 -> 0x8006D1D4
static int ramGet8(struct __anon_0x4BFE7* pRAM, unsigned int nAddress, char* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int nAddress; // r4
    // char* pData; // r1+0x8
}

// Range: 0x8006D170 -> 0x8006D1A4
static int ramGet16(struct __anon_0x4BFE7* pRAM, unsigned int nAddress, s16* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int nAddress; // r4
    // s16* pData; // r1+0x8
}

// Range: 0x8006D13C -> 0x8006D170
static int ramGet32(struct __anon_0x4BFE7* pRAM, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int nAddress; // r4
    // int* pData; // r1+0x8
}

// Range: 0x8006D0F8 -> 0x8006D13C
static int ramGet64(struct __anon_0x4BFE7* pRAM, unsigned int nAddress, s64* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int nAddress; // r4
    // s64* pData; // r1+0x8
}

// Range: 0x8006D0A0 -> 0x8006D0F8
int ramGetBuffer(struct __anon_0x4BFE7* pRAM, void* ppRAM, unsigned int nOffset, unsigned int* pnSize) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // void* ppRAM; // r1+0x4
    // unsigned int nOffset; // r5
    // unsigned int* pnSize; // r1+0xC
}

// Range: 0x8006D058 -> 0x8006D0A0
int ramWipe(struct __anon_0x4BFE7* pRAM) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r3
}

// Range: 0x8006CFE8 -> 0x8006D058
int ramSetSize(struct __anon_0x4BFE7* pRAM, unsigned int nSize) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r30
    // unsigned int nSize; // r31
}

// Range: 0x8006CFD0 -> 0x8006CFE8
int ramGetSize(struct __anon_0x4BFE7* pRAM, unsigned int* pnSize) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // unsigned int* pnSize; // r1+0x4
}

// Range: 0x8006CD98 -> 0x8006CFD0
int ramEvent(struct __anon_0x4BFE7* pRAM, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
