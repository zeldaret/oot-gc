#include "dolphin/os.h"
#include "dolphin/types.h"

int udp_cc_initialize(void* flagOut, __OSInterruptHandler handler) { return -1; }

int udp_cc_shutdown() { return -1; }

int udp_cc_open() { return -1; }

int udp_cc_close() { return -1; }

int udp_cc_read(u8* dest, int size) { return 0; }

int udp_cc_write(const u8* src, int size) { return 0; }

int udp_cc_peek() { return 0; }

int udp_cc_pre_continue() { return -1; }

int udp_cc_post_stop() { return -1; }
