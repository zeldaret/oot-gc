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

// Location: 0x800ED6C8
_XL_OBJECTTYPE gClassRAM;

// size: 0xC
struct __anon_0x4BFE7
{
	void *pHost; // 0x0
	void *pBuffer; // 0x4
	unsigned int nSize; // 0x8
};

int ramEvent(__anon_0x4BFE7 *pRAM, int nEvent, void *pArgument);

int ramGetSize(__anon_0x4BFE7 *pRAM, unsigned int *pnSize);

int ramSetSize(__anon_0x4BFE7 *pRAM, unsigned int nSize);

int ramWipe(__anon_0x4BFE7 *pRAM);

int ramGetBuffer(__anon_0x4BFE7 *pRAM, void *ppRAM, unsigned int nOffset, unsigned int *pnSize);

// Local to compilation unit
static int ramGet64(__anon_0x4BFE7 *pRAM, unsigned int nAddress, signed long long *pData);

// Local to compilation unit
static int ramGet32(__anon_0x4BFE7 *pRAM, unsigned int nAddress, int *pData);

// Local to compilation unit
static int ramGet16(__anon_0x4BFE7 *pRAM, unsigned int nAddress, signed short *pData);

// Local to compilation unit
static int ramGet8(__anon_0x4BFE7 *pRAM, unsigned int nAddress, char *pData);

// Local to compilation unit
static int ramPut64(__anon_0x4BFE7 *pRAM, unsigned int nAddress, signed long long *pData);

// Local to compilation unit
static int ramPut32(__anon_0x4BFE7 *pRAM, unsigned int nAddress, int *pData);

// Local to compilation unit
static int ramPut16(__anon_0x4BFE7 *pRAM, unsigned int nAddress, signed short *pData);

// Local to compilation unit
static int ramPut8(__anon_0x4BFE7 *pRAM, unsigned int nAddress, char *pData);

// Local to compilation unit
static int ramGetRI64();

// Local to compilation unit
static int ramGetRI32(unsigned int nAddress);

// Local to compilation unit
static int ramGetRI16();

// Local to compilation unit
static int ramGetRI8();

// Local to compilation unit
static int ramPutRI64();

// Local to compilation unit
static int ramPutRI32(unsigned int nAddress);

// Local to compilation unit
static int ramPutRI16();

// Local to compilation unit
static int ramPutRI8();

// Local to compilation unit
static int ramGetControl64();

// Local to compilation unit
static int ramGetControl32(unsigned int nAddress);

// Local to compilation unit
static int ramGetControl16();

// Local to compilation unit
static int ramGetControl8();

// Local to compilation unit
static int ramPutControl64();

// Local to compilation unit
static int ramPutControl32(unsigned int nAddress);

// Local to compilation unit
static int ramPutControl16();

// Local to compilation unit
static int ramPutControl8();

