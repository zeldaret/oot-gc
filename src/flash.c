#include "flash.h"
#include "macros.h"
#include "ram.h"
#include "simGCN.h"
#include "system.h"
#include "xlHeap.h"

_XL_OBJECTTYPE gClassFlash = {
    "FLASH",
    sizeof(Flash),
    NULL,
    (EventFunc)flashEvent,
};

s32 flashCopyFLASH(Flash* pFLASH, s32 nOffsetRAM, s32 nOffsetFLASH, s32 nSize) {
    void* pTarget;

    if (!ramGetBuffer(SYSTEM_RAM(pFLASH->pHost), &pTarget, nOffsetRAM, (u32*)&nSize)) {
        return 0;
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
                return 0;
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

    return 1;
}

// ``nOffsetFLASH`` is assumed based on the function above
s32 flashTransferFLASH(Flash* pFLASH, s32 nOffsetRAM, s32 nOffsetFLASH, s32 nSize) {
    void* pTarget;
    s32 i;

    if (!ramGetBuffer(SYSTEM_RAM(pFLASH->pHost), &pTarget, nOffsetRAM, (u32*)&nSize)) {
        return 0;
    }

    switch (pFLASH->flashCommand & 0xFF000000) {
        case 0xB4000000:
            for (i = 0; i < nSize; i++) {
                pFLASH->flashBuffer[i] = ((char*)(pTarget))[i];
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

    return 1;
}

static s32 flashPut8(Flash* pFLASH, u32 nAddress, s8* pData) { return 1; }

static s32 flashPut16(Flash* pFLASH, u32 nAddress, s16* pData) { return 1; }

static s32 flashPut32(Flash* pFLASH, u32 nAddress, s32* pData) {
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
            if ((pFLASH->flashCommand & 0xFF000000) + 0xC4000000 == 0) {
                for (i = 0; i < 1024; i++) {
                    if (!simulatorWriteFLASH(i << 7, (u8*)buffer, ARRAY_COUNT(buffer))) {
                        return 0;
                    }
                }
            } else {
                if (((pFLASH->flashCommand & 0xFF000000) + 0xB5000000 == 0) &&
                    !simulatorWriteFLASH((pFLASH->flashCommand << 7) & 0x7FFFFF80, (u8*)buffer, ARRAY_COUNT(buffer))) {
                    return 0;
                }
            }
            break;
        case 0xA5000000:
            pFLASH->flashStatus = 0x11118004;
            if (!simulatorWriteFLASH((*pData << 7) & 0x7FFFFF80, (u8*)pFLASH->flashBuffer, 128)) {
                return 0;
            }
            break;
        case 0xF0000000:
            pFLASH->flashStatus = 0x11118004;
            break;
    }

    pFLASH->flashCommand = *pData;
    return 1;
}

static s32 flashPut64(Flash* pFLASH, u32 nAddress, s64* pData) { return 1; }

static s32 flashGet8(Flash* pFLASH, u32 nAddress, s8* pData) { return 1; }

static s32 flashGet16(Flash* pFLASH, u32 nAddress, s16* pData) { return 1; }

static s32 flashGet32(Flash* pFLASH, u32 nAddress, s32* pData) {
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

    return 1;
}

static s32 flashGet64(Flash* pFLASH, u32 nAddress, s64* pData) { return 1; }

s32 flashEvent(Flash* pFLASH, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pFLASH->pHost = pArgument;
            pFLASH->flashCommand = 0;
            xlHeapTake(&pFLASH->flashBuffer, 128);
            break;
        case 3:
            xlHeapFree(&pFLASH->flashBuffer);
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pFLASH->pHost), pArgument, (Put8Func)flashPut8, (Put16Func)flashPut16,
                                 (Put32Func)flashPut32, (Put64Func)flashPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pFLASH->pHost), pArgument, (Get8Func)flashGet8, (Get16Func)flashGet16,
                                 (Get32Func)flashGet32, (Get64Func)flashGet64)) {
                return 0;
            }
        case 0:
        case 1:
        case 0x1003:
            break;
        default:
            return 0;
    }

    return 1;
}
