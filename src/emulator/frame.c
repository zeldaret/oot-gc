#include "emulator/frame.h"
#include "dolphin.h"
#include "emulator/ram.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"
#include "macros.h"

const s32 D_800D31C0[] = {
    0x00000006, 0x00000000, 0x00000005, 0x00020000, 0x00000004, 0x00030000, 0x00000003, 0x00038000,
    0x00000002, 0x0003C000, 0x00000001, 0x0003E000, 0x00000000, 0x0003F000, 0x00000000, 0x0003F800,
};

static char D_800EA838[] = "Frame-Buffer";

_XL_OBJECTTYPE gClassFrame = {
    D_800EA838,
    sizeof(Frame),
    NULL,
    (EventFunc)frameEvent,
};

static s32 gbFrameValid;
static s32 gbFrameBegin;
static s32 snScissorChanged;
static u32 snScissorXOrig;
static u32 snScissorYOrig;
static u32 snScissorWidth;
static u32 snScissorHeight;

static volatile s32 sCopyFrameSyncReceived;

static u8 sSpecialZeldaHackON;
static u32 sDestinationBuffer;
static u32 sSrcBuffer;
static u32 sConstantBufAddr[6] ALIGNAS(32);
static u32 sNumAddr;
static u32 gHackCreditsColor;
s32 ganNameColor[] = {
    0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007,
};
static s32 sRemapI[] = {
    0x00020406,
    0x080A0C0F,
};

s32 ganNamePixel[] = {
    0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007,
};

s32 ganNameTexMtx[] = {
    0x0000001E, 0x00000021, 0x00000024, 0x00000027, 0x0000002A, 0x0000002D, 0x00000030, 0x00000033,
};

s32 ganNameTexCoord[] = {
    0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007,
};

char D_800EA8D8[] = "TEXRRR (obsolete)";
char D_800EA8EC[] = "TEXGGG (obsolete)";
char D_800EA900[] = "TEXBBB (obsolete)";
char D_800EA914[] = "GX_CC_KONST";

char* gaszNameColor[] = {
    "CPREV", "APREV", "C0",  "A0",   "C1",    "A1",   "C2",       "A2",       "TEXC",     "TEXA",
    "RASC",  "RASA",  "ONE", "HALF", "KONST", "ZERO", D_800EA8D8, D_800EA8EC, D_800EA900, D_800EA914,
};

char* gaszNameAlpha[] = {
    "APREV", "A0", "A1", "A2", "TEXA", "RASA", "KONST", "ZERO", "KONST",
};

s32 (*gapfDrawTriangle[8])(Frame*, Primitive*) = {
    frameDrawTriangle_C0T0, frameDrawTriangle_C1T0, 0x00000000, frameDrawTriangle_C3T0,
    frameDrawTriangle_C0T3, frameDrawTriangle_C1T3, 0x00000000, frameDrawTriangle_C3T3,
};

s32 (*gapfDrawLine[6])(Frame*, Primitive*) = {
    frameDrawLine_C0T0, frameDrawLine_C1T0, frameDrawLine_C2T0,
    frameDrawLine_C0T2, frameDrawLine_C1T2, frameDrawLine_C2T2,
};

s32 nCopyFrame;
s32 nLastFrame;
s32 bSkip;
s32 nCounter;
s32 gnCountMapHack;
s32 gNoSwapBuffer;
static u16 sTempZBuf[4800][4][4] ALIGNAS(32);

s32 sZBufShift[] = {
    0x0003F800, 0x00000000, 0x0003F000, 0x00000000, 0x0003E000, 0x00000001, 0x0003C000, 0x00000002,
    0x00038000, 0x00000003, 0x00030000, 0x00000004, 0x00020000, 0x00000005, 0x00000000, 0x00000006,
};

char D_800EAA0C[] = "PRIMITIVE";
char D_800EAA18[] = "ENVIRONMENT";
char* gaszNameColorType[] = {
    "FOG", "FILL", "BLEND", D_800EAA0C, D_800EAA18,
};

static GXTexObj sFrameObj1;
static GXTexObj sFrameObj2;
static GXTexObj sFrameObj_1564;
static GXTexObj sFrameObj_1565;
static GXTexObj sFrameObj_1568;
static u32 line_1582[80][4][4];
static u16 line_1606[80][4][4];
static u16 line_1630[80][4][4];
static GXTexObj sFrameObj_1647;
static u8 cAlpha = 0x0F;
static GXTexObj sFrameObj_1660;
static GXTexObj frameObj_1663;
static GXTexObj frameObj_1673;

