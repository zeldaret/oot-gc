#include "dolphin.h"
#include "emulator/_buildtev.h"
#include "emulator/frame.h"
#include "emulator/simGCN.h"

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
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG0},
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG1},
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG0},
    {GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG0},
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV},
};

static GXTevColorArg sTevColorArg[] = {
    GX_CC_ZERO,  GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV, GX_CC_ZERO, GX_CC_ZERO,  GX_CC_ZERO,
    GX_CC_CPREV, GX_CC_ZERO, GX_CC_C0,   GX_CC_C1,    GX_CC_ZERO, GX_CC_ZERO,  GX_CC_CPREV,
    GX_CC_C1,    GX_CC_C0,   GX_CC_ZERO, GX_CC_C0,    GX_CC_ONE,  GX_CC_CPREV,
};

static GXTevAlphaArg sTevAlphaArg[] = {
    GX_CA_ZERO,  GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV, GX_CA_ZERO,  GX_CA_ZERO,  GX_CA_ZERO,
    GX_CA_APREV, GX_CA_ZERO, GX_CA_A0,   GX_CA_A1,    GX_CA_ZERO,  GX_CA_ZERO,  GX_CA_APREV,
    GX_CA_A1,    GX_CA_A0,   GX_CA_ZERO, GX_CA_A0,    GX_CA_KONST, GX_CA_APREV,
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

char D_800F0450[] = "0x%08x = ( ";

static void SetTableTevStages(Frame* pFrame, CombineModeTev* ctP);

#pragma GLOBAL_ASM("asm/non_matchings/_frameGCNcc/SetTableTevStages.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/_frameGCNcc/SetTevStages.s")

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
