/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\video.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008E8A0 -> 0x8008EE20
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x75A44; // size = 0x10

// size = 0x10, address = 0x800EE870
struct _XL_OBJECTTYPE gClassVideo;

typedef struct __anon_0x75B37 {
    /* 0x00 */ s32 nScan;
    /* 0x04 */ s32 bBlack;
    /* 0x08 */ s32 nBurst;
    /* 0x0C */ s32 nSizeX;
    /* 0x10 */ void* pHost;
    /* 0x14 */ s32 nStatus;
    /* 0x18 */ s32 nTiming;
    /* 0x1C */ s32 nAddress;
    /* 0x20 */ s32 nScanInterrupt;
    /* 0x24 */ s32 nScaleX;
    /* 0x28 */ s32 nScaleY;
    /* 0x2C */ s32 nStartH;
    /* 0x30 */ s32 nStartV;
    /* 0x34 */ s32 nSyncH;
    /* 0x38 */ s32 nSyncV;
    /* 0x3C */ s32 nSyncLeap;
} __anon_0x75B37; // size = 0x40

typedef struct __anon_0x76165 {
    /* 0x0 */ f32 rX;
    /* 0x4 */ f32 rY;
    /* 0x8 */ f32 rSizeX;
    /* 0xC */ f32 rSizeY;
} __anon_0x76165; // size = 0x10

typedef struct __anon_0x761FF {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nWidth;
    /* 0x08 */ s32 nFormat;
    /* 0x0C */ void* pData;
    /* 0x10 */ s32 nAddress;
} __anon_0x761FF; // size = 0x14

typedef struct __anon_0x76340 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} __anon_0x76340; // size = 0xC

typedef struct __anon_0x763B0 {
    /* 0x00 */ s32 bTransformed;
    /* 0x04 */ struct __anon_0x76340 rVecOrigTowards;
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
} __anon_0x763B0; // size = 0x3C

typedef struct __anon_0x765E0 {
    /* 0x00 */ s32 bTransformed;
    /* 0x04 */ struct __anon_0x76340 rS;
    /* 0x10 */ struct __anon_0x76340 rT;
    /* 0x1C */ struct __anon_0x76340 rSRaw;
    /* 0x28 */ struct __anon_0x76340 rTRaw;
} __anon_0x765E0; // size = 0x34

typedef struct __anon_0x766C9 {
    /* 0x00 */ f32 rSum;
    /* 0x04 */ f32 rS;
    /* 0x08 */ f32 rT;
    /* 0x0C */ struct __anon_0x76340 vec;
    /* 0x18 */ u8 anColor[4];
} __anon_0x766C9; // size = 0x1C

typedef union __anon_0x76828 {
    /* 0x0 */ u8 u8[4096];
    /* 0x0 */ u16 u16[2048];
    /* 0x0 */ u32 u32[1024];
    /* 0x0 */ u64 u64[512];
} __anon_0x76828;

typedef struct __anon_0x768C5 {
    /* 0x0 */ union __anon_0x76828 data;
} __anon_0x768C5; // size = 0x1000

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
} __anon_0x7695E;

typedef struct _GXTlutObj {
    /* 0x0 */ u32 dummy[3];
} __anon_0x76B20; // size = 0xC

typedef struct _GXTexObj {
    /* 0x0 */ u32 dummy[8];
} __anon_0x76B87; // size = 0x20

typedef enum _GXTexWrapMode {
    GX_CLAMP = 0,
    GX_REPEAT = 1,
    GX_MIRROR = 2,
    GX_MAX_TEXWRAPMODE = 3,
} __anon_0x76BCD;

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
} __anon_0x76C36; // size = 0x6C

typedef struct __anon_0x76F93 {
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
} __anon_0x76F93; // size = 0x2C

typedef enum __anon_0x77275 {
    FMP_NONE = -1,
    FMP_PERSPECTIVE = 0,
    FMP_ORTHOGRAPHIC = 1,
} __anon_0x77275;

typedef struct __anon_0x772F8 {
    /* 0x00 */ s32 nCount;
    /* 0x04 */ f32 rScale;
    /* 0x08 */ f32 rAspect;
    /* 0x0C */ f32 rFieldOfViewY;
    /* 0x10 */ f32 rClipNear;
    /* 0x14 */ f32 rClipFar;
    /* 0x18 */ u32 nAddressFloat;
    /* 0x1C */ u32 nAddressFixed;
    /* 0x20 */ enum __anon_0x77275 eProjection;
} __anon_0x772F8; // size = 0x24

