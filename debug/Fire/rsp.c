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

// Location: 0x20E20E80
_XL_OBJECTTYPE gClassRSP;

// Location: 0x0
unsigned short rsp_VCO;

// Location: 0x0
unsigned short rsp_VCC;

// Location: 0x0
unsigned char rsp_VCE;

// Location: 0x0
unsigned char vco_carry[8];

// Location: 0x0
unsigned char vco_equal[8];

// Location: 0x30E20E80
int cmask_tab[8];

// Location: 0x50E20E80
int emask_tab[8];

// Location: 0x0
int bSoundDebugOutput;

// Local to compilation unit
// Location: 0x801352C4
static int nFirstTime$2148;

// Location: 0x0
unsigned int nTimesCalled$2403;

// Local to compilation unit
// Location: 0x80135788
static int counter$2409;

// Local to compilation unit
// Location: 0x801352C8
static int nFirstTime$2648;

// Local to compilation unit
// Location: 0x801352CC
static int nFirstTime$2757;

// Local to compilation unit
// Location: 0x801352D0
static int nFirstTime$2796;

// Local to compilation unit
// Location: 0x8013578C
static unsigned short scissorX0;

// Local to compilation unit
// Location: 0x8013578E
static unsigned short scissorY0;

// Local to compilation unit
// Location: 0x801352D4
static unsigned short scissorX1;

// Local to compilation unit
// Location: 0x801352D6
static unsigned short scissorY1;

// Local to compilation unit
// Location: 0x80135790
static unsigned char flagBilerp;

// Local to compilation unit
// Location: 0x80135794
static unsigned int rdpSetTimg_w0;

// Local to compilation unit
// Location: 0x80135798
static unsigned int rdpSetTile_w0;

// Local to compilation unit
// Location: 0x8013579C
static unsigned short tmemSliceWmax;

// Local to compilation unit
// Location: 0x8013579E
static unsigned short imageSrcWsize;

// Local to compilation unit
// Location: 0x801357A0
static unsigned short flagSplit;

// Local to compilation unit
// Location: 0x801357A2
static unsigned short imagePtrX0;

// Local to compilation unit
// Location: 0x801357A4
static unsigned int imageTop;

// Local to compilation unit
// Location: 0x801357A8
static signed short tmemSrcLines;

// Local to compilation unit
// Location: 0x70E20E80
static signed short TMEMSIZE$3463[5];

// Local to compilation unit
// Location: 0x801352D8
static signed short TMEMMASK$3464[4];

// Local to compilation unit
// Location: 0x801352E0
static signed short TMEMSHIFT$3465[4];

// size: 0x40
struct __anon_0x575BD
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

// size: 0xD8
struct __anon_0x57890
{
	int iDL; // 0x0
	int bValid; // 0x4
	__anon_0x575BD task; // 0x8
	int nCountVertex; // 0x48
	__anon_0x60B3F eTypeUCode; // 0x4C
	unsigned int n2TriMult; // 0x50
	unsigned int nVersionUCode; // 0x54
	int anBaseSegment[16]; // 0x58
	unsigned long long  *apDL[16]; // 0x98
};

// size: 0x20
struct __anon_0x57AB1
{
	float aRotations[2][2]; // 0x0
	float fX; // 0x10
	float fY; // 0x14
	float fBaseScaleX; // 0x18
	float fBaseScaleY; // 0x1C
};

// size: 0x14
struct __anon_0x57BBE
{
	float rS; // 0x0
	float rT; // 0x4
	signed short nX; // 0x8
	signed short nY; // 0xA
	signed short nZ; // 0xC
	unsigned char anData[4]; // 0xE
};

// size: 0x3
struct __anon_0x57CD6
{
	char anNormal[3]; // 0x0
};

// size: 0x4
struct __anon_0x57D55
{
	unsigned char anMaterial[4]; // 0x0
};

// size: 0x40
struct __anon_0x57DF8
{
	float aMatrix[4][4]; // 0x0
};

// size: 0x6
struct __anon_0x57E56
{
	unsigned char nRed; // 0x0
	unsigned char nGreen; // 0x1
	unsigned char nBlue; // 0x2
	char rVectorX; // 0x3
	char rVectorY; // 0x4
	char rVectorZ; // 0x5
};

