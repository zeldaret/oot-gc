#include "system.h"
#include "audio.h"
#include "cpu.h"
#include "dolphin.h"
#include "flash.h"
#include "frame.h"
#include "macros.h"
#include "mcardGCN.h"
#include "mips.h"
#include "pif.h"
#include "ram.h"
#include "rom.h"
#include "rsp.h"
#include "simGCN.h"
#include "soundGCN.h"
#include "sram.h"
#include "xlObject.h"

//! TODO: move these declarations to the proper headers
extern _XL_OBJECTTYPE gClassRdb;
extern _XL_OBJECTTYPE gClassPeripheral;
extern _XL_OBJECTTYPE gClassLibrary;
extern _XL_OBJECTTYPE gClassSerial;
extern _XL_OBJECTTYPE gClassVideo;
extern _XL_OBJECTTYPE gClassAudio;
extern _XL_OBJECTTYPE gClassDisk;
extern _XL_OBJECTTYPE gClassMips;
extern _XL_OBJECTTYPE gClassRDP;
extern _XL_OBJECTTYPE gClassRSP;
extern _XL_OBJECTTYPE gClassROM;
extern _XL_OBJECTTYPE gClassRAM;
extern _XL_OBJECTTYPE gClassPIF;
extern _XL_OBJECTTYPE gClassCPU;
extern _XL_OBJECTTYPE gClassFlash;
extern _XL_OBJECTTYPE gClassSram;

extern void* gpFrame;
extern void* gpSound;

extern s32 gz_bnrSize;
extern s32 gz_iconSize;

extern MemCard mCard;

//! TODO: remove when these functions are matched
static s32 systemGet8(System* pSystem, u32 nAddress, s8* pData);
static s32 systemGet16(System* pSystem, u32 nAddress, s16* pData);
static s32 systemGet32(System* pSystem, u32 nAddress, s32* pData);
static s32 systemGet64(System* pSystem, u32 nAddress, s64* pData);
static s32 systemPut8(System* pSystem, u32 nAddress, s8* pData);
static s32 systemPut16(System* pSystem, u32 nAddress, s16* pData);
static s32 systemPut32(System* pSystem, u32 nAddress, s32* pData);
static s32 systemPut64(System* pSystem, u32 nAddress, s64* pData);

//! TODO: import MSL headers
extern int atoi(const char* str);

_XL_OBJECTTYPE gClassSystem = {
    "SYSTEM (N64)",
    sizeof(System),
    NULL,
    (EventFunc)systemEvent,
}; // size = 0x10

static u32 contMap[4][20] = {
    // Controller 1
    {
        0x80000000, 0x40000000, 0x00000000, 0x00000000, 0x00200000, 0x00100000, 0x20000000,
        0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x08000000, 0x04000000,
        0x02000000, 0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,

    },
    // Controller 2
    {
        0x80000000, 0x40000000, 0x00000000, 0x00000000, 0x20000000, 0x00100000, 0x20000000,
        0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x08000000, 0x04000000,
        0x02000000, 0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,

    },
    // Controller 3
    {
        0x80000000, 0x40000000, 0x00010000, 0x00020000, 0x20000000, 0x00100000, 0x00040000,
        0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00200000, 0x00200000,
        0x00200000, 0x00200000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,

    },
    // Controller 4
    {
        0x80000000, 0x40000000, 0x00200000, 0x00000000, 0x20000000, 0x00100000, 0x20000000,
        0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x08000000, 0x04000000,
        0x02000000, 0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,
    },

}; // size = 0x140

SystemRomConfig gSystemRomConfigurationList[1];
u32 nTickMultiplier = 2;
f32 fTickScale = 1.0;
u32 gnFlagZelda;

#define Z_ICON_PATH "TPL/z_icon.tpl"
#define Z_BNR_PATH "TPL/z_bnr.tpl"

static s32 systemSetupGameRAM(System* pSystem) {
    char* szExtra;
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

    // Majora's Mask
    if (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE")) {
        bExpansion = 1;
    }

    // Ocarina of Time or Majora's Mask
    if (romTestCode(pROM, "CZLJ") || romTestCode(pROM, "CZLE") || romTestCode(pROM, "NZSJ") ||
        romTestCode(pROM, "NZSE")) {
        switch (nCode) {
            case 0x5CAC1C8F:
                gnFlagZelda = 2;
                break;
            case 0x184CED80:
                gnFlagZelda = 3;
                break;
            case 0x54A59B56:
            case 0x421EB8E9:
                gnFlagZelda = 4;
                break;
            case 0x7E8BEE60:
                gnFlagZelda = 5;
                break;
        }

        if (gnFlagZelda & 1) {
            bExpansion = 1;
        }
    }

    // Conker's Bad Fur Day
    if (romTestCode(pROM, "NFUE")) {
        bExpansion = 1;
    }

    if (bExpansion) {
        nSizeRAM = 0x800000;
        nSizeCacheROM = 0x400000;
    } else {
        nSizeRAM = 0x400000;
        nSizeCacheROM = 0x800000;
    }

    if (simulatorGetArgument(SAT_XTRA, &szExtra)) {
        nSizeExtra = atoi(szExtra) << 0x14;

        if (nSizeExtra > (s32)(nSizeCacheROM + 0xFFF00000)) {
            nSizeExtra = nSizeCacheROM + 0xFFF00000;
        }

        nSizeRAM += nSizeExtra;
        nSizeCacheROM -= nSizeExtra;
    }

    if (!ramSetSize(SYSTEM_RAM(pSystem), nSizeRAM)) {
        return 0;
    }

    if (!romSetCacheSize(SYSTEM_ROM(pSystem), nSizeCacheROM)) {
        return 0;
    }

    return 1;
}

