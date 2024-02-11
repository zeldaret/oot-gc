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

// Location: 0x58B60E80
_XL_OBJECTTYPE gClassCPU;

// Local to compilation unit
// Location: 0x68B60E80
static char  *gaszNameGPR[32];

// Local to compilation unit
// Location: 0x800EB6E8
static char  *gaszNameFPR[32];

// Local to compilation unit
// Location: 0x50B80E80
static char  *gaszNameCP0[32];

// Local to compilation unit
// Location: 0x4BB0E80
static char  *gaszNameCP1[32];

// Local to compilation unit
// Location: 0x800EBB88
static signed long long ganMaskGetCP0[32];

// Local to compilation unit
// Location: 0x800EBC88
static signed long long ganMaskSetCP0[32];

// Local to compilation unit
// Location: 0x800EBD88
static unsigned char Opcode[64];

// Local to compilation unit
// Location: 0x800EBDC8
static unsigned char SpecialOpcode[64];

// Local to compilation unit
// Location: 0x8BE0E80
static unsigned char RegimmOpcode[32];

// Location: 0x801356E0
void *gHeapTree;

// Local to compilation unit
// Location: 0x28BE0E80
static unsigned int ganOpcodeSaveFP1[5];

// Local to compilation unit
// Location: 0x3CBE0E80
static unsigned int ganOpcodeSaveFP2_0[5];

// Local to compilation unit
// Location: 0x50BE0E80
static unsigned int ganOpcodeSaveFP2_1[3];

// Local to compilation unit
// Location: 0x5CBE0E80
static unsigned int ganOpcodeLoadFP[5];

// Location: 0x70BE0E80
int ganMapGPR[32];

// Local to compilation unit
// Location: 0x801356E4
static int cpuCompile_DSLLV_function;

// Local to compilation unit
// Location: 0x801356E8
static int cpuCompile_DSRLV_function;

// Local to compilation unit
// Location: 0x801356EC
static int cpuCompile_DSRAV_function;

// Local to compilation unit
// Location: 0x801356F0
static int cpuCompile_DMULT_function;

// Local to compilation unit
// Location: 0x801356F4
static int cpuCompile_DMULTU_function;

// Local to compilation unit
// Location: 0x801356F8
static int cpuCompile_DDIV_function;

// Local to compilation unit
// Location: 0x801356FC
static int cpuCompile_DDIVU_function;

// Local to compilation unit
// Location: 0x571380
static int cpuCompile_DADD_function;

// Local to compilation unit
// Location: 0x4571380
static int cpuCompile_DADDU_function;

// Local to compilation unit
// Location: 0x8571380
static int cpuCompile_DSUB_function;

// Local to compilation unit
// Location: 0xC571380
static int cpuCompile_DSUBU_function;

// Local to compilation unit
// Location: 0x10571380
static int cpuCompile_S_SQRT_function;

// Local to compilation unit
// Location: 0x14571380
static int cpuCompile_D_SQRT_function;

// Local to compilation unit
// Location: 0x18571380
static int cpuCompile_W_CVT_SD_function;

// Local to compilation unit
// Location: 0x1C571380
static int cpuCompile_L_CVT_SD_function;

// Local to compilation unit
// Location: 0x20571380
static int cpuCompile_CEIL_W_function;

// Local to compilation unit
// Location: 0x24571380
static int cpuCompile_FLOOR_W_function;

// Local to compilation unit
// Location: 0x28571380
static int cpuCompile_ROUND_W_function;

// Local to compilation unit
// Location: 0x2C571380
static int cpuCompile_TRUNC_W_function;

// Local to compilation unit
// Location: 0x30571380
static int cpuCompile_LB_function;

// Local to compilation unit
// Location: 0x34571380
static int cpuCompile_LH_function;

// Local to compilation unit
// Location: 0x38571380
static int cpuCompile_LW_function;

// Local to compilation unit
// Location: 0x3C571380
static int cpuCompile_LBU_function;

// Local to compilation unit
// Location: 0x40571380
static int cpuCompile_LHU_function;

// Local to compilation unit
// Location: 0x44571380
static int cpuCompile_SB_function;

// Local to compilation unit
// Location: 0x48571380
static int cpuCompile_SH_function;

