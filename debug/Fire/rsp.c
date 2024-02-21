/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\rsp.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80071BB8 -> 0x80074454
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x56F42; // size = 0x10

// size = 0x10, address = 0x800EE220
struct _XL_OBJECTTYPE gClassRSP;

// size = 0x20, address = 0x800EE230
s32 cmask_tab[8];

// size = 0x20, address = 0x800EE250
s32 emask_tab[8];

// size = 0x4, address = 0x801352C4
static s32 nFirstTime$2148;

// size = 0x4, address = 0x80135788
static s32 counter$2409;

// size = 0x4, address = 0x801352C8
static s32 nFirstTime$2648;

// size = 0x4, address = 0x801352CC
static s32 nFirstTime$2757;

// size = 0x4, address = 0x801352D0
static s32 nFirstTime$2796;

// size = 0x2, address = 0x8013578C
static u16 scissorX0;

// size = 0x2, address = 0x8013578E
static u16 scissorY0;

// size = 0x2, address = 0x801352D4
static u16 scissorX1;

// size = 0x2, address = 0x801352D6
static u16 scissorY1;

// size = 0x1, address = 0x80135790
static u8 flagBilerp;

// size = 0x4, address = 0x80135794
static u32 rdpSetTimg_w0;

// size = 0x4, address = 0x80135798
static u32 rdpSetTile_w0;

// size = 0x2, address = 0x8013579C
static u16 tmemSliceWmax;

// size = 0x2, address = 0x8013579E
static u16 imageSrcWsize;

// size = 0x2, address = 0x801357A0
static u16 flagSplit;

// size = 0x2, address = 0x801357A2
static u16 imagePtrX0;

// size = 0x4, address = 0x801357A4
static u32 imageTop;

// size = 0x2, address = 0x801357A8
static s16 tmemSrcLines;

// size = 0xA, address = 0x800EE270
static s16 TMEMSIZE$3463[5];

// size = 0x8, address = 0x801352D8
static s16 TMEMMASK$3464[4];

// size = 0x8, address = 0x801352E0
static s16 TMEMSHIFT$3465[4];

typedef struct __anon_0x575BD {
    /* 0x00 */ s32 nType;
    /* 0x04 */ s32 nFlag;
    /* 0x08 */ s32 nOffsetBoot;
    /* 0x0C */ s32 nLengthBoot;
    /* 0x10 */ s32 nOffsetCode;
    /* 0x14 */ s32 nLengthCode;
    /* 0x18 */ s32 nOffsetData;
    /* 0x1C */ s32 nLengthData;
    /* 0x20 */ s32 nOffsetStack;
    /* 0x24 */ s32 nLengthStack;
    /* 0x28 */ s32 nOffsetBuffer;
    /* 0x2C */ s32 nLengthBuffer;
    /* 0x30 */ s32 nOffsetMBI;
    /* 0x34 */ s32 nLengthMBI;
    /* 0x38 */ s32 nOffsetYield;
    /* 0x3C */ s32 nLengthYield;
} __anon_0x575BD; // size = 0x40

typedef struct __anon_0x57890 {
    /* 0x00 */ s32 iDL;
    /* 0x04 */ s32 bValid;
    /* 0x08 */ struct __anon_0x575BD task;
    /* 0x48 */ s32 nCountVertex;
    /* 0x4C */ enum __anon_0x60B3F eTypeUCode;
    /* 0x50 */ u32 n2TriMult;
    /* 0x54 */ u32 nVersionUCode;
    /* 0x58 */ s32 anBaseSegment[16];
    /* 0x98 */ u64* apDL[16];
} __anon_0x57890; // size = 0xD8

typedef struct __anon_0x57AB1 {
    /* 0x00 */ f32 aRotations[2][2];
    /* 0x10 */ f32 fX;
    /* 0x14 */ f32 fY;
    /* 0x18 */ f32 fBaseScaleX;
    /* 0x1C */ f32 fBaseScaleY;
} __anon_0x57AB1; // size = 0x20

typedef struct __anon_0x57BBE {
    /* 0x0 */ f32 rS;
    /* 0x4 */ f32 rT;
    /* 0x8 */ s16 nX;
    /* 0xA */ s16 nY;
    /* 0xC */ s16 nZ;
    /* 0xE */ u8 anData[4];
} __anon_0x57BBE; // size = 0x14

typedef struct __anon_0x57CD6 {
    /* 0x0 */ char anNormal[3];
} __anon_0x57CD6; // size = 0x3

typedef struct __anon_0x57D55 {
    /* 0x0 */ u8 anMaterial[4];
} __anon_0x57D55; // size = 0x4

typedef struct __anon_0x57DF8 {
    /* 0x0 */ f32 aMatrix[4][4];
} __anon_0x57DF8; // size = 0x40

typedef struct __anon_0x57E56 {
    /* 0x0 */ u8 nRed;
    /* 0x1 */ u8 nGreen;
    /* 0x2 */ u8 nBlue;
    /* 0x3 */ char rVectorX;
    /* 0x4 */ char rVectorY;
    /* 0x5 */ char rVectorZ;
} __anon_0x57E56; // size = 0x6

typedef struct __anon_0x58107 {
    /* 0x0 */ s16 anSlice[8];
} __anon_0x58107; // size = 0x10

typedef enum __anon_0x581E7 {
    RUT_NOCODE = -1,
    RUT_ABI1 = 0,
    RUT_ABI2 = 1,
    RUT_ABI3 = 2,
    RUT_ABI4 = 3,
    RUT_UNKNOWN = 4,
} __anon_0x581E7;

typedef struct tXL_LIST {
    /* 0x0 */ s32 nItemSize;
    /* 0x4 */ s32 nItemCount;
    /* 0x8 */ void* pNodeHead;
    /* 0xC */ void* pNodeNext;
} __anon_0x58263; // size = 0x10

typedef struct __anon_0x58360 {
    /* 0x0 */ s16 r;
    /* 0x2 */ s16 g;
    /* 0x4 */ s16 b;
    /* 0x6 */ s16 a;
} __anon_0x58360; // size = 0x8

typedef struct __anon_0x583EE {
    /* 0x0 */ s16 y;
    /* 0x2 */ s16 u;
    /* 0x4 */ s16 v;
} __anon_0x583EE; // size = 0x6

