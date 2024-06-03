#ifndef _CONSOLE_IO
#define _CONSOLE_IO

#include "stdio.h"

extern int __read_console(__file_handle handle, unsigned char* buffer, size_t* count, __idle_proc idle_proc);
extern int __write_console(__file_handle handle, unsigned char* buffer, size_t* count, __idle_proc idle_proc);
extern int __close_console(__file_handle file);

#endif // _CONSOLE_IO
