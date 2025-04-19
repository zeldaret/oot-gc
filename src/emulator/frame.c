#include "emulator/frame.h"
#include "dolphin.h"
#include "emulator/cpu.h"
#include "emulator/ram.h"
#include "emulator/rdp.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "math.h"

static bool frameDrawLine_Setup(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_Setup(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawRectFill_Setup(Frame* pFrame, Rectangle* pRectangle);
static bool frameDrawRectTexture_Setup(Frame* pFrame, Rectangle* pRectangle);
static inline bool frameGetMatrixHint(Frame* pFrame, u32 nAddress, s32* piHint);
static bool frameEvent(Frame* pFrame, s32 nEvent, void* pArgument);
void PSMTX44MultVecNoW(Mtx44 m, Vec3f* src, Vec3f* dst);

_XL_OBJECTTYPE gClassFrame = {
    "Frame-Buffer",
    sizeof(Frame),
    NULL,
    (EventFunc)frameEvent,
};

static inline bool frameCopyMatrix(Mtx44 matrixTarget, Mtx44 matrixSource) {
    matrixTarget[0][0] = matrixSource[0][0];
    matrixTarget[0][1] = matrixSource[0][1];
    matrixTarget[0][2] = matrixSource[0][2];
    matrixTarget[0][3] = matrixSource[0][3];
    matrixTarget[1][0] = matrixSource[1][0];
    matrixTarget[1][1] = matrixSource[1][1];
    matrixTarget[1][2] = matrixSource[1][2];
    matrixTarget[1][3] = matrixSource[1][3];
    matrixTarget[2][0] = matrixSource[2][0];
    matrixTarget[2][1] = matrixSource[2][1];
    matrixTarget[2][2] = matrixSource[2][2];
    matrixTarget[2][3] = matrixSource[2][3];
    matrixTarget[3][0] = matrixSource[3][0];
    matrixTarget[3][1] = matrixSource[3][1];
    matrixTarget[3][2] = matrixSource[3][2];
    matrixTarget[3][3] = matrixSource[3][3];
    return true;
}

static inline bool frameTransposeMatrix(Mtx44 matrixTarget, Mtx44 matrixSource) {
    matrixTarget[0][0] = matrixSource[0][0];
    matrixTarget[0][1] = matrixSource[1][0];
    matrixTarget[0][2] = matrixSource[2][0];
    matrixTarget[0][3] = matrixSource[3][0];
    matrixTarget[1][0] = matrixSource[0][1];
    matrixTarget[1][1] = matrixSource[1][1];
    matrixTarget[1][2] = matrixSource[2][1];
    matrixTarget[1][3] = matrixSource[3][1];
    matrixTarget[2][0] = matrixSource[0][2];
    matrixTarget[2][1] = matrixSource[1][2];
    matrixTarget[2][2] = matrixSource[2][2];
    matrixTarget[2][3] = matrixSource[3][2];
    matrixTarget[3][0] = matrixSource[0][3];
    matrixTarget[3][1] = matrixSource[1][3];
    matrixTarget[3][2] = matrixSource[2][3];
    matrixTarget[3][3] = matrixSource[3][3];
    return true;
}

bool frameScaleMatrix(Mtx44 matrixResult, Mtx44 matrix, f32 rScale) {
    matrixResult[0][0] = matrix[0][0] * rScale;
    matrixResult[0][1] = matrix[0][1] * rScale;
    matrixResult[0][2] = matrix[0][2] * rScale;
    matrixResult[0][3] = matrix[0][3] * rScale;
    matrixResult[1][0] = matrix[1][0] * rScale;
    matrixResult[1][1] = matrix[1][1] * rScale;
    matrixResult[1][2] = matrix[1][2] * rScale;
    matrixResult[1][3] = matrix[1][3] * rScale;
    matrixResult[2][0] = matrix[2][0] * rScale;
    matrixResult[2][1] = matrix[2][1] * rScale;
    matrixResult[2][2] = matrix[2][2] * rScale;
    matrixResult[2][3] = matrix[2][3] * rScale;
    matrixResult[3][0] = matrix[3][0] * rScale;
    matrixResult[3][1] = matrix[3][1] * rScale;
    matrixResult[3][2] = matrix[3][2] * rScale;
    matrixResult[3][3] = matrix[3][3] * rScale;
    return true;
}

static bool frameConvertYUVtoRGB(u32* YUV, u32* RGB) {
    s32 Yl;
    s32 R;
    s32 G;
    s32 B;

    Yl = YUV[0] - 16;
    B = (s32)((YUV[1] - 128) * 20830 + Yl * 12014) >> 16;
    G = (s32)(Yl * 11079 + ((YUV[2] - 128) * -6480 - B * 12729)) >> 16;
    R = (s32)(Yl * 31026 - B * 24987 - G * 128660) >> 16;

    if (R > 31) {
        R = 31;
    } else if (R < 0) {
        R = 0;
    }
    if (G > 31) {
        G = 31;
    } else if (G < 0) {
        G = 0;
    }
    if (B > 31) {
        B = 31;
    } else if (B < 0) {
        B = 0;
    }

    RGB[0] = R;
    RGB[1] = G;
    RGB[2] = B;
    return true;
}

static bool packTakeBlocks(s32* piPack, u32* anPack, s32 nPackCount, s32 nBlockCount) {
    s32 nOffset;
    s32 nCount;
    s32 iPack;
    u32 nPack;
    u32 nMask;
    u32 nMask0;

    if (nBlockCount >= 32 || nBlockCount < 0) {
        return false;
    }

    nCount = 33 - nBlockCount;
    for (iPack = 0; iPack < nPackCount; iPack++) {
        nPack = anPack[iPack];
        if (nPack != -1) {
            nMask = (1 << nBlockCount) - 1;
            nOffset = nCount;
            do {
                if ((nPack & nMask) == 0) {
                    anPack[iPack] |= nMask;
                    *piPack = (nBlockCount << 16) | ((iPack << 5) + (nCount - nOffset));
                    return true;
                }
                nOffset -= 1;
                nMask <<= 1;
            } while (nOffset != 0);
        }
    }

    *piPack = -1;
    return false;
}

static bool packFreeBlocks(s32* piPack, u32* anPack, s32 nPackCount) {
    s32 iPack;
    u32 nMask;

    s32 temp_r6;

    iPack = *piPack;

    if (iPack == -1) {
        return true;
    }

    nMask = ((1 << (iPack >> 16)) - 1) << (iPack & 0x1F);
    temp_r6 = (iPack & 0xFFFF) >> 5;

    if (nMask == (nMask & anPack[temp_r6])) {
        anPack[temp_r6] &= ~nMask;
        *piPack = -1;
        return true;
    }

    return false;
}

static bool frameMakeTexture(Frame* pFrame, FrameTexture** ppTexture) {
    u32 nMask;
    s32 iTexture;
    s32 iTextureUsed;

    iTextureUsed = 0;
    while (iTextureUsed < ARRAY_COUNTU(pFrame->anTextureUsed) && (nMask = pFrame->anTextureUsed[iTextureUsed]) == -1) {
        iTextureUsed++;
    }

    if (iTextureUsed == ARRAY_COUNTU(pFrame->anTextureUsed)) {
        xlPostText("MakeTexture: 'aTexture' is exhausted!", "frame.c", 554);
        return false;
    }

    iTexture = 0;
    while (nMask & 1) {
        iTexture++;
        nMask >>= 1;
    }

    pFrame->anTextureUsed[iTextureUsed] |= (1 << iTexture);
    *ppTexture = &pFrame->aTexture[(iTextureUsed << 5) + iTexture];
    (*ppTexture)->iPackPixel = -1;
    (*ppTexture)->iPackColor = -1;
    (*ppTexture)->pTextureNext = NULL;

    if (++pFrame->nBlocksTexture > pFrame->nBlocksMaxTexture) {
        pFrame->nBlocksMaxTexture = pFrame->nBlocksTexture;
    }

    return true;
}

static inline bool frameFreeTexture(Frame* pFrame, FrameTexture* pTexture) {
    s32 iTexture = (u8*)pTexture - (u8*)&pFrame->aTexture[0];

    if (!frameFreePixels(pFrame, pTexture)) {
        return false;
    }

    iTexture /= sizeof(FrameTexture);
    pFrame->anTextureUsed[iTexture >> 5] &= ~(1 << (iTexture & 0x1F));
    pFrame->nBlocksTexture--;
    return true;
}

static bool frameSetupCache(Frame* pFrame) {
    s32 iTexture;

    pFrame->nBlocksMaxPixel = 0;
    pFrame->nBlocksPixel = 0;
    pFrame->nBlocksMaxColor = 0;
    pFrame->nBlocksColor = 0;
    pFrame->nBlocksMaxTexture = 0;
    pFrame->nBlocksTexture = 0;

    for (iTexture = 0; iTexture < ARRAY_COUNT(pFrame->apTextureCached); iTexture++) {
        pFrame->apTextureCached[iTexture] = 0;
    }

    for (iTexture = 0; iTexture < ARRAY_COUNTU(pFrame->anTextureUsed); iTexture++) {
        pFrame->anTextureUsed[iTexture] = 0;
    }

    for (iTexture = 0; iTexture < ARRAY_COUNT(pFrame->anPackPixel); iTexture++) {
        pFrame->anPackPixel[iTexture] = 0;
    }

    if (!xlHeapTake(&pFrame->aPixelData, 0x30000000 | 0x00300000)) {
        return false;
    }

    for (iTexture = 0; iTexture < ARRAY_COUNT(pFrame->anPackColor); iTexture++) {
        pFrame->anPackColor[iTexture] = 0;
    }

    if (!xlHeapTake(&pFrame->aColorData, 0x30000000 | (N64_FRAME_WIDTH * 1024))) {
        return false;
    }

    return true;
}

static inline bool frameResetCache(Frame* pFrame) {
    if (!xlHeapFree(&pFrame->aColorData)) {
        return false;
    }

    if (!xlHeapFree(&pFrame->aPixelData)) {
        return false;
    }

    return true;
}

static bool frameUpdateCache(Frame* pFrame) {
    // s32 nCount;
    // s32 nCountFree;
    u32 nMask;
    s32 nFrameCount;
    s32 nFrameDelta;
    s32 iTexture;
    s32 iTextureUsed;
    s32 iTextureCached;
    FrameTexture* pTexture;
    FrameTexture* pTextureCached;
    FrameTexture* pTextureLast;

    nFrameCount = pFrame->nCountFrames;
    for (iTextureUsed = 0; iTextureUsed < ARRAY_COUNTU(pFrame->anTextureUsed); iTextureUsed++) {
        if ((nMask = pFrame->anTextureUsed[iTextureUsed]) != 0) {
            for (iTexture = 0; nMask != 0; iTexture++, nMask >>= 1) {
                if (nMask & 1) {
                    pTexture = &pFrame->aTexture[(iTextureUsed << 5) + iTexture];
                    nFrameDelta = pTexture->nFrameLast - nFrameCount;
                    if (nFrameDelta < 0) {
                        nFrameDelta = -nFrameDelta;
                    }
                    if (nFrameDelta > 1) {
                        pTextureLast = NULL;
                        iTextureCached = pTexture->nAddress >> 11;
                        pTextureCached = pFrame->apTextureCached[iTextureCached];

                        while (pTextureCached != NULL && pTextureCached != pTexture) {
                            pTextureLast = pTextureCached;
                            pTextureCached = pTextureCached->pTextureNext;
                        }

                        if (pTextureLast == NULL) {
                            pFrame->apTextureCached[iTextureCached] = pTextureCached->pTextureNext;
                        } else {
                            pTextureLast->pTextureNext = pTextureCached->pTextureNext;
                        }
                        if (!frameFreeTexture(pFrame, pTexture)) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

static bool frameLoadTile(Frame* pFrame, FrameTexture** ppTexture, s32 iTileCode) {
    bool bFlag;
    Tile* pTile;
    FrameTexture* pTexture;
    FrameTexture* pTextureLast;
    u32 nData0;
    u32 nData1;
    u32 nData2;
    u32 nData3;
    s32 iTexture;
    s32 nShift;
    s32 pad;

    pTile = &pFrame->aTile[iTileCode & 0xF];
    if (pTile->nX0 == 0 && pTile->nY0 == 0 && pTile->nX1 == 0 && pTile->nY1 == 0) {
        bFlag = true;
        pTile->nX0 = pFrame->aTile[pFrame->iTileLoad].nX0;
        pTile->nY0 = pFrame->aTile[pFrame->iTileLoad].nY0;
        pTile->nX1 = pFrame->aTile[pFrame->iTileLoad].nX1;
        pTile->nY1 = pFrame->aTile[pFrame->iTileLoad].nY1;
        nShift = pFrame->aTile[pFrame->iTileLoad].nSize - pTile->nSize;
        if (nShift < 0) {
            nShift = -nShift;
            pTile->nX0 >>= nShift;
            pTile->nX1 >>= nShift;
        } else {
            pTile->nX0 <<= nShift;
            pTile->nX1 <<= nShift;
        }
        pTile->nModeS = 2;
        pTile->nModeT = 2;
    } else {
        bFlag = false;
    }

    nData0 = (pTile->nX0 & 0xFFFF) | ((pTile->nX1 & 0xFFFF) << 16);
    nData1 = (pTile->nY0 & 0xFFFF) | ((pTile->nY1 & 0xFFFF) << 16);
    nData2 = ((pTile->nMaskS & 0xF) << 0) | ((pTile->nMaskT & 0xF) << 4) | ((pTile->nModeS & 7) << 8) |
             ((pTile->nModeT & 7) << 11) | ((pTile->nShiftS & 0xF) << 14) | ((pTile->nShiftT & 0xF) << 18) |
             ((pTile->nSize & 7) << 22) | ((pTile->nFormat & 7) << 25) | ((pTile->iTLUT & 0xF) << 28);
    nData3 = (pTile->nTMEM & 0xFFFF) | ((pTile->nSizeX & 0xFFFF) << 16);
    if (pFrame->nAddressLoad == -1) {
        iTexture = 0;
    } else {
        iTexture = pFrame->nAddressLoad >> 11;
    }

    pTextureLast = pTexture = pFrame->apTextureCached[iTexture];
    while (pTexture != NULL) {
        if (pTexture->nData0 == nData0 && pTexture->nData1 == nData1 && pTexture->nData2 == nData2 &&
            pTexture->nData3 == nData3 && pTexture->nCodePixel == pTile->nCodePixel &&
            pTexture->nAddress == pFrame->nAddressLoad) {
            break;
        }
        pTextureLast = pTexture;
        pTexture = pTexture->pTextureNext;
    }

    if (pTexture == NULL) {
        if (!frameMakeTexture(pFrame, &pTexture)) {
            return false;
        }

        frameMakePixels(pFrame, pTexture, pTile, false);
        pTexture->nData0 = nData0;
        pTexture->nData1 = nData1;
        pTexture->nData2 = nData2;
        pTexture->nData3 = nData3;

        if (pFrame->nAddressLoad == -1) {
            pTexture->nAddress = 0;
        } else {
            pTexture->nAddress = pFrame->nAddressLoad;
        }
        if (pTextureLast == NULL) {
            pFrame->apTextureCached[iTexture] = pTexture;
        } else {
            pTextureLast->pTextureNext = pTexture;
        }
    } else if (pTexture->iPackColor != -1 && pTexture->nCodeColor != pFrame->nTlutCode[pTile->iTLUT]) {
        frameMakePixels(pFrame, pTexture, pTile, true);
    }

    pTexture->nFrameLast = pFrame->nCountFrames;
    pTexture->nCodeColor = pFrame->nTlutCode[pTile->iTLUT];
    pTexture->nCodePixel = pTile->nCodePixel;

    if (!frameLoadTexture(pFrame, pTexture, iTileCode, pTile)) {
        return false;
    }

    if (ppTexture != NULL) {
        *ppTexture = pTexture;
    }

    if (bFlag) {
        pTile->nX0 = pTile->nY0 = pTile->nX1 = pTile->nY1 = 0;
    }
    return true;
}

bool frameDrawReset(Frame* pFrame, s32 nFlag) {
    pFrame->nFlag |= nFlag;
    pFrame->aDraw[0] = (FrameDrawFunc)frameDrawLine_Setup;
    pFrame->aDraw[1] = (FrameDrawFunc)frameDrawTriangle_Setup;
    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill_Setup;
    pFrame->aDraw[3] = (FrameDrawFunc)frameDrawRectTexture_Setup;
    return true;
}

#include "emulator/_frameGCN.c"

bool frameSetFill(Frame* pFrame, bool bFill) {
    if (bFill) {
        pFrame->nMode |= 0x20000;
    } else {
        pFrame->nMode &= ~0x20000;
    }
    return true;
}

bool frameSetSize(Frame* pFrame, FrameSize eSize, s32 nSizeX, s32 nSizeY) {
    if (nSizeX > 0 && nSizeY > 0) {
        pFrame->anSizeX[eSize] = nSizeX;
        pFrame->anSizeY[eSize] = nSizeY;
        if (eSize == FS_SOURCE) {
            pFrame->rScaleX = (f32)pFrame->anSizeX[FS_TARGET] / nSizeX;
            pFrame->rScaleY = (f32)pFrame->anSizeY[FS_TARGET] / nSizeY;
        } else if (eSize == FS_TARGET) {
            pFrame->rScaleX = (f32)nSizeX / pFrame->anSizeX[FS_SOURCE];
            pFrame->rScaleY = (f32)nSizeY / pFrame->anSizeY[FS_SOURCE];
        }
    }

    return true;
}

bool frameSetMode(Frame* pFrame, FrameModeType eType, u32 nMode) {
    u32 nFlag;
    u32 nModeChanged;

    if (pFrame->nMode & (1 << eType)) {
        nModeChanged = pFrame->aMode[eType] ^ nMode;
    } else {
        nModeChanged = 0xFFFFFFFF;
        *((volatile u32*)&pFrame->nMode) |= (1 << eType);
    }

    nFlag = 0;
    switch (eType) {
        case FMT_FOG:
            if (nModeChanged != 0) {
                nFlag |= 0x20;
            }
            break;
        case FMT_GEOMETRY:
            if ((nModeChanged & 0x10) != 0) {
                nFlag |= 0x20;
            }
            if ((nModeChanged & 1) != 0) {
                nFlag |= 4;
            }
            if ((nModeChanged & 0xC) != 0) {
                nFlag |= 8;
            }
            if ((nModeChanged & 0x180) != 0) {
                nFlag |= 2;
            }
            break;
        case FMT_TEXTURE1:
            if (nModeChanged != 0) {
                nFlag |= 0x7C01;
            }
            break;
        case FMT_TEXTURE2:
            if (nModeChanged != 0) {
                nFlag |= 0x7D01;
            }
            break;
        case FMT_OTHER0:
            nFlag |= 0x200;
            if ((nModeChanged & 3) != 0) {
                nFlag |= 0x7C00;
            }
            if ((nModeChanged & 0xF0) != 0) {
                nFlag |= 4;
            }
            if ((nModeChanged & 0xC00) != 0) {
                nFlag |= 0x40000 | 4;
            }
            if ((nModeChanged & 0xFFFF0000) != 0) {
                nFlag |= 0x7C00;
            }
            break;
        case FMT_OTHER1:
            if (nModeChanged != 0) {
                nFlag |= 0x7F01;
            }
            break;
        case FMT_COMBINE_COLOR1:
        case FMT_COMBINE_COLOR2:
        case FMT_COMBINE_ALPHA1:
        case FMT_COMBINE_ALPHA2:
            if (nModeChanged != 0) {
                nFlag |= 0x7D00;
            }
            break;
        default:
            break;
    }

    if (nFlag != 0) {
        frameDrawReset(pFrame, nFlag);
    }

    pFrame->aMode[eType] = nMode;
    return true;
}

bool frameGetMode(Frame* pFrame, FrameModeType eType, u32* pnMode) {
    *pnMode = pFrame->aMode[eType];
    return true;
}

bool frameSetMatrix(Frame* pFrame, Mtx44 matrix, FrameMatrixType eType, bool bLoad, bool bPush, s32 nAddressN64) {
    s32 pad1;
    bool bFlag;
    Mtx44Ptr matrixTarget;
    Mtx44 matrixResult;
    s32 pad2[9];

    OSGetTick();

    switch (eType) {
        case FMT_MODELVIEW:
            if (!bLoad && (pFrame->nMode & 0x800000)) {
                bFlag = true;
                PSMTX44Concat(matrix, pFrame->aMatrixModel[pFrame->iMatrixModel], matrixResult);
            } else {
                bFlag = false;
            }

            if (bPush && pFrame->iMatrixModel < ARRAY_COUNT(pFrame->aMatrixModel) - 1) {
                pFrame->iMatrixModel++;
            }

            if (bFlag) {
                matrixTarget = pFrame->aMatrixModel[pFrame->iMatrixModel];
                frameCopyMatrix(matrixTarget, matrixResult);
            } else {
                matrixTarget = pFrame->aMatrixModel[pFrame->iMatrixModel];
                frameCopyMatrix(matrixTarget, matrix);
            }

            pFrame->nMode |= 0x800000;
            pFrame->nMode &= ~0x600000;
            break;
        case FMT_PROJECTION:
            pFrame->nMode &= ~0x20000000;
            if (gpSystem->eTypeROM == SRT_1080 && (matrix[0][0] < 0.006240f || matrix[0][0] > 0.006242f)) {
                if (!frameSetProjection(pFrame, pFrame->iHintHack)) {
                    return false;
                }
                bLoad = false;
            }

            // TODO: fake volatile
            if (bLoad || !(*(volatile u32*)&pFrame->nMode & 0x4000000) ||
                (*(volatile u32*)&pFrame->nMode & 0x10000000)) {
                if (matrix[0][0] == 1.0f && matrix[0][1] == 0.0f && matrix[0][2] == 0.0f && matrix[0][3] == 0.0f &&
                    matrix[1][0] == 0.0f && matrix[1][1] == 1.0f && matrix[1][2] == 0.0f && matrix[1][3] == 0.0f &&
                    matrix[2][0] == 0.0f && matrix[2][1] == 0.0f && matrix[2][2] == 1.0f && matrix[2][3] == 0.0f &&
                    matrix[3][0] == 0.0f && matrix[3][1] == 0.0f && matrix[3][2] == 0.0f && matrix[3][3] == 1.0f) {
                    pFrame->nMode |= 0x10000000;
                } else {
                    pFrame->nMode &= ~0x10000000;
                }

                matrixTarget = pFrame->matrixProjection;
                frameCopyMatrix(matrixTarget, matrix);

                pFrame->nMode |= 0x4000000;
                pFrame->nMode &= ~0x8000000;

                if (!frameGetMatrixHint(pFrame, nAddressN64 | 0x80000000, &pFrame->iHintProjection)) {
                    pFrame->iHintProjection = -1;
                }
            } else if (*(volatile u32*)&pFrame->nMode & 0x8000000) {
                PSMTX44Concat(matrix, pFrame->matrixProjectionExtra, pFrame->matrixProjectionExtra);
            } else {
                pFrame->nMode |= 0x8000000;
                matrixTarget = pFrame->matrixProjectionExtra;
                frameCopyMatrix(matrixTarget, matrix);
            }

            pFrame->nMode &= ~0x400000;
            frameDrawReset(pFrame, 0x40000);
            break;
        default:
            return false;
    }

    return true;
}

bool frameGetMatrix(Frame* pFrame, Mtx44 matrix, FrameMatrixType eType, bool bPull) {
    switch (eType) {
        case FMT_MODELVIEW:
            if (matrix != NULL) {
                if (!xlHeapCopy(matrix, pFrame->aMatrixModel[pFrame->iMatrixModel], sizeof(Mtx44))) {
                    return false;
                }
            }
            if (bPull) {
                if (pFrame->iMatrixModel > 0) {
                    pFrame->iMatrixModel--;
                    pFrame->nMode &= ~0x600000;
                }
            }
            break;
        case FMT_PROJECTION:
            if (matrix != NULL) {
                if (pFrame->nMode & 0x8000000) {
                    PSMTX44Concat(pFrame->matrixProjectionExtra, pFrame->matrixProjection, matrix);
                } else {
                    if (!xlHeapCopy(matrix, pFrame->matrixProjection, sizeof(Mtx44))) {
                        return false;
                    }
                }
            }
            break;
        default:
            return false;
    }

    return true;
}

// TODO: move these paired-single/quantization functions to a separate header
// along with the GQR initialization in xlMain()?
static inline void s16tof32(register s16* in, register f32* out) { OSs16tof32(in, out); }

static inline void s16tof32Pair(register s16* in, register f32* out) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l f1, 0(in), 0, OS_FASTCAST_S16
        psq_st f1, 0(out), 0, 0
    }
    // clang-format on
#else
    out[0] = (f32)in[0];
    out[1] = (f32)in[1];
#endif
}

static inline void s8tof32Scaled128(register s8* in, register f32* out) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l f1, 0(in), 1, 6
        stfs  f1, 0(out)
    }
    // clang-format on
#else
    *out = (f32)*in / 128.0f;
#endif
}

static inline void s8tof32Scaled128Pair(register s8* in, register f32* out) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l f1, 0(in), 0, 6
        psq_st f1, 0(out), 0, 0
    }
    // clang-format on
#else
    out[0] = (f32)in[0] / 128.0f;
    out[1] = (f32)in[1] / 128.0f;
#endif
}

static inline void s16tof32Scaled32Pair(register s16* src, register f32* dst) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l f1, 0(src), 0, 7
        psq_st f1, 0(dst), 0, 0
    }
    // clang-format on
#else
    dst[0] = (f32)src[0] / 32.0f;
    dst[1] = (f32)src[1] / 32.0f;
#endif
}

