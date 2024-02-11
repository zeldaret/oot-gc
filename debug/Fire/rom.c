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

// Location: 0x800ED8E8
_XL_OBJECTTYPE gClassROM;

// Local to compilation unit
// Location: 0x800ED8F8
static unsigned int ganOffsetBlock_ZLJ[198];

// Local to compilation unit
// Location: 0x10DC0E80
static unsigned int ganOffsetBlock_URAZLJ[198];

// Location: 0x0
int iImage$261;

// Local to compilation unit
// Location: 0x60571380
static int gbProgress;

// Local to compilation unit
// Location: 0x64571380
static void *gpImageBack;

// Local to compilation unit
// Location: 0x68571380
static int iImage$294;

// size: 0x4
enum __anon_0x4CF87
{
	RLM_NONE = 4294967295,
	RLM_PART = 0,
	RLM_FULL = 1,
	RLM_COUNT_ = 2
};

// size: 0x10
struct __anon_0x4CFE6
{
	int iCache; // 0x0
	unsigned int nSize; // 0x4
	unsigned int nTickUsed; // 0x8
	char keep; // 0xC
};

// size: 0x14
struct __anon_0x4D0FA
{
	int bWait; // 0x0
	int (*pCallback)(); // 0x4
	unsigned char *pTarget; // 0x8
	unsigned int nSize; // 0xC
	unsigned int nOffset; // 0x10
};

// size: 0x30
struct __anon_0x4D1DA
{
	int bWait; // 0x0
	int bDone; // 0x4
	int nResult; // 0x8
	unsigned char *anData; // 0xC
	int (*pCallback)(); // 0x10
	int iCache; // 0x14
	int iBlock; // 0x18
	int nOffset; // 0x1C
	unsigned int nOffset0; // 0x20
	unsigned int nOffset1; // 0x24
	unsigned int nSize; // 0x28
	unsigned int nSizeRead; // 0x2C
};

// size: 0x20
struct DVDDiskID
{
	char gameName[4]; // 0x0
	char company[2]; // 0x4
	unsigned char diskNumber; // 0x6
	unsigned char gameVersion; // 0x7
	unsigned char streaming; // 0x8
	unsigned char streamingBufSize; // 0x9
	unsigned char padding[22]; // 0xA
};

// size: 0x30
struct DVDCommandBlock
{
	DVDCommandBlock *next; // 0x0
	DVDCommandBlock *prev; // 0x4
	unsigned long command; // 0x8
	long state; // 0xC
	unsigned long offset; // 0x10
	unsigned long length; // 0x14
	void *addr; // 0x18
	unsigned long currTransferSize; // 0x1C
	unsigned long transferredSize; // 0x20
	DVDDiskID *id; // 0x24
	void (*callback)(long /* unknown0 */, DVDCommandBlock */* unknown1 */); // 0x28
	void *userData; // 0x2C
};

// size: 0x3C
struct DVDFileInfo
{
	DVDCommandBlock cb; // 0x0
	unsigned long startAddr; // 0x30
	unsigned long length; // 0x34
	void (*callback)(long /* unknown0 */, DVDFileInfo */* unknown1 */); // 0x38
};

// size: 0x10EF8
struct __anon_0x4D873
{
	void *pHost; // 0x0
	void *pBuffer; // 0x4
	int bFlip; // 0x8
	int bLoad; // 0xC
	char acNameFile[513]; // 0x10
	unsigned int nSize; // 0x214
	__anon_0x4CF87 eModeLoad; // 0x218
	__anon_0x4CFE6 aBlock[4096]; // 0x21C
	unsigned int nTick; // 0x1021C
	unsigned char *pCacheRAM; // 0x10220
	unsigned char anBlockCachedRAM[1024]; // 0x10224
	unsigned char anBlockCachedARAM[2046]; // 0x10624
	__anon_0x4D0FA copy; // 0x10E24
	__anon_0x4D1DA load; // 0x10E38
	int nCountBlockRAM; // 0x10E68
	int nSizeCacheRAM; // 0x10E6C
	unsigned char acHeader[64]; // 0x10E70
	unsigned int *anOffsetBlock; // 0x10EB0
	int nCountOffsetBlocks; // 0x10EB4
	DVDFileInfo fileInfo; // 0x10EB8
	int offsetToRom; // 0x10EF4
};

int romEvent(__anon_0x4D873 *pROM, int nEvent, void *pArgument);

int romGetImage(__anon_0x4D873 *pROM, char *acNameFile)
{
	int iName;
}

