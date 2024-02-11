// Local to compilation unit
static int frameEvent(Frame_Class_t *pFrame, int nEvent)
{
	// References: gpSystem (0x561380)
	// References: gnCountMapHack (0x801356C0)
	// References: gbFrameValid (0x80135688)
	// References: gbFrameBegin (0x8013568C)
}

int frameGetDepth(Frame_Class_t *pFrame, unsigned short *pnData, int nAddress)
{
	unsigned int nX;
	unsigned int nY;
	unsigned int nOffset;
	long n64CalcValue;
	int exp;
	int mantissa;
	long compare;
	long val;
	__anon_0x285E5 z_format[8];
	// References: sTempZBuf (0x801085C0)
}

int frameHackCIMG_Panel(__anon_0x2865F *pRDP, Frame_Class_t *pFrame, __anon_0x23B9E *pBuffer, unsigned long long **ppnGBI)
{
	__anon_0x297E0 *pRSP;
	unsigned long long *pnGBI;
	int count;
	int nAddress;
	int sizeX;
	unsigned int nCommandLo;
	unsigned int nCommandHi;
	unsigned short *BG;
	unsigned short *FR;
	unsigned short *pLUT;
	unsigned short *pBitmap16;
	unsigned char *pBitmap8;
	int iTile;
	int nCount;
	__anon_0x247BF *pTile;
	int iTile;
	int nCount;
	int iTile;
	int nCount;
	__anon_0x2ACA3 bg;
	__anon_0x2B091 objTxtr;
	unsigned int nLoadType;
	__anon_0x23B9E *pBG;
	// References: GBIcode2D2$1906 (0x800EAAB4)
	// References: GBIcode3D2$1908 (0x800EAAE4)
	// References: GBIcode3D1$1907 (0x800EAAD0)
}

int frameHackTIMG_Panel(Frame_Class_t *pFrame, __anon_0x23B9E *pBuffer);

void PanelDrawFR3D(unsigned short *FR, unsigned short *LUT, unsigned char *bitmap, int sizeX, int sizeY, int posX, int posY, int first)
{
	int i;
	int j;
	unsigned short color;
}

void PanelDrawBG16(unsigned short *BG, unsigned short *bitmap, int sizeX, int sizeY, int posX, int posY, int flip)
{
	int i;
	int j;
	unsigned short color;
}

void PanelDrawBG8(unsigned short *BG, unsigned short *LUT, unsigned char *bitmap, int sizeX, int sizeY, int posX, int posY, int flip)
{
	int i;
	int j;
	unsigned short color;
}

int frameHackCIMG_Zelda2_Camera(Frame_Class_t *pFrame, __anon_0x23B9E *pBuffer, unsigned int nCommandHi, unsigned int nCommandLo);

int frameHackCIMG_Zelda2_Shrink(__anon_0x2865F *pRDP, Frame_Class_t *pFrame, unsigned long long **ppnGBI)
{
	unsigned long long *pnGBI;
	int count;
	int nAddress;
	unsigned int nCommandLo;
	unsigned int nCommandHi;
	__anon_0x297E0 *pRSP;
	int done;
	__anon_0x2ACA3 bg;
	// References: GBIcode$1816 (0x800EAAA8)
}

int frameHackCIMG_Zelda(Frame_Class_t *pFrame, __anon_0x23B9E *pBuffer, unsigned long long *pnGBI, unsigned int nCommandLo)
{
	unsigned int i;
	unsigned long low2;
	unsigned long high2;
	unsigned short *srcP;
	unsigned short *val;
	unsigned short *valEnd;
	long tile;
	long y;
	long x;
	unsigned char *val;
	unsigned char *valEnd;
	// References: tempLine$1785 (0x801306E0)
	// References: sCopyFrameSyncReceived (0x801356A4)
	// References: gNoSwapBuffer (0x801356BC)
	// References: sNumAddr (0x801356B4)
	// References: sConstantBufAddr (0x801085A0)
	// References: gnCountMapHack (0x801356C0)
	// References: sSrcBuffer (0x801356B0)
	// References: sDestinationBuffer (0x801356AC)
	// References: gpSystem (0x561380)
}

