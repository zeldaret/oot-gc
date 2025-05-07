#ifndef _METROTRK_PPC_TARGIMPL_H
#define _METROTRK_PPC_TARGIMPL_H

#include "dolphin/types.h"
#include "metrotrk/m7xx_m603e_reg.h"
#include "metrotrk/ppc_reg.h"
#include "metrotrk/trk.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TRKState_PPC {
    /* 0x00 */ DefaultType GPR[32];
    /* 0x80 */ DefaultType LR;
    /* 0x84 */ DefaultType CTR;
    /* 0x88 */ DefaultType XER;
    /* 0x8C */ Extended1Type MSR;
    /* 0x90 */ Extended1Type DAR;
    /* 0x94 */ Extended1Type DSISR;
    /* 0x98 */ bool stopped;
    /* 0x9C */ bool inputActivated;
    /* 0xA0 */ u8* inputPendingPtr;
} TRKState_PPC; // size = 0xA4

extern TRKState_PPC gTRKState;

typedef struct ProcessorRestoreFlags_PPC {
    /* 0x00 */ u8 TBR;
    /* 0x01 */ u8 DEC;
    /* 0x02 */ u8 linker_padding[9 - 2];
} ProcessorRestoreFlags_PPC; // size = 0x09

extern ProcessorRestoreFlags_PPC gTRKRestoreFlags;
extern ProcessorState_PPC gTRKCPUState;

u32 __TRK_get_MSR();
void __TRK_set_MSR(register u32 val);
u32 __TRK_get_PVR();
u32 __TRK_get_IBAT0U();
u32 __TRK_get_IBAT0L();
u32 __TRK_get_IBAT1U();
u32 __TRK_get_IBAT1L();
u32 __TRK_get_IBAT2U();
u32 __TRK_get_IBAT2L();
u32 __TRK_get_IBAT3U();
u32 __TRK_get_IBAT3L();
u32 __TRK_get_DBAT0U();
u32 __TRK_get_DBAT0L();
u32 __TRK_get_DBAT1U();
u32 __TRK_get_DBAT1L();
u32 __TRK_get_DBAT2U();
u32 __TRK_get_DBAT2L();
u32 __TRK_get_DBAT3U();
u32 __TRK_get_DBAT3L();

DSError TRKPPCAccessSPR(void* srcDestPtr, u32 spr, bool read);
DSError TRKPPCAccessPairedSingleRegister(void* srcDestPtr, u32 psr, bool read);
DSError TRKPPCAccessFPRegister(void* srcDestPtr, u32 fpr, bool read);
DSError TRKPPCAccessSpecialReg(void* srcDestPtr, u32* instructionData, bool read);
void TRKPostInterruptEvent();
u32 ConvertAddress(u32);

#ifdef __cplusplus
}
#endif

#endif
