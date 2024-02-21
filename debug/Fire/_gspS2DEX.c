/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_gspS2DEX.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80077850 -> 0x8007AC6C
*/

#include "dolphin/types.h"

// Erased
static s32 frameFillVertex(struct __anon_0x5A89F* pFrame, s32 nIndex, s16 nX, s16 nY, s16 nZ, f32 rS, f32 rT) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r1+0x8
    // s32 nIndex; // r1+0xC
    // s16 nX; // r1+0x10
    // s16 nY; // r1+0x12
    // s16 nZ; // r1+0x14
    // f32 rS; // r1+0x18
    // f32 rT; // r1+0x1C
}

// Range: 0x8007AC1C -> 0x8007AC6C
static s32 Matrix4by4Identity(f32 (*matrix4b4)[4]) {
    // Parameters
    // f32 (* matrix4b4)[4]; // r1+0x0
}

// Range: 0x8007AB54 -> 0x8007AC1C
static s32 rspFillObjSprite(struct __anon_0x5845E* pRSP, s32 nAddress, union __anon_0x5F63B* pSprite) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 nAddress; // r4
    // union __anon_0x5F63B* pSprite; // r31

    // Local variables
    u16* pnData16; // r1+0x8
    u8* pnData8; // r1+0x8
    u8* pObjSprite; // r1+0x14
}

// Range: 0x8007AA74 -> 0x8007AB54
s32 rspFillObjBgScale(struct __anon_0x5845E* pRSP, s32 nAddress, union __anon_0x5F2FB* pBg) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 nAddress; // r4
    // union __anon_0x5F2FB* pBg; // r31

    // Local variables
    u8* pnData8; // r1+0x8
    u8* pObjBg; // r1+0x14
    u16* pnData16; // r1+0x8
    u32* pnData32; // r1+0x8
}

// Range: 0x8007A97C -> 0x8007AA74
s32 rspFillObjBg(struct __anon_0x5845E* pRSP, s32 nAddress, union __anon_0x5F2FB* pBg) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 nAddress; // r4
    // union __anon_0x5F2FB* pBg; // r31

    // Local variables
    u8* pnData8; // r1+0x8
    u8* pObjBg; // r1+0x18
    u16* pnData16; // r1+0x8
}

// Erased
static s32 rspSetTile(struct __anon_0x5A89F* pFrame, struct __anon_0x5A2EC* pTile, s32 nSize, s32 nTmem, s32 nTLUT,
                      s32 nFormat, s32 nMaskS, s32 nMaskT, s32 nModeS, s32 nModeT, s32 nShiftS, s32 nShiftT) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r3
    // struct __anon_0x5A2EC* pTile; // r1+0xC
    // s32 nSize; // r1+0x10
    // s32 nTmem; // r1+0x14
    // s32 nTLUT; // r1+0x18
    // s32 nFormat; // r1+0x20
    // s32 nMaskS; // r1+0x24
    // s32 nMaskT; // r1+0x8
    // s32 nModeS; // r8
    // s32 nModeT; // r6
    // s32 nShiftS; // r9
    // s32 nShiftT; // r8
}

// Range: 0x8007A8E8 -> 0x8007A97C
s32 rspSetImage(struct __anon_0x5A89F* pFrame, struct __anon_0x5845E* pRSP, s32 nFormat, s32 nWidth, s32 nSize,
                s32 nImage) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r31
    // struct __anon_0x5845E* pRSP; // r1+0xC
    // s32 nFormat; // r1+0x10
    // s32 nWidth; // r1+0x14
    // s32 nSize; // r1+0x18
    // s32 nImage; // r1+0x1C

    // Local variables
    s32 addr; // r5
    struct __anon_0x59558* pBuffer; // r9
}

// Erased
static s32 rspLoadBlock(struct __anon_0x5A89F* pFrame, struct __anon_0x5A2EC* pTile, s32 nX0, s32 nY0, s32 nX1,
                        s32 nY1) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r3
    // struct __anon_0x5A2EC* pTile; // r1+0xC
    // s32 nX0; // r1+0x10
    // s32 nY0; // r1+0x14
    // s32 nX1; // r1+0x18
    // s32 nY1; // r1+0x1C
}

// Erased
static s32 rspLoadTile(struct __anon_0x5A89F* pFrame, struct __anon_0x5A2EC* pTile, s32 nX0, s32 nY0, s32 nX1,
                       s32 nY1) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r3
    // struct __anon_0x5A2EC* pTile; // r1+0xC
    // s32 nX0; // r1+0x10
    // s32 nY0; // r1+0x14
    // s32 nX1; // r1+0x18
    // s32 nY1; // r1+0x1C
}