int frameHackCIMG_Zelda2(Frame_Class_t *pFrame, __anon_0x23B9E *pBuffer, unsigned long long *pnGBI)
{
	unsigned int i;
	unsigned long *pGBI;
	// References: sCopyFrameSyncReceived (0x801356A4)
	// References: gNoSwapBuffer (0x801356BC)
	// References: nLastFrame$1695 (0x801356CC)
	// References: nCopyFrame$1697 (0x801356D0)
	// References: sCommandCodes2$1722 (0x800EAA80)
	// References: sCommandCodes$1702 (0x58AA0E80)
}

int frameHackTIMG_Zelda(Frame_Class_t *pFrame, unsigned long long **pnGBI, unsigned int *pnCommandLo, unsigned int *pnCommandHi)
{
	unsigned int i;
	// References: sDestinationBuffer (0x801356AC)
	// References: gpSystem (0x561380)
	// References: sSrcBuffer (0x801356B0)
	// References: sSpecialZeldaHackON (0x801356A8)
	// References: sCommandCodes$1679 (0x38AA0E80)
}

void ZeldaDrawFrameCamera(Frame_Class_t *pFrame, void *buffer)
{
	float matrix[3][4];
	_GXColor color;
	// References: frameObj$1673 (0x801306C0)
}

void ZeldaCopyCamera(unsigned short *buffer);

void ZeldaDrawFrameShrink(Frame_Class_t *pFrame, int posX, int posY, int size)
{
	float matrix[3][4];
	float nX0;
	float nX1;
	float nY0;
	float nY1;
	float scale;
	void *frameBuffer;
	_GXColor color;
	// References: frameObj$1663 (0x801306A0)
	// References: DemoCurrentBuffer (0x80135A8C)
}

void ZeldaDrawFrameHiRes(Frame_Class_t *pFrame, void *pSrc)
{
	float matrix[3][4];
	_GXColor color;
	// References: sFrameObj$1660 (0x80061380)
}

void ZeldaCopyFrameHiRes(void *pSrc)
{
	// References: sCopyFrameSyncReceived (0x801356A4)
}

// Local to compilation unit
static void ZeldaGreyScaleConvert(Frame_Class_t *pFrame)
{
	float matrix[3][4];
	void *dataP;
	_GXColor color;
	// References: sFrameObj$1647 (0x60061380)
	// References: cAlpha$1648 (0x564E1380)
	// References: gHackCreditsColor (0x801356B8)
	// References: DemoCurrentBuffer (0x80135A8C)
}

void CopyAndConvertCFB(unsigned short *srcP)
{
	unsigned short *dataEndP;
	long tile;
	long y;
	long x;
	unsigned short val;
	// References: line$1630 (0x60FC1280)
	// References: sCopyFrameSyncReceived (0x801356A4)
}

void ConvertCFB(unsigned short *srcP)
{
	unsigned short *dataEndP;
	long tile;
	long y;
	long x;
	unsigned short val;
	// References: line$1606 (0x60F21280)
}

void CopyCFB(unsigned short *srcP)
{
	// References: sCopyFrameSyncReceived (0x801356A4)
}

void ConvertZ(unsigned short *srcP)
{
	unsigned short *dataEndP;
	long tile;
	long y;
	long x;
	unsigned short val;
	// References: line$1582 (0x60DE1280)
}

void CopyCFBZTexture(unsigned int *srcP)
{
	// References: sCopyFrameSyncReceived (0x801356A4)
}

void CopyCFBAlpha(unsigned char *srcP)
{
	// References: sCopyFrameSyncReceived (0x801356A4)
}

void ZeldaDrawFrame(Frame_Class_t *pFrame, unsigned short *pData)
{
	float matrix[3][4];
	_GXColor color;
	// References: sFrameObj$1568 (0x40DE1280)
}

void ZeldaDrawFrameBlur(Frame_Class_t *pFrame, unsigned short *pData)
{
	float matrix[3][4];
	_GXColor color;
	// References: sFrameObj$1565 (0x20DE1280)
}

