// Local to compilation unit
static int rspParseJPEG_DecodeZ(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	int y;
	signed short *temp;
	signed short *temp2;
	unsigned long long *system_imb;
	unsigned int *infoStruct;
	int size;
}

// Local to compilation unit
static int rspParseJPEG_EncodeZ(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	int y;
	signed short *temp;
	signed short *temp2;
	unsigned long long *system_imb;
	unsigned int *infoStruct;
	int size;
}

int rspRecon420Z(__anon_0x5845E *pRSP, signed short *imgBuf)
{
	int i;
	int j;
	int r;
	int g;
	int b;
	int y;
	int u;
	int v;
}

int rspLoadColorBufferZ(int *r, int *g, int *b, signed short *imgBuf, int index);

int rspUndoRecon420Z(__anon_0x5845E *pRSP, signed short *imgBuf)
{
	int i;
	int j;
	int r;
	int g;
	int b;
	int y;
	int u;
	int v;
}

int rspUndoLoadColorBufferZ(int r, int g, int b, signed short *imgBuf, int index);

void rspUndoDCTZ(__anon_0x5845E *pRSP)
{
	int c;
	int i;
	int j;
	int dd;
	signed short t[8][8];
}

void rspUndoZigzagDataZ(__anon_0x5845E *pRSP, signed short *dataBuf)
{
	int c;
}

void rspUndoQuantizeZ(__anon_0x5845E *pRSP, signed short *dataBuf)
{
	int c;
	int i;
}

void rspZigzagDataZ(__anon_0x5845E *pRSP, signed short *dataBuf)
{
	int c;
}

// Local to compilation unit
static void rspQuantizeZ(__anon_0x5845E *pRSP, signed short *dataBuf)
{
	int c;
	int i;
}

// Local to compilation unit
static void rspDCTZ(__anon_0x5845E *pRSP)
{
	int c;
	int i;
	int j;
	int dd;
	signed short t[8][8];
}

int rspDestroyJPEGArraysZ();

// Local to compilation unit
static int rspCreateJPEGArraysZ(__anon_0x5845E *pRSP, int qYAddress, int qCbAddress, int qCrAddress);

// Local to compilation unit
static int rspParseJPEG_Decode(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	int i;
	int y;
	unsigned char *temp;
	unsigned char *temp2;
	unsigned long long *system_imb;
	int size;
	int scale;
}

// Local to compilation unit
static int rspParseJPEG_Encode(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	unsigned char *temp;
	unsigned char *temp2;
	int i;
	int j;
	int x;
	int y;
	unsigned char *system_imb;
	unsigned char *system_cfb;
	int scale;
}

void rspFormatYUV(__anon_0x5845E *pRSP, char *imgBuf)
{
	int i;
	int j;
}

void rspUndoYUVtoDCTBuf(__anon_0x5845E *pRSP)
{
	int i;
	int j;
}

void rspUndoDCT(__anon_0x5845E *pRSP)
{
	int c;
	int i;
	int j;
	int dd;
	signed short t[8][8];
}

void rspUndoQuantize(__anon_0x5845E *pRSP, int scale)
{
	int c;
	int i;
	int j;
	signed short q;
	signed short s;
}

void rspUndoZigzagData(__anon_0x5845E *pRSP, unsigned char **databuf, int n, int *preDc)
{
	signed short Dc;
	signed short Ac;
	int i;
	int z;
}

void rspZigzagData(__anon_0x5845E *pRSP, unsigned char **databuf, int n, int *preDc)
{
	signed short Ac;
	int i;
	int z;
}

// Local to compilation unit
static void rspQuantize(__anon_0x5845E *pRSP, int scale)
{
	int c;
	int i;
	int j;
	signed short q;
	signed short s;
}

// Local to compilation unit
static void rspDCT(__anon_0x5845E *pRSP)
{
	int c;
	int i;
	int j;
	int dd;
	signed short t[8][8];
}

// Local to compilation unit
static void rspYUVtoDCTBuf(__anon_0x5845E *pRSP)
{
	int i;
}

// Local to compilation unit
static void rspConvertRGBAtoYUV(__anon_0x5845E *pRSP)
{
	int i;
	int j;
	long Y;
	long U;
	long V;
}

void rspConvertBufferToRGBA(unsigned char *buf, __anon_0x58360 *rgba);

int rspDestroyJPEGArrays();

// Local to compilation unit
static int rspCreateJPEGArrays(__anon_0x5845E *pRSP);

