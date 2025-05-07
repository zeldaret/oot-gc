#ifndef _METROTRK_DISPATCH_H
#define _METROTRK_DISPATCH_H

#include "dolphin/types.h"
#include "metrotrk/dserror.h"
#include "metrotrk/msgbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKInitializeDispatcher(void);
DSError TRKDispatchMessage(MessageBuffer* buf);

#ifdef __cplusplus
}
#endif

#endif
