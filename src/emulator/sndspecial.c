#include "dolphin/demo.h"
#include "dolphin/gx.h"
#include "dolphin/pad.h"
#include "dolphin/types.h"
#include "emulator/frame.h"
#include "emulator/simGCN.h"
#include "macros.h"

#define BUTTON_COMBO_HOLD (PAD_TRIGGER_Z | PAD_TRIGGER_R | PAD_TRIGGER_L)
#define CHAR_EMPTY 0x40

#include "special_data.inc"

static u16 sButtonOrder[18] = {
    PAD_BUTTON_UP,   PAD_BUTTON_UP,    PAD_BUTTON_DOWN, PAD_BUTTON_DOWN,  PAD_BUTTON_LEFT, PAD_BUTTON_RIGHT,
    PAD_BUTTON_LEFT, PAD_BUTTON_RIGHT, PAD_BUTTON_X,    PAD_BUTTON_Y,     PAD_BUTTON_B,    PAD_BUTTON_A,
    PAD_BUTTON_UP,   PAD_BUTTON_LEFT,  PAD_BUTTON_DOWN, PAD_BUTTON_RIGHT, PAD_BUTTON_A,    PAD_BUTTON_START,
};

// clang-format off
static u8 ImportantData[] = {
    // "CREDITS"
    7, 'C', 'R', 'E', 'D', 'I', 'T', 'S',

    1, CHAR_EMPTY,
    1, CHAR_EMPTY,
    1, CHAR_EMPTY,

    // "ENGINEERING"
    11, 'E', 'N', 'G', 'I', 'N', 'E', 'E', 'R', 'I', 'N', 'G',

    1, CHAR_EMPTY,
    1, CHAR_EMPTY,

    // "Robert Champagne"
    16, 'R', 'o', 'b', 'e', 'r', 't', ' ', 'C', 'h', 'a', 'm', 'p', 'a', 'g', 'n', 'e',

    // "David Devaty"
    12, 'D', 'a', 'v', 'i', 'd', ' ', 'D', 'e', 'v', 'a', 't', 'y',

    // "Rory Johnston"
    13, 'R', 'o', 'r', 'y', ' ', 'J', 'o', 'h', 'n', 's', 't', 'o', 'n',

    // "Stephen Lee"
    11, 'S', 't', 'e', 'p', 'h', 'e', 'n', ' ', 'L', 'e', 'e',

    // "YoonJoon Lee"
    12, 'Y', 'o', 'o', 'n', 'J', 'o', 'o', 'n', ' ', 'L', 'e', 'e',

    // "Max Szlagor"
    11, 'M', 'a', 'x', ' ', 'S', 'z', 'l', 'a', 'g', 'o', 'r',

    0
};
// clang-format on

static u16 sCurrButton;

static void DrawStuff(u8* dataP, s32 y) {
    s32 i;
    s32 length;
    s32 x;
    f32 tx;
    s32 id;
    f32 xscale;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    length = *dataP++;

    while (length > 0) {
        GXBegin(GX_QUADS, GX_VTXFMT0, length * 4);
        x = (N64_FRAME_WIDTH - length * 8) / 2;

        for (i = 0; i < length; i++) {
            id = *dataP++;
            xscale = 1.0f / 59.0f;
            tx = (id - CHAR_EMPTY) * xscale;

            GXPosition3f32(x, y, 0.0f);
            GXTexCoord2f32(tx, 0.0f);
            GXPosition3f32(x + 8, y, 0.0f);
            GXTexCoord2f32(tx + xscale, 0.0f);
            GXPosition3f32(x + 8, y + 8, 0.0f);
            GXTexCoord2f32(tx + xscale, 1.0f);
            GXPosition3f32(x, y + 8, 0.0f);
            GXTexCoord2f32(tx, 1.0f);
            x += 8;
        }

        GXEnd();
        y += 8;
        length = *dataP++;
    }

    GXPixModeSync();
}

static void DrawSpecialScreen(void) {
    GXColor color;
    Mtx matrix;
    static GXTexObj texObj;
    static GXTexObj texObj2;
    s32 pad[12];

    while (frameBeginOK(gpFrame) != 1) {}
    xlCoreBeforeRender();
    frameDrawSetup2D(gpFrame);

    // draw background
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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXEnd();

    // draw text
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
    GXLoadTexMtxImm(matrix, 0x1E, GX_MTX2x4);
    GXInitTexObj(&texObj, special_data, 472, 8, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    DrawStuff(ImportantData, 30);

    gpFrame->nMode = 0;
    gpFrame->nModeVtx = -1;
    frameDrawReset(gpFrame, 0x5FFED);
    simulatorDEMODoneRender();
}

void UpdateSpecial(void) {
    u16 buttons;
    u16 pressed;
    s32 pad;
    static u16 lastButtons;

    pressed = DemoPad->pst.button & (lastButtons ^ DemoPad->pst.button);
    buttons = DemoPad->pst.button;

    if ((DemoPad->pst.button & BUTTON_COMBO_HOLD) == BUTTON_COMBO_HOLD) {
        if (pressed == sButtonOrder[sCurrButton]) {
            sCurrButton += 1;
        } else if (pressed != 0) {
            sCurrButton = 0;
        }
    } else {
        sCurrButton = 0;
    }

    if (sCurrButton == ARRAY_COUNT(sButtonOrder)) {
        while (true) {
            DEMOPadRead();
            pressed = DemoPad->pst.button & (lastButtons ^ DemoPad->pst.button);
            buttons = DemoPad->pst.button;
            DrawSpecialScreen();

            if (pressed & PAD_BUTTON_B) {
                break;
            }

            lastButtons = buttons;
        }
    }

    lastButtons = buttons;
}
