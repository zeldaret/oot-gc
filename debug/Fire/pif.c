/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\pif.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8006BE68 -> 0x8006CD98
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x4A7FA; // size = 0x10

// size = 0x10, address = 0x800ED6B8
struct _XL_OBJECTTYPE gClassPIF;

typedef struct __anon_0x4A974 {
    /* 0x00 */ void* pROM;
    /* 0x04 */ void* pRAM;
    /* 0x08 */ void* pHost;
    /* 0x0C */ u16 controllerType[5];
    /* 0x16 */ char controllerStatus[5];
    /* 0x1C */ enum __anon_0x4B3FE eControllerType[5];
} __anon_0x4A974; // size = 0x30

typedef enum __anon_0x4B3FE {
    CT_NONE = 0,
    CT_CONTROLLER = 1,
    CT_CONTROLLER_W_PAK = 2,
    CT_CONTROLLER_W_RPAK = 3,
    CT_MOUSE = 4,
    CT_VOICE = 5,
    CT_4K = 6,
    CT_16K = 7,
    CT_COUNT = 8,
} __anon_0x4B3FE;

// Erased
static int pifIdCheckSum(u16* ptr, u16* csum, u16* icsum) {
    // Parameters
    // u16* ptr; // r4
    // u16* csum; // r1+0x8
    // u16* icsum; // r1+0xC

    // Local variables
    u16 data; // r7
    unsigned int j; // r1+0x0
}

// Range: 0x8006CC74 -> 0x8006CD98
int pifReadRumble(u16 address, u8* data) {
    // Parameters
    // u16 address; // r1+0x8
    // u8* data; // r1+0xC

    // Local variables
    int i; // r1+0x0
}

// Range: 0x8006CC1C -> 0x8006CC74
int pifWriteRumble(int channel, u16 address, u8* data) {
    // Parameters
    // int channel; // r4
    // u16 address; // r1+0x10
    // u8* data; // r1+0x14
}

// Range: 0x8006CAA4 -> 0x8006CC1C
static u8 pifContDataCrc(u8* data) {
    // Parameters
    // u8* data; // r4

    // Local variables
    unsigned int temp; // r3
    unsigned int i; // r5
    unsigned int j; // r6
}

// Range: 0x8006C994 -> 0x8006CAA4
int pifSetControllerType(struct __anon_0x4A974* pPIF, int channel, enum __anon_0x4B3FE type) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r29
    // int channel; // r30
    // enum __anon_0x4B3FE type; // r31
}

// Range: 0x8006C97C -> 0x8006C994
int pifGetEControllerType(struct __anon_0x4A974* pPIF, int channel, enum __anon_0x4B3FE* type) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // int channel; // r1+0x4
    // enum __anon_0x4B3FE* type; // r1+0x8
}

// Range: 0x8006C918 -> 0x8006C97C
int pifSetEEPROMType(struct __anon_0x4A974* pPIF, enum __anon_0x4B3FE type) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // enum __anon_0x4B3FE type; // r1+0x4
}

// Erased
static int pifGetControllerInput(int channel, unsigned int* controllerInput) {
    // Parameters
    // int channel; // r4
    // unsigned int* controllerInput; // r5
}

// Erased
static int pifGetControllerType(struct __anon_0x4A974* pPIF, int channel, u16* type, char* status) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // int channel; // r1+0x4
    // u16* type; // r1+0x8
    // char* status; // r1+0xC

    // Local variables
    enum __anon_0x4B3FE eType; // r1+0x0
}

// Range: 0x8006C8D4 -> 0x8006C918
int pifGetEEPROMSize(struct __anon_0x4A974* pPIF, unsigned int* size) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int* size; // r1+0x4
}

// Erased
static int pifQueryController(struct __anon_0x4A974* pPIF, u8* buffer, u8* prx, int channel) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // u8* buffer; // r1+0x4
    // u8* prx; // r1+0xC
    // int channel; // r1+0x10
}

// Erased
static int pifReadController(struct __anon_0x4A974* pPIF, u8* buffer, u8* prx, int channel) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x8
    // u8* buffer; // r4
    // u8* prx; // r1+0x14
    // int channel; // r7

    // Local variables
    enum __anon_0x4B3FE type; // r1+0x8
}

// Range: 0x8006C8B0 -> 0x8006C8D4
static int pifPut8(struct __anon_0x4A974* pPIF, unsigned int nAddress, char* pData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // char* pData; // r1+0x8
}

// Range: 0x8006C888 -> 0x8006C8B0
static int pifPut16(struct __anon_0x4A974* pPIF, unsigned int nAddress, s16* pData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // s16* pData; // r1+0x8
}

// Range: 0x8006C860 -> 0x8006C888
static int pifPut32(struct __anon_0x4A974* pPIF, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // int* pData; // r1+0x8
}

// Range: 0x8006C82C -> 0x8006C860
static int pifPut64(struct __anon_0x4A974* pPIF, unsigned int nAddress, s64* pData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // s64* pData; // r1+0x8
}

// Range: 0x8006C7F8 -> 0x8006C82C
static int pifGet8(struct __anon_0x4A974* pPIF, unsigned int nAddress, char* pData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // char* pData; // r1+0x8
}

// Range: 0x8006C7BC -> 0x8006C7F8
static int pifGet16(struct __anon_0x4A974* pPIF, unsigned int nAddress, s16* pData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // s16* pData; // r1+0x8
}

// Range: 0x8006C780 -> 0x8006C7BC
static int pifGet32(struct __anon_0x4A974* pPIF, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // int* pData; // r1+0x8
}

// Range: 0x8006C72C -> 0x8006C780
static int pifGet64(struct __anon_0x4A974* pPIF, unsigned int nAddress, s64* pData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // s64* pData; // r1+0x8
}

// Range: 0x8006C488 -> 0x8006C72C
int pifExecuteCommand(struct __anon_0x4A974* pPIF, u8* buffer, u8* prx, int channel) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r30
    // u8* buffer; // r31
    // u8* prx; // r1+0x14
    // int channel; // r7
}

// Range: 0x8006C2F8 -> 0x8006C488
int pifProcessInputData(struct __anon_0x4A974* pPIF) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r30

    // Local variables
    u8* prx; // r6
    u8* ptx; // r5
    int iData; // r29
    int channel; // r31
}

// Range: 0x8006C15C -> 0x8006C2F8
int pifProcessOutputData(struct __anon_0x4A974* pPIF) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r29

    // Local variables
    u8* prx; // r6
    u8* ptx; // r5
    int iData; // r31
    int channel; // r30
}

// Range: 0x8006C0FC -> 0x8006C15C
int pifSetData(struct __anon_0x4A974* pPIF, u8* acData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r31
    // u8* acData; // r4
}

// Range: 0x8006C090 -> 0x8006C0FC
int pifGetData(struct __anon_0x4A974* pPIF, u8* acData) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r30
    // u8* acData; // r31
}

// Range: 0x8006BE68 -> 0x8006C090
int pifEvent(struct __anon_0x4A974* pPIF, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x4A974* pPIF; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31

    // Local variables
    int i; // r31
}
