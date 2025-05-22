#include "emulator/cpu.h"
#include "dolphin.h"
#include "emulator/frame.h"
#include "emulator/library.h"
#include "emulator/mcardGCN.h"
#include "emulator/ram.h"
#include "emulator/rom.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/video.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "math.h"
#include "stdio.h"

// Line numbers for different versions
#if IS_OOT
#define LN(n) n
#else
#define LN(n) (n + 6)
#endif

static bool cpuHeapReset(u32* array, s32 count);
static bool cpuDMAUpdateFunction(Cpu* pCPU, s32 start, s32 end);
static bool treeInit(Cpu* pCPU, s32 root_address);
static bool treeKill(Cpu* pCPU);
static bool treeKillNodes(Cpu* pCPU, CpuFunction* tree);
static bool treeAdjustRoot(Cpu* pCPU, s32 new_start, s32 new_end);
static inline bool treeSearch(Cpu* pCPU, s32 target, CpuFunction** node);
static bool treeSearchNode(CpuFunction* tree, s32 target, CpuFunction** node);
bool treeInsert(Cpu* pCPU, s32 start, s32 end);
static bool treeInsertNode(CpuFunction** tree, s32 start, s32 end, CpuFunction** ppFunction);
static bool treeBalance(CpuTreeRoot* root);
static bool treeKillRange(Cpu* pCPU, CpuFunction* tree, s32 start, s32 end);
static bool treeCleanNodes(Cpu* pCPU, CpuFunction* top);
static bool treeForceCleanNodes(Cpu* pCPU, CpuFunction* tree, s32 kill_limit);
static bool treePrintNode(Cpu* pCPU, CpuFunction* tree, s32 print_flag, s32* left, s32* right);
static inline s32 treeMemory(Cpu* pCPU);

_XL_OBJECTTYPE gClassCPU = {
    "CPU",
    sizeof(Cpu),
    NULL,
    (EventFunc)cpuEvent,
};

static char* gaszNameGPR[] = {
    "ZERO", "AT", "V0", "V1", "A0", "A1", "A2", "A3", "T0", "T1", "T2", "T3", "T4", "T5", "T6", "T7",
    "S0",   "S1", "S2", "S3", "S4", "S5", "S6", "S7", "T8", "T9", "K0", "K1", "GP", "SP", "S8", "RA",
};

static char* gaszNameFPR[] = {
    "F0",  "F1",  "F2",  "F3",  "F4",  "F5",  "F6",  "F7",  "F8",  "F9",  "F10",
    "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21",
    "F22", "F23", "F24", "F25", "F26", "F27", "F28", "F29", "F30", "F21", // bug, should be "F31"
};

static char* gaszNameCP0[] = {
    "INDEX",         "RANDOM",        "ENTRY-LO0",     "ENTRY-LO1",     "CONTEXT",       "PAGE-MASK", "WIRED",
    "(RESERVED-7)",  "BAD-VADDR",     "COUNT",         "ENTRY-HI",      "COMPARE",       "STATUS",    "CAUSE",
    "EPC",           "uPC-ID",        "CONFIG",        "LLADDR",        "WATCH-LO",      "WATCH-HI",  "X-CONTEXT",
    "(RESERVED-21)", "(RESERVED-22)", "(RESERVED-23)", "(RESERVED-24)", "(RESERVED-25)", "ECC",       "CACHE-ERROR",
    "TAG-LO",        "TAG-HI",        "ERROR-EPC",     "(RESERVED-31)",
};

static char* gaszNameCP1[] = {
    "FCR0",
    "FCR1 (RESERVED)",
    "FCR2 (RESERVED)",
    "FCR3 (RESERVED)",
    "FCR4 (RESERVED)",
    "FCR5 (RESERVED)",
    "FCR6 (RESERVED)",
    "FCR7 (RESERVED)",
    "FCR8 (RESERVED)",
    "FCR9 (RESERVED)",
    "FCR10 (RESERVED)",
    "FCR11 (RESERVED)",
    "FCR12 (RESERVED)",
    "FCR13 (RESERVED)",
    "FCR14 (RESERVED)",
    "FCR15 (RESERVED)",
    "FCR16 (RESERVED)",
    "FCR17 (RESERVED)",
    "FCR18 (RESERVED)",
    "FCR19 (RESERVED)",
    "FCR20 (RESERVED)",
    "FCR21 (RESERVED)",
    "FCR22 (RESERVED)",
    "FCR23 (RESERVED)",
    "FCR24 (RESERVED)",
    "FCR25 (RESERVED)",
    "FCR26 (RESERVED)",
    "FCR27 (RESERVED)",
    "FCR28 (RESERVED)",
    "FCR29 (RESERVED)",
    "FCR30 (RESERVED)",
    "FCR31",
};

static s64 ganMaskGetCP0[] = {
    0x000000008000003F, 0x000000000000003F, 0x000000003FFFFFFF, 0x000000003FFFFFFF, 0xFFFFFFFFFFFFFFF0,
    0x0000000001FFE000, 0x000000000000001F, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x00000000FFFFFFFF,
    0x00000000FFFFE0FF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFF, 0x00000000F000FF7C, 0xFFFFFFFFFFFFFFFF,
    0x000000000000FFFF, 0x00000000FFFFEFFF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFB, 0x000000000000000F,
    0x00000000FFFFFFF0, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x00000000000000FF, 0x00000000FFBFFFFF, 0x00000000FFFFFFFF, 0x0000000000000000,
    0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
};

static s64 ganMaskSetCP0[] = {
    0x000000000000003F, 0x000000000000003F, 0x000000003FFFFFFF, 0x000000003FFFFFFF, 0xFFFFFFFFFFFFFFF0,
    0x0000000001FFE000, 0x000000000000001F, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x00000000FFFFFFFF,
    0x00000000FFFFE0FF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFF, 0x0000000000000300, 0xFFFFFFFFFFFFFFFF,
    0x000000000000FFFF, 0x00000000FFFFEFFF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFB, 0x000000000000000F,
    0x00000000FFFFFFF0, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x00000000000000FF, 0x00000000FFBFFFFF, 0x00000000FFFFFFFF, 0x0000000000000000,
    0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
};

static u8 Opcode[] = {
    true, true, true, true,  true, true, true, true, true, true, true, true,  true,  true,  true,  true,
    true, true, true, false, true, true, true, true, true, true, true, true,  false, false, false, true,
    true, true, true, true,  true, true, true, true, true, true, true, true,  true,  true,  true,  true,
    true, true, true, false, true, true, true, true, true, true, true, false, true,  true,  true,  true,
};

static u8 SpecialOpcode[] = {
    true, false, true, true, true, false, true, true,  true,  true,  false, false, true, true,  false, true,
    true, true,  true, true, true, false, true, true,  true,  true,  true,  true,  true, true,  true,  true,
    true, true,  true, true, true, true,  true, true,  false, false, true,  true,  true, true,  true,  true,
    true, true,  true, true, true, false, true, false, true,  false, true,  true,  true, false, true,  true,
};

static u8 RegimmOpcode[] = {
    true, true, true, true, false, false, false, false, true,  true,  true,  true,  true,  false, true,  false,
    true, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false,
};

static void* gHeapTree;

#if IS_MM
static u8 gRegCount;
#endif

static s32 ganOpcodeSaveFP1[] = {
    0x8F480018, 0x11000014, 0x00000000, 0x4448F800, 0x00000000,
};

static s32 ganOpcodeSaveFP2_0[] = {
    0x8CBB0018, 0x1360000A, 0x00000000, 0x445BF800, 0x00000000,
};

static s32 ganOpcodeSaveFP2_1[] = {
    0x13600009,
    0xACBF011C,
    0x445BF800,
};

static s32 ganOpcodeLoadFP[] = {
    0x8F5B0018, 0x13600013, 0x00000000, 0x8F5B012C, 0x44DBF800,
};

/**
 * @brief Mapping of VR4300 to PPC registers.
 *
 * If bit 0x100 is set the VR4300 register is not directly mapped to any PPC register,
 * Instead the register will use the emulated VR4300 object for saving/loading register values.
 */
s32 ganMapGPR[32] = {
    0x0000000A, 0x0000000B, 0x0000000C, 0x0000000E, 0x0000000F, 0x00000010, 0x00000011, 0x00000012,
    0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018, 0x00000019, 0x0000001A,
    0x00000110, 0x00000111, 0x00000112, 0x00000113, 0x00000114, 0x00000115, 0x00000116, 0x00000117,
    0x0000001B, 0x0000001C, 0x0000001D, 0x0000001E, 0x0000011C, 0x0000001F, 0x0000011E, 0x0000011F,
};

u32 aHeapTreeFlag[125];

#if IS_MM
u8 gRegList[32];

static inline s32 cpuCountTLB(Cpu* pCPU, s32* pnCount);
#endif

static bool cpuHackHandler(Cpu* pCPU) {
    u32 nSize;
    u32* pnCode;
    s32 iCode;
    s32 iSave1;
    s32 iSave2;
    s32 iLoad;

    iSave1 = iSave2 = iLoad = 0;

    if (xlObjectTest(SYSTEM_RAM(pCPU->pHost), &gClassRAM) &&
        ramGetBuffer(SYSTEM_RAM(pCPU->pHost), (void**)&pnCode, 0, NULL)) {
        if (!ramGetSize(SYSTEM_RAM(pCPU->pHost), (s32*)&nSize)) {
            return false;
        }

        for (iCode = 0; iCode < (nSize >> 2) && (iSave1 != -1 || iSave2 != -1 || iLoad != -1); iCode++) {
            if (iSave1 != -1) {
                if (pnCode[iCode] == ganOpcodeSaveFP1[iSave1]) {
                    iSave1 += 1;
                    if (iSave1 == 5U) {
                        pnCode[iCode - 3] = 0;
                        iSave1 = -1;
                    }
                } else {
                    iSave1 = 0;
                }
            }

            if (iSave2 != -1) {
                if (pnCode[iCode] == ganOpcodeSaveFP2_0[iSave2]) {
                    iSave2 += 1;
                    if (iSave2 == 5U) {
                        pnCode[iCode - 3] = 0;
                        iSave2 = -1;
                    }
                } else if (pnCode[iCode] == ganOpcodeSaveFP2_1[iSave2]) {
                    iSave2 += 1;
                    if (iSave2 == 3U) {
                        pnCode[iCode - 2] = 0;
                        iSave2 = -1;
                    }
                } else {
                    iSave2 = 0;
                }
            }

            if (iLoad != -1) {
                if (pnCode[iCode] == ganOpcodeLoadFP[iLoad]) {
                    iLoad += 1;
                    if (iLoad == 5U) {
                        pnCode[iCode - 3] = 0;
                        iLoad = -1;
                    }
                } else {
                    iLoad = 0;
                }
            }
        }
    }

    return (iSave1 == -1 && iSave2 == -1 && iLoad == -1) ? true : false;
}

static inline bool cpuMakeCachedAddress(Cpu* pCPU, s32 nAddressN64, s32 nAddressHost, CpuFunction* pFunction) {
    s32 iAddress;
    CpuAddress* aAddressCache;

    aAddressCache = pCPU->aAddressCache;
    if ((iAddress = pCPU->nCountAddress) == ARRAY_COUNT(pCPU->aAddressCache)) {
        iAddress -= 1;
    } else {
        pCPU->nCountAddress++;
    }

    for (; iAddress > 0; iAddress--) {
        aAddressCache[iAddress] = aAddressCache[iAddress - 1];
    }

    aAddressCache[0].nN64 = nAddressN64;
    aAddressCache[0].nHost = nAddressHost;
    aAddressCache[0].pFunction = pFunction;
    return true;
}

