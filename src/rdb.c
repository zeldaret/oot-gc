#include "rdb.h"
#include "rdb_jumptables.h"

_XL_OBJECTTYPE gClassRdb = {
    "RDB",
    sizeof(Rdb),
    NULL,
    (EventFunc)rdbEvent,
};

void* jtbl_800EE1C0[] = {
    &lbl_8007178C, &lbl_80071794, &lbl_80071AC8, &lbl_80071AD0, &lbl_80071AD8, &lbl_80071AE0,
    &lbl_80071AE8, &lbl_80071AF0, &lbl_80071AF8, &lbl_80071B00, &lbl_80071B08, &lbl_80071B10,
    &lbl_80071B18, &lbl_80071B28, &lbl_80071B30, &lbl_80071B38, &lbl_80071B40, &lbl_80071B48,
    &lbl_80071B50, &lbl_80071B58, &lbl_80071B60, &lbl_80071B68, &lbl_80071B20,
};

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbEvent.s")
