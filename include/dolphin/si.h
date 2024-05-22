#ifndef _DOLPHIN_SI_H
#define _DOLPHIN_SI_H

#include "dolphin/hw_regs.h"
#include "dolphin/os.h"
#include "dolphin/types.h"

#define CHAN_NONE -1

#define SI_MAX_CHAN 4

#define SI_COMCSR_IDX 13
#define SI_STATUS_IDX 14

#define SI_COMCSR_TCINT_MASK (1 << 31)
#define SI_COMCSR_TCINTMSK_MASK (1 << 30)
#define SI_COMCSR_COMERR_MASK (1 << 29)
#define SI_COMCSR_RDSTINT_MASK (1 << 28)
#define SI_COMCSR_RDSTINTMSK_MASK (1 << 27)
// 4 bits of padding
#define SI_COMCSR_OUTLNGTH_MASK (1 << 22) | (1 << 21) | (1 << 20) | (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16)
// 1 bit of padding
#define SI_COMCSR_INLNGTH_MASK (1 << 14) | (1 << 13) | (1 << 12) | (1 << 11) | (1 << 10) | (1 << 9) | (1 << 8)
// 5 bits of padding
#define SI_COMCSR_CHANNEL_MASK (1 << 2) | (1 << 1)
#define SI_COMCSR_TSTART_MASK (1 << 0)

typedef void (*SICallback)(s32 chan, u32 sr, OSContext* context);
typedef void (*SITypeAndStatusCallback)(s32 chan, u32 type);

typedef struct SIControl {
    s32 chan;
    u32 poll;
    u32 inputBytes;
    void* input;
    SICallback callback;
} SIControl;

typedef struct SIPacket {
    s32 chan;
    void* output;
    u32 outputBytes;
    void* input;
    u32 inputBytes;
    SICallback callback;
    OSTime fire;
} SIPacket;

bool SIBusy(void);
bool SIIsChanBusy(s32 chan);
bool SIRegisterPollingHandler(__OSInterruptHandler handler);
bool SIUnregisterPollingHandler(__OSInterruptHandler handler);
void SIInit(void);
u32 SIGetStatus(s32 chan);
void SISetCommand(s32 chan, u32 command);
void SITransferCommands(void);
u32 SISetXY(u32 x, u32 y);
u32 SIEnablePolling(u32 poll);
u32 SIDisablePolling(u32 poll);
bool SIGetResponse(s32 chan, void* data);
bool SITransfer(s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes,
                void (*callback)(s32, u32, OSContext*), s64 time);
u32 SIGetType(s32 chan);
u32 SIGetTypeAsync(s32 chan, SITypeAndStatusCallback callback);

void SISetSamplingRate(u32 msec);
void SIRefreshSamplingRate(void);

u32 SISync(void);
u32 SIGetCommand(s32 chan);
u32 SIDecodeType(u32 type);

#endif
