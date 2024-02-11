// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// size: 0x10
struct _XL_OBJECTTYPE
{
	char *szName; // 0x0
	int nSizeObject; // 0x4
	_XL_OBJECTTYPE *pClassBase; // 0x8
	int (*pfEvent)(void */* unknown0 */, int /* unknown1 */, void */* unknown2 */); // 0xC
};

// Location: 0x48A80E80
_XL_OBJECTTYPE gClassFrame;

// Local to compilation unit
// Location: 0x80135688
static int gbFrameValid;

// Local to compilation unit
// Location: 0x8013568C
static int gbFrameBegin;

// Local to compilation unit
// Location: 0x80135690
static int snScissorChanged;

// Local to compilation unit
// Location: 0x80135694
static unsigned long snScissorXOrig;

// Local to compilation unit
// Location: 0x80135698
static unsigned long snScissorYOrig;

// Local to compilation unit
// Location: 0x8013569C
static unsigned long snScissorWidth;

// Local to compilation unit
// Location: 0x801356A0
static unsigned long snScissorHeight;

// Local to compilation unit
// Location: 0x801356A4
static int sCopyFrameSyncReceived;

// Local to compilation unit
// Location: 0x801356A8
static unsigned char sSpecialZeldaHackON;

// Local to compilation unit
// Location: 0x801356AC
static unsigned int sDestinationBuffer;

// Local to compilation unit
// Location: 0x801356B0
static unsigned int sSrcBuffer;

// Local to compilation unit
// Location: 0x801085A0
static unsigned int sConstantBufAddr[6];

// Local to compilation unit
// Location: 0x801356B4
static unsigned int sNumAddr;

// Location: 0x0
unsigned int sZBufIdx;

// Local to compilation unit
// Location: 0x801356B8
static unsigned int gHackCreditsColor;

// Location: 0x801356BC
int gNoSwapBuffer;

// Location: 0x58A80E80
unsigned long ganNameColor[8];

// Local to compilation unit
// Location: 0x80134DD8
static unsigned char sRemapI$746[8];

// size: 0x4
enum _GXTexMapID
{
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
	GX_TEX_DISABLE = 256
};

// Location: 0x78A80E80
_GXTexMapID ganNamePixel[8];

// Location: 0x800EA898
unsigned long ganNameTexMtx[8];

// size: 0x4
enum _GXTexCoordID
{
	GX_TEXCOORD0 = 0,
	GX_TEXCOORD1 = 1,
	GX_TEXCOORD2 = 2,
	GX_TEXCOORD3 = 3,
	GX_TEXCOORD4 = 4,
	GX_TEXCOORD5 = 5,
	GX_TEXCOORD6 = 6,
	GX_TEXCOORD7 = 7,
	GX_MAX_TEXCOORD = 8,
	GX_TEXCOORD_NULL = 255
};

// Location: 0x800EA8B8
_GXTexCoordID ganNameTexCoord[8];

// Local to compilation unit
// Location: 0x20A90E80
static char  *gaszNameColor[20];

// Local to compilation unit
// Location: 0x70A90E80
static char  *gaszNameAlpha[9];

// Local to compilation unit
// Location: 0x800EA994
static int (*gapfDrawTriangle[8])(void */* unknown0 */, void */* unknown1 */);

// Local to compilation unit
// Location: 0x800EA9B4
static int (*gapfDrawLine[6])(void */* unknown0 */, void */* unknown1 */);

// Local to compilation unit
// Location: 0x801356C0
static int gnCountMapHack;

// Local to compilation unit
// Location: 0x801356C4
static int nCounter$1367;

// Local to compilation unit
// Location: 0x801356C8
static int bSkip$1410;

// Local to compilation unit
// Location: 0x801085C0
static unsigned short sTempZBuf[4800][4][4];

// Local to compilation unit
// Location: 0x800EA9CC
static unsigned long sZBufShift[8][2];

// Local to compilation unit
// Location: 0x24AA0E80
static char  *gaszNameColorType[5];

// Location: 0x0
void *pSrc$1492;

// Location: 0x0
signed long long lastTime$1493;

// Location: 0x0
signed long long curTime$1494;

// Location: 0x0
signed long long diffTime$1495;

// size: 0x20
struct _GXTexObj
{
	unsigned long dummy[8]; // 0x0
};

// Local to compilation unit
// Location: 0x8012DDC0
static _GXTexObj sFrameObj1$1562;

// Local to compilation unit
// Location: 0x8012DDE0
static _GXTexObj sFrameObj2$1563;

// Local to compilation unit
// Location: 0xDE1280
static _GXTexObj sFrameObj$1564;

// Local to compilation unit
// Location: 0x20DE1280
static _GXTexObj sFrameObj$1565;

// Local to compilation unit
// Location: 0x40DE1280
static _GXTexObj sFrameObj$1568;

// Local to compilation unit
// Location: 0x60DE1280
static unsigned long line$1582[80][4][4];

// Local to compilation unit
// Location: 0x60F21280
static unsigned short line$1606[80][4][4];

// Local to compilation unit
// Location: 0x60FC1280
static unsigned short line$1630[80][4][4];

// Local to compilation unit
// Location: 0x60061380
static _GXTexObj sFrameObj$1647;

// Local to compilation unit
// Location: 0x564E1380
static unsigned char cAlpha$1648;

// Local to compilation unit
// Location: 0x80061380
static _GXTexObj sFrameObj$1660;

// Local to compilation unit
// Location: 0x801306A0
static _GXTexObj frameObj$1663;

// Local to compilation unit
// Location: 0x801306C0
static _GXTexObj frameObj$1673;

// Local to compilation unit
// Location: 0x38AA0E80
static unsigned long sCommandCodes$1679[8];

// Local to compilation unit
// Location: 0x801356CC
static int nLastFrame$1695;

// Location: 0x0
int nLensThisFrame$1696;

// Local to compilation unit
// Location: 0x801356D0
static int nCopyFrame$1697;

// Local to compilation unit
// Location: 0x58AA0E80
static unsigned long sCommandCodes$1702[10];

// Local to compilation unit
// Location: 0x800EAA80
static unsigned long sCommandCodes2$1722[10];

// Local to compilation unit
// Location: 0x801306E0
static unsigned short tempLine$1785[16][4][4];

