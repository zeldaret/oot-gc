#ifndef _DOLPHIN_GX_GXTEXTURE_H_
#define _DOLPHIN_GX_GXTEXTURE_H_

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

typedef GXTexRegion* (*GXTexRegionCallback)(GXTexObj* t_obj, GXTexMapID id);
typedef GXTlutRegion* (*GXTlutRegionCallback)(u32 idx);

void __GetImageTileCount(GXTexFmt format, u16 width, u16 height, u32* a, u32* b, u32* c);
void GXInitTexObj(GXTexObj* obj, void* imagePtr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode sWrap,
                  GXTexWrapMode tWrap, GXBool useMIPmap);
void GXInitTexObjCI(GXTexObj* obj, void* imagePtr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode sWrap,
                    GXTexWrapMode tWrap, GXBool useMIPmap, u32 tlutName);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter minFilter, GXTexFilter maxFilter, f32 minLOD, f32 maxLOD, f32 lodBias,
                     GXBool doBiasClamp, GXBool doEdgeLOD, GXAnisotropy maxAniso);
void GXInitTexObjData(GXTexObj* obj, void* image_ptr);
void* GXGetTexObjData(GXTexObj* tex_obj);
GXTexFmt GXGetTexObjFmt(GXTexObj* obj);
GXBool GXGetTexObjMipMap(GXTexObj* obj);
void GXLoadTexObjPreLoaded(GXTexObj* obj, GXTexRegion* region, GXTexMapID map);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID map);
void GXInitTlutObj(GXTlutObj* obj, void* table, GXTlutFmt format, u16 numEntries);
void GXLoadTlut(GXTlutObj* obj, u32 tlutName);
void GXInitTexCacheRegion(GXTexRegion* region, GXBool is32bMIPmap, u32 memEven, GXTexCacheSize sizeEven, u32 memOdd,
                          GXTexCacheSize sizeOdd);
void GXInitTlutRegion(GXTlutRegion* region, u32 memAddr, GXTlutSize tlutSize);
void GXInvalidateTexAll(void);
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback func);
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback func);
void __SetSURegs(u32 texImgIndex, u32 setUpRegIndex);
void __GXSetSUTexRegs(void);
void __GXSetTmemConfig(u32 config);

#endif