// Erased
static s32 rspSetTileSize(struct __anon_0x5A89F* pFrame, struct __anon_0x5A2EC* pTile, s32 nX0, s32 nY0, s32 nX1,
                          s32 nY1) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r3
    // struct __anon_0x5A2EC* pTile; // r1+0xC
    // s32 nX0; // r1+0x10
    // s32 nY0; // r1+0x14
    // s32 nX1; // r1+0x18
    // s32 nY1; // r1+0x1C
}

// Erased
static s32 guS2DEmuSetScissor(u32 ulx, u32 uly, u32 lrx, u32 lry, u8 flag) {
    // Parameters
    // u32 ulx; // r1+0x0
    // u32 uly; // r1+0x4
    // u32 lrx; // r1+0x8
    // u32 lry; // r1+0xC
    // u8 flag; // r1+0x10

    // References
    // -> static u8 flagBilerp;
    // -> static u16 scissorY1;
    // -> static u16 scissorX1;
    // -> static u16 scissorY0;
    // -> static u16 scissorX0;
}

// Range: 0x8007A7D4 -> 0x8007A8E8
static s32 tmemLoad_B(struct __anon_0x5A89F* pFrame, struct __anon_0x5845E* pRSP, u32 imagePtr, s16 loadLines,
                      s16 tmemSH) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r30
    // struct __anon_0x5845E* pRSP; // r1+0xC
    // u32 imagePtr; // r1+0x10
    // s16 loadLines; // r31
    // s16 tmemSH; // r28

    // Local variables
    struct __anon_0x59558* pBuffer; // r8
    s32 nAddr; // r5

    // References
    // -> static u16 imageSrcWsize;
}

// Range: 0x8007A728 -> 0x8007A7D4
static s32 tmemLoad_A(struct __anon_0x5A89F* pFrame, struct __anon_0x5845E* pRSP, u32 imagePtr, s16 loadLines,
                      s16 tmemAdrs, s16 tmemSH) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r27
    // struct __anon_0x5845E* pRSP; // r28
    // u32 imagePtr; // r29
    // s16 loadLines; // r30
    // s16 tmemAdrs; // r1+0x16
    // s16 tmemSH; // r31

    // References
    // -> static u16 tmemSliceWmax;
}

// Range: 0x8007A4B8 -> 0x8007A728
static s32 tmemLoad(struct __anon_0x5A89F* pFrame, struct __anon_0x5845E* pRSP, u32* imagePtr, s16* imageRemain,
                    s16 drawLines, s16 flagBilerp) {
    // Parameters
    // struct __anon_0x5A89F* pFrame; // r21
    // struct __anon_0x5845E* pRSP; // r22
    // u32* imagePtr; // r23
    // s16* imageRemain; // r24
    // s16 drawLines; // r25
    // s16 flagBilerp; // r1+0x1A

    // Local variables
    s16 loadLines; // r6
    s16 iLoadable; // r29
    s16 SubSliceL2; // r6
    s16 SubSliceD2; // r28
    s16 SubSliceY2; // r7
    u32 imageTopSeg; // r30
    u32 imagePtr2; // r5
    u32 imagePtr1A; // r27
    u32 imagePtr1B; // r5
    s16 SubSliceY1; // r4
    s16 SubSliceL1; // r26
    s16 tmemSH_A; // r20
    s16 tmemSH_B; // r8

    // References
    // -> static u16 imageSrcWsize;
    // -> static u32 imageTop;
    // -> static u16 imagePtrX0;
    // -> static s16 tmemSrcLines;
    // -> static u16 tmemSliceWmax;
    // -> static u16 flagSplit;
}

