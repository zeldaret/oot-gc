#include "peripheral.h"
#include "cpu.h"
#include "flash.h"
#include "simGCN.h"
#include "sram.h"
#include "system.h"
#include "xlObject.h"

_XL_OBJECTTYPE gClassPeripheral = {
    "PERIPHERAL",
    sizeof(Peripheral),
    NULL,
    (EventFunc)peripheralEvent,
};

s32 peripheralDMA_Complete(void) {
    Peripheral* pPeripheral = SYSTEM_PERIPHERAL(gpSystem);

    pPeripheral->nStatus &= 0xFFFFFFFC;
    xlObjectEvent(pPeripheral->pHost, 0x1000, (void*)9);
    return 1;
}

s32 peripheralPut8(Peripheral* pPeripheral, u32 nAddress, s8* pData) { return 0; }

s32 peripheralPut16(Peripheral* pPeripheral, u32 nAddress, s16* pData) { return 0; }

s32 peripheralPut32(Peripheral* pPeripheral, u32 nAddress, s32* pData) {
    s32 bFlag = 1;
    SystemObjectType storageDevice;
    s32 nAddressROM;

    switch (nAddress & 0x3F) {
        case 0x00:
            pPeripheral->nAddressRAM = *pData & 0xFFFFFF;
            break;
        case 0x04:
            pPeripheral->nAddressROM = *pData;
            break;
        case 0x08:
            pPeripheral->nSizeGet = *pData & 0xFFFFFF;
            nAddressROM = pPeripheral->nAddressROM;
            if (!(0x05000000 <= nAddressROM && nAddressROM <= 0x05FFFFFF) &&
                !(0x06000000 <= nAddressROM && nAddressROM <= 0x07FFFFFF)) {
                if (0x08000000 <= nAddressROM && nAddressROM <= 0x0FFFFFFF) {
                    if (!systemGetStorageDevice((System*)pPeripheral->pHost, &storageDevice)) {
                        return 0;
                    }
                    if (storageDevice == SOT_SRAM) {
                        if (!sramTransferSRAM(SYSTEM_SRAM(pPeripheral->pHost), pPeripheral->nAddressRAM,
                                              pPeripheral->nAddressROM, pPeripheral->nSizeGet + 1)) {
                            return 0;
                        }
                    } else if (storageDevice == SOT_FLASH) {
                        if (!flashTransferFLASH(SYSTEM_FLASH(pPeripheral->pHost), pPeripheral->nAddressRAM,
                                                pPeripheral->nAddressROM, pPeripheral->nSizeGet + 1)) {
                            return 0;
                        }
                    }
                }
            }
            xlObjectEvent(pPeripheral->pHost, 0x1000, (void*)9);
            break;
        case 0x0C:
            pPeripheral->nSizePut = *pData & 0xFFFFFF;
            nAddressROM = pPeripheral->nAddressROM;
            if (!(0x05000000 <= nAddressROM && nAddressROM <= 0x05FFFFFF) &&
                !(0x06000000 <= nAddressROM && nAddressROM <= 0x07FFFFFF)) {
                if (0x08000000 <= nAddressROM && nAddressROM <= 0x0FFFFFFF) {
                    if (!systemGetStorageDevice((System*)pPeripheral->pHost, &storageDevice)) {
                        return 0;
                    }
                    if (storageDevice == SOT_SRAM) {
                        if (!sramCopySRAM(SYSTEM_SRAM(pPeripheral->pHost), pPeripheral->nAddressRAM,
                                          pPeripheral->nAddressROM, pPeripheral->nSizePut + 1)) {
                            return 0;
                        }
                    } else if (storageDevice == SOT_FLASH) {
                        if (!flashCopyFLASH(SYSTEM_FLASH(pPeripheral->pHost), pPeripheral->nAddressRAM,
                                            pPeripheral->nAddressROM, pPeripheral->nSizePut + 1)) {
                            return 0;
                        }
                    }
                } else if (0x10000000 <= nAddressROM && nAddressROM <= 0x1FBFFFFF) {
                    pPeripheral->nStatus |= 3;
                    bFlag = 0;
                    if (systemCopyROM((System*)pPeripheral->pHost, pPeripheral->nAddressRAM, pPeripheral->nAddressROM,
                                      pPeripheral->nSizePut + 1, &peripheralDMA_Complete) == 0) {
                        return 0;
                    }
                }
            }
            if (bFlag) {
                xlObjectEvent(pPeripheral->pHost, 0x1000, (void*)9);
            }
            break;
        case 0x10:
            if (*pData & 2) {
                xlObjectEvent(pPeripheral->pHost, 0x1001, (void*)9);
            }
            break;
        case 0x14:
            pPeripheral->nLatency1 = *pData & 0xFF;
            break;
        case 0x18:
            pPeripheral->nWidthPulse1 = *pData & 0xFF;
            break;
        case 0x1C:
            pPeripheral->nSizePage1 = *pData & 0xF;
            break;
        case 0x20:
            pPeripheral->nRelease1 = *pData & 1;
            break;
        case 0x24:
            pPeripheral->nLatency2 = *pData & 0xFF;
            break;
        case 0x28:
            pPeripheral->nWidthPulse2 = *pData & 0xFF;
            break;
        case 0x2C:
            pPeripheral->nSizePage2 = *pData & 0xF;
            break;
        case 0x30:
            pPeripheral->nRelease2 = *pData & 1;
            break;
        default:
            return 0;
    }

    return 1;
}

