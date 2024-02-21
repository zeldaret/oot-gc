/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\serial.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008EE20 -> 0x8008F0F4
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x7869D; // size = 0x10

// size = 0x10, address = 0x800EEA28
struct _XL_OBJECTTYPE gClassSerial;

typedef struct __anon_0x78791 {
    /* 0x0 */ void* pHost;
    /* 0x4 */ s32 nAddress;
} __anon_0x78791; // size = 0x8

// Range: 0x8008F0EC -> 0x8008F0F4
s32 serialPut8() {}

// Range: 0x8008F0E4 -> 0x8008F0EC
s32 serialPut16() {}

// Range: 0x8008EFA4 -> 0x8008F0E4
s32 serialPut32(struct __anon_0x78791* pSerial, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x78791* pSerial; // r31
    // u32 nAddress; // r1+0xC
    // s32* pData; // r1+0x10

    // Local variables
    s32 nSize; // r1+0x18
    void* aData; // r1+0x14
}

// Range: 0x8008EF9C -> 0x8008EFA4
s32 serialPut64() {}

// Range: 0x8008EF94 -> 0x8008EF9C
s32 serialGet8() {}

// Range: 0x8008EF8C -> 0x8008EF94
s32 serialGet16() {}

// Range: 0x8008EF28 -> 0x8008EF8C
s32 serialGet32(struct __anon_0x78791* pSerial, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x78791* pSerial; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s32* pData; // r1+0x8
}

// Range: 0x8008EF20 -> 0x8008EF28
s32 serialGet64() {}

// Range: 0x8008EE20 -> 0x8008EF20
s32 serialEvent(struct __anon_0x78791* pSerial, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x78791* pSerial; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
