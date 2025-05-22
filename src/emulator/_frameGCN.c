#include "dolphin.h"
#include "emulator/cpu.h"
#include "emulator/frame.h"
#include "emulator/ram.h"
#include "emulator/rdp.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/snddvdtrk.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "math.h"

static bool frameDrawTriangle_C0T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C1T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C3T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C0T3(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C1T3(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C3T3(Frame* pFrame, Primitive* pPrimitive);

static bool frameDrawLine_C0T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C1T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C2T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C0T2(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C1T2(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C2T2(Frame* pFrame, Primitive* pPrimitive);

static void CopyCFB(u16* srcP);
static bool packTakeBlocks(s32* piPack, u32* anPack, s32 nPackCount, s32 nBlockCount);
static bool packFreeBlocks(s32* piPack, u32* anPack, s32 nPackCount);
static inline bool frameTransposeMatrix(Mtx44 matrixTarget, Mtx44 matrixSource);
static bool frameLoadTile(Frame* pFrame, FrameTexture** ppTexture, s32 iTileCode);
static bool frameUpdateCache(Frame* pFrame);

static bool gbFrameValid;
static bool gbFrameBegin;
static bool snScissorChanged;
static u32 snScissorXOrig;
static u32 snScissorYOrig;
static u32 snScissorWidth;
static u32 snScissorHeight;

static volatile bool sCopyFrameSyncReceived;

static u8 sSpecialZeldaHackON;
static u32 sDestinationBuffer;
static u32 sSrcBuffer;
static u32 sConstantBufAddr[6] ATTRIBUTE_ALIGN(32);
static u32 sNumAddr;
static u32 gHackCreditsColor;

bool gNoSwapBuffer = false;

static s32 gnCountMapHack;

#if VERSION == MM_J
#define CAMERA_BUFFER_SIZE (ZELDA2_CAMERA_WIDTH * ZELDA2_CAMERA_HEIGHT)
#else
#define CAMERA_BUFFER_SIZE (ZELDA2_CAMERA_WIDTH * ZELDA2_CAMERA_HEIGHT * sizeof(u16))
#endif

#if IS_MM
GXProjectionType gRealProjectionType;
f32 gNearVal;
f32 gFarVal;

Mtx44 gRealProjectionMtx;
Mtx gTextureMatrix[8];
FrameTexture* gpTexture[8];
#endif

static inline bool frameSetProjection(Frame* pFrame, s32 iHint) {
    MatrixHint* pHint = &pFrame->aMatrixHint[iHint];

    pFrame->nMode |= 0x24000000;
    pFrame->nMode &= ~0x18000000;

    if (pHint->eProjection == FMP_PERSPECTIVE) {
        C_MTXPerspective(pFrame->matrixProjection, pHint->rFieldOfViewY, pHint->rAspect, pHint->rClipNear,
                         pHint->rClipFar);
    } else if (pHint->eProjection == FMP_ORTHOGRAPHIC) {
        C_MTXOrtho(pFrame->matrixProjection, 0.0f, pFrame->anSizeY[FS_SOURCE] - 1.0f, 0.0f,
                   pFrame->anSizeX[FS_SOURCE] - 1.0f, pHint->rClipNear, pHint->rClipFar);
    } else {
        return false;
    }

    pFrame->eTypeProjection = pHint->eProjection;
    return true;
}

#if IS_MM
static bool frameDrawSetupFog_MarioKart(Frame* pFrame) {
    GXFogType nFogType;
    f32 rNear;
    f32 rFar;
    u32 nMode;
    u32 iHint;
    f32 rFogNear;
    f32 rFogFar;
    f32 rFogMin;
    f32 rFogMax;
    f32 rMultiplier;
    f32 dplane;
    s32 pad[4];

    rMultiplier = (s16)(pFrame->aMode[0] >> 16);
    iHint = pFrame->iHintProjection;

    if (iHint != -1) {
        rFar = pFrame->aMatrixHint[pFrame->iHintProjection].rClipFar;
        rNear = 0.1f * pFrame->aMatrixHint[pFrame->iHintProjection].rClipNear;
    } else {
        rFar = 32000.0f;
        rNear = 1.0f;
    }

    if (rMultiplier == 0.0f) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
    } else {
        f32 dplane = rFar - rNear;

        nFogType = GX_FOG_LIN;
        rFogNear = rNear;
        rFogFar = rFar;
        rFogMin = 0.15f * dplane + rNear;
        rFogMax = 0.6f * dplane + rNear;

        nMode = pFrame->aMode[4];
        if (((nMode >> 26) & 3) == 1 || (nMode >> 30) == 3 || ((nMode >> 22) & 3) == 3) {
            GXSetFog(nFogType, rFogMin, rFogMax, rFogNear, rFogFar, pFrame->aColor[0]);
        } else {
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
        }
    }

    return true;
}

static bool frameDrawSetupFog_StarFox(Frame* pFrame) {
    GXFogType nFogType;
    f32 rNear;
    f32 rFar;
    u32 nMode;
    u32 iHint;
    f32 rFogNear;
    f32 rFogFar;
    f32 rFogMin;
    f32 rFogMax;
    f32 rMultiplier;
    s32 pad[4];

    rMultiplier = (s16)(pFrame->aMode[0] >> 16);
    iHint = pFrame->iHintProjection;

    if (iHint != -1) {
        rFar = pFrame->aMatrixHint[pFrame->iHintProjection].rClipFar;
        rNear = 0.1f * pFrame->aMatrixHint[pFrame->iHintProjection].rClipNear;
    } else {
        rFar = 32000.0f;
        rNear = 1.0f;
    }

    if (rMultiplier == 0.0f) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
    } else {
        f32 dplane = rFar - rNear;

        nFogType = GX_FOG_LIN;
        rFogNear = rNear;
        rFogFar = rFar;
        rFogMin = 0.1f * dplane + rNear;
        rFogMax = 0.85f * dplane + rNear;

        nMode = pFrame->aMode[4];
        if (((nMode >> 26) & 3) == 1 || (nMode >> 30) == 3 || ((nMode >> 22) & 3) == 3) {
            GXSetFog(nFogType, rFogMin, rFogMax, rFogNear, rFogFar, pFrame->aColor[0]);
        } else {
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
        }
    }

    return true;
}
#endif

// non-matching for MM
static bool frameDrawSetupFog_Zelda1(Frame* pFrame) {
    GXFogType nFogType;
    f32 rNear;
    f32 rFar;
    u32 nMode;
    u32 iHint;
    f32 rFogNear;
    f32 rFogFar;
    f32 rFogMin;
    f32 rFogMax;
    f32 rMultiplier;
    f32 rOffset;
    f32 rMinimum;
    f32 rMaximum;
    s32 pad[4];

    nMode = pFrame->aMode[0];
    iHint = pFrame->iHintProjection;
    rMultiplier = (s16)(nMode >> 16);
    rOffset = rMinimum = (s16)(nMode & 0xFFFF);

    if (iHint != -1) {
        rFar = pFrame->aMatrixHint[pFrame->iHintProjection].rClipFar;
        rNear = 0.1f * pFrame->aMatrixHint[pFrame->iHintProjection].rClipNear;
    } else {
        rFar = 32000.0f;
        rNear = 1.0f;
    }

    if (rMultiplier == 0.0f) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
    } else {
        if (rOffset == rMultiplier) {
            nFogType = GX_FOG_LIN;
            rFogNear = 500.0f;
            rFogFar = 1000.0f;
            rFogMin = rFogNear * (1.0f - (rOffset / rMultiplier));
            rFogMax = (128000.0f / rMultiplier) + rFogMin;
        } else if (rOffset == -25344.0f && rMultiplier == 25600.0f && rFar == 2200.0f) {
            f32 dplane = rFar - rNear;

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = 0.575f * dplane + rNear;
            rFogMax = 0.75f * dplane + rNear;
        } else if (rOffset == -21077.0f && rMultiplier == 21333.0f && rFar == 12800.0f) {
            f32 dplane = rFar - rNear;

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = 0.1f * dplane + rNear;
            rFogMax = dplane + rNear;
        } else if (gpSystem->eTypeROM == SRT_ZELDA2 && rOffset == -90.0f && rMultiplier == 258.0f && rFar == 12800.0f) {
            f32 dplane = rFar - rNear;

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = 0.45f * dplane + rNear;
            rFogMax = dplane + rNear;
        } else if (gpSystem->eTypeROM == SRT_ZELDA2 && rOffset == -667.0f && rMultiplier == 688.0f &&
                   rFar == 12800.0f) {
            f32 dplane = rFar - rNear;

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = 0.45f * dplane + rNear;
            rFogMax = dplane + rNear;
#if IS_MM
        } else if (gpSystem->eTypeROM == SRT_ZELDA2 && rFar == 12800.0f) {
            f32 dminmax;
            f32 rDMinMax;
            f32 val1;
            f32 dplane;
            f32 rNearScale;

            dplane = rFar - rNear;

            nFogType = GX_FOG_LIN;
            rMultiplier = 128000.0f / rMultiplier;
            rFogNear = gNearVal = rNear;
            rFogFar = gFarVal = rFar;
            rNearScale = -((rOffset * rMultiplier * 0.00390625f) - 500.0f);
            rDMinMax = rNearScale + rMultiplier;
            dminmax = rDMinMax - rNearScale;

            if (gRealProjectionType == GX_PERSPECTIVE) {
                rMinimum = -gRealProjectionMtx[4][3] / (((rNearScale - 1000.0f) / 1064.0f) + gRealProjectionMtx[4][2]);
            } else {
                rMinimum = (((rNearScale - 1000.0f) / 1064.0f) - gRealProjectionMtx[4][3]) / gRealProjectionMtx[4][2];
            }

            rOffset = dminmax / 1000.0f;
            val1 = rOffset;

            if (rOffset > 0.19f) {
                val1 = 0.19f;
            } else if (val1 < 0.15f) {
                val1 = 0.15f;
            }

            rNearScale = -((dminmax * val1) - rDMinMax);
            if (rNearScale > 1000.0f) {
                rNearScale = 1000.0f;
            }

            if (gRealProjectionType == GX_PERSPECTIVE) {
                rMaximum = -gRealProjectionMtx[4][3] / (((rNearScale - 1000.0f) / 1064.0f) + gRealProjectionMtx[4][2]);
            } else {
                rMaximum = (((rNearScale - 1000.0f) / 1064.0f) - gRealProjectionMtx[4][3]) / gRealProjectionMtx[4][2];
            }

            rFogMin = (((-rMinimum - rNear) / dplane) * dplane) + rNear;
            rFogMax = (((-rMaximum - rNear) / dplane) * dplane) + rNear;
#endif
        } else {
            f32 dplane = rFar - rNear;
            f32 rFarScale;
            f32 rNearScale;

            rMultiplier = 128000.0f / rMultiplier;
            rMultiplier = rOffset * rMultiplier;
            rFogFar = 1.0f / 256.0f;
            rFogNear = 500.0f - rMultiplier * rFogFar;

            if (rFogNear <= 860.0f) {
                rMinimum = 0.0f;
                rMaximum = 0.15f;
            } else {
                rMinimum = (rFogNear - 860.0f) / 140.0f;
                rMaximum = 0.72f * rMinimum * rMinimum * rMinimum * rMinimum + 0.28f;
                rMinimum = 0.26f * rMinimum * rMinimum * rMinimum * rMinimum;
            }

            rFarScale = rFar / 12800.0f;
            rFarScale = 1.0f - rFarScale;
            rFarScale = rFarScale * rFarScale;
            rFarScale = rFarScale * rFarScale;
            rFarScale = rFarScale * rFarScale;

            rNearScale = rNear * rNear;
            rNearScale *= 0.1f * rFarScale;

            rFarScale *= 8.44f;
            rNearScale *= 8.44; // bug? should be 8.44f

            rFarScale += 1.0f;
            rNearScale += 1.0f;

            rMaximum *= rFarScale;
            if (rMaximum > 1.0f) {
                rMaximum = 1.0f;
            }

            rMinimum *= rNearScale;
            if (rMinimum > 1.0f) {
                rMinimum = 1.0f;
            }

            if (rMinimum > rMaximum) {
                rMinimum = rMaximum;
            }

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = rMinimum * dplane + rNear;
            rFogMax = rMaximum * dplane + rNear;
        }

        nMode = pFrame->aMode[4];
        if (((nMode >> 26) & 3) == 1 || (nMode >> 30) == 3 || ((nMode >> 22) & 3) == 3) {
            GXSetFog(nFogType, rFogMin, rFogMax, rFogNear, rFogFar, pFrame->aColor[0]);
        } else {
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
        }
    }

    return true;
}

static s32 frameDrawSetupFog_Default(Frame* pFrame) {
    s32 iHint;
    f32 rNear;
    f32 rFar;
    f32 rFOVY;
    Mtx44 matrixProjection;
    GXFogAdjTable fogTable;
    f32 rMax;
    f32 rMin;
    f32 rIntpV;
    f32 rMinimum;
    f32 rMultiplier;
    f32 rOffset;
    s32 pad;

    rMultiplier = (s16)(pFrame->aMode[0] >> 16);
    rOffset = (s16)(pFrame->aMode[0] & 0xFFFF);
    iHint = pFrame->iHintProjection;

    if (iHint != -1) {
        rFar = pFrame->aMatrixHint[pFrame->iHintProjection].rClipFar;
        rNear = pFrame->aMatrixHint[pFrame->iHintProjection].rClipNear;
        rFOVY = pFrame->aMatrixHint[pFrame->iHintProjection].rFieldOfViewY;
    } else {
        rFar = 32000.0f;
        rNear = 1.0f;
        rFOVY = 30.0f;
    }
    if (rMultiplier == 0.0f) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
    } else {
        rMinimum = 500.0f * (1.0f - rOffset / rMultiplier);
        C_MTXPerspective(matrixProjection, 30.0f, 4.0f / 3.0f, 0.1f * rNear, rFar);
        GXInitFogAdjTable(&fogTable, GC_FRAME_WIDTH, matrixProjection);
        GXSetFogRangeAdj(GX_TRUE, pFrame->viewport.rX + pFrame->viewport.rSizeX / 2.0f, &fogTable);
        if (rMinimum > 970.0f) {
            if (rFOVY > 59.0f || rMinimum > 990.0f) {
                rMin = 0.21f * (rFar - 0.35f * rNear);
                rMin = MAX(rMin, 0.35f * rNear);
                if (rFOVY < 59.0f && rFar >= 12800.0f) {
                    rMax = 0.6f * rFar;
                } else {
                    rMax = 0.7f * rFar;
                }
            } else if (rFOVY > 44.0f) {
                rMin = 0.13f * (rFar - 0.35f * rNear);
                rMin = MAX(rMin, 0.35f * rNear);
                rIntpV = MAX(rFOVY - 45.0f, 0.0f) / 15.0f;
                rMax = rFar * (0.6f * (1.0f - rIntpV) + 0.7f * rIntpV);
            } else {
                rMin = 0.1f * (rFar - 0.35f * rNear);
                rMin = MAX(rMin, 0.35f * rNear);
                rMax = 0.38f * rFar;
            }
            GXSetFog(GX_FOG_LIN, rMin, rMax, 0.35f * rNear, rFar, pFrame->aColor[0]);
        } else if (rMinimum > 900.0f) {
            GXSetFog(GX_FOG_LIN, 350.0f, 500.0f, 10.0f, 500.0f, pFrame->aColor[0]);
        } else {
            GXSetFog(GX_FOG_LIN, 10.0f, 200.0f, 10.0f, 200.0f, pFrame->aColor[0]);
        }
    }

    return true;
}

static void frameDrawSyncCallback(u16 nToken) {
    if (nToken == FRAME_SYNC_TOKEN) {
        sCopyFrameSyncReceived = true;
    }
}

static void frameDrawDone(void) {
    if (gbFrameValid) {
        gbFrameValid = false;
        if (!gNoSwapBuffer) {
            VISetNextFrameBuffer(DemoCurrentBuffer);
            VIFlush();
            if (DemoCurrentBuffer == DemoFrameBuffer1) {
                DemoCurrentBuffer = DemoFrameBuffer2;
            } else {
                DemoCurrentBuffer = DemoFrameBuffer1;
            }
        } else {
            VIFlush();
            gNoSwapBuffer = false;
        }
    }
}

static bool frameMakeTLUT(Frame* pFrame, FrameTexture* pTexture, s32 nCount, s32 nOffsetTMEM, bool bReload) {
    s32 iColor;
    u16* anColor;
    u16 nData16;

    if (bReload) {
        if (pTexture->iPackColor == -1) {
            return true;
        }
        anColor = (u16*)((u8*)pFrame->aColorData + ((pTexture->iPackColor & 0xFFFF) << 5));
    } else {
        if (!packTakeBlocks(&pTexture->iPackColor, pFrame->anPackColor, ARRAY_COUNT(pFrame->anPackColor),
                            (nCount * sizeof(u16)) >> 5)) {
            return false;
        }
        anColor = (u16*)((u8*)pFrame->aColorData + ((pTexture->iPackColor & 0xFFFF) << 5));
    }

    for (iColor = 0; iColor < nCount; iColor++) {
        nData16 = pFrame->TMEM.data.u64[nOffsetTMEM + 0x100 + iColor] & 0xFFFF;
        if (nData16 & 1) {
            anColor[iColor] =
                (((nData16 >> 11) & 0x1F) << 10) | (((nData16 >> 6) & 0x1F) << 5) | ((nData16 >> 1) & 0x1F) | 0x8000;
        } else {
            anColor[iColor] = (((nData16 >> 12) & 0xF) << 8) | (((nData16 >> 7) & 0xF) << 4) | ((nData16 >> 2) & 0xF);
        }
    }

    DCStoreRange(anColor, nCount * sizeof(u16));

    return true;
}

static inline bool frameFreeTLUT(Frame* pFrame, FrameTexture* pTexture) {
    if (!packFreeBlocks(&pTexture->iPackColor, pFrame->anPackColor, ARRAY_COUNT(pFrame->anPackColor))) {
        return false;
    }
    return true;
}