typedef struct __anon_0x5845E {
    /* 0x0000 */ s32 nMode;
    /* 0x0004 */ struct __anon_0x57890 yield;
    /* 0x00DC */ u32 nTickLast;
    /* 0x00E0 */ s32 (*pfUpdateWaiting)();
    /* 0x00E4 */ u32 n2TriMult;
    /* 0x00E8 */ s32 aStatus[4];
    /* 0x00F8 */ f32 aMatrixOrtho[4][4];
    /* 0x0138 */ u32 nMode2D;
    /* 0x013C */ struct __anon_0x57AB1 twoDValues;
    /* 0x015C */ s32 nPass;
    /* 0x0160 */ u32 nZSortSubDL;
    /* 0x0164 */ u32 nStatusSubDL;
    /* 0x0168 */ u32 nNumZSortLights;
    /* 0x016C */ s32 aLightAddresses[8];
    /* 0x018C */ s32 nAmbientLightAddress;
    /* 0x0190 */ struct __anon_0x57BBE aZSortVertex[128];
    /* 0x0B90 */ struct __anon_0x57CD6 aZSortNormal[128];
    /* 0x0D10 */ struct __anon_0x57D55 aZSortMaterial[128];
    /* 0x0F10 */ struct __anon_0x57DF8 aZSortMatrix[128];
    /* 0x2F10 */ struct __anon_0x57E56 aZSortLight[8];
    /* 0x2F40 */ s32 aZSortInvW[128];
    /* 0x3140 */ s16 aZSortWiVal[128];
    /* 0x3240 */ u32 nNumZSortMatrices;
    /* 0x3244 */ u32 nNumZSortVertices;
    /* 0x3248 */ u32 nTotalZSortVertices;
    /* 0x324C */ u32 nNumZSortNormals;
    /* 0x3250 */ u32 nNumZSortMaterials;
    /* 0x3254 */ s32 anAudioBaseSegment[16];
    /* 0x3294 */ s16* anAudioBuffer;
    /* 0x3298 */ s16 anADPCMCoef[5][2][8];
    /* 0x3338 */ u16 nAudioDMOutR[2];
    /* 0x333C */ u16 nAudioDMauxL[2];
    /* 0x3340 */ u16 nAudioDMauxR[2];
    /* 0x3344 */ u16 nAudioCount[2];
    /* 0x3348 */ u16 nAudioFlags;
    /* 0x334A */ u16 nAudioDMEMIn[2];
    /* 0x334E */ u16 nAudioDMEMOut[2];
    /* 0x3354 */ u32 nAudioLoopAddress;
    /* 0x3358 */ u32 nAudioDryAmt;
    /* 0x335C */ u32 nAudioWetAmt;
    /* 0x3360 */ u32 nAudioVolL;
    /* 0x3364 */ u32 nAudioVolR;
    /* 0x3368 */ u32 nAudioVolTGTL;
    /* 0x336C */ u32 nAudioVolRateLM;
    /* 0x3370 */ u32 nAudioVolRateLL;
    /* 0x3374 */ u32 nAudioVolTGTR;
    /* 0x3378 */ u32 nAudioVolRateRM;
    /* 0x337C */ u32 nAudioVolRateRL;
    /* 0x3380 */ struct __anon_0x58107 vParams;
    /* 0x3390 */ s16 stepF;
    /* 0x3392 */ s16 stepL;
    /* 0x3394 */ s16 stepR;
    /* 0x3398 */ s32 anGenReg[32];
    /* 0x3418 */ struct __anon_0x58107 aVectorReg[32];
    /* 0x3618 */ s32 anCP0Reg[32];
    /* 0x3698 */ struct __anon_0x58107 anCP2Reg[32];
    /* 0x3898 */ s16 anAcc[24];
    /* 0x38C8 */ s16 nVCC;
    /* 0x38CA */ s16 nVC0;
    /* 0x38CC */ char nVCE;
    /* 0x38D0 */ enum __anon_0x581E7 eTypeAudioUCode;
    /* 0x38D4 */ u16 nAudioMemOffset;
    /* 0x38D6 */ u16 nAudioADPCMOffset;
    /* 0x38D8 */ u16 nAudioScratchOffset;
    /* 0x38DA */ u16 nAudioParBase;
    /* 0x38DC */ s32 nPC;
    /* 0x38E0 */ s32 iDL;
    /* 0x38E4 */ s32 nBIST;
    /* 0x38E8 */ void* pHost;
    /* 0x38EC */ void* pDMEM;
    /* 0x38F0 */ void* pIMEM;
    /* 0x38F4 */ s32 nStatus;
    /* 0x38F8 */ s32 nFullDMA;
    /* 0x38FC */ s32 nBusyDMA;
    /* 0x3900 */ s32 nSizeGet;
    /* 0x3904 */ s32 nSizePut;
    /* 0x3908 */ s32 nSemaphore;
    /* 0x390C */ s32 nAddressSP;
    /* 0x3910 */ s32 nGeometryMode;
    /* 0x3914 */ s32 nAddressRDRAM;
    /* 0x3918 */ struct tXL_LIST* pListUCode;
    /* 0x391C */ s32 nCountVertex;
    /* 0x3920 */ enum __anon_0x60B3F eTypeUCode;
    /* 0x3924 */ u32 nVersionUCode;
    /* 0x3928 */ s32 anBaseSegment[16];
    /* 0x3968 */ u64* apDL[16];
    /* 0x39A8 */ s32* Coeff;
    /* 0x39AC */ s16* QTable;
    /* 0x39B0 */ s16* QYTable;
    /* 0x39B4 */ s16* QCbTable;
    /* 0x39B8 */ s16* QCrTable;
    /* 0x39BC */ s32* Zigzag;
    /* 0x39C0 */ struct __anon_0x58360* rgbaBuf;
    /* 0x39C4 */ struct __anon_0x583EE* yuvBuf;
    /* 0x39C8 */ s32* dctBuf;
} __anon_0x5845E; // size = 0x39CC

// size = 0x4, address = 0x801356BC
s32 gNoSwapBuffer;

typedef enum __anon_0x5943B {
    RUM_NONE = 0,
    RUM_IDLE = 1,
} __anon_0x5943B;

typedef struct __anon_0x594BE {
    /* 0x0 */ f32 rX;
    /* 0x4 */ f32 rY;
    /* 0x8 */ f32 rSizeX;
    /* 0xC */ f32 rSizeY;
} __anon_0x594BE; // size = 0x10

typedef struct __anon_0x59558 {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nWidth;
    /* 0x08 */ s32 nFormat;
    /* 0x0C */ void* pData;
    /* 0x10 */ s32 nAddress;
} __anon_0x59558; // size = 0x14

typedef struct __anon_0x59699 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} __anon_0x59699; // size = 0xC

typedef struct __anon_0x59709 {
    /* 0x00 */ s32 bTransformed;
    /* 0x04 */ struct __anon_0x59699 rVecOrigTowards;
    /* 0x10 */ f32 rColorR;
    /* 0x14 */ f32 rColorG;
    /* 0x18 */ f32 rColorB;
    /* 0x1C */ f32 rVectorX;
    /* 0x20 */ f32 rVectorY;
    /* 0x24 */ f32 rVectorZ;
    /* 0x28 */ f32 kc;
    /* 0x2C */ f32 kl;
    /* 0x30 */ f32 kq;
    /* 0x34 */ s16 coordX;
    /* 0x36 */ s16 coordY;
    /* 0x38 */ s16 coordZ;
} __anon_0x59709; // size = 0x3C

