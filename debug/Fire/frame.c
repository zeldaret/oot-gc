/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\frame.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8001D34C -> 0x80021204
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x22648; // size = 0x10

// size = 0x10, address = 0x800EA848
struct _XL_OBJECTTYPE gClassFrame;

// size = 0x4, address = 0x80135688
static s32 gbFrameValid;

// size = 0x4, address = 0x8013568C
static s32 gbFrameBegin;

// size = 0x4, address = 0x80135690
static s32 snScissorChanged;

// size = 0x4, address = 0x80135694
static u32 snScissorXOrig;

// size = 0x4, address = 0x80135698
static u32 snScissorYOrig;

// size = 0x4, address = 0x8013569C
static u32 snScissorWidth;

// size = 0x4, address = 0x801356A0
static u32 snScissorHeight;

// size = 0x4, address = 0x801356A4
static s32 sCopyFrameSyncReceived;

// size = 0x1, address = 0x801356A8
static u8 sSpecialZeldaHackON;

// size = 0x4, address = 0x801356AC
static u32 sDestinationBuffer;

// size = 0x4, address = 0x801356B0
static u32 sSrcBuffer;

// size = 0x18, address = 0x801085A0
static u32 sConstantBufAddr[6];

// size = 0x4, address = 0x801356B4
static u32 sNumAddr;

// size = 0x4, address = 0x801356B8
static u32 gHackCreditsColor;

// size = 0x4, address = 0x801356BC
s32 gNoSwapBuffer;

// size = 0x20, address = 0x800EA858
u32 ganNameColor[8];

// size = 0x8, address = 0x80134DD8
static u8 sRemapI$746[8];

typedef enum _GXTexMapID {
    GX_TEXMAP0 = 0,
    GX_TEXMAP1 = 1,
    GX_TEXMAP2 = 2,
    GX_TEXMAP3 = 3,
    GX_TEXMAP4 = 4,
    GX_TEXMAP5 = 5,
    GX_TEXMAP6 = 6,
    GX_TEXMAP7 = 7,
    GX_MAX_TEXMAP = 8,
    GX_TEXMAP_NULL = 255,
    GX_TEX_DISABLE = 256,
} __anon_0x22A94;

// size = 0x20, address = 0x800EA878
enum _GXTexMapID ganNamePixel[8];

// size = 0x20, address = 0x800EA898
u32 ganNameTexMtx[8];

typedef enum _GXTexCoordID {
    GX_TEXCOORD0 = 0,
    GX_TEXCOORD1 = 1,
    GX_TEXCOORD2 = 2,
    GX_TEXCOORD3 = 3,
    GX_TEXCOORD4 = 4,
    GX_TEXCOORD5 = 5,
    GX_TEXCOORD6 = 6,
    GX_TEXCOORD7 = 7,
    GX_MAX_TEXCOORD = 8,
    GX_TEXCOORD_NULL = 255,
} __anon_0x22C01;

// size = 0x20, address = 0x800EA8B8
enum _GXTexCoordID ganNameTexCoord[8];

// size = 0x50, address = 0x800EA920
static char* gaszNameColor[20];

// size = 0x24, address = 0x800EA970
static char* gaszNameAlpha[9];

// size = 0x20, address = 0x800EA994
static s32 (*gapfDrawTriangle[8])(void*, void*);

// size = 0x18, address = 0x800EA9B4
static s32 (*gapfDrawLine[6])(void*, void*);

// size = 0x4, address = 0x801356C0
static s32 gnCountMapHack;

// size = 0x4, address = 0x801356C4
static s32 nCounter$1367;

// size = 0x4, address = 0x801356C8
static s32 bSkip$1410;

// size = 0x25800, address = 0x801085C0
static u16 sTempZBuf[4800][4][4];

// size = 0x40, address = 0x800EA9CC
static u32 sZBufShift[8][2];

// size = 0x14, address = 0x800EAA24
static char* gaszNameColorType[5];

typedef struct _GXTexObj {
    /* 0x0 */ u32 dummy[8];
} __anon_0x2311A; // size = 0x20

// size = 0x20, address = 0x8012DDC0
static struct _GXTexObj sFrameObj1$1562;

// size = 0x20, address = 0x8012DDE0
static struct _GXTexObj sFrameObj2$1563;

// size = 0x20, address = 0x8012DE00
static struct _GXTexObj sFrameObj$1564;

// size = 0x20, address = 0x8012DE20
static struct _GXTexObj sFrameObj$1565;

// size = 0x20, address = 0x8012DE40
static struct _GXTexObj sFrameObj$1568;

// size = 0x1400, address = 0x8012DE60
static u32 line$1582[80][4][4];

// size = 0xA00, address = 0x8012F260
static u16 line$1606[80][4][4];

// size = 0xA00, address = 0x8012FC60
static u16 line$1630[80][4][4];

// size = 0x20, address = 0x80130660
static struct _GXTexObj sFrameObj$1647;

// size = 0x1, address = 0x80134E56
static u8 cAlpha$1648;

// size = 0x20, address = 0x80130680
static struct _GXTexObj sFrameObj$1660;

// size = 0x20, address = 0x801306A0
static struct _GXTexObj frameObj$1663;

// size = 0x20, address = 0x801306C0
static struct _GXTexObj frameObj$1673;

// size = 0x20, address = 0x800EAA38
static u32 sCommandCodes$1679[8];

// size = 0x4, address = 0x801356CC
static s32 nLastFrame$1695;

// size = 0x4, address = 0x801356D0
static s32 nCopyFrame$1697;

// size = 0x28, address = 0x800EAA58
static u32 sCommandCodes$1702[10];

// size = 0x28, address = 0x800EAA80
static u32 sCommandCodes2$1722[10];

// size = 0x200, address = 0x801306E0
static u16 tempLine$1785[16][4][4];

// size = 0xC, address = 0x800EAAA8
static u32 GBIcode$1816[3];

// size = 0x1C, address = 0x800EAAB4
static u32 GBIcode2D2$1906[7];

// size = 0x14, address = 0x800EAAD0
static u32 GBIcode3D1$1907[5];

