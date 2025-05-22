#include "emulator/system.h"
#include "dolphin.h"
#include "emulator/audio.h"
#include "emulator/cpu.h"
#include "emulator/disk.h"
#include "emulator/flash.h"
#include "emulator/frame.h"
#include "emulator/library.h"
#include "emulator/mcardGCN.h"
#include "emulator/mips.h"
#include "emulator/peripheral.h"
#include "emulator/pif.h"
#include "emulator/ram.h"
#include "emulator/rdb.h"
#include "emulator/rdp.h"
#include "emulator/rom.h"
#include "emulator/rsp.h"
#include "emulator/serial.h"
#include "emulator/simGCN.h"
#include "emulator/soundGCN.h"
#include "emulator/sram.h"
#include "emulator/video.h"
#include "emulator/xlHeap.h"
#include "macros.h"
#include "stdlib.h"
#include "string.h"

#if IS_MQ
#define MCARD_FILE_NAME "ZELDA"
#define MCARD_FILE_SIZE (0xC000 * 2)
#else
#define MCARD_FILE_NAME "ZELDA1"
#define MCARD_FILE_SIZE 0xC000
#endif

#if IS_MM
#define MCARD_FILE_NAME_MM "ZELDA2"
#else
#define MCARD_FILE_NAME_MM "ZELDA3"
#endif

#if VERSION == CE_J
#define MCARD_COMMENT "ゼルダコレクション" // "Zelda Collection"
#elif VERSION == MQ_J || VERSION == MM_J
#define MCARD_COMMENT "ゼルダの伝説　時のオカリナＧＣ" // "The Legend of Zelda: Ocarina of Time GC"
#elif VERSION == CE_E || VERSION == CE_U
#define MCARD_COMMENT "Zelda: Collector's Edition"
#else
#define MCARD_COMMENT "Zelda: Ocarina of Time"
#endif

#if IS_MM_JP
#define MCARD_COMMENT_MM "ゼルダコレクション" // "Zelda Collection"
#elif IS_MM_US || IS_MM_EU
#define MCARD_COMMENT_MM "Zelda: Collector's Edition"
#else
#define MCARD_COMMENT_MM "Legend of Zelda"
#endif

#if IS_MM_JP
#define MCARD_FILE_NAME_STARFOX "Starfox 64"
#define MCARD_FILE_NAME_MK64 "Mario Kart 64"
#else
#define MCARD_FILE_NAME_STARFOX "Starfox"
#define MCARD_FILE_NAME_MK64 "Mario Kart"
#endif

#if IS_MM
#define ROM_IS_PW64(pROM) (romTestCode(pROM, "NPWE") || romTestCode(pROM, "NPWJ"))
#define ROM_IS_MK64(pROM) (romTestCode(pROM, "NKTE") || romTestCode(pROM, "NKTJ"))
#define ROM_IS_KIRBY(pROM) (romTestCode(pROM, "NK4E") || romTestCode(pROM, "NK4J"))
#else
#define ROM_IS_PW64(pROM) (romTestCode(pROM, "NPWE"))
#define ROM_IS_MK64(pROM) (romTestCode(pROM, "NKTE"))
#define ROM_IS_KIRBY(pROM) (romTestCode(pROM, "NK4E"))
#endif

#if IS_MM_JP || IS_MM_EU
#define ROM_IS_MM(pROM) (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE") || romTestCode(pROM, "NZSP"))
#else
#define ROM_IS_MM(pROM) (romTestCode(pROM, "NZSJ") || romTestCode(pROM, "NZSE"))
#endif

#if IS_OOT_EU || IS_MM
#define ROM_IS_OOT(pROM) (romTestCode(pROM, "CZLJ") || romTestCode(pROM, "CZLE") || romTestCode(pROM, "NZLP"))
#define Z_ICON_PATH buf1
#define Z_BNR_PATH buf2
#else
#define ROM_IS_OOT(pROM) (romTestCode(pROM, "CZLJ") || romTestCode(pROM, "CZLE"))
#define Z_ICON_PATH "TPL/z_icon.tpl"
#define Z_BNR_PATH "TPL/z_bnr.tpl"
#endif

_XL_OBJECTTYPE gClassSystem = {
    "SYSTEM (N64)",
    sizeof(System),
    NULL,
    (EventFunc)systemEvent,
}; // size = 0x10

// clang-format off
static u32 contMap[][GCN_BTN_COUNT] = {
    // Controller Configuration No. 1
    {
        N64_BTN_A,      // GCN_BTN_A
        N64_BTN_B,      // GCN_BTN_B
        N64_BTN_UNSET,  // GCN_BTN_X
        N64_BTN_UNSET,  // GCN_BTN_Y
        N64_BTN_L,      // GCN_BTN_L
        N64_BTN_R,      // GCN_BTN_R
        N64_BTN_Z,      // GCN_BTN_Z
        N64_BTN_START,  // GCN_BTN_START
        0x08000000,     // GCN_BTN_UNK8
        0x04000000,     // GCN_BTN_UNK9
        0x02000000,     // GCN_BTN_UNK10
        0x01000000,     // GCN_BTN_UNK11
        N64_BTN_DUP,    // GCN_BTN_DPAD_UP
        N64_BTN_DDOWN,  // GCN_BTN_DPAD_DOWN
        N64_BTN_DLEFT,  // GCN_BTN_DPAD_LEFT
        N64_BTN_DRIGHT, // GCN_BTN_DPAD_RIGHT
        N64_BTN_CUP,    // GCN_BTN_CSTICK_UP
        N64_BTN_CDOWN,  // GCN_BTN_CSTICK_DOWN
        N64_BTN_CLEFT,  // GCN_BTN_CSTICK_LEFT
        N64_BTN_CRIGHT, // GCN_BTN_CSTICK_RIGHT
    },
    // Controller Configuration No. 2
    {
        N64_BTN_A,      // GCN_BTN_A
        N64_BTN_B,      // GCN_BTN_B
        N64_BTN_UNSET,  // GCN_BTN_X
        N64_BTN_UNSET,  // GCN_BTN_Y
        N64_BTN_Z,      // GCN_BTN_L
        N64_BTN_R,      // GCN_BTN_R
        N64_BTN_Z,      // GCN_BTN_Z
        N64_BTN_START,  // GCN_BTN_START
        0x08000000,     // GCN_BTN_UNK8
        0x04000000,     // GCN_BTN_UNK9
        0x02000000,     // GCN_BTN_UNK10
        0x01000000,     // GCN_BTN_UNK11
        N64_BTN_DUP,    // GCN_BTN_DPAD_UP
        N64_BTN_DDOWN,  // GCN_BTN_DPAD_DOWN
        N64_BTN_DLEFT,  // GCN_BTN_DPAD_LEFT
        N64_BTN_DRIGHT, // GCN_BTN_DPAD_RIGHT
        N64_BTN_CUP,    // GCN_BTN_CSTICK_UP
        N64_BTN_CDOWN,  // GCN_BTN_CSTICK_DOWN
        N64_BTN_CLEFT,  // GCN_BTN_CSTICK_LEFT
        N64_BTN_CRIGHT, // GCN_BTN_CSTICK_RIGHT
    },
    // Controller Configuration No. 3
    {
        N64_BTN_A,      // GCN_BTN_A
        N64_BTN_B,      // GCN_BTN_B
        N64_BTN_CRIGHT, // GCN_BTN_X
        N64_BTN_CLEFT,  // GCN_BTN_Y
        N64_BTN_Z,      // GCN_BTN_L
        N64_BTN_R,      // GCN_BTN_R
        N64_BTN_CDOWN,  // GCN_BTN_Z
        N64_BTN_START,  // GCN_BTN_START
        0x08000000,     // GCN_BTN_UNK8
        0x04000000,     // GCN_BTN_UNK9
        0x02000000,     // GCN_BTN_UNK10
        0x01000000,     // GCN_BTN_UNK11
        N64_BTN_L,      // GCN_BTN_DPAD_UP
        N64_BTN_L,      // GCN_BTN_DPAD_DOWN
        N64_BTN_L,      // GCN_BTN_DPAD_LEFT
        N64_BTN_L,      // GCN_BTN_DPAD_RIGHT
        N64_BTN_CUP,    // GCN_BTN_CSTICK_UP
        N64_BTN_CDOWN,  // GCN_BTN_CSTICK_DOWN
        N64_BTN_CLEFT,  // GCN_BTN_CSTICK_LEFT
        N64_BTN_CRIGHT, // GCN_BTN_CSTICK_RIGHT
    },
    // Controller Configuration No. 4
    {
        N64_BTN_A,      // GCN_BTN_A
        N64_BTN_B,      // GCN_BTN_B
        N64_BTN_L,      // GCN_BTN_X
        N64_BTN_UNSET,  // GCN_BTN_Y
        N64_BTN_Z,      // GCN_BTN_L
        N64_BTN_R,      // GCN_BTN_R
        N64_BTN_Z,      // GCN_BTN_Z
        N64_BTN_START,  // GCN_BTN_START
        0x08000000,     // GCN_BTN_UNK8
        0x04000000,     // GCN_BTN_UNK9
        0x02000000,     // GCN_BTN_UNK10
        0x01000000,     // GCN_BTN_UNK11
        N64_BTN_DUP,    // GCN_BTN_DPAD_UP
        N64_BTN_DDOWN,  // GCN_BTN_DPAD_DOWN
        N64_BTN_DLEFT,  // GCN_BTN_DPAD_LEFT
        N64_BTN_DRIGHT, // GCN_BTN_DPAD_RIGHT
        N64_BTN_CUP,    // GCN_BTN_CSTICK_UP
        N64_BTN_CDOWN,  // GCN_BTN_CSTICK_DOWN
        N64_BTN_CLEFT,  // GCN_BTN_CSTICK_LEFT
        N64_BTN_CRIGHT, // GCN_BTN_CSTICK_RIGHT
    },
#if IS_MM
    // Controller Configuration No. 5
    {
        N64_BTN_A,      // GCN_BTN_A
        N64_BTN_B,      // GCN_BTN_B
        N64_BTN_UNSET,  // GCN_BTN_X
        N64_BTN_UNSET,  // GCN_BTN_Y
        N64_BTN_Z,      // GCN_BTN_L
        N64_BTN_R,      // GCN_BTN_R
        N64_BTN_Z,      // GCN_BTN_Z
        N64_BTN_START,  // GCN_BTN_START
        0x08000000,     // GCN_BTN_UNK8
        0x04000000,     // GCN_BTN_UNK9
        0x02000000,     // GCN_BTN_UNK10
        0x01000000,     // GCN_BTN_UNK11
        N64_BTN_DUP,    // GCN_BTN_DPAD_UP
        N64_BTN_DDOWN,  // GCN_BTN_DPAD_DOWN
        N64_BTN_DLEFT,  // GCN_BTN_DPAD_LEFT
        N64_BTN_DRIGHT, // GCN_BTN_DPAD_RIGHT
        N64_BTN_CUP,    // GCN_BTN_CSTICK_UP
        N64_BTN_CDOWN,  // GCN_BTN_CSTICK_DOWN
        N64_BTN_CLEFT,  // GCN_BTN_CSTICK_LEFT
        N64_BTN_CRIGHT, // GCN_BTN_CSTICK_RIGHT
    },
#endif
}; // size = 0x140
// clang-format on