// Local to compilation unit
// Location: 0x800EAAA8
static unsigned int GBIcode$1816[3];

// Local to compilation unit
// Location: 0x800EAAB4
static unsigned int GBIcode2D2$1906[7];

// Local to compilation unit
// Location: 0x800EAAD0
static unsigned int GBIcode3D1$1907[5];

// Local to compilation unit
// Location: 0x800EAAE4
static unsigned int GBIcode3D2$1908[6];

// Location: 0x800EAAFC
unsigned int anRenderModeDatabaseCycle2[100];

// Location: 0x800EAC8C
unsigned int anRenderModeDatabaseCopy[100];

// Location: 0x1CAE0E80
unsigned int anRenderModeDatabaseFill[100];

// Location: 0x800EAFAC
unsigned int anRenderModeDatabaseCycle1[100];

// Location: 0x0
unsigned int nTotal$2284;

// Location: 0x0
unsigned int nTimesCalled$2285;

// size: 0xC
struct __anon_0x239BA
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
};

void PSMTX44MultVecNoW(float *m[4], __anon_0x239BA *src, __anon_0x239BA *dst);

// size: 0x10
struct __anon_0x23B04
{
	float rX; // 0x0
	float rY; // 0x4
	float rSizeX; // 0x8
	float rSizeY; // 0xC
};

// size: 0x14
struct __anon_0x23B9E
{
	int nSize; // 0x0
	int nWidth; // 0x4
	int nFormat; // 0x8
	void *pData; // 0xC
	int nAddress; // 0x10
};

// size: 0x3C
struct __anon_0x23CAB
{
	int bTransformed; // 0x0
	__anon_0x274AD rVecOrigTowards; // 0x4
	float rColorR; // 0x10
	float rColorG; // 0x14
	float rColorB; // 0x18
	float rVectorX; // 0x1C
	float rVectorY; // 0x20
	float rVectorZ; // 0x24
	float kc; // 0x28
	float kl; // 0x2C
	float kq; // 0x30
	signed short coordX; // 0x34
	signed short coordY; // 0x36
	signed short coordZ; // 0x38
};

// size: 0x34
struct __anon_0x23EDB
{
	int bTransformed; // 0x0
	__anon_0x274AD rS; // 0x4
	__anon_0x274AD rT; // 0x10
	__anon_0x274AD rSRaw; // 0x1C
	__anon_0x274AD rTRaw; // 0x28
};

// size: 0x1C
struct __anon_0x23FC4
{
	float rSum; // 0x0
	float rS; // 0x4
	float rT; // 0x8
	__anon_0x274AD vec; // 0xC
	unsigned char anColor[4]; // 0x18
};

// size: 0x1000
union __anon_0x24123
{
	unsigned char u8[4096]; // 0x0
	unsigned short u16[2048]; // 0x0
	unsigned int u32[1024]; // 0x0
	unsigned long long u64[512]; // 0x0
};

// size: 0x1000
struct __anon_0x241C0
{
	__anon_0x24123 data; // 0x0
};

// size: 0x4
enum _GXTexFmt
{
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
	GX_TF_A8 = 39
};

// size: 0xC
struct _GXTlutObj
{
	unsigned long dummy[3]; // 0x0
};

// size: 0x6C
struct _FRAME_TEXTURE
{
	int nMode; // 0x0
	int iPackPixel; // 0x4
	int iPackColor; // 0x8
	int nFrameLast; // 0xC
	signed short nSizeX; // 0x10
	signed short nSizeY; // 0x12
	unsigned int nAddress; // 0x14
	unsigned int nCodePixel; // 0x18
	unsigned int nCodeColor; // 0x1C
	_FRAME_TEXTURE *pTextureNext; // 0x20
	unsigned int nData0; // 0x24
	unsigned int nData1; // 0x28
	unsigned int nData2; // 0x2C
	unsigned int nData3; // 0x30
	_GXTexFmt eFormat; // 0x34
	_GXTlutObj objectTLUT; // 0x38
	_GXTexObj objectTexture; // 0x44
	_GXTexWrapMode eWrapS; // 0x64
	_GXTexWrapMode eWrapT; // 0x68
};

// size: 0x2C
struct __anon_0x247BF
{
	int nSize; // 0x0
	int nTMEM; // 0x4
	int iTLUT; // 0x8
	int nSizeX; // 0xC
	int nFormat; // 0x10
	signed short nMaskS; // 0x14
	signed short nMaskT; // 0x16
	signed short nModeS; // 0x18
	signed short nModeT; // 0x1A
	signed short nShiftS; // 0x1C
	signed short nShiftT; // 0x1E
	signed short nX0; // 0x20
	signed short nY0; // 0x22
	signed short nX1; // 0x24
	signed short nY1; // 0x26
	unsigned int nCodePixel; // 0x28
};

// size: 0x24
struct __anon_0x24A81
{
	int nCount; // 0x0
	float rScale; // 0x4
	float rAspect; // 0x8
	float rFieldOfViewY; // 0xC
	float rClipNear; // 0x10
	float rClipFar; // 0x14
	unsigned int nAddressFloat; // 0x18
	unsigned int nAddressFixed; // 0x1C
	__anon_0x25D5E eProjection; // 0x20
};

