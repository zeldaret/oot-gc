#ifndef _DOLPHIN_OS_OSINTERRUPT_H_
#define _DOLPHIN_OS_OSINTERRUPT_H_

#include "dolphin/os/OSContext.h"
#include "dolphin/types.h"

typedef s16 __OSInterrupt;
typedef u32 OSInterruptMask;

#define __OS_INTERRUPT_MEM_0 0
#define __OS_INTERRUPT_MEM_1 1
#define __OS_INTERRUPT_MEM_2 2
#define __OS_INTERRUPT_MEM_3 3
#define __OS_INTERRUPT_MEM_ADDRESS 4
#define __OS_INTERRUPT_DSP_AI 5
#define __OS_INTERRUPT_DSP_ARAM 6
#define __OS_INTERRUPT_DSP_DSP 7
#define __OS_INTERRUPT_AI_AI 8
#define __OS_INTERRUPT_EXI_0_EXI 9
#define __OS_INTERRUPT_EXI_0_TC 10
#define __OS_INTERRUPT_EXI_0_EXT 11
#define __OS_INTERRUPT_EXI_1_EXI 12
#define __OS_INTERRUPT_EXI_1_TC 13
#define __OS_INTERRUPT_EXI_1_EXT 14
#define __OS_INTERRUPT_EXI_2_EXI 15
#define __OS_INTERRUPT_EXI_2_TC 16
#define __OS_INTERRUPT_PI_CP 17
#define __OS_INTERRUPT_PI_PE_TOKEN 18
#define __OS_INTERRUPT_PI_PE_FINISH 19
#define __OS_INTERRUPT_PI_SI 20
#define __OS_INTERRUPT_PI_DI 21
#define __OS_INTERRUPT_PI_RSW 22
#define __OS_INTERRUPT_PI_ERROR 23
#define __OS_INTERRUPT_PI_VI 24
#define __OS_INTERRUPT_PI_DEBUG 25
#define __OS_INTERRUPT_PI_HSP 26
#define __OS_INTERRUPT_MAX 32

#define OS_INTERRUPTMASK_DSP_DSP (0x80000000u >> __OS_INTERRUPT_DSP_DSP)

typedef void (*__OSInterruptHandler)(__OSInterrupt intr, OSContext* ctx);

BOOL OSDisableInterrupts(void);
BOOL OSEnableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt interrupt, __OSInterruptHandler handler);
__OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt interrupt);
OSInterruptMask __OSMaskInterrupts(OSInterruptMask mask);
OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask mask);

#endif
