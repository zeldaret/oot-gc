#include "xlCoreGCN.h"
#include "macros.h"

u8 gTgPcTPL[] = {
#pragma INCBIN("SIM_original.elf", 0x000D07A0, 0x00008081)
};

char D_800DB7A4[] = "xlCoreGCN.c";
char D_800DB7B0[] = "CORE DONE!";
char D_800DB7BC[] = "DEMOInit: invalid TV format\n";

static GXRenderModeObj rmodeobj;
GXTexObj g_texMap[4];
static s32 gnCountArgument;
static char** gaszArgument;
static void* DefaultFifo;
static __anon_0x238* DefaultFifoObj;
static void* gpHeap;
static void* gArenaHi;
static void* gArenaLo;
GXRenderModeObj* rmode;

const s32 D_80135D00 = 0x00000000;
const f32 D_80135D04 = 0.0;
const f32 D_80135D08 = 1.0;
const f64 D_80135D10 = 4503599627370496.0;

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreReset.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreInitRenderMode.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreInitMem.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreInitGX.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreGetArgumentCount.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreGetArgument.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreHiResolution.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/main.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreBeforeRender.s")
