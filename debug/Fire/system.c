// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// Location: 0x604E1380
unsigned int nTickMultiplier;

// Location: 0x644E1380
float fTickScale;

// size: 0x10
struct _XL_OBJECTTYPE
{
	char *szName; // 0x0
	int nSizeObject; // 0x4
	_XL_OBJECTTYPE *pClassBase; // 0x8
	int (*pfEvent)(void */* unknown0 */, int /* unknown1 */, void */* unknown2 */); // 0xC
};

// Location: 0x10B30E80
_XL_OBJECTTYPE gClassSystem;

// Local to compilation unit
// Location: 0x20B30E80
static unsigned int contMap[4][20];

// Location: 0x801356D8
unsigned int gnFlagZelda;

// size: 0x174
struct __anon_0x3459E
{
	char rom[36]; // 0x0
	int controllerConfiguration[4][20]; // 0x24
	int rumbleConfiguration; // 0x164
	int storageDevice; // 0x168
	int normalControllerConfig; // 0x16C
	int currentControllerConfig; // 0x170
};

// Location: 0x801308E0
__anon_0x3459E gSystemRomConfigurationList[1];

// size: 0x10
struct __anon_0x34768
{
	float rX; // 0x0
	float rY; // 0x4
	float rSizeX; // 0x8
	float rSizeY; // 0xC
};

// size: 0x14
struct __anon_0x34802
{
	int nSize; // 0x0
	int nWidth; // 0x4
	int nFormat; // 0x8
	void *pData; // 0xC
	int nAddress; // 0x10
};

// size: 0xC
struct __anon_0x34943
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
};

