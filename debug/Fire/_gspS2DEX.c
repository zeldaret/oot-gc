// Local to compilation unit
static int rspSetupS2DEX(__anon_0x5845E *pRSP)
{
	float fL;
	float fR;
	float fB;
	float fT;
	__anon_0x5A89F *pFrame;
}

// Local to compilation unit
static int rspObjMatrix(__anon_0x5845E *pRSP, int nAddress)
{
	unsigned int *pnData32;
	unsigned short *pnData16;
	unsigned char *pObjMtx;
	unsigned short nBaseScaleX;
	unsigned short nBaseScaleY;
	int nA;
	int nB;
	int nC;
	int nD;
	signed short nY;
}

int rspObjSubMatrix(__anon_0x5845E *pRSP, int nAddress)
{
	unsigned short *pnData16;
	unsigned char *pObjSubMtx;
	unsigned short nBaseScaleX;
	unsigned short nBaseScaleY;
	signed short nY;
}

int rspBgRectCopy(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, int nAddress)
{
	__anon_0x5F2FB bg;
	__anon_0x5F2FB bgScale;
	unsigned int nOldMode1;
	unsigned int nOldMode2;
	// References: flagBilerp (0x80135790)
	// References: scissorY1 (0x801352D6)
	// References: scissorX1 (0x801352D4)
	// References: scissorY0 (0x8013578E)
	// References: scissorX0 (0x8013578C)
}

int rspObjLoadTxSprite(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, int nAddress);

int rspObjLoadTxRectR(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, int nAddress);

int rspObjLoadTxRect(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, int nAddress);

// Local to compilation unit
static int rspObjRectangleR(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, int nAddress)
{
	unsigned short nSizLineBytes;
	float fLeft;
	float fRight;
	float fTop;
	float fBottom;
	float fTexRight;
	float fTexBottom;
	float fTexLeft;
	float fTexTop;
	int nTexTrim2;
	int nTexTrim5;
	float fSpriteWidth;
	float fSpriteHeight;
	int nClampSetting;
	__anon_0x5F63B objSprite;
	__anon_0x5A2EC *pTile;
	__anon_0x5EBE0 primitive;
	float mtxTransL[3][4];
	float mtxTransW[3][4];
	float mtxScale[3][4];
	float mtxTemp[3][4];
	float mtxOut[3][4];
	__anon_0x5F6E9 vecIn;
	__anon_0x5F6E9 vecOut;
}

// Local to compilation unit
static int rspObjSprite(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, int nAddress)
{
	unsigned short nSizLineBytes;
	float fLeft;
	float fRight;
	float fTop;
	float fBottom;
	float fTexRight;
	float fTexBottom;
	float fTexLeft;
	float fTexTop;
	float fScaleX;
	float fScaleY;
	float fSpriteWidth;
	float fSpriteHeight;
	int nTexTrim2;
	int nTexTrim5;
	int nClampSetting;
	__anon_0x5F63B objSprite;
	__anon_0x5A2EC *pTile;
	__anon_0x5EBE0 primitive;
	float mtxTransL[3][4];
	float mtxTransW[3][4];
	float mtxScale[3][4];
	float mtxTemp[3][4];
	float mtxOut[3][4];
	__anon_0x5F6E9 vecIn;
	__anon_0x5F6E9 vecOut;
}

// Local to compilation unit
static int rspObjRectangle(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, int nAddress)
{
	unsigned short nSizLineBytes;
	float fDeltaS;
	float fDeltaT;
	__anon_0x5F63B objSprite;
	__anon_0x5A2EC *pTile;
	__anon_0x5F759 primitive;
	int nClampSetting;
	int nTexTrim2;
	int nTexTrim5;
}

// Local to compilation unit
static int rspObjLoadTxtr(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, int nAddress)
{
	unsigned int nSizDefine;
	unsigned int nLoadType;
	int nAddr;
	__anon_0x5A2EC *pTile;
	__anon_0x59558 *pBuffer;
	__anon_0x5FC1B objTxtr;
}

int rspFillObjTxtr(__anon_0x5845E *pRSP, int nAddress, __anon_0x5FC1B *pTxtr, unsigned int *pLoadType)
{
	unsigned int *pnData32;
	unsigned short *pnData16;
	unsigned char *pTxtrBlock;
	unsigned int nLoadType;
}

