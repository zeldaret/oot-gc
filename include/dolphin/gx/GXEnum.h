#ifndef _DOLPHIN_GX_GXENUM_H_
#define _DOLPHIN_GX_GXENUM_H_

#include "dolphin/types.h"

typedef u8 GXBool;

#define GX_FALSE ((GXBool)0)
#define GX_TRUE ((GXBool)1)

#define GX_ENABLE ((GXBool)1)
#define GX_DISABLE ((GXBool)0)

#define GX_LARGE_NUMBER 1.0e+18f;

typedef enum _GXProjectionType {
    GX_PERSPECTIVE,
    GX_ORTHOGRAPHIC,
} GXProjectionType;

typedef enum _GXCompare {
    GX_NEVER,
    GX_LESS,
    GX_EQUAL,
    GX_LEQUAL,
    GX_GREATER,
    GX_NEQUAL,
    GX_GEQUAL,
    GX_ALWAYS,
} GXCompare;

typedef enum _GXAlphaOp {
    GX_AOP_AND,
    GX_AOP_OR,
    GX_AOP_XOR,
    GX_AOP_XNOR,
    GX_MAX_ALPHAOP,
} GXAlphaOp;

typedef enum _GXZFmt16 {
    GX_ZC_LINEAR,
    GX_ZC_NEAR,
    GX_ZC_MID,
    GX_ZC_FAR,
} GXZFmt16;

typedef enum _GXGamma {
    GX_GM_1_0,
    GX_GM_1_7,
    GX_GM_2_2,
} GXGamma;

typedef enum _GXPixelFmt {
    GX_PF_RGB8_Z24,
    GX_PF_RGBA6_Z24,
    GX_PF_RGB565_Z16,
    GX_PF_Z24,
    GX_PF_Y8,
    GX_PF_U8,
    GX_PF_V8,
    GX_PF_YUV420,
    GX_MAX_PIXELFMT
} GXPixelFmt;

typedef enum _GXPrimitive {
    GX_QUADS = 0x80,
    GX_TRIANGLES = 0x90,
    GX_TRIANGLESTRIP = 0x98,
    GX_TRIANGLEFAN = 0xA0,
    GX_LINES = 0xA8,
    GX_LINESTRIP = 0xB0,
    GX_POINTS = 0xB8,
} GXPrimitive;

typedef enum _GXVtxFmt {
    GX_VTXFMT0,
    GX_VTXFMT1,
    GX_VTXFMT2,
    GX_VTXFMT3,
    GX_VTXFMT4,
    GX_VTXFMT5,
    GX_VTXFMT6,
    GX_VTXFMT7,
    GX_MAX_VTXFMT,
} GXVtxFmt;

typedef enum _GXAttr {
    GX_VA_PNMTXIDX,
    GX_VA_TEX0MTXIDX,
    GX_VA_TEX1MTXIDX,
    GX_VA_TEX2MTXIDX,
    GX_VA_TEX3MTXIDX,
    GX_VA_TEX4MTXIDX,
    GX_VA_TEX5MTXIDX,
    GX_VA_TEX6MTXIDX,
    GX_VA_TEX7MTXIDX,
    GX_VA_POS,
    GX_VA_NRM,
    GX_VA_CLR0,
    GX_VA_CLR1,
    GX_VA_TEX0,
    GX_VA_TEX1,
    GX_VA_TEX2,
    GX_VA_TEX3,
    GX_VA_TEX4,
    GX_VA_TEX5,
    GX_VA_TEX6,
    GX_VA_TEX7,
    GX_POS_MTX_ARRAY,
    GX_NRM_MTX_ARRAY,
    GX_TEX_MTX_ARRAY,
    GX_LIGHT_ARRAY,
    GX_VA_NBT,
    GX_VA_MAX_ATTR,
    GX_VA_NULL = 0xFF,
} GXAttr;

typedef enum _GXAttrType {
    GX_NONE,
    GX_DIRECT,
    GX_INDEX8,
    GX_INDEX16,
} GXAttrType;

#define _GX_TF_CTF 0x20
#define _GX_TF_ZTF 0x10

typedef enum _GXTexFmt {
    GX_TF_I4 = 0x0,
    GX_TF_I8 = 0x1,
    GX_TF_IA4 = 0x2,
    GX_TF_IA8 = 0x3,
    GX_TF_RGB565 = 0x4,
    GX_TF_RGB5A3 = 0x5,
    GX_TF_RGBA8 = 0x6,
    GX_TF_CMPR = 0xE,

    GX_CTF_R4 = 0x0 | _GX_TF_CTF,
    GX_CTF_RA4 = 0x2 | _GX_TF_CTF,
    GX_CTF_RA8 = 0x3 | _GX_TF_CTF,
    GX_CTF_YUVA8 = 0x6 | _GX_TF_CTF,
    GX_CTF_A8 = 0x7 | _GX_TF_CTF,
    GX_CTF_R8 = 0x8 | _GX_TF_CTF,
    GX_CTF_G8 = 0x9 | _GX_TF_CTF,
    GX_CTF_B8 = 0xA | _GX_TF_CTF,
    GX_CTF_RG8 = 0xB | _GX_TF_CTF,
    GX_CTF_GB8 = 0xC | _GX_TF_CTF,

    GX_TF_Z8 = 0x1 | _GX_TF_ZTF,
    GX_TF_Z16 = 0x3 | _GX_TF_ZTF,
    GX_TF_Z24X8 = 0x6 | _GX_TF_ZTF,

    GX_CTF_Z4 = 0x0 | _GX_TF_ZTF | _GX_TF_CTF,
    GX_CTF_Z8M = 0x9 | _GX_TF_ZTF | _GX_TF_CTF,
    GX_CTF_Z8L = 0xA | _GX_TF_ZTF | _GX_TF_CTF,
    GX_CTF_Z16L = 0xC | _GX_TF_ZTF | _GX_TF_CTF,

    GX_TF_A8 = GX_CTF_A8,
} GXTexFmt;

typedef enum _GXCITexFmt {
    GX_TF_C4 = 0x8,
    GX_TF_C8 = 0x9,
    GX_TF_C14X2 = 0xA,
} GXCITexFmt;

typedef enum _GXTexWrapMode {
    GX_CLAMP,
    GX_REPEAT,
    GX_MIRROR,
    GX_MAX_TEXWRAPMODE,
} GXTexWrapMode;

typedef enum _GXTexFilter {
    GX_NEAR,
    GX_LINEAR,
    GX_NEAR_MIP_NEAR,
    GX_LIN_MIP_NEAR,
    GX_NEAR_MIP_LIN,
    GX_LIN_MIP_LIN,
} GXTexFilter;

typedef enum _GXAnisotropy {
    GX_ANISO_1,
    GX_ANISO_2,
    GX_ANISO_4,
    GX_MAX_ANISOTROPY,
} GXAnisotropy;

typedef enum _GXTexMapID {
    GX_TEXMAP0,
    GX_TEXMAP1,
    GX_TEXMAP2,
    GX_TEXMAP3,
    GX_TEXMAP4,
    GX_TEXMAP5,
    GX_TEXMAP6,
    GX_TEXMAP7,
    GX_MAX_TEXMAP,
    GX_TEXMAP_NULL = 0xFF,
    GX_TEX_DISABLE = 0x100,
} GXTexMapID;

typedef enum _GXTexCoordID {
    GX_TEXCOORD0,
    GX_TEXCOORD1,
    GX_TEXCOORD2,
    GX_TEXCOORD3,
    GX_TEXCOORD4,
    GX_TEXCOORD5,
    GX_TEXCOORD6,
    GX_TEXCOORD7,
    GX_MAX_TEXCOORD,
    GX_TEXCOORD_NULL = 0xFF,
} GXTexCoordID;

typedef enum _GXTevStageID {
    GX_TEVSTAGE0,
    GX_TEVSTAGE1,
    GX_TEVSTAGE2,
    GX_TEVSTAGE3,
    GX_TEVSTAGE4,
    GX_TEVSTAGE5,
    GX_TEVSTAGE6,
    GX_TEVSTAGE7,
    GX_TEVSTAGE8,
    GX_TEVSTAGE9,
    GX_TEVSTAGE10,
    GX_TEVSTAGE11,
    GX_TEVSTAGE12,
    GX_TEVSTAGE13,
    GX_TEVSTAGE14,
    GX_TEVSTAGE15,
    GX_MAX_TEVSTAGE,
} GXTevStageID;

typedef enum _GXTevMode {
    GX_MODULATE,
    GX_DECAL,
    GX_BLEND,
    GX_REPLACE,
    GX_PASSCLR,
} GXTevMode;

typedef enum _GXTexMtxType {
    GX_MTX3x4,
    GX_MTX2x4,
} GXTexMtxType;

typedef enum _GXTexGenType {
    GX_TG_MTX3x4,
    GX_TG_MTX2x4,
    GX_TG_BUMP0,
    GX_TG_BUMP1,
    GX_TG_BUMP2,
    GX_TG_BUMP3,
    GX_TG_BUMP4,
    GX_TG_BUMP5,
    GX_TG_BUMP6,
    GX_TG_BUMP7,
    GX_TG_SRTG,
} GXTexGenType;

typedef enum _GXPosNrmMtx {
    GX_PNMTX0 = 0,
    GX_PNMTX1 = 3,
    GX_PNMTX2 = 6,
    GX_PNMTX3 = 9,
    GX_PNMTX4 = 12,
    GX_PNMTX5 = 15,
    GX_PNMTX6 = 18,
    GX_PNMTX7 = 21,
    GX_PNMTX8 = 24,
    GX_PNMTX9 = 27,
} GXPosNrmMtx;

typedef enum _GXTexMtx {
    GX_TEXMTX0 = 30,
    GX_TEXMTX1 = 33,
    GX_TEXMTX2 = 36,
    GX_TEXMTX3 = 39,
    GX_TEXMTX4 = 42,
    GX_TEXMTX5 = 45,
    GX_TEXMTX6 = 48,
    GX_TEXMTX7 = 51,
    GX_TEXMTX8 = 54,
    GX_TEXMTX9 = 57,
    GX_IDENTITY = 60,
} GXTexMtx;

typedef enum _GXChannelID {
    GX_COLOR0,
    GX_COLOR1,
    GX_ALPHA0,
    GX_ALPHA1,
    GX_COLOR0A0,
    GX_COLOR1A1,
    GX_COLOR_ZERO,
    GX_ALPHA_BUMP,
    GX_ALPHA_BUMPN,
    GX_COLOR_NULL = 0xFF,
} GXChannelID;

typedef enum _GXTexGenSrc {
    GX_TG_POS,
    GX_TG_NRM,
    GX_TG_BINRM,
    GX_TG_TANGENT,
    GX_TG_TEX0,
    GX_TG_TEX1,
    GX_TG_TEX2,
    GX_TG_TEX3,
    GX_TG_TEX4,
    GX_TG_TEX5,
    GX_TG_TEX6,
    GX_TG_TEX7,
    GX_TG_TEXCOORD0,
    GX_TG_TEXCOORD1,
    GX_TG_TEXCOORD2,
    GX_TG_TEXCOORD3,
    GX_TG_TEXCOORD4,
    GX_TG_TEXCOORD5,
    GX_TG_TEXCOORD6,
    GX_TG_COLOR0,
    GX_TG_COLOR1,
} GXTexGenSrc;

typedef enum _GXBlendMode {
    GX_BM_NONE,
    GX_BM_BLEND,
    GX_BM_LOGIC,
    GX_BM_SUBTRACT,
    GX_MAX_BLENDMODE,
} GXBlendMode;

