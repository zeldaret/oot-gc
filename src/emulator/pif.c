#include "emulator/pif.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlHeap.h"

_XL_OBJECTTYPE gClassPIF = {
    "PIF",
    sizeof(Pif),
    NULL,
    (EventFunc)pifEvent,
};

static u8 pifContDataCrc(Pif* pPIF, u8* data);

// Erased
static bool pifGetControllerInput(s32 channel, u32* controllerInput);
static bool pifGetControllerType(Pif* pPIF, s32 channel, u16* type, s8* status);

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifReadRumble.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifWriteRumble.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifContDataCrc.s")

bool pifSetControllerType(Pif* pPIF, s32 channel, ControllerType type) {
    if (!simulatorDetectController(channel)) {
        type = CT_NONE;
    }

    pPIF->controllerStatus[channel] = 0;
    pPIF->eControllerType[channel] = type;

    switch (type) {
        case CT_NONE:
            pPIF->controllerType[channel] = 0;
            break;
        case CT_CONTROLLER:
            pPIF->controllerType[channel] = 0x500;
            break;
        case CT_CONTROLLER_W_PAK:
        case CT_CONTROLLER_W_RPAK:
            pPIF->controllerType[channel] = 0x500;
            pPIF->controllerStatus[channel] = 1;
            break;
        case CT_MOUSE:
            pPIF->controllerType[channel] = 0x200;
            break;
        case CT_VOICE:
            pPIF->controllerType[channel] = 1;
            break;
        default:
            return false;
    }

    return true;
}

bool pifGetEControllerType(Pif* pPIF, s32 channel, ControllerType* type) {
    *type = pPIF->eControllerType[channel];
    return true;
}

bool pifSetEEPROMType(Pif* pPIF, ControllerType type) {
    pPIF->eControllerType[4] = type;

    switch (type) {
        case CT_NONE:
            pPIF->controllerType[4] = 0;
            pPIF->controllerStatus[4] = 0;
            break;
        case CT_4K:
            pPIF->controllerType[4] = 0x80;
            pPIF->controllerStatus[4] = 0;
            break;
        case CT_16K:
            pPIF->controllerType[4] = 0x40;
            pPIF->controllerStatus[4] = 0;
            break;
        default:
            break;
    }

    NO_INLINE();
    return true;
}

bool pifGetEEPROMSize(Pif* pPIF, u32* size) {
    if (pPIF->eControllerType[4] == CT_4K) {
        *size = 0x200;
    } else if (pPIF->eControllerType[4] == CT_16K) {
        *size = 0x800;
    } else {
        *size = 0;
        return false;
    }

    return true;
}

static inline bool pifQueryController(Pif* pPIF, u8* buffer, u8* prx, s32 channel) {
    if (pPIF->eControllerType[channel] == CT_NONE) {
        return false;
    }

    *(u16*)(buffer + 1) = pPIF->controllerType[channel];
    *(buffer + 3) = pPIF->controllerStatus[channel];

    return true;
}

static inline bool pifReadController(Pif* pPIF, u8* buffer, u8* prx, s32 channel, s32 unused) {
    if (pPIF->eControllerType[channel] == CT_NONE) {
        *prx |= 0x80;
    }

    if (!simulatorReadController(channel, (u32*)&buffer[1], unused)) {
        return false;
    }

    return true;
}

bool pifPut8(Pif* pPIF, u32 nAddress, s8* pData) {
    if ((nAddress & 0x7FF) >= 0x7C0) {
        *((s8*)(pPIF->pRAM) + ((nAddress & 0x7FF) - 0x7C0)) = *pData;
    }

    return true;
}

bool pifPut16(Pif* pPIF, u32 nAddress, s16* pData) {
    if ((nAddress & 0x7FF) >= 0x7C0) {
        *((s16*)(pPIF->pRAM) + (((nAddress & 0x7FF) - 0x7C0) >> 1)) = *pData;
    }

    return true;
}

bool pifPut32(Pif* pPIF, u32 nAddress, s32* pData) {
    if ((nAddress & 0x7FF) >= 0x7C0) {
        *((s32*)(pPIF->pRAM) + (((nAddress & 0x7FF) - 0x7C0) >> 2)) = *pData;
    }

    return true;
}

bool pifPut64(Pif* pPIF, u32 nAddress, s64* pData) {
    if ((nAddress & 0x7FF) >= 0x7C0) {
        *((s64*)(pPIF->pRAM) + (((nAddress & 0x7FF) - 0x7C0) >> 3)) = *pData;
    }

    return true;
}

bool pifGet8(Pif* pPIF, u32 nAddress, s8* pData) {
    if ((nAddress & 0x7FF) < 0x7C0) {
        *pData = *((s8*)pPIF->pROM + (nAddress & 0x7FF));
    } else {
        *pData = *((s8*)pPIF->pROM + ((nAddress & 0x7FF) - 0x7C0));
    }

    return true;
}

bool pifGet16(Pif* pPIF, u32 nAddress, s16* pData) {
    if ((nAddress & 0x7FF) < 0x7C0) {
        *pData = *((s16*)pPIF->pROM + ((nAddress & 0x7FF) >> 1));
    } else {
        *pData = *((s16*)pPIF->pROM + (((nAddress & 0x7FF) - 0x7C0) >> 1));
    }

    return true;
}