// size: 0x3D150
struct __anon_0x24C38
{
	unsigned int anCIMGAddresses[8]; // 0x0
	unsigned short nNumCIMGAddresses; // 0x20
	int bBlurOn; // 0x24
	int bHackPause; // 0x28
	int nHackCount; // 0x2C
	int nFrameCounter; // 0x30
	int bPauseThisFrame; // 0x34
	int bCameFromBomberNotes; // 0x38
	int bInBomberNotes; // 0x3C
	int bShrinking; // 0x40
	int bSnapShot; // 0x44
	int bUsingLens; // 0x48
	unsigned char cBlurAlpha; // 0x4C
	int bBlurredThisFrame; // 0x50
	int nFrameCIMGCalls; // 0x54
	int bModifyZBuffer; // 0x58
	int bOverrideDepth; // 0x5C
	int nZBufferSets; // 0x60
	int nLastFrameZSets; // 0x64
	int bPauseBGDrawn; // 0x68
	int bFrameOn; // 0x6C
	int bBackBufferDrawn; // 0x70
	int bGrabbedFrame; // 0x74
	unsigned long long *pnGBI; // 0x78
	unsigned int nFlag; // 0x7C
	float rScaleX; // 0x80
	float rScaleY; // 0x84
	unsigned int nCountFrames; // 0x88
	unsigned int nMode; // 0x8C
	unsigned int aMode[10]; // 0x90
	__anon_0x23B04 viewport; // 0xB8
	__anon_0x23B9E aBuffer[4]; // 0xC8
	unsigned int nOffsetDepth0; // 0x118
	unsigned int nOffsetDepth1; // 0x11C
	int nWidthLine; // 0x120
	float rDepth; // 0x124
	float rDelta; // 0x128
	int (*aDraw[4])(void */* unknown0 */, void */* unknown1 */); // 0x12C
	int nCountLight; // 0x13C
	__anon_0x23CAB aLight[8]; // 0x140
	__anon_0x23EDB lookAt; // 0x320
	int nCountVertex; // 0x354
	__anon_0x23FC4 aVertex[80]; // 0x358
	__anon_0x241C0 TMEM; // 0xC18
	void *aPixelData; // 0x1C18
	void *aColorData; // 0x1C1C
	int nBlocksPixel; // 0x1C20
	int nBlocksMaxPixel; // 0x1C24
	int nBlocksColor; // 0x1C28
	int nBlocksMaxColor; // 0x1C2C
	int nBlocksTexture; // 0x1C30
	int nBlocksMaxTexture; // 0x1C34
	unsigned int anPackPixel[48]; // 0x1C38
	unsigned int anPackColor[320]; // 0x1CF8
	unsigned int nAddressLoad; // 0x21F8
	unsigned int nCodePixel; // 0x21FC
	unsigned int nTlutCode[16]; // 0x2200
	_FRAME_TEXTURE aTexture[2048]; // 0x2240
	unsigned int anTextureUsed[64]; // 0x38240
	_FRAME_TEXTURE *apTextureCached[4096]; // 0x38340
	int iTileLoad; // 0x3C340
	unsigned int n2dLoadTexType; // 0x3C344
	int nLastX0; // 0x3C348
	int nLastY0; // 0x3C34C
	int nLastX1; // 0x3C350
	int nLastY1; // 0x3C354
	__anon_0x247BF aTile[8]; // 0x3C358
	int anSizeX[2]; // 0x3C4B8
	int anSizeY[2]; // 0x3C4C0
	int iHintMatrix; // 0x3C4C8
	int iMatrixModel; // 0x3C4CC
	int iHintProjection; // 0x3C4D0
	float matrixView[4][4]; // 0x3C4D4
	int iHintLast; // 0x3C514
	int iHintHack; // 0x3C518
	__anon_0x25D5E eTypeProjection; // 0x3C51C
	float aMatrixModel[10][4][4]; // 0x3C520
	float matrixProjection[4][4]; // 0x3C7A0
	float matrixProjectionExtra[4][4]; // 0x3C7E0
	__anon_0x24A81 aMatrixHint[64]; // 0x3C820
	unsigned char primLODmin; // 0x3D120
	unsigned char primLODfrac; // 0x3D121
	unsigned char lastTile; // 0x3D122
	unsigned char iTileDrawn; // 0x3D123
	_GXColor aColor[5]; // 0x3D124
	unsigned int nModeVtx; // 0x3D138
	unsigned short *nTempBuffer; // 0x3D13C
	unsigned short *nCopyBuffer; // 0x3D140
	unsigned int *nLensBuffer; // 0x3D144
	unsigned short *nCameraBuffer; // 0x3D148
};

// size: 0x8
struct __anon_0x25A82
{
	int nSizeTextures; // 0x0
	int nCountTextures; // 0x4
};

int frameGetTextureInfo(__anon_0x24C38 *pFrame, __anon_0x25A82 *pInfo)
{
	_FRAME_TEXTURE *pTexture;
	int iTexture;
	int nCount;
	int nSize;
}

int frameInvalidateCache(__anon_0x24C38 *pFrame, int nOffset0, int nOffset1)
{
	int iTexture0;
	int iTexture1;
	_FRAME_TEXTURE *pTexture;
	_FRAME_TEXTURE *pTextureNext;
}

// size: 0x4
enum __anon_0x25D5E
{
	FMP_NONE = 4294967295,
	FMP_PERSPECTIVE = 0,
	FMP_ORTHOGRAPHIC = 1
};

int frameSetMatrixHint(__anon_0x24C38 *pFrame, __anon_0x25D5E eProjection, int nAddressFloat, int nAddressFixed, float rNear, float rFar, float rFOVY, float rAspect, float rScale)
{
	int iHint;
}

int frameGetMatrixHint(__anon_0x24C38 *pFrame, unsigned int nAddress, int *piHint)
{
	int iHint;
}

int frameFixMatrixHint(__anon_0x24C38 *pFrame, int nAddressFloat, int nAddressFixed)
{
	int iHint;
	int iHintTest;
}

// size: 0x4
enum __anon_0x2614E
{
	FBT_NONE = 4294967295,
	FBT_DEPTH = 0,
	FBT_IMAGE = 1,
	FBT_COLOR_SHOW = 2,
	FBT_COLOR_DRAW = 3,
	FBT_COUNT = 4
};

int frameSetBuffer(__anon_0x24C38 *pFrame, __anon_0x2614E eType);

// size: 0x4
enum __anon_0x2625D
{
	FRT_NONE = 4294967295,
	FRT_COLD = 0,
	FRT_WARM = 1
};

int frameResetUCode(__anon_0x24C38 *pFrame, __anon_0x2625D eType)
{
	int iMode;
}

int frameSetViewport(__anon_0x24C38 *pFrame, signed short *pData)
{
	int iScale;
	float rY;
	float rSizeX;
	float rSizeY;
	float arScale[3];
}

int frameSetLookAt(__anon_0x24C38 *pFrame, int iLookAt, char *pData);

int frameSetLight(__anon_0x24C38 *pFrame, int iLight, char *pData)
{
	__anon_0x23CAB *pLight;
}

int frameSetLightCount(__anon_0x24C38 *pFrame, int nCount);

// size: 0x4
enum __anon_0x266CE
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