// See https://ultra64.ca/files/documentation/online-manuals/man/pro-man/pro13/index13.8.html
static bool frameMakePixels(Frame* pFrame, FrameTexture* pTexture, Tile* pTile, bool bReload) {
    void* aPixel;
    s32 nSizeLine;
    s32 nFlip;
    s32 nSize;
    s32 temp;
    s32 temp2;
    s32 pad;
    s32 nCount;
    s32 nMode;
    s32 nSizeX;
    s32 nSizeY;
    s32 nSource;
    s32 nTarget;
    s32 iPixelX;
    s32 iPixelY;
    s32 iTarget;
    u8 nData8;
    u16 nData16;
    u32 nData32;
    s32 nSizeTextureX;
    s32 nSizeTextureY;
    s32 lineX;
    s32 lineY;
    s32 linePixX;
    s32 lineStep;
    s32 tmemStart;
    s32 tmemEnd;
    s32 __nSizeX;
    s32 __nSizeY;
    u32 rgb[3];
    u32 yuv[3];
    bool var_r29;
    bool var_r14;

    if (bReload) {
        nSizeX = pTexture->nSizeX;
        nSizeY = pTexture->nSizeY;
    } else {
        nMode = 0;
        pTexture->nMode = 0x1000;
        pTexture->eWrapT = GX_MAX_TEXWRAPMODE;
        pTexture->eWrapS = GX_MAX_TEXWRAPMODE;

        if ((pTile->nModeS & G_TX_CLAMP) || pTile->nMaskS == 0) {
            nMode |= 1;
            nSizeX = (pTile->nX1 >> 2) - (pTile->nX0 >> 2) + 1;
            if (nSizeX < 0) {
                nSizeX = -nSizeX;
            }
        } else {
            nSizeX = 1 << pTile->nMaskS;
        }

        if ((pTile->nModeT & G_TX_CLAMP) || pTile->nMaskT == 0) {
            nMode |= 2;
            nSizeY = (pTile->nY1 >> 2) - (pTile->nY0 >> 2) + 1;
            if (nSizeY < 0) {
                nSizeY = -nSizeY;
            }
        } else {
            nSizeY = 1 << pTile->nMaskT;
        }

        if (nSizeX + nSizeY > 399) {
            __nSizeX = nSizeX;
            __nSizeY = nSizeY;

            if (nMode & 1) {
                nSizeX = 1 << pTile->nMaskS;
            } else {
                nSizeX = (pTile->nX1 >> 2) - (pTile->nX0 >> 2) + 1;
            }

            if (nSizeX <= 0 || nSizeX > 128) {
                nSizeX = __nSizeX;
            } else {
                pTexture->nMode |= 1;
            }

            if (nMode & 2) {
                nSizeY = 1 << pTile->nMaskT;
            } else {
                nSizeY = (pTile->nY1 >> 2) - (pTile->nY0 >> 2) + 1;
            }

            if (nSizeY <= 0 || nSizeY > 128) {
                nSizeY = __nSizeY;
            } else {
                pTexture->nMode |= 2;
            }
        }
    }

    if (pTile->nMaskS > 0) {
        lineX = 1 << pTile->nMaskS;
    } else {
        lineX = nSizeX + 1;
    }

    if (pTile->nMaskT > 0) {
        lineY = 1 << pTile->nMaskT;
    } else {
        lineY = nSizeY + 1;
    }

    if (pTile->nModeS & G_TX_WRAP) {
        var_r29 = true;
    } else {
        var_r29 = false;
    }

    if (pTile->nModeT & G_TX_WRAP) {
        var_r14 = true;
    } else {
        var_r14 = false;
    }

    if ((pTexture->nSizeX = nSizeX) <= 0 || (pTexture->nSizeY = nSizeY) <= 0) {
        pTexture->nSizeY = 0;
        pTexture->nSizeX = 0;
        return false;
    }

    if (pTile->nFormat == G_IM_FMT_RGBA && pTile->nSize == G_IM_SIZ_4b) {
        pTile->nFormat = G_IM_FMT_IA;
    }
    if (pTile->nFormat == G_IM_FMT_I && pTile->nSize == G_IM_SIZ_16b) {
        pTile->nFormat = G_IM_FMT_IA;
    }

    if (pTile->nFormat == G_IM_FMT_RGBA) {
        if (pTile->nSize == G_IM_SIZ_16b) {
            nCount = 2;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_RGB5A3;
                if ((pTexture->nSizeX & 3) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 3) & ~3;
                }
                if ((pTexture->nSizeY & 3) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 3) & ~3;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    ((pTexture->nSizeX * pTexture->nSizeY * 2) + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            tmemStart = nSource = pTile->nTMEM * 4;
            nSizeLine = pTile->nSizeX * 4;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 2) * (nSizeTextureX >> 2);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 1;
                while (iPixelX < nSizeTextureX) {
                    if (iPixelX < nSizeX) {
                        nData16 = pFrame->TMEM.data.u16[(nSource & 0x7FF) + (linePixX ^ nFlip)];
                        linePixX += lineStep;
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }
                    temp = (nTarget + (iPixelX >> 2)) * 16;
                    iTarget = (iPixelX & 3) + (iPixelY & 3) * 4 + temp;
                    if (nData16 & 1) {
                        ((u16*)aPixel)[iTarget] = (((nData16 >> 11) & 0x1F) << 10) | (((nData16 >> 6) & 0x1F) << 5) |
                                                  ((nData16 >> 1) & 0x1F) | 0x8000;
                    } else {
                        ((u16*)aPixel)[iTarget] =
                            (((nData16 >> 12) & 0xF) << 8) | (((nData16 >> 7) & 0xF) << 4) | ((nData16 >> 2) & 0xF);
                    }
                    iPixelX++;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 2;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 2;
                    }
                }
            }
        } else if (pTile->nSize == G_IM_SIZ_32b) {
            nCount = 4;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_RGBA8;
                if ((pTexture->nSizeX & 3) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 3) & ~3;
                }
                if ((pTexture->nSizeY & 3) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 3) & ~3;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    ((pTexture->nSizeX * pTexture->nSizeY * 4) + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            tmemStart = nSource = pTile->nTMEM * 4;
            nSizeLine = pTile->nSizeX * 4;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 2) * (nSizeTextureX >> 2);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 1;
                while (iPixelX < nSizeTextureX) {
                    if (iPixelX < nSizeX) {
                        nData32 = pFrame->TMEM.data.u32[(nSource & 0x3FF) + (linePixX ^ nFlip)];
                        linePixX += lineStep;
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }
                    temp = (nTarget + (iPixelX >> 2)) * 32;
                    iTarget = (iPixelX & 3) + (iPixelY & 3) * 4 + temp;
                    ((u16*)aPixel)[iTarget] = ((nData32 & 0xFF) << 8) | (nData32 >> 24);
                    ((u16*)aPixel)[iTarget + 16] = (((nData32 >> 16) & 0xFF) << 8) | ((nData32 >> 8) & 0xFF);
                    iPixelX += 1;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 2;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 2;
                    }
                }
            }
        } else {
            return false;
        }
    } else if (pTile->nFormat == G_IM_FMT_CI) {
        if (pTile->nSize == G_IM_SIZ_8b) {
            nCount = 1;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_C8;
                if ((pTexture->nSizeX & 7) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 7) & ~7;
                }
                if ((pTexture->nSizeY & 3) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 3) & ~3;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    (pTexture->nSizeX * pTexture->nSizeY + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            tmemStart = nSource = pTile->nTMEM * 8;
            nSizeLine = pTile->nSizeX * 8;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            if (!frameMakeTLUT(pFrame, pTexture, 0x100, 0, bReload)) {
                return false;
            }

            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 2) * (nSizeTextureX >> 3);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 1;
                while (iPixelX < nSizeTextureX) {
                    if (iPixelX < nSizeX) {
                        nData8 = pFrame->TMEM.data.u8[(nSource & 0xFFF) + (linePixX ^ nFlip)];
                        linePixX += lineStep;
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }
                    temp = (nTarget + (iPixelX >> 3)) * 32;
                    iTarget = (iPixelX & 7) + (iPixelY & 3) * 8 + temp;
                    ((u8*)aPixel)[iTarget] = nData8;
                    iPixelX += 1;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 4;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 4;
                    }
                }
            }
        } else if (pTile->nSize == G_IM_SIZ_4b) {
            nCount = 1;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_C4;
                if ((pTexture->nSizeX & 7) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 7) & ~7;
                }
                if ((pTexture->nSizeY & 7) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 7) & ~7;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    ((((pTexture->nSizeX + 1) >> 1) * pTexture->nSizeY) + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            nSizeLine = pTile->nSizeX * 8;
            tmemStart = nSource = pTile->nTMEM * 8;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            if (!frameMakeTLUT(pFrame, pTexture, 0x10, pTile->iTLUT * 0x10, bReload)) {
                return false;
            }

            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 3) * (nSizeTextureX >> 3);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 2;
                while (iPixelX < nSizeTextureX) {
                    if (iPixelX < nSizeX) {
                        nData8 = pFrame->TMEM.data.u8[(nSource & 0xFFF) + ((linePixX ^ nFlip) >> 1)];
                        linePixX += lineStep;
                        if (lineStep < 0) {
                            nData8 = (nData8 << 4) | (nData8 >> 4);
                        }
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }
                    temp = (nTarget + (iPixelX >> 3)) * 32;
                    iTarget = ((iPixelX >> 1) & 3) + (iPixelY & 7) * 4 + temp;
                    ((u8*)aPixel)[iTarget] = nData8;
                    iPixelX += 2;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 8;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 8;
                    }
                }
            }
        } else {
            return false;
        }
    } else if (pTile->nFormat == G_IM_FMT_IA) {
        if (pTile->nSize == G_IM_SIZ_16b) {
            nCount = 2;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_IA8;
                if ((pTexture->nSizeX & 3) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 3) & ~3;
                }
                if ((pTexture->nSizeY & 3) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 3) & ~3;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    ((pTexture->nSizeX * pTexture->nSizeY * 2) + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            nSizeLine = pTile->nSizeX * 4;
            nSource = pTile->nTMEM * 4;
            tmemStart = nSource = pTile->nTMEM * 4;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 2) * (nSizeTextureX >> 2);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 1;
                while (iPixelX < nSizeTextureX) {
                    if (iPixelX < nSizeX) {
                        nData16 = pFrame->TMEM.data.u16[(nSource & 0x7FF) + (linePixX ^ nFlip)];
                        linePixX += lineStep;
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }
                    temp = (nTarget + (iPixelX >> 2)) * 16;
                    iTarget = (iPixelX & 3) + (iPixelY & 3) * 4 + temp;
                    ((u16*)aPixel)[iTarget] = ((nData16 & 0xFF) << 8) | ((nData16 >> 8) & 0xFF);
                    iPixelX += 1;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 2;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 2;
                    }
                }
            }
        } else if (pTile->nSize == G_IM_SIZ_8b) {
            nCount = 1;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_IA4;
                if ((pTexture->nSizeX & 7) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 7) & ~7;
                }
                if ((pTexture->nSizeY & 3) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 3) & ~3;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    ((pTexture->nSizeX * pTexture->nSizeY) + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            tmemStart = nSource = pTile->nTMEM * 8;
            nSizeLine = pTile->nSizeX * 8;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 2) * (nSizeTextureX >> 3);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 1;
                while (iPixelX < nSizeTextureX) {
                    if (iPixelX < nSizeX) {
                        nData8 = pFrame->TMEM.data.u8[(nSource & 0xFFF) + (linePixX ^ nFlip)];
                        linePixX += lineStep;
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }
                    temp = (nTarget + (iPixelX >> 3)) * 32;
                    iTarget = (iPixelX & 7) + (iPixelY & 3) * 8 + temp;
                    ((u8*)aPixel)[iTarget] = ((nData8 & 0xF) << 4) | ((nData8 >> 4) & 0xF);
                    iPixelX += 1;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 4;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 4;
                    }
                }
            }
        } else if (pTile->nSize == G_IM_SIZ_4b) {
            nCount = 1;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_IA4;
                if ((pTexture->nSizeX & 7) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 7) & ~7;
                }
                if ((pTexture->nSizeY & 7) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 7) & ~7;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    ((pTexture->nSizeX * pTexture->nSizeY) + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            nSizeLine = pTile->nSizeX * 8;
            tmemStart = nSource = pTile->nTMEM * 8;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 2) * (nSizeTextureX >> 3);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 2;
                while (iPixelX < nSizeTextureX) {
                    static u8 sRemapI[] = {
                        0, 2, 4, 6, 8, 10, 12, 15,
                    };

                    if (iPixelX < nSizeX) {
                        nData8 = pFrame->TMEM.data.u8[(nSource & 0xFFF) + ((linePixX ^ nFlip) >> 1)];
                        if (lineStep < 0) {
                            nData8 = (nData8 >> 4) | (nData8 << 4);
                        }
                        linePixX += lineStep;
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }

                    temp = (nTarget + (iPixelX >> 3)) * 32;
                    iTarget = (iPixelX & 7) + (iPixelY & 3) * 8 + temp;
                    ((u8*)aPixel)[iTarget] = ((((nData8 >> 4) & 1) * 0xF) << 4) | sRemapI[(nData8 >> 5) & 7];
                    temp = (nTarget + ((iPixelX + 1) >> 3)) * 32;
                    iTarget = ((iPixelX + 1) & 7) + (iPixelY & 3) * 8 + temp;
                    ((u8*)aPixel)[iTarget] = ((((nData8 >> 0) & 1) * 0xF) << 4) | sRemapI[(nData8 >> 1) & 7];
                    iPixelX += 2;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 8;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 8;
                    }
                }
            }
        } else {
            return false;
        }
    } else if (pTile->nFormat == G_IM_FMT_I) {
        if (pTile->nSize == G_IM_SIZ_8b) {
            nCount = 1;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_I8;
                if ((pTexture->nSizeX & 7) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 7) & ~7;
                }
                if ((pTexture->nSizeY & 3) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 3) & ~3;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    ((pTexture->nSizeX * pTexture->nSizeY) + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            tmemStart = nSource = pTile->nTMEM * 8;
            nSizeLine = pTile->nSizeX * 8;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 2) * (nSizeTextureX >> 3);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 1;
                while (iPixelX < nSizeTextureX) {
                    if (iPixelX < nSizeX) {
                        nData8 = pFrame->TMEM.data.u8[(nSource & 0xFFF) + (linePixX ^ nFlip)];
                        linePixX += lineStep;
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }
                    temp = (nTarget + (iPixelX >> 3)) * 32;
                    iTarget = (iPixelX & 7) + (iPixelY & 3) * 8 + temp;
                    ((u8*)aPixel)[iTarget] = nData8;
                    iPixelX += 1;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 4;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 4;
                    }
                }
            }
        } else if (pTile->nSize == G_IM_SIZ_4b) {
            nCount = 1;
            if (bReload) {
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            } else {
                pTexture->eFormat = GX_TF_I4;
                if ((pTexture->nSizeX & 7) != 0) {
                    pTexture->nSizeX = (pTexture->nSizeX + 7) & ~7;
                }
                if ((pTexture->nSizeY & 7) != 0) {
                    pTexture->nSizeY = (pTexture->nSizeY + 7) & ~7;
                }
                if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                    ((((pTexture->nSizeX + 1) >> 1) * pTexture->nSizeY) + 0x7FF) / 0x800)) {
                    return false;
                }
                aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }

            nSizeLine = pTile->nSizeX * 8;
            tmemStart = nSource = pTile->nTMEM * 8;
            tmemEnd = tmemStart + (nSizeLine * lineY);
            iPixelY = nFlip = 0;
            nSizeTextureX = pTexture->nSizeX;
            nSizeTextureY = pTexture->nSizeY;
            while (iPixelY < nSizeTextureY) {
                nTarget = (iPixelY >> 3) * (nSizeTextureX >> 3);
                iPixelX = 0;
                linePixX = 0;
                lineStep = 2;
                while (iPixelX < nSizeTextureX) {
                    if (iPixelX < nSizeX) {
                        nData8 = pFrame->TMEM.data.u8[(nSource & 0xFFF) + ((linePixX ^ nFlip) >> 1)];
                        linePixX += lineStep;
                        if (lineStep < 0) {
                            nData8 = (nData8 >> 4) | (nData8 << 4);
                        }
                        if (linePixX >= lineX || linePixX < 0) {
                            if (var_r29) {
                                lineStep = -lineStep;
                                linePixX += lineStep;
                            } else {
                                linePixX = 0;
                            }
                        }
                    }
                    temp = (nTarget + (iPixelX >> 3)) * 32;
                    iTarget = ((iPixelX >> 1) & 3) + (iPixelY & 7) * 4 + temp;
                    ((u8*)aPixel)[iTarget] = nData8 & 0xFF;
                    iPixelX += 2;
                }
                iPixelY += 1;
                if (iPixelY < nSizeY) {
                    nSource += nSizeLine;
                    if (nSource >= tmemEnd || nSource < tmemStart) {
                        if (var_r14) {
                            nSizeLine = -nSizeLine;
                            nSource += nSizeLine;
                        } else {
                            if (nSource % 2 == tmemStart % 2) {
                                nFlip ^= 8;
                            }
                            nSource = tmemStart;
                        }
                    } else {
                        nFlip ^= 8;
                    }
                }
            }
        } else {
            return false;
        }
    } else if (pTile->nFormat == G_IM_FMT_YUV) {
        nCount = 2;
        if (bReload) {
            aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
        } else {
            pTexture->eFormat = GX_TF_RGB5A3;
            if ((pTexture->nSizeX & 3) != 0) {
                pTexture->nSizeX = (pTexture->nSizeX + 3) & ~3;
            }
            if ((pTexture->nSizeY & 3) != 0) {
                pTexture->nSizeY = (pTexture->nSizeY + 3) & ~3;
            }
            if (!packTakeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel),
                                ((pTexture->nSizeX * pTexture->nSizeY * 2) + 0x7FF) / 0x800)) {
                return false;
            }
            aPixel = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
        }

        nFlip = 0;
        iPixelY = 0;
        nSizeY >>= 1;
        tmemStart = pTile->nTMEM * 4;
        nSizeLine = pTile->nSizeX * 4;
        nSizeTextureX = pTexture->nSizeX;
        nSizeTextureY = pTexture->nSizeY;
        while (iPixelY < nSizeY) {
            // TODO: Uses of `termEnd`, `nSource`, and `temp2` are probably fake
            tmemEnd = (iPixelY & 3) * 4;
            nTarget = (iPixelY >> 2) * (nSizeTextureX >> 2);
            iPixelX = 0;
            while (iPixelX < nSizeX) {
                nSource = iPixelY * nSizeLine;
                nSource += tmemStart;
                temp2 = iPixelX ^ nFlip;
                nData16 = pFrame->TMEM.data.u16[temp2 + nSource];
                yuv[0] = nData16 & 0xFF;
                yuv[1] = (nData16 >> 8) & 0xFF;

                nData16 = pFrame->TMEM.data.u16[temp2 + nSource + 1];
                yuv[2] = (nData16 >> 8) & 0xFF;
                frameConvertYUVtoRGB(yuv, rgb);

                temp = (nTarget + (iPixelX >> 2)) * 16;
                iTarget = ((iPixelX & 3) + tmemEnd) + temp;
                ((u16*)aPixel)[iTarget] =
                    (((rgb[0] >> 1) & 0xF) << 8) | (((rgb[1] >> 1) & 0xF) << 4) | ((rgb[2] >> 1) & 0xF) | 0x7000;

                yuv[0] = nData16 & 0xFF;
                frameConvertYUVtoRGB(yuv, rgb);
                ((u16*)aPixel)[iTarget + 1] =
                    (((rgb[0] >> 1) & 0xF) << 8) | (((rgb[1] >> 1) & 0xF) << 4) | ((rgb[2] >> 1) & 0xF) | 0x7000;

                iPixelX += 2;
            }
            nFlip ^= 2;
            iPixelY += 1;
        }
    }

    DCStoreRange(aPixel, pTexture->nSizeX * pTexture->nSizeY * nCount);
    return true;
}

