#ifndef _METROTRK_CC_UDP_H
#define _METROTRK_CC_UDP_H

#include "dolphin/os/OSInterrupt.h"
#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

int udp_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int udp_cc_shutdown(void);
int udp_cc_open(void);
int udp_cc_close(void);
int udp_cc_read(u8* dest, int size);
int udp_cc_write(const u8* src, int size);
int udp_cc_pre_continue(void);
int udp_cc_post_stop(void);
int udp_cc_peek(void);
int udp_cc_initinterrupts(void);

#ifdef __cplusplus
}
#endif

#endif
