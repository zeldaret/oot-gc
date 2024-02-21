#include "disk.h"
#include "cpu.h"
#include "system.h"
#include "xlObject.h"

_XL_OBJECTTYPE gClassDisk = {
    "DISK",
    sizeof(Disk),
    NULL,
    (EventFunc)diskEvent,
};

s32 diskPutROM8(Disk* pDisk, u32 nAddress, s8* pData) { return 1; }

s32 diskPutROM16(Disk* pDisk, u32 nAddress, s16* pData) { return 1; }

s32 diskPutROM32(Disk* pDisk, u32 nAddress, s32* pData) { return 1; }

s32 diskPutROM64(Disk* pDisk, u32 nAddress, s64* pData) { return 1; }

s32 diskGetROM8(Disk* pDisk, u32 nAddress, s8* pData) {
    *pData = 0;
    return 1;
}

s32 diskGetROM16(Disk* pDisk, u32 nAddress, s16* pData) {
    *pData = 0;
    return 1;
}

s32 diskGetROM32(Disk* pDisk, u32 nAddress, s32* pData) {
    *pData = 0;
    return 1;
}

s32 diskGetROM64(Disk* pDisk, u32 nAddress, s64* pData) {
    *pData = 0;
    return 1;
}

s32 diskPutDrive8(Disk* pDisk, u32 nAddress, s8* pData) { return 1; }

s32 diskPutDrive16(Disk* pDisk, u32 nAddress, s16* pData) { return 1; }

s32 diskPutDrive32(Disk* pDisk, u32 nAddress, s32* pData) {
    nAddress &= 0x00FFFFFF;

    switch (nAddress) {
        case 0x508:
            return 0;
        case 0x510:
        default:
            break;
    }

    return 1;
}

s32 diskPutDrive64(Disk* pDisk, u32 nAddress, s64* pData) { return 1; }

s32 diskGetDrive8(Disk* pDisk, u32 nAddress, s8* pData) { return 1; }

s32 diskGetDrive16(Disk* pDisk, u32 nAddress, s16* pData) { return 1; }

s32 diskGetDrive32(Disk* pDisk, u32 nAddress, s32* pData) {
    nAddress &= 0x00FFFFFF;

    switch (nAddress) {
        case 0x508:
            *pData = 0;
            break;
        case 0x510:
            return 0;
        default:
            break;
    }

    return 1;
}

s32 diskGetDrive64(Disk* pDisk, u32 nAddress, s64* pData) { return 1; }

s32 diskEvent(Disk* pDisk, s32 nEvent, void* pArgument) {
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
                        return 0;
                    }

                    if (!cpuSetDeviceGet(SYSTEM_CPU(pDisk->pHost), pArgument, (Get8Func)diskGetDrive8,
                                         (Get16Func)diskGetDrive16, (Get32Func)diskGetDrive32,
                                         (Get64Func)diskGetDrive64)) {
                        return 0;
                    }
                    break;
                case 1:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pDisk->pHost), pArgument, (Put8Func)diskPutROM8,
                                         (Put16Func)diskPutROM16, (Put32Func)diskPutROM32, (Put64Func)diskPutROM64)) {
                        return 0;
                    }

                    if (!cpuSetDeviceGet(SYSTEM_CPU(pDisk->pHost), pArgument, (Get8Func)diskGetROM8,
                                         (Get16Func)diskGetROM16, (Get32Func)diskGetROM32, (Get64Func)diskGetROM64)) {
                        return 0;
                    }
                    break;
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
