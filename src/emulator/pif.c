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

bool pifReadRumble(Pif* pPIF, s32 channel, u16 address, u8* data) {
    int i;

    for (i = 0; i < 0x20; i++) {
        data[i] = 0;
    }

    switch (address) {
        case 0x400:
            for (i = 0; i < 0x20; i++) {
                data[i] = 0x80;
            }
            break;
        default:
            break;
    }

    return true;
}

bool pifWriteRumble(Pif* pPIF, s32 channel, u16 address, u8* data) {
    switch (address) {
        case 0x600:
            if (*data == 1) {
                simulatorRumbleStart(channel);
            } else if (*data == 0) {
                simulatorRumbleStop(channel);
            }
            break;
        default:
            break;
    }

    return true;
}

// this function is a copy-paste of ``__osContDataCrc``
static u8 pifContDataCrc(Pif* pPIF, u8* data) {
    u32 temp = 0;
    u32 i;
    u32 j;

    for (i = PIF_DATA_CRC_MESSAGE_BYTES; i != 0; data++, i--) {
        // Loop over each bit in the byte starting with most significant
        for (j = (1 << (PIF_DATA_CRC_LENGTH - 1)); j != 0; j >>= 1) {
            temp <<= 1;
            if (*data & j) {
                if (temp & (1 << PIF_DATA_CRC_LENGTH)) {
                    // Same as ret++; ret ^= 0x85 since last bit always 0 after the shift
                    temp ^= PIF_DATA_CRC_GENERATOR - 1;
                } else {
                    temp++;
                }
            } else if (temp & (1 << PIF_DATA_CRC_LENGTH)) {
                temp ^= PIF_DATA_CRC_GENERATOR;
            }
        }
    }

    // Act like a byte of zeros is appended to data
    do {
        temp <<= 1;
        if (temp & (1 << PIF_DATA_CRC_LENGTH)) {
            temp ^= PIF_DATA_CRC_GENERATOR;
        }
        i++;
    } while (i < PIF_DATA_CRC_LENGTH);

    // Discarding the excess is done automatically by the return type
    return temp;
}

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

static inline bool pifQueryController(Pif* pPIF, u8* buffer, s32 channel) {
    if (pPIF->eControllerType[channel] == CT_NONE) {
        return false;
    }

    *(u16*)(buffer + 1) = pPIF->controllerType[channel];
    *(buffer + 3) = pPIF->controllerStatus[channel];

    return true;
}

static inline bool pifReadController(Pif* pPIF, u8* buffer, u8* ptx, u8* prx, s32 channel) {
    if (pPIF->eControllerType[channel] == CT_NONE) {
        *prx |= 0x80;
    }

    if (!simulatorReadController(channel, (u32*)&buffer[1], ptx)) {
        return false;
    }

    return true;
}

bool pifPut8(Pif* pPIF, u32 nAddress, s8* pData) {
    if ((nAddress & 0x7FF) >= PIF_RAM_START) {
        *((s8*)(pPIF->pRAM) + ((nAddress & 0x7FF) - PIF_RAM_START)) = *pData;
    }

    return true;
}

bool pifPut16(Pif* pPIF, u32 nAddress, s16* pData) {
    if ((nAddress & 0x7FF) >= PIF_RAM_START) {
        *((s16*)(pPIF->pRAM) + (((nAddress & 0x7FF) - PIF_RAM_START) >> 1)) = *pData;
    }

    return true;
}

bool pifPut32(Pif* pPIF, u32 nAddress, s32* pData) {
    if ((nAddress & 0x7FF) >= PIF_RAM_START) {
        *((s32*)(pPIF->pRAM) + (((nAddress & 0x7FF) - PIF_RAM_START) >> 2)) = *pData;
    }

    return true;
}

bool pifPut64(Pif* pPIF, u32 nAddress, s64* pData) {
    if ((nAddress & 0x7FF) >= PIF_RAM_START) {
        *((s64*)(pPIF->pRAM) + (((nAddress & 0x7FF) - PIF_RAM_START) >> 3)) = *pData;
    }

    return true;
}

bool pifGet8(Pif* pPIF, u32 nAddress, s8* pData) {
    if ((nAddress & 0x7FF) < PIF_RAM_START) {
        *pData = *((s8*)pPIF->pROM + (nAddress & 0x7FF));
    } else {
        *pData = *((s8*)pPIF->pROM + ((nAddress & 0x7FF) - PIF_RAM_START));
    }

    return true;
}

bool pifGet16(Pif* pPIF, u32 nAddress, s16* pData) {
    if ((nAddress & 0x7FF) < PIF_RAM_START) {
        *pData = *((s16*)pPIF->pROM + ((nAddress & 0x7FF) >> 1));
    } else {
        *pData = *((s16*)pPIF->pROM + (((nAddress & 0x7FF) - PIF_RAM_START) >> 1));
    }

    return true;
}

bool pifGet32(Pif* pPIF, u32 nAddress, s32* pData) {
    if ((nAddress & 0x7FF) < PIF_RAM_START) {
        *pData = *((s32*)pPIF->pROM + ((nAddress & 0x7FF) >> 2));
    } else {
        *pData = *((s32*)pPIF->pROM + (((nAddress & 0x7FF) - PIF_RAM_START) >> 2));
    }

    return true;
}

