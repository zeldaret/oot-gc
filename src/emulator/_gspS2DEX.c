#include "emulator/frame.h"
#include "emulator/rsp.h"

static u16 scissorX0 = 0 << 2;
static u16 scissorY0 = 0 << 2;
static u16 scissorX1 = N64_FRAME_WIDTH << 2;
static u16 scissorY1 = N64_FRAME_HEIGHT << 2;
static u8 flagBilerp;

static u32 rdpSetTimg_w0;
static u32 rdpSetTile_w0;
static u16 tmemSliceWmax;
static u16 imageSrcWsize;
static u16 flagSplit;
static u16 imagePtrX0;
static u32 imageTop;
static s16 tmemSrcLines;

static inline bool frameFillVertex(Frame* pFrame, s32 nIndex, s16 nX, s16 nY, s16 nZ, f32 rS, f32 rT) {
    pFrame->aVertex[nIndex].vec.x = nX;
    pFrame->aVertex[nIndex].vec.y = nY;
    pFrame->aVertex[nIndex].vec.z = nZ;
    pFrame->aVertex[nIndex].rS = rS;
    pFrame->aVertex[nIndex].rT = rT;
    return true;
}

static bool Matrix4by4Identity(Mtx44Ptr matrix4b4) {
    matrix4b4[0][0] = 1.0f;
    matrix4b4[1][0] = 0.0f;
    matrix4b4[2][0] = 0.0f;
    matrix4b4[3][0] = 0.0f;
    matrix4b4[0][1] = 0.0f;
    matrix4b4[1][1] = 1.0f;
    matrix4b4[2][1] = 0.0f;
    matrix4b4[3][1] = 0.0f;
    matrix4b4[0][2] = 0.0f;
    matrix4b4[1][2] = 0.0f;
    matrix4b4[2][2] = 1.0f;
    matrix4b4[3][2] = 0.0f;
    matrix4b4[0][3] = 0.0f;
    matrix4b4[1][3] = 0.0f;
    matrix4b4[2][3] = 0.0f;
    matrix4b4[3][3] = 1.0f;

    return true;
}

static bool rspFillObjSprite(Rsp* pRSP, s32 nAddress, uObjSprite* pSprite) {
    u16* pnData16;
    u8* pnData8;
    u8* pObjSprite;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pObjSprite, nAddress, NULL)) {
        return false;
    }

    pnData8 = (u8*)pObjSprite;
    pnData16 = (u16*)pObjSprite;

    pSprite->s.objX = pnData16[0];
    pSprite->s.scaleW = pnData16[1];
    pSprite->s.imageW = pnData16[2];
    pSprite->s.paddingX = pnData16[3];
    pSprite->s.objY = pnData16[4];
    pSprite->s.scaleH = pnData16[5];
    pSprite->s.imageH = pnData16[6];
    pSprite->s.paddingY = pnData16[7];
    pSprite->s.imageStride = pnData16[8];
    pSprite->s.imageAdrs = pnData16[9];
    pSprite->s.imageFmt = pnData8[20];
    pSprite->s.imageSiz = pnData8[21];
    pSprite->s.imagePal = pnData8[22];
    pSprite->s.imageFlags = pnData8[23];

    return true;
}

bool rspFillObjBgScale(Rsp* pRSP, s32 nAddress, uObjBg* pBg) {
    u8* pnData8;
    u8* pObjBg;
    u16* pnData16;
    u32* pnData32;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pObjBg, nAddress, NULL)) {
        return false;
    }

    pnData8 = (u8*)pObjBg;
    pnData16 = (u16*)pObjBg;
    pnData32 = (u32*)pObjBg;

    pBg->s.imageX = pnData16[0];
    pBg->s.imageW = pnData16[1];
    pBg->s.frameX = pnData16[2];
    pBg->s.frameW = pnData16[3];
    pBg->s.imageY = pnData16[4];
    pBg->s.imageH = pnData16[5];
    pBg->s.frameY = pnData16[6];
    pBg->s.frameH = pnData16[7];
    pBg->s.imagePtr = pnData32[4];
    pBg->s.imageLoad = pnData16[10];
    pBg->s.imageFmt = pnData8[22];
    pBg->s.imageSiz = pnData8[23];
    pBg->s.imagePal = pnData16[12];
    pBg->s.imageFlip = pnData16[13];
    pBg->s.scaleW = pnData16[14];
    pBg->s.scaleH = pnData16[15];
    pBg->s.imageYorig = pnData32[8];

    return true;
}

bool rspFillObjBg(Rsp* pRSP, s32 nAddress, uObjBg* pBg) {
    u8* pnData8;
    u8* pObjBg;
    u16* pnData16;
    u32* pnData32;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pObjBg, nAddress, NULL)) {
        return false;
    }

    pnData8 = (u8*)pObjBg;
    pnData16 = (u16*)pObjBg;
    pnData32 = (u32*)pObjBg;

    pBg->b.imageX = pnData16[0];
    pBg->b.imageW = pnData16[1];
    pBg->b.frameX = pnData16[2];
    pBg->b.frameW = pnData16[3];
    pBg->b.imageY = pnData16[4];
    pBg->b.imageH = pnData16[5];
    pBg->b.frameY = pnData16[6];
    pBg->b.frameH = pnData16[7];
    pBg->b.imagePtr = pnData32[4];
    pBg->b.imageLoad = pnData16[10];
    pBg->b.imageFmt = pnData8[22];
    pBg->b.imageSiz = pnData8[23];
    pBg->b.imagePal = pnData16[12];
    pBg->b.imageFlip = pnData16[13];
    pBg->b.tmemW = pnData16[14];
    pBg->b.tmemH = pnData16[15];
    pBg->b.tmemLoadSH = pnData16[16];
    pBg->b.tmemLoadTH = pnData16[17];
    pBg->b.tmemSizeW = pnData16[18];
    pBg->b.tmemSize = pnData16[19];

    return true;
}

static inline bool rspSetTile(Frame* pFrame, Tile* pTile, s32 nSize, s32 nTmem, s32 nTLUT, s32 nFormat, s32 nMaskS,
                              s32 nMaskT, s32 nModeS, s32 nModeT, s32 nShiftS, s32 nShiftT) {
    pTile->nSize = nSize;
    pTile->nTMEM = nTmem;
    pTile->iTLUT = nTLUT;
    pTile->nFormat = nFormat;
    pTile->nMaskS = nMaskS;
    pTile->nMaskT = nMaskT;
    pTile->nModeS = nModeS;
    pTile->nModeT = nModeT;
    pTile->nShiftS = nShiftS;
    pTile->nShiftT = nShiftT;
    if (!frameDrawReset(pFrame, 1)) {
        return false;
    }
    return true;
}

bool rspSetImage(Frame* pFrame, Rsp* pRSP, s32 nFormat, s32 nWidth, s32 nSize, s32 nImage) {
    FrameBuffer* pBuffer;
    s32 nAddr;

    pBuffer = &pFrame->aBuffer[FBT_IMAGE];
    pBuffer->nFormat = nFormat;
    pBuffer->nWidth = nWidth;
    pBuffer->nSize = nSize;
    nAddr = SEGMENT_ADDRESS(pRSP, nImage);
    pBuffer->nAddress = nAddr;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pBuffer->pData, nAddr, NULL)) {
        return false;
    }

    if (!frameSetBuffer(pFrame, FBT_IMAGE)) {
        return false;
    }

    return true;
}