// Range: 0x80079D7C -> 0x8007A4B8
static s32 guS2DEmuBgRect1Cyc(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, union __anon_0x5F2FB* pBG) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r15
    // struct __anon_0x5A89F* pFrame; // r29
    // union __anon_0x5F2FB* pBG; // r26

    // Local variables
    s16 frameX0; // r4
    s16 frameX1; // r1+0x50
    s16 framePtrY0; // r23
    s16 frameRemain; // r31
    s16 imageX0; // r3
    s16 imageY0; // r4
    s16 imageSliceW; // r9
    s16 imageW; // r21
    s32 imageYorig; // r5
    s16 scaleW; // r1+0x8
    s16 scaleH; // r1+0x8
    s16 imageSrcW; // r6
    s16 imageSrcH; // r7
    s16 imageSliceLines; // r25
    s32 frameSliceLines; // r22
    s32 frameSliceCount; // r28
    u16 imageS; // r18
    u16 imageT; // r24
    u32 imagePtr; // r1+0x44
    s16 imageISliceL0; // r20
    s16 imageIY0; // r1+0x8
    s32 frameLSliceL0; // r7
    s16 pixX0; // r3
    s16 pixY0; // r4
    s16 pixX1; // r1+0x8
    s16 pixY1; // r8
    s16 frameY0; // r5
    s16 frameW; // r3
    s16 frameH; // r7
    s32 frameWmax; // r1+0x8
    s32 frameHmax; // r7
    s16 tmemSize; // r1+0x8
    s16 tmemMask; // r18
    s16 tmemShift; // r10
    s32 imageNumSlice; // r1+0x8
    s32 imageSliceWmax; // r6
    s32 imageLYoffset; // r4
    s32 frameLYoffset; // r4
    s32 imageLHidden; // r4
    s32 frameLHidden; // r6
    s32 frameLYslice; // r6
    s16 imageRemain; // r1+0x40
    s16 imageSliceH; // r1+0x8
    s16 frameSliceH; // r30
    struct __anon_0x5F759 primitive; // r1+0x18
    s16 nT; // r3
    s16 framePtrY1; // r30

    // References
    // -> static u8 flagBilerp;
    // -> static s16 tmemSrcLines;
    // -> static u16 imageSrcWsize;
    // -> static u32 imageTop;
    // -> static u16 imagePtrX0;
    // -> static u16 tmemSliceWmax;
    // -> static u32 rdpSetTile_w0;
    // -> static u32 rdpSetTimg_w0;
    // -> static s16 TMEMSHIFT$3465[4];
    // -> static s16 TMEMMASK$3464[4];
    // -> static s16 TMEMSIZE$3463[5];
    // -> static u16 flagSplit;
    // -> static u16 scissorY1;
    // -> static u16 scissorX1;
    // -> static u16 scissorY0;
    // -> static u16 scissorX0;
}

// Range: 0x80079C1C -> 0x80079D7C
s32 rspFillObjTxtr(struct __anon_0x5845E* pRSP, s32 nAddress, union __anon_0x5FC1B* pTxtr, u32* pLoadType) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 nAddress; // r4
    // union __anon_0x5FC1B* pTxtr; // r30
    // u32* pLoadType; // r31

    // Local variables
    u32* pnData32; // r1+0x8
    u16* pnData16; // r1+0x8
    u8* pTxtrBlock; // r1+0x18
    u32 nLoadType; // r1+0x8
}

// Range: 0x800797D0 -> 0x80079C1C
static s32 rspObjLoadTxtr(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x5A89F* pFrame; // r29
    // s32 nAddress; // r5

    // Local variables
    u32 nSizDefine; // r26
    u32 nLoadType; // r1+0x30
    s32 nAddr; // r5
    struct __anon_0x5A2EC* pTile; // r31
    struct __anon_0x59558* pBuffer; // r30
    union __anon_0x5FC1B objTxtr; // r1+0x18
}

// Range: 0x80079234 -> 0x800797D0
static s32 rspObjRectangle(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r27
    // struct __anon_0x5A89F* pFrame; // r30
    // s32 nAddress; // r5

    // Local variables
    u16 nSizLineBytes; // r5
    f32 fDeltaS; // f3
    f32 fDeltaT; // f4
    union __anon_0x5F63B objSprite; // r1+0x48
    struct __anon_0x5A2EC* pTile; // r31
    struct __anon_0x5F759 primitive; // r1+0x1C
    s32 nClampSetting; // r1+0x8
    s32 nTexTrim2; // r29
    s32 nTexTrim5; // r28
}

// Range: 0x8007876C -> 0x80079234
static s32 rspObjSprite(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29
    // struct __anon_0x5A89F* pFrame; // r30
    // s32 nAddress; // r5

    // Local variables
    u16 nSizLineBytes; // r5
    f32 fLeft; // f29
    f32 fRight; // r1+0x8
    f32 fTop; // f28
    f32 fBottom; // r1+0x8
    f32 fTexRight; // f27
    f32 fTexBottom; // f26
    f32 fTexLeft; // f25
    f32 fTexTop; // f24
    f32 fScaleX; // f23
    f32 fScaleY; // f22
    f32 fSpriteWidth; // f2
    f32 fSpriteHeight; // f4
    s32 nTexTrim2; // r28
    s32 nTexTrim5; // r27
    s32 nClampSetting; // r1+0x8
    union __anon_0x5F63B objSprite; // r1+0x438
    struct __anon_0x5A2EC* pTile; // r31
    struct __anon_0x5EBE0 primitive; // r1+0x12C
    f32 mtxTransL[3][4]; // r1+0xFC
    f32 mtxTransW[3][4]; // r1+0xCC
    f32 mtxScale[3][4]; // r1+0x9C
    f32 mtxTemp[3][4]; // r1+0x6C
    f32 mtxOut[3][4]; // r1+0x3C
    struct __anon_0x5F6E9 vecIn; // r1+0x30
    struct __anon_0x5F6E9 vecOut; // r1+0x24
}

