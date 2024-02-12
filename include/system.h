#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "types.h"


// probably wrong but size matches (0x88)
typedef struct System {
    /* 0x0000 */ s32 unk_0x00;
    /* 0x0004 */ char unk_0x04[0x8];
    /* 0x000C */ int rom_id;
    /* 0x0010 */ void* cpu;
    /* 0x0014 */ char unk_0x14[4];
    /* 0x0018 */ void* ram;
    /* 0x001C */ void* rom;
    /* 0x0020 */ void *rsp;
    /* 0x0024 */ char unk_0x24[0x10];
    /* 0x0034 */ void *video;
    /* 0x0038 */ char unk_0x38[0x1C];
    /* 0x0054 */ void* help_menu;
    /* 0x0058 */ void *unk_0x0058;
    /* 0x005C */ u32 *frame;
} System;

typedef struct SystemRomConfig {
    /* 0x0000 */ char rom[36];
    /* 0x0024 */ int controllerConfiguration[4][20];
    /* 0x0164 */ int rumbleConfiguration;
    /* 0x0168 */ int storageDevice;
    /* 0x016C */ int normalControllerConfig;
    /* 0x0170 */ int currentControllerConfig;
} SystemRomConfig; // size = 0x174


int systemEvent(System* pSystem, int nEvent, void *pArgument);

char D_800EB300[13] = "SYSTEM (N64)";

_XL_OBJECTTYPE gClassSystem = {
    D_800EB300,
    sizeof(System),
    NULL,
    (EventFunc)systemEvent,
};

u32 contMap[80] = {
    0x80000000, 0x40000000, 0x00000000, 0x00000000, 0x00200000, 0x00100000, 0x20000000, 0x10000000,
    0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000,
    0x00080000, 0x00040000, 0x00020000, 0x00010000, 0x80000000, 0x40000000, 0x00000000, 0x00000000,
    0x20000000, 0x00100000, 0x20000000, 0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000,
    0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,
    0x80000000, 0x40000000, 0x00010000, 0x00020000, 0x20000000, 0x00100000, 0x00040000, 0x10000000,
    0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00200000, 0x00200000, 0x00200000, 0x00200000,
    0x00080000, 0x00040000, 0x00020000, 0x00010000, 0x80000000, 0x40000000, 0x00200000, 0x00000000,
    0x20000000, 0x00100000, 0x20000000, 0x10000000, 0x08000000, 0x04000000, 0x02000000, 0x01000000,
    0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00080000, 0x00040000, 0x00020000, 0x00010000,
};

// jtbl_800EB460 ?

char D_800EB4A0[12] = "BREAK (CPU)";
char D_800EB4AC[11] = "BREAK (SP)";
char D_800EB4B8[13] = "THREADSTATUS";

// jtbl_800EB4C8 ?

char D_800EB508[15] = "TPL/z_icon.tpl";
char D_800EB518[14] = "TPL/z_bnr.tpl";
char D_800EB528[9] = "Mario 64";

/* "ゼルダコレクション" */
char D_800EB534[19] = "\x83\x5b\x83\x8b\x83\x5f\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93";

char D_800EB548[36] = "The Legend of Zelda Debug";
char D_800EB564[16] = "Legend of Zelda";
char D_800EB574[11] = "Pilotwings";
char D_800EB580[14] = "Animal Forest";
char D_800EB590[14] = "Cruise 'n USA";
char D_800EB5A0[10] = "Dr. Mario";
char D_800EB5AC[11] = "Mario Kart";
char D_800EB5B8[14] = "Mario Party 1";
char D_800EB5C8[14] = "Mario Party 2";
char D_800EB5D8[14] = "Mario Party 3";
char D_800EB5E8[11] = "PaperMario";
char D_800EB5F4[12] = "Paper Mario";
char D_800EB600[11] = "PAPERMARIO";
char D_800EB60C[15] = "PokemonStadium";
char D_800EB61C[16] = "Pokemon Stadium";
char D_800EB62C[15] = "POKEMONSTADIUM";
char D_800EB63C[13] = "Panel de Pon";
char D_800EB64C[11] = "YoshiStory";

