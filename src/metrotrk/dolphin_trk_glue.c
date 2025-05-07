#include "metrotrk/dolphin_trk_glue.h"
#include "metrotrk/cc_gdev.h"
#include "metrotrk/cc_udp.h"
#include "metrotrk/mem_TRK.h"
#include "metrotrk/targimpl.h"
#include "metrotrk/trk.h"

extern void PPCHalt(void);

static u8 TRK_Use_BBA;
static DBCommTable gDBCommTable = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};

ASM void TRKLoadContext(OSContext* ctx, u32 r4) {
#ifdef __MWERKS__ // clang-format off
    nofralloc

    lwz r0, OSContext.gpr[0](r3)
    lwz r1, OSContext.gpr[1](r3)
    lwz r2, OSContext.gpr[2](r3)
    lhz r5, OSContext.state(r3)
    rlwinm. r6, r5, 0, 0x1e, 0x1e
    beq L_802CC24C
    rlwinm r5, r5, 0, 0x1f, 0x1d
    sth r5, OSContext.state(r3)
    lmw r5, OSContext.gpr[5](r3)
    b L_802CC250
L_802CC24C:
    lmw r13, OSContext.gpr[13](r3)
L_802CC250:
    mr r31, r3
    mr r3, r4
    lwz r4, OSContext.cr(r31)
    mtcrf 0xff, r4
    lwz r4, OSContext.lr(r31)
    mtlr r4
    lwz r4, OSContext.ctr(r31)
    mtctr r4
    lwz r4, OSContext.xer(r31)
    mtxer r4
    mfmsr r4
    rlwinm r4, r4, 0, 0x11, 0xf //Turn off external exceptions
    rlwinm r4, r4, 0, 0x1f, 0x1d //Turn off recoverable exception flag
    mtmsr r4
    mtsprg 1, r2
    lwz r4, OSContext.gpr[3](r31)
    mtsprg 2, r4
    lwz r4, OSContext.gpr[4](r31)
    mtsprg 3, r4
    lwz r2, OSContext.srr0(r31)
    lwz r4, OSContext.srr1(r31)
    lwz r31, OSContext.gpr[31](r31)
    b TRKInterruptHandler
#endif // clang-format on
}

void TRKEXICallBack(short r3, OSContext* ctx) {
    OSEnableScheduler();
    TRKLoadContext(ctx, 0x500);
}

int InitMetroTRKCommTable(int hwId) {
    TRK_Use_BBA = false;

    if (hwId == HARDWARE_BBA) { // BBA hardware
        TRK_Use_BBA = true;
        gDBCommTable.initialize_func = udp_cc_initialize;
        gDBCommTable.open_func = udp_cc_open;
        gDBCommTable.close_func = udp_cc_close;
        gDBCommTable.read_func = udp_cc_read;
        gDBCommTable.write_func = udp_cc_write;
        gDBCommTable.shutdown_func = udp_cc_shutdown;
        gDBCommTable.peek_func = udp_cc_peek;
        gDBCommTable.pre_continue_func = udp_cc_pre_continue;
        gDBCommTable.post_stop_func = udp_cc_post_stop;
        gDBCommTable.initinterrupts_func = NULL;
        return 0;
    } else if (hwId == HARDWARE_NDEV) { // NDEV hardware
        // Initialize gDBCommTable
        gDBCommTable.initialize_func = gdev_cc_initialize;
        gDBCommTable.open_func = gdev_cc_open;
        gDBCommTable.close_func = gdev_cc_close;
        gDBCommTable.read_func = gdev_cc_read;
        gDBCommTable.write_func = gdev_cc_write;
        gDBCommTable.shutdown_func = gdev_cc_shutdown;
        gDBCommTable.peek_func = gdev_cc_peek;
        gDBCommTable.pre_continue_func = gdev_cc_pre_continue;
        gDBCommTable.post_stop_func = gdev_cc_post_stop;
        gDBCommTable.initinterrupts_func = gdev_cc_initinterrupts;
        return 0;
    } else { // GDEV/unknown hardware
        return 1;
    }
}

void TRKUARTInterruptHandler() {}

UARTError TRKInitializeIntDrivenUART(u32 r3, u32 r4, u32 r5, void* r6) {
    gDBCommTable.initialize_func(r6, TRKEXICallBack);
    return kUARTNoError;
}

void EnableEXI2Interrupts() { gDBCommTable.initinterrupts_func(); }

int TRKPollUART() { return gDBCommTable.peek_func(); }

UARTError TRKReadUARTN(void* bytes, u32 limit) {
    int r3 = gDBCommTable.read_func(bytes, limit);
    return !r3 ? 0 : -1;
}

UARTError TRK_WriteUARTN(const void* bytes, u32 length) {
    int r3 = gDBCommTable.write_func(bytes, length);
    return !r3 ? 0 : -1;
}

void ReserveEXI2Port() { gDBCommTable.post_stop_func(); }

void UnreserveEXI2Port() { gDBCommTable.pre_continue_func(); }

void TRK_board_display(char* str) { OSReport(str); }

void InitializeProgramEndTrap() {
    static const u32 EndofProgramInstruction = 0x00454E44; //\x00END

    u8* endOfProgramInstructionBytes = (u8*)&EndofProgramInstruction;
    u8* ppcHaltPtr = (u8*)PPCHalt;
    TRK_memcpy(ppcHaltPtr + 4, endOfProgramInstructionBytes, 4);
    ICInvalidateRange(ppcHaltPtr + 4, 4);
    DCFlushRange(ppcHaltPtr + 4, 4);
}