// size = 0x18, address = 0x800EAAE4
static u32 GBIcode3D2$1908[6];

// size = 0x190, address = 0x800EAAFC
u32 anRenderModeDatabaseCycle2[100];

// size = 0x190, address = 0x800EAC8C
u32 anRenderModeDatabaseCopy[100];

// size = 0x190, address = 0x800EAE1C
u32 anRenderModeDatabaseFill[100];

// size = 0x190, address = 0x800EAFAC
u32 anRenderModeDatabaseCycle1[100];

typedef struct __anon_0x239BA {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} __anon_0x239BA; // size = 0xC

typedef struct __anon_0x23B04 {
    /* 0x0 */ f32 rX;
    /* 0x4 */ f32 rY;
    /* 0x8 */ f32 rSizeX;
    /* 0xC */ f32 rSizeY;
} __anon_0x23B04; // size = 0x10

typedef struct __anon_0x23B9E {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nWidth;
    /* 0x08 */ s32 nFormat;
    /* 0x0C */ void* pData;
    /* 0x10 */ s32 nAddress;
} __anon_0x23B9E; // size = 0x14

typedef struct __anon_0x23CAB {
    /* 0x00 */ s32 bTransformed;
    /* 0x04 */ struct __anon_0x274AD rVecOrigTowards;
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
} __anon_0x23CAB; // size = 0x3C

typedef struct __anon_0x23EDB {
    /* 0x00 */ s32 bTransformed;
    /* 0x04 */ struct __anon_0x274AD rS;
    /* 0x10 */ struct __anon_0x274AD rT;
    /* 0x1C */ struct __anon_0x274AD rSRaw;
    /* 0x28 */ struct __anon_0x274AD rTRaw;
} __anon_0x23EDB; // size = 0x34

typedef struct __anon_0x23FC4 {
    /* 0x00 */ f32 rSum;
    /* 0x04 */ f32 rS;
    /* 0x08 */ f32 rT;
    /* 0x0C */ struct __anon_0x274AD vec;
    /* 0x18 */ u8 anColor[4];
} __anon_0x23FC4; // size = 0x1C

typedef union __anon_0x24123 {
    /* 0x0 */ u8 u8[4096];
    /* 0x0 */ u16 u16[2048];
    /* 0x0 */ u32 u32[1024];
    /* 0x0 */ u64 u64[512];
} __anon_0x24123;

typedef struct __anon_0x241C0 {
    /* 0x0 */ union __anon_0x24123 data;
} __anon_0x241C0; // size = 0x1000

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
} __anon_0x24259;

typedef struct _GXTlutObj {
    /* 0x0 */ u32 dummy[3];
} __anon_0x2441B; // size = 0xC

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
} __anon_0x24462; // size = 0x6C

typedef struct __anon_0x247BF {
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
} __anon_0x247BF; // size = 0x2C

typedef struct __anon_0x24A81 {
    /* 0x00 */ s32 nCount;
    /* 0x04 */ f32 rScale;
    /* 0x08 */ f32 rAspect;
    /* 0x0C */ f32 rFieldOfViewY;
    /* 0x10 */ f32 rClipNear;
    /* 0x14 */ f32 rClipFar;
    /* 0x18 */ u32 nAddressFloat;
    /* 0x1C */ u32 nAddressFixed;
    /* 0x20 */ enum __anon_0x25D5E eProjection;
} __anon_0x24A81; // size = 0x24

typedef struct __anon_0x24C38 {
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
    /* 0x000B8 */ struct __anon_0x23B04 viewport;
    /* 0x000C8 */ struct __anon_0x23B9E aBuffer[4];
    /* 0x00118 */ u32 nOffsetDepth0;
    /* 0x0011C */ u32 nOffsetDepth1;
    /* 0x00120 */ s32 nWidthLine;
    /* 0x00124 */ f32 rDepth;
    /* 0x00128 */ f32 rDelta;
    /* 0x0012C */ s32 (*aDraw[4])(void*, void*);
    /* 0x0013C */ s32 nCountLight;
    /* 0x00140 */ struct __anon_0x23CAB aLight[8];
    /* 0x00320 */ struct __anon_0x23EDB lookAt;
    /* 0x00354 */ s32 nCountVertex;
    /* 0x00358 */ struct __anon_0x23FC4 aVertex[80];
    /* 0x00C18 */ struct __anon_0x241C0 TMEM;
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
    /* 0x3C358 */ struct __anon_0x247BF aTile[8];
    /* 0x3C4B8 */ s32 anSizeX[2];
    /* 0x3C4C0 */ s32 anSizeY[2];
    /* 0x3C4C8 */ s32 iHintMatrix;
    /* 0x3C4CC */ s32 iMatrixModel;
    /* 0x3C4D0 */ s32 iHintProjection;
    /* 0x3C4D4 */ f32 matrixView[4][4];
    /* 0x3C514 */ s32 iHintLast;
    /* 0x3C518 */ s32 iHintHack;
    /* 0x3C51C */ enum __anon_0x25D5E eTypeProjection;
    /* 0x3C520 */ f32 aMatrixModel[10][4][4];
    /* 0x3C7A0 */ f32 matrixProjection[4][4];
    /* 0x3C7E0 */ f32 matrixProjectionExtra[4][4];
    /* 0x3C820 */ struct __anon_0x24A81 aMatrixHint[64];
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
} __anon_0x24C38; // size = 0x3D150

typedef struct __anon_0x25A82 {
    /* 0x0 */ s32 nSizeTextures;
    /* 0x4 */ s32 nCountTextures;
} __anon_0x25A82; // size = 0x8

typedef enum __anon_0x25D5E {
    FMP_NONE = -1,
    FMP_PERSPECTIVE = 0,
    FMP_ORTHOGRAPHIC = 1,
} __anon_0x25D5E;

typedef enum __anon_0x2614E {
    FBT_NONE = -1,
    FBT_DEPTH = 0,
    FBT_IMAGE = 1,
    FBT_COLOR_SHOW = 2,
    FBT_COLOR_DRAW = 3,
    FBT_COUNT = 4,
} __anon_0x2614E;

