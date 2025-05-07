#ifndef _METROTRK_MSLSUPP_H
#define _METROTRK_MSLSUPP_H

#include "dolphin/types.h"
#include "metrotrk/trk.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

DSIOResult __read_console(__file_handle, u8*, size_t*, __ref_con);
DSIOResult __read_file(__file_handle, u8*, size_t*, __ref_con);
DSIOResult __write_file(__file_handle, u8*, size_t*, __ref_con);
DSIOResult __access_file(__file_handle, u8*, size_t*, __ref_con, MessageCommandID);

#ifdef __cplusplus
}
#endif

#endif
