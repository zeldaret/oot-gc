#ifndef _DOLPHIN_BASE_PPCARCH_H_
#define _DOLPHIN_BASE_PPCARCH_H_

#include <dolphin/types.h>

// GEKKO registers
#define GQR0 0x390
#define GQR1 0x391
#define GQR2 0x392
#define GQR3 0x393
#define GQR4 0x394
#define GQR5 0x395
#define GQR6 0x396
#define GQR7 0x397

void PPCHalt(void);
void PPCSync(void);
void PPCMthid2(u32 newhid2);
u32 PPCMfhid2(void);
void PPCMtwpar(u32 newwpar);

#endif