static inline bool frameFreePixels(Frame* pFrame, FrameTexture* pTexture) {
    if (!frameFreeTLUT(pFrame, pTexture)) {
        return false;
    }
    if (!packFreeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel))) {
        return false;
    }
    return true;
}

u32 ganNameColor[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

GXTexMapID ganNamePixel[] = {
    GX_TEXMAP0, GX_TEXMAP1, GX_TEXMAP2, GX_TEXMAP3, GX_TEXMAP4, GX_TEXMAP5, GX_TEXMAP6, GX_TEXMAP7,
};

u32 ganNameTexMtx[] = {
    0x1E, 0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30, 0x33,
};

GXTexCoordID ganNameTexCoord[] = {
    GX_TEXCOORD0, GX_TEXCOORD1, GX_TEXCOORD2, GX_TEXCOORD3, GX_TEXCOORD4, GX_TEXCOORD5, GX_TEXCOORD6, GX_TEXCOORD7,
};

static char* gaszNameColor[] = {
    "CPREV",
    "APREV",
    "C0",
    "A0",
    "C1",
    "A1",
    "C2",
    "A2",
    "TEXC",
    "TEXA",
    "RASC",
    "RASA",
    "ONE",
    "HALF",
    "KONST",
    "ZERO",
    "TEXRRR (obsolete)",
    "TEXGGG (obsolete)",
    "TEXBBB (obsolete)",
    "GX_CC_KONST",
};

static char* gaszNameAlpha[] = {
    "APREV", "A0", "A1", "A2", "TEXA", "RASA", "KONST", "ZERO", "KONST",
};

static FrameDrawFunc gapfDrawTriangle[8] = {
    (FrameDrawFunc)frameDrawTriangle_C0T0,
    (FrameDrawFunc)frameDrawTriangle_C1T0,
    NULL,
    (FrameDrawFunc)frameDrawTriangle_C3T0,
    (FrameDrawFunc)frameDrawTriangle_C0T3,
    (FrameDrawFunc)frameDrawTriangle_C1T3,
    NULL,
    (FrameDrawFunc)frameDrawTriangle_C3T3,
};

static FrameDrawFunc gapfDrawLine[6] = {
    (FrameDrawFunc)frameDrawLine_C0T0, (FrameDrawFunc)frameDrawLine_C1T0, (FrameDrawFunc)frameDrawLine_C2T0,
    (FrameDrawFunc)frameDrawLine_C0T2, (FrameDrawFunc)frameDrawLine_C1T2, (FrameDrawFunc)frameDrawLine_C2T2,
};

static u16 sTempZBuf[N64_FRAME_WIDTH * N64_FRAME_HEIGHT / 16][4][4] ATTRIBUTE_ALIGN(32);

static s32 sZBufShift[] = {
    0x0003F800, 0x00000000, 0x0003F000, 0x00000000, 0x0003E000, 0x00000001, 0x0003C000, 0x00000002,
    0x00038000, 0x00000003, 0x00030000, 0x00000004, 0x00020000, 0x00000005, 0x00000000, 0x00000006,
};

static char* gaszNameColorType[] = {
    "FOG", "FILL", "BLEND", "PRIMITIVE", "ENVIRONMENT",
};

static bool frameLoadTexture(Frame* pFrame, FrameTexture* pTexture, s32 iTextureCode, Tile* pTile) {
    void* pData;
    s32 iName;
    s32 nFilter;
    GXTexWrapMode eWrapS;
    GXTexWrapMode eWrapT;
    s32 pad;

    pTexture->nFrameLast = pFrame->nCountFrames;
    iName = iTextureCode >> 4;
    pTile->nModeS = pTile->nModeS;

    if (((pTile->nModeS & 2) || pTile->nMaskS == 0) && !(pTexture->nMode & 1)) {
        eWrapS = GX_CLAMP;
    } else if (pTile->nModeS & 1) {
        eWrapS = GX_MIRROR;
    } else {
        eWrapS = GX_REPEAT;
    }
    pTile->nModeT = pTile->nModeT;
    if (((pTile->nModeT & 2) || pTile->nMaskT == 0) && !(pTexture->nMode & 2)) {
        eWrapT = GX_CLAMP;
    } else if (pTile->nModeT & 1) {
        eWrapT = GX_MIRROR;
    } else {
        eWrapT = GX_REPEAT;
    }
    if (pTexture->eWrapS != eWrapS || pTexture->eWrapT != eWrapT) {
        pTexture->eWrapS = eWrapS;
        pTexture->eWrapT = eWrapT;

        if ((GXCITexFmt)pTexture->eFormat == GX_TF_C4 || (GXCITexFmt)pTexture->eFormat == GX_TF_C8) {
            if (pTexture->iPackColor == -1) {
                pData = NULL;
            } else {
                pData = (u8*)pFrame->aColorData + ((pTexture->iPackColor & 0xFFFF) << 5);
            }
            GXInitTlutObj(&pTexture->objectTLUT, pData, GX_TL_RGB5A3,
                          (GXCITexFmt)pTexture->eFormat == GX_TF_C4 ? 16 : 256);

            if (pTexture->iPackPixel == -1) {
                pData = NULL;
            } else {
                pData = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }
            GXInitTexObjCI(&pTexture->objectTexture, pData, pTexture->nSizeX, pTexture->nSizeY,
                           (GXCITexFmt)pTexture->eFormat, eWrapS, eWrapT, GX_FALSE, 0);
        } else {
            if (pTexture->iPackPixel == -1) {
                pData = NULL;
            } else {
                pData = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }
            GXInitTexObj(&pTexture->objectTexture, pData, pTexture->nSizeX, pTexture->nSizeY, pTexture->eFormat, eWrapS,
                         eWrapT, 0);
        }
    }

    nFilter = pFrame->aMode[FMT_OTHER1] & 0x3000;
    if ((pTexture->nMode & 0x3000) != nFilter) {
        pTexture->nMode &= ~0x3000;
        pTexture->nMode |= nFilter;
        switch (nFilter) {
            case 0x0000:
                GXInitTexObjLOD(&pTexture->objectTexture, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                GX_ANISO_1);
                break;
            case 0x2000:
            case 0x3000:
                GXInitTexObjLOD(&pTexture->objectTexture, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                GX_ANISO_1);
                break;
            default:
                OSReport("LoadTexture: Unknown FILTER mode (%d)\n", nFilter);
                break;
        }
    }

    if ((GXCITexFmt)pTexture->eFormat == GX_TF_C4 || (GXCITexFmt)pTexture->eFormat == GX_TF_C8) {
        GXLoadTlut(&pTexture->objectTLUT, ganNameColor[iName]);
    }

    GXLoadTexObj(&pTexture->objectTexture, ganNamePixel[iName]);

    return true;
}

bool frameDrawSetup2D(Frame* pFrame) {
    Mtx44 matrix44;

    if (!(pFrame->nMode & 0x40000000)) {
        pFrame->nMode |= 0x40000000;

        GXSetViewport(0.0f, 0.0f, pFrame->anSizeX[1], pFrame->anSizeY[1], 0.0f, 1.0f);
        pFrame->nFlag |= 0x10000;

#if IS_MM
        if (gpSystem->eTypeROM == SRT_ZELDA2 && pFrame->bInBomberNotes) {
            GXSetViewport(32.0f, 13.0f, pFrame->anSizeX[1], pFrame->anSizeY[1], 0.0f, 1.0f);
        }
#endif

        if (snScissorChanged) {
            GXSetScissor(snScissorXOrig, snScissorYOrig, snScissorWidth, snScissorHeight);
            snScissorChanged = false;
        }

        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[FCT_FOG]);
        pFrame->nFlag |= 0x20;

        C_MTXOrtho(matrix44, 0.0f, pFrame->anSizeY[0] - 1.0f, 0.0f, pFrame->anSizeX[0] - 1.0f, 0.0f, 1001.0f);
        GXSetProjection(matrix44, GX_ORTHOGRAPHIC);
        pFrame->nFlag |= 0x40000;

        GXSetCullMode(GX_CULL_NONE);
        pFrame->nFlag |= 8;

        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);
        pFrame->nFlag |= 4;
    }

    return true;
}

static inline void frameSetZMode(Frame* pFrame) {
    u32 mode = pFrame->aMode[FMT_OTHER0];

#if IS_OOT
    if (pFrame->aMode[FMT_GEOMETRY] & 1) {
        if (mode & 0x10) {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            } else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            }
        } else {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
            } else {
                GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
            }
        }
    } else if (pFrame->bModifyZBuffer) {
        if (mode & 0x10) {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            } else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            }
        } else {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
            } else {
                GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
            }
        }
    } else {
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    }
#else
    if (pFrame->aMode[FMT_GEOMETRY] & 1) {
        if (mode & 0x10) {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            } else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            }
        }
    } else {
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    }

    if (pFrame->bModifyZBuffer == true) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
#endif
}

// non-matching for MM
static bool frameDrawSetupSP(Frame* pFrame, s32* pnColors, bool* pbFlag, s32 nVertexCount) {
    f32 rValue23;
    bool bTextureGen;
    f32 rNear;
    f32 rFar;
    f32 rScaleS;
    f32 rScaleT;
    f32 rSlideS;
    f32 rSlideT;
    FrameTexture* pTexture[8];
    s32 nColors;
    s32 bFlag;
    s32 iTile;
    s32 iHint;
    Mtx matrix;
    Mtx matrixA;
    Mtx matrixB;
    Mtx44 matrix44;
    Mtx44 matrixProjection;
    GXProjectionType eTypeProjection;
    f32 scale;
    s32 nCount;
    s32 iIndex;
#if IS_OOT
    s32 pad;

    nColors = 0;
#endif
    bTextureGen = (pFrame->aMode[FMT_GEOMETRY] & 0xA0) == 0xA0;

    if (pFrame->nFlag & 0x10000) {
        snScissorChanged = false;
        pFrame->nFlag &= ~0x10000;
        GXSetViewport(pFrame->viewport.rX, pFrame->viewport.rY, pFrame->viewport.rSizeX, pFrame->viewport.rSizeY, 0.0f,
                      1.0f);

        if (pFrame->viewport.rSizeX < GC_FRAME_WIDTH) {
            // TODO: regalloc hacks?
            u32* left = &snScissorXOrig;
            u32* top = &snScissorYOrig;
            GXGetScissor(left, top, &snScissorWidth, &snScissorHeight);

            if (snScissorWidth > pFrame->viewport.rSizeX) {
                GXSetScissor(pFrame->viewport.rX, pFrame->viewport.rY, pFrame->viewport.rSizeX,
                             pFrame->viewport.rSizeY);
                snScissorChanged = true;
            }
        }

        pFrame->nMode &= ~0x40000000;
    }

    if (pFrame->nFlag & 4) {
        pFrame->nFlag &= ~4;
        frameSetZMode(pFrame);
        pFrame->nMode &= ~0x40000000;
    }

    if (pFrame->nFlag & 8) {
        pFrame->nFlag &= ~8;
        switch (pFrame->aMode[FMT_GEOMETRY] & 0xC) {
            case 0x8:
                GXSetCullMode(GX_CULL_FRONT);
                break;
            case 0x4:
                GXSetCullMode(GX_CULL_BACK);
                break;
            case 0xC:
                GXSetCullMode(GX_CULL_ALL);
                break;
            default:
                GXSetCullMode(GX_CULL_NONE);
                break;
        }
        pFrame->nMode &= ~0x40000000;
    }

    if ((pFrame->nFlag & 0x40000) && (pFrame->nMode & 0x04000000)) {
        pFrame->nFlag &= ~0x40000;
        if (pFrame->nMode & 0x20000000) {
            eTypeProjection = pFrame->eTypeProjection == FMP_PERSPECTIVE ? GX_PERSPECTIVE : GX_ORTHOGRAPHIC;
            if ((pFrame->aMode[FMT_OTHER0] & 0xC00) == 0xC00 && eTypeProjection == GX_PERSPECTIVE) {
                GXSetProjection(pFrame->matrixProjection, eTypeProjection);
            } else {
                GXSetProjection(pFrame->matrixProjection, eTypeProjection);
            }
        } else {
            frameTransposeMatrix(matrix44, pFrame->matrixProjection);

            iHint = pFrame->iHintProjection;
            if (iHint != -1) {
                if (pFrame->aMatrixHint[iHint].eProjection == FMP_PERSPECTIVE) {
                    eTypeProjection = GX_PERSPECTIVE;
                } else {
                    eTypeProjection = GX_ORTHOGRAPHIC;
                }
                rNear = pFrame->aMatrixHint[iHint].rClipNear;
                rFar = pFrame->aMatrixHint[iHint].rClipFar;
            } else if (pFrame->matrixProjection[3][3] == 1.0f) {
                rNear = 0.0f;
                rFar = 32000.0f;
                eTypeProjection = GX_ORTHOGRAPHIC;
            } else {
                rNear = 1.0f;
                rFar = 32000.0f;
                eTypeProjection = GX_PERSPECTIVE;
            }
            if (eTypeProjection == GX_PERSPECTIVE) {
                C_MTXPerspective(matrixProjection, 30.0f, 4.0f / 3.0f, 0.1f * rNear, rFar);
            } else {
                rNear = -rFar;
                C_MTXOrtho(matrixProjection, (f32)pFrame->anSizeY[0] / 2.0, -(f32)pFrame->anSizeY[0] / 2.0,
                           -(f32)pFrame->anSizeX[0] / 2.0, (f32)pFrame->anSizeX[0] / 2.0, rNear, rFar);
            }

            rValue23 = matrixProjection[2][3];
            if ((pFrame->aMode[FMT_OTHER0] & 0xC00) == 0xC00 && eTypeProjection == GX_PERSPECTIVE) {
                rValue23 = -((0.0015f * rNear) - rValue23);
            }

#if IS_MM
            if (eTypeProjection == GX_PERSPECTIVE) {
                gNearVal = matrix44[2][3] * ((matrix44[2][2] + 1.0f) / (matrix44[2][3] - 1.0f) - 1.0f) * 0.5f;
                gFarVal = gNearVal * ((matrix44[2][2] - 1.0f) / (matrix44[2][2] + 1.0f) + 1.0f);
            } else {
                gNearVal = (matrix44[2][3] + 1.0f) / matrix44[2][2];
                gFarVal = (matrix44[2][3] - 1.0f) / matrix44[2][2];
            }
#endif

            matrix44[2][2] = matrixProjection[2][2];
            matrix44[2][3] = rValue23;

#if IS_MM
            memcpy(gRealProjectionMtx, matrix44, sizeof(Mtx44));
            C_MTXPerspective(matrix44, 30.0f, 4.0f / 3.0f, 0.1f * rNear, rFar);
            gRealProjectionMtx[2][2] = matrixProjection[2][2];
            gRealProjectionMtx[2][3] = matrixProjection[2][3];
            gRealProjectionType = eTypeProjection;
#endif

            GXSetProjection(matrix44, eTypeProjection);
        }

        pFrame->nMode &= ~0x40000000;
    }

    if (pFrame->aMode[FMT_TEXTURE2] & 1) {
        bFlag = true;
        scale = !(pFrame->aMode[FMT_OTHER1] & 0x80000) ? 0.5f : 1.0f;
        iTile = (pFrame->aMode[FMT_TEXTURE2] >> 8) & 7;
        nCount = iTile +
                 (((s32)((pFrame->aMode[FMT_TEXTURE2] >> 8) & 7) < 7 && pFrame->aTile[iTile + 1].nSizeX != 0) ? 1 : 0);

        if (pFrame->nFlag & 1) {
            for (iIndex = 0; iTile <= nCount; iTile++, iIndex++) {
                if (frameLoadTile(pFrame, &pTexture[iTile], iTile | (iIndex << 4))) {
                    if (bTextureGen) {
                        rSlideS = (pFrame->aTile[iTile].nX0 / 4.0f) / pTexture[iTile]->nSizeX;
                        rSlideT = (pFrame->aTile[iTile].nY0 / 4.0f) / pTexture[iTile]->nSizeY;

                        rScaleS = 65536.0f * ((pFrame->aMode[FMT_TEXTURE1] >> 16) / 65536.0f);
                        rScaleS /= (pTexture[iTile]->nSizeX << 6);
                        rScaleT = 65536.0f * ((pFrame->aMode[FMT_TEXTURE1] & 0xFFFF) / 65536.0f);
                        rScaleT /= (pTexture[iTile]->nSizeY << 6);
                    } else {
                        rSlideS = ((pFrame->aTile[iTile].nX0 / 4.0f) - 0.5f) / pTexture[iTile]->nSizeX;
                        rSlideT = ((pFrame->aTile[iTile].nY0 / 4.0f) - 0.5f) / pTexture[iTile]->nSizeY;

                        rScaleS = (pFrame->aMode[FMT_TEXTURE1] >> 16) / 65536.0f;
                        rScaleS /= pTexture[iTile]->nSizeX;
                        rScaleT = (pFrame->aMode[FMT_TEXTURE1] & 0xFFFF) / 65536.0f;
                        rScaleT /= pTexture[iTile]->nSizeY;
                    }

                    if (pFrame->aTile[iTile].nShiftS < 11) {
                        rScaleS /= (1 << pFrame->aTile[iTile].nShiftS);
                    } else {
                        rScaleS *= (1 << (16 - pFrame->aTile[iTile].nShiftS));
                    }

                    if (pFrame->aTile[iTile].nShiftT < 11) {
                        rScaleT /= (1 << pFrame->aTile[iTile].nShiftT);
                    } else {
                        rScaleT *= (1 << (16 - pFrame->aTile[iTile].nShiftT));
                    }

                    PSMTXTrans(matrixA, -rSlideS, -rSlideT, 0.0f);
                    PSMTXScale(matrixB, rScaleS * scale, rScaleT * scale, 0.0f);
                    PSMTXConcat(matrixA, matrixB, matrix);
                    GXLoadTexMtxImm(matrix, ganNameTexMtx[iIndex], GX_MTX2x4);
                }
            }
        }
    } else {
        bFlag = false;
    }

    if (pFrame->aMode[FMT_GEOMETRY] & 2) {
        if (pFrame->aMode[FMT_GEOMETRY] & 0x200) {
            nColors = nVertexCount;
        } else {
            nColors = 1;
        }
    }

    *pbFlag = bFlag;
    *pnColors = nColors;
    return true;
}