// Range: 0x80077CB8 -> 0x8007876C
static s32 rspObjRectangleR(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29
    // struct __anon_0x5A89F* pFrame; // r30
    // s32 nAddress; // r5

    // Local variables
    u16 nSizLineBytes; // r5
    f32 fLeft; // f30
    f32 fRight; // f29
    f32 fTop; // f28
    f32 fBottom; // f27
    f32 fTexRight; // f26
    f32 fTexBottom; // f25
    f32 fTexLeft; // f24
    f32 fTexTop; // f23
    s32 nTexTrim2; // r28
    s32 nTexTrim5; // r27
    f32 fSpriteWidth; // f22
    f32 fSpriteHeight; // f1
    s32 nClampSetting; // r1+0x8
    union __anon_0x5F63B objSprite; // r1+0x438
    struct __anon_0x5A2EC* pTile; // r31
    struct __anon_0x5EBE0 primitive; // r1+0x12C
    f32 mtxTransL[3][4]; // r1+0xFC
    f32 mtxTransW[3][4]; // r1+0xCC
    f32 mtxScale[3][4]; // r1+0x9C
    f32 mtxTemp[3][4]; // r1+0x6C
    f32 mtxOut[3][4]; // r1+0x3C
    struct __anon_0x5F6E9 vecIn; // r1+0x30
    struct __anon_0x5F6E9 vecOut; // r1+0x24
}

// Erased
static s32 rspObjLoadTxRect(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29
    // struct __anon_0x5A89F* pFrame; // r30
    // s32 nAddress; // r31
}

// Erased
static s32 rspObjLoadTxRectR(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29
    // struct __anon_0x5A89F* pFrame; // r30
    // s32 nAddress; // r31
}

// Erased
static s32 rspObjLoadTxSprite(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29
    // struct __anon_0x5A89F* pFrame; // r30
    // s32 nAddress; // r31
}

// Range: 0x80077B18 -> 0x80077CB8
s32 rspBgRectCopy(struct __anon_0x5845E* pRSP, struct __anon_0x5A89F* pFrame, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // struct __anon_0x5A89F* pFrame; // r31
    // s32 nAddress; // r5

    // Local variables
    union __anon_0x5F2FB bg; // r1+0x48
    union __anon_0x5F2FB bgScale; // r1+0x20
    u32 nOldMode1; // r1+0x18
    u32 nOldMode2; // r1+0x14

    // References
    // -> static u8 flagBilerp;
    // -> static u16 scissorY1;
    // -> static u16 scissorX1;
    // -> static u16 scissorY0;
    // -> static u16 scissorX0;
}

// Erased
static s32 rspObjSubMatrix(struct __anon_0x5845E* pRSP, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // s32 nAddress; // r5

    // Local variables
    u16* pnData16; // r6
    u8* pObjSubMtx; // r1+0x18
    u16 nBaseScaleX; // r7
    u16 nBaseScaleY; // r5
    s16 nY; // r1+0x8
}

// Range: 0x800779B0 -> 0x80077B18
static s32 rspObjMatrix(struct __anon_0x5845E* pRSP, s32 nAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // s32 nAddress; // r5

    // Local variables
    u32* pnData32; // r1+0x8
    u16* pnData16; // r1+0x8
    u8* pObjMtx; // r1+0x18
    u16 nBaseScaleX; // r6
    u16 nBaseScaleY; // r8
    s32 nA; // r5
    s32 nB; // r4
    s32 nC; // r1+0x8
    s32 nD; // r9
    s16 nY; // r1+0x8
}

// Range: 0x80077850 -> 0x800779B0
static s32 rspSetupS2DEX(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31

    // Local variables
    f32 fL; // f31
    f32 fR; // f30
    f32 fB; // f29
    f32 fT; // f28
    struct __anon_0x5A89F* pFrame; // r4
}
