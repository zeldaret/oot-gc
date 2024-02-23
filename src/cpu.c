#include "cpu.h"
#include "dolphin.h"
#include "xlObject.h"
#include "macros.h"
#include "cpu_jumptable.h"

_XL_OBJECTTYPE gClassCPU = {
    "CPU",
    sizeof(Cpu),
    NULL,
    (EventFunc)cpuEvent,
};

char* gaszNameGPR[] = {
    "ZERO", "AT", "V0", "V1", "A0", "A1", "A2", "A3", "T0", "T1", "T2", "T3", "T4", "T5", "T6", "T7",
    "S0",   "S1", "S2", "S3", "S4", "S5", "S6", "S7", "T8", "T9", "K0", "K1", "GP", "SP", "S8", "RA",
};

char* gaszNameFPR[] = {
    "F0",  "F1",  "F2",  "F3",  "F4",  "F5",  "F6",  "F7",  "F8",  "F9",  "F10", "F11", "F12", "F13", "F14", "F15",
    "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", "F25", "F26", "F27", "F28", "F29", "F30", "F21", // bug, should be "F31"
};

char* gaszNameCP0[] = {
    "INDEX",         "RANDOM",        "ENTRY-LO0",     "ENTRY-LO1",     "CONTEXT",       "PAGE-MASK", "WIRED",
    "(RESERVED-7)",  "BAD-VADDR",     "COUNT",         "ENTRY-HI",      "COMPARE",       "STATUS",    "CAUSE",
    "EPC",           "uPC-ID",        "CONFIG",        "LLADDR",        "WATCH-LO",      "WATCH-HI",  "X-CONTEXT",
    "(RESERVED-21)", "(RESERVED-22)", "(RESERVED-23)", "(RESERVED-24)", "(RESERVED-25)", "ECC",       "CACHE-ERROR",
    "TAG-LO",        "TAG-HI",        "ERROR-EPC",     "(RESERVED-31)",
};

