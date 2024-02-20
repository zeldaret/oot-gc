#ifndef _DOLPHIN_GX_GXPIXEL_H_
#define _DOLPHIN_GX_GXPIXEL_H_

#include <dolphin/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

// 0x800E2B9C
void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
// 0x800E2D50
void GXSetFogRangeAdj(GXBool enable, u16 center, GXFogAdjTable *table);
// 0x800E2E50
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
// 0x800E2F54
void GXSetColorUpdate(GXBool update_enable);
// 0x800E2F94
void GXSetAlphaUpdate(GXBool update_enable);
// 0x800E2FD4
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
// 0x800E304C
void GXSetZCompLoc(GXBool before_tex);
// 0x800E308C
// ? GXSetPixelFmt();
// 0x800E319C
void GXSetDither(GXBool dither);
// 0x800E31DC
void GXSetDstAlpha(GXBool enable, u8 alpha);
// 0x800E3230
void GXSetFieldMask(GXBool odd_mask, GXBool even_mask);
// 0x800E3268
void GXSetFieldMode(GXBool field_mode, GXBool half_aspect_ratio);

#ifdef __cplusplus
}
#endif

#endif
