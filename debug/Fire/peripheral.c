/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\peripheral.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8009779C -> 0x80097D9C
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x83C1D; // size = 0x10

// size = 0x10, address = 0x800EFFBC
struct _XL_OBJECTTYPE gClassPeripheral;

typedef struct __anon_0x83D15 {
    /* 0x00 */ void* pHost;
    /* 0x04 */ int nStatus;
    /* 0x08 */ int nSizeGet;
    /* 0x0C */ int nSizePut;
    /* 0x10 */ int nLatency1;
    /* 0x14 */ int nLatency2;
    /* 0x18 */ int nRelease1;
    /* 0x1C */ int nRelease2;
    /* 0x20 */ int nSizePage1;
    /* 0x24 */ int nSizePage2;
    /* 0x28 */ int nAddressRAM;
    /* 0x2C */ int nAddressROM;
    /* 0x30 */ int nWidthPulse1;
    /* 0x34 */ int nWidthPulse2;
} __anon_0x83D15; // size = 0x38

typedef enum __anon_0x8415D {
    SOT_NONE = -1,
    SOT_CPU = 0,
    SOT_PIF = 1,
    SOT_RAM = 2,
    SOT_ROM = 3,
    SOT_RSP = 4,
    SOT_RDP = 5,
    SOT_MIPS = 6,
    SOT_DISK = 7,
    SOT_FLASH = 8,
    SOT_SRAM = 9,
    SOT_AUDIO = 10,
    SOT_VIDEO = 11,
    SOT_SERIAL = 12,
    SOT_LIBRARY = 13,
    SOT_PERIPHERAL = 14,
    SOT_RDB = 15,
    SOT_COUNT = 16,
} __anon_0x8415D;

typedef enum __anon_0x843DE {
    SM_NONE = -1,
    SM_RUNNING = 0,
    SM_STOPPED = 1,
} __anon_0x843DE;

typedef struct __anon_0x84447 {
    /* 0x0 */ int nSize;
    /* 0x4 */ int nOffsetRAM;
    /* 0x8 */ int nOffsetROM;
    /* 0xC */ int (*pCallback)();
} __anon_0x84447; // size = 0x10

typedef enum __anon_0x844F8 {
    SRT_NONE = -1,
    SRT_MARIO = 0,
    SRT_WAVERACE = 1,
    SRT_MARIOKART = 2,
    SRT_STARFOX = 3,
    SRT_ZELDA1 = 4,
    SRT_ZELDA2 = 5,
    SRT_1080 = 6,
    SRT_PANEL = 7,
    SRT_MARIOPARTY1 = 8,
    SRT_MARIOPARTY2 = 9,
    SRT_MARIOPARTY3 = 10,
    SRT_DRMARIO = 11,
    SRT_UNKNOWN = 12,
} __anon_0x844F8;

typedef struct __anon_0x8464B {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ int bException;
    /* 0x0C */ enum __anon_0x843DE eMode;
    /* 0x10 */ struct __anon_0x84447 romCopy;
    /* 0x20 */ enum __anon_0x844F8 eTypeROM;
    /* 0x24 */ void* apObject[16];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ enum __anon_0x8415D storageDevice;
    /* 0x74 */ u8 anException[16];
    /* 0x84 */ int bJapaneseVersion;
} __anon_0x8464B; // size = 0x88

// size = 0x4, address = 0x80135600
struct __anon_0x8464B* gpSystem;

// Range: 0x80097D58 -> 0x80097D9C
static int peripheralDMA_Complete() {
    // Local variables
    struct __anon_0x83D15* pPeripheral; // r3

    // References
    // -> struct __anon_0x8464B* gpSystem;
}

// Range: 0x80097D50 -> 0x80097D58
int peripheralPut8() {}

// Range: 0x80097D48 -> 0x80097D50
int peripheralPut16() {}

// Range: 0x800979C4 -> 0x80097D48
int peripheralPut32(struct __anon_0x83D15* pPeripheral, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x83D15* pPeripheral; // r30
    // unsigned int nAddress; // r1+0xC
    // int* pData; // r1+0x10

    // Local variables
    int bFlag; // r31
    enum __anon_0x8415D storageDevice; // r1+0x14
}

// Range: 0x800979BC -> 0x800979C4
int peripheralPut64() {}

// Range: 0x800979B4 -> 0x800979BC
int peripheralGet8() {}

// Range: 0x800979AC -> 0x800979B4
int peripheralGet16() {}

// Range: 0x800978AC -> 0x800979AC
int peripheralGet32(struct __anon_0x83D15* pPeripheral, unsigned int nAddress, int* pData) {
    // Parameters
    // struct __anon_0x83D15* pPeripheral; // r1+0x0
    // unsigned int nAddress; // r1+0x4
    // int* pData; // r1+0x8
}

// Range: 0x800978A4 -> 0x800978AC
int peripheralGet64() {}

// Range: 0x8009779C -> 0x800978A4
int peripheralEvent(struct __anon_0x83D15* pPeripheral, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x83D15* pPeripheral; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r31
}
