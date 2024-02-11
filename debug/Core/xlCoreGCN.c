// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// Location: 0x20370D80
unsigned char gTgPcTPL[32897];

// Local to compilation unit
// Location: 0x80135580
static int gnCountArgument;

// Local to compilation unit
// Location: 0x80135584
static char **gaszArgument;

// Local to compilation unit
// Location: 0x80135588
static void *DefaultFifo;

// size: 0x80
struct __anon_0x238
{
	unsigned char pad[128]; // 0x0
};

// Local to compilation unit
// Location: 0x8013558C
static __anon_0x238 *DefaultFifoObj;

// size: 0x4
enum __anon_0x29F
{
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
	VI_TVMODE_DEBUG_PAL_DS = 17
};

// size: 0x4
enum __anon_0x3EC
{
	VI_XFBMODE_SF = 0,
	VI_XFBMODE_DF = 1
};

// size: 0x3C
struct _GXRenderModeObj
{
	__anon_0x29F viTVmode; // 0x0
	unsigned short fbWidth; // 0x4
	unsigned short efbHeight; // 0x6
	unsigned short xfbHeight; // 0x8
	unsigned short viXOrigin; // 0xA
	unsigned short viYOrigin; // 0xC
	unsigned short viWidth; // 0xE
	unsigned short viHeight; // 0x10
	__anon_0x3EC xFBmode; // 0x14
	unsigned char field_rendering; // 0x18
	unsigned char aa; // 0x19
	unsigned char sample_pattern[12][2]; // 0x1A
	unsigned char vfilter[7]; // 0x32
};

// Local to compilation unit
// Location: 0x800F3EE0
static _GXRenderModeObj rmodeobj;

// Local to compilation unit
// Location: 0x80135590
static void *gpHeap;

// Local to compilation unit
// Location: 0x80135594
static void *gArenaHi;

// Local to compilation unit
// Location: 0x80135598
static void *gArenaLo;

// size: 0x20
struct _GXTexObj
{
	unsigned long dummy[8]; // 0x0
};

// Location: 0x1C3F0F80
_GXTexObj g_texMap[4];

// Location: 0x8013559C
_GXRenderModeObj *rmode;

void xlCoreBeforeRender()
{
	// References: rmode (0x8013559C)
}

// Location: 0x20541380
int __OSCurrHeap;

// Location: 0x80135A94
void *DemoFrameBuffer1;

// Location: 0x80135A8C
void *DemoCurrentBuffer;

// Location: 0x80135A90
void *DemoFrameBuffer2;

// size: 0x4
enum _GXTexWrapMode
{
	GX_CLAMP = 0,
	GX_REPEAT = 1,
	GX_MIRROR = 2,
	GX_MAX_TEXWRAPMODE = 3
};

// size: 0x4
enum _GXTexFilter
{
	GX_NEAR = 0,
	GX_LINEAR = 1,
	GX_NEAR_MIP_NEAR = 2,
	GX_LIN_MIP_NEAR = 3,
	GX_NEAR_MIP_LIN = 4,
	GX_LIN_MIP_LIN = 5
};

// size: 0x24
struct __anon_0x9F7
{
	unsigned short height; // 0x0
	unsigned short width; // 0x2
	unsigned long format; // 0x4
	char *data; // 0x8
	_GXTexWrapMode wrapS; // 0xC
	_GXTexWrapMode wrapT; // 0x10
	_GXTexFilter minFilter; // 0x14
	_GXTexFilter magFilter; // 0x18
	float LODBias; // 0x1C
	unsigned char edgeLODEnable; // 0x20
	unsigned char minLOD; // 0x21
	unsigned char maxLOD; // 0x22
	unsigned char unpacked; // 0x23
};

// size: 0x4
enum _GXTlutFmt
{
	GX_TL_IA8 = 0,
	GX_TL_RGB565 = 1,
	GX_TL_RGB5A3 = 2,
	GX_MAX_TLUTFMT = 3
};

// size: 0xC
struct __anon_0xC52
{
	unsigned short numEntries; // 0x0
	unsigned char unpacked; // 0x2
	unsigned char pad8; // 0x3
	_GXTlutFmt format; // 0x4
	char *data; // 0x8
};