// size: 0x10
struct __anon_0x58107
{
	signed short anSlice[8]; // 0x0
};

// size: 0x4
enum __anon_0x581E7
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
struct __anon_0x58360
{
	signed short r; // 0x0
	signed short g; // 0x2
	signed short b; // 0x4
	signed short a; // 0x6
};

// size: 0x6
struct __anon_0x583EE
{
	signed short y; // 0x0
	signed short u; // 0x2
	signed short v; // 0x4
};

// size: 0x39CC
struct __anon_0x5845E
{
	int nMode; // 0x0
	__anon_0x57890 yield; // 0x4
	unsigned int nTickLast; // 0xDC
	int (*pfUpdateWaiting)(); // 0xE0
	unsigned int n2TriMult; // 0xE4
	int aStatus[4]; // 0xE8
	float aMatrixOrtho[4][4]; // 0xF8
	unsigned int nMode2D; // 0x138
	__anon_0x57AB1 twoDValues; // 0x13C
	int nPass; // 0x15C
	unsigned int nZSortSubDL; // 0x160
	unsigned int nStatusSubDL; // 0x164
	unsigned int nNumZSortLights; // 0x168
	int aLightAddresses[8]; // 0x16C
	int nAmbientLightAddress; // 0x18C
	__anon_0x57BBE aZSortVertex[128]; // 0x190
	__anon_0x57CD6 aZSortNormal[128]; // 0xB90
	__anon_0x57D55 aZSortMaterial[128]; // 0xD10
	__anon_0x57DF8 aZSortMatrix[128]; // 0xF10
	__anon_0x57E56 aZSortLight[8]; // 0x2F10
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
	__anon_0x58107 vParams; // 0x3380
	signed short stepF; // 0x3390
	signed short stepL; // 0x3392
	signed short stepR; // 0x3394
	int anGenReg[32]; // 0x3398
	__anon_0x58107 aVectorReg[32]; // 0x3418
	int anCP0Reg[32]; // 0x3618
	__anon_0x58107 anCP2Reg[32]; // 0x3698
	signed short anAcc[24]; // 0x3898
	signed short nVCC; // 0x38C8
	signed short nVC0; // 0x38CA
	char nVCE; // 0x38CC
	__anon_0x581E7 eTypeAudioUCode; // 0x38D0
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
	__anon_0x60B3F eTypeUCode; // 0x3920
	unsigned int nVersionUCode; // 0x3924
	int anBaseSegment[16]; // 0x3928
	unsigned long long  *apDL[16]; // 0x3968
	int *Coeff; // 0x39A8
	signed short *QTable; // 0x39AC
	signed short *QYTable; // 0x39B0
	signed short *QCbTable; // 0x39B4
	signed short *QCrTable; // 0x39B8
	int *Zigzag; // 0x39BC
	__anon_0x58360 *rgbaBuf; // 0x39C0
	__anon_0x583EE *yuvBuf; // 0x39C4
	int *dctBuf; // 0x39C8
};

int rspEvent(__anon_0x5845E *pRSP, int nEvent, void *pArgument);

// Location: 0x801356BC
int gNoSwapBuffer;

// size: 0x4
enum __anon_0x5943B
{
	RUM_NONE = 0,
	RUM_IDLE = 1
};

// size: 0x10
struct __anon_0x594BE
{
	float rX; // 0x0
	float rY; // 0x4
	float rSizeX; // 0x8
	float rSizeY; // 0xC
};

// size: 0x14
struct __anon_0x59558
{
	int nSize; // 0x0
	int nWidth; // 0x4
	int nFormat; // 0x8
	void *pData; // 0xC
	int nAddress; // 0x10
};

// size: 0xC
struct __anon_0x59699
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
};