typedef enum __anon_0x2625D {
    FRT_NONE = -1,
    FRT_COLD = 0,
    FRT_WARM = 1,
} __anon_0x2625D;

typedef enum __anon_0x266CE {
    SM_NONE = -1,
    SM_RUNNING = 0,
    SM_STOPPED = 1,
} __anon_0x266CE;

typedef struct __anon_0x26732 {
    /* 0x0 */ s32 nSize;
    /* 0x4 */ s32 nOffsetRAM;
    /* 0x8 */ s32 nOffsetROM;
    /* 0xC */ s32 (*pCallback)();
} __anon_0x26732; // size = 0x10

typedef enum __anon_0x267E3 {
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
} __anon_0x267E3;

typedef enum __anon_0x26911 {
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
} __anon_0x26911;

typedef struct __anon_0x26A4E {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ s32 bException;
    /* 0x0C */ enum __anon_0x266CE eMode;
    /* 0x10 */ struct __anon_0x26732 romCopy;
    /* 0x20 */ enum __anon_0x267E3 eTypeROM;
    /* 0x24 */ void* apObject[16];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ enum __anon_0x26911 storageDevice;
    /* 0x74 */ u8 anException[16];
    /* 0x84 */ s32 bJapaneseVersion;
} __anon_0x26A4E; // size = 0x88

// size = 0x4, address = 0x80135600
struct __anon_0x26A4E* gpSystem;

typedef enum __anon_0x26C3F {
    FLT_NONE = -1,
    FLT_TILE = 0,
    FLT_BLOCK = 1,
} __anon_0x26C3F;

// size = 0x0, address = 0x800F3E78
s32 __float_nan[];

// size = 0x0, address = 0x800F3E7C
s32 __float_huge[];

typedef struct __anon_0x274AD {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} __anon_0x274AD; // size = 0xC

typedef enum __anon_0x27B8C {
    FMT_MODELVIEW = 0,
    FMT_PROJECTION = 1,
} __anon_0x27B8C;

typedef enum __anon_0x27E96 {
    FMT_NONE = -1,
    FMT_FOG = 0,
    FMT_GEOMETRY = 1,
    FMT_TEXTURE1 = 2,
    FMT_TEXTURE2 = 3,
    FMT_OTHER0 = 4,
    FMT_OTHER1 = 5,
    FMT_COMBINE_COLOR1 = 6,
    FMT_COMBINE_COLOR2 = 7,
    FMT_COMBINE_ALPHA1 = 8,
    FMT_COMBINE_ALPHA2 = 9,
    FMT_COUNT = 10,
} __anon_0x27E96;

typedef enum __anon_0x2813A {
    FS_NONE = -1,
    FS_SOURCE = 0,
    FS_TARGET = 1,
    FS_COUNT = 2,
} __anon_0x2813A;

typedef struct __anon_0x285E5 {
    /* 0x0 */ s32 shift;
    /* 0x4 */ s32 add;
} __anon_0x285E5; // size = 0x8

typedef struct __anon_0x2865F {
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
} __anon_0x2865F; // size = 0x30

typedef struct __anon_0x28835 {
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
} __anon_0x28835; // size = 0x40

typedef enum __anon_0x28AC5 {
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
} __anon_0x28AC5;

typedef struct __anon_0x28C10 {
    /* 0x00 */ s32 iDL;
    /* 0x04 */ s32 bValid;
    /* 0x08 */ struct __anon_0x28835 task;
    /* 0x48 */ s32 nCountVertex;
    /* 0x4C */ enum __anon_0x28AC5 eTypeUCode;
    /* 0x50 */ u32 n2TriMult;
    /* 0x54 */ u32 nVersionUCode;
    /* 0x58 */ s32 anBaseSegment[16];
    /* 0x98 */ u64* apDL[16];
} __anon_0x28C10; // size = 0xD8

typedef struct __anon_0x28E31 {
    /* 0x00 */ f32 aRotations[2][2];
    /* 0x10 */ f32 fX;
    /* 0x14 */ f32 fY;
    /* 0x18 */ f32 fBaseScaleX;
    /* 0x1C */ f32 fBaseScaleY;
} __anon_0x28E31; // size = 0x20

typedef struct __anon_0x28F3E {
    /* 0x0 */ f32 rS;
    /* 0x4 */ f32 rT;
    /* 0x8 */ s16 nX;
    /* 0xA */ s16 nY;
    /* 0xC */ s16 nZ;
    /* 0xE */ u8 anData[4];
} __anon_0x28F3E; // size = 0x14

typedef struct __anon_0x29056 {
    /* 0x0 */ char anNormal[3];
} __anon_0x29056; // size = 0x3

typedef struct __anon_0x290D5 {
    /* 0x0 */ u8 anMaterial[4];
} __anon_0x290D5; // size = 0x4

typedef struct __anon_0x29178 {
    /* 0x0 */ f32 aMatrix[4][4];
} __anon_0x29178; // size = 0x40

typedef struct __anon_0x291D6 {
    /* 0x0 */ u8 nRed;
    /* 0x1 */ u8 nGreen;
    /* 0x2 */ u8 nBlue;
    /* 0x3 */ char rVectorX;
    /* 0x4 */ char rVectorY;
    /* 0x5 */ char rVectorZ;
} __anon_0x291D6; // size = 0x6

typedef struct __anon_0x29487 {
    /* 0x0 */ s16 anSlice[8];
} __anon_0x29487; // size = 0x10

typedef enum __anon_0x29567 {
    RUT_NOCODE = -1,
    RUT_ABI1 = 0,
    RUT_ABI2 = 1,
    RUT_ABI3 = 2,
    RUT_ABI4 = 3,
    RUT_UNKNOWN = 4,
} __anon_0x29567;

typedef struct tXL_LIST {
    /* 0x0 */ s32 nItemSize;
    /* 0x4 */ s32 nItemCount;
    /* 0x8 */ void* pNodeHead;
    /* 0xC */ void* pNodeNext;
} __anon_0x295E5; // size = 0x10

