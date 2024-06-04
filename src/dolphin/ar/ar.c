#include "dolphin/ar.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os.h"

#if IS_MQ
char* __ARVersion = "<< Dolphin SDK - AR\trelease build: Sep  5 2002 05:34:27 (0x2301) >>";
#else
char* __ARVersion = "<< Dolphin SDK - AR\trelease build: Apr 17 2003 12:33:55 (0x2301) >>";
#endif

static ARCallback __AR_Callback;
static u32 __AR_Size;
static u32 __AR_InternalSize;
static u32 __AR_ExpansionSize;

static u32 __AR_StackPointer;
static u32 __AR_FreeBlocks;
static u32* __AR_BlockLength;

static volatile bool __AR_init_flag = false;

static void __ARHandler(__OSInterrupt interrupt, OSContext* context);
static void __ARChecksize(void);
static void __ARClearArea(u32 start_addr, u32 length);

u32 ARGetDMAStatus() {
    bool enabled;
    u32 val;
    enabled = OSDisableInterrupts();
    val = __DSPRegs[DSP_CONTROL_STATUS] & 0x0200;
    OSRestoreInterrupts(enabled);
    return val;
}

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length) {
    bool enabled;

    enabled = OSDisableInterrupts();

    // Set main mem address
    __DSPRegs[DSP_ARAM_DMA_MM_HI] = (u16)(__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x3FF) | (u16)(mainmem_addr >> 16);
    __DSPRegs[DSP_ARAM_DMA_MM_LO] = (u16)(__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xFFE0) | (u16)(mainmem_addr & 0xFFFF);

    // Set ARAM address
    __DSPRegs[DSP_ARAM_DMA_ARAM_HI] = (u16)(__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x3FF) | (u16)(aram_addr >> 16);
    __DSPRegs[DSP_ARAM_DMA_ARAM_LO] = (u16)(__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xFFE0) | (u16)(aram_addr & 0xFFFF);

    // Set DMA buffer size
    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x8000) | (type << 15));
    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x3FF) | (u16)(length >> 16);
    __DSPRegs[DSP_ARAM_DMA_SIZE_LO] = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xFFE0) | (u16)(length & 0xFFFF);

    OSRestoreInterrupts(enabled);
}

u32 ARInit(u32* stack_index_addr, u32 num_entries) {
    bool old;
    u16 refresh;

    if (__AR_init_flag == true) {
        return __AR_ARAM_USR_BASE_ADDR;
    }

    OSRegisterVersion(__ARVersion);

    old = OSDisableInterrupts();

    __AR_Callback = NULL;

    __OSSetInterruptHandler(__OS_INTERRUPT_DSP_ARAM, __ARHandler);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_DSP_ARAM);

    __AR_StackPointer = __AR_ARAM_USR_BASE_ADDR;
    __AR_FreeBlocks = num_entries;
    __AR_BlockLength = stack_index_addr;

    refresh = (u16)(__DSPRegs[DSP_ARAM_REFRESH] & 0xFF);

    __DSPRegs[DSP_ARAM_REFRESH] = (u16)((__DSPRegs[DSP_ARAM_REFRESH] & ~0xFF) | (refresh & 0xFF));

    __ARChecksize();

    __AR_init_flag = true;

    OSRestoreInterrupts(old);

    return __AR_StackPointer;
}

u32 ARGetBaseAddress() { return __AR_ARAM_USR_BASE_ADDR; }