s32 sCommandCodes_1679[] = {
    0xF5500000, 0x07080200, 0xE6000000, 0x00000000, 0xF3000000, 0x073BF01A, 0xE7000000, 0x00000000,
};

s32 sCommandCodes_1702[] = {
    0xE7000000, 0x00000000, 0xEF000CF0, 0x0F0A4004, 0xFB000000,
    0xFFFFFFFF, 0xFC12FE25, 0xFFFFFBFD, 0xFF10013F, 0x804096C0,
};

s32 sCommandCodes2[] = {
    0xE7000000, 0x00000000, 0xE7000000, 0x00000000, 0xEF000CF0,
    0x0F0A0004, 0xFCFFFFFF, 0xFFFCFE7F, 0xFF88013F, 0x80784600,
};

static u16 tempLine[16][4][4];

s32 GBIcode[] = {
    0xED000000,
    0x0B000000,
    0x0A000000,
};

s32 GBIcode2D2[] = {
    0xB9000000, 0xBA000000, 0xE7000000, 0xBA000000, 0xC1000000, 0xE7000000, 0x02000000,
};

s32 GBIcode3D1[] = {
    0xBA000000, 0xFC000000, 0xB9000000, 0xBA000000, 0xB9000000,
};

s32 GBIcode3D2[] = {
    0xE7000000, 0xBA000000, 0xFC000000, 0xB9000000, 0xBA000000, 0xB9000000,
};

s32 anRenderModeDatabaseCycle2[] = {
    0x0C192078, 0x00552078, 0x0C184F50, 0x00504A50, 0x0F0A4000, 0xC8112078, 0x0C187858, 0x00442078, 0x00553078,
    0xC8113078, 0x00443078, 0x00552D58, 0xC8112D58, 0x005049D8, 0xC81049D8, 0x0C193078, 0x00504240, 0x5F505240,
    0x0C184240, 0x0C182048, 0x0C183048, 0x0C182078, 0x0C192D58, 0x0C1849D8, 0x0F0A7008, 0x0C1841C8, 0x0C184DD8,
    0x0C183078, 0x0C1845D8, 0x00504241, 0x0C184341, 0x0C184241, 0xC8104DD8, 0xC8104F50, 0x00504341, 0xC8104A50,
    0x00504340, 0x0C184340, 0xC8104B50, 0x0C184B50, 0x0C184B51, 0x00504B51, 0x0F0A4004, 0x0F0A3231, 0x00504B50,
    0xC81049F8, 0xC8103478, 0x005041C8, 0xC4104240, 0x00552038, 0x0F0A100C, 0x0C184A50, 0xC8104A51, 0xC8112479,
    0xC81045D8, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000,
};

s32 anRenderModeDatabaseCopy[] = {
    0x0F0A7008, 0x00000001, 0x0F0A4001, 0x00442478, 0x00442479, 0x005041C9, 0x00552079, 0x00552078, 0x005045D8,
    0x005045D9, 0x00504DD8, 0x00504DD9, 0x00553078, 0x00553079, 0x0F0A4000, 0x005049D8, 0x005049D9, 0x00442078,
    0x00442079, 0x0F0A7009, 0x00504240, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000,
};

s32 anRenderModeDatabaseFill[] = {
    0x0F0A4000, 0x0C084000, 0x00000001, 0x0F0A4001, 0x00504240, 0xC8112078, 0x00504341, 0x00504244, 0x00504340,
    0x00504241, 0x00504B50, 0x0C184241, 0x0F0A4004, 0x00553049, 0x00552078, 0x0F0A100C, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000,
};

s32 anRenderModeDatabaseCycle1[] = {
    0x0F0A4000, 0x00552048, 0x0F0A7008, 0x00552078, 0x0C084000, 0x00504241, 0x00504240, 0x0F0A4001, 0x005041C8,
    0x00552D58, 0x0C184F50, 0x00504F50, 0x0C192078, 0x00504A50, 0x00000001, 0x005049D8, 0xC8112078, 0x0C187858,
    0x00552230, 0x00442478, 0x00443078, 0x00442479, 0x00443079, 0x005041C9, 0x00553048, 0x00553078, 0x00504DD8,
    0x005045D8, 0x004049F8, 0x004049D8, 0x00442078, 0xC8113078, 0x005049DB, 0x00442D58, 0xC8112D58, 0x004049F8,
    0xC81049D8, 0x0C193078, 0x00504B50, 0x00504340, 0x5F505240, 0x0C182078, 0x0C182048, 0x0F0A7009, 0x0C1841C8,
    0x0C184240, 0x0C1849D8, 0x00504244, 0x0C184340, 0x00504B51, 0x0C184B50, 0x0F0A4004, 0x0F0A4044, 0x0F0A0004,
    0xC8104B50, 0x0FA54044, 0x00504341, 0x00553049, 0x0F0A3231, 0xC8104F50, 0x00552038, 0xC4104240, 0x00504344,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000,
};

