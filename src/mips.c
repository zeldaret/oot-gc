#include "mips.h"
#include "mips_jumptables.h"
#include "xlObject.h"

_XL_OBJECTTYPE gClassMips = {
    "MIPS",
    sizeof(Mips),
    NULL,
    (EventFunc)mipsEvent,
};

void* jtbl_800EE6E0[] = {
    &lbl_8008D384, &lbl_8008D3B8, &lbl_8008D3B8, &lbl_8008D3B8, &lbl_8008D390, &lbl_8008D3B8, &lbl_8008D3B8,
    &lbl_8008D3B8, &lbl_8008D3A0, &lbl_8008D3B8, &lbl_8008D3B8, &lbl_8008D3B8, &lbl_8008D3AC,
};

void* jtbl_800EE714[] = {
    &lbl_8008D41C, &lbl_8008D5C4, &lbl_8008D5C4, &lbl_8008D5C4, &lbl_8008D5CC, &lbl_8008D5C4, &lbl_8008D5C4,
    &lbl_8008D5C4, &lbl_8008D5CC, &lbl_8008D5C4, &lbl_8008D5C4, &lbl_8008D5C4, &lbl_8008D4C8,
};

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsSetInterrupt.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsResetInterrupt.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/mips/mipsEvent.s")