bool cpuFreeCachedAddress(Cpu* pCPU, s32 nAddress0, s32 nAddress1) {
    s32 iAddress;
    s32 iAddressNext;
    s32 nAddressN64;
    CpuAddress* aAddressCache = pCPU->aAddressCache;

    iAddress = 0;
    while (iAddress < pCPU->nCountAddress) {
        nAddressN64 = aAddressCache[iAddress].nN64;
        if (nAddress0 <= nAddressN64 && nAddressN64 <= nAddress1) {
            for (iAddressNext = iAddress; iAddressNext < pCPU->nCountAddress - 1; iAddressNext++) {
                aAddressCache[iAddressNext] = aAddressCache[iAddressNext + 1];
            }
            pCPU->nCountAddress--;
        } else {
            iAddress++;
        }
    }

    return true;
}

static bool cpuFindCachedAddress(Cpu* pCPU, s32 nAddressN64, s32* pnAddressHost) {
    s32 iAddress;
    CpuFunction* pFunction;
    CpuAddress addressFound;
    CpuAddress* aAddressCache = pCPU->aAddressCache;

    for (iAddress = 0; iAddress < pCPU->nCountAddress; iAddress++) {
        if (nAddressN64 == aAddressCache[iAddress].nN64) {
            if (iAddress > ARRAY_COUNT(pCPU->aAddressCache) / 2) {
                addressFound = aAddressCache[iAddress];
                for (; iAddress > 0; iAddress--) {
                    aAddressCache[iAddress] = aAddressCache[iAddress - 1];
                }
                aAddressCache[iAddress] = addressFound;
            }

            pFunction = aAddressCache[iAddress].pFunction;
            if (pFunction->timeToLive > 0) {
                pFunction->timeToLive = pCPU->survivalTimer;
            }

            *pnAddressHost = aAddressCache[iAddress].nHost;
            return true;
        }
    }

    return false;
}

bool cpuTestInterrupt(Cpu* pCPU, s32 nMaskIP) {
    pCPU->anCP0[13] |= (nMaskIP & 0xFF) << 8;
    if ((pCPU->anCP0[12] & 6) != 0) {
        return false;
    }
    if ((pCPU->anCP0[12] & 1) == 0) {
        return false;
    }
    if ((((pCPU->anCP0[12] & 0xFF00) >> 8) & (nMaskIP & 0xFF)) == 0) {
        return false;
    }
    return true;
}

bool cpuException(Cpu* pCPU, CpuExceptionCode eCode, s32 nMaskIP) {
    s32 pad[2];

    if ((pCPU->anCP0[12] & 6) != 0) {
        return false;
    }
    nMaskIP &= 0xFF;
    if (eCode == CEC_NONE) {
        return false;
    }
    if ((eCode >= CEC_RESERVED_16 && eCode <= CEC_RESERVED_22) ||
        (eCode >= CEC_RESERVED_24 && eCode <= CEC_RESERVED_30)) {
        return false;
    }
    if (eCode == CEC_RESERVED) {
        return false;
    }

    if (eCode == CEC_INTERRUPT) {
        if (!cpuTestInterrupt(pCPU, nMaskIP)) {
            return false;
        }
    } else {
        pCPU->nPC -= 4;
        pCPU->nMode |= 4;
    }

    pCPU->nMode &= ~8;
    if (!(pCPU->nMode & 0x10)) {
        if (!cpuHackHandler(pCPU)) {
            xlPostText("Exception: #### INTERNAL ERROR #### Cannot match exception-handler!", "cpu.c", LN(923));
        }
        pCPU->nMode |= 0x10;
    }
    if (pCPU->nWaitPC != 0xFFFFFFFF) {
        pCPU->nWaitPC = -1;
        pCPU->anCP0[14] = pCPU->nPC - 4;
        pCPU->anCP0[13] |= 0x80000000;
    } else {
        pCPU->anCP0[14] = pCPU->nPC;
    }

    pCPU->nMode &= ~0x80;
    pCPU->anCP0[12] |= 2;
    pCPU->anCP0[13] = (pCPU->anCP0[13] & ~0x7C) | (eCode << 2);

    if (eCode - 1 <= 2U) {
        pCPU->nPC = 0x80000000;
    } else {
        pCPU->nPC = 0x80000180;
    }

    pCPU->nMode |= 4;
    pCPU->nMode |= 0x20;

    if (!libraryCall(SYSTEM_LIBRARY(pCPU->pHost), pCPU, -1)) {
        return false;
    }

    return true;
}

/**
 * @brief Creates a new device and registers memory space for that device.
 *
 * @param pCPU The emulated VR4300.
 * @param piDevice A pointer to the index in the cpu->devices array which the device was created.
 * @param pObject The object which will handle reuqests for this device.
 * @param nOffset Starting address of the device's address space.
 * @param nAddress Starting physical address of the device's address space.
 * @param nAddress1 Ending physical address of the device's address space.
 * @param nType An argument which will be passed back to the device's event handler.
 * @return bool true on success, false otherwise.
 */
static bool cpuMakeDevice(Cpu* pCPU, s32* piDevice, void* pObject, s32 nOffset, u32 nAddress0, u32 nAddress1,
                          s32 nType) {
    CpuDevice* pDevice;
    s32 iDevice;
    s32 pad;

    iDevice = (nType & 0x100) ? (ARRAY_COUNT(pCPU->apDevice) / 2) : 0;
    for (; iDevice < ARRAY_COUNT(pCPU->apDevice); iDevice++) {
        if (pCPU->apDevice[iDevice] == NULL) {
            break;
        }
    }
    if (iDevice == ARRAY_COUNT(pCPU->apDevice)) {
        return false;
    }

    *piDevice = iDevice;
    if (!xlHeapTake((void**)&pDevice, sizeof(CpuDevice))) {
        return false;
    }

    pCPU->apDevice[iDevice] = pDevice;
    pDevice->nType = nType;
    pDevice->pObject = pObject;
    pDevice->nOffsetAddress = nOffset;
    pDevice->nAddressPhysical0 = nAddress0;
    pDevice->nAddressPhysical1 = nAddress1;

    if (!xlObjectEvent(pObject, 0x1002, pDevice)) {
        return false;
    }

    return true;
}

bool cpuFreeDevice(Cpu* pCPU, s32 iDevice) {
    if (!xlHeapFree((void**)&pCPU->apDevice[iDevice])) {
        return false;
    } else {
        s32 iAddress;

        pCPU->apDevice[iDevice] = NULL;
        for (iAddress = 0; iAddress < ARRAY_COUNT(pCPU->aiDevice); iAddress++) {
            if (pCPU->aiDevice[iAddress] == iDevice) {
                pCPU->aiDevice[iAddress] = pCPU->iDeviceDefault;
            }
        }
        return true;
    }
}

static bool cpuMapAddress(Cpu* pCPU, s32* piDevice, u32 nVirtual, u32 nPhysical, s32 nSize) {
    s32 iDeviceTarget;
    s32 iDeviceSource;
    u32 nAddressVirtual0;
    u32 nAddressVirtual1;

    for (iDeviceSource = 0; iDeviceSource < ARRAY_COUNT(pCPU->apDevice); iDeviceSource++) {
        if (iDeviceSource != pCPU->iDeviceDefault && pCPU->apDevice[iDeviceSource] != NULL &&
            pCPU->apDevice[iDeviceSource]->nAddressPhysical0 <= nPhysical &&
            nPhysical <= pCPU->apDevice[iDeviceSource]->nAddressPhysical1) {
            break;
        }
    }

    if (iDeviceSource == ARRAY_COUNT(pCPU->apDevice)) {
        iDeviceSource = pCPU->iDeviceDefault;
    }

    if (!cpuMakeDevice(pCPU, &iDeviceTarget, pCPU->apDevice[iDeviceSource]->pObject, nPhysical - nVirtual,
                       pCPU->apDevice[iDeviceSource]->nAddressPhysical0,
                       pCPU->apDevice[iDeviceSource]->nAddressPhysical1, pCPU->apDevice[iDeviceSource]->nType)) {
        return false;
    }

    nAddressVirtual0 = nVirtual;
    nAddressVirtual1 = nVirtual + nSize - 1;
    while (nAddressVirtual0 < nAddressVirtual1) {
        pCPU->aiDevice[nAddressVirtual0 >> 16] = iDeviceTarget;
        nAddressVirtual0 += 0x10000;
    }

    if (piDevice != NULL) {
        *piDevice = iDeviceTarget;
    }

    return true;
}

static inline s32 cpuCountTLB(Cpu* pCPU, s32* pnCount) {
    s32 iEntry;
    s32 nCount;

    nCount = 0;
    for (iEntry = 0; iEntry < 48; iEntry++) {
        if (!(pCPU->aTLB[iEntry][2] & 2)) {
            nCount++;
        }
    }

    *pnCount = nCount;
    return nCount;
}

static bool cpuSetTLB(Cpu* pCPU, s32 iEntry) {
    s32 iDevice;
    u32 nMask;
    u32 nVirtual;
    u32 nPhysical;

    if ((pCPU->anCP0[10] & 0xFFFFE000) == 0x80000000) {
        pCPU->aTLB[iEntry][0] &= ~2;
        ;
        if ((iDevice = pCPU->aTLB[iEntry][4]) != -1) {
            if (!cpuFreeDevice(pCPU, iDevice)) {
                return false;
            }
            pCPU->aTLB[iEntry][4] = -1;
        }

        return true;
    }

    if ((iDevice = pCPU->aTLB[iEntry][4]) != -1) {
        if (!cpuFreeDevice(pCPU, iDevice)) {
            return false;
        }
    }

    pCPU->aTLB[iEntry][0] = pCPU->anCP0[2] | 2;
    pCPU->aTLB[iEntry][1] = pCPU->anCP0[3];
    pCPU->aTLB[iEntry][2] = pCPU->anCP0[10];
    pCPU->aTLB[iEntry][3] = pCPU->anCP0[5];

    nMask = pCPU->aTLB[iEntry][3] | 0x1FFF;
    nVirtual = pCPU->aTLB[iEntry][2] & 0xFFFFE000;
    nPhysical = ((s32)(pCPU->aTLB[iEntry][0] & 0xFFFFFFC0) << 6) + (nVirtual & nMask);
    if (nVirtual == 0xC0000000 && nPhysical == 0x80000000) {
        nPhysical = 0x04900000;
    }
    if (nVirtual < 0x80000000 || 0xC0000000 <= nVirtual) {
        if (!cpuMapAddress(pCPU, &iDevice, nVirtual, nPhysical, nMask + 1)) {
            return false;
        }
        if (nVirtual == 0x70000000 && nPhysical == 0 && nMask == 0x007FFFFF) {
            if (!cpuMapAddress(pCPU, NULL, 0x7F000000, 0x10034B30, 0x01000000)) {
                return false;
            }
        }
    } else {
        iDevice = -1;
    }

    pCPU->aTLB[iEntry][4] = iDevice;
    return true;
}

/**
 * @brief Gets the operating mode of the VR4300
 *
 * @param nStatus The status bits to determine the mode for.
 * @param peMode A pointer to the mode determined.
 * @return bool true on success, false otherwise.
 */
