#include "emulator/frame.h"
#include "dolphin.h"
#include "emulator/cpu.h"
#include "emulator/ram.h"
#include "emulator/rdp.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"
#include "macros.h"

#define FRAME_SYNC_TOKEN 0x7D00

// N64 frame buffer dimensions
#define N64_FRAME_WIDTH 320
#define N64_FRAME_HEIGHT 240

// GC is rendered at double the resolution
#define GC_FRAME_WIDTH (N64_FRAME_WIDTH * 2)
#define GC_FRAME_HEIGHT (N64_FRAME_HEIGHT * 2)

// Dimensions of the player preview on the equipment menu of the Zelda pause screen
#define ZELDA_PAUSE_EQUIP_PLAYER_WIDTH 64
#define ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT 112

#define ZELDA2_CAMERA_WIDTH 160
#define ZELDA2_CAMERA_HEIGHT 128

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

u32 ganNameColor[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

static u8 sRemapI[] = {
    0, 2, 4, 6, 8, 10, 12, 15,
};

GXTexMapID ganNamePixel[] = {
    GX_TEXMAP0, GX_TEXMAP1, GX_TEXMAP2, GX_TEXMAP3, GX_TEXMAP4, GX_TEXMAP5, GX_TEXMAP6, GX_TEXMAP7,
};

u32 ganNameTexMtx[] = {
    0x1E, 0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30, 0x33,
};

GXTexCoordID ganNameTexCoord[] = {
    GX_TEXCOORD0, GX_TEXCOORD1, GX_TEXCOORD2, GX_TEXCOORD3, GX_TEXCOORD4, GX_TEXCOORD5, GX_TEXCOORD6, GX_TEXCOORD7,
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
static u16 sTempZBuf[N64_FRAME_WIDTH * N64_FRAME_HEIGHT / 16][4][4] ALIGNAS(32);

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
static u32 line_1582[N64_FRAME_WIDTH / 4][4][4];
static u16 line_1606[N64_FRAME_WIDTH / 4][4][4];
static u16 line_1630[N64_FRAME_WIDTH / 4][4][4];
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

static u16 tempLine[ZELDA_PAUSE_EQUIP_PLAYER_WIDTH / 4][4][4];

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

#define GBI_COMMAND_HI(p) (((u32*)(p))[0])
#define GBI_COMMAND_LO(p) (((u32*)(p))[1])
#define SEGMENT_ADDRESS(pRSP, nOffsetRDRAM) \
    (pRSP->anBaseSegment[((nOffsetRDRAM) >> 24) & 0xF] + ((nOffsetRDRAM)&0xFFFFFF))

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

static inline void CopyCFB(u16* srcP) {
    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_TRUE);
    DCInvalidateRange(srcP, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
    GXCopyTex(srcP, GX_FALSE);
    sCopyFrameSyncReceived = 0;
    GXSetDrawSync(FRAME_SYNC_TOKEN);
    while (!sCopyFrameSyncReceived) {}
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupFog_Zelda1.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupFog_Default.s")

static void frameDrawSyncCallback(u16 nToken) {
    if (nToken == FRAME_SYNC_TOKEN) {
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
    if (gbFrameValid) {
        return 0;
    }
    return 1;
}

inline void frameClearModes(Frame* pFrame) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(pFrame->aMode); i++) {
        pFrame->aMode[i] = 0;
    }
}

s32 frameBegin(Frame* pFrame, s32 nCountVertex) {
    s32 i;
    Mtx matrix;

    if (gbFrameBegin) {
        gbFrameBegin = 0;

        while (gbFrameValid) {
            OSReport(D_800EB1F8);
        }

        if (!simulatorTestReset(0, 0, 1, 0)) {
            return 0;
        }

        if (!frameUpdateCache(pFrame)) {
            return 0;
        }

        xlCoreBeforeRender();
        pFrame->nMode &= ~0x180000;

        GXSetMisc(GX_MT_XF_FLUSH, 8);
        PSMTXIdentity(matrix);
        GXLoadPosMtxImm(matrix, 0);

        pFrame->nCountVertex = nCountVertex;

        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);

        GXSetDrawSyncCallback(&frameDrawSyncCallback);

        for (i = 0; i < 8; i++) {
            GXSetTexCoordGen(ganNameTexCoord[i], GX_TG_MTX2x4, GX_TG_TEX0, ganNameTexMtx[i]);
        }

        GXSetScissor(0, 0, pFrame->anSizeX[1], pFrame->anSizeY[1]);
    }

    pFrame->iMatrixModel = 0;
    pFrame->nMode &= 0x9C1F0000;
    pFrame->nMode &= ~0x1C000000;
    pFrame->iHintProjection = -1;

    frameClearModes(pFrame);

    pFrame->nWidthLine = -1;
    pFrame->nCountLight = 0;

    frameDrawReset(pFrame, 0x47F2D);

    pFrame->nModeVtx = -1;
    pFrame->nAddressLoad = -1;
    return 1;
}

s32 frameEnd(Frame* pFrame) {
    Cpu* pCPU;
    s32 iHint;
    void* pData;

    pCPU = SYSTEM_CPU(gpSystem);

    if (gbFrameBegin) {
        OSReport(D_800EB1B8);
    }
    gbFrameBegin = 1;

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if (pFrame->aMatrixHint[iHint].nCount >= 0) {
            pFrame->aMatrixHint[iHint].nCount--;
        }
    }

    pFrame->nCountFrames++;
    gbFrameValid = 1;

    if (pFrame->aBuffer[0].nAddress != 0) {
        pData = &sTempZBuf;

        GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
        GXSetTexCopyDst(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_Z16, GX_TRUE);
        GXCopyTex(pData, GX_FALSE);
        DCInvalidateRange(pData, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
    }

    if (gpSystem->eTypeROM == SRT_DRMARIO && pFrame->bGrabbedFrame) {
        pData = pFrame->nTempBuffer;
        CopyCFB(pData);
        pFrame->bGrabbedFrame = 0;
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
    GXSetDrawDone();
    GXFlush();

    if (gpSystem->eTypeROM == SRT_ZELDA2) {
        pFrame->nHackCount = 0;
        pFrame->nFrameCounter++;
        pFrame->bBlurredThisFrame = 0;
        pFrame->nFrameCIMGCalls = 0;
        pFrame->bUsingLens = 0;
        pFrame->bModifyZBuffer = 0;
        pFrame->bOverrideDepth = 0;

        pFrame->nLastFrameZSets = pFrame->nZBufferSets;
        pFrame->nZBufferSets = 0;

        pFrame->bPauseBGDrawn = 0;
        GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);

        if ((pFrame->bShrinking & 0xF) == 0) {
            pFrame->bShrinking &= ~0xFFFF;
        }
        pFrame->bShrinking &= ~0xFF;
        pFrame->bSnapShot = 0;
    }

    if (gpSystem->eTypeROM == SRT_DRMARIO) {
        pFrame->bBackBufferDrawn = 0;
    }

    pCPU->gTree->kill_number = 0;
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/_frameDrawRectangle.s")

#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameNoBlend.s")

// matches but data doesn't
//! TODO: make sFrameObj a static variable in the function
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameBlur.s")
#else
void ZeldaDrawFrameBlur(Frame* pFrame, u16* pData) {
    Mtx matrix;
    s32 pad[8];
    GXColor color;

    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = pFrame->cBlurAlpha;

    frameDrawSetup2D(pFrame);
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(1, color);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetTevColorIn(0, 0xF, 8, 2, 0xF);
    GXSetTevAlphaIn(0, 7, 7, 7, 1);
    GXSetTevOrder(0, 0, 0, 0xFF);
    GXSetBlendMode(1, 4, 5, 5);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZMode(0, 3, 0);
    GXSetZCompLoc(1);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, 1);
    GXInitTexObj(&sFrameObj_1565, pData, N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 4, 0, 0, 0);
    GXInitTexObjLOD(&sFrameObj_1565, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    GXLoadTexObj(&sFrameObj_1565, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXBegin(0x80, 0, 4);
    GXWGFifo.f32 = -1.0f;
    GXWGFifo.f32 = -1.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 319.0f;
    GXWGFifo.f32 = -1.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 319.0f;
    GXWGFifo.f32 = 239.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = -1.0f;
    GXWGFifo.f32 = 239.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}
#endif

#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrame.s")

void CopyAndConvertCFB(u16* srcP) {
    u16* dataEndP;
    s32 tile;
    s32 y;
    s32 x;
    u16 val;

    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB5A3, GX_TRUE);
    DCInvalidateRange(srcP, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
    GXCopyTex(srcP, GX_FALSE);

    sCopyFrameSyncReceived = 0;
    GXSetDrawSync(FRAME_SYNC_TOKEN);
    while (!sCopyFrameSyncReceived) {};

    dataEndP = srcP + N64_FRAME_WIDTH * N64_FRAME_HEIGHT;
    while (srcP < dataEndP) {
        xlHeapCopy(&line_1630, srcP, sizeof(line_1630));

        for (y = 0; y < 4; y++) {
            for (tile = 0; tile < N64_FRAME_WIDTH / 4; tile++) {
                for (x = 0; x < 4; x++, srcP++) {
                    val = line_1630[tile][y][x];
                    *srcP = (val << 1) | 1;
                }
            }
        }
    }
}

// matches but data doesn't
//! TODO: make sFrameObj and cAlpha a static variable in the function
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaGreyScaleConvert.s")
#else
void ZeldaGreyScaleConvert(Frame* pFrame) {
    Mtx matrix;
    void* dataP;
    s32 pad[9];
    GXColor color;

    dataP = DemoCurrentBuffer;
    color.r = 192;
    color.g = 161;
    color.b = 85;
    color.a = cAlpha;
    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(GC_FRAME_WIDTH, GC_FRAME_HEIGHT, 1, 0);
    GXCopyTex(dataP, 0);
    GXPixModeSync();
    frameDrawSetup2D(pFrame);

    if (gHackCreditsColor != 0) {
        GXSetNumTevStages(1);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTevColor(1, color);
        GXSetTevColorOp(0, 0, 0, 0, 0, 0);
        GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
        GXSetTevColorIn(0, 0xF, 8, 2, 0xF);
        GXSetTevAlphaIn(0, 7, 7, 7, 1);
        GXSetTevOrder(0, 0, 0, 0xFF);
        GXSetBlendMode(1, 4, 5, 5);
        if (cAlpha < 255) {
            cAlpha += 20;
        }
    } else {
        GXSetNumTevStages(1);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTevOp(0, 3);
        GXSetTevOrder(0, 0, 0, 0xFF);
        GXSetBlendMode(0, 4, 5, 5);
    }

    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZMode(0, 3, 0);
    GXSetZCompLoc(1);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, 1);
    GXInitTexObj(&sFrameObj_1647, dataP, GC_FRAME_WIDTH, GC_FRAME_HEIGHT, 1, 0, 0, 0);
    GXInitTexObjLOD(&sFrameObj_1647, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    GXLoadTexObj(&sFrameObj_1647, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXBegin(0x80, 0, 4);
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 320.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 320.0f;
    GXWGFifo.f32 = 240.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 240.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    pFrame->nFlag |= 0x40000 | 0x7F2D;
    pFrame->aDraw[0] = (FrameDrawFunc)frameDrawLine_Setup;
    pFrame->aDraw[1] = (FrameDrawFunc)frameDrawTriangle_Setup;
    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill_Setup;
    pFrame->aDraw[3] = (FrameDrawFunc)frameDrawRectTexture_Setup;
}
#endif

// matches but data doesn't
//! TODO: make sFrameObj a static variable in the function
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameShrink.s")
#else
void ZeldaDrawFrameShrink(Frame* pFrame, s32 posX, s32 posY, s32 size) {
    Mtx matrix;
    s32 pad;
    f32 nX0;
    f32 nX1;
    f32 nY0;
    f32 nY1;
    f32 scale;
    void* frameBuffer;
    GXColor color;

    frameBuffer = DemoCurrentBuffer;
    nX0 = posX;
    nY0 = posY;
    nX1 = 320.0f;
    nY1 = 240.0f;

    nX0 *= 2.0f;
    nY0 *= 2.0f;
    switch (size) {
        case 0x435:
            scale = 0.95f;
            break;
        case 0x471:
            scale = 0.90f;
            break;
        case 0x4B4:
            scale = 0.85f;
            break;
        case 0x500:
            scale = 0.80f;
            break;
    }
    nX1 *= scale;
    nY1 *= scale;
    GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
    GXSetTexCopyDst(0x280, 0x1E0, 4, 0);
    GXCopyTex(frameBuffer, 0);
    GXPixModeSync();
    frameDrawSetup2D(pFrame);
    GXSetZMode(0, 3, 0);
    GXSetZCompLoc(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    GXSetTevColor(1, color);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 2);
    GXSetTevAlphaIn(0, 7, 7, 7, 6);
    GXSetTevOrder(0, 0xFF, 0xFF, 0xFF);
    GXSetBlendMode(0, 4, 5, 5);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXBegin(0x80, 0, 4);
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 320.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 320.0f;
    GXWGFifo.f32 = 240.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 240.0f;
    GXWGFifo.f32 = 0.0f;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(1, color);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetTevColorIn(0, 0xF, 8, 2, 0xF);
    GXSetTevAlphaIn(0, 7, 7, 7, 1);
    GXSetTevOrder(0, 0, 0, 0xFF);
    GXSetBlendMode(1, 4, 5, 5);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZMode(0, 3, 0);
    GXSetZCompLoc(1);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, 1);
    GXInitTexObj(&frameObj_1663, frameBuffer, 0x280, 0x1E0, 4, 0, 0, 0);
    GXInitTexObjLOD(&frameObj_1663, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    GXLoadTexObj(&frameObj_1663, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXBegin(0x80, 0, 4);
    GXWGFifo.f32 = nX0;
    GXWGFifo.f32 = nY0;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = nX1;
    GXWGFifo.f32 = nY0;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = nX1;
    GXWGFifo.f32 = nY1;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = nX0;
    GXWGFifo.f32 = nY1;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    pFrame->nFlag |= 0x40000 | 0x7F2D;
    pFrame->aDraw[0] = (FrameDrawFunc)frameDrawLine_Setup;
    pFrame->aDraw[1] = (FrameDrawFunc)frameDrawTriangle_Setup;
    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill_Setup;
    pFrame->aDraw[3] = (FrameDrawFunc)frameDrawRectTexture_Setup;
}
#endif

// matches but data doesn't
//! TODO: make sFrameObj a static variable in the function
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameCamera.s")
#else
void ZeldaDrawFrameCamera(Frame* pFrame, void* buffer) {
    Mtx matrix;
    GXColor color;
    s32 pad[6];

    frameDrawSetup2D(pFrame);
    color.r = 255;
    color.g = 167;
    color.b = 176;
    color.a = 255;
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(1, color);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetTevColorIn(0, 0xF, 8, 2, 0xF);
    GXSetTevAlphaIn(0, 7, 7, 7, 1);
    GXSetTevOrder(0, 0, 0, 0xFF);
    GXSetBlendMode(1, 4, 5, 5);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZMode(0, 3, 0);
    GXSetZCompLoc(1);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, 1);
    GXInitTexObj(&frameObj_1673, buffer, ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT, 1, 0, 0, 0);
    GXInitTexObjLOD(&frameObj_1673, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    GXLoadTexObj(&frameObj_1673, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXBegin(0x80, 0, 4);
    GXWGFifo.f32 = 80.0f;
    GXWGFifo.f32 = 31.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.015625f;
    GXWGFifo.f32 = 240.0f;
    GXWGFifo.f32 = 31.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 0.015625f;
    GXWGFifo.f32 = 240.0f;
    GXWGFifo.f32 = 143.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 0.859375;
    GXWGFifo.f32 = 80.0f;
    GXWGFifo.f32 = 143.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.859375;
    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    pFrame->nFlag |= 0x40000 | 0x7F2D;
    pFrame->aDraw[0] = (FrameDrawFunc)frameDrawLine_Setup;
    pFrame->aDraw[1] = (FrameDrawFunc)frameDrawTriangle_Setup;
    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill_Setup;
    pFrame->aDraw[3] = (FrameDrawFunc)frameDrawRectTexture_Setup;
}
#endif

//! TODO: make sCommandCodes a static variable in the function
s32 frameHackTIMG_Zelda(Frame* pFrame, u64** pnGBI, u32* pnCommandLo, u32* pnCommandHi) {
    u32 i;

    if ((*pnCommandLo == 0x0F000000) && (*pnCommandHi == 0xFD500000)) {
        u32* tmp = (u32*)*pnGBI;
        for (i = 0; i < ARRAY_COUNT(sCommandCodes_1679); i++) {
            if (tmp[i] != sCommandCodes_1679[i]) {
                break;
            }
        }

        if (i == ARRAY_COUNT(sCommandCodes_1679)) {
            ZeldaGreyScaleConvert(pFrame);
            sSpecialZeldaHackON = 1;
        }
    }

    if ((sSpecialZeldaHackON != 0) && ((*pnCommandLo & 0xFF000000) != 0x0F000000)) {
        sSpecialZeldaHackON = 0;
    }

    if (sSrcBuffer == SEGMENT_ADDRESS(SYSTEM_RSP(gpSystem), *pnCommandLo)) {
        *pnCommandLo = sDestinationBuffer;
        *pnGBI += 8;
    }

    return 1;
}

s32 frameHackCIMG_Zelda2(Frame* pFrame, FrameBuffer* pBuffer, u64* pnGBI) {
    u32 i;
    u32* pGBI;
    s32 pad[4];

    if (pBuffer->nAddress == pFrame->aBuffer[0].nAddress) {
        pFrame->nHackCount += 1;
    }

    pFrame->nFrameCIMGCalls += 1;

    if ((s32)pFrame->nHackCount > 1) {
        pGBI = (u32*)&pnGBI[-5];
        for (i = 0; i < ARRAY_COUNT(sCommandCodes_1702); i++) {
            if (pGBI[i] != sCommandCodes_1702[i] && !(i == 9 && (pGBI[9] == 0x80383C80 || pGBI[9] == 0x80383AC0))) {
                break;
            }
        }

        if (i == ARRAY_COUNT(sCommandCodes_1702)) {
            if (!pFrame->bHackPause) {
                nCopyFrame = 1;
            }
        } else {
            pFrame->bPauseThisFrame = 0;
        }
    }

    if ((s32)nCopyFrame != 0) {
        pGBI = (u32*)&pnGBI[-5];
        for (i = 0; i < ARRAY_COUNT(sCommandCodes2); i++) {
            if (pGBI[i] != sCommandCodes2[i]) {
                break;
            }
        }

        if (i == ARRAY_COUNT(sCommandCodes2)) {
            if (!pFrame->bHackPause) {
                for (i = 0; i < N64_FRAME_WIDTH * N64_FRAME_HEIGHT; i++) {
                    pFrame->nCopyBuffer[i] = pFrame->nTempBuffer[i];
                }
            }
            pFrame->bHackPause = 1;
            pFrame->nHackCount = 0;
            pFrame->bPauseThisFrame = 1;
            nCopyFrame = 0;
        } else {
            pFrame->bPauseThisFrame = 0;
        }
    }

    if (pFrame->bHackPause) {
        if ((pFrame->nFrameCounter - nLastFrame) >= 2) {
            nLastFrame = pFrame->nFrameCounter;
            gNoSwapBuffer = 1;
        }
        pFrame->bHackPause = 0;
    } else {
        if (pFrame->bShrinking & 0xFFFF) {
            if (pFrame->bBlurOn) {
                pFrame->bShrinking |= 0x10;
            }
            if (!pFrame->bBlurOn && (pFrame->bShrinking & 0xF0) == 0) {
                CopyCFB(pFrame->nTempBuffer);
            }
        } else if (!pFrame->bBlurOn) {
            CopyCFB(pFrame->nTempBuffer);
        }
    }

    if (((pBuffer->nAddress == 0x42EEC0) || (pBuffer->nAddress == 0x3A9480) || (pBuffer->nAddress == 0x3A92C0)) &&
        pFrame->bBlurOn && !pFrame->bBlurredThisFrame) {
        ZeldaDrawFrameBlur(pFrame, pFrame->nTempBuffer);
        CopyCFB(pFrame->nTempBuffer);
        pFrame->bBlurredThisFrame = 1;
    }

    return 1;
}

s32 frameHackCIMG_Zelda(Frame* pFrame, FrameBuffer* pBuffer, u64* pnGBI, u32 nCommandLo) {
    u32 i;
    u32 low2;
    u32 high2;
    u16* srcP;

    for (i = 0; i < sNumAddr; i++) {
        if (nCommandLo == sConstantBufAddr[i]) {
            break;
        }
    }

    if (pBuffer->nAddress == pFrame->aBuffer[0].nAddress && pBuffer->nWidth == N64_FRAME_WIDTH) {
        low2 = pnGBI[1];
        high2 = pnGBI[1] >> 32;
        if (high2 == 0xFD10013F) {
            low2 = SYSTEM_RSP(gpSystem)->anBaseSegment[(low2 >> 24) & 0xF] + (low2 & 0xFFFFFF);
            if (!ramGetBuffer(SYSTEM_RAM(gpSystem), &srcP, low2, NULL)) {
                return 0;
            }
            sDestinationBuffer = low2;
            sSrcBuffer = pBuffer->nAddress;
            CopyAndConvertCFB(srcP);
            gnCountMapHack = -1;
            gNoSwapBuffer = 1;
        }
    }

    if (i >= sNumAddr) {
        if (sNumAddr < ARRAY_COUNT(sConstantBufAddr)) {
            sConstantBufAddr[sNumAddr++] = nCommandLo;
            sConstantBufAddr[sNumAddr++] =
                nCommandLo + ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT * sizeof(u16);
        } else if (pBuffer->nWidth == ZELDA_PAUSE_EQUIP_PLAYER_WIDTH) {
            gNoSwapBuffer = 1;
            if (pBuffer->nSize == 2) {
                u16* val = pBuffer->pData;
                u16* valEnd = val + ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT;
                s32 tile;
                s32 y;
                s32 x;

                GXSetTexCopySrc(0, 0, ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * 2, ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT * 2);
                GXSetTexCopyDst(ZELDA_PAUSE_EQUIP_PLAYER_WIDTH, ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT, GX_TF_RGB5A3, GX_TRUE);
                DCInvalidateRange(pBuffer->pData,
                                  ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT * sizeof(u16));
                GXCopyTex(pBuffer->pData, GX_FALSE);

                sCopyFrameSyncReceived = 0;
                GXSetDrawSync(FRAME_SYNC_TOKEN);
                while (!sCopyFrameSyncReceived) {}

                while (val < valEnd) {
                    xlHeapCopy(tempLine, val, sizeof(tempLine));

                    for (y = 0; y < 4; y++) {
                        for (tile = 0; tile < ZELDA_PAUSE_EQUIP_PLAYER_WIDTH / 4; tile++) {
                            for (x = 0; x < 4; x++, val++) {
                                *val = (tempLine[tile][y][x] << 1) | 1;
                            }
                        }
                    }
                }
            } else {
                u8* val = pBuffer->pData;
                u8* valEnd = val + ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT;

                // bug? val incremented twice per iteration
                for (; val < valEnd; val++) {
                    *(val++) = 0;
                }
            }
        }
    }

    PAD_STACK();
    PAD_STACK();
    return 1;
}

s32 frameHackCIMG_Zelda2_Shrink(Rdp* pRDP, Frame* pFrame, u64** ppnGBI) {
    u64* pnGBI;
    s32 count;
    s32 nAddress;
    u32 nCommandLo;
    u32 nCommandHi;
    Rsp* pRSP;
    s32 done;
    __anon_0x2ACA3 bg;

    pnGBI = *ppnGBI;
    for (count = 0; count < ARRAY_COUNT(GBIcode); count++) {
        nCommandHi = GBI_COMMAND_HI(pnGBI + count);
        if (GBIcode[count] != nCommandHi) {
            break;
        }
    }

    if (count == ARRAY_COUNT(GBIcode)) {
        pnGBI = pnGBI + count;
        pRSP = SYSTEM_RSP(pRDP->pHost);
        done = 0;

        while (TRUE) {
            nCommandHi = GBI_COMMAND_HI(pnGBI);
            if (nCommandHi == 0x09000000) {
                nCommandLo = GBI_COMMAND_LO(pnGBI);
                nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                rspFillObjBgScale(pRSP, nAddress, &bg);
                pFrame->bShrinking |= 1;
                pFrame->bShrinking |= 0x100;

                if ((pFrame->bShrinking & 0xFFFF0000) == 0) {
                    pFrame->bShrinking |= bg.b.tmemW << 16;
                }
                ZeldaDrawFrameShrink(pFrame, bg.b.frameX >> 2, bg.b.frameY >> 2, bg.b.tmemW);
                done = 1;
            }

            if (done && nCommandHi == 0xDF000000) {
                break;
            }
            pnGBI++;
        };
    } else {
        return 0;
    }

    *ppnGBI = ++pnGBI;
    return 1;
}

static inline void Zelda2Camera_UnkownInline(u16* nCameraBuffer) {
    GXSetTexCopySrc(ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT - 10, ZELDA2_CAMERA_WIDTH * 2, ZELDA2_CAMERA_HEIGHT * 2);
    GXSetTexCopyDst(ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT, GX_TF_I8, GX_TRUE);
    DCInvalidateRange(nCameraBuffer, ZELDA2_CAMERA_WIDTH * ZELDA2_CAMERA_HEIGHT * sizeof(u16));
    GXCopyTex(nCameraBuffer, GX_FALSE);
    GXPixModeSync();
}

s32 frameHackCIMG_Zelda2_Camera(Frame* pFrame, FrameBuffer* pBuffer, u32 nCommandHi, u32 nCommandLo) {
    if (pBuffer != NULL) {
        if (pBuffer->nAddress == 0x00784600) {
            pFrame->bSnapShot |= 0x10;
            return 1;
        }

        if ((pFrame->bSnapShot & 0xF00) != 0) {
            ZeldaDrawFrameCamera(pFrame, pFrame->nCameraBuffer);
            pFrame->bSnapShot &= ~0xF00;
            return 1;
        }
        return 0;
    }

    if ((nCommandHi == 0xF63EC25C) && (nCommandLo == 0x00118058)) {
        pFrame->bSnapShot |= 1;

        // possible bug? probably meant to be ``pFrame->bSnapShot & 0xF00``
        if ((pFrame->bSnapShot & 0xF0) != 0) {
            Zelda2Camera_UnkownInline(pFrame->nCameraBuffer);
            pFrame->bSnapShot &= ~0xF00;
        }

        return 1;
    }

    return 0;
}

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

s32 frameGetMode(Frame* pFrame, FrameModeType eType, u32* pnMode) {
    *pnMode = pFrame->aMode[eType];
    return 1;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetMatrix.s")
#else
s32 frameSetMatrix(Frame* pFrame, Mtx44 matrix, FrameMatrixType eType, s32 bLoad, s32 bPush, s32 nAddressN64) {
    s32 pad1;
    s32 bFlag;
    f32(*matrixTarget)[4];
    Mtx44 matrixResult;
    s32 pad2[9];

    OSGetTick();

    switch (eType) {
        case FMT_MODELVIEW:
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
        case FMT_PROJECTION:
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

s32 frameGetMatrix(Frame* pFrame, Mtx44 matrix, FrameMatrixType eType, s32 bPull) {
    switch (eType) {
        case FMT_MODELVIEW:
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
        case FMT_PROJECTION:
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

s32 frameSetBuffer(Frame* pFrame, FrameBufferType eType) {
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
s32 frameSetMatrixHint(Frame* pFrame, FrameMatrixProjection eProjection, s32 nAddressFloat, s32 nAddressFixed,
                       f32 rNear, f32 rFar, f32 rFOVY, f32 rAspect, f32 rScale) {
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