char D_800EB13C[] = "GetTextureInfo: Unknown texture-format: %d\n";

extern void* lbl_8001D3FC;
extern void* lbl_8001D418;
extern void* lbl_8001D418;
extern void* lbl_8001D42C;
extern void* lbl_8001D42C;
extern void* lbl_8001D42C;
extern void* lbl_8001D444;
extern void* lbl_8001D45C;
extern void* lbl_8001D3FC;
extern void* lbl_8001D418;

void* jtbl_800EB168[] = {&lbl_8001D3FC, &lbl_8001D418, &lbl_8001D418, &lbl_8001D42C, &lbl_8001D42C,
                         &lbl_8001D42C, &lbl_8001D444, &lbl_8001D45C, &lbl_8001D3FC, &lbl_8001D418};

extern void* lbl_80020074;
extern void* lbl_80020084;
extern void* lbl_800200C8;
extern void* lbl_800200D8;
extern void* lbl_800200E8;
extern void* lbl_80020134;
extern void* lbl_80020144;
extern void* lbl_80020144;
extern void* lbl_80020144;
extern void* lbl_80020144;

void* jtbl_800EB190[] = {&lbl_80020074, &lbl_80020084, &lbl_800200C8, &lbl_800200D8, &lbl_800200E8,
                         &lbl_80020134, &lbl_80020144, &lbl_80020144, &lbl_80020144, &lbl_80020144};
char D_800EB1B8[] = "frameEnd: INTERNAL ERROR: Called when 'gbFrameBegin' is TRUE!\n";
char D_800EB1F8[] = "Waiting for valid?\n";

extern void* lbl_800297DC;
extern void* lbl_800297E8;
extern void* lbl_800297F4;
extern void* lbl_80029800;
extern void* lbl_8002980C;
extern void* lbl_80029818;
extern void* lbl_80029824;
extern void* lbl_80029830;

#ifndef NON_MATCHING
void* jtbl_800EB20C[] = {
    &lbl_800297DC, &lbl_800297E8, &lbl_800297F4, &lbl_80029800,
    &lbl_8002980C, &lbl_80029818, &lbl_80029824, &lbl_80029830,
};
#endif

extern void* lbl_8002986C;
extern void* lbl_80029878;
extern void* lbl_80029884;
extern void* lbl_80029890;
extern void* lbl_8002989C;
extern void* lbl_800298A8;
extern void* lbl_80029920;
extern void* lbl_800298B4;
extern void* lbl_800298C0;
extern void* lbl_800298CC;
extern void* lbl_800298D8;
extern void* lbl_800298E4;
extern void* lbl_800298F0;
extern void* lbl_800298FC;
extern void* lbl_80029908;
extern void* lbl_80029914;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_80029938;
extern void* lbl_8002992C;

#ifndef NON_MATCHING
void* jtbl_800EB22C[] = {
    &lbl_8002986C, &lbl_80029878, &lbl_80029884, &lbl_80029890, &lbl_8002989C, &lbl_800298A8, &lbl_80029920,
    &lbl_800298B4, &lbl_800298C0, &lbl_800298CC, &lbl_800298D8, &lbl_800298E4, &lbl_800298F0, &lbl_800298FC,
    &lbl_80029908, &lbl_80029914, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938,
    &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938,
    &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_8002992C,
};
#endif

char D_800EB2AC[] = "LoadTexture: Unknown FILTER mode (%d)\n";
char D_800EB2D4[] = "MakeTexture: 'aTexture' is exhausted!\0\0";

static char D_80134E58[] = "frame.c";

