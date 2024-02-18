#include "macros.h"
#include "xlObject.h"
#include "system.h"
#include "rom.h"
#include "ram.h"
#include "cpu.h"

s32 systemEvent(System* pSystem, s32 nEvent, void* pArgument);

char D_800EB300[] = "SYSTEM (N64)";

_XL_OBJECTTYPE gClassSystem = {
    D_800EB300,
    sizeof(System),
    NULL,
    (EventFunc)systemEvent,
};

u32 contMap[] = {
    0x80000000, 0x40000000, 0x00000000, 0x00000000, 0x00200000, 0x00100000, 0x20000000, 0x10000000, 0x08000000,
    0x04000000, 0x02000000, 0x01000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00080000, 0x00040000,
    0x00020000, 0x00010000, 0x80000000, 0x40000000, 0x00000000, 0x00000000, 0x20000000, 0x00100000, 0x20000000,
    0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000,
    0x00080000, 0x00040000, 0x00020000, 0x00010000, 0x80000000, 0x40000000, 0x00010000, 0x00020000, 0x20000000,
    0x00100000, 0x00040000, 0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00200000, 0x00200000,
    0x00200000, 0x00200000, 0x00080000, 0x00040000, 0x00020000, 0x00010000, 0x80000000, 0x40000000, 0x00200000,
    0x00000000, 0x20000000, 0x00100000, 0x20000000, 0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000,
    0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,
};

void* jtbl_800EB460[] = {
    (void*)0x8002CC70, (void*)0x8002CCBC, (void*)0x8002CD04, (void*)0x8002CD9C, (void*)0x8002CE0C, (void*)0x8002CE54,
    (void*)0x8002CEC4, (void*)0x8002CF0C, (void*)0x8002CF7C, (void*)0x8002CF88, (void*)0x8002CF94, (void*)0x8002CFDC,
    (void*)0x8002D024, (void*)0x8002D070, (void*)0x8002D090, (void*)0x8002D0DC,
};

char D_800EB4A0[] = "BREAK (CPU)";
char D_800EB4AC[] = "BREAK (SP)";
char D_800EB4B8[] = "THREADSTATUS";

void* jtbl_800EB4C8[] = {
    (void*)0x8002DBDC, (void*)0x8002DBF4, (void*)0x8002DC0C, (void*)0x8002DC24, (void*)0x8002DC3C, (void*)0x8002DC54,
    (void*)0x8002DC70, (void*)0x8002DC90, (void*)0x8002DCB0, (void*)0x8002DCD0, (void*)0x8002DCEC, (void*)0x8002DD0C,
    (void*)0x8002DD20, (void*)0x8002DD38, (void*)0x8002DD44, (void*)0x8002DD50,
};

char D_800EB508[] = "TPL/z_icon.tpl";
char D_800EB518[] = "TPL/z_bnr.tpl";

char D_800EB528[] = "Mario 64";
char D_800EB534[] = "\x83\x5b\x83\x8b\x83\x5f\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93"; // "ゼルダコレクション"
char D_800EB548[] = "The Legend of Zelda Debug";
char D_800EB564[] = "Legend of Zelda";
char D_800EB574[] = "Pilotwings";
char D_800EB580[] = "Animal Forest";
char D_800EB590[] = "Cruise 'n USA";
char D_800EB5A0[] = "Dr. Mario";
char D_800EB5AC[] = "Mario Kart";
char D_800EB5B8[] = "Mario Party 1";
char D_800EB5C8[] = "Mario Party 2";
char D_800EB5D8[] = "Mario Party 3";
char D_800EB5E8[] = "PaperMario";
char D_800EB5F4[] = "Paper Mario";
char D_800EB600[] = "PAPERMARIO";
char D_800EB60C[] = "PokemonStadium";
char D_800EB61C[] = "Pokemon Stadium";
char D_800EB62C[] = "POKEMONSTADIUM";
char D_800EB63C[] = "Panel de Pon";
char D_800EB64C[] = "YoshiStory";

SystemRomConfig gSystemRomConfigurationList;

u32 nTickMultiplier = 2;
f32 fTickScale = 1.0;

static char D_80134E68[] = "";
static char D_80134E6C[] = "SW0";
static char D_80134E70[] = "SW1";
static char D_80134E74[] = "CART";
static char D_80134E7C[] = "COUNTER";
static char D_80134E84[] = "RDB";
static char D_80134E88[] = "SP";
static char D_80134E8C[] = "SI";
static char D_80134E90[] = "AI";
static char D_80134E94[] = "VI";
static char D_80134E98[] = "PI";
static char D_80134E9C[] = "DP";
static char D_80134EA0[] = "FAULT";
static char D_80134EA8[] = "PRENMI";