// size: 0x10
struct __anon_0x26732
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x267E3
{
	SRT_NONE = 4294967295,
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
	SRT_UNKNOWN = 12
};

// size: 0x4
enum __anon_0x26911
{
	SOT_NONE = 4294967295,
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
	SOT_COUNT = 16
};

// size: 0x88
struct __anon_0x26A4E
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x266CE eMode; // 0xC
	__anon_0x26732 romCopy; // 0x10
	__anon_0x267E3 eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x26911 storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// Location: 0x561380
__anon_0x26A4E *gpSystem;

// size: 0x4
enum __anon_0x26C3F
{
	FLT_NONE = 4294967295,
	FLT_TILE = 0,
	FLT_BLOCK = 1
};

int frameLoadTMEM(__anon_0x24C38 *pFrame, __anon_0x26C3F eType, int iTile)
{
	int bFlip;
	int iTMEM;
	int nSize;
	int nStep;
	int nDelta;
	int iScan;
	int nOffset;
	__anon_0x247BF *pTile;
	unsigned char nData8;
	unsigned short nData16;
	unsigned int nData32;
	unsigned int nSum;
	unsigned long long *pSource;
	int nCount;
	int nScanFull;
	int nScanPart;
	unsigned char *pSource8;
	unsigned short *pSource16;
	unsigned int *pSource32;
	// References: gpSystem (0x561380)
}

int frameLoadTLUT(__anon_0x24C38 *pFrame, int nCount, int iTile)
{
	int iTMEM;
	int nSize;
	unsigned int nSum;
	unsigned long long nData64;
	unsigned short nData16;
	unsigned short *pSource;
	long tileNum;
}

int frameCullDL(__anon_0x24C38 *pFrame, int nVertexStart, int nVertexEnd)
{
	float rX;
	float rY;
	float rZ;
	float rW;
	float *matrix[4];
	__anon_0x23FC4 *vtxP;
	__anon_0x23FC4 *endVtxP;
	int nCode;
	int nCodeFull;
}

// Location: 0x783E0F80
int __float_nan[];

// Location: 0x7C3E0F80
int __float_huge[];

// size: 0xC
struct __anon_0x274AD
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
};

int frameLoadVertex(__anon_0x24C38 *pFrame, void *pBuffer, int iVertex0, int nCount)
{
	float mag;
	int iLight;
	int nLight;
	int nTexGen;
	float colorS;
	float colorT;
	float rS;
	float rT;
	float arNormal[3];
	float arPosition[3];
	__anon_0x23FC4 *pVertex;
	unsigned int nData32;
	__anon_0x23CAB *aLight;
	__anon_0x23CAB *pLight;
	int iVertex1;
	float rScale;
	float rScaleST;
	char *pnData8;
	signed short *pnData16;
	float *matrixView[4];
	float *matrixModel[4];
	float rColorR;
	float rColorG;
	float rColorB;
	float rDiffuse;
	float rInverseW;
	float rInverseLength;
	__anon_0x274AD vec;
	float distance;
	// References: gpSystem (0x561380)
	// References: __float_huge (0x7C3E0F80)
	// References: __float_nan (0x783E0F80)
}

int frameProjectVertex(__anon_0x24C38 *pFrame, int iVertex, float *prX, float *prY, float *prZ)
{
	float rW;
	__anon_0x23FC4 *pVertex;
}

// size: 0x4
enum __anon_0x27B8C
{
	FMT_MODELVIEW = 0,
	FMT_PROJECTION = 1
};

int frameGetMatrix(__anon_0x24C38 *pFrame, float *matrix[4], __anon_0x27B8C eType, int bPull);

int frameSetMatrix(__anon_0x24C38 *pFrame, float *matrix[4], __anon_0x27B8C eType, int bLoad, int bPush, int nAddressN64)
{
	int bFlag;
	float *matrixTarget[4];
	float matrixResult[4][4];
	// References: gpSystem (0x561380)
}

// size: 0x4
enum __anon_0x27E96
{
	FMT_NONE = 4294967295,
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
	FMT_COUNT = 10
};

int frameGetMode(__anon_0x24C38 *pFrame, __anon_0x27E96 eType, unsigned int *pnMode);

int frameSetMode(__anon_0x24C38 *pFrame, __anon_0x27E96 eType, unsigned int nMode)
{
	unsigned int nFlag;
	unsigned int nModeChanged;
}

// size: 0x4
enum __anon_0x2813A
{
	FS_NONE = 4294967295,
	FS_SOURCE = 0,
	FS_TARGET = 1,
	FS_COUNT = 2
};

int frameGetSize(__anon_0x24C38 *pFrame, __anon_0x2813A eSize, int *pnSizeX, int *pnSizeY);

int frameSetSize(__anon_0x24C38 *pFrame, __anon_0x2813A eSize, int nSizeX, int nSizeY);

int frameGetWire(__anon_0x24C38 *pFrame, int *pbWire);

int frameSetWire(__anon_0x24C38 *pFrame, int bWire);

int frameGetFill(__anon_0x24C38 *pFrame, int *pbFill);

int frameSetFill(__anon_0x24C38 *pFrame, int bFill);

int frameDrawReset(__anon_0x24C38 *pFrame, int nFlag);

// size: 0x8
struct __anon_0x285E5
{
	int shift; // 0x0
	long add; // 0x4
};

// size: 0x30
struct __anon_0x2865F
{
	int nBIST; // 0x0
	int nStatus; // 0x4
	void *pHost; // 0x8
	int nModeTest; // 0xC
	int nDataTest; // 0x10
	int nAddressTest; // 0x14
	int nAddress0; // 0x18
	int nAddress1; // 0x1C
	int nClock; // 0x20
	int nClockCmd; // 0x24
	int nClockPipe; // 0x28
	int nClockTMEM; // 0x2C
};

// size: 0x40
struct __anon_0x28835
{
	int nType; // 0x0
	int nFlag; // 0x4
	int nOffsetBoot; // 0x8
	int nLengthBoot; // 0xC
	int nOffsetCode; // 0x10
	int nLengthCode; // 0x14
	int nOffsetData; // 0x18
	int nLengthData; // 0x1C
	int nOffsetStack; // 0x20
	int nLengthStack; // 0x24
	int nOffsetBuffer; // 0x28
	int nLengthBuffer; // 0x2C
	int nOffsetMBI; // 0x30
	int nLengthMBI; // 0x34
	int nOffsetYield; // 0x38
	int nLengthYield; // 0x3C
};

