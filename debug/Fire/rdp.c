/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\rdp.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8006FEC0 -> 0x800715D0
*/

#include "types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x52A92; // size = 0x10

// size = 0x10, address = 0x800EDF40
struct _XL_OBJECTTYPE gClassRDP;

// size = 0x4, address = 0x80135770
static s32 nCount$122;

// size = 0x4, address = 0x80135774
static s32 nBlurCount$123;

// size = 0x4, address = 0x80135778
static s32 nNoteCount$124;

// size = 0x4, address = 0x8013577C
static s32 nZCount$125;

// size = 0x4, address = 0x80135780
static s32 nZBufferCount$126;

// size = 0xC, address = 0x800EDF50
static u32 sCommandCodes$168[3];

typedef struct __anon_0x52CD0 {
    /* 0x00 */ s32 nBIST;
    /* 0x04 */ s32 nStatus;
    /* 0x08 */ void* pHost;
    /* 0x0C */ s32 nModeTest;
    /* 0x10 */ s32 nDataTest;
    /* 0x14 */ s32 nAddressTest;
    /* 0x18 */ s32 nAddress0;
    /* 0x1C */ s32 nAddress1;
    /* 0x20 */ s32 nClock;
    /* 0x24 */ s32 nClockCmd;
    /* 0x28 */ s32 nClockPipe;
    /* 0x2C */ s32 nClockTMEM;
} __anon_0x52CD0; // size = 0x30

typedef enum __anon_0x533F6 {
    SM_NONE = -1,
    SM_RUNNING = 0,
    SM_STOPPED = 1,
} __anon_0x533F6;

typedef struct __anon_0x53458 {
    /* 0x0 */ s32 nSize;
    /* 0x4 */ s32 nOffsetRAM;
    /* 0x8 */ s32 nOffsetROM;
    /* 0xC */ s32 (*pCallback)();
} __anon_0x53458; // size = 0x10

typedef enum __anon_0x53509 {
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
} __anon_0x53509;

typedef enum __anon_0x53635 {
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
} __anon_0x53635;

typedef struct __anon_0x53770 {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ s32 bException;
    /* 0x0C */ enum __anon_0x533F6 eMode;
    /* 0x10 */ struct __anon_0x53458 romCopy;
    /* 0x20 */ enum __anon_0x53509 eTypeROM;
    /* 0x24 */ void* apObject[16];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ enum __anon_0x53635 storageDevice;
    /* 0x74 */ u8 anException[16];
    /* 0x84 */ s32 bJapaneseVersion;
} __anon_0x53770; // size = 0x88

// size = 0x4, address = 0x80135600
struct __anon_0x53770* gpSystem;

typedef enum __anon_0x53961 {
    VI_TVMODE_NTSC_INT = 0,
    VI_TVMODE_NTSC_DS = 1,
    VI_TVMODE_NTSC_PROG = 2,
    VI_TVMODE_PAL_INT = 4,
    VI_TVMODE_PAL_DS = 5,
    VI_TVMODE_EURGB60_INT = 20,
    VI_TVMODE_EURGB60_DS = 21,
    VI_TVMODE_MPAL_INT = 8,
    VI_TVMODE_MPAL_DS = 9,
    VI_TVMODE_DEBUG_INT = 12,
    VI_TVMODE_DEBUG_PAL_INT = 16,
    VI_TVMODE_DEBUG_PAL_DS = 17,
} __anon_0x53961;

typedef enum __anon_0x53AA8 {
    VI_XFBMODE_SF = 0,
    VI_XFBMODE_DF = 1,
} __anon_0x53AA8;

typedef struct _GXRenderModeObj {
    /* 0x00 */ enum __anon_0x53961 viTVmode;
    /* 0x04 */ u16 fbWidth;
    /* 0x06 */ u16 efbHeight;
    /* 0x08 */ u16 xfbHeight;
    /* 0x0A */ u16 viXOrigin;
    /* 0x0C */ u16 viYOrigin;
    /* 0x0E */ u16 viWidth;
    /* 0x10 */ u16 viHeight;
    /* 0x14 */ enum __anon_0x53AA8 xFBmode;
    /* 0x18 */ u8 field_rendering;
    /* 0x19 */ u8 aa;
    /* 0x1A */ u8 sample_pattern[12][2];
    /* 0x32 */ u8 vfilter[7];
} __anon_0x53B56; // size = 0x3C

// size = 0x4, address = 0x8013559C
struct _GXRenderModeObj* rmode;

typedef struct __anon_0x53DD5 {
    /* 0x0 */ f32 rX;
    /* 0x4 */ f32 rY;
    /* 0x8 */ f32 rSizeX;
    /* 0xC */ f32 rSizeY;
} __anon_0x53DD5; // size = 0x10

