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

// Location: 0x48E70E80
_XL_OBJECTTYPE gClassDisk;

// size: 0x4
struct __anon_0x73B29
{
	void *pHost; // 0x0
};

int diskEvent(__anon_0x73B29 *pDisk, int nEvent, void *pArgument);

// Local to compilation unit
static int diskGetDrive64();

// Local to compilation unit
static int diskGetDrive32(unsigned int nAddress, int *pData);

// Local to compilation unit
static int diskGetDrive16();

// Local to compilation unit
static int diskGetDrive8();

// Local to compilation unit
static int diskPutDrive64();

// Local to compilation unit
static int diskPutDrive32(unsigned int nAddress);

// Local to compilation unit
static int diskPutDrive16();

// Local to compilation unit
static int diskPutDrive8();

// Local to compilation unit
static int diskGetROM64(signed long long *pData);

// Local to compilation unit
static int diskGetROM32(int *pData);

// Local to compilation unit
static int diskGetROM16(signed short *pData);

// Local to compilation unit
static int diskGetROM8(char *pData);

// Local to compilation unit
static int diskPutROM64();

// Local to compilation unit
static int diskPutROM32();

// Local to compilation unit
static int diskPutROM16();

// Local to compilation unit
static int diskPutROM8();

