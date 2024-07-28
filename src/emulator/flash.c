#include "emulator/flash.h"
#include "emulator/ram.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlHeap.h"
#include "macros.h"

_XL_OBJECTTYPE gClassFlash = {
    "FLASH",
    sizeof(Flash),
    NULL,
    (EventFunc)flashEvent,
};

bool flashCopyFLASH(Flash* pFLASH, s32 nOffsetRAM, s32 nOffsetFLASH, s32 nSize) {
    void* pTarget;

    if (!ramGetBuffer(SYSTEM_RAM(pFLASH->pHost), &pTarget, nOffsetRAM, (u32*)&nSize)) {
        return false;
    }

    // ``((s32*)pTarget)[0]`` fake?
    ((s32*)pTarget)[0] = pFLASH->flashStatus;
    switch (pFLASH->flashCommand & 0xFF000000) {
        case 0xE1000000:
            ((s32*)pTarget)[0] = pFLASH->flashStatus;
            ((s32*)pTarget)[1] = 0xC2001E;
            break;
        case 0xF0000000:
            if (!simulatorReadFLASH((nOffsetFLASH * 2) & 0x01FFFFFE, pTarget, nSize)) {
                return false;
            }
            break;
        case 0x0:
        case 0x3C000000:
        case 0x4B000000:
        case 0x78000000:
        case 0xA5000000:
        case 0xB4000000:
        case 0xD2000000:
        default:
            break;
    }

    return true;
}

// ``nOffsetFLASH`` is assumed based on the function above
bool flashTransferFLASH(Flash* pFLASH, s32 nOffsetRAM, s32 nOffsetFLASH, s32 nSize) {
    void* pTarget;
    s32 i;

    if (!ramGetBuffer(SYSTEM_RAM(pFLASH->pHost), &pTarget, nOffsetRAM, (u32*)&nSize)) {
        return false;
    }

    switch (pFLASH->flashCommand & 0xFF000000) {
        case 0xB4000000:
            for (i = 0; i < nSize; i++) {
                pFLASH->flashBuffer[i] = ((char*)pTarget)[i];
            }
            break;
        case 0x0:
        case 0x3C000000:
        case 0x4B000000:
        case 0x78000000:
        case 0xA5000000:
        case 0xD2000000:
        case 0xE1000000:
        case 0xF0000000:
        default:
            break;
    }

    return true;
}

static bool flashPut8(Flash* pFLASH, u32 nAddress, s8* pData) { return true; }

static bool flashPut16(Flash* pFLASH, u32 nAddress, s16* pData) { return true; }

static bool flashPut32(Flash* pFLASH, u32 nAddress, s32* pData) {
    s32 i;
    char buffer[128];

    switch (*pData & 0xFF000000) {
        case 0xE1000000:
            pFLASH->flashStatus = 0x11118001;
            break;
        case 0x0:
        case 0xB4000000:
        case 0x3C000000:
        case 0x4B000000:
        case 0xD2000000:
        default:
            break;
        case 0x78000000:
            pFLASH->flashStatus = 0x11118008;
            for (i = 0; i < ARRAY_COUNT(buffer); i++) {
                buffer[i] = 0;
            }
            if ((pFLASH->flashCommand & 0xFF000000) == 0x3C000000) {
                for (i = 0; i < 1024; i++) {
                    if (!simulatorWriteFLASH(i << 7, (u8*)buffer, ARRAY_COUNT(buffer))) {
                        return false;
                    }
                }
            } else {
                if ((pFLASH->flashCommand & 0xFF000000) == 0x4B000000) {
                    if (!simulatorWriteFLASH((pFLASH->flashCommand << 7) & 0x7FFFFF80, (u8*)buffer,
                                             ARRAY_COUNT(buffer))) {
                        return false;
                    }
                }
            }
            break;
        case 0xA5000000:
            pFLASH->flashStatus = 0x11118004;
            if (!simulatorWriteFLASH((*pData << 7) & 0x7FFFFF80, (u8*)pFLASH->flashBuffer, 128)) {
                return false;
            }
            break;
        case 0xF0000000:
            pFLASH->flashStatus = 0x11118004;
            break;
    }

    pFLASH->flashCommand = *pData;
    return true;
}

static bool flashPut64(Flash* pFLASH, u32 nAddress, s64* pData) { return true; }

static bool flashGet8(Flash* pFLASH, u32 nAddress, s8* pData) { return true; }

static bool flashGet16(Flash* pFLASH, u32 nAddress, s16* pData) { return true; }

static bool flashGet32(Flash* pFLASH, u32 nAddress, s32* pData) {
    switch (pFLASH->flashCommand & 0xFF000000) {
        case 0x0:
        case 0x3C000000:
        case 0x4B000000:
        case 0x78000000:
        case 0xA5000000:
        case 0xB4000000:
        case 0xD2000000:
        case 0xE1000000:
        case 0xF0000000:
            *pData = pFLASH->flashStatus;
            break;
        default:
            break;
    }

    return true;
}

static bool flashGet64(Flash* pFLASH, u32 nAddress, s64* pData) { return true; }

bool flashEvent(Flash* pFLASH, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pFLASH->pHost = pArgument;
            pFLASH->flashCommand = 0;
            xlHeapTake((void**)&pFLASH->flashBuffer, 128);
            break;
        case 3:
            xlHeapFree((void**)&pFLASH->flashBuffer);
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pFLASH->pHost), pArgument, (Put8Func)flashPut8, (Put16Func)flashPut16,
                                 (Put32Func)flashPut32, (Put64Func)flashPut64)) {
                return false;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pFLASH->pHost), pArgument, (Get8Func)flashGet8, (Get16Func)flashGet16,
                                 (Get32Func)flashGet32, (Get64Func)flashGet64)) {
                return false;
            }
        case 0:
        case 1:
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