bool frameLoadVertex(Frame* pFrame, void* pBuffer, s32 iVertex0, s32 nCount) {
    f32 mag;
    s32 iLight;
    s32 nLight;
    s32 nTexGen;
    f32 colorS;
    f32 colorT;
    f32 rS;
    f32 rT;
    f32 arNormal[3];
    f32 arPosition[3];
    Vertex* pVertex;
    u32 nData32;
    Light* aLight;
    Light* pLight;
    s32 iVertex1;
    // f32 rScale;
    // f32 rScaleST;
    s8* pnData8;
    s16* pnData16;
    Mtx44Ptr matrixView;
    Mtx44Ptr matrixModel;
    f32 rColorR;
    f32 rColorG;
    f32 rColorB;
    f32 rDiffuse;
    f32 rInverseW;
    f32 rInverseLength;
    Vec3f vec;
    f32 distance;

    pnData8 = pBuffer;
    pnData16 = pBuffer;
    iVertex1 = iVertex0 + nCount - 1;
    if (iVertex0 < 0 || iVertex0 >= 80 || iVertex1 < 0 || iVertex1 >= 80) {
        return false;
    }

    matrixModel = pFrame->aMatrixModel[pFrame->iMatrixModel];
    if (pFrame->nMode & 0x08000000) {
        // TODO: volatile hacks
        if (!(*(volatile u32*)&pFrame->nMode & 0x400000)) {
            PSMTX44Concat(matrixModel, pFrame->matrixProjectionExtra, pFrame->matrixView);
            pFrame->nMode |= 0x400000;
            if (pFrame->iHintProjection != -1) {
                if (!frameScaleMatrix(pFrame->matrixView, pFrame->matrixView,
                                      pFrame->aMatrixHint[pFrame->iHintProjection].rScale)) {
                    return false;
                }
            }
        }
        matrixView = pFrame->matrixView;
        // TODO: volatile hacks
    } else if (!(*(volatile u32*)&pFrame->nMode & 0x400000) && pFrame->iHintProjection != -1) {
        if (!frameScaleMatrix(pFrame->matrixView, matrixModel, pFrame->aMatrixHint[pFrame->iHintProjection].rScale)) {
            return false;
        }
        pFrame->nMode |= 0x400000;
        matrixView = pFrame->matrixView;
    } else {
        matrixView = matrixModel;
    }

    if (pFrame->aMode[1] & 0x20) {
        nLight = pFrame->nCountLight;
        nTexGen = pFrame->aMode[1] & 0x180;
        aLight = pFrame->aLight;

        for (iLight = 0; iLight < nLight; iLight++) {
            pLight = &aLight[iLight];
            if (!pLight->bTransformed || !(pFrame->nMode & 0x200000)) {
                PSMTX44MultVecNoW(matrixModel, &pLight->rVecOrigTowards, &vec);
                rInverseLength = _inv_sqrtf(SQ(vec.x) + SQ(vec.y) + SQ(vec.z));
                pLight->rVectorX = vec.x * rInverseLength;
                pLight->rVectorY = vec.y * rInverseLength;
                pLight->rVectorZ = vec.z * rInverseLength;
                pLight->bTransformed = true;
            }
        }

        if (nTexGen != 0 && (!pFrame->lookAt.bTransformed || !(pFrame->nMode & 0x200000))) {
            if (!(pFrame->nMode & 0x01000000)) {
                pFrame->lookAt.rSRaw.x = 0.0f;
                pFrame->lookAt.rSRaw.y = 1.0f;
                pFrame->lookAt.rSRaw.z = 0.0f;
            }
            if (!(pFrame->nMode & 0x02000000)) {
                pFrame->lookAt.rTRaw.x = 1.0f;
                pFrame->lookAt.rTRaw.y = 0.0f;
                pFrame->lookAt.rTRaw.z = 0.0f;
            }
            PSMTX44MultVecNoW(matrixModel, &pFrame->lookAt.rSRaw, &pFrame->lookAt.rS);
            PSMTX44MultVecNoW(matrixModel, &pFrame->lookAt.rTRaw, &pFrame->lookAt.rT);

            mag = SQ(pFrame->lookAt.rS.x) + SQ(pFrame->lookAt.rS.y) + SQ(pFrame->lookAt.rS.z);
            if (mag > 0.0f) {
                rInverseLength = _inv_sqrtf(mag);
                pFrame->lookAt.rS.x *= rInverseLength;
                pFrame->lookAt.rS.y *= rInverseLength;
                pFrame->lookAt.rS.z *= rInverseLength;
            }

            mag = SQ(pFrame->lookAt.rT.x) + SQ(pFrame->lookAt.rT.y) + SQ(pFrame->lookAt.rT.z);
            if (mag > 0.0f) {
                rInverseLength = _inv_sqrtf(mag);
                pFrame->lookAt.rT.x *= rInverseLength;
                pFrame->lookAt.rT.y *= rInverseLength;
                pFrame->lookAt.rT.z *= rInverseLength;
            }

            pFrame->lookAt.bTransformed = true;
        }
        pFrame->nMode |= 0x200000;
    } else {
        nTexGen = 0;
        nLight = 0;
    }

    pVertex = &pFrame->aVertex[iVertex0];
    while (nCount-- != 0) {
        s16tof32Pair(&pnData16[0], &arPosition[0]);
        s16tof32(&pnData16[2], &arPosition[2]);

        pVertex->rSum = arPosition[0] + arPosition[1] + arPosition[2];
        rInverseW = 1.0f / (matrixView[0][3] * arPosition[0] + matrixView[1][3] * arPosition[1] +
                            matrixView[2][3] * arPosition[2] + matrixView[3][3]);
        pVertex->vec.x = rInverseW * (arPosition[0] * matrixView[0][0] + arPosition[1] * matrixView[1][0] +
                                      arPosition[2] * matrixView[2][0] + matrixView[3][0]);
        pVertex->vec.y = rInverseW * (arPosition[0] * matrixView[0][1] + arPosition[1] * matrixView[1][1] +
                                      arPosition[2] * matrixView[2][1] + matrixView[3][1]);
        pVertex->vec.z = rInverseW * (arPosition[0] * matrixView[0][2] + arPosition[1] * matrixView[1][2] +
                                      arPosition[2] * matrixView[2][2] + matrixView[3][2]);

        if (nLight != 0) {
            s8tof32Scaled128Pair(&pnData8[12], &arNormal[0]);
            s8tof32Scaled128(&pnData8[14], &arNormal[2]);

            iLight = nLight;
            pLight = &aLight[iLight];
            if (gpSystem->eTypeROM == SRT_STARFOX) {
                while ((rColorR = pLight->rColorR) + (rColorG = pLight->rColorG) + (rColorB = pLight->rColorB) ==
                       0.0f) {
                    pLight++;
                }
                pLight = &aLight[iLight];
            } else {
                rColorR = pLight->rColorR;
                rColorG = pLight->rColorG;
                rColorB = pLight->rColorB;
            }

            while (--iLight >= 0) {
                pLight--;
                if ((pFrame->aMode[1] & 0x800) && pLight->kc != 0.0f) {
                    distance = sqrtf(SQ(pLight->coordX - arPosition[0]) + SQ(pLight->coordY - arPosition[1]) +
                                     SQ(pLight->coordZ - arPosition[2]));
                    pLight->rVectorX = (pLight->coordX - arPosition[0]) / distance;
                    pLight->rVectorY = (pLight->coordY - arPosition[1]) / distance;
                    pLight->rVectorZ = (pLight->coordZ - arPosition[2]) / distance;
                    rDiffuse = (pLight->rVectorX * arNormal[0] + pLight->rVectorY * arNormal[1] +
                                pLight->rVectorZ * arNormal[2]) /
                               (pLight->kc + pLight->kl * distance + pLight->kq * distance * distance);
                    if (rDiffuse > 1.0f) {
                        rDiffuse = 1.0f;
                    }
                } else {
                    rDiffuse = pLight->rVectorX * arNormal[0] + pLight->rVectorY * arNormal[1] +
                               pLight->rVectorZ * arNormal[2];
                }

                if (rDiffuse > 0.0f) {
                    rColorR += pLight->rColorR * rDiffuse;
                    rColorG += pLight->rColorG * rDiffuse;
                    rColorB += pLight->rColorB * rDiffuse;
                }
            }

            OSf32tou8(&rColorR, &pVertex->anColor[0]);
            OSf32tou8(&rColorG, &pVertex->anColor[1]);
            OSf32tou8(&rColorB, &pVertex->anColor[2]);
            pVertex->anColor[3] = pnData8[15];

            if (nTexGen != 0) {
                rS = arNormal[0] * pFrame->lookAt.rS.x + arNormal[1] * pFrame->lookAt.rS.y +
                     arNormal[2] * pFrame->lookAt.rS.z;
                rT = arNormal[0] * pFrame->lookAt.rT.x + arNormal[1] * pFrame->lookAt.rT.y +
                     arNormal[2] * pFrame->lookAt.rT.z;
                if (nTexGen & 0x100) {
                    colorS = rS * rS * rS;
                    colorS = (0.22673035f * colorS) + colorS;
                    rS = (0.3183136f * rS) + colorS;
                    colorT = rT * rT * rT;
                    colorT = (0.22673035f * colorT) + colorT;
                    rT = (0.3183136f * rT) + colorT;
                } else {
                    rS *= 0.5f;
                    rT *= 0.5f;
                }
                pVertex->rS = rS + 0.5f;
                pVertex->rT = rT + 0.5f;
            }
        } else {
            nData32 = *(u32*)&pnData8[12];
            pVertex->anColor[0] = nData32 >> 24;
            pVertex->anColor[1] = nData32 >> 16;
            pVertex->anColor[2] = nData32 >> 8;
            pVertex->anColor[3] = nData32;
            if (nTexGen != 0) {
                s8tof32Scaled128Pair(&pnData8[12], &arNormal[0]);
                s8tof32Scaled128(&pnData8[14], &arNormal[2]);

                rS = arNormal[0] * pFrame->lookAt.rS.x + arNormal[1] * pFrame->lookAt.rS.y +
                     arNormal[2] * pFrame->lookAt.rS.z;
                rT = arNormal[0] * pFrame->lookAt.rT.x + arNormal[1] * pFrame->lookAt.rT.y +
                     arNormal[2] * pFrame->lookAt.rT.z;

                if (nTexGen & 0x100) {
                    colorS = rS * rS * rS;
                    colorS = (0.22673035f * colorS) + colorS;
                    rS = (0.3183136f * rS) + colorS;
                    colorT = rT * rT * rT;
                    colorT = (0.22673035f * colorT) + colorT;
                    rT = (0.3183136f * rT) + colorT;
                } else {
                    rS *= 0.5f;
                    rT *= 0.5f;
                }

                pVertex->rS = rS + 0.5f;
                pVertex->rT = rT + 0.5f;
            }
        }

        if (nTexGen == 0) {
            s16tof32Scaled32Pair(&pnData16[4], &pVertex->rS);
        }

        pVertex++;
        pnData8 += 0x10;
        pnData16 += 0x8;
    }

    return true;
}

