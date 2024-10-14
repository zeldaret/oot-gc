#include "emulator/rsp.h"
#include "emulator/cpu.h"
#include "emulator/frame.h"
#include "emulator/ram.h"
#include "emulator/rdp.h"
#include "emulator/rsp_jumptables.h"
#include "emulator/system.h"
#include "emulator/xlHeap.h"
#include "emulator/xlList.h"
#include "string.h"

_XL_OBJECTTYPE gClassRSP = {
    "RSP",
    sizeof(Rsp),
    NULL,
    (EventFunc)rspEvent,
};

s32 cmask_tab[8] = {0x7, 0xE, 0xC, 0xC, 0x0, 0x0, 0x0, 0x0};
s32 emask_tab[8] = {0x0, 0x1, 0x3, 0x3, 0x7, 0x7, 0x7, 0x7};

static s16 TMEMSIZE[5] = {
    0x0200, 0x0200, 0x0100, 0x0200, 0x0200,
};

char D_800EE27C[40] = "FrameComplete: Yielded task pending...\n";

#ifndef NON_MATCHING
// rspGet32
void* jtbl_800EE2A4[29] = {
    &lbl_800721A4, &lbl_80072218, &lbl_80072218, &lbl_80072218, &lbl_800721B0, &lbl_80072218,
    &lbl_80072218, &lbl_80072218, &lbl_800721BC, &lbl_80072218, &lbl_80072218, &lbl_80072218,
    &lbl_800721C8, &lbl_80072218, &lbl_80072218, &lbl_80072218, &lbl_800721D4, &lbl_80072218,
    &lbl_80072218, &lbl_80072218, &lbl_800721E4, &lbl_80072218, &lbl_80072218, &lbl_80072218,
    &lbl_800721F4, &lbl_80072218, &lbl_80072218, &lbl_80072218, &lbl_80072204,
};
#else
void* jtbl_800EE2A4[29] = {0};
#endif

#ifndef NON_MATCHING
// rspPut32
void* jtbl_800EE318[8] = {
    &lbl_80072718, &lbl_80072580, &lbl_800725B4, &lbl_800725E8,
    &lbl_80072608, &lbl_80072670, &lbl_800726D8, &lbl_800726F8,
};
#else
void* jtbl_800EE318[8] = {0};
#endif

#ifndef NON_MATCHING
// rspPut32
void* jtbl_800EE338[29] = {
    &lbl_8007241C, &lbl_80072948, &lbl_80072948, &lbl_80072948, &lbl_8007242C, &lbl_80072948,
    &lbl_80072948, &lbl_80072948, &lbl_8007243C, &lbl_80072948, &lbl_80072948, &lbl_80072948,
    &lbl_800724AC, &lbl_80072948, &lbl_80072948, &lbl_80072948, &lbl_80072534, &lbl_80072948,
    &lbl_80072948, &lbl_80072948, &lbl_80072998, &lbl_80072948, &lbl_80072948, &lbl_80072948,
    &lbl_80072998, &lbl_80072948, &lbl_80072948, &lbl_80072948, &lbl_8007293C,
};
#else
void* jtbl_800EE338[29] = {0};
#endif

#ifndef NON_MATCHING
// rspParseGBI
void* jtbl_800EE3AC[11] = {
    &lbl_80072AC0, &lbl_80072AC0, &lbl_80072AC0, &lbl_80072AD4, &lbl_80072AE8, &lbl_80072AC0,
    &lbl_80072AD4, &lbl_80072AC0, &lbl_80072AD4, &lbl_80072AC0, &lbl_80072AD4,
};
#else
void* jtbl_800EE3AC[11] = {0};
#endif

void* jtbl_800EE3D8[13] = {
    &lbl_80075608, &lbl_8007600C, &lbl_8007600C, &lbl_8007600C, &lbl_80075630, &lbl_8007600C, &lbl_8007600C,
    &lbl_8007600C, &lbl_8007600C, &lbl_8007600C, &lbl_8007600C, &lbl_8007600C, &lbl_8007600C,
};

void* jtbl_800EE40C[15] = {
    &lbl_8007600C, &lbl_800750A4, &lbl_80074F84, &lbl_800750A4, &lbl_8007600C,
    &lbl_800750A4, &lbl_80074FB0, &lbl_800750A4, &lbl_80074FC4, &lbl_800750A4,
    &lbl_80075020, &lbl_800750A4, &lbl_8007600C, &lbl_800750A4, &lbl_8007600C,
};

void* jtbl_800EE448[13] = {
    &lbl_80074A78, &lbl_80074D04, &lbl_8007600C, &lbl_80074D04, &lbl_80074C44, &lbl_80074D04, &lbl_80074CA4,
    &lbl_80074D04, &lbl_8007600C, &lbl_80074D04, &lbl_8007600C, &lbl_80074D04, &lbl_800749F0,
};

void* jtbl_800EE47C[13] = {
    &lbl_80077440, &lbl_80077778, &lbl_80077778, &lbl_80077778, &lbl_80077468, &lbl_80077778, &lbl_80077778,
    &lbl_80077778, &lbl_80077778, &lbl_80077778, &lbl_80077778, &lbl_80077778, &lbl_80077778,
};

void* jtbl_800EE4B0[15] = {
    &lbl_80076D14, &lbl_80076F5C, &lbl_80076E3C, &lbl_80076F5C, &lbl_80077778,
    &lbl_80076F5C, &lbl_80076E84, &lbl_80076F5C, &lbl_80076E94, &lbl_80076F5C,
    &lbl_80076EF0, &lbl_80076F5C, &lbl_80077778, &lbl_80076F5C, &lbl_80077778,
};

void* jtbl_800EE4EC[31] = {
    &lbl_80076698, &lbl_8007685C, &lbl_800766EC, &lbl_8007685C, &lbl_80076744, &lbl_8007685C, &lbl_8007679C,
    &lbl_8007685C, &lbl_8007679C, &lbl_8007685C, &lbl_8007679C, &lbl_8007685C, &lbl_8007679C, &lbl_8007685C,
    &lbl_8007679C, &lbl_8007685C, &lbl_8007679C, &lbl_8007685C, &lbl_8007679C, &lbl_8007685C, &lbl_8007679C,
    &lbl_8007685C, &lbl_80077778, &lbl_8007685C, &lbl_80077778, &lbl_8007685C, &lbl_80077778, &lbl_8007685C,
    &lbl_80077778, &lbl_8007685C, &lbl_800767FC,
};

#ifndef NON_MATCHING
// rspParseABI4
void* jtbl_800EE568[27] = {
    &lbl_8008118C, &lbl_80080B40, &lbl_80080B50, &lbl_8008117C, &lbl_80080B6C, &lbl_80080B7C, &lbl_80080B8C,
    &lbl_8008117C, &lbl_80080CF4, &lbl_8008117C, &lbl_80080D20, &lbl_80080D4C, &lbl_80080DB0, &lbl_80080DC0,
    &lbl_80080E2C, &lbl_80080E3C, &lbl_80080E58, &lbl_80080E98, &lbl_80080FFC, &lbl_80081048, &lbl_80081058,
    &lbl_800810A4, &lbl_800810F0, &lbl_8008111C, &lbl_8008112C, &lbl_8008118C, &lbl_8008113C,
};
#else
void* jtbl_800EE568[27] = {0};
#endif

#ifndef NON_MATCHING
// rspParseABI3
void* jtbl_800EE5D4[23] = {
    &lbl_80082B60, &lbl_800826C0, &lbl_800826D0, &lbl_80082B50, &lbl_80082B50, &lbl_80082764,
    &lbl_80082B50, &lbl_800827D0, &lbl_800827E4, &lbl_80082B50, &lbl_800827F4, &lbl_80082830,
    &lbl_80082894, &lbl_800828A4, &lbl_8008291C, &lbl_8008292C, &lbl_80082948, &lbl_80082990,
    &lbl_80082B04, &lbl_800826F8, &lbl_80082708, &lbl_80082774, &lbl_80082B40,
};
#else
void* jtbl_800EE5D4[23] = {0};
#endif

#ifndef NON_MATCHING
// rspParseABI2
void* jtbl_800EE630[24] = {
    &lbl_80084950, &lbl_80084338, &lbl_80084360, &lbl_8008437C, &lbl_8008438C, &lbl_8008439C,
    &lbl_800843AC, &lbl_80084514, &lbl_80084524, &lbl_80084550, &lbl_80084590, &lbl_800845BC,
    &lbl_80084620, &lbl_80084630, &lbl_80084640, &lbl_80084650, &lbl_8008466C, &lbl_800846AC,
    &lbl_80084810, &lbl_8008485C, &lbl_8008486C, &lbl_800848B8, &lbl_80084904, &lbl_80084930,
};
#else
void* jtbl_800EE630[24] = {0};
#endif

#ifndef NON_MATCHING
// rspParseABI1
void* jtbl_800EE690[16] = {
    &lbl_80088B18, &lbl_80088890, &lbl_8008889C, &lbl_80088AD8, &lbl_800888C4, &lbl_80088AE4,
    &lbl_80088914, &lbl_80088970, &lbl_80088984, &lbl_80088AF0, &lbl_80088990, &lbl_800889CC,
    &lbl_80088A38, &lbl_80088A44, &lbl_80088AFC, &lbl_80088ABC,
};
#else
void* jtbl_800EE690[16] = {0};
#endif

static bool nFirstTime_2148 = true;
static bool nFirstTime_2648 = true;
static bool nFirstTime_2757 = true;
static bool nFirstTime_2796 = true;

static s32 counter;

// TODO: initialize as 0 << 2
static u16 scissorX0;
static u16 scissorY0;
static u16 scissorX1 = N64_FRAME_WIDTH << 2;
static u16 scissorY1 = N64_FRAME_HEIGHT << 2;

static u8 flagBilerp;
static u32 rdpSetTimg_w0;
static u32 rdpSetTile_w0;
static u16 tmemSliceWmax;
static u16 imageSrcWsize;
static u16 flagSplit;
static u16 imagePtrX0;
static u32 imageTop;
static s16 tmemSrcLines;

static s16 TMEMMASK[4] = {
    0x01FF,
    0x00FF,
    0x007F,
    0x003F,
};

static s16 TMEMSHIFT[4] = {
    0x0200,
    0x0100,
    0x0080,
    0x0040,
};

const f32 D_80136038 = 0.25f;
const f32 D_8013603C = 1024.0f;
const f32 D_80136040 = 0.03125f;
const f64 D_80136048 = 4503601774854144.0;
const f64 D_80136050 = 4503599627370496.0;
const f32 D_80136058 = 1.0f;
const f32 D_8013605C = 0.0f;
const f32 D_80136060 = 0.5f;
const f32 D_80136064 = 2.0f;
const f32 D_80136068 = -1.0;
const f32 D_8013606C = 65536.0f;
const f32 D_80136070 = 0.0009765625f;
const f32 D_80136074 = 1.52587890625e-05;

static bool rspInitAudioDMEM1(Rsp* pRSP);
static bool rspInitAudioDMEM2(Rsp* pRSP);
static bool rspInitAudioDMEM3(Rsp* pRSP);
static bool rspInitAudioDMEM4(Rsp* pRSP);

static bool rspParseABI1(Rsp* pRSP, RspTask* pTask);
static bool rspParseABI2(Rsp* pRSP, RspTask* pTask);
static bool rspParseABI3(Rsp* pRSP, RspTask* pTask);
static bool rspParseABI4(Rsp* pRSP, RspTask* pTask);

static bool rspVMUDN(Rsp* pRSP, s16* pVec1, s16* pVec2, s16* pVecResult, u32 nElement, s64* pAcc) {
    s32 i;
    s64 taccum;
    s64 ai;
    u16 su;
    s16 ti;
    u16 du;
    s32 clampShift = 31;
    s64 clampMask = ~(((s64)1 << clampShift) - 1);
    s32 elementMaskIndex = (nElement & 0xF) >> 1;
    s32 pad[8];

    for (i = 0; i < 8; i++) {
        ai = 0;
        su = pVec1[i];
        ti = pVec2[(i & cmask_tab[elementMaskIndex]) + (nElement & emask_tab[elementMaskIndex])];

        taccum = (u64)su * (u64)ti;
        taccum += ai;

        if ((taccum >> 47) & 1) {
            taccum = 0xFFFF000000000000 | (taccum & 0xFFFFFFFFFFFF);
        } else {
            taccum = taccum & 0xFFFFFFFFFFFF;
        }

        pAcc[i] = taccum;

        if (taccum < 0) {
            if (~taccum & clampMask) {
                taccum = 0;
            }
        } else {
            if (taccum & clampMask) {
                taccum = 0xFFFF;
            }
        }

        du = taccum & 0xFFFF;
        du &= 0xFFFF;
        pVecResult[i] = du;
    }

    return true;
}

static bool rspVMADN(Rsp* pRSP, s16* pVec1, s16* pVec2, s16* pVecResult, u32 nElement, s64* pAcc) {
    s32 i;
    s64 taccum;
    s64 ai;
    u16 su;
    s16 ti;
    u16 du;
    s32 clampShift = 31;
    s64 clampMask = ~(((s64)1 << clampShift) - 1);
    s32 elementMaskIndex = (nElement & 0xF) >> 1;
    s32 pad[8];

    for (i = 0; i < 8; i++) {
        ai = pAcc[i];
        su = pVec1[i];
        ti = pVec2[(i & cmask_tab[elementMaskIndex]) + (nElement & emask_tab[elementMaskIndex])];

        taccum = (u64)su * (u64)ti;
        taccum += ai;

        if ((taccum >> 47) & 1) {
            taccum = 0xFFFF000000000000 | (taccum & 0xFFFFFFFFFFFF);
        } else {
            taccum = taccum & 0xFFFFFFFFFFFF;
        }

        pAcc[i] = taccum;

        if (taccum < 0) {
            if (~taccum & clampMask) {
                taccum = 0;
            }
        } else {
            if (taccum & clampMask) {
                taccum = 0xFFFF;
            }
        }

        du = taccum & 0xFFFF;
        du &= 0xFFFF;
        pVecResult[i] = du;
    }

    return true;
}

static bool rspInitAudioDMEM1(Rsp* pRSP) {
    pRSP->anAudioBuffer = pRSP->pDMEM;

    pRSP->anAudioBuffer[0x000] = 0x0000;
    pRSP->anAudioBuffer[0x001] = 0x0001;
    pRSP->anAudioBuffer[0x002] = 0x0002;
    pRSP->anAudioBuffer[0x003] = 0xFFFF;
    pRSP->anAudioBuffer[0x004] = 0x0020;
    pRSP->anAudioBuffer[0x005] = 0x0800;
    pRSP->anAudioBuffer[0x006] = 0x7FFF;
    pRSP->anAudioBuffer[0x007] = 0x4000;
    pRSP->anAudioBuffer[0x008] = 0x1118;
    pRSP->anAudioBuffer[0x009] = 0x1470;
    pRSP->anAudioBuffer[0x00A] = 0x11DC;
    pRSP->anAudioBuffer[0x00B] = 0x1B38;
    pRSP->anAudioBuffer[0x00C] = 0x1214;
    pRSP->anAudioBuffer[0x00D] = 0x187C;
    pRSP->anAudioBuffer[0x00E] = 0x1254;
    pRSP->anAudioBuffer[0x00F] = 0x12D0;
    pRSP->anAudioBuffer[0x010] = 0x12EC;
    pRSP->anAudioBuffer[0x011] = 0x1328;
    pRSP->anAudioBuffer[0x012] = 0x140C;
    pRSP->anAudioBuffer[0x013] = 0x1294;
    pRSP->anAudioBuffer[0x014] = 0x1E24;
    pRSP->anAudioBuffer[0x015] = 0x138C;
    pRSP->anAudioBuffer[0x016] = 0x170C;
    pRSP->anAudioBuffer[0x017] = 0x144C;
    pRSP->anAudioBuffer[0x018] = 0xF000;
    pRSP->anAudioBuffer[0x019] = 0x0F00;
    pRSP->anAudioBuffer[0x01A] = 0x00F0;
    pRSP->anAudioBuffer[0x01B] = 0x000F;
    pRSP->anAudioBuffer[0x01C] = 0x0001;
    pRSP->anAudioBuffer[0x01D] = 0x0010;
    pRSP->anAudioBuffer[0x01E] = 0x0100;
    pRSP->anAudioBuffer[0x01F] = 0x1000;
    pRSP->anAudioBuffer[0x020] = 0x0002;
    pRSP->anAudioBuffer[0x021] = 0x0004;
    pRSP->anAudioBuffer[0x022] = 0x0006;
    pRSP->anAudioBuffer[0x023] = 0x0008;
    pRSP->anAudioBuffer[0x024] = 0x000A;
    pRSP->anAudioBuffer[0x025] = 0x000C;
    pRSP->anAudioBuffer[0x026] = 0x000E;
    pRSP->anAudioBuffer[0x027] = 0x0010;
    pRSP->anAudioBuffer[0x028] = 0x0001;
    pRSP->anAudioBuffer[0x029] = 0x0001;
    pRSP->anAudioBuffer[0x02A] = 0x0001;
    pRSP->anAudioBuffer[0x02B] = 0x0001;
    pRSP->anAudioBuffer[0x02C] = 0x0001;
    pRSP->anAudioBuffer[0x02D] = 0x0001;
    pRSP->anAudioBuffer[0x02E] = 0x0001;
    pRSP->anAudioBuffer[0x02F] = 0x0001;
    pRSP->anAudioBuffer[0x030] = 0x0000;
    pRSP->anAudioBuffer[0x031] = 0x0001;
    pRSP->anAudioBuffer[0x032] = 0x0002;
    pRSP->anAudioBuffer[0x033] = 0x0004;
    pRSP->anAudioBuffer[0x034] = 0x0008;
    pRSP->anAudioBuffer[0x035] = 0x0010;
    pRSP->anAudioBuffer[0x036] = 0x0100;
    pRSP->anAudioBuffer[0x037] = 0x0200;
    pRSP->anAudioBuffer[0x038] = 0x0001;
    pRSP->anAudioBuffer[0x039] = 0x0000;
    pRSP->anAudioBuffer[0x03A] = 0x0000;
    pRSP->anAudioBuffer[0x03B] = 0x0000;
    pRSP->anAudioBuffer[0x03C] = 0x0001;
    pRSP->anAudioBuffer[0x03D] = 0x0000;
    pRSP->anAudioBuffer[0x03E] = 0x0000;
    pRSP->anAudioBuffer[0x03F] = 0x0000;
    pRSP->anAudioBuffer[0x040] = 0x0000;
    pRSP->anAudioBuffer[0x041] = 0x0001;
    pRSP->anAudioBuffer[0x042] = 0x0000;
    pRSP->anAudioBuffer[0x043] = 0x0000;
    pRSP->anAudioBuffer[0x044] = 0x0000;
    pRSP->anAudioBuffer[0x045] = 0x0001;
    pRSP->anAudioBuffer[0x046] = 0x0000;
    pRSP->anAudioBuffer[0x047] = 0x0000;
    pRSP->anAudioBuffer[0x048] = 0x0000;
    pRSP->anAudioBuffer[0x049] = 0x0000;
    pRSP->anAudioBuffer[0x04A] = 0x0001;
    pRSP->anAudioBuffer[0x04B] = 0x0000;
    pRSP->anAudioBuffer[0x04C] = 0x0000;
    pRSP->anAudioBuffer[0x04D] = 0x0000;
    pRSP->anAudioBuffer[0x04E] = 0x0001;
    pRSP->anAudioBuffer[0x04F] = 0x0000;
    pRSP->anAudioBuffer[0x050] = 0x0000;
    pRSP->anAudioBuffer[0x051] = 0x0000;
    pRSP->anAudioBuffer[0x052] = 0x0000;
    pRSP->anAudioBuffer[0x053] = 0x0001;
    pRSP->anAudioBuffer[0x054] = 0x0000;
    pRSP->anAudioBuffer[0x055] = 0x0000;
    pRSP->anAudioBuffer[0x056] = 0x0000;
    pRSP->anAudioBuffer[0x057] = 0x0001;
    pRSP->anAudioBuffer[0x058] = 0x2000;
    pRSP->anAudioBuffer[0x059] = 0x4000;
    pRSP->anAudioBuffer[0x05A] = 0x6000;
    pRSP->anAudioBuffer[0x05B] = 0x8000;
    pRSP->anAudioBuffer[0x05C] = 0xA000;
    pRSP->anAudioBuffer[0x05D] = 0xC000;
    pRSP->anAudioBuffer[0x05E] = 0xE000;
    pRSP->anAudioBuffer[0x05F] = 0xFFFF;
    pRSP->anAudioBuffer[0x060] = 0x0C39;
    pRSP->anAudioBuffer[0x061] = 0x66AD;
    pRSP->anAudioBuffer[0x062] = 0x0D46;
    pRSP->anAudioBuffer[0x063] = 0xFFDF;
    pRSP->anAudioBuffer[0x064] = 0x0B39;
    pRSP->anAudioBuffer[0x065] = 0x6696;
    pRSP->anAudioBuffer[0x066] = 0x0E5F;
    pRSP->anAudioBuffer[0x067] = 0xFFD8;
    pRSP->anAudioBuffer[0x068] = 0x0A44;
    pRSP->anAudioBuffer[0x069] = 0x6669;
    pRSP->anAudioBuffer[0x06A] = 0x0F83;
    pRSP->anAudioBuffer[0x06B] = 0xFFD0;
    pRSP->anAudioBuffer[0x06C] = 0x095A;
    pRSP->anAudioBuffer[0x06D] = 0x6626;
    pRSP->anAudioBuffer[0x06E] = 0x10B4;
    pRSP->anAudioBuffer[0x06F] = 0xFFC8;
    pRSP->anAudioBuffer[0x070] = 0x087D;
    pRSP->anAudioBuffer[0x071] = 0x65CD;
    pRSP->anAudioBuffer[0x072] = 0x11F0;
    pRSP->anAudioBuffer[0x073] = 0xFFBF;
    pRSP->anAudioBuffer[0x074] = 0x07AB;
    pRSP->anAudioBuffer[0x075] = 0x655E;
    pRSP->anAudioBuffer[0x076] = 0x1338;
    pRSP->anAudioBuffer[0x077] = 0xFFB6;
    pRSP->anAudioBuffer[0x078] = 0x06E4;
    pRSP->anAudioBuffer[0x079] = 0x64D9;
    pRSP->anAudioBuffer[0x07A] = 0x148C;
    pRSP->anAudioBuffer[0x07B] = 0xFFAC;
    pRSP->anAudioBuffer[0x07C] = 0x0628;
    pRSP->anAudioBuffer[0x07D] = 0x643F;
    pRSP->anAudioBuffer[0x07E] = 0x15EB;
    pRSP->anAudioBuffer[0x07F] = 0xFFA1;
    pRSP->anAudioBuffer[0x080] = 0x0577;
    pRSP->anAudioBuffer[0x081] = 0x638F;
    pRSP->anAudioBuffer[0x082] = 0x1756;
    pRSP->anAudioBuffer[0x083] = 0xFF96;
    pRSP->anAudioBuffer[0x084] = 0x04D1;
    pRSP->anAudioBuffer[0x085] = 0x62CB;
    pRSP->anAudioBuffer[0x086] = 0x18CB;
    pRSP->anAudioBuffer[0x087] = 0xFF8A;
    pRSP->anAudioBuffer[0x088] = 0x0435;
    pRSP->anAudioBuffer[0x089] = 0x61F3;
    pRSP->anAudioBuffer[0x08A] = 0x1A4C;
    pRSP->anAudioBuffer[0x08B] = 0xFF7E;
    pRSP->anAudioBuffer[0x08C] = 0x03A4;
    pRSP->anAudioBuffer[0x08D] = 0x6106;
    pRSP->anAudioBuffer[0x08E] = 0x1BD7;
    pRSP->anAudioBuffer[0x08F] = 0xFF71;
    pRSP->anAudioBuffer[0x090] = 0x031C;
    pRSP->anAudioBuffer[0x091] = 0x6007;
    pRSP->anAudioBuffer[0x092] = 0x1D6C;
    pRSP->anAudioBuffer[0x093] = 0xFF64;
    pRSP->anAudioBuffer[0x094] = 0x029F;
    pRSP->anAudioBuffer[0x095] = 0x5EF5;
    pRSP->anAudioBuffer[0x096] = 0x1F0B;
    pRSP->anAudioBuffer[0x097] = 0xFF56;
    pRSP->anAudioBuffer[0x098] = 0x022A;
    pRSP->anAudioBuffer[0x099] = 0x5DD0;
    pRSP->anAudioBuffer[0x09A] = 0x20B3;
    pRSP->anAudioBuffer[0x09B] = 0xFF48;
    pRSP->anAudioBuffer[0x09C] = 0x01BE;
    pRSP->anAudioBuffer[0x09D] = 0x5C9A;
    pRSP->anAudioBuffer[0x09E] = 0x2264;
    pRSP->anAudioBuffer[0x09F] = 0xFF3A;
    pRSP->anAudioBuffer[0x0A0] = 0x015B;
    pRSP->anAudioBuffer[0x0A1] = 0x5B53;
    pRSP->anAudioBuffer[0x0A2] = 0x241E;
    pRSP->anAudioBuffer[0x0A3] = 0xFF2C;
    pRSP->anAudioBuffer[0x0A4] = 0x0101;
    pRSP->anAudioBuffer[0x0A5] = 0x59FC;
    pRSP->anAudioBuffer[0x0A6] = 0x25E0;
    pRSP->anAudioBuffer[0x0A7] = 0xFF1E;
    pRSP->anAudioBuffer[0x0A8] = 0x00AE;
    pRSP->anAudioBuffer[0x0A9] = 0x5896;
    pRSP->anAudioBuffer[0x0AA] = 0x27A9;
    pRSP->anAudioBuffer[0x0AB] = 0xFF10;
    pRSP->anAudioBuffer[0x0AC] = 0x0063;
    pRSP->anAudioBuffer[0x0AD] = 0x5720;
    pRSP->anAudioBuffer[0x0AE] = 0x297A;
    pRSP->anAudioBuffer[0x0AF] = 0xFF02;
    pRSP->anAudioBuffer[0x0B0] = 0x001F;
    pRSP->anAudioBuffer[0x0B1] = 0x559D;
    pRSP->anAudioBuffer[0x0B2] = 0x2B50;
    pRSP->anAudioBuffer[0x0B3] = 0xFEF4;
    pRSP->anAudioBuffer[0x0B4] = 0xFFE2;
    pRSP->anAudioBuffer[0x0B5] = 0x540D;
    pRSP->anAudioBuffer[0x0B6] = 0x2D2C;
    pRSP->anAudioBuffer[0x0B7] = 0xFEE8;
    pRSP->anAudioBuffer[0x0B8] = 0xFFAC;
    pRSP->anAudioBuffer[0x0B9] = 0x5270;
    pRSP->anAudioBuffer[0x0BA] = 0x2F0D;
    pRSP->anAudioBuffer[0x0BB] = 0xFEDB;
    pRSP->anAudioBuffer[0x0BC] = 0xFF7C;
    pRSP->anAudioBuffer[0x0BD] = 0x50C7;
    pRSP->anAudioBuffer[0x0BE] = 0x30F3;
    pRSP->anAudioBuffer[0x0BF] = 0xFED0;
    pRSP->anAudioBuffer[0x0C0] = 0xFF53;
    pRSP->anAudioBuffer[0x0C1] = 0x4F14;
    pRSP->anAudioBuffer[0x0C2] = 0x32DC;
    pRSP->anAudioBuffer[0x0C3] = 0xFEC6;
    pRSP->anAudioBuffer[0x0C4] = 0xFF2E;
    pRSP->anAudioBuffer[0x0C5] = 0x4D57;
    pRSP->anAudioBuffer[0x0C6] = 0x34C8;
    pRSP->anAudioBuffer[0x0C7] = 0xFEBD;
    pRSP->anAudioBuffer[0x0C8] = 0xFF0F;
    pRSP->anAudioBuffer[0x0C9] = 0x4B91;
    pRSP->anAudioBuffer[0x0CA] = 0x36B6;
    pRSP->anAudioBuffer[0x0CB] = 0xFEB6;
    pRSP->anAudioBuffer[0x0CC] = 0xFEF5;
    pRSP->anAudioBuffer[0x0CD] = 0x49C2;
    pRSP->anAudioBuffer[0x0CE] = 0x38A5;
    pRSP->anAudioBuffer[0x0CF] = 0xFEB0;
    pRSP->anAudioBuffer[0x0D0] = 0xFEDF;
    pRSP->anAudioBuffer[0x0D1] = 0x47ED;
    pRSP->anAudioBuffer[0x0D2] = 0x3A95;
    pRSP->anAudioBuffer[0x0D3] = 0xFEAC;
    pRSP->anAudioBuffer[0x0D4] = 0xFECE;
    pRSP->anAudioBuffer[0x0D5] = 0x4611;
    pRSP->anAudioBuffer[0x0D6] = 0x3C85;
    pRSP->anAudioBuffer[0x0D7] = 0xFEAB;
    pRSP->anAudioBuffer[0x0D8] = 0xFEC0;
    pRSP->anAudioBuffer[0x0D9] = 0x4430;
    pRSP->anAudioBuffer[0x0DA] = 0x3E74;
    pRSP->anAudioBuffer[0x0DB] = 0xFEAC;
    pRSP->anAudioBuffer[0x0DC] = 0xFEB6;
    pRSP->anAudioBuffer[0x0DD] = 0x424A;
    pRSP->anAudioBuffer[0x0DE] = 0x4060;
    pRSP->anAudioBuffer[0x0DF] = 0xFEAF;
    pRSP->anAudioBuffer[0x0E0] = 0xFEAF;
    pRSP->anAudioBuffer[0x0E1] = 0x4060;
    pRSP->anAudioBuffer[0x0E2] = 0x424A;
    pRSP->anAudioBuffer[0x0E3] = 0xFEB6;
    pRSP->anAudioBuffer[0x0E4] = 0xFEAC;
    pRSP->anAudioBuffer[0x0E5] = 0x3E74;
    pRSP->anAudioBuffer[0x0E6] = 0x4430;
    pRSP->anAudioBuffer[0x0E7] = 0xFEC0;
    pRSP->anAudioBuffer[0x0E8] = 0xFEAB;
    pRSP->anAudioBuffer[0x0E9] = 0x3C85;
    pRSP->anAudioBuffer[0x0EA] = 0x4611;
    pRSP->anAudioBuffer[0x0EB] = 0xFECE;
    pRSP->anAudioBuffer[0x0EC] = 0xFEAC;
    pRSP->anAudioBuffer[0x0ED] = 0x3A95;
    pRSP->anAudioBuffer[0x0EE] = 0x47ED;
    pRSP->anAudioBuffer[0x0EF] = 0xFEDF;
    pRSP->anAudioBuffer[0x0F0] = 0xFEB0;
    pRSP->anAudioBuffer[0x0F1] = 0x38A5;
    pRSP->anAudioBuffer[0x0F2] = 0x49C2;
    pRSP->anAudioBuffer[0x0F3] = 0xFEF5;
    pRSP->anAudioBuffer[0x0F4] = 0xFEB6;
    pRSP->anAudioBuffer[0x0F5] = 0x36B6;
    pRSP->anAudioBuffer[0x0F6] = 0x4B91;
    pRSP->anAudioBuffer[0x0F7] = 0xFF0F;
    pRSP->anAudioBuffer[0x0F8] = 0xFEBD;
    pRSP->anAudioBuffer[0x0F9] = 0x34C8;
    pRSP->anAudioBuffer[0x0FA] = 0x4D57;
    pRSP->anAudioBuffer[0x0FB] = 0xFF2E;
    pRSP->anAudioBuffer[0x0FC] = 0xFEC6;
    pRSP->anAudioBuffer[0x0FD] = 0x32DC;
    pRSP->anAudioBuffer[0x0FE] = 0x4F14;
    pRSP->anAudioBuffer[0x0FF] = 0xFF53;
    pRSP->anAudioBuffer[0x100] = 0xFED0;
    pRSP->anAudioBuffer[0x101] = 0x30F3;
    pRSP->anAudioBuffer[0x102] = 0x50C7;
    pRSP->anAudioBuffer[0x103] = 0xFF7C;
    pRSP->anAudioBuffer[0x104] = 0xFEDB;
    pRSP->anAudioBuffer[0x105] = 0x2F0D;
    pRSP->anAudioBuffer[0x106] = 0x5270;
    pRSP->anAudioBuffer[0x107] = 0xFFAC;
    pRSP->anAudioBuffer[0x108] = 0xFEE8;
    pRSP->anAudioBuffer[0x109] = 0x2D2C;
    pRSP->anAudioBuffer[0x10A] = 0x540D;
    pRSP->anAudioBuffer[0x10B] = 0xFFE2;
    pRSP->anAudioBuffer[0x10C] = 0xFEF4;
    pRSP->anAudioBuffer[0x10D] = 0x2B50;
    pRSP->anAudioBuffer[0x10E] = 0x559D;
    pRSP->anAudioBuffer[0x10F] = 0x001F;
    pRSP->anAudioBuffer[0x110] = 0xFF02;
    pRSP->anAudioBuffer[0x111] = 0x297A;
    pRSP->anAudioBuffer[0x112] = 0x5720;
    pRSP->anAudioBuffer[0x113] = 0x0063;
    pRSP->anAudioBuffer[0x114] = 0xFF10;
    pRSP->anAudioBuffer[0x115] = 0x27A9;
    pRSP->anAudioBuffer[0x116] = 0x5896;
    pRSP->anAudioBuffer[0x117] = 0x00AE;
    pRSP->anAudioBuffer[0x118] = 0xFF1E;
    pRSP->anAudioBuffer[0x119] = 0x25E0;
    pRSP->anAudioBuffer[0x11A] = 0x59FC;
    pRSP->anAudioBuffer[0x11B] = 0x0101;
    pRSP->anAudioBuffer[0x11C] = 0xFF2C;
    pRSP->anAudioBuffer[0x11D] = 0x241E;
    pRSP->anAudioBuffer[0x11E] = 0x5B53;
    pRSP->anAudioBuffer[0x11F] = 0x015B;
    pRSP->anAudioBuffer[0x120] = 0xFF3A;
    pRSP->anAudioBuffer[0x121] = 0x2264;
    pRSP->anAudioBuffer[0x122] = 0x5C9A;
    pRSP->anAudioBuffer[0x123] = 0x01BE;
    pRSP->anAudioBuffer[0x124] = 0xFF48;
    pRSP->anAudioBuffer[0x125] = 0x20B3;
    pRSP->anAudioBuffer[0x126] = 0x5DD0;
    pRSP->anAudioBuffer[0x127] = 0x022A;
    pRSP->anAudioBuffer[0x128] = 0xFF56;
    pRSP->anAudioBuffer[0x129] = 0x1F0B;
    pRSP->anAudioBuffer[0x12A] = 0x5EF5;
    pRSP->anAudioBuffer[0x12B] = 0x029F;
    pRSP->anAudioBuffer[0x12C] = 0xFF64;
    pRSP->anAudioBuffer[0x12D] = 0x1D6C;
    pRSP->anAudioBuffer[0x12E] = 0x6007;
    pRSP->anAudioBuffer[0x12F] = 0x031C;
    pRSP->anAudioBuffer[0x130] = 0xFF71;
    pRSP->anAudioBuffer[0x131] = 0x1BD7;
    pRSP->anAudioBuffer[0x132] = 0x6106;
    pRSP->anAudioBuffer[0x133] = 0x03A4;
    pRSP->anAudioBuffer[0x134] = 0xFF7E;
    pRSP->anAudioBuffer[0x135] = 0x1A4C;
    pRSP->anAudioBuffer[0x136] = 0x61F3;
    pRSP->anAudioBuffer[0x137] = 0x0435;
    pRSP->anAudioBuffer[0x138] = 0xFF8A;
    pRSP->anAudioBuffer[0x139] = 0x18CB;
    pRSP->anAudioBuffer[0x13A] = 0x62CB;
    pRSP->anAudioBuffer[0x13B] = 0x04D1;
    pRSP->anAudioBuffer[0x13C] = 0xFF96;
    pRSP->anAudioBuffer[0x13D] = 0x1756;
    pRSP->anAudioBuffer[0x13E] = 0x638F;
    pRSP->anAudioBuffer[0x13F] = 0x0577;
    pRSP->anAudioBuffer[0x140] = 0xFFA1;
    pRSP->anAudioBuffer[0x141] = 0x15EB;
    pRSP->anAudioBuffer[0x142] = 0x643F;
    pRSP->anAudioBuffer[0x143] = 0x0628;
    pRSP->anAudioBuffer[0x144] = 0xFFAC;
    pRSP->anAudioBuffer[0x145] = 0x148C;
    pRSP->anAudioBuffer[0x146] = 0x64D9;
    pRSP->anAudioBuffer[0x147] = 0x06E4;
    pRSP->anAudioBuffer[0x148] = 0xFFB6;
    pRSP->anAudioBuffer[0x149] = 0x1338;
    pRSP->anAudioBuffer[0x14A] = 0x655E;
    pRSP->anAudioBuffer[0x14B] = 0x07AB;
    pRSP->anAudioBuffer[0x14C] = 0xFFBF;
    pRSP->anAudioBuffer[0x14D] = 0x11F0;
    pRSP->anAudioBuffer[0x14E] = 0x65CD;
    pRSP->anAudioBuffer[0x14F] = 0x087D;
    pRSP->anAudioBuffer[0x150] = 0xFFC8;
    pRSP->anAudioBuffer[0x151] = 0x10B4;
    pRSP->anAudioBuffer[0x152] = 0x6626;
    pRSP->anAudioBuffer[0x153] = 0x095A;
    pRSP->anAudioBuffer[0x154] = 0xFFD0;
    pRSP->anAudioBuffer[0x155] = 0x0F83;
    pRSP->anAudioBuffer[0x156] = 0x6669;
    pRSP->anAudioBuffer[0x157] = 0x0A44;
    pRSP->anAudioBuffer[0x158] = 0xFFD8;
    pRSP->anAudioBuffer[0x159] = 0x0E5F;
    pRSP->anAudioBuffer[0x15A] = 0x6696;
    pRSP->anAudioBuffer[0x15B] = 0x0B39;
    pRSP->anAudioBuffer[0x15C] = 0xFFDF;
    pRSP->anAudioBuffer[0x15D] = 0x0D46;
    pRSP->anAudioBuffer[0x15E] = 0x66AD;
    pRSP->anAudioBuffer[0x15F] = 0x0C39;

    return true;
}

