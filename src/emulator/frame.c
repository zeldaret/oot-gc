#include "emulator/frame.h"
#include "dolphin.h"
#include "emulator/cpu.h"
#include "emulator/ram.h"
#include "emulator/rdp.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "math.h"

static bool frameDrawTriangle_C0T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C1T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C3T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C0T3(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C1T3(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawTriangle_C3T3(Frame* pFrame, Primitive* pPrimitive);

static bool frameDrawLine_C0T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C1T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C2T0(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C0T2(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C1T2(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawLine_C2T2(Frame* pFrame, Primitive* pPrimitive);

static bool frameDrawSetupSP(Frame* pFrame, s32* pnColors, bool* pbFlag, s32 nVertexCount);
static bool frameDrawSetupDP(Frame* pFrame, s32* pnColors, bool* pbFlag, s32 nVertexCount);
static bool frameDrawRectFill(Frame* pFrame, Rectangle* pRectangle);
static bool frameDrawTriangle_Setup(Frame* pFrame, Primitive* pPrimitive);
static bool frameDrawRectTexture_Setup(Frame* pFrame, Rectangle* pRectangle);
static inline void CopyCFB(u16* srcP);
static bool packTakeBlocks(s32* piPack, u32* anPack, s32 nPackCount, s32 nBlockCount);
static bool packFreeBlocks(s32* piPack, u32* anPack, s32 nPackCount);
static inline bool frameTransposeMatrix(Mtx44 matrixTarget, Mtx44 matrixSource);
static bool frameLoadTile(Frame* pFrame, FrameTexture** ppTexture, s32 iTileCode);
static bool frameUpdateCache(Frame* pFrame);
static inline bool frameGetMatrixHint(Frame* pFrame, u32 nAddress, s32* piHint);
static inline bool frameResetCache(Frame* pFrame);
static bool frameSetupCache(Frame* pFrame);
void PSMTX44MultVecNoW(Mtx44 m, Vec3f* src, Vec3f* dst);

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

static bool gbFrameValid;
static bool gbFrameBegin;
static bool snScissorChanged;
static u32 snScissorXOrig;
static u32 snScissorYOrig;
static u32 snScissorWidth;
static u32 snScissorHeight;

static volatile bool sCopyFrameSyncReceived;

static u8 sSpecialZeldaHackON;
static u32 sDestinationBuffer;
static u32 sSrcBuffer;
static u32 sConstantBufAddr[6] ATTRIBUTE_ALIGN(32);
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

char* gaszNameColor[] = {
    "CPREV", "APREV", "C0",  "A0",   "C1",    "A1",   "C2",       "A2",       "TEXC",     "TEXA",
    "RASC",  "RASA",  "ONE", "HALF", "KONST", "ZERO", D_800EA8D8, D_800EA8EC, D_800EA900, "GX_CC_KONST",
};

char* gaszNameAlpha[] = {
    "APREV", "A0", "A1", "A2", "TEXA", "RASA", "KONST", "ZERO", "KONST",
};

FrameDrawFunc gapfDrawTriangle[8] = {
    (FrameDrawFunc)frameDrawTriangle_C0T0,
    (FrameDrawFunc)frameDrawTriangle_C1T0,
    NULL,
    (FrameDrawFunc)frameDrawTriangle_C3T0,
    (FrameDrawFunc)frameDrawTriangle_C0T3,
    (FrameDrawFunc)frameDrawTriangle_C1T3,
    NULL,
    (FrameDrawFunc)frameDrawTriangle_C3T3,
};

FrameDrawFunc gapfDrawLine[6] = {
    (FrameDrawFunc)frameDrawLine_C0T0, (FrameDrawFunc)frameDrawLine_C1T0, (FrameDrawFunc)frameDrawLine_C2T0,
    (FrameDrawFunc)frameDrawLine_C0T2, (FrameDrawFunc)frameDrawLine_C1T2, (FrameDrawFunc)frameDrawLine_C2T2,
};

s32 nCopyFrame;
s32 nLastFrame;
bool bSkip;
s32 nCounter;
s32 gnCountMapHack;
bool gNoSwapBuffer;
static u16 sTempZBuf[N64_FRAME_WIDTH * N64_FRAME_HEIGHT / 16][4][4] ATTRIBUTE_ALIGN(32);

s32 sZBufShift[] = {
    0x0003F800, 0x00000000, 0x0003F000, 0x00000000, 0x0003E000, 0x00000001, 0x0003C000, 0x00000002,
    0x00038000, 0x00000003, 0x00030000, 0x00000004, 0x00020000, 0x00000005, 0x00000000, 0x00000006,
};

char* gaszNameColorType[] = {
    "FOG", "FILL", "BLEND", "PRIMITIVE", "ENVIRONMENT",
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

#ifndef NON_MATCHING
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

void* jtbl_800EB168[10] = {&lbl_8001D3FC, &lbl_8001D418, &lbl_8001D418, &lbl_8001D42C, &lbl_8001D42C,
                           &lbl_8001D42C, &lbl_8001D444, &lbl_8001D45C, &lbl_8001D3FC, &lbl_8001D418};
#else
void* jtbl_800EB168[10] = {0};
#endif

#ifndef NON_MATCHING
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

void* jtbl_800EB190[10] = {&lbl_80020074, &lbl_80020084, &lbl_800200C8, &lbl_800200D8, &lbl_800200E8,
                           &lbl_80020134, &lbl_80020144, &lbl_80020144, &lbl_80020144, &lbl_80020144};
#else
void* jtbl_800EB190[10] = {0};
#endif

char D_800EB1B8[] = "frameEnd: INTERNAL ERROR: Called when 'gbFrameBegin' is TRUE!\n";
char D_800EB1F8[] = "Waiting for valid?\n";

#ifndef NON_MATCHING
extern void* lbl_800297DC;
extern void* lbl_800297E8;
extern void* lbl_800297F4;
extern void* lbl_80029800;
extern void* lbl_8002980C;
extern void* lbl_80029818;
extern void* lbl_80029824;
extern void* lbl_80029830;

void* jtbl_800EB20C[8] = {
    &lbl_800297DC, &lbl_800297E8, &lbl_800297F4, &lbl_80029800,
    &lbl_8002980C, &lbl_80029818, &lbl_80029824, &lbl_80029830,
};
#else
void* jtbl_800EB20C[8] = {0};
#endif

#ifndef NON_MATCHING
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

void* jtbl_800EB22C[32] = {
    &lbl_8002986C, &lbl_80029878, &lbl_80029884, &lbl_80029890, &lbl_8002989C, &lbl_800298A8, &lbl_80029920,
    &lbl_800298B4, &lbl_800298C0, &lbl_800298CC, &lbl_800298D8, &lbl_800298E4, &lbl_800298F0, &lbl_800298FC,
    &lbl_80029908, &lbl_80029914, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938,
    &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_80029938,
    &lbl_80029938, &lbl_80029938, &lbl_80029938, &lbl_8002992C,
};
#else
void* jtbl_800EB22C[32] = {0};
#endif

char D_800EB2AC[] = "LoadTexture: Unknown FILTER mode (%d)\n";
char D_800EB2D4[] = "MakeTexture: 'aTexture' is exhausted!";

static char D_80134E58[] = "frame.c";

const f32 D_80135E00 = 0.0f;
const f32 D_80135E04 = 0.25f;
const f32 D_80135E08 = 2.0f;
const f64 D_80135E10 = 4503601774854144.0;
const f32 D_80135E18 = 0.0625f;
const f32 D_80135E1C = 0.0078125f;
const f32 D_80135E20 = 4096.0f;
const f32 D_80135E24 = 4194304.0f;
const f64 D_80135E28 = 4503599627370496.0;
const f32 D_80135E30 = 0.5f;
const f32 D_80135E34 = 3.0f;
const f32 D_80135E38 = 1.0f;
const f64 D_80135E40 = 0.5;
const f64 D_80135E48 = 3.0;
const f32 D_80135E50 = 0.2267303466796875f;
const f32 D_80135E54 = 0.3183135986328125f;
const f32 D_80135E58 = 0.00624f;
const f32 D_80135E5C = 0.006242f;
const f32 D_80135E60 = 640.0f;
const f32 D_80135E64 = 480.0f;
const f32 D_80135E68 = 320.0f;
const f32 D_80135E6C = 240.0f;
const f64 D_80135E70 = 262143.0;
const f64 D_80135E78 = 43.52;
const f32 D_80135E80 = 80.0f;
const f32 D_80135E84 = 31.0f;
const f32 D_80135E88 = 0.015625f;
const f32 D_80135E8C = 143.0f;
const f32 D_80135E90 = 0.859375f;
const f32 D_80135E94 = 0.95f;
const f32 D_80135E98 = 0.9f;
const f32 D_80135E9C = 0.85f;
const f32 D_80135EA0 = 0.8f;
const f32 D_80135EA4 = -1.0;
const f32 D_80135EA8 = 319.0f;
const f32 D_80135EAC = 239.0f;
const f32 D_80135EB0 = -1001.0;
const f32 D_80135EB4 = -53.0;
const f32 D_80135EB8 = -3080.0;
const f32 D_80135EBC = 6067.0f;
const f32 D_80135EC0 = -31.0;
const f32 D_80135EC4 = 1669.0f;
const f32 D_80135EC8 = 1000.0f;
const f32 D_80135ECC = 32000.0f;
const f32 D_80135ED0 = 30.0f;
const f32 D_80135ED4 = 1.3333334f;
const f32 D_80135ED8 = 0.1f;
const f32 D_80135EDC = 0.0015f;
const f32 D_80135EE0 = 65536.0f;
const f32 D_80135EE4 = 1001.0f;
const f32 D_80135EE8 = 500.0f;
const f32 D_80135EEC = 970.0f;
const f32 D_80135EF0 = 59.0f;
const f32 D_80135EF4 = 990.0f;
const f32 D_80135EF8 = 0.21f;
const f32 D_80135EFC = 0.35f;
const f32 D_80135F00 = 12800.0f;
const f32 D_80135F04 = 0.6f;
const f32 D_80135F08 = 0.7f;
const f32 D_80135F0C = 44.0f;
const f32 D_80135F10 = 0.13f;
const f32 D_80135F14 = 45.0f;
const f32 D_80135F18 = 15.0f;
const f32 D_80135F1C = 0.38f;
const f32 D_80135F20 = 900.0f;
const f32 D_80135F24 = 350.0f;
const f32 D_80135F28 = 10.0f;
const f32 D_80135F2C = 200.0f;
const f32 D_80135F30 = 128000.0f;
const f32 D_80135F34 = -25344.0;
const f32 D_80135F38 = 25600.0f;
const f32 D_80135F3C = 2200.0f;
const f32 D_80135F40 = 0.575f;
const f32 D_80135F44 = 0.75f;
const f32 D_80135F48 = -21077.0;
const f32 D_80135F4C = 21333.0f;
const f32 D_80135F50 = -90.0;
const f32 D_80135F54 = 258.0f;
const f32 D_80135F58 = 0.45f;
const f32 D_80135F5C = -667.0;
const f32 D_80135F60 = 688.0f;
const f32 D_80135F64 = 0.00390625f;
const f32 D_80135F68 = 860.0f;
const f32 D_80135F6C = 0.15f;
const f32 D_80135F70 = 140.0f;
const f32 D_80135F74 = 0.28f;
const f32 D_80135F78 = 0.72f;
const f32 D_80135F7C = 0.26f;
const f32 D_80135F80 = 8.44f;
const f64 D_80135F88 = 8.44;

static inline bool frameSetProjection(Frame* pFrame, s32 iHint) {
    MatrixHint* pHint = &pFrame->aMatrixHint[iHint];

    pFrame->nMode |= 0x24000000;
    pFrame->nMode &= ~0x18000000;

    if (pHint->eProjection == FMP_PERSPECTIVE) {
        C_MTXPerspective(pFrame->matrixProjection, pHint->rFieldOfViewY, pHint->rAspect, pHint->rClipNear,
                         pHint->rClipFar);
    } else if (pHint->eProjection == FMP_ORTHOGRAPHIC) {
        C_MTXOrtho(pFrame->matrixProjection, 0.0f, pFrame->anSizeY[FS_SOURCE] - 1.0f, 0.0f,
                   pFrame->anSizeX[FS_SOURCE] - 1.0f, pHint->rClipNear, pHint->rClipFar);
    } else {
        return false;
    }

    pFrame->eTypeProjection = pHint->eProjection;
    return true;
}

#ifndef NON_MATCHING
static bool frameDrawSetupFog_Zelda1(Frame* pFrame);
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupFog_Zelda1.s")
#else
static bool frameDrawSetupFog_Zelda1(Frame* pFrame) {
    GXFogType nFogType;
    f32 rNear;
    f32 rFar;
    u32 nMode;
    u32 iHint;
    f32 rFogNear;
    f32 rFogFar;
    f32 rFogMin;
    f32 rFogMax;
    f32 rMultiplier;
    f32 rOffset;
    f32 rMinimum;
    f32 rMaximum;
    s32 pad[4];

    nMode = pFrame->aMode[0];
    iHint = pFrame->iHintProjection;
    rMultiplier = (s16)(nMode >> 16);
    rOffset = rMinimum = (s16)(nMode & 0xFFFF);

    if (iHint != -1) {
        rFar = pFrame->aMatrixHint[pFrame->iHintProjection].rClipFar;
        rNear = 0.1f * pFrame->aMatrixHint[pFrame->iHintProjection].rClipNear;
    } else {
        rFar = 32000.0f;
        rNear = 1.0f;
    }

    if (rMultiplier == 0.0f) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
    } else {
        if (rOffset == rMultiplier) {
            nFogType = GX_FOG_LIN;
            rFogNear = 500.0f;
            rFogFar = 1000.0f;
            rFogMin = rFogNear * (1.0f - (rOffset / rMultiplier));
            rFogMax = (128000.0f / rMultiplier) + rFogMin;
        } else if (rOffset == -25344.0f && rMultiplier == 25600.0f && rFar == 2200.0f) {
            f32 dplane = rFar - rNear;

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = 0.575f * dplane + rNear;
            rFogMax = 0.75f * dplane + rNear;
        } else if (rOffset == -21077.0f && rMultiplier == 21333.0f && rFar == 12800.0f) {
            f32 dplane = rFar - rNear;

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = 0.1f * dplane + rNear;
            rFogMax = dplane + rNear;
        } else if (gpSystem->eTypeROM == SRT_ZELDA2 && rOffset == -90.0f && rMultiplier == 258.0f && rFar == 12800.0f) {
            f32 dplane = rFar - rNear;

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = 0.45f * dplane + rNear;
            rFogMax = dplane + rNear;
        } else if (gpSystem->eTypeROM == SRT_ZELDA2 && rOffset == -667.0f && rMultiplier == 688.0f &&
                   rFar == 12800.0f) {
            f32 dplane = rFar - rNear;

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = 0.45f * dplane + rNear;
            rFogMax = dplane + rNear;
        } else {
            f32 dplane = rFar - rNear;
            f32 rFarScale;
            f32 rNearScale;

            rMultiplier = 128000.0f / rMultiplier;
            rMultiplier = rOffset * rMultiplier;
            rFogFar = 1.0f / 256.0f;
            rFogNear = 500.0f - rMultiplier * rFogFar;

            if (rFogNear <= 860.0f) {
                rMinimum = 0.0f;
                rMaximum = 0.15f;
            } else {
                rMinimum = (rFogNear - 860.0f) / 140.0f;
                rMaximum = 0.72f * rMinimum * rMinimum * rMinimum * rMinimum + 0.28f;
                rMinimum = 0.26f * rMinimum * rMinimum * rMinimum * rMinimum;
            }

            rFarScale = rFar / 12800.0f;
            rFarScale = 1.0f - rFarScale;
            rFarScale = rFarScale * rFarScale;
            rFarScale = rFarScale * rFarScale;
            rFarScale = rFarScale * rFarScale;

            rNearScale = rNear * rNear;
            rNearScale *= 0.1f * rFarScale;

            rFarScale *= 8.44f;
            rNearScale *= 8.44; // bug? should be 8.44f

            rFarScale += 1.0f;
            rNearScale += 1.0f;

            rMaximum *= rFarScale;
            if (rMaximum > 1.0f) {
                rMaximum = 1.0f;
            }

            rMinimum *= rNearScale;
            if (rMinimum > 1.0f) {
                rMinimum = 1.0f;
            }

            if (rMinimum > rMaximum) {
                rMinimum = rMaximum;
            }

            nFogType = GX_FOG_EXP;
            rFogNear = rNear;
            rFogFar = rFar;
            rFogMin = rMinimum * dplane + rNear;
            rFogMax = rMaximum * dplane + rNear;
        }

        nMode = pFrame->aMode[4];
        if (((nMode >> 26) & 3) == 1 || (nMode >> 30) == 3 || ((nMode >> 22) & 3) == 3) {
            GXSetFog(nFogType, rFogMin, rFogMax, rFogNear, rFogFar, pFrame->aColor[0]);
        } else {
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
        }
    }

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
static bool frameDrawSetupFog_Default(Frame* pFrame);
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupFog_Default.s")
#else
static s32 frameDrawSetupFog_Default(Frame* pFrame) {
    s32 iHint;
    f32 rNear;
    f32 rFar;
    f32 rFOVY;
    Mtx44 matrixProjection;
    GXFogAdjTable fogTable;
    f32 rMax;
    f32 rMin;
    f32 rIntpV;
    f32 rMinimum;
    f32 rMultiplier;
    f32 rOffset;
    s32 pad;

    rMultiplier = (s16)(pFrame->aMode[0] >> 16);
    rOffset = (s16)(pFrame->aMode[0] & 0xFFFF);
    iHint = pFrame->iHintProjection;

    if (iHint != -1) {
        rFar = pFrame->aMatrixHint[pFrame->iHintProjection].rClipFar;
        rNear = pFrame->aMatrixHint[pFrame->iHintProjection].rClipNear;
        rFOVY = pFrame->aMatrixHint[pFrame->iHintProjection].rFieldOfViewY;
    } else {
        rFar = 32000.0f;
        rNear = 1.0f;
        rFOVY = 30.0f;
    }
    if (rMultiplier == 0.0f) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[0]);
    } else {
        rMinimum = 500.0f * (1.0f - rOffset / rMultiplier);
        C_MTXPerspective(matrixProjection, 30.0f, 4.0f / 3.0f, 0.1f * rNear, rFar);
        GXInitFogAdjTable(&fogTable, GC_FRAME_WIDTH, matrixProjection);
        GXSetFogRangeAdj(GX_TRUE, pFrame->viewport.rX + pFrame->viewport.rSizeX / 2.0f, &fogTable);
        if (rMinimum > 970.0f) {
            if (rFOVY > 59.0f || rMinimum > 990.0f) {
                rMin = 0.21f * (rFar - 0.35f * rNear);
                rMin = MAX(rMin, 0.35f * rNear);
                if (rFOVY < 59.0f && rFar >= 12800.0f) {
                    rMax = 0.6f * rFar;
                } else {
                    rMax = 0.7f * rFar;
                }
            } else if (rFOVY > 44.0f) {
                rMin = 0.13f * (rFar - 0.35f * rNear);
                rMin = MAX(rMin, 0.35f * rNear);
                rIntpV = MAX(rFOVY - 45.0f, 0.0f) / 15.0f;
                rMax = rFar * (0.6f * (1.0f - rIntpV) + 0.7f * rIntpV);
            } else {
                rMin = 0.1f * (rFar - 0.35f * rNear);
                rMin = MAX(rMin, 0.35f * rNear);
                rMax = 0.37f * rFar;
            }
            GXSetFog(GX_FOG_LIN, rMin, rMax, 0.35f * rNear, rFar, pFrame->aColor[0]);
        } else if (rMinimum > 900.0f) {
            GXSetFog(GX_FOG_LIN, 350.0f, 500.0f, 10.0f, 500.0f, pFrame->aColor[0]);
        } else {
            GXSetFog(GX_FOG_LIN, 10.0f, 200.0f, 10.0f, 200.0f, pFrame->aColor[0]);
        }
    }

    return true;
}
#endif

static void frameDrawSyncCallback(u16 nToken) {
    if (nToken == FRAME_SYNC_TOKEN) {
        sCopyFrameSyncReceived = true;
    }
}

static void frameDrawDone(void) {
    if (gbFrameValid) {
        gbFrameValid = false;
        if (!gNoSwapBuffer) {
            VISetNextFrameBuffer(DemoCurrentBuffer);
            VIFlush();
            if (DemoCurrentBuffer == DemoFrameBuffer1) {
                DemoCurrentBuffer = DemoFrameBuffer2;
            } else {
                DemoCurrentBuffer = DemoFrameBuffer1;
            }
        } else {
            VIFlush();
            gNoSwapBuffer = false;
        }
    }
}

static bool frameMakeTLUT(Frame* pFrame, FrameTexture* pTexture, s32 nCount, s32 nOffsetTMEM, bool bReload) {
    s32 iColor;
    u16* anColor;
    u16 nData16;

    if (bReload) {
        if (pTexture->iPackColor == -1) {
            return true;
        }
        anColor = (u16*)((u8*)pFrame->aColorData + ((pTexture->iPackColor & 0xFFFF) << 5));
    } else {
        if (!packTakeBlocks(&pTexture->iPackColor, pFrame->anPackColor, ARRAY_COUNT(pFrame->anPackColor),
                            (nCount * sizeof(u16)) >> 5)) {
            return false;
        }
        anColor = (u16*)((u8*)pFrame->aColorData + ((pTexture->iPackColor & 0xFFFF) << 5));
    }

    for (iColor = 0; iColor < nCount; iColor++) {
        nData16 = pFrame->TMEM.data.u64[nOffsetTMEM + 0x100 + iColor] & 0xFFFF;
        if (nData16 & 1) {
            anColor[iColor] =
                (((nData16 >> 11) & 0x1F) << 10) | (((nData16 >> 6) & 0x1F) << 5) | ((nData16 >> 1) & 0x1F) | 0x8000;
        } else {
            anColor[iColor] = (((nData16 >> 12) & 0xF) << 8) | (((nData16 >> 7) & 0xF) << 4) | ((nData16 >> 2) & 0xF);
        }
    }

    DCStoreRange(anColor, nCount * sizeof(u16));

    return true;
}

static inline bool frameFreeTLUT(Frame* pFrame, FrameTexture* pTexture) {
    if (!packFreeBlocks(&pTexture->iPackColor, pFrame->anPackColor, ARRAY_COUNT(pFrame->anPackColor))) {
        return false;
    }
    return true;
}

static bool frameMakePixels(Frame* pFrame, FrameTexture* pTexture, Tile* pTile, bool bReload);
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameMakePixels.s")

static inline bool frameFreePixels(Frame* pFrame, FrameTexture* pTexture) {
    if (!frameFreeTLUT(pFrame, pTexture)) {
        return false;
    }
    if (!packFreeBlocks(&pTexture->iPackPixel, pFrame->anPackPixel, ARRAY_COUNT(pFrame->anPackPixel))) {
        return false;
    }
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
static bool frameLoadTexture(Frame* pFrame, FrameTexture* pTexture, s32 iTextureCode, Tile* pTile);
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameLoadTexture.s")
#else
static bool frameLoadTexture(Frame* pFrame, FrameTexture* pTexture, s32 iTextureCode, Tile* pTile) {
    void* pData;
    s32 iName;
    s32 nFilter;
    GXTexWrapMode eWrapS;
    GXTexWrapMode eWrapT;
    s32 pad;

    pTexture->nFrameLast = pFrame->nCountFrames;
    iName = iTextureCode >> 4;
    pTile->nModeS = pTile->nModeS;

    if (((pTile->nModeS & 2) || pTile->nMaskS == 0) && !(pTexture->nMode & 1)) {
        eWrapS = GX_CLAMP;
    } else if (pTile->nModeS & 1) {
        eWrapS = GX_MIRROR;
    } else {
        eWrapS = GX_REPEAT;
    }
    pTile->nModeT = pTile->nModeT;
    if (((pTile->nModeT & 2) || pTile->nMaskT == 0) && !(pTexture->nMode & 2)) {
        eWrapT = GX_CLAMP;
    } else if (pTile->nModeT & 1) {
        eWrapT = GX_MIRROR;
    } else {
        eWrapT = GX_REPEAT;
    }
    if (pTexture->eWrapS != eWrapS || pTexture->eWrapT != eWrapT) {
        pTexture->eWrapS = eWrapS;
        pTexture->eWrapT = eWrapT;

        if ((GXCITexFmt)pTexture->eFormat == GX_TF_C4 || (GXCITexFmt)pTexture->eFormat == GX_TF_C8) {
            if (pTexture->iPackColor == -1) {
                pData = NULL;
            } else {
                pData = (u8*)pFrame->aColorData + ((pTexture->iPackColor & 0xFFFF) << 5);
            }
            GXInitTlutObj(&pTexture->objectTLUT, pData, GX_TL_RGB5A3,
                          (GXCITexFmt)pTexture->eFormat == GX_TF_C4 ? 16 : 256);

            if (pTexture->iPackPixel == -1) {
                pData = NULL;
            } else {
                pData = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }
            GXInitTexObjCI(&pTexture->objectTexture, pData, pTexture->nSizeX, pTexture->nSizeY,
                           (GXCITexFmt)pTexture->eFormat, eWrapS, eWrapT, GX_FALSE, 0);
        } else {
            if (pTexture->iPackPixel == -1) {
                pData = NULL;
            } else {
                pData = (u8*)pFrame->aPixelData + ((pTexture->iPackPixel & 0xFFFF) << 11);
            }
            GXInitTexObj(&pTexture->objectTexture, pData, pTexture->nSizeX, pTexture->nSizeY, pTexture->eFormat, eWrapS,
                         eWrapT, 0);
        }
    }

    nFilter = pFrame->aMode[FMT_OTHER1] & 0x3000;
    if ((pTexture->nMode & 0x3000) != nFilter) {
        pTexture->nMode &= ~0x3000;
        pTexture->nMode |= nFilter;
        switch (nFilter) {
            case 0x0000:
                GXInitTexObjLOD(&pTexture->objectTexture, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                GX_ANISO_1);
                break;
            case 0x2000:
            case 0x3000:
                GXInitTexObjLOD(&pTexture->objectTexture, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                GX_ANISO_1);
                break;
            default:
                OSReport("LoadTexture: Unknown FILTER mode (%d)\n", nFilter);
                break;
        }
    }

    if ((GXCITexFmt)pTexture->eFormat == GX_TF_C4 || (GXCITexFmt)pTexture->eFormat == GX_TF_C8) {
        GXLoadTlut(&pTexture->objectTLUT, ganNameColor[iName]);
    }

    GXLoadTexObj(&pTexture->objectTexture, ganNamePixel[iName]);

    return true;
}
#endif

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetup2D.s")
#else
bool frameDrawSetup2D(Frame* pFrame) {
    Mtx44 matrix44;

    if (!(*(volatile u32*)&pFrame->nMode & 0x40000000)) {
        pFrame->nMode |= 0x40000000;

        GXSetViewport(0.0f, 0.0f, pFrame->anSizeX[1], pFrame->anSizeY[1], 0.0f, 1.0f);
        pFrame->nFlag |= 0x10000;

        if (snScissorChanged) {
            GXSetScissor(snScissorXOrig, snScissorYOrig, snScissorWidth, snScissorHeight);
            snScissorChanged = false;
        }

        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[FCT_FOG]);
        pFrame->nFlag |= 0x20;

        C_MTXOrtho(matrix44, 0.0f, pFrame->anSizeY[0] - 1.0f, 0.0f, pFrame->anSizeX[0] - 1.0f, 0.0f, 1001.0f);
        GXSetProjection(matrix44, GX_ORTHOGRAPHIC);
        pFrame->nFlag |= 0x40000;

        GXSetCullMode(GX_CULL_NONE);
        pFrame->nFlag |= 8;

        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);
        pFrame->nFlag |= 4;
    }

    return true;
}
#endif

static inline void frameSetZMode(Frame* pFrame) {
    u32 mode = pFrame->aMode[FMT_OTHER0];

    if (pFrame->aMode[FMT_GEOMETRY] & 1) {
        if (mode & 0x10) {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            } else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            }
        } else {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
            } else {
                GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
            }
        }
    } else if (pFrame->bModifyZBuffer) {
        if (mode & 0x10) {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            } else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            }
        } else {
            if (mode & 0x20) {
                GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
            } else {
                GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
            }
        }
    } else {
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    }
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupSP.s")
#else
static bool frameDrawSetupSP(Frame* pFrame, s32* pnColors, bool* pbFlag, s32 nVertexCount) {
    f32 rValue23;
    bool bTextureGen;
    f32 rNear;
    f32 rFar;
    f32 rScaleS;
    f32 rScaleT;
    f32 rSlideS;
    f32 rSlideT;
    FrameTexture* pTexture[8];
    s32 nColors;
    s32 bFlag;
    s32 iTile;
    s32 iHint;
    Mtx matrix;
    Mtx matrixA;
    Mtx matrixB;
    Mtx44 matrix44;
    Mtx44 matrixProjection;
    GXProjectionType eTypeProjection;
    f32 scale;
    s32 nCount;
    s32 iIndex;
    s32 pad;

    nColors = 0;
    bTextureGen = (pFrame->aMode[FMT_GEOMETRY] & 0xA0) == 0xA0;

    if (pFrame->nFlag & 0x10000) {
        snScissorChanged = false;
        pFrame->nFlag &= ~0x10000;
        GXSetViewport(pFrame->viewport.rX, pFrame->viewport.rY, pFrame->viewport.rSizeX, pFrame->viewport.rSizeY, 0.0f,
                      1.0f);

        if (pFrame->viewport.rSizeX < GC_FRAME_WIDTH) {
            // TODO: regalloc hacks?
            u32* left = &snScissorXOrig;
            u32* top = &snScissorYOrig;
            GXGetScissor(left, top, &snScissorWidth, &snScissorHeight);

            if (snScissorWidth > pFrame->viewport.rSizeX) {
                GXSetScissor(pFrame->viewport.rX, pFrame->viewport.rY, pFrame->viewport.rSizeX,
                             pFrame->viewport.rSizeY);
                snScissorChanged = true;
            }
        }

        pFrame->nMode &= ~0x40000000;
    }

    if (pFrame->nFlag & 4) {
        pFrame->nFlag &= ~4;
        frameSetZMode(pFrame);
        pFrame->nMode &= ~0x40000000;
    }

    if (pFrame->nFlag & 8) {
        pFrame->nFlag &= ~8;
        switch (pFrame->aMode[FMT_GEOMETRY] & 0xC) {
            case 0x8:
                GXSetCullMode(GX_CULL_FRONT);
                break;
            case 0x4:
                GXSetCullMode(GX_CULL_BACK);
                break;
            case 0xC:
                GXSetCullMode(GX_CULL_ALL);
                break;
            default:
                GXSetCullMode(GX_CULL_NONE);
                break;
        }
        pFrame->nMode &= ~0x40000000;
    }

    if ((pFrame->nFlag & 0x40000) && (pFrame->nMode & 0x04000000)) {
        pFrame->nFlag &= ~0x40000;
        if (pFrame->nMode & 0x20000000) {
            eTypeProjection = pFrame->eTypeProjection == FMP_PERSPECTIVE ? GX_PERSPECTIVE : GX_ORTHOGRAPHIC;
            if ((pFrame->aMode[FMT_OTHER0] & 0xC00) == 0xC00 && eTypeProjection == GX_PERSPECTIVE) {
                GXSetProjection(pFrame->matrixProjection, eTypeProjection);
            } else {
                GXSetProjection(pFrame->matrixProjection, eTypeProjection);
            }
        } else {
            frameTransposeMatrix(matrix44, pFrame->matrixProjection);

            iHint = pFrame->iHintProjection;
            if (iHint != -1) {
                if (pFrame->aMatrixHint[iHint].eProjection == FMP_PERSPECTIVE) {
                    eTypeProjection = GX_PERSPECTIVE;
                } else {
                    eTypeProjection = GX_ORTHOGRAPHIC;
                }
                rNear = pFrame->aMatrixHint[iHint].rClipNear;
                rFar = pFrame->aMatrixHint[iHint].rClipFar;
            } else if (pFrame->matrixProjection[3][3] == 1.0f) {
                rNear = 0.0f;
                rFar = 32000.0f;
                eTypeProjection = GX_ORTHOGRAPHIC;
            } else {
                rNear = 1.0f;
                rFar = 32000.0f;
                eTypeProjection = GX_PERSPECTIVE;
            }
            if (eTypeProjection == GX_PERSPECTIVE) {
                C_MTXPerspective(matrixProjection, 30.0f, 4.0f / 3.0f, 0.1f * rNear, rFar);
            } else {
                rNear = -rFar;
                C_MTXOrtho(matrixProjection, (f32)pFrame->anSizeY[0] / 2.0, -(f32)pFrame->anSizeY[0] / 2.0,
                           -(f32)pFrame->anSizeX[0] / 2.0, (f32)pFrame->anSizeX[0] / 2.0, rNear, rFar);
            }

            rValue23 = matrixProjection[2][3];
            if ((pFrame->aMode[FMT_OTHER0] & 0xC00) == 0xC00 && eTypeProjection == GX_PERSPECTIVE) {
                rValue23 = -((0.0015f * rNear) - rValue23);
            }
            matrix44[2][2] = matrixProjection[2][2];
            matrix44[2][3] = rValue23;

            GXSetProjection(matrix44, eTypeProjection);
        }

        pFrame->nMode &= ~0x40000000;
    }

    if (pFrame->aMode[FMT_TEXTURE2] & 1) {
        bFlag = true;
        scale = !(pFrame->aMode[FMT_OTHER1] & 0x80000) ? 0.5f : 1.0f;
        iTile = (pFrame->aMode[FMT_TEXTURE2] >> 8) & 7;
        nCount = iTile +
                 (((s32)((pFrame->aMode[FMT_TEXTURE2] >> 8) & 7) < 7 && pFrame->aTile[iTile + 1].nSizeX != 0) ? 1 : 0);

        if (pFrame->nFlag & 1) {
            for (iIndex = 0; iTile <= nCount; iTile++, iIndex++) {
                if (frameLoadTile(pFrame, &pTexture[iTile], iTile | (iIndex << 4))) {
                    if (bTextureGen) {
                        rSlideS = (pFrame->aTile[iTile].nX0 / 4.0f) / pTexture[iTile]->nSizeX;
                        rSlideT = (pFrame->aTile[iTile].nY0 / 4.0f) / pTexture[iTile]->nSizeY;

                        rScaleS = 65536.0f * ((pFrame->aMode[FMT_TEXTURE1] >> 16) / 65536.0f);
                        rScaleS /= (pTexture[iTile]->nSizeX << 6);
                        rScaleT = 65536.0f * ((pFrame->aMode[FMT_TEXTURE1] & 0xFFFF) / 65536.0f);
                        rScaleT /= (pTexture[iTile]->nSizeY << 6);
                    } else {
                        rSlideS = ((pFrame->aTile[iTile].nX0 / 4.0f) - 0.5f) / pTexture[iTile]->nSizeX;
                        rSlideT = ((pFrame->aTile[iTile].nY0 / 4.0f) - 0.5f) / pTexture[iTile]->nSizeY;

                        rScaleS = (pFrame->aMode[FMT_TEXTURE1] >> 16) / 65536.0f;
                        rScaleS /= pTexture[iTile]->nSizeX;
                        rScaleT = (pFrame->aMode[FMT_TEXTURE1] & 0xFFFF) / 65536.0f;
                        rScaleT /= pTexture[iTile]->nSizeY;
                    }

                    if (pFrame->aTile[iTile].nShiftS < 11) {
                        rScaleS /= (1 << pFrame->aTile[iTile].nShiftS);
                    } else {
                        rScaleS *= (1 << (16 - pFrame->aTile[iTile].nShiftS));
                    }

                    if (pFrame->aTile[iTile].nShiftT < 11) {
                        rScaleT /= (1 << pFrame->aTile[iTile].nShiftT);
                    } else {
                        rScaleT *= (1 << (16 - pFrame->aTile[iTile].nShiftT));
                    }

                    PSMTXTrans(matrixA, -rSlideS, -rSlideT, 0.0f);
                    PSMTXScale(matrixB, rScaleS * scale, rScaleT * scale, 0.0f);
                    PSMTXConcat(matrixA, matrixB, matrix);
                    GXLoadTexMtxImm(matrix, ganNameTexMtx[iIndex], GX_MTX2x4);
                }
            }
        }
    } else {
        bFlag = false;
    }

    if (pFrame->aMode[FMT_GEOMETRY] & 2) {
        if (pFrame->aMode[FMT_GEOMETRY] & 0x200) {
            nColors = nVertexCount;
        } else {
            nColors = 1;
        }
    }

    *pbFlag = bFlag;
    *pnColors = nColors;
    return true;
}
#endif

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameGetCombineColor.s")
#else
static bool frameGetCombineColor(Frame* pFrame, GXTevColorArg* pnColorTEV, s32 nColorN64) {
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
            return false;
    }

    return true;
}
#endif

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameGetCombineAlpha.s")
#else
static bool frameGetCombineAlpha(Frame* pFrame, GXTevAlphaArg* pnAlphaTEV, s32 nAlphaN64) {
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
            return false;
    }

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawSetupDP.s")
#else
static bool frameDrawSetupDP(Frame* pFrame, s32* pnColors, bool* pbFlag, s32 vertexCount) {
    u32 nMode;
    s32 numCycles;
    u32 mode;
    u32 cycle;
    s32 pad[2];

    if (pFrame->nFlag & 0x100) {
        pFrame->nFlag &= ~0x100;
        if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x300000) {
            *pnColors = 0;
            *pbFlag = false;
            GXSetNumTevStages(1);
            GXSetNumChans(1);
            GXSetNumTexGens(0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C2);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A2);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            GXSetTevColor(GX_TEVREG2, pFrame->aColor[FCT_FILL]);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        } else if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x200000) {
            GXSetNumTevStages(1);
            GXSetNumChans(0);
            GXSetNumTexGens(1);
            GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        } else {
            numCycles = ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x100000) + 1;
            if (!SetTevStageTable(pFrame, numCycles)) {
                GXSetNumTevStages(numCycles * 5);
                SetNumTexGensChans(pFrame, numCycles);
                SetTevStages(pFrame, 0, numCycles);
                if (numCycles == 2) {
                    SetTevStages(pFrame, 1, numCycles);
                }
            }
        }
    }

    if (pFrame->nFlag & 0x220) {
        pFrame->nFlag &= ~0x20;
        if ((pFrame->aMode[FMT_GEOMETRY] & 0x10)) {
            switch (gpSystem->eTypeROM) {
                case SRT_ZELDA1:
                case SRT_ZELDA2:
                    if (!frameDrawSetupFog_Zelda1(pFrame)) {
                        return false;
                    }
                    break;
                default:
                    if (!frameDrawSetupFog_Default(pFrame)) {
                        return false;
                    }
                    break;
            }
        } else {
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 1000.0f, pFrame->aColor[FCT_FOG]);
        }
        pFrame->nMode &= ~0x40000000;
    }

    if (pFrame->nFlag & 0x200) {
        pFrame->nFlag &= ~0x200;
        mode = pFrame->aMode[FMT_OTHER0];

        if ((mode & 0xFFFF0000) == 0xAF500000) {
            GXSetColorUpdate(GX_FALSE);
        } else {
            GXSetColorUpdate(GX_TRUE);
        }

        cycle = pFrame->aMode[FMT_OTHER1] & 0x300000;
        if (((mode & 0x33330000) == 0x100000 && cycle == 0x100000) || (mode & 0xCCCC0000) == 0x400000) {
            GXSetZCompLoc(GX_FALSE);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            if ((mode & 3) == 1) {
                GXSetAlphaCompare(GX_GREATER, pFrame->aColor[FCT_BLEND].a, GX_AOP_AND, GX_GREATER,
                                  pFrame->aColor[FCT_BLEND].a);
            } else if (mode & 0x1000) {
                GXSetAlphaCompare(GX_GREATER, 16, GX_AOP_AND, GX_GREATER, 16);
            } else {
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
            }
        } else if ((mode & 0x1000) || (mode & 1)) {
            GXSetZCompLoc(GX_FALSE);
            GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            if ((mode & 3) == 1) {
                GXSetAlphaCompare(GX_GREATER, pFrame->aColor[FCT_BLEND].a, GX_AOP_AND, GX_GREATER,
                                  pFrame->aColor[FCT_BLEND].a);
            } else {
                GXSetAlphaCompare(GX_GREATER, 16, GX_AOP_AND, GX_GREATER, 16);
            }
        } else {
            if ((mode & 3) == 1) {
                GXSetZCompLoc(GX_FALSE);
                GXSetAlphaCompare(GX_GREATER, pFrame->aColor[FCT_BLEND].a, GX_AOP_AND, GX_GREATER,
                                  pFrame->aColor[FCT_BLEND].a);
            } else {
                GXSetZCompLoc(GX_TRUE);
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
            }
            GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        }

        frameSetZMode(pFrame);
    }

    return true;
}
#endif

