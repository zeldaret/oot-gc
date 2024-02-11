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

// Location: 0x800DB7E0
_XL_OBJECTTYPE gTypeFile;

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

// Local to compilation unit
// Location: 0x801355A0
static int (*gpfOpen)(char */* unknown0 */, DVDFileInfo */* unknown1 */);

// Local to compilation unit
// Location: 0x801355A4
static int (*gpfRead)(DVDFileInfo */* unknown0 */, void */* unknown1 */, int /* unknown2 */, int /* unknown3 */, void (*/* unknown4 */)(long /* unknown0 */, DVDFileInfo */* unknown1 */));

// size: 0x58
struct tXL_FILE
{
	int iBuffer; // 0x0
	void *pData; // 0x4
	void *pBuffer; // 0x8
	int nAttributes; // 0xC
	int nSize; // 0x10
	int nOffset; // 0x14
	__anon_0x2757 eType; // 0x18
	DVDFileInfo info; // 0x1C
};

int xlFileEvent(tXL_FILE *pFile, int nEvent);

int xlFileGetPosition(tXL_FILE *pFile, int *pnOffset);

int xlFileSetPosition(tXL_FILE *pFile, int nOffset);

int xlFilePutLine();

int xlFilePutFlip(int nSizeBytes);

int xlFilePut();

int xlFileGetLine(tXL_FILE *pFile, char *acLine, int nSizeLine)
{
	int iCharacter;
	char nCharacter;
}

int xlFileGetFlip(tXL_FILE *pFile, void *pTarget, int nSizeBytes);

int xlFileGet(tXL_FILE *pFile, void *pTarget, int nSizeBytes)
{
	int nOffset;
	int nOffsetExtra;
	int nSize;
	int nSizeUsed;
	// References: gpfRead (0x801355A4)
}

int xlFileClose(tXL_FILE **ppFile);

int xlFileCreate();

// size: 0x4
enum __anon_0x2757
{
	XLFT_NONE = 4294967295,
	XLFT_TEXT = 0,
	XLFT_BINARY = 1
};

int xlFileOpen(tXL_FILE **ppFile, __anon_0x2757 eType, char *szFileName)
{
	int nStatus;
	// References: gpfOpen (0x801355A0)
	// References: gTypeFile (0x800DB7E0)
}

int xlFileLoad(char *szFileName, void *ppBuffer)
{
	int nSize;
	tXL_FILE *pFile;
	// References: gpfOpen (0x801355A0)
	// References: gTypeFile (0x800DB7E0)
}

int xlFileGetSize(int *pnSize, char *szFileName)
{
	tXL_FILE *pFile;
	// References: gpfOpen (0x801355A0)
	// References: gTypeFile (0x800DB7E0)
}

int xlFileSetRead(int (*pfRead)(DVDFileInfo */* unknown0 */, void */* unknown1 */, int /* unknown2 */, int /* unknown3 */, void (*/* unknown4 */)(long /* unknown0 */, DVDFileInfo */* unknown1 */)))
{
	// References: gpfRead (0x801355A4)
}

int xlFileSetOpen(int (*pfOpen)(char */* unknown0 */, DVDFileInfo */* unknown1 */))
{
	// References: gpfOpen (0x801355A0)
}