SystemRomConfig gSystemRomConfigurationList[1];
u32 nTickMultiplier = 2;
f32 fTickScale = 1.0;
u32 gnFlagZelda;

static bool systemSetupGameRAM(System* pSystem) {
    char* szExtra;
    bool bExpansion;
    s32 nSizeRAM;
    s32 nSizeCacheROM;
    s32 nSizeExtra;
    Rom* pROM;
    u32 nCode;
    u32 iCode;
    u32 anCode[0x100]; // size = 0x400

    bExpansion = false;
    pROM = SYSTEM_ROM(pSystem);

    if (!romCopy(SYSTEM_ROM(pSystem), anCode, 0x1000, sizeof(anCode), NULL)) {
        return false;
    }

    nCode = 0;
    for (iCode = 0; iCode < ARRAY_COUNT(anCode); iCode++) {
        nCode += anCode[iCode];
    }

    // Majora's Mask
    if (ROM_IS_MM(pROM)) {
        bExpansion = true;
    }

    // Ocarina of Time or Majora's Mask
    if (ROM_IS_OOT(pROM) || ROM_IS_MM(pROM)) {
        switch (nCode) {

#if VERSION == MQ_J
            case 0x5CAC1CF7:
                gnFlagZelda = 2;
                break;
            case 0x184CED80:
                gnFlagZelda = 3;
                bExpansion = 1;
                break;
            case 0x5CAC1C8F:
                gnFlagZelda = 0;
                break;
            case 0x184CED18:
                gnFlagZelda = 1;
                bExpansion = 1;
                break;
            case 0x7E8BEE60:
                gnFlagZelda = 1;
                bExpansion = 1;
                break;

#elif VERSION == CE_J
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

#elif IS_OOT_US
            case 0x5CAC1CF7:
                gnFlagZelda = 2;
                break;
            case 0x184CED80:
                gnFlagZelda = 3;
                break;
            case 0x5CAC1C27:
                gnFlagZelda = 0;
                break;
            case 0x5CAC1C8F:
                gnFlagZelda = romTestCode(pROM, "CZLE") ? 2 : 0;
                break;
            case 0x184CED18:
                gnFlagZelda = 1;
                break;
            case 0x54A59B56:
            case 0x421EB8E9:
                gnFlagZelda = 4;
                break;
            case 0x7E8BEE60:
                gnFlagZelda = 5;
                break;

#elif IS_OOT_EU || IS_MM
            case 0x5CAC1CF7:
                gnFlagZelda = 2;
                break;
            case 0x5CABE4F4:
                gnFlagZelda = 2;
                break;
            case 0x184CED80:
                gnFlagZelda = 3;
                break;
            case 0x5CAC1C27:
                gnFlagZelda = 0;
                break;
            case 0x5CAC1C8F:
#if IS_OOT_EU
                gnFlagZelda = 0;
#else
                gnFlagZelda = romTestCode(pROM, "CZLE") ? 2 : 0;
#endif
                break;
            case 0x5CABE48C:
                gnFlagZelda = 0;
                break;
            case 0x184CED18:
                gnFlagZelda = 1;
                break;
#if IS_OOT_EU
            case 0x54A59B56:
            case 0x421EB8E9:
                gnFlagZelda = 4;
                break;
#elif IS_MM_JP
            case 0xA1ADC351:
            case 0xA1AD0330:
                gnFlagZelda = 4;
                break;
            case 0xA1AF7705:
                gnFlagZelda = 4;
                break;
#elif IS_MM_US
            case 0xA1ADC351:
            case 0xA1AD0040:
                gnFlagZelda = 4;
                break;
#elif IS_MM_EU
            case 0xA1ADC351:
            case 0xA1AD0040:
                gnFlagZelda = 4;
                break;
            case 0xA1AF7705:
                gnFlagZelda = 4;
                break;
#endif
            case 0x7E8BEE60:
                gnFlagZelda = 5;
                break;
#endif
        }

#if VERSION != MQ_J
        if (gnFlagZelda & 1) {
            bExpansion = true;
        }
#endif
    }

    // Conker's Bad Fur Day
    if (romTestCode(pROM, "NFUE")) {
        bExpansion = true;
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
        return false;
    }

    if (!romSetCacheSize(SYSTEM_ROM(pSystem), nSizeCacheROM)) {
        return false;
    }

    return true;
}

static inline void systemSetControllerConfiguration(SystemRomConfig* pRomConfig, s32 controllerConfig,
                                                    bool bSetControllerConfig) {
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

bool systemGetInitialConfiguration(System* pSystem, Rom* pROM, s32 index) {
    char* szText;

    // fake match
    (void)contMap;
    (void)contMap;

    if (!romGetCode(pROM, gSystemRomConfigurationList[index].rom)) {
        return false;
    }

    systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, false);
    gSystemRomConfigurationList[index].storageDevice = SOT_CPU;

#if VERSION == MQ_J
    if (!simulatorGetArgument(SAT_VIBRATION, &szText) || (*szText == '1')) {
        if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x82828282, true);
        } else {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x80808080, true);
        }
    } else {
        if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x02020202, true);
        } else {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, true);
        }
    }
#endif

    if (romTestCode(pROM, "NSME") || romTestCode(pROM, "NSMJ")) {
        // Super Mario 64

#if IS_OOT
        systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x01010101, false);
#else
        if (romTestCode(pROM, "NSMJ")) {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x81818181, true);
        } else {
            systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x01010101, true);
        }
#endif

