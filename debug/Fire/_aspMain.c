// Local to compilation unit
static int rspParseABI4(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	unsigned int nCommandLo;
	unsigned int nCommandHi;
	unsigned int *pABI32;
	unsigned int *pABILast32;
	unsigned int nSize;
	// References: nFirstTime$2796 (0x801352D0)
}

int rspADMEMMove4(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned short nDMEMOut;
	unsigned short nCount;
	unsigned int nDMEMIn;
}

int rspAInterleave4(__anon_0x5845E *pRSP, unsigned int nCommandLo)
{
	unsigned int iIndex;
	unsigned int iIndex2;
}

int rspARingFilter4();

// Local to compilation unit
static int rspInitAudioDMEM4(__anon_0x5845E *pRSP);

// Local to compilation unit
static int rspParseABI3(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	unsigned int nCommandLo;
	unsigned int nCommandHi;
	unsigned int *pABI32;
	unsigned int *pABILast32;
	unsigned int nSize;
	// References: nFirstTime$2757 (0x801352CC)
}

int rspADMEMCopy(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi);

// Local to compilation unit
static int rspAMix3(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned int i;
	unsigned int nCount;
	signed short *srcP;
	int outData32;
}

int rspAHalfCut3(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	int count;
	int outp;
	int inpp;
	int i;
}

// Local to compilation unit
static int rspAEnvMixer3(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned short vParams[8];
	int i;
	int j;
	int inpp;
	int outL;
	int outR;
	int outFL;
	int outFR;
	int count;
	long id;
	int waveL;
	int waveR;
	int waveI;
	int srcL;
	int srcR;
	int srcFXL;
	int srcFXR;
}

int rspASaveBuffer3(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	void *pData;
}

int rspALoadBuffer3(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	void *pData;
}

int rspASetEnvParam32(__anon_0x5845E *pRSP, unsigned int nCommandLo);

int rspASetEnvParam3(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi);

// Local to compilation unit
static int rspInitAudioDMEM3(__anon_0x5845E *pRSP);

// Local to compilation unit
static int rspParseABI2(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	unsigned int nCommandLo;
	unsigned int nCommandHi;
	unsigned int *pABI32;
	unsigned int *pABILast32;
	unsigned int nSize;
	// References: nFirstTime$2648 (0x801352C8)
}

// Local to compilation unit
static int rspAPCM8Dec2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	int inpp;
	int outp;
	int count;
	signed short flags;
	signed short vtmp0[8];
	signed short vtmp1[8];
	int i;
	int j;
	int stateAddr;
	int s;
	void *pData;
	signed short *pStateAddress;
	signed short *pTempStateAddr;
}

int rspASaveBuffer2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	void *pData;
}

int rspALoadBuffer2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	void *pData;
}

// Local to compilation unit
static int rspAEnvMixer2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	signed short vStep[8];
	unsigned short vParams[8];
	int i;
	int j;
	int inpp;
	int outL;
	int outR;
	int outFL;
	int outFR;
	int count;
	int temp;
	long id;
	int waveL;
	int waveR;
	int waveI;
	int srcL;
	int srcR;
	int srcFXL;
	int srcFXR;
}

int rspASetEnvParam22(__anon_0x5845E *pRSP, unsigned int nCommandLo)
{
	signed short tmp;
}

int rspASetEnvParam2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	signed short temp;
}

int rspAHalfCut2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	int count;
	int outp;
	int inpp;
	int i;
}

int rspADMEMCopy2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi);

int rspASetLoop2(__anon_0x5845E *pRSP, unsigned int nCommandLo);

// Local to compilation unit
static int rspADistFilter2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	signed short dpow;
	int i;
	signed long long mult;
}

// Local to compilation unit
static int rspAInterleave2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	int outp;
	int inpr;
	int inpl;
	int count;
	int i;
}

// Local to compilation unit
static int rspAMix2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned int i;
	unsigned int nCount;
	signed short *srcP;
	int outData32;
}

int rspALoadADPCM2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	void *pData;
}

int rspADMEMMove2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi);

int rspAWMEMCopy2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi);

int rspASetBuffer2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned short nDMEMIn;
	unsigned short nDMEMOut;
	unsigned short nCount;
}

// Local to compilation unit
static int rspAFirFilter2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	int filterState;
	int filterTable;
	int i;
	int pointer;
	void *pData;
	signed short *pStateAddress;
	signed short flag;
	signed short vANS[8];
	signed short vOLD[8];
	signed short vTP1[8];
	signed short vT0[8];
	int accumulator[8];
	int temp32[8];
	int stateAddr;
	signed short anMatrix[8];
	signed short anInputVec[15];
	// References: counter$2409 (0x80135788)
}

