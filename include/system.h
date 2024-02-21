#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <dolphin/types.h>

// __anon_0x394CD
typedef enum SystemMode {
    SM_NONE = -1,
    SM_RUNNING = 0,
    SM_STOPPED = 1,
} SystemMode;

// __anon_0x370F1
typedef enum SystemRomType {
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
} SystemRomType;

// __anon_0x370F1
typedef enum SystemObjectType {
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
} SystemObjectType;

// __anon_0x37040
typedef struct RomCopy {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nOffsetRAM;
    /* 0x08 */ s32 nOffsetROM;
    /* 0x0C */ s32 (*pCallback)();
} RomCopy; // size = 0x10

// __anon_0x37240
typedef struct System {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ s32 bException;
    /* 0x0C */ SystemMode eMode;
    /* 0x10 */ RomCopy romCopy;
    /* 0x20 */ SystemRomType eTypeROM;
    /* 0x24 */ void* apObject[SOT_COUNT];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ SystemObjectType storageDevice;
    /* 0x74 */ u8 anException[16];
    /* 0x84 */ s32 bJapaneseVersion;
} System; // size = 0x88

// __anon_0x3459E
typedef struct SystemRomConfig {
    /* 0x0000 */ char rom[36];
    /* 0x0024 */ s32 controllerConfiguration[4][20];
    /* 0x0164 */ s32 rumbleConfiguration;
    /* 0x0168 */ SystemObjectType storageDevice;
    /* 0x016C */ s32 normalControllerConfig;
    /* 0x0170 */ s32 currentControllerConfig;
} SystemRomConfig; // size = 0x174

extern u32 gnFlagZelda;

#endif
