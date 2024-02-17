#include "xlObject.h"
#include "ram.h"

s32 ramEvent(void* pObject, s32 nEvent, void* pArgument);

static s32 ramGet64(Ram* pRAM, u32 nAddress, s64* pData);
static s32 ramGet32(Ram* pRAM, u32 nAddress, s32* pData);
static s32 ramGet16(Ram* pRAM, u32 nAddress, s16* pData);
static s32 ramGet8(Ram* pRAM, u32 nAddress, s8* pData);

static s32 ramPut64(Ram* pRAM, u32 nAddress, s64* pData);
static s32 ramPut32(Ram* pRAM, u32 nAddress, s32* pData);
static s32 ramPut16(Ram* pRAM, u32 nAddress, s16* pData);
static s32 ramPut8(Ram* pRAM, u32 nAddress, s8* pData);

static s32 ramGetRI64(Ram* pRAM, u32 nAddress, s64* pData);
static s32 ramGetRI16(Ram* pRAM, u32 nAddress, s32* pData);
static s32 ramGetRI32(Ram* pRAM, u32 nAddress, s16* pData);
static s32 ramGetRI8(Ram* pRAM, u32 nAddress, s8* pData);

static s32 ramPutRI64(Ram* pRAM, u32 nAddress, s64* pData);
static s32 ramPutRI16(Ram* pRAM, u32 nAddress, s32* pData);
static s32 ramPutRI32(Ram* pRAM, u32 nAddress, s16* pData);
static s32 ramPutRI8(Ram* pRAM, u32 nAddress, s8* pData);

static s32 ramGetControl64(Ram* pRAM, u32 nAddress, s64* pData);
static s32 ramGetControl16(Ram* pRAM, u32 nAddress, s32* pData);
static s32 ramGetControl32(Ram* pRAM, u32 nAddress, s16* pData);
static s32 ramGetControl8(Ram* pRAM, u32 nAddress, s8* pData);

static s32 ramPutControl64(Ram* pRAM, u32 nAddress, s64* pData);
static s32 ramPutControl16(Ram* pRAM, u32 nAddress, s32* pData);
static s32 ramPutControl32(Ram* pRAM, u32 nAddress, s16* pData);
static s32 ramPutControl8(Ram* pRAM, u32 nAddress, s8* pData);

_XL_OBJECTTYPE gClassRAM = {
    "RAM",
    sizeof(Ram),
    NULL,
    (EventFunc)ramEvent,
};

//! TODO: proper fix
typedef struct UnknownDeviceStruct {
    /* 0x00 */ int unk;
    /* 0x04 */ char unk2[0x20];
    /* 0x24 */ struct __anon_0x3EB4F* pDevice;
} UnknownDeviceStruct;

s32 ramEvent(void* pObject, s32 nEvent, void* pArgument) {
    Ram* pRAM = (Ram*)pObject;

    switch (nEvent) {
        case 2:
            pRAM->nSize = 0;
            pRAM->pBuffer = NULL;
            pRAM->pHost = pArgument;
            break;
        case 0x1002:
            switch (((UnknownDeviceStruct*)pArgument)->unk & 0xFF) {
                case 0:
                    if (!cpuSetDevicePut(((UnknownDeviceStruct*)pRAM->pHost)->pDevice, pArgument, ramPut8, ramPut16,
                                         ramPut32, ramPut64)) {
                        return 0;
                    }

                    if (!cpuSetDeviceGet(((UnknownDeviceStruct*)pRAM->pHost)->pDevice, pArgument, ramGet8, ramGet16,
                                         ramGet32, ramGet64)) {
                        return 0;
                    }
                    break;
                case 1:
                    if (!cpuSetDevicePut(((UnknownDeviceStruct*)pRAM->pHost)->pDevice, pArgument, ramPutRI8, ramPutRI16,
                                         ramPutRI32, ramPutRI64)) {
                        return 0;
                    }

                    if (!cpuSetDeviceGet(((UnknownDeviceStruct*)pRAM->pHost)->pDevice, pArgument, ramGetRI8, ramGetRI16,
                                         ramGetRI32, ramGetRI64)) {
                        return 0;
                    }
                    break;
                case 2:
                    if (!cpuSetDevicePut(((UnknownDeviceStruct*)pRAM->pHost)->pDevice, pArgument, ramPutControl8,
                                         ramPutControl16, ramPutControl32, ramPutControl64)) {
                        return 0;
                    }

                    if (!cpuSetDeviceGet(((UnknownDeviceStruct*)pRAM->pHost)->pDevice, pArgument, ramGetControl8,
                                         ramGetControl16, ramGetControl32, ramGetControl64)) {
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

s32 ramGetSize(Ram* pRAM, s32* nSize) {
    if (nSize != NULL) {
        *nSize = pRAM->nSize;
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

s32 ramWipe(Ram* pRAM) {
    if (pRAM->nSize != 0 && !xlHeapFill32(pRAM->pBuffer, pRAM->nSize, 0)) {
        return 0;
    }

    return 1;
}

// int ramGetBuffer(Ram *pRAM, void *ppRAM, unsigned int nOffset, unsigned int *pnSize);
s32 ramGetBuffer(Ram* pRAM, void* ppRAM, u32 nOffset, u32* pnSize) {
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

    *((u32*)ppRAM) = (u32)pRAM->pBuffer + nOffset;
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

static s32 ramGet32(Ram* pRAM, u32 nAddress, s32* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *pData = *((s32*)pRAM->pBuffer + (nAddress >> 2));
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

static s32 ramGet8(Ram* pRAM, u32 nAddress, s8* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *pData = *((s8*)pRAM->pBuffer + nAddress);
    } else {
        *pData = 0;
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

static s32 ramPut32(Ram* pRAM, u32 nAddress, s32* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *((s32*)pRAM->pBuffer + (nAddress >> 2)) = *pData;
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

static s32 ramPut8(Ram* pRAM, u32 nAddress, s8* pData) {
    nAddress &= 0x03FFFFFF;

    if (nAddress < pRAM->nSize) {
        *((s8*)pRAM->pBuffer + nAddress) = *pData;
    }

    return 1;
}

static s32 ramGetRI64(Ram* pRAM, u32 nAddress, s64* pData) { return 0; }

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

static s32 ramGetRI16(Ram* pRAM, u32 nAddress, s32* pData) { return 0; }

static s32 ramGetRI8(Ram* pRAM, u32 nAddress, s8* pData) { return 0; }

static s32 ramPutRI64(Ram* pRAM, u32 nAddress, s64* pData) { return 0; }

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

static s32 ramPutRI16(Ram* pRAM, u32 nAddress, s32* pData) { return 0; }

static s32 ramPutRI8(Ram* pRAM, u32 nAddress, s8* pData) { return 0; }

static s32 ramGetControl64(Ram* pRAM, u32 nAddress, s64* pData) { return 0; }

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

static s32 ramGetControl16(Ram* pRAM, u32 nAddress, s32* pData) { return 0; }

static s32 ramGetControl8(Ram* pRAM, u32 nAddress, s8* pData) { return 0; }

static s32 ramPutControl64(Ram* pRAM, u32 nAddress, s64* pData) { return 0; }

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

static s32 ramPutControl16(Ram* pRAM, u32 nAddress, s32* pData) { return 0; }

static s32 ramPutControl8(Ram* pRAM, u32 nAddress, s8* pData) { return 0; }
