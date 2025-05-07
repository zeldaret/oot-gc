#ifndef _METROTRK_SUPPORT_H
#define _METROTRK_SUPPORT_H

#include "dolphin/types.h"
#include "metrotrk/msgbuf.h"
#include "metrotrk/trk.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRK_SuppAccessFile(u32, u8*, size_t*, DSIOResult*, bool, bool);
DSError TRK_RequestSend(MessageBuffer*, int*, int, int, int);
DSError HandleOpenFileSupportRequest(const char*, u8, u32*, DSIOResult*);
DSError HandleCloseFileSupportRequest(int, DSIOResult*);
DSError HandlePositionFileSupportRequest(u32, u32*, u8, DSIOResult*);

#ifdef __cplusplus
}
#endif

#endif
