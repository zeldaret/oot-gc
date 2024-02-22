/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_cpuGCN.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80036870 -> 0x80068368
*/

#include "dolphin/types.h"

// Erased
static s32 cpuFindBranchOffset(struct cpu_function* pFunction, s32* pnOffset, s32 nAddress, s32* anCode) {
    // Parameters
    // struct cpu_function* pFunction; // r1+0x4
    // s32* pnOffset; // r1+0x8
    // s32 nAddress; // r1+0xC
    // s32* anCode; // r1+0x10

    // Local variables
    s32 iJump; // r8
}

// Range: 0x80068238 -> 0x80068368
static s32 cpuCheckDelaySlot(u32 opcode) {
    // Parameters
    // u32 opcode; // r1+0x0

    // Local variables
    s32 flag; // r5
}

// Erased
static void cpuCompileNOP(s32* anCode, s32* iCode, s32 number) {
    // Parameters
    // s32* anCode; // r1+0x0
    // s32* iCode; // r1+0x4
    // s32 number; // r5
}

// Erased
static s32 cpuRecompileFunction(struct _CPU* pCPU, struct cpu_function* pFunction, s32 nAddressN64) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // struct cpu_function* pFunction; // r1+0xC
    // s32 nAddressN64; // r5
}

// Range: 0x8003EE04 -> 0x80068238
static s32 cpuGetPPC(struct _CPU* pCPU, s32* pnAddress, struct cpu_function* pFunction, s32* anCode, s32* piCode,
                     s32 bSlot) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // s32* pnAddress; // r18
    // struct cpu_function* pFunction; // r27
    // s32* anCode; // r31
    // s32* piCode; // r16
    // s32 bSlot; // r1+0x8C

    // Local variables
    s32 nSize; // r1+0x88
    s32 iHack; // r1+0x8
    s32 bInterpret; // r22
    s32 iCode; // r1+0x84
    s32 iJump; // r23
    s32 nAddress; // r29
    s32 nDeltaAddress; // r21
    s32 bFlag; // r15
    s32 nAddressJump; // r6
    s32 nOffset; // r25
    u32 nOpcode; // r28
    u32 nOpcodePrev; // r23
    u32 nOpcodeNext; // r24
    u32* pnOpcode; // r1+0x7C
    s32 prev; // r19
    s32 iRegisterA; // r1+0x8
    s32 iRegisterB; // r9
    s32 iRegisterC; // r7
    s32 nTemp1; // r1+0x8
    s32 nTemp2; // r1+0x8
    s32 nTemp3; // r3
    s32 update; // r14
    s32 iUpdate; // r1+0x90
    s32 nTarget; // r3

    // References
    // -> s32 ganMapGPR[32];
    // -> static s32 cpuCompile_SDC_function;
    // -> static s32 cpuCompile_SW_function;
    // -> static s32 cpuCompile_LDC_function;
    // -> static s32 cpuCompile_LW_function;
    // -> struct __anon_0x3DB14* gpSystem;
    // -> static s32 cpuCompile_SH_function;
    // -> static s32 cpuCompile_SB_function;
    // -> static s32 cpuCompile_LWR_function;
    // -> static s32 cpuCompile_LHU_function;
    // -> static s32 cpuCompile_LBU_function;
    // -> static s32 cpuCompile_LWL_function;
    // -> static s32 cpuCompile_LH_function;
    // -> static s32 cpuCompile_LB_function;
    // -> static s32 cpuCompile_L_CVT_SD_function;
    // -> static s32 cpuCompile_W_CVT_SD_function;
    // -> static s32 cpuCompile_TRUNC_W_function;
    // -> static s32 cpuCompile_FLOOR_W_function;
    // -> static s32 cpuCompile_CEIL_W_function;
    // -> static s32 cpuCompile_ROUND_W_function;
    // -> static s32 cpuCompile_D_SQRT_function;
    // -> static s32 cpuCompile_S_SQRT_function;
    // -> static s32 cpuCompile_DSUBU_function;
    // -> static s32 cpuCompile_DSUB_function;
    // -> static s32 cpuCompile_DADDU_function;
    // -> static s32 cpuCompile_DADD_function;
    // -> static s32 cpuCompile_DDIVU_function;
    // -> static s32 cpuCompile_DDIV_function;
    // -> static s32 cpuCompile_DMULTU_function;
    // -> static s32 cpuCompile_DMULT_function;
    // -> static s32 cpuCompile_DSRAV_function;
    // -> static s32 cpuCompile_DSRLV_function;
    // -> static s32 cpuCompile_DSLLV_function;
}

