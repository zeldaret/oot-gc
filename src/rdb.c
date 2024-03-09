#include "rdb.h"
#include "system.h"

_XL_OBJECTTYPE gClassRdb = {
    "RDB",
    sizeof(Rdb),
    NULL,
    (EventFunc)rdbEvent,
};

// This function only clears the string buffer, but it may have output the
// string to the console in debug mode.
inline void rdbPrintString(Rdb* pRDB) {
    s32 iCounter;

    for (iCounter = 0; iCounter < pRDB->nIndexString; iCounter++) {
        pRDB->szString[iCounter] = ' ';
    }
    pRDB->nIndexString = 0;
}

static s32 rdbPut8(Rdb* pRDB, u32 nAddress, s8* pData) { return 0; }

static s32 rdbPut16(Rdb* pRDB, u32 nAddress, s16* pData) { return 0; }

static s32 rdbPut32(Rdb* pRDB, u32 nAddress, s32* pData) {
    s32 nLength;
    s32 iCounter;

    switch (nAddress & 0xF) {
        case 0x0:
            nLength = (*pData >> 24) & 3;
            switch ((*pData >> 26) & 0x3F) {
                case 0:
                    return 0;
                case 1:
                    switch (nLength) {
                        case 0:
                            break;
                        case 1:
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 16) & 0xFF);
                            rdbPrintString(pRDB);
                            break;
                        case 2:
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 16) & 0xFF);
                            if (pRDB->szString[pRDB->nIndexString] == '\n') {
                                rdbPrintString(pRDB);
                            } else if (pRDB->nIndexString > 256) {
                                rdbPrintString(pRDB);
                            } else {
                                pRDB->nIndexString++;
                            }
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 8) & 0xFF);
                            rdbPrintString(pRDB);
                            break;
                        case 3:
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 16) & 0xFF);
                            if (pRDB->szString[pRDB->nIndexString] == '\n') {
                                rdbPrintString(pRDB);
                            } else if (pRDB->nIndexString > 256) {
                                rdbPrintString(pRDB);
                            } else {
                                pRDB->nIndexString++;
                            }
                            pRDB->szString[pRDB->nIndexString] = (s32)((*pData >> 8) & 0xFF);
                            if (pRDB->szString[pRDB->nIndexString] == '\n') {
                                rdbPrintString(pRDB);
                            } else if (pRDB->nIndexString > 256) {
                                rdbPrintString(pRDB);
                            } else {
                                pRDB->nIndexString++;
                            }
                            pRDB->szString[pRDB->nIndexString] = *pData & 0xFF;
                            if (pRDB->szString[pRDB->nIndexString] == '\n') {
                                rdbPrintString(pRDB);
                            } else if (pRDB->nIndexString > 256) {
                                rdbPrintString(pRDB);
                            } else {
                                pRDB->nIndexString++;
                            }
                            break;
                        default:
                            return 0;
                    }
                    xlObjectEvent(pRDB->pHost, 0x1000, (void*)4);
                    break;
                case 2:
                    return 0;
                case 3:
                    return 0;
                case 4:
                    return 0;
                case 5:
                    return 0;
                case 6:
                    return 0;
                case 7:
                    return 0;
                case 8:
                    return 0;
                case 9:
                    return 0;
                case 10:
                    return 0;
                case 11:
                    return 0;
                case 12:
                    return 0;
                case 22: // bug?
                    return 0;
                case 13:
                    return 0;
                case 14:
                    return 0;
                case 15:
                    return 0;
                case 16:
                    return 0;
                case 17:
                    return 0;
                case 18:
                    return 0;
                case 19:
                    return 0;
                case 20:
                    return 0;
                case 21:
                    return 0;
                default:
                    return 0;
            }
            break;
        case 0x8:
            break;
        case 0xC:
            xlObjectEvent(pRDB->pHost, 0x1001, (void*)4);
            break;
        default:
            return 0;
    }

    return 1;
}

static s32 rdbPut64(Rdb* pRDB, u32 nAddress, s64* pData) { return 0; }

static s32 rdbGet8(Rdb* pRDB, u32 nAddress, s8* pData) { return 0; }

static s32 rdbGet16(Rdb* pRDB, u32 nAddress, s16* pData) { return 0; }

static s32 rdbGet32(Rdb* pRDB, u32 nAddress, s32* pData) {
    switch (nAddress & 0xF) {
        case 0x0:
        case 0x8:
        case 0xC:
            break;
        default:
            return 0;
    }

    return 1;
}

static s32 rdbGet64(Rdb* pRDB, u32 nAddress, s64* pData) { return 0; }

s32 rdbEvent(Rdb* pRDB, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pRDB->pHost = pArgument;
            pRDB->nIndexString = 0;
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pRDB->pHost), pArgument, (Put8Func)rdbPut8, (Put16Func)rdbPut16,
                                 (Put32Func)rdbPut32, (Put64Func)rdbPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pRDB->pHost), pArgument, (Get8Func)rdbGet8, (Get16Func)rdbGet16,
                                 (Get32Func)rdbGet32, (Get64Func)rdbGet64)) {
                return 0;
            }
        case 0:
        case 1:
        case 3:
        case 0x1003:
            break;
        default:
            return 0;
    }

    return 1;
}