bool pifGet32(Pif* pPIF, u32 nAddress, s32* pData) {
    if ((nAddress & 0x7FF) < 0x7C0) {
        *pData = *((s32*)pPIF->pROM + ((nAddress & 0x7FF) >> 2));
    } else {
        *pData = *((s32*)pPIF->pROM + (((nAddress & 0x7FF) - 0x7C0) >> 2));
    }

    return true;
}

bool pifGet64(Pif* pPIF, u32 nAddress, s64* pData) {
    if ((nAddress & 0x7FF) < 0x7C0) {
        *pData = *((s64*)pPIF->pROM + ((nAddress & 0x7FF) >> 3));
    } else {
        *pData = *((s64*)pPIF->pROM + (((nAddress & 0x7FF) - 0x7C0) >> 3));
    }

    return true;
}

bool pifExecuteCommand(Pif* pPIF, u8* buffer, s32 unused, u8* prx, s32 channel) {
    switch (*buffer) {
        case 0x00:
            if (!pifQueryController(pPIF, buffer, prx, channel)) {
                *prx |= 0x80;
            }
            break;
        case 0xFF:
            if (!pifQueryController(pPIF, buffer, prx, channel)) {
                *prx |= 0x80;
            }
            break;
        case 0x01: {
            bool result = !pifReadController(pPIF, buffer, prx, channel, unused) ? false : true;
            if (!result) {
                return false;
            }
            break;
        }
        case 0x02:
            if (simulatorReadPak(channel, ((buffer[1] & 0xFF) << 3) | (buffer[2] >> 5), buffer + 3) == 0) {
                return false;
            }
            buffer[0x23] = pifContDataCrc(pPIF, buffer + 3);
            break;
        case 0x03:
            if (simulatorWritePak(channel, ((buffer[1] & 0xFF) << 3) | (buffer[2] >> 5), buffer + 3) == 0) {
                return false;
            }
            buffer[0x23] = pifContDataCrc(pPIF, buffer + 3);
            break;
        case 0x04:
            if (simulatorReadEEPROM(buffer[1], buffer + 2) == 0) {
                return false;
            }
            break;
        case 0x05:
            if (simulatorWriteEEPROM(buffer[1], buffer + 2) == 0) {
                return false;
            }
            break;
        case 0x06:
            buffer[1] = 0;
            buffer[2] = 0x10;
            buffer[3] = 0x80;
            break;
        case 0x07:
            buffer[3] = 2;
            buffer[6] = 0x59;
            buffer[7] = 0x23;
            break;
        case 0x08:
            buffer[0xA] = 0;
            break;
        default:
            return false;
    }

    return true;
}

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifProcessInputData.s")

#pragma GLOBAL_ASM("asm/non_matchings/pif/pifProcessOutputData.s")

bool pifSetData(Pif* pPIF, u8* acData) {
    if (!xlHeapCopy(pPIF->pRAM, acData, 0x40)) {
        return false;
    }

    if (!pifProcessInputData(pPIF)) {
        return false;
    }

    return true;
}

bool pifGetData(Pif* pPIF, u8* acData) {
    if (!pifProcessOutputData(pPIF)) {
        return false;
    }

    if (!xlHeapCopy(acData, pPIF->pRAM, 0x40)) {
        return false;
    }

    return true;
}

bool pifEvent(Pif* pPIF, s32 nEvent, void* pArgument) {
    s32 i;

    switch (nEvent) {
        case 2:
            pPIF->pHost = pArgument;
            if (!xlHeapTake(&pPIF->pROM, 0x800)) {
                return false;
            }
            if (!xlHeapTake(&pPIF->pRAM, 0x40)) {
                return false;
            }
            for (i = 0; i < ARRAY_COUNT(pPIF->controllerType); i++) {
                if (!pifSetControllerType(pPIF, i, CT_NONE)) {
                    return false;
                }
            }
            if (!pifSetEEPROMType(pPIF, CT_NONE)) {
                return false;
            }
            break;
        case 3:
            for (i = 0; i < ARRAY_COUNT(pPIF->controllerType); i++) {
                if (!pifSetControllerType(pPIF, i, CT_NONE)) {
                    return false;
                }
            }
            if (!pifSetEEPROMType(pPIF, CT_NONE)) {
                return false;
            }
            if (pPIF->pROM != NULL && !xlHeapFree(&pPIF->pROM)) {
                return false;
            }
            pPIF->pROM = NULL;
            if (pPIF->pRAM != NULL && !xlHeapFree(&pPIF->pRAM)) {
                return false;
            }
            pPIF->pRAM = NULL;
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pPIF->pHost), pArgument, (Put8Func)pifPut8, (Put16Func)pifPut16,
                                 (Put32Func)pifPut32, (Put64Func)pifPut64)) {
                return false;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pPIF->pHost), pArgument, (Get8Func)pifGet8, (Get16Func)pifGet16,
                                 (Get32Func)pifGet32, (Get64Func)pifGet64)) {
                return false;
            }
            break;
        case 0:
        case 1:
        case 0x1003:
            break;
        default:
            return false;
    }

    return true;
}