typedef struct __anon_0x53E6F {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nWidth;
    /* 0x08 */ s32 nFormat;
    /* 0x0C */ void* pData;
    /* 0x10 */ s32 nAddress;
} __anon_0x53E6F; // size = 0x14

typedef struct __anon_0x53FB0 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} __anon_0x53FB0; // size = 0xC

typedef struct __anon_0x54020 {
    /* 0x00 */ s32 bTransformed;
    /* 0x04 */ struct __anon_0x53FB0 rVecOrigTowards;
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
} __anon_0x54020; // size = 0x3C

typedef struct __anon_0x54250 {
    /* 0x00 */ s32 bTransformed;
    /* 0x04 */ struct __anon_0x53FB0 rS;
    /* 0x10 */ struct __anon_0x53FB0 rT;
    /* 0x1C */ struct __anon_0x53FB0 rSRaw;
    /* 0x28 */ struct __anon_0x53FB0 rTRaw;
} __anon_0x54250; // size = 0x34

typedef struct __anon_0x54339 {
    /* 0x00 */ f32 rSum;
    /* 0x04 */ f32 rS;
    /* 0x08 */ f32 rT;
    /* 0x0C */ struct __anon_0x53FB0 vec;
    /* 0x18 */ u8 anColor[4];
} __anon_0x54339; // size = 0x1C

typedef union __anon_0x54498 {
    /* 0x0 */ u8 u8[4096];
    /* 0x0 */ u16 u16[2048];
    /* 0x0 */ u32 u32[1024];
    /* 0x0 */ u64 u64[512];
} __anon_0x54498;

typedef struct __anon_0x54535 {
    /* 0x0 */ union __anon_0x54498 data;
} __anon_0x54535; // size = 0x1000

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
} __anon_0x545CE;

typedef struct _GXTlutObj {
    /* 0x0 */ u32 dummy[3];
} __anon_0x54790; // size = 0xC

typedef struct _GXTexObj {
    /* 0x0 */ u32 dummy[8];
} __anon_0x547F7; // size = 0x20

typedef enum _GXTexWrapMode {
    GX_CLAMP = 0,
    GX_REPEAT = 1,
    GX_MIRROR = 2,
    GX_MAX_TEXWRAPMODE = 3,
} __anon_0x5483D;

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
} __anon_0x548A6; // size = 0x6C

typedef struct __anon_0x54C03 {
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
} __anon_0x54C03; // size = 0x2C

typedef enum __anon_0x54EE5 {
    FMP_NONE = -1,
    FMP_PERSPECTIVE = 0,
    FMP_ORTHOGRAPHIC = 1,
} __anon_0x54EE5;

typedef struct __anon_0x54F66 {
    /* 0x00 */ s32 nCount;
    /* 0x04 */ f32 rScale;
    /* 0x08 */ f32 rAspect;
    /* 0x0C */ f32 rFieldOfViewY;
    /* 0x10 */ f32 rClipNear;
    /* 0x14 */ f32 rClipFar;
    /* 0x18 */ u32 nAddressFloat;
    /* 0x1C */ u32 nAddressFixed;
    /* 0x20 */ enum __anon_0x54EE5 eProjection;
} __anon_0x54F66; // size = 0x24

typedef struct _GXColor {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} __anon_0x550FB; // size = 0x4

typedef struct __anon_0x551B6 {
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
    /* 0x000B8 */ struct __anon_0x53DD5 viewport;
    /* 0x000C8 */ struct __anon_0x53E6F aBuffer[4];
    /* 0x00118 */ u32 nOffsetDepth0;
    /* 0x0011C */ u32 nOffsetDepth1;
    /* 0x00120 */ s32 nWidthLine;
    /* 0x00124 */ f32 rDepth;
    /* 0x00128 */ f32 rDelta;
    /* 0x0012C */ s32 (*aDraw[4])(void*, void*);
    /* 0x0013C */ s32 nCountLight;
    /* 0x00140 */ struct __anon_0x54020 aLight[8];
    /* 0x00320 */ struct __anon_0x54250 lookAt;
    /* 0x00354 */ s32 nCountVertex;
    /* 0x00358 */ struct __anon_0x54339 aVertex[80];
    /* 0x00C18 */ struct __anon_0x54535 TMEM;
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
    /* 0x3C358 */ struct __anon_0x54C03 aTile[8];
    /* 0x3C4B8 */ s32 anSizeX[2];
    /* 0x3C4C0 */ s32 anSizeY[2];
    /* 0x3C4C8 */ s32 iHintMatrix;
    /* 0x3C4CC */ s32 iMatrixModel;
    /* 0x3C4D0 */ s32 iHintProjection;
    /* 0x3C4D4 */ f32 matrixView[4][4];
    /* 0x3C514 */ s32 iHintLast;
    /* 0x3C518 */ s32 iHintHack;
    /* 0x3C51C */ enum __anon_0x54EE5 eTypeProjection;
    /* 0x3C520 */ f32 aMatrixModel[10][4][4];
    /* 0x3C7A0 */ f32 matrixProjection[4][4];
    /* 0x3C7E0 */ f32 matrixProjectionExtra[4][4];
    /* 0x3C820 */ struct __anon_0x54F66 aMatrixHint[64];
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
} __anon_0x551B6; // size = 0x3D150