// Local to compilation unit
// Location: 0x4C571380
static int cpuCompile_SW_function;

// Local to compilation unit
// Location: 0x50571380
static int cpuCompile_LDC_function;

// Local to compilation unit
// Location: 0x54571380
static int cpuCompile_SDC_function;

// Local to compilation unit
// Location: 0x58571380
static int cpuCompile_LWL_function;

// Local to compilation unit
// Location: 0x5C571380
static int cpuCompile_LWR_function;

// Location: 0x580A1380
unsigned int aHeapTreeFlag[125];

// size: 0x4
enum __anon_0x3D79A
{
	SM_NONE = 4294967295,
	SM_RUNNING = 0,
	SM_STOPPED = 1
};

// size: 0x10
struct __anon_0x3D7FC
{
	int nSize; // 0x0
	int nOffsetRAM; // 0x4
	int nOffsetROM; // 0x8
	int (*pCallback)(); // 0xC
};

// size: 0x4
enum __anon_0x3D8AD
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
enum __anon_0x3D9D9
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
struct __anon_0x3DB14
{
	void *pFrame; // 0x0
	void *pSound; // 0x4
	int bException; // 0x8
	__anon_0x3D79A eMode; // 0xC
	__anon_0x3D7FC romCopy; // 0x10
	__anon_0x3D8AD eTypeROM; // 0x20
	void *apObject[16]; // 0x24
	unsigned long long nAddressBreak; // 0x68
	__anon_0x3D9D9 storageDevice; // 0x70
	unsigned char anException[16]; // 0x74
	int bJapaneseVersion; // 0x84
};

// Location: 0x561380
__anon_0x3DB14 *gpSystem;

int cpuUpdateDiskChecksum(unsigned int *checksum, int startAddress, int endAddress)
{
	int count;
	int instruction;
	int check;
	unsigned int *opcode;
	unsigned int part;
	// References: gpSystem (0x561380)
}

// size: 0x8
struct __anon_0x3DE78
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
	__anon_0x3DE78 *aJump; // 0xC
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
union __anon_0x3E22D
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
union __anon_0x3E641
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
struct __anon_0x3EB4F
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
struct __anon_0x3F080
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
	__anon_0x3E22D aGPR[32]; // 0x40
	__anon_0x3E641 aFPR[32]; // 0x140
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
	__anon_0x3EB4F *apDevice[256]; // 0xB64
	unsigned char aiDevice[65536]; // 0xF64
	void *gHeap1; // 0x10F64
	void *gHeap2; // 0x10F68
	unsigned int aHeap1Flag[192]; // 0x10F6C
	unsigned int aHeap2Flag[13]; // 0x1126C
	cpu_treeRoot *gTree; // 0x112A0
	_CPU_ADDRESS aAddressCache[256]; // 0x112A4
	int nCountCodeHack; // 0x11EA4
	__anon_0x3F080 aCodeHack[32]; // 0x11EA8
	signed long long nTimeRetrace; // 0x12028
	OSAlarm alarmRetrace; // 0x12030
	unsigned int nFlagRAM; // 0x12058
	unsigned int nFlagCODE; // 0x1205C
	unsigned int nCompileFlag; // 0x12060
	cpu_optimize nOptimize; // 0x12064
};

int cpuCheckOpcodeHack(_CPU *pCPU, int startAddress, int instruction)
{
	int iHack;
	unsigned int *opcode;
}

// size: 0x40
struct cpu_disk_node
{
	unsigned int functionLength; // 0x0
	unsigned int checksum; // 0x4
	int startAddress; // 0x8
	int endAddress; // 0xC
	unsigned int specialFlag; // 0x10
	unsigned int frequency; // 0x14
	unsigned int inCatalog; // 0x18
	unsigned int *length; // 0x1C
	unsigned int size; // 0x20
	unsigned int GCNsize; // 0x24
	unsigned int *N64code; // 0x28
	unsigned int *GCNcode; // 0x2C
	cpu_disk_node *prev; // 0x30
	cpu_disk_node *left; // 0x34
	cpu_disk_node *right; // 0x38
	cpu_disk_node *same; // 0x3C
};

