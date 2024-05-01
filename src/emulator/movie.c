#include "dolphin.h"
#include "emulator/THPPlayer.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"

void* gBufferP;

void MovieInit(void) {
    char* szText;
    u32 size;

    THPPlayerInit(false);

    if (!simulatorGetArgument(SAT_MOVIE, &szText)) {
        THPPlayerOpen("final_zelda_credits_sound.thp", false);
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
