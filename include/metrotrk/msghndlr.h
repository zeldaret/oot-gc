#ifndef _METROTRK_MSGHNDLR_H
#define _METROTRK_MSGHNDLR_H

#include "dolphin/types.h"
#include "metrotrk/dserror.h"
#include "metrotrk/msgbuf.h"
#include "metrotrk/msgcmd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct msgbuf_t {
    /* 0x00 */ u32 msgLength;
    //! TODO: fix enum size shenanigans
    /* 0x04 */ union {
        u8 commandId;
        MessageCommandID commandIdInt;
    };
    /* 0x08 */ union {
        u8 replyError;
        DSReplyError replyErrorInt;
    };
    /* 0x0C */ u32 unk0C;
    /* 0x10 */ u8 unk10[0x30];
} msgbuf_t; // size = 0x40

bool GetTRKConnected();
DSError TRKDoConnect(MessageBuffer* buf);
DSError TRKDoDisconnect(MessageBuffer* buf);
DSError TRKDoReset(MessageBuffer* buf);
DSError TRKDoOverride(MessageBuffer* buf);
DSError TRKDoVersions(MessageBuffer* buf);
DSError TRKDoSupportMask(MessageBuffer* buf);
DSError TRKDoReadMemory(MessageBuffer* buf);
DSError TRKDoWriteMemory(MessageBuffer* buf);
DSError TRKDoReadRegisters(MessageBuffer* buf);
DSError TRKDoWriteRegisters(MessageBuffer* buf);
DSError TRKDoContinue(MessageBuffer* buf);
DSError TRKDoStep(MessageBuffer* buf);
DSError TRKDoStop(MessageBuffer* buf);
DSError TRKDoSetOption(MessageBuffer* buf);
DSError TRKStandardACK(MessageBuffer* b, MessageCommandID commandId, DSReplyError replyError);

#ifdef __cplusplus
}
#endif

#endif