static bool frameGetCombineColor(Frame* pFrame, GXTevColorArg* pnColorTEV, s32 nColorN64) {
    switch (nColorN64) {
        case 0:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 1:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 2:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 3:
            *pnColorTEV = GX_CC_C0;
            break;
        case 4:
            *pnColorTEV = GX_CC_RASC;
            break;
        case 5:
            *pnColorTEV = GX_CC_C1;
            break;
        case 7:
            *pnColorTEV = GX_CC_TEXA;
            break;
        case 8:
            *pnColorTEV = GX_CC_TEXA;
            break;
        case 9:
            *pnColorTEV = GX_CC_TEXA;
            break;
        case 10:
            *pnColorTEV = GX_CC_A0;
            break;
        case 11:
            *pnColorTEV = GX_CC_RASA;
            break;
        case 12:
            *pnColorTEV = GX_CC_A1;
            break;
        case 13:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 14:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 15:
            *pnColorTEV = GX_CC_C2;
            break;
        case 6:
            *pnColorTEV = GX_CC_ONE;
            break;
        case 31:
            *pnColorTEV = GX_CC_ZERO;
            break;
        default:
            return false;
    }

    return true;
}

static bool frameGetCombineAlpha(Frame* pFrame, GXTevAlphaArg* pnAlphaTEV, s32 nAlphaN64) {
    switch (nAlphaN64) {
        case 0:
            *pnAlphaTEV = GX_CA_TEXA;
            break;
        case 1:
            *pnAlphaTEV = GX_CA_TEXA;
            break;
        case 2:
            *pnAlphaTEV = GX_CA_TEXA;
            break;
        case 3:
            *pnAlphaTEV = GX_CA_A0;
            break;
        case 4:
            *pnAlphaTEV = GX_CA_RASA;
            break;
        case 5:
            *pnAlphaTEV = GX_CA_A1;
            break;
        case 6:
            *pnAlphaTEV = GX_CA_KONST;
            break;
        case 7:
            *pnAlphaTEV = GX_CA_ZERO;
            break;
        default:
            return false;
    }

    return true;
}

static bool frameDrawSetupDP(Frame* pFrame, s32* pnColors, bool* pbFlag, s32 vertexCount) {
    u32 nMode;
    s32 numCycles;
    u32 mode;
    u32 cycle;
    s32 pad[2];

    if (pFrame->nFlag & 0x100) {
        pFrame->nFlag &= ~0x100;
        if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x300000) {
            *pnColors = 0;
            *pbFlag = false;
            GXSetNumTevStages(1);
            GXSetNumChans(1);
            GXSetNumTexGens(0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C2);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A2);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            GXSetTevColor(GX_TEVREG2, pFrame->aColor[FCT_FILL]);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        } else if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x200000) {
            GXSetNumTevStages(1);
            GXSetNumChans(0);
            GXSetNumTexGens(1);
            GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        } else {
            numCycles = ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x100000) + 1;
            if (!SetTevStageTable(pFrame, numCycles)) {
                GXSetNumTevStages(numCycles * 5);
                SetNumTexGensChans(pFrame, numCycles);
                SetTevStages(pFrame, 0, numCycles);
                if (numCycles == 2) {
                    SetTevStages(pFrame, 1, numCycles);
                }
            }
        }
    }

    if (pFrame->nFlag & 0x220) {
        pFrame->nFlag &= ~0x20;
        if ((pFrame->aMode[FMT_GEOMETRY] & 0x10)) {
            switch (gpSystem->eTypeROM) {
                case SRT_ZELDA1:
                case SRT_ZELDA2:
                    if (!frameDrawSetupFog_Zelda1(pFrame)) {
                        return false;
                    }
                    break;
#if IS_MM
                case SRT_STARFOX:
                    if (!frameDrawSetupFog_StarFox(pFrame)) {
                        return false;
                    }
                    break;
                case SRT_MARIOKART:
                    if (!frameDrawSetupFog_MarioKart(pFrame)) {
                        return false;
                    }
                    break;
#endif
                default:
                    if (!frameDrawSetupFog_Default(pFrame)) {
                        return false;
                    }
                    break;
            }
        } else {
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[FCT_FOG]);
        }
        pFrame->nMode &= ~0x40000000;
    }

    if (pFrame->nFlag & 0x200) {
        pFrame->nFlag &= ~0x200;
        mode = pFrame->aMode[FMT_OTHER0];

        if ((mode & 0xFFFF0000) == 0xAF500000) {
            GXSetColorUpdate(GX_FALSE);
        } else {
            GXSetColorUpdate(GX_TRUE);
        }

        cycle = pFrame->aMode[FMT_OTHER1] & 0x300000;
        if (((mode & 0x33330000) == 0x100000 && cycle == 0x100000) || (mode & 0xCCCC0000) == 0x400000) {
            GXSetZCompLoc(GX_FALSE);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            if ((mode & 3) == 1) {
                GXSetAlphaCompare(GX_GREATER, pFrame->aColor[FCT_BLEND].a, GX_AOP_AND, GX_GREATER,
                                  pFrame->aColor[FCT_BLEND].a);
            } else if (mode & 0x1000) {
                GXSetAlphaCompare(GX_GREATER, 16, GX_AOP_AND, GX_GREATER, 16);
            } else {
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
            }
        } else if ((mode & 0x1000) || (mode & 1)) {
            GXSetZCompLoc(GX_FALSE);
            GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            if ((mode & 3) == 1) {
                GXSetAlphaCompare(GX_GREATER, pFrame->aColor[FCT_BLEND].a, GX_AOP_AND, GX_GREATER,
                                  pFrame->aColor[FCT_BLEND].a);
            } else {
                GXSetAlphaCompare(GX_GREATER, 16, GX_AOP_AND, GX_GREATER, 16);
            }
        } else {
            if ((mode & 3) == 1) {
                GXSetZCompLoc(GX_FALSE);
                GXSetAlphaCompare(GX_GREATER, pFrame->aColor[FCT_BLEND].a, GX_AOP_AND, GX_GREATER,
                                  pFrame->aColor[FCT_BLEND].a);
            } else {
                GXSetZCompLoc(GX_TRUE);
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
            }
            GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        }

        frameSetZMode(pFrame);
    }

    return true;
}

static bool frameDrawTriangle_C0T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    if (pFrame->nModeVtx != 0x11) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        pFrame->nModeVtx = 0x11;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
    }
    GXEnd();

    return true;
}

static bool frameDrawTriangle_C1T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;
    Vertex* pVertexColor;

    if (pFrame->nModeVtx != 0x13) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0x13;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertexColor = &pFrame->aVertex[anData[iData + 0]];
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
    }
    GXEnd();

    return true;
}

static bool frameDrawTriangle_C3T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    if (pFrame->nModeVtx != 0x13) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0x13;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
    }
    GXEnd();

    return true;
}

static bool frameDrawTriangle_C0T3(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    if (pFrame->nModeVtx != 0x15) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x15;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}

static bool frameDrawTriangle_C1T3(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;
    Vertex* pVertexColor;

    if (pFrame->nModeVtx != 0x17) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x17;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertexColor = &pFrame->aVertex[anData[iData + 0]];
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}

static inline void frameWriteVertex(Vertex* pVertex) {
    GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
    GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
    GXTexCoord2f32(pVertex->rS, pVertex->rT);
}

static bool frameCheckTriangleDivide(Frame* pFrame, Primitive* pPrimitive) {
    s32 pad1[3];
    Vertex* v0;
    Vertex* v1;
    Vertex* v2;
    s32 iData;
    u8* anData;
    Vertex aNewVertArray[8];
    f32 fInterp;
    f32 fTempColor1;
    f32 fTempColor2;
    u32 nNewVertCount;
    u32 bInFront;
    u32 bBehind;
    u32 aSide[3];

    iData = 0;
    anData = pPrimitive->anData;
    while (iData < pPrimitive->nCount) {
        aSide[0] = 3;
        aSide[1] = 3;
        aSide[2] = 3;
        bInFront = false;
        bBehind = false;

        v0 = &pFrame->aVertex[anData[iData + 0]];
        if (v0->vec.z < 0.0f) {
            aSide[0] = 0;
            bBehind = true;
        } else if (v0->vec.z > 0.0f) {
            aSide[0] = 1;
            bInFront = true;
        }

        v1 = &pFrame->aVertex[anData[iData + 1]];
        if (v1->vec.z < 0.0f) {
            aSide[1] = 0;
            bBehind = true;
        } else if (v1->vec.z > 0.0f) {
            aSide[1] = 1;
            bInFront = true;
        }

        v2 = &pFrame->aVertex[anData[iData + 2]];
        if (v2->vec.z < 0.0f) {
            aSide[2] = 0;
            bBehind = true;
        } else if (v2->vec.z > 0.0f) {
            aSide[2] = 1;
            bInFront = true;
        }

        if (!bBehind || !bInFront) {
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
            frameWriteVertex(v0);
            frameWriteVertex(v1);
            frameWriteVertex(v2);
            GXEnd();
            iData += 3;
        } else {
            nNewVertCount = 0;
            aNewVertArray[nNewVertCount++] = *v0;
            if ((aSide[0] == 0 && aSide[1] == 1) || (aSide[0] == 1 && aSide[1] == 0)) {
                fInterp = -v0->vec.z / (v1->vec.z - v0->vec.z);

                aNewVertArray[1].vec.z = 0.0f;
                if (v0->vec.y == v1->vec.y) {
                    aNewVertArray[1].vec.y = v0->vec.y;
                } else {
                    aNewVertArray[1].vec.y = v0->vec.y + fInterp * (v1->vec.y - v0->vec.y);
                }
                if (v0->vec.x == v1->vec.x) {
                    aNewVertArray[1].vec.x = v0->vec.x;
                } else {
                    aNewVertArray[1].vec.x = v0->vec.x + fInterp * (v1->vec.x - v0->vec.x);
                }

                aNewVertArray[1].rS = v0->rS + fInterp * (v1->rS - v0->rS);
                aNewVertArray[1].rT = v0->rT + fInterp * (v1->rT - v0->rT);

                fTempColor1 = v1->anColor[0];
                fTempColor2 = v0->anColor[0];
                aNewVertArray[1].anColor[0] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v1->anColor[1];
                fTempColor2 = v0->anColor[1];
                aNewVertArray[1].anColor[1] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v1->anColor[2];
                fTempColor2 = v0->anColor[2];
                aNewVertArray[1].anColor[2] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v1->anColor[3];
                fTempColor2 = v0->anColor[3];
                aNewVertArray[1].anColor[3] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);

                nNewVertCount++;
            }

            aNewVertArray[nNewVertCount++] = *v1;
            if ((aSide[1] == 1 && aSide[2] == 0) || (aSide[1] == 0 && aSide[2] == 1)) {
                fInterp = -v1->vec.z / (v2->vec.z - v1->vec.z);

                aNewVertArray[nNewVertCount].vec.z = 0.0f;
                if (v1->vec.y == v2->vec.y) {
                    aNewVertArray[nNewVertCount].vec.y = v1->vec.y;
                } else {
                    aNewVertArray[nNewVertCount].vec.y = v1->vec.y + fInterp * (v2->vec.y - v1->vec.y);
                }
                if (v1->vec.x == v2->vec.x) {
                    aNewVertArray[nNewVertCount].vec.x = v1->vec.x;
                } else {
                    aNewVertArray[nNewVertCount].vec.x = v1->vec.x + fInterp * (v2->vec.x - v1->vec.x);
                }

                aNewVertArray[nNewVertCount].rS = v1->rS + fInterp * (v2->rS - v1->rS);
                aNewVertArray[nNewVertCount].rT = v1->rT + fInterp * (v2->rT - v1->rT);

                fTempColor1 = v2->anColor[0];
                fTempColor2 = v1->anColor[0];
                aNewVertArray[nNewVertCount].anColor[0] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[1];
                fTempColor2 = v1->anColor[1];
                aNewVertArray[nNewVertCount].anColor[1] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[2];
                fTempColor2 = v1->anColor[2];
                aNewVertArray[nNewVertCount].anColor[2] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[3];
                fTempColor2 = v1->anColor[3];
                aNewVertArray[nNewVertCount].anColor[3] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);

                nNewVertCount++;
            }

            aNewVertArray[nNewVertCount++] = *v2;
            if ((aSide[0] == 0 && aSide[2] == 1) || (aSide[0] == 1 && aSide[2] == 0)) {
                fInterp = -v0->vec.z / (v2->vec.z - v0->vec.z);

                aNewVertArray[nNewVertCount].vec.z = 0.0f;
                if (v0->vec.y == v2->vec.y) {
                    aNewVertArray[nNewVertCount].vec.y = v0->vec.y;
                } else {
                    aNewVertArray[nNewVertCount].vec.y = v0->vec.y + fInterp * (v2->vec.y - v0->vec.y);
                }
                if (v0->vec.x == v2->vec.x) {
                    aNewVertArray[nNewVertCount].vec.x = v0->vec.x;
                } else {
                    aNewVertArray[nNewVertCount].vec.x = v0->vec.x + fInterp * (v2->vec.x - v0->vec.x);
                }

                aNewVertArray[nNewVertCount].rS = v0->rS + fInterp * (v2->rS - v0->rS);
                aNewVertArray[nNewVertCount].rT = v0->rT + fInterp * (v2->rT - v0->rT);

                fTempColor1 = v2->anColor[0];
                fTempColor2 = v0->anColor[0];
                aNewVertArray[nNewVertCount].anColor[0] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[1];
                fTempColor2 = v0->anColor[1];
                aNewVertArray[nNewVertCount].anColor[1] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[2];
                fTempColor2 = v0->anColor[2];
                aNewVertArray[nNewVertCount].anColor[2] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[3];
                fTempColor2 = v0->anColor[3];
                aNewVertArray[nNewVertCount].anColor[3] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);

                nNewVertCount++;
            }

            if (nNewVertCount == 5) {
                if (v1->vec.x == aNewVertArray[1].vec.x && v1->vec.y == aNewVertArray[1].vec.y &&
                    v1->vec.z == aNewVertArray[1].vec.z) {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 9);
                    frameWriteVertex(&aNewVertArray[0]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[0]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[3]);
                    GXEnd();
                } else if (v2->vec.x == aNewVertArray[3].vec.x && v2->vec.y == aNewVertArray[3].vec.y &&
                           v2->vec.z == aNewVertArray[3].vec.z) {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 9);
                    frameWriteVertex(&aNewVertArray[0]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[3]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[3]);
                    GXEnd();
                } else {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 9);
                    frameWriteVertex(&aNewVertArray[0]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[3]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[3]);
                    GXEnd();
                }
            }
            iData += 3;
        }
    }

    return true;
}

bool frameDrawTriangle_C3T3(Frame* pFrame, Primitive* pPrimitive) {
    u32 pad[20];

    if (gpSystem->eTypeROM == SRT_ZELDA1 && pPrimitive->nCount == 3 && (pFrame->aMode[FMT_OTHER0] & 0xC00) == 0xC00) {
        Mtx44Ptr pMatrix = pFrame->aMatrixModel[pFrame->iMatrixModel];
        Vertex* vtx = &pFrame->aVertex[pPrimitive->anData[0]];
        if ((vtx->rSum == -53.0f && pMatrix[3][0] == -3080.0f && pMatrix[3][2] == 6067.0f) ||
            (pMatrix[3][0] == -31.0f && pMatrix[3][2] == 1669.0f)) {
            if (pMatrix[3][0] == -31.0f && pMatrix[3][2] == 1669.0f) {
                gHackCreditsColor = true;
            }
            return true;
        }
    }

    if (pFrame->nModeVtx != 0x17) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x17;
    }

    frameCheckTriangleDivide(pFrame, pPrimitive);
    return true;
}

static bool frameDrawTriangle_Setup(Frame* pFrame, Primitive* pPrimitive) {
    bool bFlag;
    s32 nColors;

    if (!frameDrawSetupSP(pFrame, &nColors, &bFlag, 3)) {
        return false;
    }

    if (!frameDrawSetupDP(pFrame, &nColors, &bFlag, 0)) {
        return false;
    }

    pFrame->aDraw[1] = (FrameDrawFunc)gapfDrawTriangle[nColors + (bFlag ? 4 : 0)];
    if (!pFrame->aDraw[1](pFrame, pPrimitive)) {
        return false;
    }

    return true;
}

static bool frameDrawLine_C0T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x21) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        pFrame->nModeVtx = 0x21;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
    }
    GXEnd();

    return true;
}

static bool frameDrawLine_C1T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;
    Vertex* pVertexColor;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x23) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0x23;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertexColor = &pFrame->aVertex[anData[iData + 0]];
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
    }
    GXEnd();

    return true;
}

static bool frameDrawLine_C2T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x23) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0x23;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
    }
    GXEnd();

    return true;
}

static bool frameDrawLine_C0T2(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x25) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x25;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}

static bool frameDrawLine_C1T2(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;
    Vertex* pVertexColor;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x27) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x27;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertexColor = &pFrame->aVertex[anData[iData + 0]];
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}

static bool frameDrawLine_C2T2(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x27) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x27;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}

static bool frameDrawLine_Setup(Frame* pFrame, Primitive* pPrimitive) {
    bool bFlag;
    s32 nColors;

    if (!frameDrawSetupSP(pFrame, &nColors, &bFlag, 2)) {
        return false;
    }

    if (!frameDrawSetupDP(pFrame, &nColors, &bFlag, 0)) {
        return false;
    }

    pFrame->aDraw[0] = (FrameDrawFunc)gapfDrawLine[nColors + (bFlag ? 3 : 0)];
    if (!pFrame->aDraw[0](pFrame, pPrimitive)) {
        return false;
    }

    return true;
}