bool pifGet64(Pif* pPIF, u32 nAddress, s64* pData) {
    if ((nAddress & 0x7FF) < PIF_RAM_START) {
        *pData = *((s64*)pPIF->pROM + ((nAddress & 0x7FF) >> 3));
    } else {
        *pData = *((s64*)pPIF->pROM + (((nAddress & 0x7FF) - PIF_RAM_START) >> 3));
    }

    return true;
}

bool pifExecuteCommand(Pif* pPIF, u8* buffer, u8* ptx, u8* prx, s32 channel) {
    switch (*buffer) {
        case 0x00:
            if (!pifQueryController(pPIF, buffer, channel)) {
                *prx |= 0x80;
            }
            break;
        case 0xFF:
            if (!pifQueryController(pPIF, buffer, channel)) {
                *prx |= 0x80;
            }
            break;
        case 0x01: {
            bool result = !pifReadController(pPIF, buffer, ptx, prx, channel) ? false : true;
            if (!result) {
                return false;
            }
            break;
        }
        case 0x02:
            if (!simulatorReadPak(channel, (buffer[1] << 3) | (buffer[2] >> 5), buffer + 3)) {
                return false;
            }
            buffer[0x23] = pifContDataCrc(pPIF, buffer + 3);
            break;
        case 0x03:
            if (!simulatorWritePak(channel, (buffer[1] << 3) | (buffer[2] >> 5), buffer + 3)) {
                return false;
            }
            buffer[0x23] = pifContDataCrc(pPIF, buffer + 3);
            break;
        case 0x04:
            if (!simulatorReadEEPROM(buffer[1], buffer + 2)) {
                return false;
            }
            break;
        case 0x05:
            if (!simulatorWriteEEPROM(buffer[1], buffer + 2)) {
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

bool pifProcessInputData(Pif* pPIF) {
    u8* prx;
    u8* ptx;
    s32 iData;
    s32 channel;

    iData = 0;
    channel = 0;

    while ((PIF_GET_RAM_DATA(pPIF, iData) != 0xFE && PIF_GET_RAM_DATA(pPIF, iData + 1) != 0xFE)) {
        while (PIF_GET_RAM_DATA(pPIF, iData) == 0xFF || PIF_GET_RAM_DATA(pPIF, iData) == 0xFD) {
            iData++;
        }

        if (PIF_GET_RAM_DATA(pPIF, iData) == 0xFE) {
            break;
        }

        ptx = PIF_GET_RAM_ADDR(pPIF, iData++);
        if (*ptx == 0) {
            channel++;
            continue;
        }

        prx = PIF_GET_RAM_ADDR(pPIF, iData++);
        if (!pifExecuteCommand(pPIF, PIF_GET_RAM_ADDR(pPIF, iData), ptx, prx, channel)) {
            return false;
        }

        channel++;
        switch (PIF_GET_RAM_DATA(pPIF, iData)) {
            case 0xFF:
            case 0:
                iData += 4;
                break;
            case 1:
                iData += 5;
                break;
            case 2:
            case 3:
                iData += 0x24;
                break;
            case 4:
            case 5:
                iData += 0xA;
                break;
            case 6:
                iData += 4;
                break;
            case 7:
                iData += 0xB;
                break;
            case 8:
                iData += 0xB;
                break;
            default:
                return false;
        }
    }

    ((u8*)pPIF->pRAM)[0x3F] = 0;
    return true;
}

bool pifProcessOutputData(Pif* pPIF) {
    u8* prx;
    u8* ptx;
    s32 iData;
    s32 channel;

    iData = 0;
    channel = 0;

    while ((PIF_GET_RAM_DATA(pPIF, iData) != 0xFE && PIF_GET_RAM_DATA(pPIF, iData + 1) != 0xFE)) {
        while (PIF_GET_RAM_DATA(pPIF, iData) == 0xFF || PIF_GET_RAM_DATA(pPIF, iData) == 0xFD) {
            iData++;
        }

        if (PIF_GET_RAM_DATA(pPIF, iData) == 0xFE) {
            break;
        }

        ptx = PIF_GET_RAM_ADDR(pPIF, iData++);
        if (*ptx == 0) {
            channel++;
            continue;
        }

        prx = PIF_GET_RAM_ADDR(pPIF, iData++);
        if (PIF_GET_RAM_DATA(pPIF, iData) == 1) {
            if (!pifExecuteCommand(pPIF, PIF_GET_RAM_ADDR(pPIF, iData), ptx, prx, channel)) {
                return false;
            }
        }

        channel++;
        switch (PIF_GET_RAM_DATA(pPIF, iData)) {
            case 0xFF:
            case 0:
                iData += 4;
                break;
            case 1:
                iData += 5;
                break;
            case 2:
            case 3:
                iData += 0x24;
                break;
            case 4:
            case 5:
                iData += 0xA;
                break;
            case 6:
                iData += 4;
                break;
            case 7:
                iData += 0xB;
                break;
            case 8:
                iData += 0xB;
                break;
            default:
                return false;
        }
    }

    ((u8*)pPIF->pRAM)[0x3F] = 0;
    return true;
}

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

            if (pPIF->pROM != NULL) {
                if (!xlHeapFree(&pPIF->pROM)) {
                    return false;
                }
            }

            pPIF->pROM = NULL;

            if (pPIF->pRAM != NULL) {
                if (!xlHeapFree(&pPIF->pRAM)) {
                    return false;
                }
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