// size: 0x4
enum __anon_0x4DD08
{
	XLFT_NONE = 4294967295,
	XLFT_TEXT = 0,
	XLFT_BINARY = 1
};

// size: 0x58
struct tXL_FILE
{
	int iBuffer; // 0x0
	void *pData; // 0x4
	void *pBuffer; // 0x8
	int nAttributes; // 0xC
	int nSize; // 0x10
	int nOffset; // 0x14
	__anon_0x4DD08 eType; // 0x18
	DVDFileInfo info; // 0x1C
};

int romSetImage(__anon_0x4D873 *pROM, char *szNameFile)
{
	tXL_FILE *pFile;
	int iName;
	int nSize;
}

int romGetCacheSize(__anon_0x4D873 *pROM, int *pnSize);

int romSetCacheSize(__anon_0x4D873 *pROM, int nSize);

int romCopyBusy(__anon_0x4D873 *pROM);

int romUpdate(__anon_0x4D873 *pROM)
{
	int nStatus;
}

int romCopyImmediate(__anon_0x4D873 *pROM, void *pTarget, int nOffsetROM, unsigned int nSize)
{
	void *pSource;
	__anon_0x4CFE6 *pBlock;
	int nOffsetARAM;
	int nSizeCopy;
	int nOffsetBlock;
	int nSizeCopyARAM;
	int nSizeDMA;
	int nOffset;
	int nOffsetTarget;
	unsigned char *pBuffer;
	unsigned char anBuffer[608];
}

int romCopy(__anon_0x4D873 *pROM, void *pTarget, int nOffset, unsigned int nSize, int (*pCallback)())
{
	void *pSource;
	tXL_FILE *pFile;
}

int romGetSize(__anon_0x4D873 *pROM, int *pnSize);

// Local to compilation unit
static int romGetDebug64(signed long long *pData);

// Local to compilation unit
static int romGetDebug32(int *pData);

// Local to compilation unit
static int romGetDebug16(signed short *pData);

// Local to compilation unit
static int romGetDebug8(char *pData);

// Local to compilation unit
static int romPutDebug64();

// Local to compilation unit
static int romPutDebug32();

// Local to compilation unit
static int romPutDebug16();

// Local to compilation unit
static int romPutDebug8();

// Local to compilation unit
static int romGet64(__anon_0x4D873 *pROM, unsigned int nAddress, signed long long *pData)
{
	unsigned long long nData;
}

// Local to compilation unit
static int romGet32(__anon_0x4D873 *pROM, unsigned int nAddress, int *pData)
{
	unsigned int nData;
}

// Local to compilation unit
static int romGet16(__anon_0x4D873 *pROM, unsigned int nAddress, signed short *pData)
{
	unsigned short nData;
}

// Local to compilation unit
static int romGet8(__anon_0x4D873 *pROM, unsigned int nAddress, char *pData)
{
	unsigned char nData;
}

// Local to compilation unit
static int romPut64();

// Local to compilation unit
static int romPut32();

// Local to compilation unit
static int romPut16();

// Local to compilation unit
static int romPut8();

int romTestCode(__anon_0x4D873 *pROM, char *acCode)
{
	int iCode;
	char acCodeCurrent[5];
}

int romGetMask(__anon_0x4D873 *pROM, int *pnMask);

int romGetName(__anon_0x4D873 *pROM, char *acName)
{
	int iName;
}

int romGetCode(__anon_0x4D873 *pROM, char *acCode);

int romGetPC(__anon_0x4D873 *pROM, unsigned long long *pnPC)
{
	int nOffset;
	unsigned int nData;
	unsigned int iData;
	unsigned int anData[1024];
}

int romLoad(__anon_0x4D873 *pROM);

// Local to compilation unit
static int romLoadFullOrPart(__anon_0x4D873 *pROM)
{
	tXL_FILE *pFile;
	int iBlock;
	int nLoad;
	int nStep;
	int iData;
	unsigned int nData;
}

int romCacheAllBlocks(__anon_0x4D873 *pROM)
{
	int iCache;
	unsigned int iBlock;
	unsigned int iBlockLast;
}

// size: 0x8
struct __anon_0x4F17B
{
	int nOffsetHost; // 0x0
	int nAddressN64; // 0x4
};

// size: 0x8
struct cpu_callerID
{
	int N64address; // 0x0
	int GCNaddress; // 0x4
};