typedef struct __anon_0x296E2 {
    /* 0x0 */ s16 r;
    /* 0x2 */ s16 g;
    /* 0x4 */ s16 b;
    /* 0x6 */ s16 a;
} __anon_0x296E2; // size = 0x8

typedef struct __anon_0x29770 {
    /* 0x0 */ s16 y;
    /* 0x2 */ s16 u;
    /* 0x4 */ s16 v;
} __anon_0x29770; // size = 0x6

typedef struct __anon_0x297E0 {
    /* 0x0000 */ s32 nMode;
    /* 0x0004 */ struct __anon_0x28C10 yield;
    /* 0x00DC */ u32 nTickLast;
    /* 0x00E0 */ s32 (*pfUpdateWaiting)();
    /* 0x00E4 */ u32 n2TriMult;
    /* 0x00E8 */ s32 aStatus[4];
    /* 0x00F8 */ f32 aMatrixOrtho[4][4];
    /* 0x0138 */ u32 nMode2D;
    /* 0x013C */ struct __anon_0x28E31 twoDValues;
    /* 0x015C */ s32 nPass;
    /* 0x0160 */ u32 nZSortSubDL;
    /* 0x0164 */ u32 nStatusSubDL;
    /* 0x0168 */ u32 nNumZSortLights;
    /* 0x016C */ s32 aLightAddresses[8];
    /* 0x018C */ s32 nAmbientLightAddress;
    /* 0x0190 */ struct __anon_0x28F3E aZSortVertex[128];
    /* 0x0B90 */ struct __anon_0x29056 aZSortNormal[128];
    /* 0x0D10 */ struct __anon_0x290D5 aZSortMaterial[128];
    /* 0x0F10 */ struct __anon_0x29178 aZSortMatrix[128];
    /* 0x2F10 */ struct __anon_0x291D6 aZSortLight[8];
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
    /* 0x3380 */ struct __anon_0x29487 vParams;
    /* 0x3390 */ s16 stepF;
    /* 0x3392 */ s16 stepL;
    /* 0x3394 */ s16 stepR;
    /* 0x3398 */ s32 anGenReg[32];
    /* 0x3418 */ struct __anon_0x29487 aVectorReg[32];
    /* 0x3618 */ s32 anCP0Reg[32];
    /* 0x3698 */ struct __anon_0x29487 anCP2Reg[32];
    /* 0x3898 */ s16 anAcc[24];
    /* 0x38C8 */ s16 nVCC;
    /* 0x38CA */ s16 nVC0;
    /* 0x38CC */ char nVCE;
    /* 0x38D0 */ enum __anon_0x29567 eTypeAudioUCode;
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
    /* 0x3920 */ enum __anon_0x28AC5 eTypeUCode;
    /* 0x3924 */ u32 nVersionUCode;
    /* 0x3928 */ s32 anBaseSegment[16];
    /* 0x3968 */ u64* apDL[16];
    /* 0x39A8 */ s32* Coeff;
    /* 0x39AC */ s16* QTable;
    /* 0x39B0 */ s16* QYTable;
    /* 0x39B4 */ s16* QCbTable;
    /* 0x39B8 */ s16* QCrTable;
    /* 0x39BC */ s32* Zigzag;
    /* 0x39C0 */ struct __anon_0x296E2* rgbaBuf;
    /* 0x39C4 */ struct __anon_0x29770* yuvBuf;
    /* 0x39C8 */ s32* dctBuf;
} __anon_0x297E0; // size = 0x39CC

typedef struct __anon_0x2A6F7 {
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
} __anon_0x2A6F7; // size = 0x28

typedef struct __anon_0x2AA02 {
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
} __anon_0x2AA02; // size = 0x28

typedef union __anon_0x2ACA3 {
    /* 0x0 */ struct __anon_0x2A6F7 b;
    /* 0x0 */ struct __anon_0x2AA02 s;
    /* 0x0 */ s64 force_structure_alignment;
} __anon_0x2ACA3;

typedef struct __anon_0x2AD2F {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 image;
    /* 0x08 */ u16 tmem;
    /* 0x0A */ u16 tsize;
    /* 0x0C */ u16 tline;
    /* 0x0E */ u16 sid;
    /* 0x10 */ u32 flag;
    /* 0x14 */ u32 mask;
} __anon_0x2AD2F; // size = 0x18

typedef struct __anon_0x2AE4F {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 image;
    /* 0x08 */ u16 tmem;
    /* 0x0A */ u16 twidth;
    /* 0x0C */ u16 theight;
    /* 0x0E */ u16 sid;
    /* 0x10 */ u32 flag;
    /* 0x14 */ u32 mask;
} __anon_0x2AE4F; // size = 0x18

typedef struct __anon_0x2AF72 {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 image;
    /* 0x08 */ u16 phead;
    /* 0x0A */ u16 pnum;
    /* 0x0C */ u16 zero;
    /* 0x0E */ u16 sid;
    /* 0x10 */ u32 flag;
    /* 0x14 */ u32 mask;
} __anon_0x2AF72; // size = 0x18

typedef union __anon_0x2B091 {
    /* 0x0 */ struct __anon_0x2AD2F block;
    /* 0x0 */ struct __anon_0x2AE4F tile;
    /* 0x0 */ struct __anon_0x2AF72 tlut;
    /* 0x0 */ s64 force_structure_alignment;
} __anon_0x2B091;

typedef struct _GXColor {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} __anon_0x2B189; // size = 0x4

// size = 0x4, address = 0x80135A8C
void* DemoCurrentBuffer;

// size = 0x4, address = 0x80135A94
void* DemoFrameBuffer1;

// size = 0x4, address = 0x80135A90
void* DemoFrameBuffer2;

typedef struct __anon_0x2B2A7 {
    /* 0x0 */ s32 nOffsetHost;
    /* 0x4 */ s32 nAddressN64;
} __anon_0x2B2A7; // size = 0x8

typedef struct cpu_callerID {
    /* 0x0 */ s32 N64address;
    /* 0x4 */ s32 GCNaddress;
} __anon_0x2B30D; // size = 0x8