static bool cpuGetMode(u64 nStatus, CpuMode* peMode) {
    if (nStatus & 2) {
        *peMode = CM_KERNEL;
        return true;
    }

    if (!(nStatus & 4)) {
        switch (nStatus & 0x18) {
            case 0x10:
                *peMode = CM_USER;
                break;
            case 8:
                *peMode = CM_SUPER;
                break;
            case 0:
                *peMode = CM_KERNEL;
                break;
            default:
                return false;
        }
        return true;
    }

    NO_INLINE();
    return false;
}

/**
 * @brief Determines the register size that the VR4300 is using.
 *
 * @param nStatus Status bits for determining the register size.
 * @param peSize A pointer to the size determined.
 * @param peMode A pointer to the mode determined.
 * @return bool
 */
static bool cpuGetSize(u64 nStatus, CpuSize* peSize, CpuMode* peMode) {
    CpuMode eMode;

    *peSize = CS_NONE;
    if (peMode != NULL) {
        *peMode = CM_NONE;
    }

    if (cpuGetMode(nStatus, &eMode)) {
        switch (eMode) {
            case CM_USER:
                *peSize = nStatus & 0x20 ? CS_64BIT : CS_32BIT;
                break;
            case CM_SUPER:
                *peSize = nStatus & 0x40 ? CS_64BIT : CS_32BIT;
                break;
            case CM_KERNEL:
                *peSize = nStatus & 0x80 ? CS_64BIT : CS_32BIT;
                break;
            default:
                return false;
        }

        if (peMode != NULL) {
            *peMode = eMode;
        }

        return true;
    }

    return false;
}

/**
 * @brief Sets the status bits of the VR4300
 *
 * @param pCPU The emulated VR4300
 * @param nStatus New status.
 * @param unknown Unused.
 * @return bool true on success, false otherwise.
 */
static bool cpuSetCP0_Status(Cpu* pCPU, u64 nStatus, u32 unknown) {
    CpuMode eMode;
    CpuMode eModeLast;
    CpuSize eSize;
    CpuSize eSizeLast;

    if (!cpuGetSize(nStatus, &eSize, &eMode)) {
        return false;
    }
    if (!cpuGetSize(pCPU->anCP0[12], &eSizeLast, &eModeLast)) {
        return false;
    }

    pCPU->anCP0[12] = nStatus;

    NO_INLINE();
    return true;
}

bool cpuSetRegisterCP0(Cpu* pCPU, s32 iRegister, s64 nData) {
    s32 pad;
    s32 bFlag = false;

    switch (iRegister) {
        case 1:
        case 7:
        case 8:
            break;
        case 9:
            bFlag = true;
            break;
        case 11:
            bFlag = true;
            xlObjectEvent(pCPU->pHost, 0x1001, (void*)3);
            if (pCPU->nMode & 1 || (nData & ganMaskSetCP0[iRegister]) == 0) {
                pCPU->nMode &= ~1;
            } else {
                pCPU->nMode |= 1;
            }
            break;
        case 12:
            cpuSetCP0_Status(pCPU, nData & ganMaskSetCP0[iRegister], 0);
            break;
        case 13:
            xlObjectEvent(pCPU->pHost, (nData & 0x100) ? 0x1000 : 0x1001, (void*)0);
            xlObjectEvent(pCPU->pHost, (nData & 0x200) ? 0x1000 : 0x1001, (void*)1);
            bFlag = true;
            break;
        case 14:
            bFlag = true;
            break;
        case 15:
            break;
        case 16:
            pCPU->anCP0[16] = (u32)(nData & ganMaskSetCP0[iRegister]);
            break;
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 27:
        case 31:
            break;
        default:
            bFlag = true;
            break;
    }

    if (bFlag) {
        pCPU->anCP0[iRegister] = nData & ganMaskSetCP0[iRegister];
    }

    return true;
}

bool cpuGetRegisterCP0(Cpu* pCPU, s32 iRegister, s64* pnData) {
    s32 bFlag = false;
    s32 nCount;

    switch (iRegister) {
        case 1:
            cpuCountTLB(pCPU, &nCount);
            *pnData = nCount;
            break;
        case 9:
            bFlag = true;
            break;
        case 11:
            bFlag = true;
            break;
        case 14:
            bFlag = true;
            break;
        case 7:
            *pnData = 0;
            break;
        case 8:
            bFlag = true;
            break;
        case 21:
            *pnData = 0;
            break;
        case 22:
            *pnData = 0;
            break;
        case 23:
            *pnData = 0;
            break;
        case 24:
            *pnData = 0;
            break;
        case 25:
            *pnData = 0;
            break;
        case 31:
            *pnData = 0;
            break;
        default:
            bFlag = true;
            break;
    }

    if (bFlag) {
        *pnData = pCPU->anCP0[iRegister] & ganMaskGetCP0[iRegister];
    }

    return true;
}

/**
 * @brief Sets CP0 values for returnning from an exception.
 *
 * @param pCPU The emulated VR4300.
 * @return bool true on success, false otherwise
 */
bool __cpuERET(Cpu* pCPU) {
    if (pCPU->anCP0[12] & 4) {
        pCPU->nPC = pCPU->anCP0[30];
        pCPU->anCP0[12] &= ~4;
    } else {
        pCPU->nPC = pCPU->anCP0[14];
        pCPU->anCP0[12] &= ~2;
    }

    pCPU->nMode |= 4;
    pCPU->nMode |= 0x20;

    return true;
}

/**
 * @brief Sets flags for handling cpu breakpoints.
 *
 * @param pCPU The emulated VR4300.
 * @return bool true on success, false otherwise
 */
bool __cpuBreak(Cpu* pCPU) {
    pCPU->nMode |= 2;
    return true;
}

#include "emulator/_cpuGCN.c"

/**
 * @brief Maps an object to a cpu device.
 *
 * @param pCPU The emulated VR4300.
 * @param pObject The device that will handle requests for this memory space.
 * @param nAddress0 The start of the memory space for which the device will be responsible.
 * @param nAddress1 The end of the memory space for which the device will be responsible.
 * @param nType An argument which will be passed back to the device on creation.
 * @return bool true on success, false otherwise.
 */
bool cpuMapObject(Cpu* pCPU, void* pObject, u32 nAddress0, u32 nAddress1, s32 nType) {
    s32 iDevice;
    s32 iAddress;
    u32 nAddressVirtual0;
    u32 nAddressVirtual1;

    if (nAddress0 == 0 && nAddress1 == 0xFFFFFFFF) {
        if (!cpuMakeDevice(pCPU, &iDevice, pObject, 0, nAddress0, nAddress1, nType)) {
            return false;
        }

        pCPU->iDeviceDefault = iDevice;
        for (iAddress = 0; iAddress < ARRAY_COUNT(pCPU->aiDevice); iAddress++) {
            pCPU->aiDevice[iAddress] = iDevice;
        }
    } else {
        //! @bug: nAddress0 should not be added to nOffset (0x80000000) here. The start address
        //! is computed as nAddress0 + nOffset, so essentially the address gets added twice.
        if (!cpuMakeDevice(pCPU, &iDevice, pObject, nAddress0 + 0x80000000, nAddress0, nAddress1, nType)) {
            return false;
        }

        nAddressVirtual0 = nAddress0 | 0x80000000;
        nAddressVirtual1 = nAddress1 | 0x80000000;
        iAddress = nAddressVirtual0 >> 16;
        while (nAddressVirtual0 < nAddressVirtual1) {
            pCPU->aiDevice[iAddress] = iDevice;
            nAddressVirtual0 += 0x10000;
            iAddress++;
        }

        //! @bug: nAddress0 should not be added to nOffset (0x60000000) here. The start address
        //! is computed as nAddress0 + nOffset, so essentially the address gets added twice.
        if (!cpuMakeDevice(pCPU, &iDevice, pObject, nAddress0 + 0x60000000, nAddress0, nAddress1, nType)) {
            return false;
        }

        nAddressVirtual0 = nAddress0 | 0xA0000000;
        nAddressVirtual1 = nAddress1 | 0xA0000000;
        iAddress = nAddressVirtual0 >> 16;
        while (nAddressVirtual0 < nAddressVirtual1) {
            pCPU->aiDevice[iAddress] = iDevice;
            nAddressVirtual0 += 0x10000;
            iAddress++;
        }
    }

    return true;
}

/**
 * @brief Sets load handlers for a device.
 *
 * @param pCPU The emulated VR4300.
 * @param pDevice The device which handles the load operations.
 * @param pfGet8 byte handler.
 * @param pfGet16 halfword handler.
 * @param pfGet32 word handler.
 * @param pfGet64 doubleword handler.
 * @return bool true on success, false otherwise.
 */
bool cpuSetDeviceGet(Cpu* pCPU, CpuDevice* pDevice, Get8Func pfGet8, Get16Func pfGet16, Get32Func pfGet32,
                     Get64Func pfGet64) {
    pDevice->pfGet8 = pfGet8;
    pDevice->pfGet16 = pfGet16;
    pDevice->pfGet32 = pfGet32;
    pDevice->pfGet64 = pfGet64;
    return true;
}

/**
 * @brief Sets store handlers for a device.
 *
 * @param pCPU The emulated VR4300.
 * @param pDevice The device which handles the store operations.
 * @param pfPut8 byte handler.
 * @param pfPut16 halfword handler.
 * @param pfPut32 word handler.
 * @param pfPut64 doubleword handler.
 * @return bool true on success, false otherwise.
 */
bool cpuSetDevicePut(Cpu* pCPU, CpuDevice* pDevice, Put8Func pfPut8, Put16Func pfPut16, Put32Func pfPut32,
                     Put64Func pfPut64) {
    pDevice->pfPut8 = pfPut8;
    pDevice->pfPut16 = pfPut16;
    pDevice->pfPut32 = pfPut32;
    pDevice->pfPut64 = pfPut64;
    return true;
}

bool cpuSetCodeHack(Cpu* pCPU, s32 nAddress, s32 nOpcodeOld, s32 nOpcodeNew) {
    s32 iHack;

    for (iHack = 0; iHack < pCPU->nCountCodeHack; iHack++) {
        if (pCPU->aCodeHack[iHack].nAddress == nAddress) {
            return false;
        }
    }

    pCPU->aCodeHack[iHack].nAddress = nAddress;
    pCPU->aCodeHack[iHack].nOpcodeOld = nOpcodeOld;
    pCPU->aCodeHack[iHack].nOpcodeNew = nOpcodeNew;
    pCPU->nCountCodeHack++;
    return true;
}