void __ARHandler(__OSInterrupt interrupt, OSContext* context) {
    OSContext exceptionContext;
    u16 tmp;

    tmp = __DSPRegs[DSP_CONTROL_STATUS];
    tmp = (u16)((tmp & ~(0x80 | 0x8)) | 0x20);
    __DSPRegs[DSP_CONTROL_STATUS] = tmp;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (__AR_Callback) {
        (*__AR_Callback)();
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

inline void __ARClearInterrupt() {
    u16 tmp;
    tmp = __DSPRegs[DSP_CONTROL_STATUS];
    tmp = (u16)((tmp & ~(0x80 | 0x8)) | 0x20);
    __DSPRegs[DSP_CONTROL_STATUS] = tmp;
}

inline void __ARWaitForDMA() {
    while (__DSPRegs[DSP_CONTROL_STATUS] & 0x0200) {}
}

inline void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length) {
    // Main mem address
    __DSPRegs[DSP_ARAM_DMA_MM_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03FF) | (u16)(mmem_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_MM_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xFFE0) | (u16)(mmem_addr & 0xFFFF));

    // ARAM address
    __DSPRegs[DSP_ARAM_DMA_ARAM_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03FF) | (u16)(aram_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_ARAM_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xFFE0) | (u16)(aram_addr & 0xFFFF));

    // DMA buffer size
    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x8000);

    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03FF) | (u16)(length >> 16));
    __DSPRegs[DSP_ARAM_DMA_SIZE_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xFFE0) | (u16)(length & 0xFFFF));

    __ARWaitForDMA();

    __ARClearInterrupt();
}

inline void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length) {
    // Main mem address
    __DSPRegs[DSP_ARAM_DMA_MM_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03FF) | (u16)(mmem_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_MM_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xFFE0) | (u16)(mmem_addr & 0xFFFF));

    // ARAM address
    __DSPRegs[DSP_ARAM_DMA_ARAM_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03FF) | (u16)(aram_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_ARAM_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xFFE0) | (u16)(aram_addr & 0xFFFF));

    // DMA buffer size
    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] | 0x8000);

    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03FF) | (u16)(length >> 16));
    __DSPRegs[DSP_ARAM_DMA_SIZE_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xFFE0) | (u16)(length & 0xFFFF));

    __ARWaitForDMA();

    __ARClearInterrupt();
}

