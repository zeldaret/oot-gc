#include "rdb.h"
#include "rdb_jumptables.h"
#include "system.h"

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

static s32 rdbPut8(Rdb* pRDB, u32 nAddress, s8* pData) { return 0; }

static s32 rdbPut16(Rdb* pRDB, u32 nAddress, s16* pData) { return 0; }

//! TODO: remove when the function is decompiled
static s32 rdbPut32(Rdb* pRDB, u32 nAddress, s32* pData);
#pragma GLOBAL_ASM("asm/non_matchings/rdb/rdbPut32.s")

static s32 rdbPut64(Rdb* pRDB, u32 nAddress, s64* pData) { return 0; }

static s32 rdbGet8(Rdb* pRDB, u32 nAddress, s8* pData) { return 0; }

static s32 rdbGet16(Rdb* pRDB, u32 nAddress, s16* pData) { return 0; }

static s32 rdbGet32(Rdb* pRDB, u32 nAddress, s32* pData) {
    switch (nAddress & 0xF) {
        case 0x0:
        case 0x8:
        case 0xC:
            break;
        default:
            return 0;
    }

    return 1;
}

static s32 rdbGet64(Rdb* pRDB, u32 nAddress, s64* pData) { return 0; }

s32 rdbEvent(Rdb* pRDB, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pRDB->pHost = pArgument;
            pRDB->nIndexString = 0;
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pRDB->pHost), pArgument, (Put8Func)rdbPut8, (Put16Func)rdbPut16,
                                 (Put32Func)rdbPut32, (Put64Func)rdbPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pRDB->pHost), pArgument, (Get8Func)rdbGet8, (Get16Func)rdbGet16,
                                 (Get32Func)rdbGet32, (Get64Func)rdbGet64)) {
                return 0;
            }
        case 0:
        case 1:
        case 3:
        case 0x1003:
            break;
        default:
            return 0;
    }

    return 1;
}
