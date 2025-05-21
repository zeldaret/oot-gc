#include "emulator/rsp.h"

s32 cmask_tab[8] = {0x7, 0xE, 0xC, 0xC, 0x0, 0x0, 0x0, 0x0};
s32 emask_tab[8] = {0x0, 0x1, 0x3, 0x3, 0x7, 0x7, 0x7, 0x7};

static bool rspVMUDN(Rsp* pRSP, s16* pVec1, s16* pVec2, s16* pVecResult, u32 nElement, s64* pAcc) {
    s32 i;
    s64 taccum;
    s64 ai;
    u16 su;
    s16 ti;
    u16 du;
    s32 clampShift = 31;
    s64 clampMask = ~(((s64)1 << clampShift) - 1);
    s32 elementMaskIndex = (nElement & 0xF) >> 1;
    s32 pad[8];

    for (i = 0; i < 8; i++) {
        ai = 0;
        su = pVec1[i];
        ti = pVec2[(i & cmask_tab[elementMaskIndex]) + (nElement & emask_tab[elementMaskIndex])];

        taccum = (u64)su * (u64)ti;
        taccum += ai;

        if ((taccum >> 47) & 1) {
            taccum = 0xFFFF000000000000 | (taccum & 0xFFFFFFFFFFFF);
        } else {
            taccum = taccum & 0xFFFFFFFFFFFF;
        }

        pAcc[i] = taccum;

        if (taccum < 0) {
            if (~taccum & clampMask) {
                taccum = 0;
            }
        } else {
            if (taccum & clampMask) {
                taccum = 0xFFFF;
            }
        }

        du = taccum & 0xFFFF;
        du &= 0xFFFF;
        pVecResult[i] = du;
    }

    return true;
}

static bool rspVMADN(Rsp* pRSP, s16* pVec1, s16* pVec2, s16* pVecResult, u32 nElement, s64* pAcc) {
    s32 i;
    s64 taccum;
    s64 ai;
    u16 su;
    s16 ti;
    u16 du;
    s32 clampShift = 31;
    s64 clampMask = ~(((s64)1 << clampShift) - 1);
    s32 elementMaskIndex = (nElement & 0xF) >> 1;
    s32 pad[8];

    for (i = 0; i < 8; i++) {
        ai = pAcc[i];
        su = pVec1[i];
        ti = pVec2[(i & cmask_tab[elementMaskIndex]) + (nElement & emask_tab[elementMaskIndex])];

        taccum = (u64)su * (u64)ti;
        taccum += ai;

        if ((taccum >> 47) & 1) {
            taccum = 0xFFFF000000000000 | (taccum & 0xFFFFFFFFFFFF);
        } else {
            taccum = taccum & 0xFFFFFFFFFFFF;
        }

        pAcc[i] = taccum;

        if (taccum < 0) {
            if (~taccum & clampMask) {
                taccum = 0;
            }
        } else {
            if (taccum & clampMask) {
                taccum = 0xFFFF;
            }
        }

        du = taccum & 0xFFFF;
        du &= 0xFFFF;
        pVecResult[i] = du;
    }

    return true;
}