static char D_80134EB0[] = "NSME";
static char D_80134EB8[] = "NSMJ";
static char D_80134EC0[] = "MARIO";
static char D_80134EC8[] = "CZLE";
static char D_80134ED0[] = "CZLJ";
static char D_80134ED8[] = "ZELDA1";
static char D_80134EE0[] = "ZELDAX";
static char D_80134EE8[] = "ZELDA";
static char D_80134EF0[] = "ZELDAD";
static char D_80134EF8[] = "NZSJ";
static char D_80134F00[] = "NZSE";
static char D_80134F08[] = "ZELDA3";
static char D_80134F10[] = "NPWE";
static char D_80134F18[] = "PILOT";
static char D_80134F20[] = "NAFJ";
static char D_80134F28[] = "AF";
static char D_80134F2C[] = "NBCE";
static char D_80134F34[] = "NBKE";
static char D_80134F3C[] = "NGEE";
static char D_80134F44[] = "NFUE";
static char D_80134F4C[] = "NBYE";
static char D_80134F54[] = "NCUE";
static char D_80134F5C[] = "CRUISE";
static char D_80134F64[] = "NDNE";
static char D_80134F6C[] = "NDOE";
static char D_80134F74[] = "NN6E";
static char D_80134F7C[] = "NN6J";
static char D_80134F84[] = "DRMARIO";
static char D_80134F8C[] = "CFZE";
static char D_80134F94[] = "NLRE";
static char D_80134F9C[] = "NMFE";
static char D_80134FA4[] = "NKTE";
static char D_80134FAC[] = "KART";
static char D_80134FB4[] = "NK4E";
static char D_80134FBC[] = "CLBE";
static char D_80134FC4[] = "MP1";
static char D_80134FC8[] = "NMWE";
static char D_80134FD0[] = "MP2";
static char D_80134FD4[] = "NMVE";
static char D_80134FDC[] = "MP3";
static char D_80134FE0[] = "NM3E";
static char D_80134FE8[] = "NRIE";
static char D_80134FF0[] = "NMQE";
static char D_80134FF8[] = "NPOE";
static char D_80135000[] = "NQKE";
static char D_80135008[] = "NRSE";
static char D_80135010[] = "NRZE";
static char D_80135018[] = "NFXE";
static char D_80135020[] = "NFXJ";
static char D_80135028[] = "STARFOX";
static char D_80135030[] = "Starfox";
static char D_80135038[] = "NGUJ";
static char D_80135040[] = "NALE";
static char D_80135048[] = "NTEA";
static char D_80135050[] = "1080";
static char D_80135058[] = "NTPE";
static char D_80135060[] = "NEPE";
static char D_80135068[] = "NM8E";
static char D_80135070[] = "NYLJ";
static char D_80135078[] = "PANEL";
static char D_80135080[] = "NTUE";
static char D_80135088[] = "NWRE";
static char D_80135090[] = "NYSE";
static char D_80135098[] = "NBNJ";
static char D_801350A0[] = "XXX";

u32 gnFlagZelda;
const f32 D_80135F90 = 0.01666666753590107;
const f32 D_80135F94 = 1.100000023841858;
const f64 D_80135F98 = 4503599627370496.0;

extern _XL_OBJECTTYPE gClassFlash;
extern _XL_OBJECTTYPE gClassSram;
extern System* gpSystem;

//! TODO: import sdk headers
extern int atoi(const char* str);

s32 simulatorGetArgument(SystemArgumentType eType, char* pszArgument);