static bool frameDrawRectFill(Frame* pFrame, Rectangle* pRectangle) {
    bool bFlag;
    f32 rDepth;
    f32 rX0;
    f32 rY0;
    f32 rX1;
    f32 rY1;

    //! @bug `pRectangle->nY1` is using the N64 width instead of the height
    if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x300000 && pRectangle->nX0 <= 16 && pRectangle->nY0 <= 32 &&
        pRectangle->nX1 >= N64_FRAME_WIDTH - 16 && pRectangle->nY1 >= N64_FRAME_HEIGHT - 32) {
        bFlag = false;
        if (pFrame->aColor[FCT_FILL].r == 0xFF && pFrame->aColor[FCT_FILL].g == 0xFC &&
            pFrame->aColor[FCT_FILL].b == 0xFF && pFrame->aColor[FCT_FILL].a == 0xFC) {
            bFlag = true;
        }
        if (pFrame->aColor[FCT_FILL].r == 0xF8 && pFrame->aColor[FCT_FILL].g == 0xF8 &&
            pFrame->aColor[FCT_FILL].b == 0xF0 && pFrame->aColor[FCT_FILL].a == 0x00) {
            bFlag = true;
        }
        if (bFlag && !(pFrame->nMode & 0x100000)) {
            pFrame->nMode |= 0x100000;
            return true;
        }
    }

    rX0 = pRectangle->nX0;
    rX1 = pRectangle->nX1;
    rY0 = pRectangle->nY0;
    rY1 = pRectangle->nY1;
    if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x300000 || (pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x200000) {
        rX1 += 1.0f;
        rY1 += 1.0f;
    }
    if ((pFrame->aMode[FMT_OTHER0] & 4) == 4) {
        rDepth = pFrame->rDepth;
    } else {
        rDepth = 0.0f;
    }
    if (pFrame->nModeVtx != 0xB) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0xB;
    }

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(rX0, rY0, rDepth);
    GXColor1u32(0);
    GXPosition3f32(rX1, rY0, rDepth);
    GXColor1u32(0);
    GXPosition3f32(rX1, rY1, rDepth);
    GXColor1u32(0);
    GXPosition3f32(rX0, rY1, rDepth);
    GXColor1u32(0);
    GXEnd();

    return true;
}

static bool frameDrawRectFill_Setup(Frame* pFrame, Rectangle* pRectangle) {
    bool bFlag;
    s32 nColors;

    if (!frameDrawSetup2D(pFrame)) {
        return false;
    }

    bFlag = false;
    nColors = 0;

    if (!frameDrawSetupDP(pFrame, &nColors, &bFlag, 1)) {
        return false;
    }

    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill;

    if (!pFrame->aDraw[2](pFrame, pRectangle)) {
        return false;
    }

    return true;
}

// non-matching for MM
static bool frameDrawRectTexture(Frame* pFrame, Rectangle* pRectangle) {
    s32 bCopy;
    f32 rDepth;
    f32 rDeltaS;
    f32 rDeltaT;
    f32 rX0;
    f32 rY0;
    f32 rX1;
    f32 rY1;
    f32 rS0;
    f32 rT0;
    f32 rS1;
    f32 rT1;
    s32 pad;

#if IS_OOT
    static s32 nCounter;

    if (gpSystem->eTypeROM == SRT_DRMARIO) {
        if (pRectangle->nX0 == 0 && pRectangle->nY0 == 0 && pRectangle->nX1 == 1308 && pRectangle->nY1 == 20) {
            if (pFrame->aBuffer[FBT_IMAGE].nAddress != 0x3B5000 && pFrame->aBuffer[FBT_IMAGE].nAddress != 0x3DA800 &&
                !pFrame->bBackBufferDrawn) {
                ZeldaDrawFrameNoBlend(pFrame, TEMP_BUFFER);
                pFrame->bBackBufferDrawn = true;
                nCounter = 0;
            }
        }
        if (pFrame->bBackBufferDrawn == true) {
            nCounter += 1;
            if (nCounter < 40) {
                return true;
            }
        }
    }
#endif

    if (sSpecialZeldaHackON) {
        return true;
    }

    if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x300000 || (pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x200000) {
        bCopy = true;
    } else {
        bCopy = false;
    }

    rDeltaS = bCopy ? pRectangle->rDeltaS / 4.0f : pRectangle->rDeltaS;
    rDeltaT = pRectangle->rDeltaT;

    rX0 = (pRectangle->nX0 + 3) >> 2;
    rX1 = (pRectangle->nX1 + 3) >> 2;
    rY0 = (pRectangle->nY0 + 3) >> 2;
    rY1 = (pRectangle->nY1 + 3) >> 2;

#if IS_MM
    if (gpSystem->eTypeROM == SRT_ZELDA2) {
        if (rX1 - rX0 <= 1.0 || rY1 - rY0 <= 1.0) {
            rX0 = 0.25 * ((pRectangle->nX0 >> 2));
            rX1 = 0.25 * ((pRectangle->nX1 >> 2));
            rY0 = 0.25 * ((pRectangle->nY0 >> 2));
            rY1 = 0.25 * ((pRectangle->nY1 >> 2));
        }
    }
#endif

    // TODO: regalloc hacks
    (void)pRectangle->nY0;
    if (gpSystem->eTypeROM == SRT_ZELDA1) {
        if (pRectangle->nX0 == 816 && pRectangle->nY0 == 560) {
            if (gnCountMapHack < 0 && ++gnCountMapHack == 0) {
                gnCountMapHack = 1;
            } else if (gnCountMapHack > 0) {
                gnCountMapHack--;
                return true;
            }
        }
    }

    if (pRectangle->bFlip) {
        rS0 = pRectangle->rS;
        rT0 = pRectangle->rT;
        rS1 = pRectangle->rS + rDeltaS * (rY1 - rY0);
        rT1 = pRectangle->rT + rDeltaT * (rX1 - rX0);
    } else {
        rS0 = pRectangle->rS;
        rT0 = pRectangle->rT;
        rS1 = pRectangle->rS + rDeltaS * (rX1 - rX0);
        rT1 = pRectangle->rT + rDeltaT * (rY1 - rY0);
    }

    if (bCopy) {
        rX1 += 1.0f;
        rS1 += 1.0f;
        rY1 += 1.0f;
        rT1 += 1.0f;
    }

    rDepth = 0.0f;
#if IS_OOT
    if (pFrame->bOverrideDepth) {
        rDepth = -1001.0;
    }
#endif

    if (pFrame->nModeVtx != 0xF) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0xF;
    }

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    if (pRectangle->bFlip) {
        GXPosition3f32(rX0, rY0, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS0, rT0);
        GXPosition3f32(rX0, rY1, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS1, rT0);
        GXPosition3f32(rX1, rY1, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS1, rT1);
        GXPosition3f32(rX1, rY0, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS0, rT1);
    } else {
        GXPosition3f32(rX0, rY0, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS0, rT0);
        GXPosition3f32(rX1, rY0, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS1, rT0);
        GXPosition3f32(rX1, rY1, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS1, rT1);
        GXPosition3f32(rX0, rY1, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS0, rT1);
    }
    GXEnd();

    return true;
}

// non-matching for MM
static bool frameDrawRectTexture_Setup(Frame* pFrame, Rectangle* pRectangle) {
    Mtx matrix;
    Mtx matrixA;
    Mtx matrixB;
    FrameTexture* pTexture[8];
    f32 rScaleS;
    f32 rScaleT;
    f32 rSlideS;
    f32 rSlideT;
    u32 bFlag;
    u32 nColors;
    s32 iTile;
    s32 firstTile;
    s32 nCount;
    s32 iIndex;
    s8 cTempAlpha;

    iTile = firstTile = pRectangle->iTile;
    if (sSpecialZeldaHackON) {
        return true;
    }

    if (!frameDrawSetup2D(pFrame)) {
        return false;
    }

    nColors = 0;
    bFlag = true;
    if (!frameDrawSetupDP(pFrame, (s32*)&nColors, (bool*)&bFlag, 1)) {
        return false;
    }

    nCount = iTile + (iTile < 7 && pFrame->aTile[iTile + 1].nSizeX != 0 ? 1 : 0);
    if (bFlag) {
        for (iIndex = 0; iTile <= nCount; iTile++, iIndex++) {
            if (frameLoadTile(pFrame, &pTexture[iTile], iTile | (iIndex << 4))) {
#if IS_OOT
                static bool bSkip;

                if (gpSystem->eTypeROM == SRT_ZELDA2 && pTexture[iTile]->nAddress == 0x784600 &&
                    pRectangle->nX1 == 1280) {
                    bSkip = true;
                    if (!pFrame->bPauseBGDrawn) {
                        cTempAlpha = pFrame->cBlurAlpha;
                        pFrame->cBlurAlpha = 220;
                        ZeldaDrawFrame(pFrame, COPY_BUFFER);
                        pFrame->cBlurAlpha = cTempAlpha;
                        pFrame->bPauseBGDrawn = true;
                        bSkip = true;
                    }
                }

                if (bSkip) {
                    if (pRectangle->nY1 == 960) {
                        bSkip = false;
                        return true;
                    }
                    return true;
                }
#endif

                rScaleS = 1.0f / pTexture[iTile]->nSizeX;
                if (pFrame->aTile[iTile].nShiftS < 11) {
                    rScaleS /= (1 << pFrame->aTile[iTile].nShiftS);
                } else {
                    rScaleS *= (1 << (16 - pFrame->aTile[iTile].nShiftS));
                }

                rScaleT = 1.0f / pTexture[iTile]->nSizeY;
                if (pFrame->aTile[iTile].nShiftT < 11) {
                    rScaleT /= (1 << pFrame->aTile[iTile].nShiftT);
                } else {
                    rScaleT *= (1 << (16 - pFrame->aTile[iTile].nShiftT));
                }

                rSlideS = (pFrame->aTile[iTile].nX0 / 4.0f) / pTexture[iTile]->nSizeX;
                rSlideT = (pFrame->aTile[iTile].nY0 / 4.0f) / pTexture[iTile]->nSizeY;
                PSMTXTrans(matrixA, -rSlideS, -rSlideT, 0.0f);
                PSMTXScale(matrixB, rScaleS, rScaleT, 0.0f);
                PSMTXConcat(matrixA, matrixB, matrix);
                GXLoadTexMtxImm(matrix, ganNameTexMtx[iIndex], 1);
            }
        }

        pFrame->aDraw[3] = (FrameDrawFunc)frameDrawRectTexture;
        if (!pFrame->aDraw[3](pFrame, pRectangle)) {
            return false;
        }
    }

    return true;
}

bool frameShow(Frame* pFrame) { return true; }

bool frameSetScissor(Frame* pFrame, Rectangle* pScissor) {
    s32 nTemp;
    s32 nX0;
    s32 nY0;
    s32 nX1;
    s32 nY1;

    nX0 = pScissor->nX0 / 4.0f * pFrame->rScaleX;
    nY0 = pScissor->nY0 / 4.0f * pFrame->rScaleY;
    nX1 = pScissor->nX1 / 4.0f * pFrame->rScaleX;
    nY1 = pScissor->nY1 / 4.0f * pFrame->rScaleY;

    if (nX1 < nX0) {
        nTemp = nX1;
        nX1 = nX0;
        nX0 = nTemp;
    }

    if (nY1 < nY0) {
        nTemp = nY1;
        nY1 = nY0;
        nY0 = nTemp;
    }

    GXSetScissor(nX0, nY0, nX1 - nX0, nY1 - nY0);
    return true;
}

bool frameSetDepth(Frame* pFrame, f32 rDepth, f32 rDelta) {
    pFrame->rDepth = rDepth;
    pFrame->rDelta = rDelta;
    return true;
}

bool frameSetColor(Frame* pFrame, FrameColorType eType, u32 nRGBA) {
    pFrame->aColor[eType].r = (nRGBA >> 24) & 0xFF;
    pFrame->aColor[eType].g = (nRGBA >> 16) & 0xFF;
    pFrame->aColor[eType].b = (nRGBA >> 8) & 0xFF;
    pFrame->aColor[eType].a = nRGBA & 0xFF;

    if (eType == FCT_PRIMITIVE) {
        GXSetTevColor(GX_TEVREG2, pFrame->aColor[eType]);
    } else if (eType == FCT_ENVIRONMENT) {
        GXSetTevKColor(GX_KCOLOR1, pFrame->aColor[eType]);
    }

    frameDrawReset(pFrame, (eType == FCT_FOG ? 0x20 : 0x0) | 0x7F00);
    return true;
}

bool frameBeginOK(Frame* pFrame) {
    if (gbFrameValid) {
        return false;
    }
    return true;
}

static inline void frameClearModes(Frame* pFrame) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(pFrame->aMode); i++) {
        pFrame->aMode[i] = 0;
    }
}

bool frameBegin(Frame* pFrame, s32 nCountVertex) {
    s32 i;
    Mtx matrix;

#if IS_MM
    UpdateDVDTrackList();
#endif

    if (gbFrameBegin) {
        gbFrameBegin = false;

        while (gbFrameValid) {
            OSReport("Waiting for valid?\n");
        }

        if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
            return false;
        }

        if (!frameUpdateCache(pFrame)) {
            return false;
        }

        xlCoreBeforeRender();
        pFrame->nMode &= ~0x180000;

        GXSetMisc(GX_MT_XF_FLUSH, 8);
        PSMTXIdentity(matrix);
        GXLoadPosMtxImm(matrix, 0);

        pFrame->nCountVertex = nCountVertex;

        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);

        GXSetDrawSyncCallback(&frameDrawSyncCallback);

        for (i = 0; i < 8; i++) {
            GXSetTexCoordGen(ganNameTexCoord[i], GX_TG_MTX2x4, GX_TG_TEX0, ganNameTexMtx[i]);
        }

        GXSetScissor(0, 0, pFrame->anSizeX[FS_TARGET], pFrame->anSizeY[FS_TARGET]);
    }

    pFrame->iMatrixModel = 0;
    pFrame->nMode &= 0x9C1F0000;
    pFrame->nMode &= ~0x1C000000;
    pFrame->iHintProjection = -1;

    frameClearModes(pFrame);

    pFrame->nWidthLine = -1;
    pFrame->nCountLight = 0;

    frameDrawReset(pFrame, 0x47F2D);

    pFrame->nModeVtx = -1;
    pFrame->nAddressLoad = -1;
    return true;
}

bool frameEnd(Frame* pFrame) {
    Cpu* pCPU;
    s32 iHint;
    void* pData;

    pCPU = SYSTEM_CPU(gpSystem);

    if (gbFrameBegin) {
        OSReport("frameEnd: INTERNAL ERROR: Called when 'gbFrameBegin' is TRUE!\n");
    }
    gbFrameBegin = true;

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if (pFrame->aMatrixHint[iHint].nCount >= 0) {
            pFrame->aMatrixHint[iHint].nCount--;
        }
    }

    pFrame->nCountFrames++;
    gbFrameValid = true;

    if (pFrame->aBuffer[FBT_DEPTH].nAddress != 0) {
        pData = &sTempZBuf;

        GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
        GXSetTexCopyDst(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_Z16, GX_TRUE);
        GXCopyTex(pData, GX_FALSE);
        DCInvalidateRange(pData, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
    }

#if IS_OOT
    if (gpSystem->eTypeROM == SRT_DRMARIO && pFrame->bGrabbedFrame) {
        CopyCFB(TEMP_BUFFER);
        pFrame->bGrabbedFrame = false;
    }
#endif

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
    GXSetDrawDone();
    GXFlush();

    if (gpSystem->eTypeROM == SRT_ZELDA2) {
        pFrame->nHackCount = 0;
        pFrame->nFrameCounter++;
        pFrame->bBlurredThisFrame = false;
        pFrame->nFrameCIMGCalls = 0;
        pFrame->bUsingLens = false;
        pFrame->bModifyZBuffer = false;
#if IS_OOT
        pFrame->bOverrideDepth = false;
#endif

        pFrame->nLastFrameZSets = pFrame->nZBufferSets;
        pFrame->nZBufferSets = 0;
        pFrame->bPauseBGDrawn = false;

#if IS_OOT
        GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);

        if ((pFrame->bShrinking & 0xF) == 0) {
            pFrame->bShrinking &= ~0xFFFF;
        }
        pFrame->bShrinking &= ~0xFF;
        pFrame->bSnapShot = 0;
#else
        pFrame->bShrinking = 0;

        if ((u32)pFrame->bSnapShot & ~0xFFFF) {
            pFrame->bSnapShot |= 0x10;
        } else {
            pFrame->bSnapShot &= ~0xFFFF;
        }
#endif
    }

#if IS_OOT
    if (gpSystem->eTypeROM == SRT_DRMARIO) {
        pFrame->bBackBufferDrawn = false;
    }
#endif

    pCPU->gTree->kill_number = 0;
    return true;
}

bool _frameDrawRectangle(Frame* pFrame, u32 nColor, s32 nX, s32 nY, s32 nSizeX, s32 nSizeY) {
    s32 iY;
    s32 iX;
    u32* pnPixel;
    s32 nSizeTargetX = pFrame->anSizeX[FS_TARGET];

    nX = (nX + 1) & ~1;
    nSizeX = (nSizeX + 1) & ~1;
    if (DemoCurrentBuffer == DemoFrameBuffer1) {
        pnPixel = (u32*)((s16*)DemoFrameBuffer2 + (nY * nSizeTargetX) + nX);
    } else {
        pnPixel = (u32*)((s16*)DemoFrameBuffer1 + (nY * nSizeTargetX) + nX);
    }

    pnPixel = (u32*)((u8*)pnPixel + 0x40000000);

    for (iY = 0; iY < nSizeY; iY++) {
        for (iX = 0; iX < (nSizeX >> 1); iX++) {
            pnPixel[iX] = nColor;
        }
        pnPixel += (nSizeTargetX >> 1);
    }

    return true;
}

#if IS_OOT
// Variables from unused function ZeldaDrawFrameZTexture
static GXTexObj sFrameObj1_1562;
static GXTexObj sFrameObj2_1563;
#endif