bool frameCullDL(Frame* pFrame, s32 nVertexStart, s32 nVertexEnd) {
    f32 rX;
    f32 rY;
    f32 rZ;
    f32 rW;
    Mtx44Ptr matrix;
    Vertex* vtxP;
    Vertex* endVtxP;
    s32 nCode;
    s32 nCodeFull;

    matrix = pFrame->matrixProjection;
    vtxP = &pFrame->aVertex[nVertexStart];
    endVtxP = &pFrame->aVertex[nVertexEnd];
    nCodeFull = 0xFF;

    for (; vtxP <= endVtxP; vtxP++) {
        rX = vtxP->vec.x * matrix[0][0] + vtxP->vec.y * matrix[1][0] + vtxP->vec.z * matrix[2][0] + matrix[3][0];
        rY = vtxP->vec.x * matrix[0][1] + vtxP->vec.y * matrix[1][1] + vtxP->vec.z * matrix[2][1] + matrix[3][1];
        rZ = vtxP->vec.x * matrix[0][2] + vtxP->vec.y * matrix[1][2] + vtxP->vec.z * matrix[2][2] + matrix[3][2];
        rW = vtxP->vec.x * matrix[0][3] + vtxP->vec.y * matrix[1][3] + vtxP->vec.z * matrix[2][3] + matrix[3][3];

        nCode = 0;
        if (rX < -rW) {
            nCode |= 0x01;
        }
        if (rX > rW) {
            nCode |= 0x02;
        }
        if (rY < -rW) {
            nCode |= 0x04;
        }
        if (rY > rW) {
            nCode |= 0x08;
        }
        if (rZ < -rW) {
            nCode |= 0x10;
        }
        if (rZ > rW) {
            nCode |= 0x20;
        }

        nCodeFull &= nCode;
        if (nCodeFull == 0) {
            return false;
        }
    }

    return true;
}