// Range: 0x8003E974 -> 0x8003EE04
s32 cpuMakeFunction(struct _CPU* pCPU, struct cpu_function** ppFunction, s32 nAddressN64) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // struct cpu_function** ppFunction; // r31
    // s32 nAddressN64; // r5

    // Local variables
    s32 iCode; // r1+0x2028
    s32 iCode0; // r1+0x8
    s32 iJump; // r7
    s32 iCheck; // r1+0x8
    s32 firstTime; // r24
    s32 kill_value; // r23
    s32 memory_used; // r22
    s32 codeMemory; // r1+0x8
    s32 blockMemory; // r21
    s32* chunkMemory; // r1+0x2020
    s32* anCode; // r23
    s32 nAddress; // r1+0x201C
    struct cpu_function* pFunction; // r1+0x2018
    struct __anon_0x3DE78 aJump[1024]; // r1+0x18
}

// Erased
static s32 cpuFreeFunction(struct _CPU* pCPU, struct cpu_function* pFunction) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // struct cpu_function* pFunction; // r4
}

// Range: 0x8003E4D8 -> 0x8003E974
static s32 cpuFindAddress(struct _CPU* pCPU, s32 nAddressN64, s32* pnAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // s32 nAddressN64; // r30
    // s32* pnAddressGCN; // r31

    // Local variables
    s32 iJump; // r6
    s32 iCode; // r1+0x20
    s32 nAddress; // r1+0x1C
    struct cpu_function* pFunction; // r1+0x18
}

// Erased
static s32 cpuNoBranchTo(struct cpu_function* pFunction, s32 currentAddress) {
    // Parameters
    // struct cpu_function* pFunction; // r1+0x0
    // s32 currentAddress; // r1+0x4

    // Local variables
    s32 i; // r1+0x0
}

// Erased
static s32 cpuCutStoreLoad(struct _CPU* pCPU, s32 currentAddress, s32 source) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // s32 currentAddress; // r1+0x4
    // s32 source; // r1+0x8
}

// Erased
static s32 cpuCutStoreLoadF(struct _CPU* pCPU, s32 currentAddress, s32 source) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // s32 currentAddress; // r1+0x4
    // s32 source; // r1+0x8
}

// Erased
static s32 cpuStackOffset(struct _CPU* pCPU, s32 currentAddress, s32* anCode, s32 source, s32 target) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // s32 currentAddress; // r1+0x4
    // s32* anCode; // r1+0x8
    // s32 source; // r1+0xC
    // s32 target; // r1+0x10
}

// Range: 0x8003E214 -> 0x8003E4D8
static s32 cpuNextInstruction(struct _CPU* pCPU, s32 addressN64, s32 opcode, s32* anCode, s32* iCode) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
    // s32 addressN64; // r10
    // s32 opcode; // r5
    // s32* anCode; // r1+0x14
    // s32* iCode; // r1+0x18
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
static void cpuRetraceCallback(u32 nCount) {
    // Parameters
    // u32 nCount; // r1+0x0

    // References
    // -> struct __anon_0x3DB14* gpSystem;
}

// Erased
static s32 cpuRetraceSetup(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
}

// Erased
static s32 cpuRetraceReset() {}

// Range: 0x8003DF08 -> 0x8003E204
static s32 cpuExecuteUpdate(struct _CPU* pCPU, s32* pnAddressGCN, u32 nCount) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // s32* pnAddressGCN; // r29
    // u32 nCount; // r30

    // Local variables
    enum __anon_0x44829 eModeUpdate; // r4
    struct __anon_0x3DB14* pSystem; // r31
    s32 nDelta; // r1+0x8
    u32 nCounter; // r1+0x8
    u32 nCompare; // r1+0x8

    // References
    // -> struct __anon_0x3DB14* gpSystem;
    // -> u32 nTickMultiplier;
    // -> f32 fTickScale;
}

// Range: 0x80039594 -> 0x8003DF08
static s32 cpuExecuteOpcode(struct _CPU* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // s32 nCount; // r1+0xC
    // s32 nAddressN64; // r22
    // s32 nAddressGCN; // r1+0x14

    // Local variables
    u64 save; // r25
    s32 restore; // r27
    u32 nOpcode; // r30
    u32* opcode; // r1+0x6C
    struct __anon_0x3EB4F** apDevice; // r28
    u8* aiDevice; // r29
    s32 iEntry; // r4
    s32 nCount; // r22
    char nData8; // r1+0x66
    s16 nData16; // r1+0x64
    s32 nData32; // r1+0x60
    s64 nData64; // r1+0x58
    s32 nAddress; // r23
    struct cpu_function* pFunction; // r1+0x50

    // References
    // -> s32 __float_huge[];
    // -> s32 __float_nan[];
}

// Range: 0x80039488 -> 0x80039594
static s32 cpuExecuteIdle(struct _CPU* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // s32 nCount; // r28
    // s32 nAddressN64; // r29
    // s32 nAddressGCN; // r1+0x14

    // Local variables
    struct __anon_0x443F6* pROM; // r30
}

// Range: 0x800393B8 -> 0x80039488
static s32 cpuExecuteJump(struct _CPU* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // s32 nCount; // r30
    // s32 nAddressN64; // r31
    // s32 nAddressGCN; // r1+0x14

    // References
    // -> struct __anon_0x3DB14* gpSystem;
}