void __ARChecksize() {
    u8 test_data_pad[0x20 + 31];
    u8 dummy_data_pad[0x20 + 31];
    u8 buffer_pad[0x20 + 31];

    u8 save_pad_1[0x20 + 31];
    u8 save_pad_2[0x20 + 31];
    u8 save_pad_3[0x20 + 31];
    u8 save_pad_4[0x20 + 31];
    u8 save_pad_5[0x20 + 31];

    u32* test_data;
    u32* dummy_data;
    u32* buffer;
    u32* save1;
    u32* save2;
    u32* save3;
    u32* save4;
    u32* save5;

    u16 ARAM_mode = 0;
    u32 ARAM_size = 0;

    u32 i;

    while (!(__DSPRegs[DSP_ARAM_MODE] & 1)) {}

    ARAM_mode = 3;
    ARAM_size = __AR_InternalSize = 0x1000000;
    __DSPRegs[DSP_ARAM_SIZE] = (u16)((__DSPRegs[DSP_ARAM_SIZE] & ~(0x7 | 0x38)) | 0x20 | 2 | 1);

    test_data = (u32*)(OSRoundUp32B((u32)(test_data_pad)));
    dummy_data = (u32*)(OSRoundUp32B((u32)(dummy_data_pad)));
    buffer = (u32*)(OSRoundUp32B((u32)(buffer_pad)));

    save1 = (u32*)(OSRoundUp32B((u32)(save_pad_1)));
    save2 = (u32*)(OSRoundUp32B((u32)(save_pad_2)));
    save3 = (u32*)(OSRoundUp32B((u32)(save_pad_3)));
    save4 = (u32*)(OSRoundUp32B((u32)(save_pad_4)));
    save5 = (u32*)(OSRoundUp32B((u32)(save_pad_5)));

    for (i = 0; i < 8; i++) {
        *(test_data + i) = 0xDEADBEEF;
        *(dummy_data + i) = 0xBAD0BAD0;
    }

    DCFlushRange((void*)test_data, 0x20);
    DCFlushRange((void*)dummy_data, 0x20);

    __AR_ExpansionSize = 0;

    DCInvalidateRange((void*)save1, 0x20);
    __ARReadDMA((u32)save1, ARAM_size + 0, 0x20);
    PPCSync();

    __ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

    memset((void*)buffer, 0, 0x20);
    DCFlushRange((void*)buffer, 0x20);

    __ARReadDMA((u32)buffer, ARAM_size + 0x0000000, 0x20);
    PPCSync();

    if (buffer[0] == test_data[0]) {

        DCInvalidateRange((void*)save2, 0x20);
        __ARReadDMA((u32)save2, ARAM_size + 0x0200000, 0x20);
        PPCSync();

        DCInvalidateRange((void*)save3, 0x20);
        __ARReadDMA((u32)save3, ARAM_size + 0x1000000, 0x20);
        PPCSync();

        DCInvalidateRange((void*)save4, 0x20);
        __ARReadDMA((u32)save4, ARAM_size + 0x0000200, 0x20);
        PPCSync();

        DCInvalidateRange((void*)save5, 0x20);
        __ARReadDMA((u32)save5, ARAM_size + 0x0400000, 0x20);
        PPCSync();

        __ARWriteDMA((u32)dummy_data, ARAM_size + 0x0200000, 0x20);

        __ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

        memset((void*)buffer, 0, 0x20);
        DCFlushRange((void*)buffer, 0x20);

        __ARReadDMA((u32)buffer, ARAM_size + 0x0200000, 0x20);
        PPCSync();

        if (buffer[0] == test_data[0]) {
            __ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);

            ARAM_mode |= 0 << 1;
            ARAM_size += 0x0200000;
            __AR_ExpansionSize = 0x0200000;
        } else {
            __ARWriteDMA((u32)dummy_data, ARAM_size + 0x1000000, 0x20);

            __ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

            memset((void*)buffer, 0, 0x20);
            DCFlushRange((void*)buffer, 0x20);

            __ARReadDMA((u32)buffer, ARAM_size + 0x1000000, 0x20);
            PPCSync();

            if (buffer[0] == test_data[0]) {
                __ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);
                __ARWriteDMA((u32)save2, ARAM_size + 0x0200000, 0x20);

                ARAM_mode |= 4 << 1;
                ARAM_size += 0x0400000;
                __AR_ExpansionSize = 0x0400000;
            } else {
                __ARWriteDMA((u32)dummy_data, ARAM_size + 0x0000200, 0x20);

                __ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

                memset((void*)buffer, 0, 0x20);
                DCFlushRange((void*)buffer, 0x20);

                __ARReadDMA((u32)buffer, ARAM_size + 0x0000200, 0x20);
                PPCSync();

                if (buffer[0] == test_data[0]) {
                    __ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);
                    __ARWriteDMA((u32)save2, ARAM_size + 0x0200000, 0x20);
                    __ARWriteDMA((u32)save3, ARAM_size + 0x1000000, 0x20);

                    ARAM_mode |= 8 << 1;
                    ARAM_size += 0x0800000;
                    __AR_ExpansionSize = 0x0800000;
                } else {
                    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x0400000, 0x20);

                    __ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

                    memset((void*)buffer, 0, 0x20);
                    DCFlushRange((void*)buffer, 0x20);

                    __ARReadDMA((u32)buffer, ARAM_size + 0x0400000, 0x20);
                    PPCSync();

                    if (buffer[0] == test_data[0]) {
                        __ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);
                        __ARWriteDMA((u32)save2, ARAM_size + 0x0200000, 0x20);
                        __ARWriteDMA((u32)save3, ARAM_size + 0x1000000, 0x20);
                        __ARWriteDMA((u32)save4, ARAM_size + 0x0000200, 0x20);

                        ARAM_mode |= 12 << 1;
                        ARAM_size += 0x1000000;
                        __AR_ExpansionSize = 0x1000000;
                    } else {
                        __ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);
                        __ARWriteDMA((u32)save2, ARAM_size + 0x0200000, 0x20);
                        __ARWriteDMA((u32)save3, ARAM_size + 0x1000000, 0x20);
                        __ARWriteDMA((u32)save4, ARAM_size + 0x0000200, 0x20);
                        __ARWriteDMA((u32)save5, ARAM_size + 0x0400000, 0x20);

                        ARAM_mode |= 16 << 1;
                        ARAM_size += 0x2000000;
                        __AR_ExpansionSize = 0x2000000;
                    }
                }
            }
        }
        __DSPRegs[DSP_ARAM_SIZE] = (u16)((__DSPRegs[DSP_ARAM_SIZE] & ~(0x7 | 0x38)) | ARAM_mode);
    }

    *(u32*)OSPhysicalToUncached(0x00D0) = ARAM_size;

    __AR_Size = ARAM_size;
}
