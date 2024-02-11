// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// Location: 0x10561380
unsigned char *gBufferP;

// Location: 0x20541380
int __OSCurrHeap;

void MovieDestroy()
{
	// References: gBufferP (0x10561380)
	// References: __OSCurrHeap (0x20541380)
}

// size: 0x4
enum __anon_0xEF02
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
enum __anon_0xF04A
{
	VI_XFBMODE_SF = 0,
	VI_XFBMODE_DF = 1
};

// size: 0x3C
struct _GXRenderModeObj
{
	__anon_0xEF02 viTVmode; // 0x0
	unsigned short fbWidth; // 0x4
	unsigned short efbHeight; // 0x6
	unsigned short xfbHeight; // 0x8
	unsigned short viXOrigin; // 0xA
	unsigned short viYOrigin; // 0xC
	unsigned short viWidth; // 0xE
	unsigned short viHeight; // 0x10
	__anon_0xF04A xFBmode; // 0x14
	unsigned char field_rendering; // 0x18
	unsigned char aa; // 0x19
	unsigned char sample_pattern[12][2]; // 0x1A
	unsigned char vfilter[7]; // 0x32
};

// Location: 0x8013559C
_GXRenderModeObj *rmode;

void MovieDraw()
{
	// References: rmode (0x8013559C)
}

void MovieUpdate();

void MovieInit()
{
	char *szText;
	unsigned long size;
	// References: gBufferP (0x10561380)
	// References: __OSCurrHeap (0x20541380)
}