#if VERSION != MQ_J
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;
#endif

    } else if (romTestCode(pROM, "CZLE") || romTestCode(pROM, "CZLJ")
#if IS_OOT_EU || IS_MM
               || romTestCode(pROM, "NZLP")
#endif
    ) {
        // Ocarina of Time
        gSystemRomConfigurationList[index].storageDevice = SOT_PIF;

#if VERSION != MQ_J
        if (!simulatorGetArgument(SAT_VIBRATION, &szText) || (*szText == '1')) {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x82828282, true);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x80808080, true);
            }
        } else {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x02020202, true);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, true);
            }
        }
#endif

    } else if (ROM_IS_MM(pROM)) {
        // Majora's Mask
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

#if VERSION != MQ_J
        if (!simulatorGetArgument(SAT_VIBRATION, &szText) || (*szText == '1')) {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x82828282, true);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x80808080, true);
            }
        } else {
            if (!simulatorGetArgument(SAT_CONTROLLER, &szText) || (*szText == '0')) {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x02020202, true);
            } else {
                systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0, true);
            }
        }
#endif

    } else if (ROM_IS_PW64(pROM)) {
        // Pilotwings 64
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

    } else if (romTestCode(pROM, "NAFJ")) {
        // Animal Forest
        gSystemRomConfigurationList[index].storageDevice = SOT_RAM;

    } else if (romTestCode(pROM, "NCUE")) {
        // Cruis'n
        gSystemRomConfigurationList[index].storageDevice = 20; // bug?

    } else if (ROM_IS_MK64(pROM)) {
        // Mario Kart 64
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

#if IS_MM
    } else if (romTestCode(pROM, "NK4E") || romTestCode(pROM, "NK4J")) {
        // Kirby 64
        gSystemRomConfigurationList[index].storageDevice = SOT_FLASH;
#endif

    } else if (romTestCode(pROM, "NFXE") || romTestCode(pROM, "NFXJ")) {
        // Star Fox 64
        gSystemRomConfigurationList[index].storageDevice = SOT_RSP;

#if IS_MM
        systemSetControllerConfiguration(&gSystemRomConfigurationList[index], 0x84848484, true);
#endif

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

    return true;
}

static bool systemSetupGameALL(System* pSystem) {
    s32 nSizeSound;
    s32 iController;
    s32 nSize;
    u32* anMode;
    s32 i;
    u64 nTimeRetrace;
    char acCode[5];
#if IS_OOT_EU || IS_MM
    char buf1[30] = "TPL/";
    char buf2[30] = "TPL/";
#endif
    DVDFileInfo fileInfo;
    Cpu* pCPU;
    Rom* pROM;
    Pif* pPIF;
    s32 defaultConfiguration;

    pCPU = SYSTEM_CPU(pSystem);
    pROM = SYSTEM_ROM(pSystem);
    pPIF = SYSTEM_PIF(pSystem);

#if IS_OOT_EU || IS_MM_EU
    if (gLanguage == 1) {
        strcpy(buf1, "TPL/GERMAN/");
        strcpy(buf2, "TPL/GERMAN/");
    } else if (gLanguage == 2) {
        strcpy(buf1, "TPL/FRENCH/");
        strcpy(buf2, "TPL/FRENCH/");

#if VERSION == CE_E
    } else if (gLanguage == 3) {
        strcpy(buf1, "TPL/SPANISH/");
        strcpy(buf2, "TPL/SPANISH/");
    } else if (gLanguage == 4) {
        strcpy(buf1, "TPL/ITALIAN/");
        strcpy(buf2, "TPL/ITALIAN/");
#elif IS_MM_EU
    } else if (gLanguage == 3) {
        strcpy(buf1, "TPL/SPANISH/");
        strcpy(buf2, "TPL/SPANISH/");
    } else if (gLanguage == 3) {
        //! @bug: This code is never reached because the condition should be `gLanguage == 4` for Italian
        strcpy(buf1, "TPL/ITALIAN/");
        strcpy(buf2, "TPL/ITALIAN/");
#endif

    } else {
        strcpy(buf1, "TPL/ENGLISH/");
        strcpy(buf2, "TPL/ENGLISH/");
    }
#endif

    if (!xlHeapTake((void**)&mCard.saveIcon, gz_iconSize | 0x30000000)) {
        return false;
    }

    if (!xlHeapTake((void**)&mCard.saveBanner, gz_bnrSize | 0x30000000)) {
        return false;
    }

    nSizeSound = 0x2000;
    memset(&defaultConfiguration, 0, 4);
    pSystem->eTypeROM = SRT_UNKNOWN;

    if (!ramGetBuffer(SYSTEM_RAM(pSystem), (void**)&anMode, 0x300, NULL)) {
        return false;
    }

    anMode[0] = 1;
    anMode[1] = 0;
    anMode[2] = 0xB0000000;
    anMode[3] = 0;
    anMode[4] = 0x17D7;
    anMode[5] = 1;

    nTimeRetrace = OSSecondsToTicks(1.0f / 60.0f);

    if (!ramGetSize(SYSTEM_RAM(pSystem), &nSize)) {
        return false;
    }

    anMode[6] = nSize;
    systemGetInitialConfiguration(pSystem, pROM, 0);

    i = 0;
    if (gSystemRomConfigurationList[i].storageDevice & 1) {
        if (!systemSetStorageDevice(pSystem, SOT_SRAM)) {
            return false;
        }
    } else {
        if (gSystemRomConfigurationList[i].storageDevice & 2) {
            if (!systemSetStorageDevice(pSystem, SOT_FLASH)) {
                return false;
            }
        } else {
            if (!systemSetStorageDevice(pSystem, SOT_NONE)) {
                return false;
            }
        }
    }

    if (gSystemRomConfigurationList[i].storageDevice & 4) {
        if (!pifSetEEPROMType(pPIF, CT_4K)) {
            return false;
        }
    } else {
        if (gSystemRomConfigurationList[i].storageDevice & 8) {
            if (!pifSetEEPROMType(pPIF, CT_16K)) {
                return false;
            }
        } else {
            if (!pifSetEEPROMType(pPIF, CT_NONE)) {
                return false;
            }
        }
    }

    if (romTestCode(pROM, "NSME") || romTestCode(pROM, "NSMJ")) {
        // Super Mario 64
        pSystem->eTypeROM = SRT_MARIO;
        nSizeSound = 0x1000;

#if IS_OOT_EU || IS_MM
        strcat(buf1, "z_icon.tpl");
#endif

        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
        strcat(buf2, "z_bnr.tpl");
#endif

        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
        mcardOpen(&mCard, "MARIO", "Mario 64", mCard.saveIcon, mCard.saveBanner, "MARIO",
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);

        if (!cpuSetCodeHack(pCPU, 0x80317938, 0x5420FFFE, 0)) {
            return false;
        }
    } else if (romTestCode(pROM, "CZLE") || romTestCode(pROM, "CZLJ")
#if IS_OOT_EU || IS_MM
               || romTestCode(pROM, "NZLP")
#endif
    ) {
        // Ocarina of Time
        pSystem->eTypeROM = SRT_ZELDA1;
        nSizeSound = 0x1000;

#if VERSION == MQ_J
        if ((gnFlagZelda & 1)) {
            if (!cpuSetCodeHack(pCPU, 0x80062D64, 0x94639680, -1)) {
                return false;
            }

            if (!cpuSetCodeHack(pCPU, 0x8006E468, 0x97040000, -1)) {
                return false;
            }
        } else {
            if (!cpuSetCodeHack(pCPU, 0x8005BB34, 0x9463D040, -1)) {
                return false;
            }

            if (!cpuSetCodeHack(pCPU, 0x80066658, 0x97040000, -1)) {
                return false;
            }
        }
#else
        if (gnFlagZelda & 1) {
            if (romTestCode(pROM, "CZLE")) {
                if (!cpuSetCodeHack(pCPU, 0x80062D64, 0x94639680, -1)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x8006E468, 0x97040000, -1)) {
                    return false;
                }
            } else
#if IS_OOT_EU || IS_MM
                if (romTestCode(pROM, "CZLJ"))
#endif
            {
                if (!cpuSetCodeHack(pCPU, 0x80062D64, 0x94639680, -1)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x8006E468, 0x97040000, -1)) {
                    return false;
                }
            }
#if IS_OOT_EU || IS_MM
            else if (romTestCode(pROM, "NZLP")) {
                if (!cpuSetCodeHack(pCPU, 0x80062D64, 0x94639680, -1)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x8006E468, 0x97040000, -1)) {
                    return false;
                }
            }
#endif
        } else {
            if (romTestCode(pROM, "CZLE")) {
                if (!cpuSetCodeHack(pCPU, 0x8005BB14, ((gnFlagZelda & 2) ? 0x9463D040 : 0x9463D000), -1)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x80066638, 0x97040000, -1)) {
                    return false;
                }
            } else
