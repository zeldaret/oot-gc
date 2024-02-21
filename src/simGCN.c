#include "simGCN.h"

// TODO: move to macros.h
#define ALIGNAS(N) __attribute__((aligned(N)))

const f32 D_800D2FE0[] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D3010[] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D3040[] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D3070[] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D30A0[] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D30D0[] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D3100[] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

u8 gcoverOpen[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000D8880, 0x000028C1)
};

u8 gnoDisk[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000DB160, 0x00001F01)
};

u8 gretryErr[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000DD080, 0x00002441)
};

u8 gfatalErr[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000DF4E0, 0x000032E1)
};

u8 gwrongDisk[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E27E0, 0x00001F01)
};

u8 greadingDisk[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E4700, 0x00000C41)
};

u8 gbar[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E5360, 0x00000741)
};

u8 gyes[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E5AC0, 0x000005C1)
};

u8 gno[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E60A0, 0x000005C1)
};

u8 gmesgOK[] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E6680, 0x00000341)
};

s16 Vert_s16[12] ALIGNAS(32) = {0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF};
s16 VertTitle_s16[12] ALIGNAS(32) = {0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF};
s16 VertYes_s16[12] ALIGNAS(32) = {0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF};
s16 VertNo_s16[12] ALIGNAS(32) = {0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF};
s16 Vert_s16Bar[12] ALIGNAS(32) = {0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF};
u32 Colors_u32[3] ALIGNAS(32) = {0x000000FF, 0x000000FF, 0x000000FF};
u8 TexCoords_u8[] ALIGNAS(32) = {0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01};

char D_800E9A28[] = "Play Delay";
char D_800E9A34[] = "Silence Count";
char D_800E9A44[] = "Fade Up Count";
char D_800E9A54[] = "How many audio frames the\ngame must be playing before it\nconsiders the sound stable";
char D_800E9AA8[] = "How many audio frames the\ngame must NOT play before it\nconsiders itself unstable";
char D_800E9AFC[] = "How many audio frames to\nperform a fade up on the audio";
char D_800E9B34[] = "\n\nERROR: This program MUST be run on a system with 24MB (or less) memory!\n";
char D_800E9B80[] = "       Please reduce memory-size to 24MB (using 'setsmemsize 0x1800000')...\n";
char D_800E9BD0[] = "zlj_f.n64";
char D_800E9BDC[] = "cursor.raw";