bool cpuReset(Cpu* pCPU) {
    s32 iRegister;
    s32 iTLB;
    s32 i;

    pCPU->nTick = 0;
    pCPU->nCountCodeHack = 0;
    pCPU->nMode = 0x40;
    pCPU->pfStep = NULL;

    for (iTLB = 0; iTLB < ARRAY_COUNT(pCPU->aTLB); iTLB++) {
        for (iRegister = 0; iRegister < 5; iRegister++) {
            pCPU->aTLB[iTLB][iRegister] = 0;
        }
        pCPU->aTLB[iTLB][4] = -1;
    }

    pCPU->nLo = 0;
    pCPU->nHi = 0;
    pCPU->nPC = 0x80000400;
    pCPU->nWaitPC = -1;

    for (iRegister = 0; iRegister < ARRAY_COUNT(pCPU->aGPR); iRegister++) {
        pCPU->aGPR[iRegister].u64 = 0;
    }

    for (iRegister = 0; iRegister < ARRAY_COUNT(pCPU->aFPR); iRegister++) {
        pCPU->aFPR[iRegister].f64 = 0.0;
    }

    for (iRegister = 0; iRegister < ARRAY_COUNT(pCPU->anFCR); iRegister++) {
        pCPU->anFCR[iRegister] = 0;
    }

    pCPU->aGPR[20].u64 = 1;
    pCPU->aGPR[22].u64 = 0x3F;
    pCPU->aGPR[29].u64 = 0xA4001FF0;

    for (iRegister = 0; iRegister < ARRAY_COUNT(pCPU->anCP0); iRegister++) {
        pCPU->anCP0[iRegister] = 0;
    }

    pCPU->anCP0[15] = 0xB00;
    pCPU->anCP0[9] = 0x10000000;
    cpuSetCP0_Status(pCPU, 0x2000FF01, 1);
    pCPU->anCP0[16] = 0x6E463;

    pCPU->nCountAddress = 0;
    if (cpuHackHandler(pCPU)) {
        pCPU->nMode |= 0x10;
    }

    if (!cpuHeapReset(pCPU->aHeap1Flag, ARRAY_COUNT(pCPU->aHeap1Flag))) {
        return false;
    }
    if (pCPU->gHeap1 == NULL) {
        if (!xlHeapTake(&pCPU->gHeap1, 0x300000 | 0x30000000)) {
            return false;
        }
    }

    if (!cpuHeapReset(pCPU->aHeap2Flag, ARRAY_COUNT(pCPU->aHeap2Flag))) {
        return false;
    }
    if (pCPU->gHeap2 == NULL) {
        if (!xlHeapTake(&pCPU->gHeap2, 0x104000 | 0x30000000)) {
            return false;
        }
    }

    if (!cpuHeapReset(aHeapTreeFlag, ARRAY_COUNT(aHeapTreeFlag))) {
        return false;
    }
    if (gHeapTree == NULL) {
        if (!xlHeapTake(&gHeapTree, 0x46500 | 0x30000000)) {
            return false;
        }
    }

    if (pCPU->gTree != NULL) {
        treeKill(pCPU);
    }

    pCPU->nCompileFlag = 1;

#if IS_MM
    gRegCount = 0;

    for (i = 0; i < ARRAY_COUNT(gRegList); i++) {
        gRegList[i] = 0;
    }
#endif

    return true;
}

bool cpuSetXPC(Cpu* pCPU, s64 nPC, s64 nLo, s64 nHi) {
    if (!xlObjectTest(pCPU, &gClassCPU)) {
        return false;
    }

    pCPU->nMode |= 4;
    pCPU->nPC = nPC;
    pCPU->nLo = nLo;
    pCPU->nHi = nHi;

    return true;
}

static inline bool cpuInitAllDevices(Cpu* pCPU) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(pCPU->apDevice); i++) {
        pCPU->apDevice[i] = NULL;
    }

    return true;
}

static inline bool cpuFreeAllDevices(Cpu* pCPU) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(pCPU->apDevice); i++) {
        if (pCPU->apDevice[i] != NULL) {
            if (!cpuFreeDevice(pCPU, i)) {
                return false;
            }
        } else {
            pCPU->apDevice[i] = NULL;
        }
    }

    return true;
}

