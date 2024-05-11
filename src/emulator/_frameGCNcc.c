#include "dolphin.h"
#include "emulator/_buildtev.h"
#include "emulator/frame.h"
#include "emulator/simGCN.h"

GXTevColorArg gCombinedColor[] = {
    0x00000000, 0x00000008, 0x00000008, 0x00000006, 0x0000000A, 0x0000000E, 0x0000000C, 0x00000001,
    0x00000009, 0x00000009, 0x00000007, 0x0000000B, 0x0000000E, 0x0000000F, 0x0000000F, 0x0000000F,
};

GXTevAlphaArg gCombinedAlpha[] = {
    0x00000000, 0x00000004, 0x00000004, 0x00000003, 0x00000005, 0x00000006, 0x00000006, 0x00000007,
};

static GXTevStageID ganNameTevStage[] = {
    0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007,
    0x00000008, 0x00000009, 0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D, 0x0000000E, 0x0000000F,
};

static TevColorOp sTevColorOp[] = {
    {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001},
    {0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000001},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

static GXTevColorArg sTevColorArg[] = {
    0x0000000F, 0x0000000F, 0x0000000F, 0x00000000, 0x0000000F, 0x0000000F, 0x0000000F,
    0x00000000, 0x0000000F, 0x00000002, 0x00000004, 0x0000000F, 0x0000000F, 0x00000000,
    0x00000004, 0x00000002, 0x0000000F, 0x00000002, 0x0000000C, 0x00000000,
};

static GXTevAlphaArg sTevAlphaArg[] = {
    0x00000007, 0x00000007, 0x00000007, 0x00000000, 0x00000007, 0x00000007, 0x00000007,
    0x00000000, 0x00000007, 0x00000001, 0x00000002, 0x00000007, 0x00000007, 0x00000000,
    0x00000002, 0x00000001, 0x00000007, 0x00000001, 0x00000006, 0x00000000,
};

static u8 sOrder[] = {0x00, 0x03, 0x01, 0x04, 0x02};

static u8 sReplace[] = {0x03, 0x03, 0x00, 0x01, 0x03};

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
