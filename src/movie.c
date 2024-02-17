#include "types.h"

//! TODO: move these typedefs
typedef enum _VI_XFBMode {
    /* 0 */ VI_XFBMODE_SF = 0,
    /* 1 */ VI_XFBMODE_DF = 1
} VI_XFBMode;

typedef enum _VI_TVMode {
    /*  0 */ VI_TVMODE_NTSC_INT = 0,
    /*  1 */ VI_TVMODE_NTSC_DS,
    /*  2 */ VI_TVMODE_NTSC_PROG,
    /*  4 */ VI_TVMODE_PAL_INT = 4,
    /*  5 */ VI_TVMODE_PAL_DS,
    /* 20 */ VI_TVMODE_EURGB60_INT = 20,
    /* 21 */ VI_TVMODE_EURGB60_DS,
    /*  8 */ VI_TVMODE_MPAL_INT = 8,
    /*  9 */ VI_TVMODE_MPAL_DS,
    /* 12 */ VI_TVMODE_DEBUG_INT = 12,
    /* 16 */ VI_TVMODE_DEBUG_PAL_INT = 16,
    /* 17 */ VI_TVMODE_DEBUG_PAL_DS,
} VI_TVMode;

typedef struct _GXRenderModeObj {
    /* 0x00 */ VI_TVMode viTVmode;
    /* 0x04 */ unsigned short fbWidth;
    /* 0x06 */ unsigned short efbHeight;
    /* 0x08 */ unsigned short xfbHeight;
    /* 0x0A */ unsigned short viXOrigin;
    /* 0x0C */ unsigned short viYOrigin;
    /* 0x0E */ unsigned short viWidth;
    /* 0x10 */ unsigned short viHeight;
    /* 0x14 */ VI_XFBMode xFBmode;
    /* 0x18 */ unsigned char field_rendering;
    /* 0x19 */ unsigned char aa;
    /* 0x1A */ unsigned char sample_pattern[12][2];
    /* 0x32 */ unsigned char vfilter[7];
} GXRenderModeObj; // size = 0x3C

extern int __OSCurrHeap;

extern GXRenderModeObj* rmode;
void* gBufferP;

//! TODO: import SDK headers
void* OSAllocFromHeap(int, u32);

void MovieInit(void) {
    char* szText;
    u32 size;

    THPPlayerInit(0);

    if (!simulatorGetArgument(6, &szText)) {
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
