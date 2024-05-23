#ifndef _FILE_STRUC
#define _FILE_STRUC

#include "stddef.h"

typedef unsigned long __file_handle;
typedef unsigned long fpos_t;

typedef void (*__idle_proc)(void);
typedef int (*__pos_proc)(__file_handle file, fpos_t* position, int mode, __idle_proc idle_proc);
typedef int (*__io_proc)(__file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
typedef int (*__close_proc)(__file_handle file);

#endif // _FILE_STRUC