// size: 0x4
enum __anon_0x28AC5
{
	RUT_NONE = 4294967295,
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
	RUT_JPEG = 13
};

// size: 0xD8
struct __anon_0x28C10
{
	int iDL; // 0x0
	int bValid; // 0x4
	__anon_0x28835 task; // 0x8
	int nCountVertex; // 0x48
	__anon_0x28AC5 eTypeUCode; // 0x4C
	unsigned int n2TriMult; // 0x50
	unsigned int nVersionUCode; // 0x54
	int anBaseSegment[16]; // 0x58
	unsigned long long  *apDL[16]; // 0x98
};

// size: 0x20
struct __anon_0x28E31
{
	float aRotations[2][2]; // 0x0
	float fX; // 0x10
	float fY; // 0x14
	float fBaseScaleX; // 0x18
	float fBaseScaleY; // 0x1C
};

// size: 0x14
struct __anon_0x28F3E
{
	float rS; // 0x0
	float rT; // 0x4
	signed short nX; // 0x8
	signed short nY; // 0xA
	signed short nZ; // 0xC
	unsigned char anData[4]; // 0xE
};

// size: 0x3
struct __anon_0x29056
{
	char anNormal[3]; // 0x0
};

// size: 0x4
struct __anon_0x290D5
{
	unsigned char anMaterial[4]; // 0x0
};

// size: 0x40
struct __anon_0x29178
{
	float aMatrix[4][4]; // 0x0
};

// size: 0x6
struct __anon_0x291D6
{
	unsigned char nRed; // 0x0
	unsigned char nGreen; // 0x1
	unsigned char nBlue; // 0x2
	char rVectorX; // 0x3
	char rVectorY; // 0x4
	char rVectorZ; // 0x5
};

// size: 0x10
struct __anon_0x29487
{
	signed short anSlice[8]; // 0x0
};

// size: 0x4
enum __anon_0x29567
{
	RUT_NOCODE = 4294967295,
	RUT_ABI1 = 0,
	RUT_ABI2 = 1,
	RUT_ABI3 = 2,
	RUT_ABI4 = 3,
	RUT_UNKNOWN = 4
};

// size: 0x10
struct tXL_LIST
{
	int nItemSize; // 0x0
	int nItemCount; // 0x4
	void *pNodeHead; // 0x8
	void *pNodeNext; // 0xC
};

// size: 0x8
struct __anon_0x296E2
{
	signed short r; // 0x0
	signed short g; // 0x2
	signed short b; // 0x4
	signed short a; // 0x6
};

// size: 0x6
struct __anon_0x29770
{
	signed short y; // 0x0
	signed short u; // 0x2
	signed short v; // 0x4
};

// size: 0x39CC
struct __anon_0x297E0
{
	int nMode; // 0x0
	__anon_0x28C10 yield; // 0x4
	unsigned int nTickLast; // 0xDC
	int (*pfUpdateWaiting)(); // 0xE0
	unsigned int n2TriMult; // 0xE4
	int aStatus[4]; // 0xE8
	float aMatrixOrtho[4][4]; // 0xF8
	unsigned int nMode2D; // 0x138
	__anon_0x28E31 twoDValues; // 0x13C
	int nPass; // 0x15C
	unsigned int nZSortSubDL; // 0x160
	unsigned int nStatusSubDL; // 0x164
	unsigned int nNumZSortLights; // 0x168
	int aLightAddresses[8]; // 0x16C
	int nAmbientLightAddress; // 0x18C
	__anon_0x28F3E aZSortVertex[128]; // 0x190
	__anon_0x29056 aZSortNormal[128]; // 0xB90
	__anon_0x290D5 aZSortMaterial[128]; // 0xD10
	__anon_0x29178 aZSortMatrix[128]; // 0xF10
	__anon_0x291D6 aZSortLight[8]; // 0x2F10
	int aZSortInvW[128]; // 0x2F40
	signed short aZSortWiVal[128]; // 0x3140
	unsigned int nNumZSortMatrices; // 0x3240
	unsigned int nNumZSortVertices; // 0x3244
	unsigned int nTotalZSortVertices; // 0x3248
	unsigned int nNumZSortNormals; // 0x324C
	unsigned int nNumZSortMaterials; // 0x3250
	int anAudioBaseSegment[16]; // 0x3254
	signed short *anAudioBuffer; // 0x3294
	signed short anADPCMCoef[5][2][8]; // 0x3298
	unsigned short nAudioDMOutR[2]; // 0x3338
	unsigned short nAudioDMauxL[2]; // 0x333C
	unsigned short nAudioDMauxR[2]; // 0x3340
	unsigned short nAudioCount[2]; // 0x3344
	unsigned short nAudioFlags; // 0x3348
	unsigned short nAudioDMEMIn[2]; // 0x334A
	unsigned short nAudioDMEMOut[2]; // 0x334E
	unsigned int nAudioLoopAddress; // 0x3354
	unsigned int nAudioDryAmt; // 0x3358
	unsigned int nAudioWetAmt; // 0x335C
	unsigned int nAudioVolL; // 0x3360
	unsigned int nAudioVolR; // 0x3364
	unsigned int nAudioVolTGTL; // 0x3368
	unsigned int nAudioVolRateLM; // 0x336C
	unsigned int nAudioVolRateLL; // 0x3370
	unsigned int nAudioVolTGTR; // 0x3374
	unsigned int nAudioVolRateRM; // 0x3378
	unsigned int nAudioVolRateRL; // 0x337C
	__anon_0x29487 vParams; // 0x3380
	signed short stepF; // 0x3390
	signed short stepL; // 0x3392
	signed short stepR; // 0x3394
	int anGenReg[32]; // 0x3398
	__anon_0x29487 aVectorReg[32]; // 0x3418
	int anCP0Reg[32]; // 0x3618
	__anon_0x29487 anCP2Reg[32]; // 0x3698
	signed short anAcc[24]; // 0x3898
	signed short nVCC; // 0x38C8
	signed short nVC0; // 0x38CA
	char nVCE; // 0x38CC
	__anon_0x29567 eTypeAudioUCode; // 0x38D0
	unsigned short nAudioMemOffset; // 0x38D4
	unsigned short nAudioADPCMOffset; // 0x38D6
	unsigned short nAudioScratchOffset; // 0x38D8
	unsigned short nAudioParBase; // 0x38DA
	int nPC; // 0x38DC
	int iDL; // 0x38E0
	int nBIST; // 0x38E4
	void *pHost; // 0x38E8
	void *pDMEM; // 0x38EC
	void *pIMEM; // 0x38F0
	int nStatus; // 0x38F4
	int nFullDMA; // 0x38F8
	int nBusyDMA; // 0x38FC
	int nSizeGet; // 0x3900
	int nSizePut; // 0x3904
	int nSemaphore; // 0x3908
	int nAddressSP; // 0x390C
	int nGeometryMode; // 0x3910
	int nAddressRDRAM; // 0x3914
	tXL_LIST *pListUCode; // 0x3918
	int nCountVertex; // 0x391C
	__anon_0x28AC5 eTypeUCode; // 0x3920
	unsigned int nVersionUCode; // 0x3924
	int anBaseSegment[16]; // 0x3928
	unsigned long long  *apDL[16]; // 0x3968
	int *Coeff; // 0x39A8
	signed short *QTable; // 0x39AC
	signed short *QYTable; // 0x39B0
	signed short *QCbTable; // 0x39B4
	signed short *QCrTable; // 0x39B8
	int *Zigzag; // 0x39BC
	__anon_0x296E2 *rgbaBuf; // 0x39C0
	__anon_0x29770 *yuvBuf; // 0x39C4
	int *dctBuf; // 0x39C8
};

