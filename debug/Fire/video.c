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

// Location: 0x70E80E80
_XL_OBJECTTYPE gClassVideo;

// size: 0x40
struct __anon_0x75B37
{
	int nScan; // 0x0
	int bBlack; // 0x4
	int nBurst; // 0x8
	int nSizeX; // 0xC
	void *pHost; // 0x10
	int nStatus; // 0x14
	int nTiming; // 0x18
	int nAddress; // 0x1C
	int nScanInterrupt; // 0x20
	int nScaleX; // 0x24
	int nScaleY; // 0x28
	int nStartH; // 0x2C
	int nStartV; // 0x30
	int nSyncH; // 0x34
	int nSyncV; // 0x38
	int nSyncLeap; // 0x3C
};

int videoEvent(__anon_0x75B37 *pVideo, int nEvent, void *pArgument);

int videoGetMode(__anon_0x75B37 *pVideo, int *pbBlack, int *pnSizeX, int *pnSizeY)
{
	int nSizeX;
	int nSizeY;
}

int videoForceRetrace(__anon_0x75B37 *pVideo);

int videoTickScan();

int videoGet64();

int videoGet32(__anon_0x75B37 *pVideo, unsigned int nAddress, int *pData);

int videoGet16();

int videoGet8();

int videoPut64();

// size: 0x10
struct __anon_0x76165
{
	float rX; // 0x0
	float rY; // 0x4
	float rSizeX; // 0x8
	float rSizeY; // 0xC
};

// size: 0x14
struct __anon_0x761FF
{
	int nSize; // 0x0
	int nWidth; // 0x4
	int nFormat; // 0x8
	void *pData; // 0xC
	int nAddress; // 0x10
};

// size: 0xC
struct __anon_0x76340
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
};

// size: 0x3C
struct __anon_0x763B0
{
	int bTransformed; // 0x0
	__anon_0x76340 rVecOrigTowards; // 0x4
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
struct __anon_0x765E0
{
	int bTransformed; // 0x0
	__anon_0x76340 rS; // 0x4
	__anon_0x76340 rT; // 0x10
	__anon_0x76340 rSRaw; // 0x1C
	__anon_0x76340 rTRaw; // 0x28
};

// size: 0x1C
struct __anon_0x766C9
{
	float rSum; // 0x0
	float rS; // 0x4
	float rT; // 0x8
	__anon_0x76340 vec; // 0xC
	unsigned char anColor[4]; // 0x18
};

// size: 0x1000
union __anon_0x76828
{
	unsigned char u8[4096]; // 0x0
	unsigned short u16[2048]; // 0x0
	unsigned int u32[1024]; // 0x0
	unsigned long long u64[512]; // 0x0
};

// size: 0x1000
struct __anon_0x768C5
{
	__anon_0x76828 data; // 0x0
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
struct __anon_0x76F93
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
enum __anon_0x77275
{
	FMP_NONE = 4294967295,
	FMP_PERSPECTIVE = 0,
	FMP_ORTHOGRAPHIC = 1
};

// size: 0x24
struct __anon_0x772F8
{
	int nCount; // 0x0
	float rScale; // 0x4
	float rAspect; // 0x8
	float rFieldOfViewY; // 0xC
	float rClipNear; // 0x10
	float rClipFar; // 0x14
	unsigned int nAddressFloat; // 0x18
	unsigned int nAddressFixed; // 0x1C
	__anon_0x77275 eProjection; // 0x20
};

// size: 0x4
struct _GXColor
{
	unsigned char r; // 0x0
	unsigned char g; // 0x1
	unsigned char b; // 0x2
	unsigned char a; // 0x3
};

// size: 0x3D150
struct __anon_0x77548
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
	__anon_0x76165 viewport; // 0xB8
	__anon_0x761FF aBuffer[4]; // 0xC8
	unsigned int nOffsetDepth0; // 0x118
	unsigned int nOffsetDepth1; // 0x11C
	int nWidthLine; // 0x120
	float rDepth; // 0x124
	float rDelta; // 0x128
	int (*aDraw[4])(void */* unknown0 */, void */* unknown1 */); // 0x12C
	int nCountLight; // 0x13C
	__anon_0x763B0 aLight[8]; // 0x140
	__anon_0x765E0 lookAt; // 0x320
	int nCountVertex; // 0x354
	__anon_0x766C9 aVertex[80]; // 0x358
	__anon_0x768C5 TMEM; // 0xC18
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
	__anon_0x76F93 aTile[8]; // 0x3C358
	int anSizeX[2]; // 0x3C4B8
	int anSizeY[2]; // 0x3C4C0
	int iHintMatrix; // 0x3C4C8
	int iMatrixModel; // 0x3C4CC
	int iHintProjection; // 0x3C4D0
	float matrixView[4][4]; // 0x3C4D4
	int iHintLast; // 0x3C514
	int iHintHack; // 0x3C518
	__anon_0x77275 eTypeProjection; // 0x3C51C
	float aMatrixModel[10][4][4]; // 0x3C520
	float matrixProjection[4][4]; // 0x3C7A0
	float matrixProjectionExtra[4][4]; // 0x3C7E0
	__anon_0x772F8 aMatrixHint[64]; // 0x3C820
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

int videoPut32(__anon_0x75B37 *pVideo, unsigned int nAddress, int *pData)
{
	void *pRAM;
	__anon_0x77548 *pFrame;
	__anon_0x761FF *pBuffer;
}

int videoPut16();

int videoPut8();