#if IS_OOT_EU || IS_MM
                if (romTestCode(pROM, "CZLJ"))
#endif
            {
                if (!cpuSetCodeHack(pCPU, 0x8005BB34, 0x9463D040, -1)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x80066658, 0x97040000, -1)) {
                    return false;
                }
            }
#if IS_OOT_EU || IS_MM
            else if (romTestCode(pROM, "NZLP")) {
                if (!cpuSetCodeHack(pCPU, 0x8005BB3C, 0x9502000C, -1)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800665E8, 0x97040000, -1)) {
                    return false;
                }
            }
#endif
        }
#endif

        if (!(gnFlagZelda & 1)) {
            if (!(gnFlagZelda & 2)) {
                // CE-J/MQ-J?
#if IS_OOT_EU || IS_MM
                strcat(buf1, "z_icon.tpl");
#endif
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                strcat(buf2, "z_bnr.tpl");
#endif

                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                mcardOpen(&mCard, MCARD_FILE_NAME, MCARD_COMMENT, mCard.saveIcon, mCard.saveBanner, "ZELDAX",
                          &gSystemRomConfigurationList[i].currentControllerConfig, MCARD_FILE_SIZE, 0x8000);
            } else {
#if IS_OOT_EU || IS_MM
                strcat(buf1, "z_icon.tpl");
#endif
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);
#if IS_OOT_EU || IS_MM
                strcat(buf2, "z_bnr.tpl");
#endif
                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                mcardOpen(&mCard, MCARD_FILE_NAME, MCARD_COMMENT, mCard.saveIcon, mCard.saveBanner, "ZELDA",
                          &gSystemRomConfigurationList[i].currentControllerConfig, MCARD_FILE_SIZE, 0x8000);
            }
#if IS_OOT_EU || IS_MM_EU
            mCard.file.game.buffer[2] = gLanguage;
#endif
        } else {
            // debug rom?
#if IS_OOT_EU || IS_MM
            strcat(buf1, "z_icon.tpl");
#endif
            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                    return false;
                }
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
            strcat(buf2, "z_bnr.tpl");
#endif
            if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                    return false;
                }
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
            mcardOpen(&mCard, "ZELDAD", "The Legend of Zelda Debug", mCard.saveIcon, mCard.saveBanner, "ZELDAD",
                      &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
        }

        pCPU->nCompileFlag |= 0x110;
    } else if (ROM_IS_MM(pROM)) {
        // Majora's Mask
        pSystem->eTypeROM = SRT_ZELDA2;
        nSizeSound = 0x1000;

#if IS_OOT || IS_MM_US
        if (romTestCode(pROM, "NZSJ")) {
            pSystem->bJapaneseVersion = true;
        } else {
            pSystem->bJapaneseVersion = false;
        }

#if IS_OOT
        nTickMultiplier = 2;
        fTickScale = 1.1f;
#endif

#endif

        if (!ramGetBuffer(SYSTEM_RAM(pSystem), (void**)&anMode, 0x300U, NULL)) {
            return false;
        }

        anMode[4] = 0x17D9;

#if IS_OOT_EU || IS_MM
        strcat(buf1, "z_icon.tpl");
#endif

        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
        strcat(buf2, "z_bnr.tpl");
#endif

        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
        mcardOpen(&mCard, MCARD_FILE_NAME_MM, MCARD_COMMENT_MM, mCard.saveIcon, mCard.saveBanner, "ZELDA3",
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);

        if (gnFlagZelda & 1) {
            if (cpuSetCodeHack(pCPU, 0x801C6FC0, 0x95630000, -1) == 0) {
                return false;
            }
        } else {
#if IS_OOT
            if (romTestCode(pROM, "NZSJ")) {
                if (!cpuSetCodeHack(pCPU, 0x80179994, 0x95630000, -1)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDA84, 0x860C0000, 0x6025)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDA88, 0x860D0004, 0x6825)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDB0C, 0x86180000, 0xC025)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDB20, 0x86190004, 0xC825)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDB34, 0x86080002, 0x4025)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDB4C, 0x8609FFFA, 0x4825)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDB60, 0x860AFFFE, 0x5025)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDB94, 0x844EFFFA, 0x7025)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDBA8, 0x844FFFFE, 0x7825)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDC20, 0x860A0006, 0x5025)) {
                    return false;
                }

                if (!cpuSetCodeHack(pCPU, 0x800BDC34, 0x860B000A, 0x5825)) {
                    return false;
                }
            } else {
                if (!cpuSetCodeHack(pCPU, 0x80178A80, 0x95630000, -1)) {
                    return false;
                }
            }
#elif IS_MM_JP || IS_MM_EU
            if (romTestCode(pROM, "NZSJ")) {
                if (!cpuSetCodeHack(pCPU, 0x80177CF4, 0x95630000, -1)) {
                    return false;
                }
            } else if (romTestCode(pROM, "NZSE")) {
                if (!cpuSetCodeHack(pCPU, 0x80177D34, 0x95630000, -1)) {
                    return false;
                }
            } else {
                if (!cpuSetCodeHack(pCPU, 0x801786B4, 0x95630000, -1)) {
                    return false;
                }
            }
#elif IS_MM_US
            if (romTestCode(pROM, "NZSJ")) {
                if (!cpuSetCodeHack(pCPU, 0x80177BF4, 0x95630000, -1)) {
                    return false;
                }
            } else {
                if (!cpuSetCodeHack(pCPU, 0x80177C34, 0x95630000, -1)) {
                    return false;
                }
            }
#endif
        }

        pCPU->nCompileFlag |= 0x1010;
    } else if (ROM_IS_PW64(pROM)) {
        // Pilotwings 64

#if IS_OOT_EU || IS_MM
        strcat(buf1, "z_icon.tpl");
#endif
        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
        strcat(buf2, "z_bnr.tpl");
#endif
        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
        mcardOpen(&mCard, "PILOT", "Pilotwings", mCard.saveIcon, mCard.saveBanner, "PILOT",
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
    } else if (romTestCode(pROM, "NAFJ")) {
        // Animal Forest

#if IS_OOT_EU || IS_MM
        strcat(buf1, "z_icon.tpl");
#endif
        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }

        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
        strcat(buf2, "z_bnr.tpl");
        if (DVDOpen(buf2, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }
#else
        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
            if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                return false;
            }
        }
#endif
        DVDClose(&fileInfo);

#if IS_OOT_EU || IS_MM
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
#else
        simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);
#endif

        mcardOpen(&mCard, "AF", "Animal Forest", mCard.saveIcon, mCard.saveBanner, "AF",
                  &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);
    } else if (romTestCode(pROM, "NBCE")) {
        // Blast Corps
        if (!cpuSetCodeHack(pCPU, 0x80244CFC, 0x1420FFFA, 0)) {
            return false;
        }
    } else if (!romTestCode(pROM, "NBKE") && !romTestCode(pROM, "NGEE") && !romTestCode(pROM, "NFUE")) {
        if (romTestCode(pROM, "NBYE")) {
            // A Bug's Life
            if (!cpuSetCodeHack(pCPU, 0x8007ADD0, 0x1440FFF9, 0)) {
                return false;
            }
        } else if (romTestCode(pROM, "NCUE")) {
            // Cruis'n USA
#if IS_OOT_EU || IS_MM
            strcat(buf1, "z_icon.tpl");
#endif
            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                    return false;
                }
            }

            DVDClose(&fileInfo);
            simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
            strcat(buf2, "z_bnr.tpl");
            if (DVDOpen(buf2, &fileInfo) == 1) {
                if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                    return false;
                }
            }
#else
            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                    return false;
                }
            }
#endif

            DVDClose(&fileInfo);

#if IS_OOT_EU || IS_MM
            simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
#else
            simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);
