#include "flash.h"

_XL_OBJECTTYPE gClassFlash = {
    "FLASH",
    sizeof(Flash),
    NULL,
    (EventFunc)flashEvent,
};

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashCopyFLASH.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashTransferFLASH.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/flash/flashEvent.s")
