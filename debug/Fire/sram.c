/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\sram.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008E138 -> 0x8008E4A8
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x749C7; // size = 0x10

// size = 0x10, address = 0x800EE768
struct _XL_OBJECTTYPE gClassSram;

typedef struct __anon_0x74AB9 {
    /* 0x0 */ void* pHost;
} __anon_0x74AB9; // size = 0x4

// Range: 0x8008E430 -> 0x8008E4A8
s32 sramCopySRAM(struct __anon_0x74AB9* pSRAM, s32 nOffsetRAM, s32 nOffsetSRAM, s32 nSize) {
    // Parameters
    // struct __anon_0x74AB9* pSRAM; // r1+0x8
    // s32 nOffsetRAM; // r4
    // s32 nOffsetSRAM; // r31
    // s32 nSize; // r1+0x14

    // Local variables
    void* pTarget; // r1+0x18
}

// Range: 0x8008E3B8 -> 0x8008E430
s32 sramTransferSRAM(struct __anon_0x74AB9* pSRAM, s32 nOffsetRAM, s32 nOffsetSRAM, s32 nSize) {
    // Parameters
    // struct __anon_0x74AB9* pSRAM; // r1+0x8
    // s32 nOffsetRAM; // r4
    // s32 nOffsetSRAM; // r31
    // s32 nSize; // r1+0x14

    // Local variables
    void* pTarget; // r1+0x18
}

// Range: 0x8008E388 -> 0x8008E3B8
static s32 sramPut8(u32 nAddress, char* pData) {
    // Parameters
    // u32 nAddress; // r1+0xC
    // char* pData; // r5
}

// Range: 0x8008E358 -> 0x8008E388
static s32 sramPut16(u32 nAddress, s16* pData) {
    // Parameters
    // u32 nAddress; // r1+0xC
    // s16* pData; // r5
}

// Range: 0x8008E328 -> 0x8008E358
static s32 sramPut32(u32 nAddress, s32* pData) {
    // Parameters
    // u32 nAddress; // r1+0xC
    // s32* pData; // r5
}

// Range: 0x8008E2F8 -> 0x8008E328
static s32 sramPut64(u32 nAddress, s64* pData) {
    // Parameters
    // u32 nAddress; // r1+0xC
    // s64* pData; // r5
}

// Range: 0x8008E2C8 -> 0x8008E2F8
static s32 sramGet8(u32 nAddress, char* pData) {
    // Parameters
    // u32 nAddress; // r1+0xC
    // char* pData; // r5
}

// Range: 0x8008E298 -> 0x8008E2C8
static s32 sramGet16(u32 nAddress, s16* pData) {
    // Parameters
    // u32 nAddress; // r1+0xC
    // s16* pData; // r5
}

// Range: 0x8008E268 -> 0x8008E298
static s32 sramGet32(u32 nAddress, s32* pData) {
    // Parameters
    // u32 nAddress; // r1+0xC
    // s32* pData; // r5
}

// Range: 0x8008E238 -> 0x8008E268
static s32 sramGet64(u32 nAddress, s64* pData) {
    // Parameters
    // u32 nAddress; // r1+0xC
    // s64* pData; // r5
}

// Range: 0x8008E138 -> 0x8008E238
s32 sramEvent(struct __anon_0x74AB9* pSram, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x74AB9* pSram; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
