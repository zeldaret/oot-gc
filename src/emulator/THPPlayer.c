#include "emulator/THPPlayer.h"
#include "macros.h"

u16 VolumeTable[128] = {
    0x0000, 0x0002, 0x0008, 0x0012, 0x0020, 0x0032, 0x0049, 0x0063, 0x0082, 0x00A4, 0x00CB, 0x00F5, 0x0124,
    0x0157, 0x018E, 0x01C9, 0x0208, 0x024B, 0x0292, 0x02DD, 0x032C, 0x037F, 0x03D7, 0x0432, 0x0492, 0x04F5,
    0x055D, 0x05C9, 0x0638, 0x06AC, 0x0724, 0x07A0, 0x0820, 0x08A4, 0x092C, 0x09B8, 0x0A48, 0x0ADD, 0x0B75,
    0x0C12, 0x0CB2, 0x0D57, 0x0DFF, 0x0EAC, 0x0F5D, 0x1012, 0x10CA, 0x1187, 0x1248, 0x130D, 0x13D7, 0x14A4,
    0x1575, 0x164A, 0x1724, 0x1801, 0x18E3, 0x19C8, 0x1AB2, 0x1BA0, 0x1C91, 0x1D87, 0x1E81, 0x1F7F, 0x2081,
    0x2187, 0x2291, 0x239F, 0x24B2, 0x25C8, 0x26E2, 0x2801, 0x2923, 0x2A4A, 0x2B75, 0x2CA3, 0x2DD6, 0x2F0D,
    0x3048, 0x3187, 0x32CA, 0x3411, 0x355C, 0x36AB, 0x37FF, 0x3956, 0x3AB1, 0x3C11, 0x3D74, 0x3EDC, 0x4048,
    0x41B7, 0x432B, 0x44A3, 0x461F, 0x479F, 0x4923, 0x4AAB, 0x4C37, 0x4DC7, 0x4F5C, 0x50F4, 0x5290, 0x5431,
    0x55D6, 0x577E, 0x592B, 0x5ADC, 0x5C90, 0x5E49, 0x6006, 0x61C7, 0x638C, 0x6555, 0x6722, 0x68F4, 0x6AC9,
    0x6CA2, 0x6E80, 0x7061, 0x7247, 0x7430, 0x761E, 0x7810, 0x7A06, 0x7C00, 0x7DFE, 0x8000,
};

char D_800EA2E8[] = "Pleae call AXInit or sndInit before you call THPPlayerInit\n";
char D_800EA324[] = "You must call THPPlayerInit before you call this function\n";
char D_800EA360[] = "Can't open %s because a thp file is already opened.\n";
char D_800EA398[] = "Can't open %s.\n";
char D_800EA3A8[] = "This file is not a THP file.\n";
char D_800EA3C8[] = "invalid version.\n";
char D_800EA3DC[] = "Unknown frame components.\n";
char D_800EA3F8[] = "This thp file doesn't have the offset data\n";
char D_800EA424[] = "Specified frame number is over total frame number\n";
char D_800EA458[] = "Specified audio track number is invalid\n";

static char gpErrorMessageBuffer[20480];

static s32 WorkBuffer[16];
static OSMessageQueue PrepareReadyQueue;
static OSMessageQueue UsedTextureSetQueue;
static void* UsedTextureSetMessage[3];
static s16 SoundBuffer[2][320] ALIGNAS(32);
__anon_0x10B6F ActivePlayer;

static char D_80134DB0[] = "THP";

static s32 Initialized;
static void* PrepareReadyMessage;
static void (*OldVIPostCallback)(u32);
static s32 SoundBufferIndex;
static void (*OldAIDCallback)();
static s16* LastAudioBuffer;
static s16* CurAudioBuffer;
static s32 AudioSystem;

const f32 D_80135D70 = 127.0;
const f32 D_80135D74 = 100.0;

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/MixAudio.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPAudioMixCallback.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPPlayerDrawDone.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/PushUsedTextureSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPPlayerDrawCurrentFrame.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/ProperTimingForGettingNextFrame.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/ProperTimingForStart.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/PlayControl.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPPlayerPlay.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPPlayerPrepare.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/PrepareReady.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/InitAllMessageQueue.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPPlayerSetBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPPlayerCalcNeedMemory.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPPlayerOpen.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPPlayer/THPPlayerInit.s")
