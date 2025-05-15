/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_cpuGCN.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80036870 -> 0x80068368
*/

#include "dolphin/types.h"

// Erased
static int cpuFindBranchOffset(struct cpu_function* pFunction, int* pnOffset, int nAddress, int* anCode) {
    // Parameters
    // struct cpu_function* pFunction; // r1+0x4
    // int* pnOffset; // r1+0x8
    // int nAddress; // r1+0xC
    // int* anCode; // r1+0x10

    // Local variables
    int iJump; // r8
}

// Range: 0x80068238 -> 0x80068368
static int cpuCheckDelaySlot(unsigned int opcode) {
    // Parameters
    // unsigned int opcode; // r1+0x0

    // Local variables
    int flag; // r5
}

// Erased
static void cpuCompileNOP(int* anCode, int* iCode, int number) {
    // Parameters
    // int* anCode; // r1+0x0
    // int* iCode; // r1+0x4
    // int number; // r5
}

// Erased
static int cpuRecompileFunction(struct _CPU* pCPU, struct cpu_function* pFunction, int nAddressN64) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // struct cpu_function* pFunction; // r1+0xC
    // int nAddressN64; // r5
}

// Range: 0x8003EE04 -> 0x80068238
static int cpuGetPPC(struct _CPU* pCPU, int* pnAddress, struct cpu_function* pFunction, int* anCode, int* piCode,
                     int bSlot) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* pnAddress; // r18
    // struct cpu_function* pFunction; // r27
    // int* anCode; // r31
    // int* piCode; // r16
    // int bSlot; // r1+0x8C

    // Local variables
    int nSize; // r1+0x88
    int iHack; // r1+0x8
    int bInterpret; // r22
    int iCode; // r1+0x84
    int iJump; // r23
    int nAddress; // r29
    int nDeltaAddress; // r21
    int bFlag; // r15
    int nAddressJump; // r6
    int nOffset; // r25
    unsigned int nOpcode; // r28
    unsigned int nOpcodePrev; // r23
    unsigned int nOpcodeNext; // r24
    unsigned int* pnOpcode; // r1+0x7C
    int prev; // r19
    int iRegisterA; // r1+0x8
    int iRegisterB; // r9
    int iRegisterC; // r7
    int nTemp1; // r1+0x8
    int nTemp2; // r1+0x8
    int nTemp3; // r3
    int update; // r14
    int iUpdate; // r1+0x90
    int nTarget; // r3

    // References
    // -> int ganMapGPR[32];
    // -> static int cpuCompile_SDC_function;
    // -> static int cpuCompile_SW_function;
    // -> static int cpuCompile_LDC_function;
    // -> static int cpuCompile_LW_function;
    // -> struct __anon_0x3DB14* gpSystem;
    // -> static int cpuCompile_SH_function;
    // -> static int cpuCompile_SB_function;
    // -> static int cpuCompile_LWR_function;
    // -> static int cpuCompile_LHU_function;
    // -> static int cpuCompile_LBU_function;
    // -> static int cpuCompile_LWL_function;
    // -> static int cpuCompile_LH_function;
    // -> static int cpuCompile_LB_function;
    // -> static int cpuCompile_L_CVT_SD_function;
    // -> static int cpuCompile_W_CVT_SD_function;
    // -> static int cpuCompile_TRUNC_W_function;
    // -> static int cpuCompile_FLOOR_W_function;
    // -> static int cpuCompile_CEIL_W_function;
    // -> static int cpuCompile_ROUND_W_function;
    // -> static int cpuCompile_D_SQRT_function;
    // -> static int cpuCompile_S_SQRT_function;
    // -> static int cpuCompile_DSUBU_function;
    // -> static int cpuCompile_DSUB_function;
    // -> static int cpuCompile_DADDU_function;
    // -> static int cpuCompile_DADD_function;
    // -> static int cpuCompile_DDIVU_function;
    // -> static int cpuCompile_DDIV_function;
    // -> static int cpuCompile_DMULTU_function;
    // -> static int cpuCompile_DMULT_function;
    // -> static int cpuCompile_DSRAV_function;
    // -> static int cpuCompile_DSRLV_function;
    // -> static int cpuCompile_DSLLV_function;
}

// Range: 0x8003E974 -> 0x8003EE04
int cpuMakeFunction(struct _CPU* pCPU, struct cpu_function** ppFunction, int nAddressN64) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // struct cpu_function** ppFunction; // r31
    // int nAddressN64; // r5

    // Local variables
    int iCode; // r1+0x2028
    int iCode0; // r1+0x8
    int iJump; // r7
    int iCheck; // r1+0x8
    int firstTime; // r24
    int kill_value; // r23
    int memory_used; // r22
    int codeMemory; // r1+0x8
    int blockMemory; // r21
    int* chunkMemory; // r1+0x2020
    int* anCode; // r23
    int nAddress; // r1+0x201C
    struct cpu_function* pFunction; // r1+0x2018
    struct __anon_0x3DE78 aJump[1024]; // r1+0x18
}