inline void systemSetControllerConfiguration(SystemRomConfig* pRomConfig, s32 controllerConfig,
                                             s32 bSetControllerConfig) {
    s32 iConfigList;

    pRomConfig->rumbleConfiguration = 0;

    for (iConfigList = 0; iConfigList < 4; iConfigList++) {
        simulatorCopyControllerMap((u32*)pRomConfig->controllerConfiguration[iConfigList],
                                   contMap[((controllerConfig >> (iConfigList * 8)) & 0x7F)]);
        pRomConfig->rumbleConfiguration |= (1 << (iConfigList * 8)) & (controllerConfig >> 7);
    }

    if (bSetControllerConfig) {
        pRomConfig->normalControllerConfig = controllerConfig;
        pRomConfig->currentControllerConfig = controllerConfig;
    }
}

s32 systemGetInitialConfiguration(System* pSystem, Rom* pROM, s32 index) {
    char* szText;

    // fake match
    (void)contMap;
    (void)contMap;

    if (!romGetCode(pROM, gSystemRomConfigurationList[index].rom)) {
        return 0;
    }

    systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, 0);
    gSystemRomConfigurationList[index].storageDevice = SOT_CPU;

    if (romTestCode(pROM, "NSME") || romTestCode(pROM, "NSMJ")) {
        // Super Mario 64
        systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x01010101, 0);
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, "CZLE") || romTestCode(pROM, "CZLJ")) {
        // Ocarina of Time
        gSystemRomConfigurationList[index].storageDevice = SOT_PIF;

        if (!simulatorGetArgument(SAT_VIBRATION, &szText) || (*szText == '1')) {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x82828282, 1);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x80808080, 1);
            }
        } else {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x02020202, 1);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, 1);
            }
        }

    } else if (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE")) {
        // Majora's Mask
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

        if (!simulatorGetArgument(SAT_VIBRATION, &szText) || (*szText == '1')) {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x82828282, 1);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x80808080, 1);
            }
        } else {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x02020202, 1);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, 1);
            }
        }

    } else if (romTestCode(pROM, "NPWE")) {
        // Pilotwings 64
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, "NAFJ")) {
        // Animal Forest
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

    } else if (romTestCode(pROM, "NCUE")) {
        // Cruis'n
        gSystemRomConfigurationList[index].storageDevice = 20; // bug?

    } else if (romTestCode(pROM, "NKTE")) {
        // Mario Kart 64
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, "NFXE") || romTestCode(pROM, "NFXJ")) {
        // Star Fox 64
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, "NMVE")) {
        // Mario Party 3
        gSystemRomConfigurationList[index].storageDevice = SOT_FLASH;

    } else if (romTestCode(pROM, "NYSE")) {
        // Yoshi's Story
        gSystemRomConfigurationList[index].storageDevice = SOT_FLASH;

    } else if (romTestCode(pROM, "NTEA")) {
        // 1080° Snowboarding
        gSystemRomConfigurationList[index].storageDevice = SOT_PIF;

    } else if (romTestCode(pROM, "NMQE")) {
        // Paper Mario
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

    } else if (romTestCode(pROM, "NPOE")) {
        // Pokémon Stadium
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

    } else if (romTestCode(pROM, "NYLJ")) {
        // Panel de Pon 64
        gSystemRomConfigurationList[index].storageDevice = SOT_PIF;

    } else if (romTestCode(pROM, "NN6E") || romTestCode(pROM, "NN6J")) {
        // Dr. Mario 64
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, "NBNJ")) {
        // Bakuretsu Muteki Bangaioh
        gSystemRomConfigurationList[index].storageDevice = SOT_FLASH;
    }

    return 1;
}

