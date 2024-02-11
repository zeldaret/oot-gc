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

// Location: 0x58E70E80
_XL_OBJECTTYPE gClassFlash;

// size: 0x10
struct __anon_0x7428F
{
	void *pHost; // 0x0
	int flashCommand; // 0x4
	char *flashBuffer; // 0x8
	int flashStatus; // 0xC
};

int flashEvent(__anon_0x7428F *pFLASH, int nEvent, void *pArgument);

// Local to compilation unit
static int flashGet64();

// Local to compilation unit
static int flashGet32(__anon_0x7428F *pFLASH, int *pData);

// Local to compilation unit
static int flashGet16();

// Local to compilation unit
static int flashGet8();

// Local to compilation unit
static int flashPut64();

// Local to compilation unit
static int flashPut32(__anon_0x7428F *pFLASH, int *pData)
{
	int i;
	char buffer[128];
}

// Local to compilation unit
static int flashPut16();

// Local to compilation unit
static int flashPut8();

int flashTransferFLASH(__anon_0x7428F *pFLASH, int nOffsetRAM, int nSize)
{
	void *pTarget;
	int i;
}

int flashCopyFLASH(__anon_0x7428F *pFLASH, int nOffsetRAM, int nOffsetFLASH, int nSize)
{
	void *pTarget;
}

