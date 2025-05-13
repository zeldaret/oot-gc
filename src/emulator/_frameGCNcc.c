#include "dolphin.h"
#include "emulator/_buildtev.h"
#include "emulator/frame.h"
#include "emulator/simGCN.h"

#if VERSION == MQ_J
u16 gnTempBuffer[N64_FRAME_WIDTH * N64_FRAME_HEIGHT];
u16 gnCopyBuffer[N64_FRAME_WIDTH * N64_FRAME_HEIGHT];
u16 gnCameraBuffer[ZELDA2_CAMERA_WIDTH * ZELDA2_CAMERA_HEIGHT];
#endif

GXTevColorArg gCombinedColor[] = {
    GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXC, GX_CC_C2,   GX_CC_RASC,  GX_CC_KONST, GX_CC_ONE,  GX_CC_APREV,
    GX_CC_TEXA,  GX_CC_TEXA, GX_CC_A2,   GX_CC_RASA, GX_CC_KONST, GX_CC_ZERO,  GX_CC_ZERO, GX_CC_ZERO,
};

GXTevAlphaArg gCombinedAlpha[] = {
    GX_CA_APREV, GX_CA_TEXA, GX_CA_TEXA, GX_CA_A2, GX_CA_RASA, GX_CA_KONST, GX_CA_KONST, GX_CA_ZERO,
};

static GXTevStageID ganNameTevStage[] = {
    GX_TEVSTAGE0,  GX_TEVSTAGE1,  GX_TEVSTAGE2,  GX_TEVSTAGE3,  GX_TEVSTAGE4,  GX_TEVSTAGE5,
    GX_TEVSTAGE6,  GX_TEVSTAGE7,  GX_TEVSTAGE8,  GX_TEVSTAGE9,  GX_TEVSTAGE10, GX_TEVSTAGE11,
    GX_TEVSTAGE12, GX_TEVSTAGE13, GX_TEVSTAGE14, GX_TEVSTAGE15,
};

static TevColorOp sTevColorOp[] = {
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG0}, {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG1},
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG0}, {GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG0},
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV},
};

static GXTevColorArg sTevColorArg[5][4] = {
    {GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV}, {GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV},
    {GX_CC_ZERO, GX_CC_C0, GX_CC_C1, GX_CC_ZERO},      {GX_CC_ZERO, GX_CC_CPREV, GX_CC_C1, GX_CC_C0},
    {GX_CC_ZERO, GX_CC_C0, GX_CC_ONE, GX_CC_CPREV},
};

static GXTevAlphaArg sTevAlphaArg[5][4] = {
    {GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV}, {GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV},
    {GX_CA_ZERO, GX_CA_A0, GX_CA_A1, GX_CA_ZERO},      {GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_A0},
    {GX_CA_ZERO, GX_CA_A0, GX_CA_KONST, GX_CA_APREV},
};

static u8 sOrder[] = {0, 3, 1, 4, 2};

static u8 sReplace[] = {3, 3, 0, 1, 3};

static char* sColorNames[16] = {
    "COMBINED",    "TEXEL0",      "TEXEL1",         "PRIMITIVE",    "SHADE",
    "ENVIRONMENT", "1",           "COMBINED_ALPHA", "TEXEL0_ALPHA", "TEXEL1_ALPHA",
    "PRIM_ALPHA",  "SHADE_ALPHA", "ENV_ALPHA",      "LOD_FRAC",     "PRIM_LOD_FRAC",
    "0",
};

static char* sAlphaNames[2][8] = {
    {"LOD_FRAC", "TEXEL0", "TEXEL1", "PRIMITIVE", "SHADE", "ENVIRONMENT", "1", "0"},
    {"COMBINED", "TEXEL0", "TEXEL1", "PRIMITIVE", "SHADE", "ENVIRONMENT", "1", "0"},
};

static char* strings[] = {
    "PIXEL ", "MEMORY", "BL_REG", "FOGREG", "CC_A  ", "FOG_A ", "STEP_A", "ZERO  ",
    "PIXEL ", "MEMORY", "BL_REG", "FOGREG", "A_INV",  "MEM_A",  "ONE  ",  "ZERO ",
};

char unused[] = "0x%08x = ( ";

