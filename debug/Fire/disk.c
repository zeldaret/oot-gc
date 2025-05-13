/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\disk.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008D788 -> 0x8008DA1C
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x73A37; // size = 0x10

// size = 0x10, address = 0x800EE748
struct _XL_OBJECTTYPE gClassDisk;

typedef struct __anon_0x73B29 {
    /* 0x0 */ void* pHost;
} __anon_0x73B29; // size = 0x4

// Range: 0x8008DA14 -> 0x8008DA1C
static int diskPutROM8() {}

// Range: 0x8008DA0C -> 0x8008DA14
static int diskPutROM16() {}

// Range: 0x8008DA04 -> 0x8008DA0C
static int diskPutROM32() {}

// Range: 0x8008D9FC -> 0x8008DA04
static int diskPutROM64() {}

// Range: 0x8008D9EC -> 0x8008D9FC
static int diskGetROM8(char* pData) {
    // Parameters
    // char* pData; // r1+0x8
}

// Range: 0x8008D9DC -> 0x8008D9EC
static int diskGetROM16(s16* pData) {
    // Parameters
    // s16* pData; // r1+0x8
}

// Range: 0x8008D9CC -> 0x8008D9DC
static int diskGetROM32(int* pData) {
    // Parameters
    // int* pData; // r1+0x8
}

// Range: 0x8008D9B8 -> 0x8008D9CC
static int diskGetROM64(s64* pData) {
    // Parameters
    // s64* pData; // r1+0x8
}

// Range: 0x8008D9B0 -> 0x8008D9B8
static int diskPutDrive8() {}

// Range: 0x8008D9A8 -> 0x8008D9B0
static int diskPutDrive16() {}

// Range: 0x8008D97C -> 0x8008D9A8
static int diskPutDrive32(unsigned int nAddress) {
    // Parameters
    // unsigned int nAddress; // r1+0x4
}

// Range: 0x8008D974 -> 0x8008D97C
static int diskPutDrive64() {}

// Range: 0x8008D96C -> 0x8008D974
static int diskGetDrive8() {}

// Range: 0x8008D964 -> 0x8008D96C
static int diskGetDrive16() {}

// Range: 0x8008D92C -> 0x8008D964
static int diskGetDrive32(unsigned int nAddress, int* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0x4
    // int* pData; // r1+0x8
}

// Range: 0x8008D924 -> 0x8008D92C
static int diskGetDrive64() {}

// Range: 0x8008D788 -> 0x8008D924
int diskEvent(struct __anon_0x73B29* pDisk, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x73B29* pDisk; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
