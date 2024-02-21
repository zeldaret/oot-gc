/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\audio.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008E4A8 -> 0x8008E8A0
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x752F4; // size = 0x10

// size = 0x10, address = 0x800EE778
struct _XL_OBJECTTYPE gClassAudio;

typedef struct __anon_0x753E7 {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 bEnable;
    /* 0x08 */ void* pHost;
    /* 0x0C */ s32 nControl;
    /* 0x10 */ s32 nAddress;
    /* 0x14 */ s32 nRateBit;
    /* 0x18 */ s32 nRateDAC;
    /* 0x1C */ s32 nStatus;
} __anon_0x753E7; // size = 0x20

// Range: 0x8008E898 -> 0x8008E8A0
s32 audioPut8() {}

// Range: 0x8008E890 -> 0x8008E898
s32 audioPut16() {}

// Range: 0x8008E748 -> 0x8008E890
s32 audioPut32(struct __anon_0x753E7* pAudio, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r31
    // u32 nAddress; // r1+0xC
    // s32* pData; // r1+0x10

    // Local variables
    void* pBuffer; // r1+0x14
}

// Range: 0x8008E740 -> 0x8008E748
s32 audioPut64() {}

// Range: 0x8008E738 -> 0x8008E740
s32 audioGet8() {}

// Range: 0x8008E730 -> 0x8008E738
s32 audioGet16() {}

// Range: 0x8008E628 -> 0x8008E730
s32 audioGet32(struct __anon_0x753E7* pAudio, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r30
    // u32 nAddress; // r1+0xC
    // s32* pData; // r31
}

// Range: 0x8008E620 -> 0x8008E628
s32 audioGet64() {}

// Range: 0x8008E5C8 -> 0x8008E620
s32 audioEnable(struct __anon_0x753E7* pAudio, s32 bEnable) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r3
    // s32 bEnable; // r1+0xC
}

// Range: 0x8008E4A8 -> 0x8008E5C8
s32 audioEvent(struct __anon_0x753E7* pAudio, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
