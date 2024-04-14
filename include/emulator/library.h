#ifndef _LIBRARY_H
#define _LIBRARY_H

#include "dolphin.h"
#include "emulator/cpu.h"
#include "emulator/xlObject.h"

typedef void (*LibraryFuncImpl)(Cpu*);

// __anon_0x7AD10
typedef struct LibraryFunc {
    /* 0x0 */ char* szName;
    /* 0x4 */ LibraryFuncImpl pfLibrary;
    /* 0x8 */ u32 anData[17];
} LibraryFunc; // size = 0x4C

// __anon_0x7AE26
typedef struct Library {
    /* 0x00 */ s32 nFlag;
    /* 0x04 */ void* pHost;
    /* 0x08 */ s32 nAddStackSwap;
    /* 0x0C */ s32 nCountFunction;
    /* 0x10 */ s32 nAddressException;
    /* 0x14 */ LibraryFunc* aFunction;
    /* 0x18 */ void* apData[10];
    /* 0x40 */ s32 anAddress[10];
} Library; // size = 0x68

s32 send_mesg(Cpu* pCPU);
s32 __osEnqueueAndYield(Cpu* pCPU);
s32 __osEnqueueThread(Cpu* pCPU);
s32 __osPopThread(Cpu* pCPU);
s32 __osDispatchThread(Cpu* pCPU);
s32 osGetMemSize(Cpu* pCPU);
s32 osInvalDCache(Cpu* pCPU);
s32 osInvalICache(Cpu* pCPU);
s32 osWritebackDCache(Cpu* pCPU);
s32 osWritebackDCacheAll(Cpu* pCPU);
s32 __osDisableInt(Cpu* pCPU);
s32 __osRestoreInt(Cpu* pCPU);
s32 __osSpSetStatus(Cpu* pCPU);
void __cosf(Cpu* pCPU);
void __sinf(Cpu* pCPU);
void _bzero(Cpu* pCPU);
void _bcopy(Cpu* pCPU);
void _memcpy(Cpu* pCPU);
void osVirtualToPhysical(Cpu* pCPU);
void osPhysicalToVirtual(Cpu* pCPU);
void guMtxF2L(Cpu* pCPU);
void guMtxCatF(Cpu* pCPU);
void guMtxIdentF(Cpu* pCPU);
void guMtxIdent(Cpu* pCPU);
void guOrthoF(Cpu* pCPU);
void guOrtho(Cpu* pCPU);
void guPerspectiveF(Cpu* pCPU);
void guPerspective(Cpu* pCPU);
void guScaleF(Cpu* pCPU);
void guScale(Cpu* pCPU);
void guRotateF(Cpu* pCPU);
void guRotate(Cpu* pCPU);
void guTranslateF(Cpu* pCPU);
void guTranslate(Cpu* pCPU);
void guLookAtF(Cpu* pCPU);
void guLookAt(Cpu* pCPU);
void guLookAtHiliteF(Cpu* pCPU);
void guLookAtHilite(Cpu* pCPU);
void guLookAtReflectF(Cpu* pCPU);
void guLookAtReflect(Cpu* pCPU);
s32 osAiSetFrequency(Cpu* pCPU);
s32 osAiSetNextBuffer(Cpu* pCPU);
s32 __osEepStatus(Cpu* pCPU);
s32 osEepromRead(Cpu* pCPU);
s32 osEepromWrite(Cpu* pCPU);
s32 osEepromLongRead(Cpu* pCPU);
s32 osEepromLongWrite(Cpu* pCPU);
s32 starfoxCopy(Cpu* pCPU);
s32 GenPerspective_1080(Cpu* pCPU);
s32 pictureSnap_Zelda2(Cpu* pCPU);
s32 dmaSoundRomHandler_ZELDA1(Cpu* pCPU);
s32 osViSwapBuffer_Entry(Cpu* pCPU);
s32 zeldaLoadSZS_Entry(Cpu* pCPU);
s32 zeldaLoadSZS_Exit(Cpu* pCPU);

s32 libraryTestFunction(Library* pLibrary, CpuFunction* pFunction);
s32 libraryFunctionReplaced(Library* pLibrary, s32 iFunction);
s32 libraryCall(Library* pLibrary, Cpu* pCPU, s32 iFunction);
s32 libraryEvent(Library* pLibrary, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassLibrary;

#endif