bool frameLoadTLUT(Frame* pFrame, s32 nCount, s32 iTile) {
    s32 iTMEM = pFrame->aTile[iTile].nTMEM & 0x1FF;
    s32 nSize = nCount + 1;
    u32 nSum = 0;
    u64 nData64;
    u16 nData16;
    u16* pSource = pFrame->aBuffer[FBT_IMAGE].pData;
    s32 tileNum;

    while (nSize-- != 0) {
        nData16 = *pSource;
        pSource++;

        nSum += nData16 ^ iTMEM;
        nData64 = (nData16 << 16) | nData16;
        nData64 = (nData64 << 32) | nData64;
        pFrame->TMEM.data.u64[iTMEM] = nData64;
        iTMEM = (iTMEM + 1) & 0x1FF;
    }

    tileNum = pFrame->aTile[iTile].nTMEM & 0x1FF;
    tileNum -= 0x100;
    tileNum /= 16;
    tileNum &= 0xF;

    pFrame->nTlutCode[tileNum] = nSum;

    return true;
}

bool frameLoadTMEM(Frame* pFrame, FrameLoadType eType, s32 iTile) {
    bool bFlip;
    s32 iTMEM;
    s32 var_r0;
    s32 nSize;
    s32 nStep;
    s32 nDelta;
    s32 iScan;
    s32 nOffset;
    Tile* pTile;
    u8 nData8;
    u16 nData16;
    u32 nData32;
    u32 nData64[2];
    u32 nSum;
    u64* pSource;
    s32 nCount;
    s32 nScanFull;
    int nScanPart;
    u8* pSource8;
    u16* pSource16;
    u32* pSource32;

    s32 i;
    s32 temp_r3;
    s32 temp_r10;
    s32 pad[3];

    frameDrawReset(pFrame, 1);

#if IS_OOT
    if (gpSystem->eTypeROM == SRT_ZELDA2 &&
        (pFrame->aBuffer[FBT_IMAGE].nAddress == 0x500 || pFrame->aBuffer[FBT_IMAGE].nAddress == 0x7DA800)) {
        CopyAndConvertCFB(pFrame->aBuffer[FBT_IMAGE].pData);
    }
#endif

    pSource = (u64*)((u32)pFrame->aBuffer[FBT_IMAGE].pData & ~3);
    pFrame->iTileLoad = iTile;
    pTile = &pFrame->aTile[iTile];
    iTMEM = pTile->nTMEM & 0x1FF;
    if (eType == FLT_BLOCK) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }

    switch (pFrame->aBuffer[FBT_IMAGE].nSize) {
        case G_IM_SIZ_4b:
            nSize = (pTile->nX1 + 1) >> 4;
            nOffset =
                ((pTile->nX0 >> var_r0) >> 1) + ((pFrame->aBuffer[FBT_IMAGE].nWidth + 1) >> 1) * (pTile->nY0 >> var_r0);
            break;
        case G_IM_SIZ_8b:
            nSize = (pTile->nX1 + 1) >> 3;
            nOffset = (pTile->nX0 >> var_r0) + pFrame->aBuffer[FBT_IMAGE].nWidth * (pTile->nY0 >> var_r0);
            break;
        case G_IM_SIZ_16b:
            nSize = (pTile->nX1 + 1) >> 2;
            nOffset = ((pTile->nX0 >> var_r0) << 1) + (pFrame->aBuffer[FBT_IMAGE].nWidth << 1) * (pTile->nY0 >> var_r0);
            break;
        case G_IM_SIZ_32b:
            nSize = (pTile->nX1 + 1) >> 1;
            nOffset = ((pTile->nX0 >> var_r0) << 2) + (pFrame->aBuffer[FBT_IMAGE].nWidth << 2) * (pTile->nY0 >> var_r0);
            break;
        default:
            return false;
    }

    pSource = (u64*)((u8*)pSource + nOffset);
    pFrame->nAddressLoad = (pFrame->aBuffer[FBT_IMAGE].nAddress & 0x7FFFFF) + nOffset;
    nSum = 0;
    if (eType == FLT_BLOCK) {
        nDelta = pTile->nY1;
        if (nDelta == 0) {
            while (nSize-- != 0) {
                nData64[0] = ((u32*)pSource)[0];
                nData64[1] = ((u32*)pSource)[1];
                pSource++;

                nSum += nData64[0];
                nSum += nData64[1];
                nSum ^= iTMEM;

                pFrame->TMEM.data.u32[2 * iTMEM + 0] = nData64[0];
                pFrame->TMEM.data.u32[2 * iTMEM + 1] = nData64[1];

                iTMEM = (iTMEM + 1) & 0x1FF;
            }
        } else {
            nStep = 0;
            while (nSize != 0) {
                while (nSize != 0 && (nStep & 0x800) == 0) {
                    nData64[0] = ((u32*)pSource)[0];
                    nData64[1] = ((u32*)pSource)[1];
                    pSource++;

                    nSum += nData64[0];
                    nSum += nData64[1];
                    nSum ^= iTMEM;

                    pFrame->TMEM.data.u32[2 * iTMEM + 0] = nData64[0];
                    pFrame->TMEM.data.u32[2 * iTMEM + 1] = nData64[1];

                    iTMEM = (iTMEM + 1) & 0x1FF;
                    nStep += nDelta;
                    nSize--;
                }
                nStep -= 0x800;
                if (pFrame->aBuffer[FBT_IMAGE].nSize == 3) {
                    bFlip = 0;
                    while (nSize != 0 && (nStep & 0x800) == 0) {
                        nData64[0] = ((u32*)pSource)[0];
                        nData64[1] = ((u32*)pSource)[1];
                        pSource++;

                        nSum += nData64[0];
                        nSum += nData64[1];
                        nSum ^= iTMEM;

                        temp_r3 = iTMEM + (bFlip ? -1 : 1);
                        pFrame->TMEM.data.u32[2 * temp_r3 + 0] = nData64[0];
                        pFrame->TMEM.data.u32[2 * temp_r3 + 1] = nData64[1];

                        iTMEM = (iTMEM + 1) & 0x1FF;
                        nStep += nDelta;
                        nSize--;
                        bFlip ^= 1;
                    }
                } else {
                    while (nSize != 0 && (nStep & 0x800) == 0) {
                        nData64[0] = ((u32*)pSource)[0];
                        nData64[1] = ((u32*)pSource)[1];
                        pSource++;

                        nSum += nData64[0];
                        nSum += nData64[1];
                        nSum ^= iTMEM;

                        pFrame->TMEM.data.u32[2 * iTMEM + 0] = nData64[1];
                        pFrame->TMEM.data.u32[2 * iTMEM + 1] = nData64[0];

                        iTMEM = (iTMEM + 1) & 0x1FF;
                        nStep += nDelta;
                        nSize--;
                    }
                }
                nStep -= 0x800;
            }
        }
    } else {
        nCount = ((pTile->nY1 - pTile->nY0) + 4) >> 2;
        nScanFull = pFrame->aBuffer[FBT_IMAGE].nWidth;
        nScanPart = ((pTile->nX1 - pTile->nX0) + 4) >> 2;
        switch (pFrame->aBuffer[FBT_IMAGE].nSize) {
            case G_IM_SIZ_4b:
            case G_IM_SIZ_8b:
                if (nScanPart >= pTile->nSizeX * 8) {
                    nScanPart = pTile->nSizeX * 8;
                }
                iTMEM <<= 3;
                for (iScan = 0; iScan < nCount; iScan++) {
                    pSource8 = (u8*)pSource;
                    for (i = 0; i != nScanPart; i++) {
                        if (iScan & 1) {
                            temp_r10 = iTMEM ^ 4;
                        } else {
                            temp_r10 = iTMEM;
                        }
                        nData8 = *pSource8;
                        nSum += nData8;
                        nSum ^= iTMEM;
                        pFrame->TMEM.data.u8[temp_r10] = nData8;
                        pSource8++;
                        iTMEM = (iTMEM + 1) & 0xFFF;
                    }
                    pSource = (u64*)((u8*)pSource + nScanFull);
                    iTMEM += (pTile->nSizeX * 8) - nScanPart;
                    iTMEM &= 0xFFF;
                }
                break;
            case G_IM_SIZ_16b:
                if (nScanPart >= pTile->nSizeX * 4) {
                    nScanPart = pTile->nSizeX * 4;
                }
                iTMEM <<= 2;
                for (iScan = 0; iScan < nCount; iScan++) {
                    pSource16 = (u16*)pSource;
                    for (i = 0; i != nScanPart; i++) {
                        if (iScan & 1) {
                            temp_r10 = iTMEM ^ 2;
                        } else {
                            temp_r10 = iTMEM;
                        }
                        nData16 = *pSource16;
                        nSum += nData16;
                        nSum ^= iTMEM;
                        pFrame->TMEM.data.u16[temp_r10] = nData16;
                        pSource16++;
                        iTMEM = (iTMEM + 1) & 0x7FF;
                    }
                    pSource = (u64*)((u16*)pSource + nScanFull);
                    iTMEM = (iTMEM + ((pTile->nSizeX * 4) - nScanPart)) & 0x7FF;
                }
                break;
            case G_IM_SIZ_32b:
                if (nScanPart >= pTile->nSizeX * 4) {
                    nScanPart = pTile->nSizeX * 4;
                }
                iTMEM <<= 1;
                for (iScan = 0; iScan < nCount; iScan++) {
                    pSource32 = (u32*)pSource;
                    for (i = 0; i != nScanPart; i++) {
                        if (iScan & 1) {
                            temp_r10 = iTMEM ^ 2;
                        } else {
                            temp_r10 = iTMEM;
                        }
                        nData32 = *pSource32;
                        nSum += nData32;
                        nSum ^= iTMEM;
                        pFrame->TMEM.data.u32[temp_r10] = nData32;
                        pSource32++;
                        iTMEM = (iTMEM + 1) & 0x3FF;
                    }
                    pSource = (u64*)((u32*)pSource + nScanFull);
                    iTMEM += (pTile->nSizeX * 4) - nScanPart;
                    iTMEM &= 0x3FF;
                }
                break;
            default:
                return false;
        }
    }

    pFrame->nCodePixel = nSum;
    return true;
}

