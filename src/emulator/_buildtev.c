#include "emulator/_buildtev.h"
#include "emulator/simGCN.h"
#include "emulator/xlHeap.h"
#include "stddef.h"

GXTevColorArg gColorArgs[16] = {
    GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXC, GX_CC_C1,   GX_CC_RASC, GX_CC_C2,  GX_CC_ONE, GX_CC_APREV,
    GX_CC_TEXA,  GX_CC_TEXA, GX_CC_A1,   GX_CC_RASA, GX_CC_A2,   GX_CC_ONE, GX_CC_C0,  GX_CC_ZERO,
};

GXTevAlphaArg gAlphaArgs[10] = {
    GX_CA_KONST, GX_CA_TEXA, GX_CA_TEXA, GX_CA_A1, GX_CA_RASA, GX_CA_A2, GX_CA_KONST, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0,
};

static TevColorOp sUsualOps[] = {
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV},
    {GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV},
    {GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV},
    {GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV},
};

static GXTevColorArg sUsualCArgs[] = {
    GX_CC_ZERO,
    GX_CC_ZERO,
    GX_CC_ZERO,
    GX_CC_ZERO,
};

static GXTevAlphaArg sUsualAArgs[] = {
    GX_CA_ZERO,
    GX_CA_ZERO,
    GX_CA_ZERO,
    GX_CA_ZERO,
};

static s32 texelType[2][4] = {
    {0x00000001, 0x00000002, 0x00000008, 0x00000009},
    {0x00000001, 0x00000002, 0x00000004, 0x00000002},
};

static s32 lightType[2][2] = {
    {0x00000004, 0x0000000B},
    {0x00000004, 0x00000004},
};

char D_800F0568[] = "TEXCOORD0 twice -> should NOT happen!\n";
char D_800F0590[] = "TEXCOORD1 twice -> should NOT happen!\n";
char D_800F05B8[] = "BAD MODE in two-texture, no C texture\n";
char D_800F05E0[] = "case of multi-texture, with C value being a texture -> NOT HANDLED!\n";

static CombineModeTev tevStages;

static s32 zeroType[] = {
    0x0000000F,
    0x00000007,
};

char D_80135408[6] = "NOO!!";

const s32 D_801360D8[2] = {
    0x00000000,
    0x00000000,
};

// special ``memset`` function?
inline void memset(void* ptr, int value, size_t num) {
    u8* p = ptr;

    while (num-- > 0) {
        *p++ = value;
    }
}

void SetColor(u8* stageValues, u32 colorVal, u8 cycle) {
    s32 i;

    stageValues[0] = colorVal & 0xFF;
    stageValues[1] = (colorVal >> 8) & 0xFF;
    stageValues[2] = (colorVal >> 16) & 0xFF;
    stageValues[3] = (colorVal >> 24) & 0xFF;

    for (i = 0; i < 4; i++) {
        if (cycle == 2) {
            if (stageValues[i] == 1) {
                stageValues[i] = 2;
            }
            if (stageValues[i] == 8) {
                stageValues[i] = 9;
            }
        } else {
            if (stageValues[i] == 0) {
                stageValues[i] = 0xF;
            } else if (stageValues[i] == 7 && gpSystem->eTypeROM == SRT_ZELDA2) {
                stageValues[i] = 6;
            } else if (stageValues[i] == 7) {
                stageValues[i] = 0xF;
            }
        }

        if (stageValues[i] == 0x1F) {
            stageValues[i] = 0xF;
        }
    }

    if (cycle == 1 && colorVal == 0) {
        stageValues[2] = 0xF;
        stageValues[1] = 0xF;
        stageValues[0] = 0xF;
        stageValues[3] = 1;
    }
}

void SetAlpha(u8* stageValues, u32 alphaVal, u8 cycle, u32 colorVal, u32 color2Val, u32 alpha2Val) {
    s32 i;

    stageValues[0] = alphaVal & 0xFF;
    stageValues[1] = (alphaVal >> 8) & 0xFF;
    stageValues[2] = (alphaVal >> 16) & 0xFF;
    stageValues[3] = (alphaVal >> 24) & 0xFF;

    for (i = 0; i < 4; i++) {
        if (cycle == 2) {
            if (stageValues[i] == 0) {
                stageValues[i] = 8;
            }
            if (stageValues[i] == 2) {
                stageValues[i] = 1;
            } else if (stageValues[i] == 1) {
                stageValues[i] = 2;
            }
        }

        if (i == 2 && stageValues[i] == 6) {
            stageValues[i] = 9;
        }
    }

    if (cycle == 1 && alphaVal == 0) {
        stageValues[2] = 7;
        stageValues[1] = 7;
        stageValues[0] = 7;
        stageValues[3] = 1;
    }
}