typedef enum _GXBlendFactor {
    GX_BL_ZERO,
    GX_BL_ONE,
    GX_BL_SRCCLR,
    GX_BL_INVSRCCLR,
    GX_BL_SRCALPHA,
    GX_BL_INVSRCALPHA,
    GX_BL_DSTALPHA,
    GX_BL_INVDSTALPHA,
    GX_BL_DSTCLR = GX_BL_SRCCLR,
    GX_BL_INVDSTCLR = GX_BL_INVSRCCLR,
} GXBlendFactor;

typedef enum _GXLogicOp {
    GX_LO_CLEAR,
    GX_LO_AND,
    GX_LO_REVAND,
    GX_LO_COPY,
    GX_LO_INVAND,
    GX_LO_NOOP,
    GX_LO_XOR,
    GX_LO_OR,
    GX_LO_NOR,
    GX_LO_EQUIV,
    GX_LO_INV,
    GX_LO_REVOR,
    GX_LO_INVCOPY,
    GX_LO_INVOR,
    GX_LO_NAND,
    GX_LO_SET,
} GXLogicOp;

typedef enum _GXCompCnt {
    GX_POS_XY = 0,
    GX_POS_XYZ = 1,
    GX_NRM_XYZ = 0,
    GX_NRM_NBT = 1,
    GX_NRM_NBT3 = 2,
    GX_CLR_RGB = 0,
    GX_CLR_RGBA = 1,
    GX_TEX_S = 0,
    GX_TEX_ST = 1,
    GX_COMPCNT_NULL = 0,
} GXCompCnt;

typedef enum _GXCompType {
    GX_U8 = 0,
    GX_S8 = 1,
    GX_U16 = 2,
    GX_S16 = 3,
    GX_F32 = 4,
    GX_RGB565 = 0,
    GX_RGB8 = 1,
    GX_RGBX8 = 2,
    GX_RGBA4 = 3,
    GX_RGBA6 = 4,
    GX_RGBA8 = 5,
    GX_COMP_NULL = 0,
} GXCompType;

typedef enum _GXPTTexMtx {
    GX_PTTEXMTX0 = 64,
    GX_PTTEXMTX1 = 67,
    GX_PTTEXMTX2 = 70,
    GX_PTTEXMTX3 = 73,
    GX_PTTEXMTX4 = 76,
    GX_PTTEXMTX5 = 79,
    GX_PTTEXMTX6 = 82,
    GX_PTTEXMTX7 = 85,
    GX_PTTEXMTX8 = 88,
    GX_PTTEXMTX9 = 91,
    GX_PTTEXMTX10 = 94,
    GX_PTTEXMTX11 = 97,
    GX_PTTEXMTX12 = 100,
    GX_PTTEXMTX13 = 103,
    GX_PTTEXMTX14 = 106,
    GX_PTTEXMTX15 = 109,
    GX_PTTEXMTX16 = 112,
    GX_PTTEXMTX17 = 115,
    GX_PTTEXMTX18 = 118,
    GX_PTTEXMTX19 = 121,
    GX_PTIDENTITY = 125,
} GXPTTexMtx;

typedef enum _GXTevRegID {
    GX_TEVPREV,
    GX_TEVREG0,
    GX_TEVREG1,
    GX_TEVREG2,
    GX_MAX_TEVREG,
} GXTevRegID;

typedef enum _GXDiffuseFn {
    GX_DF_NONE,
    GX_DF_SIGN,
    GX_DF_CLAMP,
} GXDiffuseFn;

typedef enum _GXColorSrc {
    GX_SRC_REG,
    GX_SRC_VTX,
} GXColorSrc;

typedef enum _GXAttnFn {
    GX_AF_SPEC,
    GX_AF_SPOT,
    GX_AF_NONE,
} GXAttnFn;

typedef enum _GXLightID {
    GX_LIGHT0 = 0x001,
    GX_LIGHT1 = 0x002,
    GX_LIGHT2 = 0x004,
    GX_LIGHT3 = 0x008,
    GX_LIGHT4 = 0x010,
    GX_LIGHT5 = 0x020,
    GX_LIGHT6 = 0x040,
    GX_LIGHT7 = 0x080,
    GX_MAX_LIGHT = 0x100,
    GX_LIGHT_NULL = 0,
} GXLightID;

typedef enum _GXTexOffset {
    GX_TO_ZERO,
    GX_TO_SIXTEENTH,
    GX_TO_EIGHTH,
    GX_TO_FOURTH,
    GX_TO_HALF,
    GX_TO_ONE,
    GX_MAX_TEXOFFSET,
} GXTexOffset;

typedef enum _GXSpotFn {
    GX_SP_OFF,
    GX_SP_FLAT,
    GX_SP_COS,
    GX_SP_COS2,
    GX_SP_SHARP,
    GX_SP_RING1,
    GX_SP_RING2,
} GXSpotFn;

typedef enum _GXDistAttnFn {
    GX_DA_OFF,
    GX_DA_GENTLE,
    GX_DA_MEDIUM,
    GX_DA_STEEP,
} GXDistAttnFn;

typedef enum _GXCullMode {
    GX_CULL_NONE,
    GX_CULL_FRONT,
    GX_CULL_BACK,
    GX_CULL_ALL,
} GXCullMode;

typedef enum _GXTevSwapSel {
    GX_TEV_SWAP0 = 0,
    GX_TEV_SWAP1,
    GX_TEV_SWAP2,
    GX_TEV_SWAP3,
    GX_MAX_TEVSWAP,
} GXTevSwapSel;

typedef enum _GXTevColorChan {
    GX_CH_RED = 0,
    GX_CH_GREEN,
    GX_CH_BLUE,
    GX_CH_ALPHA,
} GXTevColorChan;

typedef enum _GXFogType {
    GX_FOG_NONE = 0,
    GX_FOG_LIN = 2,
    GX_FOG_EXP = 4,
    GX_FOG_EXP2 = 5,
    GX_FOG_REVEXP = 6,
    GX_FOG_REVEXP2 = 7,
} GXFogType;

typedef enum _GXTevColorArg {
    GX_CC_CPREV,
    GX_CC_APREV,
    GX_CC_C0,
    GX_CC_A0,
    GX_CC_C1,
    GX_CC_A1,
    GX_CC_C2,
    GX_CC_A2,
    GX_CC_TEXC,
    GX_CC_TEXA,
    GX_CC_RASC,
    GX_CC_RASA,
    GX_CC_ONE,
    GX_CC_HALF,
    GX_CC_KONST,
    GX_CC_ZERO,
} GXTevColorArg;

typedef enum _GXTevAlphaArg {
    GX_CA_APREV,
    GX_CA_A0,
    GX_CA_A1,
    GX_CA_A2,
    GX_CA_TEXA,
    GX_CA_RASA,
    GX_CA_KONST,
    GX_CA_ZERO,
} GXTevAlphaArg;

typedef enum _GXTevOp {
    GX_TEV_ADD = 0,
    GX_TEV_SUB = 1,
    GX_TEV_COMP_R8_GT = 8,
    GX_TEV_COMP_R8_EQ = 9,
    GX_TEV_COMP_GR16_GT = 10,
    GX_TEV_COMP_GR16_EQ = 11,
    GX_TEV_COMP_BGR24_GT = 12,
    GX_TEV_COMP_BGR24_EQ = 13,
    GX_TEV_COMP_RGB8_GT = 14,
    GX_TEV_COMP_RGB8_EQ = 15,
    GX_TEV_COMP_A8_GT = GX_TEV_COMP_RGB8_GT,
    GX_TEV_COMP_A8_EQ = GX_TEV_COMP_RGB8_EQ,
} GXTevOp;

typedef enum _GXTevBias {
    GX_TB_ZERO,
    GX_TB_ADDHALF,
    GX_TB_SUBHALF,
    GX_MAX_TEVBIAS,
} GXTevBias;

typedef enum _GXTevScale {
    GX_CS_SCALE_1,
    GX_CS_SCALE_2,
    GX_CS_SCALE_4,
    GX_CS_DIVIDE_2,
    GX_MAX_TEVSCALE,
} GXTevScale;

typedef enum _GXTevKColorSel {
    GX_TEV_KCSEL_1 = 0x00,
    GX_TEV_KCSEL_7_8 = 0x01,
    GX_TEV_KCSEL_3_4 = 0x02,
    GX_TEV_KCSEL_5_8 = 0x03,
    GX_TEV_KCSEL_1_2 = 0x04,
    GX_TEV_KCSEL_3_8 = 0x05,
    GX_TEV_KCSEL_1_4 = 0x06,
    GX_TEV_KCSEL_1_8 = 0x07,
    GX_TEV_KCSEL_K0 = 0x0C,
    GX_TEV_KCSEL_K1 = 0x0D,
    GX_TEV_KCSEL_K2 = 0x0E,
    GX_TEV_KCSEL_K3 = 0x0F,
    GX_TEV_KCSEL_K0_R = 0x10,
    GX_TEV_KCSEL_K1_R = 0x11,
    GX_TEV_KCSEL_K2_R = 0x12,
    GX_TEV_KCSEL_K3_R = 0x13,
    GX_TEV_KCSEL_K0_G = 0x14,
    GX_TEV_KCSEL_K1_G = 0x15,
    GX_TEV_KCSEL_K2_G = 0x16,
    GX_TEV_KCSEL_K3_G = 0x17,
    GX_TEV_KCSEL_K0_B = 0x18,
    GX_TEV_KCSEL_K1_B = 0x19,
    GX_TEV_KCSEL_K2_B = 0x1A,
    GX_TEV_KCSEL_K3_B = 0x1B,
    GX_TEV_KCSEL_K0_A = 0x1C,
    GX_TEV_KCSEL_K1_A = 0x1D,
    GX_TEV_KCSEL_K2_A = 0x1E,
    GX_TEV_KCSEL_K3_A = 0x1F,
} GXTevKColorSel;

typedef enum _GXTevKAlphaSel {
    GX_TEV_KASEL_1 = 0x00,
    GX_TEV_KASEL_7_8 = 0x01,
    GX_TEV_KASEL_3_4 = 0x02,
    GX_TEV_KASEL_5_8 = 0x03,
    GX_TEV_KASEL_1_2 = 0x04,
    GX_TEV_KASEL_3_8 = 0x05,
    GX_TEV_KASEL_1_4 = 0x06,
    GX_TEV_KASEL_1_8 = 0x07,
    GX_TEV_KASEL_K0_R = 0x10,
    GX_TEV_KASEL_K1_R = 0x11,
    GX_TEV_KASEL_K2_R = 0x12,
    GX_TEV_KASEL_K3_R = 0x13,
    GX_TEV_KASEL_K0_G = 0x14,
    GX_TEV_KASEL_K1_G = 0x15,
    GX_TEV_KASEL_K2_G = 0x16,
    GX_TEV_KASEL_K3_G = 0x17,
    GX_TEV_KASEL_K0_B = 0x18,
    GX_TEV_KASEL_K1_B = 0x19,
    GX_TEV_KASEL_K2_B = 0x1A,
    GX_TEV_KASEL_K3_B = 0x1B,
    GX_TEV_KASEL_K0_A = 0x1C,
    GX_TEV_KASEL_K1_A = 0x1D,
    GX_TEV_KASEL_K2_A = 0x1E,
    GX_TEV_KASEL_K3_A = 0x1F,
} GXTevKAlphaSel;

typedef enum _GXTevKColorID {
    GX_KCOLOR0 = 0,
    GX_KCOLOR1,
    GX_KCOLOR2,
    GX_KCOLOR3,
    GX_MAX_KCOLOR,
} GXTevKColorID;

