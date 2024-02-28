#include "xlCoreGCN.h"
#include "macros.h"

u8 gTgPcTPL[] = {
#pragma INCBIN("SIM_original.elf", 0x000D07A0, 0x00008081)
};

char D_800DB7B0[] = "CORE DONE!";

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

s32 xlCoreReset(void) {
    OSFreeToHeap(__OSCurrHeap, gpHeap);
    OSSetArenaLo(gArenaLo);
    OSSetArenaHi(gArenaHi);
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreInitRenderMode.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreInitMem.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreInitGX.s")

s32 xlCoreGetArgumentCount(void) {
    return gnCountArgument;
}

s32 xlCoreGetArgument(s32 iArgument, char** pszArgument) {
    if ((iArgument >= 0) && (iArgument < gnCountArgument)) {
        *pszArgument = *(gaszArgument + iArgument);
        return 1;
    }

    return 0;
}

s32 xlCoreHiResolution(void) {
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/main.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreBeforeRender.s")
