// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// Local to compilation unit
// Location: 0x60D90F80
static char gMCardCardWorkArea[40960];

// Location: 0x60561380
long currentIdx;

// Local to compilation unit
// Location: 0x64561380
static int yes$771;

// size: 0x4
enum __anon_0x1A5F0
{
	MC_M_NONE = 0,
	MC_M_LD01 = 1,
	MC_M_LD02 = 2,
	MC_M_LD03 = 3,
	MC_M_LD04 = 4,
	MC_M_LD05 = 5,
	MC_M_LD05_2 = 6,
	MC_M_LD06 = 7,
	MC_M_LD06_2 = 8,
	MC_M_LD06_3 = 9,
	MC_M_LD06_4 = 10,
	MC_M_LD07 = 11,
	MC_M_SV01 = 12,
	MC_M_SV01_2 = 13,
	MC_M_SV02 = 14,
	MC_M_SV03 = 15,
	MC_M_SV04 = 16,
	MC_M_SV05 = 17,
	MC_M_SV05_2 = 18,
	MC_M_SV06 = 19,
	MC_M_SV06_2 = 20,
	MC_M_SV06_3 = 21,
	MC_M_SV06_4 = 22,
	MC_M_SV06_5 = 23,
	MC_M_SV07 = 24,
	MC_M_SV08_L = 25,
	MC_M_SV08_L_2 = 26,
	MC_M_SV08 = 27,
	MC_M_SV08_2 = 28,
	MC_M_SV10 = 29,
	MC_M_SV11 = 30,
	MC_M_SV12 = 31,
	MC_M_SV_SHARE = 32,
	MC_M_IN01_L = 33,
	MC_M_IN01_S = 34,
	MC_M_IN02 = 35,
	MC_M_IN03 = 36,
	MC_M_IN04_L = 37,
	MC_M_IN04_S = 38,
	MC_M_IN05 = 39,
	MC_M_GF01_L = 40,
	MC_M_GF01_L_2 = 41,
	MC_M_GF01_S = 42,
	MC_M_GF01_S_2 = 43,
	MC_M_GF02 = 44,
	MC_M_GF03 = 45,
	MC_M_GF04_L = 46,
	MC_M_GF04_S = 47,
	MC_M_GF05 = 48,
	MC_M_GF06 = 49
};

// Local to compilation unit
// Location: 0x68561380
static __anon_0x1A5F0 prevMenuEntry$772;

// Local to compilation unit
// Location: 0x6C561380
static __anon_0x1A5F0 nextMenuEntry$773;

// Local to compilation unit
// Location: 0x70561380
static int toggle2$1029;

// Local to compilation unit
// Location: 0x80134DB8
static int toggle$1034;

// Local to compilation unit
// Location: 0x74561380
static int checkFailCount$1490;

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

// Location: 0x60791080
OSCalendarTime gDate;

// Location: 0x78561380
long bWrite2Card;

// Location: 0x80107988
long bNoWriteInCurrentFrame[10];

