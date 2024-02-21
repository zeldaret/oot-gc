#ifndef _SIMGCN_H
#define _SIMGCN_H

#include <dolphin/types.h>
#include <dolphin/gx.h>
#include "system.h"

//! TODO: missing from the sdk?
// __anon_0xBEA
typedef enum _GXTlutFmt {
    GX_TL_IA8 = 0,
    GX_TL_RGB565 = 1,
    GX_TL_RGB5A3 = 2,
    GX_MAX_TLUTFMT = 3,
} _GXTlutFmt;

typedef struct __anon_0xD7D1 {
    /* 0x00 */ u16 height;
    /* 0x02 */ u16 width;
    /* 0x04 */ u32 format;
    /* 0x08 */ char* data;
    /* 0x0C */ GXTexWrapMode wrapS;
    /* 0x10 */ GXTexWrapMode wrapT;
    /* 0x14 */ GXTexFilter minFilter;
    /* 0x18 */ GXTexFilter magFilter;
    /* 0x1C */ f32 LODBias;
    /* 0x20 */ u8 edgeLODEnable;
    /* 0x21 */ u8 minLOD;
    /* 0x22 */ u8 maxLOD;
    /* 0x23 */ u8 unpacked;
} __anon_0xD7D1; // size = 0x24

typedef struct __anon_0xDA2C {
    /* 0x0 */ u16 numEntries;
    /* 0x2 */ u8 unpacked;
    /* 0x3 */ u8 pad8;
    /* 0x4 */ _GXTlutFmt format;
    /* 0x8 */ char* data;
} __anon_0xDA2C; // size = 0xC

typedef struct __anon_0xDAF8 {
    /* 0x0 */ __anon_0xD7D1* textureHeader;
    /* 0x4 */ __anon_0xDA2C* CLUTHeader;
} __anon_0xDAF8; // size = 0x8

typedef struct __anon_0xDB69 {
    /* 0x0 */ u32 versionNumber;
    /* 0x4 */ u32 numDescriptors;
    /* 0x8 */ __anon_0xDAF8* descriptorArray;
} __anon_0xDB69; // size = 0xC

extern s32 gDVDResetToggle;
extern s32 gbDisplayedError;

extern System* gpSystem;

void simulatorUnpackTexPalette(__anon_0xDB69* pal);
s32 simulatorShowLoad(s32 /* unknown */, char* szNameFile, f32 rProgress);
s32 simulatorGetArgument(SystemArgumentType eType, char** pszArgument);
s32 simulatorCopyControllerMap(u32* mapDataOutput, u32* mapDataInput);
s32 simulatorSetControllerMap(u32* mapData, s32 channel);

#endif
