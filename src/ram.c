#include "ram.h"
#include "cpu.h"
#include "system.h"
#include "xlObject.h"

s32 ramEvent(Ram* pRAM, s32 nEvent, void* pArgument);

_XL_OBJECTTYPE gClassRAM = {
    "RAM",
    sizeof(Ram),
    NULL,
    (EventFunc)ramEvent,
};

static s32 ramPutControl8(Ram* pRAM, u32 nAddress, s8* pData) { return 0; }

static s32 ramPutControl16(Ram* pRAM, u32 nAddress, s32* pData) { return 0; }

static s32 ramPutControl32(Ram* pRAM, u32 nAddress, s16* pData) {
    nAddress &= 0x3F;

    switch (nAddress) {
        default:
            return 0;
        case 0x00:
        case 0x04:
        case 0x08:
        case 0x0C:
        case 0x10:
        case 0x14:
        case 0x18:
        case 0x1C:
        case 0x20:
        case 0x24:
            return 1;
    }
}

static s32 ramPutControl64(Ram* pRAM, u32 nAddress, s64* pData) { return 0; }

static s32 ramGetControl8(Ram* pRAM, u32 nAddress, s8* pData) { return 0; }

static s32 ramGetControl16(Ram* pRAM, u32 nAddress, s32* pData) { return 0; }

static s32 ramGetControl32(Ram* pRAM, u32 nAddress, s16* pData) {
    nAddress &= 0x3F;

    switch (nAddress) {
        default:
            return 0;
        case 0x00:
        case 0x04:
        case 0x08:
        case 0x0C:
        case 0x10:
        case 0x14:
        case 0x18:
        case 0x1C:
        case 0x20:
        case 0x24:
            return 1;
    }
}

static s32 ramGetControl64(Ram* pRAM, u32 nAddress, s64* pData) { return 0; }

static s32 ramPutRI8(Ram* pRAM, u32 nAddress, s8* pData) { return 0; }

static s32 ramPutRI16(Ram* pRAM, u32 nAddress, s32* pData) { return 0; }

static s32 ramPutRI32(Ram* pRAM, u32 nAddress, s16* pData) {
    nAddress &= 0x1F;

    switch (nAddress) {
        default:
            return 0;
        case 0x00:
        case 0x04:
        case 0x08:
        case 0x0C:
        case 0x10:
        case 0x14:
        case 0x18:
        case 0x1C:
            return 1;
    }
}

static s32 ramPutRI64(Ram* pRAM, u32 nAddress, s64* pData) { return 0; }

static s32 ramGetRI8(Ram* pRAM, u32 nAddress, s8* pData) { return 0; }

static s32 ramGetRI16(Ram* pRAM, u32 nAddress, s32* pData) { return 0; }

static s32 ramGetRI32(Ram* pRAM, u32 nAddress, s16* pData) {
    nAddress &= 0x1F;

    switch (nAddress) {
        default:
            return 0;
        case 0x00:
        case 0x04:
        case 0x08:
        case 0x0C:
        case 0x10:
        case 0x14:
        case 0x18:
        case 0x1C:
            return 1;
    }
}

static s32 ramGetRI64(Ram* pRAM, u32 nAddress, s64* pData) { return 0; }

static s32 ramPut8(Ram* pRAM, u32 nAddress, s8* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *((s8*)pRAM->pBuffer + nAddress) = *pData;
    }

    return 1;
}

static s32 ramPut16(Ram* pRAM, u32 nAddress, s16* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *((u16*)pRAM->pBuffer + (nAddress >> 1)) = *pData;
    }

    return 1;
}

static s32 ramPut32(Ram* pRAM, u32 nAddress, s32* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *((s32*)pRAM->pBuffer + (nAddress >> 2)) = *pData;
    }

    return 1;
}

static s32 ramPut64(Ram* pRAM, u32 nAddress, s64* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *((s64*)pRAM->pBuffer + (nAddress >> 3)) = *pData;
    }

    return 1;
}

static s32 ramGet8(Ram* pRAM, u32 nAddress, s8* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *pData = *((s8*)pRAM->pBuffer + nAddress);
    } else {
        *pData = 0;
    }

    return 1;
}