static inline bool rspLoadBlock(Frame* pFrame, Tile* pTile, s32 nX0, s32 nY0, s32 nX1, s32 nY1) {
    pTile->nX0 = nX0;
    pTile->nY0 = nY0;
    pTile->nX1 = nX1;
    pTile->nY1 = nY1;
    if (!frameLoadTMEM(pFrame, FLT_BLOCK, 0)) {
        return false;
    }
    return true;
}

static inline bool rspLoadTile(Frame* pFrame, Tile* pTile, s32 nX0, s32 nY0, s32 nX1, s32 nY1) {
    pTile->nX0 = nX0;
    pTile->nY0 = nY0;
    pTile->nX1 = nX1;
    pTile->nY1 = nY1;
    if (!frameLoadTMEM(pFrame, FLT_TILE, 0)) {
        return false;
    }
    return true;
}

static inline bool rspSetTileSize(Frame* pFrame, Tile* pTile, s32 nX0, s32 nY0, s32 nX1, s32 nY1) {
    pTile->nX0 = nX0;
    pTile->nY0 = nY0;
    pTile->nX1 = nX1;
    pTile->nY1 = nY1;
    if (!frameDrawReset(pFrame, 1)) {
        return false;
    }
    return true;
}

static bool tmemLoad_B(Frame* pFrame, Rsp* pRSP, u32 imagePtr, s16 loadLines, s16 tmemSH) {
    FrameBuffer* pBuffer;
    s32 nAddr;

    pBuffer = &pFrame->aBuffer[FBT_IMAGE];
    pBuffer->nFormat = 0;
    pBuffer->nWidth = imageSrcWsize >> 1;
    pBuffer->nSize = 2;
    nAddr = SEGMENT_ADDRESS(pRSP, imagePtr);
    pBuffer->nAddress = nAddr;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pBuffer->pData, nAddr, NULL)) {
        return false;
    }

    if (!frameSetBuffer(pFrame, FBT_IMAGE)) {
        return false;
    }

    pFrame->aTile[7].nX0 = 0;
    pFrame->aTile[7].nY0 = 0;
    pFrame->aTile[7].nX1 = (tmemSH - 1) * 16;
    pFrame->aTile[7].nY1 = (loadLines * 4) - 1;

    if (!frameLoadTMEM(pFrame, FLT_TILE, 7)) {
        return false;
    }

    return true;
}

static bool tmemLoad_A(Frame* pFrame, Rsp* pRSP, s32 imagePtr, s16 loadLines, s16 tmemAdrs, s16 tmemSH) {
    pFrame->aTile[7].nSize = 2;
    pFrame->aTile[7].nTMEM = tmemAdrs;
    pFrame->aTile[7].iTLUT = 0;
    pFrame->aTile[7].nSizeX = tmemSliceWmax;
    pFrame->aTile[7].nFormat = 0;
    pFrame->aTile[7].nMaskS = 0;
    pFrame->aTile[7].nMaskT = 0;
    pFrame->aTile[7].nModeS = 0;
    pFrame->aTile[7].nModeT = 0;
    pFrame->aTile[7].nShiftS = 0;
    pFrame->aTile[7].nShiftT = 0;

    if (!frameDrawReset(pFrame, 0x1)) {
        return false;
    }

    tmemLoad_B(pFrame, pRSP, imagePtr, loadLines, tmemSH);

    NO_INLINE();
    return true;
}

// Similar to
// https://github.com/decompals/ultralib/blob/1616482098e51d2e1906e198bf1bde14e8fc5e90/src/gu/us2dex_emu.c#L97
static bool tmemLoad(Frame* pFrame, Rsp* pRSP, u32* imagePtr, s16* imageRemain, s16 drawLines, s16 flagBilerp) {
    s16 loadLines = drawLines + flagBilerp;
    s16 iLoadable = *imageRemain - flagSplit;

    if (iLoadable >= loadLines) {
        tmemLoad_B(pFrame, pRSP, *imagePtr, loadLines, tmemSliceWmax);
        *imagePtr += imageSrcWsize * drawLines;
        *imageRemain -= drawLines;
    } else {
        s16 SubSliceL2, SubSliceD2, SubSliceY2;
        u32 imageTopSeg = imageTop & 0xFF000000;

        SubSliceY2 = *imageRemain;
        SubSliceL2 = loadLines - SubSliceY2;
        SubSliceD2 = drawLines - SubSliceY2;

        if (SubSliceL2 > 0) {
            u32 imagePtr2 = imageTop + imagePtrX0;

            if (SubSliceY2 & 1) {
                imagePtr2 -= imageSrcWsize;
                imagePtr2 = imageTopSeg | (imagePtr2 & 0xFFFFFF);
                SubSliceY2--;
                SubSliceL2++;
            }
            tmemLoad_A(pFrame, pRSP, imagePtr2, SubSliceL2, SubSliceY2 * tmemSliceWmax, tmemSliceWmax);
        }
        if (flagSplit) {
            u32 imagePtr1A, imagePtr1B;
            s16 SubSliceY1, SubSliceL1;
            s16 tmemSH_A, tmemSH_B;

            imagePtr1A = *imagePtr + iLoadable * imageSrcWsize;
            imagePtr1B = imageTop;
            SubSliceY1 = iLoadable;

            if (iLoadable & 1) {
                imagePtr1A -= imageSrcWsize;
                imagePtr1B -= imageSrcWsize;
                imagePtr1B = imageTopSeg | (imagePtr1B & 0xFFFFFF);
                SubSliceY1--;
                SubSliceL1 = 2;
            } else {
                SubSliceL1 = 1;
            }
            tmemSH_A = (imageSrcWsize - imagePtrX0) >> 3;
            tmemSH_B = tmemSliceWmax - tmemSH_A;
            tmemLoad_A(pFrame, pRSP, imagePtr1B, SubSliceL1, SubSliceY1 * tmemSliceWmax + tmemSH_A, tmemSH_B);
            tmemLoad_A(pFrame, pRSP, imagePtr1A, SubSliceL1, SubSliceY1 * tmemSliceWmax, tmemSH_A);
        }

        if (iLoadable > 0) {
            tmemLoad_A(pFrame, pRSP, *imagePtr, iLoadable, 0, tmemSliceWmax);
        } else {
            pFrame->aTile[7].nSize = 2;
            pFrame->aTile[7].nTMEM = 0;
            pFrame->aTile[7].iTLUT = 0;
            pFrame->aTile[7].nSizeX = tmemSliceWmax;
            pFrame->aTile[7].nFormat = 0;
            pFrame->aTile[7].nMaskS = 0;
            pFrame->aTile[7].nMaskT = 0;
            pFrame->aTile[7].nModeS = 0;
            pFrame->aTile[7].nModeT = 0;
            pFrame->aTile[7].nShiftS = 0;
            pFrame->aTile[7].nShiftT = 0;

            if (!frameDrawReset(pFrame, 0x1)) {
                return false;
            }
        }

        *imageRemain -= drawLines;
        if (*imageRemain > 0) {
            *imagePtr += imageSrcWsize * drawLines;
        } else {
            *imageRemain = tmemSrcLines - SubSliceD2;
            *imagePtr = imageTop + SubSliceD2 * imageSrcWsize + imagePtrX0;
        }
    }

    return true;
}

static inline bool guS2DEmuSetScissor(u32 ulx, u32 uly, u32 lrx, u32 lry, u8 flag) {
    scissorX0 = ulx;
    scissorY0 = uly;
    scissorX1 = lrx;
    scissorY1 = lry;
    flagBilerp = flag;
    return true;
}