void ZeldaDrawFrameNoBlend(Frame* pFrame, u16* pData) {
    Mtx matrix;
    u32 pad[8];
    static GXTexObj sFrameObj;

    frameDrawSetup2D(pFrame);
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevOp(0, 3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&sFrameObj, pData, N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sFrameObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sFrameObj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}

void ZeldaDrawFrameBlur(Frame* pFrame, u16* pData) {
    Mtx matrix;
    s32 pad[8];
    GXColor color;
    static GXTexObj sFrameObj;

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = pFrame->cBlurAlpha;

    frameDrawSetup2D(pFrame);
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&sFrameObj, pData, N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sFrameObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sFrameObj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-1.0f, -1.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH - 1, -1.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH - 1, N64_FRAME_HEIGHT - 1, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(-1.0f, N64_FRAME_HEIGHT - 1, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}

void ZeldaDrawFrame(Frame* pFrame, u16* pData) {
    Mtx matrix;
    u32 pad[8];
    GXColor color;
    static GXTexObj sFrameObj;

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = pFrame->cBlurAlpha;

    frameDrawSetup2D(pFrame);
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&sFrameObj, pData, N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sFrameObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sFrameObj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}

#if IS_OOT
// Variables from unused functions ConvertZ and ConvertCFB
static u32 line_1582[N64_FRAME_WIDTH / 4][4][4];
static u16 line_1606[N64_FRAME_WIDTH / 4][4][4];
#endif

static void CopyCFB(u16* srcP) {
    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_TRUE);
    DCInvalidateRange(srcP, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
    GXCopyTex(srcP, GX_FALSE);
    sCopyFrameSyncReceived = false;
    GXSetDrawSync(FRAME_SYNC_TOKEN);
    while (!sCopyFrameSyncReceived) {}
}

// non-matching for MM
void CopyAndConvertCFB(u16* srcP) {
    u16* dataEndP;
    s32 tile;
    s32 y;
    s32 x;
    u16 val;
    static u16 line[N64_FRAME_WIDTH / 4][4][4];

    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB5A3, GX_TRUE);
    DCInvalidateRange(srcP, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
    GXCopyTex(srcP, GX_FALSE);

    sCopyFrameSyncReceived = false;
    GXSetDrawSync(FRAME_SYNC_TOKEN);
    while (!sCopyFrameSyncReceived) {};

    dataEndP = srcP + N64_FRAME_WIDTH * N64_FRAME_HEIGHT;
    while (srcP < dataEndP) {
        xlHeapCopy(&line, srcP, sizeof(line));

        for (y = 0; y < 4; y++) {
            for (tile = 0; tile < N64_FRAME_WIDTH / 4; tile++) {
                for (x = 0; x < 4; x++, srcP++) {
                    val = line[tile][y][x];
                    *srcP = (val << 1) | 1;
                }
            }
        }
    }
}

#if IS_MM
static u16 line_1629[N64_FRAME_WIDTH / 4][4][4];
static LensTexture sLensTex;

void CopyZValue(u32* ptr) {
    GXSetCopyFilter(GX_FALSE, NULL, GX_FALSE, NULL);
    GXSetColorUpdate(GX_FALSE);
    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_Z24X8, GX_FALSE);
    DCInvalidateRange(ptr, GC_FRAME_WIDTH * GC_FRAME_HEIGHT * 4);
    GXCopyTex(ptr, GX_FALSE);
    GXPixModeSync();
    GXSetCopyFilter(rmode->aa, &rmode->sample_pattern[0], GX_TRUE, rmode->vfilter);
    GXSetColorUpdate(GX_TRUE);
}

// non-matching for MM
void frameCopyLensTexture(Frame* pFrame, Rectangle* pRectangle) {
    // Parameters
    // Frame* pFrame; // r30
    // struct __anon_0x2F75F* pRectangle; // r31

    // Local variables
    void* originalDataP; // r1+0x8

    // References
    // -> static struct LensTexture sLensTex;
    // -> struct _FRAME_TEXTURE* gpTexture[8];
    // -> f32 gTextureMatrix[8][3][4];

    memcpy(sLensTex.texMtx, gTextureMatrix[pRectangle->iTile], sizeof(Mtx));

    // var_r5 = sLensTex.texture;
    // var_r4 = gTextureMatrix[pRectangle->iTile] - 8;

    // s32 i;

    // for (i = 0; i < 12; i++) {

    // }

    // do {
    //     temp_r3 = var_r4->unk8;
    //     var_r4 += 8;
    //     var_r5 += 8;
    //     var_r5[2] = temp_r3;
    //     var_r5[1] = var_r4->unk4;
    // } while (var_ctr != 0);

    // var_r5[2] = var_r4->unk8;
    memcpy(sLensTex.lensTexture, OSPhysicalToCached(GXGetTexObjData(&sLensTex.texture.objectTexture)),
           sizeof(sLensTex.lensTexture));
    GXInitTexObjData(&sLensTex.texture.objectTexture, sLensTex.lensTexture);

    sLensTex.rS0 = pRectangle->rS;
    sLensTex.rS1 = N64_FRAME_WIDTH * pRectangle->rDeltaS + pRectangle->rS;
    sLensTex.rT0 = pRectangle->rT;
    sLensTex.rT1 = N64_FRAME_HEIGHT * pRectangle->rDeltaT + pRectangle->rT;
    sLensTex.alphaComp = pFrame->aColor[2].a;
}

// non-matching for MM
const GXColor color = {0, 0, 255, 255};
void WriteZValue(Frame* pFrame, u32* ptr) {
    // Parameters
    // Frame* pFrame; // r27
    // u32* ptr; // r28

    // Local variables
    s32 x; // r1+0x5C
    f32 matrix[3][4]; // r1+0x2C
    s32 pad[3];

    static GXTexObj texObj;

    // References
    // -> struct _GXRenderModeObj* rmode;
    // -> static struct LensTexture sLensTex;
    // -> static struct _GXTexObj texObj$1646;
    // -> enum _GXTexCoordID ganNameTexCoord[8];
    // -> u32 ganNameTexMtx[8];

    frameDrawSetup2D(pFrame);

    DCStoreRange(ptr, GC_FRAME_WIDTH * GC_FRAME_HEIGHT * 4);
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GXSetNumTevStages(2);
    GXSetNumTexGens(2);
    GXSetNumChans(0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXPeekZ(0, 0, (u32*)&x);

    if (x == 1) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    }

    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTexCoordGen2(ganNameTexCoord[1], GX_TG_MTX2x4, GX_TG_TEX1, ganNameTexMtx[1], GX_FALSE, 0x7D);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetColorUpdate(0U);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GREATER, sLensTex.alphaComp, GX_AOP_AND, GX_GREATER, sLensTex.alphaComp);
    GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetZCompLoc(GX_FALSE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, GX_MTX2x4);
    GXLoadTexMtxImm(matrix, 0x21, GX_MTX2x4);
    GXLoadTexMtxImm(sLensTex.texMtx, 0x21, GX_MTX2x4);
    GXInitTexObj(&texObj, ptr, GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_Z24X8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXLoadTexObj(&sLensTex.texture.objectTexture, GX_TEXMAP1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXTexCoord2f32(sLensTex.rS0, sLensTex.rT0);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXTexCoord2f32(sLensTex.rS1, sLensTex.rT0);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXTexCoord2f32(sLensTex.rS1, sLensTex.rT1);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXTexCoord2f32(sLensTex.rS0, sLensTex.rT1);
    GXEnd();

    GXPixModeSync();
    GXSetColorUpdate(1U);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0U);

    if ((u8)rmode->aa != 0) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    }

    GXSetTexCoordGen2(ganNameTexCoord[1], GX_TG_MTX2x4, GX_TG_TEX0, ganNameTexMtx[1], GX_FALSE, 0x7D);
    pFrame->nMode &= 0x0CC00000;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0xFFFFFFFF);
}
#endif

// non-matching for MM
static void ZeldaGreyScaleConvert(Frame* pFrame) {
    Mtx matrix;
    void* dataP;
    s32 pad[9];
    GXColor color;
    static GXTexObj sFrameObj;
    static u8 cAlpha = 15;

    dataP = DemoCurrentBuffer;
    color.r = 192;
    color.g = 161;
    color.b = 85;
    color.a = cAlpha;
    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_I8, GX_FALSE);
    GXCopyTex(dataP, GX_FALSE);
    GXPixModeSync();
    frameDrawSetup2D(pFrame);

    if (gHackCreditsColor) {
        GXSetNumTevStages(1);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        if (cAlpha < 255) {
            cAlpha += 20;
        }
    } else {
        GXSetNumTevStages(1);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&sFrameObj, dataP, GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sFrameObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sFrameObj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}

#if IS_OOT
// Variables from unused function ZeldaDrawFrameHiRes
static GXTexObj sFrameObj_1660;
#endif

// non-matching for MM
void ZeldaDrawFrameShrink(Frame* pFrame, s32 posX, s32 posY, s32 size) {
    Mtx matrix;
#if IS_OOT
    s32 pad;
#endif
    f32 nX0;
    f32 nX1;
    f32 nY0;
    f32 nY1;
    f32 scale;
    void* frameBuffer;
    GXColor color;
    static GXTexObj frameObj;

    frameBuffer = DemoCurrentBuffer;
    nX0 = posX;
    nY0 = posY;
    nX1 = N64_FRAME_WIDTH;
    nY1 = N64_FRAME_HEIGHT;

    nX0 *= 2.0f;
    nY0 *= 2.0f;
    switch (size) {
        case 0x435:
            scale = 0.95f;
            break;
        case 0x471:
            scale = 0.90f;
            break;
        case 0x4B4:
            scale = 0.85f;
            break;
        case 0x500:
            scale = 0.80f;
            break;
    }
    nX1 *= scale;
    nY1 *= scale;
    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(frameBuffer, GX_FALSE);
    GXPixModeSync();
    frameDrawSetup2D(pFrame);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXEnd();

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&frameObj, frameBuffer, GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&frameObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&frameObj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0, nY0, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX1, nY0, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX1, nY1, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0, nY1, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}

#if IS_MM
void ZeldaEraseCamera(void) {
    Frame* pFrame = SYSTEM_FRAME(gpSystem);

    DCInvalidateRange(pFrame->nCameraBuffer, 0x5000);
    memset(pFrame->nCameraBuffer, 0, 0x5000);
}
#endif

// non-matching for MM
void ZeldaDrawFrameCamera(Frame* pFrame, void* buffer) {
    Mtx matrix;
    GXColor color;
    f32 nX0;
    f32 nY0;
    f32 nX1;
    f32 nY1;
    f32 width;
    f32 height;

#if IS_MM
    s32 shrink;
#endif

    static GXTexObj frameObj;

    nX0 = 80.0f;
    nY0 = 31.0f;
    nX1 = 240.0f;
    nY1 = 143.0f;

#if IS_MM
    width = 160.0f;
    height = 112.0f;
    shrink = pFrame->bShrinking >> 16;

    if (shrink != 0) {
        switch (shrink) {
            case 0x435:
                nX0 = 88.0f;
                nY0 = 40.0f;
                nX1 = nX0 + (f32)(width * 0.9025);
                nY1 = nY0 + (f32)(height * 0.9025);
                break;
            case 0x471:
                nX0 = 96.0f;
                nY0 = 49.0f;
                nX1 = nX0 + (f32)(width * 0.81);
                nY1 = nY0 + (f32)(height * 0.81);
                break;
            case 0x4B4:
                nX0 = 102.0f;
                nY0 = 56.0f;
                nX1 = nX0 + (f32)(width * 0.7225);
                nY1 = nY0 + (f32)(height * 0.7225);
                break;
            case 0x500:
                nX0 = 111.0f;
                nY0 = 64.0f;
                nX1 = nX0 + (f32)(width * 0.61);
                nY1 = nY0 + (f32)(height * 0.64);
                break;
            default:
                break;
        }
    }
#endif

    frameDrawSetup2D(pFrame);
    color.r = 255;
    color.g = 167;
    color.b = 176;
    color.a = 255;
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&frameObj, buffer, ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&frameObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&frameObj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0, nY0, 0.0f);
    GXTexCoord2f32(0.0f, 0.015625f);
    GXPosition3f32(nX1, nY0, 0.0f);
    GXTexCoord2f32(1.0f, 0.015625f);
    GXPosition3f32(nX1, nY1, 0.0f);
    GXTexCoord2f32(1.0f, 0.859375f);
    GXPosition3f32(nX0, nY1, 0.0f);
    GXTexCoord2f32(0.0f, 0.859375f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}

bool frameHackTIMG_Zelda(Frame* pFrame, u64** pnGBI, u32* pnCommandLo, u32* pnCommandHi) {
    u32 i;
    static s32 sCommandCodes[] = {
        0xF5500000, 0x07080200, 0xE6000000, 0x00000000, 0xF3000000, 0x073BF01A, 0xE7000000, 0x00000000,
    };

    if ((*pnCommandLo == 0x0F000000) && (*pnCommandHi == 0xFD500000)) {
        u32* tmp = (u32*)*pnGBI;
        for (i = 0; i < ARRAY_COUNT(sCommandCodes); i++) {
            if (tmp[i] != sCommandCodes[i]) {
                break;
            }
        }

        if (i == ARRAY_COUNT(sCommandCodes)) {
            ZeldaGreyScaleConvert(pFrame);
            sSpecialZeldaHackON = 1;
        }
    }

    if ((sSpecialZeldaHackON != 0) && ((*pnCommandLo & 0xFF000000) != 0x0F000000)) {
        sSpecialZeldaHackON = 0;
    }

    if (sSrcBuffer == SEGMENT_ADDRESS(SYSTEM_RSP(gpSystem), *pnCommandLo)) {
        *pnCommandLo = sDestinationBuffer;
        *pnGBI += 8;
    }

    return true;
}

