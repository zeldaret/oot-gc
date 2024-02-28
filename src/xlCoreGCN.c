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

s32 xlCoreReset(void) {
    OSFreeToHeap(__OSCurrHeap, gpHeap);
    OSSetArenaLo(gArenaLo);
    OSSetArenaHi(gArenaHi);
    return 1;
}

static void xlCoreInitRenderMode(GXRenderModeObj* mode) {
    char* szText;
    s32 iArgument;

    if (mode != NULL) {
        rmode = mode;
        return;
    }

    switch (VIGetTvFormat()) {
        case 0:
            rmode = &GXNtsc480IntDf;

            for (iArgument = 0; iArgument < gnCountArgument; iArgument++) {
                if (iArgument >= 0 && iArgument < gnCountArgument) {
                    szText = gaszArgument[iArgument];
                }
                    
                if ((szText[0] == '-' || szText[0] == '/' || szText[0] == '\\') 
                    && (szText[1] == 'p' || szText[1] == 'P') 
                    && szText[2] == '1') {
                    rmode = &GXNtsc480Prog;
                    break;
                }
            }

            rmode->viXOrigin -= 0x20;
            rmode->viWidth += 0x40;
            break;
        case 1:
            rmode = &GXPal528IntDf;
            break;
        case 2:
            rmode = &GXMpal480IntDf;
            break;
        default:
            OSPanic(D_800DB7A4, 182, D_800DB7BC);
            break;
    }

    GXAdjustForOverscan(rmode, &rmodeobj, 0, 0);
    rmode = &rmodeobj;
}

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