// Erased
static int cpuFreeFunction(struct _CPU* pCPU, struct cpu_function* pFunction) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // struct cpu_function* pFunction; // r4
}

// Range: 0x8003E4D8 -> 0x8003E974
static int cpuFindAddress(struct _CPU* pCPU, int nAddressN64, int* pnAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // int nAddressN64; // r30
    // int* pnAddressGCN; // r31

    // Local variables
    int iJump; // r6
    int iCode; // r1+0x20
    int nAddress; // r1+0x1C
    struct cpu_function* pFunction; // r1+0x18
}

// Erased
static int cpuNoBranchTo(struct cpu_function* pFunction, int currentAddress) {
    // Parameters
    // struct cpu_function* pFunction; // r1+0x0
    // int currentAddress; // r1+0x4

    // Local variables
    int i; // r1+0x0
}

// Erased
static int cpuCutStoreLoad(struct _CPU* pCPU, int currentAddress, int source) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int currentAddress; // r1+0x4
    // int source; // r1+0x8
}

// Erased
static int cpuCutStoreLoadF(struct _CPU* pCPU, int currentAddress, int source) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int currentAddress; // r1+0x4
    // int source; // r1+0x8
}

// Erased
static int cpuStackOffset(struct _CPU* pCPU, int currentAddress, int* anCode, int source, int target) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int currentAddress; // r1+0x4
    // int* anCode; // r1+0x8
    // int source; // r1+0xC
    // int target; // r1+0x10
}

// Range: 0x8003E214 -> 0x8003E4D8
static int cpuNextInstruction(struct _CPU* pCPU, int addressN64, int opcode, int* anCode, int* iCode) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
    // int addressN64; // r10
    // int opcode; // r5
    // int* anCode; // r1+0x14
    // int* iCode; // r1+0x18
}

// Erased
static void cpuAlarmCallback(struct OSAlarm* pAlarm) {
    // Parameters
    // struct OSAlarm* pAlarm; // r3

    // Local variables
    struct _CPU* pCPU; // r31

    // References
    // -> struct __anon_0x3DB14* gpSystem;
}

// Range: 0x8003E204 -> 0x8003E214
static void cpuRetraceCallback(unsigned int nCount) {
    // Parameters
    // unsigned int nCount; // r1+0x0

    // References
    // -> struct __anon_0x3DB14* gpSystem;
}

// Erased
static int cpuRetraceSetup(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
}

// Erased
static int cpuRetraceReset() {}

// Range: 0x8003DF08 -> 0x8003E204
static int cpuExecuteUpdate(struct _CPU* pCPU, int* pnAddressGCN, unsigned int nCount) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // int* pnAddressGCN; // r29
    // unsigned int nCount; // r30

    // Local variables
    enum __anon_0x44829 eModeUpdate; // r4
    struct __anon_0x3DB14* pSystem; // r31
    int nDelta; // r1+0x8
    unsigned int nCounter; // r1+0x8
    unsigned int nCompare; // r1+0x8

    // References
    // -> struct __anon_0x3DB14* gpSystem;
    // -> unsigned int nTickMultiplier;
    // -> f32 fTickScale;
}

// Range: 0x80039594 -> 0x8003DF08
static int cpuExecuteOpcode(struct _CPU* pCPU, int nCount, int nAddressN64, int nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // int nCount; // r1+0xC
    // int nAddressN64; // r22
    // int nAddressGCN; // r1+0x14

    // Local variables
    u64 save; // r25
    int restore; // r27
    unsigned int nOpcode; // r30
    unsigned int* opcode; // r1+0x6C
    struct __anon_0x3EB4F** apDevice; // r28
    u8* aiDevice; // r29
    int iEntry; // r4
    int nCount; // r22
    char nData8; // r1+0x66
    s16 nData16; // r1+0x64
    int nData32; // r1+0x60
    s64 nData64; // r1+0x58
    int nAddress; // r23
    struct cpu_function* pFunction; // r1+0x50

    // References
    // -> int __float_huge[];
    // -> int __float_nan[];
}

// Range: 0x80039488 -> 0x80039594
static int cpuExecuteIdle(struct _CPU* pCPU, int nCount, int nAddressN64, int nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // int nCount; // r28
    // int nAddressN64; // r29
    // int nAddressGCN; // r1+0x14

    // Local variables
    struct __anon_0x443F6* pROM; // r30
}