static bool frameDrawTriangle_C0T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    if (pFrame->nModeVtx != 0x11) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        pFrame->nModeVtx = 0x11;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
    }
    GXEnd();

    return true;
}

static bool frameDrawTriangle_C1T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;
    Vertex* pVertexColor;

    if (pFrame->nModeVtx != 0x13) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0x13;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertexColor = &pFrame->aVertex[anData[iData + 0]];
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
    }
    GXEnd();

    return true;
}

static bool frameDrawTriangle_C3T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    if (pFrame->nModeVtx != 0x13) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0x13;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
    }
    GXEnd();

    return true;
}

static bool frameDrawTriangle_C0T3(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    if (pFrame->nModeVtx != 0x15) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x15;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}

static bool frameDrawTriangle_C1T3(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;
    Vertex* pVertexColor;

    if (pFrame->nModeVtx != 0x17) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x17;
    }

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, pPrimitive->nCount);
    anData = pPrimitive->anData;
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertexColor = &pFrame->aVertex[anData[iData + 0]];
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 2]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}

static inline void frameWriteVertex(Vertex* pVertex) {
    GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
    GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
    GXTexCoord2f32(pVertex->rS, pVertex->rT);
}

// Matches but data doesn't
#ifndef NON_MATCHING
static bool frameCheckTriangleDivide(Frame* pFrame, Primitive* pPrimitive);
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameCheckTriangleDivide.s")
#else
static bool frameCheckTriangleDivide(Frame* pFrame, Primitive* pPrimitive) {
    s32 pad1[3];
    Vertex* v0;
    Vertex* v1;
    Vertex* v2;
    s32 iData;
    u8* anData;
    Vertex aNewVertArray[8];
    f32 fInterp;
    f32 fTempColor1;
    f32 fTempColor2;
    u32 nNewVertCount;
    u32 bInFront;
    u32 bBehind;
    u32 aSide[3];

    iData = 0;
    anData = pPrimitive->anData;
    while (iData < pPrimitive->nCount) {
        aSide[0] = 3;
        aSide[1] = 3;
        aSide[2] = 3;
        bInFront = false;
        bBehind = false;

        v0 = &pFrame->aVertex[anData[iData + 0]];
        if (v0->vec.z < 0.0f) {
            aSide[0] = 0;
            bBehind = true;
        } else if (v0->vec.z > 0.0f) {
            aSide[0] = 1;
            bInFront = true;
        }

        v1 = &pFrame->aVertex[anData[iData + 1]];
        if (v1->vec.z < 0.0f) {
            aSide[1] = 0;
            bBehind = true;
        } else if (v1->vec.z > 0.0f) {
            aSide[1] = 1;
            bInFront = true;
        }

        v2 = &pFrame->aVertex[anData[iData + 2]];
        if (v2->vec.z < 0.0f) {
            aSide[2] = 0;
            bBehind = true;
        } else if (v2->vec.z > 0.0f) {
            aSide[2] = 1;
            bInFront = true;
        }

        if (!bBehind || !bInFront) {
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
            frameWriteVertex(v0);
            frameWriteVertex(v1);
            frameWriteVertex(v2);
            GXEnd();
            iData += 3;
        } else {
            nNewVertCount = 0;
            aNewVertArray[nNewVertCount++] = *v0;
            if ((aSide[0] == 0 && aSide[1] == 1) || (aSide[0] == 1 && aSide[1] == 0)) {
                fInterp = -v0->vec.z / (v1->vec.z - v0->vec.z);

                aNewVertArray[1].vec.z = 0.0f;
                if (v0->vec.y == v1->vec.y) {
                    aNewVertArray[1].vec.y = v0->vec.y;
                } else {
                    aNewVertArray[1].vec.y = v0->vec.y + fInterp * (v1->vec.y - v0->vec.y);
                }
                if (v0->vec.x == v1->vec.x) {
                    aNewVertArray[1].vec.x = v0->vec.x;
                } else {
                    aNewVertArray[1].vec.x = v0->vec.x + fInterp * (v1->vec.x - v0->vec.x);
                }

                aNewVertArray[1].rS = v0->rS + fInterp * (v1->rS - v0->rS);
                aNewVertArray[1].rT = v0->rT + fInterp * (v1->rT - v0->rT);

                fTempColor1 = v1->anColor[0];
                fTempColor2 = v0->anColor[0];
                aNewVertArray[1].anColor[0] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v1->anColor[1];
                fTempColor2 = v0->anColor[1];
                aNewVertArray[1].anColor[1] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v1->anColor[2];
                fTempColor2 = v0->anColor[2];
                aNewVertArray[1].anColor[2] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v1->anColor[3];
                fTempColor2 = v0->anColor[3];
                aNewVertArray[1].anColor[3] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);

                nNewVertCount++;
            }

            aNewVertArray[nNewVertCount++] = *v1;
            if ((aSide[1] == 1 && aSide[2] == 0) || (aSide[1] == 0 && aSide[2] == 1)) {
                fInterp = -v1->vec.z / (v2->vec.z - v1->vec.z);

                aNewVertArray[nNewVertCount].vec.z = 0.0f;
                if (v1->vec.y == v2->vec.y) {
                    aNewVertArray[nNewVertCount].vec.y = v1->vec.y;
                } else {
                    aNewVertArray[nNewVertCount].vec.y = v1->vec.y + fInterp * (v2->vec.y - v1->vec.y);
                }
                if (v1->vec.x == v2->vec.x) {
                    aNewVertArray[nNewVertCount].vec.x = v1->vec.x;
                } else {
                    aNewVertArray[nNewVertCount].vec.x = v1->vec.x + fInterp * (v2->vec.x - v1->vec.x);
                }

                aNewVertArray[nNewVertCount].rS = v1->rS + fInterp * (v2->rS - v1->rS);
                aNewVertArray[nNewVertCount].rT = v1->rT + fInterp * (v2->rT - v1->rT);

                fTempColor1 = v2->anColor[0];
                fTempColor2 = v1->anColor[0];
                aNewVertArray[nNewVertCount].anColor[0] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[1];
                fTempColor2 = v1->anColor[1];
                aNewVertArray[nNewVertCount].anColor[1] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[2];
                fTempColor2 = v1->anColor[2];
                aNewVertArray[nNewVertCount].anColor[2] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[3];
                fTempColor2 = v1->anColor[3];
                aNewVertArray[nNewVertCount].anColor[3] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);

                nNewVertCount++;
            }

            aNewVertArray[nNewVertCount++] = *v2;
            if ((aSide[0] == 0 && aSide[2] == 1) || (aSide[0] == 1 && aSide[2] == 0)) {
                fInterp = -v0->vec.z / (v2->vec.z - v0->vec.z);

                aNewVertArray[nNewVertCount].vec.z = 0.0f;
                if (v0->vec.y == v2->vec.y) {
                    aNewVertArray[nNewVertCount].vec.y = v0->vec.y;
                } else {
                    aNewVertArray[nNewVertCount].vec.y = v0->vec.y + fInterp * (v2->vec.y - v0->vec.y);
                }
                if (v0->vec.x == v2->vec.x) {
                    aNewVertArray[nNewVertCount].vec.x = v0->vec.x;
                } else {
                    aNewVertArray[nNewVertCount].vec.x = v0->vec.x + fInterp * (v2->vec.x - v0->vec.x);
                }

                aNewVertArray[nNewVertCount].rS = v0->rS + fInterp * (v2->rS - v0->rS);
                aNewVertArray[nNewVertCount].rT = v0->rT + fInterp * (v2->rT - v0->rT);

                fTempColor1 = v2->anColor[0];
                fTempColor2 = v0->anColor[0];
                aNewVertArray[nNewVertCount].anColor[0] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[1];
                fTempColor2 = v0->anColor[1];
                aNewVertArray[nNewVertCount].anColor[1] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[2];
                fTempColor2 = v0->anColor[2];
                aNewVertArray[nNewVertCount].anColor[2] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);
                fTempColor1 = v2->anColor[3];
                fTempColor2 = v0->anColor[3];
                aNewVertArray[nNewVertCount].anColor[3] = fTempColor2 + fInterp * (fTempColor1 - fTempColor2);

                nNewVertCount++;
            }

            if (nNewVertCount == 5) {
                if (v1->vec.x == aNewVertArray[1].vec.x && v1->vec.y == aNewVertArray[1].vec.y &&
                    v1->vec.z == aNewVertArray[1].vec.z) {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 9);
                    frameWriteVertex(&aNewVertArray[0]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[0]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[3]);
                    GXEnd();
                } else if (v2->vec.x == aNewVertArray[3].vec.x && v2->vec.y == aNewVertArray[3].vec.y &&
                           v2->vec.z == aNewVertArray[3].vec.z) {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 9);
                    frameWriteVertex(&aNewVertArray[0]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[3]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[3]);
                    GXEnd();
                } else {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 9);
                    frameWriteVertex(&aNewVertArray[0]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[3]);
                    frameWriteVertex(&aNewVertArray[4]);
                    frameWriteVertex(&aNewVertArray[1]);
                    frameWriteVertex(&aNewVertArray[2]);
                    frameWriteVertex(&aNewVertArray[3]);
                    GXEnd();
                }
            }
            iData += 3;
        }
    }

    return true;
}
#endif

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawTriangle_C3T3.s")
#else
bool frameDrawTriangle_C3T3(Frame* pFrame, Primitive* pPrimitive) {
    u32 pad[20];

    if (gpSystem->eTypeROM == SRT_ZELDA1 && pPrimitive->nCount == 3 && (pFrame->aMode[FMT_OTHER0] & 0xC00) == 0xC00) {
        Mtx44Ptr pMatrix = pFrame->aMatrixModel[pFrame->iMatrixModel];
        Vertex* vtx = &pFrame->aVertex[pPrimitive->anData[0]];
        if ((vtx->rSum == 53.0f && pMatrix[3][0] == -3080.0f && pMatrix[3][2] == 6067.0f) ||
            (pMatrix[3][0] == -31.0f && pMatrix[3][2] == 1669.0f)) {
            if (pMatrix[3][0] == -31.0f && pMatrix[3][2] == 1669.0f) {
                gHackCreditsColor = true;
            }
            return true;
        }
    }

    if (pFrame->nModeVtx != 0x17) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x17;
    }

    frameCheckTriangleDivide(pFrame, pPrimitive);
    return true;
}
#endif