typedef struct __anon_0x59939 {
    /* 0x00 */ s32 bTransformed;
    /* 0x04 */ struct __anon_0x59699 rS;
    /* 0x10 */ struct __anon_0x59699 rT;
    /* 0x1C */ struct __anon_0x59699 rSRaw;
    /* 0x28 */ struct __anon_0x59699 rTRaw;
} __anon_0x59939; // size = 0x34

typedef struct __anon_0x59A22 {
    /* 0x00 */ f32 rSum;
    /* 0x04 */ f32 rS;
    /* 0x08 */ f32 rT;
    /* 0x0C */ struct __anon_0x59699 vec;
    /* 0x18 */ u8 anColor[4];
} __anon_0x59A22; // size = 0x1C

typedef union __anon_0x59B81 {
    /* 0x0 */ u8 u8[4096];
    /* 0x0 */ u16 u16[2048];
    /* 0x0 */ u32 u32[1024];
    /* 0x0 */ u64 u64[512];
} __anon_0x59B81;

typedef struct __anon_0x59C1E {
    /* 0x0 */ union __anon_0x59B81 data;
} __anon_0x59C1E; // size = 0x1000

typedef enum _GXTexFmt {
    GX_TF_I4 = 0,
    GX_TF_I8 = 1,
    GX_TF_IA4 = 2,
    GX_TF_IA8 = 3,
    GX_TF_RGB565 = 4,
    GX_TF_RGB5A3 = 5,
    GX_TF_RGBA8 = 6,
    GX_TF_CMPR = 14,
    GX_CTF_R4 = 32,
    GX_CTF_RA4 = 34,
    GX_CTF_RA8 = 35,
    GX_CTF_YUVA8 = 38,
    GX_CTF_A8 = 39,
    GX_CTF_R8 = 40,
    GX_CTF_G8 = 41,
    GX_CTF_B8 = 42,
    GX_CTF_RG8 = 43,
    GX_CTF_GB8 = 44,
    GX_TF_Z8 = 17,
    GX_TF_Z16 = 19,
    GX_TF_Z24X8 = 22,
    GX_CTF_Z4 = 48,
    GX_CTF_Z8M = 57,
    GX_CTF_Z8L = 58,
    GX_CTF_Z16L = 60,
    GX_TF_A8 = 39,
} __anon_0x59CB7;

typedef struct _GXTlutObj {
    /* 0x0 */ u32 dummy[3];
} __anon_0x59E79; // size = 0xC

typedef struct _GXTexObj {
    /* 0x0 */ u32 dummy[8];
} __anon_0x59EE0; // size = 0x20

typedef enum _GXTexWrapMode {
    GX_CLAMP = 0,
    GX_REPEAT = 1,
    GX_MIRROR = 2,
    GX_MAX_TEXWRAPMODE = 3,
} __anon_0x59F26;

typedef struct _FRAME_TEXTURE {
    /* 0x00 */ s32 nMode;
    /* 0x04 */ s32 iPackPixel;
    /* 0x08 */ s32 iPackColor;
    /* 0x0C */ s32 nFrameLast;
    /* 0x10 */ s16 nSizeX;
    /* 0x12 */ s16 nSizeY;
    /* 0x14 */ u32 nAddress;
    /* 0x18 */ u32 nCodePixel;
    /* 0x1C */ u32 nCodeColor;
    /* 0x20 */ struct _FRAME_TEXTURE* pTextureNext;
    /* 0x24 */ u32 nData0;
    /* 0x28 */ u32 nData1;
    /* 0x2C */ u32 nData2;
    /* 0x30 */ u32 nData3;
    /* 0x34 */ enum _GXTexFmt eFormat;
    /* 0x38 */ struct _GXTlutObj objectTLUT;
    /* 0x44 */ struct _GXTexObj objectTexture;
    /* 0x64 */ enum _GXTexWrapMode eWrapS;
    /* 0x68 */ enum _GXTexWrapMode eWrapT;
} __anon_0x59F8F; // size = 0x6C

typedef struct __anon_0x5A2EC {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nTMEM;
    /* 0x08 */ s32 iTLUT;
    /* 0x0C */ s32 nSizeX;
    /* 0x10 */ s32 nFormat;
    /* 0x14 */ s16 nMaskS;
    /* 0x16 */ s16 nMaskT;
    /* 0x18 */ s16 nModeS;
    /* 0x1A */ s16 nModeT;
    /* 0x1C */ s16 nShiftS;
    /* 0x1E */ s16 nShiftT;
    /* 0x20 */ s16 nX0;
    /* 0x22 */ s16 nY0;
    /* 0x24 */ s16 nX1;
    /* 0x26 */ s16 nY1;
    /* 0x28 */ u32 nCodePixel;
} __anon_0x5A2EC; // size = 0x2C

typedef enum __anon_0x5A5CE {
    FMP_NONE = -1,
    FMP_PERSPECTIVE = 0,
    FMP_ORTHOGRAPHIC = 1,
} __anon_0x5A5CE;

typedef struct __anon_0x5A64F {
    /* 0x00 */ s32 nCount;
    /* 0x04 */ f32 rScale;
    /* 0x08 */ f32 rAspect;
    /* 0x0C */ f32 rFieldOfViewY;
    /* 0x10 */ f32 rClipNear;
    /* 0x14 */ f32 rClipFar;
    /* 0x18 */ u32 nAddressFloat;
    /* 0x1C */ u32 nAddressFixed;
    /* 0x20 */ enum __anon_0x5A5CE eProjection;
} __anon_0x5A64F; // size = 0x24

typedef struct _GXColor {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} __anon_0x5A7E4; // size = 0x4

