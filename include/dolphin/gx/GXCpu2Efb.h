#ifndef _DOLPHIN_GX_GXCPU2EFB_H_
#define _DOLPHIN_GX_GXCPU2EFB_H_

#include "dolphin/gx/GXEnum.h"

void GXPokeColorUpdate(GXBool update_enable);
void GXPokeAlphaUpdate(GXBool update_enable);
void GXPokeDither(GXBool dither);
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXPokeAlphaMode(GXCompare func, u8 threshold);
void GXPokeAlphaRead(GXAlphaReadMode mode);
void GXPokeDstAlpha(GXBool enable, u8 alpha);
void GXPokeZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void GXPeekZ(u16 x, u16 y, u32* z);

#endif