typedef struct cpu_function {
    /* 0x00 */ void* pnBase;
    /* 0x04 */ void* pfCode;
    /* 0x08 */ s32 nCountJump;
    /* 0x0C */ struct __anon_0x2B2A7* aJump;
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
} __anon_0x2B380; // size = 0x48

typedef union __anon_0x2B65C {
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
} __anon_0x2B65C;

typedef union __anon_0x2BA70 {
    /* 0x0 */ f32 _0f32;
    /* 0x4 */ f32 f32;
    /* 0x0 */ f64 f64;
    /* 0x0 */ s32 _0s32;
    /* 0x4 */ s32 s32;
    /* 0x0 */ s64 s64;
    /* 0x0 */ u32 _0u32;
    /* 0x4 */ u32 u32;
    /* 0x0 */ u64 u64;
} __anon_0x2BA70;

typedef struct __anon_0x2BF7E {
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
} __anon_0x2BF7E; // size = 0x34

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
} __anon_0x2C24C; // size = 0x84

typedef struct _CPU_ADDRESS {
    /* 0x0 */ s32 nN64;
    /* 0x4 */ s32 nHost;
    /* 0x8 */ struct cpu_function* pFunction;
} __anon_0x2C48D; // size = 0xC

typedef struct __anon_0x2C542 {
    /* 0x0 */ u32 nAddress;
    /* 0x4 */ u32 nOpcodeOld;
    /* 0x8 */ u32 nOpcodeNew;
} __anon_0x2C542; // size = 0xC

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
} __anon_0x2C66D; // size = 0x2C8

typedef struct OSAlarm {
    /* 0x00 */ void (*handler)(struct OSAlarm*, struct OSContext*);
    /* 0x04 */ u32 tag;
    /* 0x08 */ s64 fire;
    /* 0x10 */ struct OSAlarm* prev;
    /* 0x14 */ struct OSAlarm* next;
    /* 0x18 */ s64 period;
    /* 0x20 */ s64 start;
} __anon_0x2C8C4; // size = 0x28

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
} __anon_0x2C9DF; // size = 0x28

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
    /* 0x00040 */ union __anon_0x2B65C aGPR[32];
    /* 0x00140 */ union __anon_0x2BA70 aFPR[32];
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
    /* 0x00B64 */ struct __anon_0x2BF7E* apDevice[256];
    /* 0x00F64 */ u8 aiDevice[65536];
    /* 0x10F64 */ void* gHeap1;
    /* 0x10F68 */ void* gHeap2;
    /* 0x10F6C */ u32 aHeap1Flag[192];
    /* 0x1126C */ u32 aHeap2Flag[13];
    /* 0x112A0 */ struct cpu_treeRoot* gTree;
    /* 0x112A4 */ struct _CPU_ADDRESS aAddressCache[256];
    /* 0x11EA4 */ s32 nCountCodeHack;
    /* 0x11EA8 */ struct __anon_0x2C542 aCodeHack[32];
    /* 0x12028 */ s64 nTimeRetrace;
    /* 0x12030 */ struct OSAlarm alarmRetrace;
    /* 0x12058 */ u32 nFlagRAM;
    /* 0x1205C */ u32 nFlagCODE;
    /* 0x12060 */ u32 nCompileFlag;
    /* 0x12064 */ struct cpu_optimize nOptimize;
} __anon_0x2CB8C; // size = 0x12090

typedef enum __anon_0x2D223 {
    FCT_NONE = -1,
    FCT_FOG = 0,
    FCT_FILL = 1,
    FCT_BLEND = 2,
    FCT_PRIMITIVE = 3,
    FCT_ENVIRONMENT = 4,
    FCT_COUNT = 5,
} __anon_0x2D223;

typedef struct __anon_0x2D2B6 {
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
} __anon_0x2D2B6; // size = 0x28

typedef struct __anon_0x2D45B {
    /* 0x0 */ s32 nCount;
    /* 0x4 */ u8 anData[768];
} __anon_0x2D45B; // size = 0x304

typedef enum _GXTevAlphaArg {
    GX_CA_APREV = 0,
    GX_CA_A0 = 1,
    GX_CA_A1 = 2,
    GX_CA_A2 = 3,
    GX_CA_TEXA = 4,
    GX_CA_RASA = 5,
    GX_CA_KONST = 6,
    GX_CA_ZERO = 7,
    GX_CA_ONE = 6,
} __anon_0x2D4FB;

typedef enum _GXTevColorArg {
    GX_CC_CPREV = 0,
    GX_CC_APREV = 1,
    GX_CC_C0 = 2,
    GX_CC_A0 = 3,
    GX_CC_C1 = 4,
    GX_CC_A1 = 5,
    GX_CC_C2 = 6,
    GX_CC_A2 = 7,
    GX_CC_TEXC = 8,
    GX_CC_TEXA = 9,
    GX_CC_RASC = 10,
    GX_CC_RASA = 11,
    GX_CC_ONE = 12,
    GX_CC_HALF = 13,
    GX_CC_KONST = 14,
    GX_CC_ZERO = 15,
    GX_CC_TEXRRR = 16,
    GX_CC_TEXGGG = 17,
    GX_CC_TEXBBB = 18,
    GX_CC_QUARTER = 14,
} __anon_0x2D5A6;

typedef enum _GXProjectionType {
    GX_PERSPECTIVE = 0,
    GX_ORTHOGRAPHIC = 1,
} __anon_0x2D741;

typedef enum _GXTexWrapMode {
    GX_CLAMP = 0,
    GX_REPEAT = 1,
    GX_MIRROR = 2,
    GX_MAX_TEXWRAPMODE = 3,
} __anon_0x2D794;

typedef struct _GXFogAdjTable {
    /* 0x0 */ u16 r[10];
} __anon_0x2D85D; // size = 0x14

