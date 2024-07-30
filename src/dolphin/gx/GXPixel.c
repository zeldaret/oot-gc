#include "dolphin.h"
#include "math.h"

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color) {
#if IS_MQ
    u32 fogColorReg;
    u32 fogParamReg0;
    u32 fogParamReg1;
    u32 fogParamReg2;
    u32 fogParamReg3;
    f32 a;
    f32 c;
    u32 a_bits;
    u32 c_bits;
#else
    f32 a;
    f32 c;
    u32 a_bits;
    u32 c_bits;
    u32 fogColorReg = 0;
    u32 fogParamReg0 = 0;
    u32 fogParamReg1 = 0;
    u32 fogParamReg2 = 0;
    u32 fogParamReg3 = 0;

    u32 fsel = type & 7;
    bool isOrtho = (type >> 3) & 1;

    if (isOrtho) {
        if (farz == nearz || endz == startz) {
            a = 0.0f;
            c = 0.0f;
        } else {
            a = (1.0f / (endz - startz)) * (farz - nearz);
            c = (1.0f / (endz - startz)) * (startz - nearz);
        }
    } else
#endif

    {
        f32 tmpA;
        f32 tmpB;
        f32 tmpC;
        u32 expB;
        u32 magB;
        u32 shiftB;

        if (farz == nearz || endz == startz) {
            tmpA = 0.0f;
            tmpB = 0.5f;
            tmpC = 0.0f;
        } else {
            tmpA = (farz * nearz) / ((farz - nearz) * (endz - startz));
            tmpB = farz / (farz - nearz);
            tmpC = startz / (endz - startz);
        }

        expB = 0;
        while (tmpB > 1.0) {
            tmpB /= 2.0f;
            expB++;
        }
        while (tmpB > 0.0f && tmpB < 0.5) {
            tmpB *= 2.0f;
            expB--;
        }

        a = tmpA / (1 << expB + 1);
        magB = 8388638.0f * tmpB;
        shiftB = expB + 1;
        c = tmpC;

#if IS_MQ
        fogParamReg1 = 0;
        SET_REG_FIELD(fogParamReg1, 24, 0, magB);
        SET_REG_FIELD(fogParamReg1, 8, 24, 0xEF);

        fogParamReg2 = 0;
        SET_REG_FIELD(fogParamReg2, 5, 0, shiftB);
        SET_REG_FIELD(fogParamReg2, 8, 24, 0xF0);
#else
        GX_SET_REG(fogParamReg1, magB, GX_BP_FOGPARAM1_B_MAG_ST, GX_BP_FOGPARAM1_B_MAG_END);
        GX_SET_REG(fogParamReg2, shiftB, GX_BP_FOGPARAM2_B_SHIFT_ST, GX_BP_FOGPARAM2_B_SHIFT_END);

        GX_SET_REG(fogParamReg1, GX_BP_REG_FOGPARAM1, 0, 7);
        GX_SET_REG(fogParamReg2, GX_BP_REG_FOGPARAM2, 0, 7);
#endif
    }

    a_bits = *(u32*)&a;
    c_bits = *(u32*)&c;

#if IS_MQ
    fogParamReg0 = 0;
    SET_REG_FIELD(fogParamReg0, 11, 0, (a_bits >> 12) & 0x7FF);
    SET_REG_FIELD(fogParamReg0, 8, 11, (a_bits >> 23) & 0xFF);
    SET_REG_FIELD(fogParamReg0, 1, 19, (a_bits >> 31));
    SET_REG_FIELD(fogParamReg0, 8, 24, 0xEE);

    fogParamReg3 = 0;
    SET_REG_FIELD(fogParamReg3, 11, 0, (c_bits >> 12) & 0x7FF);
    SET_REG_FIELD(fogParamReg3, 8, 11, (c_bits >> 23) & 0xFF);
    SET_REG_FIELD(fogParamReg3, 1, 19, (c_bits >> 31));
    SET_REG_FIELD(fogParamReg3, 1, 20, 0);
    SET_REG_FIELD(fogParamReg3, 3, 21, type);
    SET_REG_FIELD(fogParamReg3, 8, 24, 0xF1);

    fogColorReg = 0;
    SET_REG_FIELD(fogColorReg, 8, 0, color.b);
    SET_REG_FIELD(fogColorReg, 8, 8, color.g);
    SET_REG_FIELD(fogColorReg, 8, 16, color.r);
    SET_REG_FIELD(fogColorReg, 8, 24, 0xF2);
#else
    GX_SET_REG(fogParamReg0, a_bits >> 12, GX_BP_FOGPARAM0_A_MANT_ST, GX_BP_FOGPARAM0_A_MANT_END);
    GX_SET_REG(fogParamReg0, a_bits >> 23, GX_BP_FOGPARAM0_A_EXP_ST, GX_BP_FOGPARAM0_A_EXP_END);
    GX_SET_REG(fogParamReg0, a_bits >> 31, GX_BP_FOGPARAM0_A_SIGN_ST, GX_BP_FOGPARAM0_A_SIGN_END);

    GX_SET_REG(fogParamReg0, GX_BP_REG_FOGPARAM0, 0, 7);

    GX_SET_REG(fogParamReg3, c_bits >> 12, GX_BP_FOGPARAM3_C_MANT_ST, GX_BP_FOGPARAM3_C_MANT_END);
    GX_SET_REG(fogParamReg3, c_bits >> 23, GX_BP_FOGPARAM3_C_EXP_ST, GX_BP_FOGPARAM3_C_EXP_END);
    GX_SET_REG(fogParamReg3, c_bits >> 31, GX_BP_FOGPARAM3_C_SIGN_ST, GX_BP_FOGPARAM3_C_SIGN_END);

    GX_SET_REG(fogParamReg3, isOrtho, GX_BP_FOGPARAM3_PROJ_ST, GX_BP_FOGPARAM3_PROJ_END);
    GX_SET_REG(fogParamReg3, fsel, GX_BP_FOGPARAM3_FSEL_ST, GX_BP_FOGPARAM3_FSEL_END);

    GX_SET_REG(fogParamReg3, GX_BP_REG_FOGPARAM3, 0, 7);

    GX_SET_REG(fogColorReg, color.b, GX_BP_FOGCOLOR_RGB_ST + 16, GX_BP_FOGCOLOR_RGB_END);
    GX_SET_REG(fogColorReg, color.g, (GX_BP_FOGCOLOR_RGB_ST + 8), (GX_BP_FOGCOLOR_RGB_END - 8));
    GX_SET_REG(fogColorReg, color.r, (GX_BP_FOGCOLOR_RGB_ST + 0), (GX_BP_FOGCOLOR_RGB_END - 16));
    GX_SET_REG(fogColorReg, GX_BP_REG_FOGCOLOR, 0, 7);
#endif

    GX_BP_LOAD_REG(fogParamReg0);
    GX_BP_LOAD_REG(fogParamReg1);
    GX_BP_LOAD_REG(fogParamReg2);
    GX_BP_LOAD_REG(fogParamReg3);
    GX_BP_LOAD_REG(fogColorReg);

    gx->bpSentNot = GX_FALSE;
}

