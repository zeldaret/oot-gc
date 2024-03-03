#ifndef _LIBRARY_H
#define _LIBRARY_H

#include "cpu.h"
#include "dolphin.h"
#include "xlObject.h"

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

void send_mesg(Cpu* pCPU);
void __osEnqueueAndYield(Cpu* pCPU);
void __osEnqueueThread(Cpu* pCPU);
void __osPopThread(Cpu* pCPU);
void __osDispatchThread(Cpu* pCPU);
void osGetMemSize(Cpu* pCPU);
void osInvalDCache(Cpu* pCPU);
void osInvalICache(Cpu* pCPU);
void osWritebackDCache(Cpu* pCPU);
void osWritebackDCacheAll(Cpu* pCPU);
void __osDisableInt(Cpu* pCPU);
void __osRestoreInt(Cpu* pCPU);
void __osSpSetStatus(Cpu* pCPU);
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
void osAiSetFrequency(Cpu* pCPU);
void osAiSetNextBuffer(Cpu* pCPU);
void __osEepStatus(Cpu* pCPU);
void osEepromRead(Cpu* pCPU);
void osEepromWrite(Cpu* pCPU);
void osEepromLongRead(Cpu* pCPU);
void osEepromLongWrite(Cpu* pCPU);
void starfoxCopy(Cpu* pCPU);
void GenPerspective_1080(Cpu* pCPU);
void pictureSnap_Zelda2(Cpu* pCPU);
void dmaSoundRomHandler_ZELDA1(Cpu* pCPU);
void osViSwapBuffer_Entry(Cpu* pCPU);
void zeldaLoadSZS_Entry(Cpu* pCPU);
void zeldaLoadSZS_Exit(Cpu* pCPU);

s32 libraryTestFunction(Library* pLibrary, CpuFunction* pFunction);
s32 libraryEvent(Library* pLibrary, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassLibrary;

#endif
