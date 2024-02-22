#include "cpu.h"
#include "dolphin.h"
#include "system.h"
#include "xlObject.h"
#include "ram.h"
#include "simGCN.h"

//! TODO: move these to sram.h

// __anon_0x74AB9
typedef struct Sram {
    void* pHost; // 0x0
} Sram;

s32 sramEvent(Sram* pSram, s32 nEvent, void* pArgument);

_XL_OBJECTTYPE gClassSram = {
    "SRAM",
    sizeof(Sram),
    NULL,
    (EventFunc)sramEvent,
};

s32 sramCopySRAM(Sram* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* pTarget;

    if (!ramGetBuffer(((System*)pSRAM->pHost)->apObject[SOT_RAM], &pTarget, nOffsetRAM, &nSize)) {
        return 0;
    }
    if (!simulatorReadSRAM(nOffsetSRAM & 0x7FFF, (u8*)pTarget, nSize)) {
        return 0;
    }
    return 1;
}

s32 sramTransferSRAM(Sram* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* pTarget;

    if (!ramGetBuffer(((System*)pSRAM->pHost)->apObject[SOT_RAM], &pTarget, nOffsetRAM, &nSize)) {
        return 0;
    }
    if (!simulatorWriteSRAM(nOffsetSRAM & 0x7FFF, (u8*)pTarget, nSize)) {
        return 0;
    }
    return 1;
}

static s32 sramPut8(Sram* pObject, u32 nAddress, s8* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s8));
    return 1;
}

static s32 sramPut16(Sram* pObject, u32 nAddress, s16* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s16));
    return 1;
}

static s32 sramPut32(Sram* pObject, u32 nAddress, s32* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s32));
    return 1;
}

static s32 sramPut64(Sram* pObject, u32 nAddress, s64* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s64));
    return 1;
}

static s32 sramGet8(Sram* pObject, u32 nAddress, s8* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s8));
    return 1;
}

static s32 sramGet16(Sram* pObject, u32 nAddress, s16* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s16));
    return 1;
}

static s32 sramGet32(Sram* pObject, u32 nAddress, s32* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s32));
    return 1;
}

static s32 sramGet64(Sram* pObject, u32 nAddress, s64* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s64));
    return 1;
}

s32 sramEvent(Sram* pObject, s32 nEvent, void* pArgument) {
    Sram* pSram = (Sram*)pObject;

    switch (nEvent) {
        case 2:
            pSram->pHost = pArgument;
        case 0:
        case 1:
        case 3:
            break;

        case 0x1002:
            if (!cpuSetDevicePut(((System*)pSram->pHost)->apObject[SOT_CPU], pArgument, (Put8Func)sramPut8,
                                 (Put16Func)sramPut16, (Put32Func)sramPut32, (Put64Func)sramPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(((System*)pSram->pHost)->apObject[SOT_CPU], pArgument, (Get8Func)sramGet8,
                                 (Get16Func)sramGet16, (Get32Func)sramGet32, (Get64Func)sramGet64)) {
                return 0;
            }
        case 0x1003:
            break;

        default:
            return 0;
    }
    return 1;
}