// size: 0x3C
struct __anon_0x59709
{
	int bTransformed; // 0x0
	__anon_0x59699 rVecOrigTowards; // 0x4
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
struct __anon_0x59939
{
	int bTransformed; // 0x0
	__anon_0x59699 rS; // 0x4
	__anon_0x59699 rT; // 0x10
	__anon_0x59699 rSRaw; // 0x1C
	__anon_0x59699 rTRaw; // 0x28
};

// size: 0x1C
struct __anon_0x59A22
{
	float rSum; // 0x0
	float rS; // 0x4
	float rT; // 0x8
	__anon_0x59699 vec; // 0xC
	unsigned char anColor[4]; // 0x18
};

// size: 0x1000
union __anon_0x59B81
{
	unsigned char u8[4096]; // 0x0
	unsigned short u16[2048]; // 0x0
	unsigned int u32[1024]; // 0x0
	unsigned long long u64[512]; // 0x0
};

// size: 0x1000
struct __anon_0x59C1E
{
	__anon_0x59B81 data; // 0x0
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
struct __anon_0x5A2EC
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
enum __anon_0x5A5CE
{
	FMP_NONE = 4294967295,
	FMP_PERSPECTIVE = 0,
	FMP_ORTHOGRAPHIC = 1
};

// size: 0x24
struct __anon_0x5A64F
{
	int nCount; // 0x0
	float rScale; // 0x4
	float rAspect; // 0x8
	float rFieldOfViewY; // 0xC
	float rClipNear; // 0x10
	float rClipFar; // 0x14
	unsigned int nAddressFloat; // 0x18
	unsigned int nAddressFixed; // 0x1C
	__anon_0x5A5CE eProjection; // 0x20
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
struct __anon_0x5A89F
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
	__anon_0x594BE viewport; // 0xB8
	__anon_0x59558 aBuffer[4]; // 0xC8
	unsigned int nOffsetDepth0; // 0x118
	unsigned int nOffsetDepth1; // 0x11C
	int nWidthLine; // 0x120
	float rDepth; // 0x124
	float rDelta; // 0x128
	int (*aDraw[4])(void */* unknown0 */, void */* unknown1 */); // 0x12C
	int nCountLight; // 0x13C
	__anon_0x59709 aLight[8]; // 0x140
	__anon_0x59939 lookAt; // 0x320
	int nCountVertex; // 0x354
	__anon_0x59A22 aVertex[80]; // 0x358
	__anon_0x59C1E TMEM; // 0xC18
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
	__anon_0x5A2EC aTile[8]; // 0x3C358
	int anSizeX[2]; // 0x3C4B8
	int anSizeY[2]; // 0x3C4C0
	int iHintMatrix; // 0x3C4C8
	int iMatrixModel; // 0x3C4CC
	int iHintProjection; // 0x3C4D0
	float matrixView[4][4]; // 0x3C4D4
	int iHintLast; // 0x3C514
	int iHintHack; // 0x3C518
	__anon_0x5A5CE eTypeProjection; // 0x3C51C
	float aMatrixModel[10][4][4]; // 0x3C520
	float matrixProjection[4][4]; // 0x3C7A0
	float matrixProjectionExtra[4][4]; // 0x3C7E0
	__anon_0x5A64F aMatrixHint[64]; // 0x3C820
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

int rspUpdate(__anon_0x5845E *pRSP, __anon_0x5943B eMode)
{
	__anon_0x575BD *pTask;
	int bDone;
	int nCount;
	__anon_0x5A89F *pFrame;
	// References: gNoSwapBuffer (0x801356BC)
}

int rspFrameComplete(__anon_0x5845E *pRSP);

int rspEnableABI(__anon_0x5845E *pRSP, int bFlag);

// size: 0x60
struct __anon_0x5B8F2
{
	int nOffsetCode; // 0x0
	int nLengthCode; // 0x4
	int nOffsetData; // 0x8
	int nLengthData; // 0xC
	char acUCodeName[64]; // 0x10
	unsigned long long nUCodeCheckSum; // 0x50
	int nCountVertex; // 0x58
	__anon_0x60B3F eType; // 0x5C
};

int rspInvalidateCache(__anon_0x5845E *pRSP, int nOffset0, int nOffset1)
{
	__anon_0x5B8F2 *pUCode;
	void *pListNode;
	int nOffsetUCode0;
	int nOffsetUCode1;
}

int rspGet64(__anon_0x5845E *pRSP, unsigned int nAddress, signed long long *pData);

int rspGet32(__anon_0x5845E *pRSP, unsigned int nAddress, int *pData);

int rspGet16(__anon_0x5845E *pRSP, unsigned int nAddress, signed short *pData);

int rspGet8(__anon_0x5845E *pRSP, unsigned int nAddress, char *pData);

int rspPut64(__anon_0x5845E *pRSP, unsigned int nAddress, signed long long *pData);

int rspPut32(__anon_0x5845E *pRSP, unsigned int nAddress, int *pData)
{
	__anon_0x575BD *pTask;
	int nData;
	int nSize;
	void *pTarget;
	void *pSource;
	int nLength;
}

int rspPut16(__anon_0x5845E *pRSP, unsigned int nAddress, signed short *pData);

int rspPut8(__anon_0x5845E *pRSP, unsigned int nAddress, char *pData);

int rspSaveUCode();

// size: 0x8
struct __anon_0x5C1E6
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
	__anon_0x5C1E6 *aJump; // 0xC
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
union __anon_0x5C59B
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
union __anon_0x5C9AF
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
struct __anon_0x5CEBD
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
struct __anon_0x5D481
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
	__anon_0x5C59B aGPR[32]; // 0x40
	__anon_0x5C9AF aFPR[32]; // 0x140
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
	__anon_0x5CEBD *apDevice[256]; // 0xB64
	unsigned char aiDevice[65536]; // 0xF64
	void *gHeap1; // 0x10F64
	void *gHeap2; // 0x10F68
	unsigned int aHeap1Flag[192]; // 0x10F6C
	unsigned int aHeap2Flag[13]; // 0x1126C
	cpu_treeRoot *gTree; // 0x112A0
	_CPU_ADDRESS aAddressCache[256]; // 0x112A4
	int nCountCodeHack; // 0x11EA4
	__anon_0x5D481 aCodeHack[32]; // 0x11EA8
	signed long long nTimeRetrace; // 0x12028
	OSAlarm alarmRetrace; // 0x12030
	unsigned int nFlagRAM; // 0x12058
	unsigned int nFlagCODE; // 0x1205C
	unsigned int nCompileFlag; // 0x12060
	cpu_optimize nOptimize; // 0x12064
};

// Local to compilation unit
static int rspParseGBI(__anon_0x5845E *pRSP, int *pbDone, int nCount)
{
	int bDone;
	int nStatus;
	unsigned long long *pDL;
	_CPU *pCPU;
}

// Local to compilation unit
static int rspParseGBI_Setup(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	int iSegment;
}

int rspTaskComplete(__anon_0x5845E *pRSP, int bUsedSP, int bUsedDP);

int rspParseDisplayLists(__anon_0x5845E *pRSP)
{
	int bDone;
	int nStatus;
	unsigned long long *pDL;
	unsigned long long nGBI;
}

// Local to compilation unit
static int rspLoadYield(__anon_0x5845E *pRSP)
{
	int iData;
	__anon_0x575BD *pTask;
}

// Local to compilation unit
static int rspSaveYield(__anon_0x5845E *pRSP)
{
	int iData;
	__anon_0x575BD *pTask;
}

// size: 0x4
enum __anon_0x5E613
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

// size: 0x10
struct __anon_0x5E675
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x5E726
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
enum __anon_0x5E852
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
struct __anon_0x5E98D
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x5E613 eMode; // 0xC
	__anon_0x5E675 romCopy; // 0x10
	__anon_0x5E726 eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x5E852 storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// Location: 0x561380
__anon_0x5E98D *gpSystem;

// size: 0x304
struct __anon_0x5EBE0
{
	int nCount; // 0x0
	unsigned char anData[768]; // 0x4
};

// size: 0x10
struct __anon_0x5EC3E
{
	signed short sx; // 0x0
	signed short sy; // 0x2
	int invw; // 0x4
	signed short xi; // 0x8
	signed short yi; // 0xA
	unsigned char cc; // 0xC
	unsigned char fog; // 0xD
	signed short wi; // 0xE
};

// size: 0x28
struct __anon_0x5ED4F
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
struct __anon_0x5F05A
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
union __anon_0x5F2FB
{
	__anon_0x5ED4F b; // 0x0
	__anon_0x5F05A s; // 0x0
	signed long long force_structure_alignment; // 0x0
};

// size: 0x18
struct __anon_0x5F429
{
	signed short objX; // 0x0
	unsigned short scaleW; // 0x2
	unsigned short imageW; // 0x4
	unsigned short paddingX; // 0x6
	signed short objY; // 0x8
	unsigned short scaleH; // 0xA
	unsigned short imageH; // 0xC
	unsigned short paddingY; // 0xE
	unsigned short imageStride; // 0x10
	unsigned short imageAdrs; // 0x12
	unsigned char imageFmt; // 0x14
	unsigned char imageSiz; // 0x15
	unsigned char imagePal; // 0x16
	unsigned char imageFlags; // 0x17
};

// size: 0x18
union __anon_0x5F63B
{
	__anon_0x5F429 s; // 0x0
	signed long long force_structure_alignment; // 0x0
};

// size: 0xC
struct __anon_0x5F6E9
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
};

// size: 0x28
struct __anon_0x5F759
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

// size: 0x18
struct __anon_0x5F8B9
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
struct __anon_0x5F9D9
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
struct __anon_0x5FAFC
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
union __anon_0x5FC1B
{
	__anon_0x5F8B9 block; // 0x0
	__anon_0x5F9D9 tile; // 0x0
	__anon_0x5FAFC tlut; // 0x0
	signed long long force_structure_alignment; // 0x0
};

// size: 0x4
enum __anon_0x6029B
{
	XLFT_NONE = 4294967295,
	XLFT_TEXT = 0,
	XLFT_BINARY = 1
};

// size: 0x20
struct DVDDiskID
{
	char gameName[4]; // 0x0
	char company[2]; // 0x4
	unsigned char diskNumber; // 0x6
	unsigned char gameVersion; // 0x7
	unsigned char streaming; // 0x8
	unsigned char streamingBufSize; // 0x9
	unsigned char padding[22]; // 0xA
};

// size: 0x30
struct DVDCommandBlock
{
	DVDCommandBlock *next; // 0x0
	DVDCommandBlock *prev; // 0x4
	unsigned long command; // 0x8
	long state; // 0xC
	unsigned long offset; // 0x10
	unsigned long length; // 0x14
	void *addr; // 0x18
	unsigned long currTransferSize; // 0x1C
	unsigned long transferredSize; // 0x20
	DVDDiskID *id; // 0x24
	void (*callback)(long /* unknown0 */, DVDCommandBlock */* unknown1 */); // 0x28
	void *userData; // 0x2C
};

// size: 0x3C
struct DVDFileInfo
{
	DVDCommandBlock cb; // 0x0
	unsigned long startAddr; // 0x30
	unsigned long length; // 0x34
	void (*callback)(long /* unknown0 */, DVDFileInfo */* unknown1 */); // 0x38
};

// size: 0x58
struct tXL_FILE
{
	int iBuffer; // 0x0
	void *pData; // 0x4
	void *pBuffer; // 0x8
	int nAttributes; // 0xC
	int nSize; // 0x10
	int nOffset; // 0x14
	__anon_0x6029B eType; // 0x18
	DVDFileInfo info; // 0x1C
};

// size: 0x4
enum __anon_0x60B3F
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

// Local to compilation unit
static int rspFindUCode(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	int nCountVertex;
	__anon_0x5B8F2 *pUCode;
	__anon_0x60B3F eType;
	void *pListNode;
	int nOffsetCode;
	int nOffsetData;
	unsigned long long nFUData;
	unsigned long long *pFUData;
	unsigned long long *pFUCode;
	unsigned long long nCheckSum;
	unsigned int nLengthData;
	unsigned int i;
	unsigned int nLengthCode;
	char aBigBuffer[4096];
	char acUCodeName[64];
}

int rspGetUCodeName(__anon_0x5845E *pRSP)
{
	unsigned int nItemCount;
	void *pListNode;
}

int rspGetNumUCodes(__anon_0x5845E *pRSP, unsigned int *pNumCodes);

int rspSetupUCode(__anon_0x5845E *pRSP)
{
	__anon_0x5A89F *pFrame;
}

int rspPopDL(__anon_0x5845E *pRSP);

int rspSetDL(__anon_0x5845E *pRSP, int nOffsetRDRAM, int bPush)
{
	int nAddress;
	unsigned long long *pDL;
}

// Local to compilation unit
static int rspLoadMatrix(__anon_0x5845E *pRSP, int nAddress, float *matrix[4])
{
	int *pMtx;
	int nDataA;
	int nDataB;
	float rScale;
	float rUpper;
	float rLower;
	unsigned short nUpper;
	unsigned short nLower;
}