static bool frameDrawTriangle_Setup(Frame* pFrame, Primitive* pPrimitive) {
    bool bFlag;
    s32 nColors;

    if (!frameDrawSetupSP(pFrame, &nColors, &bFlag, 3)) {
        return false;
    }

    if (!frameDrawSetupDP(pFrame, &nColors, &bFlag, 0)) {
        return false;
    }

    pFrame->aDraw[1] = (FrameDrawFunc)gapfDrawTriangle[nColors + (bFlag ? 4 : 0)];
    if (!pFrame->aDraw[1](pFrame, pPrimitive)) {
        return false;
    }

    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C0T0.s")
#else
static bool frameDrawLine_C0T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x21) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        pFrame->nModeVtx = 0x21;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
    }
    GXEnd();

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C1T0.s")
#else
static bool frameDrawLine_C1T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;
    Vertex* pVertexColor;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x23) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0x23;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertexColor = &pFrame->aVertex[anData[iData + 0]];
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
    }
    GXEnd();

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C2T0.s")
#else
static bool frameDrawLine_C2T0(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x23) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0x23;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
    }
    GXEnd();

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C0T2.s")
#else
static bool frameDrawLine_C0T2(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x25) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x25;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C1T2.s")
#else
static bool frameDrawLine_C1T2(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;
    Vertex* pVertexColor;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x27) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x27;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertexColor = &pFrame->aVertex[anData[iData + 0]];
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertexColor->anColor[0], pVertexColor->anColor[1], pVertexColor->anColor[2],
                   pVertexColor->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawLine_C2T2.s")