// size: 0x3C
struct __anon_0x349B3
{
	int bTransformed; // 0x0
	__anon_0x34943 rVecOrigTowards; // 0x4
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
struct __anon_0x34BE3
{
	int bTransformed; // 0x0
	__anon_0x34943 rS; // 0x4
	__anon_0x34943 rT; // 0x10
	__anon_0x34943 rSRaw; // 0x1C
	__anon_0x34943 rTRaw; // 0x28
};

// size: 0x1C
struct __anon_0x34CCC
{
	float rSum; // 0x0
	float rS; // 0x4
	float rT; // 0x8
	__anon_0x34943 vec; // 0xC
	unsigned char anColor[4]; // 0x18
};

// size: 0x1000
union __anon_0x34E2B
{
	unsigned char u8[4096]; // 0x0
	unsigned short u16[2048]; // 0x0
	unsigned int u32[1024]; // 0x0
	unsigned long long u64[512]; // 0x0
};

// size: 0x1000
struct __anon_0x34EC8
{
	__anon_0x34E2B data; // 0x0
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
struct __anon_0x35596
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
enum __anon_0x35878
{
	FMP_NONE = 4294967295,
	FMP_PERSPECTIVE = 0,
	FMP_ORTHOGRAPHIC = 1
};

// size: 0x24
struct __anon_0x358FC
{
	int nCount; // 0x0
	float rScale; // 0x4
	float rAspect; // 0x8
	float rFieldOfViewY; // 0xC
	float rClipNear; // 0x10
	float rClipFar; // 0x14
	unsigned int nAddressFloat; // 0x18
	unsigned int nAddressFixed; // 0x1C
	__anon_0x35878 eProjection; // 0x20
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
struct __anon_0x35B4C
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
	__anon_0x34768 viewport; // 0xB8
	__anon_0x34802 aBuffer[4]; // 0xC8
	unsigned int nOffsetDepth0; // 0x118
	unsigned int nOffsetDepth1; // 0x11C
	int nWidthLine; // 0x120
	float rDepth; // 0x124
	float rDelta; // 0x128
	int (*aDraw[4])(void */* unknown0 */, void */* unknown1 */); // 0x12C
	int nCountLight; // 0x13C
	__anon_0x349B3 aLight[8]; // 0x140
	__anon_0x34BE3 lookAt; // 0x320
	int nCountVertex; // 0x354
	__anon_0x34CCC aVertex[80]; // 0x358
	__anon_0x34EC8 TMEM; // 0xC18
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
	__anon_0x35596 aTile[8]; // 0x3C358
	int anSizeX[2]; // 0x3C4B8
	int anSizeY[2]; // 0x3C4C0
	int iHintMatrix; // 0x3C4C8
	int iMatrixModel; // 0x3C4CC
	int iHintProjection; // 0x3C4D0
	float matrixView[4][4]; // 0x3C4D4
	int iHintLast; // 0x3C514
	int iHintHack; // 0x3C518
	__anon_0x35878 eTypeProjection; // 0x3C51C
	float aMatrixModel[10][4][4]; // 0x3C520
	float matrixProjection[4][4]; // 0x3C7A0
	float matrixProjectionExtra[4][4]; // 0x3C7E0
	__anon_0x358FC aMatrixHint[64]; // 0x3C820
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

// Location: 0x8561380
__anon_0x35B4C *gpFrame;

// size: 0x4
enum __anon_0x36A3E
{
	SPM_NONE = 4294967295,
	SPM_PLAY = 0,
	SPM_RAMPQUEUED = 1,
	SPM_RAMPPLAYED = 2
};

// size: 0xD8
struct __anon_0x36AAA
{
	void *pSrcData; // 0x0
	int nFrequency; // 0x4
	int nDacrate; // 0x8
	int nSndLen; // 0xC
	void *apBuffer[16]; // 0x10
	int anSizeBuffer[16]; // 0x50
	int nCountBeep; // 0x90
	int anSizeBeep[3]; // 0x94
	void *apDataBeep[3]; // 0xA0
	int iBufferPlay; // 0xAC
	int iBufferMake; // 0xB0
	__anon_0x36A3E eMode; // 0xB4
	void *pBufferZero; // 0xB8
	void *pBufferHold; // 0xBC
	void *pBufferRampUp; // 0xC0
	void *pBufferRampDown; // 0xC4
	int nSizePlay; // 0xC8
	int nSizeZero; // 0xCC
	int nSizeHold; // 0xD0
	int nSizeRamp; // 0xD4
};

// Location: 0x4561380
__anon_0x36AAA *gpSound;

// Location: 0x58B60E80
_XL_OBJECTTYPE gClassCPU;

// Location: 0x800ED6B8
_XL_OBJECTTYPE gClassPIF;

// Location: 0x800ED6C8
_XL_OBJECTTYPE gClassRAM;

// Location: 0x800ED8E8
_XL_OBJECTTYPE gClassROM;

// Location: 0x20E20E80
_XL_OBJECTTYPE gClassRSP;

// Location: 0x40DF0E80
_XL_OBJECTTYPE gClassRDP;

// Location: 0x800EE6D0
_XL_OBJECTTYPE gClassMips;

// Location: 0x48E70E80
_XL_OBJECTTYPE gClassDisk;

// Location: 0x78E70E80
_XL_OBJECTTYPE gClassAudio;

// Location: 0x70E80E80
_XL_OBJECTTYPE gClassVideo;

// Location: 0x28EA0E80
_XL_OBJECTTYPE gClassSerial;

// Location: 0xCEB0E80
_XL_OBJECTTYPE gClassLibrary;

// Location: 0x800EFFBC
_XL_OBJECTTYPE gClassPeripheral;

// Location: 0x800EE1B0
_XL_OBJECTTYPE gClassRdb;

// size: 0x10
struct __anon_0x37040
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x370F1
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

// size: 0x88
struct __anon_0x37240
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x3A085 eMode; // 0xC
	__anon_0x37040 romCopy; // 0x10
	__anon_0x370F1 eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x394CD storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// size: 0x8
struct __anon_0x37408
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
	__anon_0x37408 *aJump; // 0xC
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
union __anon_0x377BD
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
union __anon_0x37BD1
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
struct __anon_0x380DF
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
struct __anon_0x386A3
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
	__anon_0x377BD aGPR[32]; // 0x40
	__anon_0x37BD1 aFPR[32]; // 0x140
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
	__anon_0x380DF *apDevice[256]; // 0xB64
	unsigned char aiDevice[65536]; // 0xF64
	void *gHeap1; // 0x10F64
	void *gHeap2; // 0x10F68
	unsigned int aHeap1Flag[192]; // 0x10F6C
	unsigned int aHeap2Flag[13]; // 0x1126C
	cpu_treeRoot *gTree; // 0x112A0
	_CPU_ADDRESS aAddressCache[256]; // 0x112A4
	int nCountCodeHack; // 0x11EA4
	__anon_0x386A3 aCodeHack[32]; // 0x11EA8
	signed long long nTimeRetrace; // 0x12028
	OSAlarm alarmRetrace; // 0x12030
	unsigned int nFlagRAM; // 0x12058
	unsigned int nFlagCODE; // 0x1205C
	unsigned int nCompileFlag; // 0x12060
	cpu_optimize nOptimize; // 0x12064
};

// size: 0x4
enum __anon_0x39384
{
	MIT_NONE = 4294967295,
	MIT_SP = 0,
	MIT_SI = 1,
	MIT_AI = 2,
	MIT_VI = 3,
	MIT_PI = 4,
	MIT_DP = 5
};

// size: 0x14
struct __anon_0x393FF
{
	char *szType; // 0x0
	unsigned int nMask; // 0x4
	__anon_0x3994B eCode; // 0x8
	__anon_0x3979C eType; // 0xC
	__anon_0x39384 eTypeMips; // 0x10
};

// size: 0x4
enum __anon_0x394CD
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

int systemEvent(__anon_0x37240 *pSystem, int nEvent, void *pArgument)
{
	_CPU *pCPU;
	__anon_0x393FF exception;
	__anon_0x394CD eObject;
	__anon_0x394CD storageDevice;
	// References: gClassRdb (0x800EE1B0)
	// References: gClassPeripheral (0x800EFFBC)
	// References: gClassLibrary (0xCEB0E80)
	// References: gClassSerial (0x28EA0E80)
	// References: gClassVideo (0x70E80E80)
	// References: gClassAudio (0x78E70E80)
	// References: gClassDisk (0x48E70E80)
	// References: gClassMips (0x800EE6D0)
	// References: gClassRDP (0x40DF0E80)
	// References: gClassRSP (0x20E20E80)
	// References: gClassROM (0x800ED8E8)
	// References: gClassRAM (0x800ED6C8)
	// References: gClassPIF (0x800ED6B8)
	// References: gClassCPU (0x58B60E80)
	// References: gpSound (0x4561380)
	// References: gpFrame (0x8561380)
}

// size: 0x4
enum __anon_0x3979C
{
	SIT_NONE = 4294967295,
	SIT_SW0 = 0,
	SIT_SW1 = 1,
	SIT_CART = 2,
	SIT_COUNTER = 3,
	SIT_RDB = 4,
	SIT_SP = 5,
	SIT_SI = 6,
	SIT_AI = 7,
	SIT_VI = 8,
	SIT_PI = 9,
	SIT_DP = 10,
	SIT_CPU_BREAK = 11,
	SIT_SP_BREAK = 12,
	SIT_FAULT = 13,
	SIT_THREADSTATUS = 14,
	SIT_PRENMI = 15,
	SIT_COUNT_ = 16
};

int systemExceptionPending(__anon_0x37240 *pSystem, __anon_0x3979C eType);

// size: 0x4
enum __anon_0x3994B
{
	CEC_NONE = 4294967295,
	CEC_INTERRUPT = 0,
	CEC_TLB_MODIFICATION = 1,
	CEC_TLB_LOAD = 2,
	CEC_TLB_STORE = 3,
	CEC_ADDRESS_LOAD = 4,
	CEC_ADDRESS_STORE = 5,
	CEC_BUS_INSTRUCTION = 6,
	CEC_BUS_DATA = 7,
	CEC_SYSCALL = 8,
	CEC_BREAK = 9,
	CEC_RESERVED = 10,
	CEC_COPROCESSOR = 11,
	CEC_OVERFLOW = 12,
	CEC_TRAP = 13,
	CEC_VCE_INSTRUCTION = 14,
	CEC_FLOAT = 15,
	CEC_RESERVED_16 = 16,
	CEC_RESERVED_17 = 17,
	CEC_RESERVED_18 = 18,
	CEC_RESERVED_19 = 19,
	CEC_RESERVED_20 = 20,
	CEC_RESERVED_21 = 21,
	CEC_RESERVED_22 = 22,
	CEC_WATCH = 23,
	CEC_RESERVED_24 = 24,
	CEC_RESERVED_25 = 25,
	CEC_RESERVED_26 = 26,
	CEC_RESERVED_27 = 27,
	CEC_RESERVED_28 = 28,
	CEC_RESERVED_29 = 29,
	CEC_RESERVED_30 = 30,
	CEC_VCE_DATA = 31,
	CEC_COUNT = 32
};

int systemCheckInterrupts(__anon_0x37240 *pSystem)
{
	int iException;
	int nMaskFinal;
	int bUsed;
	int bDone;
	__anon_0x393FF exception;
	__anon_0x3994B eCodeFinal;
}

int systemExecute(__anon_0x37240 *pSystem, int nCount)
{
	// References: gClassSystem (0x10B30E80)
}

int systemReset(__anon_0x37240 *pSystem)
{
	signed long long nPC;
	int nOffsetRAM;
	__anon_0x394CD eObject;
}

int systemGetStorageDevice(__anon_0x37240 *pSystem, __anon_0x394CD *pStorageDevice);

// Location: 0x58E70E80
_XL_OBJECTTYPE gClassFlash;

// Location: 0x68E70E80
_XL_OBJECTTYPE gClassSram;

int systemSetStorageDevice(__anon_0x37240 *pSystem, __anon_0x394CD storageDevice)
{
	// References: gClassSram (0x68E70E80)
	// References: gClassFlash (0x58E70E80)
}

int systemGetMode(__anon_0x37240 *pSystem, __anon_0x3A085 *peMode)
{
	// References: gClassSystem (0x10B30E80)
}

// size: 0x4
enum __anon_0x3A085
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

int systemSetMode(__anon_0x37240 *pSystem, __anon_0x3A085 eMode)
{
	// References: gClassSystem (0x10B30E80)
}

int systemClearBreak(__anon_0x37240 *pSystem);

int systemSetBreak(__anon_0x37240 *pSystem, signed long long nAddress);

int systemCopyROM(__anon_0x37240 *pSystem, int nOffsetRAM, int nOffsetROM, int nSize, int (*pCallback)())
{
	void *pTarget;
}

// Location: 0x561380
__anon_0x37240 *gpSystem;

// Local to compilation unit
static int __systemCopyROM_Complete()
{
	int iAddress;
	int nCount;
	unsigned int nAddress0;
	unsigned int nAddress1;
	unsigned int anAddress[32];
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int systemPut64();

// Local to compilation unit
static int systemPut32();

// Local to compilation unit
static int systemPut16();

// Local to compilation unit
static int systemPut8();

// Local to compilation unit
static int systemGet64(signed long long *pData);

// Local to compilation unit
static int systemGet32(int *pData);

// Local to compilation unit
static int systemGet16(signed short *pData);

// Local to compilation unit
static int systemGet8(char *pData);

// Local to compilation unit
static int systemGetException(__anon_0x3979C eType, __anon_0x393FF *pException);

int systemClearExceptions(__anon_0x37240 *pSystem)
{
	int iException;
}

// size: 0x18
struct __anon_0x3A807
{
	int configuration; // 0x0
	int size; // 0x4
	int offset; // 0x8
	char *buffer; // 0xC
	int *writtenBlocks; // 0x10
	int writtenConfig; // 0x14
};

// size: 0x28
struct OSCalendarTime
{
	int sec; // 0x0
	int min; // 0x4
	int hour; // 0x8
	int mday; // 0xC
	int mon; // 0x10
	int year; // 0x14
	int wday; // 0x18
	int yday; // 0x1C
	int msec; // 0x20
	int usec; // 0x24
};

// size: 0x14
struct CARDFileInfo
{
	long chan; // 0x0
	long fileNo; // 0x4
	long offset; // 0x8
	long length; // 0xC
	unsigned short iBlock; // 0x10
	unsigned short __padding; // 0x12
};

// size: 0x35C
struct __anon_0x3AC10
{
	int currentGame; // 0x0
	int fileSize; // 0x4
	char name[33]; // 0x8
	int numberOfGames; // 0x2C
	__anon_0x3A807 game; // 0x30
	int changedDate; // 0x48
	int changedChecksum; // 0x4C
	int gameSize[16]; // 0x50
	int gameOffset[16]; // 0x90
	int gameConfigIndex[16]; // 0xD0
	char gameName[16][33]; // 0x110
	OSCalendarTime time; // 0x320
	CARDFileInfo fileInfo; // 0x348
};

// size: 0x4
enum __anon_0x3AE26
{
	MC_E_NONE = 0,
	MC_E_BUSY = 1,
	MC_E_WRONGDEVICE = 2,
	MC_E_NOCARD = 3,
	MC_E_NOFILE = 4,
	MC_E_IOERROR = 5,
	MC_E_BROKEN = 6,
	MC_E_EXIST = 7,
	MC_E_NOENT = 8,
	MC_E_INSSPACE = 9,
	MC_E_NOPERM = 10,
	MC_E_LIMIT = 11,
	MC_E_NAMETOOLONG = 12,
	MC_E_ENCODING = 13,
	MC_E_CANCELED = 14,
	MC_E_FATAL = 15,
	MC_E_SECTOR_SIZE_INVALID = 16,
	MC_E_GAME_NOT_FOUND = 17,
	MC_E_CHECKSUM = 18,
	MC_E_NO_FREE_SPACE = 19,
	MC_E_NO_FREE_FILES = 20,
	MC_E_FILE_EXISTS = 21,
	MC_E_GAME_EXISTS = 22,
	MC_E_TIME_WRONG = 23,
	MC_E_WRITE_CORRUPTED = 24,
	MC_E_UNKNOWN = 25
};

// size: 0x7B8
struct _MCARD
{
	__anon_0x3AC10 file; // 0x0
	__anon_0x3AE26 error; // 0x35C
	int slot; // 0x360
	int (*pPollFunction)(); // 0x364
	int pollPrevBytes; // 0x368
	int pollSize; // 0x36C
	char pollMessage[256]; // 0x370
	int saveToggle; // 0x470
	char *writeBuffer; // 0x474
	char *readBuffer; // 0x478
	int writeToggle; // 0x47C
	int soundToggle; // 0x480
	int writeStatus; // 0x484
	int writeIndex; // 0x488
	int accessType; // 0x48C
	int gameIsLoaded; // 0x490
	char saveFileName[256]; // 0x494
	char saveComment[256]; // 0x594
	char *saveIcon; // 0x694
	char *saveBanner; // 0x698
	char saveGameName[256]; // 0x69C
	int saveFileSize; // 0x79C
	int saveGameSize; // 0x7A0
	int bufferCreated; // 0x7A4
	int cardSize; // 0x7A8
	int wait; // 0x7AC
	int isBroken; // 0x7B0
	int saveConfiguration; // 0x7B4
};

// Location: 0x801079B0
_MCARD mCard;

// Location: 0x80134D8C
unsigned int gz_iconSize;

// Location: 0x80134D88
unsigned int gz_bnrSize;

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

// size: 0x4
enum __anon_0x3BAA7
{
	RLM_NONE = 4294967295,
	RLM_PART = 0,
	RLM_FULL = 1,
	RLM_COUNT_ = 2
};

// size: 0x10
struct __anon_0x3BB09
{
	int iCache; // 0x0
	unsigned int nSize; // 0x4
	unsigned int nTickUsed; // 0x8
	char keep; // 0xC
};

// size: 0x14
struct __anon_0x3BC1D
{
	int bWait; // 0x0
	int (*pCallback)(); // 0x4
	unsigned char *pTarget; // 0x8
	unsigned int nSize; // 0xC
	unsigned int nOffset; // 0x10
};

// size: 0x30
struct __anon_0x3BCFD
{
	int bWait; // 0x0
	int bDone; // 0x4
	int nResult; // 0x8
	unsigned char *anData; // 0xC
	int (*pCallback)(); // 0x10
	int iCache; // 0x14
	int iBlock; // 0x18
	int nOffset; // 0x1C
	unsigned int nOffset0; // 0x20
	unsigned int nOffset1; // 0x24
	unsigned int nSize; // 0x28
	unsigned int nSizeRead; // 0x2C
};

// size: 0x10EF8
struct __anon_0x3BEE8
{
	void *pHost; // 0x0
	void *pBuffer; // 0x4
	int bFlip; // 0x8
	int bLoad; // 0xC
	char acNameFile[513]; // 0x10
	unsigned int nSize; // 0x214
	__anon_0x3BAA7 eModeLoad; // 0x218
	__anon_0x3BB09 aBlock[4096]; // 0x21C
	unsigned int nTick; // 0x1021C
	unsigned char *pCacheRAM; // 0x10220
	unsigned char anBlockCachedRAM[1024]; // 0x10224
	unsigned char anBlockCachedARAM[2046]; // 0x10624
	__anon_0x3BC1D copy; // 0x10E24
	__anon_0x3BCFD load; // 0x10E38
	int nCountBlockRAM; // 0x10E68
	int nSizeCacheRAM; // 0x10E6C
	unsigned char acHeader[64]; // 0x10E70
	unsigned int *anOffsetBlock; // 0x10EB0
	int nCountOffsetBlocks; // 0x10EB4
	DVDFileInfo fileInfo; // 0x10EB8
	int offsetToRom; // 0x10EF4
};

// size: 0x4
enum __anon_0x3C277
{
	CT_NONE = 0,
	CT_CONTROLLER = 1,
	CT_CONTROLLER_W_PAK = 2,
	CT_CONTROLLER_W_RPAK = 3,
	CT_MOUSE = 4,
	CT_VOICE = 5,
	CT_4K = 6,
	CT_16K = 7,
	CT_COUNT = 8
};

// size: 0x30
struct __anon_0x3C350
{
	void *pROM; // 0x0
	void *pRAM; // 0x4
	void *pHost; // 0x8
	unsigned short controllerType[5]; // 0xC
	char controllerStatus[5]; // 0x16
	__anon_0x3C277 eControllerType[5]; // 0x1C
};

// Local to compilation unit
static int systemSetupGameALL(__anon_0x37240 *pSystem)
{
	int nSizeSound;
	int iController;
	int nSize;
	unsigned int *anMode;
	int i;
	unsigned long long nTimeRetrace;
	char acCode[5];
	DVDFileInfo fileInfo;
	_CPU *pCPU;
	__anon_0x3BEE8 *pROM;
	__anon_0x3C350 *pPIF;
	int defaultConfiguration;
	// References: contMap (0x20B30E80)
	// References: gSystemRomConfigurationList (0x801308E0)
	// References: mCard (0x801079B0)
	// References: gpSystem (0x561380)
	// References: gz_bnrSize (0x80134D88)
	// References: gz_iconSize (0x80134D8C)
	// References: nTickMultiplier (0x604E1380)
	// References: gnFlagZelda (0x801356D8)
	// References: fTickScale (0x644E1380)
}

int systemGetInitialConfiguration(__anon_0x3BEE8 *pROM, int index)
{
	char *szText;
	// References: gSystemRomConfigurationList (0x801308E0)
	// References: contMap (0x20B30E80)
}

int systemMapControllerIndex(int gameIndex, int configIndex)
{
	int i;
	// References: contMap (0x20B30E80)
	// References: gSystemRomConfigurationList (0x801308E0)
}

// Local to compilation unit
static int systemSetupGameRAM(__anon_0x37240 *pSystem)
{
	char *szExtra;
	int bExpansion;
	int nSizeRAM;
	int nSizeCacheROM;
	int nSizeExtra;
	__anon_0x3BEE8 *pROM;
	unsigned int nCode;
	unsigned int iCode;
	unsigned int anCode[256];
	// References: gnFlagZelda (0x801356D8)
}

