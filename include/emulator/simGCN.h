#ifndef _SIMGCN_H
#define _SIMGCN_H

#include "dolphin.h"
#include "emulator/system.h"

typedef enum SimulatorMessage {
    S_M_NONE = -1,
    S_M_DISK_COVER_OPEN = 0,
    S_M_DISK_WRONG_DISK = 1,
    S_M_DISK_READING_DISK = 2,
    S_M_DISK_FATAL_ERROR = 3,
    S_M_DISK_RETRY_ERROR = 4,
    S_M_DISK_NO_DISK = 5,
    S_M_DISK_DEFAULT_ERROR = 6,
    S_M_CARD_LD01 = 7,
    S_M_CARD_LD02 = 8,
    S_M_CARD_LD03 = 9,
    S_M_CARD_LD04 = 10,
    S_M_CARD_LD05_1 = 11,
    S_M_CARD_LD05_2 = 12,
    S_M_CARD_LD06_1 = 13,
    S_M_CARD_LD06_2 = 14,
    S_M_CARD_LD06_3 = 15,
    S_M_CARD_LD06_4 = 16,
    S_M_CARD_LD07 = 17,
    S_M_CARD_GF01 = 18,
    S_M_CARD_GF02 = 19,
    S_M_CARD_GF03 = 20,
    S_M_CARD_GF04 = 21,
    S_M_CARD_GF05 = 22,
    S_M_CARD_GF06 = 23,
    S_M_CARD_IN01 = 24,
    S_M_CARD_IN02 = 25,
    S_M_CARD_IN03 = 26,
    S_M_CARD_IN04 = 27,
    S_M_CARD_IN05 = 28,
    S_M_CARD_SV01 = 29,
    S_M_CARD_SV01_2 = 30,
    S_M_CARD_SV02 = 31,
    S_M_CARD_SV03 = 32,
    S_M_CARD_SV04 = 33,
    S_M_CARD_SV05_1 = 34,
    S_M_CARD_SV06_1 = 35,
    S_M_CARD_SV06_2 = 36,
    S_M_CARD_SV06_3 = 37,
    S_M_CARD_SV06_4 = 38,
    S_M_CARD_SV06_5 = 39,
    S_M_CARD_SV07 = 40,
    S_M_CARD_SV08 = 41,
    S_M_CARD_SV09 = 42,
    S_M_CARD_SV10 = 43,
    S_M_CARD_SV11 = 44,
    S_M_CARD_SV12 = 45,
    S_M_CARD_SV_SHARE = 46,
    S_M_CARD_DEFAULT_ERROR = 47,
} SimulatorMessage;

typedef enum SimulatorArgumentType {
    SAT_NONE = -1,
    SAT_NAME = 0,
    SAT_PROGRESSIVE = 1,
    SAT_VIBRATION = 2,
    SAT_CONTROLLER = 3,
    SAT_XTRA = 4,
    SAT_MEMORYCARD = 5,
    SAT_MOVIE = 6,
    SAT_RESET = 7,
    SAT_COUNT = 8
} SimulatorArgumentType;

extern bool gDVDResetToggle;
extern bool gbDisplayedError;

extern void* gpFrame;
extern void* gpSound;
extern System* gpSystem;

extern u32 gz_bnrSize;
extern u32 gz_iconSize;

extern u8 gcoverOpen[];
extern u8 gnoDisk[];
extern u8 gretryErr[];
extern u8 gfatalErr[];
extern u8 gwrongDisk[];
extern u8 greadingDisk[];
extern u8 gbar[];
extern u8 gyes[];
extern u8 yno[];
extern u8 gmesgOK[];

#if IS_EU
extern u8 gLanguage;

extern u8 ggerman_coverOpen[];
extern u8 ggerman_wrongDisk[];
extern u8 ggerman_readingDisk[];
extern u8 ggerman_retryErr[];
extern u8 ggerman_fatalErr[];
extern u8 ggerman_noDisk[];
extern u8 ggerman_bar[];
extern u8 ggerman_yes[];
extern u8 ggerman_no[];
extern u8 ggerman_mesgOK[];