bool rspDotProduct8x15MatrixBy15x1Vector(Rsp* pRSP, s16* matrix, s16* vectorIn, s16* vectorOut) {
    s32 sum;
    s32 vec0 = vectorIn[0];
    s32 vec1 = vectorIn[1];
    s32 vec2 = vectorIn[2];
    s32 vec3 = vectorIn[3];
    s32 vec4 = vectorIn[4];
    s32 vec5 = vectorIn[5];
    s32 vec6 = vectorIn[6];
    s32 vec7 = vectorIn[7];
    s32 vec8 = vectorIn[8];
    s32 vec9 = vectorIn[9];
    s32 vec10 = vectorIn[10];
    s32 vec11 = vectorIn[11];
    s32 vec12 = vectorIn[12];
    s32 vec13 = vectorIn[13];
    s32 vec14 = vectorIn[14];

    sum = matrix[0] * vec0;
    sum += matrix[1] * vec1;
    sum += matrix[2] * vec2;
    sum += matrix[3] * vec3;
    sum += matrix[4] * vec4;
    sum += matrix[5] * vec5;
    sum += matrix[6] * vec6;
    sum += matrix[7] * vec7;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[0] = sum;

    sum = matrix[0] * vec1;
    sum += matrix[1] * vec2;
    sum += matrix[2] * vec3;
    sum += matrix[3] * vec4;
    sum += matrix[4] * vec5;
    sum += matrix[5] * vec6;
    sum += matrix[6] * vec7;
    sum += matrix[7] * vec8;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[1] = sum;

    sum = matrix[0] * vec2;
    sum += matrix[1] * vec3;
    sum += matrix[2] * vec4;
    sum += matrix[3] * vec5;
    sum += matrix[4] * vec6;
    sum += matrix[5] * vec7;
    sum += matrix[6] * vec8;
    sum += matrix[7] * vec9;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[2] = sum;

    sum = matrix[0] * vec3;
    sum += matrix[1] * vec4;
    sum += matrix[2] * vec5;
    sum += matrix[3] * vec6;
    sum += matrix[4] * vec7;
    sum += matrix[5] * vec8;
    sum += matrix[6] * vec9;
    sum += matrix[7] * vec10;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[3] = sum;

    sum = matrix[0] * vec4;
    sum += matrix[1] * vec5;
    sum += matrix[2] * vec6;
    sum += matrix[3] * vec7;
    sum += matrix[4] * vec8;
    sum += matrix[5] * vec9;
    sum += matrix[6] * vec10;
    sum += matrix[7] * vec11;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[4] = sum;

    sum = matrix[0] * vec5;
    sum += matrix[1] * vec6;
    sum += matrix[2] * vec7;
    sum += matrix[3] * vec8;
    sum += matrix[4] * vec9;
    sum += matrix[5] * vec10;
    sum += matrix[6] * vec11;
    sum += matrix[7] * vec12;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[5] = sum;

    sum = matrix[0] * vec6;
    sum += matrix[1] * vec7;
    sum += matrix[2] * vec8;
    sum += matrix[3] * vec9;
    sum += matrix[4] * vec10;
    sum += matrix[5] * vec11;
    sum += matrix[6] * vec12;
    sum += matrix[7] * vec13;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[6] = sum;

    sum = matrix[0] * vec7;
    sum += matrix[1] * vec8;
    sum += matrix[2] * vec9;
    sum += matrix[3] * vec10;
    sum += matrix[4] * vec11;
    sum += matrix[5] * vec12;
    sum += matrix[6] * vec13;
    sum += matrix[7] * vec14;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[7] = sum;

    return true;
}

bool rspMultPolef(Rsp* pRSP, s16 (*matrix)[8], s16* vectorIn, s16* vectorOut) {
    s32 sum;
    s32 vec0 = vectorIn[0];
    s32 vec1 = vectorIn[1];
    s32 vec2 = vectorIn[2];
    s32 vec3 = vectorIn[3];
    s32 vec4 = vectorIn[4];
    s32 vec5 = vectorIn[5];
    s32 vec6 = vectorIn[6];
    s32 vec7 = vectorIn[7];
    s32 vec8 = vectorIn[8];
    s32 vec9 = vectorIn[9];

    sum = matrix[0][0] * vec0;
    sum += matrix[1][0] * vec1;
    sum += matrix[9][0] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[0] = sum;

    sum = matrix[0][1] * vec0;
    sum += matrix[1][1] * vec1;
    sum += matrix[2][1] * vec2;
    sum += matrix[9][1] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[1] = sum;

    sum = matrix[0][2] * vec0;
    sum += matrix[1][2] * vec1;
    sum += matrix[2][2] * vec2;
    sum += matrix[3][2] * vec3;
    sum += matrix[9][2] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[2] = sum;

    sum = matrix[0][3] * vec0;
    sum += matrix[1][3] * vec1;
    sum += matrix[2][3] * vec2;
    sum += matrix[3][3] * vec3;
    sum += matrix[4][3] * vec4;
    sum += matrix[9][3] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[3] = sum;

    sum = matrix[0][4] * vec0;
    sum += matrix[1][4] * vec1;
    sum += matrix[2][4] * vec2;
    sum += matrix[3][4] * vec3;
    sum += matrix[4][4] * vec4;
    sum += matrix[5][4] * vec5;
    sum += matrix[9][4] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[4] = sum;

    sum = matrix[0][5] * vec0;
    sum += matrix[1][5] * vec1;
    sum += matrix[2][5] * vec2;
    sum += matrix[3][5] * vec3;
    sum += matrix[4][5] * vec4;
    sum += matrix[5][5] * vec5;
    sum += matrix[6][5] * vec6;
    sum += matrix[9][5] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[5] = sum;

    sum = matrix[0][6] * vec0;
    sum += matrix[1][6] * vec1;
    sum += matrix[2][6] * vec2;
    sum += matrix[3][6] * vec3;
    sum += matrix[4][6] * vec4;
    sum += matrix[5][6] * vec5;
    sum += matrix[6][6] * vec6;
    sum += matrix[7][6] * vec7;
    sum += matrix[9][6] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[6] = sum;

    sum = matrix[0][7] * vec0;
    sum += matrix[1][7] * vec1;
    sum += matrix[2][7] * vec2;
    sum += matrix[3][7] * vec3;
    sum += matrix[4][7] * vec4;
    sum += matrix[5][7] * vec5;
    sum += matrix[6][7] * vec6;
    sum += matrix[7][7] * vec7;
    sum += matrix[8][7] * vec8;
    sum += matrix[9][7] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[7] = sum;

    return true;
}

static bool rspLoadADPCMCoefTable1(Rsp* pRSP) {
    u32 i;
    u32 j;
    u32 nCoefIndex;

    nCoefIndex = (s32)pRSP->nAudioADPCMOffset / 2;
    for (j = 0; j < 4; j++, nCoefIndex += 16) {
        for (i = 0; i < 8; i++) {
            pRSP->anADPCMCoef[j][0][i] = pRSP->anAudioBuffer[nCoefIndex + i];
            pRSP->anADPCMCoef[j][1][i] = pRSP->anAudioBuffer[nCoefIndex + 8 + i];
        }
    }

    return true;
}

static bool rspLoadADPCMCoefTable2(Rsp* pRSP) {
    u32 i;
    u32 j;
    u32 nCoefIndex;

    nCoefIndex = (s32)pRSP->nAudioADPCMOffset / 2;
    for (j = 0; j < 4; j++, nCoefIndex += 16) {
        for (i = 0; i < 8; i++) {
            pRSP->anADPCMCoef[j][0][i] = pRSP->anAudioBuffer[nCoefIndex + i];
            pRSP->anADPCMCoef[j][1][i] = pRSP->anAudioBuffer[nCoefIndex + 8 + i];
        }
    }

    return true;
}

static inline bool rspALoadBuffer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;
    s32 nAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
        xlHeapCopy(&pRSP->anAudioBuffer[pRSP->nAudioDMEMIn[0]], pData, pRSP->nAudioCount[1]);
    }

    return true;
}

static bool rspAADPCMDec1Fast(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u8 nFlags;
    u8 ucControl;
    s8* pHeader;
    s16* pStateAddress;
    s16 anIData0;
    s16 anIData1;
    s32 pad1[4];
    s32 nDMEMOut;
    s32 nCount;
    s32 nSrcAddress;
    s32 nOptPred;
    s32 nVScale;
    int i;
    u32 dwDecodeSelect;
    s32 nLogScale;
    s16 nInput0;
    s16 nInput1;
    u32 n;
    s32 nA;
    s32 nB;
    s16 nSamp1;
    s16 nSamp2;
    s16* pTempStateAddr;
    s32 nOutput;
    s32 pad2[4];

    nFlags = (nCommandHi >> 16) & 0xFF;
    pHeader = (s8*)pRSP->anAudioBuffer + pRSP->nAudioDMEMIn[1];
    nDMEMOut = pRSP->nAudioDMEMOut[0];
    nCount = pRSP->nAudioCount[0];
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pStateAddress, nSrcAddress, NULL)) {
        return false;
    }

    if (!(nFlags & 1)) {
        pTempStateAddr = pStateAddress;
        if (nFlags & 2) {
            if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pTempStateAddr, pRSP->nAudioLoopAddress, NULL)) {
                return false;
            }
        }

        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[nDMEMOut + i] = pTempStateAddr[i];
        }
    } else {
        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[nDMEMOut + i] = 0;
        }
    }

    nDMEMOut += 16;
    if (nCount == 0) {
        for (i = 0; i < 16; i++) {
            pStateAddress[i] = pRSP->anAudioBuffer[nDMEMOut - 16 + i];
        }
        return true;
    }

    while (nCount > 0) {
        ucControl = *pHeader;
        pHeader++;
        dwDecodeSelect = (ucControl & 0xF) << 5;
        if (dwDecodeSelect == 0x00) {
            nOptPred = 0;
        } else if (dwDecodeSelect == 0x20) {
            nOptPred = 1;
        } else if (dwDecodeSelect == 0x40) {
            nOptPred = 2;
        } else if (dwDecodeSelect == 0x60) {
            nOptPred = 3;
        } else {
            nOptPred = 4;
            dwDecodeSelect = (dwDecodeSelect / 2) + ((s32)pRSP->nAudioADPCMOffset / 2);
            for (i = 0; i < 8; i++) {
                pRSP->anADPCMCoef[4][0][i] = pRSP->anAudioBuffer[dwDecodeSelect + i];
                pRSP->anADPCMCoef[4][1][i] = pRSP->anAudioBuffer[dwDecodeSelect + 8 + i];
            }
        }

        nA = pRSP->anADPCMCoef[nOptPred][0][0];
        nB = pRSP->anADPCMCoef[nOptPred][1][0];
        nSamp2 = pRSP->anAudioBuffer[nDMEMOut - 2];
        nSamp1 = pRSP->anAudioBuffer[nDMEMOut - 1];

        for (n = 0; n < 16; n += 2) {
            nLogScale = 12 - (ucControl >> 4);
            nInput0 = ((*pHeader >> 4) & 0xF) << 12;
            nInput1 = ((*pHeader >> 0) & 0xF) << 12;
            pHeader++;

            nVScale = (0x8000 >> (nLogScale - 1)) & 0xFFFF;
            if (nLogScale > 0) {
                anIData0 = (nInput0 * nVScale) >> 16;
            } else {
                anIData0 = nInput0;
            }

            nOutput = (nSamp1 * nB + (nSamp2 * nA + (anIData0 << 11))) >> 16;
            nOutput <<= 5;
            if (nOutput > 0x7FFF) {
                nOutput = 0x7FFF;
            } else if (nOutput < -0x8000) {
                nOutput = -0x8000;
            }

            nSamp2 = nSamp1;
            nSamp1 = nOutput;
            pRSP->anAudioBuffer[nDMEMOut + n] = nOutput;

            nVScale = (0x8000 >> (nLogScale - 1)) & 0xFFFF;
            if (nLogScale > 0) {
                anIData1 = (nInput1 * nVScale) >> 16;
            } else {
                anIData1 = nInput1;
            }

            nOutput = (nSamp1 * nB + (nSamp2 * nA + (anIData1 << 11))) >> 16;
            nOutput <<= 5;
            if (nOutput > 0x7FFF) {
                nOutput = 0x7FFF;
            } else if (nOutput < -0x8000) {
                nOutput = -0x8000;
            }

            nSamp2 = nSamp1;
            nSamp1 = nOutput;
            pRSP->anAudioBuffer[nDMEMOut + n + 1] = nOutput;
        }

        nDMEMOut += 16;
        nCount -= 16;
    }

    for (i = 0; i < 16; i++) {
        pStateAddress[i] = pRSP->anAudioBuffer[nDMEMOut - 16 + i];
    }

    return true;
}

static inline bool rspAClearBuffer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    memset(&pRSP->anAudioBuffer[((nCommandHi & 0xFFFF) + pRSP->nAudioMemOffset) / 2], 0, nCommandLo & 0xFFFF);
    return true;
}

static bool rspAPoleFilter1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u8 nFlags;
    u16 nScale;
    s16 anCoef[10][8];
    s16 anEntries[8];
    s16 nVTemp[8];
    s16 nTempScale;
    s16 anIData0[8];
    s16 anOData0[8];
    s16 anInputVec[10];
    s16* pStateAddress;
    s16* pDMEM16;
    s32 nDMEMIn;
    s32 nDMEMOut;
    s32 nCount;
    s32 nSrcAddress;
    int i;

    nCount = pRSP->nAudioCount[0];
    if ((int)nCount == 0) {
        return true;
    }

    for (i = 0; i < 4; i++) {
        anOData0[i] = 0;
    }
    nFlags = (nCommandHi >> 16) & 0xFF;
    nScale = nCommandHi & 0xFFFF;
    nDMEMIn = pRSP->nAudioDMEMIn[0];
    nDMEMOut = pRSP->nAudioDMEMOut[0];
    pDMEM16 = pRSP->anAudioBuffer;
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pStateAddress, nSrcAddress, NULL)) {
        return false;
    }

    pDMEM16[(s32)pRSP->nAudioScratchOffset / 2 + 0] = 0;
    pDMEM16[(s32)pRSP->nAudioScratchOffset / 2 + 1] = 0;

    if (!(nFlags & 1)) {
        for (i = 0; i < 4; i++) {
            pDMEM16[(s32)pRSP->nAudioScratchOffset / 2 + i] = pStateAddress[i];
        }
    }

    nTempScale = (nScale & 0x3FFF) << 2;
    for (i = 0; i < 8; i++) {
        anCoef[1][i] = pDMEM16[(s32)pRSP->nAudioADPCMOffset / 2 + 8 + i];
        nVTemp[i] = ((s32)anCoef[1][i] * (s32)nTempScale) >> 16;
    }

    for (i = 4; i < 8; i++) {
        anOData0[i] = pDMEM16[(s32)pRSP->nAudioScratchOffset / 2 + i - 4];
    }

    for (i = 0; i < 8; i++) {
        pDMEM16[(s32)pRSP->nAudioADPCMOffset / 2 + 8 + i] = nVTemp[i];
    }

    for (i = 0; i < 8; i++) {
        anCoef[0][i] = pDMEM16[(s32)pRSP->nAudioADPCMOffset / 2 + i];
        anEntries[i] = pDMEM16[(s32)pRSP->nAudioADPCMOffset / 2 + 8 + i];
    }

    anCoef[2][0] = 0;
    anCoef[2][1] = anEntries[0];
    anCoef[2][2] = anEntries[1];
    anCoef[2][3] = anEntries[2];
    anCoef[2][4] = anEntries[3];
    anCoef[2][5] = anEntries[4];
    anCoef[2][6] = anEntries[5];
    anCoef[2][7] = anEntries[6];
    anCoef[3][0] = 0;
    anCoef[3][1] = 0;
    anCoef[3][2] = anEntries[0];
    anCoef[3][3] = anEntries[1];
    anCoef[3][4] = anEntries[2];
    anCoef[3][5] = anEntries[3];
    anCoef[3][6] = anEntries[4];
    anCoef[3][7] = anEntries[5];
    anCoef[4][0] = 0;
    anCoef[4][1] = 0;
    anCoef[4][2] = 0;
    anCoef[4][3] = anEntries[0];
    anCoef[4][4] = anEntries[1];
    anCoef[4][5] = anEntries[2];
    anCoef[4][6] = anEntries[3];
    anCoef[4][7] = anEntries[4];
    anCoef[5][0] = 0;
    anCoef[5][1] = 0;
    anCoef[5][2] = 0;
    anCoef[5][3] = 0;
    anCoef[5][4] = anEntries[0];
    anCoef[5][5] = anEntries[1];
    anCoef[5][6] = anEntries[2];
    anCoef[5][7] = anEntries[3];
    anCoef[6][0] = 0;
    anCoef[6][1] = 0;
    anCoef[6][2] = 0;
    anCoef[6][3] = 0;
    anCoef[6][4] = 0;
    anCoef[6][5] = anEntries[0];
    anCoef[6][6] = anEntries[1];
    anCoef[6][7] = anEntries[2];
    anCoef[7][0] = 0;
    anCoef[7][1] = 0;
    anCoef[7][2] = 0;
    anCoef[7][3] = 0;
    anCoef[7][4] = 0;
    anCoef[7][5] = 0;
    anCoef[7][6] = anEntries[0];
    anCoef[7][7] = anEntries[1];
    anCoef[8][0] = 0;
    anCoef[8][1] = 0;
    anCoef[8][2] = 0;
    anCoef[8][3] = 0;
    anCoef[8][4] = 0;
    anCoef[8][5] = 0;
    anCoef[8][6] = 0;
    anCoef[8][7] = anEntries[0];

    for (i = 0; i < 8; i++) {
        anIData0[i] = pDMEM16[nDMEMIn + i];
    }

    anInputVec[9] = nScale;

    while (nCount > 0) {
        for (i = 0; i < 8; i++) {
            anCoef[9][i] = anIData0[i];
        }

        anInputVec[0] = anOData0[6];
        anInputVec[1] = anOData0[7];
        anInputVec[2] = anIData0[0];
        anInputVec[3] = anIData0[1];
        anInputVec[4] = anIData0[2];
        anInputVec[5] = anIData0[3];
        anInputVec[6] = anIData0[4];
        anInputVec[7] = anIData0[5];
        anInputVec[8] = anIData0[6];

        rspMultPolef(pRSP, anCoef, anInputVec, anOData0);

        nDMEMIn += 8;
        for (i = 0; i < 8; i++) {
            pDMEM16[nDMEMOut + i] = anOData0[i];
            anIData0[i] = pDMEM16[nDMEMIn + i];
        }

        nDMEMOut += 8;
        nCount -= 8;
    }

    for (i = 0; i < 4; i++) {
        pStateAddress[i] = pDMEM16[nDMEMOut - 4 + i];
    }

    return true;
}

static bool rspAEnvMixer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAEnvMixer1.s")

static inline bool rspAInterleave1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nLeft = (s32)((nCommandLo >> 16) + pRSP->nAudioMemOffset) / 2;
    u16 nRight = (s32)((nCommandLo & 0xFFFF) + pRSP->nAudioMemOffset) / 2;
    u32 nDMEMOut = pRSP->nAudioDMEMOut[0];
    u32 iIndex;
    u32 iIndex2;

    for (iIndex = 0, iIndex2 = 0; iIndex < pRSP->nAudioCount[0]; iIndex++, iIndex2++) {
        pRSP->anAudioBuffer[nDMEMOut + 2 * iIndex + 0] = pRSP->anAudioBuffer[nLeft + iIndex2];
        pRSP->anAudioBuffer[nDMEMOut + 2 * iIndex + 1] = pRSP->anAudioBuffer[nRight + iIndex2];
    }

    return true;
}

static bool rspAMix1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32 nCount;
    s16 inScale;
    s16* srcP;
    s16* dstP;
    s32 tmp;
    s32 inData32;
    s32 outData32;

    nCount = pRSP->nAudioCount[0];
    inScale = nCommandHi & 0xFFFF;
    srcP = &pRSP->anAudioBuffer[(s32)(((nCommandLo >> 16) & 0xFFFF) + 0x5C0) / 2];
    dstP = &pRSP->anAudioBuffer[(s32)((nCommandLo & 0xFFFF) + 0x5C0) / 2];

    for (i = 0; i < nCount; i++) {
        outData32 = dstP[i];
        inData32 = srcP[i];

        outData32 += (inData32 * inScale) >> 15;
        if (outData32 > 0x7FFF) {
            outData32 = 0x7FFF;
        } else if (outData32 < -0x7FFF) {
            outData32 = -0x7FFF;
        }
        dstP[i] = outData32;
    }

    return true;
}

static bool rspAResample1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 nSrcStep;
    s16* srcP;
    s16* dstP;
    s16 lastValue;
    u16 nCount;
    u16 i;
    s32 nCursorPos;
    s32 nExtra;
    u32 scratch;
    u8 flags;
    s16* pData;
    s32 nSrcAddress;
    s32 pad[7];

    srcP = &pRSP->anAudioBuffer[pRSP->nAudioDMEMIn[0]];
    dstP = &pRSP->anAudioBuffer[pRSP->nAudioDMEMOut[0]];
    nCount = pRSP->nAudioCount[0];
    nSrcStep = nCommandHi & 0xFFFF;
    flags = (nCommandHi >> 16) & 0xFF;
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nSrcAddress, NULL)) {
        return false;
    }

    if (flags & 1) {
        for (i = 0; i < 16; i++) {
            pData[i] = 0;
        }
    }

    if (flags & 2) {
        srcP[-8] = pData[8];
        srcP[-7] = pData[9];
        srcP[-6] = pData[10];
        srcP[-5] = pData[11];
        srcP[-4] = pData[12];
        srcP[-3] = pData[13];
        srcP[-2] = pData[14];
        srcP[-1] = pData[15];
        srcP -= pData[5] / 2;
    }

    srcP -= 4;
    srcP[0] = pData[0];
    srcP[1] = pData[1];
    srcP[2] = pData[2];
    srcP[3] = pData[3];

    nCursorPos = pData[4];
    for (i = 0; i < nCount; i++, nCursorPos += nSrcStep) {
        lastValue = srcP[nCursorPos >> 15];
        dstP[i] = lastValue + (((nCursorPos & 0x7FFF) * (srcP[(nCursorPos >> 15) + 1] - lastValue)) >> 15);
    }

    pData[4] = (nCursorPos & 0x7FFF);
    srcP += nCursorPos >> 15;

    pData[0] = srcP[0];
    pData[1] = srcP[1];
    pData[2] = srcP[2];
    pData[3] = srcP[3];

    scratch = ((srcP + 4 - &pRSP->anAudioBuffer[pRSP->nAudioDMEMIn[0]]) & 7) << 1;
    if (scratch != 0) {
        scratch -= 16;
    }
    pData[5] = scratch;

    pData[8] = srcP[4];
    pData[9] = srcP[5];
    pData[10] = srcP[6];
    pData[11] = srcP[7];
    pData[12] = srcP[8];
    pData[13] = srcP[9];
    pData[14] = srcP[10];
    pData[15] = srcP[11];

    return true;
}

static inline bool rspASaveBuffer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 nSize = pRSP->nAudioCount[0];
    u32* pData;
    s32 nAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, &nSize)) {
        xlHeapCopy(pData, &pRSP->anAudioBuffer[pRSP->nAudioDMEMOut[0]], nSize * sizeof(s16));
    }

    return true;
}

static inline bool rspASegment1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->anAudioBaseSegment[(nCommandLo >> 24) & 0xF] = nCommandLo & 0xFFFFFF;
    return true;
}

static bool rspASetBuffer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nDMEMIn = nCommandHi & 0xFFFF;
    u16 nDMEMOut = (nCommandLo >> 16) & 0xFFFF;
    u16 nCount = nCommandLo & 0xFFFF;

    if ((nCommandHi >> 16) & 8) {
        pRSP->nAudioDMauxR[1] = nCount + pRSP->nAudioMemOffset;
        pRSP->nAudioDMauxR[0] = (u16)((s32)pRSP->nAudioDMauxR[1] / 2);
        pRSP->anAudioBuffer[0x1B7] = (s16)pRSP->nAudioDMauxR[1];
        pRSP->nAudioDMOutR[1] = nDMEMIn + pRSP->nAudioMemOffset;
        pRSP->nAudioDMOutR[0] = (u16)((s32)pRSP->nAudioDMOutR[1] / 2);
        pRSP->anAudioBuffer[0x1B5] = (s16)pRSP->nAudioDMOutR[1];
        pRSP->nAudioDMauxL[1] = nDMEMOut + pRSP->nAudioMemOffset;
        pRSP->nAudioDMauxL[0] = (u16)((s32)pRSP->nAudioDMauxL[1] / 2);
        pRSP->anAudioBuffer[0x1B6] = (s16)pRSP->nAudioDMauxL[1];
    } else {
        pRSP->nAudioCount[1] = nCount;
        pRSP->nAudioCount[0] = (u16)((s32)pRSP->nAudioCount[1] / 2);
        pRSP->anAudioBuffer[0x1B2] = (s16)pRSP->nAudioCount[1];
        pRSP->nAudioDMEMIn[1] = nDMEMIn + pRSP->nAudioMemOffset;
        pRSP->nAudioDMEMIn[0] = (u16)((s32)pRSP->nAudioDMEMIn[1] / 2);
        pRSP->anAudioBuffer[0x1B0] = (s16)pRSP->nAudioDMEMIn[1];
        pRSP->nAudioDMEMOut[1] = nDMEMOut + pRSP->nAudioMemOffset;
        pRSP->nAudioDMEMOut[0] = (u16)((s32)pRSP->nAudioDMEMOut[1] / 2);
        pRSP->anAudioBuffer[0x1B1] = (s16)pRSP->nAudioDMEMOut[1];
    }

    return true;
}

static bool rspASetVolume1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nFlags = (nCommandHi >> 16) & 0xFF;
    u16 v = nCommandHi & 0xFFFF;
    u16 t = (nCommandLo >> 16) & 0xFFFF;
    u16 r = nCommandLo & 0xFFFF;

    if (nFlags & 8) {
        pRSP->anAudioBuffer[0x1BE] = v;
        pRSP->anAudioBuffer[0x1BF] = r;
    } else if (nFlags & 4) {
        if (nFlags & 2) {
            pRSP->anAudioBuffer[0x1B3] = v;
        } else {
            pRSP->anAudioBuffer[0x1B4] = v;
        }
    } else {
        if (nFlags & 2) {
            pRSP->anAudioBuffer[0x1B8] = v;
            pRSP->anAudioBuffer[0x1B9] = t;
            pRSP->anAudioBuffer[0x1BA] = r;
        } else {
            pRSP->anAudioBuffer[0x1BB] = v;
            pRSP->anAudioBuffer[0x1BC] = t;
            pRSP->anAudioBuffer[0x1BD] = r;
        }
    }

    return true;
}

static inline bool rspASetLoop1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->nAudioLoopAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    return true;
}

static inline bool rspADMEMMove1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 nDMEMOut = ((nCommandHi & 0xFFFF) + pRSP->nAudioMemOffset) / 2;
    u16 nCount = nCommandLo & 0xFFFF;
    u16 nDMEMIn = (s32)((nCommandLo >> 16) + pRSP->nAudioMemOffset) / 2;

    xlHeapCopy(&pRSP->anAudioBuffer[nDMEMIn], &pRSP->anAudioBuffer[nDMEMOut], nCount);
    return true;
}

static inline bool rspALoadADPCM1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;
    u32 nCount = nCommandHi & 0xFFFFFF;
    s32 nAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
        if (xlHeapCopy(&pRSP->anAudioBuffer[pRSP->nAudioADPCMOffset / 2], pData, nCount)) {
            rspLoadADPCMCoefTable1(pRSP);
        }
    }

    return true;
}

static bool rspParseABI(Rsp* pRSP, RspTask* pTask) {
    u8* pFUCode;
    u32 nCheckSum;
    s32 pad[3];

    if (!(pRSP->eTypeAudioUCode == RUT_ABI1 || pRSP->eTypeAudioUCode == RUT_ABI2 ||
          pRSP->eTypeAudioUCode == RUT_UNKNOWN)) {
        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pFUCode, pTask->nOffsetCode, NULL)) {
            return false;
        }

        nCheckSum = 0;
        nCheckSum += pFUCode[0];
        nCheckSum += pFUCode[1];
        nCheckSum += pFUCode[2];
        nCheckSum += pFUCode[3];
        nCheckSum += pFUCode[4];
        nCheckSum += pFUCode[5];
        nCheckSum += pFUCode[6];
        nCheckSum += pFUCode[7];

        switch (nCheckSum) {
            case 0x171:
                pRSP->eTypeAudioUCode = RUT_ABI1;
                pRSP->nAudioMemOffset = 0x5C0;
                pRSP->nAudioADPCMOffset = 0x4C0;
                pRSP->nAudioParBase = 0x360;
                pRSP->nAudioScratchOffset = 0xF90;
                rspInitAudioDMEM1(pRSP);
                break;
            case 0x1F4:
                pRSP->eTypeAudioUCode = RUT_ABI2;
                pRSP->nAudioMemOffset = 0x3B0;
                pRSP->nAudioADPCMOffset = 0x330;
                pRSP->nAudioParBase = 0;
                pRSP->nAudioScratchOffset = 0xFB0;
                rspInitAudioDMEM2(pRSP);
                break;
            case 0x151:
                pRSP->eTypeAudioUCode = RUT_ABI3;
                pRSP->nAudioMemOffset = 0x450;
                pRSP->nAudioADPCMOffset = 0x3D0;
                pRSP->nAudioParBase = 0x330;
                pRSP->nAudioScratchOffset = 0xFA0;
                rspInitAudioDMEM3(pRSP);
                break;
            case 0x131:
                pRSP->eTypeAudioUCode = RUT_ABI4;
                pRSP->nAudioMemOffset = 0x450;
                pRSP->nAudioADPCMOffset = 0x3C0;
                pRSP->nAudioParBase = 0x320;
                pRSP->nAudioScratchOffset = 0xF90;
                rspInitAudioDMEM4(pRSP);
                break;
            default:
                pRSP->eTypeAudioUCode = RUT_UNKNOWN;
                break;
        }
    }

    switch (pRSP->eTypeAudioUCode) {
        case RUT_ABI1:
            rspParseABI1(pRSP, pTask);
            break;
        case RUT_ABI2:
            rspParseABI2(pRSP, pTask);
            break;
        case RUT_ABI3:
            rspParseABI3(pRSP, pTask);
            break;
        case RUT_ABI4:
            rspParseABI4(pRSP, pTask);
            break;
        default:
            break;
    }

    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI1.s")
