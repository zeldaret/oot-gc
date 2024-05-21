#ifndef _DOLPHIN_GX_ATTR_H
#define _DOLPHIN_GX_ATTR_H

#include "dolphin/gx/GXData.h"
#include "dolphin/gx/GXEnum.h"

void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void __GXSetVCD(void);
void __GXCalculateVLim(void);
void GXClearVtxDesc(void);
void GXSetVtxAttrFmt(GXVtxFmt format, GXAttr attr, GXCompCnt count, GXCompType type, u8 frac);
void GXSetVtxAttrFmtv(GXVtxFmt format, GXVtxAttrFmtList* list);
void __GXSetVAT(void);
void GXSetArray(GXAttr attr, void* basePtr, u8 stride);
void GXInvalidateVtxCache(void);
void GXSetTexCoordGen2(GXTexCoordID id, GXTexGenType type, GXTexGenSrc src, u32 texMtxIdx, GXBool normalize,
                       u32 dualTexMtxIdx);
void GXSetNumTexGens(u8 count);

#endif
