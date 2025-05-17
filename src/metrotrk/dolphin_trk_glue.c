#include "metrotrk/dolphin_trk_glue.h"
#include "debugger.h"
#include "dolphin/amc/AmcExi2Comm.h"
#include "metrotrk/mem_TRK.h"
#include "metrotrk/targimpl.h"
#include "metrotrk/trk.h"

static DBCommTable gDBCommTable = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

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
    bool isStub;

    if (hwId == HARDWARE_NDEV) {
        isStub = Hu_IsStub();
        gDBCommTable.initialize_func = (DBCommInitFunc)DBInitComm;
        gDBCommTable.initinterrupts_func = (DBCommFunc)DBInitInterrupts;
        gDBCommTable.peek_func = (DBCommFunc)DBQueryData;
        gDBCommTable.read_func = (DBCommReadFunc)DBRead;
        gDBCommTable.write_func = (DBCommWriteFunc)DBWrite;
        gDBCommTable.open_func = (DBCommFunc)DBOpen;
        gDBCommTable.close_func = (DBCommFunc)DBClose;
        return isStub;
    }

    isStub = AMC_IsStub();
    gDBCommTable.initialize_func = (DBCommInitFunc)EXI2_Init;
    gDBCommTable.initinterrupts_func = (DBCommFunc)EXI2_EnableInterrupts;
    gDBCommTable.peek_func = (DBCommFunc)EXI2_Poll;
    gDBCommTable.read_func = (DBCommReadFunc)EXI2_ReadN;
    gDBCommTable.write_func = (DBCommWriteFunc)EXI2_WriteN;
    gDBCommTable.open_func = (DBCommFunc)EXI2_Reserve;
    gDBCommTable.close_func = (DBCommFunc)EXI2_Unreserve;
    return isStub;
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

void ReserveEXI2Port() { gDBCommTable.open_func(); }

void UnreserveEXI2Port() { gDBCommTable.close_func(); }

void TRK_board_display(char* str) { OSReport(str); }