#else
static bool rspParseABI1(Rsp* pRSP, RspTask* pTask) {
    u32 nCommandLo;
    u32 nCommandHi;
    u32* pABI32;
    u32* pABILast32;
    u32 nSize;

    nSize = pTask->nLengthMBI & 0x7FFFFF;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pABI32, pTask->nOffsetMBI, NULL)) {
        return false;
    }
    pABILast32 = pABI32 + (nSize >> 2);

    if (nFirstTime_2148) {
        nFirstTime_2148 = false;
    }

    while (pABI32 < pABILast32) {
        nCommandHi = pABI32[0];
        nCommandLo = pABI32[1];
        pABI32 += 2;
        switch (nCommandHi >> 24) {
            case 0:
                break;
            case 1:
                rspAADPCMDec1Fast(pRSP, nCommandLo, nCommandHi);
                break;
            case 2:
                rspAClearBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 4:
                rspALoadBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 6:
                rspASaveBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 7:
                rspASegment1(pRSP, nCommandLo, nCommandHi);
                break;
            case 8:
                rspASetBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 10:
                rspADMEMMove1(pRSP, nCommandLo, nCommandHi);
                break;
            case 11:
                rspALoadADPCM1(pRSP, nCommandLo, nCommandHi);
                break;
            case 12:
                rspAMix1(pRSP, nCommandLo, nCommandHi);
                break;
            case 13:
                rspAInterleave1(pRSP, nCommandLo, nCommandHi);
                break;
            case 15:
                rspASetLoop1(pRSP, nCommandLo, nCommandHi);
                break;
            case 3:
                rspAEnvMixer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 5:
                rspAResample1(pRSP, nCommandLo, nCommandHi);
                break;
            case 9:
                rspASetVolume1(pRSP, nCommandLo, nCommandHi);
                break;
            case 14:
                rspAPoleFilter1(pRSP, nCommandLo, nCommandHi);
                break;
            default:
                return false;
        }
    }

    return true;
}
#endif

static bool rspInitAudioDMEM2(Rsp* pRSP) {
    pRSP->anAudioBuffer = pRSP->pDMEM;

    pRSP->anAudioBuffer[0x000] = 0x0000;
    pRSP->anAudioBuffer[0x001] = 0x0001;
    pRSP->anAudioBuffer[0x002] = 0x0002;
    pRSP->anAudioBuffer[0x003] = 0xFFFF;
    pRSP->anAudioBuffer[0x004] = 0x0020;
    pRSP->anAudioBuffer[0x005] = 0x0800;
    pRSP->anAudioBuffer[0x006] = 0x7FFF;
    pRSP->anAudioBuffer[0x007] = 0x4000;

    pRSP->anAudioBuffer[0x020] = 0xF000;
    pRSP->anAudioBuffer[0x021] = 0x0F00;
    pRSP->anAudioBuffer[0x022] = 0x00F0;
    pRSP->anAudioBuffer[0x023] = 0x000F;
    pRSP->anAudioBuffer[0x024] = 0x0001;
    pRSP->anAudioBuffer[0x025] = 0x0010;
    pRSP->anAudioBuffer[0x026] = 0x0100;
    pRSP->anAudioBuffer[0x027] = 0x1000;
    pRSP->anAudioBuffer[0x028] = 0xC000;
    pRSP->anAudioBuffer[0x029] = 0x3000;
    pRSP->anAudioBuffer[0x02A] = 0x0C00;
    pRSP->anAudioBuffer[0x02B] = 0x0300;
    pRSP->anAudioBuffer[0x02C] = 0x0001;
    pRSP->anAudioBuffer[0x02D] = 0x0004;
    pRSP->anAudioBuffer[0x02E] = 0x0010;
    pRSP->anAudioBuffer[0x02F] = 0x0040;
    pRSP->anAudioBuffer[0x030] = 0x0002;
    pRSP->anAudioBuffer[0x031] = 0x0004;
    pRSP->anAudioBuffer[0x032] = 0x0006;
    pRSP->anAudioBuffer[0x033] = 0x0008;
    pRSP->anAudioBuffer[0x034] = 0x000A;
    pRSP->anAudioBuffer[0x035] = 0x000C;
    pRSP->anAudioBuffer[0x036] = 0x000E;
    pRSP->anAudioBuffer[0x037] = 0x0010;
    pRSP->anAudioBuffer[0x038] = 0x0001;
    pRSP->anAudioBuffer[0x039] = 0x0001;
    pRSP->anAudioBuffer[0x03A] = 0x0001;
    pRSP->anAudioBuffer[0x03B] = 0x0001;
    pRSP->anAudioBuffer[0x03C] = 0x0001;
    pRSP->anAudioBuffer[0x03D] = 0x0001;
    pRSP->anAudioBuffer[0x03E] = 0x0001;
    pRSP->anAudioBuffer[0x03F] = 0x0001;
    pRSP->anAudioBuffer[0x040] = 0x0000;
    pRSP->anAudioBuffer[0x041] = 0x0001;
    pRSP->anAudioBuffer[0x042] = 0x0002;
    pRSP->anAudioBuffer[0x043] = 0x0004;
    pRSP->anAudioBuffer[0x044] = 0x0008;
    pRSP->anAudioBuffer[0x045] = 0x0010;
    pRSP->anAudioBuffer[0x046] = 0x0100;
    pRSP->anAudioBuffer[0x047] = 0x0200;
    pRSP->anAudioBuffer[0x048] = 0x0001;
    pRSP->anAudioBuffer[0x049] = 0x0000;
    pRSP->anAudioBuffer[0x04A] = 0x0000;
    pRSP->anAudioBuffer[0x04B] = 0x0000;
    pRSP->anAudioBuffer[0x04C] = 0x0001;
    pRSP->anAudioBuffer[0x04D] = 0x0000;
    pRSP->anAudioBuffer[0x04E] = 0x0000;
    pRSP->anAudioBuffer[0x04F] = 0x0000;
    pRSP->anAudioBuffer[0x050] = 0x0000;
    pRSP->anAudioBuffer[0x051] = 0x0001;
    pRSP->anAudioBuffer[0x052] = 0x0000;
    pRSP->anAudioBuffer[0x053] = 0x0000;
    pRSP->anAudioBuffer[0x054] = 0x0000;
    pRSP->anAudioBuffer[0x055] = 0x0001;
    pRSP->anAudioBuffer[0x056] = 0x0000;
    pRSP->anAudioBuffer[0x057] = 0x0000;
    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0001;
    pRSP->anAudioBuffer[0x05B] = 0x0000;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0001;
    pRSP->anAudioBuffer[0x05F] = 0x0000;
    pRSP->anAudioBuffer[0x060] = 0x0000;
    pRSP->anAudioBuffer[0x061] = 0x0000;
    pRSP->anAudioBuffer[0x062] = 0x0000;
    pRSP->anAudioBuffer[0x063] = 0x0001;
    pRSP->anAudioBuffer[0x064] = 0x0000;
    pRSP->anAudioBuffer[0x065] = 0x0000;
    pRSP->anAudioBuffer[0x066] = 0x0000;
    pRSP->anAudioBuffer[0x067] = 0x0001;
    pRSP->anAudioBuffer[0x068] = 0x2000;
    pRSP->anAudioBuffer[0x069] = 0x4000;
    pRSP->anAudioBuffer[0x06A] = 0x6000;
    pRSP->anAudioBuffer[0x06B] = 0x8000;
    pRSP->anAudioBuffer[0x06C] = 0xA000;
    pRSP->anAudioBuffer[0x06D] = 0xC000;
    pRSP->anAudioBuffer[0x06E] = 0xE000;
    pRSP->anAudioBuffer[0x06F] = 0xFFFF;
    pRSP->anAudioBuffer[0x070] = 0x0C39;
    pRSP->anAudioBuffer[0x071] = 0x66AD;
    pRSP->anAudioBuffer[0x072] = 0x0D46;
    pRSP->anAudioBuffer[0x073] = 0xFFDF;
    pRSP->anAudioBuffer[0x074] = 0x0B39;
    pRSP->anAudioBuffer[0x075] = 0x6696;
    pRSP->anAudioBuffer[0x076] = 0x0E5F;
    pRSP->anAudioBuffer[0x077] = 0xFFD8;
    pRSP->anAudioBuffer[0x078] = 0x0A44;
    pRSP->anAudioBuffer[0x079] = 0x6669;
    pRSP->anAudioBuffer[0x07A] = 0x0F83;
    pRSP->anAudioBuffer[0x07B] = 0xFFD0;
    pRSP->anAudioBuffer[0x07C] = 0x095A;
    pRSP->anAudioBuffer[0x07D] = 0x6626;
    pRSP->anAudioBuffer[0x07E] = 0x10B4;
    pRSP->anAudioBuffer[0x07F] = 0xFFC8;
    pRSP->anAudioBuffer[0x080] = 0x087D;
    pRSP->anAudioBuffer[0x081] = 0x65CD;
    pRSP->anAudioBuffer[0x082] = 0x11F0;
    pRSP->anAudioBuffer[0x083] = 0xFFBF;
    pRSP->anAudioBuffer[0x084] = 0x07AB;
    pRSP->anAudioBuffer[0x085] = 0x655E;
    pRSP->anAudioBuffer[0x086] = 0x1338;
    pRSP->anAudioBuffer[0x087] = 0xFFB6;
    pRSP->anAudioBuffer[0x088] = 0x06E4;
    pRSP->anAudioBuffer[0x089] = 0x64D9;
    pRSP->anAudioBuffer[0x08A] = 0x148C;
    pRSP->anAudioBuffer[0x08B] = 0xFFAC;
    pRSP->anAudioBuffer[0x08C] = 0x0628;
    pRSP->anAudioBuffer[0x08D] = 0x643F;
    pRSP->anAudioBuffer[0x08E] = 0x15EB;
    pRSP->anAudioBuffer[0x08F] = 0xFFA1;
    pRSP->anAudioBuffer[0x090] = 0x0577;
    pRSP->anAudioBuffer[0x091] = 0x638F;
    pRSP->anAudioBuffer[0x092] = 0x1756;
    pRSP->anAudioBuffer[0x093] = 0xFF96;
    pRSP->anAudioBuffer[0x094] = 0x04D1;
    pRSP->anAudioBuffer[0x095] = 0x62CB;
    pRSP->anAudioBuffer[0x096] = 0x18CB;
    pRSP->anAudioBuffer[0x097] = 0xFF8A;
    pRSP->anAudioBuffer[0x098] = 0x0435;
    pRSP->anAudioBuffer[0x099] = 0x61F3;
    pRSP->anAudioBuffer[0x09A] = 0x1A4C;
    pRSP->anAudioBuffer[0x09B] = 0xFF7E;
    pRSP->anAudioBuffer[0x09C] = 0x03A4;
    pRSP->anAudioBuffer[0x09D] = 0x6106;
    pRSP->anAudioBuffer[0x09E] = 0x1BD7;
    pRSP->anAudioBuffer[0x09F] = 0xFF71;
    pRSP->anAudioBuffer[0x0A0] = 0x031C;
    pRSP->anAudioBuffer[0x0A1] = 0x6007;
    pRSP->anAudioBuffer[0x0A2] = 0x1D6C;
    pRSP->anAudioBuffer[0x0A3] = 0xFF64;
    pRSP->anAudioBuffer[0x0A4] = 0x029F;
    pRSP->anAudioBuffer[0x0A5] = 0x5EF5;
    pRSP->anAudioBuffer[0x0A6] = 0x1F0B;
    pRSP->anAudioBuffer[0x0A7] = 0xFF56;
    pRSP->anAudioBuffer[0x0A8] = 0x022A;
    pRSP->anAudioBuffer[0x0A9] = 0x5DD0;
    pRSP->anAudioBuffer[0x0AA] = 0x20B3;
    pRSP->anAudioBuffer[0x0AB] = 0xFF48;
    pRSP->anAudioBuffer[0x0AC] = 0x01BE;
    pRSP->anAudioBuffer[0x0AD] = 0x5C9A;
    pRSP->anAudioBuffer[0x0AE] = 0x2264;
    pRSP->anAudioBuffer[0x0AF] = 0xFF3A;
    pRSP->anAudioBuffer[0x0B0] = 0x015B;
    pRSP->anAudioBuffer[0x0B1] = 0x5B53;
    pRSP->anAudioBuffer[0x0B2] = 0x241E;
    pRSP->anAudioBuffer[0x0B3] = 0xFF2C;
    pRSP->anAudioBuffer[0x0B4] = 0x0101;
    pRSP->anAudioBuffer[0x0B5] = 0x59FC;
    pRSP->anAudioBuffer[0x0B6] = 0x25E0;
    pRSP->anAudioBuffer[0x0B7] = 0xFF1E;
    pRSP->anAudioBuffer[0x0B8] = 0x00AE;
    pRSP->anAudioBuffer[0x0B9] = 0x5896;
    pRSP->anAudioBuffer[0x0BA] = 0x27A9;
    pRSP->anAudioBuffer[0x0BB] = 0xFF10;
    pRSP->anAudioBuffer[0x0BC] = 0x0063;
    pRSP->anAudioBuffer[0x0BD] = 0x5720;
    pRSP->anAudioBuffer[0x0BE] = 0x297A;
    pRSP->anAudioBuffer[0x0BF] = 0xFF02;
    pRSP->anAudioBuffer[0x0C0] = 0x001F;
    pRSP->anAudioBuffer[0x0C1] = 0x559D;
    pRSP->anAudioBuffer[0x0C2] = 0x2B50;
    pRSP->anAudioBuffer[0x0C3] = 0xFEF4;
    pRSP->anAudioBuffer[0x0C4] = 0xFFE2;
    pRSP->anAudioBuffer[0x0C5] = 0x540D;
    pRSP->anAudioBuffer[0x0C6] = 0x2D2C;
    pRSP->anAudioBuffer[0x0C7] = 0xFEE8;
    pRSP->anAudioBuffer[0x0C8] = 0xFFAC;
    pRSP->anAudioBuffer[0x0C9] = 0x5270;
    pRSP->anAudioBuffer[0x0CA] = 0x2F0D;
    pRSP->anAudioBuffer[0x0CB] = 0xFEDB;
    pRSP->anAudioBuffer[0x0CC] = 0xFF7C;
    pRSP->anAudioBuffer[0x0CD] = 0x50C7;
    pRSP->anAudioBuffer[0x0CE] = 0x30F3;
    pRSP->anAudioBuffer[0x0CF] = 0xFED0;
    pRSP->anAudioBuffer[0x0D0] = 0xFF53;
    pRSP->anAudioBuffer[0x0D1] = 0x4F14;
    pRSP->anAudioBuffer[0x0D2] = 0x32DC;
    pRSP->anAudioBuffer[0x0D3] = 0xFEC6;
    pRSP->anAudioBuffer[0x0D4] = 0xFF2E;
    pRSP->anAudioBuffer[0x0D5] = 0x4D57;
    pRSP->anAudioBuffer[0x0D6] = 0x34C8;
    pRSP->anAudioBuffer[0x0D7] = 0xFEBD;
    pRSP->anAudioBuffer[0x0D8] = 0xFF0F;
    pRSP->anAudioBuffer[0x0D9] = 0x4B91;
    pRSP->anAudioBuffer[0x0DA] = 0x36B6;
    pRSP->anAudioBuffer[0x0DB] = 0xFEB6;
    pRSP->anAudioBuffer[0x0DC] = 0xFEF5;
    pRSP->anAudioBuffer[0x0DD] = 0x49C2;
    pRSP->anAudioBuffer[0x0DE] = 0x38A5;
    pRSP->anAudioBuffer[0x0DF] = 0xFEB0;
    pRSP->anAudioBuffer[0x0E0] = 0xFEDF;
    pRSP->anAudioBuffer[0x0E1] = 0x47ED;
    pRSP->anAudioBuffer[0x0E2] = 0x3A95;
    pRSP->anAudioBuffer[0x0E3] = 0xFEAC;
    pRSP->anAudioBuffer[0x0E4] = 0xFECE;
    pRSP->anAudioBuffer[0x0E5] = 0x4611;
    pRSP->anAudioBuffer[0x0E6] = 0x3C85;
    pRSP->anAudioBuffer[0x0E7] = 0xFEAB;
    pRSP->anAudioBuffer[0x0E8] = 0xFEC0;
    pRSP->anAudioBuffer[0x0E9] = 0x4430;
    pRSP->anAudioBuffer[0x0EA] = 0x3E74;
    pRSP->anAudioBuffer[0x0EB] = 0xFEAC;
    pRSP->anAudioBuffer[0x0EC] = 0xFEB6;
    pRSP->anAudioBuffer[0x0ED] = 0x424A;
    pRSP->anAudioBuffer[0x0EE] = 0x4060;
    pRSP->anAudioBuffer[0x0EF] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F0] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F1] = 0x4060;
    pRSP->anAudioBuffer[0x0F2] = 0x424A;
    pRSP->anAudioBuffer[0x0F3] = 0xFEB6;
    pRSP->anAudioBuffer[0x0F4] = 0xFEAC;
    pRSP->anAudioBuffer[0x0F5] = 0x3E74;
    pRSP->anAudioBuffer[0x0F6] = 0x4430;
    pRSP->anAudioBuffer[0x0F7] = 0xFEC0;
    pRSP->anAudioBuffer[0x0F8] = 0xFEAB;
    pRSP->anAudioBuffer[0x0F9] = 0x3C85;
    pRSP->anAudioBuffer[0x0FA] = 0x4611;
    pRSP->anAudioBuffer[0x0FB] = 0xFECE;
    pRSP->anAudioBuffer[0x0FC] = 0xFEAC;
    pRSP->anAudioBuffer[0x0FD] = 0x3A95;
    pRSP->anAudioBuffer[0x0FE] = 0x47ED;
    pRSP->anAudioBuffer[0x0FF] = 0xFEDF;
    pRSP->anAudioBuffer[0x100] = 0xFEB0;
    pRSP->anAudioBuffer[0x101] = 0x38A5;
    pRSP->anAudioBuffer[0x102] = 0x49C2;
    pRSP->anAudioBuffer[0x103] = 0xFEF5;
    pRSP->anAudioBuffer[0x104] = 0xFEB6;
    pRSP->anAudioBuffer[0x105] = 0x36B6;
    pRSP->anAudioBuffer[0x106] = 0x4B91;
    pRSP->anAudioBuffer[0x107] = 0xFF0F;
    pRSP->anAudioBuffer[0x108] = 0xFEBD;
    pRSP->anAudioBuffer[0x109] = 0x34C8;
    pRSP->anAudioBuffer[0x10A] = 0x4D57;
    pRSP->anAudioBuffer[0x10B] = 0xFF2E;
    pRSP->anAudioBuffer[0x10C] = 0xFEC6;
    pRSP->anAudioBuffer[0x10D] = 0x32DC;
    pRSP->anAudioBuffer[0x10E] = 0x4F14;
    pRSP->anAudioBuffer[0x10F] = 0xFF53;
    pRSP->anAudioBuffer[0x110] = 0xFED0;
    pRSP->anAudioBuffer[0x111] = 0x30F3;
    pRSP->anAudioBuffer[0x112] = 0x50C7;
    pRSP->anAudioBuffer[0x113] = 0xFF7C;
    pRSP->anAudioBuffer[0x114] = 0xFEDB;
    pRSP->anAudioBuffer[0x115] = 0x2F0D;
    pRSP->anAudioBuffer[0x116] = 0x5270;
    pRSP->anAudioBuffer[0x117] = 0xFFAC;
    pRSP->anAudioBuffer[0x118] = 0xFEE8;
    pRSP->anAudioBuffer[0x119] = 0x2D2C;
    pRSP->anAudioBuffer[0x11A] = 0x540D;
    pRSP->anAudioBuffer[0x11B] = 0xFFE2;
    pRSP->anAudioBuffer[0x11C] = 0xFEF4;
    pRSP->anAudioBuffer[0x11D] = 0x2B50;
    pRSP->anAudioBuffer[0x11E] = 0x559D;
    pRSP->anAudioBuffer[0x11F] = 0x001F;
    pRSP->anAudioBuffer[0x120] = 0xFF02;
    pRSP->anAudioBuffer[0x121] = 0x297A;
    pRSP->anAudioBuffer[0x122] = 0x5720;
    pRSP->anAudioBuffer[0x123] = 0x0063;
    pRSP->anAudioBuffer[0x124] = 0xFF10;
    pRSP->anAudioBuffer[0x125] = 0x27A9;
    pRSP->anAudioBuffer[0x126] = 0x5896;
    pRSP->anAudioBuffer[0x127] = 0x00AE;
    pRSP->anAudioBuffer[0x128] = 0xFF1E;
    pRSP->anAudioBuffer[0x129] = 0x25E0;
    pRSP->anAudioBuffer[0x12A] = 0x59FC;
    pRSP->anAudioBuffer[0x12B] = 0x0101;
    pRSP->anAudioBuffer[0x12C] = 0xFF2C;
    pRSP->anAudioBuffer[0x12D] = 0x241E;
    pRSP->anAudioBuffer[0x12E] = 0x5B53;
    pRSP->anAudioBuffer[0x12F] = 0x015B;
    pRSP->anAudioBuffer[0x130] = 0xFF3A;
    pRSP->anAudioBuffer[0x131] = 0x2264;
    pRSP->anAudioBuffer[0x132] = 0x5C9A;
    pRSP->anAudioBuffer[0x133] = 0x01BE;
    pRSP->anAudioBuffer[0x134] = 0xFF48;
    pRSP->anAudioBuffer[0x135] = 0x20B3;
    pRSP->anAudioBuffer[0x136] = 0x5DD0;
    pRSP->anAudioBuffer[0x137] = 0x022A;
    pRSP->anAudioBuffer[0x138] = 0xFF56;
    pRSP->anAudioBuffer[0x139] = 0x1F0B;
    pRSP->anAudioBuffer[0x13A] = 0x5EF5;
    pRSP->anAudioBuffer[0x13B] = 0x029F;
    pRSP->anAudioBuffer[0x13C] = 0xFF64;
    pRSP->anAudioBuffer[0x13D] = 0x1D6C;
    pRSP->anAudioBuffer[0x13E] = 0x6007;
    pRSP->anAudioBuffer[0x13F] = 0x031C;
    pRSP->anAudioBuffer[0x140] = 0xFF71;
    pRSP->anAudioBuffer[0x141] = 0x1BD7;
    pRSP->anAudioBuffer[0x142] = 0x6106;
    pRSP->anAudioBuffer[0x143] = 0x03A4;
    pRSP->anAudioBuffer[0x144] = 0xFF7E;
    pRSP->anAudioBuffer[0x145] = 0x1A4C;
    pRSP->anAudioBuffer[0x146] = 0x61F3;
    pRSP->anAudioBuffer[0x147] = 0x0435;
    pRSP->anAudioBuffer[0x148] = 0xFF8A;
    pRSP->anAudioBuffer[0x149] = 0x18CB;
    pRSP->anAudioBuffer[0x14A] = 0x62CB;
    pRSP->anAudioBuffer[0x14B] = 0x04D1;
    pRSP->anAudioBuffer[0x14C] = 0xFF96;
    pRSP->anAudioBuffer[0x14D] = 0x1756;
    pRSP->anAudioBuffer[0x14E] = 0x638F;
    pRSP->anAudioBuffer[0x14F] = 0x0577;
    pRSP->anAudioBuffer[0x150] = 0xFFA1;
    pRSP->anAudioBuffer[0x151] = 0x15EB;
    pRSP->anAudioBuffer[0x152] = 0x643F;
    pRSP->anAudioBuffer[0x153] = 0x0628;
    pRSP->anAudioBuffer[0x154] = 0xFFAC;
    pRSP->anAudioBuffer[0x155] = 0x148C;
    pRSP->anAudioBuffer[0x156] = 0x64D9;
    pRSP->anAudioBuffer[0x157] = 0x06E4;
    pRSP->anAudioBuffer[0x158] = 0xFFB6;
    pRSP->anAudioBuffer[0x159] = 0x1338;
    pRSP->anAudioBuffer[0x15A] = 0x655E;
    pRSP->anAudioBuffer[0x15B] = 0x07AB;
    pRSP->anAudioBuffer[0x15C] = 0xFFBF;
    pRSP->anAudioBuffer[0x15D] = 0x11F0;
    pRSP->anAudioBuffer[0x15E] = 0x65CD;
    pRSP->anAudioBuffer[0x15F] = 0x087D;
    pRSP->anAudioBuffer[0x160] = 0xFFC8;
    pRSP->anAudioBuffer[0x161] = 0x10B4;
    pRSP->anAudioBuffer[0x162] = 0x6626;
    pRSP->anAudioBuffer[0x163] = 0x095A;
    pRSP->anAudioBuffer[0x164] = 0xFFD0;
    pRSP->anAudioBuffer[0x165] = 0x0F83;
    pRSP->anAudioBuffer[0x166] = 0x6669;
    pRSP->anAudioBuffer[0x167] = 0x0A44;
    pRSP->anAudioBuffer[0x168] = 0xFFD8;
    pRSP->anAudioBuffer[0x169] = 0x0E5F;
    pRSP->anAudioBuffer[0x16A] = 0x6696;
    pRSP->anAudioBuffer[0x16B] = 0x0B39;
    pRSP->anAudioBuffer[0x16C] = 0xFFDF;
    pRSP->anAudioBuffer[0x16D] = 0x0D46;
    pRSP->anAudioBuffer[0x16E] = 0x66AD;
    pRSP->anAudioBuffer[0x16F] = 0x0C39;

    return true;
}

static bool rspAADPCMDec2Fast(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u8 nFlags;
    u8 ucControl;
    s8* pHeader;
    s16* pStateAddress;
    s32 pad1[3];
    s16 anIData0;
    s32 nDMEMOut;
    s32 nCount;
    s32 nSrcAddress;
    s32 nOptPred;
    s32 nLogScale;
    s32 nVScale;
    int i;
    u32 dwDecodeSelect;
    u32 n;
    s32 nA;
    s32 nB;
    s16 nSamp1;
    s16 nSamp2;
    s16* pTempStateAddr;
    s16 nibble[4];
    s32 nOutput;
    s32 pad2[3];

    nFlags = (nCommandHi >> 16) & 0xFF;
    pHeader = (s8*)pRSP->anAudioBuffer + pRSP->nAudioDMEMIn[1];
    nDMEMOut = pRSP->nAudioDMEMOut[0];
    nCount = pRSP->nAudioCount[0];
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pStateAddress, nSrcAddress, NULL)) {
        return false;
    }

    if (!(nFlags & 1)) {
        pTempStateAddr = pStateAddress;
        if (nFlags & 2) {
            if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pTempStateAddr, pRSP->nAudioLoopAddress, NULL)) {
                return false;
            }
        }

        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[nDMEMOut + i] = pTempStateAddr[i];
        }
    } else {
        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[nDMEMOut + i] = 0;
        }
    }

    nDMEMOut += 16;
    if (nCount == 0) {
        for (i = 0; i < 16; i++) {
            pStateAddress[i] = pRSP->anAudioBuffer[nDMEMOut - 16 + i];
        }
        return true;
    }

    while (nCount > 0) {
        ucControl = *pHeader;
        pHeader++;
        dwDecodeSelect = (ucControl & 0xF) << 5;
        if (dwDecodeSelect == 0x00) {
            nOptPred = 0;
        } else if (dwDecodeSelect == 0x20) {
            nOptPred = 1;
        } else if (dwDecodeSelect == 0x40) {
            nOptPred = 2;
        } else if (dwDecodeSelect == 0x60) {
            nOptPred = 3;
        } else {
            nOptPred = 4;
            dwDecodeSelect = (dwDecodeSelect / 2) + ((s32)pRSP->nAudioADPCMOffset / 2);
            for (i = 0; i < 8; i++) {
                pRSP->anADPCMCoef[4][0][i] = pRSP->anAudioBuffer[dwDecodeSelect + i];
                pRSP->anADPCMCoef[4][1][i] = pRSP->anAudioBuffer[dwDecodeSelect + 8 + i];
            }
        }

        nA = pRSP->anADPCMCoef[nOptPred][0][0];
        nB = pRSP->anADPCMCoef[nOptPred][1][0];
        nSamp2 = pRSP->anAudioBuffer[nDMEMOut - 2];
        nSamp1 = pRSP->anAudioBuffer[nDMEMOut - 1];

        for (n = 0; n < 16; n += 4) {
            nibble[0] = ((*pHeader >> 6) & 3) << 14;
            nibble[1] = ((*pHeader >> 4) & 3) << 14;
            nibble[2] = ((*pHeader >> 2) & 3) << 14;
            nibble[3] = ((*pHeader >> 0) & 3) << 14;
            pHeader++;

            for (i = 0; i < 4; i++) {
                nLogScale = 14 - (ucControl >> 4);
                nVScale = nLogScale == 0 ? 0x8000 : (0x8000 >> (nLogScale - 1)) & 0xFFFF;
                if (nLogScale > 0) {
                    anIData0 = (nibble[i] * nVScale) >> 16;
                } else {
                    anIData0 = nibble[i];
                }

                nOutput = (nSamp1 * nB + (nSamp2 * nA + (anIData0 << 11))) >> 16;
                nOutput <<= 5;
                if (nOutput > 0x7FFF) {
                    nOutput = 0x7FFF;
                } else if (nOutput < -0x8000) {
                    nOutput = -0x8000;
                }

                nSamp2 = nSamp1;
                nSamp1 = nOutput;
                pRSP->anAudioBuffer[nDMEMOut + n + i] = nOutput;
            }
        }

        nDMEMOut += 16;
        nCount -= 16;
    }

    for (i = 0; i < 16; i++) {
        pStateAddress[i] = pRSP->anAudioBuffer[nDMEMOut - 16 + i];
    }

    return true;
}

static inline bool rspAClearBuffer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    memset(&pRSP->anAudioBuffer[(nCommandHi & 0xFFFF) >> 1], 0, nCommandLo & 0xFFFF);
    return true;
}

static bool rspANoise2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspANoise2.s")

static bool rspANMix2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 nCount;
    u32 i;
    s16* inP;
    s16* outP;
    s32 out;

    nCount = ((nCommandHi >> 16) & 0xFF) << 3;
    inP = &pRSP->anAudioBuffer[((nCommandLo >> 16) & 0xFFFF) >> 1];
    outP = &pRSP->anAudioBuffer[(nCommandLo & 0xFFFF) >> 1];

    for (i = 0; i < nCount; i++) {
        out = outP[i];
        out += inP[i];
        if (out > 0x7FFF) {
            out = 0x7FFF;
        } else if (out < -0x8000) {
            out = -0x8000;
        }
        outP[i] = out;
    }

    return true;
}

static bool rspAResample2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 nSrcStep;
    s16* srcP;
    s16* dstP;
    s16 lastValue;
    u16 nCount;
    u16 i;
    s32 nCursorPos;
    u32 scratch;
    u8 flags;
    s16* pData;
    s32 nSrcAddress;
    s32 pad[6];

    srcP = &pRSP->anAudioBuffer[pRSP->nAudioDMEMIn[0]];
    dstP = &pRSP->anAudioBuffer[pRSP->nAudioDMEMOut[0]];
    nCount = pRSP->nAudioCount[0];
    nSrcStep = nCommandHi & 0xFFFF;
    flags = (nCommandHi >> 16) & 0xFF;
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nSrcAddress, NULL)) {
        return false;
    }

    if (flags & 1) {
        for (i = 0; i < 5; i++) {
            pData[i] = 0;
        }
    }

    if (flags & 2) {
        srcP[-2] = pData[0];
        srcP[-1] = pData[2];
        srcP -= 2;
    } else if (flags & 4) {
        srcP[-8] = pData[0];
        srcP[-7] = pData[0];
        srcP[-6] = pData[1];
        srcP[-5] = pData[1];
        srcP[-4] = pData[2];
        srcP[-3] = pData[2];
        srcP[-2] = pData[3];
        srcP[-1] = pData[3];
        srcP -= 8;
    } else {
        srcP[-4] = pData[0];
        srcP[-3] = pData[1];
        srcP[-2] = pData[2];
        srcP[-1] = pData[3];
        srcP -= 4;
    }

    nCursorPos = pData[4];
    for (i = 0; i < nCount; i++, nCursorPos += nSrcStep) {
        lastValue = srcP[nCursorPos >> 15];
        dstP[i] = lastValue + (((nCursorPos & 0x7FFF) * (srcP[(nCursorPos >> 15) + 1] - lastValue)) >> 15);
    }

    pData[4] = nCursorPos & 0x7FFF;
    srcP += nCursorPos >> 15;

    pData[0] = srcP[0];
    pData[1] = srcP[1];
    pData[2] = srcP[2];
    pData[3] = srcP[3];

    return true;
}

static inline bool rspASResample2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 outp = pRSP->nAudioDMEMOut[0];
    s32 outCount = pRSP->nAudioCount[0];
    s32 pitchSpeed = (nCommandHi & 0xFFFF) * 4;
    int i;
    s32 mainCounter = (pRSP->nAudioDMEMIn[1] << 16) | (nCommandLo & 0xFFFF);

    for (i = 0; i < outCount; i++, mainCounter += pitchSpeed) {
        pRSP->anAudioBuffer[outp + i] = pRSP->anAudioBuffer[(mainCounter >> 17) & 0x7FFF];
    }

    return true;
}

static bool rspAFirFilter2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAFirFilter2.s")

static inline bool rspASetBuffer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nDMEMIn = nCommandHi & 0xFFFF;
    u16 nDMEMOut = nCommandLo >> 16;
    u16 nCount = nCommandLo & 0xFFFF;

    pRSP->nAudioDMEMIn[1] = nDMEMIn;
    pRSP->nAudioDMEMIn[0] = (nCommandHi & 0xFFFF) >> 1;
    pRSP->nAudioDMEMOut[1] = nDMEMOut;
    pRSP->nAudioDMEMOut[0] = nDMEMOut >> 1;
    pRSP->nAudioCount[1] = nCount;
    pRSP->nAudioCount[0] = nCount >> 1;

    return true;
}

static inline bool rspAWMEMCopy2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    xlHeapCopy(&pRSP->anAudioBuffer[(s16)(nCommandLo >> 16) >> 1],
               &pRSP->anAudioBuffer[(s16)(nCommandHi & 0xFFFF) >> 1], (s16)((nCommandHi >> 16) & 0xFF) << 7);
    return true;
}

static inline bool rspADMEMMove2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 nSize = nCommandLo & 0xFFFF;

    xlHeapCopy(&pRSP->anAudioBuffer[(s32)(nCommandLo >> 16) / 2], &pRSP->anAudioBuffer[(nCommandHi & 0xFFFF) / 2],
               nSize);
    return true;
}

static inline bool rspALoadADPCM2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        if (xlHeapCopy(&pRSP->anAudioBuffer[pRSP->nAudioADPCMOffset >> 1], pData, nCommandHi & 0xFFFF)) {
            rspLoadADPCMCoefTable2(pRSP);
        }
    }

    return true;
}