typedef struct __anon_0x5A89F {
    /* 0x00000 */ u32 anCIMGAddresses[8];
    /* 0x00020 */ u16 nNumCIMGAddresses;
    /* 0x00024 */ s32 bBlurOn;
    /* 0x00028 */ s32 bHackPause;
    /* 0x0002C */ s32 nHackCount;
    /* 0x00030 */ s32 nFrameCounter;
    /* 0x00034 */ s32 bPauseThisFrame;
    /* 0x00038 */ s32 bCameFromBomberNotes;
    /* 0x0003C */ s32 bInBomberNotes;
    /* 0x00040 */ s32 bShrinking;
    /* 0x00044 */ s32 bSnapShot;
    /* 0x00048 */ s32 bUsingLens;
    /* 0x0004C */ u8 cBlurAlpha;
    /* 0x00050 */ s32 bBlurredThisFrame;
    /* 0x00054 */ s32 nFrameCIMGCalls;
    /* 0x00058 */ s32 bModifyZBuffer;
    /* 0x0005C */ s32 bOverrideDepth;
    /* 0x00060 */ s32 nZBufferSets;
    /* 0x00064 */ s32 nLastFrameZSets;
    /* 0x00068 */ s32 bPauseBGDrawn;
    /* 0x0006C */ s32 bFrameOn;
    /* 0x00070 */ s32 bBackBufferDrawn;
    /* 0x00074 */ s32 bGrabbedFrame;
    /* 0x00078 */ u64* pnGBI;
    /* 0x0007C */ u32 nFlag;
    /* 0x00080 */ f32 rScaleX;
    /* 0x00084 */ f32 rScaleY;
    /* 0x00088 */ u32 nCountFrames;
    /* 0x0008C */ u32 nMode;
    /* 0x00090 */ u32 aMode[10];
    /* 0x000B8 */ struct __anon_0x594BE viewport;
    /* 0x000C8 */ struct __anon_0x59558 aBuffer[4];
    /* 0x00118 */ u32 nOffsetDepth0;
    /* 0x0011C */ u32 nOffsetDepth1;
    /* 0x00120 */ s32 nWidthLine;
    /* 0x00124 */ f32 rDepth;
    /* 0x00128 */ f32 rDelta;
    /* 0x0012C */ s32 (*aDraw[4])(void*, void*);
    /* 0x0013C */ s32 nCountLight;
    /* 0x00140 */ struct __anon_0x59709 aLight[8];
    /* 0x00320 */ struct __anon_0x59939 lookAt;
    /* 0x00354 */ s32 nCountVertex;
    /* 0x00358 */ struct __anon_0x59A22 aVertex[80];
    /* 0x00C18 */ struct __anon_0x59C1E TMEM;
    /* 0x01C18 */ void* aPixelData;
    /* 0x01C1C */ void* aColorData;
    /* 0x01C20 */ s32 nBlocksPixel;
    /* 0x01C24 */ s32 nBlocksMaxPixel;
    /* 0x01C28 */ s32 nBlocksColor;
    /* 0x01C2C */ s32 nBlocksMaxColor;
    /* 0x01C30 */ s32 nBlocksTexture;
    /* 0x01C34 */ s32 nBlocksMaxTexture;
    /* 0x01C38 */ u32 anPackPixel[48];
    /* 0x01CF8 */ u32 anPackColor[320];
    /* 0x021F8 */ u32 nAddressLoad;
    /* 0x021FC */ u32 nCodePixel;
    /* 0x02200 */ u32 nTlutCode[16];
    /* 0x02240 */ struct _FRAME_TEXTURE aTexture[2048];
    /* 0x38240 */ u32 anTextureUsed[64];
    /* 0x38340 */ struct _FRAME_TEXTURE* apTextureCached[4096];
    /* 0x3C340 */ s32 iTileLoad;
    /* 0x3C344 */ u32 n2dLoadTexType;
    /* 0x3C348 */ s32 nLastX0;
    /* 0x3C34C */ s32 nLastY0;
    /* 0x3C350 */ s32 nLastX1;
    /* 0x3C354 */ s32 nLastY1;
    /* 0x3C358 */ struct __anon_0x5A2EC aTile[8];
    /* 0x3C4B8 */ s32 anSizeX[2];
    /* 0x3C4C0 */ s32 anSizeY[2];
    /* 0x3C4C8 */ s32 iHintMatrix;
    /* 0x3C4CC */ s32 iMatrixModel;
    /* 0x3C4D0 */ s32 iHintProjection;
    /* 0x3C4D4 */ f32 matrixView[4][4];
    /* 0x3C514 */ s32 iHintLast;
    /* 0x3C518 */ s32 iHintHack;
    /* 0x3C51C */ enum __anon_0x5A5CE eTypeProjection;
    /* 0x3C520 */ f32 aMatrixModel[10][4][4];
    /* 0x3C7A0 */ f32 matrixProjection[4][4];
    /* 0x3C7E0 */ f32 matrixProjectionExtra[4][4];
    /* 0x3C820 */ struct __anon_0x5A64F aMatrixHint[64];
    /* 0x3D120 */ u8 primLODmin;
    /* 0x3D121 */ u8 primLODfrac;
    /* 0x3D122 */ u8 lastTile;
    /* 0x3D123 */ u8 iTileDrawn;
    /* 0x3D124 */ struct _GXColor aColor[5];
    /* 0x3D138 */ u32 nModeVtx;
    /* 0x3D13C */ u16* nTempBuffer;
    /* 0x3D140 */ u16* nCopyBuffer;
    /* 0x3D144 */ u32* nLensBuffer;
    /* 0x3D148 */ u16* nCameraBuffer;
} __anon_0x5A89F; // size = 0x3D150

typedef struct __anon_0x5B8F2 {
    /* 0x00 */ s32 nOffsetCode;
    /* 0x04 */ s32 nLengthCode;
    /* 0x08 */ s32 nOffsetData;
    /* 0x0C */ s32 nLengthData;
    /* 0x10 */ char acUCodeName[64];
    /* 0x50 */ u64 nUCodeCheckSum;
    /* 0x58 */ s32 nCountVertex;
    /* 0x5C */ enum __anon_0x60B3F eType;
} __anon_0x5B8F2; // size = 0x60

typedef struct __anon_0x5C1E6 {
    /* 0x0 */ s32 nOffsetHost;
    /* 0x4 */ s32 nAddressN64;
} __anon_0x5C1E6; // size = 0x8

typedef struct cpu_callerID {
    /* 0x0 */ s32 N64address;
    /* 0x4 */ s32 GCNaddress;
} __anon_0x5C24C; // size = 0x8

typedef struct cpu_function {
    /* 0x00 */ void* pnBase;
    /* 0x04 */ void* pfCode;
    /* 0x08 */ s32 nCountJump;
    /* 0x0C */ struct __anon_0x5C1E6* aJump;
    /* 0x10 */ s32 nAddress0;
    /* 0x14 */ s32 nAddress1;
    /* 0x18 */ struct cpu_callerID* block;
    /* 0x1C */ s32 callerID_total;
    /* 0x20 */ s32 callerID_flag;
    /* 0x24 */ u32 nChecksum;
    /* 0x28 */ s32 timeToLive;
    /* 0x2C */ s32 memory_size;
    /* 0x30 */ s32 heapID;
    /* 0x34 */ s32 heapWhere;
    /* 0x38 */ s32 treeheapWhere;
    /* 0x3C */ struct cpu_function* prev;
    /* 0x40 */ struct cpu_function* left;
    /* 0x44 */ struct cpu_function* right;
} __anon_0x5C2BF; // size = 0x48

