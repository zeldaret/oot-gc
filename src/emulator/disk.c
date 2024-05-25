#include "emulator/disk.h"
#include "emulator/cpu.h"
#include "emulator/system.h"

_XL_OBJECTTYPE gClassDisk = {
    "DISK",
    sizeof(Disk),
    NULL,
    (EventFunc)diskEvent,
};

bool diskPutROM8(Disk* pDisk, u32 nAddress, s8* pData) { return true; }

bool diskPutROM16(Disk* pDisk, u32 nAddress, s16* pData) { return true; }

bool diskPutROM32(Disk* pDisk, u32 nAddress, s32* pData) { return true; }

bool diskPutROM64(Disk* pDisk, u32 nAddress, s64* pData) { return true; }

bool diskGetROM8(Disk* pDisk, u32 nAddress, s8* pData) {
    *pData = 0;
    return true;
}

bool diskGetROM16(Disk* pDisk, u32 nAddress, s16* pData) {
    *pData = 0;
    return true;
}

bool diskGetROM32(Disk* pDisk, u32 nAddress, s32* pData) {
    *pData = 0;
    return true;
}

bool diskGetROM64(Disk* pDisk, u32 nAddress, s64* pData) {
    *pData = 0;
    return true;
}

bool diskPutDrive8(Disk* pDisk, u32 nAddress, s8* pData) { return true; }

bool diskPutDrive16(Disk* pDisk, u32 nAddress, s16* pData) { return true; }

bool diskPutDrive32(Disk* pDisk, u32 nAddress, s32* pData) {
    nAddress &= 0x00FFFFFF;

    switch (nAddress) {
        case 0x508:
            return false;
        case 0x510:
        default:
            break;
    }

    return true;
}

bool diskPutDrive64(Disk* pDisk, u32 nAddress, s64* pData) { return true; }

bool diskGetDrive8(Disk* pDisk, u32 nAddress, s8* pData) { return true; }

bool diskGetDrive16(Disk* pDisk, u32 nAddress, s16* pData) { return true; }

bool diskGetDrive32(Disk* pDisk, u32 nAddress, s32* pData) {
    nAddress &= 0x00FFFFFF;

    switch (nAddress) {
        case 0x508:
            *pData = 0;
            break;
        case 0x510:
            return false;
        default:
            break;
    }

    return true;
}

bool diskGetDrive64(Disk* pDisk, u32 nAddress, s64* pData) { return true; }

bool diskEvent(Disk* pDisk, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pDisk->pHost = pArgument;
            break;
        case 0x1002:
            switch (((CpuDevice*)pArgument)->nType) {
                case 0:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pDisk->pHost), pArgument, (Put8Func)diskPutDrive8,
                                         (Put16Func)diskPutDrive16, (Put32Func)diskPutDrive32,
                                         (Put64Func)diskPutDrive64)) {
                        return false;
                    }

                    if (!cpuSetDeviceGet(SYSTEM_CPU(pDisk->pHost), pArgument, (Get8Func)diskGetDrive8,
                                         (Get16Func)diskGetDrive16, (Get32Func)diskGetDrive32,
                                         (Get64Func)diskGetDrive64)) {
                        return false;
                    }
                    break;
                case 1:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pDisk->pHost), pArgument, (Put8Func)diskPutROM8,
                                         (Put16Func)diskPutROM16, (Put32Func)diskPutROM32, (Put64Func)diskPutROM64)) {
                        return false;
                    }

                    if (!cpuSetDeviceGet(SYSTEM_CPU(pDisk->pHost), pArgument, (Get8Func)diskGetROM8,
                                         (Get16Func)diskGetROM16, (Get32Func)diskGetROM32, (Get64Func)diskGetROM64)) {
                        return false;
                    }
                    break;
            }
            break;
        case 0:
        case 1:
        case 3:
            break;
#if VERSION != MQ_J
        case 0x1003:
            break;
#endif
        default:
            return false;
    }

    return true;
}
