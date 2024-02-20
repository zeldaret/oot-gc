#include "macros.h"
#include "xlObject.h"
#include "system.h"
#include "rom.h"
#include "ram.h"
#include "cpu.h"
#include "mcard.h"
#include "pif.h"
#include "simGCN.h"

s32 systemEvent(System* pSystem, s32 nEvent, void* pArgument);

char D_800EB300[] = "SYSTEM (N64)";

_XL_OBJECTTYPE gClassSystem = {
    // size = 0x10
    D_800EB300,
    sizeof(System),
    NULL,
    (EventFunc)systemEvent,
};

// clang-format off
static u32 contMap[4][20] = { // size = 0x140
    // 1
    0x80000000, 0x40000000, 0x00000000, 0x00000000, 0x00200000,
    0x00100000, 0x20000000, 0x10000000, 0x08000000, 0x04000000, 
    0x02000000, 0x01000000, 0x08000000, 0x04000000, 0x02000000, 
    0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,
 
    // 2
    0x80000000, 0x40000000, 0x00000000, 0x00000000, 0x20000000, 
    0x00100000, 0x20000000, 0x10000000, 0x08000000, 0x04000000, 
    0x02000000, 0x01000000, 0x08000000, 0x04000000, 0x02000000, 
    0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,

    // 3
    0x80000000, 0x40000000, 0x00010000, 0x00020000, 0x20000000,
    0x00100000, 0x00040000, 0x10000000, 0x08000000, 0x04000000, 
    0x02000000, 0x01000000, 0x00200000, 0x00200000, 0x00200000, 
    0x00200000, 0x00080000, 0x00040000, 0x00020000, 0x00010000, 

    // 4
    0x80000000, 0x40000000, 0x00200000, 0x00000000, 0x20000000, 
    0x00100000, 0x20000000, 0x10000000, 0x08000000, 0x04000000, 
    0x02000000, 0x01000000, 0x08000000, 0x04000000, 0x02000000,
    0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,
};
// clang-format on

void* jtbl_800EB460[] = {
    (void*)0x8002CC70, (void*)0x8002CCBC, (void*)0x8002CD04, (void*)0x8002CD9C, (void*)0x8002CE0C, (void*)0x8002CE54,
    (void*)0x8002CEC4, (void*)0x8002CF0C, (void*)0x8002CF7C, (void*)0x8002CF88, (void*)0x8002CF94, (void*)0x8002CFDC,
    (void*)0x8002D024, (void*)0x8002D070, (void*)0x8002D090, (void*)0x8002D0DC,
};

//! TODO: remove these (needed for systemGetException.s)
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

SystemRomConfig gSystemRomConfigurationList[1];

u32 nTickMultiplier = 2;
f32 fTickScale = 1.0;

//! TODO: remove these (needed for systemGetException.s)
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

//! TODO: remove later
static char D_80134EB0[] = "NSME"; // Super Mario 64
static char D_80134EB8[] = "NSMJ"; // Super Mario 64

static char D_80134EC0[] = "MARIO";

//! TODO: remove later
static char D_80134EC8[] = "CZLE"; // Ocarina of Time
static char D_80134ED0[] = "CZLJ"; // Ocarina of Time

static char D_80134ED8[] = "ZELDA1";
static char D_80134EE0[] = "ZELDAX";
static char D_80134EE8[] = "ZELDA";
static char D_80134EF0[] = "ZELDAD";

//! TODO: remove later
static char D_80134EF8[] = "NZSJ"; // Majora's Mask
static char D_80134F00[] = "NZSE"; // Majora's Mask

static char D_80134F08[] = "ZELDA3";

//! TODO: remove later
static char D_80134F10[] = "NPWE";
static char D_80134F18[] = "PILOT";
static char D_80134F20[] = "NAFJ";

static char D_80134F28[] = "AF";
static char D_80134F2C[] = "NBCE";
static char D_80134F34[] = "NBKE";
static char D_80134F3C[] = "NGEE";
static char D_80134F44[] = "NFUE";
static char D_80134F4C[] = "NBYE";

//! TODO: remove later
static char D_80134F54[] = "NCUE";

static char D_80134F5C[] = "CRUISE";
static char D_80134F64[] = "NDNE";
static char D_80134F6C[] = "NDOE";

//! TODO: remove later
static char D_80134F74[] = "NN6E";
static char D_80134F7C[] = "NN6J";