static s32 systemSetupGameALL(System* pSystem) {
    s32 nSizeSound;
    s32 iController;
    s32 nSize;
    u32* anMode;
    s32 i;
    u64 nTimeRetrace;
    char acCode[5];
    DVDFileInfo fileInfo;
    Cpu* pCPU;
    Rom* pROM;
    Pif* pPIF;
    s32 defaultConfiguration;

    pCPU = SYSTEM_CPU(pSystem);
    pROM = SYSTEM_ROM(pSystem);
    pPIF = SYSTEM_PIF(pSystem);

    if (!xlHeapTake(&mCard.saveIcon, gz_iconSize | 0x30000000)) {
        return 0;
    }

    if (!xlHeapTake(&mCard.saveBanner, gz_bnrSize | 0x30000000)) {
        return 0;
    }

    nSizeSound = 0x2000;
    memset(&defaultConfiguration, 0, 4);
    pSystem->eTypeROM = SRT_UNKNOWN;

    if (!ramGetBuffer(SYSTEM_RAM(pSystem), &anMode, 0x300, NULL)) {
        return 0;
    }

    anMode[0] = 1;
    anMode[1] = 0;
    anMode[2] = 0xB0000000;
    anMode[3] = 0;
    anMode[4] = 0x17D7;
    anMode[5] = 1;

    nTimeRetrace = OSSecondsToTicks(1.0f / 60.0f);

    if (!ramGetSize(SYSTEM_RAM(pSystem), &nSize)) {
        return 0;
    }

    anMode[6] = nSize;
    systemGetInitialConfiguration(pSystem, pROM, 0);

    i = 0;
    if (gSystemRomConfigurationList[i].storageDevice & 1) {
        if (!systemSetStorageDevice(pSystem, SOT_SRAM)) {
            return 0;
        }
    } else {
        if (gSystemRomConfigurationList[i].storageDevice & 2) {
            if (!systemSetStorageDevice(pSystem, SOT_FLASH)) {
                return 0;
            }
        } else {
            if (!systemSetStorageDevice(pSystem, SOT_NONE)) {
                return 0;
            }
        }
    }

    if (gSystemRomConfigurationList[i].storageDevice & 4) {
        if (!pifSetEEPROMType(pPIF, CT_4K)) {
            return 0;
        }
    } else {
        if (gSystemRomConfigurationList[i].storageDevice & 8) {
            if (!pifSetEEPROMType(pPIF, CT_16K)) {
                return 0;
            }
        } else {
            if (!pifSetEEPROMType(pPIF, CT_NONE)) {
                return 0;
            }
        }
    }

    if (romTestCode(pROM, "NSME") || romTestCode(pROM, "NSMJ")) {
        // Super Mario 64
        pSystem->eTypeROM = SRT_MARIO;
        nSizeSound = 0x1000;

        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
        mcardOpen(&mCard, "MARIO", "Mario 64", mCard.saveIcon, mCard.saveBanner, "MARIO",
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);

        if (!cpuSetCodeHack(pCPU, 0x80317938, 0x5420FFFE, 0)) {
            return 0;
        }
    } else if (romTestCode(pROM, "CZLE") || romTestCode(pROM, "CZLJ")) {
        // Ocarina of Time
        pSystem->eTypeROM = SRT_ZELDA1;
        nSizeSound = 0x1000;

        if (gnFlagZelda & 1) {
            if (romTestCode(pROM, "CZLE")) {
                if (!cpuSetCodeHack(pCPU, 0x80062D64, 0x94639680, -1)) {
                    return 0;
                }

                if (!cpuSetCodeHack(pCPU, 0x8006E468, 0x97040000, -1)) {
                    return 0;
                }
            } else {
                if (!cpuSetCodeHack(pCPU, 0x80062D64, 0x94639680, -1)) {
                    return 0;
                }

                if (!cpuSetCodeHack(pCPU, 0x8006E468, 0x97040000, -1)) {
                    return 0;
                }
            }
        } else if (romTestCode(pROM, "CZLE")) {
            if (!cpuSetCodeHack(pCPU, 0x8005BB14, ((gnFlagZelda & 2) ? 0x9463D040 : 0x9463D000), -1)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x80066638, 0x97040000, -1)) {
                return 0;
            }
        } else {
            if (!cpuSetCodeHack(pCPU, 0x8005BB34, 0x9463D040, -1)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x80066658, 0x97040000, -1)) {
                return 0;
            }
        }

        if (!(gnFlagZelda & 1)) {
            if (!(gnFlagZelda & 2)) {
                // CE-J/MQ-J?
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                // "ゼルダコレクション"
                mcardOpen(&mCard, "ZELDA1", "\x83\x5b\x83\x8b\x83\x5f\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93",
                          mCard.saveIcon, mCard.saveBanner, "ZELDAX",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
            } else {
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                // "ゼルダコレクション"
                mcardOpen(&mCard, "ZELDA1", "\x83\x5b\x83\x8b\x83\x5f\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93",
                          mCard.saveIcon, mCard.saveBanner, "ZELDA",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
            }
        } else {
            // debug rom?
            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                return 0;
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

            if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                return 0;
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
            mcardOpen(&mCard, "ZELDAD", "The Legend of Zelda Debug", mCard.saveIcon, mCard.saveBanner, "ZELDAD",
                      &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
        }

        pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x110);
    } else if (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE")) {
        // Majora's Mask
        pSystem->eTypeROM = SRT_ZELDA2;
        nSizeSound = 0x1000;

        if (romTestCode(pROM, "NZSJ")) {
            pSystem->bJapaneseVersion = 1;
        } else {
            pSystem->bJapaneseVersion = 0;
        }

        nTickMultiplier = 2;
        fTickScale = 1.1f;

        if (!ramGetBuffer(SYSTEM_RAM(pSystem), &anMode, 0x300U, NULL)) {
            return 0;
        }

        anMode[4] = 0x17D9;

        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
        mcardOpen(&mCard, "ZELDA3", "Legend of Zelda", mCard.saveIcon, mCard.saveBanner, "ZELDA3",
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);

        if (gnFlagZelda & 1) {
            if (cpuSetCodeHack(pCPU, 0x801C6FC0, 0x95630000, -1) == 0) {
                return 0;
            }
        } else if (romTestCode(pROM, "NZSJ")) {
            if (!cpuSetCodeHack(pCPU, 0x80179994, 0x95630000, -1)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDA84, 0x860C0000, 0x6025)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDA88, 0x860D0004, 0x6825)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDB0C, 0x86180000, 0xC025)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDB20, 0x86190004, 0xC825)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDB34, 0x86080002, 0x4025)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDB4C, 0x8609FFFA, 0x4825)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDB60, 0x860AFFFE, 0x5025)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDB94, 0x844EFFFA, 0x7025)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDBA8, 0x844FFFFE, 0x7825)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDC20, 0x860A0006, 0x5025)) {
                return 0;
            }

            if (!cpuSetCodeHack(pCPU, 0x800BDC34, 0x860B000A, 0x5825)) {
                return 0;
            }
        } else {
            if (!cpuSetCodeHack(pCPU, 0x80178A80, 0x95630000, -1)) {
                return 0;
            }
        }

        pCPU->nCompileFlag |= 0x1010;
    } else if (romTestCode(pROM, "NPWE")) {
        // Pilotwings 64
        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
        mcardOpen(&mCard, "PILOT", "Pilotwings", mCard.saveIcon, mCard.saveBanner, "PILOT",
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
    } else if (romTestCode(pROM, "NAFJ")) {
        // Animal Forest
        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);
        mcardOpen(&mCard, "AF", "Animal Forest", mCard.saveIcon, mCard.saveBanner, "AF",
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);
    } else if (romTestCode(pROM, "NBCE")) {
        // Blast Corps
        if (!cpuSetCodeHack(pCPU, 0x80244CFC, 0x1420FFFA, 0)) {
            return 0;
        }
    } else if (!romTestCode(pROM, "NBKE") && !romTestCode(pROM, "NGEE") && !romTestCode(pROM, "NFUE")) {
        if (romTestCode(pROM, "NBYE")) {
            // A Bug's Life
            if (!cpuSetCodeHack(pCPU, 0x8007ADD0, 0x1440FFF9, 0)) {
                return 0;
            }
        } else if (romTestCode(pROM, "NCUE")) {
            // Cruis'n USA
            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                return 0;
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                return 0;
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);
            mcardOpen(&mCard, "CRUISE", "Cruise 'n USA", mCard.saveIcon, mCard.saveBanner, "CRUISE",
                      &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);

            if (!cpuSetCodeHack(pCPU, 0x80103E0C, 0x1616FFF2, 0)) {
                return 0;
            }
        } else if (!romTestCode(pROM, "NDNE")) {
            if (romTestCode(pROM, "NDOE")) {
                // Donkey Kong 64
                if (!cpuSetCodeHack(pCPU, 0x80000A04, 0x1462FFFF, 0)) {
                    return 0;
                }
            } else if ((romTestCode(pROM, "NN6E")) || (romTestCode(pROM, "NN6J"))) {
                // Dr. Mario 64
                nTickMultiplier = 3;

                if (!cpuSetCodeHack(pCPU, 0x800005EC, 0x3C028001, -1)) {
                    return 0;
                }

                if (romTestCode(pROM, "NN6J")) {
                    if (!cpuSetCodeHack(pCPU, 0x8006D458, 0x0C0189E9, 0x0C0189A3)) {
                        return 0;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8006D664, 0x0C0189E9, 0x0C0189A3)) {
                        return 0;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8006D6D0, 0x0C0189E9, 0x0C0189A3)) {
                        return 0;
                    }
                } else {
                    if (!cpuSetCodeHack(pCPU, 0x8006D338, 0x0C0189A9, 0x0C018963)) {
                        return 0;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8006D544, 0x0C0189A9, 0x0C018963)) {
                        return 0;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8006D5B0, 0x0C0189A9, 0x0C018963)) {
                        return 0;
                    }
                }

                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, "DRMARIO", "Dr. Mario", mCard.saveIcon, mCard.saveBanner, "DRMARIO",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
                gpSystem->eTypeROM = SRT_DRMARIO;
                pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x10);
            } else if (romTestCode(pROM, "CFZE")) {
                // F-Zero X
                if (!cpuSetCodeHack(pCPU, 0x800673A8, 0x144DFFFC, 0)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x80067564, 0x144FFFFC, 0)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x8006759C, 0x1459FFFC, 0)) {
                    return 0;
                }
            } else if (romTestCode(pROM, "NLRE")) {
                // Lode Runner 3D
                if (!cpuSetCodeHack(pCPU, 0x80097B6C, 0x1443FFF9, 0)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x80097BF4, 0x1443FFF9, 0)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x80096D08, 0x08025B40, 0x1000FFFF)) {
                    return 0;
                }
            } else if (romTestCode(pROM, "NMFE")) {
                // Mario Golf
                if (!cpuSetCodeHack(pCPU, 0x800B2DCC, 0x8C430004, -1)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x800B2E70, 0x8C430004, -1)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x80029EB8, 0x8C4252CC, -1)) {
                    return 0;
                }
            } else if (romTestCode(pROM, "NKTE")) {
                // Mario Kart 64
                pSystem->eTypeROM = SRT_MARIOKART;

                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, "KART", "Mario Kart", mCard.saveIcon, mCard.saveBanner, "KART",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
                pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x10);
            } else if (romTestCode(pROM, "NK4E")) {
                // Kirby 64
                if (!audioEnable(SYSTEM_AUDIO(pSystem), 0)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x80020BCC, 0x8DF80034, -1)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x80020EBC, 0x8DEFF330, -1)) {
                    return 0;
                }
            } else if (romTestCode(pROM, "CLBE")) {
                // Mario Party 1
                pSystem->eTypeROM = SRT_MARIOPARTY1;

                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, "MP1", "Mario Party 1", mCard.saveIcon, mCard.saveBanner, "MP1",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
            } else if (romTestCode(pROM, "NMWE")) {
                // Mario Party 2
                pSystem->eTypeROM = SRT_MARIOPARTY2;

                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, "MP2", "Mario Party 2", mCard.saveIcon, mCard.saveBanner, "MP2",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
            } else if (romTestCode(pROM, "NMVE")) {
                // Mario Party 3
                pSystem->eTypeROM = SRT_MARIOPARTY3;

                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, "MP3", "Mario Party 3", mCard.saveIcon, mCard.saveBanner, "MP3",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x800);
            } else if (!romTestCode(pROM, "NM3E") && !romTestCode(pROM, "NRIE")) {
                if (romTestCode(pROM, "NMQE")) {
                    // Paper Mario
                    if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                        !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                        return 0;
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                    if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                        !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                        return 0;
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);

                    mcardOpen(&mCard, "PaperMario", "Paper Mario", mCard.saveIcon, mCard.saveBanner, "PAPERMARIO",
                              &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);
                } else if (romTestCode(pROM, "NPOE")) {
                    if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                        !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                        return 0;
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                    if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                        !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                        return 0;
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                    mcardOpen(&mCard, "PokemonStadium", "Pokemon Stadium", mCard.saveIcon, mCard.saveBanner,
                              "POKEMONSTADIUM", &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000,
                              0x20000);
                } else if (romTestCode(pROM, "NQKE")) {
                    if (!cpuSetCodeHack(pCPU, 0x8004989C, 0x1459FFFB, 0)) {
                        return 0;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x80049FF0, 0x1608FFFB, 0)) {
                        return 0;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8004A384, 0x15E0FFFB, 0)) {
                        return 0;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8004A97C, 0x15E0FFFB, 0)) {
                        return 0;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x80048FF8, 0x1000FFFD, 0x1000FFFF)) {
                        return 0;
                    }
                } else if (!romTestCode(pROM, "NRSE") && !romTestCode(pROM, "NRZE")) {
                    if (romTestCode(pROM, "NFXE") || romTestCode(pROM, "NFXJ")) {
                        pSystem->eTypeROM = SRT_STARFOX;

                        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                            return 0;
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                            return 0;
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                        mcardOpen(&mCard, "STARFOX", "Starfox", mCard.saveIcon, mCard.saveBanner, "STARFOX",
                                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
                        pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x110);
                    } else if (romTestCode(pROM, "NGUJ")) {
                        if (!cpuSetCodeHack(pCPU, 0x80025D30, 0x3C018006, -1)) {
                            return 0;
                        }
                    } else if (romTestCode(pROM, "NALE")) {
                        if (!cpuSetCodeHack(pCPU, 0x8000092C, 0x3C028004, -1)) {
                            return 0;
                        }
                        if (!cpuSetCodeHack(pCPU, 0x8002103C, 0x3C028004, -1)) {
                            return 0;
                        }
                        if (!cpuSetCodeHack(pCPU, 0x80021048, 0x3C028004, -1)) {
                            return 0;
                        }
                        if (!cpuSetCodeHack(pCPU, 0x800A1BB8, 0x1440FFFD, 0)) {
                            return 0;
                        }
                        if (!cpuSetCodeHack(pCPU, 0x800A1BE0, 0x1440FFFD, 0)) {
                            return 0;
                        }
                        pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x110);
                    } else if (romTestCode(pROM, "NTEA")) {
                        pSystem->eTypeROM = SRT_1080;

                        if (!ramGetBuffer(SYSTEM_RAM(pSystem), &anMode, 0x300U, NULL)) {
                            return 0;
                        }

                        anMode[4] = 0x17D7;
                        if (!ramGetBuffer(SYSTEM_RAM(pSystem), &anMode, 0x200U, NULL)) {
                            return 0;
                        }

                        anMode[0] = 0xAC290000;
                        if (!ramGetBuffer(SYSTEM_RAM(pSystem), &anMode, 0x284U, NULL)) {
                            return 0;
                        }

                        anMode[0] = 0x240B17D7;
                        if (!cpuSetCodeHack(pCPU, 0x800F04E8, 0x1218FFFB, 0)) {
                            return 0;
                        }

                        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                            return 0;
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, NULL)) {
                            return 0;
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                        mcardOpen(&mCard, "1080", "1080", mCard.saveIcon, mCard.saveBanner, "1080",
                                  &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
                    } else if (!romTestCode(pROM, "NTPE") && !romTestCode(pROM, "NEPE")) {
                        if (romTestCode(pROM, "NM8E")) {
                            if (!cpuSetCodeHack(pCPU, 0x80031D94, 0x8C421F6C, -1)) {
                                return 0;
                            }
                        } else if (romTestCode(pROM, "NYLJ")) {
                            pSystem->eTypeROM = SRT_PANEL;
                            if (!cpuSetCodeHack(pCPU, 0x800A58F8, 0x8C62FF8C, -1)) {
                                return 0;
                            }

                            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0,
                                                  NULL)) {
                                return 0;
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                            if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                                !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0,
                                                  NULL)) {
                                return 0;
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);

                            mcardOpen(&mCard, "PANEL", "Panel de Pon", mCard.saveIcon, mCard.saveBanner, "PANEL",
                                      &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
                            pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x10);
                        } else if (romTestCode(pROM, "NTUE")) {
                            if (!cpuSetCodeHack(pCPU, 0x8002BDD0, 0xA0000000, 0)) {
                                return 0;
                            }
                        } else if (romTestCode(pROM, "NWRE")) {
                            pSystem->eTypeROM = SRT_WAVERACE;

                            if (!cpuSetCodeHack(pCPU, 0x8004795C, 0x1448FFFC, 0)) {
                                return 0;
                            }

                            if (!cpuSetCodeHack(pCPU, 0x80047994, 0x144AFFFC, 0)) {
                                return 0;
                            }

                            pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x10);
                        } else if (romTestCode(pROM, "NYSE")) {
                            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1 &&
                                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0,
                                                  NULL)) {
                                return 0;
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                            if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                                !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0,
                                                  NULL)) {
                                return 0;
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                            mcardOpen(&mCard, "YoshiStory", "YoshiStory", mCard.saveIcon, mCard.saveBanner,
                                      "YoshiStory", &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000,
                                      0x800);
                        } else if (romTestCode(pROM, "NBNJ")) {
                            mcardOpen(&mCard, "XXX", "XXX", mCard.saveIcon, mCard.saveBanner, "XXX",
                                      &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x800);

                            if (!cpuSetCodeHack(pCPU, 0x80000548, 0x08000156, 0x1000FFFF)) {
                                return 0;
                            }

                            if (!cpuSetCodeHack(pCPU, 0x80000730, 0x3C02800C, -1)) {
                                return 0;
                            }
                        } else if (!romGetCode(pROM, acCode)) {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    if (!soundSetBufferSize(SYSTEM_SOUND(gpSystem), nSizeSound)) {
        return 0;
    }

    pCPU->nTimeRetrace = nTimeRetrace;
    systemSetControllerConfiguration(&gSystemRomConfigurationList[0],
                                     gSystemRomConfigurationList[i].currentControllerConfig, 0);

    for (iController = 0; iController < 4; iController++) {
        simulatorSetControllerMap((u32*)gSystemRomConfigurationList[i].controllerConfiguration[iController],
                                  iController);

        if (gSystemRomConfigurationList[i].storageDevice & 0x10) {
            if (!pifSetControllerType(pPIF, iController, 2)) {
                return 0;
            }
        } else if ((1 << (iController << 3)) & gSystemRomConfigurationList[0].rumbleConfiguration) {
            if (!pifSetControllerType(pPIF, iController, 3)) {
                return 0;
            }
        } else if (!pifSetControllerType(pPIF, iController, 1)) {
            return 0;
        }
    }

    if (mCard.saveToggle == 1) {
        systemSetControllerConfiguration(&gSystemRomConfigurationList[0], mCard.file.game.configuration, 0);
    }

    return 1;
}

