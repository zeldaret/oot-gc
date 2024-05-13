#ifndef _DOLPHIN_TEX_H_
#define _DOLPHIN_TEX_H_

#include "dolphin/gx.h"
#include "dolphin/types.h"

typedef struct {
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
} TEXHeader; // size = 0x24

typedef struct {
    /* 0x0 */ u16 numEntries;
    /* 0x2 */ u8 unpacked;
    /* 0x3 */ u8 pad8;
    /* 0x4 */ GXTlutFmt format;
    /* 0x8 */ char* data;
} CLUTHeader; // size = 0xC

typedef struct {
    /* 0x0 */ TEXHeader* textureHeader;
    /* 0x4 */ CLUTHeader* CLUTHeader;
} TEXDescriptor; // size = 0x8

typedef struct {
    /* 0x0 */ u32 versionNumber;
    /* 0x4 */ u32 numDescriptors;
    /* 0x8 */ TEXDescriptor* descriptorArray;
} TEXPalette; // size = 0xC

TEXDescriptor* TEXGet(TEXPalette* pal, u32 id);
void TEXGetGXTexObjFromPalette(TEXPalette* pal, GXTexObj* to, u32 id);

#endif
