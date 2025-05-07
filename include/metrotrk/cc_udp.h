#ifndef _METROTRK_CC_UDP_H
#define _METROTRK_CC_UDP_H

#include "dolphin/os/OSInterrupt.h"
#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

int udp_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int udp_cc_shutdown();
int udp_cc_open();
int udp_cc_close();
int udp_cc_read(u8* dest, int size);
int udp_cc_write(const u8* src, int size);
int udp_cc_pre_continue();
int udp_cc_post_stop();
int udp_cc_peek();
int udp_cc_initinterrupts();

#ifdef __cplusplus
}
#endif

#endif