// size: 0x48
struct cpu_function
{
	void *pnBase; // 0x0
	void *pfCode; // 0x4
	int nCountJump; // 0x8
	__anon_0x4F17B *aJump; // 0xC
	int nAddress0; // 0x10
	int nAddress1; // 0x14
	cpu_callerID *block; // 0x18
	int callerID_total; // 0x1C
	int callerID_flag; // 0x20
	unsigned int nChecksum; // 0x24
	int timeToLive; // 0x28
	int memory_size; // 0x2C
	int heapID; // 0x30
	int heapWhere; // 0x34
	int treeheapWhere; // 0x38
	cpu_function *prev; // 0x3C
	cpu_function *left; // 0x40
	cpu_function *right; // 0x44
};

// size: 0x8
union __anon_0x4F530
{
	char _0s8; // 0x0
	char _1s8; // 0x1
	char _2s8; // 0x2
	char _3s8; // 0x3
	char _4s8; // 0x4
	char _5s8; // 0x5
	char _6s8; // 0x6
	char s8; // 0x7
	signed short _0s16; // 0x0
	signed short _1s16; // 0x2
	signed short _2s16; // 0x4
	signed short s16; // 0x6
	int _0s32; // 0x0
	int s32; // 0x4
	signed long long s64; // 0x0
	unsigned char _0u8; // 0x0
	unsigned char _1u8; // 0x1
	unsigned char _2u8; // 0x2
	unsigned char _3u8; // 0x3
	unsigned char _4u8; // 0x4
	unsigned char _5u8; // 0x5
	unsigned char _6u8; // 0x6
	unsigned char u8; // 0x7
	unsigned short _0u16; // 0x0
	unsigned short _1u16; // 0x2
	unsigned short _2u16; // 0x4
	unsigned short u16; // 0x6
	unsigned int _0u32; // 0x0
	unsigned int u32; // 0x4
	unsigned long long u64; // 0x0
};

// size: 0x8
union __anon_0x4F944
{
	float _0f32; // 0x0
	float f32; // 0x4
	long float f64; // 0x0
	int _0s32; // 0x0
	int s32; // 0x4
	signed long long s64; // 0x0
	unsigned int _0u32; // 0x0
	unsigned int u32; // 0x4
	unsigned long long u64; // 0x0
};

// size: 0x34
struct __anon_0x4FE52
{
	int nType; // 0x0
	void *pObject; // 0x4
	int nOffsetAddress; // 0x8
	int (*pfGet8)(void */* unknown0 */, unsigned int /* unknown1 */, char */* unknown2 */); // 0xC
	int (*pfGet16)(void */* unknown0 */, unsigned int /* unknown1 */, signed short */* unknown2 */); // 0x10
	int (*pfGet32)(void */* unknown0 */, unsigned int /* unknown1 */, int */* unknown2 */); // 0x14
	int (*pfGet64)(void */* unknown0 */, unsigned int /* unknown1 */, signed long long */* unknown2 */); // 0x18
	int (*pfPut8)(void */* unknown0 */, unsigned int /* unknown1 */, char */* unknown2 */); // 0x1C
	int (*pfPut16)(void */* unknown0 */, unsigned int /* unknown1 */, signed short */* unknown2 */); // 0x20
	int (*pfPut32)(void */* unknown0 */, unsigned int /* unknown1 */, int */* unknown2 */); // 0x24
	int (*pfPut64)(void */* unknown0 */, unsigned int /* unknown1 */, signed long long */* unknown2 */); // 0x28
	unsigned int nAddressPhysical0; // 0x2C
	unsigned int nAddressPhysical1; // 0x30
};

// size: 0x84
struct cpu_treeRoot
{
	unsigned short total; // 0x0
	int total_memory; // 0x4
	int root_address; // 0x8
	int start_range; // 0xC
	int end_range; // 0x10
	int cache_miss; // 0x14
	int cache[20]; // 0x18
	cpu_function *left; // 0x68
	cpu_function *right; // 0x6C
	int kill_limit; // 0x70
	int kill_number; // 0x74
	int side; // 0x78
	cpu_function *restore; // 0x7C
	int restore_side; // 0x80
};

// size: 0xC
struct _CPU_ADDRESS
{
	int nN64; // 0x0
	int nHost; // 0x4
	cpu_function *pFunction; // 0x8
};

// size: 0xC
struct __anon_0x50416
{
	unsigned int nAddress; // 0x0
	unsigned int nOpcodeOld; // 0x4
	unsigned int nOpcodeNew; // 0x8
};

