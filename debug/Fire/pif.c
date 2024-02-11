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

// Location: 0x800ED6B8
_XL_OBJECTTYPE gClassPIF;

// Location: 0x0
int counter$295;

// size: 0x30
struct __anon_0x4A974
{
	void *pROM; // 0x0
	void *pRAM; // 0x4
	void *pHost; // 0x8
	unsigned short controllerType[5]; // 0xC
	char controllerStatus[5]; // 0x16
	__anon_0x4B3FE eControllerType[5]; // 0x1C
};

int pifEvent(__anon_0x4A974 *pPIF, int nEvent, void *pArgument)
{
	int i;
}

int pifGetData(__anon_0x4A974 *pPIF, unsigned char *acData);

int pifSetData(__anon_0x4A974 *pPIF, unsigned char *acData);

int pifProcessOutputData(__anon_0x4A974 *pPIF)
{
	unsigned char *prx;
	unsigned char *ptx;
	int iData;
	int channel;
}

int pifProcessInputData(__anon_0x4A974 *pPIF)
{
	unsigned char *prx;
	unsigned char *ptx;
	int iData;
	int channel;
}

int pifExecuteCommand(__anon_0x4A974 *pPIF, unsigned char *buffer, unsigned char *prx, int channel);

// Local to compilation unit
static int pifGet64(__anon_0x4A974 *pPIF, unsigned int nAddress, signed long long *pData);

// Local to compilation unit
static int pifGet32(__anon_0x4A974 *pPIF, unsigned int nAddress, int *pData);

// Local to compilation unit
static int pifGet16(__anon_0x4A974 *pPIF, unsigned int nAddress, signed short *pData);

// Local to compilation unit
static int pifGet8(__anon_0x4A974 *pPIF, unsigned int nAddress, char *pData);

// Local to compilation unit
static int pifPut64(__anon_0x4A974 *pPIF, unsigned int nAddress, signed long long *pData);

// Local to compilation unit
static int pifPut32(__anon_0x4A974 *pPIF, unsigned int nAddress, int *pData);

// Local to compilation unit
static int pifPut16(__anon_0x4A974 *pPIF, unsigned int nAddress, signed short *pData);

// Local to compilation unit
static int pifPut8(__anon_0x4A974 *pPIF, unsigned int nAddress, char *pData);

// size: 0x4
enum __anon_0x4B3FE
{
	CT_NONE = 0,
	CT_CONTROLLER = 1,
	CT_CONTROLLER_W_PAK = 2,
	CT_CONTROLLER_W_RPAK = 3,
	CT_MOUSE = 4,
	CT_VOICE = 5,
	CT_4K = 6,
	CT_16K = 7,
	CT_COUNT = 8
};

int pifReadController(__anon_0x4A974 *pPIF, unsigned char *buffer, unsigned char *prx, int channel)
{
	__anon_0x4B3FE type;
}

int pifQueryController(__anon_0x4A974 *pPIF, unsigned char *buffer, unsigned char *prx, int channel);

int pifGetEEPROMSize(__anon_0x4A974 *pPIF, unsigned int *size);

int pifGetControllerType(__anon_0x4A974 *pPIF, int channel, unsigned short *type, char *status)
{
	__anon_0x4B3FE eType;
}

int pifGetControllerInput(int channel, unsigned int *controllerInput);

int pifSetEEPROMType(__anon_0x4A974 *pPIF, __anon_0x4B3FE type);

int pifGetEControllerType(__anon_0x4A974 *pPIF, int channel, __anon_0x4B3FE *type);

int pifSetControllerType(__anon_0x4A974 *pPIF, int channel, __anon_0x4B3FE type);

// Local to compilation unit
static unsigned char pifContDataCrc(unsigned char *data)
{
	unsigned int temp;
	unsigned int i;
	unsigned int j;
}

int pifWriteRumble(int channel, unsigned short address, unsigned char *data);

int pifReadRumble(unsigned short address, unsigned char *data)
{
	int i;
}

int pifIdCheckSum(unsigned short *ptr, unsigned short *csum, unsigned short *icsum)
{
	unsigned short data;
	unsigned int j;
}

