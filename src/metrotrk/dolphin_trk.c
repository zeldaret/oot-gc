#include "dolphin/os.h"
#include "dolphin/types.h"
#include "macros.h"
#include "metrotrk/__exception.h"
#include "metrotrk/mpc_7xx_603e.h"
#include "metrotrk/ppc_except.h"
#include "metrotrk/ppc_targimpl.h"
#include "metrotrk/dolphin_trk_glue.h"
#include "metrotrk/mem_TRK.h"
#include "metrotrk/flush_cache.h"

#define BOOTINFO 0x80000000
#define MEM2_CACHED 0x90000000
#define DB_EXCEPTION_MASK 0x44

#define EXCEPTION_SIZE 0x100
#define NUM_EXCEPTIONS 15

static u32 TRK_ISR_OFFSETS[NUM_EXCEPTIONS] = {
    PPC_SYSTEMRESET,
    PPC_MACHINECHECK,
    PPC_DATAACCESSERROR,
    PPC_INSTACCESSERROR,
    PPC_EXTERNALINTERRUPT,
    PPC_ALIGNMENTERROR,
    PPC_PROGRAMERROR,
    PPC_FPUNAVAILABLE,
    PPC_DECREMENTERINTERRUPT,
    PPC_SYSTEMCALL,
    PPC_TRACE,
    PPC_PERFORMANCE_MONITOR,
    PPC7xx_603E_INSTR_ADDR_BREAK,
    PPC7xx_603E_SYS_MANAGE,
    PPC_THERMAL_MANAGE,
};

extern int TRK_main(void);
extern int InitMetroTRKCommTable(int hwId);
void __TRK_copy_vectors(void);

INIT void __TRK_reset(void) { __TRK_copy_vectors(); }

// Debugger stack
extern u8 _db_stack_addr[];
extern u8 _db_stack_end[];

// r5: hardware id
ASM void InitMetroTRK(void) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    addi r1, r1, -4
    stw r3, 0(r1)
    lis r3, gTRKCPUState@h
    ori r3, r3, gTRKCPUState@l
    stmw r0, ProcessorState_PPC.Default.GPR(r3) //Save the gprs
    lwz r4, 0(r1)
    addi r1, r1, 4
    stw r1, ProcessorState_PPC.Default.GPR[1](r3)
    stw r4, ProcessorState_PPC.Default.GPR[3](r3)
    mflr r4
    stw r4, ProcessorState_PPC.Default.LR(r3)
    stw r4, ProcessorState_PPC.Default.PC(r3)
    mfcr r4
    stw r4, ProcessorState_PPC.Default.CR(r3)
    //???
    mfmsr r4
    ori r3, r4, MSR_EE
    xori r3, r3, MSR_EE
    mtmsr r3
    mtsrr1 r4 //Copy msr to srr1
    //Save misc registers to gTRKCPUState
    bl TRKSaveExtended1Block
    lis r3, gTRKCPUState@h
    ori r3, r3, gTRKCPUState@l
    lmw r0, ProcessorState_PPC.Default.GPR(r3) //Restore the gprs
    //Reset IABR and DABR
    li r0, 0
    mtspr IABR, r0
    mtspr DABR, r0
    //Restore stack pointer
    lis r1, _db_stack_addr@h
    ori r1, r1, _db_stack_addr@l
    mr r3, r5
    bl InitMetroTRKCommTable //Initialize comm table
    /*
    If InitMetroTRKCommTable returned 1 (failure), an invalid hardware
    id or the id for GDEV was somehow passed. Since only BBA or NDEV
    are supported, we return early. Otherwise, we proceed with
    starting up TRK.
    */
    cmpwi r3, 1
    bne initCommTableSuccess
    /*
    BUG: The code probably orginally reloaded gTRKCPUState here, but
    as is it will read the returned value of InitMetroTRKCommTable
    as a TRKCPUState struct pointer, causing the CPU to return to
    a garbage code address.
    */
    lwz r4, ProcessorState_PPC.Default.LR(r3)
    mtlr r4
    lmw r0, ProcessorState_PPC.Default.GPR(r3) //Restore the gprs
    blr
initCommTableSuccess:
    b TRK_main //Jump to TRK_main
#endif // clang-format on
}

void EnableMetroTRKInterrupts() { EnableEXI2Interrupts(); }

void* TRKTargetTranslate(u32* addr) { return (void*)(((u32)addr & 0x3FFFFFFF) | BOOTINFO); }

static void TRK_copy_vector(u32 offset) {
    void* destPtr = TRKTargetTranslate((u32*)offset);
    TRK_memcpy(destPtr, (void*)(gTRKInterruptVectorTable + offset), EXCEPTION_SIZE);
    TRK_flush_cache((u32)destPtr, EXCEPTION_SIZE);
}

void __TRK_copy_vectors(void) {
    int i;
    u32 data;

    data = *(u32*)TRKTargetTranslate((u32*)0x44);

    for (i = 0; i <= ARRAY_COUNT(TRK_ISR_OFFSETS) - 1; i++) {
        if ((data & (1 << i)) != 0) {
            TRK_copy_vector(TRK_ISR_OFFSETS[i]);
        }
    }
}

DSError TRKInitializeTarget() {
    gTRKState.stopped = true;
    gTRKState.MSR = __TRK_get_MSR();
    return kNoError;
}
