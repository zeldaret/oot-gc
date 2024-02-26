#include "soundGCN.h"
#include "macros.h"
#include "xlObject.h"

_XL_OBJECTTYPE gClassSound = {
    "SOUND",
    sizeof(Sound),
    NULL,
    (EventFunc)soundEvent,
};

char D_800EA7E8[62] = "SetBufferSize: ERROR: 'nSize' must be a multiple of 32! (%d)\n";
char D_800EA828[11] = "soundGCN.c";

s32 gVolumeCurve[257] ALIGNAS(32);

s32 D_80134DD0 = 0x0000000A;

const f32 D_80135DD8 = 65536.0;
const f32 D_80135DDC = 20.0;
const f32 D_80135DE0 = 256.0;
const f64 D_80135DE8 = 256.0;
const f64 D_80135DF0 = 4503601774854144.0;
const f32 D_80135DF8 = 0.5;

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundWipeBuffers.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundMakeRamp.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundPlayBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundCallbackDMA.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundMakeBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundSetLength.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundSetDACRate.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundSetAddress.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundGetDMABuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundSetBufferSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundCallbackBeep.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundLoadBeep.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundPlayBeep.s")

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundEvent.s")
