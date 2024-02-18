#ifndef _DOLPHIN_GX_GXTEV_H_
#define _DOLPHIN_GX_GXTEV_H_

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>

#ifdef __cplusplus
extern "C" {
#endif

// 0x800E2214
void GXSetTevOp(GXTevStageID id, GXTevMode mode);
// 0x800E23B8
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
// 0x800E2438
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
// 0x800E24BC
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
// 0x800E257C
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
// // 0x800E263C
void GXSetTevColor(GXTevRegID id, GXColor color);
// // 0x800E26B0
void GXSetTevKColor(GXTevKColorID id, GXColor color);
// // 0x800E2724
void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel);
// // 0x800E2790
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel);
// // 0x800E27FC
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
// // 0x800E2854
void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red, GXTevColorChan green, GXTevColorChan blue, GXTevColorChan alpha);
// // 0x800E28F4
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
// // 0x800E2944
void GXSetZTexture(GXZTexOp op,GXTexFmt fmt, u32 bias);
// 0x800E29C8
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
// 0x800E2B68
void GXSetNumTevStages(u8 nStages);

#ifdef __cplusplus
}
#endif

#endif
