#include "simGCN.h"
#include "codeGCN.h"
#include "dolphin.h"
#include "macros.h"
#include "mcardGCN.h"
#include "movie.h"
#include "pif.h"
#include "rom.h"
#include "soundGCN.h"
#include "system.h"
#include "xlObject.h"
#include "xlPostGCN.h"

//! TODO: Move these to proper headers
extern _XL_OBJECTTYPE gClassCode;
extern _XL_OBJECTTYPE gClassFrame;
extern _XL_OBJECTTYPE gClassSound;
extern _XL_OBJECTTYPE gClassSystem;

extern GXRenderModeObj* rmode;
extern s32 gMovieErrorToggle;
extern char gpErrorMessageBuffer[20480];

const f32 D_800D2FE0[3][4] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, -1.0},
};

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

s16 Vert_s16[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

s16 VertTitle_s16[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

s16 VertYes_s16[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

s16 VertNo_s16[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

s16 Vert_s16Bar[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

u32 Colors_u32[3] ALIGNAS(32) = {
    0x000000FF,
    0x000000FF,
    0x000000FF,
};

u8 TexCoords_u8[] ALIGNAS(32) = {
    0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01,
};

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

extern void *lbl_80008684, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_80008678, *lbl_800086B8, *lbl_800086B8,
    *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_80008690, *lbl_800086B8, *lbl_800086B8, *lbl_8000866C,
    *lbl_800086B8, *lbl_8000869C, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_80008660, *lbl_800086B8,
    *lbl_800086A8, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8,
    *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_80008684, *lbl_800086B8, *lbl_800086B8,
    *lbl_800086B8, *lbl_80008678, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8, *lbl_800086B8,
    *lbl_80008690, *lbl_800086B8, *lbl_800086B8, *lbl_8000866C, *lbl_800086B8, *lbl_8000869C, *lbl_800086B8,
    *lbl_800086B8, *lbl_800086B8, *lbl_80008660, *lbl_800086B8, *lbl_800086A8;

void* jtbl_800E9BE8[] = {
    &lbl_80008684, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_80008678, &lbl_800086B8, &lbl_800086B8,
    &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_80008690, &lbl_800086B8, &lbl_800086B8, &lbl_8000866C,
    &lbl_800086B8, &lbl_8000869C, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_80008660, &lbl_800086B8,
    &lbl_800086A8, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8,
    &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_80008684, &lbl_800086B8, &lbl_800086B8,
    &lbl_800086B8, &lbl_80008678, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8, &lbl_800086B8,
    &lbl_80008690, &lbl_800086B8, &lbl_800086B8, &lbl_8000866C, &lbl_800086B8, &lbl_8000869C, &lbl_800086B8,
    &lbl_800086B8, &lbl_800086B8, &lbl_80008660, &lbl_800086B8, &lbl_800086A8,
};

extern void *lbl_8000882C, *lbl_80008834, *lbl_8000883C, *lbl_80008844, *lbl_80008850, *lbl_8000885C, *lbl_80008868;

void* jtbl_800E9CC0[] = {
    &lbl_8000882C, &lbl_80008834, &lbl_8000883C, &lbl_80008844, &lbl_80008850, &lbl_8000885C, &lbl_80008868,
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

extern void *lbl_80009A74, *lbl_80009C24, *lbl_80009DD4, *lbl_80009F84, *lbl_8000A134, *lbl_8000CB64, *lbl_8000A2E4,
    *lbl_8000A494, *lbl_8000A644, *lbl_8000CB64, *lbl_8000CB64, *lbl_8000CB64, *lbl_8000CB64, *lbl_8000A7F4,
    *lbl_8000A9A4, *lbl_8000AB54, *lbl_8000AD04, *lbl_8000CB64, *lbl_8000CB64, *lbl_8000AEB4, *lbl_8000B064,
    *lbl_8000B214, *lbl_8000B3C4, *lbl_8000B574, *lbl_8000B724, *lbl_8000B8D4, *lbl_8000BA84, *lbl_8000BC34,
    *lbl_8000BDE4, *lbl_8000BF94, *lbl_8000C144, *lbl_8000CB64, *lbl_8000CB64, *lbl_8000C2F4, *lbl_8000CB64,
    *lbl_8000CB64, *lbl_8000C4A4, *lbl_8000C654, *lbl_8000C804, *lbl_8000C9B4;

void* jtbl_800E9F5C[] = {
    &lbl_80009A74, &lbl_80009C24, &lbl_80009DD4, &lbl_80009F84, &lbl_8000A134, &lbl_8000CB64, &lbl_8000A2E4,
    &lbl_8000A494, &lbl_8000A644, &lbl_8000CB64, &lbl_8000CB64, &lbl_8000CB64, &lbl_8000CB64, &lbl_8000A7F4,
    &lbl_8000A9A4, &lbl_8000AB54, &lbl_8000AD04, &lbl_8000CB64, &lbl_8000CB64, &lbl_8000AEB4, &lbl_8000B064,
    &lbl_8000B214, &lbl_8000B3C4, &lbl_8000B574, &lbl_8000B724, &lbl_8000B8D4, &lbl_8000BA84, &lbl_8000BC34,
    &lbl_8000BDE4, &lbl_8000BF94, &lbl_8000C144, &lbl_8000CB64, &lbl_8000CB64, &lbl_8000C2F4, &lbl_8000CB64,
    &lbl_8000CB64, &lbl_8000C4A4, &lbl_8000C654, &lbl_8000C804, &lbl_8000C9B4,
};

char D_800E9FFC[] = "TPL/msg_ld05_2.tpl";
char D_800EA010[] = "TPL/msg_ld06_4.tpl";
char D_800EA024[] = "TPL/msg_ld07.tpl";
char D_800EA038[] = "TPL/msg_gf01.tpl";
char D_800EA04C[] = "TPL/msg_in01.tpl";
char D_800EA060[] = "TPL/msg_sv06_4.tpl";
char D_800EA074[] = "TPL/msg_sv06_5.tpl";
char D_800EA088[] = "TPL/msg_sv08.tpl";

extern void *lbl_8000CBC8, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CC30, *lbl_8000CC98, *lbl_8000CD00,
    *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CD68, *lbl_8000CF08,
    *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08,
    *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CF08, *lbl_8000CDD0, *lbl_8000CE38,
    *lbl_8000CF08, *lbl_8000CEA0;

void* jtbl_800EA09C[] = {
    &lbl_8000CBC8, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CC30, &lbl_8000CC98,
    &lbl_8000CD00, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08,
    &lbl_8000CD68, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08,
    &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CF08,
    &lbl_8000CF08, &lbl_8000CF08, &lbl_8000CDD0, &lbl_8000CE38, &lbl_8000CF08, &lbl_8000CEA0,
};

char D_800EA114[] = "TPL/msg_in02.tpl";
char D_800EA128[] = "TPL/msg_sv09.tpl";
char D_800EA13C[] = "TPL/msg_gf02.tpl";

extern void *lbl_8000D3B8, *lbl_8000D3F4, *lbl_8000D434, *lbl_8000D4B0, *lbl_8000D474, *lbl_8000D4EC, *lbl_8000D528;

void* jtbl_800EA150[] = {
    &lbl_8000D3B8, &lbl_8000D3F4, &lbl_8000D434, &lbl_8000D4B0, &lbl_8000D474, &lbl_8000D4EC, &lbl_8000D528,
};

char D_800EA16C[] = "ShowError: Unknown FileInfoStatus: %d";

extern void *lbl_8000EEA8, *lbl_8000EEEC, *lbl_8000EEEC, *lbl_8000EEEC, *lbl_8000EEEC, *lbl_8000EEB0, *lbl_8000EEB8,
    *lbl_8000EEC0, *lbl_8000EEEC, *lbl_8000EEEC, *lbl_8000EEEC, *lbl_8000EEEC, *lbl_8000EEC8;

void* jtbl_800EA194[] = {
    &lbl_8000EEA8, &lbl_8000EEEC, &lbl_8000EEEC, &lbl_8000EEEC, &lbl_8000EEEC, &lbl_8000EEB0, &lbl_8000EEB8,
    &lbl_8000EEC0, &lbl_8000EEEC, &lbl_8000EEEC, &lbl_8000EEEC, &lbl_8000EEEC, &lbl_8000EEC8,
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

static Code* gpCode;

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

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorGXInit.s")
#else
s32 simulatorGXInit(void) {
    s32 i;
    GXColor GX_DEFAULT_BG = {0};
    GXColor BLACK = {0};
    GXColor WHITE = {0};
    f32 identity_mtx[3][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, -1.0},
    };

    // possible bug? GX_TG_MTX3x4 vs GX_TG_MTX2x4 (see identity_mtx)
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, 0x3C, GX_FALSE, 0x7D);

    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetPointSize(6, GX_TO_ZERO);

    GXEnableTexOffsets(GX_TEXCOORD0, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD1, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD2, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD3, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD4, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD5, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD6, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD7, GX_DISABLE, GX_DISABLE);

    GXLoadPosMtxImm(identity_mtx, 0);
    GXLoadNrmMtxImm(identity_mtx, 0);
    GXSetCurrentMtx(0);
    GXLoadTexMtxImm(identity_mtx, 0x3C, 0);

    GXSetCoPlanar(GX_DISABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetScissorBoxOffset(0, 0);

    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, BLACK);
    GXSetChanMatColor(GX_COLOR0A0, WHITE);
    GXSetChanCtrl(GX_COLOR1A1, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, BLACK);
    GXSetChanMatColor(GX_COLOR1A1, WHITE);
    GXInvalidateTexAll();

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD4, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD5, GX_TEXMAP5, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD6, GX_TEXMAP6, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD7, GX_TEXMAP7, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);

    for (i = 0; i < 0x10; i++) {
        GXSetTevKColorSel(i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel(i, GX_TEV_KASEL_1);
        GXSetTevSwapMode(i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevDirect(i);
    }

    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.10000000149011612f, 1.0f, BLACK);
    GXSetFogRangeAdj(GX_DISABLE, 0, NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_ENABLE);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetZCompLoc(GX_ENABLE);
    GXSetDither(GX_ENABLE);
    GXSetDstAlpha(GX_DISABLE, 0);
    GXSetPixelFmt(GX_DISABLE, GX_ZC_LINEAR);
    GXSetFieldMask(GX_ENABLE, GX_ENABLE);

    GXSetCopyClear(GX_DEFAULT_BG, 0xFFFFFF);
    GXSetCopyClamp(3); // missing enum?
    GXSetDispCopyGamma(GX_GM_1_0);
    GXSetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
    GXClearBoundingBox();
    GXPokeColorUpdate(GX_ENABLE);
    GXPokeAlphaUpdate(GX_ENABLE);
    GXPokeDither(GX_DISABLE);
    GXPokeBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ONE, GX_LO_SET);
    GXPokeAlphaMode(GX_ALWAYS, 0);
    GXPokeAlphaRead(GX_READ_FF);
    GXPokeDstAlpha(GX_DISABLE, 0);
    GXPokeZMode(GX_ENABLE, GX_ALWAYS, GX_ENABLE);
    GXSetGPMetric(GX_PERF0_NONE, GX_PERF0_TRIANGLES_7TEX);
    GXClearGPMetric();

    return 1;
}
#endif

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorUnpackTexPalette.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDVDShowError.s")

s32 simulatorDVDOpen(char* szNameFile, DVDFileInfo* pFileInfo) {
    s32 nStatus;

    while ((nStatus = DVDGetDriveStatus()) != 0) {
        if (!simulatorDVDShowError(nStatus, NULL, 0, 0)) {
            return 0;
        }
    }

    return DVDOpen(szNameFile, pFileInfo);
}

s32 simulatorDVDRead(DVDFileInfo* pFileInfo, void* anData, s32 nSizeRead, s32 nOffset, DVDCallback callback) {
    s32 nStatus;
    s32 bRetry;

    if (callback == NULL) {
        do {
            bRetry = 0;
            DVDReadAsyncPrio(pFileInfo, anData, nSizeRead, nOffset, NULL, 2);

            while ((nStatus = DVDGetCommandBlockStatus(&pFileInfo->cb)) != 0) {
                if (!simulatorDVDShowError(nStatus, anData, nSizeRead, nOffset)) {
                    return 0;
                }

                if ((nStatus == 11) || (nStatus == -1)) {
                    DVDCancel(&pFileInfo->cb);
                    bRetry = 1;
                    break;
                }
            }
        } while (bRetry);
    } else {
        DVDReadAsyncPrio(pFileInfo, anData, nSizeRead, nOffset, callback, 2);
        return 1;
    }

    return 1;
}

s32 simulatorPlayMovie(void) {
    simulatorResetAndPlayMovie();
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawImage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawYesNoImage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawOKImage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawErrorMessage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorPrepareMessage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawYesNoMessageLoop.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawYesNoMessage.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawErrorMessageWait.s")

inline void simulatorResetInit() {
    mcardWriteGameDataReset(&mCard);
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();
    PADRecalibrate(0xF0000000);
    GXAbortFrame();
    LCDisable();
    VIWaitForRetrace();
}

void simulatorReset(s32 IPL, s32 forceMenu) {
    simulatorResetInit();

    if (IPL == 1) {
        if (forceMenu == 1) {
            OSResetSystem(1, 0, 1);
        } else {
            OSResetSystem(1, 0, 0);
        }
        return;
    }

    OSResetSystem(0, 0, 0);
    NO_INLINE();
}

inline void simulatorUnknownInline() {
    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
    GXDrawDone();
    VISetNextFrameBuffer(DemoCurrentBuffer);
    VIFlush();
    VIWaitForRetrace();

    if (DemoCurrentBuffer == DemoFrameBuffer1) {
        DemoCurrentBuffer = DemoFrameBuffer2;
    } else {
        DemoCurrentBuffer = DemoFrameBuffer1;
    }
}

void simulatorResetAndPlayMovie(void) {
    int pad1;
    GXColor color;
    GXRenderModeObj* simrmode;
    int pad2;

    simrmode = rmode;
    simulatorResetInit();
    xlCoreReset();
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 1;
    DEMOInit(NULL);
    rmode = simrmode;
    VISetBlack(1);
    AIInit(NULL);
    GXSetCopyClear(color, 0);
    MovieInit();

    while (TRUE) {
        OSGetTick();

        if (gMovieErrorToggle == 1) {
            continue;
        }

        DEMOBeforeRender();
        MovieDraw();
        simulatorUnknownInline();
        VISetBlack(0);
        GXSetCopyClear(color, 0);
        movieTestReset(0, 0);
    }
}

s32 simulatorSetControllerMap(u32* mapData, s32 channel) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gContMap[channel]); i++) {
        gContMap[channel][i] = mapData[i];
    }

    return 1;
}

s32 simulatorCopyControllerMap(u32* mapDataOutput, u32* mapDataInput) {
    int i;

    for (i = 0; i < 20; i++) {
        mapDataOutput[i] = mapDataInput[i];
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorReadController.s")

s32 simulatorShowLoad(s32 /* unknown */, char* szNameFile, f32 rProgress) { return 1; }

s32 simulatorDetectController(s32 channel) {
    PADStatus status[4];

    PADRead(status);

    if (status[channel].err == -1) {
        return 0;
    }

    return 1;
}

s32 simulatorReadPak(s32 channel, u16 address, u8* data) {
    ControllerType type;

    pifGetEControllerType(SYSTEM_PIF(gpSystem), channel, &type);

    if (type == CT_CONTROLLER_W_RPAK) {
        pifReadRumble(SYSTEM_PIF(gpSystem), channel, address, data);
    }

    return 1;
}

s32 simulatorWritePak(s32 channel, u16 address, u8* data) {
    ControllerType type;

    pifGetEControllerType(SYSTEM_PIF(gpSystem), channel, &type);

    if (type == CT_CONTROLLER_W_RPAK) {
        pifWriteRumble(SYSTEM_PIF(gpSystem), channel, address, data);
    }

    return 1;
}

s32 simulatorReadEEPROM(u8 address, u8* data) {
    s32 size;

    if (!pifGetEEPROMSize(SYSTEM_PIF(gpSystem), &size, gpSystem)) {
        return 0;
    }

    mcardRead(&mCard, (address * 8) & 0x7F8, 8, (char*)data);
    return 1;
}

s32 simulatorWriteEEPROM(u8 address, u8* data) {
    s32 size;

    if (!pifGetEEPROMSize(SYSTEM_PIF(gpSystem), &size, gpSystem)) {
        return 0;
    }

    mcardWrite(&mCard, (address * 8) & 0x7F8, 8, (char*)data);
    return 1;
}

s32 simulatorReadSRAM(u32 address, u8* data, s32 size) {
    mcardRead(&mCard, address, size, (char*)data);
    return 1;
}

s32 simulatorWriteSRAM(u32 address, u8* data, s32 size) {
    mcardWrite(&mCard, address, size, (char*)data);
    return 1;
}

s32 simulatorReadFLASH(u32 address, u8* data, s32 size) {
    mcardRead(&mCard, address, size, (char*)data);
    return 1;
}

s32 simulatorWriteFLASH(u32 address, u8* data, s32 size) {
    mcardWrite(&mCard, address, size, (char*)data);
    return 1;
}

s32 simulatorRumbleStart(s32 channel) {
    PADControlMotor(channel, 1);
    return 1;
}

s32 simulatorRumbleStop(s32 channel) {
    PADControlMotor(channel, 0);
    return 1;
}

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorTestReset.s")
#else
s32 simulatorTestReset(s32 IPL, s32 forceMenu, s32 allowReset, s32 usePreviousSettings) {
    u32 bFlag;
    u32 nTick;
    s32 prevIPLSetting;
    s32 prevForceMenuSetting;
    s32 prevAllowResetSetting;
    s32 pad;

    nTick = OSGetTick();
    prevAllowResetSetting = gPreviousAllowResetSetting;
    prevIPLSetting = gPreviousIPLSetting;
    prevForceMenuSetting = gPreviousForceMenuSetting;

    if (usePreviousSettings == 1) {
        IPL = gPreviousIPLSetting;
        forceMenu = gPreviousForceMenuSetting;
        allowReset = gPreviousAllowResetSetting;
    } else {
        gPreviousIPLSetting = IPL;
        gPreviousForceMenuSetting = forceMenu;
        gPreviousAllowResetSetting = allowReset;
    }

    DEMOPadRead();
    bFlag = OSGetResetButtonState();

    if ((gResetBeginFlag == 1) && ((DemoPad[0].pst.button & 0x1600) == 0x1600)) {
        if ((gbReset == 0) || bFlag) {
            gbReset = bFlag;
            return 1;
        }

        if (allowReset == 1) {
            if (prevAllowResetSetting == 1) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    } else {
        gResetBeginFlag = 0;
    }

    if ((DemoPad[0].pst.button & 0x1600) != 0x1600) {
        gnTickReset = nTick;
        if ((gbReset == 0) || (bFlag != 0)) {
            gbReset = bFlag;
            return 1;
        }

        if (allowReset == 1) {
            if (prevAllowResetSetting == 1) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    } else {
        if (((nTick - gnTickReset) >= OSSecondsToTicks(0.5f)) && (allowReset == 1)) {
            if (prevAllowResetSetting == 1) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    }

    return 1;
}
#endif

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawMCardText.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorMCardPollDrawBar.s")

#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorMCardPollDrawFormatBar.s")

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorDrawCursor.s")
#else
static s32 simulatorDrawCursor(s32 nX, s32 nY) {
    GXColor color;
    s32 nTick;
    u8 var_r5;
    s32 pad;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXCOORD_NULL, GX_TEXCOORD_NULL);

    nTick = OSGetTick() >> 14;
    if (nTick & 0x100) {
        var_r5 = (u8)nTick ^ 0xFF;
    } else {
        var_r5 = (u8)nTick;
    }

    color.r = color.g = color.b = 0;

    switch ((nTick >> 9) % 7) {
        case 0:
            color.r = var_r5;
            break;
        case 1:
            color.g = var_r5;
            break;
        case 2:
            color.b = var_r5;
            break;
        case 3:
            color.g = var_r5;
            color.r = var_r5;
            break;
        case 4:
            color.b = var_r5;
            color.r = var_r5;
            break;
        case 5:
            color.b = var_r5;
            color.g = var_r5;
            break;
        case 6:
            color.b = var_r5;
            color.g = var_r5;
            color.r = var_r5;
            break;
    }

    GXSetTevColor(GX_TEVREG0, color);
    GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);

    GXWGFifo.s16 = nX;
    GXWGFifo.s16 = nY;
    GXWGFifo.s16 = nX + 8;
    GXWGFifo.s16 = nY + 4;
    GXWGFifo.s16 = nX;
    GXWGFifo.s16 = nY + 8;

    return 1;
}
#endif

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/simGCN/simulatorParseArguments.s")
#else
static s32 simulatorParseArguments(void) {
    s32 iArgument;
    char* szText;
    char* szValue;
    s32 pad1;
    s32 pad2;

    gaszArgument[SAT_NAME] = NULL;
    gaszArgument[SAT_PROGRESSIVE] = NULL;
    gaszArgument[SAT_VIBRATION] = NULL;
    gaszArgument[SAT_CONTROLLER] = NULL;
    gaszArgument[SAT_XTRA] = NULL;
    gaszArgument[SAT_MEMORYCARD] = NULL;
    gaszArgument[SAT_MOVIE] = NULL;
    gaszArgument[SAT_RESET] = NULL;

    iArgument = 0;
    while (iArgument < xlCoreGetArgumentCount()) {
        xlCoreGetArgument(iArgument, &szText);
        iArgument += 1;
        if (szText[0] == '-' || szText[0] == '/' || szText[0] == '\\') {
            if (szText[2] == '\0') {
                xlCoreGetArgument(iArgument, &szValue);
                iArgument += 1;
            } else {
                szValue = &szText[2];
            }

            switch (szText[1]) {
                case 'V':
                case 'v':
                    gaszArgument[SAT_VIBRATION] = szValue;
                    break;
                case 'P':
                case 'p':
                    gaszArgument[SAT_PROGRESSIVE] = szValue;
                    break;
                case 'G':
                case 'g':
                    gaszArgument[SAT_CONTROLLER] = szValue;
                    break;
                case 'C':
                case 'c':
                    gaszArgument[SAT_MEMORYCARD] = szValue;
                    break;
                case 'M':
                case 'm':
                    gaszArgument[SAT_MOVIE] = szValue;
                    break;
                case 'R':
                case 'r':
                    gaszArgument[SAT_RESET] = szValue;
                    break;
                case 'X':
                case 'x':
                    gaszArgument[SAT_XTRA] = szValue;
                    break;
            }
        } else {
            gaszArgument[SAT_NAME] = szText;
        }
    }
    return 1;
}
#endif

s32 simulatorGetArgument(SimArgumentType eType, char** pszArgument) {
    if (eType != SAT_NONE && pszArgument != NULL && gaszArgument[eType] != NULL) {
        *pszArgument = gaszArgument[eType];
        return 1;
    }

    return 0;
}

inline s32 simulatorRun(SystemMode* peMode) {
    int nResult;

    while (systemGetMode(gpSystem, peMode) && *peMode == SM_RUNNING) {
        nResult = systemExecute(gpSystem, 100000);
        if (!nResult) {
            return nResult;
        }
    }

    return 1;
}

s32 xlMain(void) {
    GXColor color;
    SystemMode eMode;
    s32 nSize0;
    s32 nSize1;
    s32 iName;
    char* szNameROM;
    char acNameROM[32];
    // s32 rumbleYes;

    simulatorParseArguments();
    gDVDResetToggle = 0;

    if (!xlHeapGetFree(&nSize0)) {
        return 0;
    }
    if (nSize0 > 0x01800000) {
        OSReport(D_800E9B34);
        OSReport(D_800E9B80);
        while (1) {}
    }

#ifdef __MWERKS__
    asm {
        li      r3, 0x706
        oris    r3, r3, 0x706
        mtspr   GQR6, r3
        li      r3, 0x507
        oris    r3, r3, 0x507
        mtspr   GQR7, r3
    }
#endif

    color.r = color.g = color.b = 0;
    color.a = 0xFF;

    gbDisplayedError = 0;
    gButtonDownToggle = 0;
    gResetBeginFlag = 1;

    GXSetCopyClear(color, 0xFFFFFF);
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();

    xlCoreBeforeRender();
    simulatorUnknownInline();

    xlCoreBeforeRender();
    simulatorUnknownInline();

    VIWaitForRetrace();
    VISetBlack(0);
    VIFlush();

    simulatorUnpackTexPalette((__anon_0xDB69*)&gcoverOpen);
    simulatorUnpackTexPalette((__anon_0xDB69*)&gnoDisk);
    simulatorUnpackTexPalette((__anon_0xDB69*)&gretryErr);
    simulatorUnpackTexPalette((__anon_0xDB69*)&gfatalErr);
    simulatorUnpackTexPalette((__anon_0xDB69*)&gwrongDisk);
    simulatorUnpackTexPalette((__anon_0xDB69*)&greadingDisk);
    simulatorUnpackTexPalette((__anon_0xDB69*)&gbar);
    simulatorUnpackTexPalette((__anon_0xDB69*)&gyes);
    simulatorUnpackTexPalette((__anon_0xDB69*)&gno);
    simulatorUnpackTexPalette((__anon_0xDB69*)&gmesgOK);

    gbReset = 0;
    gnTickReset = OSGetTick();

    if (!xlHeapGetFree(&nSize0)) {
        return 0;
    }

    mCard.bufferCreated = 0;
    mCard.isBroken = 0;
    mcardInit(&mCard);

    if (simulatorGetArgument(SAT_NAME, &szNameROM)) {
        strcpy(acNameROM, szNameROM);
    } else {
        strcpy(acNameROM, D_800E9BD0);
    }

    iName = strlen(acNameROM) - 1;
    while (iName >= 0 && acNameROM[iName] != '.') {
        iName--;
    }

    if (iName < 0) {
        iName = strlen(acNameROM);
        acNameROM[iName + 0] = '.';
        acNameROM[iName + 1] = 'N';
        acNameROM[iName + 2] = '6';
        acNameROM[iName + 3] = '4';
        acNameROM[iName + 4] = '\0';
    }

    gpSystem = NULL;

    if (!xlObjectMake(&gpCode, NULL, &gClassCode)) {
        return 0;
    }
    if (!xlObjectMake(&gpFrame, NULL, &gClassFrame)) {
        return 0;
    }
    if (!xlObjectMake(&gpSound, NULL, &gClassSound)) {
        return 0;
    }
    if (!xlObjectMake(&gpSystem, NULL, &gClassSystem)) {
        return 0;
    }

    if (!xlFileSetOpen(&simulatorDVDOpen)) {
        return 0;
    }
    if (!xlFileSetRead(&simulatorDVDRead)) {
        return 0;
    }

    soundLoadBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_ACCEPT, D_80134D9C);
    soundLoadBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_DECLINE, D_80134DA4);
    soundLoadBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_SELECT, D_800E9BDC);

    if (!romSetImage(SYSTEM_ROM(gpSystem), acNameROM)) {
        return 0;
    }
    if (!systemReset(gpSystem)) {
        return 0;
    }
    if (!frameShow(gpFrame)) {
        return 0;
    }
    if (!xlHeapGetFree(&nSize1)) {
        return 0;
    }
    if (!systemSetMode(gpSystem, SM_RUNNING)) {
        return 0;
    }

    simulatorRun(&eMode);

    if (!xlObjectFree(&gpSystem)) {
        return 0;
    }
    if (!xlObjectFree(&gpSound)) {
        return 0;
    }
    if (!xlObjectFree(&gpFrame)) {
        return 0;
    }
    if (!xlObjectFree(&gpCode)) {
        return 0;
    }

    return 1;
}