// size: 0x2C8
struct OSContext
{
	unsigned long gpr[32]; // 0x0
	unsigned long cr; // 0x80
	unsigned long lr; // 0x84
	unsigned long ctr; // 0x88
	unsigned long xer; // 0x8C
	long float fpr[32]; // 0x90
	unsigned long fpscr_pad; // 0x190
	unsigned long fpscr; // 0x194
	unsigned long srr0; // 0x198
	unsigned long srr1; // 0x19C
	unsigned short mode; // 0x1A0
	unsigned short state; // 0x1A2
	unsigned long gqr[8]; // 0x1A4
	unsigned long psf_pad; // 0x1C4
	long float psf[32]; // 0x1C8
};

// size: 0x28
struct OSAlarm
{
	void (*handler)(OSAlarm */* unknown0 */, OSContext */* unknown1 */); // 0x0
	unsigned long tag; // 0x4
	signed long long fire; // 0x8
	OSAlarm *prev; // 0x10
	OSAlarm *next; // 0x14
	signed long long period; // 0x18
	signed long long start; // 0x20
};

// size: 0x28
struct cpu_optimize
{
	unsigned int validCheck; // 0x0
	unsigned int destGPR_check; // 0x4
	int destGPR; // 0x8
	int destGPR_mapping; // 0xC
	unsigned int destFPR_check; // 0x10
	int destFPR; // 0x14
	unsigned int addr_check; // 0x18
	int addr_last; // 0x1C
	unsigned int checkType; // 0x20
	unsigned int checkNext; // 0x24
};

// size: 0x12090
struct _CPU
{
	int nMode; // 0x0
	int nTick; // 0x4
	void *pHost; // 0x8
	signed long long nLo; // 0x10
	signed long long nHi; // 0x18
	int nCountAddress; // 0x20
	int iDeviceDefault; // 0x24
	unsigned int nPC; // 0x28
	unsigned int nWaitPC; // 0x2C
	unsigned int nCallLast; // 0x30
	cpu_function *pFunctionLast; // 0x34
	int nReturnAddrLast; // 0x38
	int survivalTimer; // 0x3C
	__anon_0x4F530 aGPR[32]; // 0x40
	__anon_0x4F944 aFPR[32]; // 0x140
	unsigned long long aTLB[48][5]; // 0x240
	int anFCR[32]; // 0x9C0
	signed long long anCP0[32]; // 0xA40
	int (*pfStep)(_CPU */* unknown0 */); // 0xB40
	int (*pfJump)(_CPU */* unknown0 */); // 0xB44
	int (*pfCall)(_CPU */* unknown0 */); // 0xB48
	int (*pfIdle)(_CPU */* unknown0 */); // 0xB4C
	int (*pfRam)(_CPU */* unknown0 */); // 0xB50
	int (*pfRamF)(_CPU */* unknown0 */); // 0xB54
	unsigned int nTickLast; // 0xB58
	unsigned int nRetrace; // 0xB5C
	unsigned int nRetraceUsed; // 0xB60
	__anon_0x4FE52 *apDevice[256]; // 0xB64
	unsigned char aiDevice[65536]; // 0xF64
	void *gHeap1; // 0x10F64
	void *gHeap2; // 0x10F68
	unsigned int aHeap1Flag[192]; // 0x10F6C
	unsigned int aHeap2Flag[13]; // 0x1126C
	cpu_treeRoot *gTree; // 0x112A0
	_CPU_ADDRESS aAddressCache[256]; // 0x112A4
	int nCountCodeHack; // 0x11EA4
	__anon_0x50416 aCodeHack[32]; // 0x11EA8
	signed long long nTimeRetrace; // 0x12028
	OSAlarm alarmRetrace; // 0x12030
	unsigned int nFlagRAM; // 0x12058
	unsigned int nFlagCODE; // 0x1205C
	unsigned int nCompileFlag; // 0x12060
	cpu_optimize nOptimize; // 0x12064
};

// Local to compilation unit
static int romCopyUpdate(__anon_0x4D873 *pROM)
{
	__anon_0x4CFE6 *pBlock;
	int iCache;
	int nTickLast;
	unsigned char *anData;
	unsigned int iBlock;
	unsigned int nSize;
	unsigned int nOffsetBlock;
	_CPU *pCPU;
}

// size: 0x4
enum __anon_0x51281
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

// size: 0x10
struct __anon_0x512E3
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x51394
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

// size: 0x4
enum __anon_0x514C0
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