typedef union __anon_0x5C59B {
    /* 0x0 */ char _0s8;
    /* 0x1 */ char _1s8;
    /* 0x2 */ char _2s8;
    /* 0x3 */ char _3s8;
    /* 0x4 */ char _4s8;
    /* 0x5 */ char _5s8;
    /* 0x6 */ char _6s8;
    /* 0x7 */ char s8;
    /* 0x0 */ s16 _0s16;
    /* 0x2 */ s16 _1s16;
    /* 0x4 */ s16 _2s16;
    /* 0x6 */ s16 s16;
    /* 0x0 */ s32 _0s32;
    /* 0x4 */ s32 s32;
    /* 0x0 */ s64 s64;
    /* 0x0 */ u8 _0u8;
    /* 0x1 */ u8 _1u8;
    /* 0x2 */ u8 _2u8;
    /* 0x3 */ u8 _3u8;
    /* 0x4 */ u8 _4u8;
    /* 0x5 */ u8 _5u8;
    /* 0x6 */ u8 _6u8;
    /* 0x7 */ u8 u8;
    /* 0x0 */ u16 _0u16;
    /* 0x2 */ u16 _1u16;
    /* 0x4 */ u16 _2u16;
    /* 0x6 */ u16 u16;
    /* 0x0 */ u32 _0u32;
    /* 0x4 */ u32 u32;
    /* 0x0 */ u64 u64;
} __anon_0x5C59B;

typedef union __anon_0x5C9AF {
    /* 0x0 */ f32 _0f32;
    /* 0x4 */ f32 f32;
    /* 0x0 */ f64 f64;
    /* 0x0 */ s32 _0s32;
    /* 0x4 */ s32 s32;
    /* 0x0 */ s64 s64;
    /* 0x0 */ u32 _0u32;
    /* 0x4 */ u32 u32;
    /* 0x0 */ u64 u64;
} __anon_0x5C9AF;

typedef struct __anon_0x5CEBD {
    /* 0x00 */ s32 nType;
    /* 0x04 */ void* pObject;
    /* 0x08 */ s32 nOffsetAddress;
    /* 0x0C */ s32 (*pfGet8)(void*, u32, char*);
    /* 0x10 */ s32 (*pfGet16)(void*, u32, s16*);
    /* 0x14 */ s32 (*pfGet32)(void*, u32, s32*);
    /* 0x18 */ s32 (*pfGet64)(void*, u32, s64*);
    /* 0x1C */ s32 (*pfPut8)(void*, u32, char*);
    /* 0x20 */ s32 (*pfPut16)(void*, u32, s16*);
    /* 0x24 */ s32 (*pfPut32)(void*, u32, s32*);
    /* 0x28 */ s32 (*pfPut64)(void*, u32, s64*);
    /* 0x2C */ u32 nAddressPhysical0;
    /* 0x30 */ u32 nAddressPhysical1;
} __anon_0x5CEBD; // size = 0x34

typedef struct cpu_treeRoot {
    /* 0x00 */ u16 total;
    /* 0x04 */ s32 total_memory;
    /* 0x08 */ s32 root_address;
    /* 0x0C */ s32 start_range;
    /* 0x10 */ s32 end_range;
    /* 0x14 */ s32 cache_miss;
    /* 0x18 */ s32 cache[20];
    /* 0x68 */ struct cpu_function* left;
    /* 0x6C */ struct cpu_function* right;
    /* 0x70 */ s32 kill_limit;
    /* 0x74 */ s32 kill_number;
    /* 0x78 */ s32 side;
    /* 0x7C */ struct cpu_function* restore;
    /* 0x80 */ s32 restore_side;
} __anon_0x5D18B; // size = 0x84

typedef struct _CPU_ADDRESS {
    /* 0x0 */ s32 nN64;
    /* 0x4 */ s32 nHost;
    /* 0x8 */ struct cpu_function* pFunction;
} __anon_0x5D3CC; // size = 0xC

typedef struct __anon_0x5D481 {
    /* 0x0 */ u32 nAddress;
    /* 0x4 */ u32 nOpcodeOld;
    /* 0x8 */ u32 nOpcodeNew;
} __anon_0x5D481; // size = 0xC

typedef struct OSContext {
    /* 0x000 */ u32 gpr[32];
    /* 0x080 */ u32 cr;
    /* 0x084 */ u32 lr;
    /* 0x088 */ u32 ctr;
    /* 0x08C */ u32 xer;
    /* 0x090 */ f64 fpr[32];
    /* 0x190 */ u32 fpscr_pad;
    /* 0x194 */ u32 fpscr;
    /* 0x198 */ u32 srr0;
    /* 0x19C */ u32 srr1;
    /* 0x1A0 */ u16 mode;
    /* 0x1A2 */ u16 state;
    /* 0x1A4 */ u32 gqr[8];
    /* 0x1C4 */ u32 psf_pad;
    /* 0x1C8 */ f64 psf[32];
} __anon_0x5D5AC; // size = 0x2C8

typedef struct OSAlarm {
    /* 0x00 */ void (*handler)(struct OSAlarm*, struct OSContext*);
    /* 0x04 */ u32 tag;
    /* 0x08 */ s64 fire;
    /* 0x10 */ struct OSAlarm* prev;
    /* 0x14 */ struct OSAlarm* next;
    /* 0x18 */ s64 period;
    /* 0x20 */ s64 start;
} __anon_0x5D803; // size = 0x28

typedef struct cpu_optimize {
    /* 0x00 */ u32 validCheck;
    /* 0x04 */ u32 destGPR_check;
    /* 0x08 */ s32 destGPR;
    /* 0x0C */ s32 destGPR_mapping;
    /* 0x10 */ u32 destFPR_check;
    /* 0x14 */ s32 destFPR;
    /* 0x18 */ u32 addr_check;
    /* 0x1C */ s32 addr_last;
    /* 0x20 */ u32 checkType;
    /* 0x24 */ u32 checkNext;
} __anon_0x5D91E; // size = 0x28