int rspASResample2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	int outp;
	int outCount;
	int pitchSpeed;
	int i;
	int mainCounter;
}

// Local to compilation unit
static int rspAResample2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	signed short *srcP;
	signed short *dstP;
	signed short lastValue;
	unsigned short nCount;
	unsigned short i;
	int nSrcStep;
	int nCursorPos;
	unsigned int scratch;
	unsigned char flags;
	signed short *pData;
}

// Local to compilation unit
static int rspANMix2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned int nCount;
	unsigned int i;
	signed short *inP;
	int out;
}

// Local to compilation unit
static int rspANoise2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned int nDest;
	unsigned int nSource;
	unsigned int nCount;
	unsigned int i;
	unsigned int j;
	signed short vIn[16];
	signed short vOut[16];
	signed long long accumulator[8];
}

int rspAClearBuffer2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi);

int rspAADPCMDec2(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned char nFlags;
	char *pDMEM8;
	int anCoef[8];
	signed short anIData1[8];
	signed short anOData0[8];
	signed short *pStateAddress;
	signed short *pDMEM16;
	signed short anOData1[8];
	signed short anIData0[8];
	signed short anInputVec[10];
	int nDMEMIn8;
	int nDMEMOut;
	int nCount;
	int nSrcAddress;
	int nOptPred;
	int nHeaderBase8;
	int nVScale;
	int nScaleI;
	int i;
	int nHeader;
	int nTIndex;
	signed short *pTempStateAddr;
}

// Local to compilation unit
static int rspAADPCMDec2Fast(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned char nFlags;
	unsigned char ucControl;
	char *pHeader;
	signed short *pStateAddress;
	signed short anIData0;
	int nDMEMOut;
	int nCount;
	int nSrcAddress;
	int nOptPred;
	int nVScale;
	int i;
	unsigned int dwDecodeSelect;
	unsigned int n;
	int nA;
	int nB;
	signed short nSamp1;
	signed short nSamp2;
	signed short *pTempStateAddr;
	signed short nibble[4];
	int nOutput;
}

// Local to compilation unit
static int rspInitAudioDMEM2(__anon_0x5845E *pRSP);

// Local to compilation unit
static int rspParseABI1(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	unsigned int nCommandLo;
	unsigned int nCommandHi;
	unsigned int *pABI32;
	unsigned int *pABILast32;
	unsigned int nSize;
	// References: nFirstTime$2148 (0x801352C4)
}

// Local to compilation unit
static int rspParseABI(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	unsigned char *pFUCode;
	unsigned int nCheckSum;
}

int rspALoadADPCM1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	void *pData;
	unsigned int nCount;
	int nAddress;
}

int rspADMEMMove1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned short nDMEMOut;
	unsigned short nCount;
	unsigned int nDMEMIn;
}

int rspASetLoop1(__anon_0x5845E *pRSP, unsigned int nCommandLo);

// Local to compilation unit
static int rspASetVolume1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned short nFlags;
	unsigned short v;
	unsigned short t;
	unsigned short r;
}

// Local to compilation unit
static int rspASetBuffer1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned short nDMEMIn;
	unsigned short nDMEMOut;
	unsigned short nCount;
}

int rspASegment1(__anon_0x5845E *pRSP, unsigned int nCommandLo);

int rspASaveBuffer1(__anon_0x5845E *pRSP, unsigned int nCommandLo)
{
	unsigned int nSize;
	unsigned int *pData;
	int nAddress;
}

// Local to compilation unit
static int rspAResample1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	signed short *srcP;
	signed short *dstP;
	signed short lastValue;
	unsigned short nCount;
	unsigned short i;
	int nSrcStep;
	int nCursorPos;
	int nExtra;
	unsigned int scratch;
	unsigned char flags;
	signed short *pData;
}

// Local to compilation unit
static int rspAMix1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned int i;
	unsigned int nCount;
	signed short *srcP;
	int outData32;
}

int rspAInterleave1(__anon_0x5845E *pRSP, unsigned int nCommandLo)
{
	unsigned short nLeft;
	unsigned int iIndex;
	unsigned int iIndex2;
}

// Local to compilation unit
static int rspAEnvMixer1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned char nFlags;
	unsigned int s;
	signed short *pStateAddress;
	unsigned short anRamp[8];
	int envVolRateL;
	int envVolRateR;
	int envVolFinalL;
	int envVolFinalR;
	int volVecL[8];
	int volVecR[8];
	signed short anOutL;
	signed short anOutR;
	signed short anAuxL;
	signed short anAuxR;
	signed short anIn;
	unsigned int nInptr;
	unsigned int nOutptrL;
	unsigned int nOutptrR;
	unsigned int nAuxptrL;
	unsigned int nAuxptrR;
	unsigned int i;
	unsigned int nSrcAddress;
	unsigned int nLoopCtl;
	int nUpDownVolL;
	int nUpDownVolR;
	void *pData;
	int *dataP;
	signed long long tempL;
	signed long long tempR;
	signed long long totalL;
	signed long long totalR;
	signed long long resultL;
	signed long long resultR;
	int volL;
	int volR;
	signed long long temp;
	int *dataP;
}

