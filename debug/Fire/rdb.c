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

// Location: 0x800EE1B0
_XL_OBJECTTYPE gClassRdb;

// size: 0x110
struct __anon_0x56A0F
{
	int nHackCount; // 0x0
	char szString[256]; // 0x4
	int nIndexString; // 0x104
	int nAddress; // 0x108
	void *pHost; // 0x10C
};

int rdbEvent(__anon_0x56A0F *pRDB, int nEvent, void *pArgument);

// Local to compilation unit
static int rdbGet64();

// Local to compilation unit
static int rdbGet32(unsigned int nAddress);

// Local to compilation unit
static int rdbGet16();

// Local to compilation unit
static int rdbGet8();

// Local to compilation unit
static int rdbPut64();

// Local to compilation unit
static int rdbPut32(__anon_0x56A0F *pRDB, unsigned int nAddress, int *pData)
{
	int nLength;
	int iCounter;
}

// Local to compilation unit
static int rdbPut16();

// Local to compilation unit
static int rdbPut8();

