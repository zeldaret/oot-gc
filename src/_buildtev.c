#include "_buildtev.h"

GXTevColorArg gColorArgs[16] = {
    GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXC, GX_CC_C1, GX_CC_RASC, GX_CC_C2, GX_CC_ONE, GX_CC_APREV,
    GX_CC_TEXA, GX_CC_TEXA, GX_CC_A1, GX_CC_RASA, GX_CC_A2, GX_CC_ONE, GX_CC_C0, GX_CC_ZERO,
};

GXTevAlphaArg gAlphaArgs[10] = {
    GX_CA_KONST, GX_CA_TEXA, GX_CA_TEXA, GX_CA_A1, GX_CA_RASA, GX_CA_A2, GX_CA_KONST, GX_CA_ZERO,
    GX_CA_APREV, GX_CA_A0,
};

static TevColorOp sUsualOps[] = {
    { 0x00000000, 0x00000000, 0x00000000, 0, 0x00000000 },
    { 0x00000001, 0x00000000, 0x00000000, 0, 0x00000000 },
    { 0x00000001, 0x00000000, 0x00000000, 1, 0x00000000 },
    { 0x00000000, 0x00000000, 0x00000000, 1, 0x00000000 },
};

static GXTevColorArg sUsualCArgs[] = {
    GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
};

static GXTevAlphaArg sUsualAArgs[] = {
    GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
};

static s32 texelType[] = {
    0x00000001, 0x00000002, 0x00000008, 0x00000009, 0x00000001, 0x00000002, 0x00000004, 0x00000002,
};

static s32 lightType[] = {
    0x00000004, 0x0000000B, 0x00000004, 0x00000004,
};

char D_800F0568[] = "TEXCOORD0 twice -> should NOT happen!\n";

char D_800F0590[] = "TEXCOORD1 twice -> should NOT happen!\n";

char D_800F05B8[] = {
    "BAD MODE in two-texture, no C texture\n"
};

char D_800F05E0[] = {
    "case of multi-texture, with C value being a texture -> NOT HANDLED!\n"
};

static CombineModeTev tevStages;

static s32 zeroType[] = {
    0x0000000F, 0x00000007,
};

char D_80135408[6] = "NOO!!";

const s32 D_801360D8[2] = {
    0x00000000, 0x00000000,
};

#pragma GLOBAL_ASM("asm/non_matchings/_buildtev/SetColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/_buildtev/SetAlpha.s")

#pragma GLOBAL_ASM("asm/non_matchings/_buildtev/AddAlphaTevOrder.s")

#pragma GLOBAL_ASM("asm/non_matchings/_buildtev/SetupStage.s")

#pragma GLOBAL_ASM("asm/non_matchings/_buildtev/BuildCycle.s")

#pragma GLOBAL_ASM("asm/non_matchings/_buildtev/BuildCombineModeTev.s")