void ZeldaDrawFrameNoBlend(Frame_Class_t *pFrame, unsigned short *pData)
{
	float matrix[3][4];
	// References: sFrameObj$1564 (0xDE1280)
}

void ZeldaDrawFrameZTexture(Frame_Class_t *pFrame, unsigned int *pData)
{
	float matrix[3][4];
	// References: sFrameObj1$1562 (0x8012DDC0)
}

int _frameDrawImage(Frame_Class_t *pFrame, unsigned short *pnImage, int nSizeX, int nSizeY, int nX0, int nY0, int bAlpha)
{
	int iY;
	int iX;
	int nSizeTargetX;
	unsigned int *pnPixel;
	unsigned int *aPixel;
	unsigned int nPixelSource;
	unsigned int nPixelTarget;
	// References: DemoFrameBuffer2 (0x80135A90)
	// References: DemoFrameBuffer1 (0x80135A94)
	// References: DemoCurrentBuffer (0x80135A8C)
}

int _frameDrawRectangle(Frame_Class_t *pFrame, unsigned int nColor, int nX, int nY, int nSizeX, int nSizeY)
{
	int iY;
	int iX;
	unsigned int *pnPixel;
	int nSizeTargetX;
	// References: DemoFrameBuffer2 (0x80135A90)
	// References: DemoFrameBuffer1 (0x80135A94)
	// References: DemoCurrentBuffer (0x80135A8C)
}

int frameEnd(Frame_Class_t *pFrame)
{
	_CPU *pCPU;
	int iHint;
	void *pData;
	// References: gpSystem (0x561380)
	// References: DemoCurrentBuffer (0x80135A8C)
	// References: sCopyFrameSyncReceived (0x801356A4)
	// References: sTempZBuf (0x801085C0)
	// References: gbFrameValid (0x80135688)
	// References: gbFrameBegin (0x8013568C)
}

int frameBegin(Frame_Class_t *pFrame, int nCountVertex)
{
	long i;
	float matrix[3][4];
	// References: ganNameTexCoord (0x800EA8B8)
	// References: ganNameTexMtx (0x800EA898)
	// References: gbFrameValid (0x80135688)
	// References: gbFrameBegin (0x8013568C)
}

int frameBeginOK()
{
	// References: gbFrameValid (0x80135688)
}

int frameSetColor(Frame_Class_t *pFrame, __anon_0x2D223 eType, unsigned int nRGBA);

int frameSetDepth(Frame_Class_t *pFrame, float rDepth, float rDelta);

int frameGetScissor();

int frameSetScissor(Frame_Class_t *pFrame, FrameRectangle *pScissor)
{
	int nTemp;
	int nX0;
	int nY0;
	int nX1;
	int nY1;
}

int frameHide();

int frameShow();

void CopyZBuffer();

int frameDraw();

int frameTick();

// Local to compilation unit
static int frameDrawRectTexture_Setup(Frame_Class_t *pFrame, FrameRectangle *pRectangle)
{
	float matrix[3][4];
	float matrixA[3][4];
	float matrixB[3][4];
	_FRAME_TEXTURE *pTexture[8];
	float rScaleS;
	float rScaleT;
	float rSlideS;
	float rSlideT;
	unsigned int bFlag;
	unsigned int nColors;
	int iTile;
	int firstTile;
	int nCount;
	int iIndex;
	char cTempAlpha;
	// References: bSkip$1410 (0x801356C8)
	// References: gpSystem (0x561380)
	// References: ganNameTexMtx (0x800EA898)
	// References: sSpecialZeldaHackON (0x801356A8)
}

// Local to compilation unit
static int frameDrawRectTexture(Frame_Class_t *pFrame, FrameRectangle *pRectangle)
{
	int bCopy;
	float rDepth;
	float rDeltaT;
	float rX0;
	float rY0;
	float rX1;
	float rY1;
	float rS0;
	float rT0;
	float rS1;
	float rT1;
	// References: gnCountMapHack (0x801356C0)
	// References: gpSystem (0x561380)
	// References: sSpecialZeldaHackON (0x801356A8)
	// References: nCounter$1367 (0x801356C4)
}

