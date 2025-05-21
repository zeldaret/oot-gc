/**
 * @file _cpuDecodePPC2.c
 *
 * Generates PowerPC assembly code for various MIPS instructions. This file is
 * included into cpu.c instead of being compiled separately.
 */
#include "emulator/cpu.h"

static bool cpuCompile_DSLLV(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 16;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFE8; // stwu    r1,-24(r1)
    compile[count++] = 0x70E7003F; // andi.   r7,r7,63
    compile[count++] = 0x91210010; // stw     r9,16(r1)
    compile[count++] = 0x21270020; // subfic  r9,r7,32
    compile[count++] = 0x91010008; // stw     r8,8(r1)
    compile[count++] = 0x7CA53830; // slw     r5,r5,r7
    compile[count++] = 0x7CC84C30; // srw     r8,r6,r9
    compile[count++] = 0x7CA54378; // or      r5,r5,r8
    compile[count++] = 0x3927FFE0; // addi    r9,r7,-32
    compile[count++] = 0x7CC84830; // slw     r8,r6,r9
    compile[count++] = 0x7CA54378; // or      r5,r5,r8
    compile[count++] = 0x7CC63830; // slw     r6,r6,r7
    compile[count++] = 0x81010008; // lwz     r8,8(r1)
    compile[count++] = 0x81210010; // lwz     r9,16(r1)
    compile[count++] = 0x38210018; // addi    r1,r1,24
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DSRLV(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 16;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFE8; // stwu    r1,-24(r1)
    compile[count++] = 0x70E7003F; // andi.   r7,r7,63
    compile[count++] = 0x91210010; // stw     r9,16(r1)
    compile[count++] = 0x21270020; // subfic  r9,r7,32
    compile[count++] = 0x91010008; // stw     r8,8(r1)
    compile[count++] = 0x7CC63C30; // srw     r6,r6,r7
    compile[count++] = 0x7CA84830; // slw     r8,r5,r9
    compile[count++] = 0x7CC64378; // or      r6,r6,r8
    compile[count++] = 0x3927FFE0; // addi    r9,r7,-32
    compile[count++] = 0x7CA84C30; // srw     r8,r5,r9
    compile[count++] = 0x7CC64378; // or      r6,r6,r8
    compile[count++] = 0x7CA53C30; // srw     r5,r5,r7
    compile[count++] = 0x81010008; // lwz     r8,8(r1)
    compile[count++] = 0x81210010; // lwz     r9,16(r1)
    compile[count++] = 0x38210018; // addi    r1,r1,24
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DSRAV(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 17;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFE8; // stwu    r1,-24(r1)
    compile[count++] = 0x70E7003F; // andi.   r7,r7,63
    compile[count++] = 0x91210010; // stw     r9,16(r1)
    compile[count++] = 0x21270020; // subfic  r9,r7,32
    compile[count++] = 0x91010008; // stw     r8,8(r1)
    compile[count++] = 0x7CC63C30; // srw     r6,r6,r7
    compile[count++] = 0x7CA84830; // slw     r8,r5,r9
    compile[count++] = 0x7CC64378; // or      r6,r6,r8
    compile[count++] = 0x3527FFE0; // addic.  r9,r7,-32
    compile[count++] = 0x7CA84E30; // sraw    r8,r5,r9
    compile[count++] = 0x40810008; // ble-    0x8
    compile[count++] = 0x61060000; // ori     r6,r8,0
    compile[count++] = 0x7CA53E30; // sraw    r5,r5,r7
    compile[count++] = 0x81010008; // lwz     r8,8(r1)
    compile[count++] = 0x81210010; // lwz     r9,16(r1)
    compile[count++] = 0x38210018; // addi    r1,r1,24
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DMULT(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 53;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x39200000; // li      r9,0
    compile[count++] = 0x39400000; // li      r10,0
    compile[count++] = 0x39800040; // li      r12,64
    compile[count++] = 0x39600001; // li      r11,1
    compile[count++] = 0x2C050000; // cmpwi   r5,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7CC630F8; // not     r6,r6
    compile[count++] = 0x7CA528F8; // not     r5,r5
    compile[count++] = 0x7CC65814; // addc    r6,r6,r11
    compile[count++] = 0x7CA54914; // adde    r5,r5,r9
    compile[count++] = 0x2C070000; // cmpwi   r7,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7D0840F8; // not     r8,r8
    compile[count++] = 0x7CE738F8; // not     r7,r7
    compile[count++] = 0x7D085814; // addc    r8,r8,r11
    compile[count++] = 0x7CE74914; // adde    r7,r7,r9
    compile[count++] = 0x710B0001; // andi.   r11,r8,1
    compile[count++] = 0x41820018; // beq-    0x18
    compile[count++] = 0x39600000; // li      r11,0
    compile[count++] = 0x7D4A3014; // addc    r10,r10,r6
    compile[count++] = 0x7D292914; // adde    r9,r9,r5
    compile[count++] = 0x7D6B5914; // adde    r11,r11,r11
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x39600000; // li      r11,0
    compile[count++] = 0x5508F87E; // srwi    r8,r8,1
    compile[count++] = 0x50E8F800; // rlwimi  r8,r7,31,0,0
    compile[count++] = 0x54E7F87E; // srwi    r7,r7,1
    compile[count++] = 0x5147F800; // rlwimi  r7,r10,31,0,0
    compile[count++] = 0x554AF87E; // srwi    r10,r10,1
    compile[count++] = 0x512AF800; // rlwimi  r10,r9,31,0,0
    compile[count++] = 0x5529F87E; // srwi    r9,r9,1
    compile[count++] = 0x5169F800; // rlwimi  r9,r11,31,0,0
    compile[count++] = 0x556BF87E; // srwi    r11,r11,1
    compile[count++] = 0x398CFFFF; // addi    r12,r12,-1
    compile[count++] = 0x2C0C0000; // cmpwi   r12,0
    compile[count++] = 0x4082FFB4; // bne+    0xFFFFFFB4
    compile[count++] = 0x39600001; // li      r11,1
    compile[count++] = 0x7DCE7A78; // xor     r14,r14,r15
    compile[count++] = 0x2C0E0000; // cmpwi   r14,0
    compile[count++] = 0x40800024; // bge-    0x24
    compile[count++] = 0x7D0840F8; // not     r8,r8
    compile[count++] = 0x7CE738F8; // not     r7,r7
    compile[count++] = 0x7D4A50F8; // not     r10,r10
    compile[count++] = 0x7D2948F8; // not     r9,r9
    compile[count++] = 0x7D085814; // addc    r8,r8,r11
    compile[count++] = 0x7CE76114; // adde    r7,r7,r12
    compile[count++] = 0x7D4A6114; // adde    r10,r10,r12
    compile[count++] = 0x7D296114; // adde    r9,r9,r12
    compile[count++] = 0x91030004 + OFFSETOF(pCPU, nLo); // stw     r8,4(r3)
    compile[count++] = 0x90E30000 + OFFSETOF(pCPU, nLo); // stw     r7,0(r3)
    compile[count++] = 0x91430004 + OFFSETOF(pCPU, nHi); // stw     r10,4(r3)
    compile[count++] = 0x91230000 + OFFSETOF(pCPU, nHi); // stw     r9,0(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DMULTU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 28;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x39200000; // li      r9,0
    compile[count++] = 0x39400000; // li      r10,0
    compile[count++] = 0x39800040; // li      r12,64
    compile[count++] = 0x710B0001; // andi.   r11,r8,1
    compile[count++] = 0x41820018; // beq-    0x18
    compile[count++] = 0x39600000; // li      r11,0
    compile[count++] = 0x7D4A3014; // addc    r10,r10,r6
    compile[count++] = 0x7D292914; // adde    r9,r9,r5
    compile[count++] = 0x7D6B5914; // adde    r11,r11,r11
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x39600000; // li      r11,0
    compile[count++] = 0x5508F87E; // srwi    r8,r8,1
    compile[count++] = 0x50E8F800; // rlwimi  r8,r7,31,0,0
    compile[count++] = 0x54E7F87E; // srwi    r7,r7,1
    compile[count++] = 0x5147F800; // rlwimi  r7,r10,31,0,0
    compile[count++] = 0x554AF87E; // srwi    r10,r10,1
    compile[count++] = 0x512AF800; // rlwimi  r10,r9,31,0,0
    compile[count++] = 0x5529F87E; // srwi    r9,r9,1
    compile[count++] = 0x5169F800; // rlwimi  r9,r11,31,0,0
    compile[count++] = 0x556BF87E; // srwi    r11,r11,1
    compile[count++] = 0x398CFFFF; // addi    r12,r12,-1
    compile[count++] = 0x2C0C0000; // cmpwi   r12,0
    compile[count++] = 0x4082FFB4; // bne+    0xFFFFFFB4
    compile[count++] = 0x91030004 + OFFSETOF(pCPU, nLo); // stw     r8,4(r3)
    compile[count++] = 0x90E30000 + OFFSETOF(pCPU, nLo); // stw     r7,0(r3)
    compile[count++] = 0x91430004 + OFFSETOF(pCPU, nHi); // stw     r10,4(r3)
    compile[count++] = 0x91230000 + OFFSETOF(pCPU, nHi); // stw     r9,0(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DDIV(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 64;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x38A00040; // li      r5,64
    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0x38E00000; // li      r7,0
    compile[count++] = 0x39800001; // li      r12,1
    compile[count++] = 0x2C080000; // cmpwi   r8,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7D2948F8; // not     r9,r9
    compile[count++] = 0x7D0840F8; // not     r8,r8
    compile[count++] = 0x7D296014; // addc    r9,r9,r12
    compile[count++] = 0x7D083114; // adde    r8,r8,r6
    compile[count++] = 0x2C0A0000; // cmpwi   r10,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7D6B58F8; // not     r11,r11
    compile[count++] = 0x7D4A50F8; // not     r10,r10
    compile[count++] = 0x7D6B6014; // addc    r11,r11,r12
    compile[count++] = 0x7D4A3114; // adde    r10,r10,r6
    compile[count++] = 0x3D80FFFF; // lis     r12,-1
    compile[count++] = 0x618CFFFE; // ori     r12,r12,65534
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4180002C; // blt-    0x2C
    compile[count++] = 0x54C6083C; // slwi    r6,r6,1
    compile[count++] = 0x50E60FFE; // rlwimi  r6,r7,1,31,31
    compile[count++] = 0x54E7083C; // slwi    r7,r7,1
    compile[count++] = 0x51070FFE; // rlwimi  r7,r8,1,31,31
    compile[count++] = 0x5508083C; // slwi    r8,r8,1
    compile[count++] = 0x51280FFE; // rlwimi  r8,r9,1,31,31
    compile[count++] = 0x5529083C; // slwi    r9,r9,1
    compile[count++] = 0x7CEB3810; // subfc   r7,r11,r7
    compile[count++] = 0x7CCA3110; // subfe   r6,r10,r6
    compile[count++] = 0x42800028; // bc      20,lt,0x28
    compile[count++] = 0x54C6083C; // slwi    r6,r6,1
    compile[count++] = 0x50E60FFE; // rlwimi  r6,r7,1,31,31
    compile[count++] = 0x54E7083C; // slwi    r7,r7,1
    compile[count++] = 0x51070FFE; // rlwimi  r7,r8,1,31,31
    compile[count++] = 0x5508083C; // slwi    r8,r8,1
    compile[count++] = 0x51280FFE; // rlwimi  r8,r9,1,31,31
    compile[count++] = 0x5529083C; // slwi    r9,r9,1
    compile[count++] = 0x7CE75814; // addc    r7,r7,r11
    compile[count++] = 0x7CC65114; // adde    r6,r6,r10
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4180000C; // blt-    0xC
    compile[count++] = 0x61290001; // ori     r9,r9,1
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x7D296038; // and     r9,r9,r12
    compile[count++] = 0x38A5FFFF; // addi    r5,r5,-1
    compile[count++] = 0x2C050000; // cmpwi   r5,0
    compile[count++] = 0x4082FF90; // bne+    0xFFFFFF90
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4080000C; // bge-    0xC
    compile[count++] = 0x7CE75814; // addc    r7,r7,r11
    compile[count++] = 0x7CC65114; // adde    r6,r6,r10
    compile[count++] = 0x39800001; // li      r12,1
    compile[count++] = 0x7DCE7A78; // xor     r14,r14,r15
    compile[count++] = 0x2C0E0000; // cmpwi   r14,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7D2948F8; // not     r9,r9
    compile[count++] = 0x7D0840F8; // not     r8,r8
    compile[count++] = 0x7D296014; // addc    r9,r9,r12
    compile[count++] = 0x7D082914; // adde    r8,r8,r5
    compile[count++] = 0x91030000 + OFFSETOF(pCPU, nLo); // stw     r8,0(r3)
    compile[count++] = 0x91230004 + OFFSETOF(pCPU, nLo); // stw     r9,4(r3)
    compile[count++] = 0x90C30000 + OFFSETOF(pCPU, nHi); // stw     r6,0(r3)
    compile[count++] = 0x90E30004 + OFFSETOF(pCPU, nHi); // stw     r7,4(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DDIVU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 43;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x38A00040; // li      r5,64
    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0x38E00000; // li      r7,0
    compile[count++] = 0x3D80FFFF; // lis     r12,-1
    compile[count++] = 0x618CFFFE; // ori     r12,r12,65534
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4180002C; // blt-    0x2C
    compile[count++] = 0x54C6083C; // slwi    r6,r6,1
    compile[count++] = 0x50E60FFE; // rlwimi  r6,r7,1,31,31
    compile[count++] = 0x54E7083C; // slwi    r7,r7,1
    compile[count++] = 0x51070FFE; // rlwimi  r7,r8,1,31,31
    compile[count++] = 0x5508083C; // slwi    r8,r8,1
    compile[count++] = 0x51280FFE; // rlwimi  r8,r9,1,31,31
    compile[count++] = 0x5529083C; // slwi    r9,r9,1
    compile[count++] = 0x7CEB3810; // subfc   r7,r11,r7
    compile[count++] = 0x7CCA3110; // subfe   r6,r10,r6
    compile[count++] = 0x42800028; // bc      20,lt,0x28
    compile[count++] = 0x54C6083C; // slwi    r6,r6,1
    compile[count++] = 0x50E60FFE; // rlwimi  r6,r7,1,31,31
    compile[count++] = 0x54E7083C; // slwi    r7,r7,1
    compile[count++] = 0x51070FFE; // rlwimi  r7,r8,1,31,31
    compile[count++] = 0x5508083C; // slwi    r8,r8,1
    compile[count++] = 0x51280FFE; // rlwimi  r8,r9,1,31,31
    compile[count++] = 0x5529083C; // slwi    r9,r9,1
    compile[count++] = 0x7CE75814; // addc    r7,r7,r11
    compile[count++] = 0x7CC65114; // adde    r6,r6,r10
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4180000C; // blt-    0xC
    compile[count++] = 0x61290001; // ori     r9,r9,1
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x7D296038; // and     r9,r9,r12
    compile[count++] = 0x38A5FFFF; // addi    r5,r5,-1
    compile[count++] = 0x2C050000; // cmpwi   r5,0
    compile[count++] = 0x4082FF90; // bne+    0xFFFFFF90
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4080000C; // bge-    0xC
    compile[count++] = 0x7CE75814; // addc    r7,r7,r11
    compile[count++] = 0x7CC65114; // adde    r6,r6,r10
    compile[count++] = 0x91030000 + OFFSETOF(pCPU, nLo); // stw     r8,0(r3)
    compile[count++] = 0x91230004 + OFFSETOF(pCPU, nLo); // stw     r9,4(r3)
    compile[count++] = 0x90C30000 + OFFSETOF(pCPU, nHi); // stw     r6,0(r3)
    compile[count++] = 0x90E30004 + OFFSETOF(pCPU, nHi); // stw     r7,4(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_DADD(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x7CA53814; // addc    r5,r5,r7
    compile[count++] = 0x7CC64114; // adde    r6,r6,r8
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_DADDU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x7CA53814; // addc    r5,r5,r7
    compile[count++] = 0x7CC64114; // adde    r6,r6,r8
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_DSUB(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x7CA72914; // adde    r5,r7,r5
    compile[count++] = 0x7CC83014; // addc    r6,r8,r6
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_DSUBU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x7CA72914; // adde    r5,r7,r5
    compile[count++] = 0x7CC83014; // addc    r6,r8,r6
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_S_SQRT(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 36;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0xC0030000 + (OFFSETOF(pCPU, aGPR) + 4); // lfs     f0,0(r3)
    compile[count++] = 0xFC010040; // fcmpo   cr0,f1,f0
    compile[count++] = 0x40810078; // ble-    0x78
    compile[count++] = 0xFC400834; // frsqrte f2,f1
    compile[count++] = 0x3CA03FE0; // lis     r5,16352
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC8830000 + OFFSETOF(pCPU, aGPR); // lfd     f4,0(r3)
    compile[count++] = 0x3CA04008; // lis     r5,16392
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC8630000 + OFFSETOF(pCPU, aGPR); // lfd     f3,0(r3)
    compile[count++] = 0xFCA400B2; // fmul    f5,f4,f2
    compile[count++] = 0xFCC200B2; // fmul    f6,f2,f2
    compile[count++] = 0xFCC101B2; // fmul    f6,f1,f6
    compile[count++] = 0xFCC33028; // fsub    f6,f3,f6
    compile[count++] = 0xFC4501B2; // fmul    f2,f5,f6
    compile[count++] = 0xFCA400B2; // fmul    f5,f4,f2
    compile[count++] = 0xFCC200B2; // fmul    f6,f2,f2
    compile[count++] = 0xFCC101B2; // fmul    f6,f1,f6
    compile[count++] = 0xFCC33028; // fsub    f6,f3,f6
    compile[count++] = 0xFC4501B2; // fmul    f2,f5,f6
    compile[count++] = 0xFCA400B2; // fmul    f5,f4,f2
    compile[count++] = 0xFCC200B2; // fmul    f6,f2,f2
    compile[count++] = 0xFCC101B2; // fmul    f6,f1,f6
    compile[count++] = 0xFCC33028; // fsub    f6,f3,f6
    compile[count++] = 0xFC4501B2; // fmul    f2,f5,f6
    compile[count++] = 0xFCA400B2; // fmul    f5,f4,f2
    compile[count++] = 0xFCC200B2; // fmul    f6,f2,f2
    compile[count++] = 0xFCC101B2; // fmul    f6,f1,f6
    compile[count++] = 0xFCC33028; // fsub    f6,f3,f6
    compile[count++] = 0xFC4501B2; // fmul    f2,f5,f6
    compile[count++] = 0xFCC100B2; // fmul    f6,f1,f2
    compile[count++] = 0xFC203018; // frsp    f1,f6
    compile[count++] = 0x38A00000; // li      r5,0
    compile[count++] = 0x90A30000 + (OFFSETOF(pCPU, aGPR) + 4); // stw     r5,0(r3)
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_D_SQRT(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 48;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0xC8030000 + OFFSETOF(pCPU, aGPR); // lfd     f0,0(r3)
    compile[count++] = 0xFC010040; // fcmpo   cr0,f1,f0
    compile[count++] = 0x40810068; // ble-    0x68
    compile[count++] = 0xFC400834; // frsqrte f2,f1
    compile[count++] = 0x3CA03FE0; // lis     r5,16352
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC8830000 + OFFSETOF(pCPU, aGPR); // lfd     f4,0(r3)
    compile[count++] = 0x3CA04008; // lis     r5,16392
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC8630000 + OFFSETOF(pCPU, aGPR); // lfd     f3,0(r3)
    compile[count++] = 0xFC0200B2; // fmul    f0,f2,f2
    compile[count++] = 0xFC4400B2; // fmul    f2,f4,f2
    compile[count++] = 0xFC01183C; // fnmsub  f0,f1,f0,f3
    compile[count++] = 0xFC420032; // fmul    f2,f2,f0
    compile[count++] = 0xFC0200B2; // fmul    f0,f2,f2
    compile[count++] = 0xFC4400B2; // fmul    f2,f4,f2
    compile[count++] = 0xFC01183C; // fnmsub  f0,f1,f0,f3
    compile[count++] = 0xFC420032; // fmul    f2,f2,f0
    compile[count++] = 0xFC0200B2; // fmul    f0,f2,f2
    compile[count++] = 0xFC4400B2; // fmul    f2,f4,f2
    compile[count++] = 0xFC01183C; // fnmsub  f0,f1,f0,f3
    compile[count++] = 0xFC420032; // fmul    f2,f2,f0
    compile[count++] = 0xFC0200B2; // fmul    f0,f2,f2
    compile[count++] = 0xFC4400B2; // fmul    f2,f4,f2
    compile[count++] = 0xFC01183C; // fnmsub  f0,f1,f0,f3
    compile[count++] = 0xFC020032; // fmul    f0,f2,f0
    compile[count++] = 0xFC210032; // fmul    f1,f1,f0
    compile[count++] = 0x42800044; // bc      20,lt,0x44
    compile[count++] = 0xFC010000; // fcmpu   cr0,f1,f0
    compile[count++] = 0x4082000C; // bne-    0xC
    compile[count++] = 0xFC200090; // fmr     f1,f0
    compile[count++] = 0x42800034; // bc      20,lt,0x34
    compile[count++] = 0xFC010000; // fcmpu   cr0,f1,f0
    compile[count++] = 0x41820020; // beq-    0x20
    compile[count++] = 0x3CA07FFF; // lis     r5,32767
    compile[count++] = 0x60A5FFFF; // ori     r5,r5,65535
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0x3CA0E000; // lis     r5,-8192
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0xC0230000 + OFFSETOF(pCPU, aGPR); // lfs     f1,0(r3)
    compile[count++] = 0x42800010; // bc      20,lt,0x10
    compile[count++] = 0x3CA07FF0; // lis     r5,32752
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC0230000 + OFFSETOF(pCPU, aGPR); // lfs     f1,0(r3)
    compile[count++] = 0x38A00000; // li      r5,0
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_W_CVT_SD(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 14;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x6CA58000; // xoris   r5,r5,32768
    compile[count++] = 0x3CC04330; // lis     r6,17200
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0x90C30000 + OFFSETOF(pCPU, aGPR); // stw     r6,0(r3)
    compile[count++] = 0xC8030000 + OFFSETOF(pCPU, aGPR); // lfd     f0,0(r3)
    compile[count++] = 0x90C30000 + OFFSETOF(pCPU, aGPR); // stw     r6,0(r3)
    compile[count++] = 0x3CA08000; // lis     r5,-32768
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0xC8230000 + OFFSETOF(pCPU, aGPR); // lfd     f1,0(r3)
    compile[count++] = 0xFC200828; // fsub    f1,f0,f1
    compile[count++] = 0x38A00000; // li      r5,0
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_L_CVT_SD(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 56;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFD0; // stwu    r1,-48(r1)
    compile[count++] = 0x91010008; // stw     r8,8(r1)
    compile[count++] = 0x91210010; // stw     r9,16(r1)
    compile[count++] = 0x91410018; // stw     r10,24(r1)
    compile[count++] = 0x91610020; // stw     r11,32(r1)
    compile[count++] = 0x91810028; // stw     r12,40(r1)
    compile[count++] = 0x9421FFF0; // stwu    r1,-16(r1)
    compile[count++] = 0x54A70001; // clrrwi. r7,r5,31
    compile[count++] = 0x4182000C; // beq-    0xC
    compile[count++] = 0x20C60000; // subfic  r6,r6,0
    compile[count++] = 0x7CA50190; // subfze  r5,r5
    compile[count++] = 0x7CA93379; // or.     r9,r5,r6
    compile[count++] = 0x39000000; // li      r8,0
    compile[count++] = 0x41820080; // beq-    0x80
    compile[count++] = 0x7CA90034; // cntlzw  r9,r5
    compile[count++] = 0x7CCA0034; // cntlzw  r10,r6
    compile[count++] = 0x552BD008; // rlwinm  r11,r9,26,0,4
    compile[count++] = 0x7D6BFE70; // srawi   r11,r11,31
    compile[count++] = 0x7D6B5038; // and     r11,r11,r10
    compile[count++] = 0x7D295A14; // add     r9,r9,r11
    compile[count++] = 0x21490020; // subfic  r10,r9,32
    compile[count++] = 0x3169FFE0; // addic   r11,r9,-32
    compile[count++] = 0x7CA54830; // slw     r5,r5,r9
    compile[count++] = 0x7CCC5430; // srw     r12,r6,r10
    compile[count++] = 0x7CA56378; // or      r5,r5,r12
    compile[count++] = 0x7CCC5830; // slw     r12,r6,r11
    compile[count++] = 0x7CA56378; // or      r5,r5,r12
    compile[count++] = 0x7CC64830; // slw     r6,r6,r9
    compile[count++] = 0x7D094050; // subf    r8,r9,r8
    compile[count++] = 0x54C9057E; // clrlwi  r9,r6,21
    compile[count++] = 0x2C090400; // cmpwi   r9,1024
    compile[count++] = 0x3908043E; // addi    r8,r8,1086
    compile[count++] = 0x4180001C; // blt-    0x1C
    compile[count++] = 0x4181000C; // bgt-    0xC
    compile[count++] = 0x54C90529; // rlwinm. r9,r6,0,20,20
    compile[count++] = 0x41820010; // beq-    0x10
    compile[count++] = 0x30C60800; // addic   r6,r6,2048
    compile[count++] = 0x7CA50194; // addze   r5,r5
    compile[count++] = 0x7D080194; // addze   r8,r8
    compile[count++] = 0x54C6A83E; // rotlwi  r6,r6,21
    compile[count++] = 0x50A6A814; // rlwimi  r6,r5,21,0,10
    compile[count++] = 0x54A5AB3E; // rlwinm  r5,r5,21,12,31
    compile[count++] = 0x5508A016; // slwi    r8,r8,20
    compile[count++] = 0x7D052B78; // or      r5,r8,r5
    compile[count++] = 0x7CE52B78; // or      r5,r7,r5
    compile[count++] = 0x90A10008; // stw     r5,8(r1)
    compile[count++] = 0x90C1000C; // stw     r6,12(r1)
    compile[count++] = 0xC8210008; // lfd     f1,8(r1)
    compile[count++] = 0x38210010; // addi    r1,r1,16
    compile[count++] = 0x81010008; // lwz     r8,8(r1)
    compile[count++] = 0x81210010; // lwz     r9,16(r1)
    compile[count++] = 0x81410018; // lwz     r10,24(r1)
    compile[count++] = 0x81610020; // lwz     r11,32(r1)
    compile[count++] = 0x81810028; // lwz     r12,40(r1)
    compile[count++] = 0x38210030; // addi    r1,r1,48
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_CEIL_W(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 13;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    //! @bug: This code truncates its input toward zero (via fctiwz), and adds 1
    //! if the input was positive. This almost works but is not correct for
    //! positive integer inputs.
    compile[count++] = 0x9421FFE0; // stwu    r1,-32(r1)
    compile[count++] = 0xC8030000 + (OFFSETOF(pCPU, aFPR) & 0xFFFF); // lfd     f0,0(r3)
    compile[count++] = 0xFC010040; // fcmpo   cr0,f1,f0
    compile[count++] = 0x4081000C; // ble-    0xC
    compile[count++] = 0x38C00001; // li      r6,1
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0xFC20081E; // fctiwz  f1,f1
    compile[count++] = 0xD8210010; // stfd    f1,16(r1)
    compile[count++] = 0x80A10014; // lwz     r5,20(r1)
    compile[count++] = 0x7CA62A14; // add     r5,r6,r5
    compile[count++] = 0x38210020; // addi    r1,r1,32
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_FLOOR_W(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 13;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    //! @bug: This code truncates its input toward zero (via fctiwz), and subtracts 1
    //! if the input was negative. This almost works but is not correct for
    //! negative integer inputs.
    compile[count++] = 0x9421FFE0; // stwu    r1,-32(r1)
    compile[count++] = 0xC8030000 + (OFFSETOF(pCPU, aFPR) & 0xFFFF); // lfd     f0,0(r3)
    compile[count++] = 0xFC010040; // fcmpo   cr0,f1,f0
    compile[count++] = 0x4180000C; // blt-    0xC
    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x38C00001; // li      r6,1
    compile[count++] = 0xFC20081E; // fctiwz  f1,f1
    compile[count++] = 0xD8210010; // stfd    f1,16(r1)
    compile[count++] = 0x80A10014; // lwz     r5,20(r1)
    compile[count++] = 0x7CA62850; // subf    r5,r6,r5
    compile[count++] = 0x38210020; // addi    r1,r1,32
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_ROUND_W(s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0xFC00081C; // fctiw   f0,f1
    compile[count++] = 0x7C051FAE; // stfiwx  f0,r5,r3
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_TRUNC_W(s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0xFC00081E; // fctiwz  f0,f1
    compile[count++] = 0x7C051FAE; // stfiwx  f0,r5,r3
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LB(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 11;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA538AE; // lbzx    r5,r5,r7
    compile[count++] = 0x7CA50774; // extsb   r5,r5
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LH(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 11;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA53A2E; // lhzx    r5,r5,r7
    compile[count++] = 0x7CA50734; // extsh   r5,r5
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LW(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA5382E; // lwzx    r5,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LBU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA538AE; // lbzx    r5,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LHU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA53A2E; // lhzx    r5,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_SB(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7D0539AE; // stbx    r8,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_SH(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7D053B2E; // sthx    r8,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_SW(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7D05392E; // stwx    r8,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LDC(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 12;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CE53A14; // add     r7,r5,r7
    compile[count++] = 0x80A70000; // lwz     r5,0(r7)
    compile[count++] = 0x80C70004; // lwz     r6,4(r7)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_SDC(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 12;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CE53A14; // add     r7,r5,r7
    compile[count++] = 0x91070000; // stw     r8,0(r7)
    compile[count++] = 0x91270004; // stw     r9,4(r7)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LWL(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 12;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x38C00018; // li      r6,24
    compile[count++] = 0x88A70000; // lbz     r5,0(r7)
    compile[count++] = 0x7CA53030; // slw     r5,r5,r6
    compile[count++] = 0x394000FF; // li      r10,255
    compile[count++] = 0x7D4A3030; // slw     r10,r10,r6
    compile[count++] = 0x7D295078; // andc    r9,r9,r10
    compile[count++] = 0x7D292B78; // or      r9,r9,r5
    compile[count++] = 0x38C6FFF8; // addi    r6,r6,-8
    compile[count++] = 0x54E507BF; // clrlwi. r5,r7,30
    compile[count++] = 0x38E70001; // addi    r7,r7,1
    compile[count++] = 0x4082FFDC; // bne+    0xFFFFFFDC
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LWR(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 12;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0x88A70000; // lbz     r5,0(r7)
    compile[count++] = 0x7CA53030; // slw     r5,r5,r6
    compile[count++] = 0x394000FF; // li      r10,255
    compile[count++] = 0x7D4A3030; // slw     r10,r10,r6
    compile[count++] = 0x7D295078; // andc    r9,r9,r10
    compile[count++] = 0x7D292B78; // or      r9,r9,r5
    compile[count++] = 0x38C60008; // addi    r6,r6,8
    compile[count++] = 0x54E507BF; // clrlwi. r5,r7,30
    compile[count++] = 0x38E7FFFF; // addi    r7,r7,-1
    compile[count++] = 0x4082FFDC; // bne+    0xFFFFFFDC
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}
