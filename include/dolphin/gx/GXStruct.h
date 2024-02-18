#ifndef _DOLPHIN_GX_GXSTRUCT_H_
#define _DOLPHIN_GX_GXSTRUCT_H_

#include <dolphin/types.h>
#include <dolphin/vitypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    /*0x00*/ VITVMode viTVmode;
    /*0x04*/ u16 fbWidth;
    /*0x06*/ u16 efbHeight;
    /*0x08*/ u16 xfbHeight;
    /*0x0A*/ u16 viXOrigin;
    /*0x0C*/ u16 viYOrigin;
    /*0x0E*/ u16 viWidth;
    /*0x10*/ u16 viHeight;
    /*0x14*/ VIXFBMode xFBmode;
    /*0x18*/ u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
} GXRenderModeObj;

typedef struct
{
    u8 r;
    u8 g; 
    u8 b; 
    u8 a;
} GXColor;

typedef struct
{
    u32 dummy[8];
} GXTexObj;

typedef struct
{
    u32 dummy[16];
} GXLightObj;

typedef struct
{
    u32 dummy[4];
} GXTexRegion;

typedef struct
{
    u32 dummy[4];
} GXTlutRegion;

typedef struct
{
    u16 r[10];
} GXFogAdjTable;

#ifdef __cplusplus
}
#endif

#endif
