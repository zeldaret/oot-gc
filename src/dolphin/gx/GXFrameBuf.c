#include "dolphin/gx.h"

// clang-format off
GXRenderModeObj GXNtsc480IntDf = {
    VI_TVMODE_NTSC_INT, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_DF, GX_FALSE, GX_FALSE,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    8, 8, 10, 12, 10, 8, 8,
};

GXRenderModeObj GXNtsc480Prog = {
    VI_TVMODE_NTSC_PROG, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_SF, GX_FALSE, GX_FALSE,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    0, 0, 21, 22, 21, 0, 0,
};

GXRenderModeObj GXMpal480IntDf = {
    VI_TVMODE_MPAL_INT, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_DF, GX_FALSE, GX_FALSE,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    8, 8, 10, 12, 10, 8, 8,
};

GXRenderModeObj GXPal528IntDf = {
    VI_TVMODE_PAL_INT, 640, 528, 528, 40, 23, 640, 528, VI_XFBMODE_DF, GX_FALSE, GX_FALSE,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    8, 8, 10, 12, 10, 8, 8,
};

GXRenderModeObj GXEurgb60Hz480IntDf = {
    VI_TVMODE_EURGB60_INT, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_DF, GX_FALSE, GX_FALSE,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    8, 8, 10, 12, 10, 8, 8,
};
// clang-format on

void GXAdjustForOverscan(GXRenderModeObj* rIn, GXRenderModeObj* rOut, u16 horiz, u16 vert) {
    u16 hor2 = horiz * 2;
    u16 ver2 = vert * 2;
    u32 verf;

#if IS_CE
    u32 viTVMode;
#endif

    if (rIn != rOut) {
        *rOut = *rIn;
    }

#if IS_CE
    viTVMode = rIn->viTVmode & 3;
#endif

    rOut->fbWidth = rIn->fbWidth - hor2;
    verf = rIn->efbHeight;
    rOut->efbHeight = verf - ((ver2 * verf) / rIn->xfbHeight);

#if IS_MQ
    if (rIn->xFBmode == VI_XFBMODE_SF && (rIn->viTVmode & 2) != 2) {
        rOut->xfbHeight = rIn->xfbHeight - vert;
    } else {
        rOut->xfbHeight = rIn->xfbHeight - ver2;
    }
#else
    if ((rIn->xFBmode == VI_XFBMODE_SF) && (viTVMode == 0)) {
        rOut->xfbHeight = rIn->xfbHeight - (ver2 / 2);
    } else {
        rOut->xfbHeight = rIn->xfbHeight - ver2;
    }
#endif

    rOut->viWidth = rIn->viWidth - hor2;

#if IS_MQ
    rOut->viHeight = rIn->viHeight - ver2;
#else
    if (viTVMode == 1) {
        rOut->viHeight = rIn->viHeight - (ver2 * 2);
    } else {
        rOut->viHeight = rIn->viHeight - ver2;
    }
#endif

    rOut->viXOrigin = rIn->viXOrigin + horiz;
    rOut->viYOrigin = rIn->viYOrigin + vert;
}

void GXSetDispCopySrc(u16 left, u16 top, u16 width, u16 height) {
    gx->cpDispSrc = 0;
    GX_SET_REG(gx->cpDispSrc, left, 22, 31);
    GX_SET_REG(gx->cpDispSrc, top, 12, 21);
    GX_SET_REG(gx->cpDispSrc, 0x49, 0, 7);

    gx->cpDispSize = 0;
    GX_SET_REG(gx->cpDispSize, width - 1, 22, 31);
    GX_SET_REG(gx->cpDispSize, height - 1, 12, 21);
    GX_SET_REG(gx->cpDispSize, 0x4A, 0, 7);
}

void GXSetTexCopySrc(u16 left, u16 top, u16 width, u16 height) {
    gx->cpTexSrc = 0;
    GX_SET_REG(gx->cpTexSrc, left, 22, 31);
    GX_SET_REG(gx->cpTexSrc, top, 12, 21);
    GX_SET_REG(gx->cpTexSrc, 0x49, 0, 7);

    gx->cpTexSize = 0;
    GX_SET_REG(gx->cpTexSize, width - 1, 22, 31);
    GX_SET_REG(gx->cpTexSize, height - 1, 12, 21);
    GX_SET_REG(gx->cpTexSize, 0x4A, 0, 7);
}

void GXSetDispCopyDst(u16 width, u16 height) {
    u16 stride = width * 2;
    gx->cpDispStride = 0;
    GX_SET_REG(gx->cpDispStride, stride >> 5, 22, 31);
    GX_SET_REG(gx->cpDispStride, 0x4D, 0, 7);
}