static bool rspAMix2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32 nCount;
    s16 inScale;
    s16* srcP;
    s16* dstP;
    s32 tmp;
    s32 inData32;
    s32 outData32;

    nCount = (s32)((nCommandHi >> 12) & 0xFF0) >> 1;
    inScale = nCommandHi & 0xFFFF;
    srcP = &pRSP->anAudioBuffer[(s32)((nCommandLo >> 16) & 0xFFFF) >> 1];
    dstP = &pRSP->anAudioBuffer[(s32)(nCommandLo & 0xFFFF) >> 1];

    for (i = 0; i < nCount; i++) {
        outData32 = dstP[i];
        inData32 = srcP[i];

        outData32 += (inData32 * inScale) >> 15;
        if (outData32 > 0x7FFF) {
            outData32 = 0x7FFF;
        } else if (outData32 < -0x7FFF) {
            outData32 = -0x7FFF;
        }
        dstP[i] = outData32;
    }

    return true;
}

static bool rspAInterleave2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 outp;
    s32 inpr;
    s32 inpl;
    s32 count;
    s32 i;

    outp = (s32)(nCommandHi & 0xFFFF) >> 1;
    inpr = (s32)(nCommandLo & 0xFFFF) >> 1;
    inpl = (s32)(nCommandLo >> 16) >> 1;
    count = (nCommandHi >> 12) & 0xFF0;

    outp += 8;
    for (i = 0; i < count; i += 8) {
        pRSP->anAudioBuffer[outp - 8] = pRSP->anAudioBuffer[inpl + 0];
        pRSP->anAudioBuffer[outp - 7] = pRSP->anAudioBuffer[inpr + 0];
        pRSP->anAudioBuffer[outp - 6] = pRSP->anAudioBuffer[inpl + 1];
        pRSP->anAudioBuffer[outp - 5] = pRSP->anAudioBuffer[inpr + 1];
        pRSP->anAudioBuffer[outp - 4] = pRSP->anAudioBuffer[inpl + 2];
        pRSP->anAudioBuffer[outp - 3] = pRSP->anAudioBuffer[inpr + 2];
        pRSP->anAudioBuffer[outp - 2] = pRSP->anAudioBuffer[inpl + 3];
        pRSP->anAudioBuffer[outp - 1] = pRSP->anAudioBuffer[inpr + 3];
        outp += 8;
        inpl += 4;
        inpr += 4;
    }

    return true;
}

static bool rspADistFilter2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspADistFilter2.s")

static inline bool rspASetLoop2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->nAudioLoopAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    return true;
}

static inline bool rspADMEMCopy2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    xlHeapCopy(&pRSP->anAudioBuffer[(s16)(nCommandLo >> 16) >> 1],
               &pRSP->anAudioBuffer[(s16)(nCommandHi & 0xFFFF) >> 1], (s16)((nCommandHi >> 16) & 0xFF) * sizeof(s16));
    return true;
}

static inline bool rspAHalfCut2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 count = nCommandHi & 0xFFFF;
    s32 outp = (nCommandLo & 0xFFFF) >> 1;
    s32 inpp = (s32)(nCommandLo >> 16) >> 1;
    s32 i;

    for (i = 0; i < count; i++) {
        pRSP->anAudioBuffer[outp + i] = pRSP->anAudioBuffer[inpp + i * 2];
    }
    return true;
}

static inline bool rspASetEnvParam2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s16 temp;

    pRSP->vParams.anSlice[0] = 0;
    pRSP->vParams.anSlice[1] = 0;
    pRSP->vParams.anSlice[2] = 0;
    pRSP->vParams.anSlice[3] = 0;
    pRSP->vParams.anSlice[4] = 0;
    pRSP->vParams.anSlice[5] = 0;
    pRSP->vParams.anSlice[6] = 0;
    pRSP->vParams.anSlice[7] = 0;

    pRSP->stepF = nCommandHi & 0xFFFF;
    pRSP->stepL = (nCommandLo >> 16) & 0xFFFF;
    pRSP->stepR = nCommandLo & 0xFFFF;

    temp = (nCommandHi >> 8) & 0xFF00;
    pRSP->vParams.anSlice[4] = temp;
    temp += pRSP->stepF;
    pRSP->vParams.anSlice[5] = temp;

    return true;
}

static inline bool rspASetEnvParam22(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s16 tmp;

    tmp = (nCommandLo >> 16) & 0xFFFF;
    pRSP->vParams.anSlice[0] = tmp;
    tmp += pRSP->stepL;
    pRSP->vParams.anSlice[1] = tmp;

    tmp = nCommandLo & 0xFFFF;
    pRSP->vParams.anSlice[2] = tmp;
    tmp += pRSP->stepR;
    pRSP->vParams.anSlice[3] = tmp;

    return true;
}

static bool rspAEnvMixer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAEnvMixer2.s")

static inline bool rspALoadBuffer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        xlHeapCopy(&pRSP->anAudioBuffer[(nCommandHi & 0xFFFF) >> 1], pData, (nCommandHi >> 12) & 0xFF0);
    }

    return true;
}

static inline bool rspASaveBuffer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        xlHeapCopy(pData, &pRSP->anAudioBuffer[(nCommandHi & 0xFFFF) >> 1], (nCommandHi >> 12) & 0xFF0);
    }

    return true;
}

static bool rspAPCM8Dec2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAPCM8Dec2.s")

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI2.s")
#else
static bool rspParseABI2(Rsp* pRSP, RspTask* pTask) {
    u32 nCommandLo;
    u32 nCommandHi;
    u32* pABI32;
    u32* pABILast32;
    u32 nSize;
    s32 pad[4];

    nSize = pTask->nLengthMBI & 0x7FFFFF;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pABI32, pTask->nOffsetMBI, NULL)) {
        return false;
    }
    pABILast32 = pABI32 + (nSize >> 2);

    if (nFirstTime_2648) {
        nFirstTime_2648 = false;
    }

    while (pABI32 < pABILast32) {
        nCommandLo = pABI32[1];
        nCommandHi = pABI32[0];
        pABI32 += 2;
        switch (nCommandHi >> 24) {
            case 0: // A_SPNOOP
                break;
            case 1: // A_ADPCM
                if (((nCommandHi >> 16) & 4) != 0) {
                    rspAADPCMDec2Fast(pRSP, nCommandLo, nCommandHi);
                } else {
                    rspAADPCMDec1Fast(pRSP, nCommandLo, nCommandHi);
                }
                break;
            case 2: // A_CLEARBUFF
                rspAClearBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 3: // A_UNK3
                rspANoise2(pRSP, nCommandLo, nCommandHi);
                break;
            case 4: // A_ADDMIXER
                rspANMix2(pRSP, nCommandLo, nCommandHi);
                break;
            case 5: // A_RESAMPLE
                rspAResample2(pRSP, nCommandLo, nCommandHi);
                break;
            case 6: // A_RESAMPLE_ZOH
                rspASResample2(pRSP, nCommandLo, nCommandHi);
                break;
            case 7: // A_FILTER
                rspAFirFilter2(pRSP, nCommandLo, nCommandHi);
                break;
            case 8: // A_SETBUFF
                rspASetBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 9: // A_DUPLICATE
                rspAWMEMCopy2(pRSP, nCommandLo, nCommandHi);
                break;
            case 10: // A_DMEMMOVE
                rspADMEMMove2(pRSP, nCommandLo, nCommandHi);
                break;
            case 11: // A_LOADADPCM
                rspALoadADPCM2(pRSP, nCommandLo, nCommandHi);
                PAD_STACK();
                break;
            case 12: // A_MIXER
                rspAMix2(pRSP, nCommandLo, nCommandHi);
                break;
            case 13: // A_INTERLEAVE
                rspAInterleave2(pRSP, nCommandLo, nCommandHi);
                break;
            case 14: // A_HILOGAIN
                rspADistFilter2(pRSP, nCommandLo, nCommandHi);
                break;
            case 15: // A_SETLOOP
                rspASetLoop2(pRSP, nCommandLo, nCommandHi);
                break;
            case 16: // ???
                rspADMEMCopy2(pRSP, nCommandLo, nCommandHi);
                break;
            case 17: // A_INTERL
                rspAHalfCut2(pRSP, nCommandLo, nCommandHi);
                break;
            case 18: // A_ENVSETUP1
                rspASetEnvParam2(pRSP, nCommandLo, nCommandHi);
                break;
            case 19: // A_ENVMIXER
                rspAEnvMixer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 20: // A_LOADBUFF
                rspALoadBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 21: // A_SAVEBUFF
                rspASaveBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 22: // A_ENVSETUP2
                rspASetEnvParam22(pRSP, nCommandLo, nCommandHi);
                break;
            case 23: // A_S8DEC
                rspAPCM8Dec2(pRSP, nCommandLo, nCommandHi);
                break;
            default:
                return false;
        }
    }

    PAD_STACK();
    PAD_STACK();
    return true;
}
#endif

static bool rspInitAudioDMEM3(Rsp* pRSP) {
    pRSP->anAudioBuffer = pRSP->pDMEM;

    pRSP->anAudioBuffer[0x000] = 0x0000;
    pRSP->anAudioBuffer[0x001] = 0x0001;
    pRSP->anAudioBuffer[0x002] = 0x0002;
    pRSP->anAudioBuffer[0x003] = 0xFFFF;
    pRSP->anAudioBuffer[0x004] = 0x0020;
    pRSP->anAudioBuffer[0x005] = 0x0800;
    pRSP->anAudioBuffer[0x006] = 0x7FFF;
    pRSP->anAudioBuffer[0x007] = 0x4000;
    pRSP->anAudioBuffer[0x008] = 0x1118;
    pRSP->anAudioBuffer[0x009] = 0x1350;
    pRSP->anAudioBuffer[0x00A] = 0x11DC;
    pRSP->anAudioBuffer[0x00B] = 0x1118;
    pRSP->anAudioBuffer[0x00C] = 0x1118;
    pRSP->anAudioBuffer[0x00D] = 0x175C;
    pRSP->anAudioBuffer[0x00E] = 0x1118;
    pRSP->anAudioBuffer[0x00F] = 0x1214;
    pRSP->anAudioBuffer[0x010] = 0x1230;
    pRSP->anAudioBuffer[0x011] = 0x1118;
    pRSP->anAudioBuffer[0x012] = 0x12EC;
    pRSP->anAudioBuffer[0x013] = 0x1CD0;
    pRSP->anAudioBuffer[0x014] = 0x1A18;
    pRSP->anAudioBuffer[0x015] = 0x126C;
    pRSP->anAudioBuffer[0x016] = 0x15EC;
    pRSP->anAudioBuffer[0x017] = 0x132C;
    pRSP->anAudioBuffer[0x018] = 0x1A8C;
    pRSP->anAudioBuffer[0x019] = 0x1ADC;
    pRSP->anAudioBuffer[0x01A] = 0x1C28;
    pRSP->anAudioBuffer[0x01B] = 0x1B38;
    pRSP->anAudioBuffer[0x01C] = 0x1C94;
    pRSP->anAudioBuffer[0x01D] = 0x1CB8;
    pRSP->anAudioBuffer[0x01E] = 0x1C50;
    pRSP->anAudioBuffer[0x01F] = 0x1118;
    pRSP->anAudioBuffer[0x020] = 0x1118;
    pRSP->anAudioBuffer[0x021] = 0x1118;
    pRSP->anAudioBuffer[0x022] = 0x1118;
    pRSP->anAudioBuffer[0x023] = 0x1118;
    pRSP->anAudioBuffer[0x024] = 0x1118;
    pRSP->anAudioBuffer[0x025] = 0x1118;
    pRSP->anAudioBuffer[0x026] = 0x1118;
    pRSP->anAudioBuffer[0x027] = 0x1118;
    pRSP->anAudioBuffer[0x028] = 0xF000;
    pRSP->anAudioBuffer[0x029] = 0x0F00;
    pRSP->anAudioBuffer[0x02A] = 0x00F0;
    pRSP->anAudioBuffer[0x02B] = 0x000F;
    pRSP->anAudioBuffer[0x02C] = 0x0001;
    pRSP->anAudioBuffer[0x02D] = 0x0010;
    pRSP->anAudioBuffer[0x02E] = 0x0100;
    pRSP->anAudioBuffer[0x02F] = 0x1000;
    pRSP->anAudioBuffer[0x030] = 0x0002;
    pRSP->anAudioBuffer[0x031] = 0x0004;
    pRSP->anAudioBuffer[0x032] = 0x0006;
    pRSP->anAudioBuffer[0x033] = 0x0008;
    pRSP->anAudioBuffer[0x034] = 0x000A;
    pRSP->anAudioBuffer[0x035] = 0x000C;
    pRSP->anAudioBuffer[0x036] = 0x000E;
    pRSP->anAudioBuffer[0x037] = 0x0010;
    pRSP->anAudioBuffer[0x038] = 0x0001;
    pRSP->anAudioBuffer[0x039] = 0x0001;
    pRSP->anAudioBuffer[0x03A] = 0x0001;
    pRSP->anAudioBuffer[0x03B] = 0x0001;
    pRSP->anAudioBuffer[0x03C] = 0x0001;
    pRSP->anAudioBuffer[0x03D] = 0x0001;
    pRSP->anAudioBuffer[0x03E] = 0x0001;
    pRSP->anAudioBuffer[0x03F] = 0x0001;
    pRSP->anAudioBuffer[0x040] = 0x0000;
    pRSP->anAudioBuffer[0x041] = 0x0001;
    pRSP->anAudioBuffer[0x042] = 0x0002;
    pRSP->anAudioBuffer[0x043] = 0x0004;
    pRSP->anAudioBuffer[0x044] = 0x0008;
    pRSP->anAudioBuffer[0x045] = 0x0010;
    pRSP->anAudioBuffer[0x046] = 0x0100;
    pRSP->anAudioBuffer[0x047] = 0x0200;
    pRSP->anAudioBuffer[0x048] = 0x0001;
    pRSP->anAudioBuffer[0x049] = 0x0000;
    pRSP->anAudioBuffer[0x04A] = 0x0000;
    pRSP->anAudioBuffer[0x04B] = 0x0000;
    pRSP->anAudioBuffer[0x04C] = 0x0001;
    pRSP->anAudioBuffer[0x04D] = 0x0000;
    pRSP->anAudioBuffer[0x04E] = 0x0000;
    pRSP->anAudioBuffer[0x04F] = 0x0000;
    pRSP->anAudioBuffer[0x050] = 0x0000;
    pRSP->anAudioBuffer[0x051] = 0x0001;
    pRSP->anAudioBuffer[0x052] = 0x0000;
    pRSP->anAudioBuffer[0x053] = 0x0000;
    pRSP->anAudioBuffer[0x054] = 0x0000;
    pRSP->anAudioBuffer[0x055] = 0x0001;
    pRSP->anAudioBuffer[0x056] = 0x0000;
    pRSP->anAudioBuffer[0x057] = 0x0000;

    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0001;
    pRSP->anAudioBuffer[0x05B] = 0x0000;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0001;
    pRSP->anAudioBuffer[0x05F] = 0x0000;

    // bug? 0x058-0x05F initialized twice with different values
    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0000;
    pRSP->anAudioBuffer[0x05B] = 0x0001;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0000;
    pRSP->anAudioBuffer[0x05F] = 0x0001;

    pRSP->anAudioBuffer[0x060] = 0x2000;
    pRSP->anAudioBuffer[0x061] = 0x4000;
    pRSP->anAudioBuffer[0x062] = 0x6000;
    pRSP->anAudioBuffer[0x063] = 0x8000;
    pRSP->anAudioBuffer[0x064] = 0xA000;
    pRSP->anAudioBuffer[0x065] = 0xC000;
    pRSP->anAudioBuffer[0x066] = 0xE000;
    pRSP->anAudioBuffer[0x067] = 0xFFFF;
    pRSP->anAudioBuffer[0x068] = 0x0000;
    pRSP->anAudioBuffer[0x069] = 0xFFFF;
    pRSP->anAudioBuffer[0x06A] = 0x0000;
    pRSP->anAudioBuffer[0x06B] = 0x0000;
    pRSP->anAudioBuffer[0x06C] = 0x0000;
    pRSP->anAudioBuffer[0x06D] = 0x0000;
    pRSP->anAudioBuffer[0x06E] = 0x0000;
    pRSP->anAudioBuffer[0x06F] = 0x0000;
    pRSP->anAudioBuffer[0x070] = 0x0000;
    pRSP->anAudioBuffer[0x071] = 0x0000;
    pRSP->anAudioBuffer[0x072] = 0x0000;
    pRSP->anAudioBuffer[0x073] = 0x0000;
    pRSP->anAudioBuffer[0x074] = 0x0000;
    pRSP->anAudioBuffer[0x075] = 0x0000;
    pRSP->anAudioBuffer[0x076] = 0x0000;
    pRSP->anAudioBuffer[0x077] = 0x0000;
    pRSP->anAudioBuffer[0x078] = 0x0C39;
    pRSP->anAudioBuffer[0x079] = 0x66AD;
    pRSP->anAudioBuffer[0x07A] = 0x0D46;
    pRSP->anAudioBuffer[0x07B] = 0xFFDF;
    pRSP->anAudioBuffer[0x07C] = 0x0B39;
    pRSP->anAudioBuffer[0x07D] = 0x6696;
    pRSP->anAudioBuffer[0x07E] = 0x0E5F;
    pRSP->anAudioBuffer[0x07F] = 0xFFD8;
    pRSP->anAudioBuffer[0x080] = 0x0A44;
    pRSP->anAudioBuffer[0x081] = 0x6669;
    pRSP->anAudioBuffer[0x082] = 0x0F83;
    pRSP->anAudioBuffer[0x083] = 0xFFD0;
    pRSP->anAudioBuffer[0x084] = 0x095A;
    pRSP->anAudioBuffer[0x085] = 0x6626;
    pRSP->anAudioBuffer[0x086] = 0x10B4;
    pRSP->anAudioBuffer[0x087] = 0xFFC8;
    pRSP->anAudioBuffer[0x088] = 0x087D;
    pRSP->anAudioBuffer[0x089] = 0x65CD;
    pRSP->anAudioBuffer[0x08A] = 0x11F0;
    pRSP->anAudioBuffer[0x08B] = 0xFFBF;
    pRSP->anAudioBuffer[0x08C] = 0x07AB;
    pRSP->anAudioBuffer[0x08D] = 0x655E;
    pRSP->anAudioBuffer[0x08E] = 0x1338;
    pRSP->anAudioBuffer[0x08F] = 0xFFB6;
    pRSP->anAudioBuffer[0x090] = 0x06E4;
    pRSP->anAudioBuffer[0x091] = 0x64D9;
    pRSP->anAudioBuffer[0x092] = 0x148C;
    pRSP->anAudioBuffer[0x093] = 0xFFAC;
    pRSP->anAudioBuffer[0x094] = 0x0628;
    pRSP->anAudioBuffer[0x095] = 0x643F;
    pRSP->anAudioBuffer[0x096] = 0x15EB;
    pRSP->anAudioBuffer[0x097] = 0xFFA1;
    pRSP->anAudioBuffer[0x098] = 0x0577;
    pRSP->anAudioBuffer[0x099] = 0x638F;
    pRSP->anAudioBuffer[0x09A] = 0x1756;
    pRSP->anAudioBuffer[0x09B] = 0xFF96;
    pRSP->anAudioBuffer[0x09C] = 0x04D1;
    pRSP->anAudioBuffer[0x09D] = 0x62CB;
    pRSP->anAudioBuffer[0x09E] = 0x18CB;
    pRSP->anAudioBuffer[0x09F] = 0xFF8A;
    pRSP->anAudioBuffer[0x0A0] = 0x0435;
    pRSP->anAudioBuffer[0x0A1] = 0x61F3;
    pRSP->anAudioBuffer[0x0A2] = 0x1A4C;
    pRSP->anAudioBuffer[0x0A3] = 0xFF7E;
    pRSP->anAudioBuffer[0x0A4] = 0x03A4;
    pRSP->anAudioBuffer[0x0A5] = 0x6106;
    pRSP->anAudioBuffer[0x0A6] = 0x1BD7;
    pRSP->anAudioBuffer[0x0A7] = 0xFF71;
    pRSP->anAudioBuffer[0x0A8] = 0x031C;
    pRSP->anAudioBuffer[0x0A9] = 0x6007;
    pRSP->anAudioBuffer[0x0AA] = 0x1D6C;
    pRSP->anAudioBuffer[0x0AB] = 0xFF64;
    pRSP->anAudioBuffer[0x0AC] = 0x029F;
    pRSP->anAudioBuffer[0x0AD] = 0x5EF5;
    pRSP->anAudioBuffer[0x0AE] = 0x1F0B;
    pRSP->anAudioBuffer[0x0AF] = 0xFF56;
    pRSP->anAudioBuffer[0x0B0] = 0x022A;
    pRSP->anAudioBuffer[0x0B1] = 0x5DD0;
    pRSP->anAudioBuffer[0x0B2] = 0x20B3;
    pRSP->anAudioBuffer[0x0B3] = 0xFF48;
    pRSP->anAudioBuffer[0x0B4] = 0x01BE;
    pRSP->anAudioBuffer[0x0B5] = 0x5C9A;
    pRSP->anAudioBuffer[0x0B6] = 0x2264;
    pRSP->anAudioBuffer[0x0B7] = 0xFF3A;
    pRSP->anAudioBuffer[0x0B8] = 0x015B;
    pRSP->anAudioBuffer[0x0B9] = 0x5B53;
    pRSP->anAudioBuffer[0x0BA] = 0x241E;
    pRSP->anAudioBuffer[0x0BB] = 0xFF2C;
    pRSP->anAudioBuffer[0x0BC] = 0x0101;
    pRSP->anAudioBuffer[0x0BD] = 0x59FC;
    pRSP->anAudioBuffer[0x0BE] = 0x25E0;
    pRSP->anAudioBuffer[0x0BF] = 0xFF1E;
    pRSP->anAudioBuffer[0x0C0] = 0x00AE;
    pRSP->anAudioBuffer[0x0C1] = 0x5896;
    pRSP->anAudioBuffer[0x0C2] = 0x27A9;
    pRSP->anAudioBuffer[0x0C3] = 0xFF10;
    pRSP->anAudioBuffer[0x0C4] = 0x0063;
    pRSP->anAudioBuffer[0x0C5] = 0x5720;
    pRSP->anAudioBuffer[0x0C6] = 0x297A;
    pRSP->anAudioBuffer[0x0C7] = 0xFF02;
    pRSP->anAudioBuffer[0x0C8] = 0x001F;
    pRSP->anAudioBuffer[0x0C9] = 0x559D;
    pRSP->anAudioBuffer[0x0CA] = 0x2B50;
    pRSP->anAudioBuffer[0x0CB] = 0xFEF4;
    pRSP->anAudioBuffer[0x0CC] = 0xFFE2;
    pRSP->anAudioBuffer[0x0CD] = 0x540D;
    pRSP->anAudioBuffer[0x0CE] = 0x2D2C;
    pRSP->anAudioBuffer[0x0CF] = 0xFEE8;
    pRSP->anAudioBuffer[0x0D0] = 0xFFAC;
    pRSP->anAudioBuffer[0x0D1] = 0x5270;
    pRSP->anAudioBuffer[0x0D2] = 0x2F0D;
    pRSP->anAudioBuffer[0x0D3] = 0xFEDB;
    pRSP->anAudioBuffer[0x0D4] = 0xFF7C;
    pRSP->anAudioBuffer[0x0D5] = 0x50C7;
    pRSP->anAudioBuffer[0x0D6] = 0x30F3;
    pRSP->anAudioBuffer[0x0D7] = 0xFED0;
    pRSP->anAudioBuffer[0x0D8] = 0xFF53;
    pRSP->anAudioBuffer[0x0D9] = 0x4F14;
    pRSP->anAudioBuffer[0x0DA] = 0x32DC;
    pRSP->anAudioBuffer[0x0DB] = 0xFEC6;
    pRSP->anAudioBuffer[0x0DC] = 0xFF2E;
    pRSP->anAudioBuffer[0x0DD] = 0x4D57;
    pRSP->anAudioBuffer[0x0DE] = 0x34C8;
    pRSP->anAudioBuffer[0x0DF] = 0xFEBD;
    pRSP->anAudioBuffer[0x0E0] = 0xFF0F;
    pRSP->anAudioBuffer[0x0E1] = 0x4B91;
    pRSP->anAudioBuffer[0x0E2] = 0x36B6;
    pRSP->anAudioBuffer[0x0E3] = 0xFEB6;
    pRSP->anAudioBuffer[0x0E4] = 0xFEF5;
    pRSP->anAudioBuffer[0x0E5] = 0x49C2;
    pRSP->anAudioBuffer[0x0E6] = 0x38A5;
    pRSP->anAudioBuffer[0x0E7] = 0xFEB0;
    pRSP->anAudioBuffer[0x0E8] = 0xFEDF;
    pRSP->anAudioBuffer[0x0E9] = 0x47ED;
    pRSP->anAudioBuffer[0x0EA] = 0x3A95;
    pRSP->anAudioBuffer[0x0EB] = 0xFEAC;
    pRSP->anAudioBuffer[0x0EC] = 0xFECE;
    pRSP->anAudioBuffer[0x0ED] = 0x4611;
    pRSP->anAudioBuffer[0x0EE] = 0x3C85;
    pRSP->anAudioBuffer[0x0EF] = 0xFEAB;
    pRSP->anAudioBuffer[0x0F0] = 0xFEC0;
    pRSP->anAudioBuffer[0x0F1] = 0x4430;
    pRSP->anAudioBuffer[0x0F2] = 0x3E74;
    pRSP->anAudioBuffer[0x0F3] = 0xFEAC;
    pRSP->anAudioBuffer[0x0F4] = 0xFEB6;
    pRSP->anAudioBuffer[0x0F5] = 0x424A;
    pRSP->anAudioBuffer[0x0F6] = 0x4060;
    pRSP->anAudioBuffer[0x0F7] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F8] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F9] = 0x4060;
    pRSP->anAudioBuffer[0x0FA] = 0x424A;
    pRSP->anAudioBuffer[0x0FB] = 0xFEB6;
    pRSP->anAudioBuffer[0x0FC] = 0xFEAC;
    pRSP->anAudioBuffer[0x0FD] = 0x3E74;
    pRSP->anAudioBuffer[0x0FE] = 0x4430;
    pRSP->anAudioBuffer[0x0FF] = 0xFEC0;
    pRSP->anAudioBuffer[0x100] = 0xFEAB;
    pRSP->anAudioBuffer[0x101] = 0x3C85;
    pRSP->anAudioBuffer[0x102] = 0x4611;
    pRSP->anAudioBuffer[0x103] = 0xFECE;
    pRSP->anAudioBuffer[0x104] = 0xFEAC;
    pRSP->anAudioBuffer[0x105] = 0x3A95;
    pRSP->anAudioBuffer[0x106] = 0x47ED;
    pRSP->anAudioBuffer[0x107] = 0xFEDF;
    pRSP->anAudioBuffer[0x108] = 0xFEB0;
    pRSP->anAudioBuffer[0x109] = 0x38A5;
    pRSP->anAudioBuffer[0x10A] = 0x49C2;
    pRSP->anAudioBuffer[0x10B] = 0xFEF5;
    pRSP->anAudioBuffer[0x10C] = 0xFEB6;
    pRSP->anAudioBuffer[0x10D] = 0x36B6;
    pRSP->anAudioBuffer[0x10E] = 0x4B91;
    pRSP->anAudioBuffer[0x10F] = 0xFF0F;
    pRSP->anAudioBuffer[0x110] = 0xFEBD;
    pRSP->anAudioBuffer[0x111] = 0x34C8;
    pRSP->anAudioBuffer[0x112] = 0x4D57;
    pRSP->anAudioBuffer[0x113] = 0xFF2E;
    pRSP->anAudioBuffer[0x114] = 0xFEC6;
    pRSP->anAudioBuffer[0x115] = 0x32DC;
    pRSP->anAudioBuffer[0x116] = 0x4F14;
    pRSP->anAudioBuffer[0x117] = 0xFF53;
    pRSP->anAudioBuffer[0x118] = 0xFED0;
    pRSP->anAudioBuffer[0x119] = 0x30F3;
    pRSP->anAudioBuffer[0x11A] = 0x50C7;
    pRSP->anAudioBuffer[0x11B] = 0xFF7C;
    pRSP->anAudioBuffer[0x11C] = 0xFEDB;
    pRSP->anAudioBuffer[0x11D] = 0x2F0D;
    pRSP->anAudioBuffer[0x11E] = 0x5270;
    pRSP->anAudioBuffer[0x11F] = 0xFFAC;
    pRSP->anAudioBuffer[0x120] = 0xFEE8;
    pRSP->anAudioBuffer[0x121] = 0x2D2C;
    pRSP->anAudioBuffer[0x122] = 0x540D;
    pRSP->anAudioBuffer[0x123] = 0xFFE2;
    pRSP->anAudioBuffer[0x124] = 0xFEF4;
    pRSP->anAudioBuffer[0x125] = 0x2B50;
    pRSP->anAudioBuffer[0x126] = 0x559D;
    pRSP->anAudioBuffer[0x127] = 0x001F;
    pRSP->anAudioBuffer[0x128] = 0xFF02;
    pRSP->anAudioBuffer[0x129] = 0x297A;
    pRSP->anAudioBuffer[0x12A] = 0x5720;
    pRSP->anAudioBuffer[0x12B] = 0x0063;
    pRSP->anAudioBuffer[0x12C] = 0xFF10;
    pRSP->anAudioBuffer[0x12D] = 0x27A9;
    pRSP->anAudioBuffer[0x12E] = 0x5896;
    pRSP->anAudioBuffer[0x12F] = 0x00AE;
    pRSP->anAudioBuffer[0x130] = 0xFF1E;
    pRSP->anAudioBuffer[0x131] = 0x25E0;
    pRSP->anAudioBuffer[0x132] = 0x59FC;
    pRSP->anAudioBuffer[0x133] = 0x0101;
    pRSP->anAudioBuffer[0x134] = 0xFF2C;
    pRSP->anAudioBuffer[0x135] = 0x241E;
    pRSP->anAudioBuffer[0x136] = 0x5B53;
    pRSP->anAudioBuffer[0x137] = 0x015B;
    pRSP->anAudioBuffer[0x138] = 0xFF3A;
    pRSP->anAudioBuffer[0x139] = 0x2264;
    pRSP->anAudioBuffer[0x13A] = 0x5C9A;
    pRSP->anAudioBuffer[0x13B] = 0x01BE;
    pRSP->anAudioBuffer[0x13C] = 0xFF48;
    pRSP->anAudioBuffer[0x13D] = 0x20B3;
    pRSP->anAudioBuffer[0x13E] = 0x5DD0;
    pRSP->anAudioBuffer[0x13F] = 0x022A;
    pRSP->anAudioBuffer[0x140] = 0xFF56;
    pRSP->anAudioBuffer[0x141] = 0x1F0B;
    pRSP->anAudioBuffer[0x142] = 0x5EF5;
    pRSP->anAudioBuffer[0x143] = 0x029F;
    pRSP->anAudioBuffer[0x144] = 0xFF64;
    pRSP->anAudioBuffer[0x145] = 0x1D6C;
    pRSP->anAudioBuffer[0x146] = 0x6007;
    pRSP->anAudioBuffer[0x147] = 0x031C;
    pRSP->anAudioBuffer[0x148] = 0xFF71;
    pRSP->anAudioBuffer[0x149] = 0x1BD7;
    pRSP->anAudioBuffer[0x14A] = 0x6106;
    pRSP->anAudioBuffer[0x14B] = 0x03A4;
    pRSP->anAudioBuffer[0x14C] = 0xFF7E;
    pRSP->anAudioBuffer[0x14D] = 0x1A4C;
    pRSP->anAudioBuffer[0x14E] = 0x61F3;
    pRSP->anAudioBuffer[0x14F] = 0x0435;
    pRSP->anAudioBuffer[0x150] = 0xFF8A;
    pRSP->anAudioBuffer[0x151] = 0x18CB;
    pRSP->anAudioBuffer[0x152] = 0x62CB;
    pRSP->anAudioBuffer[0x153] = 0x04D1;
    pRSP->anAudioBuffer[0x154] = 0xFF96;
    pRSP->anAudioBuffer[0x155] = 0x1756;
    pRSP->anAudioBuffer[0x156] = 0x638F;
    pRSP->anAudioBuffer[0x157] = 0x0577;
    pRSP->anAudioBuffer[0x158] = 0xFFA1;
    pRSP->anAudioBuffer[0x159] = 0x15EB;
    pRSP->anAudioBuffer[0x15A] = 0x643F;
    pRSP->anAudioBuffer[0x15B] = 0x0628;
    pRSP->anAudioBuffer[0x15C] = 0xFFAC;
    pRSP->anAudioBuffer[0x15D] = 0x148C;
    pRSP->anAudioBuffer[0x15E] = 0x64D9;
    pRSP->anAudioBuffer[0x15F] = 0x06E4;
    pRSP->anAudioBuffer[0x160] = 0xFFB6;
    pRSP->anAudioBuffer[0x161] = 0x1338;
    pRSP->anAudioBuffer[0x162] = 0x655E;
    pRSP->anAudioBuffer[0x163] = 0x07AB;
    pRSP->anAudioBuffer[0x164] = 0xFFBF;
    pRSP->anAudioBuffer[0x165] = 0x11F0;
    pRSP->anAudioBuffer[0x166] = 0x65CD;
    pRSP->anAudioBuffer[0x167] = 0x087D;
    pRSP->anAudioBuffer[0x168] = 0xFFC8;
    pRSP->anAudioBuffer[0x169] = 0x10B4;
    pRSP->anAudioBuffer[0x16A] = 0x6626;
    pRSP->anAudioBuffer[0x16B] = 0x095A;
    pRSP->anAudioBuffer[0x16C] = 0xFFD0;
    pRSP->anAudioBuffer[0x16D] = 0x0F83;
    pRSP->anAudioBuffer[0x16E] = 0x6669;
    pRSP->anAudioBuffer[0x16F] = 0x0A44;
    pRSP->anAudioBuffer[0x170] = 0xFFD8;
    pRSP->anAudioBuffer[0x171] = 0x0E5F;
    pRSP->anAudioBuffer[0x172] = 0x6696;
    pRSP->anAudioBuffer[0x173] = 0x0B39;
    pRSP->anAudioBuffer[0x174] = 0xFFDF;
    pRSP->anAudioBuffer[0x175] = 0x0D46;
    pRSP->anAudioBuffer[0x176] = 0x66AD;
    pRSP->anAudioBuffer[0x177] = 0x0C39;

    return true;
}