typedef enum _GXZTexOp {
    GX_ZT_DISABLE,
    GX_ZT_ADD,
    GX_ZT_REPLACE,
    GX_MAX_ZTEXOP,
} GXZTexOp;

typedef enum _GXIndTexFormat {
    GX_ITF_8,
    GX_ITF_5,
    GX_ITF_4,
    GX_ITF_3,
    GX_MAX_ITFORMAT,
} GXIndTexFormat;

typedef enum _GXIndTexBiasSel {
    GX_ITB_NONE,
    GX_ITB_S,
    GX_ITB_T,
    GX_ITB_ST,
    GX_ITB_U,
    GX_ITB_SU,
    GX_ITB_TU,
    GX_ITB_STU,
    GX_MAX_ITBIAS,
} GXIndTexBiasSel;

typedef enum _GXIndTexAlphaSel {
    GX_ITBA_OFF,
    GX_ITBA_S,
    GX_ITBA_T,
    GX_ITBA_U,
    GX_MAX_ITBALPHA,
} GXIndTexAlphaSel;

typedef enum _GXIndTexMtxID {
    GX_ITM_OFF,
    GX_ITM_0,
    GX_ITM_1,
    GX_ITM_2,
    GX_ITM_S0 = 5,
    GX_ITM_S1,
    GX_ITM_S2,
    GX_ITM_T0 = 9,
    GX_ITM_T1,
    GX_ITM_T2,
} GXIndTexMtxID;

typedef enum _GXIndTexWrap {
    GX_ITW_OFF,
    GX_ITW_256,
    GX_ITW_128,
    GX_ITW_64,
    GX_ITW_32,
    GX_ITW_16,
    GX_ITW_0,
    GX_MAX_ITWRAP,
} GXIndTexWrap;

typedef enum _GXIndTexStageID {
    GX_INDTEXSTAGE0,
    GX_INDTEXSTAGE1,
    GX_INDTEXSTAGE2,
    GX_INDTEXSTAGE3,
    GX_MAX_INDTEXSTAGE,
} GXIndTexStageID;

typedef enum _GXIndTexScale {
    GX_ITS_1,
    GX_ITS_2,
    GX_ITS_4,
    GX_ITS_8,
    GX_ITS_16,
    GX_ITS_32,
    GX_ITS_64,
    GX_ITS_128,
    GX_ITS_256,
    GX_MAX_ITSCALE,
} GXIndTexScale;

typedef enum _GXPerf0 {
    GX_PERF0_VERTICES,
    GX_PERF0_CLIP_VTX,
    GX_PERF0_CLIP_CLKS,
    GX_PERF0_XF_WAIT_IN,
    GX_PERF0_XF_WAIT_OUT,
    GX_PERF0_XF_XFRM_CLKS,
    GX_PERF0_XF_LIT_CLKS,
    GX_PERF0_XF_BOT_CLKS,
    GX_PERF0_XF_REGLD_CLKS,
    GX_PERF0_XF_REGRD_CLKS,
    GX_PERF0_CLIP_RATIO,

    GX_PERF0_TRIANGLES,
    GX_PERF0_TRIANGLES_CULLED,
    GX_PERF0_TRIANGLES_PASSED,
    GX_PERF0_TRIANGLES_SCISSORED,
    GX_PERF0_TRIANGLES_0TEX,
    GX_PERF0_TRIANGLES_1TEX,
    GX_PERF0_TRIANGLES_2TEX,
    GX_PERF0_TRIANGLES_3TEX,
    GX_PERF0_TRIANGLES_4TEX,
    GX_PERF0_TRIANGLES_5TEX,
    GX_PERF0_TRIANGLES_6TEX,
    GX_PERF0_TRIANGLES_7TEX,
    GX_PERF0_TRIANGLES_8TEX,
    GX_PERF0_TRIANGLES_0CLR,
    GX_PERF0_TRIANGLES_1CLR,
    GX_PERF0_TRIANGLES_2CLR,

    GX_PERF0_QUAD_0CVG,
    GX_PERF0_QUAD_NON0CVG,
    GX_PERF0_QUAD_1CVG,
    GX_PERF0_QUAD_2CVG,
    GX_PERF0_QUAD_3CVG,
    GX_PERF0_QUAD_4CVG,
    GX_PERF0_AVG_QUAD_CNT,

    GX_PERF0_CLOCKS,
    GX_PERF0_NONE,
} GXPerf0;

typedef enum _GXPerf1 {
    GX_PERF1_TEXELS,
    GX_PERF1_TX_IDLE,
    GX_PERF1_TX_REGS,
    GX_PERF1_TX_MEMSTALL,
    GX_PERF1_TC_CHECK1_2,
    GX_PERF1_TC_CHECK3_4,
    GX_PERF1_TC_CHECK5_6,
    GX_PERF1_TC_CHECK7_8,
    GX_PERF1_TC_MISS,

    GX_PERF1_VC_ELEMQ_FULL,
    GX_PERF1_VC_MISSQ_FULL,
    GX_PERF1_VC_MEMREQ_FULL,
    GX_PERF1_VC_STATUS7,
    GX_PERF1_VC_MISSREP_FULL,
    GX_PERF1_VC_STREAMBUF_LOW,
    GX_PERF1_VC_ALL_STALLS,
    GX_PERF1_VERTICES,

    GX_PERF1_FIFO_REQ,
    GX_PERF1_CALL_REQ,
    GX_PERF1_VC_MISS_REQ,
    GX_PERF1_CP_ALL_REQ,

    GX_PERF1_CLOCKS,
    GX_PERF1_NONE,
} GXPerf1;

typedef enum _GXVCachePerf {
    GX_VC_POS,
    GX_VC_NRM,
    GX_VC_CLR0,
    GX_VC_CLR1,
    GX_VC_TEX0,
    GX_VC_TEX1,
    GX_VC_TEX2,
    GX_VC_TEX3,
    GX_VC_TEX4,
    GX_VC_TEX5,
    GX_VC_TEX6,
    GX_VC_TEX7,
    GX_VC_ALL = 0xF,
} GXVCachePerf;

typedef enum _GXMiscToken {
    GX_MT_NULL,
    GX_MT_XF_FLUSH,
    GX_MT_DL_SAVE_CONTEXT,
    GX_MT_ABORT_WAIT_COPYOUT,
} GXMiscToken;

typedef enum _GXClipMode {
    GX_CLIP_ENABLE = 0,
    GX_CLIP_DISABLE = 1,
} GXClipMode;

typedef enum _GXFBClamp {
    GX_CLAMP_NONE = 0,
    GX_CLAMP_TOP = 1,
    GX_CLAMP_BOTTOM = 2,
    GX_CLAMP_BOTH = GX_CLAMP_TOP | GX_CLAMP_BOTTOM,
} GXFBClamp;

typedef enum _GXCopyMode {
    GX_COPY_PROGRESSIVE = 0,
    GX_COPY_INTLC_EVEN = 2,
    GX_COPY_INTLC_ODD = 3,
} GXCopyMode;

typedef enum _GXAlphaReadMode {
    GX_READ_00,
    GX_READ_FF,
    GX_READ_NONE,
} GXAlphaReadMode;

typedef enum _GXTexCacheSize {
    GX_TEXCACHE_32K,
    GX_TEXCACHE_128K,
    GX_TEXCACHE_512K,
    GX_TEXCACHE_NONE,
} GXTexCacheSize;

typedef enum _GXTlut {
    GX_TLUT0,
    GX_TLUT1,
    GX_TLUT2,
    GX_TLUT3,
    GX_TLUT4,
    GX_TLUT5,
    GX_TLUT6,
    GX_TLUT7,
    GX_TLUT8,
    GX_TLUT9,
    GX_TLUT10,
    GX_TLUT11,
    GX_TLUT12,
    GX_TLUT13,
    GX_TLUT14,
    GX_TLUT15,
    GX_BIGTLUT0,
    GX_BIGTLUT1,
    GX_BIGTLUT2,
    GX_BIGTLUT3,

    GX_MAX_TLUT = 16,
    GX_MAX_BIGTLUT = 4,
    GX_MAX_TLUT_ALL = GX_MAX_TLUT + GX_MAX_BIGTLUT,
} GXTlut;

typedef enum _GXTlutFmt {
    GX_TL_IA8,
    GX_TL_RGB565,
    GX_TL_RGB5A3,
    GX_MAX_TLUTFMT,
} GXTlutFmt;

typedef enum _GXTlutSize {
    GX_TLUT_16 = 1,
    GX_TLUT_32 = 2,
    GX_TLUT_64 = 4,
    GX_TLUT_128 = 8,
    GX_TLUT_256 = 16,
    GX_TLUT_512 = 32,
    GX_TLUT_1K = 64,
    GX_TLUT_2K = 128,
    GX_TLUT_4K = 256,
    GX_TLUT_8K = 512,
    GX_TLUT_16K = 1024,
} GXTlutSize;

// TEV clamp modes.
typedef enum _GXTevClampMode {
    GX_TC_LINEAR = 0,
    GX_TC_GE = 1,
    GX_TC_EQ = 2,
    GX_TC_LE = 3,

    GX_MAX_TEVCLAMPMODE, // Max num clamp modes (4).
} GXTevClampMode;

typedef enum _GXDirtyFlag {
    GX_DIRTY_SU_TEX = (1 << 0), // 0x1
    GX_DIRTY_BP_MASK = (1 << 1), // 0x2
    GX_DIRTY_GEN_MODE = (1 << 2), // 0x4
    GX_DIRTY_VCD = (1 << 3), // 0x8
    GX_DIRTY_VAT = (1 << 4), // 0x10
    // . . .
    GX_DIRTY_AMB_COLOR0 = (1 << 8), // 0x100
    GX_DIRTY_AMB_COLOR1 = (1 << 9), // 0x200
    GX_DIRTY_MAT_COLOR0 = (1 << 10), // 0x400
    GX_DIRTY_MAT_COLOR1 = (1 << 11), // 0x800
    GX_DIRTY_CHAN_COLOR0 = (1 << 12), // 0x1000
    GX_DIRTY_CHAN_COLOR1 = (1 << 13), // 0x2000
    GX_DIRTY_CHAN_ALPHA0 = (1 << 14), // 0x4000
    GX_DIRTY_CHAN_ALPHA1 = (1 << 15), // 0x8000
    GX_DIRTY_TEX0 = (1 << 16), // 0x10000
    GX_DIRTY_TEX1 = (1 << 17), // 0x20000
    GX_DIRTY_TEX2 = (1 << 18), // 0x40000
    GX_DIRTY_TEX3 = (1 << 19), // 0x80000
    GX_DIRTY_TEX4 = (1 << 20), // 0x100000
    GX_DIRTY_TEX5 = (1 << 21), // 0x200000
    GX_DIRTY_TEX6 = (1 << 22), // 0x400000
    GX_DIRTY_TEX7 = (1 << 23), // 0x800000
    GX_DIRTY_NUM_COLORS = (1 << 24), // 0x1000000
    GX_DIRTY_NUM_TEX = (1 << 25), // 0x2000000
    GX_DIRTY_MTX_IDX = (1 << 26), // 0x4000000
    GX_DIRTY_PROJECTION = (1 << 27), // 0x8000000
    GX_DIRTY_VIEWPORT = (1 << 28), // 0x10000000

    GX_AMB_MAT_MASK = GX_DIRTY_AMB_COLOR0 | GX_DIRTY_AMB_COLOR1 | GX_DIRTY_MAT_COLOR0 | GX_DIRTY_MAT_COLOR1, // 0xF00

    GX_LIGHT_CHAN_MASK = GX_DIRTY_CHAN_COLOR0 | GX_DIRTY_CHAN_COLOR1 | GX_DIRTY_CHAN_ALPHA0 | GX_DIRTY_CHAN_ALPHA1 |
                         GX_DIRTY_NUM_COLORS, // 0x100F000

    GX_TEX_GEN_MASK = 0x2FF0000, // all GX_DIRTY_TEXs | GX_DIRTY_NUM_TEX
} GXDirtyFlag;