int rspAClearBuffer1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi);

// Local to compilation unit
static int rspAPoleFilter1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned char nFlags;
	unsigned short nScale;
	signed short anCoef[10][8];
	signed short anEntries[8];
	signed short nVTemp[8];
	signed short nTempScale;
	signed short anIData0[8];
	signed short anOData0[8];
	signed short anInputVec[10];
	signed short *pStateAddress;
	signed short *pDMEM16;
	int nDMEMIn;
	int nDMEMOut;
	int nCount;
	int nSrcAddress;
}

int rspAADPCMDec1(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned char nFlags;
	char *pDMEM8;
	char *pHeader;
	int anCoef[8];
	signed short anIData0[8];
	signed short anOData0[8];
	signed short *pStateAddress;
	signed short *pDMEM16;
	signed short anInputVec[10];
	int nDMEMOut;
	int nCount;
	int nSrcAddress;
	int nOptPred;
	int nVScale;
	int nScaleI;
	int i;
	int nHeader;
	int nToggle;
	int nTIndex;
	signed short *pTempStateAddr;
}

// Local to compilation unit
static int rspAADPCMDec1Fast(__anon_0x5845E *pRSP, unsigned int nCommandLo, unsigned int nCommandHi)
{
	unsigned char nFlags;
	unsigned char ucControl;
	char *pHeader;
	signed short *pStateAddress;
	signed short anIData0;
	int nDMEMOut;
	int nCount;
	int nSrcAddress;
	int nOptPred;
	int nVScale;
	int i;
	unsigned int dwDecodeSelect;
	unsigned int n;
	int nA;
	int nB;
	signed short nSamp1;
	signed short nSamp2;
	signed short *pTempStateAddr;
	int nOutput;
}

int rspALoadBuffer1(__anon_0x5845E *pRSP, unsigned int nCommandLo)
{
	void *pData;
	int nAddress;
}

// Local to compilation unit
static int rspLoadADPCMCoefTable2(__anon_0x5845E *pRSP)
{
	unsigned int j;
	unsigned int nCoefIndex;
}

// Local to compilation unit
static int rspLoadADPCMCoefTable1(__anon_0x5845E *pRSP)
{
	unsigned int j;
	unsigned int nCoefIndex;
}

int rspLoadADPCMCoefRow(__anon_0x5845E *pRSP, unsigned int nCoefIndex, unsigned int nOptPred);

int rspDumpBinaryDMEMToFile(__anon_0x5845E *pRSP)
{
	tXL_FILE *fp;
	int i;
	unsigned int nSize;
}

int rspDumpMotorolaSDMEMTOFile(__anon_0x5845E *pRSP)
{
	tXL_FILE *fp;
	int i;
	unsigned int nStartAddress;
	unsigned int nSize;
	char acDMEMLine[512];
}

int rspDumpDMEMToFile(__anon_0x5845E *pRSP)
{
	tXL_FILE *fp;
	int i;
	unsigned int nStartAddress;
	unsigned int nSize;
	char acDMEMLine[64];
}

int rspMultPolef(signed short *matrix[8], signed short *vectorIn, signed short *vectorOut)
{
	int sum;
	int vec0;
	int vec1;
	int vec2;
	int vec3;
	int vec4;
	int vec5;
	int vec6;
	int vec7;
	int vec8;
	int vec9;
}

int rspMultADPCMCoef1(__anon_0x5845E *pRSP, int *matrix, signed short *vectorIn, signed short *vectorOut, int nOptPred)
{
	int sum;
	int vec0;
	int vec1;
	int vec2;
	int vec3;
	int vec4;
	int vec5;
	int vec6;
	int vec7;
	int vec8;
}

int rspDotProduct8x15MatrixBy15x1Vector(signed short *matrix, signed short *vectorIn, signed short *vectorOut)
{
	int sum;
	int vec1;
	int vec2;
	int vec3;
	int vec4;
	int vec5;
	int vec6;
	int vec7;
	int vec8;
	int vec9;
	int vec10;
	int vec11;
	int vec12;
	int vec13;
	int vec14;
}

// Local to compilation unit
static int rspInitAudioDMEM1(__anon_0x5845E *pRSP);