static inline bool rspASetEnvParam3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->vParams.anSlice[0] = 0;
    pRSP->vParams.anSlice[1] = 0;
    pRSP->vParams.anSlice[2] = 0;
    pRSP->vParams.anSlice[3] = 0;
    pRSP->vParams.anSlice[4] = 0;
    pRSP->vParams.anSlice[5] = 0;
    pRSP->vParams.anSlice[6] = 0;
    pRSP->vParams.anSlice[7] = 0;

    pRSP->stepL = (nCommandLo >> 16) & 0xFFFF;
    pRSP->stepR = nCommandLo & 0xFFFF;
    pRSP->vParams.anSlice[4] = (nCommandHi >> 8) & 0xFF00;

    return true;
}

static inline bool rspASetEnvParam32(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->vParams.anSlice[0] = (nCommandLo >> 16) & 0xFFFF;
    pRSP->vParams.anSlice[2] = nCommandLo & 0xFFFF;
    return true;
}

static inline bool rspALoadBuffer3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        xlHeapCopy(&pRSP->anAudioBuffer[((nCommandHi & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)], pData,
                   (nCommandHi >> 12) & 0xFF0);
    }

    return true;
}

static inline bool rspASaveBuffer3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        xlHeapCopy(pData, &pRSP->anAudioBuffer[((nCommandHi & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)],
                   (nCommandHi >> 12) & 0xFF0);
    }

    return true;
}

static bool rspAEnvMixer3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAEnvMixer3.s")

static inline bool rspAHalfCut3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 count = nCommandHi & 0xFFFF;
    s32 outp = ((nCommandLo & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1);
    s32 inpp = ((s32)(nCommandLo >> 16) >> 1) + (pRSP->nAudioMemOffset >> 1);
    s32 i;

    for (i = 0; i < count; i++) {
        pRSP->anAudioBuffer[outp + i] = pRSP->anAudioBuffer[inpp + i * 2];
    }
    return true;
}

static bool rspAMix3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32 nCount;
    s16 inScale;
    s16* srcP;
    s16* dstP;
    s32 tmp;
    s32 inData32;
    s32 outData32;

    nCount = (s32)((nCommandHi >> 12) & 0xFF0) >> 1;
    inScale = nCommandHi & 0xFFFF;
    srcP = &pRSP->anAudioBuffer[((s32)((nCommandLo >> 16) & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)];
    dstP = &pRSP->anAudioBuffer[((s32)(nCommandLo & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)];

    for (i = 0; i < nCount; i++) {
        outData32 = dstP[i];
        inData32 = srcP[i];

        outData32 += (inData32 * inScale) >> 15;
        if (outData32 > 0x7FFF) {
            outData32 = 0x7FFF;
        } else if (outData32 < -0x7FFF) {
            outData32 = -0x7FFF;
        }
        dstP[i] = outData32;
    }

    return true;
}

static inline bool rspADMEMCopy(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    xlHeapCopy(&pRSP->anAudioBuffer[(s16)(nCommandLo >> 17) + (pRSP->nAudioMemOffset >> 1)],
               &pRSP->anAudioBuffer[(s16)((nCommandHi & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)],
               (s16)((nCommandHi >> 16) & 0xFF) * sizeof(s16));

    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI3.s")
#else
static bool rspParseABI3(Rsp* pRSP, RspTask* pTask) {
    u32 nCommandLo;
    u32 nCommandHi;
    u32* pABI32;
    u32* pABILast32;
    u32 nSize;

    nSize = pTask->nLengthMBI & 0x7FFFFF;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pABI32, pTask->nOffsetMBI, NULL)) {
        return false;
    }
    pABILast32 = pABI32 + (nSize >> 2);

    if (nFirstTime_2757) {
        nFirstTime_2757 = false;
    }

    while (pABI32 < pABILast32) {
        nCommandLo = pABI32[1];
        nCommandHi = pABI32[0];
        pABI32 += 2;
        switch (nCommandHi >> 24) {
            case 0:
                break;
            case 1:
                rspAADPCMDec1Fast(pRSP, nCommandLo, nCommandHi);
                break;
            case 2:
                rspAClearBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 19:
                rspAEnvMixer3(pRSP, nCommandLo, nCommandHi);
                break;
            case 20:
                rspALoadBuffer3(pRSP, nCommandLo, nCommandHi);
                break;
            case 5:
                rspAResample1(pRSP, nCommandLo, nCommandHi);
                break;
            case 21:
                rspASaveBuffer3(pRSP, nCommandLo, nCommandHi);
                break;
            case 7:
                rspASegment1(pRSP, nCommandLo, nCommandHi);
                break;
            case 8:
                rspASetBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 10:
                rspADMEMMove1(pRSP, nCommandLo, nCommandHi);
                break;
            case 11:
                rspALoadADPCM2(pRSP, nCommandLo, nCommandHi);
                break;
            case 12:
                rspAMix3(pRSP, nCommandLo, nCommandHi);
                break;
            case 13:
                rspAInterleave1(pRSP, nCommandLo, nCommandHi);
                break;
            case 14:
                rspAPoleFilter1(pRSP, nCommandLo, nCommandHi);
                break;
            case 15:
                rspASetLoop1(pRSP, nCommandLo, nCommandHi);
                break;
            case 16:
                rspADMEMCopy(pRSP, nCommandLo, nCommandHi);
                break;
            case 17:
                rspAHalfCut3(pRSP, nCommandLo, nCommandHi);
                break;
            case 18:
                rspASetEnvParam3(pRSP, nCommandLo, nCommandHi);
                break;
            case 22:
                rspASetEnvParam32(pRSP, nCommandLo, nCommandHi);
                break;
            default:
                return false;
        }
    }

    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    return true;
}
#endif

static bool rspInitAudioDMEM4(Rsp* pRSP) {
    pRSP->anAudioBuffer = pRSP->pDMEM;

    pRSP->anAudioBuffer[0x000] = 0x0000;
    pRSP->anAudioBuffer[0x001] = 0x0001;
    pRSP->anAudioBuffer[0x002] = 0x0002;
    pRSP->anAudioBuffer[0x003] = 0xFFFF;
    pRSP->anAudioBuffer[0x004] = 0x0020;
    pRSP->anAudioBuffer[0x005] = 0x0800;
    pRSP->anAudioBuffer[0x006] = 0x7FFF;
    pRSP->anAudioBuffer[0x007] = 0x4000;
    pRSP->anAudioBuffer[0x008] = 0x1118;
    pRSP->anAudioBuffer[0x009] = 0x12E0;
    pRSP->anAudioBuffer[0x00A] = 0x11DC;
    pRSP->anAudioBuffer[0x00B] = 0x1118;
    pRSP->anAudioBuffer[0x00C] = 0x1E8C;
    pRSP->anAudioBuffer[0x00D] = 0x1568;
    pRSP->anAudioBuffer[0x00E] = 0x1EFC;
    pRSP->anAudioBuffer[0x00F] = 0x1118;
    pRSP->anAudioBuffer[0x010] = 0x120C;
    pRSP->anAudioBuffer[0x011] = 0x1118;
    pRSP->anAudioBuffer[0x012] = 0x1298;
    pRSP->anAudioBuffer[0x013] = 0x1B24;
    pRSP->anAudioBuffer[0x014] = 0x1B40;
    pRSP->anAudioBuffer[0x015] = 0x1220;
    pRSP->anAudioBuffer[0x016] = 0x1D30;
    pRSP->anAudioBuffer[0x017] = 0x12D0;
    pRSP->anAudioBuffer[0x018] = 0x1818;
    pRSP->anAudioBuffer[0x019] = 0x18C4;
    pRSP->anAudioBuffer[0x01A] = 0x1A84;
    pRSP->anAudioBuffer[0x01B] = 0x1918;
    pRSP->anAudioBuffer[0x01C] = 0x1AE8;
    pRSP->anAudioBuffer[0x01D] = 0x1B0C;
    pRSP->anAudioBuffer[0x01E] = 0x1AAC;
    pRSP->anAudioBuffer[0x01F] = 0x1BAC;
    pRSP->anAudioBuffer[0x020] = 0x1C5C;
    pRSP->anAudioBuffer[0x021] = 0x1CB0;
    pRSP->anAudioBuffer[0x022] = 0x1860;
    pRSP->anAudioBuffer[0x023] = 0x1118;
    pRSP->anAudioBuffer[0x024] = 0x1118;
    pRSP->anAudioBuffer[0x025] = 0x1118;
    pRSP->anAudioBuffer[0x026] = 0x1118;
    pRSP->anAudioBuffer[0x027] = 0x1118;
    pRSP->anAudioBuffer[0x028] = 0xF000;
    pRSP->anAudioBuffer[0x029] = 0x0F00;
    pRSP->anAudioBuffer[0x02A] = 0x00F0;
    pRSP->anAudioBuffer[0x02B] = 0x000F;
    pRSP->anAudioBuffer[0x02C] = 0x0001;
    pRSP->anAudioBuffer[0x02D] = 0x0010;
    pRSP->anAudioBuffer[0x02E] = 0x0100;
    pRSP->anAudioBuffer[0x02F] = 0x1000;
    pRSP->anAudioBuffer[0x030] = 0x0002;
    pRSP->anAudioBuffer[0x031] = 0x0004;
    pRSP->anAudioBuffer[0x032] = 0x0006;
    pRSP->anAudioBuffer[0x033] = 0x0008;
    pRSP->anAudioBuffer[0x034] = 0x000A;
    pRSP->anAudioBuffer[0x035] = 0x000C;
    pRSP->anAudioBuffer[0x036] = 0x000E;
    pRSP->anAudioBuffer[0x037] = 0x0010;
    pRSP->anAudioBuffer[0x038] = 0x0001;
    pRSP->anAudioBuffer[0x039] = 0x0001;
    pRSP->anAudioBuffer[0x03A] = 0x0001;
    pRSP->anAudioBuffer[0x03B] = 0x0001;
    pRSP->anAudioBuffer[0x03C] = 0x0001;
    pRSP->anAudioBuffer[0x03D] = 0x0001;
    pRSP->anAudioBuffer[0x03E] = 0x0001;
    pRSP->anAudioBuffer[0x03F] = 0x0001;
    pRSP->anAudioBuffer[0x040] = 0x0000;
    pRSP->anAudioBuffer[0x041] = 0x0001;
    pRSP->anAudioBuffer[0x042] = 0x0002;
    pRSP->anAudioBuffer[0x043] = 0x0004;
    pRSP->anAudioBuffer[0x044] = 0x0008;
    pRSP->anAudioBuffer[0x045] = 0x0010;
    pRSP->anAudioBuffer[0x046] = 0x0100;
    pRSP->anAudioBuffer[0x047] = 0x0200;
    pRSP->anAudioBuffer[0x048] = 0x0001;
    pRSP->anAudioBuffer[0x049] = 0x0000;
    pRSP->anAudioBuffer[0x04A] = 0x0000;
    pRSP->anAudioBuffer[0x04B] = 0x0000;
    pRSP->anAudioBuffer[0x04C] = 0x0001;
    pRSP->anAudioBuffer[0x04D] = 0x0000;
    pRSP->anAudioBuffer[0x04E] = 0x0000;
    pRSP->anAudioBuffer[0x04F] = 0x0000;
    pRSP->anAudioBuffer[0x050] = 0x0000;
    pRSP->anAudioBuffer[0x051] = 0x0001;
    pRSP->anAudioBuffer[0x052] = 0x0000;
    pRSP->anAudioBuffer[0x053] = 0x0000;
    pRSP->anAudioBuffer[0x054] = 0x0000;
    pRSP->anAudioBuffer[0x055] = 0x0001;
    pRSP->anAudioBuffer[0x056] = 0x0000;
    pRSP->anAudioBuffer[0x057] = 0x0000;

    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0001;
    pRSP->anAudioBuffer[0x05B] = 0x0000;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0001;
    pRSP->anAudioBuffer[0x05F] = 0x0000;

    // bug? 0x058-0x05F initialized twice with different values
    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0000;
    pRSP->anAudioBuffer[0x05B] = 0x0001;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0000;
    pRSP->anAudioBuffer[0x05F] = 0x0001;

    pRSP->anAudioBuffer[0x060] = 0x2000;
    pRSP->anAudioBuffer[0x061] = 0x4000;
    pRSP->anAudioBuffer[0x062] = 0x6000;
    pRSP->anAudioBuffer[0x063] = 0x8000;
    pRSP->anAudioBuffer[0x064] = 0xA000;
    pRSP->anAudioBuffer[0x065] = 0xC000;
    pRSP->anAudioBuffer[0x066] = 0xE000;
    pRSP->anAudioBuffer[0x067] = 0xFFFF;
    pRSP->anAudioBuffer[0x068] = 0x0000;
    pRSP->anAudioBuffer[0x069] = 0xFFFF;
    pRSP->anAudioBuffer[0x06A] = 0x0000;
    pRSP->anAudioBuffer[0x06B] = 0x0000;
    pRSP->anAudioBuffer[0x06C] = 0x0000;
    pRSP->anAudioBuffer[0x06D] = 0x0000;
    pRSP->anAudioBuffer[0x06E] = 0x0000;
    pRSP->anAudioBuffer[0x06F] = 0x0000;
    pRSP->anAudioBuffer[0x070] = 0x0000;
    pRSP->anAudioBuffer[0x071] = 0x0000;
    pRSP->anAudioBuffer[0x072] = 0x0000;
    pRSP->anAudioBuffer[0x073] = 0x0000;
    pRSP->anAudioBuffer[0x074] = 0x0000;
    pRSP->anAudioBuffer[0x075] = 0x0000;
    pRSP->anAudioBuffer[0x076] = 0x0000;
    pRSP->anAudioBuffer[0x077] = 0x0000;
    pRSP->anAudioBuffer[0x078] = 0x0C39;
    pRSP->anAudioBuffer[0x079] = 0x66AD;
    pRSP->anAudioBuffer[0x07A] = 0x0D46;
    pRSP->anAudioBuffer[0x07B] = 0xFFDF;
    pRSP->anAudioBuffer[0x07C] = 0x0B39;
    pRSP->anAudioBuffer[0x07D] = 0x6696;
    pRSP->anAudioBuffer[0x07E] = 0x0E5F;
    pRSP->anAudioBuffer[0x07F] = 0xFFD8;
    pRSP->anAudioBuffer[0x080] = 0x0A44;
    pRSP->anAudioBuffer[0x081] = 0x6669;
    pRSP->anAudioBuffer[0x082] = 0x0F83;
    pRSP->anAudioBuffer[0x083] = 0xFFD0;
    pRSP->anAudioBuffer[0x084] = 0x095A;
    pRSP->anAudioBuffer[0x085] = 0x6626;
    pRSP->anAudioBuffer[0x086] = 0x10B4;
    pRSP->anAudioBuffer[0x087] = 0xFFC8;
    pRSP->anAudioBuffer[0x088] = 0x087D;
    pRSP->anAudioBuffer[0x089] = 0x65CD;
    pRSP->anAudioBuffer[0x08A] = 0x11F0;
    pRSP->anAudioBuffer[0x08B] = 0xFFBF;
    pRSP->anAudioBuffer[0x08C] = 0x07AB;
    pRSP->anAudioBuffer[0x08D] = 0x655E;
    pRSP->anAudioBuffer[0x08E] = 0x1338;
    pRSP->anAudioBuffer[0x08F] = 0xFFB6;
    pRSP->anAudioBuffer[0x090] = 0x06E4;
    pRSP->anAudioBuffer[0x091] = 0x64D9;
    pRSP->anAudioBuffer[0x092] = 0x148C;
    pRSP->anAudioBuffer[0x093] = 0xFFAC;
    pRSP->anAudioBuffer[0x094] = 0x0628;
    pRSP->anAudioBuffer[0x095] = 0x643F;
    pRSP->anAudioBuffer[0x096] = 0x15EB;
    pRSP->anAudioBuffer[0x097] = 0xFFA1;
    pRSP->anAudioBuffer[0x098] = 0x0577;
    pRSP->anAudioBuffer[0x099] = 0x638F;
    pRSP->anAudioBuffer[0x09A] = 0x1756;
    pRSP->anAudioBuffer[0x09B] = 0xFF96;
    pRSP->anAudioBuffer[0x09C] = 0x04D1;
    pRSP->anAudioBuffer[0x09D] = 0x62CB;
    pRSP->anAudioBuffer[0x09E] = 0x18CB;
    pRSP->anAudioBuffer[0x09F] = 0xFF8A;
    pRSP->anAudioBuffer[0x0A0] = 0x0435;
    pRSP->anAudioBuffer[0x0A1] = 0x61F3;
    pRSP->anAudioBuffer[0x0A2] = 0x1A4C;
    pRSP->anAudioBuffer[0x0A3] = 0xFF7E;
    pRSP->anAudioBuffer[0x0A4] = 0x03A4;
    pRSP->anAudioBuffer[0x0A5] = 0x6106;
    pRSP->anAudioBuffer[0x0A6] = 0x1BD7;
    pRSP->anAudioBuffer[0x0A7] = 0xFF71;
    pRSP->anAudioBuffer[0x0A8] = 0x031C;
    pRSP->anAudioBuffer[0x0A9] = 0x6007;
    pRSP->anAudioBuffer[0x0AA] = 0x1D6C;
    pRSP->anAudioBuffer[0x0AB] = 0xFF64;
    pRSP->anAudioBuffer[0x0AC] = 0x029F;
    pRSP->anAudioBuffer[0x0AD] = 0x5EF5;
    pRSP->anAudioBuffer[0x0AE] = 0x1F0B;
    pRSP->anAudioBuffer[0x0AF] = 0xFF56;
    pRSP->anAudioBuffer[0x0B0] = 0x022A;
    pRSP->anAudioBuffer[0x0B1] = 0x5DD0;
    pRSP->anAudioBuffer[0x0B2] = 0x20B3;
    pRSP->anAudioBuffer[0x0B3] = 0xFF48;
    pRSP->anAudioBuffer[0x0B4] = 0x01BE;
    pRSP->anAudioBuffer[0x0B5] = 0x5C9A;
    pRSP->anAudioBuffer[0x0B6] = 0x2264;
    pRSP->anAudioBuffer[0x0B7] = 0xFF3A;
    pRSP->anAudioBuffer[0x0B8] = 0x015B;
    pRSP->anAudioBuffer[0x0B9] = 0x5B53;
    pRSP->anAudioBuffer[0x0BA] = 0x241E;
    pRSP->anAudioBuffer[0x0BB] = 0xFF2C;
    pRSP->anAudioBuffer[0x0BC] = 0x0101;
    pRSP->anAudioBuffer[0x0BD] = 0x59FC;
    pRSP->anAudioBuffer[0x0BE] = 0x25E0;
    pRSP->anAudioBuffer[0x0BF] = 0xFF1E;
    pRSP->anAudioBuffer[0x0C0] = 0x00AE;
    pRSP->anAudioBuffer[0x0C1] = 0x5896;
    pRSP->anAudioBuffer[0x0C2] = 0x27A9;
    pRSP->anAudioBuffer[0x0C3] = 0xFF10;
    pRSP->anAudioBuffer[0x0C4] = 0x0063;
    pRSP->anAudioBuffer[0x0C5] = 0x5720;
    pRSP->anAudioBuffer[0x0C6] = 0x297A;
    pRSP->anAudioBuffer[0x0C7] = 0xFF02;
    pRSP->anAudioBuffer[0x0C8] = 0x001F;
    pRSP->anAudioBuffer[0x0C9] = 0x559D;
    pRSP->anAudioBuffer[0x0CA] = 0x2B50;
    pRSP->anAudioBuffer[0x0CB] = 0xFEF4;
    pRSP->anAudioBuffer[0x0CC] = 0xFFE2;
    pRSP->anAudioBuffer[0x0CD] = 0x540D;
    pRSP->anAudioBuffer[0x0CE] = 0x2D2C;
    pRSP->anAudioBuffer[0x0CF] = 0xFEE8;
    pRSP->anAudioBuffer[0x0D0] = 0xFFAC;
    pRSP->anAudioBuffer[0x0D1] = 0x5270;
    pRSP->anAudioBuffer[0x0D2] = 0x2F0D;
    pRSP->anAudioBuffer[0x0D3] = 0xFEDB;
    pRSP->anAudioBuffer[0x0D4] = 0xFF7C;
    pRSP->anAudioBuffer[0x0D5] = 0x50C7;
    pRSP->anAudioBuffer[0x0D6] = 0x30F3;
    pRSP->anAudioBuffer[0x0D7] = 0xFED0;
    pRSP->anAudioBuffer[0x0D8] = 0xFF53;
    pRSP->anAudioBuffer[0x0D9] = 0x4F14;
    pRSP->anAudioBuffer[0x0DA] = 0x32DC;
    pRSP->anAudioBuffer[0x0DB] = 0xFEC6;
    pRSP->anAudioBuffer[0x0DC] = 0xFF2E;
    pRSP->anAudioBuffer[0x0DD] = 0x4D57;
    pRSP->anAudioBuffer[0x0DE] = 0x34C8;
    pRSP->anAudioBuffer[0x0DF] = 0xFEBD;
    pRSP->anAudioBuffer[0x0E0] = 0xFF0F;
    pRSP->anAudioBuffer[0x0E1] = 0x4B91;
    pRSP->anAudioBuffer[0x0E2] = 0x36B6;
    pRSP->anAudioBuffer[0x0E3] = 0xFEB6;
    pRSP->anAudioBuffer[0x0E4] = 0xFEF5;
    pRSP->anAudioBuffer[0x0E5] = 0x49C2;
    pRSP->anAudioBuffer[0x0E6] = 0x38A5;
    pRSP->anAudioBuffer[0x0E7] = 0xFEB0;
    pRSP->anAudioBuffer[0x0E8] = 0xFEDF;
    pRSP->anAudioBuffer[0x0E9] = 0x47ED;
    pRSP->anAudioBuffer[0x0EA] = 0x3A95;
    pRSP->anAudioBuffer[0x0EB] = 0xFEAC;
    pRSP->anAudioBuffer[0x0EC] = 0xFECE;
    pRSP->anAudioBuffer[0x0ED] = 0x4611;
    pRSP->anAudioBuffer[0x0EE] = 0x3C85;
    pRSP->anAudioBuffer[0x0EF] = 0xFEAB;
    pRSP->anAudioBuffer[0x0F0] = 0xFEC0;
    pRSP->anAudioBuffer[0x0F1] = 0x4430;
    pRSP->anAudioBuffer[0x0F2] = 0x3E74;
    pRSP->anAudioBuffer[0x0F3] = 0xFEAC;
    pRSP->anAudioBuffer[0x0F4] = 0xFEB6;
    pRSP->anAudioBuffer[0x0F5] = 0x424A;
    pRSP->anAudioBuffer[0x0F6] = 0x4060;
    pRSP->anAudioBuffer[0x0F7] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F8] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F9] = 0x4060;
    pRSP->anAudioBuffer[0x0FA] = 0x424A;
    pRSP->anAudioBuffer[0x0FB] = 0xFEB6;
    pRSP->anAudioBuffer[0x0FC] = 0xFEAC;
    pRSP->anAudioBuffer[0x0FD] = 0x3E74;
    pRSP->anAudioBuffer[0x0FE] = 0x4430;
    pRSP->anAudioBuffer[0x0FF] = 0xFEC0;
    pRSP->anAudioBuffer[0x100] = 0xFEAB;
    pRSP->anAudioBuffer[0x101] = 0x3C85;
    pRSP->anAudioBuffer[0x102] = 0x4611;
    pRSP->anAudioBuffer[0x103] = 0xFECE;
    pRSP->anAudioBuffer[0x104] = 0xFEAC;
    pRSP->anAudioBuffer[0x105] = 0x3A95;
    pRSP->anAudioBuffer[0x106] = 0x47ED;
    pRSP->anAudioBuffer[0x107] = 0xFEDF;
    pRSP->anAudioBuffer[0x108] = 0xFEB0;
    pRSP->anAudioBuffer[0x109] = 0x38A5;
    pRSP->anAudioBuffer[0x10A] = 0x49C2;
    pRSP->anAudioBuffer[0x10B] = 0xFEF5;
    pRSP->anAudioBuffer[0x10C] = 0xFEB6;
    pRSP->anAudioBuffer[0x10D] = 0x36B6;
    pRSP->anAudioBuffer[0x10E] = 0x4B91;
    pRSP->anAudioBuffer[0x10F] = 0xFF0F;
    pRSP->anAudioBuffer[0x110] = 0xFEBD;
    pRSP->anAudioBuffer[0x111] = 0x34C8;
    pRSP->anAudioBuffer[0x112] = 0x4D57;
    pRSP->anAudioBuffer[0x113] = 0xFF2E;
    pRSP->anAudioBuffer[0x114] = 0xFEC6;
    pRSP->anAudioBuffer[0x115] = 0x32DC;
    pRSP->anAudioBuffer[0x116] = 0x4F14;
    pRSP->anAudioBuffer[0x117] = 0xFF53;
    pRSP->anAudioBuffer[0x118] = 0xFED0;
    pRSP->anAudioBuffer[0x119] = 0x30F3;
    pRSP->anAudioBuffer[0x11A] = 0x50C7;
    pRSP->anAudioBuffer[0x11B] = 0xFF7C;
    pRSP->anAudioBuffer[0x11C] = 0xFEDB;
    pRSP->anAudioBuffer[0x11D] = 0x2F0D;
    pRSP->anAudioBuffer[0x11E] = 0x5270;
    pRSP->anAudioBuffer[0x11F] = 0xFFAC;
    pRSP->anAudioBuffer[0x120] = 0xFEE8;
    pRSP->anAudioBuffer[0x121] = 0x2D2C;
    pRSP->anAudioBuffer[0x122] = 0x540D;
    pRSP->anAudioBuffer[0x123] = 0xFFE2;
    pRSP->anAudioBuffer[0x124] = 0xFEF4;
    pRSP->anAudioBuffer[0x125] = 0x2B50;
    pRSP->anAudioBuffer[0x126] = 0x559D;
    pRSP->anAudioBuffer[0x127] = 0x001F;
    pRSP->anAudioBuffer[0x128] = 0xFF02;
    pRSP->anAudioBuffer[0x129] = 0x297A;
    pRSP->anAudioBuffer[0x12A] = 0x5720;
    pRSP->anAudioBuffer[0x12B] = 0x0063;
    pRSP->anAudioBuffer[0x12C] = 0xFF10;
    pRSP->anAudioBuffer[0x12D] = 0x27A9;
    pRSP->anAudioBuffer[0x12E] = 0x5896;
    pRSP->anAudioBuffer[0x12F] = 0x00AE;
    pRSP->anAudioBuffer[0x130] = 0xFF1E;
    pRSP->anAudioBuffer[0x131] = 0x25E0;
    pRSP->anAudioBuffer[0x132] = 0x59FC;
    pRSP->anAudioBuffer[0x133] = 0x0101;
    pRSP->anAudioBuffer[0x134] = 0xFF2C;
    pRSP->anAudioBuffer[0x135] = 0x241E;
    pRSP->anAudioBuffer[0x136] = 0x5B53;
    pRSP->anAudioBuffer[0x137] = 0x015B;
    pRSP->anAudioBuffer[0x138] = 0xFF3A;
    pRSP->anAudioBuffer[0x139] = 0x2264;
    pRSP->anAudioBuffer[0x13A] = 0x5C9A;
    pRSP->anAudioBuffer[0x13B] = 0x01BE;
    pRSP->anAudioBuffer[0x13C] = 0xFF48;
    pRSP->anAudioBuffer[0x13D] = 0x20B3;
    pRSP->anAudioBuffer[0x13E] = 0x5DD0;
    pRSP->anAudioBuffer[0x13F] = 0x022A;
    pRSP->anAudioBuffer[0x140] = 0xFF56;
    pRSP->anAudioBuffer[0x141] = 0x1F0B;
    pRSP->anAudioBuffer[0x142] = 0x5EF5;
    pRSP->anAudioBuffer[0x143] = 0x029F;
    pRSP->anAudioBuffer[0x144] = 0xFF64;
    pRSP->anAudioBuffer[0x145] = 0x1D6C;
    pRSP->anAudioBuffer[0x146] = 0x6007;
    pRSP->anAudioBuffer[0x147] = 0x031C;
    pRSP->anAudioBuffer[0x148] = 0xFF71;
    pRSP->anAudioBuffer[0x149] = 0x1BD7;
    pRSP->anAudioBuffer[0x14A] = 0x6106;
    pRSP->anAudioBuffer[0x14B] = 0x03A4;
    pRSP->anAudioBuffer[0x14C] = 0xFF7E;
    pRSP->anAudioBuffer[0x14D] = 0x1A4C;
    pRSP->anAudioBuffer[0x14E] = 0x61F3;
    pRSP->anAudioBuffer[0x14F] = 0x0435;
    pRSP->anAudioBuffer[0x150] = 0xFF8A;
    pRSP->anAudioBuffer[0x151] = 0x18CB;
    pRSP->anAudioBuffer[0x152] = 0x62CB;
    pRSP->anAudioBuffer[0x153] = 0x04D1;
    pRSP->anAudioBuffer[0x154] = 0xFF96;
    pRSP->anAudioBuffer[0x155] = 0x1756;
    pRSP->anAudioBuffer[0x156] = 0x638F;
    pRSP->anAudioBuffer[0x157] = 0x0577;
    pRSP->anAudioBuffer[0x158] = 0xFFA1;
    pRSP->anAudioBuffer[0x159] = 0x15EB;
    pRSP->anAudioBuffer[0x15A] = 0x643F;
    pRSP->anAudioBuffer[0x15B] = 0x0628;
    pRSP->anAudioBuffer[0x15C] = 0xFFAC;
    pRSP->anAudioBuffer[0x15D] = 0x148C;
    pRSP->anAudioBuffer[0x15E] = 0x64D9;
    pRSP->anAudioBuffer[0x15F] = 0x06E4;
    pRSP->anAudioBuffer[0x160] = 0xFFB6;
    pRSP->anAudioBuffer[0x161] = 0x1338;
    pRSP->anAudioBuffer[0x162] = 0x655E;
    pRSP->anAudioBuffer[0x163] = 0x07AB;
    pRSP->anAudioBuffer[0x164] = 0xFFBF;
    pRSP->anAudioBuffer[0x165] = 0x11F0;
    pRSP->anAudioBuffer[0x166] = 0x65CD;
    pRSP->anAudioBuffer[0x167] = 0x087D;
    pRSP->anAudioBuffer[0x168] = 0xFFC8;
    pRSP->anAudioBuffer[0x169] = 0x10B4;
    pRSP->anAudioBuffer[0x16A] = 0x6626;
    pRSP->anAudioBuffer[0x16B] = 0x095A;
    pRSP->anAudioBuffer[0x16C] = 0xFFD0;
    pRSP->anAudioBuffer[0x16D] = 0x0F83;
    pRSP->anAudioBuffer[0x16E] = 0x6669;
    pRSP->anAudioBuffer[0x16F] = 0x0A44;
    pRSP->anAudioBuffer[0x170] = 0xFFD8;
    pRSP->anAudioBuffer[0x171] = 0x0E5F;
    pRSP->anAudioBuffer[0x172] = 0x6696;
    pRSP->anAudioBuffer[0x173] = 0x0B39;
    pRSP->anAudioBuffer[0x174] = 0xFFDF;
    pRSP->anAudioBuffer[0x175] = 0x0D46;
    pRSP->anAudioBuffer[0x176] = 0x66AD;
    pRSP->anAudioBuffer[0x177] = 0x0C39;

    return true;
}

static inline bool rspAInterleave4(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nLeft = (s32)(nCommandLo >> 16) / 2;
    u16 nRight = (s32)(nCommandLo & 0xFFFF) / 2;
    u32 nDMEMOut = pRSP->nAudioDMEMOut[0];
    u32 iIndex;
    u32 iIndex2;

    for (iIndex = 0, iIndex2 = 0; iIndex < pRSP->nAudioCount[0]; iIndex++, iIndex2++) {
        pRSP->anAudioBuffer[nDMEMOut + 2 * iIndex + 0] = pRSP->anAudioBuffer[nLeft + iIndex2];
        pRSP->anAudioBuffer[nDMEMOut + 2 * iIndex + 1] = pRSP->anAudioBuffer[nRight + iIndex2];
    }

    return true;
}

static inline bool rspADMEMMove4(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nDMEMOut = (s32)(nCommandLo >> 16) / 2;
    u16 nCount = nCommandLo & 0xFFFF;
    u32 nDMEMIn = (nCommandHi & 0xFFFF) / 2;

    xlHeapCopy(&pRSP->anAudioBuffer[nDMEMOut], &pRSP->anAudioBuffer[nDMEMIn], nCount);
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI4.s")
#else
static bool rspParseABI4(Rsp* pRSP, RspTask* pTask) {
    u32 nCommandLo;
    u32 nCommandHi;
    u32* pABI32;
    u32* pABILast32;
    u32 nSize;
    s32 pad[2];

    nSize = pTask->nLengthMBI & 0x7FFFFF;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pABI32, pTask->nOffsetMBI, NULL)) {
        return false;
    }
    pABILast32 = pABI32 + (nSize >> 2);

    if (nFirstTime_2796) {
        nFirstTime_2796 = false;
    }

    while (pABI32 < pABILast32) {
        nCommandLo = pABI32[1];
        nCommandHi = pABI32[0];
        pABI32 += 2;
        switch (nCommandHi >> 24) {
            case 0:
                break;
            case 1:
                rspAADPCMDec1Fast(pRSP, nCommandLo, nCommandHi);
                break;
            case 2:
                rspAClearBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 4:
                rspANMix2(pRSP, nCommandLo, nCommandHi);
                break;
            case 5:
                rspAResample2(pRSP, nCommandLo, nCommandHi);
                break;
            case 6:
                rspASResample2(pRSP, nCommandLo, nCommandHi);
                break;
            case 8:
                rspASetBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 10:
                rspADMEMMove4(pRSP, nCommandLo, nCommandHi);
                break;
            case 11:
                rspALoadADPCM2(pRSP, nCommandLo, nCommandHi);
                PAD_STACK();
                break;
            case 12:
                rspAMix2(pRSP, nCommandLo, nCommandHi);
                break;
            case 13:
                rspAInterleave4(pRSP, nCommandLo, nCommandHi);
                break;
            case 14:
                rspAPoleFilter1(pRSP, nCommandLo, nCommandHi);
                break;
            case 15:
                rspASetLoop2(pRSP, nCommandLo, nCommandHi);
                break;
            case 16:
                rspADMEMCopy2(pRSP, nCommandLo, nCommandHi);
                break;
            case 17:
                rspAHalfCut2(pRSP, nCommandLo, nCommandHi);
                break;
            case 18:
                rspASetEnvParam2(pRSP, nCommandLo, nCommandHi);
                break;
            case 19:
                rspAEnvMixer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 20:
                rspALoadBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 21:
                rspASaveBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 22:
                rspASetEnvParam22(pRSP, nCommandLo, nCommandHi);
                break;
            case 23:
                rspAPCM8Dec2(pRSP, nCommandLo, nCommandHi);
                break;
            case 24:
                rspADistFilter2(pRSP, nCommandLo, nCommandHi);
                break;
            case 26:
                rspAWMEMCopy2(pRSP, nCommandLo, nCommandHi);
                break;
            default:
                return false;
        }
    }

    PAD_STACK();
    PAD_STACK();
    return true;
}
#endif

