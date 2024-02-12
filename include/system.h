#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "types.h"


// TODO: should be __anon_0x37240
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
    u8 pad[0x28];
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

char D_800EB300[] = "SYSTEM (N64)";

_XL_OBJECTTYPE gClassSystem = {
    D_800EB300,
    sizeof(System),
    NULL,
    (EventFunc)systemEvent,
};

u32 contMap[] = {
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

void* jtbl_800EB460[] = {
    (void*)0x8002CC70,
    (void*)0x8002CCBC,
    (void*)0x8002CD04,
    (void*)0x8002CD9C,
    (void*)0x8002CE0C,
    (void*)0x8002CE54,
    (void*)0x8002CEC4,
    (void*)0x8002CF0C,
    (void*)0x8002CF7C,
    (void*)0x8002CF88,
    (void*)0x8002CF94,
    (void*)0x8002CFDC,
    (void*)0x8002D024,
    (void*)0x8002D070,
    (void*)0x8002D090,
    (void*)0x8002D0DC,
};

char D_800EB4A0[] = "BREAK (CPU)";
char D_800EB4AC[] = "BREAK (SP)";
char D_800EB4B8[] = "THREADSTATUS";

void* jtbl_800EB4C8[] = {
    (void*)0x8002DBDC,
    (void*)0x8002DBF4,
    (void*)0x8002DC0C,
    (void*)0x8002DC24,
    (void*)0x8002DC3C,
    (void*)0x8002DC54,
    (void*)0x8002DC70,
    (void*)0x8002DC90,
    (void*)0x8002DCB0,
    (void*)0x8002DCD0,
    (void*)0x8002DCEC,
    (void*)0x8002DD0C,
    (void*)0x8002DD20,
    (void*)0x8002DD38,
    (void*)0x8002DD44,
    (void*)0x8002DD50,
};

char D_800EB508[] = "TPL/z_icon.tpl";
char D_800EB518[] = "TPL/z_bnr.tpl";

char D_800EB528[] = "Mario 64";
char D_800EB534[] = "\x83\x5b\x83\x8b\x83\x5f\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87\x83\x93";  // "ゼルダコレクション"
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

#endif
