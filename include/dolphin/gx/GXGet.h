#ifndef _DOLPHIN_GX_GXGET_H_
#define _DOLPHIN_GX_GXGET_H_

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

GXBool GXGetTexObjMipMap(GXTexObj* tex_obj);
GXTexFmt GXGetTexObjFmt(GXTexObj* tex_obj);
void* GXGetTexObjData(GXTexObj* tex_obj);

#endif
