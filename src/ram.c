#include "xlObject.h"
#include "ram.h"

int ramEvent(Ram* pRAM, int nEvent, void *pArgument);

_XL_OBJECTTYPE gClassRAM = {
    "RAM",
    sizeof(Ram),
    NULL,
    (EventFunc)ramEvent,
};

// temporary
void* jtbl_800ED6D8[] = {
    (void*)0x8006D2B0, (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2B0, (void*)0x8006D2A8, (void*)0x8006D2A8,
    (void*)0x8006D2A8, (void*)0x8006D2B0, (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2B0, (void*)0x8006D2A8,
    (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2B0, (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2B0,
    (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2B0, (void*)0x8006D2A8, (void*)0x8006D2A8, (void*)0x8006D2A8,
    (void*)0x8006D2B0,
};

void* jtbl_800ED74C[] = {
    (void*)0x8006D2FC, (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2FC, (void*)0x8006D2F4, (void*)0x8006D2F4,
    (void*)0x8006D2F4, (void*)0x8006D2FC, (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2FC, (void*)0x8006D2F4,
    (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2FC, (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2FC,
    (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2FC, (void*)0x8006D2F4, (void*)0x8006D2F4, (void*)0x8006D2F4,
    (void*)0x8006D2FC,
};

void* jtbl_800ED7C0[] = {
    (void*)0x8006D348, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D348, (void*)0x8006D340, (void*)0x8006D340,
    (void*)0x8006D340, (void*)0x8006D348, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D348, (void*)0x8006D340,
    (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D348, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D348,
    (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D348, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D340,
    (void*)0x8006D348, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D340, (void*)0x8006D348, (void*)0x8006D340, (void*)0x8006D340,
    (void*)0x8006D340, (void*)0x8006D348,
};

void* jtbl_800ED854[] = {
    (void*)0x8006D394, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D394, (void*)0x8006D38C, (void*)0x8006D38C,
    (void*)0x8006D38C, (void*)0x8006D394, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D394, (void*)0x8006D38C,
    (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D394, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D394,
    (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D394, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D38C,
    (void*)0x8006D394, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D38C, (void*)0x8006D394, (void*)0x8006D38C, (void*)0x8006D38C,
    (void*)0x8006D38C, (void*)0x8006D394,
};

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramEvent.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramSetSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramWipe.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetRI64.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetRI32.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetRI16.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetRI8.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPutRI64.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPutRI32.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPutRI16.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPutRI8.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetControl64.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetControl32.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetControl16.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramGetControl8.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPutControl64.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPutControl32.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPutControl16.s")

#pragma GLOBAL_ASM("asm/non_matchings/ram/ramPutControl8.s")
