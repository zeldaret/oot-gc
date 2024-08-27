#include "dolphin.h"
#include "emulator/THPPlayer.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"

#if VERSION == MQ_J || VERSION == MQ_U || VERSION == CE_J
#define MOVIE_FILENAME "final_zelda_credits_sound.thp"
#elif VERSION == CE_U
#define MOVIE_FILENAME "us_final_zelda_credits_sound.thp"
#elif IS_EU
#define MOVIE_FILENAME "pal_zelda_w_snd.thp"
#endif

void* gBufferP;

void MovieInit(void) {
    char* szText;
    u32 size;

    THPPlayerInit(false);

    if (!simulatorGetArgument(SAT_MOVIE, &szText)) {
        THPPlayerOpen(MOVIE_FILENAME, false);
    } else {
        THPPlayerOpen(szText, false);
    }

    size = THPPlayerCalcNeedMemory();
    gBufferP = OSAllocFromHeap(__OSCurrHeap, size);
    THPPlayerSetBuffer(gBufferP);
    THPPlayerPrepare(0, 0, 0);
    THPPlayerPlay();
}

void MovieDraw(void) {
    THPPlayerDrawCurrentFrame(rmode, 0, -8, 0x280, 0x1B8);
    THPPlayerDrawDone();
}
