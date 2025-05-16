/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_cpuDecodePPC2.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80068368 -> 0x8006BE68
*/

#include "dolphin/types.h"

// Range: 0x8006BC80 -> 0x8006BE68
static int cpuCompile_DSLLV(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r11
    int nSize; // r1+0x8
}

// Range: 0x8006BA98 -> 0x8006BC80
static int cpuCompile_DSRLV(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r11
    int nSize; // r1+0x8
}

// Range: 0x8006B894 -> 0x8006BA98
static int cpuCompile_DSRAV(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r1+0x8
    int nSize; // r1+0x8
}

// Range: 0x8006B390 -> 0x8006B894
static int cpuCompile_DMULT(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // int* addressGCN; // r27

    // Local variables
    int* compile; // r1+0x10
    int count; // r5
    int nSize; // r1+0x8
}

// Range: 0x8006B07C -> 0x8006B390
static int cpuCompile_DMULTU(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // int* addressGCN; // r30

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Range: 0x8006AAC0 -> 0x8006B07C
static int cpuCompile_DDIV(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r16

    // Local variables
    int* compile; // r1+0x10
    int count; // r23
    int nSize; // r1+0x8
}

// Range: 0x8006A6A4 -> 0x8006AAC0
static int cpuCompile_DDIVU(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // int* addressGCN; // r24

    // Local variables
    int* compile; // r1+0x10
    int count; // r9
    int nSize; // r1+0x8
}

// Erased
static int cpuCompile_DADD(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Erased
static int cpuCompile_DADDU(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Erased
static int cpuCompile_DSUB(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Erased
static int cpuCompile_DSUBU(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Range: 0x8006A364 -> 0x8006A6A4
static int cpuCompile_S_SQRT(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r19
    // int* addressGCN; // r18

    // Local variables
    int* compile; // r1+0x10
    int count; // r29
    int nSize; // r1+0x8
}

// Range: 0x80069F30 -> 0x8006A364
static int cpuCompile_D_SQRT(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r22
    // int* addressGCN; // r21

    // Local variables
    int* compile; // r1+0x10
    int count; // r21
    int nSize; // r1+0x8
}

// Range: 0x80069D80 -> 0x80069F30
static int cpuCompile_W_CVT_SD(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // int* addressGCN; // r30

    // Local variables
    int* compile; // r1+0x10
    int count; // r30
    int nSize; // r1+0x8
}

// Range: 0x80069800 -> 0x80069D80
static int cpuCompile_L_CVT_SD(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r5
    int nSize; // r1+0x8
}

// Range: 0x80069644 -> 0x80069800
static int cpuCompile_CEIL_W(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Range: 0x80069488 -> 0x80069644
static int cpuCompile_FLOOR_W(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Erased
static int cpuCompile_ROUND_W(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Erased
static int cpuCompile_TRUNC_W(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Range: 0x8006931C -> 0x80069488
static int cpuCompile_LB(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r9
    int nSize; // r1+0x8
}

// Range: 0x800691B0 -> 0x8006931C
static int cpuCompile_LH(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r9
    int nSize; // r1+0x8
}

// Range: 0x80069058 -> 0x800691B0
static int cpuCompile_LW(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r5
    int nSize; // r1+0x8
}

// Range: 0x80068F00 -> 0x80069058
static int cpuCompile_LBU(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r5
    int nSize; // r1+0x8
}

// Range: 0x80068DA8 -> 0x80068F00
static int cpuCompile_LHU(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r5
    int nSize; // r1+0x8
}

// Range: 0x80068C4C -> 0x80068DA8
static int cpuCompile_SB(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Range: 0x80068AF0 -> 0x80068C4C
static int cpuCompile_SH(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Range: 0x80068994 -> 0x80068AF0
static int cpuCompile_SW(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}

// Range: 0x8006880C -> 0x80068994
static int cpuCompile_LDC(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r5
    int nSize; // r1+0x8
}

// Range: 0x80068684 -> 0x8006880C
static int cpuCompile_SDC(struct _CPU* pCPU, int* addressGCN) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r5
    int nSize; // r1+0x8
}

// Range: 0x800684F4 -> 0x80068684
static int cpuCompile_LWL(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r9
    int nSize; // r1+0x8
}

// Range: 0x80068368 -> 0x800684F4
static int cpuCompile_LWR(int* addressGCN) {
    // Parameters
    // int* addressGCN; // r31

    // Local variables
    int* compile; // r1+0x10
    int count; // r7
    int nSize; // r1+0x8
}
