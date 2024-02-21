#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/types.h>
#include <dolphin/vi.h>
#include "system.h"
#include "simGCN.h"

extern GXRenderModeObj* rmode;
void* gBufferP;

void MovieInit(void) {
    char* szText;
    u32 size;

    THPPlayerInit(0);

    if (!simulatorGetArgument(SAT_MOVIE, &szText)) {
        THPPlayerOpen("final_zelda_credits_sound.thp", 0);
    } else {
        THPPlayerOpen(szText, 0);
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
