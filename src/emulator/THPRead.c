#include "emulator/THPRead.h"
#include "emulator/THPRead_jumptables.h"
#include "macros.h"

const f32 D_800D3130[12] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D3160[12] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D3190[12] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

char D_800EA4B0[] = "Can't create read thread\n";

void* jtbl_800EA4CC[] = {
    &lbl_80011F4C, &lbl_80011F70, &lbl_80011F70, &lbl_80011F70, &lbl_80011F70, &lbl_80011F54, &lbl_80011F5C,
    &lbl_80011F64, &lbl_80011F70, &lbl_80011F70, &lbl_80011F70, &lbl_80011F70, &lbl_80011F6C,
};

void* jtbl_800EA500[] = {
    &lbl_8001219C, &lbl_800121D4, &lbl_8001220C, &lbl_8001227C, &lbl_80012244, &lbl_800122B4, &lbl_800122EC,
};

static OSMessageQueue FreeReadBufferQueue;
static OSMessageQueue ReadedBufferQueue;
static OSMessageQueue ReadedBufferQueue2;
static void* FreeReadBufferMessage[10];
static void* ReadedBufferMessage[10];
static void* ReadedBufferMessage2[10];
static OSThread ReadThread;
static u8 ReadThreadStack[4096];
f32 gOrthoMtx[4][4];

//! TODO: make static (data ordering issues)
// and remove prefix (there's other global variables sharing the same name)
u32 gnTickReset_thpread;
s32 gbReset_thpread;
s32 toggle_184;

s32 gMovieErrorToggle;
s32 ReadThreadCreated;

const s32 D_80135DA0 = 0x00000000;
const s32 D_80135DA4 = 0x00000000;
const s32 D_80135DA8 = 0x00000000;
const f32 D_80135DAC = 0.5;
const f64 D_80135DB0 = 4503599627370496.0;
const f32 D_80135DB8 = 0.0;
const f32 D_80135DBC = 240.0;
const f32 D_80135DC0 = 320.0;
const f32 D_80135DC4 = 0.10000000149011612;
const f32 D_80135DC8 = 10000.0;
const f32 D_80135DCC = 160.0;
const f32 D_80135DD0 = 120.0;
const f32 D_80135DD4 = 1.0;

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieGXInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieDrawImage.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieDrawErrorMessage.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieDVDShowError.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieDVDRead.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieTestReset.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieReset.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/CreateReadThread.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/ReadThreadStart.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/Reader.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/PopReadedBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/PushFreeReadBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/PopReadedBuffer2.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPRead/PushReadedBuffer2.s")
