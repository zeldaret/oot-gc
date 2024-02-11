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

// Location: 0x28EA0E80
_XL_OBJECTTYPE gClassSerial;

// size: 0x8
struct __anon_0x78791
{
	void *pHost; // 0x0
	int nAddress; // 0x4
};

int serialEvent(__anon_0x78791 *pSerial, int nEvent, void *pArgument);

int serialGet64();

int serialGet32(__anon_0x78791 *pSerial, unsigned int nAddress, int *pData);

int serialGet16();

int serialGet8();

int serialPut64();

int serialPut32(__anon_0x78791 *pSerial, unsigned int nAddress, int *pData)
{
	int nSize;
	void *aData;
}

int serialPut16();

int serialPut8();