// Similar to
// https://github.com/decompals/ultralib/blob/1616482098e51d2e1906e198bf1bde14e8fc5e90/src/gu/us2dex_emu.c#L177
static bool guS2DEmuBgRect1Cyc(Rsp* pRSP, Frame* pFrame, uObjBg* pBG) {
    s32 pad;

    s16 frameX0, frameX1, framePtrY0, frameRemain;
    s16 imageX0, imageY0, imageSliceW, imageW;
    s32 imageYorig;
    s16 scaleW, scaleH;

    s16 imageSrcW, imageSrcH;
    s16 tmemSliceLines, imageSliceLines;
    s32 frameSliceLines, frameSliceCount;
    u16 imageS, imageT;
    u32 imagePtr;

    s16 imageISliceL0, imageIY0;
    s32 frameLSliceL0;

    scaleW = pBG->s.scaleW;
    scaleH = pBG->s.scaleH;

    {
        s16 pixX0, pixY0, pixX1, pixY1;
        s16 frameY0, frameW, frameH;
        s32 frameWmax, frameHmax;

        frameWmax = (((pBG->s.imageW << 10) / scaleW) - 1) & ~3;
        frameHmax = (((pBG->s.imageH << 10) / scaleH) - 1) & ~3;

        frameW = pBG->s.frameW;
        frameH = pBG->s.frameH;
        frameX0 = pBG->s.frameX;
        frameY0 = pBG->s.frameY;

        if ((frameWmax = pBG->s.frameW - frameWmax) < 0) {
            frameWmax = 0;
        }
        if ((frameHmax = pBG->s.frameH - frameHmax) < 0) {
            frameHmax = 0;
        }

        frameW -= (s16)frameWmax;
        frameH -= (s16)frameHmax;

        if (pBG->s.imageFlip & 1) {
            frameX0 += (s16)frameWmax;
        }

        pixX0 = scissorX0 - frameX0;
        pixY0 = scissorY0 - frameY0;
        pixX1 = frameW - scissorX1 + frameX0;
        pixY1 = frameH - scissorY1 + frameY0;

        if (pixX0 < 0) {
            pixX0 = 0;
        }
        if (pixY0 < 0) {
            pixY0 = 0;
        }
        if (pixX1 < 0) {
            pixX1 = 0;
        }
        if (pixY1 < 0) {
            pixY1 = 0;
        }

        frameW = frameW - (pixX0 + pixX1);
        frameH = frameH - (pixY0 + pixY1);
        frameX0 = frameX0 + pixX0;
        frameY0 = frameY0 + pixY0;

        if (frameW <= 0 || frameH <= 0) {
            return true;
        }

        frameX1 = frameX0 + frameW;
        framePtrY0 = frameY0 >> 2;
        frameRemain = frameH >> 2;

        imageSrcW = pBG->s.imageW << 3;
        imageSrcH = pBG->s.imageH << 3;

        imageSliceW = (imageW = frameW * scaleW >> 7) + flagBilerp * 32;
        if (pBG->s.imageFlip & 1) {
            imageX0 = pBG->s.imageX + (pixX1 * scaleW >> 7);
        } else {
            imageX0 = pBG->s.imageX + (pixX0 * scaleW >> 7);
        }
        imageY0 = pBG->s.imageY + (pixY0 * scaleH >> 7);
        imageYorig = pBG->s.imageYorig;

        while (imageX0 >= imageSrcW) {
            imageX0 -= imageSrcW;
            imageY0 += 32;
            imageYorig += 32;
        }

        while (imageY0 >= imageSrcH) {
            imageY0 -= imageSrcH;
            imageYorig -= imageSrcH;
        }
    }

    {
        flagSplit = (imageX0 + imageSliceW >= imageSrcW);
        tmemSrcLines = imageSrcH >> 5;
    }

    {
        s16 tmemSize, tmemMask, tmemShift;
        s32 imageNumSlice;
        s32 imageSliceWmax;
        s32 imageLYoffset, frameLYoffset;
        s32 imageLHidden, frameLHidden;
        s32 frameLYslice;
        static s16 TMEMSIZE[] = {512, 512, 256, 512, 512};
        static s16 TMEMMASK[] = {0x1FF, 0xFF, 0x7F, 0x3F};
        static s16 TMEMSHIFT[] = {0x200, 0x100, 0x80, 0x40};

        tmemSize = TMEMSIZE[pBG->s.imageFmt];
        tmemMask = TMEMMASK[pBG->s.imageSiz];
        tmemShift = TMEMSHIFT[pBG->s.imageSiz];

        imageSliceWmax = ((pBG->s.frameW * scaleW) >> 7) + (flagBilerp << 5);
        if (imageSliceWmax > imageSrcW) {
            imageSliceWmax = imageSrcW;
        }

        tmemSliceWmax = (imageSliceWmax + tmemMask) / tmemShift + 1;
        tmemSliceLines = tmemSize / tmemSliceWmax;
        imageSliceLines = tmemSliceLines - flagBilerp;
        frameSliceLines = (imageSliceLines << 20) / scaleH;

        imageLYoffset = (imageY0 - imageYorig) << 5;
        if (imageLYoffset < 0) {
            imageLYoffset -= (scaleH - 1);
        }
        frameLYoffset = imageLYoffset / scaleH;
        frameLYoffset <<= 10;

        if (frameLYoffset >= 0) {
            imageNumSlice = frameLYoffset / frameSliceLines;
        } else {
            imageNumSlice = (frameLYoffset - frameSliceLines + 1) / frameSliceLines;
        }

        frameLYslice = (frameLSliceL0 = frameSliceLines * imageNumSlice) & ~1023;
        frameLHidden = frameLYoffset - frameLYslice;
        imageLHidden = (frameLHidden >> 10) * scaleH;

        frameLSliceL0 = (frameLSliceL0 & 1023) + frameSliceLines - frameLHidden;

        imageT = (imageLHidden >> 5) & 31;
        imageLHidden >>= 10;
        imageISliceL0 = imageSliceLines - (s16)imageLHidden;
        imageIY0 = imageSliceLines * imageNumSlice + (imageYorig & ~31) / 32 + imageLHidden;
        if (imageIY0 < 0) {
            imageIY0 += (pBG->s.imageH >> 2);
        }
        if (imageIY0 >= (pBG->s.imageH >> 2)) {
            imageIY0 -= (pBG->s.imageH >> 2);
        }

        imageTop = (u32)pBG->s.imagePtr;
        imageSrcWsize = (imageSrcW / tmemShift) << 3;
        imagePtrX0 = (imageX0 / tmemShift) << 3;
        imagePtr = imageTop + imageSrcWsize * imageIY0 + imagePtrX0;

        imageS = imageX0 & tmemMask;
        if (pBG->s.imageFlip & 1) {
            imageS = -(imageS + imageW);
        }
    }

    {
        rdpSetTimg_w0 = 0x100000 + (imageSrcWsize >> 1) - 1;
        rdpSetTile_w0 = 0x100000 + (tmemSliceWmax << 9);

        pFrame->aTile[7].nSize = 2;
        pFrame->aTile[7].nTMEM = 0;
        pFrame->aTile[7].iTLUT = 0;
        pFrame->aTile[7].nSizeX = tmemSliceWmax;
        pFrame->aTile[7].nFormat = 0;
        pFrame->aTile[7].nMaskS = 0;
        pFrame->aTile[7].nMaskT = 0;
        pFrame->aTile[7].nModeS = 0;
        pFrame->aTile[7].nModeT = 0;
        pFrame->aTile[7].nShiftS = 0;
        pFrame->aTile[7].nShiftT = 0;
        if (!frameDrawReset(pFrame, 1)) {
            return false;
        }

        pFrame->aTile[0].nSize = pBG->s.imageSiz;
        pFrame->aTile[0].nTMEM = 0;
        pFrame->aTile[0].iTLUT = pBG->s.imagePal;
        pFrame->aTile[0].nSizeX = tmemSliceWmax;
        pFrame->aTile[0].nFormat = pBG->s.imageFmt;
        pFrame->aTile[0].nMaskS = 0xF;
        pFrame->aTile[0].nMaskT = 0xF;
        pFrame->aTile[0].nModeS = 1;
        pFrame->aTile[0].nModeT = 1;
        pFrame->aTile[0].nShiftS = 0;
        pFrame->aTile[0].nShiftT = 0;
        if (!frameDrawReset(pFrame, 1)) {
            return false;
        }

        pFrame->aTile[0].nX0 = 0;
        pFrame->aTile[0].nY0 = 0;
        pFrame->aTile[0].nX1 = 0;
        pFrame->aTile[0].nY1 = 0;
        if (!frameDrawReset(pFrame, 1)) {
            return false;
        }
    }

    {
        s16 imageRemain;
        s16 imageSliceH, frameSliceH;

        imageRemain = tmemSrcLines - imageIY0;
        imageSliceH = imageISliceL0;
        frameSliceCount = frameLSliceL0;

        while (true) {
            frameSliceH = frameSliceCount >> 10;
            if (frameSliceH <= 0) {
                imageRemain -= imageSliceH;
                if (imageRemain > 0) {
                    imagePtr += imageSrcWsize * imageSliceH;
                } else {
                    imagePtr = imageTop - imageRemain * imageSrcWsize + imagePtrX0;
                    imageRemain += tmemSrcLines;
                }
            } else {
                Rectangle primitive;
                s16 nS, nT;
                s16 framePtrY1;

                frameSliceCount &= 1023;
                frameRemain -= frameSliceH;
                if (frameRemain < 0) {
                    frameSliceH += frameRemain;
                    imageSliceH += (frameRemain * scaleH >> 10) + 1;
                    if (imageSliceH > imageSliceLines) {
                        imageSliceH = imageSliceLines;
                    }
                }
                tmemLoad(pFrame, pRSP, &imagePtr, &imageRemain, imageSliceH, flagBilerp);

                framePtrY1 = framePtrY0 + frameSliceH;

                primitive.iTile = 0;
                primitive.bFlip = false;

                nS = imageS - 8 * pFrame->aTile[primitive.iTile].nX0;
                nT = imageT - 8 * pFrame->aTile[primitive.iTile].nY0;

                primitive.rS = nS / 32.0f;
                primitive.rT = nT / 32.0f;
                primitive.rDeltaS = scaleW / 1024.0f;
                primitive.rDeltaT = scaleH / 1024.0f;
                if (pBG->s.imageFlip & 1) {
                    primitive.rS *= -1.0f;
                    primitive.rDeltaS *= -1.0f;
                }
                primitive.nX0 = frameX0 << 0;
                primitive.nY0 = framePtrY0 << 2;
                primitive.nX1 = frameX1 << 0;
                primitive.nY1 = framePtrY1 << 2;
                if (!pFrame->aDraw[3](pFrame, &primitive)) {
                    return false;
                }

                framePtrY0 = framePtrY1;
                if (frameRemain <= 0) {
                    return true;
                }
            }

            frameSliceCount += frameSliceLines;
            imageSliceH = imageSliceLines;
            imageT = 0;
        }
    }
}

