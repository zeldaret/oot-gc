/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\audio.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008E4A8 -> 0x8008E8A0
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x752F4; // size = 0x10

// size = 0x10, address = 0x800EE778
struct _XL_OBJECTTYPE gClassAudio;

typedef struct __anon_0x753E7 {
    /* 0x00 */ int nSize;
    /* 0x04 */ int bEnable;
    /* 0x08 */ void* pHost;
    /* 0x0C */ int nControl;
    /* 0x10 */ int nAddress;
    /* 0x14 */ int nRateBit;
    /* 0x18 */ int nRateDAC;
    /* 0x1C */ int nStatus;
} __anon_0x753E7; // size = 0x20

// Range: 0x8008E898 -> 0x8008E8A0
int audioPut8() {}

// Range: 0x8008E890 -> 0x8008E898
int audioPut16() {}

// Range: 0x8008E748 -> 0x8008E890
int audioPut32(struct __anon_0x753E7* pAudio, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r31
    // unsigned int nAddress; // r1+0xC
    // int* pData; // r1+0x10

    // Local variables
    void* pBuffer; // r1+0x14
}

// Range: 0x8008E740 -> 0x8008E748
int audioPut64() {}

// Range: 0x8008E738 -> 0x8008E740
int audioGet8() {}

// Range: 0x8008E730 -> 0x8008E738
int audioGet16() {}

// Range: 0x8008E628 -> 0x8008E730
int audioGet32(struct __anon_0x753E7* pAudio, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r30
    // unsigned int nAddress; // r1+0xC
    // int* pData; // r31
}

// Range: 0x8008E620 -> 0x8008E628
int audioGet64() {}

// Range: 0x8008E5C8 -> 0x8008E620
int audioEnable(struct __anon_0x753E7* pAudio, int bEnable) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r3
    // int bEnable; // r1+0xC
}

// Range: 0x8008E4A8 -> 0x8008E5C8
int audioEvent(struct __anon_0x753E7* pAudio, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
