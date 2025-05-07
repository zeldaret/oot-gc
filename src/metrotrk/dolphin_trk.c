#include "dolphin/__ppc_eabi_init.h"
#include "dolphin/os.h"
#include "dolphin/types.h"
#include "macros.h"
#include "metrotrk/__exception.h"
#include "metrotrk/mpc_7xx_603e.h"
#include "metrotrk/ppc_except.h"
#include "metrotrk/ppc_targimpl.h"

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

static u32* lc_base;

extern int TRK_main(void);
extern int InitMetroTRKCommTable(int hwId);

INIT void __TRKreset(void) { OSResetSystem(0, 0, 0); }

void EnableMetroTRKInterrupts() { EnableEXI2Interrupts(); }

void* TRKTargetTranslate(u32* addr) {
    if ((addr >= lc_base) && (addr < &lc_base[0x1000]) && (gTRKCPUState.Extended1.DBAT3U & 3)) {
        return addr;
    } else if (((u32)addr >= 0x7E000000) && ((u32)addr <= BOOTINFO)) {
        return addr;
    } else {
        return (void*)(((u32)addr & 0x3FFFFFFF) | BOOTINFO);
        ;
    }
}

static void TRK_copy_vector(u32 offset) {
    void* destPtr = TRKTargetTranslate((u32*)offset);
    TRK_memcpy(destPtr, (void*)(gTRKInterruptVectorTable + offset), EXCEPTION_SIZE);
    TRK_flush_cache(destPtr, EXCEPTION_SIZE);
}

void __TRK_copy_vectors(void) {
    int i;
    u32 data;
    u32* data_ptr;

    if ((u32)lc_base <= DB_EXCEPTION_MASK && (u32)&lc_base[0x1000] > DB_EXCEPTION_MASK &&
        gTRKCPUState.Extended1.DBAT3U & 0x3) {
        data_ptr = (u32*)DB_EXCEPTION_MASK;
    } else {
        data_ptr = (u32*)(BOOTINFO + DB_EXCEPTION_MASK);
    }

    for (i = 0, data = *data_ptr; i <= ARRAY_COUNT(TRK_ISR_OFFSETS) - 1; i++) {
        if ((data & (1 << i)) != 0 && i != 4) {
            TRK_copy_vector(TRK_ISR_OFFSETS[i]);
        }
    }
}

DSError TRKInitializeTarget() {
    gTRKState.stopped = true;
    gTRKState.MSR = __TRK_get_MSR();
    lc_base = (u32*)0xE0000000;
    return kNoError;
}

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

ASM void InitMetroTRK_BBA() {
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
    //Turn on external interrupts
    mfmsr r4
    ori r3, r4, MSR_EE
    mtmsr r3
    mtsrr1 r4 //Copy original msr to srr1
    //Save misc registers to gTRKCPUState
    bl TRKSaveExtended1Block
    lis r3, gTRKCPUState@h
    ori r3, r3, gTRKCPUState@l
    lmw r0, ProcessorState_PPC.Default.GPR(r3) //Restore the gprs
    //Reset IABR and DABR
    li r0, 0
    mtspr IABR, r0
    mtspr DABR, r0
    //Restore the stack pointer
    lis r1, _db_stack_addr@h
    ori r1, r1, _db_stack_addr@l
    li r3, 2
    bl InitMetroTRKCommTable //Initialize comm table as BBA hardware
    /*
    If InitMetroTRKCommTable returned 1 (failure), something went wrong
    or whatever reason. If everything goes as expected, we proceed with
    starting up TRK.
    */
    cmpwi r3, 1
    bne initCommTableSuccess

    //! @bug: The code probably orginally reloaded gTRKCPUState here, but
    //! as is it will read the returned value of InitMetroTRKCommTable
    //! as a TRKCPUState struct pointer, causing the CPU to return to
    //! a garbage code address.
    lwz r4, ProcessorState_PPC.Default.LR(r3)
    mtlr r4
    lmw r0, ProcessorState_PPC.Default.GPR(r3)
    blr
initCommTableSuccess:
    b TRK_main //Jump to TRK_main
    blr
#endif // clang-format on
}
