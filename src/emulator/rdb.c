#include "emulator/rdb.h"
#include "emulator/system.h"

_XL_OBJECTTYPE gClassRdb = {
    "RDB",
    sizeof(Rdb),
    NULL,
    (EventFunc)rdbEvent,
};

// This function only clears the string buffer, but it may have done something
// with the string in debug mode.
static inline void rdbHandleString(Rdb* pRDB) {
    s32 iCounter;

    for (iCounter = 0; iCounter < pRDB->nIndexString; iCounter++) {
        pRDB->szString[iCounter] = ' ';
    }
    pRDB->nIndexString = 0;
}

static bool rdbPut8(Rdb* pRDB, u32 nAddress, s8* pData) { return false; }

static bool rdbPut16(Rdb* pRDB, u32 nAddress, s16* pData) { return false; }

static bool rdbPut32(Rdb* pRDB, u32 nAddress, s32* pData) {
    s32 nLength;
    s32 iCounter;

    switch (nAddress & 0xF) {
        case 0x0:
            nLength = (*pData >> 24) & 3;
            switch ((*pData >> 26) & 0x3F) {
                case 0:
                    return false;
                case 1:
                    switch (nLength) {
                        case 0:
                            break;
                        case 1:
                            //! @bug: in all these cases, pRDB->nIndexString may end up being >= 256,
                            // which will write out of bounds into pRDB->szString.
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 16) & 0xFF);
                            rdbHandleString(pRDB);
                            break;
                        case 2:
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 16) & 0xFF);
                            if (pRDB->szString[pRDB->nIndexString] == '\n') {
                                rdbHandleString(pRDB);
                            } else if (pRDB->nIndexString > 256) {
                                rdbHandleString(pRDB);
                            } else {
                                pRDB->nIndexString++;
                            }
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 8) & 0xFF);
                            rdbHandleString(pRDB);
                            break;
                        case 3:
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 16) & 0xFF);
                            if (pRDB->szString[pRDB->nIndexString] == '\n') {
                                rdbHandleString(pRDB);
                            } else if (pRDB->nIndexString > 256) {
                                rdbHandleString(pRDB);
                            } else {
                                pRDB->nIndexString++;
                            }
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 8) & 0xFF);
                            if (pRDB->szString[pRDB->nIndexString] == '\n') {
                                rdbHandleString(pRDB);
                            } else if (pRDB->nIndexString > 256) {
                                rdbHandleString(pRDB);
                            } else {
                                pRDB->nIndexString++;
                            }
                            pRDB->szString[pRDB->nIndexString] = *pData & 0xFF;
                            if (pRDB->szString[pRDB->nIndexString] == '\n') {
                                rdbHandleString(pRDB);
                            } else if (pRDB->nIndexString > 256) {
                                rdbHandleString(pRDB);
                            } else {
                                pRDB->nIndexString++;
                            }
                            break;
                        default:
                            return false;
                    }
                    xlObjectEvent(pRDB->pHost, 0x1000, (void*)4);
                    break;
                case 2:
                    return false;
                case 3:
                    return false;
                case 4:
                    return false;
                case 5:
                    return false;
                case 6:
                    return false;
                case 7:
                    return false;
                case 8:
                    return false;
                case 9:
                    return false;
                case 10:
                    return false;
                case 11:
                    return false;
                case 12:
                    return false;
                case 22: // bug?
                    return false;
                case 13:
                    return false;
                case 14:
                    return false;
                case 15:
                    return false;
                case 16:
                    return false;
                case 17:
                    return false;
                case 18:
                    return false;
                case 19:
                    return false;
                case 20:
                    return false;
                case 21:
                    return false;
                default:
                    return false;
            }
            break;
        case 0x8:
            break;
        case 0xC:
            xlObjectEvent(pRDB->pHost, 0x1001, (void*)4);
            break;
        default:
            return false;
    }

    return true;
}

static bool rdbPut64(Rdb* pRDB, u32 nAddress, s64* pData) { return false; }

static bool rdbGet8(Rdb* pRDB, u32 nAddress, s8* pData) { return false; }

static bool rdbGet16(Rdb* pRDB, u32 nAddress, s16* pData) { return false; }

static bool rdbGet32(Rdb* pRDB, u32 nAddress, s32* pData) {
    switch (nAddress & 0xF) {
        case 0x0:
        case 0x8:
        case 0xC:
            break;
        default:
            return false;
    }

    return true;
}

static bool rdbGet64(Rdb* pRDB, u32 nAddress, s64* pData) { return false; }

bool rdbEvent(Rdb* pRDB, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pRDB->pHost = pArgument;
            pRDB->nIndexString = 0;
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pRDB->pHost), pArgument, (Put8Func)rdbPut8, (Put16Func)rdbPut16,
                                 (Put32Func)rdbPut32, (Put64Func)rdbPut64)) {
                return false;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pRDB->pHost), pArgument, (Get8Func)rdbGet8, (Get16Func)rdbGet16,
                                 (Get32Func)rdbGet32, (Get64Func)rdbGet64)) {
                return false;
            }
        case 0:
        case 1:
        case 3:
            break;
#if VERSION != MQ_J
        case 0x1003:
            break;
#endif
        default:
            return false;
    }

    return true;
}