typedef enum _GXFogType {
    GX_FOG_NONE = 0,
    GX_FOG_PERSP_LIN = 2,
    GX_FOG_PERSP_EXP = 4,
    GX_FOG_PERSP_EXP2 = 5,
    GX_FOG_PERSP_REVEXP = 6,
    GX_FOG_PERSP_REVEXP2 = 7,
    GX_FOG_ORTHO_LIN = 10,
    GX_FOG_ORTHO_EXP = 12,
    GX_FOG_ORTHO_EXP2 = 13,
    GX_FOG_ORTHO_REVEXP = 14,
    GX_FOG_ORTHO_REVEXP2 = 15,
    GX_FOG_LIN = 2,
    GX_FOG_EXP = 4,
    GX_FOG_EXP2 = 5,
    GX_FOG_REVEXP = 6,
    GX_FOG_REVEXP2 = 7,
} __anon_0x2D8A4;

// Erased
static s32 frameVectorTimesMatrix(f32* fOutVector, f32* fInVector, f32 (*matrix)[4]) {
    // Parameters
    // f32* fOutVector; // r1+0x4
    // f32* fInVector; // r1+0x8
    // f32 (* matrix)[4]; // r1+0xC
}

// Range: 0x8002113C -> 0x80021204
s32 frameScaleMatrix(f32 (*matrixResult)[4], f32 (*matrix)[4], f32 rScale) {
    // Parameters
    // f32 (* matrixResult)[4]; // r1+0x0
    // f32 (* matrix)[4]; // r1+0x4
    // f32 rScale; // r1+0x8
}

// Erased
static s32 frameConcatenateMatrix(f32 (*matrixResult)[4], f32 (*matrixA)[4], f32 (*matrixB)[4]) {
    // Parameters
    // f32 (* matrixResult)[4]; // r1+0x8
    // f32 (* matrixA)[4]; // r4
    // f32 (* matrixB)[4]; // r5
}

// Range: 0x80021070 -> 0x8002113C
static s32 frameConvertYUVtoRGB(u32* YUV, u32* RGB) {
    // Parameters
    // u32* YUV; // r1+0x0
    // u32* RGB; // r1+0x4

    // Local variables
    s32 Yl; // r7
    s32 R; // r1+0x0
    s32 G; // r5
    s32 B; // r8
}

// Range: 0x80020FA4 -> 0x80021070
static s32 packTakeBlocks(s32* piPack, u32* anPack, s32 nPackCount, s32 nBlockCount) {
    // Parameters
    // s32* piPack; // r1+0x0
    // u32* anPack; // r4
    // s32 nPackCount; // r5
    // s32 nBlockCount; // r1+0xC

    // Local variables
    s32 nOffset; // r9
    s32 nCount; // r10
    s32 iPack; // r11
    u32 nPack; // r5
    u32 nMask; // r12
    u32 nMask0; // r7
}

// Range: 0x80020F3C -> 0x80020FA4
static s32 packFreeBlocks(s32* piPack, u32* anPack) {
    // Parameters
    // s32* piPack; // r1+0x0
    // u32* anPack; // r1+0x4

    // Local variables
    s32 iPack; // r1+0x0
    u32 nMask; // r7
}

// Erased
static s32 packReset(u32* anPack, s32 nPackCount) {
    // Parameters
    // u32* anPack; // r3
    // s32 nPackCount; // r1+0x4

    // Local variables
    s32 iPack; // r7
}

// Range: 0x80020E20 -> 0x80020F3C
static s32 frameMakeTexture(struct __anon_0x24C38* pFrame, struct _FRAME_TEXTURE** ppTexture) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r3
    // struct _FRAME_TEXTURE** ppTexture; // r1+0xC

    // Local variables
    u32 nMask; // r5
    s32 iTexture; // r9
    s32 iTextureUsed; // r8
}

// Erased
static s32 frameFreeTexture(struct __anon_0x24C38* pFrame, struct _FRAME_TEXTURE* pTexture) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r31
    // struct _FRAME_TEXTURE* pTexture; // r29

    // Local variables
    s32 iTexture; // r30
}

// Range: 0x80020958 -> 0x80020E20
static s32 frameSetupCache(struct __anon_0x24C38* pFrame) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r30

    // Local variables
    s32 iTexture; // r1+0x8
}

// Erased
static s32 frameResetCache(struct __anon_0x24C38* pFrame) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r31
}

// Range: 0x80020764 -> 0x80020958
static s32 frameUpdateCache(struct __anon_0x24C38* pFrame) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r23

    // Local variables
    s32 nCount; // r1+0x8
    s32 nCountFree; // r1+0x8
    u32 nMask; // r27
    s32 nFrameCount; // r26
    s32 nFrameDelta; // r1+0x8
    s32 iTexture; // r1+0x8
    s32 iTextureUsed; // r25
    s32 iTextureCached; // r1+0x8
    struct _FRAME_TEXTURE* pTexture; // r24
    struct _FRAME_TEXTURE* pTextureCached; // r4
    struct _FRAME_TEXTURE* pTextureLast; // r5
}

// Erased
static s32 frameMultiTexture(struct __anon_0x24C38* pFrame) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0

    // Local variables
    s32 iMode; // r5
    s32 iType; // r1+0x0
    s32 nMode; // r1+0x0
    s32 nUsed; // r6
}

// Range: 0x80020340 -> 0x80020764
static s32 frameLoadTile(struct __anon_0x24C38* pFrame, struct _FRAME_TEXTURE** ppTexture, s32 iTileCode) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r29
    // struct _FRAME_TEXTURE** ppTexture; // r30
    // s32 iTileCode; // r31

    // Local variables
    s32 bFlag; // r27
    struct __anon_0x247BF* pTile; // r26
    struct _FRAME_TEXTURE* pTexture; // r1+0x18
    struct _FRAME_TEXTURE* pTextureLast; // r25
    u32 nData0; // r24
    u32 nData1; // r23
    u32 nData2; // r22
    u32 nData3; // r21
    s32 iTexture; // r1+0x8
    s32 nShift; // r3
}

// Erased
static s32 frameSetupTrackBuffer() {}

// Erased
static s32 frameCheckTrackBuffer() {}