bool frameSetLightCount(Frame* pFrame, s32 nCount) {
    pFrame->nCountLight = nCount;
    return true;
}

bool frameSetLight(Frame* pFrame, s32 iLight, s8* pData) {
    Light* pLight;

    if (iLight >= 0 && iLight < 8) {
        pLight = &pFrame->aLight[iLight];
        pLight->bTransformed = false;

        if (pData[3] != 0) {
            pLight->kc = (u8)pData[3] * 0.0078125f + 0.0625f;
            pLight->kl = (u8)pData[7] / 4096.0f;
            pLight->kq = (u8)pData[14] / 4194304.0f;
            pLight->coordX = *(s16*)&pData[8];
            pLight->coordY = *(s16*)&pData[10];
            pLight->coordZ = *(s16*)&pData[12];
        } else {
            pLight->kc = 0.0f;
        }

        OSu8tof32((u8*)&pData[0], &pLight->rColorR);
        OSu8tof32((u8*)&pData[1], &pLight->rColorG);
        OSu8tof32((u8*)&pData[2], &pLight->rColorB);

        s8tof32Scaled128(&pData[8], &pLight->rVecOrigTowards.x);
        s8tof32Scaled128(&pData[9], &pLight->rVecOrigTowards.y);
        s8tof32Scaled128(&pData[10], &pLight->rVecOrigTowards.z);
        return true;
    } else {
        return false;
    }
}

