#ifndef _DOLPHIN_BASE_PPCARCH_H_
#define _DOLPHIN_BASE_PPCARCH_H_

#include "dolphin/types.h"

// GEKKO registers
#define GQR0 0x390
#define GQR1 0x391
#define GQR2 0x392
#define GQR3 0x393
#define GQR4 0x394
#define GQR5 0x395
#define GQR6 0x396
#define GQR7 0x397

u32 PPCMfmsr(void);
void PPCMtmsr(u32 newMsr);

u32 PPCMfhid0(void);
void PPCMthid0(u32 newHid0);

u32 PPCMfl2cr(void);
void PPCMtl2cr(u32 newL2cr);

u32 PPCMtdec(u32 newDec);

void PPCSync(void);
void PPCHalt(void);

void PPCMtmmcr0(u32 newMmcr0);
void PPCMtmmcr1(u32 newMmcr1);
void PPCMtpmc1(u32 newPmc1);
void PPCMtpmc2(u32 newPmc2);
void PPCMtpmc3(u32 newPmc3);
void PPCMtpmc4(u32 newPmc4);

u32 PPCMffpscr(void);
void PPCMtfpscr(u32 newFpscr);

u32 PPCMfhid2(void);
void PPCMthid2(u32 newHid2);

void PPCMtwpar(u32 newWpar);

void PPCDisableSpeculation(void);
void PPCSetFpNonIEEEMode(void);

#endif