// size: 0x28
struct __anon_0x2A6F7
{
	unsigned short imageX; // 0x0
	unsigned short imageW; // 0x2
	signed short frameX; // 0x4
	unsigned short frameW; // 0x6
	unsigned short imageY; // 0x8
	unsigned short imageH; // 0xA
	signed short frameY; // 0xC
	unsigned short frameH; // 0xE
	unsigned int imagePtr; // 0x10
	unsigned short imageLoad; // 0x14
	unsigned char imageFmt; // 0x16
	unsigned char imageSiz; // 0x17
	unsigned short imagePal; // 0x18
	unsigned short imageFlip; // 0x1A
	unsigned short tmemW; // 0x1C
	unsigned short tmemH; // 0x1E
	unsigned short tmemLoadSH; // 0x20
	unsigned short tmemLoadTH; // 0x22
	unsigned short tmemSizeW; // 0x24
	unsigned short tmemSize; // 0x26
};

// size: 0x28
struct __anon_0x2AA02
{
	unsigned short imageX; // 0x0
	unsigned short imageW; // 0x2
	signed short frameX; // 0x4
	unsigned short frameW; // 0x6
	unsigned short imageY; // 0x8
	unsigned short imageH; // 0xA
	signed short frameY; // 0xC
	unsigned short frameH; // 0xE
	unsigned int imagePtr; // 0x10
	unsigned short imageLoad; // 0x14
	unsigned char imageFmt; // 0x16
	unsigned char imageSiz; // 0x17
	unsigned short imagePal; // 0x18
	unsigned short imageFlip; // 0x1A
	unsigned short scaleW; // 0x1C
	unsigned short scaleH; // 0x1E
	int imageYorig; // 0x20
	unsigned char padding[4]; // 0x24
};

// size: 0x28
union __anon_0x2ACA3
{
	__anon_0x2A6F7 b; // 0x0
	__anon_0x2AA02 s; // 0x0
	signed long long force_structure_alignment; // 0x0
};

// size: 0x18
struct __anon_0x2AD2F
{
	unsigned int type; // 0x0
	unsigned int image; // 0x4
	unsigned short tmem; // 0x8
	unsigned short tsize; // 0xA
	unsigned short tline; // 0xC
	unsigned short sid; // 0xE
	unsigned int flag; // 0x10
	unsigned int mask; // 0x14
};

// size: 0x18
struct __anon_0x2AE4F
{
	unsigned int type; // 0x0
	unsigned int image; // 0x4
	unsigned short tmem; // 0x8
	unsigned short twidth; // 0xA
	unsigned short theight; // 0xC
	unsigned short sid; // 0xE
	unsigned int flag; // 0x10
	unsigned int mask; // 0x14
};

// size: 0x18
struct __anon_0x2AF72
{
	unsigned int type; // 0x0
	unsigned int image; // 0x4
	unsigned short phead; // 0x8
	unsigned short pnum; // 0xA
	unsigned short zero; // 0xC
	unsigned short sid; // 0xE
	unsigned int flag; // 0x10
	unsigned int mask; // 0x14
};

// size: 0x18
union __anon_0x2B091
{
	__anon_0x2AD2F block; // 0x0
	__anon_0x2AE4F tile; // 0x0
	__anon_0x2AF72 tlut; // 0x0
	signed long long force_structure_alignment; // 0x0
};

// size: 0x4
struct _GXColor
{
	unsigned char r; // 0x0
	unsigned char g; // 0x1
	unsigned char b; // 0x2
	unsigned char a; // 0x3
};

// Location: 0x80135A8C
void *DemoCurrentBuffer;

// Location: 0x80135A94
void *DemoFrameBuffer1;

// Location: 0x80135A90
void *DemoFrameBuffer2;

// size: 0x8
struct __anon_0x2B2A7
{
	int nOffsetHost; // 0x0
	int nAddressN64; // 0x4
};

// size: 0x8
struct cpu_callerID
{
	int N64address; // 0x0
	int GCNaddress; // 0x4
};

// size: 0x48
struct cpu_function
{
	void *pnBase; // 0x0
	void *pfCode; // 0x4
	int nCountJump; // 0x8
	__anon_0x2B2A7 *aJump; // 0xC
	int nAddress0; // 0x10
	int nAddress1; // 0x14
	cpu_callerID *block; // 0x18
	int callerID_total; // 0x1C
	int callerID_flag; // 0x20
	unsigned int nChecksum; // 0x24
	int timeToLive; // 0x28
	int memory_size; // 0x2C
	int heapID; // 0x30
	int heapWhere; // 0x34
	int treeheapWhere; // 0x38
	cpu_function *prev; // 0x3C
	cpu_function *left; // 0x40
	cpu_function *right; // 0x44
};