bool frameSetLookAt(Frame* pFrame, s32 iLookAt, s8* pData) {
    switch (iLookAt) {
        case 0:
            s8tof32Scaled128(&pData[8], &pFrame->lookAt.rSRaw.x);
            s8tof32Scaled128(&pData[9], &pFrame->lookAt.rSRaw.y);
            s8tof32Scaled128(&pData[10], &pFrame->lookAt.rSRaw.z);
            pFrame->nMode |= 0x01000000;
            break;
        case 1:
            s8tof32Scaled128(&pData[8], &pFrame->lookAt.rTRaw.x);
            s8tof32Scaled128(&pData[9], &pFrame->lookAt.rTRaw.y);
            s8tof32Scaled128(&pData[10], &pFrame->lookAt.rTRaw.z);
            pFrame->nMode |= 0x02000000;
            break;
        default:
            return false;
    }

    pFrame->lookAt.bTransformed = false;
    return true;
}

bool frameSetViewport(Frame* pFrame, s16* pData) {
    s32 iScale;
    f32 arScale[3];
    f32 centerX;
    f32 centerY;
    f32 rX;
    f32 rY;
    f32 rSizeX;
    f32 rSizeY;
    s32 pad[3];

    arScale[0] = pData[0] / 4.0f;
    arScale[1] = pData[1] / 4.0f;
    arScale[2] = pData[2] / 4.0f;

    for (iScale = 0; iScale < 3; iScale++) {
        if (arScale[iScale] < 0.0f) {
            arScale[iScale] = -arScale[iScale];
        }
    }

    rSizeX = (arScale[0] * 2.0f) * pFrame->rScaleX;
    rSizeY = (arScale[1] * 2.0f) * pFrame->rScaleY;

    centerX = pData[4] / 4.0f;
    centerY = pData[5] / 4.0f;

    rX = (centerX - arScale[0]) * pFrame->rScaleX;
    rY = (centerY - arScale[1]) * pFrame->rScaleY;

    pFrame->viewport.rX = rX;
    pFrame->viewport.rY = rY;
    pFrame->viewport.rSizeX = rSizeX;
    pFrame->viewport.rSizeY = rSizeY;

    frameDrawReset(pFrame, 0x10000);
    return true;
}