// Local to compilation unit
static int frameDrawRectFill_Setup(Frame_Class_t *pFrame, FrameRectangle *pRectangle)
{
	int bFlag;
	int nColors;
}

// Local to compilation unit
static int frameDrawRectFill(Frame_Class_t *pFrame, FrameRectangle *pRectangle)
{
	int bFlag;
	float rDepth;
	float rX0;
	float rY0;
	float rX1;
	float rY1;
}

// Local to compilation unit
static int frameDrawLine_Setup(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int bFlag;
	int nColors;
	// References: gapfDrawLine (0x800EA9B4)
}

// Local to compilation unit
static int frameDrawLine_C2T2(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
}

// Local to compilation unit
static int frameDrawLine_C1T2(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
	__anon_0x23FC4 *pVertexColor;
}

// Local to compilation unit
static int frameDrawLine_C0T2(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
}

// Local to compilation unit
static int frameDrawLine_C2T0(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
}

// Local to compilation unit
static int frameDrawLine_C1T0(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
	__anon_0x23FC4 *pVertexColor;
}

// Local to compilation unit
static int frameDrawLine_C0T0(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
}

// Local to compilation unit
static int frameDrawTriangle_Setup(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int bFlag;
	int nColors;
	// References: gapfDrawTriangle (0x800EA994)
}