// size: 0x18
struct __anon_0x1AC1A
{
	int configuration; // 0x0
	int size; // 0x4
	int offset; // 0x8
	char *buffer; // 0xC
	int *writtenBlocks; // 0x10
	int writtenConfig; // 0x14
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
struct __anon_0x1AEB5
{
	int currentGame; // 0x0
	int fileSize; // 0x4
	char name[33]; // 0x8
	int numberOfGames; // 0x2C
	__anon_0x1AC1A game; // 0x30
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
enum __anon_0x1B0CB
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
	__anon_0x1AEB5 file; // 0x0
	__anon_0x1B0CB error; // 0x35C
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

// size: 0x4
enum __anon_0x1B813
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

// size: 0x10
struct __anon_0x1B87B
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x1B92C
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
enum __anon_0x1BA5D
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
struct __anon_0x1BB9D
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x1B813 eMode; // 0xC
	__anon_0x1B87B romCopy; // 0x10
	__anon_0x1B92C eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x1BA5D storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// Location: 0x561380
__anon_0x1BB9D *gpSystem;

// size: 0x4
enum __anon_0x1BD8E
{
	MC_C_NONE = 0,
	MC_C_CONTINUE = 1,
	MC_C_IPL = 2,
	MC_C_GO_TO_GAME = 3,
	MC_C_CREATE_GAME = 4,
	MC_C_DELETE_GAME = 5,
	MC_C_FORMAT_CARD = 6
};

int mcardUpdate()
{
	int j;
	int i;
	int toggle;
	__anon_0x1BD8E command;
	int prevIndex;
	int index;
	int counter;
	// References: mCard (0x801079B0)
	// References: bWrite2Card (0x78561380)
	// References: gpSystem (0x561380)
}

int mcardStore(_MCARD *pMCard)
{
	int i;
	int checksum;
	int bufferOffset;
	__anon_0x1BD8E command;
	// References: checkFailCount$1490 (0x74561380)
	// References: mCard (0x801079B0)
	// References: gDate (0x60791080)
}

// Location: 0x801355D4
int gButtonDownToggle;

int mcardOpenDuringGame(_MCARD *pMCard)
{
	int i;
	__anon_0x1BD8E command;
	int loadToggle;
	// References: gButtonDownToggle (0x801355D4)
}

int mcardOpen(_MCARD *pMCard, char *fileName, char *comment, char *icon, char *banner, char *gameName, int *defaultConfiguration, int fileSize, int gameSize)
{
	int i;
	__anon_0x1BD8E command;
	// References: gpSystem (0x561380)
	// References: gButtonDownToggle (0x801355D4)
}

int mcardCheckSpace(_MCARD *pMCard, int size)
{
	int freeBytes;
	int freeFiles;
}

int mcardGetError(_MCARD *pMCard, __anon_0x1B0CB *pMCardError);

int mcardWrite(_MCARD *pMCard, int address, int size, char *data)
{
	int i;
	char testByte;
	// References: toggle2$1029 (0x70561380)
	// References: toggle$1034 (0x80134DB8)
	// References: gpSystem (0x561380)
	// References: currentIdx (0x60561380)
	// References: bNoWriteInCurrentFrame (0x80107988)
	// References: bWrite2Card (0x78561380)
}

int corruptionCheck(_MCARD *pMCard)
{
	char *buffer;
	int checksum1;
	int checksum2;
	int i;
	int toggle;
	// References: mCard (0x801079B0)
}

int mcardOpenDuringGameError(_MCARD *pMCard, __anon_0x1BD8E *pCommand);

int mcardOpenError(_MCARD *pMCard, __anon_0x1BD8E *pCommand);

int mcardMenu(_MCARD *pMCard, __anon_0x1A5F0 menuEntry, __anon_0x1BD8E *pCommand)
{
	// References: nextMenuEntry$773 (0x6C561380)
	// References: yes$771 (0x64561380)
	// References: prevMenuEntry$772 (0x68561380)
}

int mcardRead(_MCARD *pMCard, int address, int size, char *data);

int mcardGameRelease(_MCARD *pMCard);

int mcardFileRelease(_MCARD *pMCard);

int mcardGameErase(_MCARD *pMCard, int index);

int mcardFileErase(_MCARD *pMCard);

int mcardCardErase(_MCARD *pMCard)
{
	int slot;
}

int mcardGameCreateDuringGame(_MCARD *pMCard, char *name, int size)
{
	int i;
	// References: mCard (0x801079B0)
}

int mcardGameCreate(_MCARD *pMCard, char *name, int defaultConfiguration, int size)
{
	int i;
	// References: mCard (0x801079B0)
}

// size: 0x20
struct _GXTexObj
{
	unsigned long dummy[8]; // 0x0
};

// size: 0x6C
struct CARDStat
{
	char fileName[32]; // 0x0
	unsigned long length; // 0x20
	unsigned long time; // 0x24
	unsigned char gameName[4]; // 0x28
	unsigned char company[2]; // 0x2C
	unsigned char bannerFormat; // 0x2E
	unsigned char __padding; // 0x2F
	unsigned long iconAddr; // 0x30
	unsigned short iconFormat; // 0x34
	unsigned short iconSpeed; // 0x36
	unsigned long commentAddr; // 0x38
	unsigned long offsetBanner; // 0x3C
	unsigned long offsetBannerTlut; // 0x40
	unsigned long offsetIcon[8]; // 0x44
	unsigned long offsetIconTlut; // 0x64
	unsigned long offsetData; // 0x68
};

int mcardFileCreate(_MCARD *pMCard, char *name, char *comment, char *icon, char *banner, int size)
{
	int freeBytes;
	int freeFiles;
	int totalSize;
	int i;
	char *buffer;
	_GXTexObj texObj;
	void *dataP;
	CARDStat cardStatus;
	int fileNo;
	OSCalendarTime date;
	char dateString[32];
	// References: mCard (0x801079B0)
}

int mcardGameSet(_MCARD *pMCard, char *name)
{
	int i;
	// References: gpSystem (0x561380)
}

int mcardGameSetNoSave(_MCARD *pMCard, int size)
{
	// References: gpSystem (0x561380)
}

int mcardFileSet(_MCARD *pMCard, char *name)
{
	int i;
	// References: mCard (0x801079B0)
}

int mcardInit(_MCARD *pMCard);

int mcardReInit(_MCARD *pMCard);

int mcardWriteGameDataReset(_MCARD *pMCard)
{
	// References: mCard (0x801079B0)
}

int mcardWriteGameDataWait(_MCARD *pMCard)
{
	int checksum;
	int i;
	// References: mCard (0x801079B0)
}

int mcardWriteGameData(_MCARD *pMCard, int offset);

int mcardReadGameData(_MCARD *pMCard)
{
	int checksum1;
	int checksum2;
	int i;
	int toggle;
	// References: mCard (0x801079B0)
}

int mcardReplaceBlock(_MCARD *pMCard, int index)
{
	int checksum1;
	int checksum2;
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardWriteTimeAsynch(_MCARD *pMCard)
{
	// References: gDate (0x60791080)
	// References: mCard (0x801079B0)
}

int mcardWriteTimePrepareWriteBuffer(_MCARD *pMCard)
{
	char dateString[32];
	int checksum;
	// References: gDate (0x60791080)
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardWriteConfigAsynch(_MCARD *pMCard)
{
	// References: mCard (0x801079B0)
}

int mcardWriteConfigPrepareWriteBuffer(_MCARD *pMCard)
{
	int checksum;
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardReadBufferAsynch(_MCARD *pMCard, int offset)
{
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardWriteBufferAsynch(_MCARD *pMCard, int offset)
{
	OSCalendarTime date;
	// References: mCard (0x801079B0)
}

int mcardWriteCardHeader(_MCARD *pMCard, char *cardHeader)
{
	char buffer[24608];
	// References: mCard (0x801079B0)
}

int mcardReadCardHeader(_MCARD *pMCard, char *cardHeader)
{
	char buffer[24608];
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardWriteFileHeaderInitial(_MCARD *pMCard)
{
	char buffer[24608];
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardReadFileHeaderInitial(_MCARD *pMCard)
{
	char buffer[24608];
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardWriteFileHeader(_MCARD *pMCard)
{
	char buffer[24608];
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardReadFileHeader(_MCARD *pMCard)
{
	char buffer[24608];
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardWriteAnywherePartial(_MCARD *pMCard, int offset, int size, char *buffer, int partialOffset, int totalSize)
{
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardWriteAnywhere(_MCARD *pMCard, int offset, int size, char *buffer)
{
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardReadAnywhere(_MCARD *pMCard, int offset, int size, char *buffer)
{
	// References: mCard (0x801079B0)
}

int mcardTimeCheck(_MCARD *pMCard)
{
	OSCalendarTime time;
}

int mcardSetFileTime(_MCARD *pMCard, OSCalendarTime *time)
{
	char buffer[24608];
	// References: mCard (0x801079B0)
}

int mcardWriteAnywhereNoTime(_MCARD *pMCard, int offset, int size, char *buffer)
{
	// References: mCard (0x801079B0)
}

int mcardReadAnywhereNoTime(_MCARD *pMCard, int offset, int size, char *buffer)
{
	// References: mCard (0x801079B0)
}

int mcardFinishFile(_MCARD *pMCard);

int mcardReadyFile(_MCARD *pMCard);

int mcardFinishCard(_MCARD *pMCard);

// Local to compilation unit
static int mcardReadyCard(_MCARD *pMCard)
{
	int i;
	int sectorSize;
	// References: gMCardCardWorkArea (0x60D90F80)
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardPoll(_MCARD *pMCard)
{
	// References: mCard (0x801079B0)
}

int mcardCopyName(char *name1, char *name2)
{
	// References: mCard (0x801079B0)
}

int mcardCompareName(char *name1, char *name2);

// Local to compilation unit
static int mcardVerifyChecksumFileHeader(_MCARD *pMCard)
{
	char *buffer;
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardCheckChecksumFileHeader(_MCARD *pMCard, char *buffer)
{
	int checksum;
	char buffer2[8192];
	int toggle;
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardReplaceFileBlock(_MCARD *pMCard, int index)
{
	int checksum1;
	int checksum2;
	char buffer[8192];
	// References: mCard (0x801079B0)
}

int mcardGetFileTime(_MCARD *pMCard, OSCalendarTime *time)
{
	char buffer[544];
}

// Local to compilation unit
static int mcardSaveChecksumFileHeader(_MCARD *pMCard, char *buffer)
{
	char buffer2[8192];
	int checksum;
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardCalculateChecksumFileBlock2(_MCARD *pMCard, int *checksum)
{
	int i;
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardCalculateChecksumFileBlock1(_MCARD *pMCard, int *checksum)
{
	int i;
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardCalculateChecksum(_MCARD *pMCard, int *checksum)
{
	int i;
	// References: mCard (0x801079B0)
}

// Local to compilation unit
static int mcardGCErrorHandler(_MCARD *pMCard, int gcError);

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
struct __anon_0x1F23C
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
struct __anon_0x1F497
{
	unsigned short numEntries; // 0x0
	unsigned char unpacked; // 0x2
	unsigned char pad8; // 0x3
	_GXTlutFmt format; // 0x4
	char *data; // 0x8
};

// size: 0x8
struct __anon_0x1F563
{
	__anon_0x1F23C *textureHeader; // 0x0
	__anon_0x1F497 *CLUTHeader; // 0x4
};

// size: 0xC
struct __anon_0x1F5D4
{
	unsigned long versionNumber; // 0x0
	unsigned long numDescriptors; // 0x4
	__anon_0x1F563 *descriptorArray; // 0x8
};

void mcardUnpackTexPalette(__anon_0x1F5D4 *pal)
{
	unsigned short i;
}

