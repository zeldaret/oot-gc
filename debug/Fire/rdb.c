/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\rdb.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800715D0 -> 0x80071BB8
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x568FE; // size = 0x10

// size = 0x10, address = 0x800EE1B0
struct _XL_OBJECTTYPE gClassRdb;

typedef struct __anon_0x56A0F {
    /* 0x000 */ int nHackCount;
    /* 0x004 */ char szString[256];
    /* 0x104 */ int nIndexString;
    /* 0x108 */ int nAddress;
    /* 0x10C */ void* pHost;
} __anon_0x56A0F; // size = 0x110

// Range: 0x80071BB0 -> 0x80071BB8
static int rdbPut8() {}

// Range: 0x80071BA8 -> 0x80071BB0
static int rdbPut16() {}

// Range: 0x8007172C -> 0x80071BA8
static int rdbPut32(struct __anon_0x56A0F* pRDB, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x56A0F* pRDB; // r3
    // unsigned int nAddress; // r1+0xC
    // int* pData; // r1+0x10

    // Local variables
    int nLength; // r7
    int iCounter; // r5
}

// Range: 0x80071724 -> 0x8007172C
static int rdbPut64() {}

// Range: 0x8007171C -> 0x80071724
static int rdbGet8() {}

// Range: 0x80071714 -> 0x8007171C
static int rdbGet16() {}

// Range: 0x800716E0 -> 0x80071714
static int rdbGet32(unsigned int nAddress) {
    // Parameters
    // unsigned int nAddress; // r1+0x4
}

// Range: 0x800716D8 -> 0x800716E0
static int rdbGet64() {}

// Range: 0x800715D0 -> 0x800716D8
int rdbEvent(struct __anon_0x56A0F* pRDB, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x56A0F* pRDB; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
