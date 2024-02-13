#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "types.h"

typedef enum SystemMode {
    /* -1 */ SM_NONE = -1,
    /*  0 */ SM_RUNNING,
    /*  1 */ SM_STOPPED
} SystemMode;

typedef enum SystemRomType {
    /* -1 */ SRT_NONE = -1,
    /*  0 */ SRT_MARIO,
    /*  1 */ SRT_WAVERACE,
    /*  2 */ SRT_MARIOKART,
    /*  3 */ SRT_STARFOX,
    /*  4 */ SRT_ZELDA1,
    /*  5 */ SRT_ZELDA2,
    /*  6 */ SRT_1080,
    /*  7 */ SRT_PANEL,
    /*  8 */ SRT_MARIOPARTY1,
    /*  9 */ SRT_MARIOPARTY2,
    /* 10 */ SRT_MARIOPARTY3,
    /* 11 */ SRT_DRMARIO,
    /* 12 */ SRT_UNKNOWN
} SystemRomType;

typedef enum SystemObjectType {
    /* -1 */ SOT_NONE = -1,
    /*  0 */ SOT_CPU,
    /*  1 */ SOT_PIF,
    /*  2 */ SOT_RAM,
    /*  3 */ SOT_ROM,
    /*  4 */ SOT_RSP,
    /*  5 */ SOT_RDP,
    /*  6 */ SOT_MIPS,
    /*  7 */ SOT_DISK,
    /*  8 */ SOT_FLASH,
    /*  9 */ SOT_SRAM,
    /* 10 */ SOT_AUDIO,
    /* 11 */ SOT_VIDEO,
    /* 12 */ SOT_SERIAL,
    /* 13 */ SOT_LIBRARY,
    /* 14 */ SOT_PERIPHERAL,
    /* 15 */ SOT_RDB,
    /* 16 */ SOT_COUNT
} SystemObjectType;

typedef struct RomCopy {
    /* 0x00 */ int nSize;
    /* 0x04 */ int nOffsetRAM;
    /* 0x08 */ int nOffsetROM;
    /* 0x0C */ int (*pCallback)();
} RomCopy; // size = 0x10

typedef struct System {
    /* 0x00 */ void *pFrame;
    /* 0x04 */ void *pSound;
    /* 0x08 */ int bException;
    /* 0x0C */ SystemMode eMode;
    /* 0x10 */ RomCopy romCopy;
    /* 0x20 */ SystemRomType eTypeROM;
    /* 0x24 */ void *apObject[SOT_COUNT];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ SystemObjectType storageDevice;
    /* 0x74 */ u8 anException[16];
    /* 0x84 */ int bJapaneseVersion;
} System; // size = 0x88

typedef struct SystemRomConfig {
    /* 0x0000 */ char rom[36];
    /* 0x0024 */ int controllerConfiguration[4][20];
    /* 0x0164 */ int rumbleConfiguration;
    /* 0x0168 */ SystemObjectType storageDevice;
    /* 0x016C */ int normalControllerConfig;
    /* 0x0170 */ int currentControllerConfig;
} SystemRomConfig; // size = 0x174

#endif