// Erased
static s32 frameUpdateTrackBuffer() {}

// Range: 0x800202FC -> 0x80020340
s32 frameDrawReset(struct __anon_0x24C38* pFrame, s32 nFlag) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32 nFlag; // r1+0x4
}

// Range: 0x800202D0 -> 0x800202FC
s32 frameSetFill(struct __anon_0x24C38* pFrame, s32 bFill) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32 bFill; // r1+0x4
}

// Erased
static s32 frameGetFill(struct __anon_0x24C38* pFrame, s32* pbFill) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32* pbFill; // r1+0x4
}

// Erased
static s32 frameSetWire(struct __anon_0x24C38* pFrame, s32 bWire) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32 bWire; // r1+0x4
}

// Erased
static s32 frameGetWire(struct __anon_0x24C38* pFrame, s32* pbWire) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32* pbWire; // r1+0x4
}

// Range: 0x800201A8 -> 0x800202D0
s32 frameSetSize(struct __anon_0x24C38* pFrame, enum __anon_0x2813A eSize, s32 nSizeX, s32 nSizeY) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x8
    // enum __anon_0x2813A eSize; // r1+0xC
    // s32 nSizeX; // r1+0x10
    // s32 nSizeY; // r1+0x14
}

// Erased
static s32 frameGetSize(struct __anon_0x24C38* pFrame, enum __anon_0x2813A eSize, s32* pnSizeX, s32* pnSizeY) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // enum __anon_0x2813A eSize; // r1+0x4
    // s32* pnSizeX; // r1+0x8
    // s32* pnSizeY; // r1+0xC
}

// Range: 0x80020014 -> 0x800201A8
s32 frameSetMode(struct __anon_0x24C38* pFrame, enum __anon_0x27E96 eType, u32 nMode) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // enum __anon_0x27E96 eType; // r1+0x4
    // u32 nMode; // r1+0x8

    // Local variables
    u32 nFlag; // r8
    u32 nModeChanged; // r9
}

// Range: 0x8001FFFC -> 0x80020014
s32 frameGetMode(struct __anon_0x24C38* pFrame, enum __anon_0x27E96 eType, u32* pnMode) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // enum __anon_0x27E96 eType; // r1+0x4
    // u32* pnMode; // r1+0x8
}

// Range: 0x8001F970 -> 0x8001FFFC
s32 frameSetMatrix(struct __anon_0x24C38* pFrame, f32 (*matrix)[4], enum __anon_0x27B8C eType, s32 bLoad, s32 bPush,
                   s32 nAddressN64) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r29
    // f32 (* matrix)[4]; // r30
    // enum __anon_0x27B8C eType; // r26
    // s32 bLoad; // r28
    // s32 bPush; // r27
    // s32 nAddressN64; // r31

    // Local variables
    s32 bFlag; // r28
    f32(*matrixTarget)[4]; // r3
    f32 matrixResult[4][4]; // r1+0x48

    // References
    // -> struct __anon_0x26A4E* gpSystem;
}

// Range: 0x8001F850 -> 0x8001F970
s32 frameGetMatrix(struct __anon_0x24C38* pFrame, f32 (*matrix)[4], enum __anon_0x27B8C eType, s32 bPull) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r30
    // f32 (* matrix)[4]; // r7
    // enum __anon_0x27B8C eType; // r1+0x10
    // s32 bPull; // r31
}

// Erased
static s32 frameProjectVertex(struct __anon_0x24C38* pFrame, s32 iVertex, f32* prX, f32* prY, f32* prZ) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32 iVertex; // r1+0x4
    // f32* prX; // r1+0x8
    // f32* prY; // r1+0xC
    // f32* prZ; // r1+0x10

    // Local variables
    f32 rW; // r1+0x0
    struct __anon_0x23FC4* pVertex; // r8
}

// Range: 0x8001EDCC -> 0x8001F850
s32 frameLoadVertex(struct __anon_0x24C38* pFrame, void* pBuffer, s32 iVertex0, s32 nCount) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r30
    // void* pBuffer; // r4
    // s32 iVertex0; // r20
    // s32 nCount; // r31

    // Local variables
    f32 mag; // f5
    s32 iLight; // r29
    s32 nLight; // r28
    s32 nTexGen; // r27
    f32 colorS; // f7
    f32 colorT; // f6
    f32 rS; // f8
    f32 rT; // f9
    f32 arNormal[3]; // r1+0x40
    f32 arPosition[3]; // r1+0x34
    struct __anon_0x23FC4* pVertex; // r8
    u32 nData32; // r12
    struct __anon_0x23CAB* aLight; // r26
    struct __anon_0x23CAB* pLight; // r25
    s32 iVertex1; // r1+0x8
    f32 rScale; // r1+0x8
    f32 rScaleST; // r1+0x8
    char* pnData8; // r24
    s16* pnData16; // r23
    f32(*matrixView)[4]; // r22
    f32(*matrixModel)[4]; // r21
    f32 rColorR; // f7
    f32 rColorG; // f8
    f32 rColorB; // f9
    f32 rDiffuse; // f27
    f32 rInverseW; // f6
    f32 rInverseLength; // r1+0x8
    struct __anon_0x274AD vec; // r1+0x28
    f32 distance; // r1+0x8

    // References
    // -> struct __anon_0x26A4E* gpSystem;
    // -> s32 __float_huge[];
    // -> s32 __float_nan[];
}

// Range: 0x8001EC80 -> 0x8001EDCC
s32 frameCullDL(struct __anon_0x24C38* pFrame, s32 nVertexStart, s32 nVertexEnd) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32 nVertexStart; // r1+0x4
    // s32 nVertexEnd; // r1+0x8

    // Local variables
    f32 rX; // r1+0x0
    f32 rY; // f2
    f32 rZ; // f1
    f32 rW; // r1+0x0
    f32(*matrix)[4]; // r5
    struct __anon_0x23FC4* vtxP; // r6
    struct __anon_0x23FC4* endVtxP; // r4
    s32 nCode; // r1+0x0
    s32 nCodeFull; // r7
}