// Range: 0x80039158 -> 0x800393B8
static s32 cpuExecuteCall(struct _CPU* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // s32 nCount; // r29
    // s32 nAddressN64; // r30
    // s32 nAddressGCN; // r1+0x14

    // Local variables
    s32 count; // r4
    s32* anCode; // r30
    s32 saveGCN; // r31
    struct cpu_function* node; // r1+0x18
    struct cpu_callerID* block; // r5
    s32 nDeltaAddress; // r1+0x8

    // References
    // -> s32 ganMapGPR[32];
}

// Range: 0x800382F8 -> 0x80039158
static s32 cpuExecuteLoadStore(struct _CPU* pCPU, s32 nAddressN64, s32 nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r24
    // s32 nAddressN64; // r22
    // s32 nAddressGCN; // r27

    // Local variables
    u32* opcode; // r1+0x1C
    s32 address; // r1+0x8
    s32 iRegisterA; // r5
    s32 iRegisterB; // r1+0x8
    u8 device; // r5
    s32 total; // r23
    s32 count; // r31
    s32 save; // r30
    s32 interpret; // r29
    s32* before; // r28
    s32* after; // r27
    s32 check2; // r26
    s32* anCode; // r25

    // References
    // -> s32 ganMapGPR[32];
}

// Range: 0x8003779C -> 0x800382F8
static s32 cpuExecuteLoadStoreF(struct _CPU* pCPU, s32 nAddressN64, s32 nAddressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // s32 nAddressN64; // r22
    // s32 nAddressGCN; // r25

    // Local variables
    u32* opcode; // r1+0x1C
    s32 address; // r1+0x8
    s32 iRegisterA; // r6
    s32 iRegisterB; // r1+0x8
    u8 device; // r5
    s32 total; // r30
    s32 count; // r29
    s32 save; // r28
    s32 interpret; // r27
    s32* before; // r26
    s32* after; // r25
    s32 check2; // r24
    s32* anCode; // r23

    // References
    // -> s32 ganMapGPR[32];
}

// Range: 0x800374DC -> 0x8003779C
static s32 cpuMakeLink(struct _CPU* pCPU, void (**ppfLink)(), void (*pfFunction)()) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // void (** ppfLink)(); // r30
    // void (* pfFunction)(); // r31

    // Local variables
    s32 iGPR; // r1+0x8
    s32* pnCode; // r1+0x18
    s32 nData; // r1+0x8

    // References
    // -> s32 ganMapGPR[32];
}

// Erased
static s32 cpuFreeLink(void (**ppfLink)()) {
    // Parameters
    // void (** ppfLink)(); // r1+0xC
}

// Erased
static void __cpuTest() {}

// Range: 0x80036870 -> 0x800374DC
s32 cpuExecute(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    s32 iGPR; // r8
    s32* pnCode; // r1+0x54
    s32 nData; // r1+0x8
    struct cpu_function* pFunction; // r1+0x4C
    void (*pfCode)(); // r1+0x48

    // References
    // -> static s32 cpuCompile_LWR_function;
    // -> static s32 cpuCompile_LWL_function;
    // -> static s32 cpuCompile_SDC_function;
    // -> static s32 cpuCompile_LDC_function;
    // -> static s32 cpuCompile_SW_function;
    // -> static s32 cpuCompile_SH_function;
    // -> static s32 cpuCompile_SB_function;
    // -> static s32 cpuCompile_LHU_function;
    // -> static s32 cpuCompile_LBU_function;
    // -> static s32 cpuCompile_LW_function;
    // -> static s32 cpuCompile_LH_function;
    // -> static s32 cpuCompile_LB_function;
    // -> static s32 cpuCompile_ROUND_W_function;
    // -> static s32 cpuCompile_TRUNC_W_function;
    // -> static s32 cpuCompile_FLOOR_W_function;
    // -> static s32 cpuCompile_CEIL_W_function;
    // -> static s32 cpuCompile_L_CVT_SD_function;
    // -> static s32 cpuCompile_W_CVT_SD_function;
    // -> static s32 cpuCompile_D_SQRT_function;
    // -> static s32 cpuCompile_S_SQRT_function;
    // -> static s32 cpuCompile_DSUBU_function;
    // -> static s32 cpuCompile_DSUB_function;
    // -> static s32 cpuCompile_DADDU_function;
    // -> static s32 cpuCompile_DADD_function;
    // -> static s32 cpuCompile_DDIVU_function;
    // -> static s32 cpuCompile_DDIV_function;
    // -> static s32 cpuCompile_DMULTU_function;
    // -> static s32 cpuCompile_DMULT_function;
    // -> static s32 cpuCompile_DSRAV_function;
    // -> static s32 cpuCompile_DSRLV_function;
    // -> static s32 cpuCompile_DSLLV_function;
    // -> s32 ganMapGPR[32];
}
