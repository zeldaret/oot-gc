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

s32 libraryTestFunction(Library* pLibrary, CpuFunction* pFunction);
s32 libraryFunctionReplaced(Library* pLibrary, s32 iFunction);
s32 libraryCall(Library* pLibrary, Cpu* pCPU, s32 iFunction);
s32 libraryEvent(Library* pLibrary, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassLibrary;

#endif