static bool rspCreateJPEGArrays(Rsp* pRSP) {
    pRSP->Coeff = (s32*)pRSP->pDMEM;
    pRSP->Coeff[0] = 0x1000;
    pRSP->Coeff[1] = 0x1000;
    pRSP->Coeff[2] = 0x1000;
    pRSP->Coeff[3] = 0x1000;
    pRSP->Coeff[4] = 0x1000;
    pRSP->Coeff[5] = 0x1000;
    pRSP->Coeff[6] = 0x1000;
    pRSP->Coeff[7] = 0x1000;
    pRSP->Coeff[8] = 0x1631;
    pRSP->Coeff[9] = 0x12D0;
    pRSP->Coeff[10] = 0xC92;
    pRSP->Coeff[11] = 0x46A;
    pRSP->Coeff[12] = -0x46A;
    pRSP->Coeff[13] = -0xC92;
    pRSP->Coeff[14] = -0x12D0;
    pRSP->Coeff[15] = -0x1631;
    pRSP->Coeff[16] = 0x14E8;
    pRSP->Coeff[17] = 0x8A9;
    pRSP->Coeff[18] = -0x8A9;
    pRSP->Coeff[19] = -0x14E8;
    pRSP->Coeff[20] = -0x14E8;
    pRSP->Coeff[21] = -0x8A9;
    pRSP->Coeff[22] = 0x8A9;
    pRSP->Coeff[23] = 0x14E8;
    pRSP->Coeff[24] = 0x12D0;
    pRSP->Coeff[25] = -0x46A;
    pRSP->Coeff[26] = -0x1631;
    pRSP->Coeff[27] = -0xC92;
    pRSP->Coeff[28] = 0xC92;
    pRSP->Coeff[29] = 0x1631;
    pRSP->Coeff[30] = 0x46A;
    pRSP->Coeff[31] = -0x12D0;
    pRSP->Coeff[32] = 0x1000;
    pRSP->Coeff[33] = -0x1000;
    pRSP->Coeff[34] = -0x1000;
    pRSP->Coeff[35] = 0x1000;
    pRSP->Coeff[36] = 0x1000;
    pRSP->Coeff[37] = -0x1000;
    pRSP->Coeff[38] = -0x1000;
    pRSP->Coeff[39] = 0x1000;
    pRSP->Coeff[40] = 0xC92;
    pRSP->Coeff[41] = -0x1631;
    pRSP->Coeff[42] = 0x46A;
    pRSP->Coeff[43] = 0x12D0;
    pRSP->Coeff[44] = -0x12D0;
    pRSP->Coeff[45] = -0x46A;
    pRSP->Coeff[46] = 0x1631;
    pRSP->Coeff[47] = -0xC92;
    pRSP->Coeff[48] = 0x8A9;
    pRSP->Coeff[49] = -0x14E8;
    pRSP->Coeff[50] = 0x14E8;
    pRSP->Coeff[51] = -0x8A9;
    pRSP->Coeff[52] = -0x8A9;
    pRSP->Coeff[53] = 0x14E8;
    pRSP->Coeff[54] = -0x14E8;
    pRSP->Coeff[55] = 0x8A9;
    pRSP->Coeff[56] = 0x46A;
    pRSP->Coeff[57] = -0xC92;
    pRSP->Coeff[58] = 0x12D0;
    pRSP->Coeff[59] = -0x1631;
    pRSP->Coeff[60] = 0x1631;
    pRSP->Coeff[61] = -0x12D0;
    pRSP->Coeff[62] = 0xC92;
    pRSP->Coeff[63] = -0x46A;

    pRSP->QTable = (s16*)((u8*)pRSP->Coeff + 0x100);
    pRSP->QTable[0] = 0x10;
    pRSP->QTable[1] = 0x0B;
    pRSP->QTable[2] = 0x0A;
    pRSP->QTable[3] = 0x10;
    pRSP->QTable[4] = 0x18;
    pRSP->QTable[5] = 0x28;
    pRSP->QTable[6] = 0x33;
    pRSP->QTable[7] = 0x3D;
    pRSP->QTable[8] = 0x0C;
    pRSP->QTable[9] = 0x0C;
    pRSP->QTable[10] = 0x0E;
    pRSP->QTable[11] = 0x13;
    pRSP->QTable[12] = 0x1A;
    pRSP->QTable[13] = 0x3A;
    pRSP->QTable[14] = 0x3C;
    pRSP->QTable[15] = 0x37;
    pRSP->QTable[16] = 0x0E;
    pRSP->QTable[17] = 0x0D;
    pRSP->QTable[18] = 0x10;
    pRSP->QTable[19] = 0x18;
    pRSP->QTable[20] = 0x28;
    pRSP->QTable[21] = 0x39;
    pRSP->QTable[22] = 0x45;
    pRSP->QTable[23] = 0x38;
    pRSP->QTable[24] = 0x0E;
    pRSP->QTable[25] = 0x11;
    pRSP->QTable[26] = 0x16;
    pRSP->QTable[27] = 0x1D;
    pRSP->QTable[28] = 0x33;
    pRSP->QTable[29] = 0x57;
    pRSP->QTable[30] = 0x50;
    pRSP->QTable[31] = 0x3E;
    pRSP->QTable[32] = 0x12;
    pRSP->QTable[33] = 0x16;
    pRSP->QTable[34] = 0x25;
    pRSP->QTable[35] = 0x38;
    pRSP->QTable[36] = 0x44;
    pRSP->QTable[37] = 0x6D;
    pRSP->QTable[38] = 0x67;
    pRSP->QTable[39] = 0x4D;
    pRSP->QTable[40] = 0x18;
    pRSP->QTable[41] = 0x23;
    pRSP->QTable[42] = 0x37;
    pRSP->QTable[43] = 0x40;
    pRSP->QTable[44] = 0x51;
    pRSP->QTable[45] = 0x68;
    pRSP->QTable[46] = 0x71;
    pRSP->QTable[47] = 0x5C;
    pRSP->QTable[48] = 0x31;
    pRSP->QTable[49] = 0x40;
    pRSP->QTable[50] = 0x4E;
    pRSP->QTable[51] = 0x57;
    pRSP->QTable[52] = 0x67;
    pRSP->QTable[53] = 0x79;
    pRSP->QTable[54] = 0x78;
    pRSP->QTable[55] = 0x65;
    pRSP->QTable[56] = 0x48;
    pRSP->QTable[57] = 0x5C;
    pRSP->QTable[58] = 0x5F;
    pRSP->QTable[59] = 0x62;
    pRSP->QTable[60] = 0x70;
    pRSP->QTable[61] = 0x64;
    pRSP->QTable[62] = 0x67;
    pRSP->QTable[63] = 0x63;

    pRSP->Zigzag = (int*)((u8*)pRSP->QTable + 0x80);
    pRSP->Zigzag[0] = 0x00;
    pRSP->Zigzag[1] = 0x01;
    pRSP->Zigzag[2] = 0x08;
    pRSP->Zigzag[3] = 0x10;
    pRSP->Zigzag[4] = 0x09;
    pRSP->Zigzag[5] = 0x02;
    pRSP->Zigzag[6] = 0x03;
    pRSP->Zigzag[7] = 0x0A;
    pRSP->Zigzag[8] = 0x11;
    pRSP->Zigzag[9] = 0x18;
    pRSP->Zigzag[10] = 0x20;
    pRSP->Zigzag[11] = 0x19;
    pRSP->Zigzag[12] = 0x12;
    pRSP->Zigzag[13] = 0x0B;
    pRSP->Zigzag[14] = 0x04;
    pRSP->Zigzag[15] = 0x05;
    pRSP->Zigzag[16] = 0x0C;
    pRSP->Zigzag[17] = 0x13;
    pRSP->Zigzag[18] = 0x1A;
    pRSP->Zigzag[19] = 0x21;
    pRSP->Zigzag[20] = 0x28;
    pRSP->Zigzag[21] = 0x30;
    pRSP->Zigzag[22] = 0x29;
    pRSP->Zigzag[23] = 0x22;
    pRSP->Zigzag[24] = 0x1B;
    pRSP->Zigzag[25] = 0x14;
    pRSP->Zigzag[26] = 0x0D;
    pRSP->Zigzag[27] = 0x06;
    pRSP->Zigzag[28] = 0x07;
    pRSP->Zigzag[29] = 0x0E;
    pRSP->Zigzag[30] = 0x15;
    pRSP->Zigzag[31] = 0x1C;
    pRSP->Zigzag[32] = 0x23;
    pRSP->Zigzag[33] = 0x2A;
    pRSP->Zigzag[34] = 0x31;
    pRSP->Zigzag[35] = 0x38;
    pRSP->Zigzag[36] = 0x39;
    pRSP->Zigzag[37] = 0x32;
    pRSP->Zigzag[38] = 0x2B;
    pRSP->Zigzag[39] = 0x24;
    pRSP->Zigzag[40] = 0x1D;
    pRSP->Zigzag[41] = 0x16;
    pRSP->Zigzag[42] = 0x0F;
    pRSP->Zigzag[43] = 0x17;
    pRSP->Zigzag[44] = 0x1E;
    pRSP->Zigzag[45] = 0x25;
    pRSP->Zigzag[46] = 0x2C;
    pRSP->Zigzag[47] = 0x33;
    pRSP->Zigzag[48] = 0x3A;
    pRSP->Zigzag[49] = 0x3B;
    pRSP->Zigzag[50] = 0x34;
    pRSP->Zigzag[51] = 0x2D;
    pRSP->Zigzag[52] = 0x26;
    pRSP->Zigzag[53] = 0x1F;
    pRSP->Zigzag[54] = 0x27;
    pRSP->Zigzag[55] = 0x2E;
    pRSP->Zigzag[56] = 0x35;
    pRSP->Zigzag[57] = 0x3C;
    pRSP->Zigzag[58] = 0x3D;
    pRSP->Zigzag[59] = 0x36;
    pRSP->Zigzag[60] = 0x2F;
    pRSP->Zigzag[61] = 0x37;
    pRSP->Zigzag[62] = 0x3E;
    pRSP->Zigzag[63] = 0x3F;

    pRSP->rgbaBuf = (__anon_0x58360*)(u8*)pRSP->pIMEM;
    pRSP->yuvBuf = (__anon_0x583EE*)((u8*)pRSP->rgbaBuf + 0x800);
    pRSP->dctBuf = (int*)((u8*)pRSP->yuvBuf + 0x600);

    return true;
}

static void rspConvertRGBAtoYUV(Rsp* pRSP) {
    int i;
    int j;
    int Y;
    int U;
    int V;

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            Y = 0x21CBF * pRSP->rgbaBuf[i * 16 + j].r + 0x42599 * pRSP->rgbaBuf[i * 16 + j].g +
                0xCE2C * pRSP->rgbaBuf[i * 16 + j].b;
            Y >>= 16;

            U = -0x137E0 * pRSP->rgbaBuf[i * 16 + j].r - 0x26478 * pRSP->rgbaBuf[i * 16 + j].g +
                0x39C59 * pRSP->rgbaBuf[i * 16 + j].b;
            U >>= 16;

            V = 0x39C88 * pRSP->rgbaBuf[i * 16 + j].r - 0x30624 * pRSP->rgbaBuf[i * 16 + j].g -
                0x9663 * pRSP->rgbaBuf[i * 16 + j].b;
            V >>= 16;

            pRSP->yuvBuf[i * 16 + j].y = Y + 0x10;
            pRSP->yuvBuf[i * 16 + j].u = U + 0x80;
            pRSP->yuvBuf[i * 16 + j].v = V + 0x80;
        }
    }
}

static void rspYUVtoDCTBuf(Rsp* pRSP) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[i * 8 + j] = pRSP->yuvBuf[i * 16 + j].y;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0x40 + i * 8 + j] = pRSP->yuvBuf[i * 16 + (j + 8)].y;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0x80 + i * 8 + j] = pRSP->yuvBuf[(i + 8) * 16 + j].y;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0xC0 + i * 8 + j] = pRSP->yuvBuf[(i + 8) * 16 + (j + 8)].y;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0x100 + i * 8 + j] = pRSP->yuvBuf[(i << 1) * 16 + (j << 1)].u;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0x140 + i * 8 + j] = pRSP->yuvBuf[(i << 1) * 16 + (j << 1)].v;
        }
    }
}

static void rspDCT(Rsp* pRSP) {
    s32 c;
    s32 i;
    s32 j;
    s32 k;
    s32 dd;
    s16 t[8][8];

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += pRSP->Coeff[j * 8 + k] * pRSP->dctBuf[c * 0x40 + i * 8 + k];
                }
                t[i][j] = (dd + 0x800) >> 12;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += t[k][i] * pRSP->Coeff[j * 8 + k];
                }
                pRSP->dctBuf[c * 0x40 + j * 8 + i] = (dd + 0x4000) >> 15;
            }
        }
    }
}

static void rspQuantize(Rsp* pRSP, s32 scale) {
    s32 c;
    s32 i;
    s32 j;
    s16 q;
    s16 s;

    switch (scale) {
        case -2:
            s = 1;
            break;
        case -1:
            s = 2;
            break;
        case 0:
            return;
        default:
            s = scale * 4;
            break;
    }

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                q = (((4 * pRSP->QTable[i * 8 + j] * s) >> 2) + 2) >> 2;
                if (pRSP->dctBuf[c * 0x40 + i * 8 + j] >= 0) {
                    pRSP->dctBuf[c * 0x40 + i * 8 + j] = (pRSP->dctBuf[c * 0x40 + i * 8 + j] + (q >> 1)) / q;
                } else {
                    pRSP->dctBuf[c * 0x40 + i * 8 + j] = (pRSP->dctBuf[c * 0x40 + i * 8 + j] - (q >> 1)) / q;
                }
            }
        }
    }
}

void rspUndoQuantize(Rsp* pRSP, s32 scale) {
    s32 c;
    s32 i;
    s32 j;
    s16 q;
    s16 s;

    switch (scale) {
        case -2:
            s = 1;
            break;
        case -1:
            s = 2;
            break;
        case 0:
            return;
        default:
            s = scale * 4;
            break;
    }

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                q = (((4 * pRSP->QTable[i * 8 + j] * s) >> 2) + 2) >> 2;
                if (pRSP->dctBuf[c * 0x40 + i * 8 + j] > 0) {
                    pRSP->dctBuf[c * 0x40 + i * 8 + j] = pRSP->dctBuf[c * 0x40 + i * 8 + j] * q - (q >> 1);
                } else if (pRSP->dctBuf[c * 0x40 + i * 8 + j] < 0) {
                    pRSP->dctBuf[c * 0x40 + i * 8 + j] = pRSP->dctBuf[c * 0x40 + i * 8 + j] * q + (q >> 1);
                }
            }
        }
    }
}

void rspUndoDCT(Rsp* pRSP) {
    s32 c;
    s32 i;
    s32 j;
    s32 k;
    s32 dd;
    s16 t[8][8];

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += pRSP->Coeff[k * 8 + j] * pRSP->dctBuf[c * 0x40 + i * 8 + k];
                }
                t[i][j] = (dd + 0x800) >> 12;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += t[k][i] * pRSP->Coeff[k * 8 + j];
                }
                pRSP->dctBuf[c * 0x40 + j * 8 + i] = (dd + 0x4000) >> 15;
                if (pRSP->dctBuf[c * 0x40 + j * 8 + i] < 0) {
                    pRSP->dctBuf[c * 0x40 + j * 8 + i] = 0;
                }
            }
        }
    }
}

void rspUndoYUVtoDCTBuf(Rsp* pRSP) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[i * 16 + j].y = pRSP->dctBuf[i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[i * 16 + (j + 8)].y = pRSP->dctBuf[0x40 + i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[(i + 8) * 16 + j].y = pRSP->dctBuf[0x80 + i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[(i + 8) * 16 + (j + 8)].y = pRSP->dctBuf[0xC0 + i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[(i << 1) * 16 + (j << 1)].u = pRSP->dctBuf[0x100 + i * 8 + j];
            pRSP->yuvBuf[((i << 1) + 1) * 16 + (j << 1)].u = pRSP->dctBuf[0x100 + i * 8 + j];
            pRSP->yuvBuf[(i << 1) * 16 + ((j << 1) + 1)].u = pRSP->dctBuf[0x100 + i * 8 + j];
            pRSP->yuvBuf[((i << 1) + 1) * 16 + ((j << 1) + 1)].u = pRSP->dctBuf[0x100 + i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[(i << 1) * 16 + (j << 1)].v = pRSP->dctBuf[0x140 + i * 8 + j];
            pRSP->yuvBuf[((i << 1) + 1) * 16 + (j << 1)].v = pRSP->dctBuf[0x140 + i * 8 + j];
            pRSP->yuvBuf[(i << 1) * 16 + ((j << 1) + 1)].v = pRSP->dctBuf[0x140 + i * 8 + j];
            pRSP->yuvBuf[((i << 1) + 1) * 16 + ((j << 1) + 1)].v = pRSP->dctBuf[0x140 + i * 8 + j];
        }
    }
}

void rspFormatYUV(Rsp* pRSP, char* imgBuf);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFormatYUV.s")

static bool rspParseJPEG_Encode(Rsp* pRSP, RspTask* pTask);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseJPEG_Encode.s")

static bool rspParseJPEG_Decode(Rsp* pRSP, RspTask* pTask);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseJPEG_Decode.s")

static bool rspCreateJPEGArraysZ(Rsp* pRSP, s32 qYAddress, s32 qCbAddress, s32 qCrAddress) {
    pRSP->Coeff = (s32*)pRSP->pDMEM;
    pRSP->Coeff[0] = 0x1000;
    pRSP->Coeff[1] = 0x1000;
    pRSP->Coeff[2] = 0x1000;
    pRSP->Coeff[3] = 0x1000;
    pRSP->Coeff[4] = 0x1000;
    pRSP->Coeff[5] = 0x1000;
    pRSP->Coeff[6] = 0x1000;
    pRSP->Coeff[7] = 0x1000;
    pRSP->Coeff[8] = 0x1631;
    pRSP->Coeff[9] = 0x12D0;
    pRSP->Coeff[10] = 0xC92;
    pRSP->Coeff[11] = 0x46A;
    pRSP->Coeff[12] = -0x46A;
    pRSP->Coeff[13] = -0xC92;
    pRSP->Coeff[14] = -0x12D0;
    pRSP->Coeff[15] = -0x1631;
    pRSP->Coeff[16] = 0x14E8;
    pRSP->Coeff[17] = 0x8A9;
    pRSP->Coeff[18] = -0x8A9;
    pRSP->Coeff[19] = -0x14E8;
    pRSP->Coeff[20] = -0x14E8;
    pRSP->Coeff[21] = -0x8A9;
    pRSP->Coeff[22] = 0x8A9;
    pRSP->Coeff[23] = 0x14E8;
    pRSP->Coeff[24] = 0x12D0;
    pRSP->Coeff[25] = -0x46A;
    pRSP->Coeff[26] = -0x1631;
    pRSP->Coeff[27] = -0xC92;
    pRSP->Coeff[28] = 0xC92;
    pRSP->Coeff[29] = 0x1631;
    pRSP->Coeff[30] = 0x46A;
    pRSP->Coeff[31] = -0x12D0;
    pRSP->Coeff[32] = 0x1000;
    pRSP->Coeff[33] = -0x1000;
    pRSP->Coeff[34] = -0x1000;
    pRSP->Coeff[35] = 0x1000;
    pRSP->Coeff[36] = 0x1000;
    pRSP->Coeff[37] = -0x1000;
    pRSP->Coeff[38] = -0x1000;
    pRSP->Coeff[39] = 0x1000;
    pRSP->Coeff[40] = 0xC92;
    pRSP->Coeff[41] = -0x1631;
    pRSP->Coeff[42] = 0x46A;
    pRSP->Coeff[43] = 0x12D0;
    pRSP->Coeff[44] = -0x12D0;
    pRSP->Coeff[45] = -0x46A;
    pRSP->Coeff[46] = 0x1631;
    pRSP->Coeff[47] = -0xC92;
    pRSP->Coeff[48] = 0x8A9;
    pRSP->Coeff[49] = -0x14E8;
    pRSP->Coeff[50] = 0x14E8;
    pRSP->Coeff[51] = -0x8A9;
    pRSP->Coeff[52] = -0x8A9;
    pRSP->Coeff[53] = 0x14E8;
    pRSP->Coeff[54] = -0x14E8;
    pRSP->Coeff[55] = 0x8A9;
    pRSP->Coeff[56] = 0x46A;
    pRSP->Coeff[57] = -0xC92;
    pRSP->Coeff[58] = 0x12D0;
    pRSP->Coeff[59] = -0x1631;
    pRSP->Coeff[60] = 0x1631;
    pRSP->Coeff[61] = -0x12D0;
    pRSP->Coeff[62] = 0xC92;
    pRSP->Coeff[63] = -0x46A;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pRSP->QYTable, (u32)qYAddress, NULL)) {
        return false;
    }
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pRSP->QCbTable, (u32)qCbAddress, NULL)) {
        return false;
    }
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pRSP->QCrTable, (u32)qCrAddress, NULL)) {
        return false;
    }

    pRSP->dctBuf = (int*)((u8*)pRSP->Coeff + 0x100);
    return true;
}

static void rspDCTZ(Rsp* pRSP) {
    s32 c;
    s32 i;
    s32 j;
    s32 k;
    s32 dd;
    s16 t[8][8];

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += pRSP->Coeff[j * 8 + k] * pRSP->dctBuf[c * 0x40 + i * 8 + k];
                }
                t[i][j] = (dd + 0x800) >> 12;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += t[k][i] * pRSP->Coeff[j * 8 + k];
                }
                pRSP->dctBuf[c * 0x40 + i * 8 + j] = (dd + 0x4000) >> 15;
            }
        }
    }
}

static void rspQuantizeZ(Rsp* pRSP, s16* dataBuf) {
    s32 c;
    s32 i;
    s32 j;

    for (c = 0; c < 4; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dataBuf[c * 0x40 + i * 8 + j] >>= 4;
                dataBuf[c * 0x40 + i * 8 + j] /= pRSP->QYTable[i * 8 + j];
            }
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dataBuf[0x100 + i * 8 + j] >>= 4;
            dataBuf[0x100 + i * 8 + j] /= pRSP->QCbTable[i * 8 + j];
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dataBuf[0x140 + i * 8 + j] >>= 4;
            dataBuf[0x140 + i * 8 + j] /= pRSP->QCrTable[i * 8 + j];
        }
    }
}

void rspZigzagDataZ(Rsp* pRSP, s16* dataBuf) {
    s32 c;

    for (c = 0; c < 6; c++, dataBuf += 0x40) {
        dataBuf[0] = pRSP->dctBuf[c * 0x40 + 0];
        dataBuf[1] = pRSP->dctBuf[c * 0x40 + 8];
        dataBuf[2] = pRSP->dctBuf[c * 0x40 + 1];
        dataBuf[3] = pRSP->dctBuf[c * 0x40 + 2];
        dataBuf[4] = pRSP->dctBuf[c * 0x40 + 9];
        dataBuf[5] = pRSP->dctBuf[c * 0x40 + 16];
        dataBuf[6] = pRSP->dctBuf[c * 0x40 + 24];
        dataBuf[7] = pRSP->dctBuf[c * 0x40 + 17];
        dataBuf[8] = pRSP->dctBuf[c * 0x40 + 10];
        dataBuf[9] = pRSP->dctBuf[c * 0x40 + 3];
        dataBuf[10] = pRSP->dctBuf[c * 0x40 + 4];
        dataBuf[11] = pRSP->dctBuf[c * 0x40 + 11];
        dataBuf[12] = pRSP->dctBuf[c * 0x40 + 18];
        dataBuf[13] = pRSP->dctBuf[c * 0x40 + 25];
        dataBuf[14] = pRSP->dctBuf[c * 0x40 + 32];
        dataBuf[15] = pRSP->dctBuf[c * 0x40 + 40];
        dataBuf[16] = pRSP->dctBuf[c * 0x40 + 33];
        dataBuf[17] = pRSP->dctBuf[c * 0x40 + 26];
        dataBuf[18] = pRSP->dctBuf[c * 0x40 + 19];
        dataBuf[19] = pRSP->dctBuf[c * 0x40 + 12];
        dataBuf[20] = pRSP->dctBuf[c * 0x40 + 5];
        dataBuf[21] = pRSP->dctBuf[c * 0x40 + 6];
        dataBuf[22] = pRSP->dctBuf[c * 0x40 + 13];
        dataBuf[23] = pRSP->dctBuf[c * 0x40 + 20];
        dataBuf[24] = pRSP->dctBuf[c * 0x40 + 27];
        dataBuf[25] = pRSP->dctBuf[c * 0x40 + 34];
        dataBuf[26] = pRSP->dctBuf[c * 0x40 + 41];
        dataBuf[27] = pRSP->dctBuf[c * 0x40 + 48];
        dataBuf[28] = pRSP->dctBuf[c * 0x40 + 56];
        dataBuf[29] = pRSP->dctBuf[c * 0x40 + 49];
        dataBuf[30] = pRSP->dctBuf[c * 0x40 + 42];
        dataBuf[31] = pRSP->dctBuf[c * 0x40 + 35];
        dataBuf[32] = pRSP->dctBuf[c * 0x40 + 28];
        dataBuf[33] = pRSP->dctBuf[c * 0x40 + 21];
        dataBuf[34] = pRSP->dctBuf[c * 0x40 + 14];
        dataBuf[35] = pRSP->dctBuf[c * 0x40 + 7];
        dataBuf[36] = pRSP->dctBuf[c * 0x40 + 15];
        dataBuf[37] = pRSP->dctBuf[c * 0x40 + 22];
        dataBuf[38] = pRSP->dctBuf[c * 0x40 + 29];
        dataBuf[39] = pRSP->dctBuf[c * 0x40 + 36];
        dataBuf[40] = pRSP->dctBuf[c * 0x40 + 43];
        dataBuf[41] = pRSP->dctBuf[c * 0x40 + 50];
        dataBuf[42] = pRSP->dctBuf[c * 0x40 + 57];
        dataBuf[43] = pRSP->dctBuf[c * 0x40 + 58];
        dataBuf[44] = pRSP->dctBuf[c * 0x40 + 51];
        dataBuf[45] = pRSP->dctBuf[c * 0x40 + 44];
        dataBuf[46] = pRSP->dctBuf[c * 0x40 + 37];
        dataBuf[47] = pRSP->dctBuf[c * 0x40 + 30];
        dataBuf[48] = pRSP->dctBuf[c * 0x40 + 23];
        dataBuf[49] = pRSP->dctBuf[c * 0x40 + 31];
        dataBuf[50] = pRSP->dctBuf[c * 0x40 + 38];
        dataBuf[51] = pRSP->dctBuf[c * 0x40 + 45];
        dataBuf[52] = pRSP->dctBuf[c * 0x40 + 52];
        dataBuf[53] = pRSP->dctBuf[c * 0x40 + 59];
        dataBuf[54] = pRSP->dctBuf[c * 0x40 + 60];
        dataBuf[55] = pRSP->dctBuf[c * 0x40 + 53];
        dataBuf[56] = pRSP->dctBuf[c * 0x40 + 46];
        dataBuf[57] = pRSP->dctBuf[c * 0x40 + 39];
        dataBuf[58] = pRSP->dctBuf[c * 0x40 + 47];
        dataBuf[59] = pRSP->dctBuf[c * 0x40 + 54];
        dataBuf[60] = pRSP->dctBuf[c * 0x40 + 61];
        dataBuf[61] = pRSP->dctBuf[c * 0x40 + 62];
        dataBuf[62] = pRSP->dctBuf[c * 0x40 + 55];
        dataBuf[63] = pRSP->dctBuf[c * 0x40 + 63];
    }
}

void rspUndoQuantizeZ(Rsp* pRSP, s16* dataBuf) {
    s32 c;
    s32 i;
    s32 j;

    for (c = 0; c < 4; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dataBuf[c * 0x40 + i * 8 + j] *= pRSP->QYTable[i * 8 + j];
                dataBuf[c * 0x40 + i * 8 + j] <<= 4;
            }
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dataBuf[0x100 + i * 8 + j] *= pRSP->QCbTable[i * 8 + j];
            dataBuf[0x100 + i * 8 + j] <<= 4;
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dataBuf[0x140 + i * 8 + j] *= pRSP->QCrTable[i * 8 + j];
            dataBuf[0x140 + i * 8 + j] <<= 4;
        }
    }
}

void rspUndoZigzagDataZ(Rsp* pRSP, s16* dataBuf) {
    s32 c;

    for (c = 0; c < 6; c++, dataBuf += 0x40) {
        pRSP->dctBuf[c * 0x40 + 0] = dataBuf[0];
        pRSP->dctBuf[c * 0x40 + 8] = dataBuf[1];
        pRSP->dctBuf[c * 0x40 + 1] = dataBuf[2];
        pRSP->dctBuf[c * 0x40 + 2] = dataBuf[3];
        pRSP->dctBuf[c * 0x40 + 9] = dataBuf[4];
        pRSP->dctBuf[c * 0x40 + 16] = dataBuf[5];
        pRSP->dctBuf[c * 0x40 + 24] = dataBuf[6];
        pRSP->dctBuf[c * 0x40 + 17] = dataBuf[7];
        pRSP->dctBuf[c * 0x40 + 10] = dataBuf[8];
        pRSP->dctBuf[c * 0x40 + 3] = dataBuf[9];
        pRSP->dctBuf[c * 0x40 + 4] = dataBuf[10];
        pRSP->dctBuf[c * 0x40 + 11] = dataBuf[11];
        pRSP->dctBuf[c * 0x40 + 18] = dataBuf[12];
        pRSP->dctBuf[c * 0x40 + 25] = dataBuf[13];
        pRSP->dctBuf[c * 0x40 + 32] = dataBuf[14];
        pRSP->dctBuf[c * 0x40 + 40] = dataBuf[15];
        pRSP->dctBuf[c * 0x40 + 33] = dataBuf[16];
        pRSP->dctBuf[c * 0x40 + 26] = dataBuf[17];
        pRSP->dctBuf[c * 0x40 + 19] = dataBuf[18];
        pRSP->dctBuf[c * 0x40 + 12] = dataBuf[19];
        pRSP->dctBuf[c * 0x40 + 5] = dataBuf[20];
        pRSP->dctBuf[c * 0x40 + 6] = dataBuf[21];
        pRSP->dctBuf[c * 0x40 + 13] = dataBuf[22];
        pRSP->dctBuf[c * 0x40 + 20] = dataBuf[23];
        pRSP->dctBuf[c * 0x40 + 27] = dataBuf[24];
        pRSP->dctBuf[c * 0x40 + 34] = dataBuf[25];
        pRSP->dctBuf[c * 0x40 + 41] = dataBuf[26];
        pRSP->dctBuf[c * 0x40 + 48] = dataBuf[27];
        pRSP->dctBuf[c * 0x40 + 56] = dataBuf[28];
        pRSP->dctBuf[c * 0x40 + 49] = dataBuf[29];
        pRSP->dctBuf[c * 0x40 + 42] = dataBuf[30];
        pRSP->dctBuf[c * 0x40 + 35] = dataBuf[31];
        pRSP->dctBuf[c * 0x40 + 28] = dataBuf[32];
        pRSP->dctBuf[c * 0x40 + 21] = dataBuf[33];
        pRSP->dctBuf[c * 0x40 + 14] = dataBuf[34];
        pRSP->dctBuf[c * 0x40 + 7] = dataBuf[35];
        pRSP->dctBuf[c * 0x40 + 15] = dataBuf[36];
        pRSP->dctBuf[c * 0x40 + 22] = dataBuf[37];
        pRSP->dctBuf[c * 0x40 + 29] = dataBuf[38];
        pRSP->dctBuf[c * 0x40 + 36] = dataBuf[39];
        pRSP->dctBuf[c * 0x40 + 43] = dataBuf[40];
        pRSP->dctBuf[c * 0x40 + 50] = dataBuf[41];
        pRSP->dctBuf[c * 0x40 + 57] = dataBuf[42];
        pRSP->dctBuf[c * 0x40 + 58] = dataBuf[43];
        pRSP->dctBuf[c * 0x40 + 51] = dataBuf[44];
        pRSP->dctBuf[c * 0x40 + 44] = dataBuf[45];
        pRSP->dctBuf[c * 0x40 + 37] = dataBuf[46];
        pRSP->dctBuf[c * 0x40 + 30] = dataBuf[47];
        pRSP->dctBuf[c * 0x40 + 23] = dataBuf[48];
        pRSP->dctBuf[c * 0x40 + 31] = dataBuf[49];
        pRSP->dctBuf[c * 0x40 + 38] = dataBuf[50];
        pRSP->dctBuf[c * 0x40 + 45] = dataBuf[51];
        pRSP->dctBuf[c * 0x40 + 52] = dataBuf[52];
        pRSP->dctBuf[c * 0x40 + 59] = dataBuf[53];
        pRSP->dctBuf[c * 0x40 + 60] = dataBuf[54];
        pRSP->dctBuf[c * 0x40 + 53] = dataBuf[55];
        pRSP->dctBuf[c * 0x40 + 46] = dataBuf[56];
        pRSP->dctBuf[c * 0x40 + 39] = dataBuf[57];
        pRSP->dctBuf[c * 0x40 + 47] = dataBuf[58];
        pRSP->dctBuf[c * 0x40 + 54] = dataBuf[59];
        pRSP->dctBuf[c * 0x40 + 61] = dataBuf[60];
        pRSP->dctBuf[c * 0x40 + 62] = dataBuf[61];
        pRSP->dctBuf[c * 0x40 + 55] = dataBuf[62];
        pRSP->dctBuf[c * 0x40 + 63] = dataBuf[63];
    }
}

void rspUndoDCTZ(Rsp* pRSP) {
    s32 c;
    s32 i;
    s32 j;
    s32 k;
    s32 dd;
    s16 t[8][8];

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += pRSP->Coeff[k * 8 + j] * pRSP->dctBuf[c * 0x40 + i * 8 + k];
                }
                t[i][j] = (dd + 0x800) >> 12;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += t[k][i] * pRSP->Coeff[k * 8 + j];
                }
                pRSP->dctBuf[c * 0x40 + i * 8 + j] = (dd + 0x4000) >> 15;
            }
        }
    }
}

