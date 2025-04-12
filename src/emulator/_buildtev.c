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

// special ``memset`` function?
inline void BuildTevMemset(void* ptr, int value, size_t num) {
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

static s32 AddAlphaTevOrder(CombineModeTev* tvP, s32 foundTypes, s32 curStage) {
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

static inline void AddColorTevOrder(CombineModeTev* tvP, s32 foundTypes, s32 curStage) {
    if (foundTypes & 3) {
        if (foundTypes & 1) {
            tvP->tevOrder[curStage].coordID = GX_TEXCOORD0;
            tvP->tevOrder[curStage].mapID = GX_TEXMAP0;
        } else {
            tvP->tevOrder[curStage].coordID = GX_TEXCOORD1;
            tvP->tevOrder[curStage].mapID = GX_TEXMAP1;
        }
    }

    if (foundTypes & 0x400) {
        tvP->tevOrder[curStage].chanID = GX_COLOR0A0;
    }
}

s32 SetupStage(CombineModeTev* tvP, u8* stageValues, s32 type) {
    static s32 zeroType[2] = {15, 7};
    static s32 texelType[2][4] = {{1, 2, 8, 9}, {1, 2, 4, 2}};
    static s32 lightType[2][2] = {{4, 11}, {4, 4}};
    s32 zero = zeroType[type];
    s32 curStage = tvP->numStages;
    s32 textureFoundPos = 0;
    s32 numFound[2] = {0};
    s32 retStages = 1;
    s32 ret;
    int i;
    s32 num;
    int j;
    s32 foundTypes;
    int texelNum;
    int temp_r3;
    s32 pad;

    num = texelType[1][type + 2];
    foundTypes = 0;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < num; i++) {
            if (texelType[type][i] == stageValues[j]) {
                texelNum = i & 1;
                foundTypes |= 1 << texelNum;
                textureFoundPos |= 1 << (j + (texelNum << 2));
                numFound[texelNum]++;
            }
        }

        for (i = 0; i < 2; i++) {
            if (lightType[type][i] == stageValues[j]) {
                foundTypes |= 0x400;
                textureFoundPos |= 1 << (j + 8);
            }
        }
    }

    if (stageValues[0] == zero && stageValues[1] == zero && stageValues[2] == zero) {
        tvP->tevColorOpP[curStage][type] = sUsualOps[0];
        if (type == 0) {
            tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[3]];
            AddColorTevOrder(tvP, foundTypes, curStage);
        } else {
            ret = AddAlphaTevOrder(tvP, foundTypes, curStage);
            curStage += ret;
            retStages += ret;
            tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[3]];
        }
    } else if (stageValues[1] == zero && stageValues[3] == zero) {
        tvP->tevColorOpP[curStage][type] = sUsualOps[0];
        if ((foundTypes & 3) == 3) {
            if (type == 0) {
                s32 mask = 1;
                if (textureFoundPos & 0x10) {
                    mask = 2;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[0]];
                curStage++;
                retStages++;
                mask = ~mask;
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevColorArg[curStage][2] = GX_CC_CPREV;
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[2]];
            } else if (tvP->tevOrder[curStage].coordID == GX_TEXCOORD_NULL) {
                s32 mask = 1;
                if (textureFoundPos & 0x10) {
                    mask = 2;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[0]];
                curStage++;
                retStages++;
                mask = ~mask;
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevAlphaArg[curStage][2] = GX_CA_APREV;
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[2]];
            } else if (tvP->tevOrder[curStage].coordID == GX_TEXCOORD0) {
                s32 index1 = 0;
                s32 index2 = 2;
                if (textureFoundPos & 0x10) {
                    index1 = 2;
                    index2 = 0;
                }
                tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[index1]];
                retStages++;
                curStage++;
                if (tvP->tevOrder[curStage].coordID == GX_TEXCOORD0) {
                    OSReport("TEXCOORD0 twice -> should NOT happen!\n");
                }
                tvP->tevOrder[curStage].coordID = GX_TEXCOORD1;
                tvP->tevOrder[curStage].mapID = GX_TEXMAP1;
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevAlphaArg[curStage][2] = GX_CA_APREV;
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[index2]];
            } else {
                s32 index1 = 0;
                s32 index2 = 2;
                tvP->tevOrder[curStage].coordID = GX_TEXCOORD1;
                tvP->tevOrder[curStage].mapID = GX_TEXMAP1;
                if (textureFoundPos & 1) {
                    index1 = 2;
                    index2 = 0;
                }
                tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[index1]];
                curStage++;
                retStages++;
                if (tvP->tevOrder[curStage].coordID == GX_TEXCOORD1) {
                    OSReport("TEXCOORD1 twice -> should NOT happen!\n");
                }
                tvP->tevOrder[curStage].coordID = GX_TEXCOORD0;
                tvP->tevOrder[curStage].mapID = GX_TEXMAP0;
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevAlphaArg[curStage][2] = GX_CA_APREV;
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[index2]];
            }
        } else if (type == 0) {
            tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
            tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
            AddColorTevOrder(tvP, foundTypes, curStage);
        } else {
            ret = AddAlphaTevOrder(tvP, foundTypes, curStage);
            curStage += ret;
            retStages += ret;
            tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
            tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
        }
    } else if (stageValues[1] == stageValues[3]) {
        tvP->tevColorOpP[curStage][type] = sUsualOps[0];
        if ((foundTypes & 3) == 3) {
            if (type == 0) {
                s32 flag = 0;

                tvP->tevOrder[curStage].coordID = GX_TEXCOORD0;
                tvP->tevOrder[curStage].mapID = GX_TEXMAP0;

                for (i = 0; i < 4; i++) {
                    if (stageValues[i] == 1) {
                        flag |= 1;
                        tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[i]];
                        stageValues[i] = 0;
                    } else if (stageValues[i] == 8) {
                        flag |= 2;
                        tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[i]];
                        stageValues[i] = 7;
                    }
                }

                if (flag == 3) {
                    OSReport("NOO!!");
                }

                tvP->tevColorArg[curStage][3] = GX_CC_TEXC;
                curStage++;
                retStages++;
                AddColorTevOrder(tvP, (foundTypes & ~3) | 2, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevColorArg[curStage][0] = gColorArgs[stageValues[1]];
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
            } else if (tvP->tevOrder[curStage].coordID == GX_TEXCOORD1) {
                tvP->tevAlphaArg[curStage][3] = GX_CA_TEXA;
                for (i = 0; i < 4; i++) {
                    if (stageValues[i] == 2) {
                        stageValues[i] = 8;
                    }
                }
                curStage++;
                retStages++;
                ret = AddAlphaTevOrder(tvP, foundTypes & ~2, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevAlphaArg[curStage][0] = gAlphaArgs[stageValues[1]];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
            } else {
                tvP->tevOrder[curStage].coordID = GX_TEXCOORD0;
                tvP->tevOrder[curStage].mapID = GX_TEXMAP0;
                tvP->tevAlphaArg[curStage][3] = GX_CA_TEXA;
                for (i = 0; i < 4; i++) {
                    if (stageValues[i] == 1) {
                        stageValues[i] = 8;
                    }
                }
                curStage++;
                retStages++;
                ret = AddAlphaTevOrder(tvP, foundTypes & ~1, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevAlphaArg[curStage][0] = gAlphaArgs[stageValues[1]];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
            }
        } else if (type == 0) {
            tvP->tevColorArg[curStage][0] = gColorArgs[stageValues[1]];
            tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
            tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
            AddColorTevOrder(tvP, foundTypes, curStage);
        } else {
            ret = AddAlphaTevOrder(tvP, foundTypes, curStage);
            curStage += ret;
            retStages += ret;
            tvP->tevAlphaArg[curStage][0] = gAlphaArgs[stageValues[1]];
            tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
            tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
        }
    } else {
        s32 mask = 0xFFFF;
        if ((foundTypes & 3) == 0) {
            if (type == 0) {
                if (textureFoundPos & 0xD00) {
                    tvP->tevOrder[curStage].chanID = GX_COLOR0A0;
                }
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[3]];
                curStage++;
                retStages++;
                if (textureFoundPos & 0x200) {
                    tvP->tevOrder[curStage].chanID = GX_COLOR0A0;
                }
                tvP->tevColorOpP[curStage][type] = sUsualOps[2];
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[1]];
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
            } else {
                if (textureFoundPos & 0xD00) {
                    tvP->tevOrder[curStage].chanID = GX_COLOR0A0;
                }
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[3]];
                curStage++;
                retStages++;
                if (textureFoundPos & 0x200) {
                    tvP->tevOrder[curStage].chanID = GX_COLOR0A0;
                }
                tvP->tevColorOpP[curStage][type] = sUsualOps[2];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[1]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
            }
        } else if ((foundTypes & 3) != 3) {
            temp_r3 = 10 << ((foundTypes & 2) << 1);
            if ((textureFoundPos & temp_r3) == temp_r3) {
                if (type == 0) {
                    if (!(textureFoundPos & 0xE00)) {
                        mask ^= 0x400;
                    }
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[1];
                    tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                    tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[3]];
                    mask = 0xFFFF;
                    if (!(textureFoundPos & 0x55)) {
                        mask ^= 3;
                    }
                    curStage++;
                    retStages++;
                    if (!(textureFoundPos & 0x500)) {
                        mask ^= 0x400;
                    }
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[3];
                    tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                    tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
                } else {
                    if (!(textureFoundPos & 0x400)) {
                        mask ^= 0x400;
                    }
                    ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                    curStage += ret;
                    retStages += ret;
                    tvP->tevColorOpP[curStage][type] = sUsualOps[1];
                    tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                    tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[3]];
                    mask = 0xFFFF;
                    if (!(textureFoundPos & 0x55)) {
                        mask ^= 3;
                    }
                    curStage++;
                    retStages++;
                    if (!(textureFoundPos & 0x500)) {
                        mask ^= 0x400;
                    }
                    ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                    curStage += ret;
                    retStages += ret;
                    tvP->tevColorOpP[curStage][type] = sUsualOps[3];
                    tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                    tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
                }
            } else if (type == 0) {
                if (!(textureFoundPos & 0xD00)) {
                    mask ^= 0x400;
                }
                if (!(textureFoundPos & 0xDD)) {
                    mask ^= 3;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[3]];
                mask = 0xFFFF;
                if (!(textureFoundPos & 0x66)) {
                    mask ^= 3;
                }
                curStage++;
                retStages++;
                if (!(textureFoundPos & 0x600)) {
                    mask ^= 0x400;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[2];
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[1]];
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
            } else {
                if (!(textureFoundPos & 0xD00)) {
                    mask ^= 0x400;
                }
                if (!(textureFoundPos & 0xDD)) {
                    mask ^= 3;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[3]];
                mask = 0xFFFF;
                if (!(textureFoundPos & 0x66)) {
                    mask ^= 3;
                }
                curStage++;
                retStages++;
                if (!(textureFoundPos & 0x600)) {
                    mask ^= 0x400;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[2];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[1]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
            }
        } else if (!(textureFoundPos & 0x44)) {
            if (!(textureFoundPos & 0x22) || ((textureFoundPos & 0xA) == 0xA) || ((textureFoundPos & 0xA0) == 0xA0)) {
                if (type == 0) {
                    if (!(textureFoundPos & 0xE00)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x80) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[1];
                    tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[1]];
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                    tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[3]];
                    curStage++;
                    retStages++;
                    mask = 0xFFFF;
                    if (!(textureFoundPos & 0x500)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x50) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[3];
                    tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                    tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
                } else {
                    if (!(textureFoundPos & 0xE00)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x80) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                    curStage += ret;
                    retStages += ret;
                    tvP->tevColorOpP[curStage][type] = sUsualOps[1];
                    tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[1]];
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                    tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[3]];
                    mask = 0xFFFF;
                    curStage++;
                    retStages++;
                    if (!(textureFoundPos & 0x500)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x50) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                    curStage += ret;
                    retStages += ret;
                    tvP->tevColorOpP[curStage][type] = sUsualOps[3];
                    tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                    tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
                }
            } else if (!(textureFoundPos & 0x11) || !(textureFoundPos & 0x88) || ((textureFoundPos & 0x90) == 0x90) ||
                       ((textureFoundPos & 9) == 9)) {
                if (type == 0) {
                    if (!(textureFoundPos & 0xD00)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x90) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                    tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                    tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[3]];
                    mask = 0xFFFF;
                    if (textureFoundPos & 0x20) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    curStage++;
                    retStages++;
                    if (!(textureFoundPos & 0x600)) {
                        mask ^= 0x400;
                    }
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[2];
                    tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[1]];
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                    tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
                } else {
                    if (!(textureFoundPos & 0xD00)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x90) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                    curStage += ret;
                    retStages += ret;
                    tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                    tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                    tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[3]];
                    mask = 0xFFFF;
                    if (textureFoundPos & 0x20) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    curStage++;
                    retStages++;
                    if (!(textureFoundPos & 0x600)) {
                        mask ^= 0x400;
                    }
                    ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                    curStage += ret;
                    retStages += ret;
                    tvP->tevColorOpP[curStage][type] = sUsualOps[2];
                    tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[1]];
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                    tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
                }
            } else if (((textureFoundPos & 0x30) == 0x30) || ((textureFoundPos & 3) == 3)) {
                if (type == 0) {
                    if (!(textureFoundPos & 0x500)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x10) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                    tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                    mask |= 0x400;
                    if (!(textureFoundPos & 0x600)) {
                        mask ^= 0x400;
                    }
                    curStage++;
                    retStages++;
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[1];
                    tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[1]];
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                    tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
                    mask = 0xFFFF;
                    if (!(textureFoundPos & 0x800)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x80) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    curStage++;
                    retStages++;
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[3];
                    tvP->tevColorArg[curStage][1] = GX_CC_ONE;
                    tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[3]];
                    tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
                } else {
                    if (!(textureFoundPos & 0x500)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x10) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                    curStage += ret;
                    retStages += ret;
                    tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                    tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                    mask |= 0x400;
                    if (!(textureFoundPos & 0x600)) {
                        mask ^= 0x400;
                    }
                    curStage++;
                    retStages++;
                    ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                    curStage += ret;
                    retStages += ret;
                    tvP->tevColorOpP[curStage][type] = sUsualOps[1];
                    tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[1]];
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                    tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
                    mask = 0xFFFF;
                    if (!(textureFoundPos & 0x800)) {
                        mask ^= 0x400;
                    }
                    if (textureFoundPos & 0x80) {
                        mask ^= 1;
                    } else {
                        mask ^= 2;
                    }
                    curStage++;
                    retStages++;
                    AddColorTevOrder(tvP, foundTypes & mask, curStage);
                    tvP->tevColorOpP[curStage][type] = sUsualOps[3];
                    tvP->tevAlphaArg[curStage][1] = GX_CA_KONST;
                    tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[3]];
                    tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
                }
            } else {
                OSReport("BAD MODE in two-texture, no C texture\n");
            }
        } else if (!(textureFoundPos & 0xE) || !(textureFoundPos & 0xE0)) {
            if (type == 0) {
                if (textureFoundPos & 0x10) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[0]];
                mask = 0xFFFF;
                curStage++;
                retStages++;
                if (!(textureFoundPos & 0xD00)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0xC0) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[3];
                tvP->tevColorArg[curStage][1] = GX_CC_CPREV;
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                tvP->tevColorArg[curStage][3] = gColorArgs[stageValues[3]];
                mask = 0xFFFF;
                curStage++;
                retStages++;
                if (!(textureFoundPos & 0x600)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0x60) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[1];
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[1]];
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
            } else {
                if (textureFoundPos & 0x10) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[0]];
                curStage++;
                retStages++;
                mask = 0xFFFF;
                if (!(textureFoundPos & 0xD00)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0xC0) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[3];
                tvP->tevAlphaArg[curStage][1] = GX_CA_APREV;
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                tvP->tevAlphaArg[curStage][3] = gAlphaArgs[stageValues[3]];
                curStage++;
                retStages++;
                mask = 0xFFFF;
                if (!(textureFoundPos & 0x600)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0x60) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[1];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[1]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
            }
        } else if (!(textureFoundPos & 0x33) || ((textureFoundPos & 0x40) && !(textureFoundPos & 3)) ||
                   ((textureFoundPos & 4) && !(textureFoundPos & 0x30))) {
            if (type == 0) {
                if (!(textureFoundPos & 0x300)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0x30) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[0]];
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                curStage++;
                retStages++;
                mask = 0xFFFF;
                if (!(textureFoundPos & 0x600)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0x60) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[2];
                tvP->tevColorArg[curStage][1] = gColorArgs[stageValues[1]];
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[2]];
                tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
                curStage++;
                retStages++;
                mask = 0xFFFF;
                if (!(textureFoundPos & 0x800)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0x80) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                AddColorTevOrder(tvP, foundTypes & mask, curStage);
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevColorArg[curStage][1] = GX_CC_ONE;
                tvP->tevColorArg[curStage][2] = gColorArgs[stageValues[3]];
                tvP->tevColorArg[curStage][3] = GX_CC_CPREV;
            } else {
                if (!(textureFoundPos & 0x300)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0x30) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[0]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                curStage++;
                retStages++;
                mask = 0xFFFF;
                if (!(textureFoundPos & 0x600)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0x60) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[2];
                tvP->tevAlphaArg[curStage][1] = gAlphaArgs[stageValues[1]];
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[2]];
                tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
                mask = 0xFFFF;
                curStage++;
                retStages++;
                if (!(textureFoundPos & 0x800)) {
                    mask ^= 0x400;
                }
                if (textureFoundPos & 0x80) {
                    mask ^= 1;
                } else {
                    mask ^= 2;
                }
                ret = AddAlphaTevOrder(tvP, foundTypes & mask, curStage);
                curStage += ret;
                retStages += ret;
                tvP->tevColorOpP[curStage][type] = sUsualOps[0];
                tvP->tevAlphaArg[curStage][1] = GX_CA_KONST;
                tvP->tevAlphaArg[curStage][2] = gAlphaArgs[stageValues[3]];
                tvP->tevAlphaArg[curStage][3] = GX_CA_APREV;
            }
        } else {
            OSReport("case of multi-texture, with C value being a texture -> NOT HANDLED!\n");
        }
    }

    return retStages;
}

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
    static CombineModeTev tevStages;
    u8 stageValues[2][2][4];
    s32 i;
    s32 j;
    u8* tempPtr;
    s32 pad[2];

    BuildTevMemset(&tevStages, 0, sizeof(CombineModeTev));

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