const f32 D_80135E00 = 0.0;
const f32 D_80135E04 = 0.25;
const f32 D_80135E08 = 2.0;
const f64 D_80135E10 = 4503601774854144.0;
const f32 D_80135E18 = 0.0625;
const f32 D_80135E1C = 0.0078125;
const f32 D_80135E20 = 4096.0;
const f32 D_80135E24 = 4194304.0;
const f64 D_80135E28 = 4503599627370496.0;
const f32 D_80135E30 = 0.5;
const f32 D_80135E34 = 3.0;
const f32 D_80135E38 = 1.0;
const f64 D_80135E40 = 0.5;
const f64 D_80135E48 = 3.0;
const f32 D_80135E50 = 0.2267303466796875;
const f32 D_80135E54 = 0.3183135986328125;
const f32 D_80135E58 = 0.006240000016987324;
const f32 D_80135E5C = 0.0062420000322163105;
const f32 D_80135E60 = 640.0;
const f32 D_80135E64 = 480.0;
const f32 D_80135E68 = 320.0;
const f32 D_80135E6C = 240.0;
const f64 D_80135E70 = 262143.0;
const f64 D_80135E78 = 43.52;
const f32 D_80135E80 = 80.0;
const f32 D_80135E84 = 31.0;
const f32 D_80135E88 = 0.015625;
const f32 D_80135E8C = 143.0;
const f32 D_80135E90 = 0.859375;
const f32 D_80135E94 = 0.949999988079071;
const f32 D_80135E98 = 0.8999999761581421;
const f32 D_80135E9C = 0.8500000238418579;
const f32 D_80135EA0 = 0.800000011920929;
const f32 D_80135EA4 = -1.0;
const f32 D_80135EA8 = 319.0;
const f32 D_80135EAC = 239.0;
const f32 D_80135EB0 = -1001.0;
const f32 D_80135EB4 = -53.0;
const f32 D_80135EB8 = -3080.0;
const f32 D_80135EBC = 6067.0;
const f32 D_80135EC0 = -31.0;
const f32 D_80135EC4 = 1669.0;
const f32 D_80135EC8 = 1000.0;
const f32 D_80135ECC = 32000.0;
const f32 D_80135ED0 = 30.0;
const f32 D_80135ED4 = 1.3333333730697632;
const f32 D_80135ED8 = 0.10000000149011612;
const f32 D_80135EDC = 0.001500000013038516;
const f32 D_80135EE0 = 65536.0;
const f32 D_80135EE4 = 1001.0;
const f32 D_80135EE8 = 500.0;
const f32 D_80135EEC = 970.0;
const f32 D_80135EF0 = 59.0;
const f32 D_80135EF4 = 990.0;
const f32 D_80135EF8 = 0.20999999344348907;
const f32 D_80135EFC = 0.3499999940395355;
const f32 D_80135F00 = 12800.0;
const f32 D_80135F04 = 0.6000000238418579;
const f32 D_80135F08 = 0.699999988079071;
const f32 D_80135F0C = 44.0;
const f32 D_80135F10 = 0.12999999523162842;
const f32 D_80135F14 = 45.0;
const f32 D_80135F18 = 15.0;
const f32 D_80135F1C = 0.3799999952316284;
const f32 D_80135F20 = 900.0;
const f32 D_80135F24 = 350.0;
const f32 D_80135F28 = 10.0;
const f32 D_80135F2C = 200.0;
const f32 D_80135F30 = 128000.0;
const f32 D_80135F34 = -25344.0;
const f32 D_80135F38 = 25600.0;
const f32 D_80135F3C = 2200.0;
const f32 D_80135F40 = 0.574999988079071;
const f32 D_80135F44 = 0.75;
const f32 D_80135F48 = -21077.0;
const f32 D_80135F4C = 21333.0;
const f32 D_80135F50 = -90.0;
const f32 D_80135F54 = 258.0;
const f32 D_80135F58 = 0.44999998807907104;
const f32 D_80135F5C = -667.0;
const f32 D_80135F60 = 688.0;
const f32 D_80135F64 = 0.00390625;
const f32 D_80135F68 = 860.0;
const f32 D_80135F6C = 0.15000000596046448;
const f32 D_80135F70 = 140.0;
const f32 D_80135F74 = 0.2800000011920929;
const f32 D_80135F78 = 0.7200000286102295;
const f32 D_80135F7C = 0.25999999046325684;
const f32 D_80135F80 = 8.4399995803833;
const f64 D_80135F88 = 8.44;

// TODO: caused by inline asm somewhere, remove when that function is matched
#pragma peephole off

static s32 frameDrawSetupSP(Frame* pFrame, s32* pnColors, s32* pbFlag, s32 nVertexCount);
static s32 frameDrawSetupDP(Frame* pFrame, s32* pnColors, s32* pbFlag, s32);
static s32 frameDrawRectFill(Frame* pFrame, Rectangle* pRectangle);
static s32 frameDrawTriangle_Setup(Frame* pFrame, Primitive* pPrimitive);
static s32 frameDrawRectTexture_Setup(Frame* pFrame, Rectangle* pRectangle);
inline s32 frameGetMatrixHint(Frame* pFrame, u32 nAddress, s32* piHint);

