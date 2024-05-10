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

#pragma GLOBAL_ASM("asm/non_matchings/_frameGCNcc/SetNumTexGensChans.s")

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