// Commands for interacting with the GXFifo pipe.
typedef enum _GXFifoCmd {
    GX_FIFO_CMD_NOOP = 0x00, // no operation

    GX_FIFO_CMD_LOAD_BP_REG = 0x61, // load blitting processor reg
    GX_FIFO_CMD_LOAD_CP_REG = 0x08, // load command processor reg
    GX_FIFO_CMD_LOAD_XF_REG = 0x10, // load transform unit reg

    GX_FIFO_CMD_LOAD_INDX_A = 0x20, // load index A
    GX_FIFO_CMD_LOAD_INDX_B = 0x28, // load index B
    GX_FIFO_CMD_LOAD_INDX_C = 0x30, // load index C
    GX_FIFO_CMD_LOAD_INDX_D = 0x38, // load index D

    GX_FIFO_CMD_CALL_DL = 0x40, // call displaylist
    GX_FIFO_CMD_INVAL_VTX = 0x48, // invalid vertex
} GXFifoCmd;

// Transform unit registers.
typedef enum _GXXFRegs {
    GX_XF_REG_ERROR = 0x1000,
    GX_XF_REG_DIAGNOSTICS = 0x1001,
    GX_XF_REG_STATE0 = 0x1002,
    GX_XF_REG_STATE1 = 0x1003,
    GX_XF_REG_CLOCK = 0x1004,
    GX_XF_REG_CLIPDISABLE = 0x1005,
    GX_XF_REG_PERF0 = 0x1006,
    GX_XF_REG_PERF1 = 0x1007,
    GX_XF_REG_INVERTEXSPEC = 0x1008,
    GX_XF_REG_NUMCOLORS = 0x1009,
    GX_XF_REG_AMBIENT0 = 0x100A,
    GX_XF_REG_AMBIENT1 = 0x100B,
    GX_XF_REG_MATERIAL0 = 0x100C,
    GX_XF_REG_MATERIAL1 = 0x100D,
    GX_XF_REG_COLOR0CNTRL = 0x100E,
    GX_XF_REG_COLOR1CNTRL = 0x100F,
    GX_XF_REG_ALPHA0CNTRL = 0x1010,
    GX_XF_REG_ALPHA1CNTRL = 0x1011,
    GX_XF_REG_DUALTEXTRAN = 0x1012,
    GX_XF_REG_MATRIXINDEX0 = 0x1018,
    GX_XF_REG_MATRIXINDEX1 = 0x1019,
    GX_XF_REG_SCALEX = 0x101A,
    GX_XF_REG_SCALEY = 0x101B,
    GX_XF_REG_SCALEZ = 0x101C,
    GX_XF_REG_OFFSETX = 0x101D,
    GX_XF_REG_OFFSETY = 0x101E,
    GX_XF_REG_OFFSETZ = 0x101F,
    GX_XF_REG_PROJECTIONA = 0x1020,
    GX_XF_REG_PROJECTIONB = 0x1021,
    GX_XF_REG_PROJECTIONC = 0x1022,
    GX_XF_REG_PROJECTIOND = 0x1023,
    GX_XF_REG_PROJECTIONE = 0x1024,
    GX_XF_REG_PROJECTIONF = 0x1025,
    GX_XF_REG_PROJECTORTHO = 0x1026,
    GX_XF_REG_NUMTEX = 0x103F,
    GX_XF_REG_TEX0 = 0x1040,
    GX_XF_REG_TEX1 = 0x1041,
    GX_XF_REG_TEX2 = 0x1042,
    GX_XF_REG_TEX3 = 0x1043,
    GX_XF_REG_TEX4 = 0x1044,
    GX_XF_REG_TEX5 = 0x1045,
    GX_XF_REG_TEX6 = 0x1046,
    GX_XF_REG_TEX7 = 0x1047,
    GX_XF_REG_DUALTEX0 = 0x1050,
    GX_XF_REG_DUALTEX1 = 0x1051,
    GX_XF_REG_DUALTEX2 = 0x1052,
    GX_XF_REG_DUALTEX3 = 0x1053,
    GX_XF_REG_DUALTEX4 = 0x1054,
    GX_XF_REG_DUALTEX5 = 0x1055,
    GX_XF_REG_DUALTEX6 = 0x1056,
    GX_XF_REG_DUALTEX7 = 0x1057,
} GXXFRegs;

// CP locator for vertex descriptor (lo).
typedef enum _GXCPVCDLo {
    // Position matrix idx [31]
    GX_CP_VCD_LO_POSMTXIDX_ST = 31,
    GX_CP_VCD_LO_POSMTXIDX_END = 31,

    // Tex 0 matrix idx [30]
    GX_CP_VCD_LO_TEX0MTXIDX_ST = 30,
    GX_CP_VCD_LO_TEX0MTXIDX_END = 30,

    // Tex 1 matrix idx [29]
    GX_CP_VCD_LO_TEX1MTXIDX_ST = 29,
    GX_CP_VCD_LO_TEX1MTXIDX_END = 29,

    // Tex 2 matrix idx [28]
    GX_CP_VCD_LO_TEX2MTXIDX_ST = 28,
    GX_CP_VCD_LO_TEX2MTXIDX_END = 28,

    // Tex 3 matrix idx [27]
    GX_CP_VCD_LO_TEX3MTXIDX_ST = 27,
    GX_CP_VCD_LO_TEX3MTXIDX_END = 27,

    // Tex 4 matrix idx [26]
    GX_CP_VCD_LO_TEX4MTXIDX_ST = 26,
    GX_CP_VCD_LO_TEX4MTXIDX_END = 26,

    // Tex 5 matrix idx [25]
    GX_CP_VCD_LO_TEX5MTXIDX_ST = 25,
    GX_CP_VCD_LO_TEX5MTXIDX_END = 25,

    // Tex 6 matrix idx [24]
    GX_CP_VCD_LO_TEX6MTXIDX_ST = 24,
    GX_CP_VCD_LO_TEX6MTXIDX_END = 24,

    // Tex 7 matrix idx [23]
    GX_CP_VCD_LO_TEX7MTXIDX_ST = 23,
    GX_CP_VCD_LO_TEX7MTXIDX_END = 23,

    // Position [21-22]
    GX_CP_VCD_LO_POS_ST = 21,
    GX_CP_VCD_LO_POS_END = 22,

    // Normal [19-20]
    GX_CP_VCD_LO_NRM_ST = 19,
    GX_CP_VCD_LO_NRM_END = 20,

    // Color diffused [17-18]
    GX_CP_VCD_LO_CLRDIF_ST = 17,
    GX_CP_VCD_LO_CLRDIF_END = 18,

    // Color specular [15-16]
    GX_CP_VCD_LO_CLRSPEC_ST = 15,
    GX_CP_VCD_LO_CLRSPEC_END = 16,
} GXCPVCDLo;

// CP locators for vertex descriptor (hi).
typedef enum _GXCPVCDHi {
    // Tex0 coordinates [30-31]
    GX_CP_VCD_HI_TEX0COORD_ST = 30,
    GX_CP_VCD_HI_TEX0COORD_END = 31,

    // Tex1 coordinates [28-29]
    GX_CP_VCD_HI_TEX1COORD_ST = 28,
    GX_CP_VCD_HI_TEX1COORD_END = 29,

    // Tex2 coordinates [26-27]
    GX_CP_VCD_HI_TEX2COORD_ST = 26,
    GX_CP_VCD_HI_TEX2COORD_END = 27,

    // Tex3 coordinates [24-25]
    GX_CP_VCD_HI_TEX3COORD_ST = 24,
    GX_CP_VCD_HI_TEX3COORD_END = 25,

    // Tex4 coordinates [22-23]
    GX_CP_VCD_HI_TEX4COORD_ST = 22,
    GX_CP_VCD_HI_TEX4COORD_END = 23,

    // Tex5 coordinates [20-21]
    GX_CP_VCD_HI_TEX5COORD_ST = 20,
    GX_CP_VCD_HI_TEX5COORD_END = 21,

    // Tex6 coordinates [18-19]
    GX_CP_VCD_HI_TEX6COORD_ST = 18,
    GX_CP_VCD_HI_TEX6COORD_END = 19,

    // Tex7 coordinates [16-17]
    GX_CP_VCD_HI_TEX7COORD_ST = 16,
    GX_CP_VCD_HI_TEX7COORD_END = 17,
} GXCPVCDHi;

// Command processor registers.
typedef enum _GXCPRegs {
    GX_CP_REG_MTXIDXA = 0x30, // Matrix index A
    GX_CP_REG_MTXIDXB = 0x40, // Matrix index B
    GX_CP_REG_VCD_LO = 0x50, // Vertex descriptor (lo)
    GX_CP_REG_VCD_HI = 0x60, // Vertex descriptor (hi)
    GX_CP_REG_VAT_GRP0 = 0x70, // Vertex attribute table (group 0)
    GX_CP_REG_VAT_GRP1 = 0x80, // Vertex attribute table (group 1)
    GX_CP_REG_VAT_GRP2 = 0x90, // Vertex attribute table (group 2)
    GX_CP_REG_ARRAYBASE = 0xA0, // Vertex array start/base
    GX_CP_REG_ARRAYSTRIDE = 0xB0, // Vertex array stride
} GXCPRegs;

// CP locator for vertex attribute table (group 0).
typedef enum _GXCPVATGrp0 {
    // Position count [31-31]
    GX_CP_VAT_GRP0_POS_CNT_ST = 31,
    GX_CP_VAT_GRP0_POS_CNT_END = 31,

    // Position type [28-30]
    GX_CP_VAT_GRP0_POS_TYPE_ST = 28,
    GX_CP_VAT_GRP0_POS_TYPE_END = 30,

    // Position shift [23-27]
    GX_CP_VAT_GRP0_POS_SHIFT_ST = 23,
    GX_CP_VAT_GRP0_POS_SHIFT_END = 27,

    // Normal count [22-22]
    GX_CP_VAT_GRP0_NRM_CNT_ST = 22,
    GX_CP_VAT_GRP0_NRM_CNT_END = 22,

    // Normal type [19-21]
    GX_CP_VAT_GRP0_NRM_TYPE_ST = 19,
    GX_CP_VAT_GRP0_NRM_TYPE_END = 21,

    // Color diffused count [18-18]
    GX_CP_VAT_GRP0_CLRDIFF_CNT_ST = 18,
    GX_CP_VAT_GRP0_CLRDIFF_CNT_END = 18,

    // Color diffused type [15-17]
    GX_CP_VAT_GRP0_CLRDIFF_TYPE_ST = 15,
    GX_CP_VAT_GRP0_CLRDIFF_TYPE_END = 17,

    // Color specular count [14-14]
    GX_CP_VAT_GRP0_CLRSPEC_CNT_ST = 14,
    GX_CP_VAT_GRP0_CLRSPEC_CNT_END = 14,

    // Color specular type [11-13]
    GX_CP_VAT_GRP0_CLRSPEC_TYPE_ST = 11,
    GX_CP_VAT_GRP0_CLRSPEC_TYPE_END = 13,

    // Tex0 coord count [10-10]
    GX_CP_VAT_GRP0_TXC0_CNT_ST = 10,
    GX_CP_VAT_GRP0_TXC0_CNT_END = 10,

    // Tex0 coord type [7-9]
    GX_CP_VAT_GRP0_TXC0_TYPE_ST = 7,
    GX_CP_VAT_GRP0_TXC0_TYPE_END = 9,

    // Tex0 coord shift [2-6]
    GX_CP_VAT_GRP0_TXC0_SHIFT_ST = 2,
    GX_CP_VAT_GRP0_TXC0_SHIFT_END = 6,

    // Byte dequantised [1-1]
    GX_CP_VAT_GRP0_BYTEDEQ_ST = 1,
    GX_CP_VAT_GRP0_BYTEDEQ_END = 1,

    // Normal index 3 [0-0] (Input will be treated as three staggered indices (one per triple biased by component size)
    // into normal table))
    GX_CP_VAT_GRP0_NRMIDX3_ST = 0,
    GX_CP_VAT_GRP0_NRMIDX3_END = 0,
} GXCPVATGrp0;