// size: 0x8
struct __anon_0xD1E
{
	__anon_0x9F7 *textureHeader; // 0x0
	__anon_0xC52 *CLUTHeader; // 0x4
};

// size: 0x4
struct _GXColor
{
	unsigned char r; // 0x0
	unsigned char g; // 0x1
	unsigned char b; // 0x2
	unsigned char a; // 0x3
};

int main(int nCount, char **aszArgument)
{
	int nSize;
	void *pHeap;
	long nSizeHeap;
	__anon_0xD1E *tdp;
	_GXColor black;
	unsigned long i;
	// References: __OSCurrHeap (0x20541380)
	// References: gpHeap (0x80135590)
	// References: g_texMap (0x1C3F0F80)
	// References: gTgPcTPL (0x20370D80)
	// References: rmode (0x8013559C)
	// References: DemoFrameBuffer2 (0x80135A90)
	// References: DemoCurrentBuffer (0x80135A8C)
	// References: DemoFrameBuffer1 (0x80135A94)
	// References: DefaultFifo (0x80135588)
	// References: DefaultFifoObj (0x8013558C)
	// References: gaszArgument (0x80135584)
	// References: gnCountArgument (0x80135580)
}

int xlCoreGetUpper24MB(void *ppBuffer);

// size: 0x8
union DoubleLongLong
{
	long float f; // 0x0
	signed long long i; // 0x0
};

int xlCoreEnableFPExceptions()
{
	long float control;
	DoubleLongLong d;
}

int xlCoreHiResolution();

int xlCoreGetArgument(int iArgument, char **pszArgument)
{
	// References: gaszArgument (0x80135584)
	// References: gnCountArgument (0x80135580)
}

int xlCoreGetArgumentCount()
{
	// References: gnCountArgument (0x80135580)
}

void xlCoreInitVI()
{
	// References: rmode (0x8013559C)
	// References: DemoFrameBuffer2 (0x80135A90)
	// References: DemoCurrentBuffer (0x80135A8C)
	// References: DemoFrameBuffer1 (0x80135A94)
}

// Local to compilation unit
static void xlCoreInitGX()
{
	unsigned char newFilter[7];
	// References: DemoCurrentBuffer (0x80135A8C)
	// References: rmode (0x8013559C)
}

// Local to compilation unit
static void xlCoreInitMem()
{
	void *arenaLo;
	void *arenaHi;
	unsigned long fbSize;
	// References: DemoFrameBuffer2 (0x80135A90)
	// References: DemoCurrentBuffer (0x80135A8C)
	// References: DemoFrameBuffer1 (0x80135A94)
	// References: rmode (0x8013559C)
	// References: gArenaHi (0x80135594)
	// References: gArenaLo (0x80135598)
}

// Location: 0x601E0F80
_GXRenderModeObj GXNtsc480IntDf;

// Location: 0x800F1E9C
_GXRenderModeObj GXNtsc480Prog;

// Location: 0x141F0F80
_GXRenderModeObj GXPal528IntDf;

// Location: 0x800F1ED8
_GXRenderModeObj GXMpal480IntDf;

// Local to compilation unit
static void xlCoreInitRenderMode(_GXRenderModeObj *mode)
{
	char *szText;
	int iArgument;
	// References: rmodeobj (0x800F3EE0)
	// References: rmode (0x8013559C)
	// References: GXMpal480IntDf (0x800F1ED8)
	// References: GXPal528IntDf (0x141F0F80)
	// References: GXNtsc480Prog (0x800F1E9C)
	// References: gnCountArgument (0x80135580)
	// References: gaszArgument (0x80135584)
	// References: GXNtsc480IntDf (0x601E0F80)
}

int xlCoreReset()
{
	// References: gArenaHi (0x80135594)
	// References: gArenaLo (0x80135598)
	// References: gpHeap (0x80135590)
	// References: __OSCurrHeap (0x20541380)
}

void xlCoreInit(_GXRenderModeObj *mode)
{
	// References: rmode (0x8013559C)
	// References: DemoFrameBuffer2 (0x80135A90)
	// References: DemoCurrentBuffer (0x80135A8C)
	// References: DemoFrameBuffer1 (0x80135A94)
	// References: DefaultFifo (0x80135588)
	// References: DefaultFifoObj (0x8013558C)
	// References: __OSCurrHeap (0x20541380)
}

