#include "emulator/mips.h"
#include "emulator/system.h"

_XL_OBJECTTYPE gClassMips = {
    "MIPS",
    sizeof(Mips),
    NULL,
    (EventFunc)mipsEvent,
};

bool mipsSetInterrupt(Mips* pMips, MipsInterruptType eType) {
    s32 nInterrupt = pMips->nInterrupt;

    switch (eType) {
        case MIT_SP:
            if (pMips->nMask & 0x01) {
                pMips->nInterrupt = nInterrupt | 0x01;
            }
            break;
        case MIT_SI:
            if (pMips->nMask & 0x02) {
                pMips->nInterrupt = nInterrupt | 0x02;
            }
            break;
        case MIT_AI:
            if (pMips->nMask & 0x04) {
                pMips->nInterrupt = nInterrupt | 0x04;
            }
            break;
        case MIT_VI:
            if (pMips->nMask & 0x08) {
                pMips->nInterrupt = nInterrupt | 0x08;
            }
            break;
        case MIT_PI:
            if (pMips->nMask & 0x10) {
                pMips->nInterrupt = nInterrupt | 0x10;
            }
            break;
        case MIT_DP:
            if (pMips->nMask & 0x20) {
                pMips->nInterrupt = nInterrupt | 0x20;
            }
            break;
        default:
            return false;
    }

    if (nInterrupt != pMips->nInterrupt) {
        return true;
    }

    return false;
}

bool mipsResetInterrupt(Mips* pMips, MipsInterruptType eType) {
    s32 nInterrupt = pMips->nInterrupt;

    switch (eType) {
        case MIT_SP:
            pMips->nInterrupt = nInterrupt & ~0x01;
            break;
        case MIT_SI:
            pMips->nInterrupt = nInterrupt & ~0x02;
            break;
        case MIT_AI:
            pMips->nInterrupt = nInterrupt & ~0x04;
            break;
        case MIT_VI:
            pMips->nInterrupt = nInterrupt & ~0x08;
            break;
        case MIT_PI:
            pMips->nInterrupt = nInterrupt & ~0x10;
            break;
        case MIT_DP:
            pMips->nInterrupt = nInterrupt & ~0x20;
            break;
        default:
            return false;
    }

    if (nInterrupt != pMips->nInterrupt) {
        return true;
    }

    return false;
}

bool mipsPut8(Mips* pMips, u32 nAddress, s8* pData) { return false; }

bool mipsPut16(Mips* pMips, u32 nAddress, s16* pData) { return false; }

bool mipsPut32(Mips* pMips, u32 nAddress, s32* pData) {
    s32 nData;

    switch (nAddress & 0xF) {
        case 0x0:
            nData = *pData & 0xFFF;
            pMips->nMode = (pMips->nMode & ~0x7F) | (*pData & 0x7F);

            if (nData & 0x80) {
                pMips->nMode &= ~0x80;
            }
            if (nData & 0x100) {
                pMips->nMode |= 0x80;
            }
            if (nData & 0x200) {
                pMips->nMode &= ~0x100;
            }
            if (nData & 0x400) {
                pMips->nMode |= 0x100;
            }
            if (nData & 0x800) {
                xlObjectEvent(pMips->pHost, 0x1001, (void*)0xA);
            }
            if (nData & 0x1000) {
                pMips->nMode &= ~0x200;
            }
            if (nData & 0x2000) {
                pMips->nMode |= 0x200;
            }
            break;
        case 0xC:
            nData = *pData & 0xFFF;

            if (nData & 1) {
                pMips->nMask &= ~1;
            }
            if (nData & 2) {
                pMips->nMask |= 1;
            }
            if (nData & 4) {
                pMips->nMask &= ~2;
            }
            if (nData & 8) {
                pMips->nMask |= 2;
            }
            if (nData & 0x10) {
                pMips->nMask &= ~4;
            }
            if (nData & 0x20) {
                pMips->nMask |= 4;
            }
            if (nData & 0x40) {
                pMips->nMask &= ~8;
            }
            if (nData & 0x80) {
                pMips->nMask |= 8;
            }
            if (nData & 0x100) {
                pMips->nMask &= ~0x10;
            }
            if (nData & 0x200) {
                pMips->nMask |= 0x10;
            }
            if (nData & 0x400) {
                pMips->nMask &= ~0x20;
            }
            if (nData & 0x800) {
                pMips->nMask |= 0x20;
            }
            break;
        case 0x4:
        case 0x8:
            break;
        default:
            return false;
    }

    return true;
}

bool mipsPut64(Mips* pMips, u32 nAddress, s64* pData) { return false; }

bool mipsGet8(Mips* pMips, u32 nAddress, s8* pData) { return false; }

bool mipsGet16(Mips* pMips, u32 nAddress, s16* pData) { return false; }

bool mipsGet32(Mips* pMips, u32 nAddress, s32* pData) {
    switch (nAddress & 0xF) {
        case 0x0:
            *pData = pMips->nMode;
            break;
        case 0x4:
            *pData = 0x02020102;
            break;
        case 0x8:
            *pData = pMips->nInterrupt;
            break;
        case 0xC:
            *pData = pMips->nMask;
            break;
        default:
            return false;
    }

    return true;
}

bool mipsGet64(Mips* pMips, u32 nAddress, s64* pData) { return false; }

bool mipsEvent(Mips* pMips, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pMips->nMode = 0;
            pMips->nMask = 0;
            pMips->nInterrupt = 0;
            pMips->pHost = pArgument;
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pMips->pHost), pArgument, (Put8Func)mipsPut8, (Put16Func)mipsPut16,
                                 (Put32Func)mipsPut32, (Put64Func)mipsPut64)) {
                return false;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pMips->pHost), pArgument, (Get8Func)mipsGet8, (Get16Func)mipsGet16,
                                 (Get32Func)mipsGet32, (Get64Func)mipsGet64)) {
                return false;
            }
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