// CP locators for vertex attribute table (group 1).
typedef enum _GXCPVATGrp1 {
    // Tex1 coord count [31-31]
    GX_CP_VAT_GRP1_TXC1_CNT_ST = 31,
    GX_CP_VAT_GRP1_TXC1_CNT_END = 31,

    // Tex1 coord type [28-30]
    GX_CP_VAT_GRP1_TXC1_TYPE_ST = 28,
    GX_CP_VAT_GRP1_TXC1_TYPE_END = 30,

    // Tex1 coord shift [23-27]
    GX_CP_VAT_GRP1_TXC1_SHIFT_ST = 23,
    GX_CP_VAT_GRP1_TXC1_SHIFT_END = 27,

    // Tex2 coord count [22-22]
    GX_CP_VAT_GRP1_TXC2_CNT_ST = 22,
    GX_CP_VAT_GRP1_TXC2_CNT_END = 22,

    // Tex2 coord type [19-21]
    GX_CP_VAT_GRP1_TXC2_TYPE_ST = 19,
    GX_CP_VAT_GRP1_TXC2_TYPE_END = 21,

    // Tex2 coord shift [14-18]
    GX_CP_VAT_GRP1_TXC2_SHIFT_ST = 14,
    GX_CP_VAT_GRP1_TXC2_SHIFT_END = 18,

    // Tex3 coord count [13-13]
    GX_CP_VAT_GRP1_TXC3_CNT_ST = 13,
    GX_CP_VAT_GRP1_TXC3_CNT_END = 13,

    // Tex3 coord type [10-12]
    GX_CP_VAT_GRP1_TXC3_TYPE_ST = 10,
    GX_CP_VAT_GRP1_TXC3_TYPE_END = 12,

    // Tex3 coord shift [5-9]
    GX_CP_VAT_GRP1_TXC3_SHIFT_ST = 5,
    GX_CP_VAT_GRP1_TXC3_SHIFT_END = 9,

    // Tex4 coord count [4-4]
    GX_CP_VAT_GRP1_TXC4_CNT_ST = 4,
    GX_CP_VAT_GRP1_TXC4_CNT_END = 4,

    // Tex4 coord type [1-3]
    GX_CP_VAT_GRP1_TXC4_TYPE_ST = 1,
    GX_CP_VAT_GRP1_TXC4_TYPE_END = 3,

} GXCPVATGrp1;

// CP locators for vertex attribute table (group 2).
typedef enum _GXCPVATGrp2 {
    // Tex4 coord shift [27-31]
    GX_CP_VAT_GRP2_TXC4_SHIFT_ST = 27,
    GX_CP_VAT_GRP2_TXC4_SHIFT_END = 31,

    // Tex5 coord count [26-26]
    GX_CP_VAT_GRP2_TXC5_CNT_ST = 26,
    GX_CP_VAT_GRP2_TXC5_CNT_END = 26,

    // Tex5 coord type [23-25]
    GX_CP_VAT_GRP2_TXC5_TYPE_ST = 23,
    GX_CP_VAT_GRP2_TXC5_TYPE_END = 25,

    // Tex5 coord shift [18-22]
    GX_CP_VAT_GRP2_TXC5_SHIFT_ST = 18,
    GX_CP_VAT_GRP2_TXC5_SHIFT_END = 22,

    // Tex6 coord count [17-17]
    GX_CP_VAT_GRP2_TXC6_CNT_ST = 17,
    GX_CP_VAT_GRP2_TXC6_CNT_END = 17,

    // Tex6 coord type [14-16]
    GX_CP_VAT_GRP2_TXC6_TYPE_ST = 14,
    GX_CP_VAT_GRP2_TXC6_TYPE_END = 16,

    // Tex6 coord shift [9-13]
    GX_CP_VAT_GRP2_TXC6_SHIFT_ST = 9,
    GX_CP_VAT_GRP2_TXC6_SHIFT_END = 13,

    // Tex7 coord count [8-8]
    GX_CP_VAT_GRP2_TXC7_CNT_ST = 8,
    GX_CP_VAT_GRP2_TXC7_CNT_END = 8,

    // Tex7 coord type [5-7]
    GX_CP_VAT_GRP2_TXC7_TYPE_ST = 5,
    GX_CP_VAT_GRP2_TXC7_TYPE_END = 7,

    // Tex7 coord shift [0-4]
    GX_CP_VAT_GRP2_TXC7_SHIFT_ST = 0,
    GX_CP_VAT_GRP2_TXC7_SHIFT_END = 4,
} GXCPVATGrp2;