bool cpuEvent(Cpu* pCPU, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pCPU->pHost = pArgument;
            cpuInitAllDevices(pCPU);
            if (!cpuReset(pCPU)) {
                return false;
            }
            break;
        case 3:
            if (!cpuFreeAllDevices(pCPU)) {
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

bool cpuGetAddressOffset(Cpu* pCPU, s32* pnOffset, u32 nAddress) {
    s32 iDevice;

    if (0x80000000 <= nAddress && nAddress < 0xC0000000) {
        *pnOffset = nAddress & 0x7FFFFF;
    } else {
        iDevice = pCPU->aiDevice[nAddress >> 0x10];

        if (pCPU->apDevice[iDevice]->nType & 0x100) {
            *pnOffset = (nAddress + pCPU->apDevice[iDevice]->nOffsetAddress) & 0x7FFFFF;
        } else {
            return false;
        }
    }

    return true;
}

bool cpuGetAddressBuffer(Cpu* pCPU, void** ppBuffer, u32 nAddress) {
    CpuDevice* pDevice = pCPU->apDevice[pCPU->aiDevice[nAddress >> 0x10]];

    if ((Ram*)pDevice->pObject == SYSTEM_RAM(pCPU->pHost)) {
        if (!ramGetBuffer(SYSTEM_RAM(pCPU->pHost), ppBuffer, nAddress + pDevice->nOffsetAddress, NULL)) {
            return false;
        }
        return true;
    }

    return false;
}

bool cpuGetOffsetAddress(Cpu* pCPU, u32* anAddress, s32* pnCount, u32 nOffset, u32 nSize) {
    s32 iEntry;
    s32 iAddress = 0;
    u32 nAddress;
    u32 nMask;
    u32 nSizeMapped;

    anAddress[iAddress++] = nOffset | 0x80000000;
    anAddress[iAddress++] = nOffset | 0xA0000000;

    for (iEntry = 0; iEntry < ARRAY_COUNT(pCPU->aTLB); iEntry++) {
        if (pCPU->aTLB[iEntry][0] & 2) {
            nMask = pCPU->aTLB[iEntry][3] | 0x1FFF;

            switch (nMask) {
                case 0x1FFF:
                    nSizeMapped = 4 * 1024;
                    break;
                case 0x7FFF:
                    nSizeMapped = 16 * 1024;
                    break;
                case 0x1FFFF:
                    nSizeMapped = 64 * 1024;
                    break;
                case 0x7FFFF:
                    nSizeMapped = 256 * 1024;
                    break;
                case 0x1FFFFF:
                    nSizeMapped = 1 * 1024 * 1024;
                    break;
                case 0x7FFFFF:
                    nSizeMapped = 4 * 1024 * 1024;
                    break;
                case 0x1FFFFFF:
                    nSizeMapped = 16 * 1024 * 1024;
                    break;
                default:
                    return false;
            }

            nAddress = ((u32)(pCPU->aTLB[iEntry][0] & ~0x3F) << 6) + (nOffset & nMask);
            if (nAddress < (nOffset + nSize - 1) && (nAddress + nSizeMapped - 1) >= nOffset) {
                nAddress = pCPU->aTLB[iEntry][2] & 0xFFFFE000;
                anAddress[iAddress++] = ((nAddress) & ~nMask) | (nOffset & nMask);
            }
        }
    }

    *pnCount = iAddress;
    return true;
}

bool cpuInvalidateCache(Cpu* pCPU, s32 nAddress0, s32 nAddress1) {
    if ((nAddress0 & 0xF0000000) == 0xA0000000) {
        return true;
    }

    if (!cpuFreeCachedAddress(pCPU, nAddress0, nAddress1)) {
        return false;
    }

    cpuDMAUpdateFunction(pCPU, nAddress0, nAddress1);
    return true;
}

bool cpuGetFunctionChecksum(Cpu* pCPU, u32* pnChecksum, CpuFunction* pFunction) {
    s32 nSize;
    u32* pnBuffer;
    u32 nChecksum;
    u32 nData;
    u32 pad;

    if (pFunction->nChecksum != 0) {
        *pnChecksum = pFunction->nChecksum;
        return true;
    }

    if (!cpuGetAddressBuffer(pCPU, (void**)&pnBuffer, pFunction->nAddress0)) {
        return false;
    }

    nChecksum = 0;
    nSize = ((pFunction->nAddress1 - pFunction->nAddress0) >> 2) + 1;

    while (nSize > 0) {
        nSize--;
        nData = *pnBuffer;
        nData = nData >> 0x1A;
        nData = nData << ((nSize % 5) * 6);
        nChecksum += nData;
        pnBuffer++;
    }

    *pnChecksum = nChecksum;
    pFunction->nChecksum = nChecksum;

    return true;
}

static bool cpuHeapReset(u32* array, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        array[i] = 0;
    }

    NO_INLINE();
    return true;
}

bool cpuHeapTake(void* heap, Cpu* pCPU, CpuFunction* pFunction, int memory_size) {
    s32 done;
    s32 second;
    u32* anPack;
    s32 nPackCount;
    int nBlockCount;
    s32 nOffset;
    s32 nCount;
    s32 iPack;
    u32 nPack;
    u32 nMask;
    u32 nMask0;

    done = 0;
    second = 0;
    for (;;) {
        if (pFunction->heapID == -1) {
            if (memory_size > 0x3200) {
                pFunction->heapID = 2;
            } else {
                pFunction->heapID = 1;
            }
        } else if (pFunction->heapID == 1) {
            pFunction->heapID = 2;
            second = 1;
        } else if (pFunction->heapID == 2) {
            pFunction->heapID = 1;
            second = 1;
        }

        if (pFunction->heapID == 1) {
            pFunction->heapID = 1;
            nBlockCount = (memory_size + 0x1FF) / 0x200;
            nPackCount = ARRAY_COUNT(pCPU->aHeap1Flag);
            anPack = pCPU->aHeap1Flag;

            if (second && nBlockCount >= 32) {
                pFunction->heapID = 3;
                pFunction->heapWhere = -1;
                if (!xlHeapTake(heap, memory_size)) {
                    return false;
                }
                return true;
            }
        } else if (pFunction->heapID == 2) {
            pFunction->heapID = 2;
            nBlockCount = (memory_size + 0x9FF) / 0xA00;
            nPackCount = ARRAY_COUNT(pCPU->aHeap2Flag);
            anPack = pCPU->aHeap2Flag;
        }

        if (nBlockCount >= 32) {
            pFunction->heapID = 3;
            pFunction->heapWhere = -1;
            if (!xlHeapTake(heap, memory_size)) {
                return false;
            }
            return true;
        }

        nCount = 33 - nBlockCount;
        nMask0 = (1 << nBlockCount) - 1;
        for (iPack = 0; iPack < nPackCount; iPack++) {
            if ((nPack = anPack[iPack]) != -1) {
                nMask = nMask0;
                nOffset = nCount;
                do {
                    if (!(nPack & nMask)) {
                        anPack[iPack] |= nMask;
                        pFunction->heapWhere = (nBlockCount << 16) | ((iPack << 5) + (nCount - nOffset));
                        done = 1;
                        break;
                    }
                    nMask = nMask << 1;
                    nOffset--;
                } while (nOffset != 0);
            }

            if (done) {
                break;
            }
        }

        if (done) {
            break;
        }

        if (second) {
            pFunction->heapID = -1;
            pFunction->heapWhere = -1;
            return false;
        }
    }

    if (pFunction->heapID == 1) {
        *((s32*)heap) = (s32)pCPU->gHeap1 + (pFunction->heapWhere & 0xFFFF) * 0x200;
    } else {
        *((s32*)heap) = (s32)pCPU->gHeap2 + (pFunction->heapWhere & 0xFFFF) * 0xA00;
    }

    return true;
}

bool cpuHeapFree(Cpu* pCPU, CpuFunction* pFunction) {
    u32* anPack;
    s32 iPack;
    u32 nMask;

    if (pFunction->heapID == 1) {
        anPack = pCPU->aHeap1Flag;
    } else if (pFunction->heapID == 2) {
        anPack = pCPU->aHeap2Flag;
    } else {
        if (pFunction->pnBase != NULL) {
            if (!xlHeapFree(&pFunction->pnBase)) {
                return false;
            }
        } else {
            if (!xlHeapFree(&pFunction->pfCode)) {
                return false;
            }
        }

        return true;
    }

    if (pFunction->heapWhere == -1) {
        return false;
    }

    nMask = ((1 << (pFunction->heapWhere >> 16)) - 1) << (pFunction->heapWhere & 0x1F);
    iPack = ((pFunction->heapWhere & 0xFFFF) >> 5);

    if ((anPack[iPack] & nMask) == nMask) {
        anPack[iPack] &= ~nMask;
        pFunction->heapID = -1;
        pFunction->heapWhere = -1;
        return true;
    }

    return false;
}

static bool cpuTreeTake(void* heap, s32* where, s32 size) {
    bool done;
    s32 nOffset;
    s32 nCount;
    s32 iPack;
    u32 nPack;
    u32 nMask;
    u32 nMask0;

    done = false;
    for (iPack = 0; iPack < 125; iPack++) {
        if ((nPack = aHeapTreeFlag[iPack]) != -1) {
            nMask = 1;
            nOffset = 32;
            do {
                if (!(nPack & nMask)) {
                    aHeapTreeFlag[iPack] |= nMask;
                    *where = (1 << 16) | ((iPack << 5) + (32 - nOffset));
                    done = true;
                    break;
                }
                nMask = nMask << 1;
                nOffset--;
            } while (nOffset != 0);
        }

        if (done) {
            break;
        }
    }

    if (!done) {
        *where = -1;
        return false;
    }

    *((s32*)heap) = (s32)gHeapTree + ((*where & 0xFFFF) * sizeof(CpuFunction));

    return true;
}

static inline bool cpuTreeFree(CpuFunction* pFunction) {
    u32* anPack;
    s32 iPack;
    u32 nMask;

    if (pFunction->treeheapWhere == -1) {
        return false;
    }

    anPack = aHeapTreeFlag;
    nMask = ((1 << (pFunction->treeheapWhere >> 16)) - 1) << (pFunction->treeheapWhere & 0x1F);
    iPack = (pFunction->treeheapWhere & 0xFFFF) >> 5;
    if ((anPack[iPack] & nMask) == nMask) {
        anPack[iPack] &= ~nMask;
        return true;
    }

    return false;
}

bool cpuFindFunction(Cpu* pCPU, s32 theAddress, CpuFunction** tree_node) {
    CpuDevice** apDevice;
    u8* aiDevice;
    u32 opcode;
    u8 follow;
    u8 valid;
    u8 check;
    u8 end_flag;
    u8 save_restore;
    u8 alert;
    s32 beginAddress;
    s32 cheat_address;
    s32 current_address;
    s32 temp_address;
    s32 branch;
    int anAddr[3];
    s32 pad;

    save_restore = false;
    alert = false;
    cheat_address = 0;
    if (pCPU->gTree == NULL) {
        check = 0;
        pCPU->survivalTimer = 1;
        if (!xlHeapTake((void**)&pCPU->gTree, sizeof(CpuTreeRoot))) {
            return false;
        }
        treeInit(pCPU, 0x80150002);
    } else {
        check = 1;
        if (treeSearch(pCPU, theAddress, tree_node)) {
            pCPU->pFunctionLast = *tree_node;
            return true;
        }
    }

    anAddr[0] = 0;
    anAddr[1] = 0;
    anAddr[2] = 0;
    aiDevice = pCPU->aiDevice;
    apDevice = pCPU->apDevice;
    beginAddress = branch = theAddress;
    current_address = theAddress;

    do {
        CPU_DEVICE_GET32(apDevice, aiDevice, current_address, &opcode);
        follow = true;

        if (check == 0) {
            if (opcode != 0 && anAddr[0] == 0) {
                anAddr[0] = current_address;
            }
        } else {
            if (anAddr[0] == 0) {
                anAddr[0] = current_address;
            }
        }

        valid = true;
        end_flag = 0;

        switch ((u8)MIPS_OP(opcode)) {
            case 0x00: { // special
                switch ((u8)MIPS_FUNCT(opcode)) {
                    case 0x08: // jr
                        if (!save_restore && (anAddr[1] == 0 || current_address > anAddr[1]) &&
                            (anAddr[2] == 0 || current_address >= anAddr[2])) {
                            end_flag = 111;
                        }
                        break;
                    case 0x0D: // break
                        if ((anAddr[1] == 0 || current_address > anAddr[1]) &&
                            (anAddr[2] == 0 || current_address >= anAddr[2])) {
                            end_flag = 111;
                            save_restore = false;
                        }
                        break;
                    default:
                        valid = SpecialOpcode[MIPS_FUNCT(opcode)];
                        break;
                }
                break;
            }
            case 0x02: // j
                if ((branch = (MIPS_TARGET(opcode) << 2) | (current_address & 0xF0000000)) >= current_address &&
                    branch - current_address <= 0x1000) {
                    if (anAddr[2] == 0) {
                        anAddr[2] = branch;
                    } else if (branch > anAddr[2]) {
                        anAddr[2] = branch;
                    }
                }
                break;
            case 0x01: // regimm
                switch ((u8)MIPS_RT(opcode)) {
                    case 0x00: // bltz
                    case 0x01: // bgez
                    case 0x02: // bltzl
                    case 0x03: // bgezl
                    case 0x10: // bltzal
                    case 0x11: // bgezal
                    case 0x12: // bltzall
                    case 0x13: // bgezall
                        branch = MIPS_IMM_S16(opcode) * 4;
                        if (branch < 0) {
                            if (check == 1 && current_address + branch + 4 < beginAddress) {
                                anAddr[0] = 0;
                                anAddr[1] = 0;
                                anAddr[2] = 0;
                                beginAddress = current_address + branch + 4;
                                current_address = current_address + branch + 4;
                                alert = true;
                                continue;
                            }
                        } else {
                            if (anAddr[1] == 0) {
                                anAddr[1] = current_address + branch;
                            } else if (current_address + branch > anAddr[1]) {
                                anAddr[1] = current_address + branch;
                            }
                        }
                        break;
                    default:
                        valid = RegimmOpcode[MIPS_RT(opcode)];
                        break;
                }
                break;
            case 0x04: // beq
            case 0x14: // beql
                branch = MIPS_IMM_S16(opcode) * 4;
                if (branch < 0) {
                    if (check == 1 && current_address + branch + 4 < beginAddress) {
                        anAddr[0] = 0;
                        anAddr[1] = 0;
                        anAddr[2] = 0;
                        beginAddress = current_address + branch + 4;
                        current_address = current_address + branch + 4;
                        alert = true;
                        continue;
                    }

                    temp_address = current_address + 8;
                    CPU_DEVICE_GET32(apDevice, aiDevice, temp_address, &opcode);
                    if (opcode == 0) {
                        do {
                            temp_address += 4;
                            CPU_DEVICE_GET32(apDevice, aiDevice, temp_address, &opcode);
                        } while (opcode == 0);

                        if (MIPS_OP(opcode) != 0x23) { // lw
                            current_address = temp_address - 8;
                            if ((anAddr[1] == 0 || current_address > anAddr[1]) &&
                                (anAddr[2] == 0 || current_address >= anAddr[2])) {
                                end_flag = 111;
                                save_restore = false;
                            }
                        } else {
                            current_address = temp_address - 4;
                        }
                    }
                } else {
                    if (anAddr[1] == 0) {
                        anAddr[1] = current_address + branch;
                    } else if (current_address + branch > anAddr[1]) {
                        anAddr[1] = current_address + branch;
                    }
                }
                break;
            case 0x05: // bne
            case 0x06: // blez
            case 0x07: // bgtz
            case 0x15: // bnel
            case 0x16: // blezl
            case 0x17: // bgtzl
                branch = MIPS_IMM_S16(opcode) * 4;
                if (branch < 0) {
                    if (check == 1 && current_address + branch + 4 < beginAddress) {
                        anAddr[0] = 0;
                        anAddr[1] = 0;
                        anAddr[2] = 0;
                        beginAddress = current_address + branch + 4;
                        current_address = current_address + branch + 4;
                        alert = true;
                        continue;
                    }
                } else {
                    if (anAddr[1] == 0) {
                        anAddr[1] = current_address + branch;
                    } else if (current_address + branch > anAddr[1]) {
                        anAddr[1] = current_address + branch;
                    }
                }
                break;
            case 0x10: // cop0
                switch ((u8)MIPS_FUNCT(opcode)) {
                    case 0x01: // tlbr
                    case 0x02: // tlbwi
                    case 0x05: // tlbwr
                    case 0x08: // tlbp
                        break;
                    case 0x18: // eret
                        if ((anAddr[1] == 0 || current_address > anAddr[1]) &&
                            (anAddr[2] == 0 || current_address >= anAddr[2])) {
                            end_flag = 222;
                            save_restore = false;
                        }
                        break;
                    default:
                        switch ((u8)MIPS_FMT(opcode)) {
                            case 0x08:
                                switch (MIPS_FT(opcode)) {
                                    case 0x00:
                                    case 0x01:
                                    case 0x02:
                                    case 0x03:
                                        branch = MIPS_IMM_S16(opcode) * 4;
                                        if (branch < 0) {
                                            if (check == 1 && current_address + branch + 4 < beginAddress) {
                                                anAddr[0] = 0;
                                                anAddr[1] = 0;
                                                anAddr[2] = 0;
                                                beginAddress = current_address + branch + 4;
                                                current_address = current_address + branch + 4;
                                                alert = true;
                                                continue;
                                            }
                                        } else {
                                            if (anAddr[1] == 0) {
                                                anAddr[1] = current_address + branch;
                                            } else if (current_address + branch > anAddr[1]) {
                                                anAddr[1] = current_address + branch;
                                            }
                                        }
                                        break;
                                }
                                break;
                        }
                        break;
                }
                break;
            case 0x11: // cop1
                if (MIPS_FMT(opcode) == 0x08) {
                    switch ((u8)MIPS_FT(opcode)) {
                        case 0x00:
                        case 0x01:
                        case 0x02:
                        case 0x03:
                            branch = MIPS_IMM_S16(opcode) * 4;
                            if (branch < 0) {
                                if (check == 1 && current_address + branch + 4 < beginAddress) {
                                    anAddr[0] = 0;
                                    anAddr[1] = 0;
                                    anAddr[2] = 0;
                                    beginAddress = current_address + branch + 4;
                                    current_address = current_address + branch + 4;
                                    alert = true;
                                    continue;
                                }
                            } else {
                                if (anAddr[1] == 0) {
                                    anAddr[1] = current_address + branch;
                                } else if (current_address + branch > anAddr[1]) {
                                    anAddr[1] = current_address + branch;
                                }
                            }
                            break;
                    }
                }
                break;
            case 0x2B: // sw
                if (MIPS_RT(opcode) == 31) {
                    save_restore = true;
                }
                break;
            case 0x23: // lw
                if (MIPS_RT(opcode) == 31) {
                    save_restore = false;
                    if (check == 1 && alert) {
                        current_address = beginAddress;

                        while (true) {
                            CPU_DEVICE_GET32(apDevice, aiDevice, current_address, &opcode);
                            if (MIPS_OP(opcode) == 0x2B && MIPS_RT(opcode) == 31) { // sw ra, ...
                                break;
                            }
                            current_address -= 4;
                        }

                        do {
                            current_address -= 4;
                            CPU_DEVICE_GET32(apDevice, aiDevice, current_address, &opcode);
                            if (opcode != 0 && treeSearch(pCPU, current_address - 4, tree_node)) {
                                break;
                            }
                        } while (opcode != 0);

                        anAddr[0] = 0;
                        anAddr[1] = 0;
                        anAddr[2] = 0;
                        current_address = beginAddress = current_address + 4;
                        alert = false;
                        continue;
                    }
                }
                break;
            default:
                valid = Opcode[MIPS_OP(opcode)];
                break;
        }

        if (end_flag != 0) {
            if (end_flag == 111) {
                anAddr[2] = current_address + 4;
                current_address += 8;
            } else {
                anAddr[2] = current_address;
                current_address += 4;
            }

            if (check == 0) {
                if (romTestCode(SYSTEM_ROM(pCPU->pHost), "CFZE")) {
                    if (current_address == 0x800BB62C) {
                        current_address = 0x800BB9B0;
                    } else if (current_address == 0x800CC010) {
                        valid = false;
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), "NYLJ")) {
                    if (anAddr[2] == 0x800A9D40) {
                        anAddr[0] = 0x800A9CF0;
                        cheat_address = anAddr[0];
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), "NM3E")) {
                    if (current_address == 0x80000470) {
                        current_address = 0x80000870;
                    } else if (anAddr[2] == 0x80001248) {
                        anAddr[2] = 0x80001884;
                        current_address = 0x80001890;
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), "CLBE")) {
                    if (current_address == 0x800829CC) {
                        current_address = 0x80082D60;
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), "NN6J")) {
                    if (current_address == 0x8000E1C8) {
                        if (!treeInsert(pCPU, 0x8007ED94, 0x8007F55C)) {
                            return false;
                        }
                        treeSearch(pCPU, 0x8007ED94, tree_node);
                        (*tree_node)->timeToLive = 0;
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), "NN6E")) {
                    if (current_address == 0x8000E1C8) {
                        if (!treeInsert(pCPU, 0x8007EC54, 0x8007F41C)) {
                            return false;
                        }
                        treeSearch(pCPU, 0x8007EC54, tree_node);
                        (*tree_node)->timeToLive = 0;
                    }
                }
            }

            if (!treeInsert(pCPU, anAddr[0], anAddr[2])) {
                return false;
            }

            if (cheat_address != 0) {
                treeSearch(pCPU, cheat_address, tree_node);
                cheat_address = 0;
                (*tree_node)->timeToLive = 0;
            }

            if (check == 1) {
                if (treeSearch(pCPU, theAddress, tree_node)) {
                    pCPU->pFunctionLast = *tree_node;
                    return true;
                } else {
                    return false;
                }
            }

            follow = false;
            anAddr[0] = 0;
            anAddr[1] = 0;
            anAddr[2] = 0;
            if (check == 0 && pCPU->gTree->total > 3970) {
                valid = false;
            }
        }

        if (follow) {
            current_address += 4;
        }
    } while (valid);

    if (check == 0) {
        treeInsert(pCPU, 0x80000180, 0x8000018C);
        treeSearch(pCPU, 0x80000180, tree_node);
        (*tree_node)->timeToLive = 0;

        if (treeSearch(pCPU, theAddress, tree_node)) {
            pCPU->pFunctionLast = *tree_node;
            return true;
        } else {
            return false;
        }
    }

    return false;
}