bool frameResetUCode(Frame* pFrame, FrameResetType eType) {
    s32 iMode;

    pFrame->iMatrixModel = 0;
    pFrame->nMode &= 0x9C1F0000;
    if (eType == FRT_COLD) {
        pFrame->nMode &= ~0x1C000000;
        pFrame->iHintProjection = -1;
    }

    for (iMode = 0; iMode < ARRAY_COUNT(pFrame->aMode); iMode++) {
        pFrame->aMode[iMode] = 0;
    }

    pFrame->nWidthLine = -1;
    pFrame->nCountLight = 0;
    return true;
}

bool frameSetBuffer(Frame* pFrame, FrameBufferType eType) {
    if (eType == FBT_COLOR_SHOW || eType == FBT_COLOR_DRAW) {
    } else if (eType == FBT_DEPTH) {
        pFrame->nOffsetDepth0 = pFrame->aBuffer[FBT_DEPTH].nAddress & 0x03FFFFFF;
        pFrame->nOffsetDepth1 = pFrame->nOffsetDepth0 + 0x257FC;
    }

    return true;
}

bool frameFixMatrixHint(Frame* pFrame, s32 nAddressFloat, s32 nAddressFixed) {
    s32 iHint;
    s32 iHintTest;

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if (pFrame->aMatrixHint[iHint].nAddressFloat == nAddressFloat && pFrame->aMatrixHint[iHint].nCount >= 0) {
            pFrame->aMatrixHint[iHint].nAddressFloat = 0;
            pFrame->aMatrixHint[iHint].nAddressFixed = nAddressFixed;

            for (iHintTest = 0; iHintTest < pFrame->iHintMatrix; iHintTest++) {
                if (iHintTest != iHint && pFrame->aMatrixHint[iHintTest].nAddressFixed == nAddressFixed) {
                    pFrame->aMatrixHint[iHintTest].nAddressFloat = 0;
                    pFrame->aMatrixHint[iHintTest].nAddressFixed = 0;
                }
            }

            return true;
        }
    }

    return false;
}

static inline bool frameGetMatrixHint(Frame* pFrame, u32 nAddress, s32* piHint) {
    s32 iHint;

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if (pFrame->aMatrixHint[iHint].nAddressFixed == nAddress && pFrame->aMatrixHint[iHint].nCount >= 0) {
            pFrame->aMatrixHint[iHint].nCount = 4;
            *piHint = iHint;
            return true;
        }
    }

    return false;
}