// Blitting processor registers.
typedef enum _GXBPRegs {
    // gen mode
    GX_BP_REG_GENMODE = 0x0, // gen mode

    // display copy filters
    GX_BP_REG_DISPCOPYFILTER0 = 0x1, // display copy filter 0
    GX_BP_REG_DISPCOPYFILTER1 = 0x2, // display copy filter 1
    GX_BP_REG_DISPCOPYFILTER2 = 0x3, // display copy filter 2
    GX_BP_REG_DISPCOPYFILTER3 = 0x4, // display copy filter 3

    // indirect matrices
    GX_BP_REG_INDMTX0A = 0x6, // indirect matrix 0A
    GX_BP_REG_INDMTX0B = 0x7, // indirect matrix 0B
    GX_BP_REG_INDMTX0C = 0x8, // indirect matrix 0C
    GX_BP_REG_INDMTX1A = 0x9, // indirect matrix 1A
    GX_BP_REG_INDMTX1B = 0xA, // indirect matrix 1B
    GX_BP_REG_INDMTX1C = 0xB, // indirect matrix 1C
    GX_BP_REG_INDMTX2A = 0xC, // indirect matrix 2A
    GX_BP_REG_INDMTX2B = 0xD, // indirect matrix 2B
    GX_BP_REG_INDMTX2C = 0xE, // indirect matrix 2C
    GX_BP_REG_INDIMASK = 0xF, // indirect mask

    // indirect TEV stages
    GX_BP_REG_INDTEVSTAGE0 = 0x10, // indirect TEV stage 0
    GX_BP_REG_INDTEVSTAGE1 = 0x11, // indirect TEV stage 1
    GX_BP_REG_INDTEVSTAGE2 = 0x12, // indirect TEV stage 2
    GX_BP_REG_INDTEVSTAGE3 = 0x13, // indirect TEV stage 3
    GX_BP_REG_INDTEVSTAGE4 = 0x14, // indirect TEV stage 4
    GX_BP_REG_INDTEVSTAGE5 = 0x15, // indirect TEV stage 5
    GX_BP_REG_INDTEVSTAGE6 = 0x16, // indirect TEV stage 6
    GX_BP_REG_INDTEVSTAGE7 = 0x17, // indirect TEV stage 7
    GX_BP_REG_INDTEVSTAGE8 = 0x18, // indirect TEV stage 8
    GX_BP_REG_INDTEVSTAGE9 = 0x19, // indirect TEV stage 9
    GX_BP_REG_INDTEVSTAGE10 = 0x1A, // indirect TEV stage 10
    GX_BP_REG_INDTEVSTAGE11 = 0x1B, // indirect TEV stage 11
    GX_BP_REG_INDTEVSTAGE12 = 0x1C, // indirect TEV stage 12
    GX_BP_REG_INDTEVSTAGE13 = 0x1D, // indirect TEV stage 13
    GX_BP_REG_INDTEVSTAGE14 = 0x1E, // indirect TEV stage 14
    GX_BP_REG_INDTEVSTAGE15 = 0x1F, // indirect TEV stage 15

    // performance manips
    GX_BP_REG_SCISSORTL = 0x20, // scissor top left
    GX_BP_REG_SCISSORBR = 0x21, // scissor bottom right
    GX_BP_REG_LINEPTWIDTH = 0x22, // line point width
    GX_BP_REG_PERF0TRI = 0x23, // performance 0 (triangle)
    GX_BP_REG_PERF0QUAD = 0x24, // performance 0 (quad)

    // rasters
    GX_BP_REG_RAS1_SS0 = 0x25,
    GX_BP_REG_RAS1_SS1 = 0x26,
    GX_BP_REG_RAS1_IREF = 0x27,
    GX_BP_REG_RAS1_TREF0 = 0x28,
    GX_BP_REG_RAS1_TREF1 = 0x29,
    GX_BP_REG_RAS1_TREF2 = 0x2A,
    GX_BP_REG_RAS1_TREF3 = 0x2B,
    GX_BP_REG_RAS1_TREF4 = 0x2C,
    GX_BP_REG_RAS1_TREF5 = 0x2D,
    GX_BP_REG_RAS1_TREF6 = 0x2E,
    GX_BP_REG_RAS1_TREF7 = 0x2F,

    // setup sizes
    GX_BP_REG_SU_SSIZE0 = 0x30,
    GX_BP_REG_SU_TSIZE0 = 0x31,
    GX_BP_REG_SU_SSIZE1 = 0x32,
    GX_BP_REG_SU_TSIZE1 = 0x33,
    GX_BP_REG_SU_SSIZE2 = 0x34,
    GX_BP_REG_SU_TSIZE2 = 0x35,
    GX_BP_REG_SU_SSIZE3 = 0x36,
    GX_BP_REG_SU_TSIZE3 = 0x37,
    GX_BP_REG_SU_SSIZE4 = 0x38,
    GX_BP_REG_SU_TSIZE4 = 0x39,
    GX_BP_REG_SU_SSIZE5 = 0x3A,
    GX_BP_REG_SU_TSIZE5 = 0x3B,
    GX_BP_REG_SU_SSIZE6 = 0x3C,
    GX_BP_REG_SU_TSIZE6 = 0x3D,
    GX_BP_REG_SU_SSIZE7 = 0x3E,
    GX_BP_REG_SU_TSIZE7 = 0x3F,

    // Z and blend controls
    GX_BP_REG_ZMODE = 0x40,
    GX_BP_REG_BLENDMODE = 0x41,
    GX_BP_REG_DSTALPHA = 0x42,
    GX_BP_REG_ZCONTROL = 0x43,
    GX_BP_REG_FIELDMASK = 0x44,
    GX_BP_REG_DRAWDONE = 0x45,
    GX_BP_REG_PETOKEN = 0x47,
    GX_BP_REG_PETOKENINT = 0x48,

    // copying
    GX_BP_REG_TEXCOPYSRCXY = 0x49,
    GX_BP_REG_TEXCOPYSRCWH = 0x4A,
    GX_BP_REG_TEXCOPYDST = 0x4B,
    GX_BP_REG_DISPCOPYSTRIDE = 0x4D,
    GX_BP_REG_DISPCOPYSCALEY = 0x4E,
    GX_BP_REG_COPYCLEARAR = 0x4F,
    GX_BP_REG_COPYCLEARGB = 0x50,
    GX_BP_REG_COPYCLEARZ = 0x51,
    GX_BP_REG_COPYFILTER0 = 0x53,
    GX_BP_REG_COPYFILTER1 = 0x54,

    //
    GX_BP_REG_BOUNDINGBOX0 = 0x55,
    GX_BP_REG_BOUNDINGBOX1 = 0x56,

    GX_BP_REG_SCISSOROFFSET = 0x59,

    // texture memory
    GX_BP_REG_TMEMPRELOADADDR = 0x60,
    GX_BP_REG_TMEMPRELOADEVEN = 0x61,
    GX_BP_REG_TMEMPRELOADODD = 0x62,
    GX_BP_REG_TMEMPRELOADMODE = 0x63,
    GX_BP_REG_TMEMTLUTSRC = 0x64,
    GX_BP_REG_TMEMTLUTDST = 0x65,
    GX_BP_REG_TMEMTEXINVALIDATE = 0x66,

    // performance 1
    GX_BP_REG_PERF1 = 0x67,
    GX_BP_REG_FIELDMODE = 0x68,

    // set modes
    GX_BP_REG_SETMODE0_TEX0 = 0x80,
    GX_BP_REG_SETMODE0_TEX1 = 0x81,
    GX_BP_REG_SETMODE0_TEX2 = 0x82,
    GX_BP_REG_SETMODE0_TEX3 = 0x83,
    GX_BP_REG_SETMODE1_TEX0 = 0x84,
    GX_BP_REG_SETMODE1_TEX1 = 0x85,
    GX_BP_REG_SETMODE1_TEX2 = 0x86,
    GX_BP_REG_SETMODE1_TEX3 = 0x87,

    // set images
    GX_BP_REG_SETIMAGE0_TEX0 = 0x88,
    GX_BP_REG_SETIMAGE0_TEX1 = 0x89,
    GX_BP_REG_SETIMAGE0_TEX2 = 0x8A,
    GX_BP_REG_SETIMAGE0_TEX3 = 0x8B,
    GX_BP_REG_SETIMAGE1_TEX0 = 0x8C,
    GX_BP_REG_SETIMAGE1_TEX1 = 0x8D,
    GX_BP_REG_SETIMAGE1_TEX2 = 0x8E,
    GX_BP_REG_SETIMAGE1_TEX3 = 0x8F,
    GX_BP_REG_SETIMAGE2_TEX0 = 0x90,
    GX_BP_REG_SETIMAGE2_TEX1 = 0x91,
    GX_BP_REG_SETIMAGE2_TEX2 = 0x92,
    GX_BP_REG_SETIMAGE2_TEX3 = 0x93,
    GX_BP_REG_SETIMAGE3_TEX0 = 0x94,
    GX_BP_REG_SETIMAGE3_TEX1 = 0x95,
    GX_BP_REG_SETIMAGE3_TEX2 = 0x96,
    GX_BP_REG_SETIMAGE3_TEX3 = 0x97,

    // set texture lookups
    GX_BP_REG_SETTLUT_TEX0 = 0x98,
    GX_BP_REG_SETTLUT_TEX1 = 0x99,
    GX_BP_REG_SETTLUT_TEX2 = 0x9A,
    GX_BP_REG_SETTLUT_TEX3 = 0x9B,

    // set modes continued
    GX_BP_REG_SETMODE0_TEX4 = 0xA0,
    GX_BP_REG_SETMODE0_TEX5 = 0xA1,
    GX_BP_REG_SETMODE0_TEX6 = 0xA2,
    GX_BP_REG_SETMODE0_TEX7 = 0xA3,
    GX_BP_REG_SETMODE1_TEX4 = 0xA4,
    GX_BP_REG_SETMODE1_TEX5 = 0xA5,
    GX_BP_REG_SETMODE1_TEX6 = 0xA6,
    GX_BP_REG_SETMODE1_TEX7 = 0xA7,

    // set images continued
    GX_BP_REG_SETIMAGE0_TEX4 = 0xA8,
    GX_BP_REG_SETIMAGE0_TEX5 = 0xA9,
    GX_BP_REG_SETIMAGE0_TEX6 = 0xAA,
    GX_BP_REG_SETIMAGE0_TEX7 = 0xAB,
    GX_BP_REG_SETIMAGE1_TEX4 = 0xAC,
    GX_BP_REG_SETIMAGE1_TEX5 = 0xAD,
    GX_BP_REG_SETIMAGE1_TEX6 = 0xAE,
    GX_BP_REG_SETIMAGE1_TEX7 = 0xAF,
    GX_BP_REG_SETIMAGE2_TEX4 = 0xB0,
    GX_BP_REG_SETIMAGE2_TEX5 = 0xB1,
    GX_BP_REG_SETIMAGE2_TEX6 = 0xB2,
    GX_BP_REG_SETIMAGE2_TEX7 = 0xB3,
    GX_BP_REG_SETIMAGE3_TEX4 = 0xB4,
    GX_BP_REG_SETIMAGE3_TEX5 = 0xB5,
    GX_BP_REG_SETIMAGE3_TEX6 = 0xB6,
    GX_BP_REG_SETIMAGE3_TEX7 = 0xB7,

    // set texture lookups continued
    GX_BP_REG_SETTLUT_TEX4 = 0xB8,
    GX_BP_REG_SETTLUT_TEX5 = 0xB9,
    GX_BP_REG_SETTLUT_TEX6 = 0xBA,
    GX_BP_REG_SETTLUT_TEX7 = 0xBB,

    // TEV color manips
    GX_BP_REG_TEVCOLORCOMBINER0 = 0xC0,
    GX_BP_REG_TEVALPHACOMBINER0 = 0xC1,
    GX_BP_REG_TEVCOLORCOMBINER1 = 0xC2,
    GX_BP_REG_TEVALPHACOMBINER1 = 0xC3,
    GX_BP_REG_TEVCOLORCOMBINER2 = 0xC4,
    GX_BP_REG_TEVALPHACOMBINER2 = 0xC5,
    GX_BP_REG_TEVCOLORCOMBINER3 = 0xC6,
    GX_BP_REG_TEVALPHACOMBINER3 = 0xC7,
    GX_BP_REG_TEVCOLORCOMBINER4 = 0xC8,
    GX_BP_REG_TEVALPHACOMBINER4 = 0xC9,
    GX_BP_REG_TEVCOLORCOMBINER5 = 0xCA,
    GX_BP_REG_TEVALPHACOMBINER5 = 0xCB,
    GX_BP_REG_TEVCOLORCOMBINER6 = 0xCC,
    GX_BP_REG_TEVALPHACOMBINER6 = 0xCD,
    GX_BP_REG_TEVCOLORCOMBINER7 = 0xCE,
    GX_BP_REG_TEVALPHACOMBINER7 = 0xCF,
    GX_BP_REG_TEVCOLORCOMBINER8 = 0xD0,
    GX_BP_REG_TEVALPHACOMBINER8 = 0xD1,
    GX_BP_REG_TEVCOLORCOMBINER9 = 0xD2,
    GX_BP_REG_TEVALPHACOMBINER9 = 0xD3,
    GX_BP_REG_TEVCOLORCOMBINER10 = 0xD4,
    GX_BP_REG_TEVALPHACOMBINER10 = 0xD5,
    GX_BP_REG_TEVCOLORCOMBINER11 = 0xD6,
    GX_BP_REG_TEVALPHACOMBINER11 = 0xD7,
    GX_BP_REG_TEVCOLORCOMBINER12 = 0xD8,
    GX_BP_REG_TEVALPHACOMBINER12 = 0xD9,
    GX_BP_REG_TEVCOLORCOMBINER13 = 0xDA,
    GX_BP_REG_TEVALPHACOMBINER13 = 0xDB,
    GX_BP_REG_TEVCOLORCOMBINER14 = 0xDC,
    GX_BP_REG_TEVALPHACOMBINER14 = 0xDD,
    GX_BP_REG_TEVCOLORCOMBINER15 = 0xDE,
    GX_BP_REG_TEVALPHACOMBINER15 = 0xDF,

    // TEV registers
    GX_BP_REG_TEVREG0LO = 0xE0,
    GX_BP_REG_TEVREG0HI = 0xE1,
    GX_BP_REG_TEVREG1LO = 0xE2,
    GX_BP_REG_TEVREG1HI = 0xE3,
    GX_BP_REG_TEVREG2LO = 0xE4,
    GX_BP_REG_TEVREG2HI = 0xE5,
    GX_BP_REG_TEVREG3LO = 0xE6,
    GX_BP_REG_TEVREG3HI = 0xE7,

    // fog registers
    GX_BP_REG_FOGRANGE = 0xE8,
    GX_BP_REG_FOGRANGEK0 = 0xE9,
    GX_BP_REG_FOGRANGEK1 = 0xEA,
    GX_BP_REG_FOGRANGEK2 = 0xEB,
    GX_BP_REG_FOGRANGEK3 = 0xEC,
    GX_BP_REG_FOGRANGEK4 = 0xED,
    GX_BP_REG_FOGPARAM0 = 0xEE,
    GX_BP_REG_FOGPARAM1 = 0xEF,
    GX_BP_REG_FOGPARAM2 = 0xF0,
    GX_BP_REG_FOGPARAM3 = 0xF1,
    GX_BP_REG_FOGCOLOR = 0xF2,

    // performance manip registers
    GX_BP_REG_ALPHACOMPARE = 0xF3,
    GX_BP_REG_ZTEXTURE0 = 0xF4,
    GX_BP_REG_ZTEXTURE1 = 0xF5,

    // TEV K selectors
    GX_BP_REG_TEVKSEL0 = 0xF6,
    GX_BP_REG_TEVKSEL1 = 0xF7,
    GX_BP_REG_TEVKSEL2 = 0xF8,
    GX_BP_REG_TEVKSEL3 = 0xF9,
    GX_BP_REG_TEVKSEL4 = 0xFA,
    GX_BP_REG_TEVKSEL5 = 0xFB,
    GX_BP_REG_TEVKSEL6 = 0xFC,
    GX_BP_REG_TEVKSEL7 = 0xFD,

    // SS mask
    GX_BP_REG_SSMASK = 0xFE,
} GXBPRegs;

// XF locators for clip disabling.
typedef enum _GXXFClipDisable {
    // Disable detection [31-31]
    GX_XF_CLIPDISABLE_DETECT_ST = 31,
    GX_XF_CLIPDISABLE_DETECT_END = 31,

    // Disable trivial rejection [30-30]
    GX_XF_CLIPDISABLE_REJECT_ST = 30,
    GX_XF_CLIPDISABLE_REJECT_END = 30,

    // Disable cpoly clipping acceleration [29-29]
    GX_XF_CLIPDISABLE_ACCEL_ST = 29,
    GX_XF_CLIPDISABLE_ACCEL_END = 29,
} GXXFClipDisable;

// XF locators for InVertexSpec.
typedef enum _GXXFInVertexSpec {
    // Color [30-31]
    GX_XF_INVERTEXSPEC_CLR_ST = 30,
    GX_XF_INVERTEXSPEC_CLR_END = 31,

    // Normal [28-29]
    GX_XF_INVERTEXSPEC_NRM_ST = 28,
    GX_XF_INVERTEXSPEC_NRM_END = 29,

    // Tex coords [24-27]
    GX_XF_INVERTEXSPEC_TEX_ST = 24,
    GX_XF_INVERTEXSPEC_TEX_END = 27,
} GXXFInVertexSpec;