void GXSetTexCopyDst(u16 width, u16 height, GXTexFmt format, GXBool useMIPmap) {
    u32 sp20, sp1C, sp18;
    u32 value;
    u8 depthRelated;

    gx->cpTexZ = GX_NONE;

    depthRelated = format & 0xF;
    if (format == GX_TF_Z16) {
        depthRelated = 0xB;
    }

    switch (format) {
        case GX_TF_I4:
        case GX_TF_I8:
        case GX_TF_IA4:
        case GX_TF_IA8:
        case GX_CTF_YUVA8:
            GX_SET_REG(gx->cpTex, 3, 15, 16);
            break;
        default:
            GX_SET_REG(gx->cpTex, 2, 15, 16);
            break;
    }

    gx->cpTexZ = (format & 0x10) == 0x10;

    value = (depthRelated >> 3) & 1;

    GX_SET_REG(gx->cpTex, value, 28, 28);

    depthRelated &= 7;

    __GetImageTileCount(format, width, height, &sp20, &sp1C, &sp18);

    gx->cpTexStride = GX_NONE;
    GX_SET_REG(gx->cpTexStride, sp20 * sp18, 22, 31);
    GX_SET_REG(gx->cpTexStride, 0x4D, 0, 7);

    GX_SET_REG(gx->cpTex, useMIPmap, 22, 22);
    GX_SET_REG(gx->cpTex, depthRelated, 25, 27);
}

void GXSetDispCopyFrame2Field(GXCopyMode mode) {
    GX_SET_REG(gx->cpDisp, mode, 18, 19);
    GX_SET_REG(gx->cpTex, 0, 18, 19);
}

void GXSetCopyClamp(GXFBClamp clamp) {
    GXBool clamp1 = ((clamp & 1) == 1);
    GXBool clamp2 = ((clamp & 2) == 2);
    GX_SET_REG(gx->cpDisp, clamp1, 31, 31);
    GX_SET_REG(gx->cpDisp, clamp2, 30, 30);
    GX_SET_REG(gx->cpTex, clamp1, 31, 31);
    GX_SET_REG(gx->cpTex, clamp2, 30, 30);
}

static inline u32 __GXGetNumXfbLines(u32 height, u32 scale) {
    u32 numLines;
    u32 actualHeight;
    u32 newScale;

    numLines = (height - 1) * 0x100;
    actualHeight = (numLines / scale) + 1;

    newScale = scale;

    if (newScale > 0x80 && newScale < 0x100) {
        while (newScale % 2 == 0) {
            newScale /= 2;
        }

        if (height % newScale == 0) {
            actualHeight++;
        }
    }

    if (actualHeight > 0x400) {
        actualHeight = 0x400;
    }

    return actualHeight;
}

static inline u16 GXGetNumXfbLines(const u16 efbHeight, f32 yScale) {
    u32 scale = (u32)(256.0f / yScale) & 0x1FF;

    return __GXGetNumXfbLines(efbHeight, scale);
}

f32 GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight) {
    u32 scale;
    u32 height1;
    u32 height2;
    f32 scale2;
    f32 scale1;

    height1 = xfbHeight;
    scale1 = (f32)xfbHeight / (f32)efbHeight;
    scale = (u32)(256.0f / scale1) & 0x1FF;
    height2 = __GXGetNumXfbLines(efbHeight, scale);

    while (height2 > xfbHeight) {
        height1--;
        scale1 = (f32)height1 / (f32)efbHeight;
        scale = (u32)(256.0f / scale1) & 0x1FF;
        height2 = __GXGetNumXfbLines(efbHeight, scale);
    }

    scale2 = scale1;
    while (height2 < xfbHeight) {
        scale2 = scale1;
        height1++;
        scale1 = (f32)height1 / (f32)efbHeight;
        scale = (u32)(256.0f / scale1) & 0x1FF;
        height2 = __GXGetNumXfbLines(efbHeight, scale);
    }

    return scale2;
}

u32 GXSetDispCopyYScale(f32 vertScale) {
    u32 scale;
    GXBool check;
    u32 height;
    u32 reg;

    scale = (u32)(256.0f / vertScale) & 0x1FF;
    check = (scale != 0x100);

    reg = 0;
    GX_SET_REG(reg, scale, 23, 31);
    GX_SET_REG(reg, 0x4E, 0, 7);
    GX_BP_LOAD_REG(reg);
    gx->bpSentNot = GX_FALSE;

    GX_SET_REG(gx->cpDisp, check, 21, 21);

    height = (gx->cpDispSize >> 10 & 0x3FF) + 1;

    return __GXGetNumXfbLines(height, scale);
}

