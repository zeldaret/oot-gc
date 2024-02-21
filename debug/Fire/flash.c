/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\flash.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008DA1C -> 0x8008E138
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x7419C; // size = 0x10

// size = 0x10, address = 0x800EE758
struct _XL_OBJECTTYPE gClassFlash;

typedef struct __anon_0x7428F {
    /* 0x0 */ void* pHost;
    /* 0x4 */ s32 flashCommand;
    /* 0x8 */ char* flashBuffer;
    /* 0xC */ s32 flashStatus;
} __anon_0x7428F; // size = 0x10

// Range: 0x8008DFF4 -> 0x8008E138
s32 flashCopyFLASH(struct __anon_0x7428F* pFLASH, s32 nOffsetRAM, s32 nOffsetFLASH, s32 nSize) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r30
    // s32 nOffsetRAM; // r4
    // s32 nOffsetFLASH; // r31
    // s32 nSize; // r1+0x14

    // Local variables
    void* pTarget; // r1+0x18
}

// Range: 0x8008DEE0 -> 0x8008DFF4
s32 flashTransferFLASH(struct __anon_0x7428F* pFLASH, s32 nOffsetRAM, s32 nSize) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r31
    // s32 nOffsetRAM; // r4
    // s32 nSize; // r1+0x14

    // Local variables
    void* pTarget; // r1+0x18
    s32 i; // r4
}

// Range: 0x8008DED8 -> 0x8008DEE0
static s32 flashPut8() {}

// Range: 0x8008DED0 -> 0x8008DED8
static s32 flashPut16() {}

// Range: 0x8008DC00 -> 0x8008DED0
static s32 flashPut32(struct __anon_0x7428F* pFLASH, s32* pData) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r30
    // s32* pData; // r31

    // Local variables
    s32 i; // r1+0x8
    char buffer[128]; // r1+0x1C
}

// Range: 0x8008DBF8 -> 0x8008DC00
static s32 flashPut64() {}

// Range: 0x8008DBF0 -> 0x8008DBF8
static s32 flashGet8() {}

// Range: 0x8008DBE8 -> 0x8008DBF0
static s32 flashGet16() {}

// Range: 0x8008DB44 -> 0x8008DBE8
static s32 flashGet32(struct __anon_0x7428F* pFLASH, s32* pData) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r1+0x0
    // s32* pData; // r1+0x8
}

// Range: 0x8008DB3C -> 0x8008DB44
static s32 flashGet64() {}

// Range: 0x8008DA1C -> 0x8008DB3C
s32 flashEvent(struct __anon_0x7428F* pFLASH, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
