#include "emulator/serial.h"
#include "emulator/cpu.h"
#include "emulator/pif.h"
#include "emulator/ram.h"
#include "emulator/system.h"

_XL_OBJECTTYPE gClassSerial = {
    "SERIAL",
    sizeof(Serial),
    NULL,
    (EventFunc)serialEvent,
};

bool serialPut8(Serial* pSerial, u32 nAddress, s8* pData) { return false; }

bool serialPut16(Serial* pSerial, u32 nAddress, s16* pData) { return false; }

bool serialPut32(Serial* pSerial, u32 nAddress, s32* pData) {
    u32 nSize;
    void* aData;

    nAddress &= 0x1F;

    switch (nAddress) {
        case 0x00:
            pSerial->nAddress = *pData;
            break;
        case 0x04:
            nSize = 0x40;

            if (!ramGetBuffer(SYSTEM_RAM(pSerial->pHost), &aData, pSerial->nAddress, &nSize)) {
                return false;
            }

            if (!pifGetData(SYSTEM_PIF(pSerial->pHost), aData)) {
                return false;
            }

            xlObjectEvent(pSerial->pHost, 0x1000, (void*)6);
            break;
        case 0x10:
            nSize = 0x40;

            if (!ramGetBuffer(SYSTEM_RAM(pSerial->pHost), &aData, pSerial->nAddress, &nSize)) {
                return false;
            }

            if (!pifSetData(SYSTEM_PIF(pSerial->pHost), aData)) {
                return false;
            }

            xlObjectEvent(pSerial->pHost, 0x1000, (void*)6);
            break;
        case 0x18:
            xlObjectEvent(pSerial->pHost, 0x1001, (void*)6);
            break;
        default:
            return false;
    }

    return true;
}

bool serialPut64(Serial* pSerial, u32 nAddress, s64* pData) { return false; }

bool serialGet8(Serial* pSerial, u32 nAddress, s8* pData) { return false; }

bool serialGet16(Serial* pSerial, u32 nAddress, s16* pData) { return false; }

bool serialGet32(Serial* pSerial, u32 nAddress, s32* pData) {
    nAddress &= 0x1F;

    switch (nAddress) {
        case 0x00:
            *pData = pSerial->nAddress;
            break;
        case 0x04:
            *pData = 0;
            break;
        case 0x10:
            *pData = 0;
            break;
        case 0x18:
            *pData = 0;
            break;
        default:
            return false;
    }

    return true;
}

bool serialGet64(Serial* pSerial, u32 nAddress, s64* pData) { return false; }

bool serialEvent(Serial* pSerial, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pSerial->pHost = pArgument;
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pSerial->pHost), pArgument, (Put8Func)serialPut8, (Put16Func)serialPut16,
                                 (Put32Func)serialPut32, (Put64Func)serialPut64)) {
                return false;
            }

            if (!cpuSetDeviceGet(SYSTEM_CPU(pSerial->pHost), pArgument, (Get8Func)serialGet8, (Get16Func)serialGet16,
                                 (Get32Func)serialGet32, (Get64Func)serialGet64)) {
                return false;
            }
            break;
        case 0:
        case 1:
        case 3:
#if VERSION != MQ_J
        case 0x1003:
#endif
            break;
        default:
            return false;
    }

    return true;
}