static bool cpuDMAUpdateFunction(Cpu* pCPU, s32 start, s32 end) {
    CpuTreeRoot* root = pCPU->gTree;
    s32 count;
    bool cancel;

    if (root == NULL) {
        return true;
    }

    if ((start < root->root_address) && (end > root->root_address)) {
        treeAdjustRoot(pCPU, start, end);
    }

    if (root->kill_limit != 0) {
        if (root->restore != NULL) {
            cancel = false;
            if (start <= root->restore->nAddress0) {
                if ((end >= root->restore->nAddress1) || (end >= root->restore->nAddress0)) {
                    cancel = true;
                }
            } else {
                if ((end >= root->restore->nAddress1) &&
                    ((start <= root->restore->nAddress0) || (start <= root->restore->nAddress1))) {
                    cancel = true;
                }
            }
            if (cancel) {
                root->restore = NULL;
                root->restore_side = 0;
            }
        }
    }

    if (start < root->root_address) {
        do {
            count = treeKillRange(pCPU, root->left, start, end);
            root->total = root->total - count;
        } while (count != 0);
    } else {
        do {
            count = treeKillRange(pCPU, root->right, start, end);
            root->total = root->total - count;
        } while (count != 0);
    }

    return true;
}

static inline void treeCallerInit(CpuCallerID* block, s32 total) {
    s32 count;

    for (count = 0; count < total; count++) {
        block[count].N64address = 0;
        block[count].GCNaddress = 0;
    }
}

static inline bool treeCallerKill(Cpu* pCPU, CpuFunction* kill) {
    s32 left;
    s32 right;
    CpuTreeRoot* root;

    if (kill->pfCode != NULL) {
        root = pCPU->gTree;
        left = kill->nAddress0;
        right = kill->nAddress1;

        if (root->left != NULL) {
            treePrintNode(pCPU, root->left, 0x10, &left, &right);
        }
        if (root->right != NULL) {
            treePrintNode(pCPU, root->right, 0x10, &left, &right);
        }
    }

    pCPU->gTree->total_memory -= kill->memory_size + sizeof(CpuFunction);
    return true;
}

static bool treeCallerCheck(Cpu* pCPU, CpuFunction* tree, bool flag, s32 nAddress0, s32 nAddress1) {
    s32 count;
    s32 saveGCN;
    s32 saveN64;
    s32* addr_function;
    s32* addr_call;
    s32 pad;

    if (tree->callerID_total == 0) {
        return false;
    }

    if (tree->block != NULL) {
        CpuCallerID* block = tree->block;

        for (count = 0; count < tree->callerID_total; count++) {
            saveN64 = block[count].N64address;
            saveGCN = block[count].GCNaddress;
            if (saveN64 >= nAddress0 && saveN64 <= nAddress1 && saveGCN != 0) {
                addr_function = (s32*)saveGCN;
                addr_call = addr_function - (flag ? 3 : 2);

                addr_call[0] = 0x3CA00000 | ((u32)saveN64 >> 16);
                addr_call[1] = 0x60A50000 | ((u32)saveN64 & 0xFFFF);
                addr_function[0] = 0x48000000 | (((u32)pCPU->pfCall - saveGCN) & 0x03FFFFFC) | 1;

                block[count].GCNaddress = 0;
                DCStoreRange(addr_call, 16);
                ICInvalidateRange(addr_call, 16);
            }
        }
    }

    return true;
}

static bool treeInit(Cpu* pCPU, s32 root_address) {
    CpuTreeRoot* root = pCPU->gTree;

    if (root == NULL) {
        return false;
    }

    root->total = 0;
    root->total_memory = 0;
    root->root_address = root_address;
    root->start_range = 0;
    root->end_range = 0x80000000;
    root->left = NULL;
    root->right = NULL;
    root->kill_limit = 0;
    root->kill_number = 0;
    root->side = 0;
    root->restore = NULL;
    root->restore_side = 0;
    return true;
}

static bool treeInitNode(CpuFunction** tree, CpuFunction* prev, s32 start, s32 end) {
    CpuFunction* node;
    s32 where;

    if (!cpuTreeTake(&node, &where, sizeof(CpuFunction))) {
        return false;
    }

    node->nAddress0 = start;
    node->nAddress1 = end;
    node->block = NULL;
    node->callerID_total = 0;
    node->callerID_flag = 0x21;
    node->pnBase = NULL;
    node->pfCode = NULL;
    node->nCountJump = 0;
    node->aJump = NULL;
    node->nChecksum = 0;
    node->timeToLive = 1;
    node->memory_size = 0;
    node->heapID = -1;
    node->heapWhere = -1;
    node->treeheapWhere = where;
    node->prev = prev;
    node->left = NULL;
    node->right = NULL;

    *tree = node;
    return true;
}

static bool treeKill(Cpu* pCPU) {
    CpuTreeRoot* root;
    s32 count;

    count = 0;
    root = pCPU->gTree;
    if (root->left != NULL) {
        count += treeKillNodes(pCPU, root->left);
        treeCallerKill(pCPU, root->left);
        if (root->left->pfCode != NULL) {
            cpuHeapFree(pCPU, root->left);
        }
        if (!cpuTreeFree(root->left)) {
            return false;
        }
        PAD_STACK();
        PAD_STACK();

        count++;
    }

    if (root->right != NULL) {
        count += treeKillNodes(pCPU, root->right);
        treeCallerKill(pCPU, root->right);
        if (root->right->pfCode != NULL) {
            cpuHeapFree(pCPU, root->right);
        }
        if (!cpuTreeFree(root->right)) {
            return false;
        }
        PAD_STACK();
        PAD_STACK();

        count++;
    }

    root->total -= count;
    if (!xlHeapFree((void**)&pCPU->gTree)) {
        return false;
    }

    pCPU->gTree = NULL;
    return true;
}

static bool treeKillNodes(Cpu* pCPU, CpuFunction* tree) {
    CpuFunction* current;
    CpuFunction* kill;
    s32 count;

    count = 0;
    if (tree == NULL) {
        return false;
    }
    current = tree;

    do {
        while (current->left != NULL) {
            current = current->left;
        }

        do {
            if (current->right != NULL) {
                current = current->right;
                break;
            }

            if (current == tree) {
                return count;
            }

            while (current != current->prev->left) {
                kill = current;
                current = current->prev;

                treeCallerKill(pCPU, kill);
                if (kill->pfCode != NULL) {
                    cpuHeapFree(pCPU, kill);
                }

                // TODO: regalloc hacks
                (void)kill->treeheapWhere;
                if (!cpuTreeFree(kill)) {
                    return false;
                }
                PAD_STACK();
                PAD_STACK();

                count += 1;
                if (current == tree) {
                    return count;
                }
            }

            kill = current;
            current = current->prev;

            treeCallerKill(pCPU, kill);
            if (kill->pfCode != NULL) {
                cpuHeapFree(pCPU, kill);
            }
            // TODO: regalloc hacks
            (void)kill->treeheapWhere;
            if (!cpuTreeFree(kill)) {
                return false;
            }
            PAD_STACK();
            PAD_STACK();

            count += 1;
        } while (current != NULL);
    } while (current != NULL);

    return count;
}

static bool treeDeleteNode(Cpu* pCPU, CpuFunction** top, CpuFunction* kill) {
    CpuTreeRoot* root;
    CpuFunction* save1;
    CpuFunction* save2;
    CpuFunction* connect;

    root = pCPU->gTree;
    if (kill == NULL) {
        return false;
    }

    root->total--;
    connect = kill->prev;
    save1 = kill->left;
    save2 = kill->right;

    if (connect != NULL) {
        if (save1 != NULL) {
            if (connect->left == kill) {
                connect->left = save1;
            } else {
                connect->right = save1;
            }
            save1->prev = connect;
            if (save2 != NULL) {
                while (save1->right != NULL) {
                    save1 = save1->right;
                }
                save1->right = save2;
                save2->prev = save1;
            }
        } else if (save2 != NULL) {
            if (connect->left == kill) {
                connect->left = save2;
            } else {
                connect->right = save2;
            }
            save2->prev = connect;
        } else if (connect->left == kill) {
            connect->left = NULL;
        } else {
            connect->right = NULL;
        }
    } else if (save1 != NULL) {
        *top = save1;
        if (root->left == kill) {
            root->left = save1;
        } else {
            root->right = save1;
        }
        save1->prev = NULL;
        if (save2 != NULL) {
            while (save1->right != NULL) {
                save1 = save1->right;
            }
            save1->right = save2;
            save2->prev = save1;
        }
    } else if (save2 != NULL) {
        *top = save2;
        if (root->left == kill) {
            root->left = save2;
        } else {
            root->right = save2;
        }
        save2->prev = NULL;
    } else {
        *top = NULL;
        if (root->left == kill) {
            root->left = NULL;
        } else {
            root->right = NULL;
        }
    }

    if (root->start_range == kill->nAddress0) {
        if (save2 != NULL) {
            while (save2->left != NULL) {
                save2 = save2->left;
            }
            root->start_range = save2->nAddress0;
        } else if (connect != NULL) {
            root->start_range = connect->nAddress0;
        } else {
            root->start_range = root->root_address;
        }
    }

    if (root->end_range == kill->nAddress1) {
        if (save1 != NULL) {
            while (save1->right != NULL) {
                save1 = save1->right;
            }
            root->end_range = save1->nAddress1;
        } else if (connect != NULL) {
            root->end_range = connect->nAddress1;
        } else {
            root->end_range = root->root_address;
        }
    }

    treeCallerKill(pCPU, kill);
    if (kill->pfCode != NULL) {
        cpuHeapFree(pCPU, kill);
    }
    // TODO: regalloc hacks
    (void)kill->treeheapWhere;
    if (!cpuTreeFree(kill)) {
        return false;
    }
    PAD_STACK();
    PAD_STACK();

    return true;
}