#else
static bool frameDrawLine_C2T2(Frame* pFrame, Primitive* pPrimitive) {
    s32 iData;
    u8* anData;
    Vertex* pVertex;

    anData = pPrimitive->anData;
    if (pFrame->nWidthLine != anData[2]) {
        pFrame->nWidthLine = anData[2];
        GXSetLineWidth(anData[2] * 3 * (s32)(pFrame->rScaleX / 2.0f), GX_TO_ZERO);
    }
    if (pFrame->nModeVtx != 0x27) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0x27;
    }

    GXBegin(GX_LINES, GX_VTXFMT0, pPrimitive->nCount * 2 / 3);
    for (iData = 0; iData < pPrimitive->nCount; iData += 3) {
        pVertex = &pFrame->aVertex[anData[iData + 0]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
        pVertex = &pFrame->aVertex[anData[iData + 1]];
        GXPosition3f32(pVertex->vec.x, pVertex->vec.y, pVertex->vec.z);
        GXColor4u8(pVertex->anColor[0], pVertex->anColor[1], pVertex->anColor[2], pVertex->anColor[3]);
        GXTexCoord2f32(pVertex->rS, pVertex->rT);
    }
    GXEnd();

    return true;
}
#endif

static bool frameDrawLine_Setup(Frame* pFrame, Primitive* pPrimitive) {
    bool bFlag;
    s32 nColors;

    if (!frameDrawSetupSP(pFrame, &nColors, &bFlag, 2)) {
        return false;
    }

    if (!frameDrawSetupDP(pFrame, &nColors, &bFlag, 0)) {
        return false;
    }

    pFrame->aDraw[0] = (FrameDrawFunc)gapfDrawLine[nColors + (bFlag ? 3 : 0)];
    if (!pFrame->aDraw[0](pFrame, pPrimitive)) {
        return false;
    }

    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawRectFill.s")
#else
static bool frameDrawRectFill(Frame* pFrame, Rectangle* pRectangle) {
    bool bFlag;
    f32 rDepth;
    f32 rX0;
    f32 rY0;
    f32 rX1;
    f32 rY1;

    //! @bug `pRectangle->nY1` is using the N64 width instead of the height
    if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x300000 && pRectangle->nX0 <= 16 && pRectangle->nY0 <= 32 &&
        pRectangle->nX1 >= N64_FRAME_WIDTH - 16 && pRectangle->nY1 >= N64_FRAME_WIDTH - 32) {
        bFlag = false;
        if (pFrame->aColor[FCT_FILL].r == 0xFF && pFrame->aColor[FCT_FILL].g == 0xFC &&
            pFrame->aColor[FCT_FILL].b == 0xFF && pFrame->aColor[FCT_FILL].a == 0xFC) {
            bFlag = true;
        }
        if (pFrame->aColor[FCT_FILL].r == 0xF8 && pFrame->aColor[FCT_FILL].g == 0xF8 &&
            pFrame->aColor[FCT_FILL].b == 0xF0 && pFrame->aColor[FCT_FILL].a == 0) {
            bFlag = true;
        }
        if (bFlag && !(*(volatile u32*)&pFrame->nMode & 0x100000)) {
            pFrame->nMode |= 0x100000;
            return true;
        }
    }

    rX0 = pRectangle->nX0;
    rX1 = pRectangle->nX1;
    rY0 = pRectangle->nY0;
    rY1 = pRectangle->nY1;
    if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x300000 || (pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x200000) {
        rX1 += 1.0f;
        rY1 += 1.0f;
    }
    if ((pFrame->aMode[FMT_OTHER0] & 4) == 4) {
        rDepth = pFrame->rDepth;
    } else {
        rDepth = 0.0f;
    }
    if (pFrame->nModeVtx != 0xB) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        pFrame->nModeVtx = 0xB;
    }

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(rX0, rY0, rDepth);
    GXColor1u32(0);
    GXPosition3f32(rX1, rY0, rDepth);
    GXColor1u32(0);
    GXPosition3f32(rX1, rY1, rDepth);
    GXColor1u32(0);
    GXPosition3f32(rX0, rY1, rDepth);
    GXColor1u32(0);
    GXEnd();

    return true;
}
#endif

static bool frameDrawRectFill_Setup(Frame* pFrame, Rectangle* pRectangle) {
    bool bFlag;
    s32 nColors;

    if (!frameDrawSetup2D(pFrame)) {
        return false;
    }

    bFlag = false;
    nColors = 0;

    if (!frameDrawSetupDP(pFrame, &nColors, &bFlag, 1)) {
        return false;
    }

    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill;

    if (!pFrame->aDraw[2](pFrame, pRectangle)) {
        return false;
    }

    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
static bool frameDrawRectTexture(Frame* pFrame, Rectangle* pRectangle);
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawRectTexture.s")
#else
static bool frameDrawRectTexture(Frame* pFrame, Rectangle* pRectangle) {
    s32 bCopy;
    f32 rDepth;
    f32 rDeltaS;
    f32 rDeltaT;
    f32 rX0;
    f32 rY0;
    f32 rX1;
    f32 rY1;
    f32 rS0;
    f32 rT0;
    f32 rS1;
    f32 rT1;
    s32 pad;

    if (gpSystem->eTypeROM == SRT_DRMARIO) {
        if (pRectangle->nX0 == 0 && pRectangle->nY0 == 0 && pRectangle->nX1 == 1208 && pRectangle->nY1 == 20) {
            if (pFrame->aBuffer[FBT_IMAGE].nAddress != 0x3B5000 && pFrame->aBuffer[FBT_IMAGE].nAddress != 0x3DA800 &&
                !pFrame->bBackBufferDrawn) {
                ZeldaDrawFrameNoBlend(pFrame, pFrame->nTempBuffer);
                pFrame->bBackBufferDrawn = true;
                nCounter = 0;
            }
        }
        if (pFrame->bBackBufferDrawn == true) {
            nCounter += 1;
            if (nCounter < 40) {
                return true;
            }
        }
    }

    if (sSpecialZeldaHackON) {
        return true;
    }

    if ((pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x300000 || (pFrame->aMode[FMT_OTHER1] & 0x300000) == 0x200000) {
        bCopy = true;
    } else {
        bCopy = false;
    }

    rDeltaS = bCopy ? pRectangle->rDeltaS / 4.0f : pRectangle->rDeltaS;
    rDeltaT = pRectangle->rDeltaT;

    rX0 = (pRectangle->nX0 + 3) >> 2;
    rX1 = (pRectangle->nX1 + 3) >> 2;
    rY0 = (pRectangle->nY0 + 3) >> 2;
    rY1 = (pRectangle->nY1 + 3) >> 2;

    // TODO: regalloc hacks
    (void)pRectangle->nY0;
    if (gpSystem->eTypeROM == SRT_ZELDA1) {
        if (pRectangle->nX0 == 816 && pRectangle->nY0 == 560) {
            if (gnCountMapHack < 0 && ++gnCountMapHack == 0) {
                gnCountMapHack = 1;
            } else if (gnCountMapHack > 0) {
                gnCountMapHack--;
                return true;
            }
        }
    }

    if (pRectangle->bFlip) {
        rS0 = pRectangle->rS;
        rT0 = pRectangle->rT;
        rS1 = pRectangle->rS + rDeltaS * (rY1 - rY0);
        rT1 = pRectangle->rT + rDeltaT * (rX1 - rX0);
    } else {
        rS0 = pRectangle->rS;
        rT0 = pRectangle->rT;
        rS1 = pRectangle->rS + rDeltaS * (rX1 - rX0);
        rT1 = pRectangle->rT + rDeltaT * (rY1 - rY0);
    }

    if (bCopy) {
        rX1 += 1.0f;
        rS1 += 1.0f;
        rY1 += 1.0f;
        rT1 += 1.0f;
    }

    rDepth = 0.0f;
    if (pFrame->bOverrideDepth) {
        rDepth = -1001.0;
    }

    if (pFrame->nModeVtx != 0xF) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        pFrame->nModeVtx = 0xF;
    }

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    if (pRectangle->bFlip) {
        GXPosition3f32(rX0, rY0, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS0, rT0);
        GXPosition3f32(rX0, rY1, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS1, rT0);
        GXPosition3f32(rX1, rY1, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS1, rT1);
        GXPosition3f32(rX1, rY0, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS0, rT1);
    } else {
        GXPosition3f32(rX0, rY0, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS0, rT0);
        GXPosition3f32(rX1, rY0, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS1, rT0);
        GXPosition3f32(rX1, rY1, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS1, rT1);
        GXPosition3f32(rX0, rY1, rDepth);
        GXColor4u8(0, 0, 0, 0);
        GXTexCoord2f32(rS0, rT1);
    }
    GXEnd();

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
static bool frameDrawRectTexture_Setup(Frame* pFrame, Rectangle* pRectangle);
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameDrawRectTexture_Setup.s")
#else
static bool frameDrawRectTexture_Setup(Frame* pFrame, Rectangle* pRectangle) {
    Mtx matrix;
    Mtx matrixA;
    Mtx matrixB;
    FrameTexture* pTexture[8];
    f32 rScaleS;
    f32 rScaleT;
    f32 rSlideS;
    f32 rSlideT;
    u32 bFlag;
    u32 nColors;
    s32 iTile;
    s32 firstTile;
    s32 nCount;
    s32 iIndex;
    s8 cTempAlpha;

    iTile = firstTile = pRectangle->iTile;
    if (sSpecialZeldaHackON) {
        return true;
    }

    if (!frameDrawSetup2D(pFrame)) {
        return false;
    }

    nColors = 0;
    bFlag = true;
    if (!frameDrawSetupDP(pFrame, (s32*)&nColors, (bool*)&bFlag, 1)) {
        return false;
    }

    nCount = iTile + (iTile < 7 && pFrame->aTile[iTile + 1].nSizeX != 0 ? 1 : 0);
    if (bFlag) {
        for (iIndex = 0; iTile <= nCount; iTile++, iIndex++) {
            if (frameLoadTile(pFrame, &pTexture[iTile], iTile | (iIndex << 4))) {
                if (gpSystem->eTypeROM == SRT_ZELDA2 && pTexture[iTile]->nAddress == 0x784600 &&
                    pRectangle->nX1 == 1280) {
                    bSkip = true;
                    if (!pFrame->bPauseBGDrawn) {
                        cTempAlpha = pFrame->cBlurAlpha;
                        pFrame->cBlurAlpha = 220;
                        ZeldaDrawFrame(pFrame, pFrame->nCopyBuffer);
                        pFrame->cBlurAlpha = cTempAlpha;
                        pFrame->bPauseBGDrawn = true;
                        bSkip = true;
                    }
                }
                if (bSkip) {
                    if (pRectangle->nY1 == 960) {
                        bSkip = false;
                        return true;
                    }
                    return true;
                }

                rScaleS = 1.0f / pTexture[iTile]->nSizeX;
                if (pFrame->aTile[iTile].nShiftS < 11) {
                    rScaleS /= (1 << pFrame->aTile[iTile].nShiftS);
                } else {
                    rScaleS *= (1 << (16 - pFrame->aTile[iTile].nShiftS));
                }

                rScaleT = 1.0f / pTexture[iTile]->nSizeY;
                if (pFrame->aTile[iTile].nShiftT < 11) {
                    rScaleT /= (1 << pFrame->aTile[iTile].nShiftT);
                } else {
                    rScaleT *= (1 << (16 - pFrame->aTile[iTile].nShiftT));
                }

                rSlideS = (pFrame->aTile[iTile].nX0 / 4.0f) / pTexture[iTile]->nSizeX;
                rSlideT = (pFrame->aTile[iTile].nY0 / 4.0f) / pTexture[iTile]->nSizeY;
                PSMTXTrans(matrixA, -rSlideS, -rSlideT, 0.0f);
                PSMTXScale(matrixB, rScaleS, rScaleT, 0.0f);
                PSMTXConcat(matrixA, matrixB, matrix);
                GXLoadTexMtxImm(matrix, ganNameTexMtx[iIndex], 1);
            }
        }

        pFrame->aDraw[3] = (FrameDrawFunc)frameDrawRectTexture;
        if (!pFrame->aDraw[3](pFrame, pRectangle)) {
            return false;
        }
    }

    return true;
}
#endif

bool frameShow(Frame* pFrame) { return true; }

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetScissor.s")
#else
bool frameSetScissor(Frame* pFrame, Rectangle* pScissor) {
    s32 nTemp;
    s32 nX0;
    s32 nY0;
    s32 nX1;
    s32 nY1;

    nX0 = pScissor->nX0 / 4.0f * pFrame->rScaleX;
    nY0 = pScissor->nY0 / 4.0f * pFrame->rScaleY;
    nX1 = pScissor->nX1 / 4.0f * pFrame->rScaleX;
    nY1 = pScissor->nY1 / 4.0f * pFrame->rScaleY;

    if (nX1 < nX0) {
        nTemp = nX1;
        nX1 = nX0;
        nX0 = nTemp;
    }

    if (nY1 < nY0) {
        nTemp = nY1;
        nY1 = nY0;
        nY0 = nTemp;
    }

    GXSetScissor(nX0, nY0, nX1 - nX0, nY1 - nY0);
    return true;
}
#endif

bool frameSetDepth(Frame* pFrame, f32 rDepth, f32 rDelta) {
    pFrame->rDepth = rDepth;
    pFrame->rDelta = rDelta;
    return true;
}

bool frameSetColor(Frame* pFrame, FrameColorType eType, u32 nRGBA) {
    pFrame->aColor[eType].r = (nRGBA >> 24) & 0xFF;
    pFrame->aColor[eType].g = (nRGBA >> 16) & 0xFF;
    pFrame->aColor[eType].b = (nRGBA >> 8) & 0xFF;
    pFrame->aColor[eType].a = nRGBA & 0xFF;

    if (eType == FCT_PRIMITIVE) {
        GXSetTevColor(GX_TEVREG2, pFrame->aColor[eType]);
    } else if (eType == FCT_ENVIRONMENT) {
        GXSetTevKColor(GX_KCOLOR1, pFrame->aColor[eType]);
    }

    frameDrawReset(pFrame, (eType == FCT_FOG ? 0x20 : 0x0) | 0x7F00);
    return true;
}

bool frameBeginOK(Frame* pFrame) {
    if (gbFrameValid) {
        return false;
    }
    return true;
}

static inline void frameClearModes(Frame* pFrame) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(pFrame->aMode); i++) {
        pFrame->aMode[i] = 0;
    }
}

