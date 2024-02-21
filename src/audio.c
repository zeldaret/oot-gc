#include "audio.h"
#include "xlObject.h"

s32 audioEvent(Audio* pAudio, s32 nEvent, void* pArgument);

_XL_OBJECTTYPE gClassAudio = {
    "AUDIO",
    sizeof(Audio),
    NULL,
    (EventFunc)audioEvent,
};

char D_800EE788[] = "Get: DRAM Address: WRITE-ONLY?";
char D_800EE7A8[] = "Get: CONTROL: WRITE-ONLY?";

void* jtbl_800EE7C4[] = {
    (void*)0x8008E668,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E68C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E6B0,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E6D4,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E6F4,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E700,
};

void* jtbl_800EE818[] = {
    (void*)0x8008E780,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E7D8,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E810,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E820,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E834,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E860,
};

char D_80135310[8] = "audio.c";

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioEnable.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioEvent.s")
