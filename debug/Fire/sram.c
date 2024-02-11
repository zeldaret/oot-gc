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

// Location: 0x68E70E80
_XL_OBJECTTYPE gClassSram;

// size: 0x4
struct __anon_0x74AB9
{
	void *pHost; // 0x0
};

int sramEvent(__anon_0x74AB9 *pSram, int nEvent, void *pArgument);

// Local to compilation unit
static int sramGet64(unsigned int nAddress, signed long long *pData);

// Local to compilation unit
static int sramGet32(unsigned int nAddress, int *pData);

// Local to compilation unit
static int sramGet16(unsigned int nAddress, signed short *pData);

// Local to compilation unit
static int sramGet8(unsigned int nAddress, char *pData);

// Local to compilation unit
static int sramPut64(unsigned int nAddress, signed long long *pData);

// Local to compilation unit
static int sramPut32(unsigned int nAddress, int *pData);

// Local to compilation unit
static int sramPut16(unsigned int nAddress, signed short *pData);

// Local to compilation unit
static int sramPut8(unsigned int nAddress, char *pData);

int sramTransferSRAM(__anon_0x74AB9 *pSRAM, int nOffsetRAM, int nOffsetSRAM, int nSize)
{
	void *pTarget;
}

int sramCopySRAM(__anon_0x74AB9 *pSRAM, int nOffsetRAM, int nOffsetSRAM, int nSize)
{
	void *pTarget;
}