bool frameBegin(Frame* pFrame, s32 nCountVertex) {
    s32 i;
    Mtx matrix;

    if (gbFrameBegin) {
        gbFrameBegin = false;

        while (gbFrameValid) {
            OSReport(D_800EB1F8);
        }

        if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
            return false;
        }

        if (!frameUpdateCache(pFrame)) {
            return false;
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

        GXSetScissor(0, 0, pFrame->anSizeX[FS_TARGET], pFrame->anSizeY[FS_TARGET]);
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
    return true;
}

bool frameEnd(Frame* pFrame) {
    Cpu* pCPU;
    s32 iHint;
    void* pData;

    pCPU = SYSTEM_CPU(gpSystem);

    if (gbFrameBegin) {
        OSReport(D_800EB1B8);
    }
    gbFrameBegin = true;

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if (pFrame->aMatrixHint[iHint].nCount >= 0) {
            pFrame->aMatrixHint[iHint].nCount--;
        }
    }

    pFrame->nCountFrames++;
    gbFrameValid = true;

    if (pFrame->aBuffer[FBT_DEPTH].nAddress != 0) {
        pData = &sTempZBuf;

        GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
        GXSetTexCopyDst(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_Z16, GX_TRUE);
        GXCopyTex(pData, GX_FALSE);
        DCInvalidateRange(pData, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
    }

    if (gpSystem->eTypeROM == SRT_DRMARIO && pFrame->bGrabbedFrame) {
        pData = pFrame->nTempBuffer;
        CopyCFB(pData);
        pFrame->bGrabbedFrame = false;
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
    GXSetDrawDone();
    GXFlush();

    if (gpSystem->eTypeROM == SRT_ZELDA2) {
        pFrame->nHackCount = 0;
        pFrame->nFrameCounter++;
        pFrame->bBlurredThisFrame = false;
        pFrame->nFrameCIMGCalls = 0;
        pFrame->bUsingLens = false;
        pFrame->bModifyZBuffer = false;
        pFrame->bOverrideDepth = false;

        pFrame->nLastFrameZSets = pFrame->nZBufferSets;
        pFrame->nZBufferSets = 0;

        pFrame->bPauseBGDrawn = false;
        GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);

        if ((pFrame->bShrinking & 0xF) == 0) {
            pFrame->bShrinking &= ~0xFFFF;
        }
        pFrame->bShrinking &= ~0xFF;
        pFrame->bSnapShot = false;
    }

    if (gpSystem->eTypeROM == SRT_DRMARIO) {
        pFrame->bBackBufferDrawn = false;
    }

    pCPU->gTree->kill_number = 0;
    return true;
}

bool _frameDrawRectangle(Frame* pFrame, u32 nColor, s32 nX, s32 nY, s32 nSizeX, s32 nSizeY) {
    s32 iY;
    s32 iX;
    u32* pnPixel;
    s32 nSizeTargetX = pFrame->anSizeX[FS_TARGET];

    nX = (nX + 1) & ~1;
    nSizeX = (nSizeX + 1) & ~1;
    if (DemoCurrentBuffer == DemoFrameBuffer1) {
        pnPixel = (u32*)((s16*)DemoFrameBuffer2 + (nY * nSizeTargetX) + nX);
    } else {
        pnPixel = (u32*)((s16*)DemoFrameBuffer1 + (nY * nSizeTargetX) + nX);
    }

    pnPixel = (u32*)((u8*)pnPixel + 0x40000000);

    for (iY = 0; iY < nSizeY; iY++) {
        for (iX = 0; iX < (nSizeX >> 1); iX++) {
            pnPixel[iX] = nColor;
        }
        pnPixel += (nSizeTargetX >> 1);
    }

    return true;
}

// matches but data doesn't
//! TODO: make sFrameObj a static variable in the function
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameNoBlend.s")
#else
void ZeldaDrawFrameNoBlend(Frame* pFrame, u16* pData) {
    Mtx matrix;
    u32 pad[8];

    frameDrawSetup2D(pFrame);
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevOp(0, 3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&sFrameObj_1564, pData, N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sFrameObj_1564, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sFrameObj_1564, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}
#endif

// matches but data doesn't
//! TODO: make sFrameObj a static variable in the function
#ifndef NON_MATCHING
void ZeldaDrawFrameBlur(Frame* pFrame, u16* pData);
#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrameBlur.s")
#else
void ZeldaDrawFrameBlur(Frame* pFrame, u16* pData) {
    Mtx matrix;
    s32 pad[8];
    GXColor color;

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = pFrame->cBlurAlpha;

    frameDrawSetup2D(pFrame);
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&sFrameObj_1565, pData, N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sFrameObj_1565, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sFrameObj_1565, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-1.0f, -1.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH - 1, -1.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH - 1, N64_FRAME_HEIGHT - 1, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(-1.0f, N64_FRAME_HEIGHT - 1, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}
#endif

// matches but data doesn't
//! TODO: make sFrameObj a static variable in the function
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/ZeldaDrawFrame.s")
#else
void ZeldaDrawFrame(Frame* pFrame, u16* pData) {
    Mtx matrix;
    u32 pad[8];
    GXColor color;

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = pFrame->cBlurAlpha;

    frameDrawSetup2D(pFrame);
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&sFrameObj_1568, pData, N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sFrameObj_1568, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sFrameObj_1568, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}
#endif

static inline void CopyCFB(u16* srcP) {
    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, GX_TF_RGB565, GX_TRUE);
    DCInvalidateRange(srcP, N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16));
    GXCopyTex(srcP, GX_FALSE);
    sCopyFrameSyncReceived = false;
    GXSetDrawSync(FRAME_SYNC_TOKEN);
    while (!sCopyFrameSyncReceived) {}
}

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

    sCopyFrameSyncReceived = false;
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
void ZeldaGreyScaleConvert(Frame* pFrame);
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
    GXSetTexCopyDst(GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_I8, GX_FALSE);
    GXCopyTex(dataP, GX_FALSE);
    GXPixModeSync();
    frameDrawSetup2D(pFrame);

    if (gHackCreditsColor) {
        GXSetNumTevStages(1);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        if (cAlpha < 255) {
            cAlpha += 20;
        }
    } else {
        GXSetNumTevStages(1);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&sFrameObj_1647, dataP, GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sFrameObj_1647, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sFrameObj_1647, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}
#endif

// matches but data doesn't
//! TODO: make sFrameObj a static variable in the function
#ifndef NON_MATCHING
void ZeldaDrawFrameShrink(Frame* pFrame, s32 posX, s32 posY, s32 size);
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
    nX1 = N64_FRAME_WIDTH;
    nY1 = N64_FRAME_HEIGHT;

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
    GXSetTexCopySrc(0, 0, GC_FRAME_WIDTH, GC_FRAME_HEIGHT);
    GXSetTexCopyDst(GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(frameBuffer, GX_FALSE);
    GXPixModeSync();
    frameDrawSetup2D(pFrame);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXEnd();

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&frameObj_1663, frameBuffer, GC_FRAME_WIDTH, GC_FRAME_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP,
                 GX_FALSE);
    GXInitTexObjLOD(&frameObj_1663, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&frameObj_1663, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0, nY0, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX1, nY0, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX1, nY1, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0, nY1, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}
#endif

// matches but data doesn't
//! TODO: make sFrameObj a static variable in the function
#ifndef NON_MATCHING
void ZeldaDrawFrameCamera(Frame* pFrame, void* buffer);
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
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 30, GX_MTX2x4);
    GXInitTexObj(&frameObj_1673, buffer, ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT, GX_TF_I8, GX_CLAMP, GX_CLAMP,
                 GX_FALSE);
    GXInitTexObjLOD(&frameObj_1673, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&frameObj_1673, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(80.0f, 31.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.015625f);
    GXPosition3f32(240.0f, 31.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.015625f);
    GXPosition3f32(240.0f, 143.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.859375f);
    GXPosition3f32(80.0f, 143.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.859375f);
    GXEnd();

    pFrame->nMode = 0;
    pFrame->nModeVtx = -1;
    frameDrawReset(pFrame, 0x47F2D);
}
#endif

//! TODO: make sCommandCodes a static variable in the function
bool frameHackTIMG_Zelda(Frame* pFrame, u64** pnGBI, u32* pnCommandLo, u32* pnCommandHi) {
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

    return true;
}

bool frameHackCIMG_Zelda2(Frame* pFrame, FrameBuffer* pBuffer, u64* pnGBI, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32* pGBI;
    s32 pad[2];

    if (pBuffer->nAddress == pFrame->aBuffer[FBT_DEPTH].nAddress) {
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
            pFrame->bPauseThisFrame = false;
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
            pFrame->bHackPause = true;
            pFrame->nHackCount = 0;
            pFrame->bPauseThisFrame = 1;
            nCopyFrame = 0;
        } else {
            pFrame->bPauseThisFrame = false;
        }
    }

    if (pFrame->bHackPause) {
        if ((pFrame->nFrameCounter - nLastFrame) >= 2) {
            nLastFrame = pFrame->nFrameCounter;
            gNoSwapBuffer = true;
        }
        pFrame->bHackPause = false;
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
        pFrame->bBlurredThisFrame = true;
    }

    return true;
}