#endif
            mcardOpen(&mCard, "CRUISE", "Cruise 'n USA", mCard.saveIcon, mCard.saveBanner, "CRUISE",
                      &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);

            if (!cpuSetCodeHack(pCPU, 0x80103E0C, 0x1616FFF2, 0)) {
                return false;
            }
        } else if (!romTestCode(pROM, "NDNE")) {
            if (romTestCode(pROM, "NDOE")) {
                // Donkey Kong 64
                if (!cpuSetCodeHack(pCPU, 0x80000A04, 0x1462FFFF, 0)) {
                    return false;
                }
            } else if ((romTestCode(pROM, "NN6E")) || (romTestCode(pROM, "NN6J"))) {
                // Dr. Mario 64
                nTickMultiplier = 3;

                if (!cpuSetCodeHack(pCPU, 0x800005EC, 0x3C028001, -1)) {
                    return false;
                }

                if (romTestCode(pROM, "NN6J")) {
                    if (!cpuSetCodeHack(pCPU, 0x8006D458, 0x0C0189E9, 0x0C0189A3)) {
                        return false;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8006D664, 0x0C0189E9, 0x0C0189A3)) {
                        return false;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8006D6D0, 0x0C0189E9, 0x0C0189A3)) {
                        return false;
                    }
                } else {
                    if (!cpuSetCodeHack(pCPU, 0x8006D338, 0x0C0189A9, 0x0C018963)) {
                        return false;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8006D544, 0x0C0189A9, 0x0C018963)) {
                        return false;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8006D5B0, 0x0C0189A9, 0x0C018963)) {
                        return false;
                    }
                }

#if IS_OOT_EU || IS_MM
                strcat(buf1, "z_icon.tpl");
#endif
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                strcat(buf2, "z_bnr.tpl");
#endif
                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                mcardOpen(&mCard, "DRMARIO", "Dr. Mario", mCard.saveIcon, mCard.saveBanner, "DRMARIO",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
                gpSystem->eTypeROM = SRT_DRMARIO;
                pCPU->nCompileFlag |= 0x10;
            } else if (romTestCode(pROM, "CFZE")) {
                // F-Zero X
                if (!cpuSetCodeHack(pCPU, 0x800673A8, 0x144DFFFC, 0)) {
                    return false;
                }
                if (!cpuSetCodeHack(pCPU, 0x80067564, 0x144FFFFC, 0)) {
                    return false;
                }
                if (!cpuSetCodeHack(pCPU, 0x8006759C, 0x1459FFFC, 0)) {
                    return false;
                }
            } else if (romTestCode(pROM, "NLRE")) {
                // Lode Runner 3D
                if (!cpuSetCodeHack(pCPU, 0x80097B6C, 0x1443FFF9, 0)) {
                    return false;
                }
                if (!cpuSetCodeHack(pCPU, 0x80097BF4, 0x1443FFF9, 0)) {
                    return false;
                }
                if (!cpuSetCodeHack(pCPU, 0x80096D08, 0x08025B40, 0x1000FFFF)) {
                    return false;
                }
            } else if (romTestCode(pROM, "NMFE")) {
                // Mario Golf
                if (!cpuSetCodeHack(pCPU, 0x800B2DCC, 0x8C430004, -1)) {
                    return false;
                }
                if (!cpuSetCodeHack(pCPU, 0x800B2E70, 0x8C430004, -1)) {
                    return false;
                }
                if (!cpuSetCodeHack(pCPU, 0x80029EB8, 0x8C4252CC, -1)) {
                    return false;
                }
            } else if (ROM_IS_MK64(pROM)) {
                // Mario Kart 64
                pSystem->eTypeROM = SRT_MARIOKART;

#if IS_OOT_EU || IS_MM
                strcat(buf1, "z_icon.tpl");
#endif
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                strcat(buf2, "z_bnr.tpl");
#endif
                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                mcardOpen(&mCard, "KART", MCARD_FILE_NAME_MK64, mCard.saveIcon, mCard.saveBanner, "KART",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
                pCPU->nCompileFlag |= IS_MM_JP ? 0x110 : 0x10;
            } else if (ROM_IS_KIRBY(pROM)) {
                // Kirby 64
#if IS_MM
                pSystem->eTypeROM = SRT_KIRBY;
#endif

#if VERSION != MQ_J
                if (!audioEnable(SYSTEM_AUDIO(pSystem), false)) {
                    return false;
                }
#endif

                if (!cpuSetCodeHack(pCPU, 0x80020BCC, 0x8DF80034, -1)) {
                    return false;
                }
                if (!cpuSetCodeHack(pCPU, 0x80020EBC, 0x8DEFF330, -1)) {
                    return false;
                }

#if IS_MM
                strcat(buf1, "z_icon.tpl");
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

                strcat(buf2, "z_bnr.tpl");
                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1 &&
                    (simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL) == 0)) {
                    return false;
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                mcardOpen(&mCard, "KIRBY", "Kirby", mCard.saveIcon, mCard.saveBanner, "KIRBY",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x800);
                pCPU->nCompileFlag |= 0x110;
#endif
            } else if (romTestCode(pROM, "CLBE")) {
                // Mario Party 1
                pSystem->eTypeROM = SRT_MARIOPARTY1;

#if IS_OOT_EU || IS_MM
                strcat(buf1, "z_icon.tpl");
#endif
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                strcat(buf2, "z_bnr.tpl");
#endif
                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                mcardOpen(&mCard, "MP1", "Mario Party 1", mCard.saveIcon, mCard.saveBanner, "MP1",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
            } else if (romTestCode(pROM, "NMWE")) {
                // Mario Party 2
                pSystem->eTypeROM = SRT_MARIOPARTY2;

#if IS_OOT_EU || IS_MM
                strcat(buf1, "z_icon.tpl");
#endif
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                strcat(buf2, "z_bnr.tpl");
#endif
                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                mcardOpen(&mCard, "MP2", "Mario Party 2", mCard.saveIcon, mCard.saveBanner, "MP2",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);
            } else if (romTestCode(pROM, "NMVE")) {
                // Mario Party 3
                pSystem->eTypeROM = SRT_MARIOPARTY3;

#if IS_OOT_EU || IS_MM
                strcat(buf1, "z_icon.tpl");
#endif
                if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                strcat(buf2, "z_bnr.tpl");
#endif
                if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                    if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                        return false;
                    }
                }

                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                mcardOpen(&mCard, "MP3", "Mario Party 3", mCard.saveIcon, mCard.saveBanner, "MP3",
                          &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x800);
            } else if (!romTestCode(pROM, "NM3E") && !romTestCode(pROM, "NRIE")) {
                if (romTestCode(pROM, "NMQE")) {
                    // Paper Mario
#if IS_OOT_EU || IS_MM
                    strcat(buf1, "z_icon.tpl");
#endif
                    if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                        if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                            return false;
                        }
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);
#if IS_OOT_EU || IS_MM
                    strcat(buf2, "z_bnr.tpl");
#endif
                    if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                        if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                            return false;
                        }
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);

                    mcardOpen(&mCard, "PaperMario", "Paper Mario", mCard.saveIcon, mCard.saveBanner, "PAPERMARIO",
                              &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000, 0x20000);
                } else if (romTestCode(pROM, "NPOE")) {
#if IS_OOT_EU || IS_MM
                    strcat(buf1, "z_icon.tpl");
#endif
                    if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                        if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                            return false;
                        }
                    }

                    DVDClose(&fileInfo);
                    simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                    strcat(buf2, "z_bnr.tpl");
                    if (DVDOpen(buf2, &fileInfo) == 1) {
                        if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                            return false;
                        }
                    }
#else
                    if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                        if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                            return false;
                        }
                    }
#endif

                    DVDClose(&fileInfo);
#if IS_OOT_EU || IS_MM
                    simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
#else
                    simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);
#endif

                    mcardOpen(&mCard, "PokemonStadium", "Pokemon Stadium", mCard.saveIcon, mCard.saveBanner,
                              "POKEMONSTADIUM", &gSystemRomConfigurationList[i].currentControllerConfig, 0x24000,
                              0x20000);
                } else if (romTestCode(pROM, "NQKE")) {
                    if (!cpuSetCodeHack(pCPU, 0x8004989C, 0x1459FFFB, 0)) {
                        return false;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x80049FF0, 0x1608FFFB, 0)) {
                        return false;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8004A384, 0x15E0FFFB, 0)) {
                        return false;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x8004A97C, 0x15E0FFFB, 0)) {
                        return false;
                    }
                    if (!cpuSetCodeHack(pCPU, 0x80048FF8, 0x1000FFFD, 0x1000FFFF)) {
                        return false;
                    }
                } else if (!romTestCode(pROM, "NRSE") && !romTestCode(pROM, "NRZE")) {
                    if (romTestCode(pROM, "NFXE") || romTestCode(pROM, "NFXJ")) {
                        pSystem->eTypeROM = SRT_STARFOX;

#if IS_OOT_EU || IS_MM
                        strcat(buf1, "z_icon.tpl");
#endif
                        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                            if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                                return false;
                            }
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);
#if IS_OOT_EU || IS_MM
                        strcat(buf2, "z_bnr.tpl");
