/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\ram.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8006CD98 -> 0x8006D3AC
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x4BEF6; // size = 0x10

// size = 0x10, address = 0x800ED6C8
struct _XL_OBJECTTYPE gClassRAM;

typedef struct __anon_0x4BFE7 {
    /* 0x0 */ void* pHost;
    /* 0x4 */ void* pBuffer;
    /* 0x8 */ u32 nSize;
} __anon_0x4BFE7; // size = 0xC

// Range: 0x8006D3A4 -> 0x8006D3AC
static s32 ramPutControl8() {}

// Range: 0x8006D39C -> 0x8006D3A4
static s32 ramPutControl16() {}

// Range: 0x8006D368 -> 0x8006D39C
static s32 ramPutControl32(u32 nAddress) {
    // Parameters
    // u32 nAddress; // r1+0x4
}

// Range: 0x8006D360 -> 0x8006D368
static s32 ramPutControl64() {}

// Range: 0x8006D358 -> 0x8006D360
static s32 ramGetControl8() {}

// Range: 0x8006D350 -> 0x8006D358
static s32 ramGetControl16() {}

// Range: 0x8006D31C -> 0x8006D350
static s32 ramGetControl32(u32 nAddress) {
    // Parameters
    // u32 nAddress; // r1+0x4
}

// Range: 0x8006D314 -> 0x8006D31C
static s32 ramGetControl64() {}

// Range: 0x8006D30C -> 0x8006D314
static s32 ramPutRI8() {}

// Range: 0x8006D304 -> 0x8006D30C
static s32 ramPutRI16() {}

// Range: 0x8006D2D0 -> 0x8006D304
static s32 ramPutRI32(u32 nAddress) {
    // Parameters
    // u32 nAddress; // r1+0x4
}

// Range: 0x8006D2C8 -> 0x8006D2D0
static s32 ramPutRI64() {}

// Range: 0x8006D2C0 -> 0x8006D2C8
static s32 ramGetRI8() {}

// Range: 0x8006D2B8 -> 0x8006D2C0
static s32 ramGetRI16() {}

// Range: 0x8006D284 -> 0x8006D2B8
static s32 ramGetRI32(u32 nAddress) {
    // Parameters
    // u32 nAddress; // r1+0x4
}

// Range: 0x8006D27C -> 0x8006D284
static s32 ramGetRI64() {}

// Range: 0x8006D258 -> 0x8006D27C
static s32 ramPut8(struct __anon_0x4BFE7* pRAM, u32 nAddress, char* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32 nAddress; // r6
    // char* pData; // r1+0x8
}

// Range: 0x8006D230 -> 0x8006D258
static s32 ramPut16(struct __anon_0x4BFE7* pRAM, u32 nAddress, s16* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32 nAddress; // r6
    // s16* pData; // r1+0x8
}

// Range: 0x8006D208 -> 0x8006D230
static s32 ramPut32(struct __anon_0x4BFE7* pRAM, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32 nAddress; // r6
    // s32* pData; // r1+0x8
}

// Range: 0x8006D1D4 -> 0x8006D208
static s32 ramPut64(struct __anon_0x4BFE7* pRAM, u32 nAddress, s64* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32 nAddress; // r4
    // s64* pData; // r1+0x8
}

// Range: 0x8006D1A4 -> 0x8006D1D4
static s32 ramGet8(struct __anon_0x4BFE7* pRAM, u32 nAddress, char* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32 nAddress; // r4
    // char* pData; // r1+0x8
}

// Range: 0x8006D170 -> 0x8006D1A4
static s32 ramGet16(struct __anon_0x4BFE7* pRAM, u32 nAddress, s16* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32 nAddress; // r4
    // s16* pData; // r1+0x8
}

// Range: 0x8006D13C -> 0x8006D170
static s32 ramGet32(struct __anon_0x4BFE7* pRAM, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32 nAddress; // r4
    // s32* pData; // r1+0x8
}

// Range: 0x8006D0F8 -> 0x8006D13C
static s32 ramGet64(struct __anon_0x4BFE7* pRAM, u32 nAddress, s64* pData) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32 nAddress; // r4
    // s64* pData; // r1+0x8
}

// Range: 0x8006D0A0 -> 0x8006D0F8
s32 ramGetBuffer(struct __anon_0x4BFE7* pRAM, void* ppRAM, u32 nOffset, u32* pnSize) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // void* ppRAM; // r1+0x4
    // u32 nOffset; // r5
    // u32* pnSize; // r1+0xC
}

// Range: 0x8006D058 -> 0x8006D0A0
s32 ramWipe(struct __anon_0x4BFE7* pRAM) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r3
}

// Range: 0x8006CFE8 -> 0x8006D058
s32 ramSetSize(struct __anon_0x4BFE7* pRAM, u32 nSize) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r30
    // u32 nSize; // r31
}

// Range: 0x8006CFD0 -> 0x8006CFE8
s32 ramGetSize(struct __anon_0x4BFE7* pRAM, u32* pnSize) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r1+0x0
    // u32* pnSize; // r1+0x4
}

// Range: 0x8006CD98 -> 0x8006CFD0
s32 ramEvent(struct __anon_0x4BFE7* pRAM, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x4BFE7* pRAM; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