bool frameHackCIMG_Zelda(Frame* pFrame, FrameBuffer* pBuffer, u64* pnGBI, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32 low2;
    u32 high2;
    u16* srcP;

    for (i = 0; i < sNumAddr; i++) {
        if (nCommandLo == sConstantBufAddr[i]) {
            break;
        }
    }

    if (pBuffer->nAddress == pFrame->aBuffer[FBT_DEPTH].nAddress && pBuffer->nWidth == N64_FRAME_WIDTH) {
        low2 = pnGBI[1];
        high2 = pnGBI[1] >> 32;
        if (high2 == 0xFD10013F) {
            low2 = SYSTEM_RSP(gpSystem)->anBaseSegment[(low2 >> 24) & 0xF] + (low2 & 0xFFFFFF);
            if (!ramGetBuffer(SYSTEM_RAM(gpSystem), (void**)&srcP, low2, NULL)) {
                return false;
            }
            sDestinationBuffer = low2;
            sSrcBuffer = pBuffer->nAddress;
            CopyAndConvertCFB(srcP);
            gnCountMapHack = -1;
            gNoSwapBuffer = true;
        }
    }

    if (i >= sNumAddr) {
        if (sNumAddr < ARRAY_COUNT(sConstantBufAddr)) {
            sConstantBufAddr[sNumAddr++] = nCommandLo;
            sConstantBufAddr[sNumAddr++] =
                nCommandLo + ZELDA_PAUSE_EQUIP_PLAYER_WIDTH * ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT * sizeof(u16);
        } else if (pBuffer->nWidth == ZELDA_PAUSE_EQUIP_PLAYER_WIDTH) {
            gNoSwapBuffer = true;
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

                sCopyFrameSyncReceived = false;
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
    return true;
}

bool frameHackCIMG_Zelda2_Shrink(Rdp* pRDP, Frame* pFrame, u64** ppnGBI) {
    u64* pnGBI;
    s32 count;
    s32 nAddress;
    u32 nCommandLo;
    u32 nCommandHi;
    Rsp* pRSP;
    s32 done;
    union __anon_0x5F2FB bg;

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

        while (true) {
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
        return false;
    }

    *ppnGBI = ++pnGBI;
    return true;
}

static inline void ZeldaCopyCamera(u16* buffer) {
    GXSetTexCopySrc(ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT - 10, ZELDA2_CAMERA_WIDTH * 2, ZELDA2_CAMERA_HEIGHT * 2);
    GXSetTexCopyDst(ZELDA2_CAMERA_WIDTH, ZELDA2_CAMERA_HEIGHT, GX_TF_I8, GX_TRUE);
    DCInvalidateRange(buffer, ZELDA2_CAMERA_WIDTH * ZELDA2_CAMERA_HEIGHT * sizeof(u16));
    GXCopyTex(buffer, GX_FALSE);
    GXPixModeSync();
}

bool frameHackCIMG_Zelda2_Camera(Frame* pFrame, FrameBuffer* pBuffer, u32 nCommandHi, u32 nCommandLo) {
    if (pBuffer != NULL) {
        if (pBuffer->nAddress == 0x00784600) {
            pFrame->bSnapShot |= 0x10;
            return true;
        }

        if ((pFrame->bSnapShot & 0xF00) != 0) {
            ZeldaDrawFrameCamera(pFrame, pFrame->nCameraBuffer);
            pFrame->bSnapShot &= ~0xF00;
            return true;
        }

        return false;
    }

    if ((nCommandHi == 0xF63EC25C) && (nCommandLo == 0x00118058)) {
        pFrame->bSnapShot |= 1;

        // possible bug? probably meant to be ``pFrame->bSnapShot & 0xF00``
        if ((pFrame->bSnapShot & 0xF0) != 0) {
            ZeldaCopyCamera(pFrame->nCameraBuffer);
            pFrame->bSnapShot &= ~0xF00;
        }

        return true;
    }

    return false;
}

void PanelDrawBG8(u16* BG, u16* LUT, u8* bitmap, s32 sizeX, s32 sizeY, s32 posX, s32 posY, bool flip) {
    s32 i;
    s32 j;
    u16 color;
    s32 pad[3];

    for (i = 0; i < sizeY; i++) {
        for (j = 0; j < sizeX; j++) {
            color = LUT[bitmap[i * sizeX + j]];
            if (color & 1) {
                if (!flip) {
                    BG[(posY + i) * N64_FRAME_WIDTH + posX + j] = color;
                } else {
                    BG[(posY + i) * N64_FRAME_WIDTH + posX + (sizeX - j)] = color;
                }
            }
        }
    }
}

void PanelDrawBG16(u16* BG, u16* bitmap, s32 sizeX, s32 sizeY, s32 posX, s32 posY, bool flip) {
    s32 i;
    s32 j;
    u16 color;
    s32 pad[2];

    for (i = 0; i < sizeY; i++) {
        for (j = 0; j < sizeX; j++) {
            color = bitmap[i * sizeX + j];
            if (color & 1) {
                if (!flip) {
                    BG[(posY + i) * N64_FRAME_WIDTH + posX + j] = color;
                } else {
                    BG[(posY + i) * N64_FRAME_WIDTH + posX + (sizeX - j)] = color;
                }
            }
        }
    }
}

void PanelDrawFR3D(u16* FR, u16* LUT, u8* bitmap, s32 sizeX, s32 sizeY, s32 posX, s32 posY, bool first) {
    s32 i;
    s32 j;
    u16 color;
    s32 pad[3];

    for (i = 0; i < sizeY; i++) {
        for (j = 0; j < sizeX; j++) {
            color = LUT[bitmap[i * sizeX + j]];
            if (first) {
                if (color == 0x6D3F) {
                    color = 0x6D3E;
                }
                FR[(posY + i) * N64_FRAME_WIDTH + posX + j] = color;
            } else if (color & 1) {
                FR[(posY + i) * N64_FRAME_WIDTH + posX + j] = color;
            }
        }
    }
}

bool frameHackTIMG_Panel(Frame* pFrame, FrameBuffer* pBuffer) {
    if (!pFrame->bFrameOn) {
        return false;
    }

    if (pBuffer->nAddress >= 0x358800 && pBuffer->nAddress <= 0x37B800) {
        if (pBuffer->nFormat == 0 && pBuffer->nWidth == 1 && pBuffer->nSize == 2) {
            pBuffer->pData = pFrame->nTempBuffer + ((((s32)(pBuffer->nAddress + 0xFFCA7800) / 2) + 0x8C0));
            return true;
        }
        pFrame->bFrameOn = false;
        return false;
    }

    return false;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameHackCIMG_Panel.s")

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameGetDepth.s")
#else
bool frameGetDepth(Frame* pFrame, u16* pnData, s32 nAddress) {
    u32 nX;
    u32 nY;
    u32 nOffset;
    s32 n64CalcValue;
    s32 exp;
    s32 mantissa;
    s32 compare;
    s32 val;
    s32 pad[2];

    // See "Z Image Format" in the N64 Programming Manual
    // https://ultra64.ca/files/documentation/online-manuals/man/pro-man/pro15/index15.5.html
    struct {
        s32 shift;
        s32 add;
    } z_format[8] = {
        {6, 0x00000}, {5, 0x20000}, {4, 0x30000}, {3, 0x38000}, {2, 0x3C000}, {1, 0x3E000}, {0, 0x3F000}, {0, 0x3F800},
    };

    nAddress &= 0x03FFFFFF;
    if (pFrame->nOffsetDepth0 <= nAddress && nAddress <= pFrame->nOffsetDepth1) {
        nOffset = (nAddress - pFrame->nOffsetDepth0) / 2;
        nX = nOffset % N64_FRAME_WIDTH;
        nY = nOffset / N64_FRAME_WIDTH;

        val = sTempZBuf[(nY >> 2) * (N64_FRAME_WIDTH / 4) + (nX >> 2)][nY & 3][nX & 3];
        n64CalcValue = 43.52 * ((((val & 0xFF) << 8) | (val >> 8)) - 0x10000 + 1) + 262143.0;

        compare = 0x3F800;
        for (exp = 7; exp >= 0; exp--) {
            if ((n64CalcValue & compare) == compare) {
                break;
            }
            compare = (compare << 1) & 0x3FFFF;
        }

        mantissa = ((n64CalcValue - z_format[exp].add) >> z_format[exp].shift) & 0x7FF;

        *pnData = 0;
        *pnData = ((exp << 13) & 0xE000) | ((mantissa << 2) & 0x1FFC);
        return true;
    }

    return false;
}
#endif

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameEvent.s")
#else
bool frameEvent(Frame* pFrame, s32 nEvent, void* pArgument) {
    s32 temp_r4;

    switch (nEvent) {
        case 2:
            pFrame->nFlag = 0;
            pFrame->nMode = 0x20000;
            pFrame->iHintMatrix = 0;
            pFrame->nCountFrames = 0;
            gbFrameBegin = true;
            gbFrameValid = false;
            gnCountMapHack = 0;
            if (!frameSetupCache(pFrame)) {
                return false;
            }
            pFrame->nOffsetDepth0 = -1;
            pFrame->nOffsetDepth1 = -1;
            pFrame->viewport.rX = 0.0f;
            pFrame->viewport.rY = 0.0f;
            pFrame->nHackCount = 0;
            pFrame->bBlurOn = false;
            pFrame->bHackPause = false;
            pFrame->nFrameCounter = 0;
            pFrame->nNumCIMGAddresses = 0;
            pFrame->bPauseThisFrame = false;
            pFrame->bCameFromBomberNotes = false;
            pFrame->bInBomberNotes = false;
            pFrame->bShrinking = 0;
            pFrame->bUsingLens = false;
            pFrame->cBlurAlpha = 170;
            pFrame->bBlurredThisFrame = false;
            pFrame->nFrameCIMGCalls = 0;
            pFrame->nZBufferSets = 0;
            pFrame->nLastFrameZSets = 0;
            pFrame->bPauseBGDrawn = false;
            pFrame->bFrameOn = false;
            pFrame->bModifyZBuffer = false;
            pFrame->bOverrideDepth = false;
            pFrame->viewport.rSizeX = GC_FRAME_WIDTH;
            pFrame->viewport.rSizeY = GC_FRAME_HEIGHT;
            pFrame->anSizeX[FS_SOURCE] = N64_FRAME_WIDTH;
            pFrame->anSizeY[FS_SOURCE] = N64_FRAME_HEIGHT;
            pFrame->rScaleX = (f32)pFrame->anSizeX[FS_TARGET] / (f32)N64_FRAME_WIDTH;
            pFrame->rScaleY = (f32)pFrame->anSizeY[FS_TARGET] / (f32)N64_FRAME_HEIGHT;

            temp_r4 = GC_FRAME_HEIGHT >> (xlCoreHiResolution() ? 0 : 1);
            if (temp_r4 > 0) {
                pFrame->anSizeX[FS_TARGET] = GC_FRAME_WIDTH;
                pFrame->anSizeY[FS_TARGET] = temp_r4;
                pFrame->rScaleX = GC_FRAME_WIDTH / (f32)pFrame->anSizeX[FS_SOURCE];
                pFrame->rScaleY = temp_r4 / (f32)pFrame->anSizeY[FS_SOURCE];
            }
            GXSetDrawDoneCallback(&frameDrawDone);
            break;
        case 3:
            if (!frameResetCache(pFrame)) {
                return false;
            }
            break;
#if VERSION != MQ_J
        case 0x1003:
            pFrame->nTempBuffer = NULL;
            pFrame->nCopyBuffer = NULL;
            pFrame->nLensBuffer = NULL;
            pFrame->nCameraBuffer = NULL;
            if (((gpSystem->eTypeROM == SRT_PANEL) || (gpSystem->eTypeROM == SRT_ZELDA2) ||
                 (gpSystem->eTypeROM == SRT_DRMARIO)) &&
                !xlHeapTake(&pFrame->nTempBuffer, 0x30000000 | (N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16)))) {
                return false;
            }
            if ((gpSystem->eTypeROM == SRT_ZELDA2) &&
                !xlHeapTake(&pFrame->nCopyBuffer, 0x30000000 | (N64_FRAME_WIDTH * N64_FRAME_HEIGHT * sizeof(u16)))) {
                return false;
            }
            if ((gpSystem->eTypeROM == SRT_ZELDA2) && !xlHeapTake(&pFrame->nLensBuffer, 0x30000000 | 0x4B000)) {
                return false;
            }
            if ((gpSystem->eTypeROM == SRT_ZELDA2) && !xlHeapTake(&pFrame->nCameraBuffer, 0x30000000 | 0xA000)) {
                return false;
            }
            break;
#endif
        case 0:
        case 1:
        case 5:
        case 6:
            break;
        default:
            return false;
    }

    return true;
}
#endif

static inline bool frameCopyMatrix(Mtx44 matrixTarget, Mtx44 matrixSource) {
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
    return true;
}

static inline bool frameTransposeMatrix(Mtx44 matrixTarget, Mtx44 matrixSource) {
    matrixTarget[0][0] = matrixSource[0][0];
    matrixTarget[0][1] = matrixSource[1][0];
    matrixTarget[0][2] = matrixSource[2][0];
    matrixTarget[0][3] = matrixSource[3][0];
    matrixTarget[1][0] = matrixSource[0][1];
    matrixTarget[1][1] = matrixSource[1][1];
    matrixTarget[1][2] = matrixSource[2][1];
    matrixTarget[1][3] = matrixSource[3][1];
    matrixTarget[2][0] = matrixSource[0][2];
    matrixTarget[2][1] = matrixSource[1][2];
    matrixTarget[2][2] = matrixSource[2][2];
    matrixTarget[2][3] = matrixSource[3][2];
    matrixTarget[3][0] = matrixSource[0][3];
    matrixTarget[3][1] = matrixSource[1][3];
    matrixTarget[3][2] = matrixSource[2][3];
    matrixTarget[3][3] = matrixSource[3][3];
    return true;
}

bool frameScaleMatrix(Mtx44 matrixResult, Mtx44 matrix, f32 rScale) {
    matrixResult[0][0] = matrix[0][0] * rScale;
    matrixResult[0][1] = matrix[0][1] * rScale;
    matrixResult[0][2] = matrix[0][2] * rScale;
    matrixResult[0][3] = matrix[0][3] * rScale;
    matrixResult[1][0] = matrix[1][0] * rScale;
    matrixResult[1][1] = matrix[1][1] * rScale;
    matrixResult[1][2] = matrix[1][2] * rScale;
    matrixResult[1][3] = matrix[1][3] * rScale;
    matrixResult[2][0] = matrix[2][0] * rScale;
    matrixResult[2][1] = matrix[2][1] * rScale;
    matrixResult[2][2] = matrix[2][2] * rScale;
    matrixResult[2][3] = matrix[2][3] * rScale;
    matrixResult[3][0] = matrix[3][0] * rScale;
    matrixResult[3][1] = matrix[3][1] * rScale;
    matrixResult[3][2] = matrix[3][2] * rScale;
    matrixResult[3][3] = matrix[3][3] * rScale;
    return true;
}

static bool frameConvertYUVtoRGB(u32* YUV, u32* RGB) {
    s32 Yl;
    s32 R;
    s32 G;
    s32 B;

    Yl = YUV[0] - 16;
    B = (s32)((YUV[1] - 128) * 20830 + Yl * 12014) >> 16;
    G = (s32)(Yl * 11079 + ((YUV[2] - 128) * -6480 - B * 12729)) >> 16;
    R = (s32)(Yl * 31026 - B * 24987 - G * 128660) >> 16;

    if (R > 31) {
        R = 31;
    } else if (R < 0) {
        R = 0;
    }
    if (G > 31) {
        G = 31;
    } else if (G < 0) {
        G = 0;
    }
    if (B > 31) {
        B = 31;
    } else if (B < 0) {
        B = 0;
    }

    RGB[0] = R;
    RGB[1] = G;
    RGB[2] = B;
    return true;
}

static bool packTakeBlocks(s32* piPack, u32* anPack, s32 nPackCount, s32 nBlockCount) {
    s32 nOffset;
    s32 nCount;
    s32 iPack;
    u32 nPack;
    u32 nMask;
    u32 nMask0;

    if (nBlockCount >= 32 || nBlockCount < 0) {
        return false;
    }

    nCount = 33 - nBlockCount;
    for (iPack = 0; iPack < nPackCount; iPack++) {
        nPack = anPack[iPack];
        if (nPack != -1) {
            nMask = (1 << nBlockCount) - 1;
            nOffset = nCount;
            do {
                if ((nPack & nMask) == 0) {
                    anPack[iPack] |= nMask;
                    *piPack = (nBlockCount << 16) | ((iPack << 5) + (nCount - nOffset));
                    return true;
                }
                nOffset -= 1;
                nMask <<= 1;
            } while (nOffset != 0);
        }
    }

    *piPack = -1;
    return false;
}

static bool packFreeBlocks(s32* piPack, u32* anPack, s32 nPackCount) {
    s32 iPack;
    u32 nMask;

    s32 temp_r6;

    iPack = *piPack;

    if (iPack == -1) {
        return true;
    }

    nMask = ((1 << (iPack >> 16)) - 1) << (iPack & 0x1F);
    temp_r6 = (iPack & 0xFFFF) >> 5;

    if (nMask == (nMask & anPack[temp_r6])) {
        anPack[temp_r6] &= ~nMask;
        *piPack = -1;
        return true;
    }

    return false;
}

static bool frameMakeTexture(Frame* pFrame, FrameTexture** ppTexture) {
    u32 nMask;
    s32 iTexture;
    s32 iTextureUsed;

    iTextureUsed = 0;
    while (iTextureUsed < ARRAY_COUNTU(pFrame->anTextureUsed) && (nMask = pFrame->anTextureUsed[iTextureUsed]) == -1) {
        iTextureUsed++;
    }

    if (iTextureUsed == ARRAY_COUNTU(pFrame->anTextureUsed)) {
        xlPostText(D_800EB2D4, D_80134E58, 554);
        return false;
    }

    iTexture = 0;
    while (nMask & 1) {
        iTexture++;
        nMask >>= 1;
    }

    pFrame->anTextureUsed[iTextureUsed] |= (1 << iTexture);
    *ppTexture = &pFrame->aTexture[(iTextureUsed << 5) + iTexture];
    (*ppTexture)->iPackPixel = -1;
    (*ppTexture)->iPackColor = -1;
    (*ppTexture)->pTextureNext = NULL;

    if (++pFrame->nBlocksTexture > pFrame->nBlocksMaxTexture) {
        pFrame->nBlocksMaxTexture = pFrame->nBlocksTexture;
    }

    return true;
}

static inline bool frameFreeTexture(Frame* pFrame, FrameTexture* pTexture) {
    s32 iTexture = (u8*)pTexture - (u8*)&pFrame->aTexture[0];

    if (!frameFreePixels(pFrame, pTexture)) {
        return false;
    }

    iTexture /= sizeof(FrameTexture);
    pFrame->anTextureUsed[iTexture >> 5] &= ~(1 << (iTexture & 0x1F));
    pFrame->nBlocksTexture--;
    return true;
}

static bool frameSetupCache(Frame* pFrame) {
    s32 iTexture;

    pFrame->nBlocksMaxPixel = 0;
    pFrame->nBlocksPixel = 0;
    pFrame->nBlocksMaxColor = 0;
    pFrame->nBlocksColor = 0;
    pFrame->nBlocksMaxTexture = 0;
    pFrame->nBlocksTexture = 0;

    for (iTexture = 0; iTexture < ARRAY_COUNT(pFrame->apTextureCached); iTexture++) {
        pFrame->apTextureCached[iTexture] = 0;
    }

    for (iTexture = 0; iTexture < ARRAY_COUNTU(pFrame->anTextureUsed); iTexture++) {
        pFrame->anTextureUsed[iTexture] = 0;
    }

    for (iTexture = 0; iTexture < ARRAY_COUNT(pFrame->anPackPixel); iTexture++) {
        pFrame->anPackPixel[iTexture] = 0;
    }

    if (!xlHeapTake(&pFrame->aPixelData, 0x30000000 | 0x00300000)) {
        return false;
    }

    for (iTexture = 0; iTexture < ARRAY_COUNT(pFrame->anPackColor); iTexture++) {
        pFrame->anPackColor[iTexture] = 0;
    }

    if (!xlHeapTake(&pFrame->aColorData, 0x30000000 | (N64_FRAME_WIDTH * 1024))) {
        return false;
    }

    return true;
}

static inline bool frameResetCache(Frame* pFrame) {
    if (!xlHeapFree(&pFrame->aColorData)) {
        return false;
    }

    if (!xlHeapFree(&pFrame->aPixelData)) {
        return false;
    }

    return true;
}

static bool frameUpdateCache(Frame* pFrame) {
    // s32 nCount;
    // s32 nCountFree;
    u32 nMask;
    s32 nFrameCount;
    s32 nFrameDelta;
    s32 iTexture;
    s32 iTextureUsed;
    s32 iTextureCached;
    FrameTexture* pTexture;
    FrameTexture* pTextureCached;
    FrameTexture* pTextureLast;

    nFrameCount = pFrame->nCountFrames;
    for (iTextureUsed = 0; iTextureUsed < ARRAY_COUNTU(pFrame->anTextureUsed); iTextureUsed++) {
        if ((nMask = pFrame->anTextureUsed[iTextureUsed]) != 0) {
            for (iTexture = 0; nMask != 0; iTexture++, nMask >>= 1) {
                if (nMask & 1) {
                    pTexture = &pFrame->aTexture[(iTextureUsed << 5) + iTexture];
                    nFrameDelta = pTexture->nFrameLast - nFrameCount;
                    if (nFrameDelta < 0) {
                        nFrameDelta = -nFrameDelta;
                    }
                    if (nFrameDelta > 1) {
                        pTextureLast = NULL;
                        iTextureCached = pTexture->nAddress >> 11;
                        pTextureCached = pFrame->apTextureCached[iTextureCached];

                        while (pTextureCached != NULL && pTextureCached != pTexture) {
                            pTextureLast = pTextureCached;
                            pTextureCached = pTextureCached->pTextureNext;
                        }

                        if (pTextureLast == NULL) {
                            pFrame->apTextureCached[iTextureCached] = pTextureCached->pTextureNext;
                        } else {
                            pTextureLast->pTextureNext = pTextureCached->pTextureNext;
                        }
                        if (!frameFreeTexture(pFrame, pTexture)) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

static bool frameLoadTile(Frame* pFrame, FrameTexture** ppTexture, s32 iTileCode) {
    bool bFlag;
    Tile* pTile;
    FrameTexture* pTexture;
    FrameTexture* pTextureLast;
    u32 nData0;
    u32 nData1;
    u32 nData2;
    u32 nData3;
    s32 iTexture;
    s32 nShift;
    s32 pad;

    pTile = &pFrame->aTile[iTileCode & 0xF];
    if (pTile->nX0 == 0 && pTile->nY0 == 0 && pTile->nX1 == 0 && pTile->nY1 == 0) {
        bFlag = true;
        pTile->nX0 = pFrame->aTile[pFrame->iTileLoad].nX0;
        pTile->nY0 = pFrame->aTile[pFrame->iTileLoad].nY0;
        pTile->nX1 = pFrame->aTile[pFrame->iTileLoad].nX1;
        pTile->nY1 = pFrame->aTile[pFrame->iTileLoad].nY1;
        nShift = pFrame->aTile[pFrame->iTileLoad].nSize - pTile->nSize;
        if (nShift < 0) {
            nShift = -nShift;
            pTile->nX0 >>= nShift;
            pTile->nX1 >>= nShift;
        } else {
            pTile->nX0 <<= nShift;
            pTile->nX1 <<= nShift;
        }
        pTile->nModeS = 2;
        pTile->nModeT = 2;
    } else {
        bFlag = false;
    }

    nData0 = (pTile->nX0 & 0xFFFF) | ((pTile->nX1 & 0xFFFF) << 16);
    nData1 = (pTile->nY0 & 0xFFFF) | ((pTile->nY1 & 0xFFFF) << 16);
    nData2 = ((pTile->nMaskS & 0xF) << 0) | ((pTile->nMaskT & 0xF) << 4) | ((pTile->nModeS & 7) << 8) |
             ((pTile->nModeT & 7) << 11) | ((pTile->nShiftS & 0xF) << 14) | ((pTile->nShiftT & 0xF) << 18) |
             ((pTile->nSize & 7) << 22) | ((pTile->nFormat & 7) << 25) | ((pTile->iTLUT & 0xF) << 28);
    nData3 = (pTile->nTMEM & 0xFFFF) | ((pTile->nSizeX & 0xFFFF) << 16);
    if (pFrame->nAddressLoad == -1) {
        iTexture = 0;
    } else {
        iTexture = pFrame->nAddressLoad >> 11;
    }

    pTextureLast = pTexture = pFrame->apTextureCached[iTexture];
    while (pTexture != NULL) {
        if (pTexture->nData0 == nData0 && pTexture->nData1 == nData1 && pTexture->nData2 == nData2 &&
            pTexture->nData3 == nData3 && pTexture->nCodePixel == pTile->nCodePixel &&
            pTexture->nAddress == pFrame->nAddressLoad) {
            break;
        }
        pTextureLast = pTexture;
        pTexture = pTexture->pTextureNext;
    }

    if (pTexture == NULL) {
        if (!frameMakeTexture(pFrame, &pTexture)) {
            return false;
        }

        frameMakePixels(pFrame, pTexture, pTile, false);
        pTexture->nData0 = nData0;
        pTexture->nData1 = nData1;
        pTexture->nData2 = nData2;
        pTexture->nData3 = nData3;

        if (pFrame->nAddressLoad == -1) {
            pTexture->nAddress = 0;
        } else {
            pTexture->nAddress = pFrame->nAddressLoad;
        }
        if (pTextureLast == NULL) {
            pFrame->apTextureCached[iTexture] = pTexture;
        } else {
            pTextureLast->pTextureNext = pTexture;
        }
    } else if (pTexture->iPackColor != -1 && pTexture->nCodeColor != pFrame->nTlutCode[pTile->iTLUT]) {
        frameMakePixels(pFrame, pTexture, pTile, true);
    }

    pTexture->nFrameLast = pFrame->nCountFrames;
    pTexture->nCodeColor = pFrame->nTlutCode[pTile->iTLUT];
    pTexture->nCodePixel = pTile->nCodePixel;

    if (!frameLoadTexture(pFrame, pTexture, iTileCode, pTile)) {
        return false;
    }

    if (ppTexture != NULL) {
        *ppTexture = pTexture;
    }

    if (bFlag) {
        pTile->nX0 = pTile->nY0 = pTile->nX1 = pTile->nY1 = 0;
    }
    return true;
}

bool frameDrawReset(Frame* pFrame, s32 nFlag) {
    pFrame->nFlag |= nFlag;
    pFrame->aDraw[0] = (FrameDrawFunc)frameDrawLine_Setup;
    pFrame->aDraw[1] = (FrameDrawFunc)frameDrawTriangle_Setup;
    pFrame->aDraw[2] = (FrameDrawFunc)frameDrawRectFill_Setup;
    pFrame->aDraw[3] = (FrameDrawFunc)frameDrawRectTexture_Setup;
    return true;
}

bool frameSetFill(Frame* pFrame, bool bFill) {
    if (bFill) {
        pFrame->nMode |= 0x20000;
    } else {
        pFrame->nMode &= ~0x20000;
    }
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetSize.s")
#else
bool frameSetSize(Frame* pFrame, FrameSize eSize, s32 nSizeX, s32 nSizeY) {
    if (nSizeX > 0 && nSizeY > 0) {
        pFrame->anSizeX[eSize] = nSizeX;
        pFrame->anSizeY[eSize] = nSizeY;
        if (eSize == FS_SOURCE) {
            pFrame->rScaleX = (f32)pFrame->anSizeX[FS_TARGET] / nSizeX;
            pFrame->rScaleY = (f32)pFrame->anSizeY[FS_TARGET] / nSizeY;
        } else if (eSize == FS_TARGET) {
            pFrame->rScaleX = (f32)nSizeX / pFrame->anSizeX[FS_SOURCE];
            pFrame->rScaleY = (f32)nSizeY / pFrame->anSizeY[FS_SOURCE];
        }
    }

    return true;
}
#endif

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetMode.s")
#else
bool frameSetMode(Frame* pFrame, FrameModeType eType, u32 nMode) {
    u32 nFlag;
    u32 nModeChanged;

    if (pFrame->nMode & (1 << eType)) {
        nModeChanged = pFrame->aMode[eType] ^ nMode;
    } else {
        nModeChanged = 0xFFFFFFFF;
        *((volatile u32*)&pFrame->nMode) |= (1 << eType);
    }

    nFlag = 0;
    switch (eType) {
        case FMT_FOG:
            if (nModeChanged != 0) {
                nFlag |= 0x20;
            }
            break;
        case FMT_GEOMETRY:
            if ((nModeChanged & 0x10) != 0) {
                nFlag |= 0x20;
            }
            if ((nModeChanged & 1) != 0) {
                nFlag |= 4;
            }
            if ((nModeChanged & 0xC) != 0) {
                nFlag |= 8;
            }
            if ((nModeChanged & 0x180) != 0) {
                nFlag |= 2;
            }
            break;
        case FMT_TEXTURE1:
            if (nModeChanged != 0) {
                nFlag |= 0x7C01;
            }
            break;
        case FMT_TEXTURE2:
            if (nModeChanged != 0) {
                nFlag |= 0x7D01;
            }
            break;
        case FMT_OTHER0:
            nFlag |= 0x200;
            if ((nModeChanged & 3) != 0) {
                nFlag |= 0x7C00;
            }
            if ((nModeChanged & 0xF0) != 0) {
                nFlag |= 4;
            }
            if ((nModeChanged & 0xC00) != 0) {
                nFlag |= 0x40000 | 4;
            }
            if ((nModeChanged & 0xFFFF0000) != 0) {
                nFlag |= 0x7C00;
            }
            break;
        case FMT_OTHER1:
            if (nModeChanged != 0) {
                nFlag |= 0x7F01;
            }
            break;
        case FMT_COMBINE_COLOR1:
        case FMT_COMBINE_COLOR2:
        case FMT_COMBINE_ALPHA1:
        case FMT_COMBINE_ALPHA2:
            if (nModeChanged != 0) {
                nFlag |= 0x7D00;
            }
            break;
        default:
            break;
    }

    if (nFlag != 0) {
        frameDrawReset(pFrame, nFlag);
    }

    pFrame->aMode[eType] = nMode;
    return true;
}
#endif

bool frameGetMode(Frame* pFrame, FrameModeType eType, u32* pnMode) {
    *pnMode = pFrame->aMode[eType];
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetMatrix.s")
#else
bool frameSetMatrix(Frame* pFrame, Mtx44 matrix, FrameMatrixType eType, bool bLoad, bool bPush, s32 nAddressN64) {
    s32 pad1;
    bool bFlag;
    Mtx44Ptr matrixTarget;
    Mtx44 matrixResult;
    s32 pad2[9];

    OSGetTick();

    switch (eType) {
        case FMT_MODELVIEW:
            if (!bLoad && (pFrame->nMode & 0x800000)) {
                bFlag = true;
                PSMTX44Concat(matrix, pFrame->aMatrixModel[pFrame->iMatrixModel], matrixResult);
            } else {
                bFlag = false;
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
                    return false;
                }
                bLoad = false;
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
            return false;
    }

    return true;
}
#endif

bool frameGetMatrix(Frame* pFrame, Mtx44 matrix, FrameMatrixType eType, bool bPull) {
    switch (eType) {
        case FMT_MODELVIEW:
            if (matrix != NULL) {
                if (!xlHeapCopy(matrix, pFrame->aMatrixModel[pFrame->iMatrixModel], sizeof(Mtx44))) {
                    return false;
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
                        return false;
                    }
                }
            }
            break;
        default:
            return false;
    }

    return true;
}

// TODO: move these paired-single/quantization functions to a separate header
// along with the GQR initialization in xlMain()?
static inline void s16tof32(register s16* in, register f32* out) { OSs16tof32(in, out); }

static inline void s16tof32Pair(register s16* in, register f32* out) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l f1, 0(in), 0, OS_FASTCAST_S16
        psq_st f1, 0(out), 0, 0
    }
    // clang-format on
#else
    out[0] = (f32)in[0];
    out[1] = (f32)in[1];
#endif
}

static inline void s8tof32Scaled128(register s8* in, register f32* out) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l f1, 0(in), 1, 6
        stfs  f1, 0(out)
    }
    // clang-format on
#else
    *out = (f32)*in / 128.0f;
#endif
}

static inline void s8tof32Scaled128Pair(register s8* in, register f32* out) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l f1, 0(in), 0, 6
        psq_st f1, 0(out), 0, 0
    }
    // clang-format on
#else
    out[0] = (f32)in[0] / 128.0f;
    out[1] = (f32)in[1] / 128.0f;
#endif
}

static inline void s16tof32Scaled32Pair(register s16* src, register f32* dst) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l f1, 0(src), 0, 7
        psq_st f1, 0(dst), 0, 0
    }
    // clang-format on
#else
    dst[0] = (f32)src[0] / 32.0f;
    dst[1] = (f32)src[1] / 32.0f;
#endif
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameLoadVertex.s")
#else
bool frameLoadVertex(Frame* pFrame, void* pBuffer, s32 iVertex0, s32 nCount) {
    f32 mag;
    s32 iLight;
    s32 nLight;
    s32 nTexGen;
    f32 colorS;
    f32 colorT;
    f32 rS;
    f32 rT;
    f32 arNormal[3];
    f32 arPosition[3];
    Vertex* pVertex;
    u32 nData32;
    Light* aLight;
    Light* pLight;
    s32 iVertex1;
    // f32 rScale;
    // f32 rScaleST;
    s8* pnData8;
    s16* pnData16;
    Mtx44Ptr matrixView;
    Mtx44Ptr matrixModel;
    f32 rColorR;
    f32 rColorG;
    f32 rColorB;
    f32 rDiffuse;
    f32 rInverseW;
    f32 rInverseLength;
    Vec3f vec;
    f32 distance;

    pnData8 = pBuffer;
    pnData16 = pBuffer;
    iVertex1 = iVertex0 + nCount - 1;
    if (iVertex0 < 0 || iVertex0 >= 80 || iVertex1 < 0 || iVertex1 >= 80) {
        return false;
    }

    matrixModel = pFrame->aMatrixModel[pFrame->iMatrixModel];
    if (pFrame->nMode & 0x08000000) {
        // TODO: volatile hacks
        if (!(*(volatile u32*)&pFrame->nMode & 0x400000)) {
            PSMTX44Concat(matrixModel, pFrame->matrixProjectionExtra, pFrame->matrixView);
            pFrame->nMode |= 0x400000;
            if (pFrame->iHintProjection != -1) {
                if (!frameScaleMatrix(pFrame->matrixView, pFrame->matrixView,
                                      pFrame->aMatrixHint[pFrame->iHintProjection].rScale)) {
                    return false;
                }
            }
        }
        matrixView = pFrame->matrixView;
        // TODO: volatile hacks
    } else if (!(*(volatile u32*)&pFrame->nMode & 0x400000) && pFrame->iHintProjection != -1) {
        if (!frameScaleMatrix(pFrame->matrixView, matrixModel, pFrame->aMatrixHint[pFrame->iHintProjection].rScale)) {
            return false;
        }
        pFrame->nMode |= 0x400000;
        matrixView = pFrame->matrixView;
    } else {
        matrixView = matrixModel;
    }

    if (pFrame->aMode[1] & 0x20) {
        nLight = pFrame->nCountLight;
        nTexGen = pFrame->aMode[1] & 0x180;
        aLight = pFrame->aLight;

        for (iLight = 0; iLight < nLight; iLight++) {
            pLight = &aLight[iLight];
            if (!pLight->bTransformed || !(pFrame->nMode & 0x200000)) {
                PSMTX44MultVecNoW(matrixModel, &pLight->rVecOrigTowards, &vec);
                rInverseLength = _inv_sqrtf(SQ(vec.x) + SQ(vec.y) + SQ(vec.z));
                pLight->rVectorX = vec.x * rInverseLength;
                pLight->rVectorY = vec.y * rInverseLength;
                pLight->rVectorZ = vec.z * rInverseLength;
                pLight->bTransformed = true;
            }
        }

        if (nTexGen != 0 && (!pFrame->lookAt.bTransformed || !(pFrame->nMode & 0x200000))) {
            if (!(pFrame->nMode & 0x01000000)) {
                pFrame->lookAt.rSRaw.x = 0.0f;
                pFrame->lookAt.rSRaw.y = 1.0f;
                pFrame->lookAt.rSRaw.z = 0.0f;
            }
            if (!(pFrame->nMode & 0x02000000)) {
                pFrame->lookAt.rTRaw.x = 1.0f;
                pFrame->lookAt.rTRaw.y = 0.0f;
                pFrame->lookAt.rTRaw.z = 0.0f;
            }
            PSMTX44MultVecNoW(matrixModel, &pFrame->lookAt.rSRaw, &pFrame->lookAt.rS);
            PSMTX44MultVecNoW(matrixModel, &pFrame->lookAt.rTRaw, &pFrame->lookAt.rT);

            mag = SQ(pFrame->lookAt.rS.x) + SQ(pFrame->lookAt.rS.y) + SQ(pFrame->lookAt.rS.z);
            if (mag > 0.0f) {
                rInverseLength = _inv_sqrtf(mag);
                pFrame->lookAt.rS.x *= rInverseLength;
                pFrame->lookAt.rS.y *= rInverseLength;
                pFrame->lookAt.rS.z *= rInverseLength;
            }

            mag = SQ(pFrame->lookAt.rT.x) + SQ(pFrame->lookAt.rT.y) + SQ(pFrame->lookAt.rT.z);
            if (mag > 0.0f) {
                rInverseLength = _inv_sqrtf(mag);
                pFrame->lookAt.rT.x *= rInverseLength;
                pFrame->lookAt.rT.y *= rInverseLength;
                pFrame->lookAt.rT.z *= rInverseLength;
            }

            pFrame->lookAt.bTransformed = true;
        }
        pFrame->nMode |= 0x200000;
    } else {
        nTexGen = 0;
        nLight = 0;
    }

    pVertex = &pFrame->aVertex[iVertex0];
    while (nCount-- != 0) {
        s16tof32Pair(&pnData16[0], &arPosition[0]);
        s16tof32(&pnData16[2], &arPosition[2]);

        pVertex->rSum = arPosition[0] + arPosition[1] + arPosition[2];
        rInverseW = 1.0f / (matrixView[0][3] * arPosition[0] + matrixView[1][3] * arPosition[1] +
                            matrixView[2][3] * arPosition[2] + matrixView[3][3]);
        pVertex->vec.x = rInverseW * (arPosition[0] * matrixView[0][0] + arPosition[1] * matrixView[1][0] +
                                      arPosition[2] * matrixView[2][0] + matrixView[3][0]);
        pVertex->vec.y = rInverseW * (arPosition[0] * matrixView[0][1] + arPosition[1] * matrixView[1][1] +
                                      arPosition[2] * matrixView[2][1] + matrixView[3][1]);
        pVertex->vec.z = rInverseW * (arPosition[0] * matrixView[0][2] + arPosition[1] * matrixView[1][2] +
                                      arPosition[2] * matrixView[2][2] + matrixView[3][2]);

        if (nLight != 0) {
            s8tof32Scaled128Pair(&pnData8[12], &arNormal[0]);
            s8tof32Scaled128(&pnData8[14], &arNormal[2]);

            iLight = nLight;
            pLight = &aLight[iLight];
            if (gpSystem->eTypeROM == SRT_STARFOX) {
                while ((rColorR = pLight->rColorR) + (rColorG = pLight->rColorG) + (rColorB = pLight->rColorB) ==
                       0.0f) {
                    pLight++;
                }
                pLight = &aLight[iLight];
            } else {
                rColorR = pLight->rColorR;
                rColorG = pLight->rColorG;
                rColorB = pLight->rColorB;
            }

            while (--iLight >= 0) {
                pLight--;
                if ((pFrame->aMode[1] & 0x800) && pLight->kc != 0.0f) {
                    distance = sqrtf(SQ(pLight->coordX - arPosition[0]) + SQ(pLight->coordY - arPosition[1]) +
                                     SQ(pLight->coordZ - arPosition[2]));
                    pLight->rVectorX = (pLight->coordX - arPosition[0]) / distance;
                    pLight->rVectorY = (pLight->coordY - arPosition[1]) / distance;
                    pLight->rVectorZ = (pLight->coordZ - arPosition[2]) / distance;
                    rDiffuse = (pLight->rVectorX * arNormal[0] + pLight->rVectorY * arNormal[1] +
                                pLight->rVectorZ * arNormal[2]) /
                               (pLight->kc + pLight->kl * distance + pLight->kq * distance * distance);
                    if (rDiffuse > 1.0f) {
                        rDiffuse = 1.0f;
                    }
                } else {
                    rDiffuse = pLight->rVectorX * arNormal[0] + pLight->rVectorY * arNormal[1] +
                               pLight->rVectorZ * arNormal[2];
                }

                if (rDiffuse > 0.0f) {
                    rColorR += pLight->rColorR * rDiffuse;
                    rColorG += pLight->rColorG * rDiffuse;
                    rColorB += pLight->rColorB * rDiffuse;
                }
            }

            OSf32tou8(&rColorR, &pVertex->anColor[0]);
            OSf32tou8(&rColorG, &pVertex->anColor[1]);
            OSf32tou8(&rColorB, &pVertex->anColor[2]);
            pVertex->anColor[3] = pnData8[15];

            if (nTexGen != 0) {
                rS = arNormal[0] * pFrame->lookAt.rS.x + arNormal[1] * pFrame->lookAt.rS.y +
                     arNormal[2] * pFrame->lookAt.rS.z;
                rT = arNormal[0] * pFrame->lookAt.rT.x + arNormal[1] * pFrame->lookAt.rT.y +
                     arNormal[2] * pFrame->lookAt.rT.z;
                if (nTexGen & 0x100) {
                    colorS = rS * rS * rS;
                    colorS = (0.22673f * colorS) + colorS;
                    rS = ((1.0f / (f32)M_PI) * rS) + colorS;
                    colorT = rT * rT * rT;
                    colorT = (0.22673f * colorT) + colorT;
                    rT = ((1.0f / (f32)M_PI) * rT) + colorT;
                } else {
                    rS *= 0.5f;
                    rT *= 0.5f;
                }
                pVertex->rS = rS + 0.5f;
                pVertex->rT = rT + 0.5f;
            }
        } else {
            nData32 = *(u32*)&pnData8[12];
            pVertex->anColor[0] = nData32 >> 24;
            pVertex->anColor[1] = nData32 >> 16;
            pVertex->anColor[2] = nData32 >> 8;
            pVertex->anColor[3] = nData32;
            if (nTexGen != 0) {
                s8tof32Scaled128Pair(&pnData8[12], &arNormal[0]);
                s8tof32Scaled128(&pnData8[14], &arNormal[2]);

                rS = arNormal[0] * pFrame->lookAt.rS.x + arNormal[1] * pFrame->lookAt.rS.y +
                     arNormal[2] * pFrame->lookAt.rS.z;
                rT = arNormal[0] * pFrame->lookAt.rT.x + arNormal[1] * pFrame->lookAt.rT.y +
                     arNormal[2] * pFrame->lookAt.rT.z;

                if (nTexGen & 0x100) {
                    colorS = rS * rS * rS;
                    colorS = (0.22673f * colorS) + colorS;
                    rS = ((1.0f / (f32)M_PI) * rS) + colorS;
                    colorT = rT * rT * rT;
                    colorT = (0.22673f * colorT) + colorT;
                    rT = ((1.0f / (f32)M_PI) * rT) + colorT;
                } else {
                    rS *= 0.5f;
                    rT *= 0.5f;
                }

                pVertex->rS = rS + 0.5f;
                pVertex->rT = rT + 0.5f;
            }
        }

        if (nTexGen == 0) {
            s16tof32Scaled32Pair(&pnData16[4], &pVertex->rS);
        }

        pVertex++;
        pnData8 += 0x10;
        pnData16 += 0x8;
    }

    return true;
}
#endif

bool frameCullDL(Frame* pFrame, s32 nVertexStart, s32 nVertexEnd) {
    f32 rX;
    f32 rY;
    f32 rZ;
    f32 rW;
    Mtx44Ptr matrix;
    Vertex* vtxP;
    Vertex* endVtxP;
    s32 nCode;
    s32 nCodeFull;

    matrix = pFrame->matrixProjection;
    vtxP = &pFrame->aVertex[nVertexStart];
    endVtxP = &pFrame->aVertex[nVertexEnd];
    nCodeFull = 0xFF;

    for (; vtxP <= endVtxP; vtxP++) {
        rX = vtxP->vec.x * matrix[0][0] + vtxP->vec.y * matrix[1][0] + vtxP->vec.z * matrix[2][0] + matrix[3][0];
        rY = vtxP->vec.x * matrix[0][1] + vtxP->vec.y * matrix[1][1] + vtxP->vec.z * matrix[2][1] + matrix[3][1];
        rZ = vtxP->vec.x * matrix[0][2] + vtxP->vec.y * matrix[1][2] + vtxP->vec.z * matrix[2][2] + matrix[3][2];
        rW = vtxP->vec.x * matrix[0][3] + vtxP->vec.y * matrix[1][3] + vtxP->vec.z * matrix[2][3] + matrix[3][3];

        nCode = 0;
        if (rX < -rW) {
            nCode |= 0x01;
        }
        if (rX > rW) {
            nCode |= 0x02;
        }
        if (rY < -rW) {
            nCode |= 0x04;
        }
        if (rY > rW) {
            nCode |= 0x08;
        }
        if (rZ < -rW) {
            nCode |= 0x10;
        }
        if (rZ > rW) {
            nCode |= 0x20;
        }

        nCodeFull &= nCode;
        if (nCodeFull == 0) {
            return false;
        }
    }

    return true;
}

bool frameLoadTLUT(Frame* pFrame, s32 nCount, s32 iTile) {
    s32 iTMEM = pFrame->aTile[iTile].nTMEM & 0x1FF;
    s32 nSize = nCount + 1;
    u32 nSum = 0;
    u64 nData64;
    u16 nData16;
    u16* pSource = pFrame->aBuffer[FBT_IMAGE].pData;
    s32 tileNum;

    while (nSize-- != 0) {
        nData16 = *pSource;
        pSource++;

        nSum += nData16 ^ iTMEM;
        nData64 = (nData16 << 16) | nData16;
        nData64 = (nData64 << 32) | nData64;
        pFrame->TMEM.data.u64[iTMEM] = nData64;
        iTMEM = (iTMEM + 1) & 0x1FF;
    }

    tileNum = pFrame->aTile[iTile].nTMEM & 0x1FF;
    tileNum -= 0x100;
    tileNum /= 16;
    tileNum &= 0xF;

    pFrame->nTlutCode[tileNum] = nSum;

    return true;
}

#pragma GLOBAL_ASM("asm/non_matchings/frame/frameLoadTMEM.s")

bool frameSetLightCount(Frame* pFrame, s32 nCount) {
    pFrame->nCountLight = nCount;
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetLight.s")
#else
bool frameSetLight(Frame* pFrame, s32 iLight, s8* pData) {
    Light* pLight;

    if (iLight >= 0 && iLight < 8) {
        pLight = &pFrame->aLight[iLight];
        pLight->bTransformed = false;

        if (pData[3] != 0) {
            pLight->kc = (u8)pData[3] * 0.0078125f + 0.0625f;
            pLight->kl = (u8)pData[7] / 4096.0f;
            pLight->kq = (u8)pData[14] / 4194304.0f;
            pLight->coordX = *(s16*)&pData[8];
            pLight->coordY = *(s16*)&pData[10];
            pLight->coordZ = *(s16*)&pData[12];
        } else {
            pLight->kc = 0.0f;
        }

        OSu8tof32((u8*)&pData[0], &pLight->rColorR);
        OSu8tof32((u8*)&pData[1], &pLight->rColorG);
        OSu8tof32((u8*)&pData[2], &pLight->rColorB);

        s8tof32Scaled128(&pData[8], &pLight->rVecOrigTowards.x);
        s8tof32Scaled128(&pData[9], &pLight->rVecOrigTowards.y);
        s8tof32Scaled128(&pData[10], &pLight->rVecOrigTowards.z);
        return true;
    } else {
        return false;
    }
}
#endif

bool frameSetLookAt(Frame* pFrame, s32 iLookAt, s8* pData) {
    switch (iLookAt) {
        case 0:
            s8tof32Scaled128(&pData[8], &pFrame->lookAt.rSRaw.x);
            s8tof32Scaled128(&pData[9], &pFrame->lookAt.rSRaw.y);
            s8tof32Scaled128(&pData[10], &pFrame->lookAt.rSRaw.z);
            pFrame->nMode |= 0x01000000;
            break;
        case 1:
            s8tof32Scaled128(&pData[8], &pFrame->lookAt.rTRaw.x);
            s8tof32Scaled128(&pData[9], &pFrame->lookAt.rTRaw.y);
            s8tof32Scaled128(&pData[10], &pFrame->lookAt.rTRaw.z);
            pFrame->nMode |= 0x02000000;
            break;
        default:
            return false;
    }

    pFrame->lookAt.bTransformed = false;
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetViewport.s")
#else
bool frameSetViewport(Frame* pFrame, s16* pData) {
    s32 iScale;
    f32 arScale[3];
    f32 centerX;
    f32 centerY;
    f32 rX;
    f32 rY;
    f32 rSizeX;
    f32 rSizeY;
    s32 pad[3];

    arScale[0] = pData[0] / 4.0f;
    arScale[1] = pData[1] / 4.0f;
    arScale[2] = pData[2] / 4.0f;

    for (iScale = 0; iScale < 3; iScale++) {
        if (arScale[iScale] < 0.0f) {
            arScale[iScale] = -arScale[iScale];
        }
    }

    rSizeX = (arScale[0] * 2.0f) * pFrame->rScaleX;
    rSizeY = (arScale[1] * 2.0f) * pFrame->rScaleY;

    centerX = pData[4] / 4.0f;
    centerY = pData[5] / 4.0f;

    rX = (centerX - arScale[0]) * pFrame->rScaleX;
    rY = (centerY - arScale[1]) * pFrame->rScaleY;

    pFrame->viewport.rX = rX;
    pFrame->viewport.rY = rY;
    pFrame->viewport.rSizeX = rSizeX;
    pFrame->viewport.rSizeY = rSizeY;

    frameDrawReset(pFrame, 0x10000);
    return true;
}
#endif

bool frameResetUCode(Frame* pFrame, FrameResetType eType) {
    s32 iMode;

    pFrame->iMatrixModel = 0;
    pFrame->nMode &= 0x9C1F0000;
    if (eType == FRT_COLD) {
        pFrame->nMode &= ~0x1C000000;
        pFrame->iHintProjection = -1;
    }

    for (iMode = 0; iMode < ARRAY_COUNT(pFrame->aMode); iMode++) {
        pFrame->aMode[iMode] = 0;
    }

    pFrame->nWidthLine = -1;
    pFrame->nCountLight = 0;
    return true;
}

bool frameSetBuffer(Frame* pFrame, FrameBufferType eType) {
    if (eType == FBT_COLOR_SHOW || eType == FBT_COLOR_DRAW) {
    } else if (eType == FBT_DEPTH) {
        pFrame->nOffsetDepth0 = pFrame->aBuffer[FBT_DEPTH].nAddress & 0x03FFFFFF;
        pFrame->nOffsetDepth1 = pFrame->nOffsetDepth0 + 0x257FC;
    }

    return true;
}

bool frameFixMatrixHint(Frame* pFrame, s32 nAddressFloat, s32 nAddressFixed) {
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

            return true;
        }
    }

    return false;
}

static inline bool frameGetMatrixHint(Frame* pFrame, u32 nAddress, s32* piHint) {
    s32 iHint;

    for (iHint = 0; iHint < pFrame->iHintMatrix; iHint++) {
        if (pFrame->aMatrixHint[iHint].nAddressFixed == nAddress && pFrame->aMatrixHint[iHint].nCount >= 0) {
            pFrame->aMatrixHint[iHint].nCount = 4;
            *piHint = iHint;
            return true;
        }
    }

    return false;
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameSetMatrixHint.s")
#else
bool frameSetMatrixHint(Frame* pFrame, FrameMatrixProjection eProjection, s32 nAddressFloat, s32 nAddressFixed,
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
        rNear = 0.0f;
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
    return true;
}
#endif

bool frameInvalidateCache(Frame* pFrame, s32 nOffset0, s32 nOffset1) {
    s32 iTexture0;
    s32 iTexture1;
    FrameTexture* pTexture;
    FrameTexture* pTextureNext;

    iTexture0 = (nOffset0 & 0x7FFFFF) / 2048;
    iTexture1 = (nOffset1 & 0x7FFFFF) / 2048;
    while (iTexture0 <= iTexture1) {
        pTexture = pFrame->apTextureCached[iTexture0];
        while (pTexture != NULL) {
            pTextureNext = pTexture->pTextureNext;
            if (!frameFreeTexture(pFrame, pTexture)) {
                return false;
            }
            pTexture = pTextureNext;
        }
        pFrame->apTextureCached[iTexture0] = NULL;
        iTexture0 += 1;
    }

    return true;
}

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/frame/frameGetTextureInfo.s")
#else
bool frameGetTextureInfo(Frame* pFrame, TextureInfo* pInfo) {
    FrameTexture* pTexture;
    s32 iTexture;
    s32 nCount;
    s32 nSize;

    nSize = 0;
    nCount = 0;
    iTexture = 0;

    for (iTexture = 0; iTexture < ARRAY_COUNT(pFrame->apTextureCached); iTexture++) {
        pTexture = pFrame->apTextureCached[iTexture];

        while (pTexture != NULL) {
            nCount++;
            switch ((s32)pTexture->eFormat) {
                case GX_TF_I4:
                case GX_TF_C4:
                    nSize += ((pTexture->nSizeX * pTexture->nSizeY) + 1) >> 1;
                    break;
                case GX_TF_I8:
                case GX_TF_IA4:
                case GX_TF_C8:
                    nSize += pTexture->nSizeX * pTexture->nSizeY;
                    break;
                case GX_TF_IA8:
                case GX_TF_RGB565:
                case GX_TF_RGB5A3:
                    nSize += pTexture->nSizeX * pTexture->nSizeY * 2;
                    break;
                case GX_TF_RGBA8:
                    nSize += pTexture->nSizeX * pTexture->nSizeY * 4;
                    break;
                default:
                    OSReport("GetTextureInfo: Unknown texture-format: %d\n", pTexture->eFormat);
                    return false;
            }
            pTexture = pTexture->pTextureNext;
        }
    }

    pInfo->nSizeTextures = nSize + (nCount * sizeof(FrameTexture));
    pInfo->nCountTextures = nCount;
    return true;
}
#endif

ASM void PSMTX44MultVecNoW(Mtx44 m, Vec3f* src, Vec3f* dst) {
#ifdef __MWERKS__ // clang-format off
    nofralloc

    psq_l   f0, 0(r4), 0, 0
    psq_l   f1, 8(r4), 1, 0
    psq_l   f4, 0(r3), 0, 0
    psq_l   f5, 8(r3), 0, 0
    psq_l   f6, 16(r3), 0, 0
    psq_l   f7, 24(r3), 0, 0
    psq_l   f8, 32(r3), 0, 0
    psq_l   f9, 40(r3), 0, 0
    ps_mul  f4, f0, f4
    ps_madd f2, f1, f5, f4
    ps_mul  f6, f0, f6
    ps_madd f3, f1, f7, f6
    ps_mul  f8, f0, f8
    ps_sum0 f2, f2, f2, f2
    ps_madd f9, f1, f9, f8
    ps_sum1 f2, f3, f2, f3
    ps_sum0 f3, f9, f9, f9
    psq_st  f2, 0(r5), 0, 0
    psq_st  f3, 8(r5), 1, 0
    blr
#endif // clang-format on
}