// XF locators for Color 0 control.
typedef enum _GXXFClr0Ctrl {
    // Matrix source [31-31]
    GX_XF_CLR0CTRL_MTXSRC_ST = 31,
    GX_XF_CLR0CTRL_MTXSRC_END = 31,

    // Light [30-30]
    GX_XF_CLR0CTRL_LIGHT_ST = 30,
    GX_XF_CLR0CTRL_LIGHT_END = 30,

    // Light mask (hi) [26-29]
    GX_XF_CLR0CTRL_LMASKHI_ST = 26,
    GX_XF_CLR0CTRL_LMASKHI_END = 29,

    // Ambient source [25-25]
    GX_XF_CLR0CTRL_AMBSRC_ST = 25,
    GX_XF_CLR0CTRL_AMBSRC_END = 25,

    // Diffuse attenuation [23-24]
    GX_XF_CLR0CTRL_DIFATTN_ST = 23,
    GX_XF_CLR0CTRL_DIFATTN_END = 24,

    // Enable attentuation [22-22]
    GX_XF_CLR0CTRL_ATTNENABLE_ST = 22,
    GX_XF_CLR0CTRL_ATTNENABLE_END = 22,

    // Select attentuation [21-21]
    GX_XF_CLR0CTRL_ATTNSEL_ST = 21,
    GX_XF_CLR0CTRL_ATTNSEL_END = 21,

    // Light mask (lo) [17-20]
    GX_XF_CLR0CTRL_LMASKLO_ST = 17,
    GX_XF_CLR0CTRL_LMASKLO_END = 20,
} GXXFClr0Ctrl;

// XF locators for matrix index 0.
typedef enum _GXXFMtxIdx0 {
    // Geometry [26-31]
    GX_XF_MTXIDX0_GEOM_ST = 26,
    GX_XF_MTXIDX0_GEOM_END = 31,

    // Tex 0 [20-25]
    GX_XF_MTXIDX0_TEX0_ST = 20,
    GX_XF_MTXIDX0_TEX0_END = 25,

    // Tex 1 [14-19]
    GX_XF_MTXIDX0_TEX1_ST = 14,
    GX_XF_MTXIDX0_TEX1_END = 19,

    // Tex 2 [8-13]
    GX_XF_MTXIDX0_TEX2_ST = 8,
    GX_XF_MTXIDX0_TEX2_END = 13,

    // Tex 3 [2-7]
    GX_XF_MTXIDX0_TEX3_ST = 2,
    GX_XF_MTXIDX0_TEX3_END = 7,
} GXXFMtxIdx0;

// XF locators for matrix index 1.
typedef enum _GXXFMtxIdx1 {
    // Tex 4 [26-31]
    GX_XF_MTXIDX1_TEX4_ST = 26,
    GX_XF_MTXIDX1_TEX4_END = 31,

    // Tex 5 [20-25]
    GX_XF_MTXIDX1_TEX5_ST = 20,
    GX_XF_MTXIDX1_TEX5_END = 25,

    // Tex 6 [14-19]
    GX_XF_MTXIDX1_TEX6_ST = 14,
    GX_XF_MTXIDX1_TEX6_END = 19,

    // Tex 7 [8-13]
    GX_XF_MTXIDX1_TEX7_ST = 8,
    GX_XF_MTXIDX1_TEX7_END = 13,
} GXXFMtxIdx1;

// XF locators for textures.
typedef enum _GXXFTex {
    // Projection type [30-30]
    GX_XF_TEX_PROJTYPE_ST = 30,
    GX_XF_TEX_PROJTYPE_END = 30,

    // Input format [29-29]
    GX_XF_TEX_INPUTFORM_ST = 29,
    GX_XF_TEX_INPUTFORM_END = 29,

    // Texture gen type [25-27]
    GX_XF_TEX_TEXGENTYPE_ST = 25,
    GX_XF_TEX_TEXGENTYPE_END = 27,

    // Source row [20-24]
    GX_XF_TEX_SRCROW_ST = 20,
    GX_XF_TEX_SRCROW_END = 24,

    // Bump source texture [17-19]
    GX_XF_TEX_BUMPSRCTEX_ST = 17,
    GX_XF_TEX_BUMPSRCTEX_END = 19,

    // Bump source light [14-16]
    GX_XF_TEX_BUMPSRCLIGHT_ST = 14,
    GX_XF_TEX_BUMPSRCLIGHT_END = 16,
} GXXFTex;

// XF locators for dual textures.
typedef enum _GXXFDualTex {
    // Base row of the transform matrix [26-31]
    GX_XF_DUALTEX_BASEROW_ST = 26,
    GX_XF_DUALTEX_BASEROW_END = 31,

    // Normalise texcoord before sending transform [23-23]
    GX_XF_DUALTEX_NORMALISE_ST = 23,
    GX_XF_DUALTEX_NORMALISE_END = 23,
} GXXFDualTex;

// Texture register fields for XF (transform) unit.
typedef enum _GXXfTexReg {
    GX_XF_TEX_PROJ_ST = 0, // (s,t) (2x4)
    GX_XF_TEX_PROJ_STQ = 1, // (s,t,q) (3x4)

    GX_XF_TEX_FORM_AB11 = 0, // (A, B, 1.0f, 1.0f), used for regular tex src
    GX_XF_TEX_FORM_ABC1 = 1, // (A, B, C, 1.0f), used for geometry/normal src
} GXXfTexReg;

// General texture commands.
typedef enum _GXXfTexGen {
    GX_XF_TG_REGULAR = 0, // Regular; transform incoming data.
    GX_XF_TG_BUMP = 1, // Texgen bump mapping.
    GX_XF_TG_CLR0 = 2, // Color texgen for color 0 (s,t) = (r, g:b)
    GX_XF_TG_CLR1 = 3, // Color texgen for color 1 (s,t) = (r, g:b)
} GXXfTexGen;

// Transform memory types.
typedef enum _GXXfMem {
	GX_XF_MEM_POSMTX     = 0x000, // position coord matrix
	GX_XF_MEM_NRMMTX     = 0x400, // normal coord matrix
	GX_XF_MEM_DUALTEXMTX = 0x500, // dual texture matrix
	GX_XF_MEM_LIGHTOBJ   = 0x600, // light object
} GXXfMem;

// BP GenMode locators.
typedef enum _GXBPGenMode {
    // Active texture counts [28-31]
    GX_BP_GENMODE_NUMTEX_ST = 28,
    GX_BP_GENMODE_NUMTEX_END = 31,

    // Color/channel counts [25-27]
    GX_BP_GENMODE_NUMCOLORS_ST = 25,
    GX_BP_GENMODE_NUMCOLORS_END = 27,

    // Multisample mode [22-22]
    GX_BP_GENMODE_MULTISAMPLE_ST = 22,
    GX_BP_GENMODE_MULTISAMPLE_END = 22,

    // Cull mode [16-17]
    GX_BP_GENMODE_CULLMODE_ST = 16,
    GX_BP_GENMODE_CULLMODE_END = 17,

    // Indirect stage counts [13-15]
    GX_BP_GENMODE_NUMINDSTAGES_ST = 13,
    GX_BP_GENMODE_NUMINDSTAGES_END = 15,

    // Toggle co-planar/Z-freeze [12-12]
    GX_BP_GENMODE_COPLANAR_ST = 12,
    GX_BP_GENMODE_COPLANAR_END = 12,
} GXBPGenMode;

// BP locators for indirect texture matrices (same for A, B, and C).
typedef enum _GXBPIndMtx {
    // Texture offset matrix [0][0] [21-31]
    GX_BP_INDMTX_M00_ST = 21,
    GX_BP_INDMTX_M00_END = 31,

    // Texture offset matrix [1][0] [10-20]
    GX_BP_INDMTX_M10_ST = 10,
    GX_BP_INDMTX_M10_END = 20,

    // Texture scaling exponent (2^x) [8-9]
    GX_BP_INDMTX_EXP_ST = 8,
    GX_BP_INDMTX_EXP_END = 9,
} GXBPIndMtx;

// BP locators for indirect texture masks.
typedef enum _GXBPIndIMask {
    // Indirect mask [24-31]
    GX_BP_INDIMASK_ST = 24,
    GX_BP_INDIMASK_END = 31,
} GXBPIndIMask;

// BP locators for indirect texture environment details.
typedef enum _GXBPIndTevStage {
    // Indirect texture stage ID [30-31]
    GX_BP_INDTEV_STAGE_ST = 30,
    GX_BP_INDTEV_STAGE_END = 31,

    // Indirect texture format [28-29]
    GX_BP_INDTEV_FMT_ST = 28,
    GX_BP_INDTEV_FMT_END = 29,

    // Indirect texture bias [25-27]
    GX_BP_INDTEV_BIAS_ST = 25,
    GX_BP_INDTEV_BIAS_END = 27,

    // Indirect texture alpha [23-24]
    GX_BP_INDTEV_ALPHA_ST = 23,
    GX_BP_INDTEV_ALPHA_END = 24,

    // Indirect texture matrices [19-22]
    GX_BP_INDTEV_MTX_ST = 19,
    GX_BP_INDTEV_MTX_END = 22,

    // Indirect texture S component wrap factor [16-18]
    GX_BP_INDTEV_WRAPS_ST = 16,
    GX_BP_INDTEV_WRAPS_END = 18,

    // Indirect texture T component wrap factor [13-15]
    GX_BP_INDTEV_WRAPT_ST = 13,
    GX_BP_INDTEV_WRAPT_END = 15,

    // Indirect texture unmodified texcoord setting (for mipmaps) [12-12]
    GX_BP_INDTEV_UNMODTEXCOORD_ST = 12,
    GX_BP_INDTEV_UNMODTEXCOORD_END = 12,

    // Indiret texture add previous results setting [11-11]
    GX_BP_INDTEV_ADDPREV_ST = 11,
    GX_BP_INDTEV_ADDPREV_END = 11,
} GXBPIndTevStage;

// BP locators for top-left scissor.
typedef enum _GXBPScissorTL {
    // Top component [21-31]
    GX_BP_SCISSORTL_TOP_ST = 21,
    GX_BP_SCISSORTL_TOP_END = 31,

    // Left component [9-19]
    GX_BP_SCISSORTL_LEFT_ST = 9,
    GX_BP_SCISSORTL_LEFT_END = 19,
} GXBPScissorTL;

// BP locators for bottom-right scissor.
typedef enum _GXBPScissorBR {
    // Bottom component [21-31]
    GX_BP_SCISSORBR_BOT_ST = 21,
    GX_BP_SCISSORBR_BOT_END = 31,

    // Right component [9-19]
    GX_BP_SCISSORBR_RIGHT_ST = 9,
    GX_BP_SCISSORBR_RIGHT_END = 19,
} GXBPScissorBR;

// BP locators for line and point settings.
typedef enum _GXBPLinePtWidth {
    // Line size/width [24-31]
    GX_BP_LINEPTWIDTH_LINESZ_ST = 24,
    GX_BP_LINEPTWIDTH_LINESZ_END = 31,

    // Point size [16-23]
    GX_BP_LINEPTWIDTH_POINTSZ_ST = 16,
    GX_BP_LINEPTWIDTH_POINTSZ_END = 23,

    // Line offset [13-15]
    GX_BP_LINEPTWIDTH_LINEOFS_ST = 13,
    GX_BP_LINEPTWIDTH_LINEOFS_END = 15,

    // Point offset [10-12]
    GX_BP_LINEPTWIDTH_POINTOFS_ST = 10,
    GX_BP_LINEPTWIDTH_POINTOFS_END = 12,

    // Interlacing adjustment for aspect ratio [9-9]
    GX_BP_LINEPTWIDTH_ADJUST_ST = 9,
    GX_BP_LINEPTWIDTH_ADJUST_END = 9,
} GXBPLinePtWidth;