// Local to compilation unit
static int frameDrawTriangle_C3T3(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	float *pMatrix[4];
	// References: gHackCreditsColor (0x801356B8)
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int frameCheckTriangleDivide(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 aNewVertArray[8];
	float fInterp;
	float fTempColor1;
	float fTempColor2;
	unsigned int nNewVertCount;
	unsigned int bInFront;
	unsigned int bBehind;
}

// Local to compilation unit
static int frameDrawTriangle_C1T3(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
	__anon_0x23FC4 *pVertexColor;
}

// Local to compilation unit
static int frameDrawTriangle_C0T3(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
}

// Local to compilation unit
static int frameDrawTriangle_C3T0(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
}

// Local to compilation unit
static int frameDrawTriangle_C1T0(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
	__anon_0x23FC4 *pVertexColor;
}

// Local to compilation unit
static int frameDrawTriangle_C0T0(Frame_Class_t *pFrame, FramePrimitive *pPrimitive)
{
	int iData;
	unsigned char *anData;
	__anon_0x23FC4 *pVertex;
}

// Local to compilation unit
static int frameDrawSetupDP(Frame_Class_t *pFrame, int *pnColors, int *pbFlag)
{
	unsigned int nMode;
	long numCycles;
	unsigned long mode;
	unsigned long cycle;
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int frameGetCombineAlpha(_GXTevAlphaArg *pnAlphaTEV, int nAlphaN64);

// Local to compilation unit
static int frameGetCombineColor(_GXTevColorArg *pnColorTEV, int nColorN64);

// Local to compilation unit
static int frameDrawSetupSP(Frame_Class_t *pFrame, int *pnColors, int *pbFlag, int nVertexCount)
{
	float rValue23;
	int bTextureGen;
	float rNear;
	float rFar;
	float rScaleS;
	float rScaleT;
	float rSlideS;
	float rSlideT;
	_FRAME_TEXTURE *pTexture[8];
	int nColors;
	int bFlag;
	int iTile;
	int iHint;
	float matrix[3][4];
	float matrixA[3][4];
	float matrixB[3][4];
	float matrix44[4][4];
	float matrixProjection[4][4];
	_GXProjectionType eTypeProjection;
	float scale;
	int nCount;
	int iIndex;
	// References: ganNameTexMtx (0x800EA898)
	// References: snScissorChanged (0x80135690)
	// References: snScissorWidth (0x8013569C)
	// References: snScissorHeight (0x801356A0)
	// References: snScissorYOrig (0x80135698)
	// References: snScissorXOrig (0x80135694)
}

int frameDrawSetup2D(Frame_Class_t *pFrame)
{
	float matrix44[4][4];
	// References: snScissorChanged (0x80135690)
	// References: snScissorHeight (0x801356A0)
	// References: snScissorWidth (0x8013569C)
	// References: snScissorYOrig (0x80135698)
	// References: snScissorXOrig (0x80135694)
}

// Local to compilation unit
static int frameLoadTexture(Frame_Class_t *pFrame, _FRAME_TEXTURE *pTexture, int iTextureCode, __anon_0x247BF *pTile)
{
	void *pData;
	int iName;
	int nFilter;
	_GXTexWrapMode eWrapS;
	_GXTexWrapMode eWrapT;
	// References: ganNamePixel (0x78A80E80)
	// References: ganNameColor (0x58A80E80)
}

int frameFreePixels(Frame_Class_t *pFrame, _FRAME_TEXTURE *pTexture);

// Local to compilation unit
static int frameMakePixels(Frame_Class_t *pFrame, _FRAME_TEXTURE *pTexture, __anon_0x247BF *pTile, int bReload)
{
	void *aPixel;
	int nSizeLine;
	int nFlip;
	int nSize;
	int nCount;
	int nMode;
	int nSizeX;
	int nSizeY;
	int nSource;
	int nTarget;
	int iPixelX;
	int iPixelY;
	int iTarget;
	unsigned char nData8;
	unsigned short nData16;
	unsigned int nData32;
	int nSizeTextureX;
	int nSizeTextureY;
	long lineX;
	long lineY;
	long linePixX;
	long lineStep;
	long tmemStart;
	long tmemEnd;
	int __nSizeX;
	int __nSizeY;
	unsigned int rgb[3];
	unsigned int yuv[3];
	// References: sRemapI$746 (0x80134DD8)
}

int frameFreeTLUT(Frame_Class_t *pFrame, _FRAME_TEXTURE *pTexture);

// Local to compilation unit
static int frameMakeTLUT(Frame_Class_t *pFrame, _FRAME_TEXTURE *pTexture, int nCount, int nOffsetTMEM, int bReload)
{
	int iColor;
	unsigned short *anColor;
	unsigned short nData16;
}

void __DEMODoneRender()
{
	// References: DemoCurrentBuffer (0x80135A8C)
}

void *DeallocateWrapper(void *dataP);

void *AllocateWrapper(unsigned long size)
{
	void *tempP;
}

// Local to compilation unit
static void frameDrawDone()
{
	// References: gNoSwapBuffer (0x801356BC)
	// References: DemoCurrentBuffer (0x80135A8C)
	// References: DemoFrameBuffer2 (0x80135A90)
	// References: DemoFrameBuffer1 (0x80135A94)
	// References: gbFrameValid (0x80135688)
}

int frameSetVertexArray();

// Local to compilation unit
static void frameDrawSyncCallback(unsigned short nToken)
{
	// References: sCopyFrameSyncReceived (0x801356A4)
}

// Local to compilation unit
static int frameDrawSetupFog_Default(Frame_Class_t *pFrame)
{
	int iHint;
	float rNear;
	float rFar;
	float rFOVY;
	float matrixProjection[4][4];
	_GXFogAdjTable fogTable;
	float rMax;
	float rMin;
	float rIntpV;
	float rMinimum;
	float rMultiplier;
	float rOffset;
}

// Local to compilation unit
static int frameDrawSetupFog_Zelda1(Frame_Class_t *pFrame)
{
	_GXFogType nFogType;
	float rNear;
	float rFar;
	unsigned int nMode;
	unsigned int iHint;
	float rFogNear;
	float rFogFar;
	float rFogMin;
	float rFogMax;
	float rMultiplier;
	float rOffset;
	float rMinimum;
	float rMaximum;
	float dplane;
	float dplane;
	float dplane;
	float dplane;
	float dplane;
	float rFarScale;
	float rNearScale;
	// References: gpSystem (0x561380)
}

int frameSetProjection(Frame_Class_t *pFrame, int iHint)
{
	__anon_0x24A81 *pHint;
}