static s32 ramGet16(Ram* pRAM, u32 nAddress, s16* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *pData = *((s16*)pRAM->pBuffer + (nAddress >> 1));
    } else {
        *pData = 0;
    }

    return 1;
}

static s32 ramGet32(Ram* pRAM, u32 nAddress, s32* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *pData = *((s32*)pRAM->pBuffer + (nAddress >> 2));
    } else {
        *pData = 0;
    }

    return 1;
}

static s32 ramGet64(Ram* pRAM, u32 nAddress, s64* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *pData = *((s64*)pRAM->pBuffer + (nAddress >> 3));
    } else {
        *pData = 0;
    }

    return 1;
}

s32 ramGetBuffer(Ram* pRAM, void** ppRAM, u32 nOffset, u32* pnSize) {
    s32 nSize;

    nOffset &= 0x03FFFFFF;

    if (pRAM->nSize == 0) {
        return 0;
    }

    if ((pnSize != NULL) && ((u32)(nOffset + *pnSize) >= pRAM->nSize)) {
        nSize = pRAM->nSize - nOffset;
        *pnSize = nSize;

        if (nSize < 0) {
            *pnSize = 0;
        }
    }

    *((u8**)ppRAM) = (u8*)pRAM->pBuffer + nOffset;
    return 1;
}

s32 ramWipe(Ram* pRAM) {
    if (pRAM->nSize != 0 && !xlHeapFill32(pRAM->pBuffer, pRAM->nSize, 0)) {
        return 0;
    }

    return 1;
}

s32 ramSetSize(Ram* pRAM, s32 nSize) {
    s32 nSizeRAM;

    if (pRAM->pBuffer != NULL) {
        return 0;
    }

    nSizeRAM = (nSize + 0x3FF) & 0xFFFFFC00;

    if (!xlHeapTake(&pRAM->pBuffer, nSizeRAM | 0x30000000)) {
        return 0;
    }

    pRAM->nSize = nSizeRAM;

    return 1;
}

s32 ramGetSize(Ram* pRAM, s32* nSize) {
    if (nSize != NULL) {
        *nSize = pRAM->nSize;
    }

    return 1;
}

s32 ramEvent(Ram* pRAM, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pRAM->nSize = 0;
            pRAM->pBuffer = NULL;
            pRAM->pHost = pArgument;
            break;
        case 0x1002:
            switch (((CpuDevice*)pArgument)->nType & 0xFF) {
                case 0:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pRAM->pHost), pArgument, (Put8Func)ramPut8, (Put16Func)ramPut16,
                                         (Put32Func)ramPut32, (Put64Func)ramPut64)) {
                        return 0;
                    }

                    if (!cpuSetDeviceGet(SYSTEM_CPU(pRAM->pHost), pArgument, (Get8Func)ramGet8, (Get16Func)ramGet16,
                                         (Get32Func)ramGet32, (Get64Func)ramGet64)) {
                        return 0;
                    }
                    break;
                case 1:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pRAM->pHost), pArgument, (Put8Func)ramPutRI8, (Put16Func)ramPutRI16,
                                         (Put32Func)ramPutRI32, (Put64Func)ramPutRI64)) {
                        return 0;
                    }

                    if (!cpuSetDeviceGet(SYSTEM_CPU(pRAM->pHost), pArgument, (Get8Func)ramGetRI8, (Get16Func)ramGetRI16,
                                         (Get32Func)ramGetRI32, (Get64Func)ramGetRI64)) {
                        return 0;
                    }
                    break;
                case 2:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pRAM->pHost), pArgument, (Put8Func)ramPutControl8,
                                         (Put16Func)ramPutControl16, (Put32Func)ramPutControl32,
                                         (Put64Func)ramPutControl64)) {
                        return 0;
                    }

                    if (!cpuSetDeviceGet(SYSTEM_CPU(pRAM->pHost), pArgument, (Get8Func)ramGetControl8,
                                         (Get16Func)ramGetControl16, (Get32Func)ramGetControl32,
                                         (Get64Func)ramGetControl64)) {
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