void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, const Mtx44 proj) {
    f32 x, nearZ, scale, sideX, dist;
    u32 i;

#if IS_MQ
    if (proj[3][3] == 0.0) {
        nearZ = proj[2][3] / (proj[2][2] - 1.0f);
        sideX = (nearZ * (proj[0][2] + 1.0f)) / proj[0][0];
    } else {
        nearZ = (proj[2][3] + 1.0f) / proj[2][2];
        sideX = -(proj[0][3] - 1.0f) / proj[0][0];
    }
#else
    if (proj[3][3] == 0.0) {
        nearZ = proj[2][3] / (proj[2][2] - 1.0f);
        sideX = nearZ / proj[0][0];
    } else {
        sideX = 1.0f / proj[0][0];
        nearZ = (f32)M_SQRT3 * sideX;
    }
#endif

    scale = 2.0f / width;

    for (i = 0; i < ARRAY_COUNT(table->r); i++) {
        x = (i + 1) * 32;
        x *= scale;
        x *= sideX;
        dist = sqrtf(1.0f + (x * x) / (nearZ * nearZ));
        table->r[i] = (u32)(dist * 256.0f) & 0xFFF;
    }
}

void GXSetFogRangeAdj(GXBool enable, u16 center, GXFogAdjTable* table) {
    u32 fogRangeReg;
    u32 fogRangeRegK;
    u32 i;

    if (enable) {
        for (i = 0; i < ARRAY_COUNT(table->r); i += 2) {
            fogRangeRegK = 0;
            GX_SET_REG(fogRangeRegK, table->r[i], GX_BP_FOGRANGEK_HI_ST, GX_BP_FOGRANGEK_HI_END);
            GX_SET_REG(fogRangeRegK, table->r[i + 1], GX_BP_FOGRANGEK_LO_ST, GX_BP_FOGRANGEK_LO_END);
            GX_SET_REG(fogRangeRegK, GX_BP_REG_FOGRANGEK0 + (i / 2), 0, 7);
            GX_BP_LOAD_REG(fogRangeRegK);
        }
    }

    fogRangeReg = 0;
    GX_SET_REG(fogRangeReg, center + 342, GX_BP_FOGRANGE_CENTER_ST, GX_BP_FOGRANGE_CENTER_END);
    GX_SET_REG(fogRangeReg, enable, GX_BP_FOGRANGE_ENABLED_ST, GX_BP_FOGRANGE_ENABLED_END);
    GX_SET_REG(fogRangeReg, GX_BP_REG_FOGRANGE, 0, 7);
    GX_BP_LOAD_REG(fogRangeReg);

    gx->bpSentNot = GX_FALSE;
}