bool rspFillObjTxtr(Rsp* pRSP, s32 nAddress, uObjTxtr* pTxtr, u32* pLoadType) {
    u32* pnData32;
    u16* pnData16;
    u8* pTxtrBlock;
    u32 nLoadType;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pTxtrBlock, nAddress, NULL)) {
        return false;
    }

    pnData32 = (u32*)pTxtrBlock;
    pnData16 = (u16*)pTxtrBlock;
    nLoadType = pnData32[0];

    switch (nLoadType) {
        case G_OBJLT_TXTRBLOCK:
            pTxtr->block.type = nLoadType;
            pTxtr->block.image = pnData32[1];
            pTxtr->block.sid = pnData16[7];
            pTxtr->block.flag = pnData32[4];
            pTxtr->block.mask = pnData32[5];
            pTxtr->block.tmem = pnData16[4];
            pTxtr->block.tsize = pnData16[5];
            pTxtr->block.tline = pnData16[6];
            break;
        case G_OBJLT_TXTRTILE:
            pTxtr->tile.type = nLoadType;
            pTxtr->tile.image = pnData32[1];
            pTxtr->tile.sid = pnData16[7];
            pTxtr->tile.flag = pnData32[4];
            pTxtr->tile.mask = pnData32[5];
            pTxtr->tile.tmem = pnData16[4];
            pTxtr->tile.twidth = pnData16[5];
            pTxtr->tile.theight = pnData16[6];
            break;
        case G_OBJLT_TLUT:
            pTxtr->tlut.type = nLoadType;
            pTxtr->tlut.image = pnData32[1];
            pTxtr->tlut.sid = pnData16[7];
            pTxtr->tlut.flag = pnData32[4];
            pTxtr->tlut.mask = pnData32[5];
            pTxtr->tlut.phead = pnData16[4];
            pTxtr->tlut.pnum = pnData16[5];
            break;
        default:
            return false;
    }

    if (pLoadType != NULL) {
        *pLoadType = nLoadType;
    }
    return true;
}

static bool rspObjLoadTxtr(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    u32 nSizDefine;
    u32 nLoadType;
    s32 nAddr;
    Tile* pTile;
    FrameBuffer* pBuffer;
    uObjTxtr objTxtr;

    pTile = pFrame->aTile;
    pBuffer = &pFrame->aBuffer[FBT_IMAGE];
    if (!rspFillObjTxtr(pRSP, nAddress, &objTxtr, &nLoadType)) {
        return false;
    }

    switch (nLoadType) {
        case G_OBJLT_TXTRBLOCK:
            pBuffer->nFormat = 0;
            pBuffer->nWidth = 1;
            if (objTxtr.block.tsize > 0x3FF) {
                objTxtr.block.tsize = objTxtr.block.tsize / 2;
                nSizDefine = G_IM_SIZ_32b;
            } else {
                nSizDefine = G_IM_SIZ_16b;
            }
            pBuffer->nSize = nSizDefine;
            nAddr = SEGMENT_ADDRESS(pRSP, objTxtr.block.image);
            pBuffer->nAddress = nAddr;
            if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pBuffer->pData, nAddr, NULL)) {
                return false;
            }
            if (!frameSetBuffer(pFrame, FBT_IMAGE)) {
                return false;
            }
            if (!rspSetTile(pFrame, pTile, nSizDefine, objTxtr.block.tmem, 0, G_IM_FMT_RGBA, 0, 0, 0, 0, 0, 0)) {
                return false;
            }
            if (!rspLoadBlock(pFrame, pTile, 0, 0, objTxtr.block.tsize << 2, objTxtr.block.tline)) {
                return false;
            }
            pFrame->n2dLoadTexType = nLoadType;
            break;
        case G_OBJLT_TXTRTILE:
            if (!rspSetImage(pFrame, pRSP, 0, objTxtr.tile.twidth, 2, objTxtr.tile.image)) {
                return false;
            }
            !pFrame; // fake
            if (!rspSetTile(pFrame, pTile, G_IM_SIZ_16b, 0, 0, G_IM_FMT_RGBA, 0, 0, 0, 0, 0, 0)) {
                return false;
            }
            if (!rspLoadTile(pFrame, pTile, 0, 0, objTxtr.tile.twidth << 2, objTxtr.tile.theight)) {
                return false;
            }
            pFrame->n2dLoadTexType = nLoadType;
            pFrame->nLastX0 = 0;
            pFrame->nLastY0 = 0;
            pFrame->nLastX1 = objTxtr.tile.twidth << 2;
            pFrame->nLastY1 = objTxtr.tile.theight;
            break;
        case G_OBJLT_TLUT:
            if (!rspSetImage(pFrame, pRSP, G_IM_FMT_RGBA, 1, G_IM_SIZ_16b, objTxtr.tlut.image)) {
                return false;
            }
            if (!rspSetTile(pFrame, pTile, G_IM_SIZ_4b, objTxtr.tlut.phead, 0, G_IM_FMT_RGBA, 0, 0, 0, 0, 0, 0)) {
                return false;
            }
            if (!frameLoadTLUT(pFrame, objTxtr.tlut.pnum, 0)) {
                return false;
            }
            break;
        default:
            return false;
    }

    return true;
}