#endif
                        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                            if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                                return false;
                            }
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                        mcardOpen(&mCard, "STARFOX", MCARD_FILE_NAME_STARFOX, mCard.saveIcon, mCard.saveBanner,
                                  "STARFOX", &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x200);

#if IS_MM_JP
                        if (romTestCode(pROM, "NFXJ")) {
                            if (!cpuSetCodeHack(pCPU, 0x8019F548, 0xA2000000, 0)) {
                                return false;
                            }
                        }
#endif

                        pCPU->nCompileFlag |= 0x110;
                    } else if (romTestCode(pROM, "NGUJ")) {
                        if (!cpuSetCodeHack(pCPU, 0x80025D30, 0x3C018006, -1)) {
                            return false;
                        }
                    } else if (romTestCode(pROM, "NALE")) {
                        if (!cpuSetCodeHack(pCPU, 0x8000092C, 0x3C028004, -1)) {
                            return false;
                        }
                        if (!cpuSetCodeHack(pCPU, 0x8002103C, 0x3C028004, -1)) {
                            return false;
                        }
                        if (!cpuSetCodeHack(pCPU, 0x80021048, 0x3C028004, -1)) {
                            return false;
                        }
                        if (!cpuSetCodeHack(pCPU, 0x800A1BB8, 0x1440FFFD, 0)) {
                            return false;
                        }
                        if (!cpuSetCodeHack(pCPU, 0x800A1BE0, 0x1440FFFD, 0)) {
                            return false;
                        }
                        pCPU->nCompileFlag |= 0x110;
                    } else if (romTestCode(pROM, "NTEA")) {
                        pSystem->eTypeROM = SRT_1080;

                        if (!ramGetBuffer(SYSTEM_RAM(pSystem), (void**)&anMode, 0x300U, NULL)) {
                            return false;
                        }

                        anMode[4] = 0x17D7;
                        if (!ramGetBuffer(SYSTEM_RAM(pSystem), (void**)&anMode, 0x200U, NULL)) {
                            return false;
                        }

                        anMode[0] = 0xAC290000;
                        if (!ramGetBuffer(SYSTEM_RAM(pSystem), (void**)&anMode, 0x284U, NULL)) {
                            return false;
                        }

                        anMode[0] = 0x240B17D7;
                        if (!cpuSetCodeHack(pCPU, 0x800F04E8, 0x1218FFFB, 0)) {
                            return false;
                        }

#if IS_OOT_EU || IS_MM
                        strcat(buf1, "z_icon.tpl");
#endif
                        if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                            if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0, NULL)) {
                                return false;
                            }
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                        strcat(buf2, "z_bnr.tpl");
#endif
                        if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                            if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0, NULL)) {
                                return false;
                            }
                        }

                        DVDClose(&fileInfo);
                        simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                        mcardOpen(&mCard, "1080", "1080", mCard.saveIcon, mCard.saveBanner, "1080",
                                  &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
                    } else if (!romTestCode(pROM, "NTPE") && !romTestCode(pROM, "NEPE")) {
                        if (romTestCode(pROM, "NM8E")) {
                            if (!cpuSetCodeHack(pCPU, 0x80031D94, 0x8C421F6C, -1)) {
                                return false;
                            }
                        } else if (romTestCode(pROM, "NYLJ")) {
                            pSystem->eTypeROM = SRT_PANEL;
                            if (!cpuSetCodeHack(pCPU, 0x800A58F8, 0x8C62FF8C, -1)) {
                                return false;
                            }

#if IS_OOT_EU || IS_MM
                            strcat(buf1, "z_icon.tpl");
#endif
                            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                                if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0,
                                                      NULL)) {
                                    return false;
                                }
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                            strcat(buf2, "z_bnr.tpl");
#endif
                            if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                                if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0,
                                                      NULL)) {
                                    return false;
                                }
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);

                            mcardOpen(&mCard, "PANEL", "Panel de Pon", mCard.saveIcon, mCard.saveBanner, "PANEL",
                                      &gSystemRomConfigurationList[i].currentControllerConfig, 0xC000, 0x8000);
                            pCPU->nCompileFlag |= 0x10;
                        } else if (romTestCode(pROM, "NTUE")) {
                            if (!cpuSetCodeHack(pCPU, 0x8002BDD0, 0xA0000000, 0)) {
                                return false;
                            }
                        } else if (romTestCode(pROM, "NWRE")) {
                            pSystem->eTypeROM = SRT_WAVERACE;

                            if (!cpuSetCodeHack(pCPU, 0x8004795C, 0x1448FFFC, 0)) {
                                return false;
                            }

                            if (!cpuSetCodeHack(pCPU, 0x80047994, 0x144AFFFC, 0)) {
                                return false;
                            }

                            pCPU->nCompileFlag |= 0x10;
                        } else if (romTestCode(pROM, "NYSE")) {
#if IS_OOT_EU || IS_MM
                            strcat(buf1, "z_icon.tpl");
#endif
                            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                                if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0,
                                                      NULL)) {
                                    return false;
                                }
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);

#if IS_OOT_EU || IS_MM
                            strcat(buf2, "z_bnr.tpl");
#endif
                            if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                                if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0,
                                                      NULL)) {
                                    return false;
                                }
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                            mcardOpen(&mCard, "YoshiStory", "YoshiStory", mCard.saveIcon, mCard.saveBanner,
                                      "YoshiStory", &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000,
                                      0x800);
                        } else if (romTestCode(pROM, "NBNJ")) {
#if IS_OOT
                            mcardOpen(&mCard, "XXX", "XXX", mCard.saveIcon, mCard.saveBanner, "XXX",
                                      &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x800);
#endif
                            if (!cpuSetCodeHack(pCPU, 0x80000548, 0x08000156, 0x1000FFFF)) {
                                return false;
                            }

                            if (!cpuSetCodeHack(pCPU, 0x80000730, 0x3C02800C, -1)) {
                                return false;
                            }
#if IS_MM
                        } else if (romTestCode(pROM, "NRBJ")) {
                            // Mini Racers
                            pSystem->eTypeROM = SRT_SLICRADIC;

                            strcat(buf1, "z_icon.tpl");
                            if (DVDOpen(Z_ICON_PATH, &fileInfo) == 1) {
                                if (!simulatorDVDRead(&fileInfo, mCard.saveIcon, (gz_iconSize + 0x1F) & ~0x1F, 0,
                                                      NULL)) {
                                    return false;
                                }
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((TEXPalette*)mCard.saveIcon);
                            strcat(buf2, "z_bnr.tpl");
                            if (DVDOpen(Z_BNR_PATH, &fileInfo) == 1) {
                                if (!simulatorDVDRead(&fileInfo, mCard.saveBanner, (gz_bnrSize + 0x1F) & ~0x1F, 0,
                                                      NULL)) {
                                    return false;
                                }
                            }

                            DVDClose(&fileInfo);
                            simulatorUnpackTexPalette((TEXPalette*)mCard.saveBanner);
                            mcardOpen(&mCard, "SLICRADIC", "Slicradic", mCard.saveIcon, mCard.saveBanner, "SLICRADIC",
                                      &gSystemRomConfigurationList[i].currentControllerConfig, 0x4000, 0x800);
                            if (!cpuSetCodeHack(pCPU, 0x80066884, 0x8C62FF8C, -1)) {
                                return false;
                            }
                            pCPU->nCompileFlag |= 0x110;
#endif
                        } else if (!romGetCode(pROM, acCode)) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    if (!soundSetBufferSize(SYSTEM_SOUND(gpSystem), nSizeSound)) {
        return false;
    }

    pCPU->nTimeRetrace = nTimeRetrace;
    systemSetControllerConfiguration(&gSystemRomConfigurationList[0],
                                     gSystemRomConfigurationList[i].currentControllerConfig, false);

    for (iController = 0; iController < 4; iController++) {
        simulatorSetControllerMap((u32*)gSystemRomConfigurationList[i].controllerConfiguration[iController],
                                  iController);

        if (gSystemRomConfigurationList[i].storageDevice & 0x10) {
            if (!pifSetControllerType(pPIF, iController, 2)) {
                return false;
            }
        } else if ((1 << (iController << 3)) & gSystemRomConfigurationList[0].rumbleConfiguration) {
            if (!pifSetControllerType(pPIF, iController, 3)) {
                return false;
            }
        } else if (!pifSetControllerType(pPIF, iController, 1)) {
            return false;
        }
    }

    if (mCard.saveToggle == true) {
        systemSetControllerConfiguration(&gSystemRomConfigurationList[0], mCard.file.game.configuration, false);
    }

    return true;
}

