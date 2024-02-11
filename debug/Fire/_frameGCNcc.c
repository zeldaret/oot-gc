// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

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

// Location: 0x58010F80
_GXTevColorArg gCombinedColor[16];

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

// Location: 0x800F0198
_GXTevAlphaArg gCombinedAlpha[8];

// size: 0x4
enum _GXTevStageID
{
	GX_TEVSTAGE0 = 0,
	GX_TEVSTAGE1 = 1,
	GX_TEVSTAGE2 = 2,
	GX_TEVSTAGE3 = 3,
	GX_TEVSTAGE4 = 4,
	GX_TEVSTAGE5 = 5,
	GX_TEVSTAGE6 = 6,
	GX_TEVSTAGE7 = 7,
	GX_TEVSTAGE8 = 8,
	GX_TEVSTAGE9 = 9,
	GX_TEVSTAGE10 = 10,
	GX_TEVSTAGE11 = 11,
	GX_TEVSTAGE12 = 12,
	GX_TEVSTAGE13 = 13,
	GX_TEVSTAGE14 = 14,
	GX_TEVSTAGE15 = 15,
	GX_MAX_TEVSTAGE = 16
};

// Local to compilation unit
// Location: 0x800F01B8
static _GXTevStageID ganNameTevStage[16];

// Local to compilation unit
// Location: 0x70531380
static unsigned char sOrder[5];

// size: 0x4
enum _GXTevOp
{
	GX_TEV_ADD = 0,
	GX_TEV_SUB = 1,
	GX_TEV_COMP_R8_GT = 8,
	GX_TEV_COMP_R8_EQ = 9,
	GX_TEV_COMP_GR16_GT = 10,
	GX_TEV_COMP_GR16_EQ = 11,
	GX_TEV_COMP_BGR24_GT = 12,
	GX_TEV_COMP_BGR24_EQ = 13,
	GX_TEV_COMP_RGB8_GT = 14,
	GX_TEV_COMP_RGB8_EQ = 15,
	GX_TEV_COMP_A8_GT = 14,
	GX_TEV_COMP_A8_EQ = 15
};

// size: 0x4
enum _GXTevBias
{
	GX_TB_ZERO = 0,
	GX_TB_ADDHALF = 1,
	GX_TB_SUBHALF = 2,
	GX_MAX_TEVBIAS = 3
};

// size: 0x4
enum _GXTevScale
{
	GX_CS_SCALE_1 = 0,
	GX_CS_SCALE_2 = 1,
	GX_CS_SCALE_4 = 2,
	GX_CS_DIVIDE_2 = 3,
	GX_MAX_TEVSCALE = 4
};

// size: 0x4
enum _GXTevRegID
{
	GX_TEVPREV = 0,
	GX_TEVREG0 = 1,
	GX_TEVREG1 = 2,
	GX_TEVREG2 = 3,
	GX_MAX_TEVREG = 4
};

// size: 0x14
struct TevColorOp
{
	_GXTevOp op; // 0x0
	_GXTevBias bias; // 0x4
	_GXTevScale scale; // 0x8
	unsigned char clamp; // 0xC
	_GXTevRegID out_reg; // 0x10
};

// Local to compilation unit
// Location: 0x800F01F8
static TevColorOp sTevColorOp[5];

// Local to compilation unit
// Location: 0x78531380
static unsigned char sReplace[5];

// Local to compilation unit
// Location: 0x5C020F80
static _GXTevColorArg sTevColorArg[5][4];

// Local to compilation unit
// Location: 0x800F02AC
static _GXTevAlphaArg sTevAlphaArg[5][4];

// Location: 0x0
unsigned long sCurCCMode;

// Location: 0x0
unsigned long sPrevCCModes[100][2][2];

// Local to compilation unit
// Location: 0x800F0390
static char  *sColorNames[16];

// Local to compilation unit
// Location: 0x800F03D0
static char  *sAlphaNames[2][8];

// Location: 0x0
unsigned long sFoundRenderModes$277[100];

// Location: 0x0
long sCurRenderMode$278;

// Local to compilation unit
// Location: 0x10040F80
static char  *strings$288[4][4];

// Location: 0x0
unsigned char sMemShift$301[2][4];

void UpdateRenderModeList(unsigned long renderMode, unsigned long cycle)
{
	long i;
	unsigned long p[2][4];
	// References: sCurRenderMode$278 (0x0)
	// References: sFoundRenderModes$277 (0x0)
	// References: strings$288 (0x10040F80)
	// References: sMemShift$301 (0x0)
}