bool rspUndoLoadColorBufferZ(Rsp* pRSP, s32 r, s32 g, s32 b, s16* imgBuf, s32 index) {
    if (r <= 0) {
        r = 0;
    } else if (r > 0xFF0) {
        r = 31;
    } else {
        r = (r >> 7) & 0x1F;
    }

    if (g <= 0) {
        g = 0;
    } else if (g > 0xFF0) {
        g = 31;
    } else {
        g = (g >> 7) & 0x1F;
    }

    if (b <= 0) {
        b = 0;
    } else if (b > 0xFF0) {
        b = 31;
    } else {
        b = (b >> 7) & 0x1F;
    }

    imgBuf[index] = (r << 11) | (g << 6) | (b << 1) | 1;
    return true;
}

bool rspUndoRecon420Z(Rsp* pRSP, s16* imgBuf) {
    s32 i;
    s32 j;
    s32 r;
    s32 g;
    s32 b;
    s32 y;
    s32 u;
    s32 v;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            imgBuf[i * 32 + j + 0] = 0;
            imgBuf[i * 32 + j + 8] = 0;
            imgBuf[i * 32 + j + 16] = 0;
            imgBuf[i * 32 + j + 24] = 0;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            y = pRSP->dctBuf[0x000 + i * 8 + j] + 0x800;
            u = pRSP->dctBuf[0x100 + (i >> 1) * 8 + (j >> 1)];
            v = pRSP->dctBuf[0x140 + (i >> 1) * 8 + (j >> 1)];
            r = y + ((v * 0x670A) >> 16) + v;
            g = y - (((u * 0x5824) >> 16) + ((v * 0xB6E3) >> 16));
            b = y + ((u * 0xC5E3) >> 16) + u;
            rspUndoLoadColorBufferZ(pRSP, r, g, b, imgBuf, i * 16 + j);

            y = pRSP->dctBuf[0x080 + i * 8 + j] + 0x800;
            u = pRSP->dctBuf[0x100 + ((i + 8) >> 1) * 8 + (j >> 1)];
            v = pRSP->dctBuf[0x140 + ((i + 8) >> 1) * 8 + (j >> 1)];
            r = y + ((v * 0x670A) >> 16) + v;
            g = y - (((u * 0x5824) >> 16) + ((v * 0xB6E3) >> 16));
            b = y + ((u * 0xC5E3) >> 16) + u;
            rspUndoLoadColorBufferZ(pRSP, r, g, b, imgBuf, i * 16 + j + 0x80);

            y = pRSP->dctBuf[0x040 + i * 8 + j] + 0x800;
            u = pRSP->dctBuf[0x104 + (i >> 1) * 8 + (j >> 1)];
            v = pRSP->dctBuf[0x144 + (i >> 1) * 8 + (j >> 1)];
            r = y + ((v * 0x670A) >> 16) + v;
            g = y - (((u * 0x5824) >> 16) + ((v * 0xB6E3) >> 16));
            b = y + ((u * 0xC5E3) >> 16) + u;
            rspUndoLoadColorBufferZ(pRSP, r, g, b, imgBuf, i * 16 + 8 + j);

            y = pRSP->dctBuf[0x0C0 + i * 8 + j] + 0x800;
            u = pRSP->dctBuf[0x104 + ((i + 8) >> 1) * 8 + (j >> 1)];
            v = pRSP->dctBuf[0x144 + ((i + 8) >> 1) * 8 + (j >> 1)];
            r = y + ((v * 0x670A) >> 16) + v;
            g = y - (((u * 0x5824) >> 16) + ((v * 0xB6E3) >> 16));
            b = y + ((u * 0xC5E3) >> 16) + u;
            rspUndoLoadColorBufferZ(pRSP, r, g, b, imgBuf, i * 16 + j + 0x88);
        }
    }

    return true;
}

static inline bool rspLoadColorBufferZ(Rsp* pRSP, s32* r, s32* g, s32* b, s16* imgBuf, s32 index) {
    *r = (imgBuf[index] >> 11) & 0x1F;
    *g = (imgBuf[index] >> 6) & 0x1F;
    *b = (imgBuf[index] >> 1) & 0x1F;
    return true;
}

bool rspRecon420Z(Rsp* pRSP, s16* imgBuf) {
    s32 i;
    s32 j;
    s32 r;
    s32 g;
    s32 b;
    s32 y;
    s32 u;
    s32 v;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            rspLoadColorBufferZ(pRSP, &r, &g, &b, imgBuf, i * 16 + j);
            y = g + (b << 16) / 116195 + (r << 16) / 91914;
            u = ((b - y) << 16) / 116195;
            v = ((r - y) << 16) / 91914;
            pRSP->dctBuf[0x000 + 8 * i + j] = y - 0x800;
            pRSP->dctBuf[0x100 + (i >> 1) * 8 + (j >> 1)] = u;
            pRSP->dctBuf[0x140 + (i >> 1) * 8 + (j >> 1)] = v;

            rspLoadColorBufferZ(pRSP, &r, &g, &b, imgBuf, i * 16 + j + 0x80);
            y = g + (b << 16) / 116195 + (r << 16) / 91914;
            u = ((b - y) << 16) / 116195;
            v = ((r - y) << 16) / 91914;
            pRSP->dctBuf[0x080 + 8 * i + j] = y - 0x800;
            pRSP->dctBuf[0x100 + ((i + 8) >> 1) * 8 + (j >> 1)] = u;
            pRSP->dctBuf[0x140 + ((i + 8) >> 1) * 8 + (j >> 1)] = v;

            rspLoadColorBufferZ(pRSP, &r, &g, &b, imgBuf, i * 16 + 8 + j);
            y = g + (b << 16) / 116195 + (r << 16) / 91914;
            u = ((b - y) << 16) / 116195;
            v = ((r - y) << 16) / 91914;
            pRSP->dctBuf[0x040 + 8 * i + j] = y - 0x800;
            pRSP->dctBuf[0x104 + (i >> 1) * 8 + (j >> 1)] = u;
            pRSP->dctBuf[0x144 + (i >> 1) * 8 + (j >> 1)] = v;

            rspLoadColorBufferZ(pRSP, &r, &g, &b, imgBuf, i * 16 + j + 0x88);
            y = g + (b << 16) / 116195 + (r << 16) / 91914;
            u = ((b - y) << 16) / 116195;
            v = ((r - y) << 16) / 91914;
            pRSP->dctBuf[0x0C0 + 8 * i + j] = y - 0x800;
            pRSP->dctBuf[0x104 + ((i + 8) >> 1) * 8 + (j >> 1)] = u;
            pRSP->dctBuf[0x144 + ((i + 8) >> 1) * 8 + (j >> 1)] = v;
        }
    }
    return true;
}

static bool rspParseJPEG_EncodeZ(Rsp* pRSP, RspTask* pTask) {
    s32 y;
    s32 pad;
    s16* temp;
    s16* temp2;
    u64* system_imb;
    u32* infoStruct;
    s32 size;
    s32 pad2[3];

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &infoStruct, pTask->nOffsetMBI, NULL)) {
        return false;
    }

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &system_imb, infoStruct[0], NULL)) {
        return false;
    }

    size = infoStruct[1];
    rspCreateJPEGArraysZ(pRSP, infoStruct[3], infoStruct[4], infoStruct[5]);
    temp2 = (s16*)system_imb;

    for (y = 0; y < size; y++) {
        rspRecon420Z(pRSP, temp2);
        rspDCTZ(pRSP);
        rspZigzagDataZ(pRSP, temp2);
        rspQuantizeZ(pRSP, temp2);
        temp2 += 0x180;
    }

    return true;
}

static bool rspParseJPEG_DecodeZ(Rsp* pRSP, RspTask* pTask) {
    s32 y;
    s32 pad;
    s16* temp;
    s16* temp2;
    u64* system_imb;
    u32* infoStruct;
    s32 size;
    s32 pad2[3];

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &infoStruct, pTask->nOffsetMBI, NULL)) {
        return false;
    }

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &system_imb, infoStruct[0], NULL)) {
        return false;
    }

    size = infoStruct[1];
    rspCreateJPEGArraysZ(pRSP, infoStruct[3], infoStruct[4], infoStruct[5]);
    temp2 = (s16*)system_imb;

    for (y = 0; y < size; y++) {
        rspUndoQuantizeZ(pRSP, temp2);
        rspUndoZigzagDataZ(pRSP, temp2);
        rspUndoDCTZ(pRSP);
        rspUndoRecon420Z(pRSP, temp2);
        temp2 += 0x180;
    }

    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/Matrix4by4Identity.s")
#else
static bool Matrix4by4Identity(Mtx44Ptr matrix4b4) {
    matrix4b4[0][0] = 1.0f;
    matrix4b4[1][0] = 0.0f;
    matrix4b4[2][0] = 0.0f;
    matrix4b4[3][0] = 0.0f;
    matrix4b4[0][1] = 0.0f;
    matrix4b4[1][1] = 1.0f;
    matrix4b4[2][1] = 0.0f;
    matrix4b4[3][1] = 0.0f;
    matrix4b4[0][2] = 0.0f;
    matrix4b4[1][2] = 0.0f;
    matrix4b4[2][2] = 1.0f;
    matrix4b4[3][2] = 0.0f;
    matrix4b4[0][3] = 0.0f;
    matrix4b4[1][3] = 0.0f;
    matrix4b4[2][3] = 0.0f;
    matrix4b4[3][3] = 1.0f;

    return true;
}
#endif

static bool rspFillObjSprite(Rsp* pRSP, s32 nAddress, uObjSprite* pSprite) {
    u16* pnData16;
    u8* pnData8;
    u8* pObjSprite;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pObjSprite, nAddress, NULL)) {
        return false;
    }

    pnData8 = (u8*)pObjSprite;
    pnData16 = (u16*)pObjSprite;

    pSprite->s.objX = pnData16[0];
    pSprite->s.scaleW = pnData16[1];
    pSprite->s.imageW = pnData16[2];
    pSprite->s.paddingX = pnData16[3];
    pSprite->s.objY = pnData16[4];
    pSprite->s.scaleH = pnData16[5];
    pSprite->s.imageH = pnData16[6];
    pSprite->s.paddingY = pnData16[7];
    pSprite->s.imageStride = pnData16[8];
    pSprite->s.imageAdrs = pnData16[9];
    pSprite->s.imageFmt = pnData8[20];
    pSprite->s.imageSiz = pnData8[21];
    pSprite->s.imagePal = pnData8[22];
    pSprite->s.imageFlags = pnData8[23];

    return true;
}

bool rspFillObjBgScale(Rsp* pRSP, s32 nAddress, uObjBg* pBg) {
    u8* pnData8;
    u8* pObjBg;
    u16* pnData16;
    u32* pnData32;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pObjBg, nAddress, NULL)) {
        return false;
    }

    pnData8 = (u8*)pObjBg;
    pnData16 = (u16*)pObjBg;
    pnData32 = (u32*)pObjBg;

    pBg->s.imageX = pnData16[0];
    pBg->s.imageW = pnData16[1];
    pBg->s.frameX = pnData16[2];
    pBg->s.frameW = pnData16[3];
    pBg->s.imageY = pnData16[4];
    pBg->s.imageH = pnData16[5];
    pBg->s.frameY = pnData16[6];
    pBg->s.frameH = pnData16[7];
    pBg->s.imagePtr = pnData32[4];
    pBg->s.imageLoad = pnData16[10];
    pBg->s.imageFmt = pnData8[22];
    pBg->s.imageSiz = pnData8[23];
    pBg->s.imagePal = pnData16[12];
    pBg->s.imageFlip = pnData16[13];
    pBg->s.scaleW = pnData16[14];
    pBg->s.scaleH = pnData16[15];
    pBg->s.imageYorig = pnData32[8];

    return true;
}

bool rspFillObjBg(Rsp* pRSP, s32 nAddress, uObjBg* pBg) {
    u8* pnData8;
    u8* pObjBg;
    u16* pnData16;
    u32* pnData32;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pObjBg, nAddress, NULL)) {
        return false;
    }

    pnData8 = (u8*)pObjBg;
    pnData16 = (u16*)pObjBg;
    pnData32 = (u32*)pObjBg;

    pBg->b.imageX = pnData16[0];
    pBg->b.imageW = pnData16[1];
    pBg->b.frameX = pnData16[2];
    pBg->b.frameW = pnData16[3];
    pBg->b.imageY = pnData16[4];
    pBg->b.imageH = pnData16[5];
    pBg->b.frameY = pnData16[6];
    pBg->b.frameH = pnData16[7];
    pBg->b.imagePtr = pnData32[4];
    pBg->b.imageLoad = pnData16[10];
    pBg->b.imageFmt = pnData8[22];
    pBg->b.imageSiz = pnData8[23];
    pBg->b.imagePal = pnData16[12];
    pBg->b.imageFlip = pnData16[13];
    pBg->b.tmemW = pnData16[14];
    pBg->b.tmemH = pnData16[15];
    pBg->b.tmemLoadSH = pnData16[16];
    pBg->b.tmemLoadTH = pnData16[17];
    pBg->b.tmemSizeW = pnData16[18];
    pBg->b.tmemSize = pnData16[19];

    return true;
}

static inline bool rspSetTile(Frame* pFrame, Tile* pTile, s32 nSize, s32 nTmem, s32 nTLUT, s32 nFormat, s32 nMaskS,
                              s32 nMaskT, s32 nModeS, s32 nModeT, s32 nShiftS, s32 nShiftT) {
    pTile->nSize = nSize;
    pTile->nTMEM = nTmem;
    pTile->iTLUT = nTLUT;
    pTile->nFormat = nFormat;
    pTile->nMaskS = nMaskS;
    pTile->nMaskT = nMaskT;
    pTile->nModeS = nModeS;
    pTile->nModeT = nModeT;
    pTile->nShiftS = nShiftS;
    pTile->nShiftT = nShiftT;
    if (!frameDrawReset(pFrame, 1)) {
        return false;
    }
    return true;
}

bool rspSetImage(Frame* pFrame, Rsp* pRSP, s32 nFormat, s32 nWidth, s32 nSize, s32 nImage) {
    FrameBuffer* pBuffer;
    s32 nAddr;

    pBuffer = &pFrame->aBuffer[FBT_IMAGE];
    pBuffer->nFormat = nFormat;
    pBuffer->nWidth = nWidth;
    pBuffer->nSize = nSize;
    nAddr = SEGMENT_ADDRESS(pRSP, nImage);
    pBuffer->nAddress = nAddr;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pBuffer->pData, nAddr, NULL)) {
        return false;
    }

    if (!frameSetBuffer(pFrame, FBT_IMAGE)) {
        return false;
    }

    return true;
}

static inline bool rspSetTileSize(Frame* pFrame, Tile* pTile, s32 nX0, s32 nY0, s32 nX1, s32 nY1) {
    pTile->nX0 = nX0;
    pTile->nY0 = nY0;
    pTile->nX1 = nX1;
    pTile->nY1 = nY1;
    if (!frameDrawReset(pFrame, 1)) {
        return false;
    }
    return true;
}

static bool tmemLoad_B(Frame* pFrame, Rsp* pRSP, u32 imagePtr, s16 loadLines, s16 tmemSH) {
    FrameBuffer* pBuffer;
    s32 nAddr;

    pBuffer = &pFrame->aBuffer[FBT_IMAGE];
    pBuffer->nFormat = 0;
    pBuffer->nWidth = imageSrcWsize >> 1;
    pBuffer->nSize = 2;
    nAddr = SEGMENT_ADDRESS(pRSP, imagePtr);
    pBuffer->nAddress = nAddr;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pBuffer->pData, nAddr, NULL)) {
        return false;
    }

    if (!frameSetBuffer(pFrame, FBT_IMAGE)) {
        return false;
    }

    pFrame->aTile[7].nX0 = 0;
    pFrame->aTile[7].nY0 = 0;
    pFrame->aTile[7].nX1 = (tmemSH - 1) * 16;
    pFrame->aTile[7].nY1 = (loadLines * 4) - 1;

    if (!frameLoadTMEM(pFrame, FLT_TILE, 7)) {
        return false;
    }

    return true;
}

static bool tmemLoad_A(Frame* pFrame, Rsp* pRSP, s32 imagePtr, s16 loadLines, s16 tmemAdrs, s16 tmemSH) {
    pFrame->aTile[7].nSize = 2;
    pFrame->aTile[7].nTMEM = tmemAdrs;
    pFrame->aTile[7].iTLUT = 0;
    pFrame->aTile[7].nSizeX = tmemSliceWmax;
    pFrame->aTile[7].nFormat = 0;
    pFrame->aTile[7].nMaskS = 0;
    pFrame->aTile[7].nMaskT = 0;
    pFrame->aTile[7].nModeS = 0;
    pFrame->aTile[7].nModeT = 0;
    pFrame->aTile[7].nShiftS = 0;
    pFrame->aTile[7].nShiftT = 0;

    if (!frameDrawReset(pFrame, 0x1)) {
        return false;
    }

    tmemLoad_B(pFrame, pRSP, imagePtr, loadLines, tmemSH);

    NO_INLINE();
    return true;
}

// Similar to
// https://github.com/decompals/ultralib/blob/1616482098e51d2e1906e198bf1bde14e8fc5e90/src/gu/us2dex_emu.c#L97
static bool tmemLoad(Frame* pFrame, Rsp* pRSP, u32* imagePtr, s16* imageRemain, s16 drawLines, s16 flagBilerp) {
    s16 loadLines = drawLines + flagBilerp;
    s16 iLoadable = *imageRemain - flagSplit;

    if (iLoadable >= loadLines) {
        tmemLoad_B(pFrame, pRSP, *imagePtr, loadLines, tmemSliceWmax);
        *imagePtr += imageSrcWsize * drawLines;
        *imageRemain -= drawLines;
    } else {
        s16 SubSliceL2, SubSliceD2, SubSliceY2;
        u32 imageTopSeg = imageTop & 0xFF000000;

        SubSliceY2 = *imageRemain;
        SubSliceL2 = loadLines - SubSliceY2;
        SubSliceD2 = drawLines - SubSliceY2;

        if (SubSliceL2 > 0) {
            u32 imagePtr2 = imageTop + imagePtrX0;

            if (SubSliceY2 & 1) {
                imagePtr2 -= imageSrcWsize;
                imagePtr2 = imageTopSeg | (imagePtr2 & 0xFFFFFF);
                SubSliceY2--;
                SubSliceL2++;
            }
            tmemLoad_A(pFrame, pRSP, imagePtr2, SubSliceL2, SubSliceY2 * tmemSliceWmax, tmemSliceWmax);
        }
        if (flagSplit) {
            u32 imagePtr1A, imagePtr1B;
            s16 SubSliceY1, SubSliceL1;
            s16 tmemSH_A, tmemSH_B;

            imagePtr1A = *imagePtr + iLoadable * imageSrcWsize;
            imagePtr1B = imageTop;
            SubSliceY1 = iLoadable;

            if (iLoadable & 1) {
                imagePtr1A -= imageSrcWsize;
                imagePtr1B -= imageSrcWsize;
                imagePtr1B = imageTopSeg | (imagePtr1B & 0xFFFFFF);
                SubSliceY1--;
                SubSliceL1 = 2;
            } else {
                SubSliceL1 = 1;
            }
            tmemSH_A = (imageSrcWsize - imagePtrX0) >> 3;
            tmemSH_B = tmemSliceWmax - tmemSH_A;
            tmemLoad_A(pFrame, pRSP, imagePtr1B, SubSliceL1, SubSliceY1 * tmemSliceWmax + tmemSH_A, tmemSH_B);
            tmemLoad_A(pFrame, pRSP, imagePtr1A, SubSliceL1, SubSliceY1 * tmemSliceWmax, tmemSH_A);
        }

        if (iLoadable > 0) {
            tmemLoad_A(pFrame, pRSP, *imagePtr, iLoadable, 0, tmemSliceWmax);
        } else {
            pFrame->aTile[7].nSize = 2;
            pFrame->aTile[7].nTMEM = 0;
            pFrame->aTile[7].iTLUT = 0;
            pFrame->aTile[7].nSizeX = tmemSliceWmax;
            pFrame->aTile[7].nFormat = 0;
            pFrame->aTile[7].nMaskS = 0;
            pFrame->aTile[7].nMaskT = 0;
            pFrame->aTile[7].nModeS = 0;
            pFrame->aTile[7].nModeT = 0;
            pFrame->aTile[7].nShiftS = 0;
            pFrame->aTile[7].nShiftT = 0;

            if (!frameDrawReset(pFrame, 0x1)) {
                return false;
            }
        }

        *imageRemain -= drawLines;
        if (*imageRemain > 0) {
            *imagePtr += imageSrcWsize * drawLines;
        } else {
            *imageRemain = tmemSrcLines - SubSliceD2;
            *imagePtr = imageTop + SubSliceD2 * imageSrcWsize + imagePtrX0;
        }
    }

    return true;
}

static inline bool guS2DEmuSetScissor(u32 ulx, u32 uly, u32 lrx, u32 lry, u8 flag) {
    scissorX0 = ulx;
    scissorY0 = uly;
    scissorX1 = lrx;
    scissorY1 = lry;
    flagBilerp = flag;
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/guS2DEmuBgRect1Cyc.s")
#else
// Similar to
// https://github.com/decompals/ultralib/blob/1616482098e51d2e1906e198bf1bde14e8fc5e90/src/gu/us2dex_emu.c#L177
static bool guS2DEmuBgRect1Cyc(Rsp* pRSP, Frame* pFrame, uObjBg* pBG) {
    s32 pad;

    s16 frameX0, frameX1, framePtrY0, frameRemain;
    s16 imageX0, imageY0, imageSliceW, imageW;
    s32 imageYorig;
    s16 scaleW, scaleH;

    s16 imageSrcW, imageSrcH;
    s16 tmemSliceLines, imageSliceLines;
    s32 frameSliceLines, frameSliceCount;
    u16 imageS, imageT;
    u32 imagePtr;

    s16 imageISliceL0, imageIY0;
    s32 frameLSliceL0;

    scaleW = pBG->s.scaleW;
    scaleH = pBG->s.scaleH;

    {
        s16 pixX0, pixY0, pixX1, pixY1;
        s16 frameY0, frameW, frameH;
        s32 frameWmax, frameHmax;

        frameWmax = (((pBG->s.imageW << 10) / scaleW) - 1) & ~3;
        frameHmax = (((pBG->s.imageH << 10) / scaleH) - 1) & ~3;

        frameW = pBG->s.frameW;
        frameH = pBG->s.frameH;
        frameX0 = pBG->s.frameX;
        frameY0 = pBG->s.frameY;

        if ((frameWmax = pBG->s.frameW - frameWmax) < 0) {
            frameWmax = 0;
        }
        if ((frameHmax = pBG->s.frameH - frameHmax) < 0) {
            frameHmax = 0;
        }

        frameW -= (s16)frameWmax;
        frameH -= (s16)frameHmax;

        if (pBG->s.imageFlip & 1) {
            frameX0 += (s16)frameWmax;
        }

        pixX0 = scissorX0 - frameX0;
        pixY0 = scissorY0 - frameY0;
        pixX1 = frameW - scissorX1 + frameX0;
        pixY1 = frameH - scissorY1 + frameY0;

        if (pixX0 < 0) {
            pixX0 = 0;
        }
        if (pixY0 < 0) {
            pixY0 = 0;
        }
        if (pixX1 < 0) {
            pixX1 = 0;
        }
        if (pixY1 < 0) {
            pixY1 = 0;
        }

        frameW = frameW - (pixX0 + pixX1);
        frameH = frameH - (pixY0 + pixY1);
        frameX0 = frameX0 + pixX0;
        frameY0 = frameY0 + pixY0;

        if (frameW <= 0 || frameH <= 0) {
            return true;
        }

        frameX1 = frameX0 + frameW;
        framePtrY0 = frameY0 >> 2;
        frameRemain = frameH >> 2;

        imageSrcW = pBG->s.imageW << 3;
        imageSrcH = pBG->s.imageH << 3;

        imageSliceW = (imageW = frameW * scaleW >> 7) + flagBilerp * 32;
        if (pBG->s.imageFlip & 1) {
            imageX0 = pBG->s.imageX + (pixX1 * scaleW >> 7);
        } else {
            imageX0 = pBG->s.imageX + (pixX0 * scaleW >> 7);
        }
        imageY0 = pBG->s.imageY + (pixY0 * scaleH >> 7);
        imageYorig = pBG->s.imageYorig;

        while (imageX0 >= imageSrcW) {
            imageX0 -= imageSrcW;
            imageY0 += 32;
            imageYorig += 32;
        }

        while (imageY0 >= imageSrcH) {
            imageY0 -= imageSrcH;
            imageYorig -= imageSrcH;
        }
    }

    {
        flagSplit = (imageX0 + imageSliceW >= imageSrcW);
        tmemSrcLines = imageSrcH >> 5;
    }

    {
        s16 tmemSize, tmemMask, tmemShift;
        s32 imageNumSlice;
        s32 imageSliceWmax;
        s32 imageLYoffset, frameLYoffset;
        s32 imageLHidden, frameLHidden;
        s32 frameLYslice;
        // TODO: make in-function static
        // static s16 TMEMSIZE[] = { 512, 512, 256, 512, 512 };
        // static s16 TMEMMASK[] = { 0x1FF, 0xFF, 0x7F, 0x3F };
        // static s16 TMEMSHIFT[] = { 0x200, 0x100, 0x80, 0x40 };

        tmemSize = TMEMSIZE[pBG->s.imageFmt];
        tmemMask = TMEMMASK[pBG->s.imageSiz];
        tmemShift = TMEMSHIFT[pBG->s.imageSiz];

        imageSliceWmax = ((pBG->s.frameW * scaleW) >> 7) + (flagBilerp << 5);
        if (imageSliceWmax > imageSrcW) {
            imageSliceWmax = imageSrcW;
        }

        tmemSliceWmax = (imageSliceWmax + tmemMask) / tmemShift + 1;
        tmemSliceLines = tmemSize / tmemSliceWmax;
        imageSliceLines = tmemSliceLines - flagBilerp;
        frameSliceLines = (imageSliceLines << 20) / scaleH;

        imageLYoffset = (imageY0 - imageYorig) << 5;
        if (imageLYoffset < 0) {
            imageLYoffset -= (scaleH - 1);
        }
        frameLYoffset = imageLYoffset / scaleH;
        frameLYoffset <<= 10;

        if (frameLYoffset >= 0) {
            imageNumSlice = frameLYoffset / frameSliceLines;
        } else {
            imageNumSlice = (frameLYoffset - frameSliceLines + 1) / frameSliceLines;
        }

        frameLYslice = (frameLSliceL0 = frameSliceLines * imageNumSlice) & ~1023;
        frameLHidden = frameLYoffset - frameLYslice;
        imageLHidden = (frameLHidden >> 10) * scaleH;

        frameLSliceL0 = (frameLSliceL0 & 1023) + frameSliceLines - frameLHidden;

        imageT = (imageLHidden >> 5) & 31;
        imageLHidden >>= 10;
        imageISliceL0 = imageSliceLines - (s16)imageLHidden;
        imageIY0 = imageSliceLines * imageNumSlice + (imageYorig & ~31) / 32 + imageLHidden;
        if (imageIY0 < 0) {
            imageIY0 += (pBG->s.imageH >> 2);
        }
        if (imageIY0 >= (pBG->s.imageH >> 2)) {
            imageIY0 -= (pBG->s.imageH >> 2);
        }

        imageTop = (u32)pBG->s.imagePtr;
        imageSrcWsize = (imageSrcW / tmemShift) << 3;
        imagePtrX0 = (imageX0 / tmemShift) << 3;
        imagePtr = imageTop + imageSrcWsize * imageIY0 + imagePtrX0;

        imageS = imageX0 & tmemMask;
        if (pBG->s.imageFlip & 1) {
            imageS = -(imageS + imageW);
        }
    }

    {
        rdpSetTimg_w0 = 0x100000 + (imageSrcWsize >> 1) - 1;
        rdpSetTile_w0 = 0x100000 + (tmemSliceWmax << 9);

        pFrame->aTile[7].nSize = 2;
        pFrame->aTile[7].nTMEM = 0;
        pFrame->aTile[7].iTLUT = 0;
        pFrame->aTile[7].nSizeX = tmemSliceWmax;
        pFrame->aTile[7].nFormat = 0;
        pFrame->aTile[7].nMaskS = 0;
        pFrame->aTile[7].nMaskT = 0;
        pFrame->aTile[7].nModeS = 0;
        pFrame->aTile[7].nModeT = 0;
        pFrame->aTile[7].nShiftS = 0;
        pFrame->aTile[7].nShiftT = 0;
        if (!frameDrawReset(pFrame, 1)) {
            return false;
        }

        pFrame->aTile[0].nSize = pBG->s.imageSiz;
        pFrame->aTile[0].nTMEM = 0;
        pFrame->aTile[0].iTLUT = pBG->s.imagePal;
        pFrame->aTile[0].nSizeX = tmemSliceWmax;
        pFrame->aTile[0].nFormat = pBG->s.imageFmt;
        pFrame->aTile[0].nMaskS = 0xF;
        pFrame->aTile[0].nMaskT = 0xF;
        pFrame->aTile[0].nModeS = 1;
        pFrame->aTile[0].nModeT = 1;
        pFrame->aTile[0].nShiftS = 0;
        pFrame->aTile[0].nShiftT = 0;
        if (!frameDrawReset(pFrame, 1)) {
            return false;
        }

        pFrame->aTile[0].nX0 = 0;
        pFrame->aTile[0].nY0 = 0;
        pFrame->aTile[0].nX1 = 0;
        pFrame->aTile[0].nY1 = 0;
        if (!frameDrawReset(pFrame, 1)) {
            return false;
        }
    }

    {
        s16 imageRemain;
        s16 imageSliceH, frameSliceH;

        imageRemain = tmemSrcLines - imageIY0;
        imageSliceH = imageISliceL0;
        frameSliceCount = frameLSliceL0;

        while (true) {
            frameSliceH = frameSliceCount >> 10;
            if (frameSliceH <= 0) {
                imageRemain -= imageSliceH;
                if (imageRemain > 0) {
                    imagePtr += imageSrcWsize * imageSliceH;
                } else {
                    imagePtr = imageTop - imageRemain * imageSrcWsize + imagePtrX0;
                    imageRemain += tmemSrcLines;
                }
            } else {
                Rectangle primitive;
                s16 nS, nT;
                s16 framePtrY1;

                frameSliceCount &= 1023;
                frameRemain -= frameSliceH;
                if (frameRemain < 0) {
                    frameSliceH += frameRemain;
                    imageSliceH += (frameRemain * scaleH >> 10) + 1;
                    if (imageSliceH > imageSliceLines) {
                        imageSliceH = imageSliceLines;
                    }
                }
                tmemLoad(pFrame, pRSP, &imagePtr, &imageRemain, imageSliceH, flagBilerp);

                framePtrY1 = framePtrY0 + frameSliceH;

                primitive.iTile = 0;
                primitive.bFlip = false;

                nS = imageS - 8 * pFrame->aTile[primitive.iTile].nX0;
                nT = imageT - 8 * pFrame->aTile[primitive.iTile].nY0;

                primitive.rS = nS / 32.0f;
                primitive.rT = nT / 32.0f;
                primitive.rDeltaS = scaleW / 1024.0f;
                primitive.rDeltaT = scaleH / 1024.0f;
                if (pBG->s.imageFlip & 1) {
                    primitive.rS *= -1.0f;
                    primitive.rDeltaS *= -1.0f;
                }
                primitive.nX0 = frameX0 << 0;
                primitive.nY0 = framePtrY0 << 2;
                primitive.nX1 = frameX1 << 0;
                primitive.nY1 = framePtrY1 << 2;
                if (!pFrame->aDraw[3](pFrame, &primitive)) {
                    return false;
                }

                framePtrY0 = framePtrY1;
                if (frameRemain <= 0) {
                    return true;
                }
            }

            frameSliceCount += frameSliceLines;
            imageSliceH = imageSliceLines;
            imageT = 0;
        }
    }
}
#endif

bool rspFillObjTxtr(Rsp* pRSP, s32 nAddress, uObjTxtr* pTxtr, u32* pLoadType) {
    u32* pnData32;
    u16* pnData16;
    u8* pTxtrBlock;
    u32 nLoadType;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pTxtrBlock, nAddress, NULL)) {
        return false;
    }

    pnData32 = (u32*)pTxtrBlock;
    pnData16 = (u16*)pTxtrBlock;
    nLoadType = pnData32[0];

    switch (nLoadType) {
        case G_OBJLT_TXTRBLOCK:
            pTxtr->block.type = nLoadType;
            pTxtr->block.image = pnData32[1];
            pTxtr->block.sid = pnData16[7];
            pTxtr->block.flag = pnData32[4];
            pTxtr->block.mask = pnData32[5];
            pTxtr->block.tmem = pnData16[4];
            pTxtr->block.tsize = pnData16[5];
            pTxtr->block.tline = pnData16[6];
            break;
        case G_OBJLT_TXTRTILE:
            pTxtr->tile.type = nLoadType;
            pTxtr->tile.image = pnData32[1];
            pTxtr->tile.sid = pnData16[7];
            pTxtr->tile.flag = pnData32[4];
            pTxtr->tile.mask = pnData32[5];
            pTxtr->tile.tmem = pnData16[4];
            pTxtr->tile.twidth = pnData16[5];
            pTxtr->tile.theight = pnData16[6];
            break;
        case G_OBJLT_TLUT:
            pTxtr->tlut.type = nLoadType;
            pTxtr->tlut.image = pnData32[1];
            pTxtr->tlut.sid = pnData16[7];
            pTxtr->tlut.flag = pnData32[4];
            pTxtr->tlut.mask = pnData32[5];
            pTxtr->tlut.phead = pnData16[4];
            pTxtr->tlut.pnum = pnData16[5];
            break;
        default:
            return false;
    }

    if (pLoadType != NULL) {
        *pLoadType = nLoadType;
    }
    return true;
}

