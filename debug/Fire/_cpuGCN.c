int cpuExecute(_CPU *pCPU)
{
	int iGPR;
	int *pnCode;
	int nData;
	cpu_function *pFunction;
	void (*pfCode)();
	// References: cpuCompile_LWR_function (0x5C571380)
	// References: cpuCompile_LWL_function (0x58571380)
	// References: cpuCompile_SDC_function (0x54571380)
	// References: cpuCompile_LDC_function (0x50571380)
	// References: cpuCompile_SW_function (0x4C571380)
	// References: cpuCompile_SH_function (0x48571380)
	// References: cpuCompile_SB_function (0x44571380)
	// References: cpuCompile_LHU_function (0x40571380)
	// References: cpuCompile_LBU_function (0x3C571380)
	// References: cpuCompile_LW_function (0x38571380)
	// References: cpuCompile_LH_function (0x34571380)
	// References: cpuCompile_LB_function (0x30571380)
	// References: cpuCompile_ROUND_W_function (0x28571380)
	// References: cpuCompile_TRUNC_W_function (0x2C571380)
	// References: cpuCompile_FLOOR_W_function (0x24571380)
	// References: cpuCompile_CEIL_W_function (0x20571380)
	// References: cpuCompile_L_CVT_SD_function (0x1C571380)
	// References: cpuCompile_W_CVT_SD_function (0x18571380)
	// References: cpuCompile_D_SQRT_function (0x14571380)
	// References: cpuCompile_S_SQRT_function (0x10571380)
	// References: cpuCompile_DSUBU_function (0xC571380)
	// References: cpuCompile_DSUB_function (0x8571380)
	// References: cpuCompile_DADDU_function (0x4571380)
	// References: cpuCompile_DADD_function (0x571380)
	// References: cpuCompile_DDIVU_function (0x801356FC)
	// References: cpuCompile_DDIV_function (0x801356F8)
	// References: cpuCompile_DMULTU_function (0x801356F4)
	// References: cpuCompile_DMULT_function (0x801356F0)
	// References: cpuCompile_DSRAV_function (0x801356EC)
	// References: cpuCompile_DSRLV_function (0x801356E8)
	// References: cpuCompile_DSLLV_function (0x801356E4)
	// References: ganMapGPR (0x70BE0E80)
}

void __cpuTest();

int cpuFreeLink(void (**ppfLink)());

// Local to compilation unit
static int cpuMakeLink(_CPU *pCPU, void (**ppfLink)(), void (*pfFunction)())
{
	int iGPR;
	int *pnCode;
	int nData;
	// References: ganMapGPR (0x70BE0E80)
}

// Local to compilation unit
static int cpuExecuteLoadStoreF(_CPU *pCPU, int nAddressN64, int nAddressGCN)
{
	unsigned int *opcode;
	int address;
	int iRegisterA;
	int iRegisterB;
	unsigned char device;
	int total;
	int count;
	int save;
	int interpret;
	int *before;
	int *after;
	int check2;
	int *anCode;
	// References: ganMapGPR (0x70BE0E80)
}

// Local to compilation unit
static int cpuExecuteLoadStore(_CPU *pCPU, int nAddressN64, int nAddressGCN)
{
	unsigned int *opcode;
	int address;
	int iRegisterA;
	int iRegisterB;
	unsigned char device;
	int total;
	int count;
	int save;
	int interpret;
	int *before;
	int *after;
	int check2;
	int *anCode;
	// References: ganMapGPR (0x70BE0E80)
}

// Local to compilation unit
static int cpuExecuteCall(_CPU *pCPU, int nCount, int nAddressN64, int nAddressGCN)
{
	int count;
	int *anCode;
	int saveGCN;
	cpu_function *node;
	cpu_callerID *block;
	int nDeltaAddress;
	// References: ganMapGPR (0x70BE0E80)
}