// Range: 0x800393B8 -> 0x80039488
static int cpuExecuteJump(struct _CPU* pCPU, int nCount, int nAddressN64, int nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // int nCount; // r30
    // int nAddressN64; // r31
    // int nAddressGCN; // r1+0x14

    // References
    // -> struct __anon_0x3DB14* gpSystem;
}

// Range: 0x80039158 -> 0x800393B8
static int cpuExecuteCall(struct _CPU* pCPU, int nCount, int nAddressN64, int nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // int nCount; // r29
    // int nAddressN64; // r30
    // int nAddressGCN; // r1+0x14

    // Local variables
    int count; // r4
    int* anCode; // r30
    int saveGCN; // r31
    struct cpu_function* node; // r1+0x18
    struct cpu_callerID* block; // r5
    int nDeltaAddress; // r1+0x8

    // References
    // -> int ganMapGPR[32];
}

// Range: 0x800382F8 -> 0x80039158
static int cpuExecuteLoadStore(struct _CPU* pCPU, int nAddressN64, int nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r24
    // int nAddressN64; // r22
    // int nAddressGCN; // r27

    // Local variables
    unsigned int* opcode; // r1+0x1C
    int address; // r1+0x8
    int iRegisterA; // r5
    int iRegisterB; // r1+0x8
    u8 device; // r5
    int total; // r23
    int count; // r31
    int save; // r30
    int interpret; // r29
    int* before; // r28
    int* after; // r27
    int check2; // r26
    int* anCode; // r25

    // References
    // -> int ganMapGPR[32];
}

// Range: 0x8003779C -> 0x800382F8
static int cpuExecuteLoadStoreF(struct _CPU* pCPU, int nAddressN64, int nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // int nAddressN64; // r22
    // int nAddressGCN; // r25

    // Local variables
    unsigned int* opcode; // r1+0x1C
    int address; // r1+0x8
    int iRegisterA; // r6
    int iRegisterB; // r1+0x8
    u8 device; // r5
    int total; // r30
    int count; // r29
    int save; // r28
    int interpret; // r27
    int* before; // r26
    int* after; // r25
    int check2; // r24
    int* anCode; // r23

    // References
    // -> int ganMapGPR[32];
}

// Range: 0x800374DC -> 0x8003779C
static int cpuMakeLink(struct _CPU* pCPU, void (**ppfLink)(), void (*pfFunction)()) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // void (** ppfLink)(); // r30
    // void (* pfFunction)(); // r31

    // Local variables
    int iGPR; // r1+0x8
    int* pnCode; // r1+0x18
    int nData; // r1+0x8

    // References
    // -> int ganMapGPR[32];
}

// Erased
static int cpuFreeLink(void (**ppfLink)()) {
    // Parameters
    // void (** ppfLink)(); // r1+0xC
}

// Erased
static void __cpuTest() {}

// Range: 0x80036870 -> 0x800374DC
int cpuExecute(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int iGPR; // r8
    int* pnCode; // r1+0x54
    int nData; // r1+0x8
    struct cpu_function* pFunction; // r1+0x4C
    void (*pfCode)(); // r1+0x48

    // References
    // -> static int cpuCompile_LWR_function;
    // -> static int cpuCompile_LWL_function;
    // -> static int cpuCompile_SDC_function;
    // -> static int cpuCompile_LDC_function;
    // -> static int cpuCompile_SW_function;
    // -> static int cpuCompile_SH_function;
    // -> static int cpuCompile_SB_function;
    // -> static int cpuCompile_LHU_function;
    // -> static int cpuCompile_LBU_function;
    // -> static int cpuCompile_LW_function;
    // -> static int cpuCompile_LH_function;
    // -> static int cpuCompile_LB_function;
    // -> static int cpuCompile_ROUND_W_function;
    // -> static int cpuCompile_TRUNC_W_function;
    // -> static int cpuCompile_FLOOR_W_function;
    // -> static int cpuCompile_CEIL_W_function;
    // -> static int cpuCompile_L_CVT_SD_function;
    // -> static int cpuCompile_W_CVT_SD_function;
    // -> static int cpuCompile_D_SQRT_function;
    // -> static int cpuCompile_S_SQRT_function;
    // -> static int cpuCompile_DSUBU_function;
    // -> static int cpuCompile_DSUB_function;
    // -> static int cpuCompile_DADDU_function;
    // -> static int cpuCompile_DADD_function;
    // -> static int cpuCompile_DDIVU_function;
    // -> static int cpuCompile_DDIV_function;
    // -> static int cpuCompile_DMULTU_function;
    // -> static int cpuCompile_DMULT_function;
    // -> static int cpuCompile_DSRAV_function;
    // -> static int cpuCompile_DSRLV_function;
    // -> static int cpuCompile_DSLLV_function;
    // -> int ganMapGPR[32];
}
