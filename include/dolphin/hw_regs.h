#ifndef _DOLPHIN_HW_REGS_H_
#define _DOLPHIN_HW_REGS_H_

#ifdef __MWERKS__
volatile u16 __VIRegs[59]     : 0xCC002000;
extern u32 OS_PI_INTR_CAUSE[] : 0xCC003000;
volatile u16 __DSPRegs[]      : 0xCC005000;
u32 __SIRegs[0x100]           : 0xCC006400;
u32 OS_EXI[0x40]              : 0xCC006800;
#else
#define __VIRegs         ((volatile u16 *)0xCC002000)
#define OS_PI_INTR_CAUSE ((u32 *)         0xCC003000)
#define __DSPRegs        ((volatile u16 *)0xCC005000)
#define __SIRegs         ((u32 *)         0xCC006400)
#define OS_EXI           ((u32 *)         0xCC006800)
#endif

#endif
