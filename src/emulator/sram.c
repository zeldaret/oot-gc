#include "emulator/sram.h"
#include "emulator/cpu.h"
#include "emulator/ram.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"

_XL_OBJECTTYPE gClassSram = {
    "SRAM",
    sizeof(Sram),
    NULL,
    (EventFunc)sramEvent,
};

bool sramCopySRAM(Sram* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* pTarget;

    if (!ramGetBuffer(SYSTEM_RAM(pSRAM->pHost), &pTarget, nOffsetRAM, &nSize)) {
        return false;
    }
    if (!simulatorReadSRAM(nOffsetSRAM & 0x7FFF, (u8*)pTarget, nSize)) {
        return false;
    }
    return true;
}

bool sramTransferSRAM(Sram* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* pTarget;

    if (!ramGetBuffer(SYSTEM_RAM(pSRAM->pHost), &pTarget, nOffsetRAM, &nSize)) {
        return false;
    }
    if (!simulatorWriteSRAM(nOffsetSRAM & 0x7FFF, (u8*)pTarget, nSize)) {
        return false;
    }
    return true;
}

static bool sramPut8(Sram* pObject, u32 nAddress, s8* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s8));
    return true;
}

static bool sramPut16(Sram* pObject, u32 nAddress, s16* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s16));
    return true;
}

static bool sramPut32(Sram* pObject, u32 nAddress, s32* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s32));
    return true;
}

static bool sramPut64(Sram* pObject, u32 nAddress, s64* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s64));
    return true;
}

static bool sramGet8(Sram* pObject, u32 nAddress, s8* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s8));
    return true;
}

static bool sramGet16(Sram* pObject, u32 nAddress, s16* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s16));
    return true;
}

static bool sramGet32(Sram* pObject, u32 nAddress, s32* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s32));
    return true;
}

static bool sramGet64(Sram* pObject, u32 nAddress, s64* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (u8*)pData, sizeof(s64));
    return true;
}

bool sramEvent(Sram* pObject, s32 nEvent, void* pArgument) {
    Sram* pSram = (Sram*)pObject;

    switch (nEvent) {
        case 2:
            pSram->pHost = pArgument;
        case 0:
        case 1:
        case 3:
            break;

        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pSram->pHost), pArgument, (Put8Func)sramPut8, (Put16Func)sramPut16,
                                 (Put32Func)sramPut32, (Put64Func)sramPut64)) {
                return false;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pSram->pHost), pArgument, (Get8Func)sramGet8, (Get16Func)sramGet16,
                                 (Get32Func)sramGet32, (Get64Func)sramGet64)) {
                return false;
            }
        case 0x1003:
            break;

        default:
            return false;
    }
    return true;
}