static bool rspObjRectangle(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    s32 pad;
    u16 nSizLineBytes;
    f32 fDeltaS;
    f32 fDeltaT;
    uObjSprite objSprite;
    Tile* pTile;
    Rectangle primitive;
    s32 nClampSetting;
    s32 nTexTrim2;
    s32 nTexTrim5;

    nTexTrim2 = 0;
    nTexTrim5 = 0;
    pTile = &pFrame->aTile[0];
    if (!rspFillObjSprite(pRSP, nAddress, &objSprite)) {
        return false;
    }

    nClampSetting = pRSP->nMode2D & 1;
    if (pRSP->nMode2D & 0x10) {
        nTexTrim2 = -2;
        nTexTrim5 = -16;
    } else if (pRSP->nMode2D & 0x20) {
        nTexTrim2 = -4;
        nTexTrim5 = -32;
    }
    if (pRSP->nMode2D & 0x40) {
        nTexTrim2 += 1;
        nTexTrim5 += 12;
    }

    objSprite.s.imageW += nTexTrim5;
    objSprite.s.imageH += nTexTrim5;
    pFrame->nLastX1 += nTexTrim2;

    if (pTile->nSize != 0) {
        switch (objSprite.s.imageSiz) {
            case G_IM_SIZ_32b:
                nSizLineBytes = 2;
                break;
            case G_IM_SIZ_16b:
                nSizLineBytes = 2;
                break;
            case G_IM_SIZ_8b:
                nSizLineBytes = 1;
                break;
            default:
                return false;
        }
        if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
            pTile->nSizeX = objSprite.s.imageStride;
        } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
            pTile->nSizeX = (((pFrame->nLastX1 - pFrame->nLastX0 + 1) >> 5) * nSizLineBytes + 7) >> 3;
        }
    } else {
        if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
            pTile->nSizeX = ((objSprite.s.imageW >> 6) + 7) >> 3;
        } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
            pTile->nSizeX = (((pFrame->nLastX1 - pFrame->nLastX0) >> 6) + 7) >> 3;
        }
    }

    if (!rspSetTile(pFrame, pTile, objSprite.s.imageSiz, objSprite.s.imageAdrs, objSprite.s.imagePal,
                    objSprite.s.imageFmt, 0, 0, nClampSetting, nClampSetting, 0, 0)) {
        return false;
    }
    if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
        if (!rspSetTileSize(pFrame, pTile, 0, 0, ((objSprite.s.imageW >> 5) - 1) << 2,
                            ((objSprite.s.imageH >> 5) - 1) << 2)) {
            return false;
        }
    } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
        if (!rspSetTileSize(pFrame, pTile, (pFrame->nLastX0 >> 5) << 2, (pFrame->nLastY0 >> 5) << 2,
                            (pFrame->nLastX1 >> 5) << 2, (pFrame->nLastY1 >> 5) << 2)) {
            return false;
        }
    }

    primitive.nX0 = objSprite.s.objX;
    primitive.nY0 = objSprite.s.objY;
    primitive.nX1 =
        ((s32)(((objSprite.s.imageW - 1.0f) * (1024.0f / objSprite.s.scaleW)) + 8 * objSprite.s.objX) >> 3) - 2;
    primitive.nY1 =
        ((s32)(((objSprite.s.imageH - 1.0f) * (1024.0f / objSprite.s.scaleH)) + 8 * objSprite.s.objY) >> 3) - 2;
    primitive.iTile = 0;
    primitive.bFlip = false;
    fDeltaS = objSprite.s.scaleW / 1024.0f;
    fDeltaT = objSprite.s.scaleH / 1024.0f;
    if (objSprite.s.imageFlags & 1) {
        primitive.rS = (u16)(objSprite.s.imageW - 8 * pFrame->aTile[primitive.iTile].nX0) / 32.0f;
        primitive.rDeltaS = -fDeltaS;
    } else {
        primitive.rS = (u16)(-8 * pFrame->aTile[primitive.iTile].nX0) / 32.0f;
        primitive.rDeltaS = fDeltaS;
    }
    if (objSprite.s.imageFlags & 0x10) {
        primitive.rT = (u16)(objSprite.s.imageH - 8 * pFrame->aTile[primitive.iTile].nY0) / 32.0f;
        primitive.rDeltaT = -fDeltaT;
    } else {
        primitive.rT = (u16)(-8 * pFrame->aTile[primitive.iTile].nY0) / 32.0f;
        primitive.rDeltaT = fDeltaT;
    }

    if (!pFrame->aDraw[3](pFrame, &primitive)) {
        return false;
    }
    return true;
}

