#include "dolphin/gx.h"
#include "math.h"

void GXSetChanAmbColor(GXChannelID channel, GXColor color) {
    u32 reg;
    u32 rgb;
    u32 colorID;
    u8 alpha;

    switch (channel) {
        case GX_COLOR0:
            rgb = gx->ambColor[GX_COLOR0];
            reg = GX_SET_TRUNC(GX_COLOR_AS_U32(color) & ~0xff, rgb, 24, 31);
            colorID = GX_COLOR0;
            break;
        case GX_COLOR1:
            rgb = gx->ambColor[GX_COLOR1];
            reg = GX_SET_TRUNC(GX_COLOR_AS_U32(color) & ~0xff, rgb, 24, 31);
            colorID = GX_COLOR1;
            break;
        case GX_ALPHA0:
            reg = gx->ambColor[GX_COLOR0];
            reg = GX_SET_TRUNC(reg, color.a, 24, 31);
            colorID = GX_COLOR0;
            break;
        case GX_ALPHA1:
            reg = gx->ambColor[GX_COLOR1];
            reg = GX_SET_TRUNC(reg, color.a, 24, 31);
            colorID = GX_COLOR1;
            break;
        case GX_COLOR0A0:
            reg = GX_COLOR_AS_U32(color);
            colorID = GX_COLOR0;
            break;
        case GX_COLOR1A1:
            reg = GX_COLOR_AS_U32(color);
            colorID = GX_COLOR1;
            break;
        default:
            return;
    }

    GX_XF_LOAD_REG(GX_XF_REG_AMBIENT0 + colorID, reg);
    gx->bpSentNot = GX_TRUE;
    gx->ambColor[colorID] = reg;
}

void GXSetChanMatColor(GXChannelID channel, GXColor color) {
    u32 reg = 0;
    u32 rgb;
    GXChannelID colorID;

    switch (channel) {
        case GX_COLOR0:
            rgb = gx->matColor[GX_COLOR0];
            reg = GX_SET_TRUNC(GX_COLOR_AS_U32(color) & ~0xff, rgb, 24, 31);
            colorID = GX_COLOR0;
            break;
        case GX_COLOR1:
            rgb = gx->matColor[GX_COLOR1];
            reg = GX_SET_TRUNC(GX_COLOR_AS_U32(color) & ~0xff, rgb, 24, 31);
            colorID = GX_COLOR1;
            break;
        case GX_ALPHA0:
            reg = gx->matColor[GX_COLOR0];
            reg = GX_SET_TRUNC(reg, color.a, 24, 31);
            colorID = GX_COLOR0;
            break;
        case GX_ALPHA1:
            reg = gx->matColor[GX_COLOR1];
            reg = GX_SET_TRUNC(reg, color.a, 24, 31);
            colorID = GX_COLOR1;
            break;
        case GX_COLOR0A0:
            reg = GX_COLOR_AS_U32(color);
            colorID = GX_COLOR0;
            break;
        case GX_COLOR1A1:
            reg = GX_COLOR_AS_U32(color);
            colorID = GX_COLOR1;
            break;
        default:
            return;
    }

    GX_XF_LOAD_REG(GX_XF_REG_MATERIAL0 + colorID, reg);
    gx->bpSentNot = GX_TRUE;
    gx->matColor[colorID] = reg;
}

void GXSetNumChans(u8 count) {
    GX_SET_REG(gx->genMode, count, 25, 27);
    GX_XF_LOAD_REG(GX_XF_REG_NUMCOLORS, count);
    gx->dirtyState |= GX_DIRTY_GEN_MODE;
}

void GXSetChanCtrl(GXChannelID channel, GXBool doEnable, GXColorSrc ambSrc, GXColorSrc matSrc, u32 mask,
                   GXDiffuseFn diffFunc, GXAttnFn attnFunc) {
    const u32 colorID = (u32)channel & 0x3;
    u32 reg = 0;

    GX_SET_REG(reg, doEnable, GX_XF_CLR0CTRL_LIGHT_ST, GX_XF_CLR0CTRL_LIGHT_END);
    GX_SET_REG(reg, matSrc, GX_XF_CLR0CTRL_MTXSRC_ST, GX_XF_CLR0CTRL_MTXSRC_END);
    GX_SET_REG(reg, ambSrc, GX_XF_CLR0CTRL_AMBSRC_ST, GX_XF_CLR0CTRL_AMBSRC_END);
    GX_SET_REG(reg, (attnFunc == GX_AF_SPEC ? GX_DF_NONE : diffFunc), GX_XF_CLR0CTRL_DIFATTN_ST,
               GX_XF_CLR0CTRL_DIFATTN_END);
    GX_SET_REG(reg, (attnFunc != GX_AF_NONE), GX_XF_CLR0CTRL_ATTNENABLE_ST, GX_XF_CLR0CTRL_ATTNENABLE_END);
    GX_SET_REG(reg, (attnFunc != GX_AF_SPEC), GX_XF_CLR0CTRL_ATTNSEL_ST, GX_XF_CLR0CTRL_ATTNSEL_END);

    // why are we unmasking bits we're about to overwrite?

    reg = (reg & ~(0xf << 2)) | ((mask & 0xf) << 2);

    reg = (reg & ~(0xf << 11)) | (((mask >> 4) & 0xf) << 11);

    GX_XF_LOAD_REG(GX_XF_REG_COLOR0CNTRL + colorID, reg);

    if (channel == GX_COLOR0A0) {
        GX_XF_LOAD_REG(GX_XF_REG_ALPHA0CNTRL, reg);
    } else if (channel == GX_COLOR1A1) {
        GX_XF_LOAD_REG(GX_XF_REG_ALPHA1CNTRL, reg);
    }

    gx->bpSentNot = GX_TRUE;
}