s32 systemSetupGameRAM(System* pSystem) {
    s32 szExtra;
    s32 bExpansion;
    s32 nSizeRAM;
    s32 nSizeCacheROM;
    s32 nSizeExtra;
    Rom* pROM;
    u32 nCode;
    u32 iCode;
    u32 anCode[0x100]; // size = 0x400

    bExpansion = 0;
    pROM = SYSTEM_ROM(pSystem);

    if (!romCopy(SYSTEM_ROM(pSystem), anCode, 0x1000, sizeof(anCode), NULL)) {
        return 0;
    }

    nCode = 0;
    for (iCode = 0; iCode < ARRAY_COUNT(anCode); iCode++) {
        nCode += anCode[iCode];
    }

    // Majora's Mask ("NZSJ", "NZSE")
    if (romTestCode(pROM, D_80134EF8) || romTestCode(pROM, D_80134F00)) {
        bExpansion = 1;
    }

    // Ocarina of Time or Majora's Mask ("CZLJ", "CZLE", "NZSJ", "NZSE")
    if (romTestCode(pROM, D_80134ED0) || romTestCode(pROM, D_80134EC8) || romTestCode(pROM, D_80134EF8) ||
        romTestCode(pROM, D_80134F00)) {
        switch (nCode) {
            case 0x5CAC1C8F: // OoT?
                gnFlagZelda = 2;
                break;
            case 0x184CED80: // MM?
                gnFlagZelda = 3;
                break;
            case 0x54A59B56: // OoT?
            case 0x421EB8E9: // OoT?
                gnFlagZelda = 4;
                break;
            case 0x7E8BEE60: // MM?
                gnFlagZelda = 5;
                break;
        }

        if (gnFlagZelda & 1) {
            bExpansion = 1;
        }
    }

    // Conker's Bad Fur Day ("NFUE")
    if (romTestCode(pROM, D_80134F44)) {
        bExpansion = 1;
    }

    if (bExpansion) {
        nSizeRAM = 0x800000;
        nSizeCacheROM = 0x400000;
    } else {
        nSizeRAM = 0x400000;
        nSizeCacheROM = 0x800000;
    }

    if (simulatorGetArgument(SAT_XTRA, (char*)&szExtra)) {
        nSizeExtra = atoi((char*)szExtra) << 0x14;

        if (nSizeExtra > (s32)(nSizeCacheROM + 0xFFF00000)) {
            nSizeExtra = nSizeCacheROM + 0xFFF00000;
        }

        nSizeRAM += nSizeExtra;
        nSizeCacheROM -= nSizeExtra;
    }

    if (!ramSetSize(pSystem->apObject[SOT_RAM], nSizeRAM)) {
        return 0;
    }

    if (!romSetCacheSize(SYSTEM_ROM(pSystem), nSizeCacheROM)) {
        return 0;
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGetInitialConfiguration.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemSetupGameALL.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGetException.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemPut64.s")

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/system/__systemCopyROM_Complete.s")
#else
static s32 __systemCopyROM_Complete(void) {
    s32 iAddress;
    s32 nCount;
    u32 nAddress0;
    u32 nAddress1;
    u32 anAddress[0x20]; // size = 0x80
    u32* ptr;

    nAddress0 = gpSystem->romCopy.nOffsetRAM;
    nAddress1 = nAddress0 + gpSystem->romCopy.nSize - 1;

    if (!frameInvalidateCache(gpSystem->pFrame, nAddress0, nAddress1)) {
        return 0;
    }

    if (!rspInvalidateCache(SYSTEM_RSP(gpSystem), nAddress0, nAddress1)) {
        return 0;
    }

    if (!cpuGetOffsetAddress(SYSTEM_CPU(gpSystem), anAddress, &nCount, gpSystem->romCopy.nOffsetRAM, gpSystem->romCopy.nSize)) {
        return 0;
    }

    // for (iAddress = 0; iAddress < nCount; iAddress++) {
    //     // iAddress?
    //     if (!cpuInvalidateCache(SYSTEM_CPU(gpSystem), anAddress[0], anAddress[gpSystem->romCopy.nSize - 1])) {
    //         return 0;
    //     }
    // }

    for (iAddress = 0, ptr = anAddress; iAddress < nCount; iAddress++, ptr++) {
        if (!cpuInvalidateCache(SYSTEM_CPU(gpSystem), *ptr, *ptr + (gpSystem->romCopy.nSize - 1))) {
            return 0;
        }
    }

    gpSystem->romCopy.nSize = 0;
    if ((gpSystem->romCopy.pCallback != NULL) && !gpSystem->romCopy.pCallback()) {
        return 0;
    }

    return 1;
}
#endif

//! TODO: remove when the function above is matched
static s32 __systemCopyROM_Complete(void);

s32 systemCopyROM(System* pSystem, s32 nOffsetRAM, s32 nOffsetROM, s32 nSize,  SystemCopyCallbackFunc* pCallback) {
    void* pTarget;

    pSystem->romCopy.nSize = nSize;
    pSystem->romCopy.pCallback = pCallback;
    pSystem->romCopy.nOffsetRAM = nOffsetRAM & 0x7FFFFF;
    pSystem->romCopy.nOffsetROM = nOffsetROM;

    if (!ramGetBuffer(SYSTEM_RAM(pSystem), &pTarget, nOffsetRAM, (u32*)&nSize)) {
        return 0;
    }

    if (pCallback == NULL) {
        if (!romCopy(SYSTEM_ROM(pSystem), pTarget, nOffsetROM, nSize, NULL)) {
            return 0;
        }

        if (!__systemCopyROM_Complete()) {
            return 0;
        }
    } else {
        if (!romCopy(SYSTEM_ROM(pSystem), pTarget, nOffsetROM, nSize, __systemCopyROM_Complete)) {
            return 0;
        }
    }

    return 1;
}

s32 systemSetMode(System* pSystem, s32 pMode) {
    if (xlObjectTest(pSystem, &gClassSystem)) {
        pSystem->eMode = pMode;

        if (pMode == SM_STOPPED) {
            pSystem->nAddressBreak = -1;
        }

        return 1;
    }

    return 0;
}

s32 systemGetMode(System* pSystem, s32* pMode) {
    if (xlObjectTest(pSystem, &gClassSystem) && (pMode != NULL)) {
        *pMode = pSystem->eMode;
        return 1;
    }

    return 0;
}

s32 systemSetStorageDevice(System* pSystem, s32 eStorageDevice) {
    pSystem->storageDevice = eStorageDevice;

    if (eStorageDevice == SOT_FLASH) {
        if (!xlObjectMake(&pSystem->apObject[SOT_FLASH], pSystem, &gClassFlash)) {
            return 0;
        }

        if (!cpuMapObject(pSystem->apObject[SOT_CPU], pSystem->apObject[SOT_FLASH], 0x08000000, 0x0801FFFF, 0)) {
            return 0;
        }
    }

    if (eStorageDevice == SOT_SRAM) {
        if (!xlObjectMake(&pSystem->apObject[SOT_SRAM], pSystem, &gClassSram)) {
            return 0;
        }

        if (!cpuMapObject(pSystem->apObject[SOT_CPU], pSystem->apObject[SOT_SRAM], 0x08000000, 0x08007FFF, 0)) {
            return 0;
        }
    }

    return 1;
}

s32 systemGetStorageDevice(System* pSystem, s32* pStorageDevice) {
    *pStorageDevice = pSystem->storageDevice;
    return 1;
}

s32 systemReset(System* pSystem) {
    s64 nPC;
    s32 nOffsetRAM;
    SystemObjectType eObject;

    pSystem->nAddressBreak = -1;

    if (romGetImage(SYSTEM_ROM(pSystem), NULL)) {
        if (!systemSetupGameRAM(pSystem)) {
            return 0;
        }

        if (!ramWipe(pSystem->apObject[SOT_RAM])) {
            return 0;
        }

        if (!romGetPC(SYSTEM_ROM(pSystem), (u64*)&nPC)) {
            return 0;
        }

        nOffsetRAM = nPC & 0xFFFFFF;
        if (!systemCopyROM(pSystem, nOffsetRAM, 0x1000, 0x100000, NULL)) {
            return 0;
        }

        if (!cpuReset(SYSTEM_CPU(pSystem))) {
            return 0;
        }

        cpuSetXPC(SYSTEM_CPU(pSystem), nPC, 0, 0);

        if (!systemSetupGameALL(pSystem)) {
            return 0;
        }

        eObject = SOT_CPU;
        for (; eObject < SOT_COUNT; eObject++) {
            if (pSystem->apObject[eObject] != NULL && !xlObjectEvent(pSystem->apObject[eObject], 0x1003, NULL)) {
                return 0;
            }
        }

        if (!xlObjectEvent(pSystem->pFrame, 0x1003, NULL)) {
            return 0;
        }

        if (!xlObjectEvent(pSystem->pSound, 0x1003, NULL)) {
            return 0;
        }
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/system/systemExecute.s")

s32 systemCheckInterrupts(System* pSystem) {
    s32 iException;
    s32 nMaskFinal;
    s32 bUsed;
    s32 bDone;
    SystemException exception;
    CpuExceptionCode eCodeFinal;

    nMaskFinal = 0;
    eCodeFinal = CEC_NONE;
    bDone = 0;
    pSystem->bException = 0;

    for (iException = 0; iException < ARRAY_COUNT(pSystem->anException); iException++) {
        if (pSystem->anException[iException] != 0) {
            pSystem->bException = 1;

            if (!bDone) {
                if (!systemGetException(pSystem, iException, &exception)) {
                    return 0;
                }

                bUsed = 0;

                if (exception.eCode == 0) {
                    if (cpuTestInterrupt(SYSTEM_CPU(pSystem), exception.nMask) && 
                        ((exception.eTypeMips == MIT_NONE) || mipsSetInterrupt(SYSTEM_MIPS(pSystem), exception.eTypeMips))) {
                        bUsed = 1;
                    }
                } else {
                    bDone = 1;

                    if (nMaskFinal == 0) {
                        bUsed = 1;
                        eCodeFinal = exception.eCode;
                    }
                }

                if (bUsed) {
                    nMaskFinal |= exception.nMask;
                    pSystem->anException[iException] = 0;
                }
            }
        }
    }

    if (nMaskFinal != 0) {
        if (!cpuException(SYSTEM_CPU(pSystem), CEC_INTERRUPT, nMaskFinal)) {
            return 0;
        }
    } else {
        if ((eCodeFinal != CEC_NONE) && !cpuException(SYSTEM_CPU(pSystem), eCodeFinal, 0)) {
            return 0;
        }
    }

    return 1;
}

s32 systemExceptionPending(System* pSystem, s32 nException) {
    if ((nException > -1) && (nException < ARRAY_COUNT(pSystem->anException))) {
        if (pSystem->anException[nException] != 0) {
            return 1;
        }

        return 0;
    }

    return 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/system/systemEvent.s")