char* gaszNameCP1[] = {
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

s64 ganMaskGetCP0[] = {
    0x000000008000003F, 0x000000000000003F, 0x000000003FFFFFFF, 0x000000003FFFFFFF,
    0xFFFFFFFFFFFFFFF0, 0x0000000001FFE000, 0x000000000000001F, 0x0000000000000000,
    0xFFFFFFFFFFFFFFFF, 0x00000000FFFFFFFF, 0x00000000FFFFE0FF, 0x00000000FFFFFFFF,
    0x00000000FFFFFFFF, 0x00000000F000FF7C, 0xFFFFFFFFFFFFFFFF, 0x000000000000FFFF,
    0x00000000FFFFEFFF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFB, 0x000000000000000F,
    0x00000000FFFFFFF0, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x0000000000000000, 0x00000000000000FF, 0x00000000FFBFFFFF,
    0x00000000FFFFFFFF, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
};

s64 ganMaskSetCP0[] = {
    0x000000000000003F, 0x000000000000003F, 0x000000003FFFFFFF, 0x000000003FFFFFFF,
    0xFFFFFFFFFFFFFFF0, 0x0000000001FFE000, 0x000000000000001F, 0x0000000000000000,
    0xFFFFFFFFFFFFFFFF, 0x00000000FFFFFFFF, 0x00000000FFFFE0FF, 0x00000000FFFFFFFF,
    0x00000000FFFFFFFF, 0x0000000000000300, 0xFFFFFFFFFFFFFFFF, 0x000000000000FFFF,
    0x00000000FFFFEFFF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFB, 0x000000000000000F,
    0x00000000FFFFFFF0, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x0000000000000000, 0x00000000000000FF, 0x00000000FFBFFFFF,
    0x00000000FFFFFFFF, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
};

u8 Opcode[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
};

u8 SpecialOpcode[] = {
    1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
};

u8 RegimmOpcode[] = {
    1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

s32 ganOpcodeSaveFP1[] = {
    0x8F480018, 0x11000014, 0x00000000, 0x4448F800, 0x00000000,
};

s32 ganOpcodeSaveFP2_0[] = {
    0x8CBB0018, 0x1360000A, 0x00000000, 0x445BF800, 0x00000000,
};

s32 ganOpcodeSaveFP2_1[] = {
    0x13600009,
    0xACBF011C,
    0x445BF800,
};

s32 ganOpcodeLoadFP[] = {
    0x8F5B0018, 0x13600013, 0x00000000, 0x8F5B012C, 0x44DBF800,
};

s32 ganMapGPR[] = {
    0x0000000A, 0x0000000B, 0x0000000C, 0x0000000E, 0x0000000F, 0x00000010, 0x00000011, 0x00000012,
    0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018, 0x00000019, 0x0000001A,
    0x00000110, 0x00000111, 0x00000112, 0x00000113, 0x00000114, 0x00000115, 0x00000116, 0x00000117,
    0x0000001B, 0x0000001C, 0x0000001D, 0x0000001E, 0x0000011C, 0x0000001F, 0x0000011E, 0x0000011F,
};

void* jtbl_800EBEF0[] = {
    &lbl_80030EFC, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030EFC, &lbl_80030EFC,
    &lbl_80030F7C, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030F7C, &lbl_80030EFC,
    &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC,
    &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC,
    &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030F7C,
};

void* jtbl_800EBF54[] = {
    &lbl_80030F7C, &lbl_80030EA8, &lbl_80030F58, &lbl_80030F60, &lbl_80030F68, &lbl_80030F68,
    &lbl_80030F68, &lbl_80030F68, &lbl_80030F7C, &lbl_80030F70, &lbl_80030F7C, &lbl_80030F7C,
    &lbl_80030F7C, &lbl_80030F70, &lbl_80030F7C, &lbl_80030F70, &lbl_80030ED8, &lbl_80030F2C,
    &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F68, &lbl_80030F68, &lbl_80030F68, &lbl_80030F68,
    &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C,
    &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F78, &lbl_80030F78, &lbl_80030F78, &lbl_80030F78,
    &lbl_80030F78, &lbl_80030F78, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F78, &lbl_80030F78,
    &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C,
    &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F78,
    &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F7C,
    &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F78,
};

char D_800EC054[] = "start=%p, end=%p (%d) (size: %d)\n";
char D_800EC078[] = "tree range (%p - %p)\n";
char D_800EC090[] = "total nodes: %d (tree height: %d %d)\n";
char D_800EC0B8[] = "total memory: %d\n";

void* jtbl_800EC0CC[] = {
    &lbl_8003381C, &lbl_80033A68, &lbl_80033A68, &lbl_8003381C, &lbl_8003381C,
    &lbl_80033A68, &lbl_8003381C, &lbl_8003381C, &lbl_80033A68, &lbl_8003381C,
    &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C,
    &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C,
    &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_800337F0,
};

void* jtbl_800EC130[] = {
    &lbl_800334D8, &lbl_800335A0, &lbl_80033564, &lbl_80033A5C, &lbl_80033644, &lbl_80033768,
    &lbl_80033768, &lbl_80033768, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C,
    &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_800337D0, &lbl_800338AC,
    &lbl_80033A5C, &lbl_80033A5C, &lbl_80033644, &lbl_80033768, &lbl_80033768, &lbl_80033768,
    &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C,
    &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_8003394C,
    &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C,
    &lbl_80033A5C, &lbl_80033938,
};

char D_800EC1E0[] = "_cpuGCN.c";

void* jtbl_800EC1EC[] = {
    &lbl_8003789C, &lbl_80038010, &lbl_80038010, &lbl_80038010, &lbl_80037AF0,
    &lbl_80038010, &lbl_80037D08, &lbl_80038010, &lbl_800379D8, &lbl_80038010,
    &lbl_80038010, &lbl_80038010, &lbl_80037BF8, &lbl_80038010, &lbl_80037E90,
};

void* jtbl_800EC228[] = {
    &lbl_800383F4, &lbl_800386AC, &lbl_80038E70, &lbl_80038964, &lbl_80038560, &lbl_80038818,
    &lbl_80038E70, &lbl_80038E70, &lbl_80038AB0, &lbl_80038BF0, &lbl_80038E70, &lbl_80038D30,
};

void* jtbl_800EC258[] = {
    &lbl_8003C690, &lbl_8003C6CC, &lbl_8003C708, &lbl_8003C754, &lbl_8003C78C, &lbl_8003C85C,
    &lbl_8003C88C, &lbl_8003C8B0, &lbl_8003C8DC, &lbl_8003C900, &lbl_8003C924, &lbl_8003C954,
    &lbl_8003C984, &lbl_8003C9A0, &lbl_8003C9BC, &lbl_8003C9F0, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003CA24, &lbl_8003CA48, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003CA6C, &lbl_8003CA88, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003CAAC, &lbl_8003CABC, &lbl_8003CACC, &lbl_8003CB1C, &lbl_8003CB6C, &lbl_8003CBC8,
    &lbl_8003CC24, &lbl_8003CC80, &lbl_8003CCDC, &lbl_8003CCEC, &lbl_8003CD48, &lbl_8003CD98,
    &lbl_8003CDE8, &lbl_8003CE44, &lbl_8003CEA0, &lbl_8003CEFC,
};

void* jtbl_800EC358[] = {
    &lbl_8003BEA4, &lbl_8003BED0, &lbl_8003BEFC, &lbl_8003BF28, &lbl_8003BF54, &lbl_8003C030,
    &lbl_8003C078, &lbl_8003C094, &lbl_8003C0B4, &lbl_8003C0D8, &lbl_8003C0FC, &lbl_8003C140,
    &lbl_8003C184, &lbl_8003C1A0, &lbl_8003C1BC, &lbl_8003C204, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003C24C, &lbl_8003C284, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003C2BC, &lbl_8003C2D8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003C2FC, &lbl_8003C30C, &lbl_8003C31C, &lbl_8003C35C, &lbl_8003C39C, &lbl_8003C3DC,
    &lbl_8003C41C, &lbl_8003C45C, &lbl_8003C49C, &lbl_8003C4AC, &lbl_8003C4EC, &lbl_8003C52C,
    &lbl_8003C56C, &lbl_8003C5AC, &lbl_8003C5EC, &lbl_8003C62C,
};

void* jtbl_800EC458[] = {
    &lbl_8003B774, &lbl_8003B7A0, &lbl_8003B7CC, &lbl_8003B7F8, &lbl_8003B824, &lbl_8003B8C8,
    &lbl_8003B8E8, &lbl_8003B904, &lbl_8003B924, &lbl_8003B950, &lbl_8003B974, &lbl_8003B99C,
    &lbl_8003B9C4, &lbl_8003B9F4, &lbl_8003BA1C, &lbl_8003BA48, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003BA74, &lbl_8003BA94, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003BAB0, &lbl_8003BAD8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003BAFC, &lbl_8003BB0C, &lbl_8003BB1C, &lbl_8003BB5C, &lbl_8003BB9C, &lbl_8003BBDC,
    &lbl_8003BC1C, &lbl_8003BC60, &lbl_8003BCA4, &lbl_8003BCB4, &lbl_8003BCF8, &lbl_8003BD38,
    &lbl_8003BD78, &lbl_8003BDB8, &lbl_8003BDF8, &lbl_8003BE3C,
};

void* jtbl_800EC558[] = {
    &lbl_8003B040, &lbl_8003B06C, &lbl_8003B098, &lbl_8003B0C4, &lbl_8003B0F0, &lbl_8003B198,
    &lbl_8003B1BC, &lbl_8003B1D8, &lbl_8003B1F8, &lbl_8003B224, &lbl_8003B248, &lbl_8003B270,
    &lbl_8003B298, &lbl_8003B2C8, &lbl_8003B2F0, &lbl_8003B31C, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003B348, &lbl_8003B364, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003B380, &lbl_8003B3A8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003B3CC, &lbl_8003B3DC, &lbl_8003B3EC, &lbl_8003B42C, &lbl_8003B46C, &lbl_8003B4AC,
    &lbl_8003B4EC, &lbl_8003B530, &lbl_8003B574, &lbl_8003B584, &lbl_8003B5C8, &lbl_8003B608,
    &lbl_8003B648, &lbl_8003B688, &lbl_8003B6C8, &lbl_8003B70C,
};

void* jtbl_800EC658[] = {
    &lbl_8003AD84, &lbl_8003ADD4, &lbl_8003ADF8, &lbl_8003DEAC,
    &lbl_8003AE14, &lbl_8003AE98, &lbl_8003AEBC,
};

void* jtbl_800EC674[] = {
    &lbl_8003AC94, &lbl_8003ACD8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003AD0C,
    &lbl_8003AD2C, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
};

void* jtbl_800EC698[] = {
    &lbl_8003AC70, &lbl_8003A824, &lbl_8003A87C, &lbl_8003AC70, &lbl_8003AC70,
    &lbl_8003A894, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AA30, &lbl_8003AC70,
    &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70,
    &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70,
    &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003ABD8,
};

void* jtbl_800EC6FC[] = {
    &lbl_8003A1A8, &lbl_8003A1D8, &lbl_8003A208, &lbl_8003A254, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003A2A0, &lbl_8003A2D0,
    &lbl_8003A300, &lbl_8003A330, &lbl_8003A360, &lbl_8003DEAC, &lbl_8003A390,
    &lbl_8003DEAC, &lbl_8003A3C0, &lbl_8003A400, &lbl_8003A440, &lbl_8003A498,
};

void* jtbl_800EC74C[] = {
    &lbl_80039680, &lbl_8003DEAC, &lbl_800396A4, &lbl_800396C8, &lbl_800396EC, &lbl_8003DEAC,
    &lbl_8003971C, &lbl_8003974C, &lbl_8003977C, &lbl_80039790, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_800397C0, &lbl_800397D4, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_800397E8, &lbl_80039804,
    &lbl_80039820, &lbl_8003983C, &lbl_80039858, &lbl_8003DEAC, &lbl_80039894, &lbl_800398D0,
    &lbl_8003990C, &lbl_80039984, &lbl_800399F8, &lbl_80039A50, &lbl_80039AA8, &lbl_80039B24,
    &lbl_80039BA0, &lbl_80039C08, &lbl_80039C70, &lbl_80039C9C, &lbl_80039CC8, &lbl_80039CF4,
    &lbl_80039D20, &lbl_80039D4C, &lbl_80039D78, &lbl_80039DA4, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_80039DD0, &lbl_80039E0C, &lbl_80039E48, &lbl_80039E84, &lbl_80039EC0, &lbl_80039EFC,
    &lbl_80039F38, &lbl_80039F6C, &lbl_80039FA0, &lbl_80039FD4, &lbl_8003A008, &lbl_8003DEAC,
    &lbl_8003A03C, &lbl_8003DEAC, &lbl_8003A070, &lbl_8003DEAC, &lbl_8003A09C, &lbl_8003A0C8,
    &lbl_8003A0F4, &lbl_8003DEAC, &lbl_8003A124, &lbl_8003A154,
};

void* jtbl_800EC84C[] = {
    &lbl_8003965C, &lbl_8003A184, &lbl_8003A4F0, &lbl_8003A558, &lbl_8003A58C, &lbl_8003A61C,
    &lbl_8003A658, &lbl_8003A688, &lbl_8003A6B8, &lbl_8003A6E0, &lbl_8003A708, &lbl_8003A740,
    &lbl_8003A778, &lbl_8003A79C, &lbl_8003A7C0, &lbl_8003A7E4, &lbl_8003A800, &lbl_8003AD4C,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003CF58, &lbl_8003CFB0, &lbl_8003D008, &lbl_8003D054,
    &lbl_8003D0A0, &lbl_8003D0D8, &lbl_8003D138, &lbl_8003D210, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003D110, &lbl_8003D350, &lbl_8003D3B4, &lbl_8003D414, &lbl_8003D4A8,
    &lbl_8003D508, &lbl_8003D568, &lbl_8003D5F8, &lbl_8003D2E8, &lbl_8003D68C, &lbl_8003D6DC,
    &lbl_8003D72C, &lbl_8003D79C, &lbl_8003D7EC, &lbl_8003D86C, &lbl_8003D8EC, &lbl_8003D95C,
    &lbl_8003DA20, &lbl_8003DA80, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DB40, &lbl_8003DBA8,
    &lbl_8003DEAC, &lbl_8003DC10, &lbl_8003DC78, &lbl_8003DCE8, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DD6C, &lbl_8003DDF0, &lbl_8003DEAC, &lbl_8003DE50,
};

char D_800EC94C[] = "ERROR in cpuNextInstruction() with opcode %p at %p\n";
char D_800EC980[] = "CALLED: ceil_w single (%p)\n";
char D_800EC99C[] = "CALLED: floor_w single (%p)\n";
char D_800EC9BC[] = "ERROR: CVT_S_S\n";
char D_800EC9CC[] = "CALLED: ceil_w double (%p)\n";
char D_800EC9E8[] = "CALLED: floor_w double (%p)\n";
char D_800ECA08[] = "ERROR: CVT_S_D\n";
char D_800ECA18[] = "ERROR: ADD_W\n";
char D_800ECA28[] = "ERROR: SUB_W\n";
char D_800ECA38[] = "ERROR: MUL_W\n";
char D_800ECA48[] = "ERROR: DIV_W\n";
char D_800ECA58[] = "ERROR: SQRT_W\n";
char D_800ECA68[] = "ERROR: ABS_W\n";
char D_800ECA78[] = "ERROR: MOVE_W\n";
char D_800ECA88[] = "ERROR: NEG_W\n";
char D_800ECA98[] = "ERROR: ROUND_W_W\n";
char D_800ECAAC[] = "ERROR: TRUNC_W_W\n";
char D_800ECAC0[] = "ERROR: CEIL_W_W\n";
char D_800ECAD4[] = "ERROR: FLOOR_W_W\n";
char D_800ECAE8[] = "ERROR: CVT_W_W\n";
char D_800ECAF8[] = "ERROR: C.F_W\n";
char D_800ECB08[] = "ERROR: C.UN_W\n";
char D_800ECB18[] = "ERROR: C.EQ_W\n";
char D_800ECB28[] = "ERROR: C.UEQ_W\n";
char D_800ECB38[] = "ERROR: C.OLT_W\n";
char D_800ECB48[] = "ERROR: C.ULT_W\n";
char D_800ECB58[] = "ERROR: C.OLE_W\n";
char D_800ECB68[] = "ERROR: C.ULE_W\n";
char D_800ECB78[] = "ERROR: C.SF_W\n";
char D_800ECB88[] = "ERROR: C.NGLE_W\n";
char D_800ECB9C[] = "ERROR: C.SEQ_W\n";
char D_800ECBAC[] = "ERROR: C.NGL_W\n";
char D_800ECBBC[] = "ERROR: C.LT_W\n";
char D_800ECBCC[] = "ERROR: C.NGE_W\n";
char D_800ECBDC[] = "ERROR: C.LE_W\n";
char D_800ECBEC[] = "ERROR: C.NGT_W\n";
char D_800ECBFC[] = "ERROR: ADD_L\n";
char D_800ECC0C[] = "ERROR: SUB_L\n";
char D_800ECC1C[] = "ERROR: MUL_L\n";
char D_800ECC2C[] = "ERROR: DIV_L\n";
char D_800ECC3C[] = "ERROR: SQRT_L\n";
char D_800ECC4C[] = "ERROR: ABS_L\n";
char D_800ECC5C[] = "ERROR: MOVE_L\n";
char D_800ECC6C[] = "ERROR: NEG_L\n";
char D_800ECC7C[] = "ERROR: ROUND_W_L\n";
char D_800ECC90[] = "ERROR: TRUNC_W_L\n";
char D_800ECCA4[] = "ERROR: CEIL_W_L\n";
char D_800ECCB8[] = "ERROR: FLOOR_W_L\n";
char D_800ECCCC[] = "ERROR: CVT_W_L\n";
char D_800ECCDC[] = "ERROR: C.F_L\n";
char D_800ECCEC[] = "ERROR: C.UN_L\n";
char D_800ECCFC[] = "ERROR: C.EQ_L\n";
char D_800ECD0C[] = "ERROR: C.UEQ_L\n";
char D_800ECD1C[] = "ERROR: C.OLT_L\n";
char D_800ECD2C[] = "ERROR: C.ULT_L\n";
char D_800ECD3C[] = "ERROR: C.OLE_L\n";
char D_800ECD4C[] = "ERROR: C.ULE_L\n";
char D_800ECD5C[] = "ERROR: C.SF_L\n";
char D_800ECD6C[] = "ERROR: C.NGLE_L\n";
char D_800ECD80[] = "ERROR: C.SEQ_L\n";
char D_800ECD90[] = "ERROR: C.NGL_L\n";
char D_800ECDA0[] = "ERROR: C.LT_L\n";
char D_800ECDB0[] = "ERROR: C.NGE_L\n";
char D_800ECDC0[] = "ERROR: C.LE_L\n";
char D_800ECDD0[] = "ERROR: C.NGT_L\n";

void* jtbl_800ECDE0[] = {
    &lbl_8005A1E0, &lbl_8005A204, &lbl_8005A228, &lbl_8005A24C, &lbl_8005A270, &lbl_8005A280,
    &lbl_8005A2A4, &lbl_8005A2B4, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34,
    &lbl_8005A2D8, &lbl_8005A2E8, &lbl_8005A2F8, &lbl_8005A308, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A688, &lbl_8005A688, &lbl_8005A318, &lbl_8005A464, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A578, &lbl_80067F34, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A588, &lbl_8005A598, &lbl_8005A5A8, &lbl_8005A5B8, &lbl_8005A5C8, &lbl_8005A5D8,
    &lbl_8005A5E8, &lbl_8005A5F8, &lbl_8005A608, &lbl_8005A618, &lbl_8005A628, &lbl_8005A638,
    &lbl_8005A648, &lbl_8005A658, &lbl_8005A668, &lbl_8005A678,
};

void* jtbl_800ECEE0[] = {
    &lbl_80059DC0, &lbl_80059DE4, &lbl_80059E08, &lbl_80059E2C, &lbl_80059E50, &lbl_80059E60,
    &lbl_80059E84, &lbl_80059E94, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34,
    &lbl_80059EB8, &lbl_80059EC8, &lbl_80059ED8, &lbl_80059EE8, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A1B4, &lbl_8005A1B4, &lbl_80059EF8, &lbl_80059FD0, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A0A4, &lbl_80067F34, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A0B4, &lbl_8005A0C4, &lbl_8005A0D4, &lbl_8005A0E4, &lbl_8005A0F4, &lbl_8005A104,
    &lbl_8005A114, &lbl_8005A124, &lbl_8005A134, &lbl_8005A144, &lbl_8005A154, &lbl_8005A164,
    &lbl_8005A174, &lbl_8005A184, &lbl_8005A194, &lbl_8005A1A4,
};

void* jtbl_800ECFE0[] = {
    &lbl_80054BD4, &lbl_80054EF0, &lbl_80055204, &lbl_80055520, &lbl_80055834, &lbl_800559F0,
    &lbl_80055BC8, &lbl_80055C54, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34,
    &lbl_80055E2C, &lbl_80055FEC, &lbl_800561AC, &lbl_8005637C, &lbl_80059D94, &lbl_80059D94,
    &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94,
    &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94,
    &lbl_80059D94, &lbl_80059D94, &lbl_8005654C, &lbl_800565DC, &lbl_80059D94, &lbl_80059D94,
    &lbl_800565EC, &lbl_80067F34, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94,
    &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94,
    &lbl_800567AC, &lbl_80056854, &lbl_800568FC, &lbl_80056CE4, &lbl_800570CC, &lbl_800574B8,
    &lbl_800578A4, &lbl_80057CC4, &lbl_800580E4, &lbl_8005818C, &lbl_800585AC, &lbl_80058994,
    &lbl_80058D7C, &lbl_80059168, &lbl_80059554, &lbl_80059974,
};

void* jtbl_800ED0E0[] = {
    &lbl_8004F91C, &lbl_8004FC44, &lbl_8004FF64, &lbl_8005028C, &lbl_800505AC, &lbl_80050770,
    &lbl_80050950, &lbl_800509E4, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34,
    &lbl_80050BC4, &lbl_80050D88, &lbl_80050F4C, &lbl_80051120, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80054BA8, &lbl_80054BA8, &lbl_800512F4, &lbl_80051304, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80051394, &lbl_80067F34, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80051558, &lbl_80051600, &lbl_800516A8, &lbl_80051A98, &lbl_80051E88, &lbl_8005227C,
    &lbl_80052670, &lbl_80052A98, &lbl_80052EC0, &lbl_80052F68, &lbl_80053390, &lbl_80053780,
    &lbl_80053B70, &lbl_80053F64, &lbl_80054358, &lbl_80054780,
};

void* jtbl_800ED1E0[] = {
    &lbl_8004E8E8, &lbl_8004EA44, &lbl_8004EBC0, &lbl_8004F0A8,
    &lbl_8004ECB0, &lbl_8004EE70, &lbl_8004EFE4,
};

void* jtbl_800ED1FC[] = {
    &lbl_8004E810, &lbl_80067F34, &lbl_80067F34, &lbl_8004E810, &lbl_8004E810,
    &lbl_80067F34, &lbl_8004E810, &lbl_8004E810, &lbl_80067F34, &lbl_8004E810,
    &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810,
    &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810,
    &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_80067F34,
};

void* jtbl_800ED260[] = {
    &lbl_800496CC, &lbl_80049998, &lbl_80049C64, &lbl_80049F5C, &lbl_8004B55C,
    &lbl_8004B55C, &lbl_8004B55C, &lbl_8004B55C, &lbl_80067F34, &lbl_80067F34,
    &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_8004B55C, &lbl_80067F34,
    &lbl_8004B55C, &lbl_8004A254, &lbl_8004A700, &lbl_8004ABAC, &lbl_8004B084,
};

void* jtbl_800ED2B0[] = {
    &lbl_8003F290, &lbl_800496A0, &lbl_8003F524, &lbl_8003F780, &lbl_8003F9D0, &lbl_800496A0,
    &lbl_8003FDBC, &lbl_800401A8, &lbl_80040594, &lbl_800407BC, &lbl_800496A0, &lbl_800496A0,
    &lbl_80067F34, &lbl_80067F34, &lbl_800496A0, &lbl_80067F34, &lbl_80040D64, &lbl_80040F68,
    &lbl_80041154, &lbl_80041358, &lbl_80041544, &lbl_800496A0, &lbl_8004180C, &lbl_80041AD4,
    &lbl_80041D9C, &lbl_80041F68, &lbl_80042134, &lbl_80042330, &lbl_8004252C, &lbl_80042B04,
    &lbl_80042F8C, &lbl_80043564, &lbl_800439EC, &lbl_80044464, &lbl_80044EDC, &lbl_800452C8,
    &lbl_800456B4, &lbl_80045AA0, &lbl_80046518, &lbl_80046904, &lbl_800496A0, &lbl_800496A0,
    &lbl_80046CF0, &lbl_80047164, &lbl_800475DC, &lbl_800479F4, &lbl_80047E0C, &lbl_80048224,
    &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_800496A0,
    &lbl_80067F34, &lbl_800496A0, &lbl_8004863C, &lbl_800496A0, &lbl_800488E0, &lbl_80048B8C,
    &lbl_80048E2C, &lbl_800496A0, &lbl_800490FC, &lbl_800493D4,
};

void* jtbl_800ED3B0[] = {
    &lbl_8003F268, &lbl_800496A8, &lbl_8004B564, &lbl_8004B80C, &lbl_8004BD30, &lbl_8004C2FC,
    &lbl_8004C730, &lbl_8004C9FC, &lbl_8004CCC8, &lbl_8004D2D4, &lbl_8004D900, &lbl_8004DC14,
    &lbl_8004DF58, &lbl_8004E1A0, &lbl_8004E430, &lbl_8004E69C, &lbl_8004E7EC, &lbl_8004E8B0,
    &lbl_8005A690, &lbl_8005A698, &lbl_8005A6A0, &lbl_8005ABFC, &lbl_8005B05C, &lbl_8005B354,
    &lbl_8005B64C, &lbl_8005BAE8, &lbl_8005BFBC, &lbl_8005BFDC, &lbl_80067F30, &lbl_80067F30,
    &lbl_80067F30, &lbl_8005BF84, &lbl_8005C01C, &lbl_8005CC14, &lbl_8005D80C, &lbl_8005DBF4,
    &lbl_8005E9B0, &lbl_8005F568, &lbl_80060120, &lbl_8005BFFC, &lbl_80060508, &lbl_80061264,
    &lbl_80061FC0, &lbl_800622F4, &lbl_80067F34, &lbl_80067F34, &lbl_8006342C, &lbl_8006375C,
    &lbl_80063790, &lbl_800637B0, &lbl_80067F30, &lbl_80067F30, &lbl_80064660, &lbl_80064680,
    &lbl_80067F30, &lbl_80065444, &lbl_80067F34, &lbl_80065A94, &lbl_80067F30, &lbl_80067F30,
    &lbl_800669E0, &lbl_80066A00, &lbl_80067F30, &lbl_800678FC,
};

void* jtbl_800ED4B0[] = {
    &lbl_800682F0, &lbl_80068360, &lbl_80068360, &lbl_800682F0, &lbl_800682F0,
    &lbl_80068360, &lbl_800682F0, &lbl_800682F0, &lbl_80068360, &lbl_800682F0,
    &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0,
    &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0,
    &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_80068360,
};

void* jtbl_800ED514[] = {
    &lbl_80068270, &lbl_8006829C, &lbl_8006834C, &lbl_80068354, &lbl_8006835C, &lbl_8006835C,
    &lbl_8006835C, &lbl_8006835C, &lbl_80068360, &lbl_80068360, &lbl_80068360, &lbl_80068360,
    &lbl_80068360, &lbl_80068360, &lbl_80068360, &lbl_80068360, &lbl_800682CC, &lbl_80068320,
    &lbl_80068360, &lbl_80068360, &lbl_8006835C, &lbl_8006835C, &lbl_8006835C, &lbl_8006835C,
};

void* jtbl_800ED574[] = {
    &lbl_8003551C, &lbl_800352F8, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C,
    &lbl_8003551C, &lbl_800354A4, &lbl_800354B4, &lbl_8003548C, &lbl_8003551C, &lbl_80035494,
    &lbl_8003551C, &lbl_8003551C, &lbl_8003549C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C,
    &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_800354BC, &lbl_800354CC, &lbl_800354DC,
    &lbl_800354EC, &lbl_800354FC, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C,
    &lbl_8003551C, &lbl_8003550C,
};

void* jtbl_800ED5F4[] = {
    &lbl_800356F4, &lbl_800356F8, &lbl_800356F4, &lbl_800356F4, &lbl_800356F4, &lbl_800356F4,
    &lbl_800356F4, &lbl_800356F8, &lbl_800356F8, &lbl_800355BC, &lbl_800356F4, &lbl_800355C4,
    &lbl_8003562C, &lbl_80035654, &lbl_800356CC, &lbl_800356F8, &lbl_800356D4, &lbl_800356F4,
    &lbl_800356F4, &lbl_800356F4, &lbl_800356F4, &lbl_800356F8, &lbl_800356F8, &lbl_800356F8,
    &lbl_800356F8, &lbl_800356F8, &lbl_800356F4, &lbl_800356F8, &lbl_800356F4, &lbl_800356F4,
    &lbl_800356F4, &lbl_800356F8,
};

char D_800ED674[] = "Exception: #### INTERNAL ERROR #### Cannot match exception-handler!";

u32 aHeapTreeFlag[125];

static char D_8013522C[] = "CFZE";
static char D_80135234[] = "NYLJ";
static char D_8013523C[] = "NM3E";
static char D_80135244[] = "CLBE";
static char D_8013524C[] = "NN6J";
static char D_80135254[] = "NN6E";
static char D_8013525C[] = "";
static char D_80135260[] = "cpu.c";

static void* gHeapTree;

static s32 cpuCompile_DSLLV_function;
static s32 cpuCompile_DSRLV_function;
static s32 cpuCompile_DSRAV_function;
static s32 cpuCompile_DMULT_function;
static s32 cpuCompile_DMULTU_function;
static s32 cpuCompile_DDIV_function;
static s32 cpuCompile_DDIVU_function;
static s32 cpuCompile_DADD_function;
static s32 cpuCompile_DADDU_function;
static s32 cpuCompile_DSUB_function;
static s32 cpuCompile_DSUBU_function;
static s32 cpuCompile_S_SQRT_function;
static s32 cpuCompile_D_SQRT_function;
static s32 cpuCompile_W_CVT_SD_function;
static s32 cpuCompile_L_CVT_SD_function;
static s32 cpuCompile_CEIL_W_function;
static s32 cpuCompile_FLOOR_W_function;
static s32 cpuCompile_ROUND_W_function;
static s32 cpuCompile_TRUNC_W_function;
static s32 cpuCompile_LB_function;
static s32 cpuCompile_LH_function;
static s32 cpuCompile_LW_function;
static s32 cpuCompile_LBU_function;
static s32 cpuCompile_LHU_function;
static s32 cpuCompile_SB_function;
static s32 cpuCompile_SH_function;
static s32 cpuCompile_SW_function;
static s32 cpuCompile_LDC_function;
static s32 cpuCompile_SDC_function;
static s32 cpuCompile_LWL_function;
static s32 cpuCompile_LWR_function;

const f64 D_80135FA0 = 0.0;
const f64 D_80135FA8 = 0.5;
const f64 D_80135FB0 = 3.0;
const f32 D_80135FB8 = 0.5;
const f64 D_80135FC0 = 4503601774854144.0;
const f64 D_80135FC8 = 4503599627370496.0;

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_DSLLV.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_DSRLV.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_DSRAV.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_DMULT.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_DMULTU.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_DDIV.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_DDIVU.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_S_SQRT.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_D_SQRT.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_W_CVT_SD.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_L_CVT_SD.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_CEIL_W.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_FLOOR_W.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_LB.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_LH.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_LW.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_LBU.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_LHU.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_SB.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_SH.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_SW.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_LDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_SDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_LWL.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCompile_LWR.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCheckDelaySlot.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetPPC.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuMakeFunction.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuFindAddress.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuNextInstruction.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuRetraceCallback.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteUpdate.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteOpcode.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteIdle.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteJump.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteCall.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteLoadStore.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteLoadStoreF.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuMakeLink.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecute.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuHackHandler.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuFreeCachedAddress.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuFindCachedAddress.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuTestInterrupt.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuException.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuMakeDevice.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuFreeDevice.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuMapAddress.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuSetTLB.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetMode.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuSetCP0_Status.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuSetRegisterCP0.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetRegisterCP0.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/__cpuERET.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/__cpuBreak.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuMapObject.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuSetDeviceGet.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuSetDevicePut.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuSetCodeHack.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuReset.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuSetXPC.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuEvent.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetAddressOffset.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetAddressBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetOffsetAddress.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuInvalidateCache.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetFunctionChecksum.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuHeapReset.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuHeapTake.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuHeapFree.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuTreeTake.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuFindFunction.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuDMAUpdateFunction.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeCallerCheck.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeInitNode.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeKill.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeKillNodes.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeDeleteNode.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeInsert.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeInsertNode.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeBalance.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeAdjustRoot.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeSearchNode.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeKillRange.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeKillReason.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeTimerCheck.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeCleanUp.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeCleanNodes.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treeForceCleanNodes.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/treePrintNode.s")

#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuOpcodeChecksum.s")
