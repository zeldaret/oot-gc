#include "dolphin.h"

const s32 D_80135D78[2] = {
    0xFFA60000,
    0xFF8E0087,
};

const s32 D_80135D80 = 0x0000E258;
const s32 D_80135D84 = 0xB30000B6;
const s32 D_80135D88 = 0xFF00FF80;

const f32 D_80135D8C = 0.0;
const f32 D_80135D90 = -1.0;
const f32 D_80135D94 = 1.0;
const f64 D_80135D98 = 4503601774854144.0;

#pragma GLOBAL_ASM("asm/non_matchings/THPDraw/THPGXYuv2RgbDraw.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPDraw/THPGXYuv2RgbSetup.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPDraw/THPGXRestore.s")
