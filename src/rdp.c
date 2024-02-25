#include "rdp.h"
#include "rdp_jumptables.h"
#include "xlObject.h"

_XL_OBJECTTYPE gClassRDP[] = {
    "RDP",
    sizeof(Rdp),
    NULL,
    (EventFunc)rdpEvent,
};

static u32 sCommandCodes[] = {
    0xED000000,
    0x005003C0,
    0xDE010000,
};

void* jtbl_800EDF5C[] = {
    &lbl_80070090, &lbl_800700CC, &lbl_800700CC, &lbl_800700CC, &lbl_800700A0, &lbl_800700CC, &lbl_800700CC,
    &lbl_800700CC, &lbl_800700B0, &lbl_800700CC, &lbl_800700CC, &lbl_800700CC, &lbl_800700C0,
};

void* jtbl_800EDF90[] = {
    &lbl_80070118, &lbl_80070150, &lbl_80070150, &lbl_80070150, &lbl_80070128, &lbl_80070150, &lbl_80070150,
    &lbl_80070150, &lbl_80070138, &lbl_80070150, &lbl_80070150, &lbl_80070150, &lbl_80070148,
};

void* jtbl_800EDFC4[] = {
    &lbl_80070194, &lbl_80070204, &lbl_80070204, &lbl_80070204, &lbl_800701A0, &lbl_80070204,
    &lbl_80070204, &lbl_80070204, &lbl_800701AC, &lbl_80070204, &lbl_80070204, &lbl_80070204,
    &lbl_800701B8, &lbl_80070204, &lbl_80070204, &lbl_80070204, &lbl_800701C4, &lbl_80070204,
    &lbl_80070204, &lbl_80070204, &lbl_800701D4, &lbl_80070204, &lbl_80070204, &lbl_80070204,
    &lbl_800701E4, &lbl_80070204, &lbl_80070204, &lbl_80070204, &lbl_800701F4,
};

void* jtbl_800EE038[] = {
    &lbl_8007025C, &lbl_80070314, &lbl_80070314, &lbl_80070314, &lbl_8007026C, &lbl_80070314,
    &lbl_80070314, &lbl_80070314, &lbl_8007031C, &lbl_80070314, &lbl_80070314, &lbl_80070314,
    &lbl_8007028C, &lbl_80070314, &lbl_80070314, &lbl_80070314, &lbl_8007031C, &lbl_80070314,
    &lbl_80070314, &lbl_80070314, &lbl_8007031C, &lbl_80070314, &lbl_80070314, &lbl_80070314,
    &lbl_8007031C, &lbl_80070314, &lbl_80070314, &lbl_80070314, &lbl_8007031C,
};

void* jtbl_800EE0AC[] = {
    &lbl_800715A8, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0,
    &lbl_800715A0, &lbl_800715A8, &lbl_800715A8, &lbl_800715A8, &lbl_800715A8, &lbl_800715A8, &lbl_800715A8,
    &lbl_800715A8, &lbl_800715A8, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0,
    &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0,
    &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0, &lbl_800715A0,
    &lbl_800715A0, &lbl_80070F90, &lbl_80070F90, &lbl_800715A8, &lbl_800715A8, &lbl_800715A8, &lbl_800715A8,
    &lbl_800715A8, &lbl_800715A8, &lbl_800715A8, &lbl_80070F50, &lbl_80070EF4, &lbl_80070EB4, &lbl_80070E90,
    &lbl_800715A0, &lbl_80070E30, &lbl_80070DCC, &lbl_80070D1C, &lbl_80070C58, &lbl_80070BD4, &lbl_80070BA0,
    &lbl_80070B80, &lbl_80070B60, &lbl_80070B2C, &lbl_80070B0C, &lbl_80070924, &lbl_80070808, &lbl_8007077C,
    &lbl_800703CC,
};

static s32 nCount;
static s32 nBlurCount;
static s32 nNoteCount;
static s32 nZCount;
static s32 nZBufferCount;

const f32 D_80136008 = 32768.0;
const f32 D_8013600C = 65536.0;
const f32 D_80136010 = 0.03125;
const f32 D_80136014 = 0.0009765625;
const f32 D_80136018 = 0.0;
const f32 D_8013601C = 320.0;
const f32 D_80136020 = 240.0;
const f64 D_80136028 = 4503599627370496.0;
const f64 D_80136030 = 4503601774854144.0;

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpParseGBI.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpPutSpan8.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpPutSpan16.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpPutSpan32.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpPutSpan64.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpGetSpan8.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpGetSpan16.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpGetSpan32.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpGetSpan64.s")

#pragma GLOBAL_ASM("asm/non_matchings/rdp/rdpEvent.s")