typedef struct __anon_0x56000 {
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
} __anon_0x56000; // size = 0x28

// Range: 0x80070340 -> 0x800715D0
s32 rdpParseGBI(struct __anon_0x52CD0* pRDP, u64** ppnGBI) {
    // Parameters
    // struct __anon_0x52CD0* pRDP; // r25
    // u64** ppnGBI; // r26

    // Local variables
    u32 nA; // r4
    u32 nB; // r3
    u32 nC; // r5
    u32 nD; // r6
    u64* pnGBI; // r1+0x9C
    u32 nCommandLo; // r1+0x98
    u32 nCommandHi; // r1+0x94
    struct __anon_0x551B6* pFrame; // r30
    s32 nFound; // r31
    s32 i; // r5
    u32 nAddress; // r29
    s32 nSetLens; // r28
    struct __anon_0x53E6F* pBuffer; // r27
    s32 i; // r7
    u32* pGBI; // r1+0x8
    s32 nAddress; // r5
    struct __anon_0x53E6F* pBuffer; // r8
    s32 nAddress; // r5
    struct __anon_0x53E6F* pBuffer; // r27
    u32 nColor; // r5
    struct __anon_0x56000 primitive; // r1+0x6C
    s32 iTile; // r1+0x8
    struct __anon_0x54C03* pTile; // r5
    s32 iTile; // r6
    s32 iTile; // r5
    struct __anon_0x54C03* pTile; // r5
    s32 iTile; // r5
    s32 nCount; // r4
    f32 rDepth; // f1
    f32 rDelta; // f2
    struct __anon_0x56000 rectangle; // r1+0x40
    struct __anon_0x56000 primitive; // r1+0x14
    f32 rX0; // f31
    f32 rY0; // f30
    f32 rX1; // f29
    f32 rY1; // f28
    u32* pGBI; // r1+0x8
    u32* pGBI; // r4

    // References
    // -> struct __anon_0x53770* gpSystem;
    // -> struct _GXRenderModeObj* rmode;
    // -> static s32 nCount$122;
    // -> static s32 nBlurCount$123;
    // -> static s32 nNoteCount$124;
    // -> static s32 nZCount$125;
    // -> static u32 sCommandCodes$168[3];
    // -> static s32 nZBufferCount$126;
}

// Range: 0x80070338 -> 0x80070340
static s32 rdpPut8() {}

// Range: 0x80070330 -> 0x80070338
static s32 rdpPut16() {}

// Range: 0x8007022C -> 0x80070330
static s32 rdpPut32(struct __anon_0x52CD0* pRDP, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x52CD0* pRDP; // r3
    // u32 nAddress; // r1+0xC
    // s32* pData; // r1+0x10

    // Local variables
    s32 nData; // r4
}

// Range: 0x80070224 -> 0x8007022C
static s32 rdpPut64() {}

// Range: 0x8007021C -> 0x80070224
static s32 rdpGet8() {}

// Range: 0x80070214 -> 0x8007021C
static s32 rdpGet16() {}

// Range: 0x80070170 -> 0x80070214
static s32 rdpGet32(struct __anon_0x52CD0* pRDP, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x52CD0* pRDP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s32* pData; // r1+0x8
}

// Range: 0x80070168 -> 0x80070170
static s32 rdpGet64() {}

// Range: 0x80070160 -> 0x80070168
static s32 rdpPutSpan8() {}

// Range: 0x80070158 -> 0x80070160
static s32 rdpPutSpan16() {}

// Range: 0x800700F4 -> 0x80070158
static s32 rdpPutSpan32(struct __anon_0x52CD0* pRDP, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x52CD0* pRDP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s32* pData; // r1+0x8
}

// Range: 0x800700EC -> 0x800700F4
static s32 rdpPutSpan64() {}

// Range: 0x800700E4 -> 0x800700EC
static s32 rdpGetSpan8() {}

// Range: 0x800700DC -> 0x800700E4
static s32 rdpGetSpan16() {}

// Range: 0x8007006C -> 0x800700DC
static s32 rdpGetSpan32(struct __anon_0x52CD0* pRDP, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x52CD0* pRDP; // r1+0x0
    // u32 nAddress; // r1+0x4
    // s32* pData; // r1+0x8
}

// Range: 0x80070064 -> 0x8007006C
static s32 rdpGetSpan64() {}

// Range: 0x8006FEC0 -> 0x80070064
s32 rdpEvent(struct __anon_0x52CD0* pRDP, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x52CD0* pRDP; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r31
}
