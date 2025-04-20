#include "dolphin/gx.h"
#include "math.h"

#include "dolphin/private/__gx.h"

// GXLightObj private data
typedef struct {
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
} __GXLightObjInt_struct;

#define GXCOLOR_AS_U32(color) (*((u32*)&(color)))
#define GX_BITFIELD_TRUNC(field, pos, size, value) (__rlwimi((field), (value), 0, (pos), (pos) + (size) - 1))
#define GX_SET_TRUNC(reg, x, st, end) GX_BITFIELD_TRUNC((reg), (st), ((end) - (st) + 1), (x))

void GXSetChanAmbColor(GXChannelID chan, GXColor amb_color) {
    u32 reg;
    u32 rgb;
    u32 colIdx;

    switch (chan) {
#if IS_MQ
        case GX_COLOR0:
            reg = __GXData->ambColor[GX_COLOR0];
            rgb = GXCOLOR_AS_U32(amb_color) >> 8;
            SET_REG_FIELD(reg, 24, 8, rgb);
            colIdx = 0;
            break;
        case GX_COLOR1:
            reg = __GXData->ambColor[GX_COLOR1];
            rgb = GXCOLOR_AS_U32(amb_color) >> 8;
            SET_REG_FIELD(reg, 24, 8, rgb);
            colIdx = 1;
            break;
#else
        //! TODO: figure out why this is different on CE
        case GX_COLOR0:
            rgb = __GXData->ambColor[GX_COLOR0];
            reg = GX_SET_TRUNC(GXCOLOR_AS_U32(amb_color) & ~0xFF, rgb, 24, 31);
            colIdx = GX_COLOR0;
            break;
        case GX_COLOR1:
            rgb = __GXData->ambColor[GX_COLOR1];
            reg = GX_SET_TRUNC(GXCOLOR_AS_U32(amb_color) & ~0xFF, rgb, 24, 31);
            colIdx = GX_COLOR1;
            break;
#endif
        case GX_ALPHA0:
            reg = __GXData->ambColor[GX_COLOR0];
            SET_REG_FIELD(reg, 8, 0, amb_color.a);
            colIdx = 0;
            break;
        case GX_ALPHA1:
            reg = __GXData->ambColor[GX_COLOR1];
            SET_REG_FIELD(reg, 8, 0, amb_color.a);
            colIdx = 1;
            break;
        case GX_COLOR0A0:
            reg = GXCOLOR_AS_U32(amb_color);
            colIdx = 0;
            break;
        case GX_COLOR1A1:
            reg = GXCOLOR_AS_U32(amb_color);
            colIdx = 1;
            break;
        default:

            return;
    }

    GX_WRITE_XF_REG(colIdx + 10, reg);
    __GXData->bpSentNot = 1;
    __GXData->ambColor[colIdx] = reg;
}

void GXSetChanMatColor(GXChannelID chan, GXColor mat_color) {
    u32 reg;
    u32 rgb;
    u32 colIdx;

    switch (chan) {
#if IS_MQ
        case GX_COLOR0:
            reg = __GXData->matColor[GX_COLOR0];
            rgb = GXCOLOR_AS_U32(mat_color) >> 8;
            SET_REG_FIELD(reg, 24, 8, rgb);
            colIdx = 0;
            break;
        case GX_COLOR1:
            reg = __GXData->matColor[GX_COLOR1];
            rgb = GXCOLOR_AS_U32(mat_color) >> 8;
            SET_REG_FIELD(reg, 24, 8, rgb);
            colIdx = 1;
            break;
#else
        //! TODO: figure out why this is different on CE
        case GX_COLOR0:
            rgb = __GXData->matColor[GX_COLOR0];
            reg = GX_SET_TRUNC(GXCOLOR_AS_U32(mat_color) & ~0xFF, rgb, 24, 31);
            colIdx = GX_COLOR0;
            break;
        case GX_COLOR1:
            rgb = __GXData->matColor[GX_COLOR1];
            reg = GX_SET_TRUNC(GXCOLOR_AS_U32(mat_color) & ~0xFF, rgb, 24, 31);
            colIdx = GX_COLOR1;
            break;
#endif
        case GX_ALPHA0:
            reg = __GXData->matColor[GX_COLOR0];
            SET_REG_FIELD(reg, 8, 0, mat_color.a);
            colIdx = 0;
            break;
        case GX_ALPHA1:
            reg = __GXData->matColor[GX_COLOR1];
            SET_REG_FIELD(reg, 8, 0, mat_color.a);
            colIdx = 1;
            break;
        case GX_COLOR0A0:
            reg = GXCOLOR_AS_U32(mat_color);
            colIdx = 0;
            break;
        case GX_COLOR1A1:
            reg = GXCOLOR_AS_U32(mat_color);
            colIdx = 1;
            break;
        default:

            return;
    }

    GX_WRITE_XF_REG(colIdx + 12, reg);
    __GXData->bpSentNot = 1;
    __GXData->matColor[colIdx] = reg;
}

void GXSetNumChans(u8 nChans) {

    SET_REG_FIELD(__GXData->genMode, 3, 4, nChans);
    GX_WRITE_XF_REG(9, nChans);
    __GXData->dirtyState |= 4;
}

void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask,
                   GXDiffuseFn diff_fn, GXAttnFn attn_fn) {
    u32 reg;
    u32 idx;

    idx = chan & 0x3;
    reg = 0;
    SET_REG_FIELD(reg, 1, 1, enable);
    SET_REG_FIELD(reg, 1, 0, mat_src);
    SET_REG_FIELD(reg, 1, 6, amb_src);

    SET_REG_FIELD(reg, 2, 7, (attn_fn == 0) ? 0 : diff_fn);
    SET_REG_FIELD(reg, 1, 9, (attn_fn != 2));
    SET_REG_FIELD(reg, 1, 10, (attn_fn != 0));

    __OLD_SET_REG_FIELD(reg, 4, 2, light_mask & 0xF);
    __OLD_SET_REG_FIELD(reg, 4, 11, (light_mask >> 4) & 0xF);

    GX_WRITE_XF_REG(idx + 14, reg);

    if (chan == GX_COLOR0A0) {
        GX_WRITE_XF_REG(16, reg);
    } else if (chan == GX_COLOR1A1) {
        GX_WRITE_XF_REG(17, reg);
    }

    __GXData->bpSentNot = 1;
}
