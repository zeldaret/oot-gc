#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "dolphin.h"
#include "emulator/cpu.h"
#include "emulator/mips.h"
#include "emulator/xlObject.h"

#define N64_BTN_A (1 << 31)
#define N64_BTN_B (1 << 30)
#define N64_BTN_Z (1 << 29)
#define N64_BTN_START (1 << 28)
#define N64_BTN_DUP (1 << 27)
#define N64_BTN_DDOWN (1 << 26)
#define N64_BTN_DLEFT (1 << 25)
#define N64_BTN_DRIGHT (1 << 24)
#define N64_BTN_L (1 << 21)
#define N64_BTN_R (1 << 20)
#define N64_BTN_CUP (1 << 19)
#define N64_BTN_CDOWN (1 << 18)
#define N64_BTN_CLEFT (1 << 17)
#define N64_BTN_CRIGHT (1 << 16)
#define N64_BTN_UNSET 0

typedef bool (*SystemCopyCallbackFunc)(void);

// note: each stick direction count as an input
typedef enum GcnButton {
    GCN_BTN_A = 0,
    GCN_BTN_B = 1,
    GCN_BTN_X = 2,
    GCN_BTN_Y = 3,
    GCN_BTN_L = 4,
    GCN_BTN_R = 5,
    GCN_BTN_Z = 6,
    GCN_BTN_START = 7,
    GCN_BTN_UNK8 = 8,
    GCN_BTN_UNK9 = 9,
    GCN_BTN_UNK10 = 10,
    GCN_BTN_UNK11 = 11,
    GCN_BTN_DPAD_UP = 12,
    GCN_BTN_DPAD_DOWN = 13,
    GCN_BTN_DPAD_LEFT = 14,
    GCN_BTN_DPAD_RIGHT = 15,
    GCN_BTN_CSTICK_UP = 16,
    GCN_BTN_CSTICK_DOWN = 17,
    GCN_BTN_CSTICK_LEFT = 18,
    GCN_BTN_CSTICK_RIGHT = 19,
    GCN_BTN_COUNT = 20,
} GcnButton;

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
#if IS_MM
    SRT_KIRBY = 12,
    SRT_PILOTWING = 13,
    SRT_SLICRADIC = 14,
#endif
    SRT_UNKNOWN,
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
    /* 0x0C */ SystemCopyCallbackFunc pCallback;
} SystemRomCopy; // size = 0x10

// __anon_0x37240
typedef struct System {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ bool bException;
    /* 0x0C */ SystemMode eMode;
    /* 0x10 */ SystemRomCopy romCopy;
    /* 0x20 */ SystemRomType eTypeROM;
    /* 0x24 */ void* apObject[SOT_COUNT];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ SystemObjectType storageDevice;
    /* 0x74 */ u8 anException[16];
#if VERSION != MM_J && VERSION != MM_E
    /* 0x84 */ bool bJapaneseVersion;
#endif
} System; // size = 0x88

// __anon_0x3459E
typedef struct SystemRomConfig {
    /* 0x0000 */ char rom[36];
    /* 0x0024 */ s32 controllerConfiguration[4][GCN_BTN_COUNT];
    /* 0x0164 */ s32 rumbleConfiguration;
    /* 0x0168 */ SystemObjectType storageDevice;
    /* 0x016C */ s32 normalControllerConfig;
    /* 0x0170 */ s32 currentControllerConfig;
} SystemRomConfig; // size = 0x174

#define SYSTEM(pSystem) ((System*)(pSystem))
#define SYSTEM_FRAME(pSystem) ((Frame*)(SYSTEM(pSystem)->pFrame))
#define SYSTEM_SOUND(pSystem) ((Sound*)(SYSTEM(pSystem)->pSound))
#define SYSTEM_CPU(pSystem) ((Cpu*)(SYSTEM(pSystem)->apObject[SOT_CPU]))
#define SYSTEM_PIF(pSystem) ((Pif*)(SYSTEM(pSystem)->apObject[SOT_PIF]))
#define SYSTEM_RAM(pSystem) ((Ram*)(SYSTEM(pSystem)->apObject[SOT_RAM]))
#define SYSTEM_ROM(pSystem) ((Rom*)(SYSTEM(pSystem)->apObject[SOT_ROM]))
#define SYSTEM_RSP(pSystem) ((Rsp*)(SYSTEM(pSystem)->apObject[SOT_RSP]))
#define SYSTEM_RDP(pSystem) ((Rdp*)(SYSTEM(pSystem)->apObject[SOT_RDP]))
#define SYSTEM_MIPS(pSystem) ((Mips*)(SYSTEM(pSystem)->apObject[SOT_MIPS]))
#define SYSTEM_DISK(pSystem) ((Disk*)(SYSTEM(pSystem)->apObject[SOT_DISK]))
#define SYSTEM_FLASH(pSystem) ((Flash*)(SYSTEM(pSystem)->apObject[SOT_FLASH]))
#define SYSTEM_SRAM(pSystem) ((Sram*)(SYSTEM(pSystem)->apObject[SOT_SRAM]))
#define SYSTEM_AUDIO(pSystem) ((Audio*)(SYSTEM(pSystem)->apObject[SOT_AUDIO]))
#define SYSTEM_VIDEO(pSystem) ((Video*)(SYSTEM(pSystem)->apObject[SOT_VIDEO]))
#define SYSTEM_SERIAL(pSystem) ((Serial*)(SYSTEM(pSystem)->apObject[SOT_SERIAL]))
#define SYSTEM_LIBRARY(pSystem) ((Library*)(SYSTEM(pSystem)->apObject[SOT_LIBRARY]))
#define SYSTEM_PERIPHERAL(pSystem) ((Peripheral*)(SYSTEM(pSystem)->apObject[SOT_PERIPHERAL]))
#define SYSTEM_RDB(pSystem) ((Rdb*)(SYSTEM(pSystem)->apObject[SOT_RDB]))

extern u32 nTickMultiplier;
extern f32 fTickScale;
extern u32 gnFlagZelda;
extern SystemRomConfig gSystemRomConfigurationList[1];

bool systemCopyROM(System* pSystem, s32 nOffsetRAM, s32 nOffsetROM, s32 nSize, SystemCopyCallbackFunc pCallback);
bool systemSetMode(System* pSystem, SystemMode eMode);
bool systemGetMode(System* pSystem, SystemMode* peMode);
bool systemSetStorageDevice(System* pSystem, SystemObjectType eStorageDevice);
bool systemGetStorageDevice(System* pSystem, SystemObjectType* pStorageDevice);
bool systemReset(System* pSystem);
bool systemExecute(System* pSystem, s32 nCount);
bool systemCheckInterrupts(System* pSystem);
bool systemExceptionPending(System* pSystem, SystemInterruptType nException);
bool systemEvent(System* pSystem, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassSystem;

#endif
