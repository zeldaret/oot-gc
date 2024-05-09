#ifndef _PIF_H
#define _PIF_H

#include "dolphin.h"
#include "emulator/xlObject.h"

#define PIF_RAM_START 0x7C0
#define PIF_RAM_END 0x7FF

// __anon_0x3C277
typedef enum ControllerType {
    CT_NONE = 0,
    CT_CONTROLLER = 1,
    CT_CONTROLLER_W_PAK = 2, // Controller Pak?
    CT_CONTROLLER_W_RPAK = 3, // Rumble Pak
    CT_MOUSE = 4,
    CT_VOICE = 5,
    CT_4K = 6, // Mem Pak?
    CT_16K = 7, // Mem Pak?
    CT_COUNT = 8,
} ControllerType;

// __anon_0x3C350
typedef struct Pif {
    /* 0x00 */ void* pROM;
    /* 0x04 */ void* pRAM;
    /* 0x08 */ void* pHost;
    /* 0x0C */ u16 controllerType[5];
    /* 0x16 */ char controllerStatus[5];
    /* 0x1C */ ControllerType eControllerType[5];
} Pif; // size = 0x30

bool pifReadRumble(Pif* pPIF, s32 channel, u16 address, u8* data);
bool pifWriteRumble(Pif* pPIF, s32 channel, u16 address, u8* data);
bool pifSetControllerType(Pif* pPIF, s32 channel, ControllerType type);
bool pifGetEControllerType(Pif* pPIF, s32 channel, ControllerType* type);
bool pifSetEEPROMType(Pif* pPIF, ControllerType type);
bool pifGetEEPROMSize(Pif* pPIF, u32* size);
bool pifExecuteCommand(Pif* pPIF, u8* buffer, s32 unused, u8* prx, s32 channel);
bool pifProcessInputData(Pif* pPIF);
bool pifProcessOutputData(Pif* pPIF);
bool pifSetData(Pif* pPIF, u8* acData);
bool pifGetData(Pif* pPIF, u8* acData);
bool pifEvent(Pif* pPIF, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassPIF;

#endif