static s32 systemGetException(System* pSystem, SystemInterruptType eType, SystemException* pException) {
    pException->nMask = 0;
    pException->szType = "";
    pException->eType = eType;
    pException->eCode = CEC_NONE;
    pException->eTypeMips = MIT_NONE;

    switch (eType) {
        case SIT_SW0:
            pException->nMask = 5;
            pException->szType = "SW0";
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_SW1:
            pException->nMask = 6;
            pException->szType = "SW1";
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_CART:
            pException->nMask = 0xC;
            pException->szType = "CART";
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_COUNTER:
            pException->nMask = 0x84;
            pException->szType = "COUNTER";
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_RDB:
            pException->nMask = 0x24;
            pException->szType = "RDB";
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_SP:
            pException->nMask = 4;
            pException->szType = "SP";
            pException->eTypeMips = MIT_SP;
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_SI:
            pException->nMask = 4;
            pException->szType = "SI";
            pException->eTypeMips = MIT_SI;
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_AI:
            pException->nMask = 4;
            pException->szType = "AI";
            pException->eTypeMips = MIT_AI;
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_VI:
            pException->nMask = 4;
            pException->szType = "VI";
            pException->eTypeMips = MIT_VI;
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_PI:
            pException->nMask = 4;
            pException->szType = "PI";
            pException->eTypeMips = MIT_PI;
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_DP:
            pException->nMask = 4;
            pException->szType = "DP";
            pException->eTypeMips = MIT_DP;
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_CPU_BREAK:
            pException->szType = "BREAK (CPU)";
            pException->eCode = CEC_BREAK;
            break;
        case SIT_SP_BREAK:
            pException->nMask = 4;
            pException->szType = "BREAK (SP)";
            pException->eCode = CEC_INTERRUPT;
            break;
        case SIT_FAULT:
            pException->szType = "FAULT";
            break;
        case SIT_THREADSTATUS:
            pException->szType = "THREADSTATUS";
            break;
        case SIT_PRENMI:
            pException->szType = "PRENMI";
            pException->eCode = CEC_INTERRUPT;
            break;
        default:
            return 0;
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/system/systemPut64.s")

static s32 __systemCopyROM_Complete(void) {
    s32 iAddress;
    s32 nCount;
    u32 nAddress0;
    u32 nAddress1;
    u32 anAddress[0x20]; // size = 0x80

    nAddress0 = gpSystem->romCopy.nOffsetRAM;
    nAddress1 = nAddress0 + gpSystem->romCopy.nSize - 1;

    if (!frameInvalidateCache(SYSTEM_FRAME(gpSystem), gpSystem->romCopy.nOffsetRAM,
                              gpSystem->romCopy.nOffsetRAM + gpSystem->romCopy.nSize - 1)) {
        return 0;
    }

    if (!rspInvalidateCache(SYSTEM_RSP(gpSystem), nAddress0, nAddress1)) {
        return 0;
    }

    if (!cpuGetOffsetAddress(SYSTEM_CPU(gpSystem), anAddress, &nCount, gpSystem->romCopy.nOffsetRAM,
                             gpSystem->romCopy.nSize)) {
        return 0;
    }

    for (iAddress = 0; iAddress < nCount; iAddress++) {
        nAddress0 = anAddress[iAddress];
        nAddress1 = nAddress0 + gpSystem->romCopy.nSize - 1;
        if (!cpuInvalidateCache(SYSTEM_CPU(gpSystem), nAddress0, nAddress1)) {
            return 0;
        }
    }

    gpSystem->romCopy.nSize = 0;
    if ((gpSystem->romCopy.pCallback != NULL) && !gpSystem->romCopy.pCallback()) {
        return 0;
    }

    return 1;
}

s32 systemCopyROM(System* pSystem, s32 nOffsetRAM, s32 nOffsetROM, s32 nSize, SystemCopyCallbackFunc pCallback) {
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

    NO_INLINE();
    return 1;
}

s32 systemSetMode(System* pSystem, SystemMode eMode) {
    if (xlObjectTest(pSystem, &gClassSystem)) {
        pSystem->eMode = eMode;

        if (eMode == SM_STOPPED) {
            pSystem->nAddressBreak = -1;
        }

        return 1;
    }

    return 0;
}

s32 systemGetMode(System* pSystem, SystemMode* peMode) {
    if (xlObjectTest(pSystem, &gClassSystem) && (peMode != NULL)) {
        *peMode = pSystem->eMode;
        return 1;
    }

    return 0;
}

s32 systemSetStorageDevice(System* pSystem, SystemObjectType eStorageDevice) {
    pSystem->storageDevice = eStorageDevice;

    if (eStorageDevice == SOT_FLASH) {
        if (!xlObjectMake(&pSystem->apObject[SOT_FLASH], pSystem, &gClassFlash)) {
            return 0;
        }

        if (!cpuMapObject(SYSTEM_CPU(pSystem), pSystem->apObject[SOT_FLASH], 0x08000000, 0x0801FFFF, 0)) {
            return 0;
        }
    }

    if (eStorageDevice == SOT_SRAM) {
        if (!xlObjectMake(&pSystem->apObject[SOT_SRAM], pSystem, &gClassSram)) {
            return 0;
        }

        if (!cpuMapObject(SYSTEM_CPU(pSystem), pSystem->apObject[SOT_SRAM], 0x08000000, 0x08007FFF, 0)) {
            return 0;
        }
    }

    NO_INLINE();
    return 1;
}

s32 systemGetStorageDevice(System* pSystem, SystemObjectType* pStorageDevice) {
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

        if (!ramWipe(SYSTEM_RAM(pSystem))) {
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

        for (eObject = 0; eObject < SOT_COUNT; eObject++) {
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

inline s32 systemTestClassObject(System* pSystem) {
    if (xlObjectTest(pSystem, &gClassSystem)) {
        pSystem->eMode = SM_STOPPED;
        pSystem->nAddressBreak = -1;

        return 1;
    }

    return 0;
}

s32 systemExecute(System* pSystem, s32 nCount) {
    if (!cpuExecute(SYSTEM_CPU(pSystem), pSystem->nAddressBreak)) {
        if (!systemTestClassObject(pSystem)) {
            return 0;
        }

        return 0;
    }

    if (pSystem->nAddressBreak == SYSTEM_CPU(pSystem)->nPC) {
        if (!systemTestClassObject(pSystem)) {
            return 0;
        }
    }

    return 1;
}

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
                        ((exception.eTypeMips == MIT_NONE) ||
                         mipsSetInterrupt(SYSTEM_MIPS(pSystem), exception.eTypeMips))) {
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

s32 systemExceptionPending(System* pSystem, SystemInterruptType nException) {
    if ((nException > -1) && (nException < ARRAY_COUNT(pSystem->anException))) {
        if (pSystem->anException[nException] != 0) {
            return 1;
        }

        return 0;
    }

    return 0;
}

inline s32 systemClearExceptions(System* pSystem) {
    int iException;

    pSystem->bException = 0;
    for (iException = 0; iException < 16; iException++) {
        pSystem->anException[iException] = 0;
    }
    return 1;
}

s32 systemEvent(System* pSystem, s32 nEvent, void* pArgument) {
    Cpu* pCPU;
    SystemException exception;
    SystemObjectType eObject;
    SystemObjectType storageDevice;

    switch (nEvent) {
        case 2:
            pSystem->eMode = SM_STOPPED;
            pSystem->eTypeROM = SRT_NONE;
            pSystem->nAddressBreak = -1;
            pSystem->bJapaneseVersion = 0;
            pSystem->romCopy.nSize = 0;
            pSystem->pFrame = gpFrame;
            pSystem->pSound = gpSound;

            for (eObject = 0; eObject < SOT_COUNT; eObject++) {
                pSystem->apObject[eObject] = NULL;
            }

            systemClearExceptions(pSystem);

            for (eObject = 0; eObject < SOT_COUNT; eObject++) {
                switch (eObject) {
                    case SOT_CPU:
                        if (!xlObjectMake(&pSystem->apObject[SOT_CPU], pSystem, &gClassCPU)) {
                            return 0;
                        }
                        pCPU = SYSTEM_CPU(pSystem);
                        if (!cpuMapObject(pCPU, pSystem, 0, 0xFFFFFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_PIF:
                        if (!xlObjectMake(&pSystem->apObject[SOT_PIF], pSystem, &gClassPIF)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_PIF], 0x1FC00000, 0x1FC007FF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_RAM:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RAM], pSystem, &gClassRAM)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RAM], 0, 0x03EFFFFF, 0x100)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RAM], 0x03F00000, 0x03FFFFFF, 2)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RAM], 0x04700000, 0x047FFFFF, 1)) {
                            return 0;
                        }
                        break;
                    case SOT_ROM:
                        if (!xlObjectMake(&pSystem->apObject[SOT_ROM], pSystem, &gClassROM)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_ROM], 0x10000000, 0x1FBFFFFF, 0)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_ROM], 0x1FF00000, 0x1FF0FFFF, 1)) {
                            return 0;
                        }
                        break;
                    case SOT_RSP:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RSP], pSystem, &gClassRSP)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RSP], 0x04000000, 0x040FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_RDP:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RDP], pSystem, &gClassRDP)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RDP], 0x04100000, 0x041FFFFF, 0)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RDP], 0x04200000, 0x042FFFFF, 1)) {
                            return 0;
                        }
                        break;
                    case SOT_MIPS:
                        if (!xlObjectMake(&pSystem->apObject[SOT_MIPS], pSystem, &gClassMips)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_MIPS], 0x04300000, 0x043FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_DISK:
                        if (!xlObjectMake(&pSystem->apObject[SOT_DISK], pSystem, &gClassDisk)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_DISK], 0x05000000, 0x05FFFFFF, 0)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_DISK], 0x06000000, 0x06FFFFFF, 1)) {
                            return 0;
                        }
                        break;
                    case SOT_FLASH:
                        pSystem->apObject[SOT_FLASH] = NULL;
                        break;
                    case SOT_SRAM:
                        pSystem->apObject[SOT_SRAM] = NULL;
                        break;
                    case SOT_AUDIO:
                        if (!xlObjectMake(&pSystem->apObject[SOT_AUDIO], pSystem, &gClassAudio)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_AUDIO], 0x04500000, 0x045FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_VIDEO:
                        if (!xlObjectMake(&pSystem->apObject[SOT_VIDEO], pSystem, &gClassVideo)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_VIDEO], 0x04400000, 0x044FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_SERIAL:
                        if (!xlObjectMake(&pSystem->apObject[SOT_SERIAL], pSystem, &gClassSerial)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_SERIAL], 0x04800000, 0x048FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_LIBRARY:
                        if (!xlObjectMake(&pSystem->apObject[SOT_LIBRARY], pSystem, &gClassLibrary)) {
                            return 0;
                        }
                        break;
                    case SOT_PERIPHERAL:
                        if (!xlObjectMake(&pSystem->apObject[SOT_PERIPHERAL], pSystem, &gClassPeripheral)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_PERIPHERAL], 0x04600000, 0x046FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_RDB:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RDB], pSystem, &gClassRdb)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RDB], 0x04900000, 0x0490FFFF, 0)) {
                            return 0;
                        }
                        break;
                    default:
                        return 0;
                }
            }
            break;
        case 3:
            for (storageDevice = 0; storageDevice < SOT_COUNT; storageDevice++) {
                if ((storageDevice != SOT_FLASH) && (storageDevice != SOT_SRAM)) {
                    if (!xlObjectFree(&pSystem->apObject[storageDevice])) {
                        return 0;
                    }
                } else if (storageDevice == SOT_FLASH) {
                    if ((pSystem->storageDevice == SOT_FLASH) && !xlObjectFree(&pSystem->apObject[SOT_FLASH])) {
                        return 0;
                    }
                } else if ((storageDevice == SOT_SRAM) && (pSystem->storageDevice == SOT_SRAM) &&
                           !xlObjectFree(&pSystem->apObject[SOT_SRAM])) {
                    return 0;
                }
            }
            break;
        case 0x1001:
            if (!systemGetException(pSystem, (SystemInterruptType)pArgument, &exception)) {
                return 0;
            }
            if (exception.eTypeMips != MIT_NONE) {
                mipsResetInterrupt(SYSTEM_MIPS(pSystem), exception.eTypeMips);
            }
            break;
        case 0x1000:
            if (((SystemInterruptType)pArgument > SIT_NONE) && ((SystemInterruptType)pArgument < SIT_COUNT)) {
                pSystem->bException = 1;
                pSystem->anException[(SystemInterruptType)pArgument]++;
                break;
            }
            return 0;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pSystem), pArgument, (Put8Func)systemPut8, (Put16Func)systemPut16,
                                 (Put32Func)systemPut32, (Put64Func)systemPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pSystem), pArgument, (Get8Func)systemGet8, (Get16Func)systemGet16,
                                 (Get32Func)systemGet32, (Get64Func)systemGet64)) {
                return 0;
            }
            break;
        case 0:
        case 1:
        case 5:
        case 6:
        case 7:
        case 0x1003:
            break;
        default:
            return 0;
    }

    return 1;
}
