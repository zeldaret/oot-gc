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

// Location: 0x800EFFBC
_XL_OBJECTTYPE gClassPeripheral;

// size: 0x38
struct __anon_0x83D15
{
	void *pHost; // 0x0
	int nStatus; // 0x4
	int nSizeGet; // 0x8
	int nSizePut; // 0xC
	int nLatency1; // 0x10
	int nLatency2; // 0x14
	int nRelease1; // 0x18
	int nRelease2; // 0x1C
	int nSizePage1; // 0x20
	int nSizePage2; // 0x24
	int nAddressRAM; // 0x28
	int nAddressROM; // 0x2C
	int nWidthPulse1; // 0x30
	int nWidthPulse2; // 0x34
};

int peripheralEvent(__anon_0x83D15 *pPeripheral, int nEvent, void *pArgument);

int peripheralGet64();

int peripheralGet32(__anon_0x83D15 *pPeripheral, unsigned int nAddress, int *pData);

int peripheralGet16();

int peripheralGet8();

int peripheralPut64();

// size: 0x4
enum __anon_0x8415D
{
	SOT_NONE = 4294967295,
	SOT_CPU = 0,
	SOT_PIF = 1,
	SOT_RAM = 2,
	SOT_ROM = 3,
	SOT_RSP = 4,
	SOT_RDP = 5,
	SOT_MIPS = 6,
	SOT_DISK = 7,
	SOT_FLASH = 8,
	SOT_SRAM = 9,
	SOT_AUDIO = 10,
	SOT_VIDEO = 11,
	SOT_SERIAL = 12,
	SOT_LIBRARY = 13,
	SOT_PERIPHERAL = 14,
	SOT_RDB = 15,
	SOT_COUNT = 16
};

int peripheralPut32(__anon_0x83D15 *pPeripheral, unsigned int nAddress, int *pData)
{
	int bFlag;
	__anon_0x8415D storageDevice;
}

int peripheralPut16();

int peripheralPut8();

// size: 0x4
enum __anon_0x843DE
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

// size: 0x10
struct __anon_0x84447
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x844F8
{
	SRT_NONE = 4294967295,
	SRT_MARIO = 0,
	SRT_WAVERACE = 1,
	SRT_MARIOKART = 2,
	SRT_STARFOX = 3,
	SRT_ZELDA1 = 4,
	SRT_ZELDA2 = 5,
	SRT_1080 = 6,
	SRT_PANEL = 7,
	SRT_MARIOPARTY1 = 8,
	SRT_MARIOPARTY2 = 9,
	SRT_MARIOPARTY3 = 10,
	SRT_DRMARIO = 11,
	SRT_UNKNOWN = 12
};

// size: 0x88
struct __anon_0x8464B
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x843DE eMode; // 0xC
	__anon_0x84447 romCopy; // 0x10
	__anon_0x844F8 eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x8415D storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// Location: 0x561380
__anon_0x8464B *gpSystem;

// Local to compilation unit
static int peripheralDMA_Complete()
{
	__anon_0x83D15 *pPeripheral;
	// References: gpSystem (0x561380)
}