bool treeInsert(Cpu* pCPU, s32 start, s32 end) {
    CpuTreeRoot* root;
    CpuFunction* current;
    s32 flag;

    root = pCPU->gTree;
    if (root == NULL) {
        return false;
    }
    if (start < root->root_address && end > root->root_address) {
        treeAdjustRoot(pCPU, start, end);
    }
    root->total++;
    root->total_memory += sizeof(CpuFunction);
    if (start != 0x80000180) {
        if (start < root->start_range) {
            root->start_range = start;
        }
        if (end > root->end_range) {
            root->end_range = end;
        }
    }
    if (start < root->root_address) {
        flag = treeInsertNode(&root->left, start, end, &current);
    } else if (start > root->root_address) {
        flag = treeInsertNode(&root->right, start, end, &current);
    } else {
        return false;
    }

    if (flag != 0) {
        return treeBalance(root);
    }
    return false;
}

static bool treeInsertNode(CpuFunction** tree, s32 start, s32 end, CpuFunction** ppFunction) {
    CpuFunction** current;
    CpuFunction* prev;

    current = tree;
    if (*tree == NULL) {
        if (treeInitNode(current, NULL, start, end)) {
            *ppFunction = *current;
            return true;
        }
        return false;
    }

    do {
        if (start < (*current)->nAddress0) {
            prev = *current;
            current = &(*current)->left;
        } else if (start > (*current)->nAddress0) {
            prev = *current;
            current = &(*current)->right;
        } else {
            return false;
        }
    } while (*current != NULL);

    if (treeInitNode(current, prev, start, end)) {
        *ppFunction = *current;
        return true;
    }
    return false;
}

static bool treeBalance(CpuTreeRoot* root) {
    CpuFunction* tree;
    CpuFunction* current;
    CpuFunction* save;
    s32 total;
    s32 count;

    for (total = 0; total < 2; total++) {
        if (total == 0) {
            tree = root->left;
        } else {
            tree = root->right;
        }

        if (tree != NULL) {
            current = tree;
            count = 0;

            while (current->right != NULL) {
                current = current->right;
                count++;
            }

            if (count >= 12) {
                current = tree;
                save = tree->right;
                count = count / 2;

                while (count-- != 0) {
                    current = current->right;
                }

                current->prev->right = NULL;
                tree->right = current;
                current->prev = tree;

                while (current->left != NULL) {
                    current = current->left;
                }

                current->left = save;
                save->prev = current;
            }

            current = tree;
            count = 0;

            while (current->left != NULL) {
                current = current->left;
                count++;
            }

            if (count >= 12) {
                current = tree;
                save = tree->left;
                count = count / 2;

                while (count-- != 0) {
                    current = current->left;
                }

                current->prev->left = NULL;
                tree->left = current;
                current->prev = tree;

                while (current->right != NULL) {
                    current = current->right;
                }

                current->right = save;
                save->prev = current;
            }
        }
    }

    return true;
}

static bool treeAdjustRoot(Cpu* pCPU, s32 new_start, s32 new_end) {
    s32 old_root;
    s32 new_root = new_end + 2;
    s32 kill_start = 0;
    s32 check1 = 0;
    s32 check2 = 0;
    u16 total;
    s32 total_memory;
    s32 address;
    CpuTreeRoot* root = pCPU->gTree;
    CpuFunction* node = NULL;
    CpuFunction* change = NULL;

    old_root = root->root_address;
    total = root->total;
    total_memory = root->total_memory;
    address = old_root + 2;

    do {
        node = NULL;
        treeSearchNode(root->right, address, &node);
        if (node != NULL) {
            if (kill_start == 0) {
                kill_start = address;
            }

            root->root_address = new_root;
            if (!treeInsert(pCPU, node->nAddress0, node->nAddress1)) {
                return false;
            }
            if (!treeSearchNode(root->left, address, &change)) {
                return false;
            }

            change->timeToLive = node->timeToLive;
            change->memory_size = node->memory_size;
            if (node->pfCode != NULL) {
                change->pfCode = node->pfCode;
                node->pfCode = NULL;
            }
            change->nCountJump = node->nCountJump;
            if (node->aJump != NULL) {
                change->aJump = node->aJump;
                node->aJump = NULL;
            }
            change->nChecksum = node->nChecksum;
            change->callerID_flag = node->callerID_flag;
            change->callerID_total = node->callerID_total;
            if (node->callerID_total != 0) {
                change->block = node->block;
                node->block = NULL;
            }

            address = node->nAddress1;
            root->root_address = old_root;
            check2 += treeKillRange(pCPU, root->right, node->nAddress0, node->nAddress1 - 4);
        }

        address += 4;
    } while (address <= new_end);

    root->root_address = new_root;
    root->total = total;
    root->total_memory = total_memory;
    return true;
}

static inline bool treeSearch(Cpu* pCPU, s32 target, CpuFunction** node) {
    CpuTreeRoot* root = pCPU->gTree;
    bool flag;

    if (target < root->root_address) {
        flag = treeSearchNode(root->left, target, node);
    } else {
        flag = treeSearchNode(root->right, target, node);
    }
    return flag;
}

static bool treeSearchNode(CpuFunction* tree, s32 target, CpuFunction** node) {
    CpuFunction* current;

    current = tree;
    if (current == NULL) {
        return false;
    }

    do {
        if (target >= current->nAddress0 && target < current->nAddress1) {
            *node = current;
            return true;
        }
        if (target < current->nAddress0) {
            current = current->left;
        } else if (target > current->nAddress0) {
            current = current->right;
        } else {
            current = NULL;
        }
    } while (current != NULL);

    return false;
}

static bool treeKillRange(Cpu* pCPU, CpuFunction* tree, s32 start, s32 end) {
    CpuTreeRoot* root = pCPU->gTree;
    CpuFunction* node1 = NULL;
    CpuFunction* node2 = NULL;
    CpuFunction* save1;
    CpuFunction* save2;
    CpuFunction* connect;
    bool update = false;
    s32 count = 0;

    if (start < root->start_range && end < root->start_range) {
        return false;
    }
    if (start > root->end_range && end > root->end_range) {
        return false;
    }

    do {
        treeSearchNode(tree, start, &node1);
        if (node1 != NULL) {
            break;
        }
        start += 4;
    } while (start < end);

    if (node1 != NULL) {
        connect = node1->prev;
        node1->prev = NULL;
        save1 = node1->left;
        node1->left = NULL;
        save2 = node1->right;

        while (save2 != NULL) {
            if (save2->nAddress0 < end) {
                if (save2->nAddress1 == root->end_range) {
                    update = true;
                }
                save2 = save2->right;
            } else if (save2 == NULL) {
                break;
            } else {
                save2->prev->right = NULL;
                break;
            }
        }

        if (connect != NULL) {
            if (save1 != NULL) {
                if (connect->left == node1) {
                    connect->left = save1;
                } else {
                    connect->right = save1;
                }
                save1->prev = connect;
                if (save2 != NULL) {
                    while (save1->right != NULL) {
                        save1 = save1->right;
                    }
                    save1->right = save2;
                    save2->prev = save1;
                }
            } else if (save2 != NULL) {
                if (connect->left == node1) {
                    connect->left = save2;
                } else {
                    connect->right = save2;
                }
                save2->prev = connect;
            } else if (connect->left == node1) {
                connect->left = NULL;
            } else {
                connect->right = NULL;
            }
        } else if (save1 != NULL) {
            tree = save1;
            if (root->left == node1) {
                root->left = save1;
            } else {
                root->right = save1;
            }
            save1->prev = NULL;
            if (save2 != NULL) {
                while (save1->right != NULL) {
                    save1 = save1->right;
                }
                save1->right = save2;
                save2->prev = save1;
            }
        } else if (save2 != NULL) {
            tree = save2;
            if (root->left == node1) {
                root->left = save2;
            } else {
                root->right = save2;
            }
            save2->prev = NULL;
        } else {
            tree = NULL;
            if (root->left == node1) {
                root->left = NULL;
            } else {
                root->right = NULL;
            }
        }
        if (root->start_range == node1->nAddress0) {
            if (save2 != NULL) {
                while (save2->left != NULL) {
                    save2 = save2->left;
                }
                root->start_range = save2->nAddress0;
            } else if (connect != NULL) {
                root->start_range = connect->nAddress0;
            } else {
                root->start_range = root->root_address;
            }
        }

        if (update) {
            if (save1 != NULL) {
                while (save1->right != NULL) {
                    save1 = save1->right;
                }
                root->end_range = save1->nAddress1;
            } else if (connect != NULL) {
                root->end_range = connect->nAddress1;
            } else {
                root->end_range = root->root_address;
            }
        }

        count += treeKillNodes(pCPU, node1);
        treeCallerKill(pCPU, node1);
        if (node1->pfCode != NULL) {
            cpuHeapFree(pCPU, node1);
        }
        if (!cpuTreeFree(node1)) {
            return false;
        }
        PAD_STACK();
        PAD_STACK();

        count++;
    }

    do {
        treeSearchNode(tree, end, &node2);
        if (node2 != NULL) {
            break;
        }
        end -= 4;
    } while (start < end);

    if (node2 != NULL) {
        connect = node2->prev;
        node2->prev = NULL;
        save1 = node2->left;
        save2 = node2->right;
        node2->right = NULL;

        while (save1 != NULL) {
            if (save1->nAddress0 > start) {
                save1 = save1->left;
            } else if (save1 != NULL) {
                save1->prev->left = NULL;
                break;
            } else {
                break;
            }
        }

        if (connect != NULL) {
            if (save2 != NULL) {
                if (connect->left == node2) {
                    connect->left = save2;
                } else {
                    connect->right = save2;
                }
                save2->prev = connect;
                if (save1 != NULL) {
                    while (save2->left != NULL) {
                        save2 = save2->left;
                    }
                    save2->left = save1;
                    save1->prev = save2;
                }
            } else if (save1 != NULL) {
                if (connect->left == node2) {
                    connect->left = save1;
                } else {
                    connect->right = save1;
                }
                save1->prev = connect;
            } else if (connect->left == node2) {
                connect->left = NULL;
            } else {
                connect->right = NULL;
            }
        } else if (save2 != NULL) {
            if (root->left == node2) {
                root->left = save2;
            } else {
                root->right = save2;
            }
            save2->prev = NULL;
            if (save1 != NULL) {
                while (save2->left != NULL) {
                    save2 = save2->left;
                }
                save2->left = save1;
                save1->prev = save2;
            }
        } else if (save1 != NULL) {
            if (root->left == node2) {
                root->left = save1;
            } else {
                root->right = save1;
            }
            save1->prev = NULL;
        } else if (root->left == node2) {
            root->left = NULL;
        } else {
            root->right = NULL;
        }

        if (root->end_range == node2->nAddress1) {
            if (save1 != NULL) {
                while (save1->right != NULL) {
                    save1 = save1->right;
                }
                root->end_range = save1->nAddress1;
            } else if (connect != NULL) {
                root->end_range = connect->nAddress1;
            } else {
                root->end_range = root->root_address;
            }
        }

        count += treeKillNodes(pCPU, node2);
        treeCallerKill(pCPU, node2);
        if (node2->pfCode != NULL) {
            cpuHeapFree(pCPU, node2);
        }
        if (!cpuTreeFree(node2)) {
            return false;
        }
        PAD_STACK();
        PAD_STACK();

        count++;
    }

    return count;
}