bool frameHackCIMG_Zelda2(Frame* pFrame, FrameBuffer* pBuffer, u64* pnGBI, u32 nCommandLo, u32 nCommandHi) {
#if IS_OOT
    u32 i;
    s32 pad[2];
    static s32 sCommandCodes[] = {
        0xE7000000, 0x00000000, 0xEF000CF0, 0x0F0A4004, 0xFB000000,
        0xFFFFFFFF, 0xFC12FE25, 0xFFFFFBFD, 0xFF10013F, 0x804096C0,
    };
    static s32 sCommandCodes2[] = {
        0xE7000000, 0x00000000, 0xE7000000, 0x00000000, 0xEF000CF0,
        0x0F0A0004, 0xFCFFFFFF, 0xFFFCFE7F, 0xFF88013F, 0x80784600,
    };
#else
    u32 i;
    static s32 sCommandCodes[] = {
        0xE7000000, 0x00000000, 0xEF000CF0, 0x0F0A4004, 0xFB000000,
        0xFFFFFFFF, 0xFC12FE25, 0xFFFFFBFD, 0xFF10013F, 0x00000000,
    };
    static s32 sCommandCodes2[] = {
        0xE7000000, 0x00000000, 0xEF000CF0, 0x0F0A4004, 0xFB000000,
        0xFFFFFFFF, 0xFC12FE25, 0xFFFFFBFD, 0xFF10013F, 0x00000000,
    };
#endif

    static s32 nLastFrame;
    static s32 nCopyFrame;

    if (pBuffer->nAddress == pFrame->aBuffer[FBT_DEPTH].nAddress) {
        pFrame->nHackCount += 1;
    }

    pFrame->nFrameCIMGCalls += 1;

    if ((s32)pFrame->nHackCount > 1) {
        u32* pGBI = (u32*)&pnGBI[-5];

#if IS_OOT
        for (i = 0; i < ARRAY_COUNT(sCommandCodes); i++) {
            if (pGBI[i] != sCommandCodes[i] && !(i == 9 && (pGBI[9] == 0x80383C80 || pGBI[9] == 0x80383AC0))) {
                break;
            }
        }
#else
        for (i = 0; i < ARRAY_COUNT(sCommandCodes); i++) {
            if (pGBI[i] != sCommandCodes[i] && !(i == 9 && pGBI[9] == 0x8078F800)) {
                break;
            }
        }
#endif

        if (i == ARRAY_COUNT(sCommandCodes)) {
            if (!pFrame->bHackPause) {
                nCopyFrame = 1;
            }
        } else {
            pFrame->bPauseThisFrame = false;
        }
    }

    if ((s32)nCopyFrame != 0) {
        u32* pGBI = (u32*)&pnGBI[-5];

#if IS_OOT
        for (i = 0; i < ARRAY_COUNT(sCommandCodes2); i++) {
            if (pGBI[i] != sCommandCodes2[i]) {
                break;
            }
        }
#else
        for (i = 0; i < ARRAY_COUNT(sCommandCodes2); i++) {
            if (!(i == 9 && pGBI[9] == 0x8078F800) && pGBI[i] != sCommandCodes2[i]) {
                break;
            }
        }
#endif

        if (i == ARRAY_COUNT(sCommandCodes2)) {
            if (!pFrame->bHackPause) {
#if IS_OOT
                for (i = 0; i < N64_FRAME_WIDTH * N64_FRAME_HEIGHT; i++) {
                    COPY_BUFFER[i] = TEMP_BUFFER[i];
                }
#else
                memcpy(pFrame->nCopyBuffer, pFrame->nTempBuffer, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
#endif
            }
            pFrame->bHackPause = true;
            pFrame->nHackCount = 0;
            pFrame->bPauseThisFrame = 1;
            nCopyFrame = 0;
        } else {
            pFrame->bPauseThisFrame = false;
        }
    }

    if (pFrame->bHackPause) {
        if ((pFrame->nFrameCounter - nLastFrame) >= 2) {
            nLastFrame = pFrame->nFrameCounter;
            gNoSwapBuffer = true;
        }
        pFrame->bHackPause = false;
    } else {
        if (pFrame->bShrinking & 0xFFFF) {
            if (pFrame->bBlurOn) {
                pFrame->bShrinking |= 0x10;
            }
            if (!pFrame->bBlurOn && (pFrame->bShrinking & 0xF0) == 0) {
                CopyCFB(TEMP_BUFFER);
            }
        } else if (!pFrame->bBlurOn) {
            CopyCFB(TEMP_BUFFER);
        }
    }

#if IS_OOT
    if (((pBuffer->nAddress == 0x42EEC0) || (pBuffer->nAddress == 0x3A9480) || (pBuffer->nAddress == 0x3A92C0)) &&
        pFrame->bBlurOn && !pFrame->bBlurredThisFrame) {
        ZeldaDrawFrameBlur(pFrame, TEMP_BUFFER);
        CopyCFB(TEMP_BUFFER);
        pFrame->bBlurredThisFrame = true;
    }
#else
    if (pBuffer->nAddress == 0x7B5000 && pFrame->bBlurOn && !pFrame->bBlurredThisFrame) {
        ZeldaDrawFrameBlur(pFrame, TEMP_BUFFER);
        CopyCFB(TEMP_BUFFER);
        pFrame->bBlurredThisFrame = true;
    }
#endif

    return true;
}

// non-matching for MM
bool frameHackCIMG_Zelda(Frame* pFrame, FrameBuffer* pBuffer, u64* pnGBI, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32 low2;
    u32 high2;
    u16* srcP;
    static u16 tempLine[ZELDA_PAUSE_EQUIP_PLAYER_WIDTH / 4][4][4];

    for (i = 0; i < sNumAddr; i++) {
        if (nCommandLo == sConstantBufAddr[i]) {
            break;
        }
    }

    if (pBuffer->nAddress == pFrame->aBuffer[FBT_DEPTH].nAddress && pBuffer->nWidth == N64_FRAME_WIDTH) {
        low2 = pnGBI[1];
        high2 = pnGBI[1] >> 32;
        if (high2 == 0xFD10013F) {
            low2 = SYSTEM_RSP(gpSystem)->anBaseSegment[(low2 >> 24) & 0xF] + (low2 & 0xFFFFFF);
            if (!ramGetBuffer(SYSTEM_RAM(gpSystem), (void**)&srcP, low2, NULL)) {
                return false;
            }
            sDestinationBuffer = low2;
            sSrcBuffer = pBuffer->nAddress;
            CopyAndConvertCFB(srcP);
            gnCountMapHack = -1;
            gNoSwapBuffer = true;
        }
    }

    if (i >= sNumAddr) {
        if (sNumAddr < ARRAY_COUNT(sConstantBufAddr)) {
            sConstantBufAddr[sNumAddr++] = nCommandLo;
            sConstantBufAddr[sNumAddr++] =
                nCommandLo + ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT * sizeof(u16);
        } else if (pBuffer->nWidth == ZELDA_PAUSE_EQUIP_PLAYER_WIDTH) {
            gNoSwapBuffer = true;
            if (pBuffer->nSize == 2) {
                u16* val = pBuffer->pData;
                u16* valEnd = val + ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT;
                s32 tile;
                s32 y;
                s32 x;

                GXSetTexCopySrc(0, 0, ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * 2, ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT * 2);
                GXSetTexCopyDst(ZELDA_PAUSE_EQUIP_PLAYER_WIDTH, ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT, GX_TF_RGB5A3, GX_TRUE);
                DCInvalidateRange(pBuffer->pData,
                                  ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT * sizeof(u16));
                GXCopyTex(pBuffer->pData, GX_FALSE);

                sCopyFrameSyncReceived = false;
                GXSetDrawSync(FRAME_SYNC_TOKEN);
                while (!sCopyFrameSyncReceived) {}

                while (val < valEnd) {
                    xlHeapCopy(tempLine, val, sizeof(tempLine));

                    for (y = 0; y < 4; y++) {
                        for (tile = 0; tile < ZELDA_PAUSE_EQUIP_PLAYER_WIDTH / 4; tile++) {
                            for (x = 0; x < 4; x++, val++) {
                                *val = (tempLine[tile][y][x] << 1) | 1;
                            }
                        }
                    }
                }
            } else {
                u8* val = pBuffer->pData;
                u8* valEnd = val + ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT;

                // bug? val incremented twice per iteration
                for (; val < valEnd; val++) {
                    *(val++) = 0;
                }
            }
        }
    }

    PAD_STACK();
    return true;
}

bool frameHackCIMG_Zelda2_Shrink(Rdp* pRDP, Frame* pFrame, u64** ppnGBI) {
    u64* pnGBI;
    s32 count;
    s32 nAddress;
    u32 nCommandLo;
    u32 nCommandHi;
    Rsp* pRSP;
    s32 done;
    uObjBg bg;
    static s32 GBIcode[] = {
        0xED000000,
        0x0B000000,
        0x0A000000,
    };

    pnGBI = *ppnGBI;
    for (count = 0; count < ARRAY_COUNT(GBIcode); count++) {
        nCommandHi = GBI_COMMAND_HI(pnGBI + count);
        if (GBIcode[count] != nCommandHi) {
            break;
        }
    }

    if (count == ARRAY_COUNT(GBIcode)) {
        pnGBI = pnGBI + count;
        pRSP = SYSTEM_RSP(pRDP->pHost);
        done = 0;

        while (true) {
            nCommandHi = GBI_COMMAND_HI(pnGBI);
            if (nCommandHi == 0x09000000) {
                nCommandLo = GBI_COMMAND_LO(pnGBI);
                nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                rspFillObjBgScale(pRSP, nAddress, &bg);
                pFrame->bShrinking |= 1;
                pFrame->bShrinking |= 0x100;

#if IS_OOT
                if (((u32)pFrame->bShrinking & ~0xFFFF) == 0)
#endif
                {
                    pFrame->bShrinking |= bg.b.tmemW << 16;
                }
                ZeldaDrawFrameShrink(pFrame, bg.b.frameX >> 2, bg.b.frameY >> 2, bg.b.tmemW);
                done = 1;
            }

            if (done && nCommandHi == 0xDF000000) {
                break;
            }
            pnGBI++;
        };
    } else {
        return false;
    }

    *ppnGBI = ++pnGBI;
    return true;
}

static inline void ZeldaCopyCamera(u16* buffer) {
    GXSetTexCopySrc(ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT - 10, ZELDA2_CAMERA_WIDTH * 2, ZELDA2_CAMERA_HEIGHT * 2);
    GXSetTexCopyDst(ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT, GX_TF_I8, GX_TRUE);
    DCInvalidateRange(buffer, CAMERA_BUFFER_SIZE);
    GXCopyTex(buffer, GX_FALSE);
    GXPixModeSync();
}

bool frameHackCIMG_Zelda2_Camera(Frame* pFrame, FrameBuffer* pBuffer, u32 nCommandHi, u32 nCommandLo) {
    if (pBuffer != NULL) {
#if IS_OOT
        if (pBuffer->nAddress == 0x00784600) {
            pFrame->bSnapShot |= 0x10;
            return true;
        }
#endif

        if ((pFrame->bSnapShot & 0xF00) != 0) {
            ZeldaDrawFrameCamera(pFrame, CAMERA_BUFFER);
            pFrame->bSnapShot &= ~0xF00;
            return true;
        }

        return false;
    }

    if ((nCommandHi == 0xF63EC25C) && (nCommandLo == 0x00118058)) {
        pFrame->bSnapShot |= 1;

        // possible bug? probably meant to be ``pFrame->bSnapShot & 0xF00``
        if ((pFrame->bSnapShot & 0xF0) != 0) {
            ZeldaCopyCamera(CAMERA_BUFFER);
            pFrame->bSnapShot &= ~0xF00;
        }

        return true;
    }

    return false;
}

#if IS_OOT
void PanelDrawBG8(u16* BG, u16* LUT, u8* bitmap, s32 sizeX, s32 sizeY, s32 posX, s32 posY, bool flip) {
    s32 i;
    s32 j;
    u16 color;
    s32 pad[3];

    for (i = 0; i < sizeY; i++) {
        for (j = 0; j < sizeX; j++) {
            color = LUT[bitmap[i * sizeX + j]];
            if (color & 1) {
                if (!flip) {
                    BG[(posY + i) * N64_FRAME_WIDTH + posX + j] = color;
                } else {
                    BG[(posY + i) * N64_FRAME_WIDTH + posX + (sizeX - j)] = color;
                }
            }
        }
    }

    NO_INLINE();
}

void PanelDrawBG16(u16* BG, u16* bitmap, s32 sizeX, s32 sizeY, s32 posX, s32 posY, bool flip) {
    s32 i;
    s32 j;
    u16 color;
    s32 pad[2];

    for (i = 0; i < sizeY; i++) {
        for (j = 0; j < sizeX; j++) {
            color = bitmap[i * sizeX + j];
            if (color & 1) {
                if (!flip) {
                    BG[(posY + i) * N64_FRAME_WIDTH + posX + j] = color;
                } else {
                    BG[(posY + i) * N64_FRAME_WIDTH + posX + (sizeX - j)] = color;
                }
            }
        }
    }

    NO_INLINE();
}

void PanelDrawFR3D(u16* FR, u16* LUT, u8* bitmap, s32 sizeX, s32 sizeY, s32 posX, s32 posY, bool first) {
    s32 i;
    s32 j;
    u16 color;
    s32 pad[3];

    for (i = 0; i < sizeY; i++) {
        for (j = 0; j < sizeX; j++) {
            color = LUT[bitmap[i * sizeX + j]];
            if (first) {
                if (color == 0x6D3F) {
                    color = 0x6D3E;
                }
                FR[(posY + i) * N64_FRAME_WIDTH + posX + j] = color;
            } else if (color & 1) {
                FR[(posY + i) * N64_FRAME_WIDTH + posX + j] = color;
            }
        }
    }
}

bool frameHackTIMG_Panel(Frame* pFrame, FrameBuffer* pBuffer) {
    if (!pFrame->bFrameOn) {
        return false;
    }

    if (pBuffer->nAddress >= 0x358800 && pBuffer->nAddress <= 0x37B800) {
        if (pBuffer->nFormat == 0 && pBuffer->nWidth == 1 && pBuffer->nSize == 2) {
            pBuffer->pData = TEMP_BUFFER + ((((s32)(pBuffer->nAddress + 0xFFCA7800) / 2) + 0x8C0));
            return true;
        }
        pFrame->bFrameOn = false;
        return false;
    }

    return false;
}

bool frameHackCIMG_Panel(Rdp* pRDP, Frame* pFrame, FrameBuffer* pBuffer, u64** ppnGBI) {
    Rsp* pRSP;
    u64* pnGBI;
    s32 count;
    s32 nAddress;
    s32 sizeX;
    s32 posX;
    u32 nCommandLo;
    u32 nCommandHi;
    u16* BG;
    u16* FR;
    u16* pLUT;
    u16* pBitmap16;
    u8* pBitmap8;
    s32 pad1[10];
    static s32 GBIcode2D2[] = {
        0xB9000000, 0xBA000000, 0xE7000000, 0xBA000000, 0xC1000000, 0xE7000000, 0x02000000,
    };
    static s32 GBIcode3D1[] = {
        0xBA000000, 0xFC000000, 0xB9000000, 0xBA000000, 0xB9000000,
    };
    static s32 GBIcode3D2[] = {
        0xE7000000, 0xBA000000, 0xFC000000, 0xB9000000, 0xBA000000, 0xB9000000,
    };

    pRSP = SYSTEM_RSP(pRDP->pHost);
    pnGBI = *ppnGBI;

    if (pBuffer->nAddress == 0x358800) {
        s32 iTile;
        s32 nCount;
        Rectangle rect;

        pFrame->bFrameOn = true;
        FR = TEMP_BUFFER;
        pBuffer = &pFrame->aBuffer[FBT_IMAGE];

        nCommandHi = GBI_COMMAND_HI(&pnGBI[7]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[7]);
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[11]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[11]);
        iTile = (nCommandLo >> 24) & 7;
        nCount = (nCommandLo >> 14) & 0x3FF;
        if (!frameLoadTLUT(pFrame, nCount, iTile)) {
            return false;
        }
        pLUT = pFrame->aBuffer[FBT_IMAGE].pData;

        nCommandHi = GBI_COMMAND_HI(&pnGBI[16]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[16]);
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[18]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[18]);
        iTile = (nCommandLo >> 24) & 0x7;
        pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
        pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
        pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
        pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
        pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
        pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
        pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
        if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
            return false;
        }
        pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
        pBitmap8 = pFrame->aBuffer[FBT_IMAGE].pData;
        PanelDrawFR3D(FR, pLUT, pBitmap8, N64_FRAME_WIDTH, N64_FRAME_HEIGHT - 8, 0, 7, true);

        pnGBI += 20;
        do {
            nCommandHi = GBI_COMMAND_HI(pnGBI);
            pnGBI++;
        } while ((nCommandHi & 0xFF000000) != 0xBA000000);

        nCommandHi = GBI_COMMAND_HI(pnGBI);
        nCommandLo = GBI_COMMAND_LO(pnGBI);
        pBuffer = &pFrame->aBuffer[FBT_IMAGE];
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[4]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[4]);
        iTile = (nCommandLo >> 24) & 7;
        nCount = (nCommandLo >> 14) & 0x3FF;
        if (!frameLoadTLUT(pFrame, nCount, iTile)) {
            return false;
        }
        pLUT = pFrame->aBuffer[FBT_IMAGE].pData;

        pnGBI += 5;
        while (true) {
            nCommandHi = GBI_COMMAND_HI(pnGBI);
            nCommandLo = GBI_COMMAND_LO(pnGBI);
            if ((nCommandHi & 0xFF000000) == 0xFD000000) {
                pBuffer->nFormat = (nCommandHi >> 21) & 7;
                pBuffer->nSize = (nCommandHi >> 19) & 3;
                pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
                nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
                if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
                    return false;
                }

                nCommandLo = GBI_COMMAND_LO(&pnGBI[2]);
                nCommandHi = GBI_COMMAND_HI(&pnGBI[2]);
                iTile = (nCommandLo >> 24) & 7;
                pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
                pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
                pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
                pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
                pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
                pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
                pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
                pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
                pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
                if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
                    return false;
                }
                pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
                pBitmap8 = pFrame->aBuffer[FBT_IMAGE].pData;

                nCommandHi = GBI_COMMAND_HI(&pnGBI[4]);
                nCommandLo = GBI_COMMAND_LO(&pnGBI[4]);
                rect.nX0 = (nCommandLo >> 12) & 0xFFF;
                rect.nY0 = nCommandLo & 0xFFF;
                rect.nX1 = (nCommandHi >> 12) & 0xFFF;
                rect.nY1 = nCommandHi & 0xFFF;
                sizeX = (rect.nX1 - rect.nX0) >> 2;
                if (sizeX % 32 != 0) {
                    sizeX = ((sizeX / 32) + 1) * 32;
                }
                PanelDrawFR3D(FR, pLUT, pBitmap8, sizeX, (rect.nY1 - rect.nY0) >> 2, rect.nX0 >> 2, (rect.nY0 >> 2) + 7,
                              false);
            }

            nCommandHi = GBI_COMMAND_HI(pnGBI);
            pnGBI++;
            if ((nCommandHi & 0xFF000000) == 0xBA000000) {
                while (true) {
                    nCommandHi = GBI_COMMAND_HI(pnGBI);
                    if ((nCommandHi & 0xFF000000) == 0xFD000000) {
                        if ((GBI_COMMAND_HI(&pnGBI[4]) & 0xFF000000) == 0xF0000000) {
                            nCommandLo = GBI_COMMAND_LO(pnGBI);

                            pBuffer = &pFrame->aBuffer[FBT_IMAGE];
                            pBuffer->nFormat = (nCommandHi >> 21) & 7;
                            pBuffer->nSize = (nCommandHi >> 19) & 3;
                            pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
                            nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
                            if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
                                return false;
                            }

                            nCommandHi = GBI_COMMAND_HI(&pnGBI[4]);
                            nCommandLo = GBI_COMMAND_LO(&pnGBI[4]);
                            iTile = (nCommandLo >> 24) & 7;
                            nCount = (nCommandLo >> 14) & 0x3FF;
                            if (!frameLoadTLUT(pFrame, nCount, iTile)) {
                                return false;
                            }
                            pLUT = pFrame->aBuffer[FBT_IMAGE].pData;
                        } else {
                            nCommandHi = GBI_COMMAND_HI(pnGBI);
                            nCommandLo = GBI_COMMAND_LO(pnGBI);

                            pBuffer = &pFrame->aBuffer[FBT_IMAGE];
                            pBuffer->nFormat = (nCommandHi >> 21) & 7;
                            pBuffer->nSize = (nCommandHi >> 19) & 3;
                            pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
                            nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
                            if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
                                return false;
                            }

                            nCommandHi = GBI_COMMAND_HI(&pnGBI[2]);
                            nCommandLo = GBI_COMMAND_LO(&pnGBI[2]);
                            iTile = (nCommandLo >> 24) & 7;
                            pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
                            pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
                            pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
                            pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
                            pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
                            pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
                            pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
                            pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
                            pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
                            if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
                                return false;
                            }
                            pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
                            pBitmap8 = pFrame->aBuffer[FBT_IMAGE].pData;

                            nCommandLo = GBI_COMMAND_LO(&pnGBI[4]);
                            nCommandHi = GBI_COMMAND_HI(&pnGBI[4]);
                            rect.nX0 = (nCommandLo >> 12) & 0xFFF;
                            rect.nY0 = nCommandLo & 0xFFF;
                            rect.nX1 = (nCommandHi >> 12) & 0xFFF;
                            rect.nY1 = nCommandHi & 0xFFF;
                            sizeX = (rect.nX1 - rect.nX0) >> 2;
                            if (sizeX % 32 != 0) {
                                sizeX = ((sizeX / 32) + 1) * 32;
                            }
                            posX = rect.nX0 >> 2;
                            if (posX == 252 && (rect.nY0 >> 2) == 170 && sizeX == 64) {
                                sizeX = 96;
                            }
                            PanelDrawFR3D(FR, pLUT, pBitmap8, sizeX, (rect.nY1 - rect.nY0) >> 2, posX,
                                          (rect.nY0 >> 2) + 7, false);
                        }
                    }

                    nCommandHi = GBI_COMMAND_HI(pnGBI);
                    pnGBI++;
                    if ((nCommandHi & 0xFF000000) == 0x06000000) {
                        *ppnGBI = pnGBI;
                        return true;
                    }
                }
            }
        }
    }

    for (count = 0; count < ARRAY_COUNT(GBIcode3D1); count++) {
        if ((GBI_COMMAND_HI(&pnGBI[count]) & 0xFF000000) != GBIcode3D1[count]) {
            break;
        }
    }

    if (count == ARRAY_COUNT(GBIcode3D1)) {
        Tile* pTile;
        s32 iTile;
        s32 nCount;

        *ppnGBI = &pnGBI[count];
        pnGBI = *ppnGBI;
        nCommandHi = GBI_COMMAND_HI(pnGBI);
        nCommandLo = GBI_COMMAND_LO(pnGBI);
        while (true) {
            if (nCommandHi != 0xFF10013F || nCommandLo != 0x80245D00) {
                switch (nCommandHi & 0xFF000000) { /* irregular */
                    case 0xFD000000:
                        pBuffer = &pFrame->aBuffer[FBT_IMAGE];
                        pBuffer->nFormat = (nCommandHi >> 21) & 7;
                        pBuffer->nSize = (nCommandHi >> 19) & 3;
                        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
                        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
                        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
                            return false;
                        }
                        break;
                    case 0xF5000000:
                        iTile = (nCommandLo >> 24) & 7;
                        pTile = &pFrame->aTile[iTile];
                        pTile->nSize = (nCommandHi >> 19) & 3;
                        pTile->nTMEM = nCommandHi & 0x1FF;
                        pTile->iTLUT = (nCommandLo >> 20) & 0xF;
                        pTile->nSizeX = (nCommandHi >> 9) & 0x1FF;
                        pTile->nFormat = (nCommandHi >> 21) & 7;
                        pTile->nMaskS = (nCommandLo >> 4) & 0xF;
                        pTile->nMaskT = (nCommandLo >> 14) & 0xF;
                        pTile->nModeS = (nCommandLo >> 8) & 3;
                        pTile->nModeT = (nCommandLo >> 18) & 3;
                        pTile->nShiftS = nCommandLo & 0xF;
                        pTile->nShiftT = (nCommandLo >> 10) & 0xF;
                        pTile->nCodePixel = pFrame->nCodePixel;
                        pFrame->lastTile = iTile;
                        frameDrawReset(pFrame, 1);
                        break;
                    case 0xF4000000:
                        iTile = (nCommandLo >> 24) & 7;
                        pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
                        pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
                        pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
                        pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
                        pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
                        pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
                        pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
                        pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
                        pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
                        if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
                            return false;
                        }
                        pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
                        break;
                    case 0xF3000000:
                        iTile = (nCommandLo >> 24) & 7;
                        pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
                        pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
                        pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
                        pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
                        pFrame->n2dLoadTexType = G_OBJLT_TXTRBLOCK;
                        if (!frameLoadTMEM(pFrame, FLT_BLOCK, iTile)) {
                            return false;
                        }
                        break;
                    case 0xF0000000:
                        iTile = (nCommandLo >> 24) & 7;
                        nCount = (nCommandLo >> 14) & 0x3FF;
                        if (!frameLoadTLUT(pFrame, nCount, iTile)) {
                            return false;
                        }
                        break;
                    case 0xF2000000:
                        iTile = (nCommandLo >> 24) & 7;
                        pTile = &pFrame->aTile[iTile];
                        pTile->nX0 = (nCommandHi >> 12) & 0xFFF;
                        pTile->nY0 = nCommandHi & 0xFFF;
                        pTile->nX1 = (nCommandLo >> 12) & 0xFFF;
                        pTile->nY1 = nCommandLo & 0xFFF;
                        frameDrawReset(pFrame, 1);
                        break;
                    case 0xE4000000:
                    default:
                        break;
                }
                nCommandHi = GBI_COMMAND_HI(pnGBI);
                nCommandLo = GBI_COMMAND_LO(pnGBI);
                pnGBI++;
            } else {
                break;
            }
        }

        *ppnGBI = pnGBI;
        return true;
    }

    for (count = 0; count < ARRAY_COUNT(GBIcode3D2); count++) {
        if ((GBI_COMMAND_HI(&pnGBI[count]) & 0xFF000000) != GBIcode3D2[count]) {
            break;
        }
    }

    if (count == ARRAY_COUNT(GBIcode3D2)) {
        s32 iTile;
        s32 nCount;
        Rectangle rect;

        nCommandHi = GBI_COMMAND_HI(&pnGBI[10]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[10]);
        BG = pBuffer->pData;
        pBuffer = &pFrame->aBuffer[FBT_IMAGE];
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[12]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[12]);
        iTile = (nCommandLo >> 24) & 7;
        pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
        pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
        pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
        pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
        pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
        pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
        pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
        if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
            return false;
        }
        pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
        pBitmap16 = pFrame->aBuffer[FBT_IMAGE].pData;

        nCommandHi = GBI_COMMAND_HI(&pnGBI[14]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[14]);
        rect.nX0 = (nCommandLo >> 12) & 0xFFF;
        rect.nY0 = nCommandLo & 0xFFF;
        rect.nX1 = (nCommandHi >> 12) & 0xFFF;
        rect.nY1 = nCommandHi & 0xFFF;
        PanelDrawBG16(BG, pBitmap16, ((rect.nX1 - rect.nX0) >> 2) + 1, ((rect.nY1 - rect.nY0) >> 2) + 1, rect.nX0 >> 2,
                      rect.nY0 >> 2, true);

        nCommandHi = GBI_COMMAND_HI(&pnGBI[20]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[20]);
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[22]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[22]);
        iTile = (nCommandLo >> 24) & 7;
        pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
        pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
        pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
        pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
        pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
        pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
        pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
        if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
            return false;
        }
        pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
        pBitmap16 = pFrame->aBuffer[FBT_IMAGE].pData;

        nCommandHi = GBI_COMMAND_HI(&pnGBI[24]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[24]);
        rect.nX0 = (nCommandLo >> 12) & 0xFFF;
        rect.nY0 = nCommandLo & 0xFFF;
        rect.nX1 = (nCommandHi >> 12) & 0xFFF;
        rect.nY1 = nCommandHi & 0xFFF;
        PanelDrawBG16(BG, pBitmap16, ((rect.nX1 - rect.nX0) >> 2) + 1, ((rect.nY1 - rect.nY0) >> 2) + 1, rect.nX0 >> 2,
                      rect.nY0 >> 2, false);

        nCommandHi = GBI_COMMAND_HI(&pnGBI[29]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[29]);
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[33]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[33]);
        iTile = (nCommandLo >> 24) & 7;
        nCount = (nCommandLo >> 14) & 0x3FF;
        if (!frameLoadTLUT(pFrame, nCount, iTile)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[38]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[38]);
        pLUT = pFrame->aBuffer[FBT_IMAGE].pData;
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[40]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[40]);
        iTile = (nCommandLo >> 24) & 7;
        pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
        pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
        pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
        pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
        pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
        pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
        pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
        if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
            return false;
        }
        pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
        pBitmap8 = pFrame->aBuffer[FBT_IMAGE].pData;

        nCommandHi = GBI_COMMAND_HI(&pnGBI[42]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[42]);
        rect.nX1 = (nCommandLo >> 12) & 0xFFF;
        rect.nY1 = nCommandLo & 0xFFF;
        PanelDrawBG8(BG, pLUT, pBitmap8, 128, 192, rect.nX1 >> 2, rect.nY1 >> 2, false);

        pnGBI += 45;
        do {
            nCommandHi = GBI_COMMAND_HI(pnGBI);
            pnGBI++;
        } while ((nCommandHi & 0xFF000000) != 0xBA000000);

        nCommandHi = GBI_COMMAND_HI(pnGBI);
        nCommandLo = GBI_COMMAND_LO(pnGBI);
        pBuffer = &pFrame->aBuffer[FBT_IMAGE];
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[4]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[4]);
        iTile = (nCommandLo >> 24) & 7;
        nCount = (nCommandLo >> 14) & 0x3FF;
        if (!frameLoadTLUT(pFrame, nCount, iTile)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[9]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[9]);
        pLUT = pFrame->aBuffer[FBT_IMAGE].pData;
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[11]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[11]);
        iTile = (nCommandLo >> 24) & 7;
        pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
        pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
        pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
        pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
        pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
        pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
        pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
        if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
            return false;
        }
        pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
        pBitmap8 = pFrame->aBuffer[FBT_IMAGE].pData;

        nCommandHi = GBI_COMMAND_HI(&pnGBI[13]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[13]);
        rect.nX1 = (nCommandLo >> 12) & 0xFFF;
        rect.nY1 = nCommandLo & 0xFFF;
        PanelDrawBG8(BG, pLUT, pBitmap8, 128, 192, (rect.nX1 >> 2) - 20, rect.nY1 >> 2, true);

        pnGBI += 16;
        do {
            nCommandHi = GBI_COMMAND_HI(pnGBI);
            pnGBI++;
        } while ((nCommandHi & 0xFF000000) != 0xBA000000);

        nCommandHi = GBI_COMMAND_HI(pnGBI);
        nCommandLo = GBI_COMMAND_LO(pnGBI);
        pBuffer = &pFrame->aBuffer[FBT_IMAGE];
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[4]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[4]);
        iTile = (nCommandLo >> 24) & 7;
        nCount = (nCommandLo >> 14) & 0x3FF;
        if (!frameLoadTLUT(pFrame, nCount, iTile)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[9]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[9]);
        pLUT = pFrame->aBuffer[FBT_IMAGE].pData;
        pBuffer->nFormat = (nCommandHi >> 21) & 7;
        pBuffer->nSize = (nCommandHi >> 19) & 3;
        pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
        nAddress = pBuffer->nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
        if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[11]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[11]);
        iTile = (nCommandLo >> 24) & 7;
        pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
        pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
        pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
        pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
        pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
        pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
        pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
        pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
        if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
            return false;
        }
        pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
        pBitmap8 = pFrame->aBuffer[FBT_IMAGE].pData;

        nCommandHi = GBI_COMMAND_HI(&pnGBI[13]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[13]);
        rect.nX1 = (nCommandLo >> 12) & 0xFFF;
        rect.nY1 = nCommandLo & 0xFFF;
        PanelDrawBG8(BG, pLUT, pBitmap8, 64, 72, rect.nX1 >> 2, rect.nY1 >> 2, false);

        pnGBI += 16;
        do {
            nCommandHi = GBI_COMMAND_HI(pnGBI);
            pnGBI++;
        } while ((nCommandHi & 0xFF000000) != 0xBA000000);

        *ppnGBI = pnGBI;
        return true;
    }

    for (count = 0; count < ARRAY_COUNT(GBIcode2D2); count++) {
        if ((GBI_COMMAND_HI(&pnGBI[count]) & 0xFF000000) != GBIcode2D2[count]) {
            break;
        }
    }

    if (count == ARRAY_COUNT(GBIcode2D2)) {
        uObjBg bg;
        uObjTxtr objTxtr;
        u32 nLoadType;
        FrameBuffer* pBG;
        s32 pad2[6];

        nCommandHi = GBI_COMMAND_HI(&pnGBI[4]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[4]);
        BG = pBuffer->pData;
        pBG = &pFrame->aBuffer[FBT_IMAGE];
        if (!rspFillObjTxtr(pRSP, SEGMENT_ADDRESS(pRSP, nCommandLo), &objTxtr, &nLoadType)) {
            return false;
        }
        if (!rspSetImage(pFrame, pRSP, G_IM_FMT_RGBA, 1, G_IM_SIZ_16b, objTxtr.block.image)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[6]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[6]);
        pLUT = pFrame->aBuffer[FBT_IMAGE].pData;
        rspFillObjBg(pRSP, SEGMENT_ADDRESS(pRSP, nCommandLo), &bg);
        nAddress = pBG->nAddress = SEGMENT_ADDRESS(pRSP, bg.b.imagePtr);
        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pBG->pData, nAddress, NULL)) {
            return false;
        }
        pBitmap8 = pBG->pData;
        PanelDrawBG8(BG, pLUT, pBitmap8, bg.b.imageW >> 2, bg.b.imageH >> 2, bg.b.frameX >> 2, bg.b.frameY >> 2,
                     bg.b.imageFlip);

        nCommandHi = GBI_COMMAND_HI(&pnGBI[9]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[9]);
        if (!rspFillObjTxtr(pRSP, SEGMENT_ADDRESS(pRSP, nCommandLo), &objTxtr, &nLoadType)) {
            return false;
        }
        if (!rspSetImage(pFrame, pRSP, G_IM_FMT_RGBA, 1, G_IM_SIZ_16b, objTxtr.block.image)) {
            return false;
        }

        nCommandHi = GBI_COMMAND_HI(&pnGBI[11]);
        nCommandLo = GBI_COMMAND_LO(&pnGBI[11]);
        pLUT = pFrame->aBuffer[FBT_IMAGE].pData;
        rspFillObjBg(pRSP, SEGMENT_ADDRESS(pRSP, nCommandLo), &bg);
        nAddress = pBG->nAddress = SEGMENT_ADDRESS(pRSP, bg.b.imagePtr);
        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pBG->pData, nAddress, NULL)) {
            return false;
        }
        pBitmap8 = pBG->pData;
        PanelDrawBG8(BG, pLUT, pBitmap8, bg.b.imageW >> 2, bg.b.imageH >> 2, (bg.b.frameX >> 2) - 20, bg.b.frameY >> 2,
                     bg.b.imageFlip);

        *ppnGBI = pnGBI + 12;
        return true;
    }

    return false;
}
#endif