static char D_80134F84[] = "DRMARIO";
static char D_80134F8C[] = "CFZE";
static char D_80134F94[] = "NLRE";
static char D_80134F9C[] = "NMFE";

//! TODO: remove later
static char D_80134FA4[] = "NKTE";

static char D_80134FAC[] = "KART";
static char D_80134FB4[] = "NK4E";
static char D_80134FBC[] = "CLBE";
static char D_80134FC4[] = "MP1";
static char D_80134FC8[] = "NMWE";
static char D_80134FD0[] = "MP2";

//! TODO: remove later
static char D_80134FD4[] = "NMVE";

static char D_80134FDC[] = "MP3";
static char D_80134FE0[] = "NM3E";
static char D_80134FE8[] = "NRIE";

//! TODO: remove later
static char D_80134FF0[] = "NMQE";
static char D_80134FF8[] = "NPOE";

static char D_80135000[] = "NQKE";
static char D_80135008[] = "NRSE";
static char D_80135010[] = "NRZE";

//! TODO: remove later
static char D_80135018[] = "NFXE";
static char D_80135020[] = "NFXJ";

static char D_80135028[] = "STARFOX";
static char D_80135030[] = "Starfox";
static char D_80135038[] = "NGUJ";
static char D_80135040[] = "NALE";

//! TODO: remove later
static char D_80135048[] = "NTEA";

static char D_80135050[] = "1080";
static char D_80135058[] = "NTPE";
static char D_80135060[] = "NEPE";
static char D_80135068[] = "NM8E";

//! TODO: remove later
static char D_80135070[] = "NYLJ";

static char D_80135078[] = "PANEL";
static char D_80135080[] = "NTUE";
static char D_80135088[] = "NWRE";

//! TODO: remove later
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

s32 simulatorGetArgument(SystemArgumentType eType, char** pszArgument);
s32 simulatorCopyControllerMap(u32* mapDataOutput, u32* mapDataInput);

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

    if (simulatorGetArgument(SAT_XTRA, &szExtra)) {
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

    if (romTestCode(pROM, D_80134EB0) || romTestCode(pROM, D_80134EB8)) {
        // Super Mario 64 ("NSME", "NSMJ")
        systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x01010101, 0);
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, D_80134EC8) || romTestCode(pROM, D_80134ED0)) {
        // Ocarina of Time ("CZLE", "CZLJ")
        gSystemRomConfigurationList[index].storageDevice = SOT_PIF;

        if (!simulatorGetArgument(SAT_VIBRATION, &szText) || (*szText == 49)) {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == 48)) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x82828282, 1);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x80808080, 1);
            }
        } else if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == 48)) {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x02020202, 1);
        } else {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, 1);
        }

    } else if (romTestCode(pROM, D_80134EF8) || romTestCode(pROM, D_80134F00)) {
        // Majora's Mask ("NZSE", "NZSJ")
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

        if (!simulatorGetArgument(SAT_VIBRATION, &szText) || (*szText == 49)) {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == 48)) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x82828282, 1);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x80808080, 1);
            }
        } else if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == 48)) {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x02020202, 1);
        } else {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, 1);
        }

    } else if (romTestCode(pROM, D_80134F10)) {
        // Pilotwings 64 ("NPWE")
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, D_80134F20)) {
        // Animal Forest ("NAFJ")
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

    } else if (romTestCode(pROM, D_80134F54)) {
        // Cruis'n ("NCUE")
        gSystemRomConfigurationList[index].storageDevice = 20; // bug?

    } else if (romTestCode(pROM, D_80134FA4)) {
        // Mario Kart 64 ("NKTE")
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, D_80135018) || romTestCode(pROM, D_80135020)) {
        // Star Fox 64 ("NFXE", "NFXJ")
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, D_80134FD4)) {
        // Mario Party 3 ("NMVE")
        gSystemRomConfigurationList[index].storageDevice = SOT_FLASH;

    } else if (romTestCode(pROM, D_80135090)) {
        // Yoshi's Story ("NYSE")
        gSystemRomConfigurationList[index].storageDevice = SOT_FLASH;

    } else if (romTestCode(pROM, D_80135048)) {
        // 1080° Snowboarding ("NTEA")
        gSystemRomConfigurationList[index].storageDevice = SOT_PIF;

    } else if (romTestCode(pROM, D_80134FF0)) {
        // Paper Mario ("NMQE")
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

    } else if (romTestCode(pROM, D_80134FF8)) {
        // Pokémon Stadium ("NPOE")
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

    } else if (romTestCode(pROM, D_80135070)) {
        // Panel de Pon 64 ("NYLJ")
        gSystemRomConfigurationList[index].storageDevice = SOT_PIF;

    } else if (romTestCode(pROM, D_80134F74) || romTestCode(pROM, D_80134F7C)) {
        // Dr. Mario 64 ("NN6E", "NN6J")
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, D_80135098)) {
        // Bakuretsu Muteki Bangaioh ("NBNJ")
        gSystemRomConfigurationList[index].storageDevice = SOT_FLASH;
    }

    return 1;
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/system/systemSetupGameALL.s")
#else
//! TODO: remove when sdk headers are here
extern u32 __OSBusClock : 0x800000F8;
#define OS_BUS_CLOCK (__OSBusClock)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSSecondsToTicks(sec) ((sec)*OS_TIMER_CLOCK)

