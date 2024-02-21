/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\disk.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008D788 -> 0x8008DA1C
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x73A37; // size = 0x10

// size = 0x10, address = 0x800EE748
struct _XL_OBJECTTYPE gClassDisk;

typedef struct __anon_0x73B29 {
    /* 0x0 */ void* pHost;
} __anon_0x73B29; // size = 0x4

// Range: 0x8008DA14 -> 0x8008DA1C
static s32 diskPutROM8() {}

// Range: 0x8008DA0C -> 0x8008DA14
static s32 diskPutROM16() {}

// Range: 0x8008DA04 -> 0x8008DA0C
static s32 diskPutROM32() {}

// Range: 0x8008D9FC -> 0x8008DA04
static s32 diskPutROM64() {}

// Range: 0x8008D9EC -> 0x8008D9FC
static s32 diskGetROM8(char* pData) {
    // Parameters
    // char* pData; // r1+0x8
}

// Range: 0x8008D9DC -> 0x8008D9EC
static s32 diskGetROM16(s16* pData) {
    // Parameters
    // s16* pData; // r1+0x8
}

// Range: 0x8008D9CC -> 0x8008D9DC
static s32 diskGetROM32(s32* pData) {
    // Parameters
    // s32* pData; // r1+0x8
}

// Range: 0x8008D9B8 -> 0x8008D9CC
static s32 diskGetROM64(s64* pData) {
    // Parameters
    // s64* pData; // r1+0x8
}

// Range: 0x8008D9B0 -> 0x8008D9B8
static s32 diskPutDrive8() {}

// Range: 0x8008D9A8 -> 0x8008D9B0
static s32 diskPutDrive16() {}

// Range: 0x8008D97C -> 0x8008D9A8
static s32 diskPutDrive32(u32 nAddress) {
    // Parameters
    // u32 nAddress; // r1+0x4
}

// Range: 0x8008D974 -> 0x8008D97C
static s32 diskPutDrive64() {}

// Range: 0x8008D96C -> 0x8008D974
static s32 diskGetDrive8() {}

// Range: 0x8008D964 -> 0x8008D96C
static s32 diskGetDrive16() {}

// Range: 0x8008D92C -> 0x8008D964
static s32 diskGetDrive32(u32 nAddress, s32* pData) {
    // Parameters
    // u32 nAddress; // r1+0x4
    // s32* pData; // r1+0x8
}

// Range: 0x8008D924 -> 0x8008D92C
static s32 diskGetDrive64() {}

// Range: 0x8008D788 -> 0x8008D924
s32 diskEvent(struct __anon_0x73B29* pDisk, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x73B29* pDisk; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