static bool systemGetException(System* pSystem, SystemInterruptType eType, SystemException* pException) {
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
            return false;
    }

    return true;
}

static bool systemGet8(System* pSystem, u32 nAddress, s8* pData) {
    *pData = 0;
    return true;
}

static bool systemGet16(System* pSystem, u32 nAddress, s16* pData) {
    *pData = 0;
    return true;
}

static bool systemGet32(System* pSystem, u32 nAddress, s32* pData) {
    *pData = 0;
    return true;
}

static bool systemGet64(System* pSystem, u32 nAddress, s64* pData) {
    *pData = 0;
    return true;
}

static bool systemPut8(System* pSystem, u32 nAddress, s8* pData) { return true; }

static bool systemPut16(System* pSystem, u32 nAddress, s16* pData) { return true; }

static bool systemPut32(System* pSystem, u32 nAddress, s32* pData) { return true; }

static bool systemPut64(System* pSystem, u32 nAddress, s64* pData) { return true; }

static bool __systemCopyROM_Complete(void) {
    s32 iAddress;
    s32 nCount;
    u32 nAddress0;
    u32 nAddress1;
    u32 anAddress[0x20]; // size = 0x80

    nAddress0 = gpSystem->romCopy.nOffsetRAM;
    nAddress1 = nAddress0 + gpSystem->romCopy.nSize - 1;

    if (!frameInvalidateCache(SYSTEM_FRAME(gpSystem), gpSystem->romCopy.nOffsetRAM,
                              gpSystem->romCopy.nOffsetRAM + gpSystem->romCopy.nSize - 1)) {
        return false;
    }

    if (!rspInvalidateCache(SYSTEM_RSP(gpSystem), nAddress0, nAddress1)) {
        return false;
    }

    if (!cpuGetOffsetAddress(SYSTEM_CPU(gpSystem), anAddress, &nCount, gpSystem->romCopy.nOffsetRAM,
                             gpSystem->romCopy.nSize)) {
        return false;
    }

    for (iAddress = 0; iAddress < nCount; iAddress++) {
        nAddress0 = anAddress[iAddress];
        nAddress1 = nAddress0 + gpSystem->romCopy.nSize - 1;
        if (!cpuInvalidateCache(SYSTEM_CPU(gpSystem), nAddress0, nAddress1)) {
            return false;
        }
    }

    gpSystem->romCopy.nSize = 0;
    if ((gpSystem->romCopy.pCallback != NULL) && !gpSystem->romCopy.pCallback()) {
        return false;
    }

    return true;
}

bool systemCopyROM(System* pSystem, s32 nOffsetRAM, s32 nOffsetROM, s32 nSize, SystemCopyCallbackFunc pCallback) {
    void* pTarget;

    pSystem->romCopy.nSize = nSize;
    pSystem->romCopy.pCallback = pCallback;
    pSystem->romCopy.nOffsetRAM = nOffsetRAM & 0x7FFFFF;
    pSystem->romCopy.nOffsetROM = nOffsetROM;

    if (!ramGetBuffer(SYSTEM_RAM(pSystem), &pTarget, nOffsetRAM, (u32*)&nSize)) {
        return false;
    }

    if (pCallback == NULL) {
        if (!romCopy(SYSTEM_ROM(pSystem), pTarget, nOffsetROM, nSize, NULL)) {
            return false;
        }

        if (!__systemCopyROM_Complete()) {
            return false;
        }
    } else {
        if (!romCopy(SYSTEM_ROM(pSystem), pTarget, nOffsetROM, nSize, __systemCopyROM_Complete)) {
            return false;
        }
    }

    NO_INLINE();
    return true;
}

bool systemSetMode(System* pSystem, SystemMode eMode) {
    if (xlObjectTest(pSystem, &gClassSystem)) {
        pSystem->eMode = eMode;

        if (eMode == SM_STOPPED) {
            pSystem->nAddressBreak = -1;
        }

        return true;
    }

    return false;
}

bool systemGetMode(System* pSystem, SystemMode* peMode) {
    if (xlObjectTest(pSystem, &gClassSystem) && (peMode != NULL)) {
        *peMode = pSystem->eMode;
        return true;
    }

    return false;
}

bool systemSetStorageDevice(System* pSystem, SystemObjectType eStorageDevice) {
    pSystem->storageDevice = eStorageDevice;

    if (eStorageDevice == SOT_FLASH) {
        if (!xlObjectMake(&pSystem->apObject[SOT_FLASH], pSystem, &gClassFlash)) {
            return false;
        }

        if (!cpuMapObject(SYSTEM_CPU(pSystem), pSystem->apObject[SOT_FLASH], 0x08000000, 0x0801FFFF, 0)) {
            return false;
        }
    }

    if (eStorageDevice == SOT_SRAM) {
        if (!xlObjectMake(&pSystem->apObject[SOT_SRAM], pSystem, &gClassSram)) {
            return false;
        }

        if (!cpuMapObject(SYSTEM_CPU(pSystem), pSystem->apObject[SOT_SRAM], 0x08000000, 0x08007FFF, 0)) {
            return false;
        }
    }

    NO_INLINE();
    return true;
}

bool systemGetStorageDevice(System* pSystem, SystemObjectType* pStorageDevice) {
    *pStorageDevice = pSystem->storageDevice;
    return true;
}

bool systemReset(System* pSystem) {
    s64 nPC;
    s32 nOffsetRAM;
    SystemObjectType eObject;

    pSystem->nAddressBreak = -1;

    if (romGetImage(SYSTEM_ROM(pSystem), NULL)) {
        if (!systemSetupGameRAM(pSystem)) {
            return false;
        }

        if (!ramWipe(SYSTEM_RAM(pSystem))) {
            return false;
        }

        if (!romGetPC(SYSTEM_ROM(pSystem), (u64*)&nPC)) {
            return false;
        }

        nOffsetRAM = nPC & 0xFFFFFF;
        if (!systemCopyROM(pSystem, nOffsetRAM, 0x1000, 0x100000, NULL)) {
            return false;
        }

        if (!cpuReset(SYSTEM_CPU(pSystem))) {
            return false;
        }

        cpuSetXPC(SYSTEM_CPU(pSystem), nPC, 0, 0);

        if (!systemSetupGameALL(pSystem)) {
            return false;
        }

#if VERSION == MQ_J
        if (!libraryUpdate(SYSTEM_LIBRARY(pSystem))) {
            return false;
        }
#else
        for (eObject = 0; eObject < SOT_COUNT; eObject++) {
            if (pSystem->apObject[eObject] != NULL) {
                if (!xlObjectEvent(pSystem->apObject[eObject], 0x1003, NULL)) {
                    return false;
                }
            }
        }

        if (!xlObjectEvent(pSystem->pFrame, 0x1003, NULL)) {
            return false;
        }

        if (!xlObjectEvent(pSystem->pSound, 0x1003, NULL)) {
            return false;
        }
#endif
    }

    return true;
}

static inline bool systemTestClassObject(System* pSystem) {
    if (xlObjectTest(pSystem, &gClassSystem)) {
        pSystem->eMode = SM_STOPPED;
        pSystem->nAddressBreak = -1;

        return true;
    }

    return false;
}

bool systemExecute(System* pSystem, s32 nCount) {
    if (!cpuExecute(SYSTEM_CPU(pSystem), nCount, pSystem->nAddressBreak)) {
        if (!systemTestClassObject(pSystem)) {
            return false;
        }

        return false;
    }

    if (pSystem->nAddressBreak == SYSTEM_CPU(pSystem)->nPC) {
        if (!systemTestClassObject(pSystem)) {
            return false;
        }
    }

    return true;
}

