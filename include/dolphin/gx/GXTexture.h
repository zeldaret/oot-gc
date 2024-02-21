#ifndef _DOLPHIN_GX_GXTEXTURE_H_
#define _DOLPHIN_GX_GXTEXTURE_H_

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

typedef GXTexRegion* (*GXTexRegionCallback)(GXTexObj* t_obj, GXTexMapID id);
typedef GXTlutRegion* (*GXTlutRegionCallback)(u32 idx);

void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s,
                  GXTexWrapMode wrap_t, GXBool mipmap);
void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrap_s,
                    GXTexWrapMode wrap_t, GXBool mipmap, u32 tlut_name);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt, f32 min_lod, f32 max_lod, f32 lod_bias,
                     GXBool bias_clamp, GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXLoadTexObjPreLoaded(const GXTexObj* obj, const GXTexRegion* region, GXTexMapID id);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXInitTlutObj(GXTlutObj* obj, void* tlut, GXTlutFmt tlut_fmt, u16 num_entries);
void GXLoadTlut(GXTlutObj* obj, u32 tlut_name);
void GXInitTexCacheRegion(GXTexRegion* region, GXBool is_32b_mipmap, u32 tmem_even, GXTexCacheSize size_even,
                          u32 tmem_odd, GXTexCacheSize size_odd);
void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, GXTlutSize tlut_size);
void GXInvalidateTexAll(void);
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback f);
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback f);

#endif
