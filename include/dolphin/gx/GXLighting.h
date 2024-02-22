#ifndef _DOLPHIN_GX_GXLIGHTING_H_
#define _DOLPHIN_GX_GXLIGHTING_H_

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

#define XF_AMBIENT0_ID 0x100a
#define XF_MATERIAL0_ID 0x100c

void GXSetNumChans(u8 nChans);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask,
                   GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetChanAmbColor(GXChannelID chan, GXColor amb_color);
void GXSetChanMatColor(GXChannelID chan, GXColor mat_color);

#endif
