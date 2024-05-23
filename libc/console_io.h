#ifndef _CONSOLE_IO
#define _CONSOLE_IO

#include "file_struc.h"
#include "stddef.h"

int __write_console(__file_handle handle, unsigned char* buffer, size_t* count, __idle_proc idle_proc);

#endif // _CONSOLE_IO