s32 AddAlphaTevOrder(CombineModeTev* tvP, s32 foundTypes, s32 curStage) {
    s32 ret = 0;

    if (foundTypes & 3) {
        if (foundTypes & 1) {
            while (tvP->tevOrder[curStage].coordID == GX_TEXCOORD1) {
                tvP->tevColorOpP[curStage + 1][1] = sUsualOps[0];
                curStage++;
                ret++;
            }
            tvP->tevOrder[curStage].coordID = GX_TEXCOORD0;
            tvP->tevOrder[curStage].mapID = GX_TEXMAP0;
        } else {
            while (tvP->tevOrder[curStage].coordID == GX_TEXCOORD0) {
                tvP->tevColorOpP[curStage + 1][1] = sUsualOps[0];
                curStage++;
                ret++;
            }
            tvP->tevOrder[curStage].coordID = GX_TEXCOORD1;
            tvP->tevOrder[curStage].mapID = GX_TEXMAP1;
        }
    }

    if (foundTypes & 0x400) {
        tvP->tevOrder[curStage].chanID = GX_COLOR0A0;
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/non_matchings/_buildtev/SetupStage.s")

void BuildCycle(CombineModeTev* tvP, u8 (*stageValues)[4]) {
    s32 numCParts;
    s32 numAParts;
    s32 i;

    numCParts = SetupStage(tvP, stageValues[0], 0);
    numAParts = SetupStage(tvP, stageValues[1], 1);

    if (numCParts == numAParts) {
        tvP->numStages += numCParts;
    } else if (numCParts > numAParts) {
        for (i = tvP->numStages + numAParts; i < tvP->numStages + numCParts; i++) {
            tvP->tevAlphaArg[i][3] = 0;
        }
        tvP->numStages += numCParts;
    } else {
        for (i = tvP->numStages + numCParts; i < tvP->numStages + numAParts; i++) {
            tvP->tevColorArg[i][3] = 0;
        }
        tvP->numStages += numAParts;
    }
}

CombineModeTev* BuildCombineModeTev(u32 color1, u32 alpha1, u32 color2, u32 alpha2, u32 numCycles) {
    u8 stageValues[2][2][4];
    s32 i;
    s32 j;
    u8* tempPtr;
    s32 pad[2];

    memset(&tevStages, 0, sizeof(CombineModeTev));

    for (i = 0; i < 8; i++) {
        tevStages.tevOrder[i].coordID = GX_TEXCOORD_NULL;
        tevStages.tevOrder[i].mapID = GX_TEXMAP_NULL;
        tevStages.tevOrder[i].chanID = GX_COLOR_NULL;
        xlHeapCopy(tevStages.tevColorArg[i], sUsualCArgs, sizeof(sUsualCArgs));
        xlHeapCopy(tevStages.tevAlphaArg[i], sUsualAArgs, sizeof(sUsualAArgs));
    }

    tevStages.numCycles = numCycles;
    tevStages.ccCodes[0][0] = color1;
    tevStages.ccCodes[0][1] = alpha1;
    SetColor(stageValues[0][0], color1, 1);
    SetAlpha(stageValues[0][1], alpha1, 1, color1, color2, alpha2);

    if (numCycles == 2) {
        tevStages.ccCodes[1][0] = color2;
        tevStages.ccCodes[1][1] = alpha2;
        SetColor(stageValues[1][0], color2, 2);
        SetAlpha(stageValues[1][1], alpha2, 2, color1, color2, alpha2);
    }

    for (i = 0; i < numCycles; i++) {
        for (j = 0; j < 4; j++) {
            if (stageValues[i][0][j] == 3) {
                tevStages.flags |= 2;
            } else if (stageValues[i][0][j] == 10) {
                tevStages.flags |= 2;
            } else if (stageValues[i][0][j] == 5) {
                tevStages.flags |= 1;
            } else if (stageValues[i][0][j] == 12) {
                tevStages.flags |= 1;
            } else if (stageValues[i][0][j] == 14) {
                tevStages.flags |= 4;
            } else if (stageValues[i][0][j] == 4) {
                tevStages.flags |= 0x400;
            }
        }
        for (j = 0; j < 4; j++) {
            if (stageValues[i][1][j] == 3) {
                tevStages.flags |= 2;
            } else if (stageValues[i][1][j] == 5) {
                tevStages.flags |= 1;
            } else if (stageValues[i][1][j] == 9) {
                tevStages.flags |= 4;
            } else if (stageValues[i][1][j] == 4) {
                tevStages.flags |= 0x400;
            }
        }
    }

    BuildCycle(&tevStages, stageValues[0]);
    if (numCycles == 2) {
        BuildCycle(&tevStages, stageValues[1]);
    }

    for (i = 0; i < tevStages.numStages; i++) {
        if (tevStages.tevOrder[i].chanID != GX_COLOR_NULL) {
            tevStages.numChan = 1;
        }

        if (tevStages.tevOrder[i].coordID != GX_TEXCOORD_NULL) {
            if (tevStages.tevOrder[i].coordID == GX_TEXCOORD0) {
                tevStages.numTexGen |= 1;
            } else {
                tevStages.numTexGen |= 2;
            }
        }
    }

    if (tevStages.numTexGen == 3) {
        tevStages.numTexGen = 2;
    } else if (tevStages.numTexGen != 0) {
        tevStages.numTexGen = 1;
    }

    return &tevStages;
}