static bool rspObjLoadTxtr(Rsp* pRSP, Frame* pFrame, s32 nAddress);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjLoadTxtr.s")

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjRectangle.s")
#else
static bool rspObjRectangle(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    s32 pad;
    u16 nSizLineBytes;
    f32 fDeltaS;
    f32 fDeltaT;
    uObjSprite objSprite;
    Tile* pTile;
    Rectangle primitive;
    s32 nClampSetting;
    s32 nTexTrim2;
    s32 nTexTrim5;

    nTexTrim2 = 0;
    nTexTrim5 = 0;
    pTile = &pFrame->aTile[0];
    if (!rspFillObjSprite(pRSP, nAddress, &objSprite)) {
        return false;
    }

    nClampSetting = pRSP->nMode2D & 1;
    if (pRSP->nMode2D & 0x10) {
        nTexTrim2 = -2;
        nTexTrim5 = -16;
    } else if (pRSP->nMode2D & 0x20) {
        nTexTrim2 = -4;
        nTexTrim5 = -32;
    }
    if (pRSP->nMode2D & 0x40) {
        nTexTrim2 += 1;
        nTexTrim5 += 12;
    }
    objSprite.s.imageW += nTexTrim5;
    objSprite.s.imageH += nTexTrim5;
    pFrame->nLastX1 += nTexTrim2;
    if (pTile->nSize != 0) {
        switch (objSprite.s.imageSiz) {
            case 3:
                nSizLineBytes = 2;
                break;
            case 2:
                nSizLineBytes = 2;
                break;
            case 1:
                nSizLineBytes = 1;
                break;
            default:
                return false;
        }
        if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
            pTile->nSizeX = objSprite.s.imageStride;
        } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
            pTile->nSizeX = (((pFrame->nLastX1 - pFrame->nLastX0 + 1) >> 5) * nSizLineBytes + 7) >> 3;
        }
    } else {
        if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
            pTile->nSizeX = ((objSprite.s.imageW >> 6) + 7) >> 3;
        } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
            pTile->nSizeX = (((pFrame->nLastX1 - pFrame->nLastX0) >> 6) + 7) >> 3;
        }
    }

    if (!rspSetTile(pFrame, pTile, objSprite.s.imageSiz, objSprite.s.imageAdrs, objSprite.s.imagePal,
                    objSprite.s.imageFmt, 0, 0, nClampSetting, nClampSetting, 0, 0)) {
        return false;
    }
    if (pFrame->n2dLoadTexType == G_OBJLT_TXTRBLOCK) {
        if (!rspSetTileSize(pFrame, pTile, 0, 0, ((objSprite.s.imageW >> 5) - 1) * 4,
                            ((objSprite.s.imageH >> 5) - 1) * 4)) {
            return false;
        }
    } else if (pFrame->n2dLoadTexType == G_OBJLT_TXTRTILE) {
        if (!rspSetTileSize(pFrame, pTile, (pFrame->nLastX0 >> 5) * 4, (pFrame->nLastY0 >> 5) * 4,
                            (pFrame->nLastX1 >> 5) * 4, (pFrame->nLastY1 >> 5) * 4)) {
            return false;
        }
    }

    primitive.nX0 = objSprite.s.objX;
    primitive.nY0 = objSprite.s.objY;
    primitive.nX1 =
        ((s32)(((objSprite.s.imageW - 1.0f) * (1024.0f / objSprite.s.scaleW)) + 8 * objSprite.s.objX) >> 3) - 2;
    primitive.nY1 =
        ((s32)(((objSprite.s.imageH - 1.0f) * (1024.0f / objSprite.s.scaleH)) + 8 * objSprite.s.objY) >> 3) - 2;
    primitive.iTile = 0;
    primitive.bFlip = false;
    fDeltaS = objSprite.s.scaleW / 1024.0f;
    fDeltaT = objSprite.s.scaleH / 1024.0f;
    if (objSprite.s.imageFlags & 1) {
        primitive.rS = (u16)(objSprite.s.imageW - 8 * pFrame->aTile[primitive.iTile].nX0) / 32.0f;
        primitive.rDeltaS = -fDeltaS;
    } else {
        primitive.rS = (u16)(-8 * pFrame->aTile[primitive.iTile].nX0) / 32.0f;
        primitive.rDeltaS = fDeltaS;
    }
    if (objSprite.s.imageFlags & 0x10) {
        primitive.rT = (u16)(objSprite.s.imageH - 8 * pFrame->aTile[primitive.iTile].nY0) / 32.0f;
        primitive.rDeltaT = -fDeltaT;
    } else {
        primitive.rT = (u16)(-8 * pFrame->aTile[primitive.iTile].nY0) / 32.0f;
        primitive.rDeltaT = fDeltaT;
    }

    if (!pFrame->aDraw[3](pFrame, &primitive)) {
        return false;
    }
    return true;
}
#endif

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjSprite.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjRectangleR.s")

bool rspBgRectCopy(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    uObjBg bg;
    uObjBg bgScale;
    u32 nOldMode1;
    u32 nOldMode2;

    rspFillObjBg(pRSP, nAddress, &bg);
    bgScale.s.frameH = bg.b.frameH;
    bgScale.s.frameW = bg.b.frameW;
    bgScale.s.frameX = bg.b.frameX;
    bgScale.s.frameY = bg.b.frameY;
    bgScale.s.imageFlip = bg.b.imageFlip;
    bgScale.s.imageFmt = bg.b.imageFmt;
    bgScale.s.imageH = bg.b.imageH;
    bgScale.s.imageLoad = bg.b.imageLoad;
    bgScale.s.imagePal = bg.b.imagePal;
    bgScale.s.imagePtr = bg.b.imagePtr;
    bgScale.s.imageSiz = bg.b.imageSiz;
    bgScale.s.imageW = bg.b.imageW;
    bgScale.s.imageX = bg.b.imageX;
    bgScale.s.imageY = bg.b.imageY;
    bgScale.s.padding[0] = 0;
    bgScale.s.padding[1] = 0;
    bgScale.s.padding[2] = 0;
    bgScale.s.padding[3] = 0;
    bgScale.s.scaleW = 0x400;
    bgScale.s.scaleH = 0x400;
    bgScale.s.imageYorig = 0;

    frameGetMode(pFrame, FMT_OTHER0, &nOldMode1);
    frameGetMode(pFrame, FMT_OTHER1, &nOldMode2);
    if ((nOldMode2 & 0x300000) == 0x200000) {
        pFrame->aColor[FCT_PRIMITIVE].a = 0xFF;
    }
    if (!frameSetMode(pFrame, FMT_OTHER0, 0x0F0A4001)) {
        return false;
    }
    if (!frameSetMode(pFrame, FMT_OTHER1, 0x00802CC0)) {
        return false;
    }
    if (!guS2DEmuSetScissor(0, 0, 0x500, 0x3C0, 0)) {
        return false;
    }
    if (!guS2DEmuBgRect1Cyc(pRSP, pFrame, &bgScale)) {
        return false;
    }
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjMatrix.s")
#else
static bool rspObjMatrix(Rsp* pRSP, Frame* pFrame, s32 nAddress) {
    u32* pnData32;
    u16* pnData16;
    u8* pObjMtx;
    u16 nBaseScaleX;
    u16 nBaseScaleY;
    s32 nA;
    s32 nB;
    s32 nC;
    s32 nD;
    s16 nX;
    s16 nY;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pObjMtx, nAddress, NULL)) {
        return false;
    }

    pnData32 = (u32*)pObjMtx;
    pnData16 = (u16*)pObjMtx;

    nA = pnData32[0];
    nB = pnData32[1];
    nC = pnData32[2];
    nD = pnData32[3];
    nX = pnData16[8];
    nY = pnData16[9];
    nBaseScaleX = pnData16[10];
    nBaseScaleY = pnData16[11];

    pRSP->twoDValues.fX = (f32)nX / 4.0f;
    pRSP->twoDValues.fY = -(f32)nY / 4.0f;
    pRSP->twoDValues.aRotations[0][0] = nA / 65536.0f;
    pRSP->twoDValues.aRotations[0][1] = nB / 65536.0f;
    pRSP->twoDValues.aRotations[1][0] = nC / 65536.0f;
    pRSP->twoDValues.aRotations[1][1] = nD / 65536.0f;
    pRSP->twoDValues.fBaseScaleX = 1024.0f / nBaseScaleX;
    pRSP->twoDValues.fBaseScaleY = 1024.0f / nBaseScaleY;
    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
static bool rspSetupS2DEX(Rsp* pRSP);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspSetupS2DEX.s")
#else
static bool rspSetupS2DEX(Rsp* pRSP) {
    f32 fL;
    f32 fR;
    f32 fB;
    f32 fT;
    Frame* pFrame;
    f32 fScale = 2.0f;
    s32 pad;

    pFrame = SYSTEM_FRAME(pRSP->pHost);

    pRSP->twoDValues.aRotations[0][0] = 1.0f;
    pRSP->twoDValues.aRotations[1][0] = 0.0f;
    pRSP->twoDValues.aRotations[1][1] = 1.0f;
    pRSP->twoDValues.aRotations[0][1] = 0.0f;

    pRSP->twoDValues.fBaseScaleX = 1.0f;
    pRSP->twoDValues.fBaseScaleY = 1.0f;
    pRSP->twoDValues.fX = 0.0f;
    pRSP->twoDValues.fY = 0.0f;

    fL = -pFrame->anSizeX[FS_TARGET] / 2.0f;
    fR = pFrame->anSizeX[FS_TARGET] / 2.0f;
    fB = -pFrame->anSizeY[FS_TARGET] / 2.0f;
    fT = pFrame->anSizeY[FS_TARGET] / 2.0f;

    Matrix4by4Identity(pRSP->aMatrixOrtho);

    pRSP->aMatrixOrtho[0][0] = fScale / (fR - fL);
    pRSP->aMatrixOrtho[1][1] = fScale / (fT - fB);
    pRSP->aMatrixOrtho[2][2] = -1.0f;
    pRSP->aMatrixOrtho[3][0] = -(fR + fL) / (fR - fL);
    pRSP->aMatrixOrtho[3][1] = -(fT + fB) / (fT - fB);
    pRSP->aMatrixOrtho[3][2] = -fScale / 2.0f;
    pRSP->aMatrixOrtho[3][3] = 1.0f;

    return true;
}
#endif

static bool rspSetGeometryMode1(Rsp* pRSP, s32 nMode) {
    s32 nModeFrame = 0;

    pRSP->nGeometryMode = nMode;
    if (nMode & 1) {
        nModeFrame |= 1;
    }
    if (nMode & 4) {
        nModeFrame |= 2;
    }
    if (nMode & 0x200) {
        nModeFrame |= 0x200;
    }
    if (nMode & 0x1000) {
        nModeFrame |= 4;
    }
    if (nMode & 0x2000) {
        nModeFrame |= 8;
    }
    if (nMode & 0x10000) {
        nModeFrame |= 0x10;
    }
    if (nMode & 0x20000) {
        nModeFrame |= 0x20;
    }
    if (nMode & 0x40000) {
        nModeFrame |= 0x80;
    }
    if (nMode & 0x80000) {
        nModeFrame |= 0x100;
    }
    if (nMode & 0x800000) {
        nModeFrame |= 0x400;
    }

    if (!frameSetMode(SYSTEM_FRAME(pRSP->pHost), FMT_GEOMETRY, nModeFrame)) {
        return false;
    }

    return true;
}

static bool rspParseGBI_F3DEX1(Rsp* pRSP, u64** ppnGBI, bool* pbDone);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseGBI_F3DEX1.s")

static bool rspGeometryMode(Rsp* pRSP, s32 nSet, s32 nClr) {
    s32 nMode = 0;

    pRSP->nGeometryMode &= nClr;
    pRSP->nGeometryMode |= nSet;
    if (pRSP->nGeometryMode & 1) {
        nMode |= 1;
    }
    if (pRSP->nGeometryMode & 4) {
        nMode |= 2;
    }
    if (pRSP->nGeometryMode & 0x200) {
        nMode |= 4;
    }
    if (pRSP->nGeometryMode & 0x400) {
        nMode |= 8;
    }
    if (pRSP->nGeometryMode & 0x10000) {
        nMode |= 0x10;
    }
    if (pRSP->nGeometryMode & 0x20000) {
        nMode |= 0x20;
    }
    if (pRSP->nGeometryMode & 0x40000) {
        nMode |= 0x80;
    }
    if (pRSP->nGeometryMode & 0x80000) {
        nMode |= 0x100;
    }
    if (pRSP->nGeometryMode & 0x200000) {
        nMode |= 0x200;
    }
    if (pRSP->nGeometryMode & 0x800000) {
        nMode |= 0x400;
    }
    if (pRSP->nGeometryMode & 0x400000) {
        nMode |= 0x800;
    }

    if (!frameSetMode(SYSTEM_FRAME(pRSP->pHost), FMT_GEOMETRY, nMode)) {
        return false;
    }

    return true;
}

static bool rspParseGBI_F3DEX2(Rsp* pRSP, u64** ppnGBI, bool* pbDone);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseGBI_F3DEX2.s")

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspLoadMatrix.s")
#else
static bool rspLoadMatrix(Rsp* pRSP, s32 nAddress, Mtx44 matrix) {
    s32* pMtx;
    s32 nDataA;
    s32 nDataB;
    f32 rScale;
    f32 rUpper;
    f32 rLower;
    u16 nUpper;
    u16 nLower;

    rScale = 1.0f / 65536.0f;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pMtx, nAddress, NULL)) {
        return false;
    }

    nDataA = pMtx[0];
    nDataB = pMtx[8];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[0][0] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[0][1] = rUpper + rLower * rScale;

    nDataA = pMtx[1];
    nDataB = pMtx[9];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[0][2] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[0][3] = rUpper + rLower * rScale;

    nDataA = pMtx[2];
    nDataB = pMtx[10];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[1][0] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[1][1] = rUpper + rLower * rScale;

    nDataA = pMtx[3];
    nDataB = pMtx[11];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[1][2] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[1][3] = rUpper + rLower * rScale;

    nDataA = pMtx[4];
    nDataB = pMtx[12];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[2][0] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[2][1] = rUpper + rLower * rScale;

    nDataA = pMtx[5];
    nDataB = pMtx[13];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[2][2] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[2][3] = rUpper + rLower * rScale;

    nDataA = pMtx[6];
    nDataB = pMtx[14];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[3][0] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[3][1] = rUpper + rLower * rScale;

    nDataA = pMtx[7];
    nDataB = pMtx[15];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[3][2] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[3][3] = rUpper + rLower * rScale;

    return true;
}
#endif

inline bool rspSetDL(Rsp* pRSP, s32 nOffsetRDRAM, bool bPush) {
    s32 nAddress;
    s32* pDL;

    nAddress = SEGMENT_ADDRESS(pRSP, nOffsetRDRAM);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pDL, nAddress, NULL)) {
        return false;
    }

    if (bPush && ++pRSP->iDL >= ARRAY_COUNT(pRSP->apDL)) {
        return false;
    }

    pRSP->apDL[pRSP->iDL] = (u64*)pDL;
    return true;
}

inline bool rspPopDL(Rsp* pRSP) {
    if (pRSP->iDL == 0) {
        return false;
    } else {
        pRSP->iDL--;
        return true;
    }
}

static bool rspFindUCode(Rsp* pRSP, RspTask* pTask);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFindUCode.s")

static bool rspSaveYield(Rsp* pRSP) {
    int iData;
    RspTask* pTask;

    pRSP->yield.bValid = true;
    pRSP->yield.iDL = pRSP->iDL;
    pRSP->yield.n2TriMult = pRSP->n2TriMult;
    pRSP->yield.nCountVertex = pRSP->nCountVertex;
    pRSP->yield.eTypeUCode = pRSP->eTypeUCode;
    pRSP->yield.nVersionUCode = pRSP->nVersionUCode;

    for (iData = 0; iData < 16; iData++) {
        pRSP->yield.anBaseSegment[iData] = pRSP->anBaseSegment[iData];
    }

    for (iData = 0; iData < 16; iData++) {
        pRSP->yield.apDL[iData] = pRSP->apDL[iData];
    }

    pTask = RSP_TASK(pRSP);
    if (!xlHeapCopy(&pRSP->yield.task, pTask, sizeof(RspTask))) {
        return false;
    }

    return true;
}

static bool rspLoadYield(Rsp* pRSP) {
    int iData;
    RspTask* pTask;

    pRSP->iDL = pRSP->yield.iDL;
    pRSP->n2TriMult = pRSP->yield.n2TriMult;
    pRSP->nCountVertex = pRSP->yield.nCountVertex;
    pRSP->eTypeUCode = pRSP->yield.eTypeUCode;
    pRSP->nVersionUCode = pRSP->yield.nVersionUCode;

    for (iData = 0; iData < 16; iData++) {
        pRSP->anBaseSegment[iData] = pRSP->yield.anBaseSegment[iData];
    }

    for (iData = 0; iData < 16; iData++) {
        pRSP->apDL[iData] = pRSP->yield.apDL[iData];
    }

    pTask = RSP_TASK(pRSP);
    if (!xlHeapCopy(pTask, &pRSP->yield.task, sizeof(RspTask))) {
        return false;
    }

    pRSP->yield.bValid = false;
    return true;
}

static bool rspParseGBI_Setup(Rsp* pRSP, RspTask* pTask) {
    s32 iSegment;

    if (pRSP->yield.bValid) {
        pRSP->yield.bValid = false;
    }

    pRSP->nGeometryMode = 0;
    pRSP->iDL = 0;

    if (!rspSetDL(pRSP, pTask->nOffsetMBI & 0x7FFFFF, false)) {
        return false;
    }

    for (iSegment = 0; iSegment < ARRAY_COUNT(pRSP->anBaseSegment); iSegment++) {
        pRSP->anBaseSegment[iSegment] = 0;
    }

    if (!rspFindUCode(pRSP, pTask)) {
        return false;
    }

    if (pRSP->eTypeUCode != RUT_ZSORT || pRSP->nPass == 1) {
        if (!frameBegin(SYSTEM_FRAME(pRSP->pHost), pRSP->nCountVertex)) {
            return false;
        }
    }

    PAD_STACK();
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
static bool rspParseGBI(Rsp* pRSP, bool* pbDone, s32 nCount);
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseGBI.s")
#else
static bool rspParseGBI(Rsp* pRSP, bool* pbDone, s32 nCount) {
    bool bDone;
    s32 nStatus;
    u64* pDL;
    Cpu* pCPU;

    pCPU = SYSTEM_CPU(pRSP->pHost);
    bDone = false;

    while (!bDone) {
        pDL = pRSP->apDL[pRSP->iDL];
        switch (pRSP->eTypeUCode) {
            case RUT_TURBO:
            case RUT_SPRITE2D:
            case RUT_FAST3D:
            case RUT_F3DEX1:
            case RUT_S2DEX1:
            case RUT_L3DEX1:
                nStatus = rspParseGBI_F3DEX1(pRSP, &pRSP->apDL[pRSP->iDL], &bDone);
                break;
            case RUT_ZSORT:
            case RUT_F3DEX2:
            case RUT_S2DEX2:
            case RUT_L3DEX2:
                nStatus = rspParseGBI_F3DEX2(pRSP, &pRSP->apDL[pRSP->iDL], &bDone);
                break;
            default:
                return false;
        }

        if (nStatus == 0) {
            pRSP->apDL[pRSP->iDL] = pDL;
            if (!rdpParseGBI(SYSTEM_RDP(pRSP->pHost), &pRSP->apDL[pRSP->iDL], pRSP->eTypeUCode)) {
                if (!rspPopDL(pRSP)) {
                    bDone = true;
                }
            }
        }

        if (nCount == -1) {
            if (pCPU->nRetrace != pCPU->nRetraceUsed) {
                break;
            }
        } else if (nCount != 0) {
            if (--nCount == 0) {
                break;
            }
        }
    }

    if (pRSP->eTypeUCode == RUT_ZSORT) {
        if (pRSP->nPass == 1) {
            pRSP->nPass = 2;
        } else {
            pRSP->nPass = 1;
        }
    } else {
        pRSP->nPass = 2;
    }

    if (bDone) {
        pRSP->nMode |= 8;
    }

    if (pbDone != NULL) {
        *pbDone = bDone;
    }

    return true;
}
#endif

bool rspPut8(Rsp* pRSP, u32 nAddress, s8* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *((s8*)pRSP->pDMEM + (nAddress & 0xFFF)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *((s8*)pRSP->pIMEM + (nAddress & 0xFFF)) = *pData;
            break;
        default:
            return false;
    }

    return true;
}

bool rspPut16(Rsp* pRSP, u32 nAddress, s16* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *((s16*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 1)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *((s16*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 1)) = *pData;
            break;
        default:
            return false;
    }

    return true;
}

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspPut32.s")
#else
bool rspPut32(Rsp* pRSP, u32 nAddress, s32* pData) {
    RspTask* pTask;
    s32 nData;
    s32 nSize;
    void* pTarget;
    void* pSource;
    s32 nLength;

    switch ((nAddress >> 12) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *((s32*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 2)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *((s32*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 2)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_BASE_REG):
            switch (nAddress & 0x1F) {
                case RSP_REG_ADDR_LO(SP_MEM_ADDR_REG):
                    pRSP->nAddressSP = *pData & 0x1FFF;
                    break;
                case RSP_REG_ADDR_LO(SP_DRAM_ADDR_REG):
                    pRSP->nAddressRDRAM = *pData & 0x03FFFFFF;
                    break;
                case RSP_REG_ADDR_LO(SP_RD_LEN_REG):
                    pRSP->nSizeGet = *pData;
                    nLength = pRSP->nSizeGet & 0xFFF;
                    if (pRSP->nAddressSP & 0x1000) {
                        pTarget = (u8*)pRSP->pIMEM + (pRSP->nAddressSP & 0xFFF);
                    } else {
                        pTarget = (u8*)pRSP->pDMEM + (pRSP->nAddressSP & 0xFFF);
                    }
                    if (!xlHeapCopy(pTarget, (s8*)SYSTEM_RAM(pRSP->pHost)->pBuffer + pRSP->nAddressRDRAM,
                                    nLength + 1)) {
                        return false;
                    }
                    break;
                case RSP_REG_ADDR_LO(SP_WR_LEN_REG):
                    pRSP->nSizePut = *pData;
                    nLength = pRSP->nSizePut & 0xFFF;
                    if (pRSP->nAddressSP & 0x1000) {
                        pSource = (u8*)pRSP->pIMEM + (pRSP->nAddressSP & 0xFFF);
                    } else {
                        pSource = (u8*)pRSP->pDMEM + (pRSP->nAddressSP & 0xFFF);
                    }
                    nSize = nLength + 1;
                    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pTarget, pRSP->nAddressRDRAM, (u32*)&nSize)) {
                        return false;
                    }
                    if (!xlHeapCopy(pTarget, pSource, nSize)) {
                        return false;
                    }
                    break;
                case RSP_REG_ADDR_LO(SP_STATUS_REG):
                    nData = *pData & 0xFFFF;
                    if (nData & 1) {
                        OSGetTick();
                        pRSP->nStatus &= ~0x1;
                        pTask = RSP_TASK(pRSP);
                        switch (pTask->nType) {
                            case 0:
                                break;
                            case 1:
                                if (pRSP->yield.bValid) {
                                    if (!rspLoadYield(pRSP)) {
                                        return false;
                                    }
                                    break;
                                }
                                pRSP->nMode |= 2;
                                break;
                            case 2:
                                if (pRSP->eTypeAudioUCode != RUT_UNKNOWN) {
                                    rspParseABI(pRSP, pTask);
                                }
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 3:
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 4:
                                if (pTask->nOffsetYield == 0) {
                                    if (!rspParseJPEG_Decode(pRSP, pTask)) {
                                        __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                                    }
                                } else {
                                    if (!rspParseJPEG_DecodeZ(pRSP, pTask)) {
                                        __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                                    }
                                }
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 5:
                                if (pTask->nOffsetYield == 0) {
                                    if (!rspParseJPEG_Encode(pRSP, pTask)) {
                                        __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                                    }
                                } else {
                                    if (!rspParseJPEG_EncodeZ(pRSP, pTask)) {
                                        __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                                    }
                                }
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 6:
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 7:
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            default:
                                return false;
                        }
                    }
                    if (nData & 2) {
                        pRSP->nStatus |= 1;
                    }
                    if (nData & 4) {
                        pRSP->nStatus &= ~0x2;
                    }
                    if (nData & 8) {
                        xlObjectEvent(pRSP->pHost, 0x1001, (void*)5);
                    }
                    if (nData & 0x10) {
                        xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                    }
                    if (nData & 0x20) {
                        pRSP->nStatus &= ~0x20;
                    }
                    if (nData & 0x40) {
                        pRSP->nStatus |= 0x20;
                    }
                    if (nData & 0x80) {
                        pRSP->nStatus &= ~0x40;
                    }
                    if (nData & 0x100) {
                        pRSP->nStatus |= 0x40;
                    }
                    if (nData & 0x200) {
                        pRSP->nStatus &= ~0x180;
                    }
                    if (nData & 0x400) {
                        if (!(pRSP->nStatus & 1)) {
                            pRSP->nStatus = pRSP->nStatus | 0x101;
                            if (!rspSaveYield(pRSP)) {
                                return false;
                            }
                            xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                        }
                    }
                    if (nData & 0x800) {
                        pRSP->nStatus &= ~0x100;
                    }
                    if (nData & 0x1000) {
                        pRSP->nStatus |= 0x100;
                    }
                    if (nData & 0x2000) {
                        pRSP->nStatus &= ~0x200;
                    }
                    if (nData & 0x4000) {
                        pRSP->nStatus |= 0x200;
                    }
                    if (nData & 0x8000) {
                        pRSP->nStatus &= ~0x400;
                    }
                    if (nData & 0x10000) {
                        pRSP->nStatus |= 0x400;
                    }
                    if (nData & 0x20000) {
                        pRSP->nStatus &= ~0x800;
                    }
                    if (nData & 0x40000) {
                        pRSP->nStatus |= 0x800;
                    }
                    if (nData & 0x80000) {
                        pRSP->nStatus &= ~0x1000;
                    }
                    if (nData & 0x100000) {
                        pRSP->nStatus |= 0x1000;
                    }
                    if (nData & 0x200000) {
                        pRSP->nStatus &= ~0x2000;
                    }
                    if (nData & 0x400000) {
                        pRSP->nStatus |= 0x2000;
                    }
                    if (nData & 0x800000) {
                        pRSP->nStatus &= ~0x4000;
                    }
                    if (nData & 0x01000000) {
                        pRSP->nStatus |= 0x4000;
                    }
                    break;
                case RSP_REG_ADDR_LO(SP_DMA_FULL_REG):
                    break;
                case RSP_REG_ADDR_LO(SP_DMA_BUSY_REG):
                    break;
                case RSP_REG_ADDR_LO(SP_SEMAPHORE_REG):
                    pRSP->nSemaphore = 0;
                    break;
                default:
                    return false;
            }
            break;
        case RSP_REG_ADDR_HI(SP_PC_REG):
            switch (nAddress & 0xF) {
                case RSP_REG_ADDR_LO(SP_PC_REG):
                    pRSP->nPC = *pData;
                    break;
                case RSP_REG_ADDR_LO(SP_IBIST_REG):
                    pRSP->nBIST = *pData & 0xFF;
                    break;
                default:
                    return false;
            }
            break;
        default:
            return false;
    }

    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    return true;
}
#endif

bool rspPut64(Rsp* pRSP, u32 nAddress, s64* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *((s64*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 3)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *((s64*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 3)) = *pData;
            break;
        default:
            return false;
    }

    return true;
}

bool rspGet8(Rsp* pRSP, u32 nAddress, s8* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *pData = *((s8*)pRSP->pDMEM + (nAddress & 0xFFF));
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *pData = *((s8*)pRSP->pIMEM + (nAddress & 0xFFF));
            break;
        default:
            return false;
    }

    return true;
}

bool rspGet16(Rsp* pRSP, u32 nAddress, s16* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *pData = *((s16*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 1));
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *pData = *((s16*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 1));
            break;
        default:
            return false;
    }

    return true;
}

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspGet32.s")
#else
bool rspGet32(Rsp* pRSP, u32 nAddress, s32* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *pData = *((s32*)pRSP->pDMEM + ((nAddress & 0xFFC) >> 2));
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *pData = *((s32*)pRSP->pIMEM + ((nAddress & 0xFFC) >> 2));
            break;
        case RSP_REG_ADDR_HI(SP_BASE_REG):
            switch (nAddress & 0x1F) {
                case RSP_REG_ADDR_LO(SP_MEM_ADDR_REG):
                    *pData = pRSP->nAddressSP;
                    break;
                case RSP_REG_ADDR_LO(SP_DRAM_ADDR_REG):
                    *pData = pRSP->nAddressRDRAM;
                    break;
                case RSP_REG_ADDR_LO(SP_RD_LEN_REG):
                    *pData = pRSP->nSizeGet;
                    break;
                case RSP_REG_ADDR_LO(SP_WR_LEN_REG):
                    *pData = pRSP->nSizePut;
                    break;
                case RSP_REG_ADDR_LO(SP_STATUS_REG):
                    *pData = pRSP->nStatus & 0xFFFF;
                    break;
                case RSP_REG_ADDR_LO(SP_DMA_FULL_REG):
                    *pData = pRSP->nFullDMA & 1;
                    break;
                case RSP_REG_ADDR_LO(SP_DMA_BUSY_REG):
                    *pData = pRSP->nBusyDMA & 1;
                    break;
                case RSP_REG_ADDR_LO(SP_SEMAPHORE_REG):
                    pRSP->nSemaphore = 1;
                    *pData = 0;
                    break;
                default:
                    return false;
            }
            break;
        case RSP_REG_ADDR_HI(SP_PC_REG):
            switch (nAddress & 0xF) {
                case RSP_REG_ADDR_LO(SP_PC_REG):
                    *pData = pRSP->nPC;
                    break;
                case RSP_REG_ADDR_LO(SP_IBIST_REG):
                    *pData = pRSP->nBIST & 0xFF;
                    break;
                default:
                    return false;
            }
            break;
        default:
            return false;
    }

    return true;
}
#endif

bool rspGet64(Rsp* pRSP, u32 nAddress, s64* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *pData = *((s64*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 3));
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *pData = *((s64*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 3));
            break;
        default:
            return false;
    }

    return true;
}

bool rspInvalidateCache(Rsp* pRSP, s32 nOffset0, s32 nOffset1) {
    __anon_0x5B8F2* pUCode;
    void* pListNode;
    s32 nOffsetUCode0;
    s32 nOffsetUCode1;

    nOffsetUCode0 = nOffset1 & 0x7FFFFF;
    nOffsetUCode1 = nOffset0 & 0x7FFFFF;
    pListNode = pRSP->pListUCode->pNodeHead;

    while (pListNode != NULL) {
        s32 offset0;
        s32 offset1;

        pUCode = (__anon_0x5B8F2*)NODE_DATA(pListNode);
        pListNode = NODE_NEXT(pListNode);

        if (pUCode->nOffsetCode < pUCode->nOffsetData) {
            offset0 = pUCode->nOffsetCode;
            offset1 = pUCode->nOffsetData + pUCode->nLengthData;
        } else {
            offset0 = pUCode->nOffsetData;
            offset1 = pUCode->nOffsetCode + pUCode->nLengthCode;
        }

        if ((nOffsetUCode1 <= offset0 && offset0 <= nOffsetUCode0) ||
            (nOffsetUCode1 <= offset1 && offset1 <= nOffsetUCode0)) {
            if (!xlListFreeItem(pRSP->pListUCode, (void**)&pUCode)) {
                return false;
            }
        }
    }

    return true;
}

bool rspEnableABI(Rsp* pRSP, bool bFlag) {
    pRSP->eTypeAudioUCode = bFlag ? RUT_NOCODE : RUT_UNKNOWN;
    return true;
}

bool rspFrameComplete(Rsp* pRSP) {
    if (pRSP->yield.bValid) {
        OSReport(D_800EE27C);
    }

    pRSP->nMode |= 4;
    return true;
}

bool rspUpdate(Rsp* pRSP, RspUpdateMode eMode) {
    RspTask* pTask;
    bool bDone;
    s32 nCount = 0;
    Frame* pFrame = SYSTEM_FRAME(pRSP->pHost);

    if ((pRSP->nMode & 4) && (pRSP->nMode & 8)) {
        if (pRSP->nMode & 0x10) {
            gNoSwapBuffer = true;
            pRSP->nMode |= 0x20;
        }
        if (!frameEnd(pFrame)) {
            return false;
        }
        pRSP->nMode &= ~0xC;
    }

    if (!(pRSP->nStatus & 1)) {
        if (pRSP->nMode & 0x20) {
            pRSP->nMode &= ~0x30;
            pRSP->nStatus |= 0x201;
            xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
            xlObjectEvent(pRSP->pHost, 0x1000, (void*)10);
        } else {
            if (pRSP->nMode & 2) {
                if (frameBeginOK(pFrame) && eMode == RUM_IDLE) {
                    pRSP->nMode &= ~0x2;
                    pRSP->nMode |= 0x10;

                    pTask = RSP_TASK(pRSP);
                    if (!rspParseGBI_Setup(pRSP, pTask)) {
                        return false;
                    }
                } else {
                    return true;
                }
            }

            if (eMode == RUM_IDLE) {
                nCount = -1;
            }

            if (nCount != 0) {
                if (rspParseGBI(pRSP, &bDone, nCount)) {
                    if (bDone) {
                        pRSP->nMode &= ~0x10;
                        pRSP->nStatus |= 0x201;
                        xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                        xlObjectEvent(pRSP->pHost, 0x1000, (void*)10);
                    }
                } else {
                    __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                }
                pRSP->nTickLast = OSGetTick();
            }
        }
    }

    return true;
}

bool rspEvent(Rsp* pRSP, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pRSP->nPC = 0;
            pRSP->pHost = pArgument;
            pRSP->nPass = 1;
            pRSP->nMode = 0;
            pRSP->yield.bValid = false;
            pRSP->nStatus = 1;
            pRSP->pfUpdateWaiting = NULL;
            if (!xlListMake(&pRSP->pListUCode, 0x60)) {
                return false;
            }
            if (!xlHeapTake(&pRSP->pDMEM, 0x1000)) {
                return false;
            }
            if (!xlHeapTake(&pRSP->pIMEM, 0x1000)) {
                return false;
            }
            if (!rspSetupS2DEX(pRSP)) {
                return false;
            }
            if (!rspInitAudioDMEM1(pRSP)) {
                return false;
            }
            pRSP->eTypeAudioUCode = RUT_NOCODE;
            break;
        case 3:
            xlHeapFree(&pRSP->pIMEM);
            xlHeapFree(&pRSP->pDMEM);
            if (!xlListFree(&pRSP->pListUCode)) {
                return false;
            }
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pRSP->pHost), pArgument, (Put8Func)rspPut8, (Put16Func)rspPut16,
                                 (Put32Func)rspPut32, (Put64Func)rspPut64)) {
                return false;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pRSP->pHost), pArgument, (Get8Func)rspGet8, (Get16Func)rspGet16,
                                 (Get32Func)rspGet32, (Get64Func)rspGet64)) {
                return false;
            }
            break;
        case 0:
        case 1:
            break;
#if VERSION != MQ_J
        case 0x1003:
            break;
#endif
        default:
            return false;
    }

    return true;
}