bool frameSetMatrixHint(Frame* pFrame, FrameMatrixProjection eProjection, s32 nAddressFloat, s32 nAddressFixed,
                        f32 rNear, f32 rFar, f32 rFOVY, f32 rAspect, f32 rScale) {
    s32 iHint;

    if (nAddressFloat != 0) {
        nAddressFloat |= 0x80000000;
    }
    if (nAddressFixed != 0) {
        nAddressFixed |= 0x80000000;
    }

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if ((nAddressFloat != 0 && pFrame->aMatrixHint[iHint].nAddressFloat == nAddressFloat) ||
            (nAddressFixed != 0 && pFrame->aMatrixHint[iHint].nAddressFixed == nAddressFixed)) {
            break;
        }
    }

    if (iHint == pFrame->iHintMatrix) {
        for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
            if (pFrame->aMatrixHint[iHint].nCount < 0) {
                break;
            }
        }
    }

    if (eProjection == 1) {
        rNear = 0.0f;
    }

    pFrame->aMatrixHint[iHint].nCount = 4;
    pFrame->aMatrixHint[iHint].rScale = rScale;
    pFrame->aMatrixHint[iHint].rClipFar = rFar;
    pFrame->aMatrixHint[iHint].rClipNear = rNear;
    pFrame->aMatrixHint[iHint].rAspect = rAspect;
    pFrame->aMatrixHint[iHint].rFieldOfViewY = rFOVY;
    pFrame->aMatrixHint[iHint].eProjection = eProjection;
    pFrame->aMatrixHint[iHint].nAddressFloat = nAddressFloat;
    pFrame->aMatrixHint[iHint].nAddressFixed = nAddressFixed;

    if (iHint == pFrame->iHintMatrix) {
        pFrame->iHintMatrix++;
    }

    pFrame->iHintLast = iHint;
    return true;
}

bool frameInvalidateCache(Frame* pFrame, s32 nOffset0, s32 nOffset1) {
    s32 iTexture0;
    s32 iTexture1;
    FrameTexture* pTexture;
    FrameTexture* pTextureNext;

    iTexture0 = (nOffset0 & 0x7FFFFF) / 2048;
    iTexture1 = (nOffset1 & 0x7FFFFF) / 2048;
    while (iTexture0 <= iTexture1) {
        pTexture = pFrame->apTextureCached[iTexture0];
        while (pTexture != NULL) {
            pTextureNext = pTexture->pTextureNext;
            if (!frameFreeTexture(pFrame, pTexture)) {
                return false;
            }
            pTexture = pTextureNext;
        }
        pFrame->apTextureCached[iTexture0] = NULL;
        iTexture0 += 1;
    }

    return true;
}

bool frameGetTextureInfo(Frame* pFrame, TextureInfo* pInfo) {
    FrameTexture* pTexture;
    s32 iTexture;
    s32 nCount;
    s32 nSize;

    nSize = 0;
    nCount = 0;
    iTexture = 0;

    for (iTexture = 0; iTexture < ARRAY_COUNT(pFrame->apTextureCached); iTexture++) {
        pTexture = pFrame->apTextureCached[iTexture];

        while (pTexture != NULL) {
            nCount++;
            switch ((s32)pTexture->eFormat) {
                case GX_TF_I4:
                case GX_TF_C4:
                    nSize += ((pTexture->nSizeX * pTexture->nSizeY) + 1) >> 1;
                    break;
                case GX_TF_I8:
                case GX_TF_IA4:
                case GX_TF_C8:
                    nSize += pTexture->nSizeX * pTexture->nSizeY;
                    break;
                case GX_TF_IA8:
                case GX_TF_RGB565:
                case GX_TF_RGB5A3:
                    nSize += pTexture->nSizeX * pTexture->nSizeY * 2;
                    break;
                case GX_TF_RGBA8:
                    nSize += pTexture->nSizeX * pTexture->nSizeY * 4;
                    break;
                default:
                    OSReport("GetTextureInfo: Unknown texture-format: %d\n", pTexture->eFormat);
                    return false;
            }
            pTexture = pTexture->pTextureNext;
        }
    }

    pInfo->nSizeTextures = nSize + (nCount * sizeof(FrameTexture));
    pInfo->nCountTextures = nCount;
    return true;
}

ASM void PSMTX44MultVecNoW(Mtx44 m, Vec3f* src, Vec3f* dst){
#ifdef __MWERKS__ // clang-format off
    nofralloc

    psq_l   f0, 0(r4), 0, 0
    psq_l   f1, 8(r4), 1, 0
    psq_l   f4, 0(r3), 0, 0
    psq_l   f5, 8(r3), 0, 0
    psq_l   f6, 16(r3), 0, 0
    psq_l   f7, 24(r3), 0, 0
    psq_l   f8, 32(r3), 0, 0
    psq_l   f9, 40(r3), 0, 0
    ps_mul  f4, f0, f4
    ps_madd f2, f1, f5, f4
    ps_mul  f6, f0, f6
    ps_madd f3, f1, f7, f6
    ps_mul  f8, f0, f8
    ps_sum0 f2, f2, f2, f2
    ps_madd f9, f1, f9, f8
    ps_sum1 f2, f3, f2, f3
    ps_sum0 f3, f9, f9, f9
    psq_st  f2, 0(r5), 0, 0
    psq_st  f3, 8(r5), 1, 0
    blr
#endif // clang-format on
}

// clang-format off
s32 anRenderModeDatabaseCycle2[100] = {
    0x0C192078, 0x00552078, 0x0C184F50, 0x00504A50, 0x0F0A4000, 0xC8112078, 0x0C187858, 0x00442078,
    0x00553078, 0xC8113078, 0x00443078, 0x00552D58, 0xC8112D58, 0x005049D8, 0xC81049D8, 0x0C193078,
    0x00504240, 0x5F505240, 0x0C184240, 0x0C182048, 0x0C183048, 0x0C182078, 0x0C192D58, 0x0C1849D8,
    0x0F0A7008, 0x0C1841C8, 0x0C184DD8, 0x0C183078, 0x0C1845D8, 0x00504241, 0x0C184341, 0x0C184241,
    0xC8104DD8, 0xC8104F50, 0x00504341, 0xC8104A50, 0x00504340, 0x0C184340, 0xC8104B50, 0x0C184B50,
    0x0C184B51, 0x00504B51, 0x0F0A4004, 0x0F0A3231, 0x00504B50, 0xC81049F8, 0xC8103478, 0x005041C8,
    0xC4104240, 0x00552038, 0x0F0A100C, 0x0C184A50, 0xC8104A51, 0xC8112479, 0xC81045D8,
};

s32 anRenderModeDatabaseCopy[100] = {
    0x0F0A7008, 0x00000001, 0x0F0A4001, 0x00442478, 0x00442479, 0x005041C9, 0x00552079, 0x00552078,
    0x005045D8, 0x005045D9, 0x00504DD8, 0x00504DD9, 0x00553078, 0x00553079, 0x0F0A4000, 0x005049D8,
    0x005049D9, 0x00442078, 0x00442079, 0x0F0A7009, 0x00504240,
};

s32 anRenderModeDatabaseFill[100] = {
    0x0F0A4000, 0x0C084000, 0x00000001, 0x0F0A4001, 0x00504240, 0xC8112078, 0x00504341, 0x00504244,
    0x00504340, 0x00504241, 0x00504B50, 0x0C184241, 0x0F0A4004, 0x00553049, 0x00552078, 0x0F0A100C,
};

s32 anRenderModeDatabaseCycle1[100] = {
    0x0F0A4000, 0x00552048, 0x0F0A7008, 0x00552078, 0x0C084000, 0x00504241, 0x00504240, 0x0F0A4001,
    0x005041C8, 0x00552D58, 0x0C184F50, 0x00504F50, 0x0C192078, 0x00504A50, 0x00000001, 0x005049D8,
    0xC8112078, 0x0C187858, 0x00552230, 0x00442478, 0x00443078, 0x00442479, 0x00443079, 0x005041C9,
    0x00553048, 0x00553078, 0x00504DD8, 0x005045D8, 0x004049F8, 0x004049D8, 0x00442078, 0xC8113078,
    0x005049DB, 0x00442D58, 0xC8112D58, 0x004049F8, 0xC81049D8, 0x0C193078, 0x00504B50, 0x00504340,
    0x5F505240, 0x0C182078, 0x0C182048, 0x0F0A7009, 0x0C1841C8, 0x0C184240, 0x0C1849D8, 0x00504244,
    0x0C184340, 0x00504B51, 0x0C184B50, 0x0F0A4004, 0x0F0A4044, 0x0F0A0004, 0xC8104B50, 0x0FA54044,
    0x00504341, 0x00553049, 0x0F0A3231, 0xC8104F50, 0x00552038, 0xC4104240, 0x00504344,
};
// clang-format on