typedef struct _CPU {
    /* 0x00000 */ s32 nMode;
    /* 0x00004 */ s32 nTick;
    /* 0x00008 */ void* pHost;
    /* 0x00010 */ s64 nLo;
    /* 0x00018 */ s64 nHi;
    /* 0x00020 */ s32 nCountAddress;
    /* 0x00024 */ s32 iDeviceDefault;
    /* 0x00028 */ u32 nPC;
    /* 0x0002C */ u32 nWaitPC;
    /* 0x00030 */ u32 nCallLast;
    /* 0x00034 */ struct cpu_function* pFunctionLast;
    /* 0x00038 */ s32 nReturnAddrLast;
    /* 0x0003C */ s32 survivalTimer;
    /* 0x00040 */ union __anon_0x5C59B aGPR[32];
    /* 0x00140 */ union __anon_0x5C9AF aFPR[32];
    /* 0x00240 */ u64 aTLB[48][5];
    /* 0x009C0 */ s32 anFCR[32];
    /* 0x00A40 */ s64 anCP0[32];
    /* 0x00B40 */ s32 (*pfStep)(struct _CPU*);
    /* 0x00B44 */ s32 (*pfJump)(struct _CPU*);
    /* 0x00B48 */ s32 (*pfCall)(struct _CPU*);
    /* 0x00B4C */ s32 (*pfIdle)(struct _CPU*);
    /* 0x00B50 */ s32 (*pfRam)(struct _CPU*);
    /* 0x00B54 */ s32 (*pfRamF)(struct _CPU*);
    /* 0x00B58 */ u32 nTickLast;
    /* 0x00B5C */ u32 nRetrace;
    /* 0x00B60 */ u32 nRetraceUsed;
    /* 0x00B64 */ struct __anon_0x5CEBD* apDevice[256];
    /* 0x00F64 */ u8 aiDevice[65536];
    /* 0x10F64 */ void* gHeap1;
    /* 0x10F68 */ void* gHeap2;
    /* 0x10F6C */ u32 aHeap1Flag[192];
    /* 0x1126C */ u32 aHeap2Flag[13];
    /* 0x112A0 */ struct cpu_treeRoot* gTree;
    /* 0x112A4 */ struct _CPU_ADDRESS aAddressCache[256];
    /* 0x11EA4 */ s32 nCountCodeHack;
    /* 0x11EA8 */ struct __anon_0x5D481 aCodeHack[32];
    /* 0x12028 */ s64 nTimeRetrace;
    /* 0x12030 */ struct OSAlarm alarmRetrace;
    /* 0x12058 */ u32 nFlagRAM;
    /* 0x1205C */ u32 nFlagCODE;
    /* 0x12060 */ u32 nCompileFlag;
    /* 0x12064 */ struct cpu_optimize nOptimize;
} __anon_0x5DACB; // size = 0x12090

typedef enum __anon_0x5E613 {
    SM_NONE = -1,
    SM_RUNNING = 0,
    SM_STOPPED = 1,
} __anon_0x5E613;

typedef struct __anon_0x5E675 {
    /* 0x0 */ s32 nSize;
    /* 0x4 */ s32 nOffsetRAM;
    /* 0x8 */ s32 nOffsetROM;
    /* 0xC */ s32 (*pCallback)();
} __anon_0x5E675; // size = 0x10

typedef enum __anon_0x5E726 {
    SRT_NONE = -1,
    SRT_MARIO = 0,
    SRT_WAVERACE = 1,
    SRT_MARIOKART = 2,
    SRT_STARFOX = 3,
    SRT_ZELDA1 = 4,
    SRT_ZELDA2 = 5,
    SRT_1080 = 6,
    SRT_PANEL = 7,
    SRT_MARIOPARTY1 = 8,
    SRT_MARIOPARTY2 = 9,
    SRT_MARIOPARTY3 = 10,
    SRT_DRMARIO = 11,
    SRT_UNKNOWN = 12,
} __anon_0x5E726;

typedef enum __anon_0x5E852 {
    SOT_NONE = -1,
    SOT_CPU = 0,
    SOT_PIF = 1,
    SOT_RAM = 2,
    SOT_ROM = 3,
    SOT_RSP = 4,
    SOT_RDP = 5,
    SOT_MIPS = 6,
    SOT_DISK = 7,
    SOT_FLASH = 8,
    SOT_SRAM = 9,
    SOT_AUDIO = 10,
    SOT_VIDEO = 11,
    SOT_SERIAL = 12,
    SOT_LIBRARY = 13,
    SOT_PERIPHERAL = 14,
    SOT_RDB = 15,
    SOT_COUNT = 16,
} __anon_0x5E852;

typedef struct __anon_0x5E98D {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ s32 bException;
    /* 0x0C */ enum __anon_0x5E613 eMode;
    /* 0x10 */ struct __anon_0x5E675 romCopy;
    /* 0x20 */ enum __anon_0x5E726 eTypeROM;
    /* 0x24 */ void* apObject[16];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ enum __anon_0x5E852 storageDevice;
    /* 0x74 */ u8 anException[16];
    /* 0x84 */ s32 bJapaneseVersion;
} __anon_0x5E98D; // size = 0x88

// size = 0x4, address = 0x80135600
struct __anon_0x5E98D* gpSystem;

typedef struct __anon_0x5EBE0 {
    /* 0x0 */ s32 nCount;
    /* 0x4 */ u8 anData[768];
} __anon_0x5EBE0; // size = 0x304

typedef struct __anon_0x5EC3E {
    /* 0x0 */ s16 sx;
    /* 0x2 */ s16 sy;
    /* 0x4 */ s32 invw;
    /* 0x8 */ s16 xi;
    /* 0xA */ s16 yi;
    /* 0xC */ u8 cc;
    /* 0xD */ u8 fog;
    /* 0xE */ s16 wi;
} __anon_0x5EC3E; // size = 0x10

typedef struct __anon_0x5ED4F {
    /* 0x00 */ u16 imageX;
    /* 0x02 */ u16 imageW;
    /* 0x04 */ s16 frameX;
    /* 0x06 */ u16 frameW;
    /* 0x08 */ u16 imageY;
    /* 0x0A */ u16 imageH;
    /* 0x0C */ s16 frameY;
    /* 0x0E */ u16 frameH;
    /* 0x10 */ u32 imagePtr;
    /* 0x14 */ u16 imageLoad;
    /* 0x16 */ u8 imageFmt;
    /* 0x17 */ u8 imageSiz;
    /* 0x18 */ u16 imagePal;
    /* 0x1A */ u16 imageFlip;
    /* 0x1C */ u16 tmemW;
    /* 0x1E */ u16 tmemH;
    /* 0x20 */ u16 tmemLoadSH;
    /* 0x22 */ u16 tmemLoadTH;
    /* 0x24 */ u16 tmemSizeW;
    /* 0x26 */ u16 tmemSize;
} __anon_0x5ED4F; // size = 0x28

