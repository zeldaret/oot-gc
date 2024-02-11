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

// Location: 0x78E70E80
_XL_OBJECTTYPE gClassAudio;

// size: 0x20
struct __anon_0x753E7
{
	int nSize; // 0x0
	int bEnable; // 0x4
	void *pHost; // 0x8
	int nControl; // 0xC
	int nAddress; // 0x10
	int nRateBit; // 0x14
	int nRateDAC; // 0x18
	int nStatus; // 0x1C
};

int audioEvent(__anon_0x753E7 *pAudio, int nEvent, void *pArgument);

int audioEnable(__anon_0x753E7 *pAudio, int bEnable);

int audioGet64();

int audioGet32(__anon_0x753E7 *pAudio, unsigned int nAddress, int *pData);

int audioGet16();

int audioGet8();

int audioPut64();

int audioPut32(__anon_0x753E7 *pAudio, unsigned int nAddress, int *pData)
{
	void *pBuffer;
}

int audioPut16();

int audioPut8();