// BP locators for raster 1 SS0.
typedef enum _GXBPRas1SS0 {
    // S-component scale (stage 0) [28-31]
    GX_BP_RAS1_SS0_S0_ST = 28,
    GX_BP_RAS1_SS0_S0_END = 31,

    // T-component scale (stage 0) [24-27]
    GX_BP_RAS1_SS0_T0_ST = 24,
    GX_BP_RAS1_SS0_T0_END = 27,

    // S-component scale (stage 1) [20-23]
    GX_BP_RAS1_SS0_S1_ST = 20,
    GX_BP_RAS1_SS0_S1_END = 23,

    // T-component scale (stage 1) [16-19]
    GX_BP_RAS1_SS0_T1_ST = 16,
    GX_BP_RAS1_SS0_T1_END = 19,
} GXBPRas1SS0;

// BP locators for raster 1 SS1.
typedef enum _GXBPRas1SS1 {
    // S-component scale (stage 2) [28-31]
    GX_BP_RAS1_SS1_S2_ST = 28,
    GX_BP_RAS1_SS1_S2_END = 31,

    // T-component scale (stage 2) [24-27]
    GX_BP_RAS1_SS1_T2_ST = 24,
    GX_BP_RAS1_SS1_T2_END = 27,

    // S-component scale (stage 3) [20-23]
    GX_BP_RAS1_SS1_S3_ST = 20,
    GX_BP_RAS1_SS1_S3_END = 23,

    // T-component scale (stage 3) [16-19]
    GX_BP_RAS1_SS1_T3_ST = 16,
    GX_BP_RAS1_SS1_T3_END = 19,
} GXBPRas1SS1;

// BP locators for raster 1 ID-reference.
typedef enum _GXBPRasIRef {
    // Texmap ID (stage 0) [29-31]
    GX_BP_RAS1_IREF_MAP0_ST = 29,
    GX_BP_RAS1_IREF_MAP0_END = 31,

    // Texcoord ID (stage 0) [26-28]
    GX_BP_RAS1_IREF_TXC0_ST = 26,
    GX_BP_RAS1_IREF_TXC0_END = 28,

    // Texmap ID (stage 1) [23-25]
    GX_BP_RAS1_IREF_MAP1_ST = 23,
    GX_BP_RAS1_IREF_MAP1_END = 25,

    // Texcoord ID (stage 1) [20-22]
    GX_BP_RAS1_IREF_TXC1_ST = 20,
    GX_BP_RAS1_IREF_TXC1_END = 22,

    // Texmap ID (stage 2) [17-19]
    GX_BP_RAS1_IREF_MAP2_ST = 17,
    GX_BP_RAS1_IREF_MAP2_END = 19,

    // Texcoord ID (stage 2) [14-16]
    GX_BP_RAS1_IREF_TXC2_ST = 14,
    GX_BP_RAS1_IREF_TXC2_END = 16,

    // Texmap ID (stage 3) [11-13]
    GX_BP_RAS1_IREF_MAP3_ST = 11,
    GX_BP_RAS1_IREF_MAP3_END = 13,

    // Texcoord ID (stage 3) [8-10]
    GX_BP_RAS1_IREF_TXC3_ST = 8,
    GX_BP_RAS1_IREF_TXC3_END = 10,
} GXBPRasIRef;

// BP locators for setup size.
typedef enum _GXBPSUSSize {
    // Use line offsets [13-13]
    GX_BP_SU_SSIZE_USELINEOFS_ST = 13,
    GX_BP_SU_SSIZE_USELINEOFS_END = 13,

    // Use point offsets [12-12]
    GX_BP_SU_SSIZE_USEPTOFS_ST = 12,
    GX_BP_SU_SSIZE_USEPTOFS_END = 12,
} GXBPSUSSize;

// BP locators for Z mode.
typedef enum _GXBPZMode {
    // Test enable [31-31]
    GX_BP_ZMODE_TEST_ENABLE_ST = 31,
    GX_BP_ZMODE_TEST_ENABLE_END = 31,

    // Compare [28-30]
    GX_BP_ZMODE_COMPARE_ST = 28,
    GX_BP_ZMODE_COMPARE_END = 30,

    // Update enable [27-27]
    GX_BP_ZMODE_UPDATE_ENABLE_ST = 27,
    GX_BP_ZMODE_UPDATE_ENABLE_END = 27,
} GXBPZMode;

// BP locators for blend mode.
typedef enum _GXBPBlendMode {
    // Blend enable [31-31]
    GX_BP_BLENDMODE_ENABLE_ST = 31,
    GX_BP_BLENDMODE_ENABLE_END = 31,

    // Logic operation enable [30-30]
    GX_BP_BLENDMODE_LOGIC_OP_ST = 30,
    GX_BP_BLENDMODE_LOGIC_OP_END = 30,

    // Dither [29-29]
    GX_BP_BLENDMODE_DITHER_ST = 29,
    GX_BP_BLENDMODE_DITHER_END = 29,

    // Color update [28-28]
    GX_BP_BLENDMODE_COLOR_UPDATE_ST = 28,
    GX_BP_BLENDMODE_COLOR_UPDATE_END = 28,

    // Alpha update [27-27]
    GX_BP_BLENDMODE_ALPHA_UPDATE_ST = 27,
    GX_BP_BLENDMODE_ALPHA_UPDATE_END = 27,

    // Destination factor [24-26]
    GX_BP_BLENDMODE_DSTFACTOR_ST = 24,
    GX_BP_BLENDMODE_DSTFACTOR_END = 26,

    // Source factor [21-23]
    GX_BP_BLENDMODE_SRCFACTOR_ST = 21,
    GX_BP_BLENDMODE_SRCFACTOR_END = 23,

    // Subtract [20-20]
    GX_BP_BLENDMODE_SUBTRACT_ST = 20,
    GX_BP_BLENDMODE_SUBTRACT_END = 20,

    // Logic mode [16-19]
    GX_BP_BLENDMODE_LOGICMODE_ST = 16,
    GX_BP_BLENDMODE_LOGICMODE_END = 19,
} GXBPBlendMode;

// BP locators for destination alpha.
typedef enum _GXBPDstAlpha {
    // Alpha [24-31]
    GX_BP_DSTALPHA_ALPHA_ST = 24,
    GX_BP_DSTALPHA_ALPHA_END = 31,

    // Enable [23-23]
    GX_BP_DSTALPHA_ENABLE_ST = 23,
    GX_BP_DSTALPHA_ENABLE_END = 23,

    // YUV format [21-22]
    GX_BP_DSTALPHA_YUV_FMT_ST = 21,
    GX_BP_DSTALPHA_YUV_FMT_END = 22,
} GXBPDstAlpha;

// BP locators for Z control.
typedef enum _GXBPZControl {
    // Pixel format [29-31]
    GX_BP_ZCONTROL_PIXEL_FMT_ST = 29,
    GX_BP_ZCONTROL_PIXEL_FMT_END = 31,

    // Z format [26-28]
    GX_BP_ZCONTROL_Z_FMT_ST = 26,
    GX_BP_ZCONTROL_Z_FMT_END = 28,

    // Whether to do Z-buffering before or after texturing [25-25]
    GX_BP_ZCONTROL_BEFORE_TEX_ST = 25,
    GX_BP_ZCONTROL_BEFORE_TEX_END = 25,
} GXBPZControl;

// BP locators for field mask.
typedef enum _GXBPFieldMask {
    // Whether to write odd fields to the EFB [31-31]
    GX_BP_FIELDMASK_ODD_ST = 31,
    GX_BP_FIELDMASK_ODD_END = 31,

    // Whether to write even fields to the EFB [30-30]
    GX_BP_FIELDMASK_EVEN_ST = 30,
    GX_BP_FIELDMASK_EVEN_END = 30,
} GXBPFieldMask;

// BP locators for scissor offset.
typedef enum _GXBPScissorOffset {
    // X offset [22-31]
    GX_BP_SCISSOROFS_OX_ST = 22,
    GX_BP_SCISSOROFS_OX_END = 31,

    // Y offset [12-21]
    GX_BP_SCISSOROFS_OY_ST = 12,
    GX_BP_SCISSOROFS_OY_END = 21,
} GXBPScissorOffset;

// BP locators for field mode.
typedef enum _GXBPFieldMode {
    // Adjust vertex tex LOD computation to account for interlacing
    GX_BP_FIELDMODE_TEX_LOD_ST = 31,
    GX_BP_FIELDMODE_TEX_LOD_END = 31,
} GXBPFieldMode;

// BP locators for fog range.
typedef enum _GXBPFogRange {
    // Center [22-31]
    GX_BP_FOGRANGE_CENTER_ST = 22,
    GX_BP_FOGRANGE_CENTER_END = 31,

    // Enabled [21-21]
    GX_BP_FOGRANGE_ENABLED_ST = 21,
    GX_BP_FOGRANGE_ENABLED_END = 21,
} GXBPFogRange;

// BP locators for fog range K.
typedef enum _GXBPFogRangeK {
    // Hi [20-31]
    GX_BP_FOGRANGEK_HI_ST = 20,
    GX_BP_FOGRANGEK_HI_END = 31,

    // Lo [8-19]
    GX_BP_FOGRANGEK_LO_ST = 8,
    GX_BP_FOGRANGEK_LO_END = 19,
} GXBPFogRangeK;

// BP locators for fog parameter 0.
typedef enum _GXBPFogParam0 {
    // A mantissa [21-31]
    GX_BP_FOGPARAM0_A_MANT_ST = 21,
    GX_BP_FOGPARAM0_A_MANT_END = 31,

    // A exponent [13-20]
    GX_BP_FOGPARAM0_A_EXP_ST = 13,
    GX_BP_FOGPARAM0_A_EXP_END = 20,

    // A sign [12-12]
    GX_BP_FOGPARAM0_A_SIGN_ST = 12,
    GX_BP_FOGPARAM0_A_SIGN_END = 12,
} GXBPFogParam0;

// BP locators for fog parameter 1.
typedef enum _GXBPFogParam1 {
    // B magnitude [8-31]
    GX_BP_FOGPARAM1_B_MAG_ST = 8,
    GX_BP_FOGPARAM1_B_MAG_END = 31,
} GXBPFogParam1;

// BP locators for fog parameter 2.
typedef enum _GXBPFogParam2 {
    // B shift [27-31]
    GX_BP_FOGPARAM2_B_SHIFT_ST = 27,
    GX_BP_FOGPARAM2_B_SHIFT_END = 31,
} GXBPFogParam2;

// BP locators for fog parameter 3.
typedef enum _GXBPFogParam3 {
    // C mantissa [21-31]
    GX_BP_FOGPARAM3_C_MANT_ST = 21,
    GX_BP_FOGPARAM3_C_MANT_END = 31,

    // C exponent [13-20]
    GX_BP_FOGPARAM3_C_EXP_ST = 13,
    GX_BP_FOGPARAM3_C_EXP_END = 20,

    // C sign [12-12]
    GX_BP_FOGPARAM3_C_SIGN_ST = 12,
    GX_BP_FOGPARAM3_C_SIGN_END = 12,

    // Projection [11]
    GX_BP_FOGPARAM3_PROJ_ST = 11,
    GX_BP_FOGPARAM3_PROJ_END = 11,

    // F select [8-10]
    GX_BP_FOGPARAM3_FSEL_ST = 8,
    GX_BP_FOGPARAM3_FSEL_END = 10,
} GXBPFogParam3;

// BP locators for fog color.
typedef enum _GXBPFogColor {
    // RGB components of color [8-31]
    GX_BP_FOGCOLOR_RGB_ST = 8,
    GX_BP_FOGCOLOR_RGB_END = 31,
} GXBPFogColor;

#endif