// size: 0x8
union __anon_0x2B65C
{
	char _0s8; // 0x0
	char _1s8; // 0x1
	char _2s8; // 0x2
	char _3s8; // 0x3
	char _4s8; // 0x4
	char _5s8; // 0x5
	char _6s8; // 0x6
	char s8; // 0x7
	signed short _0s16; // 0x0
	signed short _1s16; // 0x2
	signed short _2s16; // 0x4
	signed short s16; // 0x6
	int _0s32; // 0x0
	int s32; // 0x4
	signed long long s64; // 0x0
	unsigned char _0u8; // 0x0
	unsigned char _1u8; // 0x1
	unsigned char _2u8; // 0x2
	unsigned char _3u8; // 0x3
	unsigned char _4u8; // 0x4
	unsigned char _5u8; // 0x5
	unsigned char _6u8; // 0x6
	unsigned char u8; // 0x7
	unsigned short _0u16; // 0x0
	unsigned short _1u16; // 0x2
	unsigned short _2u16; // 0x4
	unsigned short u16; // 0x6
	unsigned int _0u32; // 0x0
	unsigned int u32; // 0x4
	unsigned long long u64; // 0x0
};

// size: 0x8
union __anon_0x2BA70
{
	float _0f32; // 0x0
	float f32; // 0x4
	long float f64; // 0x0
	int _0s32; // 0x0
	int s32; // 0x4
	signed long long s64; // 0x0
	unsigned int _0u32; // 0x0
	unsigned int u32; // 0x4
	unsigned long long u64; // 0x0
};

// size: 0x34
struct __anon_0x2BF7E
{
	int nType; // 0x0
	void *pObject; // 0x4
	int nOffsetAddress; // 0x8
	int (*pfGet8)(void */* unknown0 */, unsigned int /* unknown1 */, char */* unknown2 */); // 0xC
	int (*pfGet16)(void */* unknown0 */, unsigned int /* unknown1 */, signed short */* unknown2 */); // 0x10
	int (*pfGet32)(void */* unknown0 */, unsigned int /* unknown1 */, int */* unknown2 */); // 0x14
	int (*pfGet64)(void */* unknown0 */, unsigned int /* unknown1 */, signed long long */* unknown2 */); // 0x18
	int (*pfPut8)(void */* unknown0 */, unsigned int /* unknown1 */, char */* unknown2 */); // 0x1C
	int (*pfPut16)(void */* unknown0 */, unsigned int /* unknown1 */, signed short */* unknown2 */); // 0x20
	int (*pfPut32)(void */* unknown0 */, unsigned int /* unknown1 */, int */* unknown2 */); // 0x24
	int (*pfPut64)(void */* unknown0 */, unsigned int /* unknown1 */, signed long long */* unknown2 */); // 0x28
	unsigned int nAddressPhysical0; // 0x2C
	unsigned int nAddressPhysical1; // 0x30
};

// size: 0x84
struct cpu_treeRoot
{
	unsigned short total; // 0x0
	int total_memory; // 0x4
	int root_address; // 0x8
	int start_range; // 0xC
	int end_range; // 0x10
	int cache_miss; // 0x14
	int cache[20]; // 0x18
	cpu_function *left; // 0x68
	cpu_function *right; // 0x6C
	int kill_limit; // 0x70
	int kill_number; // 0x74
	int side; // 0x78
	cpu_function *restore; // 0x7C
	int restore_side; // 0x80
};

// size: 0xC
struct _CPU_ADDRESS
{
	int nN64; // 0x0
	int nHost; // 0x4
	cpu_function *pFunction; // 0x8
};

// size: 0xC
struct __anon_0x2C542
{
	unsigned int nAddress; // 0x0
	unsigned int nOpcodeOld; // 0x4
	unsigned int nOpcodeNew; // 0x8
};

// size: 0x2C8
struct OSContext
{
	unsigned long gpr[32]; // 0x0
	unsigned long cr; // 0x80
	unsigned long lr; // 0x84
	unsigned long ctr; // 0x88
	unsigned long xer; // 0x8C
	long float fpr[32]; // 0x90
	unsigned long fpscr_pad; // 0x190
	unsigned long fpscr; // 0x194
	unsigned long srr0; // 0x198
	unsigned long srr1; // 0x19C
	unsigned short mode; // 0x1A0
	unsigned short state; // 0x1A2
	unsigned long gqr[8]; // 0x1A4
	unsigned long psf_pad; // 0x1C4
	long float psf[32]; // 0x1C8
};

// size: 0x28
struct OSAlarm
{
	void (*handler)(OSAlarm */* unknown0 */, OSContext */* unknown1 */); // 0x0
	unsigned long tag; // 0x4
	signed long long fire; // 0x8
	OSAlarm *prev; // 0x10
	OSAlarm *next; // 0x14
	signed long long period; // 0x18
	signed long long start; // 0x20
};

// size: 0x28
struct cpu_optimize
{
	unsigned int validCheck; // 0x0
	unsigned int destGPR_check; // 0x4
	int destGPR; // 0x8
	int destGPR_mapping; // 0xC
	unsigned int destFPR_check; // 0x10
	int destFPR; // 0x14
	unsigned int addr_check; // 0x18
	int addr_last; // 0x1C
	unsigned int checkType; // 0x20
	unsigned int checkNext; // 0x24
};