typedef struct _GXColor {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} __anon_0x7748D; // size = 0x4

typedef struct __anon_0x77548 {
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
    /* 0x000B8 */ struct __anon_0x76165 viewport;
    /* 0x000C8 */ struct __anon_0x761FF aBuffer[4];
    /* 0x00118 */ u32 nOffsetDepth0;
    /* 0x0011C */ u32 nOffsetDepth1;
    /* 0x00120 */ s32 nWidthLine;
    /* 0x00124 */ f32 rDepth;
    /* 0x00128 */ f32 rDelta;
    /* 0x0012C */ s32 (*aDraw[4])(void*, void*);
    /* 0x0013C */ s32 nCountLight;
    /* 0x00140 */ struct __anon_0x763B0 aLight[8];
    /* 0x00320 */ struct __anon_0x765E0 lookAt;
    /* 0x00354 */ s32 nCountVertex;
    /* 0x00358 */ struct __anon_0x766C9 aVertex[80];
    /* 0x00C18 */ struct __anon_0x768C5 TMEM;
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
    /* 0x3C358 */ struct __anon_0x76F93 aTile[8];
    /* 0x3C4B8 */ s32 anSizeX[2];
    /* 0x3C4C0 */ s32 anSizeY[2];
    /* 0x3C4C8 */ s32 iHintMatrix;
    /* 0x3C4CC */ s32 iMatrixModel;
    /* 0x3C4D0 */ s32 iHintProjection;
    /* 0x3C4D4 */ f32 matrixView[4][4];
    /* 0x3C514 */ s32 iHintLast;
    /* 0x3C518 */ s32 iHintHack;
    /* 0x3C51C */ enum __anon_0x77275 eTypeProjection;
    /* 0x3C520 */ f32 aMatrixModel[10][4][4];
    /* 0x3C7A0 */ f32 matrixProjection[4][4];
    /* 0x3C7E0 */ f32 matrixProjectionExtra[4][4];
    /* 0x3C820 */ struct __anon_0x772F8 aMatrixHint[64];
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
} __anon_0x77548; // size = 0x3D150

// Range: 0x8008EE18 -> 0x8008EE20
s32 videoPut8() {}

// Range: 0x8008EE10 -> 0x8008EE18
s32 videoPut16() {}

// Range: 0x8008EB9C -> 0x8008EE10
s32 videoPut32(struct __anon_0x75B37* pVideo, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x75B37* pVideo; // r31
    // u32 nAddress; // r1+0xC
    // s32* pData; // r1+0x10

    // Local variables
    void* pRAM; // r1+0x14
    struct __anon_0x77548* pFrame; // r30
    struct __anon_0x761FF* pBuffer; // r29
}

// Range: 0x8008EB94 -> 0x8008EB9C
s32 videoPut64() {}

// Range: 0x8008EB8C -> 0x8008EB94
s32 videoGet8() {}

// Range: 0x8008EB84 -> 0x8008EB8C
s32 videoGet16() {}

// Range: 0x8008EA68 -> 0x8008EB84
s32 videoGet32(struct __anon_0x75B37* pVideo, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x75B37* pVideo; // r30
    // u32 nAddress; // r1+0xC
    // s32* pData; // r31
}

// Range: 0x8008EA60 -> 0x8008EA68
s32 videoGet64() {}

// Erased
static s32 videoTickScan() {}

// Range: 0x8008E9F4 -> 0x8008EA60
s32 videoForceRetrace(struct __anon_0x75B37* pVideo) {
    // Parameters
    // struct __anon_0x75B37* pVideo; // r31
}

// Erased
static s32 videoGetMode(struct __anon_0x75B37* pVideo, s32* pbBlack, s32* pnSizeX, s32* pnSizeY) {
    // Parameters
    // struct __anon_0x75B37* pVideo; // r1+0x8
    // s32* pbBlack; // r1+0xC
    // s32* pnSizeX; // r1+0x10
    // s32* pnSizeY; // r1+0x14

    // Local variables
    s32 nSizeX; // r1+0x8
    s32 nSizeY; // r3
}

// Range: 0x8008E8A0 -> 0x8008E9F4
s32 videoEvent(struct __anon_0x75B37* pVideo, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x75B37* pVideo; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