SystemRomConfig gSystemRomConfigurationList;

u64 nTickMultiplier = 2;
f32 fTickScale = 1.0;
static u8 D_80134E68 = 0;

static char D_80134E6C[3] = "SW0";
static char D_80134E70[3] = "SW1";
static char D_80134E74[4] = "CART";
static char D_80134E7C[8] = "COUNTER";
static char D_80134E84[3] = "RDB";
static char D_80134E88[2] = "SP";
static char D_80134E8C[2] = "SI";
static char D_80134E90[2] = "AI";
static char D_80134E94[2] = "VI";
static char D_80134E98[2] = "PI";
static char D_80134E9C[2] = "DP";
static char D_80134EA0[6] = "FAULT";
static char D_80134EA8[7] = "PRENMI";
static char D_80134EB0[4] = "NSME";
static char D_80134EB8[4] = "NSMJ";
static char D_80134EC0[5] = "MARIO";
static char D_80134EC8[4] = "CZLE";
static char D_80134ED0[4] = "CZLJ";
static char D_80134ED8[7] = "ZELDA1";
static char D_80134EE0[7] = "ZELDAX";
static char D_80134EE8[6] = "ZELDA";
static char D_80134EF0[7] = "ZELDAD";
static char D_80134EF8[4] = "NZSJ";
static char D_80134F00[4] = "NZSE";
static char D_80134F08[7] = "ZELDA3";
static char D_80134F10[4] = "NPWE";
static char D_80134F18[6] = "PILOT";
static char D_80134F20[4] = "NAFJ";
static char D_80134F28[2] = "AF";
static char D_80134F2C[4] = "NBCE";
static char D_80134F34[4] = "NBKE";
static char D_80134F3C[4] = "NGEE";
static char D_80134F44[4] = "NFUE";
static char D_80134F4C[4] = "NBYE";
static char D_80134F54[4] = "NCUE";
static char D_80134F5C[7] = "CRUISE";
static char D_80134F64[4] = "NDNE";
static char D_80134F6C[4] = "NDOE";
static char D_80134F74[4] = "NN6E";
static char D_80134F7C[4] = "NN6J";
static char D_80134F84[8] = "DRMARIO";
static char D_80134F8C[4] = "CFZE";
static char D_80134F94[4] = "NLRE";
static char D_80134F9C[4] = "NMFE";
static char D_80134FA4[4] = "NKTE";
static char D_80134FAC[4] = "KART";
static char D_80134FB4[4] = "NK4E";
static char D_80134FBC[4] = "CLBE";
static char D_80134FC4[3] = "MP1";
static char D_80134FC8[4] = "NMWE";
static char D_80134FD0[3] = "MP2";
static char D_80134FD4[4] = "NMVE";
static char D_80134FDC[3] = "MP3";
static char D_80134FE0[4] = "NM3E";
static char D_80134FE8[4] = "NRIE";
static char D_80134FF0[4] = "NMQE";
static char D_80134FF8[4] = "NPOE";
static char D_80135000[4] = "NQKE";
static char D_80135008[4] = "NRSE";
static char D_80135010[4] = "NRZE";
static char D_80135018[4] = "NFXE";
static char D_80135020[4] = "NFXJ";
static char D_80135028[8] = "STARFOX";
static char D_80135030[8] = "Starfox";
static char D_80135038[4] = "NGUJ";
static char D_80135040[4] = "NALE";
static char D_80135048[4] = "NTEA";
static char D_80135050[4] = "1080";
static char D_80135058[4] = "NTPE";
static char D_80135060[4] = "NEPE";
static char D_80135068[4] = "NM8E";
static char D_80135070[4] = "NYLJ";
static char D_80135078[6] = "PANEL";
static char D_80135080[4] = "NTUE";
static char D_80135088[4] = "NWRE";
static char D_80135090[4] = "NYSE";
static char D_80135098[4] = "NBNJ";
static char D_801350A0[3] = "XXX";

u32 gnFlagZelda;
f32 D_80135F90 = 0.01666666753590107;
f32 D_80135F94 = 1.100000023841858;
f64 D_80135F98 = 4503599627370496.0;

#endif