typedef struct __anon_0x5F05A {
    /* 0x00 */ u16 imageX;
    /* 0x02 */ u16 imageW;
    /* 0x04 */ s16 frameX;
    /* 0x06 */ u16 frameW;
    /* 0x08 */ u16 imageY;
    /* 0x0A */ u16 imageH;
    /* 0x0C */ s16 frameY;
    /* 0x0E */ u16 frameH;
    /* 0x10 */ u32 imagePtr;
    /* 0x14 */ u16 imageLoad;
    /* 0x16 */ u8 imageFmt;
    /* 0x17 */ u8 imageSiz;
    /* 0x18 */ u16 imagePal;
    /* 0x1A */ u16 imageFlip;
    /* 0x1C */ u16 scaleW;
    /* 0x1E */ u16 scaleH;
    /* 0x20 */ s32 imageYorig;
    /* 0x24 */ u8 padding[4];
} __anon_0x5F05A; // size = 0x28

typedef union __anon_0x5F2FB {
    /* 0x0 */ struct __anon_0x5ED4F b;
    /* 0x0 */ struct __anon_0x5F05A s;
    /* 0x0 */ s64 force_structure_alignment;
} __anon_0x5F2FB;

typedef struct __anon_0x5F429 {
    /* 0x00 */ s16 objX;
    /* 0x02 */ u16 scaleW;
    /* 0x04 */ u16 imageW;
    /* 0x06 */ u16 paddingX;
    /* 0x08 */ s16 objY;
    /* 0x0A */ u16 scaleH;
    /* 0x0C */ u16 imageH;
    /* 0x0E */ u16 paddingY;
    /* 0x10 */ u16 imageStride;
    /* 0x12 */ u16 imageAdrs;
    /* 0x14 */ u8 imageFmt;
    /* 0x15 */ u8 imageSiz;
    /* 0x16 */ u8 imagePal;
    /* 0x17 */ u8 imageFlags;
} __anon_0x5F429; // size = 0x18

typedef union __anon_0x5F63B {
    /* 0x0 */ struct __anon_0x5F429 s;
    /* 0x0 */ s64 force_structure_alignment;
} __anon_0x5F63B;

typedef struct __anon_0x5F6E9 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} __anon_0x5F6E9; // size = 0xC

typedef struct __anon_0x5F759 {
    /* 0x00 */ s32 bFlip;
    /* 0x04 */ s32 iTile;
    /* 0x08 */ s32 nX0;
    /* 0x0C */ s32 nY0;
    /* 0x10 */ s32 nX1;
    /* 0x14 */ s32 nY1;
    /* 0x18 */ f32 rS;
    /* 0x1C */ f32 rT;
    /* 0x20 */ f32 rDeltaS;
    /* 0x24 */ f32 rDeltaT;
} __anon_0x5F759; // size = 0x28

typedef struct __anon_0x5F8B9 {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 image;
    /* 0x08 */ u16 tmem;
    /* 0x0A */ u16 tsize;
    /* 0x0C */ u16 tline;
    /* 0x0E */ u16 sid;
    /* 0x10 */ u32 flag;
    /* 0x14 */ u32 mask;
} __anon_0x5F8B9; // size = 0x18

typedef struct __anon_0x5F9D9 {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 image;
    /* 0x08 */ u16 tmem;
    /* 0x0A */ u16 twidth;
    /* 0x0C */ u16 theight;
    /* 0x0E */ u16 sid;
    /* 0x10 */ u32 flag;
    /* 0x14 */ u32 mask;
} __anon_0x5F9D9; // size = 0x18

typedef struct __anon_0x5FAFC {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 image;
    /* 0x08 */ u16 phead;
    /* 0x0A */ u16 pnum;
    /* 0x0C */ u16 zero;
    /* 0x0E */ u16 sid;
    /* 0x10 */ u32 flag;
    /* 0x14 */ u32 mask;
} __anon_0x5FAFC; // size = 0x18

typedef union __anon_0x5FC1B {
    /* 0x0 */ struct __anon_0x5F8B9 block;
    /* 0x0 */ struct __anon_0x5F9D9 tile;
    /* 0x0 */ struct __anon_0x5FAFC tlut;
    /* 0x0 */ s64 force_structure_alignment;
} __anon_0x5FC1B;

typedef enum __anon_0x6029B {
    XLFT_NONE = -1,
    XLFT_TEXT = 0,
    XLFT_BINARY = 1,
} __anon_0x6029B;

typedef struct DVDDiskID {
    /* 0x0 */ char gameName[4];
    /* 0x4 */ char company[2];
    /* 0x6 */ u8 diskNumber;
    /* 0x7 */ u8 gameVersion;
    /* 0x8 */ u8 streaming;
    /* 0x9 */ u8 streamingBufSize;
    /* 0xA */ u8 padding[22];
} __anon_0x6034F; // size = 0x20

typedef struct DVDCommandBlock {
    /* 0x00 */ struct DVDCommandBlock* next;
    /* 0x04 */ struct DVDCommandBlock* prev;
    /* 0x08 */ u32 command;
    /* 0x0C */ s32 state;
    /* 0x10 */ u32 offset;
    /* 0x14 */ u32 length;
    /* 0x18 */ void* addr;
    /* 0x1C */ u32 currTransferSize;
    /* 0x20 */ u32 transferredSize;
    /* 0x24 */ struct DVDDiskID* id;
    /* 0x28 */ void (*callback)(s32, struct DVDCommandBlock*);
    /* 0x2C */ void* userData;
} __anon_0x604BF; // size = 0x30

typedef struct DVDFileInfo {
    /* 0x00 */ struct DVDCommandBlock cb;
    /* 0x30 */ u32 startAddr;
    /* 0x34 */ u32 length;
    /* 0x38 */ void (*callback)(s32, struct DVDFileInfo*);
} __anon_0x606E5; // size = 0x3C

typedef struct tXL_FILE {
    /* 0x00 */ s32 iBuffer;
    /* 0x04 */ void* pData;
    /* 0x08 */ void* pBuffer;
    /* 0x0C */ s32 nAttributes;
    /* 0x10 */ s32 nSize;
    /* 0x14 */ s32 nOffset;
    /* 0x18 */ enum __anon_0x6029B eType;
    /* 0x1C */ struct DVDFileInfo info;
} __anon_0x6079D; // size = 0x58

typedef enum __anon_0x60B3F {
    RUT_NONE = -1,
    RUT_TURBO = 0,
    RUT_SPRITE2D = 1,
    RUT_FAST3D = 2,
    RUT_ZSORT = 3,
    RUT_LINE3D = 4,
    RUT_F3DEX1 = 5,
    RUT_F3DEX2 = 6,
    RUT_S2DEX1 = 7,
    RUT_S2DEX2 = 8,
    RUT_L3DEX1 = 9,
    RUT_L3DEX2 = 10,
    RUT_AUDIO1 = 11,
    RUT_AUDIO2 = 12,
    RUT_JPEG = 13,
} __anon_0x60B3F;