void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op) {
    u32 blendModeReg = gx->cmode0;
    GX_SET_REG2(blendModeReg, type == GX_BM_SUBTRACT, GX_BP_BLENDMODE_SUBTRACT_ST, GX_BP_BLENDMODE_SUBTRACT_END);
    GX_SET_REG2(blendModeReg, type, GX_BP_BLENDMODE_ENABLE_ST, GX_BP_BLENDMODE_ENABLE_END);
    GX_SET_REG2(blendModeReg, type == GX_BM_LOGIC, GX_BP_BLENDMODE_LOGIC_OP_ST, GX_BP_BLENDMODE_LOGIC_OP_END);
    GX_SET_REG2(blendModeReg, op, GX_BP_BLENDMODE_LOGICMODE_ST, GX_BP_BLENDMODE_LOGICMODE_END);
    GX_SET_REG2(blendModeReg, src_factor, GX_BP_BLENDMODE_SRCFACTOR_ST, GX_BP_BLENDMODE_SRCFACTOR_END);
    GX_SET_REG2(blendModeReg, dst_factor, GX_BP_BLENDMODE_DSTFACTOR_ST, GX_BP_BLENDMODE_DSTFACTOR_END);

    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;

    gx->bpSentNot = false;
}

void GXSetColorUpdate(GXBool updateEnable) {
    u32 blendModeReg = gx->cmode0;
    GX_SET_REG2(blendModeReg, updateEnable, GX_BP_BLENDMODE_COLOR_UPDATE_ST, GX_BP_BLENDMODE_COLOR_UPDATE_END);
    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetAlphaUpdate(GXBool updateEnable) {
    u32 blendModeReg = gx->cmode0;
    GX_SET_REG2(blendModeReg, updateEnable, GX_BP_BLENDMODE_ALPHA_UPDATE_ST, GX_BP_BLENDMODE_ALPHA_UPDATE_END);
    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetZMode(GXBool compareEnable, GXCompare func, GXBool updateEnable) {
    u32 zModeReg = gx->zmode;
    GX_SET_REG2(zModeReg, compareEnable, GX_BP_ZMODE_TEST_ENABLE_ST, GX_BP_ZMODE_TEST_ENABLE_END);
    GX_SET_REG2(zModeReg, func, GX_BP_ZMODE_COMPARE_ST, GX_BP_ZMODE_COMPARE_END);
    GX_SET_REG2(zModeReg, updateEnable, GX_BP_ZMODE_UPDATE_ENABLE_ST, GX_BP_ZMODE_UPDATE_ENABLE_END);
    GX_BP_LOAD_REG(zModeReg);
    gx->zmode = zModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetZCompLoc(GXBool beforeTex) {
    GX_SET_REG(gx->peCtrl, beforeTex, GX_BP_ZCONTROL_BEFORE_TEX_ST, GX_BP_ZCONTROL_BEFORE_TEX_END);
    GX_BP_LOAD_REG(gx->peCtrl);
    gx->bpSentNot = GX_FALSE;
}

void GXSetPixelFmt(GXPixelFmt pixelFmt, GXZFmt16 zFmt) {
    GXBool isZ16;
    static u32 p2f[GX_MAX_PIXELFMT] = {GX_PF_RGB8_Z24, GX_PF_RGBA6_Z24, GX_PF_RGB565_Z16, GX_PF_Z24,
                                       GX_PF_Y8,       GX_PF_Y8,        GX_PF_Y8,         GX_PF_U8};

    const u32 zControlRegOld = gx->peCtrl;

    GX_SET_REG(gx->peCtrl, p2f[pixelFmt], GX_BP_ZCONTROL_PIXEL_FMT_ST, GX_BP_ZCONTROL_PIXEL_FMT_END);
    GX_SET_REG(gx->peCtrl, zFmt, GX_BP_ZCONTROL_Z_FMT_ST, GX_BP_ZCONTROL_Z_FMT_END);

    if (zControlRegOld != gx->peCtrl) {
        GX_BP_LOAD_REG(gx->peCtrl);
        isZ16 = (pixelFmt == GX_PF_RGB565_Z16) ? GX_TRUE : GX_FALSE;
        GX_SET_REG(gx->genMode, isZ16, GX_BP_GENMODE_MULTISAMPLE_ST, GX_BP_GENMODE_MULTISAMPLE_END);
        gx->dirtyState |= GX_DIRTY_GEN_MODE;
    }

    if (p2f[pixelFmt] == GX_PF_Y8) {
        SET_REG_FIELD(gx->cmode1, 2, 9, (pixelFmt - 4) & 0x3);
        SET_REG_FIELD(gx->cmode1, 8, 24, 0x42);
        GX_BP_LOAD_REG(gx->cmode1);
    }

    gx->bpSentNot = false;
}

void GXSetDither(GXBool dither) {
    u32 blendModeReg = gx->cmode0;
    GX_SET_REG(blendModeReg, dither, GX_BP_BLENDMODE_DITHER_ST, GX_BP_BLENDMODE_DITHER_END);
    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetDstAlpha(GXBool enable, u8 alpha) {
    u32 dstAlpha = gx->cmode1;
    GX_SET_REG2(dstAlpha, alpha, GX_BP_DSTALPHA_ALPHA_ST, GX_BP_DSTALPHA_ALPHA_END);
    GX_SET_REG2(dstAlpha, enable, GX_BP_DSTALPHA_ENABLE_ST, GX_BP_DSTALPHA_ENABLE_END);
    GX_BP_LOAD_REG(dstAlpha);
    gx->cmode1 = dstAlpha;
    gx->bpSentNot = GX_FALSE;
}

void GXSetFieldMask(GXBool enableEven, GXBool enableOdd) {
    u32 fieldMaskReg = 0;
    GX_SET_REG(fieldMaskReg, enableOdd, GX_BP_FIELDMASK_ODD_ST, GX_BP_FIELDMASK_ODD_END);
    GX_SET_REG(fieldMaskReg, enableEven, GX_BP_FIELDMASK_EVEN_ST, GX_BP_FIELDMASK_EVEN_END);
    GX_SET_REG(fieldMaskReg, GX_BP_REG_FIELDMASK, 0, 7);

    GX_BP_LOAD_REG(fieldMaskReg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetFieldMode(GXBool texLOD, GXBool adjustAR) {
    GX_SET_REG(gx->lpSize, adjustAR, GX_BP_LINEPTWIDTH_ADJUST_ST, GX_BP_LINEPTWIDTH_ADJUST_END);
    GX_BP_LOAD_REG(gx->lpSize);

    __GXFlushTextureState();
    GX_BP_LOAD_REG(GX_BP_REG_FIELDMODE << 24 | texLOD);
    __GXFlushTextureState();
}

bool __GXSetRange(f32, f32) {}