void GXSetCopyClear(GXColor clearColor, u32 clearZ) {
    u32 reg = 0;
    SET_REG_FIELD(reg, 8, 0, clearColor.r);
    SET_REG_FIELD(reg, 8, 8, clearColor.a);
    SET_REG_FIELD(reg, 8, 24, 0x4F);
    GX_WRITE_RAS_REG(reg);

    reg = 0;
    SET_REG_FIELD(reg, 8, 0, clearColor.b);
    SET_REG_FIELD(reg, 8, 8, clearColor.g);
    SET_REG_FIELD(reg, 8, 24, 0x50);
    GX_WRITE_RAS_REG(reg);

    reg = 0;
    SET_REG_FIELD(reg, 24, 0, clearZ);
    SET_REG_FIELD(reg, 8, 24, 0x51);
    GX_WRITE_RAS_REG(reg);

    gx->bpSentNot = GX_FALSE;
}

void GXSetCopyFilter(GXBool useAA, u8 samplePattern[12][2], GXBool doVertFilt, u8 vFilt[7]) {
    u32 vals[4];
    u32 unk1;
    u32 unk2;

    if (useAA) {
        vals[0] = 0;
        GX_SET_REG(vals[0], samplePattern[0][0], 28, 31);
        GX_SET_REG(vals[0], samplePattern[0][1], 24, 27);
        GX_SET_REG(vals[0], samplePattern[1][0], 20, 23);
        GX_SET_REG(vals[0], samplePattern[1][1], 16, 19);
        GX_SET_REG(vals[0], samplePattern[2][0], 12, 15);
        GX_SET_REG(vals[0], samplePattern[2][1], 8, 11);
        GX_SET_REG(vals[0], 1, 0, 7);

        vals[1] = 0;
        GX_SET_REG(vals[1], samplePattern[3][0], 28, 31);
        GX_SET_REG(vals[1], samplePattern[3][1], 24, 27);
        GX_SET_REG(vals[1], samplePattern[4][0], 20, 23);
        GX_SET_REG(vals[1], samplePattern[4][1], 16, 19);
        GX_SET_REG(vals[1], samplePattern[5][0], 12, 15);
        GX_SET_REG(vals[1], samplePattern[5][1], 8, 11);
        GX_SET_REG(vals[1], 2, 0, 7);

        vals[2] = 0;
        GX_SET_REG(vals[2], samplePattern[6][0], 28, 31);
        GX_SET_REG(vals[2], samplePattern[6][1], 24, 27);
        GX_SET_REG(vals[2], samplePattern[7][0], 20, 23);
        GX_SET_REG(vals[2], samplePattern[7][1], 16, 19);
        GX_SET_REG(vals[2], samplePattern[8][0], 12, 15);
        GX_SET_REG(vals[2], samplePattern[8][1], 8, 11);
        GX_SET_REG(vals[2], 3, 0, 7);

        vals[3] = 0;
        GX_SET_REG(vals[3], samplePattern[9][0], 28, 31);
        GX_SET_REG(vals[3], samplePattern[9][1], 24, 27);
        GX_SET_REG(vals[3], samplePattern[10][0], 20, 23);
        GX_SET_REG(vals[3], samplePattern[10][1], 16, 19);
        GX_SET_REG(vals[3], samplePattern[11][0], 12, 15);
        GX_SET_REG(vals[3], samplePattern[11][1], 8, 11);
        GX_SET_REG(vals[3], 4, 0, 7);
    } else {
        vals[0] = 0x01666666;
        vals[1] = 0x02666666;
        vals[2] = 0x03666666;
        vals[3] = 0x04666666;
    }

    GX_BP_LOAD_REG(vals[0]);
    GX_BP_LOAD_REG(vals[1]);
    GX_BP_LOAD_REG(vals[2]);
    GX_BP_LOAD_REG(vals[3]);

    unk1 = 0;
    GX_SET_REG(unk1, 0x53, 0, 7);
    unk2 = 0;
    GX_SET_REG(unk2, 0x54, 0, 7);

    if (doVertFilt) {
        GX_SET_REG(unk1, vFilt[0], 26, 31);
        GX_SET_REG(unk1, vFilt[1], 20, 25);
        GX_SET_REG(unk1, vFilt[2], 14, 19);
        GX_SET_REG(unk1, vFilt[3], 8, 13);
        GX_SET_REG(unk2, vFilt[4], 26, 31);
        GX_SET_REG(unk2, vFilt[5], 20, 25);
        GX_SET_REG(unk2, vFilt[6], 14, 19);
    } else {
        SET_REG_FIELD(unk1, 6, 0, 0);
        SET_REG_FIELD(unk1, 6, 6, 0);
        SET_REG_FIELD(unk1, 6, 12, 21);
        SET_REG_FIELD(unk1, 6, 18, 22);
        SET_REG_FIELD(unk2, 6, 0, 21);
        SET_REG_FIELD(unk2, 6, 6, 0);
        SET_REG_FIELD(unk2, 6, 12, 0);
    }

    GX_BP_LOAD_REG(unk1);
    GX_BP_LOAD_REG(unk2);

    gx->bpSentNot = GX_FALSE;
}

