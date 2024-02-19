#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "types.h"
#include "mips.h"
#include "cpu.h"

typedef s32 SystemCopyCallbackFunc(void);

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

typedef enum SystemArgumentType {
    /* -1 */ SAT_NONE = -1,
    /*  0 */ SAT_NAME,
    /*  1 */ SAT_PROGRESSIVE,
    /*  2 */ SAT_VIBRATION,
    /*  3 */ SAT_CONTROLLER,
    /*  4 */ SAT_XTRA,
    /*  5 */ SAT_MEMORYCARD,
    /*  6 */ SAT_MOVIE,
    /*  7 */ SAT_RESET,
    /*  8 */ SAT_COUNT
} SystemArgumentType;

// __anon_0x3979C
typedef enum SystemInterruptType {
    SIT_NONE = -1,
    SIT_SW0 = 0,
    SIT_SW1 = 1,
    SIT_CART = 2,
    SIT_COUNTER = 3,
    SIT_RDB = 4,
    SIT_SP = 5,
    SIT_SI = 6,
    SIT_AI = 7,
    SIT_VI = 8,
    SIT_PI = 9,
    SIT_DP = 10,
    SIT_CPU_BREAK = 11,
    SIT_SP_BREAK = 12,
    SIT_FAULT = 13,
    SIT_THREADSTATUS = 14,
    SIT_PRENMI = 15,
    SIT_COUNT = 16,
} SystemInterruptType;

// __anon_0x393FF
typedef struct SystemException {
    /* 0x00 */ char* szType;
    /* 0x04 */ u32 nMask;
    /* 0x08 */ CpuExceptionCode eCode;
    /* 0x0C */ SystemInterruptType eType;
    /* 0x10 */ MipsInterruptType eTypeMips;
} SystemException; // size = 0x14

// __anon_0x37040
typedef struct SystemRomCopy {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nOffsetRAM;
    /* 0x08 */ s32 nOffsetROM;
    /* 0x0C */ SystemCopyCallbackFunc* pCallback;
} SystemRomCopy; // size = 0x10

// __anon_0x37240
typedef struct System {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ s32 bException;
    /* 0x0C */ SystemMode eMode;
    /* 0x10 */ SystemRomCopy romCopy;
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

#define SYSTEM_CPU(pSystem) ((struct Cpu*)(((System*)(pSystem))->apObject[SOT_CPU]))
#define SYSTEM_ROM(pSystem) ((struct Rom*)(((System*)(pSystem))->apObject[SOT_ROM]))
#define SYSTEM_RAM(pSystem) ((struct Ram*)(((System*)(pSystem))->apObject[SOT_RAM]))
#define SYSTEM_RSP(pSystem) ((struct Rsp*)(((System*)(pSystem))->apObject[SOT_RSP]))
#define SYSTEM_MIPS(pSystem) ((struct Mips*)(((System*)(pSystem))->apObject[SOT_MIPS]))

extern u32 gnFlagZelda;

#endif