void* jtbl_800E9BE8[] = {
    (void*)0x80008684, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x80008678, (void*)0x800086B8,
    (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x80008690, (void*)0x800086B8,
    (void*)0x800086B8, (void*)0x8000866C, (void*)0x800086B8, (void*)0x8000869C, (void*)0x800086B8, (void*)0x800086B8,
    (void*)0x800086B8, (void*)0x80008660, (void*)0x800086B8, (void*)0x800086A8, (void*)0x800086B8, (void*)0x800086B8,
    (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8,
    (void*)0x800086B8, (void*)0x800086B8, (void*)0x80008684, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8,
    (void*)0x80008678, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8,
    (void*)0x80008690, (void*)0x800086B8, (void*)0x800086B8, (void*)0x8000866C, (void*)0x800086B8, (void*)0x8000869C,
    (void*)0x800086B8, (void*)0x800086B8, (void*)0x800086B8, (void*)0x80008660, (void*)0x800086B8, (void*)0x800086A8,
};

void* jtbl_800E9CC0[] = {
    (void*)0x8000882C, (void*)0x80008834, (void*)0x8000883C, (void*)0x80008844,
    (void*)0x80008850, (void*)0x8000885C, (void*)0x80008868,
};

char D_800E9CDC[] = "Invalid Message Image Data - Assuming SV09";
char D_800E9D08[] = "simGCN.c";
char D_800E9D14[] = "TPL/msg_ld01.tpl";
char D_800E9D28[] = "TPL/msg_ld02.tpl";
char D_800E9D3C[] = "TPL/msg_ld03.tpl";
char D_800E9D50[] = "TPL/msg_ld04.tpl";
char D_800E9D64[] = "TPL/msg_ld05_1.tpl";
char D_800E9D78[] = "TPL/msg_ld06_1.tpl";
char D_800E9D8C[] = "TPL/msg_ld06_2.tpl";
char D_800E9DA0[] = "TPL/msg_ld06_3.tpl";
char D_800E9DB4[] = "TPL/msg_gf03.tpl";
char D_800E9DC8[] = "TPL/msg_gf04.tpl";
char D_800E9DDC[] = "TPL/msg_gf05.tpl";
char D_800E9DF0[] = "TPL/msg_gf06.tpl";
char D_800E9E04[] = "TPL/msg_in03.tpl";
char D_800E9E18[] = "TPL/msg_in04.tpl";
char D_800E9E2C[] = "TPL/msg_in05.tpl";
char D_800E9E40[] = "TPL/msg_sv01.tpl";
char D_800E9E54[] = "TPL/msg_sv01_2.tpl";
char D_800E9E68[] = "TPL/msg_sv02.tpl";
char D_800E9E7C[] = "TPL/msg_sv03.tpl";
char D_800E9E90[] = "TPL/msg_sv04.tpl";
char D_800E9EA4[] = "TPL/msg_sv05_1.tpl";
char D_800E9EB8[] = "TPL/msg_sv06_1.tpl";
char D_800E9ECC[] = "TPL/msg_sv06_2.tpl";
char D_800E9EE0[] = "TPL/msg_sv06_3.tpl";
char D_800E9EF4[] = "TPL/msg_sv07.tpl";
char D_800E9F08[] = "TPL/msg_sv10.tpl";
char D_800E9F1C[] = "TPL/msg_sv11.tpl";
char D_800E9F30[] = "TPL/msg_sv12.tpl";
char D_800E9F44[] = "TPL/msg_sv_share.tpl";

void* jtbl_800E9F5C[] = {
    (void*)0x80009A74, (void*)0x80009C24, (void*)0x80009DD4, (void*)0x80009F84, (void*)0x8000A134, (void*)0x8000CB64,
    (void*)0x8000A2E4, (void*)0x8000A494, (void*)0x8000A644, (void*)0x8000CB64, (void*)0x8000CB64, (void*)0x8000CB64,
    (void*)0x8000CB64, (void*)0x8000A7F4, (void*)0x8000A9A4, (void*)0x8000AB54, (void*)0x8000AD04, (void*)0x8000CB64,
    (void*)0x8000CB64, (void*)0x8000AEB4, (void*)0x8000B064, (void*)0x8000B214, (void*)0x8000B3C4, (void*)0x8000B574,
    (void*)0x8000B724, (void*)0x8000B8D4, (void*)0x8000BA84, (void*)0x8000BC34, (void*)0x8000BDE4, (void*)0x8000BF94,
    (void*)0x8000C144, (void*)0x8000CB64, (void*)0x8000CB64, (void*)0x8000C2F4, (void*)0x8000CB64, (void*)0x8000CB64,
    (void*)0x8000C4A4, (void*)0x8000C654, (void*)0x8000C804, (void*)0x8000C9B4,
};

char D_800E9FFC[] = "TPL/msg_ld05_2.tpl";
char D_800EA010[] = "TPL/msg_ld06_4.tpl";
char D_800EA024[] = "TPL/msg_ld07.tpl";
char D_800EA038[] = "TPL/msg_gf01.tpl";
char D_800EA04C[] = "TPL/msg_in01.tpl";
char D_800EA060[] = "TPL/msg_sv06_4.tpl";
char D_800EA074[] = "TPL/msg_sv06_5.tpl";
char D_800EA088[] = "TPL/msg_sv08.tpl";

void* jtbl_800EA09C[] = {
    (void*)0x8000CBC8, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CC30, (void*)0x8000CC98,
    (void*)0x8000CD00, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08,
    (void*)0x8000CD68, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08,
    (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CF08,
    (void*)0x8000CF08, (void*)0x8000CF08, (void*)0x8000CDD0, (void*)0x8000CE38, (void*)0x8000CF08, (void*)0x8000CEA0,
};

char D_800EA114[] = "TPL/msg_in02.tpl";
char D_800EA128[] = "TPL/msg_sv09.tpl";
char D_800EA13C[] = "TPL/msg_gf02.tpl";

void* jtbl_800EA150[] = {
    (void*)0x8000D3B8, (void*)0x8000D3F4, (void*)0x8000D434, (void*)0x8000D4B0,
    (void*)0x8000D474, (void*)0x8000D4EC, (void*)0x8000D528,
};

char D_800EA16C[] = "ShowError: Unknown FileInfoStatus: %d";

void* jtbl_800EA194[] = {
    (void*)0x8000EEA8, (void*)0x8000EEEC, (void*)0x8000EEEC, (void*)0x8000EEEC, (void*)0x8000EEEC,
    (void*)0x8000EEB0, (void*)0x8000EEB8, (void*)0x8000EEC0, (void*)0x8000EEEC, (void*)0x8000EEEC,
    (void*)0x8000EEEC, (void*)0x8000EEEC, (void*)0x8000EEC8,
};

static f32 gOrthoMtx[4][4] ALIGNAS(32);
static u32 gContMap[4][20];
static char* gaszArgument[8];

u32 gmsg_ld01Size = 0x00003E20;
u32 gmsg_ld02Size = 0x00003E20;
u32 gmsg_ld03Size = 0x00003E20;
u32 gmsg_ld04Size = 0x00003E20;
u32 gmsg_ld05_1Size = 0x00003E20;
u32 gmsg_ld05_2Size = 0x00003E20;
u32 gmsg_ld06_1Size = 0x00003E20;
u32 gmsg_ld06_2Size = 0x00003E20;
u32 gmsg_ld06_3Size = 0x00003E20;
u32 gmsg_ld06_4Size = 0x00003E20;
u32 gmsg_ld07Size = 0x00003E20;
u32 gmsg_gf01Size = 0x00003E20;
u32 gmsg_gf02Size = 0x00003E20;
u32 gmsg_gf03Size = 0x00003E20;
u32 gmsg_gf04Size = 0x00003E20;
u32 gmsg_gf05Size = 0x00003E20;
u32 gmsg_gf06Size = 0x00003E20;
u32 gmsg_in01Size = 0x00003E20;
u32 gmsg_in02Size = 0x00003E20;
u32 gmsg_in03Size = 0x00003E20;
u32 gmsg_in04Size = 0x00003E20;
u32 gmsg_in05Size = 0x00003E20;
u32 gmsg_sv01Size = 0x00003E20;
u32 gmsg_sv01_2Size = 0x00003E20;
u32 gmsg_sv02Size = 0x00003E20;
u32 gmsg_sv03Size = 0x00003E20;
u32 gmsg_sv04Size = 0x00003E20;
u32 gmsg_sv05_1Size = 0x00003E20;
u32 gmsg_sv06_1Size = 0x00003E20;
u32 gmsg_sv06_2Size = 0x00003E20;
u32 gmsg_sv06_3Size = 0x00003E20;
u32 gmsg_sv06_4Size = 0x00003E20;
u32 gmsg_sv06_5Size = 0x00003E20;
u32 gmsg_sv07Size = 0x00003E20;
u32 gmsg_sv08Size = 0x00003E20;
u32 gmsg_sv09Size = 0x00003E20;
u32 gmsg_sv10Size = 0x00003E20;
u32 gmsg_sv11Size = 0x00003E20;
u32 gmsg_sv12Size = 0x00003E20;
u32 gmsg_sv_shareSize = 0x00003E20;
u32 gz_bnrSize = 0x00001840;
u32 gz_iconSize = 0x00001840;

s32 gHighlightChoice = 0x00000001;
__anon_0x61D7 simulatorMessageCurrent = S_M_NONE;
s32 gResetBeginFlag = 0x00000001;

char D_80134D9C[8] = "yes.raw";
char D_80134DA4[7] = "no.raw";

// TODO: struct
static s32 gpCode;

void* gpFrame;
void* gpSound;
System* gpSystem;

s32 gbDisplayedError;
s32 gPreviousAllowResetSetting;
s32 gPreviousForceMenuSetting;
s32 gPreviousIPLSetting;

// TODO: make static (doesn't match .sbss currently)
u32 gnTickReset;
s32 gbReset;

// TODO: make in-function static (doesn't match .sbss currently)
u32 nCurrButton;
u32 nPrevButton;
s32 toggle;

s32 gDVDResetToggle;
s32 gButtonDownToggle;

const s32 D_80135D18 = 0;
const s32 D_80135D1C = 0;
const s32 D_80135D20 = 0;

const f32 D_80135D24 = 0.0;
const f32 D_80135D28 = 1.0;
const f32 D_80135D2C = 0.10000000149011612;
const f32 D_80135D30 = 100.0;
const f64 D_80135D38 = 4503601774854144.0;
const f32 D_80135D40 = 0.5;
const f64 D_80135D48 = 4503599627370496.0;
const f32 D_80135D50 = -1.0;
const f32 D_80135D54 = 1.100000023841858;
const f32 D_80135D58 = 0.9090908765792847;
const f32 D_80135D5C = 240.0;
const f32 D_80135D60 = 320.0;
const f32 D_80135D64 = 10000.0;
const f32 D_80135D68 = 160.0;
const f32 D_80135D6C = 120.0;

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorGXInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorUnpackTexPalette.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDVDShowError.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDVDOpen.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDVDRead.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorPlayMovie.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawImage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawYesNoImage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawOKImage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawErrorMessage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorPrepareMessage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawYesNoMessageLoop.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawYesNoMessage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawErrorMessageWait.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorReset.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorResetAndPlayMovie.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorSetControllerMap.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorCopyControllerMap.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorReadController.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorShowLoad.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDetectController.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorReadPak.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorWritePak.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorReadEEPROM.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorWriteEEPROM.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorReadSRAM.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorWriteSRAM.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorReadFLASH.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorWriteFLASH.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorRumbleStart.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorRumbleStop.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorTestReset.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawMCardText.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorMCardPollDrawBar.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorMCardPollDrawFormatBar.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawCursor.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorParseArguments.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorGetArgument.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/xlMain.s")