// size: 0x88
struct __anon_0x515FB
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x51281 eMode; // 0xC
	__anon_0x512E3 romCopy; // 0x10
	__anon_0x51394 eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x514C0 storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// Location: 0x561380
__anon_0x515FB *gpSystem;

// Local to compilation unit
static int __romCopyUpdate_Complete()
{
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int romLoadUpdate(__anon_0x4D873 *pROM)
{
	int iCache;
	__anon_0x4CFE6 *pBlock;
	unsigned int iBlock0;
	unsigned int iBlock1;
	_CPU *pCPU;
}

int romLoadInProgress(__anon_0x4D873 *pROM);

// Local to compilation unit
static int __romLoadUpdate_Complete()
{
	// References: gpSystem (0x561380)
}

// Location: 0x801355D8
int gDVDResetToggle;

// Location: 0x801356D8
unsigned int gnFlagZelda;

// Location: 0x801355FC
int gbDisplayedError;

// Local to compilation unit
static int romCacheGame(__anon_0x4D873 *pROM)
{
	int blockCount;
	int nSize;
	char *szName;
	tXL_FILE *pFile;
	// References: gDVDResetToggle (0x801355D8)
	// References: gnFlagZelda (0x801356D8)
	// References: gbDisplayedError (0x801355FC)
	// References: gbProgress (0x60571380)
	// References: gpImageBack (0x64571380)
	// References: ganOffsetBlock_URAZLJ (0x10DC0E80)
	// References: ganOffsetBlock_ZLJ (0x800ED8F8)
}

// size: 0x20
struct _GXTexObj
{
	unsigned long dummy[8]; // 0x0
};

// Local to compilation unit
static int romCacheGame_ZELDA(float rProgress)
{
	int nSize;
	float matrix44[4][4];
	_GXTexObj textureObject;
	// References: gbProgress (0x60571380)
	// References: iImage$294 (0x68571380)
	// References: gpSystem (0x561380)
	// References: gpImageBack (0x64571380)
	// References: gbDisplayedError (0x801355FC)
}

// Local to compilation unit
static int romLoadRange(__anon_0x4D873 *pROM, int begin, int end, int *blockCount, int whichBlock, int (*pfProgress)(float /* unknown0 */))
{
	int iCache;
	unsigned int iBlock;
	unsigned int iBlockLast;
}

int romKeepCheck();

// Local to compilation unit
static int romLoadBlock(__anon_0x4D873 *pROM, int iBlock, int iCache, int (*pCallback)())
{
	unsigned char *anData;
	int nSizeRead;
	unsigned int nSize;
	unsigned int nOffset;
}

// Local to compilation unit
static void __romLoadBlock_CompleteGCN(long nResult)
{
	__anon_0x4D873 *pROM;
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int __romLoadBlock_Complete(__anon_0x4D873 *pROM)
{
	unsigned int iData;
	unsigned int nData;
}

// size: 0x4
enum __anon_0x5219D
{
	RCT_NONE = 4294967295,
	RCT_RAM = 0,
	RCT_ARAM = 1
};

// Local to compilation unit
static int romSetBlockCache(__anon_0x4D873 *pROM, int iBlock, __anon_0x5219D eType)
{
	__anon_0x4CFE6 *pBlock;
	int iCacheRAM;
	int iCacheARAM;
	int nOffsetRAM;
	int nOffsetARAM;
}

// Local to compilation unit
static int romMakeFreeCache(__anon_0x4D873 *pROM, int *piCache, __anon_0x5219D eType)
{
	int iCache;
	int iBlockOldest;
}

// Local to compilation unit
static int romFindOldestBlock(__anon_0x4D873 *pROM, int *piBlock, __anon_0x5219D eTypeCache, int whichBlock)
{
	__anon_0x4CFE6 *pBlock;
	int iBlock;
	int iBlockOldest;
	unsigned int nTick;
	unsigned int nTickDelta;
	unsigned int nTickDeltaOldest;
}

// Local to compilation unit
static int romFindFreeCache(__anon_0x4D873 *pROM, int *piCache, __anon_0x5219D eType)
{
	int iBlock;
}

int romFreeBlock(__anon_0x4D873 *pROM, int iBlock)
{
	int iCache;
	__anon_0x4CFE6 *pBlock;
}

int romMatchRange(__anon_0x4D873 *pROM, unsigned int nOffset, int *pnOffset0, int *pnOffset1)
{
	int iBlock;
}

int romTestARAM();

