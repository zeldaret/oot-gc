/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\flash.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008DA1C -> 0x8008E138
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x7419C; // size = 0x10

// size = 0x10, address = 0x800EE758
struct _XL_OBJECTTYPE gClassFlash;

typedef struct __anon_0x7428F {
    /* 0x0 */ void* pHost;
    /* 0x4 */ int flashCommand;
    /* 0x8 */ char* flashBuffer;
    /* 0xC */ int flashStatus;
} __anon_0x7428F; // size = 0x10

// Range: 0x8008DFF4 -> 0x8008E138
int flashCopyFLASH(struct __anon_0x7428F* pFLASH, int nOffsetRAM, int nOffsetFLASH, int nSize) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r30
    // int nOffsetRAM; // r4
    // int nOffsetFLASH; // r31
    // int nSize; // r1+0x14

    // Local variables
    void* pTarget; // r1+0x18
}

// Range: 0x8008DEE0 -> 0x8008DFF4
int flashTransferFLASH(struct __anon_0x7428F* pFLASH, int nOffsetRAM, int nSize) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r31
    // int nOffsetRAM; // r4
    // int nSize; // r1+0x14

    // Local variables
    void* pTarget; // r1+0x18
    int i; // r4
}

// Range: 0x8008DED8 -> 0x8008DEE0
static int flashPut8() {}

// Range: 0x8008DED0 -> 0x8008DED8
static int flashPut16() {}

// Range: 0x8008DC00 -> 0x8008DED0
static int flashPut32(struct __anon_0x7428F* pFLASH, int* pData) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r30
    // int* pData; // r31

    // Local variables
    int i; // r1+0x8
    char buffer[128]; // r1+0x1C
}

// Range: 0x8008DBF8 -> 0x8008DC00
static int flashPut64() {}

// Range: 0x8008DBF0 -> 0x8008DBF8
static int flashGet8() {}

// Range: 0x8008DBE8 -> 0x8008DBF0
static int flashGet16() {}

// Range: 0x8008DB44 -> 0x8008DBE8
static int flashGet32(struct __anon_0x7428F* pFLASH, int* pData) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r1+0x0
    // int* pData; // r1+0x8
}

// Range: 0x8008DB3C -> 0x8008DB44
static int flashGet64() {}

// Range: 0x8008DA1C -> 0x8008DB3C
int flashEvent(struct __anon_0x7428F* pFLASH, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x7428F* pFLASH; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