// size: 0x4
enum __anon_0x8573D
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

// size: 0x10
struct __anon_0x857A7
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x85858
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
enum __anon_0x8598C
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
struct __anon_0x85ACF
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x8573D eMode; // 0xC
	__anon_0x857A7 romCopy; // 0x10
	__anon_0x85858 eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x8598C storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// Location: 0x561380
__anon_0x85ACF *gpSystem;

// size: 0x10
struct __anon_0x85D00
{
	float rX; // 0x0
	float rY; // 0x4
	float rSizeX; // 0x8
	float rSizeY; // 0xC
};

// size: 0x14
struct __anon_0x85D9A
{
	int nSize; // 0x0
	int nWidth; // 0x4
	int nFormat; // 0x8
	void *pData; // 0xC
	int nAddress; // 0x10
};

// size: 0xC
struct __anon_0x85EDB
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
};

// size: 0x3C
struct __anon_0x85F4B
{
	int bTransformed; // 0x0
	__anon_0x85EDB rVecOrigTowards; // 0x4
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
struct __anon_0x8617B
{
	int bTransformed; // 0x0
	__anon_0x85EDB rS; // 0x4
	__anon_0x85EDB rT; // 0x10
	__anon_0x85EDB rSRaw; // 0x1C
	__anon_0x85EDB rTRaw; // 0x28
};

// size: 0x1C
struct __anon_0x86264
{
	float rSum; // 0x0
	float rS; // 0x4
	float rT; // 0x8
	__anon_0x85EDB vec; // 0xC
	unsigned char anColor[4]; // 0x18
};

// size: 0x1000
union __anon_0x863C3
{
	unsigned char u8[4096]; // 0x0
	unsigned short u16[2048]; // 0x0
	unsigned int u32[1024]; // 0x0
	unsigned long long u64[512]; // 0x0
};

// size: 0x1000
struct __anon_0x86460
{
	__anon_0x863C3 data; // 0x0
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

// size: 0x20
struct _GXTexObj
{
	unsigned long dummy[8]; // 0x0
};

// size: 0x4
enum _GXTexWrapMode
{
	GX_CLAMP = 0,
	GX_REPEAT = 1,
	GX_MIRROR = 2,
	GX_MAX_TEXWRAPMODE = 3
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
struct __anon_0x86B2E
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

// size: 0x4
enum __anon_0x86E10
{
	FMP_NONE = 4294967295,
	FMP_PERSPECTIVE = 0,
	FMP_ORTHOGRAPHIC = 1
};

// size: 0x24
struct __anon_0x86E99
{
	int nCount; // 0x0
	float rScale; // 0x4
	float rAspect; // 0x8
	float rFieldOfViewY; // 0xC
	float rClipNear; // 0x10
	float rClipFar; // 0x14
	unsigned int nAddressFloat; // 0x18
	unsigned int nAddressFixed; // 0x1C
	__anon_0x86E10 eProjection; // 0x20
};

// size: 0x3D150
struct __anon_0x87050
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
	__anon_0x85D00 viewport; // 0xB8
	__anon_0x85D9A aBuffer[4]; // 0xC8
	unsigned int nOffsetDepth0; // 0x118
	unsigned int nOffsetDepth1; // 0x11C
	int nWidthLine; // 0x120
	float rDepth; // 0x124
	float rDelta; // 0x128
	int (*aDraw[4])(void */* unknown0 */, void */* unknown1 */); // 0x12C
	int nCountLight; // 0x13C
	__anon_0x85F4B aLight[8]; // 0x140
	__anon_0x8617B lookAt; // 0x320
	int nCountVertex; // 0x354
	__anon_0x86264 aVertex[80]; // 0x358
	__anon_0x86460 TMEM; // 0xC18
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
	__anon_0x86B2E aTile[8]; // 0x3C358
	int anSizeX[2]; // 0x3C4B8
	int anSizeY[2]; // 0x3C4C0
	int iHintMatrix; // 0x3C4C8
	int iMatrixModel; // 0x3C4CC
	int iHintProjection; // 0x3C4D0
	float matrixView[4][4]; // 0x3C4D4
	int iHintLast; // 0x3C514
	int iHintHack; // 0x3C518
	__anon_0x86E10 eTypeProjection; // 0x3C51C
	float aMatrixModel[10][4][4]; // 0x3C520
	float matrixProjection[4][4]; // 0x3C7A0
	float matrixProjectionExtra[4][4]; // 0x3C7E0
	__anon_0x86E99 aMatrixHint[64]; // 0x3C820
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

// size: 0x4
enum _GXChannelID
{
	GX_COLOR0 = 0,
	GX_COLOR1 = 1,
	GX_ALPHA0 = 2,
	GX_ALPHA1 = 3,
	GX_COLOR0A0 = 4,
	GX_COLOR1A1 = 5,
	GX_COLOR_ZERO = 6,
	GX_ALPHA_BUMP = 7,
	GX_ALPHA_BUMPN = 8,
	GX_COLOR_NULL = 255
};

// size: 0xC
struct TevOrder
{
	_GXTexCoordID coordID; // 0x0
	_GXTexMapID mapID; // 0x4
	_GXChannelID chanID; // 0x8
};

// size: 0x2B8
struct CombineModeTev
{
	unsigned long ccCodes[2][2]; // 0x0
	unsigned char numCycles; // 0x10
	unsigned char numStages; // 0x11
	unsigned char numTexGen; // 0x12
	unsigned char numChan; // 0x13
	unsigned long flags; // 0x14
	TevOrder tevOrder[8]; // 0x18
	TevColorOp tevColorOpP[8][2]; // 0x78
	_GXTevColorArg tevColorArg[8][4]; // 0x1B8
	_GXTevAlphaArg tevAlphaArg[8][4]; // 0x238
};

long SetTevStageTable(__anon_0x87050 *pFrame, long numCycles)
{
	unsigned long tempColor1;
	unsigned long tempAlpha1;
	unsigned long tempColor2;
	unsigned long tempAlpha2;
	CombineModeTev *ctP;
	// References: gpSystem (0x561380)
}

// Location: 0x800EA8B8
_GXTexCoordID ganNameTexCoord[];

// Location: 0x78A80E80
_GXTexMapID ganNamePixel[];

void SetTevStages(__anon_0x87050 *pFrame, int cycle)
{
	unsigned char nColor[4];
	unsigned char nAlpha[4];
	unsigned int tempColor;
	unsigned int tempAlpha;
	_GXTevColorArg colorArg[4];
	_GXTevAlphaArg alphaArg[4];
	_GXTevStageID tevStages[5];
	TevColorOp *tP;
	long j;
	_GXTevColorArg *cArgP;
	_GXTevAlphaArg *aArgP;
	long i;
	long order;
	// References: sTevAlphaArg (0x800F02AC)
	// References: sTevColorArg (0x5C020F80)
	// References: sTevColorOp (0x800F01F8)
	// References: sOrder (0x70531380)
	// References: sReplace (0x78531380)
	// References: gCombinedAlpha (0x800F0198)
	// References: gCombinedColor (0x58010F80)
	// References: ganNamePixel (0x78A80E80)
	// References: ganNameTexCoord (0x800EA8B8)
	// References: ganNameTevStage (0x800F01B8)
}

void SetNumTexGensChans(__anon_0x87050 *pFrame, int numCycles)
{
	unsigned char nColor[4];
	unsigned char nAlpha[4];
	unsigned long tempColor;
	unsigned long tempAlpha;
	long i;
	long j;
	long numGens;
	long numChans;
}

void CheckNewCCMode(__anon_0x87050 *pFrame, long numCycles)
{
	long i;
	unsigned long tempColor1;
	unsigned long tempAlpha1;
	unsigned long tempColor2;
	unsigned long tempAlpha2;
	// References: sCurCCMode (0x0)
	// References: sPrevCCModes (0x0)
}

void OutputCCMode(int cycle, unsigned long tempColor, unsigned long tempAlpha)
{
	long i;
	unsigned char nColor[4];
	unsigned char nAlpha[4];
	// References: sAlphaNames (0x800F03D0)
	// References: sColorNames (0x800F0390)
}

// size: 0x4
struct _GXColor
{
	unsigned char r; // 0x0
	unsigned char g; // 0x1
	unsigned char b; // 0x2
	unsigned char a; // 0x3
};

// Local to compilation unit
static void SetTableTevStages(__anon_0x87050 *pFrame, CombineModeTev *ctP)
{
	long i;
	int iStart;
	_GXColor color;
	TevOrder *toP;
	TevColorOp *tcP;
	_GXTevColorArg *cArgP;
	_GXTevAlphaArg *aArgP;
	// References: ganNameTevStage (0x800F01B8)
}