bool systemCheckInterrupts(System* pSystem) {
    s32 iException;
    s32 nMaskFinal;
    bool bUsed;
    bool bDone;
    SystemException exception;
    CpuExceptionCode eCodeFinal;

    nMaskFinal = 0;
    eCodeFinal = CEC_NONE;
    bDone = false;
    pSystem->bException = false;

    for (iException = 0; iException < ARRAY_COUNT(pSystem->anException); iException++) {
        if (pSystem->anException[iException] != 0) {
            pSystem->bException = true;

            if (!bDone) {
                if (!systemGetException(pSystem, iException, &exception)) {
                    return false;
                }

                bUsed = false;

                if (exception.eCode == 0) {
                    if (cpuTestInterrupt(SYSTEM_CPU(pSystem), exception.nMask) &&
                        ((exception.eTypeMips == MIT_NONE) ||
                         mipsSetInterrupt(SYSTEM_MIPS(pSystem), exception.eTypeMips))) {
                        bUsed = true;
                    }
                } else {
                    bDone = true;

                    if (nMaskFinal == 0) {
                        bUsed = true;
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
            return false;
        }
    } else if (eCodeFinal != CEC_NONE) {
        if (!cpuException(SYSTEM_CPU(pSystem), eCodeFinal, 0)) {
            return false;
        }
    }

    return true;
}

bool systemExceptionPending(System* pSystem, SystemInterruptType nException) {
    if ((nException > -1) && (nException < ARRAY_COUNT(pSystem->anException))) {
        if (pSystem->anException[nException] != 0) {
            return true;
        }

        return false;
    }

    return false;
}

static inline bool systemClearExceptions(System* pSystem) {
    int iException;

    pSystem->bException = false;
    for (iException = 0; iException < 16; iException++) {
        pSystem->anException[iException] = 0;
    }
    return true;
}

bool systemEvent(System* pSystem, s32 nEvent, void* pArgument) {
    Cpu* pCPU;
    SystemException exception;
    SystemObjectType eObject;
    SystemObjectType storageDevice;

    switch (nEvent) {
        case 2:
            pSystem->eMode = SM_STOPPED;
            pSystem->eTypeROM = SRT_NONE;
            pSystem->nAddressBreak = -1;
#if VERSION != MM_J && VERSION != MM_E
            pSystem->bJapaneseVersion = false;
#endif
            pSystem->romCopy.nSize = 0;
            pSystem->pFrame = gpFrame;
            pSystem->pSound = gpSound;

#if VERSION == MQ_J
            pSystem->apObject[SOT_CPU] = NULL;
            pSystem->apObject[SOT_PIF] = NULL;
            pSystem->apObject[SOT_RAM] = NULL;
            pSystem->apObject[SOT_ROM] = NULL;
            pSystem->apObject[SOT_RSP] = NULL;
            pSystem->apObject[SOT_RDP] = NULL;
            pSystem->apObject[SOT_MIPS] = NULL;
            pSystem->apObject[SOT_DISK] = NULL;
            pSystem->apObject[SOT_FLASH] = NULL;
            pSystem->apObject[SOT_SRAM] = NULL;
            pSystem->apObject[SOT_AUDIO] = NULL;
            pSystem->apObject[SOT_VIDEO] = NULL;
            pSystem->apObject[SOT_SERIAL] = NULL;
            pSystem->apObject[SOT_LIBRARY] = NULL;
            pSystem->apObject[SOT_PERIPHERAL] = NULL;
            pSystem->apObject[SOT_RDB] = NULL;
#else
            for (eObject = 0; eObject < SOT_COUNT; eObject++) {
                pSystem->apObject[eObject] = NULL;
            }
#endif

            systemClearExceptions(pSystem);

            for (eObject = 0; eObject < SOT_COUNT; eObject++) {
                switch (eObject) {
                    case SOT_CPU:
                        if (!xlObjectMake(&pSystem->apObject[SOT_CPU], pSystem, &gClassCPU)) {
                            return false;
                        }
                        pCPU = SYSTEM_CPU(pSystem);
                        if (!cpuMapObject(pCPU, pSystem, 0, 0xFFFFFFFF, 0)) {
                            return false;
                        }
                        break;
                    case SOT_PIF:
                        if (!xlObjectMake(&pSystem->apObject[SOT_PIF], pSystem, &gClassPIF)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_PIF], 0x1FC00000, 0x1FC007FF, 0)) {
                            return false;
                        }
                        break;
                    case SOT_RAM:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RAM], pSystem, &gClassRAM)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RAM], 0, 0x03EFFFFF, 0x100)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RAM], 0x03F00000, 0x03FFFFFF, 2)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RAM], 0x04700000, 0x047FFFFF, 1)) {
                            return false;
                        }
                        break;
                    case SOT_ROM:
                        if (!xlObjectMake(&pSystem->apObject[SOT_ROM], pSystem, &gClassROM)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_ROM], 0x10000000, 0x1FBFFFFF, 0)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_ROM], 0x1FF00000, 0x1FF0FFFF, 1)) {
                            return false;
                        }
                        break;
                    case SOT_RSP:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RSP], pSystem, &gClassRSP)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RSP], 0x04000000, 0x040FFFFF, 0)) {
                            return false;
                        }
                        break;
                    case SOT_RDP:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RDP], pSystem, &gClassRDP)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RDP], 0x04100000, 0x041FFFFF, 0)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RDP], 0x04200000, 0x042FFFFF, 1)) {
                            return false;
                        }
                        break;
                    case SOT_MIPS:
                        if (!xlObjectMake(&pSystem->apObject[SOT_MIPS], pSystem, &gClassMips)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_MIPS], 0x04300000, 0x043FFFFF, 0)) {
                            return false;
                        }
                        break;
                    case SOT_DISK:
                        if (!xlObjectMake(&pSystem->apObject[SOT_DISK], pSystem, &gClassDisk)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_DISK], 0x05000000, 0x05FFFFFF, 0)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_DISK], 0x06000000, 0x06FFFFFF, 1)) {
                            return false;
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
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_AUDIO], 0x04500000, 0x045FFFFF, 0)) {
                            return false;
                        }
                        break;
                    case SOT_VIDEO:
                        if (!xlObjectMake(&pSystem->apObject[SOT_VIDEO], pSystem, &gClassVideo)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_VIDEO], 0x04400000, 0x044FFFFF, 0)) {
                            return false;
                        }
                        break;
                    case SOT_SERIAL:
                        if (!xlObjectMake(&pSystem->apObject[SOT_SERIAL], pSystem, &gClassSerial)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_SERIAL], 0x04800000, 0x048FFFFF, 0)) {
                            return false;
                        }
                        break;
                    case SOT_LIBRARY:
                        if (!xlObjectMake(&pSystem->apObject[SOT_LIBRARY], pSystem, &gClassLibrary)) {
                            return false;
                        }
                        break;
                    case SOT_PERIPHERAL:
                        if (!xlObjectMake(&pSystem->apObject[SOT_PERIPHERAL], pSystem, &gClassPeripheral)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_PERIPHERAL], 0x04600000, 0x046FFFFF, 0)) {
                            return false;
                        }
                        break;
                    case SOT_RDB:
                        if (!xlObjectMake(&pSystem->apObject[SOT_RDB], pSystem, &gClassRdb)) {
                            return false;
                        }
                        if (!cpuMapObject(pCPU, pSystem->apObject[SOT_RDB], 0x04900000, 0x0490FFFF, 0)) {
                            return false;
                        }
                        break;
                    default:
                        return false;
                }
            }
            break;
        case 3:
            for (storageDevice = 0; storageDevice < SOT_COUNT; storageDevice++) {
                if (storageDevice != SOT_FLASH && storageDevice != SOT_SRAM) {
                    if (!xlObjectFree(&pSystem->apObject[storageDevice])) {
                        return false;
                    }
                } else if (storageDevice == SOT_FLASH) {
                    if (pSystem->storageDevice == SOT_FLASH) {
                        if (!xlObjectFree(&pSystem->apObject[SOT_FLASH])) {
                            return false;
                        }
                    }
                } else if (storageDevice == SOT_SRAM) {
                    if (pSystem->storageDevice == SOT_SRAM) {
                        if (!xlObjectFree(&pSystem->apObject[SOT_SRAM])) {
                            return false;
                        }
                    }
                }
            }
            break;
        case 0x1001:
            if (!systemGetException(pSystem, (SystemInterruptType)(s32)pArgument, &exception)) {
                return false;
            }
            if (exception.eTypeMips != MIT_NONE) {
                mipsResetInterrupt(SYSTEM_MIPS(pSystem), exception.eTypeMips);
            }
            break;
        case 0x1000:
            if (((SystemInterruptType)(s32)pArgument > SIT_NONE) && ((SystemInterruptType)(s32)pArgument < SIT_COUNT)) {
                pSystem->bException = true;
                pSystem->anException[(SystemInterruptType)(s32)pArgument]++;
                break;
            }
            return false;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pSystem), pArgument, (Put8Func)systemPut8, (Put16Func)systemPut16,
                                 (Put32Func)systemPut32, (Put64Func)systemPut64)) {
                return false;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pSystem), pArgument, (Get8Func)systemGet8, (Get16Func)systemGet16,
                                 (Get32Func)systemGet32, (Get64Func)systemGet64)) {
                return false;
            }
            break;
        case 0:
        case 1:
        case 5:
        case 6:
        case 7:
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