// Local to compilation unit
static int cpuExecuteJump(_CPU *pCPU, int nCount, int nAddressN64, int nAddressGCN)
{
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int cpuExecuteIdle(_CPU *pCPU, int nCount, int nAddressN64, int nAddressGCN)
{
	__anon_0x443F6 *pROM;
}

// Local to compilation unit
static int cpuExecuteOpcode(_CPU *pCPU, int nCount, int nAddressN64, int nAddressGCN)
{
	unsigned long long save;
	int restore;
	unsigned int nOpcode;
	unsigned int *opcode;
	__anon_0x3EB4F **apDevice;
	unsigned char *aiDevice;
	int iEntry;
	int nCount;
	char nData8;
	signed short nData16;
	int nData32;
	signed long long nData64;
	int nAddress;
	cpu_function *pFunction;
	// References: __float_huge (0x7C3E0F80)
	// References: __float_nan (0x783E0F80)
}

// Local to compilation unit
static int cpuExecuteUpdate(_CPU *pCPU, int *pnAddressGCN, unsigned int nCount)
{
	__anon_0x44829 eModeUpdate;
	__anon_0x3DB14 *pSystem;
	int nDelta;
	unsigned int nCounter;
	unsigned int nCompare;
	// References: gpSystem (0x561380)
	// References: nTickMultiplier (0x604E1380)
	// References: fTickScale (0x644E1380)
}

int cpuRetraceReset();

int cpuRetraceSetup(_CPU *pCPU);

// Local to compilation unit
static void cpuRetraceCallback(unsigned int nCount)
{
	// References: gpSystem (0x561380)
}

void cpuAlarmCallback(OSAlarm *pAlarm)
{
	_CPU *pCPU;
	// References: gpSystem (0x561380)
}

// Local to compilation unit
static int cpuNextInstruction(_CPU *pCPU, int addressN64, int opcode, int *anCode, int *iCode);

int cpuStackOffset(_CPU *pCPU, int currentAddress, int *anCode, int source, int target);

int cpuCutStoreLoadF(_CPU *pCPU, int currentAddress, int source);

int cpuCutStoreLoad(_CPU *pCPU, int currentAddress, int source);

int cpuNoBranchTo(cpu_function *pFunction, int currentAddress)
{
	int i;
}

// Local to compilation unit
static int cpuFindAddress(_CPU *pCPU, int nAddressN64, int *pnAddressGCN)
{
	int iJump;
	int iCode;
	int nAddress;
	cpu_function *pFunction;
}

int cpuFreeFunction(_CPU *pCPU, cpu_function *pFunction);

int cpuMakeFunction(_CPU *pCPU, cpu_function **ppFunction, int nAddressN64)
{
	int iCode;
	int iCode0;
	int iJump;
	int iCheck;
	int firstTime;
	int kill_value;
	int memory_used;
	int codeMemory;
	int blockMemory;
	int *chunkMemory;
	int *anCode;
	int nAddress;
	cpu_function *pFunction;
	__anon_0x3DE78 aJump[1024];
}

// Local to compilation unit
static int cpuGetPPC(_CPU *pCPU, int *pnAddress, cpu_function *pFunction, int *anCode, int *piCode, int bSlot)
{
	int nSize;
	int iHack;
	int bInterpret;
	int iCode;
	int iJump;
	int nAddress;
	int nDeltaAddress;
	int bFlag;
	int nAddressJump;
	int nOffset;
	unsigned int nOpcode;
	unsigned int nOpcodePrev;
	unsigned int nOpcodeNext;
	unsigned int *pnOpcode;
	int prev;
	int iRegisterA;
	int iRegisterB;
	int iRegisterC;
	int nTemp1;
	int nTemp2;
	int nTemp3;
	int update;
	int iUpdate;
	int nTarget;
	// References: ganMapGPR (0x70BE0E80)
	// References: cpuCompile_SDC_function (0x54571380)
	// References: cpuCompile_SW_function (0x4C571380)
	// References: cpuCompile_LDC_function (0x50571380)
	// References: cpuCompile_LW_function (0x38571380)
	// References: gpSystem (0x561380)
	// References: cpuCompile_SH_function (0x48571380)
	// References: cpuCompile_SB_function (0x44571380)
	// References: cpuCompile_LWR_function (0x5C571380)
	// References: cpuCompile_LHU_function (0x40571380)
	// References: cpuCompile_LBU_function (0x3C571380)
	// References: cpuCompile_LWL_function (0x58571380)
	// References: cpuCompile_LH_function (0x34571380)
	// References: cpuCompile_LB_function (0x30571380)
	// References: cpuCompile_L_CVT_SD_function (0x1C571380)
	// References: cpuCompile_W_CVT_SD_function (0x18571380)
	// References: cpuCompile_TRUNC_W_function (0x2C571380)
	// References: cpuCompile_FLOOR_W_function (0x24571380)
	// References: cpuCompile_CEIL_W_function (0x20571380)
	// References: cpuCompile_ROUND_W_function (0x28571380)
	// References: cpuCompile_D_SQRT_function (0x14571380)
	// References: cpuCompile_S_SQRT_function (0x10571380)
	// References: cpuCompile_DSUBU_function (0xC571380)
	// References: cpuCompile_DSUB_function (0x8571380)
	// References: cpuCompile_DADDU_function (0x4571380)
	// References: cpuCompile_DADD_function (0x571380)
	// References: cpuCompile_DDIVU_function (0x801356FC)
	// References: cpuCompile_DDIV_function (0x801356F8)
	// References: cpuCompile_DMULTU_function (0x801356F4)
	// References: cpuCompile_DMULT_function (0x801356F0)
	// References: cpuCompile_DSRAV_function (0x801356EC)
	// References: cpuCompile_DSRLV_function (0x801356E8)
	// References: cpuCompile_DSLLV_function (0x801356E4)
}

int cpuRecompileFunction(_CPU *pCPU, cpu_function *pFunction, int nAddressN64);

void cpuCompileNOP(int *anCode, int *iCode, int number);

// Local to compilation unit
static int cpuCheckDelaySlot(unsigned int opcode)
{
	int flag;
}

int cpuFindBranchOffset(cpu_function *pFunction, int *pnOffset, int nAddress, int *anCode)
{
	int iJump;
}

