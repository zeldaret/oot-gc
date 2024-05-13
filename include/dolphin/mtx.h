#ifndef _DOLPHIN_MTX_H_
#define _DOLPHIN_MTX_H_

#include "dolphin/types.h"

typedef struct Vec {
    f32 x, y, z;
} Vec;

typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];

void PSMTXIdentity(Mtx m);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);

void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);

void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);
void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void PSMTX44Concat(const Mtx44 a, const Mtx44 b, Mtx44 ab);

#endif
