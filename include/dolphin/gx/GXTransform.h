#ifndef _DOLPHIN_GX_GXTRANSFORM_H_
#define _DOLPHIN_GX_GXTRANSFORM_H_

#include "dolphin/gx/GXEnum.h"
#include "dolphin/mtx.h"

#define GX_PROJECTION_SZ 7

void __GXSetProjection(void);
void GXSetProjection(const Mtx44 proj, GXProjectionType type);
void GXSetProjectionv(const f32* proj);
void WriteMTXPS4x3(register volatile void* dst, register const Mtx src);
void WriteMTXPS3x3(register volatile void* dst, register const Mtx src);
void WriteMTXPS4x2(register volatile void* dst, register const Mtx src);
void GXLoadPosMtxImm(Mtx mtx, u32 id);
void GXLoadNrmMtxImm(Mtx mtx, u32 id);
void GXSetCurrentMtx(u32 id);
void GXLoadTexMtxImm(const Mtx mtx, u32 id, GXTexMtxType type);
void __GXSetViewport(void);
void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field);
void GXSetViewport(f32 left, f32 top, f32 width, f32 height, f32 nearZ, f32 farZ);
void GXSetScissor(u32 left, u32 top, u32 width, u32 height);
void GXGetScissor(u32* left, u32* top, u32* width, u32* height);
void GXSetScissorBoxOffset(s32 x, s32 y);
void GXSetClipMode(GXClipMode mode);
void __GXSetMatrixIndex(GXAttr index);

#endif
