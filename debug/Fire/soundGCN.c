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

// Location: 0x800EA7D8
_XL_OBJECTTYPE gClassSound;

// Location: 0x0
int sCapture$219;

// Location: 0x80108180
long gVolumeCurve[257];

// size: 0x4
enum __anon_0x2084C
{
	SPM_NONE = 4294967295,
	SPM_PLAY = 0,
	SPM_RAMPQUEUED = 1,
	SPM_RAMPPLAYED = 2
};

// size: 0xD8
struct __anon_0x208BA
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
	__anon_0x2084C eMode; // 0xB4
	void *pBufferZero; // 0xB8
	void *pBufferHold; // 0xBC
	void *pBufferRampUp; // 0xC0
	void *pBufferRampDown; // 0xC4
	int nSizePlay; // 0xC8
	int nSizeZero; // 0xCC
	int nSizeHold; // 0xD0
	int nSizeRamp; // 0xD4
};

int soundEvent(__anon_0x208BA *pSound, int nEvent)
{
	int iBuffer;
	// References: gVolumeCurve (0x80108180)
}

// size: 0x4
enum __anon_0x20C8D
{
	SOUND_BEEP_ACCEPT = 0,
	SOUND_BEEP_DECLINE = 1,
	SOUND_BEEP_SELECT = 2,
	SOUND_BEEP_COUNT = 3
};

int soundFreeBeep(__anon_0x208BA *pSound, __anon_0x20C8D iBeep);

int soundPlayBeep(__anon_0x208BA *pSound, __anon_0x20C8D iBeep);

// size: 0x4
enum __anon_0x20E13
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
	__anon_0x20E13 eType; // 0x18
	DVDFileInfo info; // 0x1C
};

int soundLoadBeep(__anon_0x208BA *pSound, __anon_0x20C8D iBeep, char *szNameFile)
{
	tXL_FILE *pFile;
}

// size: 0x4
enum __anon_0x2152F
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

// size: 0x10
struct __anon_0x21596
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x21647
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
enum __anon_0x21778
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
struct __anon_0x218B8
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x2152F eMode; // 0xC
	__anon_0x21596 romCopy; // 0x10
	__anon_0x21647 eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x21778 storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// Location: 0x561380
__anon_0x218B8 *gpSystem;

// Local to compilation unit
static void soundCallbackBeep()
{
	__anon_0x208BA *pSound;
	// References: gpSystem (0x561380)
}

void InitVolumeCurve()
{
	long i;
	// References: gVolumeCurve (0x80108180)
}

int soundSetBufferSize(__anon_0x208BA *pSound, int nSize)
{
	int iBuffer;
}

int soundGetDMABuffer(unsigned int *pnSize);

int soundSetAddress(__anon_0x208BA *pSound, void *pData);

int soundSetBitRate();

int soundSetDACRate(__anon_0x208BA *pSound, int nDacRate);

int soundSetLength(__anon_0x208BA *pSound, int nSize);

// Local to compilation unit
static int soundMakeBuffer(__anon_0x208BA *pSound)
{
	unsigned long nSamples;
	signed short *curBufP;
	unsigned long sampleStep;
	unsigned long sample;
	int j;
	int nSize;
	int samp;
	int iBuffer;
	long vol;
	int bFlag;
	int bPlay;
	long volAdjust;
	// References: gVolumeCurve (0x80108180)
}

// Local to compilation unit
static void soundCallbackDMA()
{
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int soundPlayBuffer(__anon_0x208BA *pSound)
{
	void *pData;
	int iBuffer;
	int nSize;
}

int soundMakeHold();

int soundMakeZero(__anon_0x208BA *pSound)
{
	int iData;
}

// size: 0x4
enum __anon_0x221A3
{
	SR_NONE = 4294967295,
	SR_DECREASE = 0,
	SR_INCREASE = 1
};

// Local to compilation unit
static int soundMakeRamp(__anon_0x208BA *pSound, int iBuffer, __anon_0x221A3 eRamp)
{
	int bFlag;
	int iData;
	signed short *anData;
	signed short nData0;
	signed short nData1;
	signed short nGoal0;
	signed short nGoal1;
	signed short nStep0;
	signed short nStep1;
	signed short nLast0;
	signed short nLast1;
}

int soundWipeBuffers(__anon_0x208BA *pSound)
{
	int iBuffer;
}

