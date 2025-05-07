#include "metrotrk/mslsupp.h"
#include "metrotrk/target_options.h"
#include "metrotrk/targsupp.h"

DSIOResult __read_console(__file_handle handle, u8* buffer, size_t* count, __ref_con ref_con) {
    if (GetUseSerialIO() == 0) {
        return kDSIOError;
    }
    return __read_file(0, buffer, count, ref_con);
}

DSIOResult __TRK_write_console(__file_handle handle, u8* buffer, size_t* count, __ref_con ref_con) {
    if (GetUseSerialIO() == 0) {
        return kDSIOError;
    }
    return __write_file(1, buffer, count, ref_con);
}

DSIOResult __read_file(__file_handle handle, u8* buffer, size_t* count, __ref_con ref_con) {
    return __access_file(handle, buffer, count, ref_con, kDSReadFile);
}

DSIOResult __write_file(__file_handle handle, u8* buffer, size_t* count, __ref_con ref_con) {
    return __access_file(handle, buffer, count, ref_con, kDSWriteFile);
}

DSIOResult __access_file(__file_handle handle, u8* buffer, size_t* count, __ref_con ref_con, MessageCommandID id) {
    size_t countTemp;
    u32 r0;

    if (!GetTRKConnected()) {
        return kDSIOError;
    }

    countTemp = *count;
    r0 = TRKAccessFile(id, handle, &countTemp, buffer);
    *count = countTemp;

    switch ((u8)r0) {
        case kDSIONoError:
            return kDSIONoError;
        case kDSIOEOF:
            return kDSIOEOF;
        default:
            return kDSIOError;
    }
}
