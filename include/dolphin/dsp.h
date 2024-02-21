#ifndef _DOLPHIN_DSP_H_
#define _DOLPHIN_DSP_H_

#include "dolphin/os.h"

#ifdef __MWERKS__
volatile u16 __DSPRegs[] : 0xCC005000;
#else
#define __DSPRegs ((volatile u16*)0xCC005000)
#endif

typedef void (*DSPCallback)(void* task);

typedef struct DSPTaskInfo DSPTaskInfo;

struct DSPTaskInfo {
    /* 0x00 */ volatile u32 state;
    /* 0x04 */ volatile u32 priority;
    /* 0x08 */ volatile u32 flags;
    /* 0x0C */ u16* iram_mmem_addr;
    /* 0x10 */ u32 iram_length;
    /* 0x14 */ u32 iram_addr;
    /* 0x18 */ u16* dram_mmem_addr;
    /* 0x1C */ u32 dram_length;
    /* 0x20 */ u32 dram_addr;
    /* 0x24 */ u16 dsp_init_vector;
    /* 0x26 */ u16 dsp_resume_vector;
    /* 0x28 */ DSPCallback init_cb;
    /* 0x2C */ DSPCallback res_cb;
    /* 0x30 */ DSPCallback done_cb;
    /* 0x34 */ DSPCallback req_cb;
    /* 0x38 */ DSPTaskInfo* next;
    /* 0x3C */ DSPTaskInfo* prev;
    /* 0x40 */ OSTime t_context;
    /* 0x48 */ OSTime t_task;
};

void DSPInit(void);
u32 DSPCheckMailFromDSP(void);
u32 DSPCheckMailToDSP(void);
u32 DSPReadMailFromDSP(void);
void DSPSendMailToDSP(u32 msg);
DSPTaskInfo* DSPAddTask(DSPTaskInfo* task);

#endif