// Local to compilation unit
static int guS2DEmuBgRect1Cyc(__anon_0x5845E *pRSP, __anon_0x5A89F *pFrame, __anon_0x5F2FB *pBG)
{
	signed short frameX0;
	signed short frameX1;
	signed short framePtrY0;
	signed short frameRemain;
	signed short imageX0;
	signed short imageY0;
	signed short imageSliceW;
	signed short imageW;
	int imageYorig;
	signed short scaleW;
	signed short scaleH;
	signed short imageSrcW;
	signed short imageSrcH;
	signed short imageSliceLines;
	int frameSliceLines;
	int frameSliceCount;
	unsigned short imageS;
	unsigned short imageT;
	unsigned int imagePtr;
	signed short imageISliceL0;
	signed short imageIY0;
	int frameLSliceL0;
	signed short pixX0;
	signed short pixY0;
	signed short pixX1;
	signed short pixY1;
	signed short frameY0;
	signed short frameW;
	signed short frameH;
	int frameWmax;
	int frameHmax;
	signed short tmemSize;
	signed short tmemMask;
	signed short tmemShift;
	int imageNumSlice;
	int imageSliceWmax;
	int imageLYoffset;
	int frameLYoffset;
	int imageLHidden;
	int frameLHidden;
	int frameLYslice;
	signed short imageRemain;
	signed short imageSliceH;
	signed short frameSliceH;
	__anon_0x5F759 primitive;
	signed short nT;
	signed short framePtrY1;
	// References: flagBilerp (0x80135790)
	// References: tmemSrcLines (0x801357A8)
	// References: imageSrcWsize (0x8013579E)
	// References: imageTop (0x801357A4)
	// References: imagePtrX0 (0x801357A2)
	// References: tmemSliceWmax (0x8013579C)
	// References: rdpSetTile_w0 (0x80135798)
	// References: rdpSetTimg_w0 (0x80135794)
	// References: TMEMSHIFT$3465 (0x801352E0)
	// References: TMEMMASK$3464 (0x801352D8)
	// References: TMEMSIZE$3463 (0x70E20E80)
	// References: flagSplit (0x801357A0)
	// References: scissorY1 (0x801352D6)
	// References: scissorX1 (0x801352D4)
	// References: scissorY0 (0x8013578E)
	// References: scissorX0 (0x8013578C)
}

// Local to compilation unit
static int tmemLoad(__anon_0x5A89F *pFrame, __anon_0x5845E *pRSP, unsigned int *imagePtr, signed short *imageRemain, signed short drawLines, signed short flagBilerp)
{
	signed short loadLines;
	signed short iLoadable;
	signed short SubSliceL2;
	signed short SubSliceD2;
	signed short SubSliceY2;
	unsigned int imageTopSeg;
	unsigned int imagePtr2;
	unsigned int imagePtr1A;
	unsigned int imagePtr1B;
	signed short SubSliceY1;
	signed short SubSliceL1;
	signed short tmemSH_A;
	signed short tmemSH_B;
	// References: imageSrcWsize (0x8013579E)
	// References: imageTop (0x801357A4)
	// References: imagePtrX0 (0x801357A2)
	// References: tmemSrcLines (0x801357A8)
	// References: tmemSliceWmax (0x8013579C)
	// References: flagSplit (0x801357A0)
}

// Local to compilation unit
static int tmemLoad_A(__anon_0x5A89F *pFrame, __anon_0x5845E *pRSP, unsigned int imagePtr, signed short loadLines, signed short tmemAdrs, signed short tmemSH)
{
	// References: tmemSliceWmax (0x8013579C)
}

// Local to compilation unit
static int tmemLoad_B(__anon_0x5A89F *pFrame, __anon_0x5845E *pRSP, unsigned int imagePtr, signed short loadLines, signed short tmemSH)
{
	__anon_0x59558 *pBuffer;
	int nAddr;
	// References: imageSrcWsize (0x8013579E)
}

int guS2DEmuSetScissor(unsigned int ulx, unsigned int uly, unsigned int lrx, unsigned int lry, unsigned char flag)
{
	// References: flagBilerp (0x80135790)
	// References: scissorY1 (0x801352D6)
	// References: scissorX1 (0x801352D4)
	// References: scissorY0 (0x8013578E)
	// References: scissorX0 (0x8013578C)
}

int rspSetTileSize(__anon_0x5A89F *pFrame, __anon_0x5A2EC *pTile, int nX0, int nY0, int nX1, int nY1);

int rspLoadTile(__anon_0x5A89F *pFrame, __anon_0x5A2EC *pTile, int nX0, int nY0, int nX1, int nY1);

int rspLoadBlock(__anon_0x5A89F *pFrame, __anon_0x5A2EC *pTile, int nX0, int nY0, int nX1, int nY1);

int rspSetImage(__anon_0x5A89F *pFrame, __anon_0x5845E *pRSP, int nFormat, int nWidth, int nSize, int nImage)
{
	int addr;
	__anon_0x59558 *pBuffer;
}

int rspSetTile(__anon_0x5A89F *pFrame, __anon_0x5A2EC *pTile, int nSize, int nTmem, int nTLUT, int nFormat, int nMaskS, int nMaskT, int nModeS, int nModeT, int nShiftS, int nShiftT);

int rspFillObjBg(__anon_0x5845E *pRSP, int nAddress, __anon_0x5F2FB *pBg)
{
	unsigned char *pnData8;
	unsigned char *pObjBg;
	unsigned short *pnData16;
}

int rspFillObjBgScale(__anon_0x5845E *pRSP, int nAddress, __anon_0x5F2FB *pBg)
{
	unsigned char *pnData8;
	unsigned char *pObjBg;
	unsigned short *pnData16;
	unsigned int *pnData32;
}

// Local to compilation unit
static int rspFillObjSprite(__anon_0x5845E *pRSP, int nAddress, __anon_0x5F63B *pSprite)
{
	unsigned short *pnData16;
	unsigned char *pnData8;
	unsigned char *pObjSprite;
}

// Local to compilation unit
static int Matrix4by4Identity(float *matrix4b4[4]);

int frameFillVertex(__anon_0x5A89F *pFrame, int nIndex, signed short nX, signed short nY, signed short nZ, float rS, float rT);