extern s32 gz_bnrSize;
extern s32 gz_iconSize;
extern MemCard mCard;

s32 simulatorSetControllerMap(u32* mapData, s32 channel);
s32 cpuSetCodeHack(Cpu* pCPU, s32 nAddress, s32 nOpcodeOld, s32 nOpcodeNew);
s32 mcardOpen(MemCard* pMCard, char* fileName, char* comment, char* icon, char* banner, char* gameName,
              s32* defaultConfiguration, s32 fileSize, s32 gameSize);
s32 systemSetupGameALL(System* pSystem) {
    // Parameters
    // struct __anon_0x37240* pSystem; // r18

    // Local variables
    s32 nSizeSound; // r23
    s32 iController; // r21
    s32 nSize; // r1+0x60
    u32* anMode; // r1+0x5C
    s32 i; // r25
    u64 nTimeRetrace; // r1+0x10
    char acCode[5]; // r1+0x54
    DVDFileInfo fileInfo; // r1+0x18
    Cpu* pCPU; // r31
    Rom* pROM; // r19
    Pif* pPIF; // r29
    s32 defaultConfiguration; // r1+0x14

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

    // ?????
    anMode[0] = 1;
    anMode[1] = 0;
    anMode[2] = 0xB0000000;
    anMode[3] = 0;
    anMode[4] = 0x17D7;
    anMode[5] = 1;

    nTimeRetrace = OSSecondsToTicks(D_80135F90);

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
    } else if (gSystemRomConfigurationList[i].storageDevice & 2) {
        if (!systemSetStorageDevice(pSystem, SOT_FLASH)) {
            return 0;
        }
    } else if (!systemSetStorageDevice(pSystem, SOT_NONE)) {
        return 0;
    }

    if (gSystemRomConfigurationList[i].storageDevice & 4) {
        if (!pifSetEEPROMType(pPIF, CT_4K)) {
            return 0;
        }
    } else if (gSystemRomConfigurationList[i].storageDevice & 8) {
        if (!pifSetEEPROMType(pPIF, CT_16K)) {
            return 0;
        }
    } else if (!pifSetEEPROMType(pPIF, CT_NONE)) {
        return 0;
    }

    if (romTestCode(pROM, D_80134EB0) || romTestCode(pROM, D_80134EB8)) {
        // Super Mario 64 ("NSME", "NSMJ")
        pSystem->eTypeROM = SRT_MARIO;
        nSizeSound = 0x1000;

        if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

        if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
        mcardOpen(&mCard, D_80134EC0, D_800EB528, mCard.saveIcon, mCard.saveBanner, D_80134EC0,
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);

        if (!cpuSetCodeHack(pCPU, 0x80317938, 0x5420FFFE, 0)) {
            return 0;
        }
    } else if (romTestCode(pROM, D_80134EC8) || romTestCode(pROM, D_80134ED0)) {
        // Ocarina of Time ("CZLE", "CZLJ")
        pSystem->eTypeROM = SRT_ZELDA1;
        nSizeSound = 0x1000;

        if (gnFlagZelda & 1) {
            if (romTestCode(pROM, D_80134EC8)) {
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
        } else if (romTestCode(pROM, D_80134EC8)) {
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
                if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, D_80134ED8, D_800EB534, mCard.saveIcon, mCard.saveBanner, D_80134EE0,
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
            } else {
                if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, D_80134ED8, D_800EB534, mCard.saveIcon, mCard.saveBanner, D_80134EE8,
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
            }
        } else {
            // debug rom?
            if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                return 0;
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

            if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                return 0;
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
            mcardOpen(&mCard, D_80134EF0, D_800EB548, mCard.saveIcon, mCard.saveBanner, D_80134EF0,
                      &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
        }

        pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x110);
    } else if (romTestCode(pROM, D_80134EF8) || romTestCode(pROM, D_80134F00)) {
        // Majora's Mask
        pSystem->eTypeROM = SRT_ZELDA2;
        nSizeSound = 0x1000;

        if (romTestCode(pROM, D_80134EF8)) {
            pSystem->bJapaneseVersion = 1;
        } else {
            pSystem->bJapaneseVersion = 0;
        }

        nTickMultiplier = 2;
        fTickScale = D_80135F94;

        if (!ramGetBuffer(SYSTEM_RAM(pSystem), &anMode, 0x300U, NULL)) {
            return 0;
        }

        anMode[4] = 0x17D9;

        if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

        if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
        mcardOpen(&mCard, D_80134F08, D_800EB564, mCard.saveIcon, mCard.saveBanner, D_80134F08,
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);

        if (gnFlagZelda & 1) {
            if (cpuSetCodeHack(pCPU, 0x801C6FC0, 0x95630000, -1) == 0) {
                return 0;
            }
        } else if (romTestCode(pROM, D_80134EF8)) {
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
        } else if (!cpuSetCodeHack(pCPU, 0x80178A80, 0x95630000, -1)) {
            return 0;
        }

        pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x1010);
    } else if (romTestCode(pROM, D_80134F10)) {
        // Pilotwings 64
        if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

        if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
        mcardOpen(&mCard, D_80134F18, D_800EB574, mCard.saveIcon, mCard.saveBanner, D_80134F18,
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
    } else if (romTestCode(pROM, D_80134F20)) {
        // Animal Forest
        if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

        if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
            return 0;
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);
        mcardOpen(&mCard, D_80134F28, D_800EB580, mCard.saveIcon, mCard.saveBanner, D_80134F28,
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);
    } else if (romTestCode(pROM, D_80134F2C)) {
        // Blast Corps
        if (!cpuSetCodeHack(pCPU, 0x80244CFC, 0x1420FFFA, 0)) {
            return 0;
        }
    } else if (!romTestCode(pROM, D_80134F34) && !romTestCode(pROM, D_80134F3C) && !romTestCode(pROM, D_80134F44)) {
        if (romTestCode(pROM, D_80134F4C)) {
            // A Bug's Life
            if (!cpuSetCodeHack(pCPU, 0x8007ADD0, 0x1440FFF9, 0)) {
                return 0;
            }
        } else if (romTestCode(pROM, D_80134F54)) {
            // Cruis'n USA
            if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                return 0;
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

            if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                return 0;
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);
            mcardOpen(&mCard, D_80134F5C, D_800EB590, mCard.saveIcon, mCard.saveBanner, D_80134F5C,
                      &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);

            if (!cpuSetCodeHack(pCPU, 0x80103E0C, 0x1616FFF2, 0)) {
                return 0;
            }
        } else if (!romTestCode(pROM, D_80134F64)) {
            if (romTestCode(pROM, D_80134F6C)) {
                // Donkey Kong 64
                if (!cpuSetCodeHack(pCPU, 0x80000A04, 0x1462FFFF, 0)) {
                    return 0;
                }
            } else if ((romTestCode(pROM, D_80134F74)) || (romTestCode(pROM, D_80134F7C))) {
                // Dr. Mario 64
                nTickMultiplier = 3;

                if (!cpuSetCodeHack(pCPU, 0x800005EC, 0x3C028001, -1)) {
                    return 0;
                }

                if (romTestCode(pROM, D_80134F7C)) {
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

                if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, D_80134F84, D_800EB5A0, mCard.saveIcon, mCard.saveBanner, D_80134F84,
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
                gpSystem->eTypeROM = SRT_DRMARIO;
                pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x10);
            } else if (romTestCode(pROM, D_80134F8C)) {
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
            } else if (romTestCode(pROM, D_80134F94)) {
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
            } else if (romTestCode(pROM, D_80134F9C)) {
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
            } else if (romTestCode(pROM, D_80134FA4)) {
                // Mario Kart 64
                pSystem->eTypeROM = SRT_MARIOKART;

                if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, D_80134FAC, D_800EB5AC, mCard.saveIcon, mCard.saveBanner, D_80134FAC,
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
                pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x10);
            } else if (romTestCode(pROM, D_80134FB4)) {
                // Kirby 64
                if (!audioEnable(pSystem->apObject[SOT_AUDIO], 0)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x80020BCC, 0x8DF80034, -1)) {
                    return 0;
                }
                if (!cpuSetCodeHack(pCPU, 0x80020EBC, 0x8DEFF330, -1)) {
                    return 0;
                }
            } else if (romTestCode(pROM, D_80134FBC)) {
                // Mario Party 1
                pSystem->eTypeROM = SRT_MARIOPARTY1;

                if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, D_80134FC4, D_800EB5B8, mCard.saveIcon, mCard.saveBanner, D_80134FC4,
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
            } else if (romTestCode(pROM, D_80134FC8)) {
                // Mario Party 2
                pSystem->eTypeROM = SRT_MARIOPARTY2;

                if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, D_80134FD0, D_800EB5C8, mCard.saveIcon, mCard.saveBanner, D_80134FD0,
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
            } else if (romTestCode(pROM, D_80134FD4)) {
                // Mario Party 3
                pSystem->eTypeROM = SRT_MARIOPARTY3;

                if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                    !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                    return 0;
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                mcardOpen(&mCard, D_80134FDC, D_800EB5D8, mCard.saveIcon, mCard.saveBanner, D_80134FDC,
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x800);
            } else if (!romTestCode(pROM, D_80134FE0) && !romTestCode(pROM, D_80134FE8)) {
                if (romTestCode(pROM, D_80134FF0)) {
                    // Paper Mario
                    if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                        !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                        return 0;
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                    if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                        !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                        return 0;
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);

                    mcardOpen(&mCard, D_800EB5E8, D_800EB5F4, mCard.saveIcon, mCard.saveBanner, D_800EB600,
                              &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);
                } else if (romTestCode(pROM, D_80134FF8)) {
                    if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                        !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                        return 0;
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                    if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                        !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                        return 0;
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                    mcardOpen(&mCard, D_800EB60C, D_800EB61C, mCard.saveIcon, mCard.saveBanner, D_800EB62C,
                              &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);
                } else if (romTestCode(pROM, D_80135000)) {
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
                } else if (!romTestCode(pROM, D_80135008) && !romTestCode(pROM, D_80135010)) {
                    if (romTestCode(pROM, D_80135018) || romTestCode(pROM, D_80135020)) {
                        pSystem->eTypeROM = SRT_STARFOX;

                        if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                            return 0;
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                        if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                            return 0;
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                        mcardOpen(&mCard, D_80135028, D_80135030, mCard.saveIcon, mCard.saveBanner, D_80135028,
                                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
                        pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x110);
                    } else if (romTestCode(pROM, D_80135038)) {
                        if (!cpuSetCodeHack(pCPU, 0x80025D30, 0x3C018006, -1)) {
                            return 0;
                        }
                    } else if (romTestCode(pROM, D_80135040)) {
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
                    } else if (romTestCode(pROM, D_80135048)) {
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

                        if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                            !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                            return 0;
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                        if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                            !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                            return 0;
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                        mcardOpen(&mCard, D_80135050, D_80135050, mCard.saveIcon, mCard.saveBanner, D_80135050,
                                  &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
                    } else if (!romTestCode(pROM, D_80135058) && !romTestCode(pROM, D_80135060)) {
                        if (romTestCode(pROM, D_80135068)) {
                            if (!cpuSetCodeHack(pCPU, 0x80031D94, 0x8C421F6C, -1)) {
                                return 0;
                            }
                        } else if (romTestCode(pROM, D_80135070)) {
                            pSystem->eTypeROM = SRT_PANEL;
                            if (!cpuSetCodeHack(pCPU, 0x800A58F8, 0x8C62FF8C, -1)) {
                                return 0;
                            }

                            if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                                return 0;
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                            if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                                !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0,
                                                  0)) {
                                return 0;
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);

                            mcardOpen(&mCard, D_80135078, D_800EB63C, mCard.saveIcon, mCard.saveBanner, D_80135078,
                                      &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
                            pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x10);
                        } else if (romTestCode(pROM, D_80135080)) {
                            if (!cpuSetCodeHack(pCPU, 0x8002BDD0, 0xA0000000, 0)) {
                                return 0;
                            }
                        } else if (romTestCode(pROM, D_80135088)) {
                            pSystem->eTypeROM = SRT_WAVERACE;

                            if (!cpuSetCodeHack(pCPU, 0x8004795C, 0x1448FFFC, 0)) {
                                return 0;
                            }

                            if (!cpuSetCodeHack(pCPU, 0x80047994, 0x144AFFFC, 0)) {
                                return 0;
                            }

                            pCPU->nCompileFlag = (s32)(pCPU->nCompileFlag | 0x10);
                        } else if (romTestCode(pROM, D_80135090)) {
                            if (DVDOpen(D_800EB508, &fileInfo) == 1 &&
                                !simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & 0xFFFFFFE0, 0, 0)) {
                                return 0;
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveIcon);

                            if (DVDOpen(D_800EB518, &fileInfo) == 1 &&
                                !simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & 0xFFFFFFE0, 0,
                                                  0)) {
                                return 0;
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((__anon_0xDB69*)mCard.saveBanner);
                            mcardOpen(&mCard, D_800EB64C, D_800EB64C, mCard.saveIcon, mCard.saveBanner, D_800EB64C,
                                      &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x800);
                        } else if (romTestCode(pROM, D_80135098)) {
                            mcardOpen(&mCard, D_801350A0, D_801350A0, mCard.saveIcon, mCard.saveBanner, D_801350A0,
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

    if (!soundSetBufferSize(gpSystem->pSound, nSizeSound)) {
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
        } else if (gSystemRomConfigurationList[0].rumbleConfiguration & (1 << (iController * 8))) {
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
#endif

// technically matching but data shenanigans because of the strings/switch
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/system/systemGetException.s")
#else
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
#endif

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

    if (!frameInvalidateCache(gpSystem->pFrame, gpSystem->romCopy.nOffsetRAM,
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

s32 systemCopyROM(System* pSystem, s32 nOffsetRAM, s32 nOffsetROM, s32 nSize, SystemCopyCallbackFunc* pCallback) {
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

    NO_INLINE;
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

    NO_INLINE;
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

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/system/systemEvent.s")
#else
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
extern void* gpFrame;
extern void* gpSound;

static s32 systemGet8(System* pSystem, u32 nAddress, s8* pData);
static s32 systemGet16(System* pSystem, u32 nAddress, s16* pData);
static s32 systemGet32(System* pSystem, u32 nAddress, s32* pData);
static s32 systemGet64(System* pSystem, u32 nAddress, s64* pData);
static s32 systemPut8(System* pSystem, u32 nAddress, s8* pData);
static s32 systemPut16(System* pSystem, u32 nAddress, s16* pData);
static s32 systemPut32(System* pSystem, u32 nAddress, s32* pData);
static s32 systemPut64(System* pSystem, u32 nAddress, s64* pData);

s32 cpuMapObject(Cpu* pCPU, void* pObject, u32 nAddress0, u32 nAddress1, s32 nType);
static s32 systemGetException(System* pSystem, SystemInterruptType eType, SystemException* pException);
s32 mipsResetInterrupt(Mips* pMips, MipsInterruptType eType);

s32 systemEvent(System* pSystem, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x37240* pSystem; // r31
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r26

    // Local variables
    Cpu* pCPU; // r30
    SystemException exception; // r1+0x1C
    SystemObjectType eObject; // r1+0x8
    SystemObjectType storageDevice; // r1+0x8

    pCPU = pSystem->apObject[SOT_CPU];
    // pCPU = (Cpu*)pArgument;

    switch (nEvent) {
        case 2:
            pSystem->eMode = SM_STOPPED;
            pSystem->eTypeROM = SRT_NONE;
            pSystem->nAddressBreak = -1;
            pSystem->bJapaneseVersion = 0;
            pSystem->romCopy.nSize = 0;
            pSystem->pFrame = gpFrame;
            pSystem->pSound = gpSound;

            for (eObject = SOT_CPU; eObject < SOT_COUNT; eObject++) {
                pSystem->apObject[eObject] = NULL;
            }

            pSystem->bException = 0;
            pSystem->anException[SOT_CPU] = 0;
            pSystem->anException[SOT_PIF] = 0;
            pSystem->anException[SOT_RAM] = 0;
            pSystem->anException[SOT_ROM] = 0;
            pSystem->anException[SOT_RSP] = 0;
            pSystem->anException[SOT_RDP] = 0;
            pSystem->anException[SOT_MIPS] = 0;
            pSystem->anException[SOT_DISK] = 0;
            pSystem->anException[SOT_FLASH] = 0;
            pSystem->anException[SOT_SRAM] = 0;
            pSystem->anException[SOT_AUDIO] = 0;
            pSystem->anException[SOT_VIDEO] = 0;
            pSystem->anException[SOT_SERIAL] = 0;
            pSystem->anException[SOT_LIBRARY] = 0;
            pSystem->anException[SOT_PERIPHERAL] = 0;
            pSystem->anException[SOT_RDB] = 0;

            for (eObject = SOT_CPU; eObject < SOT_COUNT; eObject++) {
                switch (eObject) {
                    case SOT_CPU:
                        if (!xlObjectMake(&pSystem->apObject[SOT_CPU], pArgument, &gClassCPU)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_CPU], 0, -1, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_PIF:
                        if (!xlObjectMake(&pSystem->apObject[SOT_PIF], pArgument, &gClassPIF)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_PIF], 0x1FC00000, 0x1FC007FF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_RAM:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RAM], pArgument, &gClassRAM)) {
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
                        if (!xlObjectMake(&pSystem->apObject[SOT_ROM], pArgument, &gClassROM)) {
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
                        if (!xlObjectMake(&pSystem->apObject[SOT_RSP], pArgument, &gClassRSP)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RSP], 0x04000000, 0x040FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_RDP:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RDP], pArgument, &gClassRDP)) {
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
                        if (!xlObjectMake(&pSystem->apObject[SOT_MIPS], pArgument, &gClassMips)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_MIPS], 0x04300000, 0x043FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_DISK:
                        if (!xlObjectMake(&pSystem->apObject[SOT_DISK], pArgument, &gClassDisk)) {
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
                        if (!xlObjectMake(&pSystem->apObject[SOT_AUDIO], pArgument, &gClassAudio)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_AUDIO], 0x04500000, 0x045FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_VIDEO:
                        if (!xlObjectMake(&pSystem->apObject[SOT_VIDEO], pArgument, &gClassVideo)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_VIDEO], 0x04400000, 0x044FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_SERIAL:
                        if (!xlObjectMake(&pSystem->apObject[SOT_SERIAL], pArgument, &gClassSerial)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_SERIAL], 0x04800000, 0x048FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_LIBRARY:
                        if (!xlObjectMake(&pSystem->apObject[SOT_LIBRARY], pArgument, &gClassLibrary)) {
                            return 0;
                        }
                        break;
                    case SOT_PERIPHERAL:
                        if (!xlObjectMake(&pSystem->apObject[SOT_PERIPHERAL], pArgument, &gClassPeripheral)) {
                            return 0;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_PERIPHERAL], 0x04600000, 0x046FFFFF, 0)) {
                            return 0;
                        }
                        break;
                    case SOT_RDB:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RDB], pArgument, &gClassRdb)) {
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
            for (eObject = SOT_CPU; eObject < SOT_COUNT; eObject++) {
                if ((eObject != SOT_FLASH) && (eObject != SOT_SRAM)) {
                    if (!xlObjectFree(&pSystem->apObject[eObject])) {
                        return 0;
                    }
                } else if (eObject == SOT_FLASH) {
                    if ((pSystem->storageDevice == SOT_FLASH) && !xlObjectFree(&pSystem->apObject[SOT_FLASH])) {
                        return 0;
                    }
                } else if ((eObject == SOT_SRAM) && (pSystem->storageDevice == SOT_SRAM) &&
                           !xlObjectFree(&pSystem->apObject[SOT_SRAM])) {
                    return 0;
                }
            }
            break;
        case 0x1001:
            if (!systemGetException(pSystem, nEvent, &exception)) {
                return 0;
            }
            if (exception.eTypeMips != MIT_NONE) {
                mipsResetInterrupt(pSystem->apObject[SOT_MIPS], exception.eTypeMips);
            }
            break;
        case 0x1000:
            if ((nEvent > SIT_NONE) && (nEvent < SIT_COUNT)) {
                pSystem->bException = 1;
                pSystem->anException[nEvent]++;
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
#endif