s32 peripheralPut64(Peripheral* pPeripheral, u32 nAddress, s64* pData) { return 0; }

s32 peripheralGet8(Peripheral* pPeripheral, u32 nAddress, s8* pData) { return 0; }

s32 peripheralGet16(Peripheral* pPeripheral, u32 nAddress, s16* pData) { return 0; }

s32 peripheralGet32(Peripheral* pPeripheral, u32 nAddress, s32* pData) {
    switch (nAddress & 0x3F) {
        case 0x00:
            *pData = pPeripheral->nAddressRAM & 0xFFFFFF;
            break;
        case 0x04:
            *pData = pPeripheral->nAddressROM;
            break;
        case 0x08:
            *pData = pPeripheral->nSizeGet & 0xFFFFFF;
            break;
        case 0x0C:
            *pData = pPeripheral->nSizePut & 0xFFFFFF;
            break;
        case 0x10:
            *pData = pPeripheral->nStatus & 7;
            break;
        case 0x14:
            *pData = pPeripheral->nLatency1 & 0xFF;
            break;
        case 0x18:
            *pData = pPeripheral->nWidthPulse1 & 0xFF;
            break;
        case 0x1C:
            *pData = pPeripheral->nSizePage1 & 0xF;
            break;
        case 0x20:
            *pData = pPeripheral->nRelease1 & 1;
            break;
        case 0x24:
            *pData = pPeripheral->nLatency2 & 0xFF;
            break;
        case 0x28:
            *pData = pPeripheral->nWidthPulse2 & 0xFF;
            break;
        case 0x2C:
            *pData = pPeripheral->nSizePage2 & 0xF;
            break;
        case 0x30:
            *pData = pPeripheral->nRelease2 & 1;
            break;
        default:
            return 0;
    }

    return 1;
}

s32 peripheralGet64(Peripheral* pPeripheral, u32 nAddress, s64* pData) { return 0; }

s32 peripheralEvent(Peripheral* pPeripheral, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pPeripheral->nStatus = 0;
            pPeripheral->pHost = pArgument;
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pPeripheral->pHost), pArgument, (Put8Func)&peripheralPut8,
                                 (Put16Func)&peripheralPut16, (Put32Func)&peripheralPut32,
                                 (Put64Func)&peripheralPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pPeripheral->pHost), pArgument, (Get8Func)&peripheralGet8,
                                 (Get16Func)&peripheralGet16, (Get32Func)&peripheralGet32,
                                 (Get64Func)&peripheralGet64)) {
                return 0;
            }
            break;
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