void GXSetDispCopyGamma(GXGamma gamma) { GX_SET_REG(gx->cpDisp, gamma, 23, 24); }

void GXCopyDisp(void* dest, GXBool doClear) {
    u32 reg;
    u32 newDest;
    GXBool changePeCtrl;

    if (doClear) {
        reg = gx->zmode;
        SET_REG_FIELD(reg, 1, 0, 1);
        SET_REG_FIELD(reg, 3, 1, 7);
        GX_BP_LOAD_REG(reg);

        reg = gx->cmode0;
        SET_REG_FIELD(reg, 1, 0, 0);
        SET_REG_FIELD(reg, 1, 1, 0);
        GX_BP_LOAD_REG(reg);
    }

    changePeCtrl = GX_FALSE;
    if ((doClear || (gx->peCtrl & 0x7) == 3) && (gx->peCtrl >> 6 & 0x1) == 1) {
        changePeCtrl = GX_TRUE;
        reg = gx->peCtrl;
        SET_REG_FIELD(reg, 1, 6, 0);
        GX_BP_LOAD_REG(reg);
    }

    GX_BP_LOAD_REG(gx->cpDispSrc);
    GX_BP_LOAD_REG(gx->cpDispSize);
    GX_BP_LOAD_REG(gx->cpDispStride);

    newDest = (u32)dest & 0x3FFFFFFF;
    reg = 0;
    GX_SET_REG(reg, newDest >> 5, 11, 31);
    GX_SET_REG(reg, 0x4B, 0, 7);
    GX_BP_LOAD_REG(reg);

    GX_SET_REG(gx->cpDisp, doClear, 20, 20);
    GX_SET_REG(gx->cpDisp, 1, 17, 17);
    GX_SET_REG(gx->cpDisp, 0x52, 0, 7);
    GX_BP_LOAD_REG(gx->cpDisp);

    if (doClear) {
        GX_BP_LOAD_REG(gx->zmode);
        GX_BP_LOAD_REG(gx->cmode0);
    }

    if (changePeCtrl) {
        GX_BP_LOAD_REG(gx->peCtrl);
    }

    gx->bpSentNot = GX_FALSE;
}

void GXCopyTex(void* dest, GXBool doClear) {
    u32 reg;
    u32 reg2;
    u32 newDest;
    GXBool check;

    if (doClear) {
        reg = gx->zmode;
        SET_REG_FIELD(reg, 1, 0, 1);
        SET_REG_FIELD(reg, 3, 1, 7);
        GX_BP_LOAD_REG(reg);

        reg = gx->cmode0;
        SET_REG_FIELD(reg, 1, 0, 0);
        SET_REG_FIELD(reg, 1, 1, 0);
        GX_BP_LOAD_REG(reg);
    }

    check = GX_FALSE;
    reg2 = gx->peCtrl;
    if (gx->cpTexZ && (reg2 & 0x7) != 3) {
        check = GX_TRUE;
        GX_SET_REG(reg2, 3, 29, 31);
    }

    if ((doClear || (reg2 & 0x7) == 3) && (reg2 >> 6 & 0x1) == 1) {
        check = GX_TRUE;
        GX_SET_REG(reg2, 0, 25, 25);
    }

    if (check) {
        GX_BP_LOAD_REG(reg2);
    }

    GX_BP_LOAD_REG(gx->cpTexSrc);
    GX_BP_LOAD_REG(gx->cpTexSize);
    GX_BP_LOAD_REG(gx->cpTexStride);

    newDest = (u32)dest & 0x3FFFFFFF;
    reg = 0;
    GX_SET_REG(reg, newDest >> 5, 11, 31);
    GX_SET_REG(reg, 0x4B, 0, 7);
    GX_BP_LOAD_REG(reg);

    GX_SET_REG(gx->cpTex, doClear, 20, 20);
    GX_SET_REG(gx->cpTex, 0, 17, 17);
    GX_SET_REG(gx->cpTex, 0x52, 0, 7);
    GX_BP_LOAD_REG(gx->cpTex);

    if (doClear) {
        GX_BP_LOAD_REG(gx->zmode);
        GX_BP_LOAD_REG(gx->cmode0);
    }

    if (check) {
        GX_BP_LOAD_REG(gx->peCtrl);
    }

    gx->bpSentNot = GX_FALSE;
}

void GXClearBoundingBox(void) {
    GX_BP_LOAD_REG(0x550003FF);
    GX_BP_LOAD_REG(0x560003FF);
    gx->bpSentNot = GX_FALSE;
}
