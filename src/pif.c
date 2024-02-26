#include "pif.h"

_XL_OBJECTTYPE gClassPIF = {
    "PIF",
    sizeof(Pif),
    NULL,
    (EventFunc)pifEvent,
};

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifReadRumble.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifWriteRumble.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifContDataCrc.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifSetControllerType.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifGetEControllerType.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifSetEEPROMType.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifGetEEPROMSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifExecuteCommand.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifProcessInputData.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifProcessOutputData.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifSetData.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifGetData.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifEvent.s")
