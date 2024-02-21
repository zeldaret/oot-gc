#ifndef _DOLPHIN_GX_GXTRANSFORM_H_
#define _DOLPHIN_GX_GXTRANSFORM_H_

#include "dolphin/gx/GXEnum.h"

#define GX_PROJECTION_SZ 7

void GXSetProjection(f32 mtx[4][4], GXProjectionType type);
void GXSetProjectionv(const f32* ptr);
void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);
void GXLoadPosMtxImm(f32 mtx[3][4], u32 id);
void GXLoadNrmMtxImm(f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(f32 mtx[][4], u32 id, GXTexMtxType type);
void GXSetCurrentMtx(u32 id);
void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field);
void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
void GXGetScissor(u32* left, u32* top, u32* width, u32* height);
void GXSetScissorBoxOffset(s32 x_off, s32 y_off);
void GXSetClipMode(GXClipMode mode);

#endif
