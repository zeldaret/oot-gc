#ifndef _METROTRK_CC_GDEV_H
#define _METROTRK_CC_GDEV_H

#include "debugger.h"
#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

//! TODO: figure out what these values represent
typedef enum UnkGdevEnum {
    GDEV_RESULT_10009 = -10009,
    GDEV_RESULT_10005 = -10005,
    GDEV_RESULT_10001 = -10001
} UnkGdevEnum;

void OutputData();
bool IsInitialized();
int gdev_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int gdev_cc_shutdown();
int gdev_cc_open();
int gdev_cc_close();
int gdev_cc_read(u8* dest, int size);
int gdev_cc_write(const u8* src, int size);
int gdev_cc_pre_continue();
int gdev_cc_post_stop();
int gdev_cc_peek();
int gdev_cc_initinterrupts();

#ifdef __cplusplus
}
#endif

#endif
