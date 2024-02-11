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

// Location: 0x800EE6D0
_XL_OBJECTTYPE gClassMips;

// size: 0x10
struct __anon_0x7331D
{
	int nMask; // 0x0
	int nMode; // 0x4
	void *pHost; // 0x8
	int nInterrupt; // 0xC
};

int mipsEvent(__anon_0x7331D *pMips, int nEvent, void *pArgument);

int mipsGet64();

int mipsGet32(__anon_0x7331D *pMips, unsigned int nAddress, int *pData);

int mipsGet16();

int mipsGet8();

int mipsPut64();

int mipsPut32(__anon_0x7331D *pMips, unsigned int nAddress, int *pData)
{
	int nData;
}

int mipsPut16();

int mipsPut8();

// size: 0x4
enum __anon_0x736C0
{
	MIT_NONE = 4294967295,
	MIT_SP = 0,
	MIT_SI = 1,
	MIT_AI = 2,
	MIT_VI = 3,
	MIT_PI = 4,
	MIT_DP = 5
};

int mipsResetInterrupt(__anon_0x7331D *pMips, __anon_0x736C0 eType)
{
	int nInterrupt;
}

int mipsSetInterrupt(__anon_0x7331D *pMips, __anon_0x736C0 eType)
{
	int nInterrupt;
}

