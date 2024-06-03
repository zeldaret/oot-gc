#include "console_io.h"
#include "dolphin/exi.h"
#include "dolphin/types.h"

static inline int __init_console(void) {
    static bool initialized;
    int res = 0;

    if (!initialized) {
        res = InitializeUART(0xE100);
        if (res == 0) {
            initialized = true;
        }
    }
    return res;
}

int __read_console(__file_handle handle, unsigned char* buffer, size_t* count, __idle_proc idle_proc) {
    int res;
    size_t len;

    if (__init_console() != 0) {
        return 1;
    }

    len = *count;
    res = 0;
    *count = 0;
    while (*count <= len && res == 0) {
        res = ReadUARTN(buffer, 1);
        *count += 1;
        if (*buffer == '\r') {
            break;
        }
        buffer += 1;
    }

    return (res == 0 ? 0 : 1) & 0xFF;
}

int __write_console(__file_handle handle, unsigned char* buffer, size_t* count, __idle_proc idle_proc) {
    if (__init_console() != 0) {
        return 1;
    }

    if (WriteUARTN(buffer, *count) != 0) {
        *count = 0;
        return 1;
    }

    return 0;
}

int __close_console(__file_handle file) { return 0; }