inline s32 frameSetProjection(Frame* pFrame, s32 iHint) {
    MatrixHint* pHint = &pFrame->aMatrixHint[iHint];

    pFrame->nMode |= 0x24000000;
    pFrame->nMode &= ~0x18000000;

    if (pHint->eProjection == FMP_PERSPECTIVE) {
        C_MTXPerspective(pFrame->matrixProjection, pHint->rFieldOfViewY, pHint->rAspect, pHint->rClipNear,
                         pHint->rClipFar);
    } else if (pHint->eProjection == FMP_ORTHOGRAPHIC) {
        C_MTXOrtho(pFrame->matrixProjection, 0.0f, pFrame->anSizeY[0] - 1.0f, 0.0f, pFrame->anSizeX[0] - 1.0f,
                   pHint->rClipNear, pHint->rClipFar);
    } else {
        return 0;
    }

    pFrame->eTypeProjection = pHint->eProjection;
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupFog_Zelda1.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupFog_Default.s")

static void frameDrawSyncCallback(u16 nToken) {
    if (nToken == 0x7D00) {
        sCopyFrameSyncReceived = 1;
    }
}

static void frameDrawDone() {
    if (gbFrameValid != 0) {
        gbFrameValid = 0;
        if (gNoSwapBuffer == 0) {
            VISetNextFrameBuffer(DemoCurrentBuffer);
            VIFlush();
            if (DemoCurrentBuffer == DemoFrameBuffer1) {
                DemoCurrentBuffer = DemoFrameBuffer2;
            } else {
                DemoCurrentBuffer = DemoFrameBuffer1;
            }
        } else {
            VIFlush();
            gNoSwapBuffer = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameMakeTLUT.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameMakePixels.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameLoadTexture.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetup2D.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupSP.s")

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameGetCombineColor.s")
#else
static s32 frameGetCombineColor(Frame* pFrame, GXTevColorArg* pnColorTEV, s32 nColorN64) {
    switch (nColorN64) {
        case 0:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 1:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 2:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 3:
            *pnColorTEV = GX_CC_C0;
            break;
        case 4:
            *pnColorTEV = GX_CC_RASC;
            break;
        case 5:
            *pnColorTEV = GX_CC_C1;
            break;
        case 7:
            *pnColorTEV = GX_CC_TEXA;
            break;
        case 8:
            *pnColorTEV = GX_CC_TEXA;
            break;
        case 9:
            *pnColorTEV = GX_CC_TEXA;
            break;
        case 10:
            *pnColorTEV = GX_CC_A0;
            break;
        case 11:
            *pnColorTEV = GX_CC_RASA;
            break;
        case 12:
            *pnColorTEV = GX_CC_A1;
            break;
        case 13:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 14:
            *pnColorTEV = GX_CC_TEXC;
            break;
        case 15:
            *pnColorTEV = GX_CC_C2;
            break;
        case 6:
            *pnColorTEV = GX_CC_ONE;
            break;
        case 31:
            *pnColorTEV = GX_CC_ZERO;
            break;
        default:
            return 0;
    }

    return 1;
}
#endif

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameGetCombineAlpha.s")
#else
static s32 frameGetCombineAlpha(Frame* pFrame, GXTevAlphaArg* pnAlphaTEV, s32 nAlphaN64) {
    switch (nAlphaN64) {
        case 0:
            *pnAlphaTEV = GX_CA_TEXA;
            break;
        case 1:
            *pnAlphaTEV = GX_CA_TEXA;
            break;
        case 2:
            *pnAlphaTEV = GX_CA_TEXA;
            break;
        case 3:
            *pnAlphaTEV = GX_CA_A0;
            break;
        case 4:
            *pnAlphaTEV = GX_CA_RASA;
            break;
        case 5:
            *pnAlphaTEV = GX_CA_A1;
            break;
        case 6:
            *pnAlphaTEV = GX_CA_KONST;
            break;
        case 7:
            *pnAlphaTEV = GX_CA_ZERO;
            break;
        default:
            return 0;
    }

    return 1;
}
#endif

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupDP.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawTriangle_C0T0.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawTriangle_C1T0.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawTriangle_C3T0.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawTriangle_C0T3.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawTriangle_C1T3.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameCheckTriangleDivide.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawTriangle_C3T3.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawTriangle_Setup.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C0T0.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C1T0.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C2T0.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C0T2.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C1T2.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C2T2.s")

static s32 frameDrawLine_Setup(Frame* pFrame, Primitive* pPrimitive) {
    s32 bFlag;
    s32 nColors;

    if (!frameDrawSetupSP(pFrame, &nColors, &bFlag, 2)) {
        return 0;
    }

    if (!frameDrawSetupDP(pFrame, &nColors, &bFlag, 0)) {
        return 0;
    }

    pFrame->aDraw[0] = (FrameDrawFunc)gapfDrawLine[nColors + (bFlag ? 3 : 0)];
    if (!pFrame->aDraw[0](pFrame, pPrimitive)) {
        return 0;
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawRectFill.s")

static s32 frameDrawRectFill_Setup(Frame* pFrame, Rectangle* pRectangle) {
    s32 bFlag;
    s32 nColors;

    if (!frameDrawSetup2D(pFrame)) {
        return 0;
    }

    bFlag = 0;
    nColors = 0;

    if (!frameDrawSetupDP(pFrame, &nColors, &bFlag, 1)) {
        return 0;
    }

    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill;

    if (!pFrame->aDraw[2](pFrame, pRectangle)) {
        return 0;
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawRectTexture.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawRectTexture_Setup.s")

s32 frameShow() { return 1; }

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetScissor.s")

s32 frameSetDepth(Frame* pFrame, f32 rDepth, f32 rDelta) {
    pFrame->rDepth = rDepth;
    pFrame->rDelta = rDelta;
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetColor.s")

s32 frameBeginOK(void) {
    if (gbFrameValid != 0) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameBegin.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameEnd.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/_frameDrawRectangle.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameNoBlend.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameBlur.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrame.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/CopyAndConvertCFB.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaGreyScaleConvert.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameShrink.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameCamera.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameHackTIMG_Zelda.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameHackCIMG_Zelda2.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameHackCIMG_Zelda.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameHackCIMG_Zelda2_Shrink.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameHackCIMG_Zelda2_Camera.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/PanelDrawBG8.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/PanelDrawBG16.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/PanelDrawFR3D.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameHackTIMG_Panel.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameHackCIMG_Panel.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameGetDepth.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameEvent.s")

inline s32 frameCopyMatrix(Mtx44 matrixTarget, Mtx44 matrixSource) {
    matrixTarget[0][0] = matrixSource[0][0];
    matrixTarget[0][1] = matrixSource[0][1];
    matrixTarget[0][2] = matrixSource[0][2];
    matrixTarget[0][3] = matrixSource[0][3];
    matrixTarget[1][0] = matrixSource[1][0];
    matrixTarget[1][1] = matrixSource[1][1];
    matrixTarget[1][2] = matrixSource[1][2];
    matrixTarget[1][3] = matrixSource[1][3];
    matrixTarget[2][0] = matrixSource[2][0];
    matrixTarget[2][1] = matrixSource[2][1];
    matrixTarget[2][2] = matrixSource[2][2];
    matrixTarget[2][3] = matrixSource[2][3];
    matrixTarget[3][0] = matrixSource[3][0];
    matrixTarget[3][1] = matrixSource[3][1];
    matrixTarget[3][2] = matrixSource[3][2];
    matrixTarget[3][3] = matrixSource[3][3];
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameScaleMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameConvertYUVtoRGB.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/packTakeBlocks.s")

static s32 packFreeBlocks(s32* piPack, u32* anPack) {
    s32 iPack;
    u32 nMask;

    s32 temp_r6;

    iPack = *piPack;

    if (iPack == -1) {
        return 1;
    }

    nMask = ((1 << (iPack >> 16)) - 1) << (iPack & 0x1F);
    temp_r6 = (iPack & 0xFFFF) >> 5;

    if (nMask == (nMask & anPack[temp_r6])) {
        anPack[temp_r6] &= ~nMask;
        *piPack = -1;
        return 1;
    }

    return 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameMakeTexture.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetupCache.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameUpdateCache.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameLoadTile.s")

s32 frameDrawReset(Frame* pFrame, s32 nFlag) {
    pFrame->nFlag |= nFlag;
    pFrame->aDraw[0] = (FrameDrawFunc)frameDrawLine_Setup;
    pFrame->aDraw[1] = (FrameDrawFunc)frameDrawTriangle_Setup;
    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill_Setup;
    pFrame->aDraw[3] = (FrameDrawFunc)frameDrawRectTexture_Setup;
    return 1;
}

s32 frameSetFill(Frame* pFrame, s32 bFill) {
    if (bFill) {
        pFrame->nMode |= 0x20000;
    } else {
        pFrame->nMode &= ~0x20000;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetMode.s")

s32 frameGetMode(Frame* pFrame, Etype eType, u32* pnMode) {
    *pnMode = pFrame->aMode[eType];
    return 1;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetMatrix.s")
#else
s32 frameSetMatrix(Frame* pFrame, Mtx44 matrix, TypeProjection eType, s32 bLoad, s32 bPush, s32 nAddressN64) {
    s32 pad1;
    s32 bFlag;
    f32(*matrixTarget)[4];
    Mtx44 matrixResult;
    s32 pad2[9];

    OSGetTick();

    switch (eType) {
        case FMP_PERSPECTIVE:
            if (!bLoad && (pFrame->nMode & 0x800000)) {
                bFlag = 1;
                PSMTX44Concat(matrix, pFrame->aMatrixModel[pFrame->iMatrixModel], matrixResult);
            } else {
                bFlag = 0;
            }

            if (bPush && pFrame->iMatrixModel < ARRAY_COUNT(pFrame->aMatrixModel) - 1) {
                pFrame->iMatrixModel++;
            }

            if (bFlag) {
                matrixTarget = pFrame->aMatrixModel[pFrame->iMatrixModel];
                frameCopyMatrix(matrixTarget, matrixResult);
            } else {
                matrixTarget = pFrame->aMatrixModel[pFrame->iMatrixModel];
                frameCopyMatrix(matrixTarget, matrix);
            }

            pFrame->nMode |= 0x800000;
            pFrame->nMode &= ~0x600000;
            break;
        case FMP_ORTHOGRAPHIC:
            pFrame->nMode &= ~0x20000000;
            if (gpSystem->eTypeROM == SRT_1080 && (matrix[0][0] < 0.006240f || matrix[0][0] > 0.006242f)) {
                if (!frameSetProjection(pFrame, pFrame->iHintHack)) {
                    return 0;
                }
                bLoad = 0;
            }

            // TODO: fake volatile
            if (bLoad || !(*(volatile u32*)&pFrame->nMode & 0x4000000) ||
                (*(volatile u32*)&pFrame->nMode & 0x10000000)) {
                if (matrix[0][0] == 1.0f && matrix[0][1] == 0.0f && matrix[0][2] == 0.0f && matrix[0][3] == 0.0f &&
                    matrix[1][0] == 0.0f && matrix[1][1] == 1.0f && matrix[1][2] == 0.0f && matrix[1][3] == 0.0f &&
                    matrix[2][0] == 0.0f && matrix[2][1] == 0.0f && matrix[2][2] == 1.0f && matrix[2][3] == 0.0f &&
                    matrix[3][0] == 0.0f && matrix[3][1] == 0.0f && matrix[3][2] == 0.0f && matrix[3][3] == 1.0f) {
                    pFrame->nMode |= 0x10000000;
                } else {
                    pFrame->nMode &= ~0x10000000;
                }

                matrixTarget = pFrame->matrixProjection;
                frameCopyMatrix(matrixTarget, matrix);

                pFrame->nMode |= 0x4000000;
                pFrame->nMode &= ~0x8000000;

                if (!frameGetMatrixHint(pFrame, nAddressN64 | 0x80000000, &pFrame->iHintProjection)) {
                    pFrame->iHintProjection = -1;
                }
            } else if (*(volatile u32*)&pFrame->nMode & 0x8000000) {
                PSMTX44Concat(matrix, pFrame->matrixProjectionExtra, pFrame->matrixProjectionExtra);
            } else {
                pFrame->nMode |= 0x8000000;
                matrixTarget = pFrame->matrixProjectionExtra;
                frameCopyMatrix(matrixTarget, matrix);
            }

            pFrame->nMode &= ~0x400000;
            frameDrawReset(pFrame, 0x40000);
            break;
        default:
            return 0;
    }

    return 1;
}
#endif

s32 frameGetMatrix(Frame* pFrame, Mtx44 matrix, TypeProjection eType, s32 bPull) {
    switch (eType) {
        case FMP_PERSPECTIVE:
            if (matrix != NULL) {
                if (!xlHeapCopy(matrix, pFrame->aMatrixModel[pFrame->iMatrixModel], sizeof(Mtx44))) {
                    return 0;
                }
            }
            if (bPull) {
                if (pFrame->iMatrixModel > 0) {
                    pFrame->iMatrixModel--;
                    pFrame->nMode &= ~0x600000;
                }
            }
            break;
        case FMP_ORTHOGRAPHIC:
            if (matrix != NULL) {
                if (pFrame->nMode & 0x8000000) {
                    PSMTX44Concat(pFrame->matrixProjectionExtra, pFrame->matrixProjection, matrix);
                } else {
                    if (!xlHeapCopy(matrix, pFrame->matrixProjection, sizeof(Mtx44))) {
                        return 0;
                    }
                }
            }
            break;
        default:
            return 0;
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameLoadVertex.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameCullDL.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameLoadTLUT.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameLoadTMEM.s")

s32 frameSetLightCount(Frame* pFrame, s32 nCount) {
    pFrame->nCountLight = nCount;
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetLight.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetLookAt.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetViewport.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameResetUCode.s")

s32 frameSetBuffer(Frame* pFrame, FBTType eType) {
    if (((u32)(eType - 2) > 1) && (eType == FBT_DEPTH)) {
        pFrame->nOffsetDepth0 = pFrame->aBuffer[0].nAddress & 0x03FFFFFF;
        pFrame->nOffsetDepth1 = pFrame->nOffsetDepth0 + 0x257FC;
    }
    return 1;
}

s32 frameFixMatrixHint(Frame* pFrame, u32 nAddressFloat, u32 nAddressFixed) {
    s32 iHint;
    s32 iHintTest;

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if (pFrame->aMatrixHint[iHint].nAddressFloat == nAddressFloat && pFrame->aMatrixHint[iHint].nCount >= 0) {
            pFrame->aMatrixHint[iHint].nAddressFloat = 0;
            pFrame->aMatrixHint[iHint].nAddressFixed = nAddressFixed;

            for (iHintTest = 0; iHintTest < pFrame->iHintMatrix; iHintTest++) {
                if (iHintTest != iHint && pFrame->aMatrixHint[iHintTest].nAddressFixed == nAddressFixed) {
                    pFrame->aMatrixHint[iHintTest].nAddressFloat = 0;
                    pFrame->aMatrixHint[iHintTest].nAddressFixed = 0;
                }
            }

            return 1;
        }
    }

    return 0;
}

inline s32 frameGetMatrixHint(Frame* pFrame, u32 nAddress, s32* piHint) {
    s32 iHint;

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if (pFrame->aMatrixHint[iHint].nAddressFixed == nAddress && pFrame->aMatrixHint[iHint].nCount >= 0) {
            pFrame->aMatrixHint[iHint].nCount = 4;
            *piHint = iHint;
            return 1;
        }
    }

    return 0;
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetMatrixHint.s")
#else
s32 frameSetMatrixHint(Frame* pFrame, TypeProjection eProjection, s32 nAddressFloat, s32 nAddressFixed, f32 rNear,
                       f32 rFar, f32 rFOVY, f32 rAspect, f32 rScale) {
    s32 iHint;

    if (nAddressFloat != 0) {
        nAddressFloat |= 0x80000000;
    }
    if (nAddressFixed != 0) {
        nAddressFixed |= 0x80000000;
    }

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if ((nAddressFloat != 0 && pFrame->aMatrixHint[iHint].nAddressFloat == nAddressFloat) ||
            (nAddressFixed != 0 && pFrame->aMatrixHint[iHint].nAddressFixed == nAddressFixed)) {
            break;
        }
    }

    if (iHint == pFrame->iHintMatrix) {
        for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
            if (pFrame->aMatrixHint[iHint].nCount < 0) {
                break;
            }
        }
    }

    if (eProjection == 1) {
        rScale = 0.0f;
    }

    pFrame->aMatrixHint[iHint].nCount = 4;
    pFrame->aMatrixHint[iHint].rScale = rScale;
    pFrame->aMatrixHint[iHint].rClipFar = rFar;
    pFrame->aMatrixHint[iHint].rClipNear = rNear;
    pFrame->aMatrixHint[iHint].rAspect = rAspect;
    pFrame->aMatrixHint[iHint].rFieldOfViewY = rFOVY;
    pFrame->aMatrixHint[iHint].eProjection = eProjection;
    pFrame->aMatrixHint[iHint].nAddressFloat = nAddressFloat;
    pFrame->aMatrixHint[iHint].nAddressFixed = nAddressFixed;

    if (iHint == pFrame->iHintMatrix) {
        pFrame->iHintMatrix++;
    }

    pFrame->iHintLast = iHint;
    return 1;
}
#endif

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameInvalidateCache.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameGetTextureInfo.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/PSMTX44MultVecNoW.s")