extern u8 gfrench_coverOpen[];
extern u8 gfrench_wrongDisk[];
extern u8 gfrench_readingDisk[];
extern u8 gfrench_retryErr[];
extern u8 gfrench_fatalErr[];
extern u8 gfrench_noDisk[];
extern u8 gfrench_bar[];
extern u8 gfrench_yes[];
extern u8 gfrench_no[];
extern u8 gfrench_mesgOK[];

#if VERSION == CE_E
extern u8 gspanish_coverOpen[];
extern u8 gspanish_wrongDisk[];
extern u8 gspanish_readingDisk[];
extern u8 gspanish_retryErr[];
extern u8 gspanish_fatalErr[];
extern u8 gspanish_noDisk[];
extern u8 gspanish_bar[];
extern u8 gspanish_yes[];
extern u8 gspanish_no[];
extern u8 gspanish_mesgOK[];

extern u8 gitalian_coverOpen[];
extern u8 gitalian_wrongDisk[];
extern u8 gitalian_readingDisk[];
extern u8 gitalian_retryErr[];
extern u8 gitalian_fatalErr[];
extern u8 gitalian_noDisk[];
extern u8 gitalian_bar[];
extern u8 gitalian_yes[];
extern u8 gitalian_no[];
extern u8 gitalian_mesgOK[];
#endif
#endif // IS_EU

extern s16 Vert_s16[];
extern u32 Colors_u32[];
extern u8 TexCoords_u8[];

extern char gpErrorMessageBuffer[20480];

void simulatorUnpackTexPalette(TEXPalette* pal);
bool simulatorDVDOpen(char* szNameFile, DVDFileInfo* pFileInfo);
bool simulatorDVDRead(DVDFileInfo* pFileInfo, void* anData, s32 nSizeRead, s32 nOffset, DVDCallback callback);
bool simulatorShowLoad(s32 unknown, char* szNameFile, f32 rProgress);
bool simulatorReadEEPROM(u8 address, u8* data);
bool simulatorWriteEEPROM(u8 address, u8* data);
bool simulatorReadSRAM(u32 address, u8* data, s32 size);
bool simulatorWriteSRAM(u32 address, u8* data, s32 size);
bool simulatorReadFLASH(u32 address, u8* data, s32 size);
bool simulatorWriteFLASH(u32 address, u8* data, s32 size);
bool simulatorRumbleStart(s32 channel);
bool simulatorRumbleStop(s32 channel);
bool simulatorCopyControllerMap(u32* mapDataOutput, u32* mapDataInput);
bool simulatorReadController(s32 channel, u32* anData, u8* ptx);
bool simulatorDetectController(s32 channel);
bool simulatorReadPak(s32 channel, u16 address, u8* data);
bool simulatorWritePak(s32 channel, u16 address, u8* data);
bool simulatorSetControllerMap(u32* mapData, s32 channel);
void simulatorResetAndPlayMovie(void);
bool simulatorDrawErrorMessage(SimulatorMessage simulatorErrorMessage, bool drawBar, s32 percent);
bool simulatorDVDShowError(s32 nStatus, void*, s32, u32);

#if VERSION == MQ_J
bool simulatorTestReset(bool IPL, bool forceMenu, bool allowReset);
#else
bool simulatorTestReset(bool IPL, bool forceMenu, bool allowReset, bool usePreviousSettings);
#endif

bool simulatorGetArgument(SimulatorArgumentType eType, char** pszArgument);
bool simulatorPlayMovie(void);
bool xlMain(void);
bool simulatorMCardPollDrawFormatBar(void);
bool simulatorPrepareMessage(SimulatorMessage simulatorErrorMessage);
bool simulatorMCardPollDrawBar(void);
bool simulatorDrawMCardText(void);
bool simulatorDrawErrorMessageWait(SimulatorMessage simulatorErrorMessage);
bool simulatorDrawYesNoMessage(SimulatorMessage simulatorMessage, bool* yes);

#if VERSION == MQ_J
#define SIMULATOR_TEST_RESET(IPL, forceMenu, allowReset, usePreviousSettings) \
    simulatorTestReset(IPL, forceMenu, allowReset)
#else
#define SIMULATOR_TEST_RESET(IPL, forceMenu, allowReset, usePreviousSettings) \
    simulatorTestReset(IPL, forceMenu, allowReset, usePreviousSettings)
#endif

#endif
