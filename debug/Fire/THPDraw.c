void THPGXRestore();

// size: 0x4
enum __anon_0x14611
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
enum __anon_0x1475B
{
	VI_XFBMODE_SF = 0,
	VI_XFBMODE_DF = 1
};

// size: 0x3C
struct _GXRenderModeObj
{
	__anon_0x14611 viTVmode; // 0x0
	unsigned short fbWidth; // 0x4
	unsigned short efbHeight; // 0x6
	unsigned short xfbHeight; // 0x8
	unsigned short viXOrigin; // 0xA
	unsigned short viYOrigin; // 0xC
	unsigned short viWidth; // 0xE
	unsigned short viHeight; // 0x10
	__anon_0x1475B xFBmode; // 0x14
	unsigned char field_rendering; // 0x18
	unsigned char aa; // 0x19
	unsigned char sample_pattern[12][2]; // 0x1A
	unsigned char vfilter[7]; // 0x32
};

void THPGXYuv2RgbSetup(_GXRenderModeObj *rmode)
{
	long scrWidth;
	long scrHeight;
	float pMtx[4][4];
	float mMtx[3][4];
}

// size: 0x20
struct _GXTexObj
{
	unsigned long dummy[8]; // 0x0
};

void THPGXYuv2RgbDraw(unsigned char *y_data, unsigned char *u_data, unsigned char *v_data, signed short x, signed short y, signed short textureWidth, signed short textureHeight, signed short polygonWidth, signed short polygonHeight)
{
	_GXTexObj tobj0;
	_GXTexObj tobj1;
	_GXTexObj tobj2;
}