static bool rspObjSprite(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    u16 nSizLineBytes;
    f32 fLeft;
    f32 fRight;
    f32 fTop;
    f32 fBottom;
    f32 fTexRight;
    f32 fTexBottom;
    f32 fTexLeft;
    f32 fTexTop;
    f32 fScaleX;
    f32 fScaleY;
    f32 fSpriteWidth;
    f32 fSpriteHeight;
    s32 nTexTrim2;
    s32 nTexTrim5;
    s32 nClampSetting;
    uObjSprite objSprite;
    Tile* pTile;
    s32 pad[2];
    Primitive primitive;
    Mtx mtxTransL;
    Mtx mtxTransW;
    Mtx mtxScale;
    Mtx mtxTemp;
    Mtx mtxOut;
    Vec vecIn;
    Vec vecOut;

    nTexTrim2 = 0;
    nTexTrim5 = 0;
    pTile = &pFrame->aTile[0];
    if (!rspFillObjSprite(pRSP, nAddress, &objSprite)) {
        return false;
    }

    nClampSetting = pRSP->nMode2D & 1;
    if (pRSP->nMode2D & 0x10) {
        nTexTrim2 = -2;
        nTexTrim5 = -16;
    } else if (pRSP->nMode2D & 0x20) {
        nTexTrim2 = -4;
        nTexTrim5 = -32;
    }
    if (pRSP->nMode2D & 0x40) {
        nTexTrim2 += 1;
        nTexTrim5 += 12;
    }

    objSprite.s.imageW += nTexTrim5;
    objSprite.s.imageH += nTexTrim5;
    pFrame->nLastX1 += nTexTrim2;

    if (pTile->nSize != 0) {
        switch (objSprite.s.imageSiz) {
            case G_IM_SIZ_32b:
                nSizLineBytes = 2;
                break;
            case G_IM_SIZ_16b:
                nSizLineBytes = 2;
                break;
            case G_IM_SIZ_8b:
                nSizLineBytes = 1;
                break;
            default:
                return false;
        }
        if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
            pTile->nSizeX = ((objSprite.s.imageW >> 5) * nSizLineBytes + 7) >> 3;
        } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
            pTile->nSizeX = (((pFrame->nLastX1 - pFrame->nLastX0 + 1) >> 5) * nSizLineBytes + 7) >> 3;
        }
    } else {
        if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
            pTile->nSizeX = ((objSprite.s.imageW >> 6) + 7) >> 3;
        } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
            pTile->nSizeX = (((pFrame->nLastX1 - pFrame->nLastX0) >> 6) + 7) >> 3;
        }
    }

    if (!rspSetTile(pFrame, pTile, objSprite.s.imageSiz, 0, objSprite.s.imagePal, objSprite.s.imageFmt, 0, 0,
                    nClampSetting, nClampSetting, 0, 0)) {
        return false;
    }

    if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
        if (!rspSetTileSize(pFrame, pTile, 0, 0, ((objSprite.s.imageW >> 5) - 1) << 2,
                            ((objSprite.s.imageH >> 5) - 1) << 2)) {
            return false;
        }
    } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
        if (!rspSetTileSize(pFrame, pTile, (pFrame->nLastX0 >> 5) << 2, (pFrame->nLastY0 >> 5) << 2,
                            (pFrame->nLastX1 >> 5) << 2, (pFrame->nLastY1 >> 5) << 2)) {
            return false;
        }
    }

    fSpriteWidth = objSprite.s.imageW / 32.0f;
    fSpriteHeight = objSprite.s.imageH / 32.0f;
    if (objSprite.s.imageFlags & 1) {
        fTexRight = 0.0f;
        fTexLeft = (2.0f * fSpriteWidth) - 2.0f;
    } else {
        fTexLeft = 0.0f;
        fTexRight = (2.0f * fSpriteWidth) - 2.0f;
    }
    if (objSprite.s.imageFlags & 0x10) {
        fTexBottom = 0.0f;
        fTexTop = (2.0f * fSpriteHeight) - 2.0f;
    } else {
        fTexTop = 0.0f;
        fTexBottom = (2.0f * fSpriteHeight) - 2.0f;
    }
    fLeft = -fSpriteWidth / 2.0f;
    fRight = fSpriteWidth / 2.0f;
    fTop = fSpriteHeight / 2.0f;
    fBottom = -fSpriteHeight / 2.0f;
    fScaleX = (1024.0f / objSprite.s.scaleW) * pFrame->rScaleX;
    fScaleY = (1024.0f / objSprite.s.scaleH) * pFrame->rScaleY;

    frameFillVertex(pFrame, 0, fLeft, fTop, 0, fTexLeft, fTexTop);
    frameFillVertex(pFrame, 1, fRight, fTop, 0, fTexRight, fTexTop);
    frameFillVertex(pFrame, 2, fRight, fBottom, 0, fTexRight, fTexBottom);
    frameFillVertex(pFrame, 3, fLeft, fBottom, 0, fTexLeft, fTexBottom);

    primitive.anData[0] = 0;
    primitive.anData[1] = 1;
    primitive.anData[2] = 2;
    primitive.anData[3] = 0;
    primitive.anData[4] = 2;
    primitive.anData[5] = 3;
    primitive.nCount = 6;

    if (!frameSetMode(pFrame, FMT_TEXTURE2, 1)) {
        return false;
    }
    if (!frameSetMode(pFrame, FMT_TEXTURE1, 0xFFFFFFFF)) {
        return false;
    }
    if (!frameSetMode(pFrame, FMT_GEOMETRY, pFrame->aMode[1] & ~0xAD)) {
        return false;
    }
    if (!frameSetMatrix(pFrame, pRSP->aMatrixOrtho, FMT_PROJECTION, true, false, 0)) {
        return false;
    }

    PSMTXIdentity(mtxTransL);
    PSMTXIdentity(mtxTransW);
    PSMTXIdentity(mtxScale);
    PSMTXTrans(mtxTransL, fSpriteWidth / 2.0f + objSprite.s.objX / 4.0f,
               -fSpriteHeight / 2.0f - objSprite.s.objY / 4.0f, 0.0f);
    PSMTXTrans(mtxTransW, -pFrame->anSizeX[1] / 2.0f + pRSP->twoDValues.fX * pFrame->rScaleX,
               pFrame->anSizeY[1] / 2.0f + pRSP->twoDValues.fY * pFrame->rScaleY, 0.0f);
    mtxScale[0][0] = fScaleX * pRSP->twoDValues.aRotations[0][0];
    mtxScale[1][0] = -fScaleX * pRSP->twoDValues.aRotations[1][0];
    mtxScale[0][1] = -fScaleY * pRSP->twoDValues.aRotations[0][1];
    mtxScale[1][1] = fScaleY * pRSP->twoDValues.aRotations[1][1];
    PSMTXConcat(mtxScale, mtxTransL, mtxTemp);
    PSMTXConcat(mtxTransW, mtxTemp, mtxOut);

    vecIn.x = fLeft;
    vecIn.y = fTop;
    vecIn.z = 0.0f;
    PSMTXMultVec(mtxOut, &vecIn, &vecOut);
    frameFillVertex(pFrame, 0, vecOut.x, vecOut.y, vecOut.z, fTexLeft, fTexTop);

    vecIn.x = fRight;
    vecIn.y = fTop;
    vecIn.z = 0.0f;
    PSMTXMultVec(mtxOut, &vecIn, &vecOut);
    frameFillVertex(pFrame, 1, vecOut.x, vecOut.y, vecOut.z, fTexRight, fTexTop);

    vecIn.x = fRight;
    vecIn.y = fBottom;
    vecIn.z = 0.0f;
    PSMTXMultVec(mtxOut, &vecIn, &vecOut);
    frameFillVertex(pFrame, 2, vecOut.x, vecOut.y, vecOut.z, fTexRight, fTexBottom);

    vecIn.x = fLeft;
    vecIn.y = fBottom;
    vecIn.z = 0.0f;
    PSMTXMultVec(mtxOut, &vecIn, &vecOut);
    frameFillVertex(pFrame, 3, vecOut.x, vecOut.y, vecOut.z, fTexLeft, fTexBottom);

    if (!pFrame->aDraw[1](pFrame, &primitive)) {
        return false;
    }
    if (!frameSetMode(pFrame, FMT_TEXTURE2, 0)) {
        return false;
    }
    return true;
}