static void SetTableTevStages(Frame* pFrame, CombineModeTev* ctP) {
    s32 i;
    int iStart;
    s32 pad[4];
    GXColor color;
    s32 pad2[4];
    TevOrder* toP;
    TevColorOp* tcP;
    GXTevColorArg* cArgP;
    GXTevAlphaArg* aArgP;

    if (((pFrame->aMode[FMT_OTHER0] >> 0x1E) == 3) && (((pFrame->aMode[FMT_OTHER0] >> 0x1A) & 3) == 1) &&
        !(ctP->flags & 4)) {
        GXSetNumTevStages(ctP->numStages + 1);
    } else {
        GXSetNumTevStages(ctP->numStages);
    }

    GXSetNumTexGens(ctP->numTexGen);
    GXSetNumChans(ctP->numTexGen != 0 ? ctP->numChan : 1);

    if (ctP->flags & 2) {
        GXSetTevColor(GX_TEVREG1, pFrame->aColor[3]);
    }

    if (ctP->flags & 1) {
        GXSetTevColor(GX_TEVREG2, pFrame->aColor[4]);
    }

    if (ctP->flags & 4) {
        color.r = color.g = color.b = pFrame->primLODfrac;
        color.a = pFrame->primLODfrac;
        GXSetTevColor(GX_TEVREG0, color);
    } else if (((pFrame->aMode[FMT_OTHER0] >> 0x1E) == 3) && (((pFrame->aMode[FMT_OTHER0] >> 0x1A) & 3) == 1)) {
        GXSetTevColor(GX_TEVREG0, pFrame->aColor[0]);
    }

    iStart = 0;
    for (i = 0; i < ctP->numStages; i++) {
        toP = &ctP->tevOrder[i];
        tcP = ctP->tevColorOpP[i];
        cArgP = ctP->tevColorArg[i];
        aArgP = ctP->tevAlphaArg[i];

        GXSetTevOrder(ganNameTevStage[iStart + i], toP[0].coordID, toP[0].mapID, toP[0].chanID);
        GXSetTevColorOp(ganNameTevStage[iStart + i], tcP[0].op, tcP[0].bias, tcP[0].scale, tcP[0].clamp,
                        tcP[0].out_reg);
        GXSetTevAlphaOp(ganNameTevStage[iStart + i], tcP[1].op, tcP[1].bias, tcP[1].scale, tcP[1].clamp,
                        tcP[1].out_reg);
        GXSetTevColorIn(ganNameTevStage[iStart + i], cArgP[0], cArgP[1], cArgP[2], cArgP[3]);
        GXSetTevAlphaIn(ganNameTevStage[iStart + i], aArgP[0], aArgP[1], aArgP[2], aArgP[3]);
        GXSetTevKColorSel(ganNameTevStage[iStart + i], GX_TEV_KCSEL_1);
        GXSetTevKAlphaSel(ganNameTevStage[iStart + i], GX_TEV_KASEL_1);
    }

    if (((pFrame->aMode[FMT_OTHER0] >> 0x1E) == 3) && (((pFrame->aMode[FMT_OTHER0] >> 0x1A) & 3) == 1) &&
        !(ctP->flags & 4)) {
        GXSetTevOrder(ganNameTevStage[iStart + i], GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColorOp(ganNameTevStage[iStart + i], GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevAlphaOp(ganNameTevStage[iStart + i], GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevColorIn(ganNameTevStage[iStart + i], GX_CC_CPREV, GX_CC_C0, GX_CC_A0, GX_CC_ZERO);
        GXSetTevAlphaIn(ganNameTevStage[iStart + i], GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevKColorSel(ganNameTevStage[iStart + i], GX_TEV_KCSEL_K2);
        GXSetTevKAlphaSel(ganNameTevStage[iStart + i], GX_TEV_KASEL_K2_A);
    }
}

void SetNumTexGensChans(Frame* pFrame, s32 numCycles) {
    u8 nColor[4];
    u8 nAlpha[4];
    u32 tempColor;
    u32 tempAlpha;
    s32 i;
    s32 j;
    s32 numGens;
    s32 numChans;

    numGens = 0;
    numChans = 1;

    for (i = 0; i < numCycles; i++) {
        if (i == 0) {
            tempColor = pFrame->aMode[FMT_COMBINE_COLOR1];
            tempAlpha = pFrame->aMode[FMT_COMBINE_ALPHA1];
        } else {
            tempColor = pFrame->aMode[FMT_COMBINE_COLOR2];
            tempAlpha = pFrame->aMode[FMT_COMBINE_ALPHA2];
        }

        nColor[0] = tempColor & 0xFF;
        nColor[1] = (tempColor >> 8) & 0xFF;
        nColor[2] = (tempColor >> 16) & 0xFF;
        nColor[3] = (tempColor >> 24) & 0xFF;

        nAlpha[0] = tempAlpha & 0xFF;
        nAlpha[1] = (tempAlpha >> 8) & 0xFF;
        nAlpha[2] = (tempAlpha >> 16) & 0xFF;
        nAlpha[3] = (tempAlpha >> 24) & 0xFF;

        for (j = 0; j < 4; j++) {
            if (nColor[j] == 1 || nAlpha[j] == 1) {
                if (numGens <= 0) {
                    numGens = 1;
                }
            } else if (nColor[j] == 2 || nAlpha[j] == 2) {
                if (numGens <= 1) {
                    numGens = 2;
                }
            }
        }
    }

    GXSetNumTexGens(numGens);
    GXSetNumChans(numChans);
}

void SetTevStages(Frame* pFrame, s32 cycle, s32 numCycles) {
    u8 nColor[4];
    u8 nAlpha[4];
    u32 tempColor;
    u32 tempAlpha;
    GXTevColorArg colorArg[4];
    GXTevAlphaArg alphaArg[4];
    GXTevStageID tevStages[5];
    TevColorOp* tP;
    s32 j;
    GXTevColorArg* cArgP;
    GXTevAlphaArg* aArgP;
    s32 i;
    // bug? order never used
    s32 order;
    s32 pad[2];

    order = 0;
    if (cycle == 0) {
        tempColor = pFrame->aMode[FMT_COMBINE_COLOR1];
        tempAlpha = pFrame->aMode[FMT_COMBINE_ALPHA1];
    } else {
        tempColor = pFrame->aMode[FMT_COMBINE_COLOR2];
        tempAlpha = pFrame->aMode[FMT_COMBINE_ALPHA2];
    }

    nColor[0] = tempColor & 0xFF;
    nColor[1] = (tempColor >> 8) & 0xFF;
    nColor[2] = (tempColor >> 16) & 0xFF;
    nColor[3] = (tempColor >> 24) & 0xFF;

    nAlpha[0] = tempAlpha & 0xFF;
    nAlpha[1] = (tempAlpha >> 8) & 0xFF;
    nAlpha[2] = (tempAlpha >> 16) & 0xFF;
    nAlpha[3] = (tempAlpha >> 24) & 0xFF;

    for (i = 0; i < 5; i++) {
        tevStages[i] = ganNameTevStage[(cycle * 5) + i];
    }

    for (i = 0; i < 4; i++) {
        j = sOrder[i];
        cArgP = sTevColorArg[j];
        aArgP = sTevAlphaArg[j];

        if (nColor[i] == 1 || nAlpha[i] == 1) {
            GXSetTevOrder(tevStages[j], ganNameTexCoord[0], ganNamePixel[0], GX_COLOR0A0);
            order |= 1 << i;
        } else if (nColor[i] == 2 || nAlpha[i] == 2) {
            GXSetTevOrder(tevStages[j], ganNameTexCoord[1], ganNamePixel[1], GX_COLOR0A0);
            order |= 1 << (i + 4);
        } else {
            GXSetTevOrder(tevStages[j], GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        }

        if (cycle == 0 && (nAlpha[i] == 0 || nAlpha[i] == 6)) {
            nAlpha[i] = 7;
        }

        if (nColor[i] == 0x1F) {
            nColor[i] = 0xF;
        } else if (nColor[i] == 0xC) {
            GXSetTevKColorSel(tevStages[j], GX_TEV_KCSEL_K1_A);
        } else {
            GXSetTevKColorSel(tevStages[j], GX_TEV_KCSEL_K1);
        }

        if (nAlpha[i] == 5) {
            GXSetTevKAlphaSel(tevStages[j], GX_TEV_KASEL_K1_A);
        } else {
            GXSetTevKAlphaSel(tevStages[j], GX_TEV_KASEL_1);
        }

        colorArg[i] = gCombinedColor[nColor[i]];
        alphaArg[i] = gCombinedAlpha[nAlpha[i]];
        cArgP[sReplace[j]] = colorArg[i];
        aArgP[sReplace[j]] = alphaArg[i];
    }

    GXSetTevOrder(tevStages[sOrder[i]], GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

    for (i = 0; i < 5; i++) {
        tP = &sTevColorOp[i];
        cArgP = sTevColorArg[i];
        aArgP = sTevAlphaArg[i];

        GXSetTevColorOp(tevStages[i], tP->op, tP->bias, tP->scale, tP->clamp, tP->out_reg);
        GXSetTevAlphaOp(tevStages[i], tP->op, tP->bias, tP->scale, tP->clamp, tP->out_reg);
        GXSetTevColorIn(tevStages[i], cArgP[0], cArgP[1], cArgP[2], cArgP[3]);
        GXSetTevAlphaIn(tevStages[i], aArgP[0], aArgP[1], aArgP[2], aArgP[3]);
    }
}

bool SetTevStageTable(Frame* pFrame, s32 numCycles) {
    u32 tempColor1;
    u32 tempAlpha1;
    u32 tempColor2;
    u32 tempAlpha2;
    CombineModeTev* ctP;

    if (gpSystem->eTypeROM == SRT_ZELDA2) {
        if (pFrame->aMode[FMT_COMBINE_COLOR1] == 0x1F040501 && pFrame->aMode[FMT_COMBINE_ALPHA1] == 0x07030701) {
            if (pFrame->aMode[FMT_COMBINE_COLOR2] == 0x04040300 && pFrame->aMode[FMT_COMBINE_ALPHA2] == 0x07050706) {
                pFrame->aMode[FMT_COMBINE_COLOR2] = 0x1F040300;
            }
        }
    }

    tempColor1 = pFrame->aMode[FMT_COMBINE_COLOR1];
    tempAlpha1 = pFrame->aMode[FMT_COMBINE_ALPHA1];

    if (numCycles == 2) {
        tempColor2 = pFrame->aMode[FMT_COMBINE_COLOR2];
        tempAlpha2 = pFrame->aMode[FMT_COMBINE_ALPHA2];
    } else {
        tempAlpha2 = 0;
        tempColor2 = 0;
    }

    ctP = BuildCombineModeTev(tempColor1, tempAlpha1, tempColor2, tempAlpha2, numCycles);
    SetTableTevStages(pFrame, ctP);
    return true;
}
