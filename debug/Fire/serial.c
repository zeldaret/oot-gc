/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\serial.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008EE20 -> 0x8008F0F4
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x7869D; // size = 0x10

// size = 0x10, address = 0x800EEA28
struct _XL_OBJECTTYPE gClassSerial;

typedef struct __anon_0x78791 {
    /* 0x0 */ void* pHost;
    /* 0x4 */ int nAddress;
} __anon_0x78791; // size = 0x8

// Range: 0x8008F0EC -> 0x8008F0F4
int serialPut8() {}

// Range: 0x8008F0E4 -> 0x8008F0EC
int serialPut16() {}

// Range: 0x8008EFA4 -> 0x8008F0E4
int serialPut32(struct __anon_0x78791* pSerial, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x78791* pSerial; // r31
    // unsigned int nAddress; // r1+0xC
    // int* pData; // r1+0x10

    // Local variables
    int nSize; // r1+0x18
    void* aData; // r1+0x14
}

// Range: 0x8008EF9C -> 0x8008EFA4
int serialPut64() {}

// Range: 0x8008EF94 -> 0x8008EF9C
int serialGet8() {}

// Range: 0x8008EF8C -> 0x8008EF94
int serialGet16() {}

// Range: 0x8008EF28 -> 0x8008EF8C
int serialGet32(struct __anon_0x78791* pSerial, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x78791* pSerial; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // int* pData; // r1+0x8
}

// Range: 0x8008EF20 -> 0x8008EF28
int serialGet64() {}

// Range: 0x8008EE20 -> 0x8008EF20
int serialEvent(struct __anon_0x78791* pSerial, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x78791* pSerial; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