bool rspObjRectangleR(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    u16 nSizLineBytes;
    f32 fLeft;
    f32 fRight;
    f32 fTop;
    f32 fBottom;
    f32 fTexRight;
    f32 fTexBottom;
    f32 fTexLeft;
    f32 fTexTop;
    f32 fScaleX;
    f32 fScaleY;
    s32 nTexTrim2;
    s32 nTexTrim5;
    f32 fSpriteWidth;
    f32 fSpriteHeight;
    s32 nClampSetting;
    uObjSprite objSprite;
    s32 pad2[2];
    Tile* pTile;
    Primitive primitive;
    Mtx mtxTransL;
    Mtx mtxTransW;
    Mtx mtxScale;
    Mtx mtxTemp;
    Mtx mtxOut;
    Vec vecIn;
    Vec vecOut;

    nTexTrim2 = 0;
    nTexTrim5 = 0;
    pTile = &pFrame->aTile[0];
    if (!rspFillObjSprite(pRSP, nAddress, &objSprite)) {
        return false;
    }

    nClampSetting = pRSP->nMode2D & 1;
    if (pRSP->nMode2D & 0x10) {
        nTexTrim2 = -2;
        nTexTrim5 = -16;
    } else if (pRSP->nMode2D & 0x20) {
        nTexTrim2 = -4;
        nTexTrim5 = -32;
    }
    if (pRSP->nMode2D & 0x40) {
        nTexTrim2 += 1;
        nTexTrim5 += 12;
    }

    objSprite.s.imageW += nTexTrim5;
    objSprite.s.imageH += nTexTrim5;
    pFrame->nLastX1 += nTexTrim2;

    if (pTile->nSize != 0) {
        switch (objSprite.s.imageSiz) {
            case G_IM_SIZ_32b:
                nSizLineBytes = 2;
                break;
            case G_IM_SIZ_16b:
                nSizLineBytes = 2;
                break;
            case G_IM_SIZ_8b:
                nSizLineBytes = 1;
                break;
            default:
                return false;
        }
        if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
            pTile->nSizeX = ((objSprite.s.imageW >> 5) * nSizLineBytes + 7) >> 3;
        } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
            pTile->nSizeX = ((((pFrame->nLastX1 - pFrame->nLastX0) >> 2) + 1) * nSizLineBytes + 7) >> 3;
        }
    } else {
        if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
            pTile->nSizeX = ((objSprite.s.imageW >> 6) + 7) >> 3;
        } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
            pTile->nSizeX = (((pFrame->nLastX1 - pFrame->nLastX0) >> 6) + 7) >> 3;
        }
    }

    if (!rspSetTile(pFrame, pTile, objSprite.s.imageSiz, 0, objSprite.s.imagePal, objSprite.s.imageFmt, 0, 0,
                    nClampSetting, nClampSetting, 0, 0)) {
        return false;
    }

    if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
        if (!rspSetTileSize(pFrame, pTile, 0, 0, ((objSprite.s.imageW >> 5) - 1) << 2,
                            ((objSprite.s.imageH >> 5) - 1) << 2)) {
            return false;
        }
    } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
        if (!rspSetTileSize(pFrame, pTile, (pFrame->nLastX0 >> 2) << 2, (pFrame->nLastY0 >> 2) << 2,
                            (pFrame->nLastX1 >> 2) << 2, (pFrame->nLastY1 >> 2) << 2)) {
            return false;
        }
    }

    fSpriteWidth = objSprite.s.imageW / 32.0f;
    fSpriteHeight = objSprite.s.imageH / 32.0f;
    if (objSprite.s.imageFlags & 1) {
        fTexRight = 0.0f;
        fTexLeft = (2.0f * fSpriteWidth) - 2.0f;
    } else {
        fTexLeft = 0.0f;
        fTexRight = (2.0f * fSpriteWidth) - 2.0f;
    }
    if (objSprite.s.imageFlags & 0x10) {
        fTexBottom = 0.0f;
        fTexTop = (2.0f * fSpriteHeight) - 2.0f;
    } else {
        fTexTop = 0.0f;
        fTexBottom = (2.0f * fSpriteHeight) - 2.0f;
    }
    fLeft = -fSpriteWidth / 2.0f;
    fRight = (1024.0f / objSprite.s.scaleW) * fSpriteWidth / 2.0f;
    fTop = fSpriteHeight / 2.0f;
    fBottom = (1024.0f / objSprite.s.scaleH) * -fSpriteHeight / 2.0f;

    frameFillVertex(pFrame, 0, fLeft, fTop, 0, fTexLeft, fTexTop);
    frameFillVertex(pFrame, 1, fRight, fTop, 0, fTexRight, fTexTop);
    frameFillVertex(pFrame, 2, fRight, fBottom, 0, fTexRight, fTexBottom);
    frameFillVertex(pFrame, 3, fLeft, fBottom, 0, fTexLeft, fTexBottom);

    primitive.anData[0] = 0;
    primitive.anData[1] = 1;
    primitive.anData[2] = 2;
    primitive.anData[3] = 0;
    primitive.anData[4] = 2;
    primitive.anData[5] = 3;
    primitive.nCount = 6;

    if (!frameSetMode(pFrame, FMT_TEXTURE2, 1)) {
        return false;
    }
    if (!frameSetMode(pFrame, FMT_TEXTURE1, 0xFFFFFFFF)) {
        return false;
    }
    if (!frameSetMode(pFrame, FMT_GEOMETRY, pFrame->aMode[1] & ~0xAD)) {
        return false;
    }
    if (!frameSetMatrix(pFrame, pRSP->aMatrixOrtho, FMT_PROJECTION, true, false, 0)) {
        return false;
    }
    PSMTXIdentity(mtxTransL);
    PSMTXIdentity(mtxTransW);
    PSMTXIdentity(mtxScale);
    PSMTXTrans(mtxTransL, fSpriteWidth / 2.0f + objSprite.s.objX / 4.0f,
               -fSpriteHeight / 2.0f - objSprite.s.objY / 4.0f, 0.0f);
    PSMTXTrans(mtxTransW, -pFrame->anSizeX[1] / 2.0f + pRSP->twoDValues.fX * pFrame->rScaleX,
               pFrame->anSizeY[1] / 2.0f + pRSP->twoDValues.fY * pFrame->rScaleY, 0.0f);
    mtxScale[0][0] = pRSP->twoDValues.fBaseScaleX * pFrame->rScaleX;
    mtxScale[1][1] = pRSP->twoDValues.fBaseScaleY * pFrame->rScaleY;
    PSMTXConcat(mtxScale, mtxTransL, mtxTemp);
    PSMTXConcat(mtxTransW, mtxTemp, mtxOut);

    vecIn.x = fLeft;
    vecIn.y = fTop;
    vecIn.z = 0.0f;
    PSMTXMultVec(mtxOut, &vecIn, &vecOut);
    frameFillVertex(pFrame, 0, vecOut.x, vecOut.y, vecOut.z, fTexLeft, fTexTop);

    vecIn.x = fRight;
    vecIn.y = fTop;
    vecIn.z = 0.0f;
    PSMTXMultVec(mtxOut, &vecIn, &vecOut);
    frameFillVertex(pFrame, 1, vecOut.x, vecOut.y, vecOut.z, fTexRight, fTexTop);

    vecIn.x = fRight;
    vecIn.y = fBottom;
    vecIn.z = 0.0f;
    PSMTXMultVec(mtxOut, &vecIn, &vecOut);
    frameFillVertex(pFrame, 2, vecOut.x, vecOut.y, vecOut.z, fTexRight, fTexBottom);

    vecIn.x = fLeft;
    vecIn.y = fBottom;
    vecIn.z = 0.0f;
    PSMTXMultVec(mtxOut, &vecIn, &vecOut);
    frameFillVertex(pFrame, 3, vecOut.x, vecOut.y, vecOut.z, fTexLeft, fTexBottom);

    if (!pFrame->aDraw[1](pFrame, &primitive)) {
        return false;
    }
    if (!frameSetMode(pFrame, FMT_TEXTURE2, 0)) {
        return false;
    }
    return true;
}

