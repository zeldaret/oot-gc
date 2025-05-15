/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\sram.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008E138 -> 0x8008E4A8
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x749C7; // size = 0x10

// size = 0x10, address = 0x800EE768
struct _XL_OBJECTTYPE gClassSram;

typedef struct __anon_0x74AB9 {
    /* 0x0 */ void* pHost;
} __anon_0x74AB9; // size = 0x4

// Range: 0x8008E430 -> 0x8008E4A8
int sramCopySRAM(struct __anon_0x74AB9* pSRAM, int nOffsetRAM, int nOffsetSRAM, int nSize) {
    // Parameters
    // struct __anon_0x74AB9* pSRAM; // r1+0x8
    // int nOffsetRAM; // r4
    // int nOffsetSRAM; // r31
    // int nSize; // r1+0x14

    // Local variables
    void* pTarget; // r1+0x18
}

// Range: 0x8008E3B8 -> 0x8008E430
int sramTransferSRAM(struct __anon_0x74AB9* pSRAM, int nOffsetRAM, int nOffsetSRAM, int nSize) {
    // Parameters
    // struct __anon_0x74AB9* pSRAM; // r1+0x8
    // int nOffsetRAM; // r4
    // int nOffsetSRAM; // r31
    // int nSize; // r1+0x14

    // Local variables
    void* pTarget; // r1+0x18
}

// Range: 0x8008E388 -> 0x8008E3B8
static int sramPut8(unsigned int nAddress, char* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0xC
    // char* pData; // r5
}

// Range: 0x8008E358 -> 0x8008E388
static int sramPut16(unsigned int nAddress, s16* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0xC
    // s16* pData; // r5
}

// Range: 0x8008E328 -> 0x8008E358
static int sramPut32(unsigned int nAddress, int* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0xC
    // int* pData; // r5
}

// Range: 0x8008E2F8 -> 0x8008E328
static int sramPut64(unsigned int nAddress, s64* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0xC
    // s64* pData; // r5
}

// Range: 0x8008E2C8 -> 0x8008E2F8
static int sramGet8(unsigned int nAddress, char* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0xC
    // char* pData; // r5
}

// Range: 0x8008E298 -> 0x8008E2C8
static int sramGet16(unsigned int nAddress, s16* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0xC
    // s16* pData; // r5
}

// Range: 0x8008E268 -> 0x8008E298
static int sramGet32(unsigned int nAddress, int* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0xC
    // int* pData; // r5
}

// Range: 0x8008E238 -> 0x8008E268
static int sramGet64(unsigned int nAddress, s64* pData) {
    // Parameters
    // unsigned int nAddress; // r1+0xC
    // s64* pData; // r5
}

// Range: 0x8008E138 -> 0x8008E238
int sramEvent(struct __anon_0x74AB9* pSram, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x74AB9* pSram; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
