#include "dolphin/dsp.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os.h"
#include "dolphin/types.h"

bool __DSP_init_flag;

#if IS_MQ
#define BUILD_DATE "Sep  5 2002"
#define BUILD_TIME "05:35:13"
#else
#define BUILD_DATE "Apr 17 2003"
#define BUILD_TIME "12:34:16"
#endif

char* __DSPVersion = "<< Dolphin SDK - DSP\trelease build: " BUILD_DATE " " BUILD_TIME " (0x2301) >>";

u32 DSPCheckMailToDSP() { return __DSPRegs[DSP_MAILBOX_IN_HI] >> 0xF & 1; }

u32 DSPCheckMailFromDSP() { return __DSPRegs[DSP_MAILBOX_OUT_HI] >> 0xF & 1; }

u32 DSPReadMailFromDSP() { return (__DSPRegs[DSP_MAILBOX_OUT_HI] << 0x10) | __DSPRegs[DSP_MAILBOX_OUT_LO]; }

void DSPSendMailToDSP(u32 mail) {
    __DSPRegs[DSP_MAILBOX_IN_HI] = mail >> 0x10;
    __DSPRegs[DSP_MAILBOX_IN_LO] = mail;
}

void DSPInit() {
    u32 tmp;
    bool old;
    __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", BUILD_DATE, BUILD_TIME);
    if (__DSP_init_flag == true) {
        return;
    }
    OSRegisterVersion(__DSPVersion);
    old = OSDisableInterrupts();
    __OSSetInterruptHandler(7, __DSPHandler);
    __OSUnmaskInterrupts(0x80000000 >> 7);

    tmp = __DSPRegs[DSP_CONTROL_STATUS];
    __DSPRegs[DSP_CONTROL_STATUS] = (tmp & ~0xA8) | 0x800;

    tmp = __DSPRegs[DSP_CONTROL_STATUS];
    __DSPRegs[DSP_CONTROL_STATUS] = (tmp & ~0xAC);

    __DSP_tmp_task = NULL;
    __DSP_curr_task = NULL;
    __DSP_last_task = NULL;
    __DSP_first_task = NULL;
    __DSP_init_flag = true;
    OSRestoreInterrupts(old);
}

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task) {
    bool old = OSDisableInterrupts();

    __DSP_insert_task(task);
    task->state = 0;
    task->flags = 1;

    OSRestoreInterrupts(old);
    if (task == __DSP_first_task) {
        __DSP_boot_task(task);
    }
    return task;
}