static bool treeKillReason(Cpu* pCPU, s32* value) {
    if (pCPU->survivalTimer < 300) {
        return false;
    }
    if (pCPU->survivalTimer == 300) {
        *value = 1;
        return true;
    }
    if (pCPU->survivalTimer % 400 == 0 && treeMemory(pCPU) > 3250000) {
        *value = pCPU->survivalTimer - 200;
        return true;
    }

    NO_INLINE();
    return false;
}

static bool treeTimerCheck(Cpu* pCPU) {
    CpuTreeRoot* root;
    s32 begin;
    s32 end;

    if (pCPU->survivalTimer > 0x7FFFF000) {
        root = pCPU->gTree;
        if (root->kill_limit != 0) {
            return false;
        }
        begin = 0;
        end = 0x7FFFF000;
        if (root->left != NULL) {
            treePrintNode(pCPU, root->left, 0x100, &begin, &end);
        }
        if (root->right != NULL) {
            treePrintNode(pCPU, root->right, 0x100, &begin, &end);
        }
        begin = end - 3;
        if (root->left != NULL) {
            treePrintNode(pCPU, root->left, 0x1000, &begin, &end);
        }
        if (root->right != NULL) {
            treePrintNode(pCPU, root->right, 0x1000, &begin, &end);
        }
        pCPU->survivalTimer -= begin;
        return true;
    }
    return false;
}

static bool treeCleanUp(Cpu* pCPU, CpuTreeRoot* root) {
    bool done = false;
    bool complete = false;
    s32 pad;

    if (root->side == 0) {
        done = treeCleanNodes(pCPU, root->left);
    }
    if ((root->side != 0 || done) && treeCleanNodes(pCPU, root->right)) {
        complete = true;
    }
    if (!complete) {
        return false;
    }

    if (treeMemory(pCPU) > 0x400000) {
        root->kill_limit = pCPU->survivalTimer - 10;
    } else if (treeMemory(pCPU) > 3250000) {
        root->kill_limit += 95;
        if (root->kill_limit > pCPU->survivalTimer - 10) {
            root->kill_limit = pCPU->survivalTimer - 10;
        }
    } else {
        root->kill_limit = 0;
        root->restore = NULL;
        root->restore_side = 0;
    }

    return true;
}

static bool treeCleanNodes(Cpu* pCPU, CpuFunction* top) {
    CpuFunction** current;
    CpuFunction* kill = NULL;
    CpuTreeRoot* root = pCPU->gTree;
    s32 kill_limit = root->kill_limit;
    CpuFunction* temp;

    if (top == NULL) {
        root->side ^= 1;
        return true;
    }

    current = &root->restore;
    if (root->restore == NULL) {
        *current = top;
    }

    while (*current != NULL) {
        if (pCPU->nRetrace != pCPU->nRetraceUsed || root->kill_number >= 12) {
            break;
        }

        if (root->restore_side == 0) {
            while ((*current)->left != NULL) {
                *current = (*current)->left;
            }
            root->restore_side = 1;
        }

        while (*current != NULL) {
            if (pCPU->nRetrace != pCPU->nRetraceUsed || root->kill_number >= 12) {
                break;
            }

            if (kill != NULL) {
                if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                    return false;
                }
                if (!treeDeleteNode(pCPU, &top, kill)) {
                    return false;
                }
                kill = NULL;
                root->kill_number++;
            }

            temp = *current;
            if (temp->timeToLive > 0 && temp->timeToLive <= kill_limit) {
                kill = *current;
            }

            if ((*current)->right != NULL) {
                *current = (*current)->right;
                root->restore_side = 0;
                break;
            }

            if (*current == top) {
                if (kill != NULL) {
                    if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                        return false;
                    }
                    if (!treeDeleteNode(pCPU, &top, kill)) {
                        return false;
                    }
                }

                root->side ^= 1;
                *current = NULL;
                root->restore_side = 0;
                return true;
            }

            while (*current != (*current)->prev->left) {
                *current = (*current)->prev;
                if (*current == top) {
                    if (kill != NULL) {
                        if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                            return false;
                        }
                        if (!treeDeleteNode(pCPU, &top, kill)) {
                            return false;
                        }
                    }

                    root->side ^= 1;
                    *current = NULL;
                    root->restore_side = 0;
                    return true;
                }
            }

            *current = (*current)->prev;
            root->restore_side = 1;
        }
    }

    if (kill != NULL) {
        if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
            return false;
        }
        if (!treeDeleteNode(pCPU, &top, kill)) {
            return false;
        }
    }
    return false;
}

static inline bool treeForceCleanUp(Cpu* pCPU, CpuFunction* tree, s32 kill_limit) {
    CpuTreeRoot* root = pCPU->gTree;

    root->kill_limit = 0;
    root->restore = NULL;
    root->restore_side = 0;
    if (tree != NULL && tree->timeToLive > 0) {
        tree->timeToLive = pCPU->survivalTimer;
    }
    if (root->side == 0) {
        if (root->left != NULL) {
            treeForceCleanNodes(pCPU, root->left, kill_limit);
        }
    } else {
        if (root->right != NULL) {
            treeForceCleanNodes(pCPU, root->right, kill_limit);
        }
    }
    root->side ^= 1;
    return true;
}

static bool treeForceCleanNodes(Cpu* pCPU, CpuFunction* tree, s32 kill_limit) {
    CpuFunction* current;
    CpuFunction* kill = NULL;

    if (tree == NULL) {
        return false;
    }
    current = tree;

    do {
        while (current->left != NULL) {
            current = current->left;
        }

        do {
            if (kill != NULL) {
                if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                    return false;
                }
                if (!treeDeleteNode(pCPU, &tree, kill)) {
                    return false;
                }
                kill = NULL;
            }

            if (current->timeToLive > 0 && current->timeToLive <= kill_limit) {
                kill = current;
            }

            if (current->right != NULL) {
                current = current->right;
                break;
            }

            if (current == tree) {
                if (kill != NULL) {
                    if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                        return false;
                    }
                    if (!treeDeleteNode(pCPU, &tree, kill)) {
                        return false;
                    }
                }
                return true;
            }

            while (current != current->prev->left) {
                current = current->prev;
                if (current == tree) {
                    if (kill != NULL) {
                        if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                            return false;
                        }
                        if (!treeDeleteNode(pCPU, &tree, kill)) {
                            return false;
                        }
                    }
                    return true;
                }
            }

            current = current->prev;
        } while (current != NULL);
    } while (current != NULL);

    return false;
}

// Stripped function with unused strings
static bool treePrint(Cpu* pCPU) {
    (void)"tree range (%p - %p)\n";
    (void)"total nodes: %d (tree height: %d %d)\n";
    (void)"total memory: %d\n";

    return true;
}

static bool treePrintNode(Cpu* pCPU, CpuFunction* tree, s32 print_flag, s32* left, s32* right) {
    CpuFunction* current;
    bool flag;
    s32 level;

    level = 0;
    if (tree == NULL) {
        return false;
    }

    flag = ganMapGPR[31] & 0x100 ? true : false;
    current = tree;

    while (true) {
        while (current->left != NULL) {
            current = current->left;
            level++;
            if (print_flag & 1) {
                if (level > *left) {
                    (*left)++;
                }
            }
        }

        do {
            if (print_flag & 0x10) {
                treeCallerCheck(pCPU, current, flag, *left, *right);
            } else if (print_flag & 0x100) {
                if (current->timeToLive > 0) {
                    if (current->timeToLive > *left) {
                        *left = current->timeToLive;
                    }
                    if (current->timeToLive < *right) {
                        *right = current->timeToLive;
                    }
                }
            } else if (print_flag & 0x1000) {
                if (current->timeToLive > 0) {
                    current->timeToLive -= *left;
                }
            } else if (print_flag & 1) {
                OSReport("start=%p, end=%p (%d) (size: %d)\n", current->nAddress0, current->nAddress1,
                         current->timeToLive, current->memory_size);
            }

            if (current->right != NULL) {
                current = current->right;
                level++;
                if (print_flag & 1) {
                    if (level > *right) {
                        (*right)++;
                    }
                }
                break;
            }

            if (current == tree) {
                return true;
            }

            while (current != current->prev->left) {
                current = current->prev;
                level -= 1;
                if (current == tree) {
                    return true;
                }
            }

            current = current->prev;
        } while (current != NULL);

        if (current == NULL) {
            return false;
        }
    }

    return false;
}

static inline s32 treeMemory(Cpu* pCPU) {
    if (pCPU->gTree == NULL) {
        return 0;
    } else {
        return pCPU->gTree->total_memory;
    }
}

s32 cpuOpcodeChecksum(u32 opcode) {
    s32 nChecksum = 0x20;

    if (opcode == 0) {
        return 0;
    }

    switch (MIPS_OP(opcode)) {
        case 0x01:
            switch (MIPS_RT(opcode)) {
                case 0x00:
                case 0x01:
                case 0x02:
                case 0x03:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                    nChecksum = 4;
                    break;
            }
            break;
        case 0x10:
            switch (MIPS_FUNCT(opcode)) {
                case 0x01:
                case 0x02:
                case 0x05:
                case 0x08:
                case 0x18:
                    break;
                default:
                case 0x00:
                case 0x03:
                case 0x04:
                case 0x06:
                case 0x07:
                case 0x09:
                case 0x0A:
                case 0x0B:
                case 0x0C:
                case 0x0D:
                case 0x0E:
                case 0x0F:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                    switch (MIPS_FMT(opcode)) {
                        case 8:
                            switch (MIPS_FT(opcode)) {
                                case 0x00:
                                case 0x01:
                                case 0x02:
                                case 0x03:
                                    nChecksum = 4;
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 0x11:
            if (MIPS_RS(opcode) == 0x08) {
                switch (MIPS_RT(opcode)) {
                    case 0x00:
                    case 0x01:
                    case 0x02:
                    case 0x03:
                        nChecksum = 4;
                        break;
                }
            }
            break;
        case 0x02:
            nChecksum = 1;
            break;
        case 0x03:
            nChecksum = 1;
            break;
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            nChecksum = 4;
            break;
        case 0x09:
        case 0x0D:
        case 0x0F:
            nChecksum = 0x10;
            break;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x28:
        case 0x29:
        case 0x2B:
        case 0x31:
        case 0x35:
        case 0x37:
        case 0x39:
        case 0x3D:
        case 0x3F:
            nChecksum = 0x10;
            break;
    }

    return nChecksum;
}