static inline bool rspObjLoadTxRect(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    if (!rspObjLoadTxtr(pRSP, pFrame, nAddress)) {
        return false;
    }
    if (!rspObjRectangle(pRSP, pFrame, nAddress + 0x18)) {
        return false;
    }
    return true;
}

static inline bool rspObjLoadTxRectR(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    if (!rspObjLoadTxtr(pRSP, pFrame, nAddress)) {
        return false;
    }
    if (!rspObjRectangleR(pRSP, pFrame, nAddress + 0x18)) {
        return false;
    }
    return true;
}

static inline bool rspObjLoadTxSprite(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    if (!rspObjLoadTxtr(pRSP, pFrame, nAddress)) {
        return false;
    }
    if (!rspObjSprite(pRSP, pFrame, nAddress + 0x18)) {
        return false;
    }
    return true;
}

bool rspBgRectCopy(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    uObjBg bg;
    uObjBg bgScale;
    u32 nOldMode1;
    u32 nOldMode2;

    rspFillObjBg(pRSP, nAddress, &bg);
    bgScale.s.frameH = bg.b.frameH;
    bgScale.s.frameW = bg.b.frameW;
    bgScale.s.frameX = bg.b.frameX;
    bgScale.s.frameY = bg.b.frameY;
    bgScale.s.imageFlip = bg.b.imageFlip;
    bgScale.s.imageFmt = bg.b.imageFmt;
    bgScale.s.imageH = bg.b.imageH;
    bgScale.s.imageLoad = bg.b.imageLoad;
    bgScale.s.imagePal = bg.b.imagePal;
    bgScale.s.imagePtr = bg.b.imagePtr;
    bgScale.s.imageSiz = bg.b.imageSiz;
    bgScale.s.imageW = bg.b.imageW;
    bgScale.s.imageX = bg.b.imageX;
    bgScale.s.imageY = bg.b.imageY;
    bgScale.s.padding[0] = 0;
    bgScale.s.padding[1] = 0;
    bgScale.s.padding[2] = 0;
    bgScale.s.padding[3] = 0;
    bgScale.s.scaleW = 0x400;
    bgScale.s.scaleH = 0x400;
    bgScale.s.imageYorig = 0;

    frameGetMode(pFrame, FMT_OTHER0, &nOldMode1);
    frameGetMode(pFrame, FMT_OTHER1, &nOldMode2);
    if ((nOldMode2 & 0x300000) == 0x200000) {
        pFrame->aColor[FCT_PRIMITIVE].a = 0xFF;
    }
    if (!frameSetMode(pFrame, FMT_OTHER0, 0x0F0A4001)) {
        return false;
    }
    if (!frameSetMode(pFrame, FMT_OTHER1, 0x00802CC0)) {
        return false;
    }
    if (!guS2DEmuSetScissor(0, 0, 0x500, 0x3C0, 0)) {
        return false;
    }
    if (!guS2DEmuBgRect1Cyc(pRSP, pFrame, &bgScale)) {
        return false;
    }
    return true;
}

static inline bool rspObjSubMatrix(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    u16* pnData16;
    u8* pObjSubMtx;
    u16 nBaseScaleX;
    u16 nBaseScaleY;
    s16 nX;
    s16 nY;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pObjSubMtx, nAddress, NULL)) {
        return false;
    }

    pnData16 = (u16*)pObjSubMtx;
    nX = pnData16[0];
    nY = pnData16[1];
    nBaseScaleX = pnData16[2];
    nBaseScaleY = pnData16[3];

    pRSP->twoDValues.fX = (f32)nX / 4.0f;
    pRSP->twoDValues.fY = -(f32)nY / 4.0f;
    pRSP->twoDValues.fBaseScaleX = 1024.0f / (f32)nBaseScaleX;
    pRSP->twoDValues.fBaseScaleY = 1024.0f / (f32)nBaseScaleY;
    return true;
}

static bool rspObjMatrix(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    u32* pnData32;
    u16* pnData16;
    u8* pObjMtx;
    u16 nBaseScaleX;
    u16 nBaseScaleY;
    s32 nA;
    s32 nB;
    s32 nC;
    s32 nD;
    s16 nX;
    s16 nY;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pObjMtx, nAddress, NULL)) {
        return false;
    }

    pnData32 = (u32*)pObjMtx;
    pnData16 = (u16*)pObjMtx;

    nA = pnData32[0];
    nB = pnData32[1];
    nC = pnData32[2];
    nD = pnData32[3];
    nX = pnData16[8];
    nY = pnData16[9];
    nBaseScaleX = pnData16[10];
    nBaseScaleY = pnData16[11];

    pRSP->twoDValues.fX = (f32)nX / 4.0f;
    pRSP->twoDValues.fY = -(f32)nY / 4.0f;
    pRSP->twoDValues.aRotations[0][0] = nA / 65536.0f;
    pRSP->twoDValues.aRotations[0][1] = nB / 65536.0f;
    pRSP->twoDValues.aRotations[1][0] = nC / 65536.0f;
    pRSP->twoDValues.aRotations[1][1] = nD / 65536.0f;
    pRSP->twoDValues.fBaseScaleX = 1024.0f / nBaseScaleX;
    pRSP->twoDValues.fBaseScaleY = 1024.0f / nBaseScaleY;
    return true;
}

static bool rspSetupS2DEX(Rsp* pRSP) {
    f32 fL;
    f32 fR;
    f32 fB;
    f32 fT;
    Frame* pFrame;
    f32 fScale = 2.0f;
    s32 pad;

    pFrame = SYSTEM_FRAME(pRSP->pHost);

    pRSP->twoDValues.aRotations[0][0] = 1.0f;
    pRSP->twoDValues.aRotations[1][0] = 0.0f;
    pRSP->twoDValues.aRotations[1][1] = 1.0f;
    pRSP->twoDValues.aRotations[0][1] = 0.0f;

    pRSP->twoDValues.fBaseScaleX = 1.0f;
    pRSP->twoDValues.fBaseScaleY = 1.0f;
    pRSP->twoDValues.fX = 0.0f;
    pRSP->twoDValues.fY = 0.0f;

    fL = -pFrame->anSizeX[FS_TARGET] / 2.0f;
    fR = pFrame->anSizeX[FS_TARGET] / 2.0f;
    fB = -pFrame->anSizeY[FS_TARGET] / 2.0f;
    fT = pFrame->anSizeY[FS_TARGET] / 2.0f;

    Matrix4by4Identity(pRSP->aMatrixOrtho);

    pRSP->aMatrixOrtho[0][0] = fScale / (fR - fL);
    pRSP->aMatrixOrtho[1][1] = fScale / (fT - fB);
    pRSP->aMatrixOrtho[2][2] = -1.0f;
    pRSP->aMatrixOrtho[3][0] = -(fR + fL) / (fR - fL);
    pRSP->aMatrixOrtho[3][1] = -(fT + fB) / (fT - fB);
    pRSP->aMatrixOrtho[3][2] = -fScale / 2.0f;
    pRSP->aMatrixOrtho[3][3] = 1.0f;

    return true;
}