bool frameGetDepth(Frame* pFrame, u16* pnData, s32 nAddress) {
    u32 nX;
    u32 nY;
    u32 nOffset;
    s32 n64CalcValue;
    s32 exp;
    s32 mantissa;
    s32 compare;
    s32 val;
    s32 pad[2];

    // See "Z Image Format" in the N64 Programming Manual
    // https://ultra64.ca/files/documentation/online-manuals/man/pro-man/pro15/index15.5.html
    struct {
        s32 shift;
        s32 add;
    } z_format[8] = {
        {6, 0x00000}, {5, 0x20000}, {4, 0x30000}, {3, 0x38000}, {2, 0x3C000}, {1, 0x3E000}, {0, 0x3F000}, {0, 0x3F800},
    };

    nAddress &= 0x03FFFFFF;
    if (pFrame->nOffsetDepth0 <= nAddress && nAddress <= pFrame->nOffsetDepth1) {
        nOffset = (nAddress - pFrame->nOffsetDepth0) / 2;
        nX = nOffset % N64_FRAME_WIDTH;
        nY = nOffset / N64_FRAME_WIDTH;

        val = sTempZBuf[(nY >> 2) * (N64_FRAME_WIDTH / 4) + (nX >> 2)][nY & 3][nX & 3];
        n64CalcValue = 43.52 * ((((val & 0xFF) << 8) | (val >> 8)) - 0x10000 + 1) + 262143.0;

        compare = 0x3F800;
        for (exp = 7; exp >= 0; exp--) {
            if ((n64CalcValue & compare) == compare) {
                break;
            }
            compare = (compare << 1) & 0x3FFFF;
        }

        mantissa = ((n64CalcValue - z_format[exp].add) >> z_format[exp].shift) & 0x7FF;

        *pnData = 0;
        *pnData = ((exp << 13) & 0xE000) | ((mantissa << 2) & 0x1FFC);
        return true;
    }

    return false;
}

static bool frameEvent(Frame* pFrame, s32 nEvent, void* pArgument) {
    s32 temp_r4;

    switch (nEvent) {
        case 2:
            pFrame->nFlag = 0;
            pFrame->nMode = 0x20000;
            pFrame->iHintMatrix = 0;
            pFrame->nCountFrames = 0;
            gbFrameBegin = true;
            gbFrameValid = false;
            gnCountMapHack = 0;
            if (!frameSetupCache(pFrame)) {
                return false;
            }
            pFrame->nOffsetDepth0 = -1;
            pFrame->nOffsetDepth1 = -1;
            pFrame->viewport.rX = 0.0f;
            pFrame->viewport.rY = 0.0f;
            pFrame->nHackCount = 0;
            pFrame->bBlurOn = false;
            pFrame->bHackPause = false;
            pFrame->nFrameCounter = 0;
            pFrame->nNumCIMGAddresses = 0;
            pFrame->bPauseThisFrame = false;
            pFrame->bCameFromBomberNotes = false;
            pFrame->bInBomberNotes = false;
            pFrame->bShrinking = 0;
#if IS_MM
            pFrame->bSnapShot = 0;
#endif
            pFrame->bUsingLens = false;
            pFrame->cBlurAlpha = 170;
            pFrame->bBlurredThisFrame = false;
            pFrame->nFrameCIMGCalls = 0;

#if IS_OOT
            pFrame->nZBufferSets = 0;
            pFrame->nLastFrameZSets = 0;
            pFrame->bPauseBGDrawn = false;
            pFrame->bFrameOn = false;
            pFrame->bModifyZBuffer = false;
            pFrame->bOverrideDepth = false;
#else
            pFrame->bModifyZBuffer = false;
            pFrame->nZBufferSets = 0;
            pFrame->nLastFrameZSets = 0;
            pFrame->bPauseBGDrawn = false;
#endif

            pFrame->viewport.rSizeX = GC_FRAME_WIDTH;
            pFrame->viewport.rSizeY = GC_FRAME_HEIGHT;
            pFrame->anSizeX[FS_SOURCE] = N64_FRAME_WIDTH;
            pFrame->anSizeY[FS_SOURCE] = N64_FRAME_HEIGHT;
            pFrame->rScaleX = (f32)pFrame->anSizeX[FS_TARGET] / (f32)N64_FRAME_WIDTH;
            pFrame->rScaleY = (f32)pFrame->anSizeY[FS_TARGET] / (f32)N64_FRAME_HEIGHT;

            temp_r4 = GC_FRAME_HEIGHT >> (xlCoreHiResolution() ? 0 : 1);
            if (temp_r4 > 0) {
                pFrame->anSizeX[FS_TARGET] = GC_FRAME_WIDTH;
                pFrame->anSizeY[FS_TARGET] = temp_r4;
                pFrame->rScaleX = GC_FRAME_WIDTH / (f32)pFrame->anSizeX[FS_SOURCE];
                pFrame->rScaleY = temp_r4 / (f32)pFrame->anSizeY[FS_SOURCE];
            }
            GXSetDrawDoneCallback(&frameDrawDone);
            break;
        case 3:
            if (!frameResetCache(pFrame)) {
                return false;
            }
            break;
#if VERSION != MQ_J
        case 0x1003:
            pFrame->nTempBuffer = NULL;
            pFrame->nCopyBuffer = NULL;
#if IS_OOT
            pFrame->nLensBuffer = NULL;
#endif
            pFrame->nCameraBuffer = NULL;
            if (gpSystem->eTypeROM == SRT_PANEL || gpSystem->eTypeROM == SRT_ZELDA2 ||
                gpSystem->eTypeROM == SRT_DRMARIO) {
                if (!xlHeapTake((void**)&pFrame->nTempBuffer,
                                0x30000000 | (N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16)))) {
                    return false;
                }
            }
            if (gpSystem->eTypeROM == SRT_ZELDA2) {
                if (!xlHeapTake((void**)&pFrame->nCopyBuffer,
                                0x30000000 | (N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16)))) {
                    return false;
                }
            }
#if IS_OOT
            if (gpSystem->eTypeROM == SRT_ZELDA2) {
                if (!xlHeapTake((void**)&pFrame->nLensBuffer, 0x30000000 | 0x4B000)) {
                    return false;
                }
            }
#endif
            if (gpSystem->eTypeROM == SRT_ZELDA2) {
                if (!xlHeapTake((void**)&pFrame->nCameraBuffer, 0x30000000 | CAMERA_BUFFER_SIZE)) {
                    return false;
                }
            }
            break;
#endif
        case 0:
        case 1:
        case 5:
        case 6:
            break;
        default:
            return false;
    }

    return true;
}
