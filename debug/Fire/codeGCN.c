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

// Location: 0x800EA7C8
_XL_OBJECTTYPE gClassCode;

// size: 0x4
enum __anon_0x1F980
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
	__anon_0x1F980 eType; // 0x18
	DVDFileInfo info; // 0x1C
};

// Location: 0x0
tXL_FILE *gpFileCode;

// Location: 0x0
unsigned int gnSizeCode;

// Local to compilation unit
// Location: 0x80135680
static void *gpBufferFunction;

// Location: 0x0
char gpBufferFunctionCache[65536];

// Local to compilation unit
// Location: 0x80135684
static unsigned int *ganDataCode;

// Location: 0x0
unsigned int gnCountFunction;

// Location: 0x0
unsigned int gnLastCountFunction;

// Location: 0x0
int gSizeInARAM;

// size: 0x10
struct _CODE_CACHE_NODE
{
	int checksum; // 0x0
	int length; // 0x4
	_CODE_CACHE_NODE *next; // 0x8
	_CODE_CACHE_NODE *child; // 0xC
};

// Location: 0x0
_CODE_CACHE_NODE gCodeCacheHead;

int codeEvent(int nEvent)
{
	// References: ganDataCode (0x80135684)
	// References: gpBufferFunction (0x80135680)
}

// Location: 0x0
int gCatalogLoaded;

int codeCheckCatalog(int nAddress0, int nAddress1)
{
	int iFunction;
	int instruction;
	unsigned int checksum;
	// References: gnCountFunction (0x0)
	// References: ganDataCode (0x80135684)
	// References: gCatalogLoaded (0x0)
}

int codeSendFilePart();

int hioInit();

int hioSendBuffer();

void hioCallback();

int hioCallbackDevice();

int hioInitSend();