// Range: 0x800741CC -> 0x80074454
static s32 rspLoadMatrix(struct __anon_0x5845E* pRSP, s32 nAddress, f32 (*matrix)[4]) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 nAddress; // r4
    // f32 (* matrix)[4]; // r31

    // Local variables
    s32* pMtx; // r1+0x18
    s32 nDataA; // r6
    s32 nDataB; // r7
    f32 rScale; // f31
    f32 rUpper; // r1+0x8
    f32 rLower; // r1+0x8
    u16 nUpper; // r1+0x16
    u16 nLower; // r1+0x14
}

// Erased
static s32 rspSetDL(struct __anon_0x5845E* pRSP, s32 nOffsetRDRAM, s32 bPush) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // s32 nOffsetRDRAM; // r1+0xC
    // s32 bPush; // r31

    // Local variables
    s32 nAddress; // r5
    s32* pDL; // r1+0x14
}

// Erased
static s32 rspPopDL(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
}

// Erased
static s32 rspSetupUCode(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    struct __anon_0x5A89F* pFrame; // r3
}

// Erased
static s32 rspGetNumUCodes(struct __anon_0x5845E* pRSP, u32* pNumCodes) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32* pNumCodes; // r1+0x4
}

// Erased
static s32 rspGetUCodeName(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0

    // Local variables
    u32 nItemCount; // r1+0x0
    void* pListNode; // r3
}

// Range: 0x8007306C -> 0x800741CC
static s32 rspFindUCode(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r24
    // struct __anon_0x575BD* pTask; // r1+0xC

    // Local variables
    s32 nCountVertex; // r16
    struct __anon_0x5B8F2* pUCode; // r1+0x1080
    enum __anon_0x60B3F eType; // r17
    void* pListNode; // r5
    s32 nOffsetCode; // r1+0x108C
    s32 nOffsetData; // r14
    u64 nFUData; // r30
    u64* pFUData; // r1+0x107C
    u64* pFUCode; // r1+0x1078
    u64 nCheckSum; // r27
    u32 nLengthData; // r1+0x1088
    u32 i; // r6
    u32 nLengthCode; // r1+0x1084
    char aBigBuffer[4096]; // r1+0x5C
    char acUCodeName[64]; // r1+0x1C
}

// Range: 0x80072EF4 -> 0x8007306C
static s32 rspSaveYield(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r7

    // Local variables
    s32 iData; // r1+0x8
    struct __anon_0x575BD* pTask; // r4
}

// Range: 0x80072D6C -> 0x80072EF4
static s32 rspLoadYield(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30

    // Local variables
    s32 iData; // r1+0x8
    struct __anon_0x575BD* pTask; // r3
}

// Erased
static s32 rspParseDisplayLists(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28

    // Local variables
    s32 bDone; // r1+0xC
    s32 nStatus; // r3
    s32* pDL; // r1+0x8
    u64 nGBI; // r30
}

// Erased
static s32 rspTaskComplete(struct __anon_0x5845E* pRSP, s32 bUsedSP, s32 bUsedDP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // s32 bUsedSP; // r1+0xC
    // s32 bUsedDP; // r31
}

// Range: 0x80072C10 -> 0x80072D6C
static s32 rspParseGBI_Setup(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // struct __anon_0x575BD* pTask; // r31

    // Local variables
    s32 iSegment; // r1+0x8
}

// Range: 0x80072A5C -> 0x80072C10
static s32 rspParseGBI(struct __anon_0x5845E* pRSP, s32* pbDone, s32 nCount) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r27
    // s32* pbDone; // r28
    // s32 nCount; // r29

    // Local variables
    s32 bDone; // r1+0x14
    s32 nStatus; // r3
    u64* pDL; // r26
    struct _CPU* pCPU; // r30
}

// Erased
static s32 rspSaveUCode() {}

// Range: 0x80072A08 -> 0x80072A5C
s32 rspPut8(struct __anon_0x5845E* pRSP, u32 nAddress, char* pData) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // char* pData; // r1+0x8
}

// Range: 0x800729B4 -> 0x80072A08
s32 rspPut16(struct __anon_0x5845E* pRSP, u32 nAddress, s16* pData) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s16* pData; // r1+0x8
}

// Range: 0x80072384 -> 0x800729B4
s32 rspPut32(struct __anon_0x5845E* pRSP, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // u32 nAddress; // r1+0xC
    // s32* pData; // r1+0x10

    // Local variables
    struct __anon_0x575BD* pTask; // r4
    s32 nData; // r31
    s32 nSize; // r1+0x24
    void* pTarget; // r1+0x20
    void* pSource; // r4
    s32 nLength; // r5
}

// Range: 0x80072318 -> 0x80072384
s32 rspPut64(struct __anon_0x5845E* pRSP, u32 nAddress, s64* pData) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s64* pData; // r1+0x8
}

// Range: 0x800722C4 -> 0x80072318
s32 rspGet8(struct __anon_0x5845E* pRSP, u32 nAddress, char* pData) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // char* pData; // r1+0x8
}

// Range: 0x80072270 -> 0x800722C4
s32 rspGet16(struct __anon_0x5845E* pRSP, u32 nAddress, s16* pData) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s16* pData; // r1+0x8
}

// Range: 0x80072124 -> 0x80072270
s32 rspGet32(struct __anon_0x5845E* pRSP, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s32* pData; // r1+0x8
}

// Range: 0x800720B8 -> 0x80072124
s32 rspGet64(struct __anon_0x5845E* pRSP, u32 nAddress, s64* pData) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s64* pData; // r1+0x8
}

// Range: 0x80071FE0 -> 0x800720B8
s32 rspInvalidateCache(struct __anon_0x5845E* pRSP, s32 nOffset0, s32 nOffset1) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // s32 nOffset0; // r29
    // s32 nOffset1; // r30

    // Local variables
    struct __anon_0x5B8F2* pUCode; // r1+0x14
    void* pListNode; // r31
    s32 nOffsetUCode0; // r3
    s32 nOffsetUCode1; // r1+0x8
}

// Range: 0x80071FC0 -> 0x80071FE0
s32 rspEnableABI(struct __anon_0x5845E* pRSP, s32 bFlag) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // s32 bFlag; // r1+0x4
}

// Range: 0x80071F6C -> 0x80071FC0
s32 rspFrameComplete(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
}

// Range: 0x80071D8C -> 0x80071F6C
s32 rspUpdate(struct __anon_0x5845E* pRSP, enum __anon_0x5943B eMode) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29
    // enum __anon_0x5943B eMode; // r30

    // Local variables
    struct __anon_0x575BD* pTask; // r4
    s32 bDone; // r1+0x10
    s32 nCount; // r31
    struct __anon_0x5A89F* pFrame; // r28

    // References
    // -> s32 gNoSwapBuffer;
}

// Range: 0x80071BB8 -> 0x80071D8C
s32 rspEvent(struct __anon_0x5845E* pRSP, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