// Range: 0x8001EBA0 -> 0x8001EC80
s32 frameLoadTLUT(struct __anon_0x24C38* pFrame, s32 nCount, s32 iTile) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r30
    // s32 nCount; // r1+0xC
    // s32 iTile; // r1+0x10

    // Local variables
    s32 iTMEM; // r28
    s32 nSize; // r27
    u32 nSum; // r26
    u64 nData64; // r25
    u16 nData16; // r3
    u16* pSource; // r31
    s32 tileNum; // r4
}

// Range: 0x8001DC58 -> 0x8001EBA0
s32 frameLoadTMEM(struct __anon_0x24C38* pFrame, enum __anon_0x26C3F eType, s32 iTile) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r29
    // enum __anon_0x26C3F eType; // r30
    // s32 iTile; // r31

    // Local variables
    s32 bFlip; // r10
    s32 iTMEM; // r5
    s32 nSize; // r6
    s32 nStep; // r11
    s32 nDelta; // r12
    s32 iScan; // r12
    s32 nOffset; // r7
    struct __anon_0x247BF* pTile; // r1+0x8
    u8 nData8; // r30
    u16 nData16; // r30
    u32 nData32; // r30
    u32 nSum; // r1+0x8
    u64* pSource; // r4
    s32 nCount; // r6
    s32 nScanFull; // r7
    s32 nScanPart; // r8
    u8* pSource8; // r31
    u16* pSource16; // r31
    u32* pSource32; // r31

    // References
    // -> struct __anon_0x26A4E* gpSystem;
}

// Range: 0x8001DC4C -> 0x8001DC58
s32 frameSetLightCount(struct __anon_0x24C38* pFrame, s32 nCount) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32 nCount; // r1+0x4
}

// Range: 0x8001DB24 -> 0x8001DC4C
s32 frameSetLight(struct __anon_0x24C38* pFrame, s32 iLight, char* pData) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x8
    // s32 iLight; // r1+0xC
    // char* pData; // r1+0x10

    // Local variables
    struct __anon_0x23CAB* pLight; // r6
}

// Range: 0x8001DA74 -> 0x8001DB24
s32 frameSetLookAt(struct __anon_0x24C38* pFrame, s32 iLookAt, char* pData) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // s32 iLookAt; // r1+0x4
    // char* pData; // r1+0x8
}

// Range: 0x8001D8E0 -> 0x8001DA74
s32 frameSetViewport(struct __anon_0x24C38* pFrame, s16* pData) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x8
    // s16* pData; // r1+0xC

    // Local variables
    s32 iScale; // r1+0x8
    f32 rY; // f1
    f32 rSizeX; // f3
    f32 rSizeY; // r1+0x8
    f32 arScale[3]; // r1+0x28
}

// Range: 0x8001D830 -> 0x8001D8E0
s32 frameResetUCode(struct __anon_0x24C38* pFrame, enum __anon_0x2625D eType) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // enum __anon_0x2625D eType; // r1+0x4

    // Local variables
    s32 iMode; // r6
}

// Range: 0x8001D7F8 -> 0x8001D830
s32 frameSetBuffer(struct __anon_0x24C38* pFrame, enum __anon_0x2614E eType) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r1+0x0
    // enum __anon_0x2614E eType; // r1+0x4
}

// Range: 0x8001D740 -> 0x8001D7F8
s32 frameFixMatrixHint(struct __anon_0x24C38* pFrame, s32 nAddressFloat, s32 nAddressFixed) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r3
    // s32 nAddressFloat; // r1+0x4
    // s32 nAddressFixed; // r1+0x8

    // Local variables
    s32 iHint; // r8
    s32 iHintTest; // r9
}

// Erased
static s32 frameGetMatrixHint(struct __anon_0x24C38* pFrame, u32 nAddress, s32* piHint) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r3
    // u32 nAddress; // r1+0x4
    // s32* piHint; // r1+0x8

    // Local variables
    s32 iHint; // r8
}

// Range: 0x8001D624 -> 0x8001D740
s32 frameSetMatrixHint(struct __anon_0x24C38* pFrame, enum __anon_0x25D5E eProjection, s32 nAddressFloat,
                       s32 nAddressFixed, f32 rNear, f32 rFar, f32 rFOVY, f32 rAspect, f32 rScale) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r3
    // enum __anon_0x25D5E eProjection; // r1+0x4
    // s32 nAddressFloat; // r5
    // s32 nAddressFixed; // r6
    // f32 rNear; // f1
    // f32 rFar; // r1+0x14
    // f32 rFOVY; // r1+0x18
    // f32 rAspect; // r1+0x1C
    // f32 rScale; // r1+0x20

    // Local variables
    s32 iHint; // r10
}

// Range: 0x8001D4B8 -> 0x8001D624
s32 frameInvalidateCache(struct __anon_0x24C38* pFrame, s32 nOffset0, s32 nOffset1) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r25
    // s32 nOffset0; // r1+0xC
    // s32 nOffset1; // r1+0x10

    // Local variables
    s32 iTexture0; // r28
    s32 iTexture1; // r27
    struct _FRAME_TEXTURE* pTexture; // r23
    struct _FRAME_TEXTURE* pTextureNext; // r26
}

// Range: 0x8001D39C -> 0x8001D4B8
s32 frameGetTextureInfo(struct __anon_0x24C38* pFrame, struct __anon_0x25A82* pInfo) {
    // Parameters
    // struct __anon_0x24C38* pFrame; // r3
    // struct __anon_0x25A82* pInfo; // r1+0xC

    // Local variables
    struct _FRAME_TEXTURE* pTexture; // r10
    s32 iTexture; // r5
    s32 nCount; // r6
    s32 nSize; // r1+0x8
}

// Range: 0x8001D34C -> 0x8001D39C
void PSMTX44MultVecNoW(f32 (*m)[4], struct __anon_0x239BA* src, struct __anon_0x239BA* dst) {
    // Parameters
    // f32 (* m)[4]; // r3
    // struct __anon_0x239BA* src; // r4
    // struct __anon_0x239BA* dst; // r5
}
