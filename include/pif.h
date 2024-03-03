#ifndef _PIF_H
#define _PIF_H

#include "dolphin.h"
#include "xlObject.h"

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
    /* 0x00 */ struct Rom* pROM;
    /* 0x04 */ struct Ram* pRAM;
    /* 0x08 */ void* pHost;
    /* 0x0C */ u16 controllerType[5];
    /* 0x16 */ char controllerStatus[5];
    /* 0x1C */ ControllerType eControllerType[5];
} Pif; // size = 0x30

s32 pifReadRumble(Pif* pPIF, s32 channel, u16 address, u8* data);
s32 pifWriteRumble(Pif* pPIF, s32 channel, u16 address, u8* data);
s32 pifGetEControllerType(Pif* pPIF, s32 channel, ControllerType* type);
s32 pifEvent(Pif* pPIF, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassPIF;

#endif