int cpuDoubleCheckSameChecksum(cpu_disk_node *pDisk, int start)
{
	int count;
	int instruction;
	unsigned int *last;
	unsigned int *current;
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int cpuOpcodeChecksum(unsigned int opcode)
{
	int flag;
}

int treeMemory(_CPU *pCPU);

// Local to compilation unit
static int treePrintNode(_CPU *pCPU, cpu_function *tree, int print_flag, int *left, int *right)
{
	cpu_function *current;
	int flag;
	int level;
	// References: ganMapGPR (0x70BE0E80)
}

int treePrint(_CPU *pCPU)
{
	cpu_treeRoot *root;
	int left;
	int right;
}

// Local to compilation unit
static int treeForceCleanNodes(_CPU *pCPU, cpu_function *tree, int kill_limit)
{
	cpu_function *current;
	cpu_function *kill;
}

int treeForceCleanUp(_CPU *pCPU, cpu_function *node, int kill_value)
{
	cpu_treeRoot *root;
}

// Local to compilation unit
static int treeCleanNodes(_CPU *pCPU, cpu_function *top)
{
	cpu_function **current;
	cpu_function *kill;
	cpu_treeRoot *root;
	int kill_limit;
}

// Local to compilation unit
static int treeCleanUp(_CPU *pCPU, cpu_treeRoot *root)
{
	int done;
	int complete;
}

int treeCleanUpCheck(_CPU *pCPU, cpu_function *node)
{
	cpu_treeRoot *root;
}

// Local to compilation unit
static int treeTimerCheck(_CPU *pCPU)
{
	cpu_treeRoot *root;
	int begin;
	int end;
}

// Local to compilation unit
static int treeKillReason(_CPU *pCPU, int *value);

// Local to compilation unit
static int treeKillRange(_CPU *pCPU, cpu_function *tree, int start, int end)
{
	cpu_treeRoot *root;
	cpu_function *node1;
	cpu_function *node2;
	cpu_function *save1;
	cpu_function *save2;
	cpu_function *connect;
	int update;
	int count;
	// References: aHeapTreeFlag (0x580A1380)
}

// Local to compilation unit
static int treeSearchNode(cpu_function *tree, int target, cpu_function **node)
{
	cpu_function *current;
}

int treeSearch(_CPU *pCPU, int target, cpu_function **node)
{
	cpu_treeRoot *root;
	int flag;
}

// Local to compilation unit
static int treeAdjustRoot(_CPU *pCPU, int new_end)
{
	int old_root;
	int new_root;
	int kill_start;
	int check1;
	int check2;
	unsigned short total;
	int total_memory;
	int address;
	cpu_treeRoot *root;
	cpu_function *node;
	cpu_function *change;
}

// Local to compilation unit
static int treeBalance(cpu_treeRoot *root)
{
	cpu_function *tree;
	cpu_function *current;
	cpu_function *save;
	int total;
	int count;
}

// Local to compilation unit
static int treeInsertNode(cpu_function **tree, int start, int end, cpu_function **ppFunction)
{
	cpu_function **current;
	cpu_function *prev;
}

int treeInsert(_CPU *pCPU, int start, int end)
{
	cpu_treeRoot *root;
	cpu_function *current;
	int flag;
}

int treeInsertAndReturn(_CPU *pCPU, int start, int end, cpu_function **ppFunction)
{
	cpu_treeRoot *root;
	int flag;
}

int treeRebuild(_CPU *pCPU, int start_address, cpu_function **node);

// Local to compilation unit
static int treeDeleteNode(_CPU *pCPU, cpu_function **top, cpu_function *kill)
{
	cpu_treeRoot *root;
	cpu_function *save1;
	cpu_function *save2;
	cpu_function *connect;
	// References: aHeapTreeFlag (0x580A1380)
}

// Local to compilation unit
static int treeKillNodes(_CPU *pCPU, cpu_function *tree)
{
	cpu_function *current;
	cpu_function *kill;
	int count;
	// References: aHeapTreeFlag (0x580A1380)
}

// Local to compilation unit
static int treeKill(_CPU *pCPU)
{
	cpu_treeRoot *root;
	int count;
	// References: aHeapTreeFlag (0x580A1380)
}

// Local to compilation unit
static int treeInitNode(cpu_function **tree, cpu_function *prev, int start, int end)
{
	cpu_function *node;
	int where;
}

// Local to compilation unit
static int treeInit(_CPU *pCPU, int root_address)
{
	cpu_treeRoot *root;
}

// Local to compilation unit
static int treeCallerCheck(_CPU *pCPU, cpu_function *tree, int flag, int nAddress0, int nAddress1)
{
	int count;
	int saveGCN;
	int saveN64;
	int *addr_function;
	int *addr_call;
}

int treeCallerKill(_CPU *pCPU, cpu_function *kill)
{
	int left;
	int right;
	cpu_treeRoot *root;
}

void treeCallerInit(cpu_callerID *block, int total)
{
	int count;
}

// Local to compilation unit
static int cpuDMAUpdateFunction(_CPU *pCPU, int start, int end)
{
	cpu_treeRoot *root;
	int count;
	int cancel;
}

int cpuFindFunction(_CPU *pCPU, int theAddress, cpu_function **tree_node)
{
	__anon_0x3EB4F **apDevice;
	unsigned char *aiDevice;
	unsigned int opcode;
	unsigned char follow;
	unsigned char valid;
	unsigned char check;
	unsigned char end_flag;
	unsigned char save_restore;
	unsigned char alert;
	int beginAddress;
	int cheat_address;
	int current_address;
	int temp_address;
	int branch;
	// References: Opcode (0x800EBD88)
	// References: RegimmOpcode (0x8BE0E80)
	// References: SpecialOpcode (0x800EBDC8)
}

int cpuTreeFree(cpu_function *pFunction)
{
	unsigned int *anPack;
	int iPack;
	unsigned int nMask;
	// References: aHeapTreeFlag (0x580A1380)
}

// Local to compilation unit
static int cpuTreeTake(void *heap, int *where)
{
	int done;
	int nOffset;
	int nCount;
	int iPack;
	unsigned int nPack;
	unsigned int nMask;
	unsigned int nMask0;
	// References: gHeapTree (0x801356E0)
	// References: aHeapTreeFlag (0x580A1380)
}

int cpuHeapFree(_CPU *pCPU, cpu_function *pFunction)
{
	unsigned int *anPack;
	int iPack;
	unsigned int nMask;
}

int cpuHeapTake(void *heap, _CPU *pCPU, cpu_function *pFunction, int memory_size)
{
	int done;
	int second;
	unsigned int *anPack;
	int nPackCount;
	int nBlockCount;
	int nOffset;
	int nCount;
	int iPack;
	unsigned int nPack;
	unsigned int nMask;
	unsigned int nMask0;
}

// Local to compilation unit
static int cpuHeapReset(unsigned int *array, int count)
{
	int i;
}

int cpuGetFunctionChecksum(_CPU *pCPU, unsigned int *pnChecksum, cpu_function *pFunction)
{
	int nSize;
	unsigned int *pnBuffer;
	unsigned int nChecksum;
	unsigned int nData;
}

int cpuInvalidateCache(_CPU *pCPU, int nAddress0, int nAddress1);

int cpuGetOffsetAddress(_CPU *pCPU, unsigned int *anAddress, int *pnCount, unsigned int nOffset, unsigned int nSize)
{
	int iEntry;
	int iAddress;
	unsigned int nAddress;
	unsigned int nMask;
	unsigned int nSizeMapped;
}

int cpuGetAddressBuffer(_CPU *pCPU, void *ppBuffer, unsigned int nAddress)
{
	__anon_0x3EB4F *pDevice;
}

int cpuGetAddressOffset(_CPU *pCPU, int *pnOffset, unsigned int nAddress)
{
	int iDevice;
}

int cpuEvent(_CPU *pCPU, int nEvent, void *pArgument);

int cpuSetFCR(_CPU *pCPU, int *anRegister)
{
	int iRegister;
	// References: gClassCPU (0x58B60E80)
}

int cpuSetFPR(_CPU *pCPU, long float *arRegister, int bDouble)
{
	int iRegister;
	// References: gClassCPU (0x58B60E80)
}

int cpuSetCP0(_CPU *pCPU, signed long long *anRegister)
{
	int iRegister;
	// References: gClassCPU (0x58B60E80)
}

// size: 0x4
enum __anon_0x42F73
{
	CS_NONE = 4294967295,
	CS_32BIT = 0,
	CS_64BIT = 1
};

int cpuSetGPR(_CPU *pCPU, signed long long *anRegister)
{
	int iRegister;
	__anon_0x42F73 eSize;
	// References: gClassCPU (0x58B60E80)
}

int cpuSetXPC(_CPU *pCPU, signed long long nPC, signed long long nLo, signed long long nHi)
{
	// References: gClassCPU (0x58B60E80)
}

int cpuGetFCR(_CPU *pCPU, int *anRegister)
{
	int iRegister;
	// References: gClassCPU (0x58B60E80)
}

int cpuGetFPR(_CPU *pCPU, long float *arRegister, int bDouble)
{
	int iRegister;
	// References: gClassCPU (0x58B60E80)
}

int cpuGetCP0(_CPU *pCPU, signed long long *anRegister)
{
	int iRegister;
	// References: gClassCPU (0x58B60E80)
}

int cpuGetGPR(_CPU *pCPU, signed long long *anRegister)
{
	int iRegister;
	__anon_0x42F73 eSize;
	// References: gClassCPU (0x58B60E80)
}

int cpuGetXPC(_CPU *pCPU, signed long long *pnPC, signed long long *pnLo, signed long long *pnHi)
{
	// References: gClassCPU (0x58B60E80)
}

int cpuReset(_CPU *pCPU)
{
	int iRegister;
	int iTLB;
	// References: gHeapTree (0x801356E0)
	// References: aHeapTreeFlag (0x580A1380)
}

int cpuSetCodeHack(_CPU *pCPU, int nAddress, int nOpcodeOld, int nOpcodeNew)
{
	int iHack;
}

int cpuSetDevicePut(__anon_0x3EB4F *pDevice, int (*pfPut8)(void */* unknown0 */, unsigned int /* unknown1 */, char */* unknown2 */), int (*pfPut16)(void */* unknown0 */, unsigned int /* unknown1 */, signed short */* unknown2 */), int (*pfPut32)(void */* unknown0 */, unsigned int /* unknown1 */, int */* unknown2 */), int (*pfPut64)(void */* unknown0 */, unsigned int /* unknown1 */, signed long long */* unknown2 */));

int cpuSetDeviceGet(__anon_0x3EB4F *pDevice, int (*pfGet8)(void */* unknown0 */, unsigned int /* unknown1 */, char */* unknown2 */), int (*pfGet16)(void */* unknown0 */, unsigned int /* unknown1 */, signed short */* unknown2 */), int (*pfGet32)(void */* unknown0 */, unsigned int /* unknown1 */, int */* unknown2 */), int (*pfGet64)(void */* unknown0 */, unsigned int /* unknown1 */, signed long long */* unknown2 */));

int cpuMapObject(_CPU *pCPU, void *pObject, unsigned int nAddress0, unsigned int nAddress1, int nType)
{
	int iDevice;
	int iAddress;
	unsigned int nAddressVirtual0;
	unsigned int nAddressVirtual1;
}

int cpuGetOpcodeText();

// size: 0x4
enum __anon_0x43B0A
{
	RLM_NONE = 4294967295,
	RLM_PART = 0,
	RLM_FULL = 1,
	RLM_COUNT_ = 2
};

// size: 0x10
struct __anon_0x43B69
{
	int iCache; // 0x0
	unsigned int nSize; // 0x4
	unsigned int nTickUsed; // 0x8
	char keep; // 0xC
};

// size: 0x14
struct __anon_0x43C7D
{
	int bWait; // 0x0
	int (*pCallback)(); // 0x4
	unsigned char *pTarget; // 0x8
	unsigned int nSize; // 0xC
	unsigned int nOffset; // 0x10
};

// size: 0x30
struct __anon_0x43D5D
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
struct __anon_0x443F6
{
	void *pHost; // 0x0
	void *pBuffer; // 0x4
	int bFlip; // 0x8
	int bLoad; // 0xC
	char acNameFile[513]; // 0x10
	unsigned int nSize; // 0x214
	__anon_0x43B0A eModeLoad; // 0x218
	__anon_0x43B69 aBlock[4096]; // 0x21C
	unsigned int nTick; // 0x1021C
	unsigned char *pCacheRAM; // 0x10220
	unsigned char anBlockCachedRAM[1024]; // 0x10224
	unsigned char anBlockCachedARAM[2046]; // 0x10624
	__anon_0x43C7D copy; // 0x10E24
	__anon_0x43D5D load; // 0x10E38
	int nCountBlockRAM; // 0x10E68
	int nSizeCacheRAM; // 0x10E6C
	unsigned char acHeader[64]; // 0x10E70
	unsigned int *anOffsetBlock; // 0x10EB0
	int nCountOffsetBlocks; // 0x10EB4
	DVDFileInfo fileInfo; // 0x10EB8
	int offsetToRom; // 0x10EF4
};

// Location: 0x783E0F80
int __float_nan[];

// Location: 0x7C3E0F80
int __float_huge[];

// Location: 0x644E1380
float fTickScale;

// Location: 0x604E1380
unsigned int nTickMultiplier;

// size: 0x4
enum __anon_0x44829
{
	RUM_NONE = 0,
	RUM_IDLE = 1
};

int __cpuBreak(_CPU *pCPU);

int __cpuERET(_CPU *pCPU);

int cpuGetRegisterCP0(_CPU *pCPU, int iRegister, signed long long *pnData)
{
	int bFlag;
	// References: ganMaskGetCP0 (0x800EBB88)
}

int cpuSetRegisterCP0(_CPU *pCPU, int iRegister, signed long long nData)
{
	int bFlag;
	// References: ganMaskSetCP0 (0x800EBC88)
}

// size: 0x4
enum __anon_0x44AE9
{
	CM_NONE = 4294967295,
	CM_USER = 0,
	CM_SUPER = 1,
	CM_KERNEL = 2
};

// Local to compilation unit
static int cpuSetCP0_Status(_CPU *pCPU, unsigned long long nStatus)
{
	__anon_0x44AE9 eMode;
	__anon_0x44AE9 eModeLast;
	__anon_0x42F73 eSize;
	__anon_0x42F73 eSizeLast;
}

int cpuSetCP0_Config(_CPU *pCPU, unsigned int nConfig);

// Local to compilation unit
static int cpuGetSize(unsigned long long nStatus, __anon_0x42F73 *peSize, __anon_0x44AE9 *peMode)
{
	__anon_0x44AE9 eMode;
}

// Local to compilation unit
static int cpuGetMode(unsigned long long nStatus, __anon_0x44AE9 *peMode);

int cpuVirtualToPhysical_Kernel64(_CPU *pCPU, unsigned long long nAddressVirtual, unsigned int *pnAddressPhysical);

int cpuVirtualToPhysical_Kernel32(_CPU *pCPU, unsigned long long nAddressVirtual, unsigned int *pnAddressPhysical);

int cpuVirtualToPhysical_Super64(_CPU *pCPU, unsigned long long nAddressVirtual, unsigned int *pnAddressPhysical);

int cpuVirtualToPhysical_Super32(_CPU *pCPU, unsigned long long nAddressVirtual, unsigned int *pnAddressPhysical);

int cpuVirtualToPhysical_User64(_CPU *pCPU, unsigned long long nAddressVirtual, unsigned int *pnAddressPhysical);

int cpuVirtualToPhysical_User32(_CPU *pCPU, unsigned long long nAddressVirtual, unsigned int *pnAddressPhysical);

int cpuFindTLB(_CPU *pCPU, unsigned long long nAddressVirtual, unsigned int *pnAddressPhysical)
{
	int iEntry;
	unsigned int nMask;
	unsigned int nVirtual;
}

int cpuGetTLB(_CPU *pCPU, int iEntry);

// Local to compilation unit
static int cpuSetTLB(_CPU *pCPU, int iEntry)
{
	int iDevice;
	unsigned int nMask;
	unsigned int nVirtual;
	unsigned int nPhysical;
}

int cpuCountTLB(_CPU *pCPU, int *pnCount)
{
	int iEntry;
	int nCount;
}

// Local to compilation unit
static int cpuMapAddress(_CPU *pCPU, int *piDevice, unsigned int nVirtual, unsigned int nPhysical, int nSize)
{
	int iDeviceTarget;
	int iDeviceSource;
	unsigned int nAddressVirtual0;
	unsigned int nAddressVirtual1;
}

int cpuWipeDevices(_CPU *pCPU, int bFree)
{
	int iDevice;
}

// Local to compilation unit
static int cpuFreeDevice(_CPU *pCPU, int iDevice)
{
	int iAddress;
}

// Local to compilation unit
static int cpuMakeDevice(_CPU *pCPU, int *piDevice, void *pObject, int nOffset, unsigned int nAddress0, unsigned int nAddress1, int nType)
{
	__anon_0x3EB4F *pDevice;
	int iDevice;
}

// size: 0x4
enum __anon_0x45AE1
{
	CEC_NONE = 4294967295,
	CEC_INTERRUPT = 0,
	CEC_TLB_MODIFICATION = 1,
	CEC_TLB_LOAD = 2,
	CEC_TLB_STORE = 3,
	CEC_ADDRESS_LOAD = 4,
	CEC_ADDRESS_STORE = 5,
	CEC_BUS_INSTRUCTION = 6,
	CEC_BUS_DATA = 7,
	CEC_SYSCALL = 8,
	CEC_BREAK = 9,
	CEC_RESERVED = 10,
	CEC_COPROCESSOR = 11,
	CEC_OVERFLOW = 12,
	CEC_TRAP = 13,
	CEC_VCE_INSTRUCTION = 14,
	CEC_FLOAT = 15,
	CEC_RESERVED_16 = 16,
	CEC_RESERVED_17 = 17,
	CEC_RESERVED_18 = 18,
	CEC_RESERVED_19 = 19,
	CEC_RESERVED_20 = 20,
	CEC_RESERVED_21 = 21,
	CEC_RESERVED_22 = 22,
	CEC_WATCH = 23,
	CEC_RESERVED_24 = 24,
	CEC_RESERVED_25 = 25,
	CEC_RESERVED_26 = 26,
	CEC_RESERVED_27 = 27,
	CEC_RESERVED_28 = 28,
	CEC_RESERVED_29 = 29,
	CEC_RESERVED_30 = 30,
	CEC_VCE_DATA = 31,
	CEC_COUNT = 32
};

int cpuException(_CPU *pCPU, __anon_0x45AE1 eCode, int nMaskIP);

int cpuResetInterrupt(_CPU *pCPU, int nMaskIP);

int cpuTestInterrupt(_CPU *pCPU, int nMaskIP);

// size: 0xC
struct _CPU_ADDRESS
{
	int nN64; // 0x0
	int nHost; // 0x4
	cpu_function *pFunction; // 0x8
};

// Local to compilation unit
static int cpuFindCachedAddress(_CPU *pCPU, int nAddressN64, int *pnAddressHost)
{
	int iAddress;
	cpu_function *pFunction;
	_CPU_ADDRESS addressFound;
	_CPU_ADDRESS *aAddressCache;
}

int cpuFreeCachedAddress(_CPU *pCPU, int nAddress0, int nAddress1)
{
	int iAddress;
	int iAddressNext;
	int nAddressN64;
	_CPU_ADDRESS *aAddressCache;
}

int cpuMakeCachedAddress(_CPU *pCPU, int nAddressN64, int nAddressHost, cpu_function *pFunction)
{
	int iAddress;
	_CPU_ADDRESS *aAddressCache;
}

// Location: 0x800ED6C8
_XL_OBJECTTYPE gClassRAM;

// Local to compilation unit
static int cpuHackHandler(_CPU *pCPU)
{
	unsigned int nSize;
	unsigned int *pnCode;
	int iCode;
	int iSave1;
	int iSave2;
	int iLoad;
	// References: ganOpcodeLoadFP (0x5CBE0E80)
	// References: ganOpcodeSaveFP2_1 (0x50BE0E80)
	// References: ganOpcodeSaveFP2_0 (0x3CBE0E80)
	// References: ganOpcodeSaveFP1 (0x28BE0E80)
	// References: gClassRAM (0x800ED6C8)
}

int cpuHackCacheInstruction(_CPU *pCPU)
{
	unsigned int *pnCode;
}

int cpuHackIdle(_CPU *pCPU)
{
	__anon_0x3DB14 *pSystem;
}