// size: 0x12090
struct _CPU
{
	int nMode; // 0x0
	int nTick; // 0x4
	void *pHost; // 0x8
	signed long long nLo; // 0x10
	signed long long nHi; // 0x18
	int nCountAddress; // 0x20
	int iDeviceDefault; // 0x24
	unsigned int nPC; // 0x28
	unsigned int nWaitPC; // 0x2C
	unsigned int nCallLast; // 0x30
	cpu_function *pFunctionLast; // 0x34
	int nReturnAddrLast; // 0x38
	int survivalTimer; // 0x3C
	__anon_0x2B65C aGPR[32]; // 0x40
	__anon_0x2BA70 aFPR[32]; // 0x140
	unsigned long long aTLB[48][5]; // 0x240
	int anFCR[32]; // 0x9C0
	signed long long anCP0[32]; // 0xA40
	int (*pfStep)(_CPU */* unknown0 */); // 0xB40
	int (*pfJump)(_CPU */* unknown0 */); // 0xB44
	int (*pfCall)(_CPU */* unknown0 */); // 0xB48
	int (*pfIdle)(_CPU */* unknown0 */); // 0xB4C
	int (*pfRam)(_CPU */* unknown0 */); // 0xB50
	int (*pfRamF)(_CPU */* unknown0 */); // 0xB54
	unsigned int nTickLast; // 0xB58
	unsigned int nRetrace; // 0xB5C
	unsigned int nRetraceUsed; // 0xB60
	__anon_0x2BF7E *apDevice[256]; // 0xB64
	unsigned char aiDevice[65536]; // 0xF64
	void *gHeap1; // 0x10F64
	void *gHeap2; // 0x10F68
	unsigned int aHeap1Flag[192]; // 0x10F6C
	unsigned int aHeap2Flag[13]; // 0x1126C
	cpu_treeRoot *gTree; // 0x112A0
	_CPU_ADDRESS aAddressCache[256]; // 0x112A4
	int nCountCodeHack; // 0x11EA4
	__anon_0x2C542 aCodeHack[32]; // 0x11EA8
	signed long long nTimeRetrace; // 0x12028
	OSAlarm alarmRetrace; // 0x12030
	unsigned int nFlagRAM; // 0x12058
	unsigned int nFlagCODE; // 0x1205C
	unsigned int nCompileFlag; // 0x12060
	cpu_optimize nOptimize; // 0x12064
};

// size: 0x4
enum __anon_0x2D223
{
	FCT_NONE = 4294967295,
	FCT_FOG = 0,
	FCT_FILL = 1,
	FCT_BLEND = 2,
	FCT_PRIMITIVE = 3,
	FCT_ENVIRONMENT = 4,
	FCT_COUNT = 5
};

// size: 0x28
struct __anon_0x2D2B6
{
	int bFlip; // 0x0
	int iTile; // 0x4
	int nX0; // 0x8
	int nY0; // 0xC
	int nX1; // 0x10
	int nY1; // 0x14
	float rS; // 0x18
	float rT; // 0x1C
	float rDeltaS; // 0x20
	float rDeltaT; // 0x24
};

// size: 0x304
struct __anon_0x2D45B
{
	int nCount; // 0x0
	unsigned char anData[768]; // 0x4
};

// size: 0x4
enum _GXTevAlphaArg
{
	GX_CA_APREV = 0,
	GX_CA_A0 = 1,
	GX_CA_A1 = 2,
	GX_CA_A2 = 3,
	GX_CA_TEXA = 4,
	GX_CA_RASA = 5,
	GX_CA_KONST = 6,
	GX_CA_ZERO = 7,
	GX_CA_ONE = 6
};

// size: 0x4
enum _GXTevColorArg
{
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
	GX_CC_QUARTER = 14
};

// size: 0x4
enum _GXProjectionType
{
	GX_PERSPECTIVE = 0,
	GX_ORTHOGRAPHIC = 1
};

// size: 0x4
enum _GXTexWrapMode
{
	GX_CLAMP = 0,
	GX_REPEAT = 1,
	GX_MIRROR = 2,
	GX_MAX_TEXWRAPMODE = 3
};

// size: 0x14
struct _GXFogAdjTable
{
	unsigned short r[10]; // 0x0
};

// size: 0x4
enum _GXFogType
{
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
	GX_FOG_REVEXP2 = 7
};

int frameUpdateTrackBuffer();

int frameCheckTrackBuffer();

int frameSetupTrackBuffer();

// Local to compilation unit
static int frameLoadTile(__anon_0x24C38 *pFrame, _FRAME_TEXTURE **ppTexture, int iTileCode)
{
	int bFlag;
	__anon_0x247BF *pTile;
	_FRAME_TEXTURE *pTexture;
	_FRAME_TEXTURE *pTextureLast;
	unsigned int nData0;
	unsigned int nData1;
	unsigned int nData2;
	unsigned int nData3;
	int iTexture;
	int nShift;
}

int frameMultiTexture(__anon_0x24C38 *pFrame)
{
	int iMode;
	int iType;
	int nMode;
	int nUsed;
}

// Local to compilation unit
static int frameUpdateCache(__anon_0x24C38 *pFrame)
{
	int nCount;
	int nCountFree;
	unsigned int nMask;
	int nFrameCount;
	int nFrameDelta;
	int iTexture;
	int iTextureUsed;
	int iTextureCached;
	_FRAME_TEXTURE *pTexture;
	_FRAME_TEXTURE *pTextureCached;
	_FRAME_TEXTURE *pTextureLast;
}

int frameResetCache(__anon_0x24C38 *pFrame);

// Local to compilation unit
static int frameSetupCache(__anon_0x24C38 *pFrame)
{
	int iTexture;
}

int frameFreeTexture(__anon_0x24C38 *pFrame, _FRAME_TEXTURE *pTexture)
{
	int iTexture;
}

// Local to compilation unit
static int frameMakeTexture(__anon_0x24C38 *pFrame, _FRAME_TEXTURE **ppTexture)
{
	unsigned int nMask;
	int iTexture;
	int iTextureUsed;
}

int packReset(unsigned int *anPack, int nPackCount)
{
	int iPack;
}

// Local to compilation unit
static int packFreeBlocks(int *piPack, unsigned int *anPack)
{
	int iPack;
	unsigned int nMask;
}

// Local to compilation unit
static int packTakeBlocks(int *piPack, unsigned int *anPack, int nPackCount, int nBlockCount)
{
	int nOffset;
	int nCount;
	int iPack;
	unsigned int nPack;
	unsigned int nMask;
	unsigned int nMask0;
}

// Local to compilation unit
static int frameConvertYUVtoRGB(unsigned int *YUV, unsigned int *RGB)
{
	long Yl;
	int R;
	int G;
	int B;
}

int frameConcatenateMatrix(float *matrixResult[4], float *matrixA[4], float *matrixB[4]);

int frameScaleMatrix(float *matrixResult[4], float *matrix[4], float rScale);

int frameVectorTimesMatrix(float *fOutVector, float *fInVector, float *matrix[4]);

