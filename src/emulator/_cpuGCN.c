/**
 * @file _cpuGCN.c
 *
 * MIPS instruction emulation for GameCube. This file is included into cpu.c
 * instead of being compiled separately.
 */
#include "emulator/cpu.h"

// Line numbers for different versions
#undef LN
#if VERSION == MQ_J
#define LN(mq_j) mq_j
#elif IS_OOT
#define LN(mq_j) (mq_j + 4)
#elif IS_MM_JP
#define LN(mq_j) (mq_j + 206)
#elif IS_MM_US
#define LN(mq_j) (mq_j + 85)
#elif IS_MM_EU
#define LN(mq_j) (mq_j + 91)
#endif

static inline bool cpuNoBranchTo(CpuFunction* pFunction, s32 addressN64);
static inline bool cpuCutStoreLoad(Cpu* pCPU, s32 currentAddress, s32 source);
static inline bool cpuCutStoreLoadF(Cpu* pCPU, s32 currentAddress, s32 source);
static inline bool cpuStackOffset(Cpu* pCPU, s32 currentAddress, s32* anCode, s32 source, s32 target);
static bool cpuNextInstruction(Cpu* pCPU, s32 addressN64, s32 opcode, s32* anCode, s32* iCode);
static inline bool cpuMakeCachedAddress(Cpu* pCPU, s32 nAddressN64, s32 nAddressHost, CpuFunction* pFunction);
static bool cpuFindCachedAddress(Cpu* pCPU, s32 nAddressN64, s32* pnAddressHost);
static bool cpuSetTLB(Cpu* pCPU, s32 iEntry);
static void treeCallerInit(CpuCallerID* block, s32 total);
static bool treeKillReason(Cpu* pCPU, s32* value);
static bool treeTimerCheck(Cpu* pCPU);
static bool treeCleanUp(Cpu* pCPU, CpuTreeRoot* root);
static inline bool treeForceCleanUp(Cpu* pCPU, CpuFunction* tree, s32 kill_limit);

static s32 cpuCompile_DSLLV_function;
static s32 cpuCompile_DSRLV_function;
static s32 cpuCompile_DSRAV_function;
static s32 cpuCompile_DMULT_function;
static s32 cpuCompile_DMULTU_function;
static s32 cpuCompile_DDIV_function;
static s32 cpuCompile_DDIVU_function;
static s32 cpuCompile_DADD_function;
static s32 cpuCompile_DADDU_function;
static s32 cpuCompile_DSUB_function;
static s32 cpuCompile_DSUBU_function;
static s32 cpuCompile_S_SQRT_function;
static s32 cpuCompile_D_SQRT_function;
static s32 cpuCompile_W_CVT_SD_function;
static s32 cpuCompile_L_CVT_SD_function;
static s32 cpuCompile_CEIL_W_function;
static s32 cpuCompile_FLOOR_W_function;
static s32 cpuCompile_ROUND_W_function;
static s32 cpuCompile_TRUNC_W_function;
static s32 cpuCompile_LB_function;
static s32 cpuCompile_LH_function;
static s32 cpuCompile_LW_function;
static s32 cpuCompile_LBU_function;
static s32 cpuCompile_LHU_function;
static s32 cpuCompile_SB_function;
static s32 cpuCompile_SH_function;
static s32 cpuCompile_SW_function;
static s32 cpuCompile_LDC_function;
static s32 cpuCompile_SDC_function;
static s32 cpuCompile_LWL_function;
static s32 cpuCompile_LWR_function;

extern s32 ganMapGPR[32];

static inline bool cpuFindBranchOffset(CpuFunction* pFunction, s32* pnOffset, s32 nAddress, s32* anCode) {
    s32 iJump;

    if (anCode == NULL) {
        *pnOffset = 0;
        return true;
    }

    for (iJump = 0; iJump < pFunction->nCountJump; iJump++) {
        if (pFunction->aJump[iJump].nAddressN64 == nAddress) {
            *pnOffset = pFunction->aJump[iJump].nOffsetHost;
            return true;
        }
    }

    return false;
}

/**
 * @brief Checks the type of delay an instruction has.
 *
 * @param opcode The instruction to determine the delay type for.
 * @return s32 The type of delay the instruction has.
 */
static s32 cpuCheckDelaySlot(u32 opcode) {
    s32 flag = 0;

    if (opcode == 0) {
        return 0;
    }

    switch (MIPS_OP(opcode)) {
        case 0x00: // special
            switch (MIPS_FUNCT(opcode)) {
                case 0x08: // jr
                    flag = 0xD05;
                    break;
                case 0x09: // jalr
                    flag = 0x8AE;
                    break;
            }
            break;
        case 0x01: // regimm
            switch (MIPS_RT(opcode)) {
                case 0x00: // bltz
                case 0x01: // bgez
                case 0x02: // bltzl
                case 0x03: // bgezl
                case 0x10: // bltzal
                case 0x11: // bgezal
                case 0x12: // bltzall
                case 0x13: // bgezall
                    flag = 0x457;
                    break;
            }
            break;
        case 0x10: // cop0
            switch (MIPS_FUNCT(opcode)) {
                case 0x01:
                case 0x02:
                case 0x05:
                case 0x08:
                case 0x18:
                    break;
                default:
                case 0x00:
                case 0x03:
                case 0x04:
                case 0x06:
                case 0x07:
                case 0x09:
                case 0x0A:
                case 0x0B:
                case 0x0C:
                case 0x0D:
                case 0x0E:
                case 0x0F:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                    switch (MIPS_RS(opcode)) {
                        case 0x08:
                            switch (MIPS_RT(opcode)) {
                                case 0x00:
                                case 0x01:
                                case 0x02:
                                case 0x03:
                                    flag = 0x457;
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 0x11: // cop1
            if (MIPS_RS(opcode) == 0x08) {
                switch (MIPS_RT(opcode)) {
                    case 0x00: // bc1f
                    case 0x01: // bc1t
                    case 0x02: // bc1fl
                    case 0x03: // bc1tl
                        flag = 0x457;
                        break;
                }
            }
            break;
        case 0x02: // j
            flag = 0xD05;
            break;
        case 0x03: // jal
            flag = 0x8AE;
            break;
        case 0x04: // beq
        case 0x05: // bne
        case 0x06: // blez
        case 0x07: // bgtz
        case 0x14: // beql
        case 0x15: // bnel
        case 0x16: // blezl
        case 0x17: // bgtzl
            flag = 0x457;
            break;
    }

    return flag;
}

/**
 * @brief Fills a code section of NOPs
 *
 * @param anCode Pointer to fill nops to.
 * @param iCode Position in @code to start filling.
 * @param number The amount of NOPs to fill.
 */
static inline void cpuCompileNOP(s32* anCode, s32* iCode, s32 number) {
    if (anCode == NULL) {
        *iCode += number;
    } else {
        while (number-- != 0) {
            anCode[(*iCode)++] = 0x60000000;
        }
    }
}

#define EMIT_PPC(i, instruction)       \
    do {                               \
        if (anCode != NULL) {          \
            anCode[i++] = instruction; \
        } else {                       \
            i++;                       \
        }                              \
    } while (0)

// Note: the original compiler (GC/1.1) doesn't understand this but it's useful for modding as it helps reduce the
// compiling time.
#pragma optimization_level 1

/**
 * @brief The main MIPS->PPC Dynamic recompiler.
 *
 * @param pCPU The emulated VR4300.
 * @param pnAddress The address to recompile.
 * @param pFunction The function that is being recompiled.
 * @param anCode Pointer to the recompiled code.
 * @param piCode Pointer to the current position in the recompiled code.
 * @param bSlot true if we are recompiling a delay slot.
 * @return bool true on success, false otherwise.
 */
static bool cpuGetPPC(Cpu* pCPU, s32* pnAddress, CpuFunction* pFunction, s32* anCode, s32* piCode, bool bSlot) {
    s32 nSize;
    s32 iHack;
    bool bInterpret;
    s32 iCode;
    s32 pad1;
    s32 iJump;
    s32 nAddress;
    s32 nReturnAddress;
    s32 nDeltaAddress;
    bool bFlag;
    s32 nAddressJump;
    s32 nOffset;
    u32 nOpcode;
    u32 nOpcodePrev;
    u32 nOpcodeNext;
    u32* pnOpcode;
    s32 prev;
    s32 iRegisterA;
    s32 iRegisterB;
    s32 iRegisterC;
    s32 nTemp1;
    s32 nTemp2;
    s32 nTemp3;
    bool update;
    s32 reg;
    s32 iUpdate;
    s32 nTarget;
    s32 var_r24;
    s32 var_r22;
    bool var_r17;
    bool var_r3;
    u8 pad2[0x50];

    bFlag = true;
    prev = 0;
    update = false;

    if (ramGetBuffer(SYSTEM_RAM(pCPU->pHost), (void**)&pnOpcode, *pnAddress, NULL)) {
        nAddress = *pnAddress;
        nOpcode = pnOpcode[0];
        nOpcodeNext = pnOpcode[1];
        nOpcodePrev = pnOpcode[-1];

        bInterpret = false;
        *pnAddress += 4;

        for (iHack = 0; iHack < pCPU->nCountCodeHack; iHack++) {
            if (pCPU->aCodeHack[iHack].nAddress == nAddress && pCPU->aCodeHack[iHack].nOpcodeOld == nOpcode) {
                if (pCPU->aCodeHack[iHack].nOpcodeNew == 0xFFFFFFFF) {
                    bInterpret = true;
                } else {
                    nOpcode = pCPU->aCodeHack[iHack].nOpcodeNew;
                }
            }
            if (pCPU->aCodeHack[iHack].nAddress == nAddress + 4 && pCPU->aCodeHack[iHack].nOpcodeOld == nOpcodeNext) {
                if (pCPU->aCodeHack[iHack].nOpcodeNew != 0xFFFFFFFF) {
                    nOpcodeNext = pCPU->aCodeHack[iHack].nOpcodeNew;
                }
            }

            if (pCPU->aCodeHack[iHack].nAddress == nAddress - 4 && pCPU->aCodeHack[iHack].nOpcodeOld == nOpcodePrev) {
                if (pCPU->aCodeHack[iHack].nOpcodeNew != 0xFFFFFFFF) {
                    nOpcodePrev = pCPU->aCodeHack[iHack].nOpcodeNew;
                }
            }
        }

        iCode = *piCode;
        nAddressJump = -1;
        pCPU->nOptimize.addr_check = 0;
        if (iCode == 0) {
            pCPU->nOptimize.addr_last = -1;
            if (!bInterpret && cpuCheckDelaySlot(nOpcode) == 0) {
                if (((s32)(pFunction->nAddress1 - pFunction->nAddress0) >> 2) + 1 > 25) {
                    bInterpret = true;
                } else {
                    update = true;
                }
            }
            if (anCode != NULL) {
                anCode[iCode++] = 0x3CA00000 | ((u32)pFunction >> 16);
                anCode[iCode++] = 0x60A50000 | ((u32)pFunction & 0xFFFF);
                anCode[iCode++] = 0x90A30000 + (OFFSETOF(pCPU, pFunctionLast) & 0xFFFF);
                anCode[iCode++] = 0x80C50000 + OFFSETOF(pFunction, timeToLive);
                anCode[iCode++] = 0x2C060000;
                anCode[iCode++] = 0x41820008;
                anCode[iCode++] = 0x90850000 + OFFSETOF(pFunction, timeToLive);
            } else {
                iCode += 7;
            }
            if (update) {
                if (anCode != NULL) {
                    anCode[iCode++] = 0x80A30000 + OFFSETOF(pCPU, nRetrace);
                    anCode[iCode++] = 0x80C30000 + OFFSETOF(pCPU, nRetraceUsed);
                    anCode[iCode++] = 0x7CA62850;
                    anCode[iCode++] = 0x2C050002;
                    anCode[iCode++] = 0x41800014;
                    anCode[iCode++] = 0x3CA00000 | ((u32)nAddress >> 16);
                    anCode[iCode++] = 0x60A50000 | ((u32)nAddress & 0xFFFF);
                    anCode[iCode++] = 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1;
                    iUpdate = iCode++;
                } else {
                    iCode += 9;
                }
            }
            *piCode = iCode;
        } else {
            prev = cpuCheckDelaySlot(nOpcodePrev);
        }

        var_r17 = nOpcode != 0 && (prev != 0 || bSlot) ? true : false;
        if (!bInterpret) {
            if (anCode == NULL || var_r17) {
                pCPU->nOptimize.destGPR_check = 0;
                pCPU->nOptimize.destFPR_check = 0;
                pCPU->nOptimize.addr_last = -1;
                pCPU->nOptimize.checkNext = 0;
            }

            switch (MIPS_OP(nOpcode)) {
                case 0x00: // special
                    switch (MIPS_FUNCT(nOpcode)) {
                        case 0x00: // sll
                            if (nOpcode != 0) {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                                if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                    iRegisterA = 5;
                                }
                                if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                    iRegisterB = 6;
                                    if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                        EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                            (iRegisterB << 16) |
                                                            (pCPU->nOptimize.destGPR_mapping << 11));
                                    } else {
                                        EMIT_PPC(iCode,
                                                 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                    }
                                }
                                nTemp1 = MIPS_SA(nOpcode);
                                nTemp2 = 31 - nTemp1;
                                EMIT_PPC(iCode, 0x54000000 | (iRegisterB << 21) | (iRegisterA << 16) | (nTemp1 << 11) |
                                                    (nTemp2 << 1));
                                if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                    pCPU->nOptimize.destGPR_check = 2;
                                    pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                    pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    EMIT_PPC(iCode,
                                             0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                                }
                            } else {
                                EMIT_PPC(iCode, 0x60000000);
                            }
                            break;
                        case 0x02: // srl
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            nTemp1 = MIPS_SA(nOpcode);
                            nTemp2 = 32 - nTemp1;
                            EMIT_PPC(iCode, 0x54000000 | (iRegisterB << 21) | (iRegisterA << 16) | (nTemp2 << 11) |
                                                (nTemp1 << 6) | 0x3E);
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x03: // sra
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            nTemp1 = MIPS_SA(nOpcode);
                            EMIT_PPC(iCode, 0x7C000670 | (iRegisterB << 21) | (iRegisterA << 16) | (nTemp1 << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x04: // sllv
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x70000000 | (iRegisterC << 21) | (iRegisterC << 16) | 0x1F);
                            EMIT_PPC(iCode, 0x7C000030 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterC << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x06: // srlv
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x70000000 | (iRegisterC << 21) | (iRegisterC << 16) | 0x1F);
                            EMIT_PPC(iCode, 0x7C000430 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterC << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x07: // srav
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x70000000 | (iRegisterC << 21) | (iRegisterC << 16) | 0x1F);
                            EMIT_PPC(iCode, 0x7C000630 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterC << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x08: // jr
                            if (nOpcodeNext != 0) {
                                if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                    return false;
                                }
                                *pnAddress -= 4;
                            }
                            if (MIPS_RS(nOpcode) != 31) {
                                pCPU->nOptimize.validCheck = 0;
                            }
                            if (MIPS_RS(nOpcode) == 31 && !(pCPU->nFlagCODE & 2)) {
                                if ((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                    iRegisterA = 5;
                                    EMIT_PPC(iCode,
                                             0x80A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                                EMIT_PPC(iCode, 0x7C0803A6 | ((iRegisterA & 0x1F) << 21));
                                EMIT_PPC(iCode, 0x4E800020);
                            } else {
                                if ((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                    EMIT_PPC(iCode,
                                             0x80A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                } else {
                                    EMIT_PPC(iCode, 0x7C050378 | (iRegisterA << 21) | (iRegisterA << 11));
                                }
                                EMIT_PPC(iCode,
                                         0x48000000 | (((u32)pCPU->pfJump - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            }
                            break;
                        case 0x09: // jalr
                            if (nOpcodeNext != 0) {
                                if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                    return false;
                                }
                                *pnAddress -= 4;
                            }
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, pFunctionLast));
                            EMIT_PPC(iCode, 0x3CE08000);
                            EMIT_PPC(iCode, 0x80C50000 + OFFSETOF(pFunction, timeToLive));
                            EMIT_PPC(iCode, 0x7CC63B78);
                            EMIT_PPC(iCode, 0x3CE00000 | (((u32)nAddress + 8) >> 16));
                            EMIT_PPC(iCode, 0x90C50000 + OFFSETOF(pFunction, timeToLive));
                            EMIT_PPC(iCode, 0x60E70000 | (((u32)nAddress + 8) & 0xFFFF));
                            EMIT_PPC(iCode, 0x90E30000 + OFFSETOF(pCPU, nReturnAddrLast));
                            if ((iRegisterB = ganMapGPR[31]) & 0x100) {
                                nReturnAddress = (u32)&anCode[iCode] + 20;
                                EMIT_PPC(iCode, 0x3CA00000 | ((u32)nReturnAddress >> 16));
                                EMIT_PPC(iCode, 0x60A50000 | ((u32)nReturnAddress & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[31]) + 4) & 0xFFFF));
                            } else {
                                u32 temp; // TODO: fake match

                                nReturnAddress = (u32)&anCode[iCode] + 16;
                                temp = nReturnAddress;
                                EMIT_PPC(iCode, 0x3C000000 | ((u32)nReturnAddress >> 16) | (iRegisterB << 21));
                                EMIT_PPC(iCode,
                                         0x60000000 | ((u32)temp & 0xFFFF) | (iRegisterB << 21) | (iRegisterB << 16));
                            }
                            if ((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, 0x80A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            } else {
                                EMIT_PPC(iCode, 0x7C050378 | (iRegisterA << 21) | (iRegisterA << 11));
                            }
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfJump - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            if (anCode != NULL) {
                                anCode[iCode++] = 0x3CA00000 | ((u32)pFunction >> 16);
                                anCode[iCode++] = 0x60A50000 | ((u32)pFunction & 0xFFFF);
                                anCode[iCode++] = 0x90A30000 + (OFFSETOF(pCPU, pFunctionLast) & 0xFFFF);
                                anCode[iCode++] = 0x3CE08000;
                                anCode[iCode++] = 0x80C50000 + OFFSETOF(pFunction, timeToLive);
                                anCode[iCode++] = 0x7CC63878;
                                anCode[iCode++] = 0x2C060000;
                                anCode[iCode++] = 0x41820008;
                                anCode[iCode++] = 0x90850000 + OFFSETOF(pFunction, timeToLive);
                            } else {
                                iCode += 9;
                            }
                            iJump = iCode++;
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (iCode - iJump) * 4;
                            }
                            EMIT_PPC(iJump, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            break;
                        case 0x0C: // syscall
                        case 0x0D: // break
                        case 0x0F: // sync
                            break;
                        case 0x10: // mfhi
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, 0x80A30000 | ((OFFSETOF(pCPU, nHi) + 4) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                                EMIT_PPC(iCode, 0x80A30000 | (OFFSETOF(pCPU, nHi) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) & 0xFFFF));
                            } else {
                                EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, nHi) + 4));
                                EMIT_PPC(iCode, 0x80A30000 | (OFFSETOF(pCPU, nHi) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) & 0xFFFF));
                            }
                            break;
                        case 0x11: // mthi
                            if ((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, 0x80A30000 | ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nHi) + 4) & 0xFFFF));
                                EMIT_PPC(iCode, 0x80A30000 | (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | (OFFSETOF(pCPU, nHi) & 0xFFFF));
                            } else {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, nHi) + 4));
                                EMIT_PPC(iCode, 0x80A30000 | (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | (OFFSETOF(pCPU, nHi) & 0xFFFF));
                            }
                            break;
                        case 0x12: // mflo
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, 0x80A30000 | ((OFFSETOF(pCPU, nLo) + 4) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                                EMIT_PPC(iCode, 0x80A30000 | (OFFSETOF(pCPU, nLo) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) & 0xFFFF));
                            } else {
                                EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, nLo) + 4));
                                EMIT_PPC(iCode, 0x80A30000 | (OFFSETOF(pCPU, nLo) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) & 0xFFFF));
                            }
                            break;
                        case 0x13: // mtlo
                            if ((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, 0x80A30000 | ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nLo) + 4) & 0xFFFF));
                                EMIT_PPC(iCode, 0x80A30000 | (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | (OFFSETOF(pCPU, nLo) & 0xFFFF));
                            } else {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, nLo) + 4));
                                EMIT_PPC(iCode, 0x80A30000 | (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) & 0xFFFF));
                                EMIT_PPC(iCode, 0x90A30000 | (OFFSETOF(pCPU, nLo) & 0xFFFF));
                            }
                            break;
                        case 0x14: // dsllv
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DSLLV_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x16: // dsrlv
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DSRLV_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x17: // dsrav
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DSRAV_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x18: // mult
                            iRegisterA = 5;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                            EMIT_PPC(iCode, 0x7C0001D6 | (iRegisterA << 21) | (iRegisterB << 16) | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nLo) + 4) & 0xFFFF));
                            EMIT_PPC(iCode, 0x7C000096 | (iRegisterA << 21) | (iRegisterB << 16) | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nHi) + 4) & 0xFFFF));
                            break;
                        case 0x19: // multu
                            iRegisterA = 5;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                            EMIT_PPC(iCode, 0x7C0001D6 | (iRegisterA << 21) | (iRegisterB << 16) | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nLo) + 4) & 0xFFFF));
                            EMIT_PPC(iCode, 0x7C000016 | (iRegisterA << 21) | (iRegisterB << 16) | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nHi) + 4) & 0xFFFF));
                            break;
                        case 0x1A: // div
                            iRegisterA = 5;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                            EMIT_PPC(iCode, 0x7C0003D6 | (iRegisterA << 21) | (iRegisterB << 16) | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nLo) + 4) & 0xFFFF));
                            EMIT_PPC(iCode, 0x7CA501D6 | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x7CA50050 | (iRegisterB << 11));
                            EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nHi) + 4) & 0xFFFF));
                            break;
                        case 0x1B: // divu
                            iRegisterA = 5;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                            EMIT_PPC(iCode, 0x7C000396 | (iRegisterA << 21) | (iRegisterB << 16) | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nLo) + 4) & 0xFFFF));
                            EMIT_PPC(iCode, 0x7CA501D6 | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x7CA50050 | (iRegisterB << 11));
                            EMIT_PPC(iCode, 0x90A30000 | ((OFFSETOF(pCPU, nHi) + 4) & 0xFFFF));
                            break;
                        case 0x1C: // dmult
                            if (!((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            EMIT_PPC(iCode, 0x9421FFC0);
                            EMIT_PPC(iCode, 0x91010008);
                            EMIT_PPC(iCode, 0x91210010);
                            EMIT_PPC(iCode, 0x91410018);
                            EMIT_PPC(iCode, 0x91610020);
                            EMIT_PPC(iCode, 0x91810028);
                            EMIT_PPC(iCode, 0x91C10030);
                            EMIT_PPC(iCode, 0x91E10038);
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81030004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81C30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x81E30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DMULT_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x81010008);
                            EMIT_PPC(iCode, 0x81210010);
                            EMIT_PPC(iCode, 0x81410018);
                            EMIT_PPC(iCode, 0x81610020);
                            EMIT_PPC(iCode, 0x81810028);
                            EMIT_PPC(iCode, 0x81C10030);
                            EMIT_PPC(iCode, 0x81E10038);
                            EMIT_PPC(iCode, 0x38210040);
                            break;
                        case 0x1D: // dmultu
                            if (!((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            EMIT_PPC(iCode, 0x9421FFD0);
                            EMIT_PPC(iCode, 0x91010008);
                            EMIT_PPC(iCode, 0x91210010);
                            EMIT_PPC(iCode, 0x91410018);
                            EMIT_PPC(iCode, 0x91610020);
                            EMIT_PPC(iCode, 0x91810028);
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81030004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x48000000 |
                                                ((cpuCompile_DMULTU_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x81010008);
                            EMIT_PPC(iCode, 0x81210010);
                            EMIT_PPC(iCode, 0x81410018);
                            EMIT_PPC(iCode, 0x81610020);
                            EMIT_PPC(iCode, 0x81810028);
                            EMIT_PPC(iCode, 0x38210030);
                            break;
                        case 0x1E: // ddiv
                            if (!((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            EMIT_PPC(iCode, 0x9421FFC0);
                            EMIT_PPC(iCode, 0x91010008);
                            EMIT_PPC(iCode, 0x91210010);
                            EMIT_PPC(iCode, 0x91410018);
                            EMIT_PPC(iCode, 0x91610020);
                            EMIT_PPC(iCode, 0x91810028);
                            EMIT_PPC(iCode, 0x91C10030);
                            EMIT_PPC(iCode, 0x91E10038);
                            EMIT_PPC(iCode, 0x81030000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x81230004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x81430000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81630004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81C30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x81E30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DDIV_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x81010008);
                            EMIT_PPC(iCode, 0x81210010);
                            EMIT_PPC(iCode, 0x81410018);
                            EMIT_PPC(iCode, 0x81610020);
                            EMIT_PPC(iCode, 0x81810028);
                            EMIT_PPC(iCode, 0x81C10030);
                            EMIT_PPC(iCode, 0x81E10038);
                            EMIT_PPC(iCode, 0x38210040);
                            break;
                        case 0x1F: // ddivu
                            if (!((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            EMIT_PPC(iCode, 0x9421FFD0);
                            EMIT_PPC(iCode, 0x91010008);
                            EMIT_PPC(iCode, 0x91210010);
                            EMIT_PPC(iCode, 0x91410018);
                            EMIT_PPC(iCode, 0x91610020);
                            EMIT_PPC(iCode, 0x91810028);
                            EMIT_PPC(iCode, 0x81030000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x81230004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x81430000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81630004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DDIVU_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x81010008);
                            EMIT_PPC(iCode, 0x81210010);
                            EMIT_PPC(iCode, 0x81410018);
                            EMIT_PPC(iCode, 0x81610020);
                            EMIT_PPC(iCode, 0x81810028);
                            EMIT_PPC(iCode, 0x38210030);
                            break;
                        case 0x20: { // add
                            bool var_r10;

                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }

                            var_r10 = false;
                            var_r3 = false;
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                                var_r3 = true;
                            }

                            if (MIPS_RS(nOpcode) == 0) {
                                if (MIPS_RT(nOpcode) == 31 && !(pCPU->nFlagCODE & 4)) {
                                    EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, nReturnAddrLast));
                                    EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                                    var_r10 = true;
                                    pCPU->nFlagCODE |= 8;
                                } else if (!var_r3) {
                                    if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                    } else {
                                        EMIT_PPC(iCode, 0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) |
                                                            (iRegisterB << 11));
                                    }
                                } else {
                                    if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                        pCPU->nOptimize.destGPR_check = 2;
                                        pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    } else {
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                    }
                                }

                                if (MIPS_RD(nOpcode) == 31) {
                                    pCPU->nFlagCODE |= 2;
                                    if (pCPU->nFlagCODE & 8) {
                                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                            iRegisterB = 6;
                                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) &
                                                                          0xFFFF));
                                        }
                                        EMIT_PPC(iCode,
                                                 (0x90030000 | (iRegisterB << 21)) + OFFSETOF(pCPU, nReturnAddrLast));
                                    }
                                }
                            } else if (MIPS_RT(nOpcode) == 0) {
                                if ((MIPS_RS(nOpcode) == 31) && !(pCPU->nFlagCODE & 4)) {
                                    EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, nReturnAddrLast));
                                    EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                                    var_r10 = true;
                                    pCPU->nFlagCODE |= 8;
                                } else if (!var_r3) {
                                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                                    } else {
                                        EMIT_PPC(iCode, 0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) |
                                                            (iRegisterB << 11));
                                    }
                                } else {
                                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                        pCPU->nOptimize.destGPR_check = 2;
                                        pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    } else {
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                    }
                                }

                                if (MIPS_RD(nOpcode) == 31) {
                                    pCPU->nFlagCODE |= 2;
                                    if (pCPU->nFlagCODE & 8) {
                                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                            iRegisterB = 6;
                                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) &
                                                                          0xFFFF));
                                        }
                                        EMIT_PPC(iCode,
                                                 (0x90030000 | (iRegisterB << 21)) + OFFSETOF(pCPU, nReturnAddrLast));
                                    }
                                }
                            } else {
                                if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                    iRegisterB = 6;
                                    if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                        EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                            (iRegisterB << 16) |
                                                            (pCPU->nOptimize.destGPR_mapping << 11));
                                    } else {
                                        EMIT_PPC(iCode,
                                                 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                    }
                                }
                                if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                    iRegisterC = 7;
                                    if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                        EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                            (iRegisterC << 16) |
                                                            (pCPU->nOptimize.destGPR_mapping << 11));
                                    } else {
                                        EMIT_PPC(iCode,
                                                 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                    }
                                }
                                EMIT_PPC(iCode,
                                         0x7C000214 | (iRegisterA << 21) | (iRegisterB << 16) | (iRegisterC << 11));
                                var_r10 = true;
                            }
                            if (var_r10 && (ganMapGPR[MIPS_RD(nOpcode)] & 0x100)) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        }
                        case 0x21: { // addu
                            bool var_r10;

                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }

                            var_r10 = false;
                            var_r3 = false;
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                                var_r3 = true;
                            }

                            if (MIPS_RS(nOpcode) == 0) {
                                if (MIPS_RT(nOpcode) == 31 && !(pCPU->nFlagCODE & 4)) {
                                    EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, nReturnAddrLast));
                                    EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                                    var_r10 = true;
                                    pCPU->nFlagCODE |= 8;
                                } else if (!var_r3) {
                                    if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                    } else {
                                        EMIT_PPC(iCode, 0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) |
                                                            (iRegisterB << 11));
                                    }
                                } else {
                                    if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                        pCPU->nOptimize.destGPR_check = 2;
                                        pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    } else {
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                    }
                                }

                                if (MIPS_RD(nOpcode) == 31) {
                                    pCPU->nFlagCODE |= 2;
                                    if (pCPU->nFlagCODE & 8) {
                                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                            iRegisterB = 6;
                                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) &
                                                                          0xFFFF));
                                        }
                                        EMIT_PPC(iCode,
                                                 (0x90030000 | (iRegisterB << 21)) + OFFSETOF(pCPU, nReturnAddrLast));
                                    }
                                }
                            } else if (MIPS_RT(nOpcode) == 0) {
                                if ((MIPS_RS(nOpcode) == 31) && !(pCPU->nFlagCODE & 4)) {
                                    EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, nReturnAddrLast));
                                    EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                                    var_r10 = true;
                                    pCPU->nFlagCODE |= 8;
                                } else if (!var_r3) {
                                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                                    } else {
                                        EMIT_PPC(iCode, 0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) |
                                                            (iRegisterB << 11));
                                    }
                                } else {
                                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                        pCPU->nOptimize.destGPR_check = 2;
                                        pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    } else {
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                    }
                                }

                                if (MIPS_RD(nOpcode) == 31) {
                                    pCPU->nFlagCODE |= 2;
                                    if (pCPU->nFlagCODE & 8) {
                                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                            iRegisterB = 6;
                                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) &
                                                                          0xFFFF));
                                        }
                                        EMIT_PPC(iCode,
                                                 (0x90030000 | (iRegisterB << 21)) + OFFSETOF(pCPU, nReturnAddrLast));
                                    }
                                }
                            } else {
                                if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                    iRegisterB = 6;
                                    if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                        EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                            (iRegisterB << 16) |
                                                            (pCPU->nOptimize.destGPR_mapping << 11));
                                    } else {
                                        EMIT_PPC(iCode,
                                                 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                    }
                                }
                                if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                    iRegisterC = 7;
                                    if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                        EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                            (iRegisterC << 16) |
                                                            (pCPU->nOptimize.destGPR_mapping << 11));
                                    } else {
                                        EMIT_PPC(iCode,
                                                 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                    }
                                }
                                EMIT_PPC(iCode,
                                         0x7C000214 | (iRegisterA << 21) | (iRegisterB << 16) | (iRegisterC << 11));
                                var_r10 = true;
                            }
                            if (var_r10 && (ganMapGPR[MIPS_RD(nOpcode)] & 0x100)) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        }
                        case 0x22: // sub
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x7C000050 | (iRegisterA << 21) | (iRegisterC << 16) | (iRegisterB << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x23: // subu
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x7C000050 | (iRegisterA << 21) | (iRegisterC << 16) | (iRegisterB << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x24: // and
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x7C000038 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterC << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x25: { // or
                            bool var_r10;

                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }

                            var_r10 = false;
                            var_r3 = false;
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                                var_r3 = true;
                            }

                            if (MIPS_RS(nOpcode) == 0) {
                                if (MIPS_RT(nOpcode) == 31 && !(pCPU->nFlagCODE & 4)) {
                                    EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, nReturnAddrLast));
                                    EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                                    var_r10 = true;
                                    pCPU->nFlagCODE |= 8;
                                } else if (!var_r3) {
                                    if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                    } else {
                                        EMIT_PPC(iCode, 0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) |
                                                            (iRegisterB << 11));
                                    }
                                } else {
                                    if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                        pCPU->nOptimize.destGPR_check = 2;
                                        pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    } else {
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                    }
                                }

                                if (MIPS_RD(nOpcode) == 31) {
                                    pCPU->nFlagCODE |= 2;
                                    if (pCPU->nFlagCODE & 8) {
                                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                            iRegisterB = 6;
                                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) &
                                                                          0xFFFF));
                                        }
                                        EMIT_PPC(iCode,
                                                 (0x90030000 | (iRegisterB << 21)) + OFFSETOF(pCPU, nReturnAddrLast));
                                    }
                                }
                            } else if (MIPS_RT(nOpcode) == 0) {
                                if ((MIPS_RS(nOpcode) == 31) && !(pCPU->nFlagCODE & 4)) {
                                    EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, nReturnAddrLast));
                                    EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                                    var_r10 = true;
                                    pCPU->nFlagCODE |= 8;
                                } else if (!var_r3) {
                                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                                    } else {
                                        EMIT_PPC(iCode, 0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) |
                                                            (iRegisterB << 11));
                                    }
                                } else {
                                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                        EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                        pCPU->nOptimize.destGPR_check = 2;
                                        pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    } else {
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                            (OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4));
                                    }
                                }

                                if (MIPS_RD(nOpcode) == 31) {
                                    pCPU->nFlagCODE |= 2;
                                    if (pCPU->nFlagCODE & 8) {
                                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                            iRegisterB = 6;
                                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) &
                                                                          0xFFFF));
                                        }
                                        EMIT_PPC(iCode,
                                                 (0x90030000 | (iRegisterB << 21)) + OFFSETOF(pCPU, nReturnAddrLast));
                                    }
                                }
                            } else {
                                if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                    iRegisterB = 6;
                                    if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                        EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                            (iRegisterB << 16) |
                                                            (pCPU->nOptimize.destGPR_mapping << 11));
                                    } else {
                                        EMIT_PPC(iCode,
                                                 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                    }
                                }
                                if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                    iRegisterC = 7;
                                    if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                        EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                            (iRegisterC << 16) |
                                                            (pCPU->nOptimize.destGPR_mapping << 11));
                                    } else {
                                        EMIT_PPC(iCode,
                                                 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                    }
                                }
                                EMIT_PPC(iCode,
                                         0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterC << 11));
                                var_r10 = true;
                            }
                            if (var_r10 && (ganMapGPR[MIPS_RD(nOpcode)] & 0x100)) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        }
                        case 0x26: // xor
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x7C000278 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterC << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x27: // nor
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x7C0000F8 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterC << 11));
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x2A: // slt
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x7C000000 | (iRegisterB << 16) | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x4180000C);
                            EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21));
                            EMIT_PPC(iCode, 0x42800008);
                            EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21) | 1);
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x2B: // sltu
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if ((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100) {
                                iRegisterA = 5;
                            }
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                iRegisterC = 7;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x7C000040 | (iRegisterB << 16) | (iRegisterC << 11));
                            EMIT_PPC(iCode, 0x4180000C);
                            EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21));
                            EMIT_PPC(iCode, 0x42800008);
                            EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21) | 1);
                            if (ganMapGPR[MIPS_RD(nOpcode)] & 0x100) {
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RD(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]) + 4) & 0xFFFF));
                            }
                            break;
                        case 0x2C: // dadd
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            iRegisterA = MIPS_RD(nOpcode);
                            EMIT_PPC(iCode, 0x9421FFF0);
                            EMIT_PPC(iCode, 0x91010008);
                            EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81030000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DADD_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x90A30004 + OFFSETOF(pCPU, aGPR[iRegisterA]));
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, aGPR[iRegisterA]));
                            EMIT_PPC(iCode, 0x81010008);
                            EMIT_PPC(iCode, 0x38210010);
                            if (!((iRegisterA = ganMapGPR[iRegisterA]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x2D: // daddu
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            iRegisterA = MIPS_RD(nOpcode);
                            EMIT_PPC(iCode, 0x9421FFF0);
                            EMIT_PPC(iCode, 0x91010008);
                            EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81030000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DADDU_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x90A30004 + OFFSETOF(pCPU, aGPR[iRegisterA]));
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, aGPR[iRegisterA]));
                            EMIT_PPC(iCode, 0x81010008);
                            EMIT_PPC(iCode, 0x38210010);
                            if (!((iRegisterA = ganMapGPR[iRegisterA]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x2E: // dsub
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            iRegisterA = MIPS_RD(nOpcode);
                            EMIT_PPC(iCode, 0x9421FFF0);
                            EMIT_PPC(iCode, 0x91010008);
                            EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81030000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DSUB_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x90A30004 + OFFSETOF(pCPU, aGPR[iRegisterA]));
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, aGPR[iRegisterA]));
                            EMIT_PPC(iCode, 0x81010008);
                            EMIT_PPC(iCode, 0x38210010);
                            if (!((iRegisterA = ganMapGPR[iRegisterA]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x2F: // dsubu
                            if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode)) || pCPU->nFlagRAM & (1 << MIPS_RT(nOpcode))) {
                                pCPU->nFlagRAM |= (1 << MIPS_RD(nOpcode));
                            } else {
                                pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            }
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            if (!((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            }
                            iRegisterA = MIPS_RD(nOpcode);
                            EMIT_PPC(iCode, 0x9421FFF0);
                            EMIT_PPC(iCode, 0x91010008);
                            EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                            EMIT_PPC(iCode, 0x80E30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x81030000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode,
                                     0x48000000 | ((cpuCompile_DSUBU_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x90A30004 + OFFSETOF(pCPU, aGPR[iRegisterA]));
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, aGPR[iRegisterA]));
                            EMIT_PPC(iCode, 0x81010008);
                            EMIT_PPC(iCode, 0x38210010);
                            if (!((iRegisterA = ganMapGPR[iRegisterA]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x30: // tge
                        case 0x31: // tgeu
                        case 0x32: // tlt
                        case 0x33: // tltu
                        case 0x34: // teq
                        case 0x36: // tne
                            break;
                        case 0x38: // dsll
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            nTemp1 = MIPS_SA(nOpcode);
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x54A50000 | (nTemp1 << 11) | ((31 - nTemp1) << 1));
                            EMIT_PPC(iCode, 0x50C50000 | (nTemp1 << 11) | ((32 - nTemp1) << 6) | (31 << 1));
                            EMIT_PPC(iCode, 0x54C60000 | (nTemp1 << 11) | ((31 - nTemp1) << 1));
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x3A: // dsrl
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            nTemp1 = MIPS_SA(nOpcode);
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x54C60000 | ((32 - nTemp1) << 11) | (nTemp1 << 6) | (31 << 1));
                            EMIT_PPC(iCode, 0x50A60000 | ((32 - nTemp1) << 11) | ((nTemp1 - 1) << 1));
                            EMIT_PPC(iCode, 0x54A50000 | ((32 - nTemp1) << 11) | (nTemp1 << 6) | (31 << 1));
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x3B: // dsra
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            nTemp1 = MIPS_SA(nOpcode);
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x54C60000 | ((32 - nTemp1) << 11) | (nTemp1 << 6) | (31 << 1));
                            EMIT_PPC(iCode, 0x50A60000 | ((32 - nTemp1) << 11) | ((nTemp1 - 1) << 1));
                            EMIT_PPC(iCode, 0x7CA50670 | (nTemp1 << 11));
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x3C: // dsll32
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            nTemp1 = MIPS_SA(nOpcode) + 32;
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            while (nTemp1 > 0) {
                                if (nTemp1 > 31) {
                                    nTemp2 = 31;
                                    nTemp1 -= 31;
                                } else {
                                    nTemp2 = nTemp1;
                                    nTemp1 = 0;
                                }
                                EMIT_PPC(iCode, 0x54A50000 | (nTemp2 << 11) | ((31 - nTemp2) << 1));
                                EMIT_PPC(iCode, 0x50C50000 | (nTemp2 << 11) | ((32 - nTemp2) << 6) | (31 << 1));
                                EMIT_PPC(iCode, 0x54C60000 | (nTemp2 << 11) | ((31 - nTemp2) << 1));
                            }
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x3E: // dsrl32
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            nTemp1 = MIPS_SA(nOpcode) + 32;
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            while (nTemp1 > 0) {
                                if (nTemp1 > 31) {
                                    nTemp2 = 31;
                                    nTemp1 -= 31;
                                } else {
                                    nTemp2 = nTemp1;
                                    nTemp1 = 0;
                                }
                                EMIT_PPC(iCode, 0x54C60000 | ((32 - nTemp2) << 11) | (nTemp2 << 6) | (31 << 1));
                                EMIT_PPC(iCode, 0x50A60000 | ((32 - nTemp2) << 11) | ((nTemp2 - 1) << 1));
                                EMIT_PPC(iCode, 0x54A50000 | ((32 - nTemp2) << 11) | (nTemp2 << 6) | (31 << 1));
                            }
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        case 0x3F: // dsra32
                            pCPU->nFlagRAM &= ~(1 << MIPS_RD(nOpcode));
                            if (!((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterC << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                            nTemp1 = MIPS_SA(nOpcode) + 32;
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                            while (nTemp1 > 0) {
                                if (nTemp1 > 31) {
                                    nTemp2 = 31;
                                    nTemp1 -= 31;
                                } else {
                                    nTemp2 = nTemp1;
                                    nTemp1 = 0;
                                }
                                EMIT_PPC(iCode, 0x54C60000 | ((32 - nTemp2) << 11) | (nTemp2 << 6) | (31 << 1));
                                EMIT_PPC(iCode, 0x50A60000 | ((32 - nTemp2) << 11) | ((nTemp2 - 1) << 1));
                                EMIT_PPC(iCode, 0x7CA50670 | (nTemp2 << 11));
                            }
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            EMIT_PPC(iCode, 0x90C30004 + OFFSETOF(pCPU, aGPR[MIPS_RD(nOpcode)]));
                            if (!((iRegisterA = ganMapGPR[MIPS_RD(nOpcode)]) & 0x100)) {
                                EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            }
                            break;
                        default:
                            bFlag = false;
                            break;
                    }
                    break;
                case 0x01: // regimm
                    switch (MIPS_RT(nOpcode)) {
                        case 0x00: // bltz
                            nAddressJump = *pnAddress + MIPS_IMM_S16(nOpcode) * 4;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));

                            iJump = iCode++;
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;

                            if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (nOffset - iCode) * 4;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            EMIT_PPC(iJump, 0x40800000 | (((iCode - iJump) & 0x3FFF) << 2));
                            break;
                        case 0x01: // bgez
                            nAddressJump = *pnAddress + MIPS_IMM_S16(nOpcode) * 4;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));

                            iJump = iCode++;
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;

                            if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (nOffset - iCode) * 4;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            EMIT_PPC(iJump, 0x41800000 | (((iCode - iJump) & 0x3FFF) << 2));
                            break;
                        case 0x02: // bltzl
                            nAddressJump = *pnAddress + MIPS_IMM_S16(nOpcode) * 4;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));

                            iJump = iCode++;
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;

                            if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (nOffset - iCode) * 4;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                                return false;
                            }
                            EMIT_PPC(iJump, 0x40800000 | (((iCode - iJump) & 0x3FFF) << 2));
                            break;
                        case 0x03: // bgezl
                            nAddressJump = *pnAddress + MIPS_IMM_S16(nOpcode) * 4;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));

                            iJump = iCode++;
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;

                            if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (nOffset - iCode) * 4;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                                return false;
                            }
                            EMIT_PPC(iJump, 0x41800000 | (((iCode - iJump) & 0x3FFF) << 2));
                            break;
                        case 0x08: // tgei
                        case 0x09: // tgeiu
                        case 0x0A: // tlti
                        case 0x0B: // tltiu
                        case 0x0C: // teqi
                        case 0x0E: // tnei
                            break;
                        case 0x10: // bltzal
                            nAddressJump = *pnAddress + MIPS_IMM_S16(nOpcode) * 4;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));

                            iJump = iCode;
                            iCode++;
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)(nAddress + 8) >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)(nAddress + 8) & 0xFFFF));
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, nReturnAddrLast));
                            if (ganMapGPR[31] & 0x100) {
                                iCode += 3;
                            } else {
                                iCode += 2;
                            }
                            var_r24 = (u32)&anCode[iCode];
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;

                            var_r22 = (u32)&anCode[iCode];
                            if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (nOffset - iCode) * 4;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            EMIT_PPC(iJump, 0x40800000 | (((iCode - iJump) * 4) & 0xFFFC));

                            iJump += 3;
                            nReturnAddress = (u32)&anCode[iCode] + (var_r22 - var_r24);
                            if ((iRegisterB = ganMapGPR[31]) & 0x100) {
                                EMIT_PPC(iJump, 0x3CA00000 | ((u32)nReturnAddress >> 16));
                                EMIT_PPC(iJump, 0x60A50000 | ((u32)nReturnAddress & 0xFFFF));
                                EMIT_PPC(iJump, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[31]) + 4) & 0xFFFF));
                            } else {
                                EMIT_PPC(iJump, 0x3C000000 | ((u32)nReturnAddress >> 16) | (iRegisterB << 21));
                                EMIT_PPC(iJump, 0x60000000 | ((u32)nReturnAddress & 0xFFFF) | (iRegisterB << 21) |
                                                    (iRegisterB << 16));
                            }
                            break;
                        case 0x11: // bgezal
                            nAddressJump = *pnAddress + MIPS_IMM_S16(nOpcode) * 4;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));

                            iJump = iCode++;
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)(nAddress + 8) >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)(nAddress + 8) & 0xFFFF));
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, nReturnAddrLast));
                            if (ganMapGPR[31] & 0x100) {
                                iCode += 3;
                            } else {
                                iCode += 2;
                            }
                            var_r24 = (u32)&anCode[iCode];
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;

                            var_r22 = (u32)&anCode[iCode];
                            if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (nOffset - iCode) * 4;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            EMIT_PPC(iJump, 0x41800000 | (((iCode - iJump) * 4) & 0xFFFC));

                            iJump += 3;
                            nReturnAddress = (u32)&anCode[iCode] + (var_r22 - var_r24);
                            if ((iRegisterB = ganMapGPR[31]) & 0x100) {
                                EMIT_PPC(iJump, 0x3CA00000 | ((u32)nReturnAddress >> 16));
                                EMIT_PPC(iJump, 0x60A50000 | ((u32)nReturnAddress & 0xFFFF));
                                EMIT_PPC(iJump, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[31]) + 4) & 0xFFFF));
                            } else {
                                EMIT_PPC(iJump, 0x3C000000 | ((u32)nReturnAddress >> 16) | (iRegisterB << 21));
                                EMIT_PPC(iJump, 0x60000000 | ((u32)nReturnAddress & 0xFFFF) | (iRegisterB << 21) |
                                                    (iRegisterB << 16));
                            }
                            break;
                        case 0x12: // bltzall
                            nAddressJump = *pnAddress + MIPS_IMM_S16(nOpcode) * 4;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));

                            iJump = iCode++;
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)(nAddress + 8) >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)(nAddress + 8) & 0xFFFF));
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, nReturnAddrLast));
                            if (ganMapGPR[31] & 0x100) {
                                iCode += 3;
                            } else {
                                iCode += 2;
                            }
                            var_r24 = (u32)&anCode[iCode];
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;

                            var_r22 = (u32)&anCode[iCode];
                            if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (nOffset - iCode) * 4;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                                return false;
                            }
                            EMIT_PPC(iJump, 0x40800000 | (((iCode - iJump) * 4) & 0xFFFC));

                            iJump += 3;
                            nReturnAddress = (u32)&anCode[iCode] + (var_r22 - var_r24);
                            if ((iRegisterB = ganMapGPR[31]) & 0x100) {
                                EMIT_PPC(iJump, 0x3CA00000 | ((u32)nReturnAddress >> 16));
                                EMIT_PPC(iJump, 0x60A50000 | ((u32)nReturnAddress & 0xFFFF));
                                EMIT_PPC(iJump, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[31]) + 4) & 0xFFFF));
                            } else {
                                EMIT_PPC(iJump, 0x3C000000 | ((u32)nReturnAddress >> 16) | (iRegisterB << 21));
                                EMIT_PPC(iJump, 0x60000000 | ((u32)nReturnAddress & 0xFFFF) | (iRegisterB << 21) |
                                                    (iRegisterB << 16));
                            }
                            break;
                        case 0x13: // bgezall
                            nAddressJump = *pnAddress + MIPS_IMM_S16(nOpcode) * 4;
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                iRegisterB = 6;
                                if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                    EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                        (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                                } else {
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                            }
                            EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));

                            iJump = iCode++;
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)(nAddress + 8) >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)(nAddress + 8) & 0xFFFF));
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, nReturnAddrLast));
                            if (ganMapGPR[31] & 0x100) {
                                iCode += 3;
                            } else {
                                iCode += 2;
                            }
                            var_r24 = (u32)&anCode[iCode];
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;

                            var_r22 = (u32)&anCode[iCode];
                            if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                return false;
                            }
                            if (anCode != NULL) {
                                nDeltaAddress = (nOffset - iCode) * 4;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                                return false;
                            }
                            EMIT_PPC(iJump, 0x41800000 | (((iCode - iJump) * 4) & 0xFFFC));

                            iJump += 3;
                            nReturnAddress = (u32)&anCode[iCode] + (var_r22 - var_r24);
                            if ((iRegisterB = ganMapGPR[31]) & 0x100) {
                                EMIT_PPC(iJump, 0x3CA00000 | ((u32)nReturnAddress >> 16));
                                EMIT_PPC(iJump, 0x60A50000 | ((u32)nReturnAddress & 0xFFFF));
                                EMIT_PPC(iJump, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[31]) + 4) & 0xFFFF));
                            } else {
                                EMIT_PPC(iJump, 0x3C000000 | ((u32)nReturnAddress >> 16) | (iRegisterB << 21));
                                EMIT_PPC(iJump, 0x60000000 | ((u32)nReturnAddress & 0xFFFF) | (iRegisterB << 21) |
                                                    (iRegisterB << 16));
                            }
                            break;
                        default:
                            bFlag = false;
                            break;
                    }
                    break;
                case 0x02: // j
                    nAddressJump = (*pnAddress & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
                    if (pFunction->nAddress0 <= nAddressJump && nAddressJump < pFunction->nAddress1) {
                        if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                            return false;
                        }
                        *pnAddress -= 4;
                        if (nAddressJump == nAddress) {
                            if (anCode != NULL) {
                                anCode[iCode++] = 0x3CA00000 | ((u32)nAddress >> 16);
                                anCode[iCode++] = 0x60A50000 | ((u32)nAddress & 0xFFFF);
                            } else {
                                iCode += 2;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfIdle - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                        if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                            return false;
                        }
                        if (anCode != NULL) {
                            nDeltaAddress = (nOffset - iCode) * 4;
                        }
                        EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    } else {
                        if (nOpcodeNext != 0) {
                            if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                return false;
                            }
                            *pnAddress -= 4;
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddressJump >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddressJump & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfJump - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        nAddressJump = -1;
                    }
                    break;
                case 0x03: // jal
                    nTarget = MIPS_TARGET(nOpcode) << 2;
                    if (nOpcodeNext != 0) {
                        if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                            return false;
                        }
                        *pnAddress -= 4;
                    }
                    EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, pFunctionLast));
                    EMIT_PPC(iCode, 0x3CE08000);
                    EMIT_PPC(iCode, 0x80C50000 + OFFSETOF(pFunction, timeToLive));
                    EMIT_PPC(iCode, 0x7CC63B78);
                    EMIT_PPC(iCode, 0x3CE00000 | ((u32)(nAddress + 8) >> 16));
                    EMIT_PPC(iCode, 0x90C50000 + OFFSETOF(pFunction, timeToLive));
                    EMIT_PPC(iCode, 0x60E70000 | ((u32)(nAddress + 8) & 0xFFFF));
                    EMIT_PPC(iCode, 0x90E30000 + OFFSETOF(pCPU, nReturnAddrLast));
                    nAddressJump = (*pnAddress & 0xF0000000) | nTarget;
                    if ((iRegisterB = ganMapGPR[31]) & 0x100) {
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddressJump >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddressJump & 0xFFFF));
                        EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[31]) + 4) & 0xFFFF));
                    } else {
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddressJump >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddressJump & 0xFFFF));
                    }
                    EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfCall - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                    if (pFunction->callerID_flag == 0x16) {
                        pFunction->block[pFunction->callerID_total].N64address = nAddressJump;
                    }
                    if (pFunction->callerID_flag != 0x21) {
                        pFunction->callerID_total++;
                    }
                    if (anCode != NULL) {
                        anCode[iCode++] = 0x3CA00000 | ((u32)pFunction >> 16);
                        anCode[iCode++] = 0x60A50000 | ((u32)pFunction & 0xFFFF);
                        anCode[iCode++] = 0x90A30000 + (OFFSETOF(pCPU, pFunctionLast) & 0xFFFF);
                        anCode[iCode++] = 0x3CE08000;
                        anCode[iCode++] = 0x80C50000 + OFFSETOF(pFunction, timeToLive);
                        anCode[iCode++] = 0x7CC63878;
                        anCode[iCode++] = 0x2C060000;
                        anCode[iCode++] = 0x41820008;
                        anCode[iCode++] = 0x90850000 + OFFSETOF(pFunction, timeToLive);
                    } else {
                        iCode += 9;
                    }
                    iJump = iCode++;
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                        return false;
                    }
                    if (anCode != NULL) {
                        nDeltaAddress = (iCode - iJump) * 4;
                    }
                    if (anCode != NULL) {
                        anCode[iJump] = 0x48000000 | (nDeltaAddress & 0x03FFFFFC);
                    }
                    nAddressJump = -1;
                    break;
                case 0x04: // beq
                    nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                    if (MIPS_RS(nOpcode) == MIPS_RT(nOpcode)) {
                        if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                            return false;
                        }
                        *pnAddress -= 4;
                        if (nAddressJump == nAddress) {
                            if (anCode != NULL) {
                                anCode[iCode++] = 0x3CA00000 | ((u32)nAddress >> 16);
                                anCode[iCode++] = 0x60A50000 | ((u32)nAddress & 0xFFFF);
                            } else {
                                iCode += 2;
                            }
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfIdle - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                        if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                            return false;
                        }
                        if (anCode != NULL) {
                            nDeltaAddress = (nOffset - iCode) * 4;
                        }
                        EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    } else {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterC = 7;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x7C000000 | (iRegisterB << 16) | (iRegisterC << 11));
                        iJump = iCode++;
                        if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                            return false;
                        }
                        *pnAddress -= 4;

                        if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                            return false;
                        }
                        if (anCode != NULL) {
                            nDeltaAddress = (nOffset - iCode) * 4;
                        }
                        EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                        EMIT_PPC(iJump, 0x40820000 | (((iCode - iJump) & 0x3FFF) << 2));
                    }
                    break;
                case 0x05: // bne
                    nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterC = 7;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterC << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x7C000000 | (iRegisterB << 16) | (iRegisterC << 11));
                    iJump = iCode++;
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                        return false;
                    }
                    *pnAddress -= 4;

                    if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                        return false;
                    }
                    if (anCode != NULL) {
                        nDeltaAddress = (nOffset - iCode) * 4;
                    }
                    EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    EMIT_PPC(iJump, 0x41820000 | (((iCode - iJump) & 0x3FFF) << 2));
                    break;
                case 0x06: // blez
                    nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));
                    iJump = iCode++;
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                        return false;
                    }
                    *pnAddress -= 4;

                    if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                        return false;
                    }
                    if (anCode != NULL) {
                        nDeltaAddress = (nOffset - iCode) * 4;
                    }
                    EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    EMIT_PPC(iJump, 0x41810000 | (((iCode - iJump) & 0x3FFF) << 2));
                    break;
                case 0x07: // bgtz
                    nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));
                    iJump = iCode++;
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                        return false;
                    }
                    *pnAddress -= 4;

                    if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                        return false;
                    }
                    if (anCode != NULL) {
                        nDeltaAddress = (nOffset - iCode) * 4;
                    }
                    EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    EMIT_PPC(iJump, 0x40810000 | (((iCode - iJump) & 0x3FFF) << 2));
                    break;
                case 0x08: { // addi
                    bool var_r10;

                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        pCPU->nFlagRAM |= (1 << MIPS_RT(nOpcode));
                    } else {
                        pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    }
                    var_r10 = false;
                    var_r3 = false;
                    if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterA = 5;
                        var_r3 = true;
                    }
                    nTemp1 = MIPS_IMM_U16(nOpcode);
                    if ((s16)nTemp1 == 0) {
                        if ((MIPS_RS(nOpcode) == 31) && !(pCPU->nFlagCODE & 4)) {
                            EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, nReturnAddrLast));
                            EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            var_r10 = true;
                            pCPU->nFlagCODE |= 8;
                        } else if (!var_r3) {
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            } else {
                                EMIT_PPC(iCode,
                                         0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterB << 11));
                            }
                        } else {
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                            } else {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                        }
                        if (MIPS_RT(nOpcode) == 31) {
                            pCPU->nFlagCODE |= 2;
                            if (pCPU->nFlagCODE & 8) {
                                if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                    iRegisterB = 6;
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) + OFFSETOF(pCPU, nReturnAddrLast));
                            }
                        }
                    } else if (MIPS_RS(nOpcode) == 0) {
                        EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21) | nTemp1);
                        var_r10 = true;
                    } else {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21) | (iRegisterB << 16) | nTemp1);
                        var_r10 = true;
                    }
                    if (var_r10 && (ganMapGPR[MIPS_RT(nOpcode)] & 0x100)) {
                        pCPU->nOptimize.destGPR_check = 2;
                        pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                        EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                    }
                    break;
                }
                case 0x09: { // addiu
                    bool var_r10;

                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        pCPU->nFlagRAM |= (1 << MIPS_RT(nOpcode));
                    } else {
                        pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    }

                    var_r10 = false;
                    var_r3 = false;
                    if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterA = 5;
                        var_r3 = true;
                    }
                    nTemp1 = MIPS_IMM_U16(nOpcode);
                    if ((s16)nTemp1 == 0) {
                        if ((MIPS_RS(nOpcode) == 31) && !(pCPU->nFlagCODE & 4)) {
                            EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, nReturnAddrLast));
                            EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                            var_r10 = true;
                            pCPU->nFlagCODE |= 8;
                        } else if (!var_r3) {
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                            } else {
                                EMIT_PPC(iCode,
                                         0x7C000378 | (iRegisterB << 21) | (iRegisterA << 16) | (iRegisterB << 11));
                            }
                        } else {
                            if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                pCPU->nOptimize.destGPR_check = 2;
                                pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                                pCPU->nOptimize.destGPR_mapping = iRegisterA;
                            } else {
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) +
                                                    (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                            }
                        }
                        if (MIPS_RT(nOpcode) == 31) {
                            pCPU->nFlagCODE |= 2;
                            if (pCPU->nFlagCODE & 8) {
                                if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                                    iRegisterB = 6;
                                    EMIT_PPC(iCode,
                                             0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                                }
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterB << 21)) + OFFSETOF(pCPU, nReturnAddrLast));
                            }
                        }
                    } else if (MIPS_RS(nOpcode) == 0) {
                        EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21) | nTemp1);
                        var_r10 = true;
                    } else if (!cpuNextInstruction(pCPU, nAddress, nOpcode, anCode, &iCode)) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21) | (iRegisterB << 16) | nTemp1);
                        var_r10 = true;
                    }
                    if (var_r10 && (ganMapGPR[MIPS_RT(nOpcode)] & 0x100)) {
                        pCPU->nOptimize.destGPR_check = 2;
                        pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                        EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                    }
                    break;
                }
                case 0x0A: // slti
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterA = 5;
                    }
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                    EMIT_PPC(iCode, 0x4180000C);
                    EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21));
                    EMIT_PPC(iCode, 0x42800008);
                    EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21) | 1);
                    if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                        pCPU->nOptimize.destGPR_check = 2;
                        pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                        EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                    }
                    break;
                case 0x0B: // sltiu
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterA = 5;
                    }
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x38E00000 | MIPS_IMM_U16(nOpcode));
                    EMIT_PPC(iCode, 0x7C003840 | (iRegisterB << 16));
                    EMIT_PPC(iCode, 0x4180000C);
                    EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21));
                    EMIT_PPC(iCode, 0x42800008);
                    EMIT_PPC(iCode, 0x38000000 | (iRegisterA << 21) | 1);
                    if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                        pCPU->nOptimize.destGPR_check = 2;
                        pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                        EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                    }
                    break;
                case 0x0C: // andi
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterA = 5;
                    }
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x70000000 | (iRegisterB << 21) | (iRegisterA << 16) | MIPS_IMM_U16(nOpcode));
                    if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                        pCPU->nOptimize.destGPR_check = 2;
                        pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                        EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                    }
                    break;
                case 0x0D: // ori
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        pCPU->nFlagRAM |= (1 << MIPS_RT(nOpcode));
                    } else {
                        pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    }
                    if (!cpuNextInstruction(pCPU, nAddress, nOpcode, anCode, &iCode)) {
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterA = 5;
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x60000000 | (iRegisterB << 21) | (iRegisterA << 16) | MIPS_IMM_U16(nOpcode));
                        if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                            pCPU->nOptimize.destGPR_check = 2;
                            pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                            pCPU->nOptimize.destGPR_mapping = iRegisterA;
                            EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    break;
                case 0x0E: // xori
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        pCPU->nFlagRAM |= (1 << MIPS_RT(nOpcode));
                    } else {
                        pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    }
                    if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterA = 5;
                    }
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x68000000 | (iRegisterB << 21) | (iRegisterA << 16) | MIPS_IMM_U16(nOpcode));
                    if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                        pCPU->nOptimize.destGPR_check = 2;
                        pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                        EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                    }
                    break;
                case 0x0F: // lui
#if IS_MM
                    if (gpSystem->eTypeROM == SRT_ZELDA2 && MIPS_IMM_U16(nOpcode) == 0x8100) {
                        gRegCount++;
                        reg = MIPS_RT(nOpcode);
                        gRegList[reg] = 1;
                        break;
                    }
#endif
                    if (!ramGetSize(SYSTEM_RAM(pCPU->pHost), &nSize)) {
                        return false;
                    }
                    nTemp1 = MIPS_IMM_U16(nOpcode);
                    if ((u32)nTemp1 >= 0x8000 && (u32)nTemp1 <= (0x8000 | (nSize >> 16))) {
                        pCPU->nFlagRAM |= (1 << MIPS_RT(nOpcode));
                    } else {
                        pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    }
                    if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterA = 5;
                    }
                    EMIT_PPC(iCode, 0x3C000000 | (iRegisterA << 21) | nTemp1);
                    if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                        pCPU->nOptimize.destGPR_check = 2;
                        pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                        pCPU->nOptimize.destGPR_mapping = iRegisterA;
                        EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        pCPU->nOptimize.checkType = 0x3E8;
                        pCPU->nOptimize.checkNext = nAddress;
                    }
                    break;
                case 0x10: // cop0
                    switch (MIPS_FUNCT(nOpcode)) {
                        case 0x01: // tlbr
                        case 0x02: // tlbwi
                        case 0x05: // tlbwr
                        case 0x08: // tlbp
                        case 0x18: // eret
                            break;
                        default:
                            switch (MIPS_RS(nOpcode)) {
                                case 0x00: // mfc0
                                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                                    break;
                                case 0x01: // dmfc0
                                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                                    break;
                                case 0x04: // mtc0
                                    break;
                                case 0x05: // dmtc0
                                    break;
                                case 0x08: // dmtc0
                                    if ((s32)MIPS_RS(nOpcode) >= 4 || (s32)MIPS_RS(nOpcode) < 0) {
                                        bFlag = false;
                                    }
                                    break;
                                default:
                                    bFlag = false;
                                    break;
                            }
                            break;
                    }
                    break;
                case 0x11: // cop1
                    if ((nOpcode & 0x7FF) == 0 && MIPS_FMT(nOpcode) < 0x10) {
                        switch ((u8)MIPS_FMT(nOpcode)) {
                            case 0x00: // mfc1
                                pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                                if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                    iRegisterA = 5;
                                }
                                iRegisterB = MIPS_FS(nOpcode);
                                if (iRegisterB % 2 == 1) {
                                    EMIT_PPC(iCode,
                                             (0x80030000 | (iRegisterA << 21)) + OFFSETOF(pCPU, aFPR[iRegisterB - 1]));
                                } else {
                                    EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                        (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                }
                                if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                                    pCPU->nOptimize.destGPR_check = 2;
                                    pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                                    pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    EMIT_PPC(iCode,
                                             0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                                break;
                            case 0x01: // dmfc1
                                pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                                iRegisterB = MIPS_FS(nOpcode);
                                EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                                EMIT_PPC(iCode, 0x80C30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                EMIT_PPC(iCode, 0x90C30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                if (!((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                    EMIT_PPC(iCode, 0x7CC03378 | (iRegisterA << 16));
                                }
                                break;
                            case 0x02: // cfc1
                                pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                                if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                    iRegisterA = 5;
                                }
                                iRegisterB = MIPS_FS(nOpcode);
                                EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) + OFFSETOF(pCPU, anFCR[iRegisterB]));
                                if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                                    pCPU->nOptimize.destGPR_check = 2;
                                    pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                                    pCPU->nOptimize.destGPR_mapping = iRegisterA;
                                    EMIT_PPC(iCode,
                                             0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                                }
                                break;
                            case 0x04: // mtc1
                                iRegisterB = MIPS_FS(nOpcode);
                                if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                    EMIT_PPC(iCode, 0x80A30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                    if (iRegisterB % 2 == 1) {
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aFPR[iRegisterB - 1]));
                                    } else {
                                        EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                    }
                                } else {
                                    if (iRegisterB % 2 == 1) {
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                            OFFSETOF(pCPU, aFPR[iRegisterB - 1]));
                                    } else {
                                        EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                    }
                                }
                                break;
                            case 0x05: // dmtc1
                                if (!((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                                    EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) +
                                                        (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                }
                                iRegisterB = MIPS_FS(nOpcode);
                                EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                                EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                EMIT_PPC(iCode, 0x80C30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                EMIT_PPC(iCode, 0x90C30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                break;
                            case 0x06: // ctc1
                                if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                                    iRegisterA = 5;
                                }
                                iRegisterB = MIPS_FS(nOpcode);
                                if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                                    EMIT_PPC(iCode, (0x80030000 | (iRegisterA << 21)) +
                                                        (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                                }
                                EMIT_PPC(iCode, (0x90030000 | (iRegisterA << 21)) + OFFSETOF(pCPU, anFCR[iRegisterB]));
                                break;
                            default:
                                bFlag = false;
                                break;
                        }
                    } else if (MIPS_FMT(nOpcode) == 0x08) {
                        switch (MIPS_FT(nOpcode)) {
                            case 0x00: // bc1f
                                nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                                EMIT_PPC(iCode, 0x3CA00080);
                                EMIT_PPC(iCode, 0x80C30000 + (OFFSETOF(pCPU, anFCR[31]) & 0xFFFF));
                                EMIT_PPC(iCode, 0x7CC62839);
                                iJump = iCode++;
                                if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                    return false;
                                }
                                *pnAddress -= 4;
                                if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                    return false;
                                }
                                if (anCode != NULL) {
                                    nDeltaAddress = (nOffset - iCode) * 4;
                                }
                                EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                                EMIT_PPC(iJump, 0x40820000 | (((iCode - iJump) & 0x3FFF) << 2));
                                break;
                            case 0x01: // bc1t
                                nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                                EMIT_PPC(iCode, 0x3CA00080);
                                EMIT_PPC(iCode, 0x80C30000 + (OFFSETOF(pCPU, anFCR[31]) & 0xFFFF));
                                EMIT_PPC(iCode, 0x7CC62839);
                                iJump = iCode++;
                                if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                    return false;
                                }
                                *pnAddress -= 4;
                                if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                    return false;
                                }
                                if (anCode != NULL) {
                                    nDeltaAddress = (nOffset - iCode) * 4;
                                }
                                EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                                EMIT_PPC(iJump, 0x41820000 | (((iCode - iJump) & 0x3FFF) << 2));
                                break;
                            case 0x02: // bc1fl
                                nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                                EMIT_PPC(iCode, 0x3CA00080);
                                EMIT_PPC(iCode, 0x80C30000 + (OFFSETOF(pCPU, anFCR[31]) & 0xFFFF));
                                EMIT_PPC(iCode, 0x7CC62839);
                                iJump = iCode++;
                                if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                    return false;
                                }
                                *pnAddress -= 4;
                                if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                    return false;
                                }
                                if (anCode != NULL) {
                                    nDeltaAddress = (nOffset - iCode) * 4;
                                }
                                EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                                if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                                    return false;
                                }
                                EMIT_PPC(iJump, 0x40820000 | (((iCode - iJump) & 0x3FFF) << 2));
                                break;
                            case 0x03: // bc1tl
                                nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                                EMIT_PPC(iCode, 0x3CA00080);
                                EMIT_PPC(iCode, 0x80C30000 + (OFFSETOF(pCPU, anFCR[31]) & 0xFFFF));
                                EMIT_PPC(iCode, 0x7CC62839);
                                iJump = iCode++;
                                if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                                    return false;
                                }
                                *pnAddress -= 4;
                                if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                                    return false;
                                }
                                if (anCode != NULL) {
                                    nDeltaAddress = (nOffset - iCode) * 4;
                                }
                                EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                                if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                                    return false;
                                }
                                EMIT_PPC(iJump, 0x41820000 | (((iCode - iJump) & 0x3FFF) << 2));
                                break;
                            default:
                                bFlag = false;
                                break;
                        }
                    } else {
                        switch ((u8)MIPS_FMT(nOpcode)) {
                            case 0x10: // s
                                switch (MIPS_FUNCT(nOpcode)) {
                                    case 0x00: // add.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (iRegisterB != iRegisterC) {
                                            if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                                EMIT_PPC(iCode, 0x60000000);
                                            } else {
                                                EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                    ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                            }
                                        }
                                        EMIT_PPC(iCode, 0xEC00002A | (iRegisterA << 21) | (iRegisterB << 16) |
                                                            (iRegisterC << 11));
                                        EMIT_PPC(iCode, (0xD0030000 | (iRegisterA << 21)) +
                                                            ((OFFSETOF(pCPU, aFPR[iRegisterA]) + 4) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x01: // sub.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xEC000028 | (iRegisterA << 21) | (iRegisterB << 16) |
                                                            (iRegisterC << 11));
                                        EMIT_PPC(iCode, (0xD0030000 | (iRegisterA << 21)) +
                                                            ((OFFSETOF(pCPU, aFPR[iRegisterA]) + 4) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x02: // mul.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (iRegisterB != iRegisterC) {
                                            if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                                EMIT_PPC(iCode, 0x60000000);
                                            } else {
                                                EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                    ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                            }
                                        }
                                        EMIT_PPC(iCode, 0xEC000032 | (iRegisterA << 21) | (iRegisterB << 16) |
                                                            (iRegisterC << 6));
                                        EMIT_PPC(iCode, (0xD0030000 | (iRegisterA << 21)) +
                                                            ((OFFSETOF(pCPU, aFPR[iRegisterA]) + 4) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x03: // div.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xEC000024 | (iRegisterA << 21) | (iRegisterB << 16) |
                                                            (iRegisterC << 11));
                                        EMIT_PPC(iCode, (0xD0030000 | (iRegisterA << 21)) +
                                                            ((OFFSETOF(pCPU, aFPR[iRegisterA]) + 4) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x04: // sqrt.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC0230000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        }
                                        EMIT_PPC(iCode,
                                                 0x48000000 |
                                                     ((cpuCompile_S_SQRT_function - (u32)&anCode[iCode]) & 0x03FFFFFC) |
                                                     1);
                                        EMIT_PPC(iCode, 0xD0230000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x05: // abs.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000210 | (iRegisterA << 21) | (iRegisterB << 11));
                                        EMIT_PPC(iCode, (0xD0030000 | (iRegisterA << 21)) +
                                                            ((OFFSETOF(pCPU, aFPR[iRegisterA]) + 4) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x06: // mov.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        EMIT_PPC(iCode, 0xC0230000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        EMIT_PPC(iCode, 0xD0230000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x07: // neg.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000050 | (iRegisterA << 21) | (iRegisterB << 11));
                                        EMIT_PPC(iCode, (0xD0030000 | (iRegisterA << 21)) +
                                                            ((OFFSETOF(pCPU, aFPR[iRegisterA]) + 4) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x08: // round.l.s
                                        break;
                                    case 0x09: // trunc.l.s
                                        break;
                                    case 0x0A: // ceil.l.s
                                        break;
                                    case 0x0B: // floor.l.s
                                        break;
                                    case 0x0C: // round.w.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC0230000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        }
                                        EMIT_PPC(iCode, 0x38A00000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_ROUND_W_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        break;
                                    case 0x0D: // trunc.w.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC0230000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        }
                                        EMIT_PPC(iCode, 0x38A00000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_TRUNC_W_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        break;
                                    case 0x0E: // ceil.w.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        OSReport("CALLED: ceil_w single (%p)\n", nAddress);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC0230000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        }
                                        EMIT_PPC(iCode,
                                                 0x48000000 |
                                                     ((cpuCompile_CEIL_W_function - (u32)&anCode[iCode]) & 0x03FFFFFC) |
                                                     1);
                                        EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x0F: // floor.w.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        OSReport("CALLED: floor_w single (%p)\n", nAddress);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC0230000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        }
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_FLOOR_W_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x20: // cvt.s.s
                                        OSReport("ERROR: CVT_S_S\n");
                                        break;
                                    case 0x21: // cvt.d.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        EMIT_PPC(iCode, 0xC0230000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        EMIT_PPC(iCode, 0xD8230000 + OFFSETOF(pCPU, aFPR[iRegisterA]));
                                        break;
                                    case 0x24: // cvt.w.s
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC0230000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        }
                                        EMIT_PPC(iCode, 0x38A00000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_TRUNC_W_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        break;
                                    case 0x25: // cvt.l.s
                                        break;
                                    case 0x30: // c.f.s
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x31: // c.un.s
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x32: // c.eq.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000000 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x33: // c.ueq.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000000 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x34: // c.olt.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4080000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x35: // c.ult.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4080000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x36: // c.ole.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x37: // c.ule.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x38: // c.sf.s
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x39: // c.ngle.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3A: // c.seq.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000000 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3B: // c.ngl.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000000 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3C: // c.lt.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4080000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3D: // c.nge.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4080000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3E: // c.le.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3F: // c.ngt.s
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterB << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterB]) + 4) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC0030000 | (iRegisterC << 21)) +
                                                                ((OFFSETOF(pCPU, aFPR[iRegisterC]) + 4) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    default:
                                        bFlag = false;
                                        break;
                                }
                                break;
                            case 0x11: // d
                                switch (MIPS_FUNCT(nOpcode)) {
                                    case 0x00: // add.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (iRegisterB != iRegisterC) {
                                            if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                                EMIT_PPC(iCode, 0x60000000);
                                            } else {
                                                EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                    (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                            }
                                        }
                                        EMIT_PPC(iCode, 0xFC00002A | (iRegisterA << 21) | (iRegisterB << 16) |
                                                            (iRegisterC << 11));
                                        EMIT_PPC(iCode, (0xD8030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aFPR[iRegisterA]) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x01: // sub.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000028 | (iRegisterA << 21) | (iRegisterB << 16) |
                                                            (iRegisterC << 11));
                                        EMIT_PPC(iCode, (0xD8030000 | (iRegisterA << 21)) +
                                                            ((OFFSETOF(pCPU, aFPR[iRegisterA]) & 0xFFFF) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x02: // mul.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (iRegisterB != iRegisterC) {
                                            if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                                EMIT_PPC(iCode, 0x60000000);
                                            } else {
                                                EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                    (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                            }
                                        }
                                        EMIT_PPC(iCode, 0xFC000032 | (iRegisterA << 21) | (iRegisterB << 16) |
                                                            (iRegisterC << 6));
                                        EMIT_PPC(iCode, (0xD8030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aFPR[iRegisterA]) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x03: // div.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000024 | (iRegisterA << 21) | (iRegisterB << 16) |
                                                            (iRegisterC << 11));
                                        EMIT_PPC(iCode, (0xD8030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aFPR[iRegisterA]) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x04: // sqrt.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC8230000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        }
                                        EMIT_PPC(iCode,
                                                 0x48000000 |
                                                     ((cpuCompile_D_SQRT_function - (u32)&anCode[iCode]) & 0x03FFFFFC) |
                                                     1);
                                        EMIT_PPC(iCode, 0xD8230000 + OFFSETOF(pCPU, aFPR[iRegisterA]));
                                        break;
                                    case 0x05: // abs.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000210 | (iRegisterA << 21) | (iRegisterB << 11));
                                        EMIT_PPC(iCode, (0xD8030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aFPR[iRegisterA]) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x06: // mov.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        EMIT_PPC(iCode, 0xC8230000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        EMIT_PPC(iCode, 0xD8230000 + OFFSETOF(pCPU, aFPR[iRegisterA]));
                                        break;
                                    case 0x07: // neg.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000050 | (iRegisterA << 21) | (iRegisterB << 11));
                                        EMIT_PPC(iCode, (0xD8030000 | (iRegisterA << 21)) +
                                                            (OFFSETOF(pCPU, aFPR[iRegisterA]) & 0xFFFF));
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = iRegisterA;
                                        break;
                                    case 0x08: // round.l.d
                                        break;
                                    case 0x09: // trunc.l.d
                                        break;
                                    case 0x0A: // ceil.l.d
                                        break;
                                    case 0x0B: // floor.l.d
                                        break;
                                    case 0x0C: // round.w.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC8230000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        }
                                        EMIT_PPC(iCode, 0x38A00000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_ROUND_W_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        break;
                                    case 0x0D: // trunc.w.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC8230000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        }
                                        EMIT_PPC(iCode, 0x38A00000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_TRUNC_W_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        break;
                                    case 0x0E: // ceil.w.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        OSReport("CALLED: ceil_w double (%p)\n", nAddress);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC8230000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        }
                                        EMIT_PPC(iCode,
                                                 0x48000000 |
                                                     ((cpuCompile_CEIL_W_function - (u32)&anCode[iCode]) & 0x03FFFFFC) |
                                                     1);
                                        EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x0F: // floor.w.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        OSReport("CALLED: floor_w double (%p)\n", nAddress);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC8230000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        }
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_FLOOR_W_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x20: // cvt.s.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        //! @bug: This generates a lfd instruction to store a double into f1, followed
                                        //! by a stfs instruction to read it out as a float. This is not defined
                                        //! according to the processor documentation, and in practice it rounds the
                                        //! double towards zero instead of rounding to nearest. In the Wii VC version of
                                        //! Super Mario 64, this is the cause of the infamous rising platforms in Bowser
                                        //! in the Fire Sea. See also
                                        //! https://dolphin-emu.org/blog/2018/07/06/dolphin-progress-report-june-2018/#floating-up-to-zero
                                        EMIT_PPC(iCode, 0xC8230000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        EMIT_PPC(iCode, 0xD0230000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x21: // cvt.d.d
                                        OSReport("ERROR: CVT_S_D\n");
                                        break;
                                    case 0x24: // cvt.w.d
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0xFC200090 | (iRegisterB << 11));
                                        } else {
                                            EMIT_PPC(iCode, 0xC8230000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        }
                                        EMIT_PPC(iCode, 0x38A00000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_TRUNC_W_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        break;
                                    case 0x25: // cvt.l.d
                                        break;
                                    case 0x30: // c.f.d
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x31: // c.un.d
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x32: // c.eq.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000000 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x33: // c.ueq.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000000 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x34: // c.olt.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4080000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x35: // c.ult.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4080000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x36: // c.ole.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x37: // c.ule.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x38: // c.sf.d
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x39: // c.ngle.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3A: // c.seq.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000000 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3B: // c.ngl.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000000 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3C: // c.lt.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4080000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3D: // c.nge.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4080000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3E: // c.le.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    case 0x3F: // c.ngt.d
                                        iRegisterB = MIPS_FS(nOpcode);
                                        iRegisterC = MIPS_FT(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterB)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterB << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterB]) & 0xFFFF));
                                        }
                                        if (cpuCutStoreLoadF(pCPU, nAddress, iRegisterC)) {
                                            EMIT_PPC(iCode, 0x60000000);
                                        } else {
                                            EMIT_PPC(iCode, (0xC8030000 | (iRegisterC << 21)) +
                                                                (OFFSETOF(pCPU, aFPR[iRegisterC]) & 0xFFFF));
                                        }
                                        EMIT_PPC(iCode, 0xFC000040 | (iRegisterB << 16) | (iRegisterC << 11));
                                        EMIT_PPC(iCode, 0x4C401382);
                                        EMIT_PPC(iCode, 0x4082000C);
                                        EMIT_PPC(iCode, 0x64A50080);
                                        EMIT_PPC(iCode, 0x42800008);
                                        EMIT_PPC(iCode, 0x54A5024E);
                                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, anFCR[31]));
                                        break;
                                    default:
                                        bFlag = false;
                                        break;
                                }
                                break;
                            case 0x14: // w
                                switch (MIPS_FUNCT(nOpcode)) {
                                    case 0x00: // add.w
                                        OSReport("ERROR: ADD_W\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x01: // sub.w
                                        OSReport("ERROR: SUB_W\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x02: // mul.w
                                        OSReport("ERROR: MUL_W\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x03: // div.w
                                        OSReport("ERROR: DIV_W\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x04: // sqrt.w
                                        OSReport("ERROR: SQRT_W\n");
                                        break;
                                    case 0x05: // abs.w
                                        OSReport("ERROR: ABS_W\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x06: // mov.w
                                        OSReport("ERROR: MOVE_W\n");
                                        break;
                                    case 0x07: // neg.w
                                        OSReport("ERROR: NEG_W\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x08: // round.l.w
                                        break;
                                    case 0x09: // trunc.l.w
                                        break;
                                    case 0x0A: // ceil.l.w
                                        break;
                                    case 0x0B: // floor.l.w
                                        break;
                                    case 0x0C: // round.w.w
                                        OSReport("ERROR: ROUND_W_W\n");
                                        break;
                                    case 0x0D: // trunc.w.w
                                        OSReport("ERROR: TRUNC_W_W\n");
                                        break;
                                    case 0x0E: // ceil.w.w
                                        OSReport("ERROR: CEIL_W_W\n");
                                        break;
                                    case 0x0F: // floor.w.w
                                        OSReport("ERROR: FLOOR_W_W\n");
                                        break;
                                    case 0x20: // cvt.s.w
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_W_CVT_SD_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        EMIT_PPC(iCode, 0xD0230000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x21: // cvt.d.w
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_W_CVT_SD_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        EMIT_PPC(iCode, 0xD8230000 + OFFSETOF(pCPU, aFPR[iRegisterA]));
                                        break;
                                    case 0x24: // cvt.w.w
                                        OSReport("ERROR: CVT_W_W\n");
                                        break;
                                    case 0x25: // cvt.l.w
                                        break;
                                    case 0x30: // c.f.w
                                        OSReport("ERROR: C.F_W\n");
                                        break;
                                    case 0x31: // c.un.w
                                        OSReport("ERROR: C.UN_W\n");
                                        break;
                                    case 0x32: // c.eq.w
                                        OSReport("ERROR: C.EQ_W\n");
                                        break;
                                    case 0x33: // c.ueq.w
                                        OSReport("ERROR: C.UEQ_W\n");
                                        break;
                                    case 0x34: // c.olt.w
                                        OSReport("ERROR: C.OLT_W\n");
                                        break;
                                    case 0x35: // c.ult.w
                                        OSReport("ERROR: C.ULT_W\n");
                                        break;
                                    case 0x36: // c.ole.w
                                        OSReport("ERROR: C.OLE_W\n");
                                        break;
                                    case 0x37: // c.ule.w
                                        OSReport("ERROR: C.ULE_W\n");
                                        break;
                                    case 0x38: // c.sf.w
                                        OSReport("ERROR: C.SF_W\n");
                                        break;
                                    case 0x39: // c.ngle.w
                                        OSReport("ERROR: C.NGLE_W\n");
                                        break;
                                    case 0x3A: // c.seq.w
                                        OSReport("ERROR: C.SEQ_W\n");
                                        break;
                                    case 0x3B: // c.ngl.w
                                        OSReport("ERROR: C.NGL_W\n");
                                        break;
                                    case 0x3C: // c.lt.w
                                        OSReport("ERROR: C.LT_W\n");
                                        break;
                                    case 0x3D: // c.nge.w
                                        OSReport("ERROR: C.NGE_W\n");
                                        break;
                                    case 0x3E: // c.le.w
                                        OSReport("ERROR: C.LE_W\n");
                                        break;
                                    case 0x3F: // c.ngt.w
                                        OSReport("ERROR: C.NGT_W\n");
                                        break;
                                    default:
                                        bFlag = false;
                                        break;
                                }
                                break;
                            case 0x15: // l
                                switch (MIPS_FUNCT(nOpcode)) {
                                    case 0x00: // add.l
                                        OSReport("ERROR: ADD_L\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x01: // sub.l
                                        OSReport("ERROR: SUB_L\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x02: // mul.l
                                        OSReport("ERROR: MUL_L\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x03: // div.l
                                        OSReport("ERROR: DIV_L\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x04: // sqrt.l
                                        OSReport("ERROR: SQRT_L\n");
                                        break;
                                    case 0x05: // abs.l
                                        OSReport("ERROR: ABS_L\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x06: // mov.l
                                        OSReport("ERROR: MOVE_L\n");
                                        break;
                                    case 0x07: // neg.l
                                        OSReport("ERROR: NEG_L\n");
                                        pCPU->nOptimize.destFPR_check = 2;
                                        pCPU->nOptimize.destFPR = MIPS_FD(nOpcode);
                                        break;
                                    case 0x08: // round.l.l
                                        break;
                                    case 0x09: // trunc.l.l
                                        break;
                                    case 0x0A: // ceil.l.l
                                        break;
                                    case 0x0B: // floor.l.l
                                        break;
                                    case 0x0C: // round.w.l
                                        OSReport("ERROR: ROUND_W_L\n");
                                        break;
                                    case 0x0D: // trunc.w.l
                                        OSReport("ERROR: TRUNC_W_L\n");
                                        break;
                                    case 0x0E: // ceil.w.l
                                        OSReport("ERROR: CEIL_W_L\n");
                                        break;
                                    case 0x0F: // floor.w.l
                                        OSReport("ERROR: FLOOR_W_L\n");
                                        break;
                                    case 0x20: // cvt.s.l
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        EMIT_PPC(iCode, 0x80C30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_L_CVT_SD_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        EMIT_PPC(iCode, 0xFC200818);
                                        EMIT_PPC(iCode, 0xD0230000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                                        break;
                                    case 0x21: // cvt.d.l
                                        iRegisterA = MIPS_FD(nOpcode);
                                        iRegisterB = MIPS_FS(nOpcode);
                                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                                        EMIT_PPC(iCode, 0x80C30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                                        EMIT_PPC(iCode, 0x48000000 |
                                                            ((cpuCompile_L_CVT_SD_function - (u32)&anCode[iCode]) &
                                                             0x03FFFFFC) |
                                                            1);
                                        EMIT_PPC(iCode, 0xD8230000 + OFFSETOF(pCPU, aFPR[iRegisterA]));
                                        break;
                                    case 0x24: // cvt.w.l
                                        OSReport("ERROR: CVT_W_L\n");
                                        break;
                                    case 0x25: // cvt.l.l
                                        break;
                                    case 0x30: // c.f.l
                                        OSReport("ERROR: C.F_L\n");
                                        break;
                                    case 0x31: // c.un.l
                                        OSReport("ERROR: C.UN_L\n");
                                        break;
                                    case 0x32: // c.eq.l
                                        OSReport("ERROR: C.EQ_L\n");
                                        break;
                                    case 0x33: // c.ueq.l
                                        OSReport("ERROR: C.UEQ_L\n");
                                        break;
                                    case 0x34: // c.olt.l
                                        OSReport("ERROR: C.OLT_L\n");
                                        break;
                                    case 0x35: // c.ult.l
                                        OSReport("ERROR: C.ULT_L\n");
                                        break;
                                    case 0x36: // c.ole.l
                                        OSReport("ERROR: C.OLE_L\n");
                                        break;
                                    case 0x37: // c.ule.l
                                        OSReport("ERROR: C.ULE_L\n");
                                        break;
                                    case 0x38: // c.sf.l
                                        OSReport("ERROR: C.SF_L\n");
                                        break;
                                    case 0x39: // c.ngle.l
                                        OSReport("ERROR: C.NGLE_L\n");
                                        break;
                                    case 0x3A: // c.seq.l
                                        OSReport("ERROR: C.SEQ_L\n");
                                        break;
                                    case 0x3B: // c.ngl.l
                                        OSReport("ERROR: C.NGL_L\n");
                                        break;
                                    case 0x3C: // c.lt.l
                                        OSReport("ERROR: C.LT_L\n");
                                        break;
                                    case 0x3D: // c.nge.l
                                        OSReport("ERROR: C.NGE_L\n");
                                        break;
                                    case 0x3E: // c.le.l
                                        OSReport("ERROR: C.LE_L\n");
                                        break;
                                    case 0x3F: // c.ngt.l
                                        OSReport("ERROR: C.NGT_L\n");
                                        break;
                                    default:
                                        bFlag = false;
                                        break;
                                }
                                break;
                        }
                    }
                    break;
                case 0x12: // cop2
                    bFlag = false;
                    break;
                case 0x13: // cop1x
                    bFlag = false;
                    break;
                case 0x14: // beql
                    nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                    if (MIPS_RS(nOpcode) == MIPS_RT(nOpcode)) {
                        if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                            return false;
                        }
                        *pnAddress -= 4;
                        if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                            return false;
                        }
                        if (anCode != NULL) {
                            nDeltaAddress = (nOffset - iCode) * 4;
                        }
                        EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    } else {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterC = 7;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x7C000000 | (iRegisterB << 16) | (iRegisterC << 11));
                        iJump = iCode++;
                        if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                            return false;
                        }
                        *pnAddress -= 4;

                        if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                            return false;
                        }
                        if (anCode != NULL) {
                            nDeltaAddress = (nOffset - iCode) * 4;
                        }
                        EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                        if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                            return false;
                        }
                        EMIT_PPC(iJump, 0x40820000 | (((iCode - iJump) & 0x3FFF) << 2));
                    }
                    break;
                case 0x15: // bnel
                    nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    if ((iRegisterC = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                        iRegisterC = 7;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterC << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x7C000000 | (iRegisterB << 16) | (iRegisterC << 11));
                    iJump = iCode++;
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                        return false;
                    }
                    *pnAddress -= 4;

                    if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                        return false;
                    }
                    if (anCode != NULL) {
                        nDeltaAddress = (nOffset - iCode) * 4;
                    }
                    EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                        return false;
                    }
                    EMIT_PPC(iJump, 0x41820000 | (((iCode - iJump) & 0x3FFF) << 2));
                    break;
                case 0x16: // blezl
                    nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));
                    iJump = iCode++;
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                        return false;
                    }
                    *pnAddress -= 4;

                    if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                        return false;
                    }
                    if (anCode != NULL) {
                        nDeltaAddress = (nOffset - iCode) * 4;
                    }
                    EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                        return false;
                    }
                    EMIT_PPC(iJump, 0x41810000 | (((iCode - iJump) & 0x3FFF) << 2));
                    break;
                case 0x17: // bgtzl
                    nAddressJump = *pnAddress + (MIPS_IMM_S16(nOpcode) * 4);
                    if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                        iRegisterB = 6;
                        if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) | (iRegisterB << 16) |
                                                (pCPU->nOptimize.destGPR_mapping << 11));
                        } else {
                            EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                        }
                    }
                    EMIT_PPC(iCode, 0x2C000000 | (iRegisterB << 16));
                    iJump = iCode++;
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, true)) {
                        return false;
                    }
                    *pnAddress -= 4;

                    if (!cpuFindBranchOffset(pFunction, &nOffset, nAddressJump, anCode)) {
                        return false;
                    }
                    if (anCode != NULL) {
                        nDeltaAddress = (nOffset - iCode) * 4;
                    }
                    EMIT_PPC(iCode, 0x48000000 | (nDeltaAddress & 0x03FFFFFC));
                    if (!cpuGetPPC(pCPU, pnAddress, pFunction, anCode, &iCode, false)) {
                        return false;
                    }
                    EMIT_PPC(iJump, 0x40810000 | (((iCode - iJump) & 0x3FFF) << 2));
                    break;
                case 0x18: // daddi
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        pCPU->nFlagRAM |= (1 << MIPS_RT(nOpcode));
                    } else {
                        pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    }
                    if (!((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                        EMIT_PPC(iCode,
                                 (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                    }
                    iRegisterB = MIPS_RT(nOpcode);
                    EMIT_PPC(iCode, 0x9421FFF0);
                    EMIT_PPC(iCode, 0x91010008);
                    EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                    EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                    EMIT_PPC(iCode, 0x38E00000 | MIPS_IMM_U16(nOpcode));
                    EMIT_PPC(iCode, 0x39000000);
                    EMIT_PPC(iCode, 0x7CE70734);
                    EMIT_PPC(iCode, 0x2C070000);
                    EMIT_PPC(iCode, 0x4080000C);
                    EMIT_PPC(iCode, 0x3900FFFF);
                    EMIT_PPC(iCode, 0x7D080734);
                    EMIT_PPC(iCode, 0x7CA53814);
                    EMIT_PPC(iCode, 0x7CC64114);
                    EMIT_PPC(iCode, 0x90A30004 + OFFSETOF(pCPU, aGPR[iRegisterB]));
                    EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, aGPR[iRegisterB]));
                    EMIT_PPC(iCode, 0x81010008);
                    EMIT_PPC(iCode, 0x38210010);
                    if (!((iRegisterB = ganMapGPR[iRegisterB]) & 0x100)) {
                        EMIT_PPC(iCode, 0x7CA02B78 | (iRegisterB << 16));
                    }
                    break;
                case 0x19: // daddiu
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        pCPU->nFlagRAM |= (1 << MIPS_RT(nOpcode));
                    } else {
                        pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    }
                    if (!((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                        EMIT_PPC(iCode,
                                 (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                    }
                    iRegisterB = MIPS_RT(nOpcode);
                    EMIT_PPC(iCode, 0x9421FFF0);
                    EMIT_PPC(iCode, 0x91010008);
                    EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                    EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                    EMIT_PPC(iCode, 0x38E00000 | MIPS_IMM_U16(nOpcode));
                    EMIT_PPC(iCode, 0x39000000);
                    EMIT_PPC(iCode, 0x7CE70734);
                    EMIT_PPC(iCode, 0x2C070000);
                    EMIT_PPC(iCode, 0x4080000C);
                    EMIT_PPC(iCode, 0x3900FFFF);
                    EMIT_PPC(iCode, 0x7D080734);
                    EMIT_PPC(iCode, 0x7CA53814);
                    EMIT_PPC(iCode, 0x7CC64114);
                    EMIT_PPC(iCode, 0x90A30004 + OFFSETOF(pCPU, aGPR[iRegisterB]));
                    EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, aGPR[iRegisterB]));
                    EMIT_PPC(iCode, 0x81010008);
                    EMIT_PPC(iCode, 0x38210010);
                    if (!((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                        EMIT_PPC(iCode, 0x7CA02B78 | (iRegisterB << 16));
                    }
                    break;
                case 0x1F: // library call
                    if (libraryFunctionReplaced(SYSTEM_LIBRARY(pCPU->pHost), MIPS_IMM_U16(nOpcode))) {
                        pCPU->nFlagCODE |= 1;
                        pFunction->nAddress1 = nAddress + 8;
                    }
                    break;
                case 0x1A: // ldl
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x1B: // ldr
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x27: // lwu
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x20: // lb
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterA = 5;
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }

                        if (!cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), MIPS_RT(nOpcode))) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterB << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0x88070000 | (iRegisterA << 21) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x7C000774 | (iRegisterA << 21) | (iRegisterA << 16));
                        if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                            pCPU->nOptimize.destGPR_check = 2;
                            pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                            pCPU->nOptimize.destGPR_mapping = iRegisterA;
                            EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        }
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRam - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 3);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 2);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800010);
                        EMIT_PPC(iCode, 0x48000000 | ((cpuCompile_LB_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                        } else {
                            EMIT_PPC(iCode, 0x7CA02B78 | (iRegisterA << 16));
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    }
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x21: // lh
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterA = 5;
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }

                        if (!cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), MIPS_RT(nOpcode))) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterB << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0xA0070000 | (iRegisterA << 21) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x7C000734 | (iRegisterA << 21) | (iRegisterA << 16));
                        if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                            pCPU->nOptimize.destGPR_check = 2;
                            pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                            pCPU->nOptimize.destGPR_mapping = iRegisterA;
                            EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        }
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRam - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 3);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 2);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800010);
                        EMIT_PPC(iCode, 0x48000000 | ((cpuCompile_LH_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                        } else {
                            EMIT_PPC(iCode, 0x7CA02B78 | (iRegisterA << 16));
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    }
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x22: // lwl
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        EMIT_PPC(iCode, 0x9421FFE8);
                        EMIT_PPC(iCode, 0x91210008);
                        EMIT_PPC(iCode, 0x91410010);
                        if ((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x80A30000 + (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                        } else {
                            EMIT_PPC(iCode, 0x7C050378 | (iRegisterA << 21) | (iRegisterA << 11));
                        }
                        EMIT_PPC(iCode, 0x7CE54214);
                        EMIT_PPC(iCode, 0x38E70000 | MIPS_IMM_U16(nOpcode));
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x81230004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        } else {
                            EMIT_PPC(iCode, 0x7C090378 | (iRegisterB << 21) | (iRegisterB << 11));
                        }
                        EMIT_PPC(iCode,
                                 0x48000000 | ((cpuCompile_LWL_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x91230004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        } else {
                            EMIT_PPC(iCode, 0x7D204B78 | (iRegisterB << 16));
                        }
                        EMIT_PPC(iCode, 0x81210008);
                        EMIT_PPC(iCode, 0x81410010);
                        EMIT_PPC(iCode, 0x38210018);
                    }
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x23: // lw
                    if ((nOpcode & 0xFFFF0000) == 0x8FBF0000) { // lw $ra, 0x????($sp)
                        if ((pCPU->nFlagCODE & 4) && (pCPU->nFlagCODE >> 16) == MIPS_IMM_U16(nOpcode)) {
                            pCPU->nFlagCODE &= ~2;
                            if (prev != 0x457) {
                                pCPU->nFlagCODE &= ~4;
                                pCPU->nFlagCODE &= 0xFFFF;
                            }
                        }
                    }
                    if (gpSystem->eTypeROM == SRT_ZELDA2) {
#if IS_OOT
                        if (nOpcode == 0x8FBF0014 && nOpcodePrev == 0 && nOpcodeNext == 0x27BD0018) {
                            if (nAddress == 0x8018570C || nAddress == 0x8018628C || nAddress == 0x8017FB5C ||
                                nAddress == 0x8018624C || nAddress == 0x801C0F14 || nAddress == 0x801B9DF4 ||
                                nAddress == 0x801B9D94) {
                                pCPU->nFlagCODE |= 2;
                            }
                        } else if (nOpcode == 0x8FBF0014 && nOpcodePrev == 0x24E40014 && nOpcodeNext == 0x27BD0018) {
                            pCPU->nFlagCODE |= 2;
                        } else if (nOpcode == 0x8FBF0014 && nOpcodePrev == 0x00603025 && nOpcodeNext == 0x27BD0050) {
                            pCPU->nFlagCODE |= 2;
                        } else if (nOpcode == 0x8FBF001C && nOpcodePrev == 0x248419C4 && nOpcodeNext == 0x8FB00018) {
                            pCPU->nFlagCODE |= 2;
                        }
#else
                        if (nOpcode == 0x8FBF0014 && nOpcodePrev == 0x24E40014 && nOpcodeNext == 0x27BD0018) {
                            pCPU->nFlagCODE |= 2;
                        }
#endif
                    } else if (gpSystem->eTypeROM == SRT_MARIOPARTY1) {
                        if (nOpcode == 0x8C9F0004 && nOpcodePrev == 0x8C9D0000 && nOpcodeNext == 0x8C900008) {
                            pCPU->nFlagCODE |= 2;
                        }
                    } else if (gpSystem->eTypeROM == SRT_STARFOX) {
                        if (nOpcode == 0x8FBF003C && nOpcodePrev == 0 && nOpcodeNext == 0xAFB20040) {
                            pCPU->nFlagCODE |= 2;
                        }
                    }
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterA = 5;
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }

                        if (!cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), MIPS_RT(nOpcode))) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterB << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0x80070000 | (iRegisterA << 21) | MIPS_IMM_U16(nOpcode));
                        if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                            pCPU->nOptimize.destGPR_check = 2;
                            pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                            pCPU->nOptimize.destGPR_mapping = iRegisterA;
                            EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        }
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRam - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 3);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 2);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800010);
                        EMIT_PPC(iCode, 0x48000000 | ((cpuCompile_LW_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                        } else {
                            EMIT_PPC(iCode, 0x7CA02B78 | (iRegisterA << 16));
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    }
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x24: // lbu
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterA = 5;
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }

                        if (!cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), MIPS_RT(nOpcode))) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterB << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0x88070000 | (iRegisterA << 21) | MIPS_IMM_U16(nOpcode));
                        if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                            pCPU->nOptimize.destGPR_check = 2;
                            pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                            pCPU->nOptimize.destGPR_mapping = iRegisterA;
                            EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        }
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRam - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 3);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 2);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800010);
                        EMIT_PPC(iCode,
                                 0x48000000 | ((cpuCompile_LBU_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                        } else {
                            EMIT_PPC(iCode, 0x7CA02B78 | (iRegisterA << 16));
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    }
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x25: // lhu
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterA = 5;
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }

                        if (!cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), MIPS_RT(nOpcode))) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterB << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0xA0070000 | (iRegisterA << 21) | MIPS_IMM_U16(nOpcode));
                        if (ganMapGPR[MIPS_RT(nOpcode)] & 0x100) {
                            pCPU->nOptimize.destGPR_check = 2;
                            pCPU->nOptimize.destGPR = MIPS_RT(nOpcode);
                            pCPU->nOptimize.destGPR_mapping = iRegisterA;
                            EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                        }
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRam - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 3);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 2);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800010);
                        EMIT_PPC(iCode,
                                 0x48000000 | ((cpuCompile_LHU_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                        } else {
                            EMIT_PPC(iCode, 0x7CA02B78 | (iRegisterA << 16));
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    }
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x26: // lwr
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        EMIT_PPC(iCode, 0x9421FFE8);
                        EMIT_PPC(iCode, 0x91210008);
                        EMIT_PPC(iCode, 0x91410010);
                        if ((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x80A30000 + (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                        } else {
                            EMIT_PPC(iCode, 0x7C050378 | (iRegisterA << 21) | (iRegisterA << 11));
                        }
                        EMIT_PPC(iCode, 0x7CE54214);
                        EMIT_PPC(iCode, 0x38E70000 | MIPS_IMM_U16(nOpcode));
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x81230004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        } else {
                            EMIT_PPC(iCode, 0x7C090378 | (iRegisterB << 21) | (iRegisterB << 11));
                        }
                        EMIT_PPC(iCode,
                                 0x48000000 | ((cpuCompile_LWR_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x91230004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        } else {
                            EMIT_PPC(iCode, 0x7D204B78 | (iRegisterB << 16));
                        }
                        EMIT_PPC(iCode, 0x81210008);
                        EMIT_PPC(iCode, 0x81410010);
                        EMIT_PPC(iCode, 0x38210018);
                    }
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x28: // sb
#if IS_MM
                    if (gpSystem->eTypeROM == SRT_ZELDA2 && gRegCount != 0 &&
                        (MIPS_IMM_U16(nOpcode) == 0x0 && gRegList[MIPS_RS(nOpcode)] != 0)) {
                        gRegCount--;
                        reg = MIPS_RS(nOpcode);
                        gRegList[reg] = 0;
                        break;
                    }
#endif
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        var_r3 = true;
                        if ((iRegisterC = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterC = 7;
                            var_r3 = false;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        if (!var_r3 || !cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), -1)) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterC << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0x98070000 | (iRegisterB << 21) | MIPS_IMM_U16(nOpcode));
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRam - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 3);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 2);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800020);
                        EMIT_PPC(iCode, 0x9421FFF0);
                        EMIT_PPC(iCode, 0x91010008);
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x81030004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        } else {
                            EMIT_PPC(iCode, 0x7C080378 | (iRegisterA << 21) | (iRegisterA << 11));
                        }
                        EMIT_PPC(iCode, 0x48000000 | ((cpuCompile_SB_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        EMIT_PPC(iCode, 0x81010008);
                        EMIT_PPC(iCode, 0x38210010);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    }
                    break;
                case 0x29: // sh
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        var_r3 = true;
                        if ((iRegisterC = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterC = 7;
                            var_r3 = false;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        if (!var_r3 || !cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), -1)) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterC << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0xB0070000 | (iRegisterB << 21) | MIPS_IMM_U16(nOpcode));
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRam - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 3);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 2);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800020);
                        EMIT_PPC(iCode, 0x9421FFF0);
                        EMIT_PPC(iCode, 0x91010008);
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x81030004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        } else {
                            EMIT_PPC(iCode, 0x7C080378 | (iRegisterA << 21) | (iRegisterA << 11));
                        }
                        EMIT_PPC(iCode, 0x48000000 | ((cpuCompile_SH_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        EMIT_PPC(iCode, 0x81010008);
                        EMIT_PPC(iCode, 0x38210010);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    }
                    break;
                case 0x2A: // swl
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if (!((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                            EMIT_PPC(iCode,
                                     (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                        } else {
                            EMIT_PPC(iCode, 0x7C050378 | (iRegisterB << 21) | (iRegisterB << 11));
                        }
                        EMIT_PPC(iCode, 0x7CE54214);
                        EMIT_PPC(iCode, 0x38E70000 | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x38C00018);
                        EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        EMIT_PPC(iCode, 0x7CA53430);
                        EMIT_PPC(iCode, 0x98A70000);
                        EMIT_PPC(iCode, 0x38C6FFF8);
                        EMIT_PPC(iCode, 0x54E507BF);
                        EMIT_PPC(iCode, 0x38E70001);
                        EMIT_PPC(iCode, 0x4082FFE8);
                    }
                    break;
                case 0x2B: // sw
                    if ((nOpcode & 0xFFFF0000) == 0xAFBF0000) { // sw $ra, ????($sp)
                        if (!(pCPU->nFlagCODE & 4)) {
                            pCPU->nFlagCODE |= 4;
                            pCPU->nFlagCODE |= MIPS_IMM_U16(nOpcode) << 16;
                        }
                    }
                    if (gpSystem->eTypeROM == SRT_MARIOPARTY1) {
                        if (nOpcode == 0xAC9F0004 && nOpcodePrev == 0xAC9D0000 && nOpcodeNext == 0xAC900008) {
                            EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, nReturnAddrLast));
                            if (ganMapGPR[31] & 0x100) {
                                EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[31]) + 4) & 0xFFFF));
                            } else {
                                EMIT_PPC(iCode, 0x7CA02B78 | (ganMapGPR[31] << 16));
                            }
                            pCPU->nFlagCODE |= 2;
                        }
                    } else if (gpSystem->eTypeROM == SRT_STARFOX && nOpcode == 0xAFBF003C &&
                               nOpcodePrev == 0x0080A025 && nOpcodeNext == 0xAFB00018) {
                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, nReturnAddrLast));
                        if (ganMapGPR[31] & 0x100) {
                            EMIT_PPC(iCode, 0x90A30000 + ((OFFSETOF(pCPU, aGPR[31]) + 4) & 0xFFFF));
                        } else {
                            EMIT_PPC(iCode, 0x7CA02B78 | (ganMapGPR[31] << 16));
                        }
                        pCPU->nFlagCODE |= 2;
                    }
                    if (nOpcode == 0xACBF011C) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RT(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        var_r3 = true;
                        if ((iRegisterC = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterC = 7;
                            var_r3 = false;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        if (!var_r3 || !cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), -1)) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterC << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0x90070000 | (iRegisterB << 21) | MIPS_IMM_U16(nOpcode));
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRam - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 3);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 2);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800020);
                        EMIT_PPC(iCode, 0x9421FFF0);
                        EMIT_PPC(iCode, 0x91010008);
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x81030004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        } else
                            EMIT_PPC(iCode, 0x7C080378 | (iRegisterB << 21) | (iRegisterB << 11));
                        EMIT_PPC(iCode, 0x48000000 | ((cpuCompile_SW_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        EMIT_PPC(iCode, 0x81010008);
                        EMIT_PPC(iCode, 0x38210010);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    }
                    break;
                case 0x2C: // sdl
                case 0x2D: // sdr
                    break;
                case 0x2E: // swr
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if (!((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100)) {
                            EMIT_PPC(iCode, ((0x90030000 | (iRegisterA << 21)) +
                                             (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4)));
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                        } else
                            EMIT_PPC(iCode, 0x7C050378 | (iRegisterB << 21) | (iRegisterB << 11));
                        EMIT_PPC(iCode, 0x7CE54214);
                        EMIT_PPC(iCode, 0x38E70000 | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x38C00000);
                        EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        EMIT_PPC(iCode, 0x7CA53430);
                        EMIT_PPC(iCode, 0x98A70000);
                        EMIT_PPC(iCode, 0x38C60008);
                        EMIT_PPC(iCode, 0x54E507BF);
                        EMIT_PPC(iCode, 0x38E7FFFF);
                        EMIT_PPC(iCode, 0x4082FFE8);
                    }
                    break;
                case 0x2F: // cache
                    EMIT_PPC(iCode, 0x60000000);
                    break;
                case 0x30: // sc
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x31: // lwc1
                    if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRamF - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 4);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 3);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        iRegisterA = MIPS_RT(nOpcode);
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800010);
                        EMIT_PPC(iCode, 0x48000000 | ((cpuCompile_LW_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (iRegisterA % 2 == 1) {
                            EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aFPR[iRegisterA - 1]));
                        } else {
                            EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    } else {
                        if (!((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                            EMIT_PPC(iCode,
                                     (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                        }
                        iRegisterB = MIPS_RT(nOpcode);
                        if (!ramGetSize(SYSTEM_RAM(pCPU->pHost), &nSize)) {
                            return false;
                        }
                        EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                        EMIT_PPC(iCode, 0x3CE08000);
                        EMIT_PPC(iCode, 0x7C072840);
                        EMIT_PPC(iCode, 0x41810014);
                        EMIT_PPC(iCode, 0x3CE08000 | ((nSize >> 16) - 1));
                        EMIT_PPC(iCode, 0x60E7FFFF);
                        EMIT_PPC(iCode, 0x7C072840);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x41810024);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else
                            EMIT_PPC(iCode, 0x41810014);
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x42800028);
                        EMIT_PPC(iCode, 0x7CE54214);
                        EMIT_PPC(iCode, 0x38A00000 | iRegisterB);
                        EMIT_PPC(iCode, 0x70A50001);
                        EMIT_PPC(iCode, 0x41820010);
                        EMIT_PPC(iCode, 0x80A70000 | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aFPR[iRegisterB - 1]));
                        EMIT_PPC(iCode, 0x4280000C);
                        EMIT_PPC(iCode, 0x80A70000 | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                    }
                    break;
                case 0x34: // lld
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x35: // ldc1
                    if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRamF - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 4);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 3);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        iRegisterA = MIPS_RT(nOpcode);
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800014);
                        EMIT_PPC(iCode,
                                 0x48000000 | ((cpuCompile_LDC_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aFPR[iRegisterA]));
                        EMIT_PPC(iCode, 0x90C30000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    } else {
                        if (!((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                            EMIT_PPC(iCode,
                                     (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                        }
                        iRegisterB = MIPS_RT(nOpcode);
                        if (!ramGetSize(SYSTEM_RAM(pCPU->pHost), &nSize)) {
                            return false;
                        }
                        EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                        EMIT_PPC(iCode, 0x3CE08000);
                        EMIT_PPC(iCode, 0x7C072840);
                        EMIT_PPC(iCode, 0x41810014);
                        EMIT_PPC(iCode, 0x3CE08000 | ((nSize >> 16) - 1));
                        EMIT_PPC(iCode, 0x60E7FFFF);
                        EMIT_PPC(iCode, 0x7C072840);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x41810024);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else
                            EMIT_PPC(iCode, 0x41810014);
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x42800018);
                        EMIT_PPC(iCode, 0x7CE54214);
                        EMIT_PPC(iCode, 0x80A70000 | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                        EMIT_PPC(iCode, 0x80A70000 | (MIPS_IMM_U16(nOpcode) + 4));
                        EMIT_PPC(iCode, 0x90A30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                    }
                    break;
                case 0x37: // ld
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        if ((iRegisterA = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterA = 5;
                        }
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        iRegisterC = 7;
                        if (!cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), MIPS_RT(nOpcode))) {
                            EMIT_PPC(iCode, 0x7C004214 | (iRegisterC << 21) | (iRegisterB << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0x80A70000 | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        EMIT_PPC(iCode, 0x80070000 | (iRegisterA << 21) | (MIPS_IMM_U16(nOpcode) + 4));
                        EMIT_PPC(iCode,
                                 (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]) + 4));
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRamF - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 4);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 3);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    }
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x38: // sc
                    break;
                case 0x39: // swc1
                    if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRamF - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 4);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 3);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        iRegisterA = MIPS_RT(nOpcode);
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x41800020);
                        EMIT_PPC(iCode, 0x9421FFF0);
                        EMIT_PPC(iCode, 0x91010008);
                        if (iRegisterA % 2 == 1) {
                            EMIT_PPC(iCode, 0x81030000 + OFFSETOF(pCPU, aFPR[iRegisterA - 1]));
                        } else {
                            EMIT_PPC(iCode, 0x81030000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                        }
                        EMIT_PPC(iCode, 0x48000000 | ((cpuCompile_SW_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        EMIT_PPC(iCode, 0x81010008);
                        EMIT_PPC(iCode, 0x38210010);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    } else {
                        if (!((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                            EMIT_PPC(iCode,
                                     (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                        }
                        iRegisterB = MIPS_RT(nOpcode);
                        if (!ramGetSize(SYSTEM_RAM(pCPU->pHost), &nSize)) {
                            return false;
                        }
                        EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                        EMIT_PPC(iCode, 0x3CE08000);
                        EMIT_PPC(iCode, 0x7C072840);
                        EMIT_PPC(iCode, 0x41810014);
                        EMIT_PPC(iCode, 0x3CE08000 | ((nSize >> 16) - 1));
                        EMIT_PPC(iCode, 0x60E7FFFF);
                        EMIT_PPC(iCode, 0x7C072840);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x41810024);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else
                            EMIT_PPC(iCode, 0x41810014);
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x42800024);
                        EMIT_PPC(iCode, 0x7CE54214);
                        EMIT_PPC(iCode, 0x38A00000 | iRegisterB);
                        EMIT_PPC(iCode, 0x70A50001);
                        EMIT_PPC(iCode, 0x4182000C);
                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aFPR[iRegisterB - 1]));
                        EMIT_PPC(iCode, 0x42800008);
                        EMIT_PPC(iCode, 0x80A30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                        EMIT_PPC(iCode, 0x90A70000 | MIPS_IMM_U16(nOpcode));
                    }
                    break;
                case 0x3C: // scd
                    pCPU->nFlagRAM &= ~(1 << MIPS_RT(nOpcode));
                    break;
                case 0x3D: // sdc1
                    if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRamF - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 4);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 3);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    } else if (pCPU->nCompileFlag & 1) {
                        iRegisterA = MIPS_RT(nOpcode);
                        if ((iRegisterB = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterB << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        EMIT_PPC(iCode, 0x38A00000 | (iRegisterB << 16) | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x54A6843E);
                        EMIT_PPC(iCode, 0x7CC648AE);
                        EMIT_PPC(iCode, 0x2C060080);
                        EMIT_PPC(iCode, 0x4180002C);
                        EMIT_PPC(iCode, 0x9421FFE8);
                        EMIT_PPC(iCode, 0x91010008);
                        EMIT_PPC(iCode, 0x91210010);
                        EMIT_PPC(iCode, 0x81030000 + OFFSETOF(pCPU, aFPR[iRegisterA]));
                        EMIT_PPC(iCode, 0x81230000 + (OFFSETOF(pCPU, aFPR[iRegisterA]) + 4));
                        EMIT_PPC(iCode,
                                 0x48000000 | ((cpuCompile_SDC_function - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        EMIT_PPC(iCode, 0x81010008);
                        EMIT_PPC(iCode, 0x81210010);
                        EMIT_PPC(iCode, 0x38210018);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x42800020);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else {
                            EMIT_PPC(iCode, 0x42800010);
                            EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                            EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                            EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        }
                    } else {
                        if (!((iRegisterA = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100)) {
                            EMIT_PPC(iCode,
                                     (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4));
                        }
                        iRegisterB = MIPS_RT(nOpcode);
                        if (!ramGetSize(SYSTEM_RAM(pCPU->pHost), &nSize)) {
                            return false;
                        }
                        EMIT_PPC(iCode, 0x80A30004 + OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]));
                        EMIT_PPC(iCode, 0x3CE08000);
                        EMIT_PPC(iCode, 0x7C072840);
                        EMIT_PPC(iCode, 0x41810014);
                        EMIT_PPC(iCode, 0x3CE08000 | ((nSize >> 16) - 1));
                        EMIT_PPC(iCode, 0x60E7FFFF);
                        EMIT_PPC(iCode, 0x7C072840);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x41810024);
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        } else
                            EMIT_PPC(iCode, 0x41810014);
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x42800018);
                        EMIT_PPC(iCode, 0x7CE54214);
                        EMIT_PPC(iCode, 0x80A30000 + OFFSETOF(pCPU, aFPR[iRegisterB]));
                        EMIT_PPC(iCode, 0x90A70000 | MIPS_IMM_U16(nOpcode));
                        EMIT_PPC(iCode, 0x80A30000 + (OFFSETOF(pCPU, aFPR[iRegisterB]) + 4));
                        EMIT_PPC(iCode, 0x90A70000 | (MIPS_IMM_U16(nOpcode) + 4));
                    }
                    break;
                case 0x3F: // sd
                    if (pCPU->nFlagRAM & (1 << MIPS_RS(nOpcode))) {
                        var_r3 = true;
                        if ((iRegisterC = ganMapGPR[MIPS_RS(nOpcode)]) & 0x100) {
                            iRegisterC = 7;
                            var_r3 = false;
                            if (cpuCutStoreLoad(pCPU, nAddress, MIPS_RS(nOpcode))) {
                                EMIT_PPC(iCode, 0x7C000378 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                                    (iRegisterC << 16) | (pCPU->nOptimize.destGPR_mapping << 11));
                            } else {
                                EMIT_PPC(iCode, 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(nOpcode)]) + 4) & 0xFFFF));
                            }
                        }
                        if (!var_r3 || !cpuStackOffset(pCPU, nAddress, anCode, MIPS_RS(nOpcode), -1)) {
                            EMIT_PPC(iCode, 0x7CE04214 | (iRegisterC << 16));
                        } else {
                            EMIT_PPC(iCode, 0x60000000);
                        }
                        EMIT_PPC(iCode, 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        EMIT_PPC(iCode, 0x90C70000 | MIPS_IMM_U16(nOpcode));
                        if ((iRegisterB = ganMapGPR[MIPS_RT(nOpcode)]) & 0x100) {
                            iRegisterB = 6;
                            EMIT_PPC(iCode, 0x80C30004 + OFFSETOF(pCPU, aGPR[MIPS_RT(nOpcode)]));
                        }
                        EMIT_PPC(iCode, 0x90070000 | (iRegisterB << 21) | (MIPS_IMM_U16(nOpcode) + 4));
                    } else if (pCPU->nCompileFlag & 0x10) {
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C00000);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                        EMIT_PPC(iCode, 0x3CA00000 | ((u32)nAddress >> 16));
                        EMIT_PPC(iCode, 0x60A50000 | ((u32)nAddress & 0xFFFF));
                        EMIT_PPC(iCode, 0x48000000 | (((u32)pCPU->pfRamF - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1);
                        if (pCPU->nCompileFlag & 0x100) {
                            cpuCompileNOP(anCode, &iCode, 4);
                        } else {
                            cpuCompileNOP(anCode, &iCode, 3);
                        }
                        if (var_r17) {
                            EMIT_PPC(iCode, 0x38C0FFFF);
                            EMIT_PPC(iCode, 0x90C30000 + OFFSETOF(pCPU, nWaitPC));
                        }
                    }
                    break;
                default:
                    bFlag = false;
                    break;
            }
        }

        if (!bFlag) {
            return false;
        }
        if (!bSlot && pFunction->pfCode == NULL) {
            if (nAddressJump != -1 && anCode == NULL) {
                pFunction->aJump[pFunction->nCountJump++].nAddressN64 = nAddressJump;
            }
            for (iJump = 0; iJump < pFunction->nCountJump; iJump++) {
                if (pFunction->aJump[iJump].nAddressN64 == nAddress) {
                    pFunction->aJump[iJump].nOffsetHost = *piCode;
                }
            }
        }
        if (iCode == *piCode) {
            if (anCode != NULL) {
                if (var_r17) {
                    anCode[iCode++] = 0x38C00000;
                    anCode[iCode++] = 0x90C30000 + OFFSETOF(pCPU, nWaitPC);
                }
                anCode[iCode++] = 0x3CA00000 | ((u32)nAddress >> 16);
                anCode[iCode++] = 0x60A50000 | ((u32)nAddress & 0xFFFF);
                anCode[iCode++] = 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[iCode]) & 0x03FFFFFC) | 1;
            } else {
                iCode += var_r17 ? 5 : 3;
            }
            if ((pCPU->nFlagCODE & 1) && anCode == NULL && pFunction->pfCode == NULL) {
                iCode += 6;
                *pnAddress = pFunction->nAddress1 + 4;
            }
            if (var_r17) {
                if (anCode != NULL) {
                    anCode[iCode++] = 0x38C0FFFF;
                    anCode[iCode++] = 0x90C30000 + OFFSETOF(pCPU, nWaitPC);
                } else {
                    iCode += 2;
                }
            }
        }

        if (update) {
            pCPU->nOptimize.addr_last = -1;
            if (anCode != NULL) {
                anCode[iUpdate] = 0x42800000 | (((iCode - iUpdate) * 4) & 0xFFFC);
            }
        }

        *piCode = iCode;
        if (anCode != NULL) {
            if (var_r17) {
                pCPU->nOptimize.destGPR_check = 0;
                pCPU->nOptimize.destFPR_check = 0;
                pCPU->nOptimize.checkNext = 0;
            } else if (pCPU->nOptimize.destGPR_check == 2) {
                pCPU->nOptimize.destGPR_check = 1;
                pCPU->nOptimize.destFPR_check = 0;
            } else if (pCPU->nOptimize.destFPR_check == 2) {
                pCPU->nOptimize.destFPR_check = 1;
                pCPU->nOptimize.destGPR_check = 0;
            } else {
                pCPU->nOptimize.destGPR_check = 0;
                pCPU->nOptimize.destFPR_check = 0;
            }
        }

        if (var_r17 || pCPU->nOptimize.addr_check == 0) {
            pCPU->nOptimize.addr_last = -1;
        }

        return true;
    } else {
        return false;
    }
}

#pragma optimization_level reset

/**
 * @brief Creates a new recompiled function block.
 *
 * @param pCPU The emulated VR4300.
 * @param ppFunction A pointer to an already recompiled function, or one that has been created.
 * @param nAddressN64 The N64 address of the function to find or create.
 * @return bool true on success, false otherwise.
 */
bool cpuMakeFunction(Cpu* pCPU, CpuFunction** ppFunction, s32 nAddressN64) {
    s32 iCode;
    s32 iCode0;
    s32 pad;
    s32 iJump;
    s32 iCheck;
    s32 firstTime;
    s32 kill_value;
    s32 memory_used;
    s32 codeMemory;
    s32 blockMemory;
    s32* chunkMemory;
    s32* anCode;
    s32 nAddress;
    CpuFunction* pFunction;
    CpuJump aJump[1024];

    firstTime = 1;
    if (!cpuFindFunction(pCPU, nAddressN64, &pFunction)) {
        return false;
    }

    if (pFunction->pfCode == NULL) {
        libraryTestFunction(SYSTEM_LIBRARY(pCPU->pHost), pFunction);
        pFunction->nCountJump = 0;
        pFunction->aJump = aJump;
        pCPU->nFlagRAM = 0x20000000;
        pCPU->nFlagCODE = 0;
        pFunction->callerID_total = 0;
        pFunction->callerID_flag = 0xB;
        pCPU->nOptimize.validCheck = 1;
        pCPU->nOptimize.checkNext = 0;
#if IS_MM
        gRegCount = 0;
#endif

        iCode = 0;
        nAddress = pFunction->nAddress0;
        while (nAddress <= pFunction->nAddress1) {
            if (!cpuGetPPC(pCPU, &nAddress, pFunction, NULL, &iCode, false)) {
                return false;
            }
        }

        iCode0 = iCode;
        codeMemory = iCode * sizeof(s32);
        memory_used = codeMemory;

        iCheck = pFunction->callerID_total;
        if (iCheck != 0) {
            blockMemory = iCheck * sizeof(CpuCallerID);
            memory_used += blockMemory;
        } else {
            blockMemory = 0;
        }

        if (pFunction->nCountJump > 0) {
            memory_used += pFunction->nCountJump * sizeof(CpuJump);
        }

        while (true) {
            if (cpuHeapTake(&chunkMemory, pCPU, pFunction, memory_used)) {
                break;
            }

            if (firstTime) {
                firstTime = 0;
                kill_value = pCPU->survivalTimer - 300;
            } else {
                kill_value += 95;
                if (kill_value > pCPU->survivalTimer - 10) {
                    kill_value = pCPU->survivalTimer - 10;
                }
            }

            treeForceCleanUp(pCPU, pFunction, kill_value);
        }

        anCode = chunkMemory;
        if (blockMemory != 0) {
            pFunction->block = (CpuCallerID*)((u8*)chunkMemory + codeMemory);
            treeCallerInit(pFunction->block, iCheck);
        }

        pCPU->nFlagRAM = 0x20000000;
        pCPU->nFlagCODE = 0;
        pFunction->callerID_total = 0;
        pFunction->callerID_flag = 0x16;
        pCPU->nOptimize.checkNext = 0;
        pCPU->nOptimize.destGPR_check = 0;
        pCPU->nOptimize.destFPR_check = 0;
#if IS_MM
        gRegCount = 0;
#endif

        iCode = 0;
        nAddress = pFunction->nAddress0;
        while (nAddress <= pFunction->nAddress1) {
            if (!cpuGetPPC(pCPU, &nAddress, pFunction, anCode, &iCode, false)) {
                return false;
            }
        }

#if IS_MM
        gRegCount = 0;
#endif

        while (iCode != iCode0) {
            anCode[iCode++] = 0x60000000;
        }

        pFunction->callerID_flag = 0x21;
        pFunction->pfCode = anCode;
        DCStoreRange(pFunction->pfCode, iCode * 4);
        ICInvalidateRange(pFunction->pfCode, iCode * 4);

        if (pFunction->nCountJump > 0) {
            if (pFunction->nCountJump >= 0x400) {
                return false;
            }

            pFunction->aJump = (CpuJump*)((u8*)chunkMemory + codeMemory + blockMemory);
            for (iJump = 0; iJump < pFunction->nCountJump; iJump++) {
                pFunction->aJump[iJump].nOffsetHost = aJump[iJump].nOffsetHost;
                pFunction->aJump[iJump].nAddressN64 = aJump[iJump].nAddressN64;
            }
        } else {
            pFunction->aJump = NULL;
        }

        pFunction->memory_size = memory_used;
        pCPU->gTree->total_memory += memory_used;
    }

    if (ppFunction != NULL) {
        *ppFunction = pFunction;
    }

    return true;
}

/**
 * @brief Searches the recompiled block cache for an address, or creates a new block if one cannot be found.
 *
 * @param pCPU The emulated VR4300.
 * @param nAddressN64 N64 code address to search for.
 * @param pnAddressGCN A pointer to set the found PPC code to.
 * @return bool true on success, false otherwise.
 */
static bool cpuFindAddress(Cpu* pCPU, s32 nAddressN64, s32* pnAddressGCN) {
    s32 iJump;
    s32 iCode;
    s32 nAddress;
    CpuFunction* pFunction;
    s32 pad;

    if (pCPU->nMode & 0x20) {
        pCPU->nMode &= ~0x20;
    }

    if (cpuFindCachedAddress(pCPU, nAddressN64, pnAddressGCN)) {
        return true;
    }

    if ((pFunction = pCPU->pFunctionLast) == NULL || nAddressN64 < pFunction->nAddress0 ||
        pFunction->nAddress1 < nAddressN64) {
        if (!cpuMakeFunction(pCPU, &pFunction, nAddressN64)) {
            return false;
        }
    }

    for (iJump = 0; iJump < pFunction->nCountJump; iJump++) {
        if (pFunction->aJump[iJump].nAddressN64 == nAddressN64) {
            *pnAddressGCN = (s32)((s32*)pFunction->pfCode + pFunction->aJump[iJump].nOffsetHost);
            if (pFunction->timeToLive > 0) {
                pFunction->timeToLive = pCPU->survivalTimer;
            }
            cpuMakeCachedAddress(pCPU, nAddressN64, *pnAddressGCN, pFunction);
            return true;
        }
    }

    pCPU->nFlagRAM = 0x20000000;
    pCPU->nFlagCODE = 0;
    pFunction->callerID_flag = 0x21;
    iCode = 0;
    if (pFunction->nAddress0 != nAddressN64) {
        pFunction->timeToLive = 0;
    }

    nAddress = pFunction->nAddress0;
    while (nAddress <= pFunction->nAddress1) {
        if (nAddress == nAddressN64) {
            *pnAddressGCN = (s32)((s32*)pFunction->pfCode + iCode);
            if (pFunction->timeToLive > 0) {
                pFunction->timeToLive = pCPU->survivalTimer;
            }
            cpuMakeCachedAddress(pCPU, nAddressN64, *pnAddressGCN, pFunction);
            return true;
        }
        if (!cpuGetPPC(pCPU, &nAddress, pFunction, NULL, &iCode, false)) {
            return false;
        }
    }

    return false;
}

static inline bool cpuNoBranchTo(CpuFunction* pFunction, s32 addressN64) {
    s32 i;

    for (i = 0; i < pFunction->nCountJump; i++) {
        if (pFunction->aJump[i].nAddressN64 == addressN64) {
            return false;
        }
    }

    return true;
}

static inline bool cpuCutStoreLoad(Cpu* pCPU, s32 currentAddress, s32 source) {
    if (pCPU->nOptimize.validCheck == 0) {
        return false;
    }
    if (pCPU->nOptimize.destGPR_check == 0) {
        return false;
    }
    if (source != pCPU->nOptimize.destGPR) {
        return false;
    }

    if (!cpuNoBranchTo(pCPU->pFunctionLast, currentAddress)) {
        pCPU->nOptimize.destGPR_check = 0;
        return false;
    }

    pCPU->nOptimize.destGPR_check = 0;
    return true;
}

static inline bool cpuCutStoreLoadF(Cpu* pCPU, s32 currentAddress, s32 source) {
    if (pCPU->nOptimize.validCheck == 0) {
        return false;
    }
    if (pCPU->nOptimize.destFPR_check == 0) {
        return false;
    }
    if (source != pCPU->nOptimize.destFPR) {
        return false;
    }

    if (!cpuNoBranchTo(pCPU->pFunctionLast, currentAddress)) {
        pCPU->nOptimize.destFPR_check = 0;
        return false;
    }

    pCPU->nOptimize.destFPR_check = 0;
    return true;
}

static inline bool cpuStackOffset(Cpu* pCPU, s32 currentAddress, s32* anCode, s32 source, s32 target) {
    if (anCode == NULL) {
        return false;
    }
    if (pCPU->nOptimize.validCheck == 0) {
        return false;
    }

    if (!cpuNoBranchTo(pCPU->pFunctionLast, currentAddress)) {
        return false;
    }

    pCPU->nOptimize.addr_check = 1;
    if (source == target) {
        pCPU->nOptimize.addr_last = -1;
        return false;
    } else if (pCPU->nOptimize.addr_last != source) {
        pCPU->nOptimize.addr_last = source;
        return false;
    }

    return true;
}

static bool cpuNextInstruction(Cpu* pCPU, s32 addressN64, s32 opcode, s32* anCode, s32* iCode) {
    if (anCode == NULL) {
        return false;
    }
    if (pCPU->nOptimize.validCheck == 0) {
        return false;
    }
    if (pCPU->nOptimize.checkNext != addressN64 - 4) {
        pCPU->nOptimize.checkNext = 0;
        return false;
    }
    pCPU->nOptimize.checkNext = 0;

    if (!cpuNoBranchTo(pCPU->pFunctionLast, addressN64)) {
        return false;
    }

    switch (MIPS_OP(opcode)) {
        case 0x0D: // ori
            if (pCPU->nOptimize.destGPR == MIPS_RS(opcode) && MIPS_RS(opcode) == MIPS_RT(opcode)) {
                if (pCPU->nOptimize.checkType != 0x3E8) {
                    return false;
                }
                anCode[*iCode - 1] = 0x60000000;
                anCode[(*iCode)++] = 0x60000000 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                     (pCPU->nOptimize.destGPR_mapping << 16) | MIPS_IMM_U16(opcode);
                anCode[(*iCode)++] = 0x60000000;
                anCode[(*iCode)++] = (0x90030000 | (pCPU->nOptimize.destGPR_mapping << 21)) +
                                     (OFFSETOF(pCPU, aGPR[MIPS_RT(opcode)]) + 4);
                pCPU->nOptimize.destGPR_check = 2;
                return true;
            }
            return false;
        case 0x09: // addiu
            if (pCPU->nOptimize.destGPR == MIPS_RS(opcode) && MIPS_RS(opcode) == MIPS_RT(opcode)) {
                if (pCPU->nOptimize.checkType != 0x3E8) {
                    return false;
                }
                anCode[*iCode - 1] = 0x60000000;
                anCode[(*iCode)++] = 0x38000000 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                     (pCPU->nOptimize.destGPR_mapping << 16) | MIPS_IMM_U16(opcode);
                anCode[(*iCode)++] = 0x60000000;
                anCode[(*iCode)++] = (0x90030000 | (pCPU->nOptimize.destGPR_mapping << 21)) +
                                     (OFFSETOF(pCPU, aGPR[MIPS_RT(opcode)]) + 4);
                pCPU->nOptimize.destGPR_check = 2;
                return true;
            }
            return false;
        default:
            OSReport("ERROR in cpuNextInstruction() with opcode %p at %p\n", opcode, addressN64);
            OSPanic("_cpuGCN.c", IS_MM_JP ? 3650 : IS_MM_US || IS_MM_EU ? 3636 : 3621, "");
            break;
    }

    return false;
}

void cpuRetraceCallback(u32 nCount) { SYSTEM_CPU(gpSystem)->nRetrace = nCount; }

static bool cpuExecuteUpdate(Cpu* pCPU, s32* pnAddressGCN, u32 nCount) {
    RspUpdateMode eModeUpdate;
    System* pSystem;
    s32 nDelta;
    u32 nCounter;
    u32 nCompare;

    u32 nCounterDelta;
    CpuTreeRoot* root;

    pSystem = (System*)pCPU->pHost;

    if (!romUpdate(SYSTEM_ROM(pSystem))) {
        return false;
    }

#if IS_OOT
    if (pSystem->eTypeROM == SRT_DRMARIO) {
        eModeUpdate = pSystem->bException ? RUM_NONE : RUM_IDLE;
    } else {
        eModeUpdate = ((pCPU->nMode & 0x80) && !pSystem->bException) ? RUM_IDLE : RUM_NONE;
    }
#else
    eModeUpdate = ((pCPU->nMode & 0x80) && !pSystem->bException) ? RUM_IDLE : RUM_NONE;
#endif

    if (!rspUpdate(SYSTEM_RSP(pSystem), eModeUpdate)) {
        return false;
    }

    root = pCPU->gTree;
    treeTimerCheck(pCPU);
    if (pCPU->nRetrace == pCPU->nRetraceUsed && root->kill_number < 12) {
        if (treeKillReason(pCPU, &root->kill_limit)) {
            pCPU->survivalTimer++;
        }
        if (root->kill_limit != 0) {
            treeCleanUp(pCPU, root);
        }
    }

    if (nCount > pCPU->nTickLast) {
        nCounterDelta = fTickScale * ((nCount - pCPU->nTickLast) << nTickMultiplier);
    } else {
        nCounterDelta = fTickScale * ((-1 - pCPU->nTickLast + nCount) << nTickMultiplier);
    }
    if ((pCPU->nMode & 0x40) && pCPU->nRetraceUsed != pCPU->nRetrace) {
        if (videoForceRetrace(SYSTEM_VIDEO(pSystem), true)) {
            nDelta = pCPU->nRetrace - pCPU->nRetraceUsed;
            if (nDelta < 0) {
                nDelta = -nDelta;
            }

            if (nDelta < 4) {
                pCPU->nRetraceUsed++;
            } else {
                pCPU->nRetraceUsed = ((Cpu*)pCPU)->nRetrace;
            }
        }
    }

    if (pCPU->nMode & 1) {
        nCounter = pCPU->anCP0[9];
        nCompare = pCPU->anCP0[11];
        if ((nCounter <= nCompare && nCounter + nCounterDelta >= nCompare) ||
            (nCounter >= nCompare && nCounter + nCounterDelta >= nCompare && nCounter + nCounterDelta < nCounter)) {
            pCPU->nMode &= ~1;
            xlObjectEvent(pCPU->pHost, 0x1000, (void*)3);
        }
    }
    pCPU->anCP0[9] += nCounterDelta;

    if ((pCPU->nMode & 8) && !(pCPU->nMode & 4) && gpSystem->bException) {
        if (!systemCheckInterrupts(gpSystem)) {
            return false;
        }
    }

    if (pCPU->nMode & 4) {
        pCPU->nMode &= ~0x84;
        if (!cpuFindAddress(pCPU, pCPU->nPC, pnAddressGCN)) {
            return false;
        }
    }
    return true;
}

#include "emulator/_cpuDecodePPC2.c"

static inline bool cpuCheckInterrupts(Cpu* pCPU) {
    System* pSystem;

    pSystem = (System*)pCPU->pHost;
    if (pSystem->bException) {
        if (!systemCheckInterrupts(pSystem)) {
            return false;
        }
    } else {
        videoForceRetrace(SYSTEM_VIDEO(pSystem), false);
    }

    return true;
}

static inline bool cpuExecuteCacheInstruction(Cpu* pCPU) {
    s32* pBuffer;

    if (!cpuGetAddressBuffer(pCPU, (void**)&pBuffer, pCPU->nPC)) {
        return false;
    }
    pBuffer[-1] = 0;
    pBuffer -= (pCPU->nPC - pCPU->nCallLast) >> 2;
    pBuffer[0] = 0x03E00008;
    pBuffer[1] = 0;

    return true;
}

#if IS_MM_JP
static bool cpuPrintOpcode(Cpu* pCPU, s32 unused, s32 nAddressN64) {
    bool bFlag;
    u32 nOpcode;
    u32* opcode;
    u32 nAddress;
    s32 pad1;
    char acLine[1024];
    char acSpace[16];
    char szText[8][64];
    char acAddress[256];
    s32 nTarget;
    s32 pad2[3];

    szText[0][0x0] = '\0';
    szText[1][0x0] = '\0';
    szText[2][0x0] = '\0';
    szText[3][0x0] = '\0';
    szText[4][0x0] = '\0';
    szText[5][0x0] = '\0';
    szText[6][0x0] = '\0';
    szText[7][0x0] = '\0';

    ramGetBuffer(SYSTEM_RAM(pCPU->pHost), &opcode, nAddressN64, NULL);
    nOpcode = *opcode;

    switch (MIPS_OP(nOpcode)) {
        case 0x0:
            switch (nOpcode & 0x3F) {
                case 0x0:
                    if (nOpcode == 0x0) {
                        strcpy(szText[0], "NOP");
                    } else {
                        strcpy(szText[0], "SLL");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                        sprintf(szText[3], "%d", MIPS_SA(nOpcode));
                    }
                    break;
                case 0x2:
                    strcpy(szText[0], "SRL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    sprintf(szText[3], "%d", MIPS_SA(nOpcode));
                    break;
                case 0x3:
                    strcpy(szText[0], "SRA");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    sprintf(szText[3], "%d", MIPS_SA(nOpcode));
                    break;
                case 0x4:
                    strcpy(szText[0], "SLLV");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x6:
                    strcpy(szText[0], "SRLV");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x7:
                    strcpy(szText[0], "SRAV");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x8:
                    strcpy(szText[0], "JR");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x9:
                    strcpy(szText[0], "JALR");
                    if (MIPS_RD(nOpcode) == 0x1F) {
                        strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    } else {
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    }
                    break;
                case 0xC:
                    strcpy(szText[0], "SYSCALL");
                    break;
                case 0xD:
                    strcpy(szText[0], "BREAK");
                    break;
                case 0xF:
                    strcpy(szText[0], "SYNC");
                    break;
                case 0x10:
                    strcpy(szText[0], "MFHI");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    break;
                case 0x11:
                    strcpy(szText[0], "MTHI");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x12:
                    strcpy(szText[0], "MFLO");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    break;
                case 0x13:
                    strcpy(szText[0], "MTLO");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x14:
                    strcpy(szText[0], "DSLLV");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x16:
                    strcpy(szText[0], "DSRLV");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x17:
                    strcpy(szText[0], "DSRAV");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RS(nOpcode)]);
                    break;
                case 0x18:
                    strcpy(szText[0], "MULT");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x19:
                    strcpy(szText[0], "MULTU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x1A:
                    strcpy(szText[0], "DIV");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x1B:
                    strcpy(szText[0], "DIVU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x1C:
                    strcpy(szText[0], "DMULT");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x1D:
                    strcpy(szText[0], "DMULTU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x1E:
                    strcpy(szText[0], "DDIV");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x1F:
                    strcpy(szText[0], "DDIVU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x20:
                    if (MIPS_RS(nOpcode) == 0 || MIPS_RT(nOpcode) == 0) {
                        strcpy(szText[0], "MOV");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2],
                               MIPS_RT(nOpcode) == 0 ? gaszNameGPR[MIPS_RS(nOpcode)] : gaszNameGPR[MIPS_RT(nOpcode)]);
                    } else {
                        strcpy(szText[0], "ADD");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                        strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    }
                    break;
                case 0x21:
                    if (MIPS_RS(nOpcode) == 0 || MIPS_RT(nOpcode) == 0) {
                        strcpy(szText[0], "MOV");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2],
                               MIPS_RS(nOpcode) == 0 ? gaszNameGPR[MIPS_RT(nOpcode)] : gaszNameGPR[MIPS_RS(nOpcode)]);
                    } else {
                        strcpy(szText[0], "ADDU");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                        strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    }
                    break;
                case 0x22:
                    strcpy(szText[0], "SUB");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x23:
                    strcpy(szText[0], "SUBU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x24:
                    if (MIPS_RS(nOpcode) == 0 || MIPS_RT(nOpcode) == 0) {
                        strcpy(szText[0], "ZERO");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    } else {
                        strcpy(szText[0], "AND");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                        strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    }
                    break;
                case 0x25:
                    if (MIPS_RS(nOpcode) == 0 || MIPS_RT(nOpcode) == 0) {
                        strcpy(szText[0], "MOV");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2],
                               MIPS_RS(nOpcode) == 0 ? gaszNameGPR[MIPS_RT(nOpcode)] : gaszNameGPR[MIPS_RS(nOpcode)]);
                    } else {
                        strcpy(szText[0], "OR");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                        strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    }
                    break;
                case 0x26:
                    if (MIPS_RS(nOpcode) == MIPS_RT(nOpcode)) {
                        strcpy(szText[0], "ZERO");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    } else {
                        strcpy(szText[0], "XOR");
                        strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                        strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                        strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    }
                    break;
                case 0x27:
                    strcpy(szText[0], "NOR");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x2A:
                    strcpy(szText[0], "SLT");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x2B:
                    strcpy(szText[0], "SLTU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x2C:
                    strcpy(szText[0], "DADD");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x2D:
                    strcpy(szText[0], "DADDU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x2E:
                    strcpy(szText[0], "DSUB");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x2F:
                    strcpy(szText[0], "DSUBU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[3], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x30:
                    strcpy(szText[0], "TGE");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x31:
                    strcpy(szText[0], "TGEU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x32:
                    strcpy(szText[0], "TLT");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x33:
                    strcpy(szText[0], "TLTU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x34:
                    strcpy(szText[0], "TEQ");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x36:
                    strcpy(szText[0], "TNE");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    break;
                case 0x38:
                    strcpy(szText[0], "DSLL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    sprintf(szText[3], "%d", MIPS_SA(nOpcode));
                    break;
                case 0x3A:
                    strcpy(szText[0], "DSRL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    sprintf(szText[3], "%d", MIPS_SA(nOpcode));
                    break;
                case 0x3B:
                    strcpy(szText[0], "DSRA");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    sprintf(szText[3], "%d", MIPS_SA(nOpcode));
                    break;
                case 0x3C:
                    strcpy(szText[0], "DSLL32");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    sprintf(szText[3], "%d", MIPS_SA(nOpcode));
                    break;
                case 0x3E:
                    strcpy(szText[0], "DSRL32");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    sprintf(szText[3], "%d", MIPS_SA(nOpcode));
                    break;
                case 0x3F:
                    strcpy(szText[0], "DSRA32");
                    strcpy(szText[1], gaszNameGPR[MIPS_RD(nOpcode)]);
                    strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                    sprintf(szText[3], "%d", MIPS_SA(nOpcode));
            }
            break;
        case 0x01:
            switch (MIPS_RT(nOpcode)) {
                case 0x0:
                    strcpy(szText[0], "BLTZ");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                    break;
                case 0x1:
                    strcpy(szText[0], "BGEZ");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                    break;
                case 0x2:
                    strcpy(szText[0], "BLTZL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                    break;
                case 0x3:
                    strcpy(szText[0], "BGEZL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                    break;
                case 0x8:
                    strcpy(szText[0], "TGEI");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
                    break;
                case 0x9:
                    strcpy(szText[0], "TGEIU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
                    break;
                case 0xA:
                    strcpy(szText[0], "TLTI");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
                    break;
                case 0xB:
                    strcpy(szText[0], "TLTIU");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
                    break;
                case 0xC:
                    strcpy(szText[0], "TEQI");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
                    break;
                case 0xE:
                    strcpy(szText[0], "TNEI");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
                    break;
                case 0x10:
                    strcpy(szText[0], "BLTZAL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                    break;
                case 0x11:
                    strcpy(szText[0], "BGEZAL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                    break;
                case 0x12:
                    strcpy(szText[0], "BLTZALL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                    break;
                case 0x13:
                    strcpy(szText[0], "BGEZALL");
                    strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                    sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                    break;
            }
            break;
        case 0x2:
            nTarget = MIPS_TARGET(nOpcode) << 2;
            strcpy(szText[0], "J");
            sprintf(szText[1], "%x", ((nAddressN64 + 4) & 0xF0000000) | nTarget);
            break;
        case 0x3:
            nTarget = MIPS_TARGET(nOpcode) << 2;
            strcpy(szText[0], "JAL");
            sprintf(szText[1], "%x", ((nAddressN64 + 4) & 0xF0000000) | nTarget);
            break;
        case 0x4:
            if (MIPS_RS(nOpcode) == MIPS_RT(nOpcode)) {
                strcpy(szText[0], "BRA");
                sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            } else {
                strcpy(szText[0], "BEQ");
                strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                sprintf(szText[3], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            }
            break;
        case 0x5:
            strcpy(szText[0], "BNE");
            strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
            strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[3], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            break;
        case 0x6:
            strcpy(szText[0], "BLEZ");
            strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
            sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            break;
        case 0x7:
            strcpy(szText[0], "BGTZ");
            strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
            sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            break;
        case 0x8:
            nTarget = MIPS_IMM_S16(nOpcode);
            if (nTarget == 0x0) {
                strcpy(szText[0], "MOV");
                strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
            } else {
                strcpy(szText[0], "ADDI");
                strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                sprintf(szText[3], "%04x", nTarget);
            }
            break;
        case 0x9:
            nTarget = MIPS_IMM_S16(nOpcode);
            if (nTarget == 0x0) {
                strcpy(szText[0], "MOV");
                strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
            } else {
                strcpy(szText[0], "ADDIU");
                strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                sprintf(szText[3], "%04x", nTarget);
            }
            break;
        case 0xA:
            strcpy(szText[0], "SLTI");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
            sprintf(szText[3], "%04x", MIPS_IMM_S16(nOpcode));
            break;
        case 0xB:
            strcpy(szText[0], "SLTIU");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
            sprintf(szText[3], "%04x", MIPS_IMM_S16(nOpcode));
            break;
        case 0xC:
            if (MIPS_RS(nOpcode) == 0x0) {
                strcpy(szText[0], "ZERO?");
                strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            } else {
                strcpy(szText[0], "ANDI");
                strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                //! TODO: fake match
                sprintf(szText[3], "%04x", ((u16)((nOpcode) & 0xFFFFF)));
            }
            break;
        case 0xD:
            if (MIPS_RS(nOpcode) == 0x0) {
                strcpy(szText[0], "MOVI");
                strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                //! TODO: fake match
                sprintf(szText[2], "%04x", ((u16)((nOpcode) & 0xFFFFF)));
            } else {
                strcpy(szText[0], "ORI");
                strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
                //! TODO: fake match
                sprintf(szText[3], "%04x", ((u16)((nOpcode) & 0xFFFFF)));
            }
            break;
        case 0xE:
            strcpy(szText[0], "XORI");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
            //! TODO: fake match
            sprintf(szText[3], "%04x", ((u16)((nOpcode) & 0xFFFFF)));
            break;
        case 0xF:
            strcpy(szText[0], "LUI");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            //! TODO: fake match
            sprintf(szText[2], "%04x", ((u16)((nOpcode) & 0xFFFFF)));
            break;
        case 0x10:
            switch (nOpcode & 0x3F) {
                case 0x1:
                    strcpy(szText[0], "TLBR");
                    break;
                case 0x2:
                    strcpy(szText[0], "TLBWI");
                    break;
                case 0x5:
                    strcpy(szText[0], "TLBWR");
                    break;
                case 0x8:
                    strcpy(szText[0], "TLBP");
                    break;
                case 0x18:
                    strcpy(szText[0], "ERET");
                    break;
                default:
                    switch (MIPS_RS(nOpcode)) {
                        case 0x0:
                            strcpy(szText[0], "MFC0");
                            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                            strcpy(szText[2], gaszNameCP0[MIPS_RD(nOpcode)]);
                            break;
                        case 0x1:
                            strcpy(szText[0], "DMFC0");
                            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                            strcpy(szText[2], gaszNameCP0[MIPS_RD(nOpcode)]);
                            break;
                        case 0x4:
                            strcpy(szText[0], "MTC0");
                            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                            strcpy(szText[2], gaszNameCP0[MIPS_RD(nOpcode)]);
                            break;
                        case 0x5:
                            strcpy(szText[0], "DMTC0");
                            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                            strcpy(szText[2], gaszNameGPR[MIPS_RD(nOpcode)]);
                            break;
                        case 0x8:
                            switch (MIPS_RS(nOpcode)) {
                                case 0:
                                    strcpy(szText[0], "BC0F");
                                    sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                                    break;
                                case 1:
                                    strcpy(szText[0], "BC0T");
                                    sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                                    break;
                                case 2:
                                    strcpy(szText[0], "BC0FL");
                                    sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                                    break;
                                case 3:
                                    strcpy(szText[0], "BC0TL");
                                    sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                                    break;
                                default:
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 0x11:
            if ((nOpcode & 0x7FF) == 0 && MIPS_FMT(nOpcode) < 0x10) {
                switch ((u8)MIPS_FMT(nOpcode)) {
                    case 0x0:
                        strcpy(szText[0], "MFC1");
                        strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                        strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                        break;
                    case 0x1:
                        strcpy(szText[0], "DMFC1");
                        strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                        strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                        break;
                    case 0x2:
                        strcpy(szText[0], "CFC1");
                        strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                        strcpy(szText[2], gaszNameCP1[MIPS_FS(nOpcode)]);
                        break;
                    case 0x4:
                        strcpy(szText[0], "MTC1");
                        strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                        strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                        break;
                    case 0x5:
                        strcpy(szText[0], "DMTC1");
                        strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                        strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                        break;
                    case 0x6:
                        strcpy(szText[0], "CTC1");
                        strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
                        strcpy(szText[2], gaszNameCP1[MIPS_FS(nOpcode)]);
                        break;
                    default:
                        break;
                }
            } else if (MIPS_RS(nOpcode) == 0x08) {
                switch (MIPS_RT(nOpcode)) {
                    case 0:
                        strcpy(szText[0], "BC1F");
                        sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                        break;
                    case 1:
                        strcpy(szText[0], "BC1T");
                        sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                        break;
                    case 2:
                        strcpy(szText[0], "BC1FL");
                        sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                        break;
                    case 3:
                        strcpy(szText[0], "BC1TL");
                        sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
                        break;
                }
            } else {
                switch ((u8)MIPS_FMT(nOpcode)) {
                    case 0x10:
                        switch (nOpcode & 0x3F) {
                            case 0x0:
                                strcpy(szText[0], "ADD");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x1:
                                strcpy(szText[0], "SUB");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x2:
                                strcpy(szText[0], "MUL");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3:
                                strcpy(szText[0], "DIV");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x4:
                                strcpy(szText[0], "SQRT");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x5:
                                strcpy(szText[0], "ABS");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x6:
                                strcpy(szText[0], "MOVE");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x7:
                                strcpy(szText[0], "NEG");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x8:
                                strcpy(szText[0], "ROUND.L");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x9:
                                strcpy(szText[0], "TRUNC.L");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xA:
                                strcpy(szText[0], "CEIL.L");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xB:
                                strcpy(szText[0], "FLOOR.L");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xC:
                                strcpy(szText[0], "ROUND.W");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xD:
                                strcpy(szText[0], "TRUNC.W");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xE:
                                strcpy(szText[0], "CEIL.W");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xF:
                                strcpy(szText[0], "FLOOR.W");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x20:
                                strcpy(szText[0], "CVT.S");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x21:
                                strcpy(szText[0], "CVT.D");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x24:
                                strcpy(szText[0], "CVT.W");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x25:
                                strcpy(szText[0], "CVT.L");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x30:
                                strcpy(szText[0], "C.F");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x31:
                                strcpy(szText[0], "C.UN");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x32:
                                strcpy(szText[0], "C.EQ");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x33:
                                strcpy(szText[0], "C.UEQ");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x34:
                                strcpy(szText[0], "C.OLT");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x35:
                                strcpy(szText[0], "C.ULT");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x36:
                                strcpy(szText[0], "C.OLE");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x37:
                                strcpy(szText[0], "C.ULE");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x38:
                                strcpy(szText[0], "C.SF");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x39:
                                strcpy(szText[0], "C.NGLE");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3A:
                                strcpy(szText[0], "C.SEQ");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3B:
                                strcpy(szText[0], "C.NGL");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3C:
                                strcpy(szText[0], "C.LT");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3D:
                                strcpy(szText[0], "C.NGE");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3E:
                                strcpy(szText[0], "C.LE");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3F:
                                strcpy(szText[0], "C.NGT");
                                strcat(szText[0], ".S");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                        }
                        break;
                    case 0x11:
                        switch (nOpcode & 0x3F) {
                            case 0x0:
                                strcpy(szText[0], "ADD");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x1:
                                strcpy(szText[0], "SUB");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x2:
                                strcpy(szText[0], "MUL");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3:
                                strcpy(szText[0], "DIV");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x4:
                                strcpy(szText[0], "SQRT");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x5:
                                strcpy(szText[0], "ABS");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x6:
                                strcpy(szText[0], "MOVE");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x7:
                                strcpy(szText[0], "NEG");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x8:
                                strcpy(szText[0], "ROUND.L");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x9:
                                strcpy(szText[0], "TRUNC.L");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xA:
                                strcpy(szText[0], "CEIL.L");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xB:
                                strcpy(szText[0], "FLOOR.L");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xC:
                                strcpy(szText[0], "ROUND.W");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xD:
                                strcpy(szText[0], "TRUNC.W");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xE:
                                strcpy(szText[0], "CEIL.W");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xF:
                                strcpy(szText[0], "FLOOR.W");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x20:
                                strcpy(szText[0], "CVT.S");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x21:
                                strcpy(szText[0], "CVT.D");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x24:
                                strcpy(szText[0], "CVT.W");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x25:
                                strcpy(szText[0], "CVT.L");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x30:
                                strcpy(szText[0], "C.F");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x31:
                                strcpy(szText[0], "C.UN");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x32:
                                strcpy(szText[0], "C.EQ");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x33:
                                strcpy(szText[0], "C.UEQ");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x34:
                                strcpy(szText[0], "C.OLT");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x35:
                                strcpy(szText[0], "C.ULT");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x36:
                                strcpy(szText[0], "C.OLE");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x37:
                                strcpy(szText[0], "C.ULE");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x38:
                                strcpy(szText[0], "C.SF");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x39:
                                strcpy(szText[0], "C.NGLE");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3A:
                                strcpy(szText[0], "C.SEQ");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3B:
                                strcpy(szText[0], "C.NGL");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3C:
                                strcpy(szText[0], "C.LT");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3D:
                                strcpy(szText[0], "C.NGE");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3E:
                                strcpy(szText[0], "C.LE");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3F:
                                strcpy(szText[0], "C.NGT");
                                strcat(szText[0], ".D");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                        }
                        break;
                    case 0x14:
                        switch (nOpcode & 0x3F) {
                            case 0x0:
                                strcpy(szText[0], "ADD");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x1:
                                strcpy(szText[0], "SUB");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x2:
                                strcpy(szText[0], "MUL");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3:
                                strcpy(szText[0], "DIV");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x4:
                                strcpy(szText[0], "SQRT");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x5:
                                strcpy(szText[0], "ABS");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x6:
                                strcpy(szText[0], "MOVE");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x7:
                                strcpy(szText[0], "NEG");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x8:
                                strcpy(szText[0], "ROUND.L");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x9:
                                strcpy(szText[0], "TRUNC.L");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xA:
                                strcpy(szText[0], "CEIL.L");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xB:
                                strcpy(szText[0], "FLOOR.L");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xC:
                                strcpy(szText[0], "ROUND.W");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xD:
                                strcpy(szText[0], "TRUNC.W");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xE:
                                strcpy(szText[0], "CEIL.W");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xF:
                                strcpy(szText[0], "FLOOR.W");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x20:
                                strcpy(szText[0], "CVT.S");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x21:
                                strcpy(szText[0], "CVT.D");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x24:
                                strcpy(szText[0], "CVT.W");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x25:
                                strcpy(szText[0], "CVT.L");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x30:
                                strcpy(szText[0], "C.F");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x31:
                                strcpy(szText[0], "C.UN");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x32:
                                strcpy(szText[0], "C.EQ");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x33:
                                strcpy(szText[0], "C.UEQ");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x34:
                                strcpy(szText[0], "C.OLT");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x35:
                                strcpy(szText[0], "C.ULT");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x36:
                                strcpy(szText[0], "C.OLE");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x37:
                                strcpy(szText[0], "C.ULE");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x38:
                                strcpy(szText[0], "C.SF");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x39:
                                strcpy(szText[0], "C.NGLE");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3A:
                                strcpy(szText[0], "C.SEQ");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3B:
                                strcpy(szText[0], "C.NGL");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3C:
                                strcpy(szText[0], "C.LT");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3D:
                                strcpy(szText[0], "C.NGE");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3E:
                                strcpy(szText[0], "C.LE");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3F:
                                strcpy(szText[0], "C.NGT");
                                strcat(szText[0], ".W");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                        }
                        break;
                    case 0x15:
                        switch (nOpcode & 0x3F) {
                            case 0x0:
                                strcpy(szText[0], "ADD");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x1:
                                strcpy(szText[0], "SUB");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x2:
                                strcpy(szText[0], "MUL");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3:
                                strcpy(szText[0], "DIV");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[3], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x4:
                                strcpy(szText[0], "SQRT");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x5:
                                strcpy(szText[0], "ABS");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x6:
                                strcpy(szText[0], "MOVE");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x7:
                                strcpy(szText[0], "NEG");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x8:
                                strcpy(szText[0], "ROUND.L");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x9:
                                strcpy(szText[0], "TRUNC.L");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xA:
                                strcpy(szText[0], "CEIL.L");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xB:
                                strcpy(szText[0], "FLOOR.L");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xC:
                                strcpy(szText[0], "ROUND.W");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xD:
                                strcpy(szText[0], "TRUNC.W");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xE:
                                strcpy(szText[0], "CEIL.W");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0xF:
                                strcpy(szText[0], "FLOOR.W");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x20:
                                strcpy(szText[0], "CVT.S");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x21:
                                strcpy(szText[0], "CVT.D");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x24:
                                strcpy(szText[0], "CVT.W");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x25:
                                strcpy(szText[0], "CVT.L");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FD(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FS(nOpcode)]);
                                break;
                            case 0x30:
                                strcpy(szText[0], "C.F");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x31:
                                strcpy(szText[0], "C.UN");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x32:
                                strcpy(szText[0], "C.EQ");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x33:
                                strcpy(szText[0], "C.UEQ");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x34:
                                strcpy(szText[0], "C.OLT");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x35:
                                strcpy(szText[0], "C.ULT");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x36:
                                strcpy(szText[0], "C.OLE");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x37:
                                strcpy(szText[0], "C.ULE");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x38:
                                strcpy(szText[0], "C.SF");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x39:
                                strcpy(szText[0], "C.NGLE");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3A:
                                strcpy(szText[0], "C.SEQ");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3B:
                                strcpy(szText[0], "C.NGL");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3C:
                                strcpy(szText[0], "C.LT");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3D:
                                strcpy(szText[0], "C.NGE");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3E:
                                strcpy(szText[0], "C.LE");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                            case 0x3F:
                                strcpy(szText[0], "C.NGT");
                                strcat(szText[0], ".L");
                                strcpy(szText[1], gaszNameFPR[MIPS_FS(nOpcode)]);
                                strcpy(szText[2], gaszNameFPR[MIPS_FT(nOpcode)]);
                                break;
                        }
                        break;
                }
            }
            break;
        case 0x12:
            strcpy(szText[0], "COP2");
            strcpy(szText[1], "????");
            break;
        case 0x13:
            strcpy(szText[0], "COP3");
            strcpy(szText[1], "????");
            break;
        case 0x14:
            if (MIPS_RS(nOpcode) == MIPS_RT(nOpcode)) {
                strcpy(szText[0], "BRAL");
                sprintf(szText[1], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            } else {
                strcpy(szText[0], "BEQL");
                strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
                strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
                sprintf(szText[3], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            }
            break;
        case 0x15:
            strcpy(szText[0], "BNEL");
            strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
            strcpy(szText[2], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[3], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            break;
        case 0x16:
            strcpy(szText[0], "BLEZL");
            strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
            sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            break;
        case 0x17:
            strcpy(szText[0], "BGTZL");
            strcpy(szText[1], gaszNameGPR[MIPS_RS(nOpcode)]);
            sprintf(szText[2], "%x", nAddressN64 + 4 + (MIPS_IMM_S16(nOpcode) << 2));
            break;
        case 0x18:
            strcpy(szText[0], "DADDI");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
            sprintf(szText[3], "%04x", MIPS_IMM_S16(nOpcode));
            break;
        case 0x19:
            strcpy(szText[0], "DADDIU");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            strcpy(szText[2], gaszNameGPR[MIPS_RS(nOpcode)]);
            sprintf(szText[3], "%04x", MIPS_IMM_S16(nOpcode));
            break;
        case 0x1F:
            nTarget = MIPS_IMM_S16(nOpcode);
            if (nTarget >= 0x0 && nTarget < SYSTEM_LIBRARY(pCPU->pHost)->nCountFunction) {
                strcpy(szText[0], "LIBRARY");
                sprintf(szText[1], "\'%s\'", SYSTEM_LIBRARY(pCPU->pHost)->aFunction[nTarget].szName);
            } else {
                strcpy(szText[0], "???");
            }
            break;
        case 0x1A:
            strcpy(szText[0], "LDL");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x1B:
            strcpy(szText[0], "LDR");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x27:
            strcpy(szText[0], "LWU");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x20:
            strcpy(szText[0], "LB");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x21:
            strcpy(szText[0], "LH");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x22:
            strcpy(szText[0], "LWL");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x23:
            strcpy(szText[0], "LW");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x24:
            strcpy(szText[0], "LBU");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x25:
            strcpy(szText[0], "LHU");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x26:
            strcpy(szText[0], "LWR");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x28:
            strcpy(szText[0], "SB");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x29:
            strcpy(szText[0], "SH");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x2A:
            strcpy(szText[0], "SWL");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x2B:
            strcpy(szText[0], "SW");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x2C:
            strcpy(szText[0], "SDL");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x2D:
            strcpy(szText[0], "SDR");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x2E:
            strcpy(szText[0], "SWR");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x2F:
            strcpy(szText[0], "CACHE");
            break;
        case 0x30:
            strcpy(szText[0], "LL");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x31:
            strcpy(szText[0], "LWC1");
            strcpy(szText[1], gaszNameFPR[MIPS_FT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x34:
            strcpy(szText[0], "LLD");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x35:
            strcpy(szText[0], "LDC1");
            strcpy(szText[1], gaszNameFPR[MIPS_FT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x37:
            strcpy(szText[0], "LD");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x38:
            strcpy(szText[0], "SC");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x39:
            strcpy(szText[0], "SWC1");
            strcpy(szText[1], gaszNameFPR[MIPS_FT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x3C:
            strcpy(szText[0], "SCD");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x3D:
            strcpy(szText[0], "SDC1");
            strcpy(szText[1], gaszNameFPR[MIPS_FT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        case 0x3F:
            strcpy(szText[0], "SD");
            strcpy(szText[1], gaszNameGPR[MIPS_RT(nOpcode)]);
            sprintf(szText[2], "%04x", MIPS_IMM_S16(nOpcode));
            sprintf(szText[3], "(%s)", gaszNameGPR[MIPS_RS(nOpcode)]);
            break;
        default:
            break;
    }

    strcpy(acSpace, "        ");
    acSpace[0x8 - strlen(szText[0])] = '\0';

    if (szText[3][0x0] == '(') {
        strcpy(szText[3], szText[3] + 0x1);
        bFlag = true;
    } else {
        bFlag = false;
    }

    sprintf(acAddress, "0x%08x  ", nAddressN64);
    sprintf(acLine, "%s   %08x      %s%s%s%c%s%c%s%c", acAddress, nOpcode, szText[0], acSpace, szText[1],
            szText[2][0x0] != '\0' ? ',' : ' ', szText[2], szText[3][0x0] != '\0' ? (bFlag ? '(' : ',') : ' ',
            szText[3], szText[4][0x0] != '\0' ? ',' : ' ');
    OSReport("%s\n", acLine);
    return true;
}
#endif

static s32 cpuExecuteOpcode(Cpu* pCPU, s32 nCount0, s32 nAddressN64, s32 nAddressGCN) {
    s32 pad1[2];
    u64 save;
    s32 restore;
#if IS_MM
    bool skipDecode;
#endif
    u32 nOpcode;
    u32* opcode;
    s32 pad2;
    CpuDevice** apDevice;
    u8* aiDevice;
#if IS_MM
    s32 reg;
    int value;
#endif
    s32 iEntry;
    s32 nCount;
    s8 nData8;
    s16 nData16;
    s32 nData32;
    s64 nData64;
    s32 nAddress;
    CpuFunction* pFunction;
    s32 nTick;
    s32 pad3[2];

    restore = 0;

#if IS_MM
    skipDecode = false;
#endif

    nTick = OSGetTick();
    if (pCPU->nWaitPC != 0) {
        pCPU->nMode |= 8;
    } else {
        pCPU->nMode &= ~8;
    }

    aiDevice = pCPU->aiDevice;
    apDevice = pCPU->apDevice;

    ramGetBuffer(SYSTEM_RAM(pCPU->pHost), (void**)&opcode, nAddressN64, NULL);
    nOpcode = *opcode;
    pCPU->nPC = nAddressN64 + 4;
    if (nOpcode == 0xACBF011C) { // sw $ra,0x11C($a1)
        save = pCPU->aGPR[31].u64;
        restore = 1;
        pCPU->aGPR[31].s32 = pCPU->nReturnAddrLast;
    }

#if IS_MM
    if (gpSystem->eTypeROM == SRT_ZELDA2) {
        if (((nOpcode) & ~0x3FF0000) == 0x3C008100) {
            gRegCount++;
            gRegList[MIPS_RT(nOpcode)] = 1;
        } else if (gRegCount != 0 && ((nOpcode) & ~0x3FF0000) == 0xA0000000) {
            reg = MIPS_RS(nOpcode);

            if (gRegList[reg] != 0) {
                gRegCount--;
                gRegList[reg] = 0;

                value = pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                if (value == 0x00) {
                    simulatorPlayMovie();
                } else if (value == 0x01) {
                    romReloadRange(pCPU);
                } else if (value >= 0x10 && value <= 0x19) {
                    mcardSaveDisplay = value;
#if IS_MM_JP
                } else if (value == 0x1A) {
                    mcardSaveDisplay = value;
#endif
#if VERSION != MM_U
                } else if (value >= 0x30 && value <= 0x31) {
                    mcardSaveCamera(value);
#endif
                } else {
                    soundPlayOcarinaTune(pCPU);
                }
                skipDecode = true;
            }
        }
    }

    if (!skipDecode)
#endif
    {
        switch (MIPS_OP(nOpcode)) {
            case 0x00: // special
                switch (MIPS_FUNCT(nOpcode)) {
                    case 0x00: // sll
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32 << MIPS_SA(nOpcode);
                        break;
                    case 0x02: // srl
                        pCPU->aGPR[MIPS_RD(nOpcode)].u32 = pCPU->aGPR[MIPS_RT(nOpcode)].u32 >> MIPS_SA(nOpcode);
                        break;
                    case 0x03: // sra
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32 >> MIPS_SA(nOpcode);
                        break;
                    case 0x04: // sllv
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32
                                                           << (pCPU->aGPR[MIPS_RS(nOpcode)].s32 & 0x1F);
                        break;
                    case 0x06: // srlv
                        pCPU->aGPR[MIPS_RD(nOpcode)].u32 =
                            pCPU->aGPR[MIPS_RT(nOpcode)].u32 >> (pCPU->aGPR[MIPS_RS(nOpcode)].s32 & 0x1F);
                        break;
                    case 0x07: // srav
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            pCPU->aGPR[MIPS_RT(nOpcode)].s32 >> (pCPU->aGPR[MIPS_RS(nOpcode)].s32 & 0x1F);
                        break;
                    case 0x08: // jr
                        pCPU->nWaitPC = pCPU->aGPR[MIPS_RS(nOpcode)].u32;
                        break;
                    case 0x09: // jalr
                        pCPU->nWaitPC = pCPU->aGPR[MIPS_RS(nOpcode)].u32;
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->nPC + 4;
                        break;
                    case 0x0C: // syscall
                        cpuException(pCPU, CEC_SYSCALL, 0);
                        break;
                    case 0x0D: // break
                        cpuException(pCPU, CEC_BREAK, 0);
                        break;
                    case 0x10: // mfhi
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->nHi;
                        break;
                    case 0x11: // mthi
                        pCPU->nHi = pCPU->aGPR[MIPS_RS(nOpcode)].s64;
                        break;
                    case 0x12: // mflo
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->nLo;
                        break;
                    case 0x13: // mtlo
                        pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].s64;
                        break;
                    case 0x14: // dsllv
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64
                                                           << (pCPU->aGPR[MIPS_RS(nOpcode)].s64 & 0x3F);
                        break;
                    case 0x16: // dsrlv
                        pCPU->aGPR[MIPS_RD(nOpcode)].u64 =
                            pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> (pCPU->aGPR[MIPS_RS(nOpcode)].s64 & 0x3F);
                        break;
                    case 0x17: // dsrav
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 =
                            pCPU->aGPR[MIPS_RT(nOpcode)].s64 >> (pCPU->aGPR[MIPS_RS(nOpcode)].s64 & 0x3F);
                        break;
                    case 0x18: // mult
                        nData64 = (s64)pCPU->aGPR[MIPS_RS(nOpcode)].s32 * (s64)pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        pCPU->nLo = (s32)(nData64 & 0xFFFFFFFF);
                        pCPU->nHi = (s32)(nData64 >> 32);
                        break;
                    case 0x19: // multu
                        nData64 = (u64)pCPU->aGPR[MIPS_RS(nOpcode)].u32 * (u64)pCPU->aGPR[MIPS_RT(nOpcode)].u32;
                        pCPU->nLo = (s32)(nData64 & 0xFFFFFFFF);
                        pCPU->nHi = (s32)(nData64 >> 32);
                        break;
                    case 0x1A: // div
                        if (pCPU->aGPR[MIPS_RT(nOpcode)].s32 != 0) {
                            pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].s32 / pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                            pCPU->nHi = pCPU->aGPR[MIPS_RS(nOpcode)].s32 % pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        }
                        break;
                    case 0x1B: // divu
                        if (pCPU->aGPR[MIPS_RT(nOpcode)].u32 != 0) {
                            pCPU->nLo = (s32)(pCPU->aGPR[MIPS_RS(nOpcode)].u32 / pCPU->aGPR[MIPS_RT(nOpcode)].u32);
                            pCPU->nHi = (s32)(pCPU->aGPR[MIPS_RS(nOpcode)].u32 % pCPU->aGPR[MIPS_RT(nOpcode)].u32);
                        }
                        break;
                    case 0x1C: // dmult
                        pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].s64 * pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                        pCPU->nHi = (pCPU->nLo < 0) ? -1 : 0;
                        break;
                    case 0x1D: // dmultu
                        pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].u64 * pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                        pCPU->nHi = (pCPU->nLo < 0) ? -1 : 0;
                        break;
                    case 0x1E: // ddiv
                        if (pCPU->aGPR[MIPS_RT(nOpcode)].s64 != 0) {
                            pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].s64 / pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                            pCPU->nHi = pCPU->aGPR[MIPS_RS(nOpcode)].s64 % pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                        }
                        break;
                    case 0x1F: // ddivu
                        if (pCPU->aGPR[MIPS_RT(nOpcode)].u64 != 0) {
                            pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].u64 / pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                            pCPU->nHi = pCPU->aGPR[MIPS_RS(nOpcode)].u64 % pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                        }
                        break;
                    case 0x20: // add
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].s32 + pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        break;
                    case 0x21: // addu
                        pCPU->aGPR[MIPS_RD(nOpcode)].u32 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].u32 + pCPU->aGPR[MIPS_RT(nOpcode)].u32;
                        break;
                    case 0x22: // sub
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].s32 - pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        break;
                    case 0x23: // subu
                        pCPU->aGPR[MIPS_RD(nOpcode)].u32 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].u32 - pCPU->aGPR[MIPS_RT(nOpcode)].u32;
                        break;
                    case 0x24: // and
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].s32 & pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        break;
                    case 0x25: // or
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].s32 | pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        break;
                    case 0x26: // xor
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].s32 ^ pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        break;
                    case 0x27: // nor
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            ~(pCPU->aGPR[MIPS_RS(nOpcode)].s32 | pCPU->aGPR[MIPS_RT(nOpcode)].s32);
                        break;
                    case 0x2A: // slt
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < pCPU->aGPR[MIPS_RT(nOpcode)].s32) ? 1 : 0;
                        break;
                    case 0x2B: // sltu
                        pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                            (pCPU->aGPR[MIPS_RS(nOpcode)].u32 < pCPU->aGPR[MIPS_RT(nOpcode)].u32) ? 1 : 0;
                        break;
                    case 0x2C: // dadd
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].s64 + pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                        break;
                    case 0x2D: // daddu
                        pCPU->aGPR[MIPS_RD(nOpcode)].u64 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].u64 + pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                        break;
                    case 0x2E: // dsub
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].s64 - pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                        break;
                    case 0x2F: // dsubu
                        pCPU->aGPR[MIPS_RD(nOpcode)].u64 =
                            pCPU->aGPR[MIPS_RS(nOpcode)].u64 - pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                        break;
                    case 0x30: // tge
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x31: // tgeu
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].u32 >= pCPU->aGPR[MIPS_RT(nOpcode)].u32) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x32: // tlt
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x33: // tltu
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].u32 < pCPU->aGPR[MIPS_RT(nOpcode)].u32) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x34: // teq
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 == pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x36: // tne
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 != pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x38: // dsll
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64 << MIPS_SA(nOpcode);
                        break;
                    case 0x3A: // dsrl
                        pCPU->aGPR[MIPS_RD(nOpcode)].u64 = pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> MIPS_SA(nOpcode);
                        break;
                    case 0x3B: // dsra
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64 >> MIPS_SA(nOpcode);
                        break;
                    case 0x3C: // dsll32
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64 << (MIPS_SA(nOpcode) + 32);
                        break;
                    case 0x3E: // dsrl32
                        pCPU->aGPR[MIPS_RD(nOpcode)].u64 = pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> (MIPS_SA(nOpcode) + 32);
                        break;
                    case 0x3F: // dsra32
                        pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64 >> (MIPS_SA(nOpcode) + 32);
                        break;
                }
                break;
            case 0x01: // regimm
                switch (MIPS_RT(nOpcode)) {
                    case 0x00: // bltz
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < 0) {
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        }
                        break;
                    case 0x01: // bgez
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= 0) {
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        }
                        break;
                    case 0x02: // bltzl
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < 0) {
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        } else {
                            pCPU->nMode |= 4;
                            pCPU->nPC += 4;
                        }
                        break;
                    case 0x03: // bgezl
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= 0) {
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        } else {
                            pCPU->nMode |= 4;
                            pCPU->nPC += 4;
                        }
                        break;
                    case 0x08: // tgei
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= MIPS_IMM_S16(nOpcode)) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x09: // tgeiu
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].u32 >= MIPS_IMM_S16(nOpcode)) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x0A: // tlti
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < MIPS_IMM_S16(nOpcode)) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x0B: // tltiu
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].u32 < MIPS_IMM_S16(nOpcode)) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x0C: // teqi
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 == MIPS_IMM_S16(nOpcode)) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x0E: // tnei
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 != MIPS_IMM_S16(nOpcode)) {
                            cpuException(pCPU, CEC_TRAP, 0);
                        }
                        break;
                    case 0x10: // bltzal
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < 0) {
                            //! @bug: The return address should be stored in $ra even if the branch is not taken.
                            pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                            pCPU->nWaitPC = pCPU->nCallLast = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        }
                        break;
                    case 0x11: // bgezal
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= 0) {
                            //! @bug: The return address should be stored in $ra even if the branch is not taken.
                            pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                            pCPU->nWaitPC = pCPU->nCallLast = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        }
                        break;
                    case 0x12: // bltzall
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < 0) {
                            pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        } else {
                            pCPU->nMode |= 4;
                            pCPU->nPC = pCPU->nPC + 4;
                        }
                        break;
                    case 0x13: // bgezall
                        if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= 0) {
                            pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        } else {
                            pCPU->nMode |= 4;
                            pCPU->nPC = pCPU->nPC + 4;
                        }
                        break;
                }
                break;
            case 0x02: // j
                pCPU->nWaitPC = (pCPU->nPC & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
                if (pCPU->nWaitPC == pCPU->nPC - 4) {
                    if (!cpuCheckInterrupts(pCPU)) {
                        return 0;
                    }
                }
                break;
            case 0x03: // jal
                pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                pCPU->nWaitPC = pCPU->nCallLast = (pCPU->nPC & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
                cpuFindFunction(pCPU, pCPU->nWaitPC, &pFunction);
                break;
            case 0x04: // beq
                if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 == (s32)pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                    pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                }
                if (pCPU->nWaitPC == pCPU->nPC - 4) {
                    if (!cpuCheckInterrupts(pCPU)) {
                        return 0;
                    }
                    break;
                }
                break;
            case 0x05: // bne
                if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 != (s32)pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                    pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                }
                break;
            case 0x06: // blez
                if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 <= 0) {
                    pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                }
                break;
            case 0x07: // bgtz
                if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 > 0) {
                    pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                }
                break;
            case 0x08: // addi
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                break;
            case 0x09: // addiu
                pCPU->aGPR[MIPS_RT(nOpcode)].u32 = pCPU->aGPR[MIPS_RS(nOpcode)].u32 + MIPS_IMM_S16(nOpcode);
                break;
            case 0x0A: // slti
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < MIPS_IMM_S16(nOpcode)) ? 1 : 0;
                break;
            case 0x0B: // sltiu
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = (pCPU->aGPR[MIPS_RS(nOpcode)].u32 < MIPS_IMM_S16(nOpcode)) ? 1 : 0;
                break;
            case 0x0C: // andi
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aGPR[MIPS_RS(nOpcode)].s32 & MIPS_IMM_U16(nOpcode);
                break;
            case 0x0D: // ori
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aGPR[MIPS_RS(nOpcode)].s32 | MIPS_IMM_U16(nOpcode);
                break;
            case 0x0E: // xori
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aGPR[MIPS_RS(nOpcode)].s32 ^ MIPS_IMM_U16(nOpcode);
                break;
            case 0x0F: // lui
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = MIPS_IMM_S16(nOpcode) << 16;
                break;
            case 0x10: // cop0
                switch (MIPS_FUNCT(nOpcode)) {
                    case 0x01: // tlbr
                        iEntry = pCPU->anCP0[0] & 0x3F;
                        pCPU->anCP0[2] = pCPU->aTLB[iEntry][0];
                        pCPU->anCP0[3] = pCPU->aTLB[iEntry][1];
                        pCPU->anCP0[10] = pCPU->aTLB[iEntry][2];
                        pCPU->anCP0[5] = pCPU->aTLB[iEntry][3];
                        break;
                    case 0x02: // tlbwi
                        iEntry = pCPU->anCP0[0] & 0x3F;
                        cpuSetTLB(pCPU, iEntry);
                        break;
                    case 0x05: // tlbwr
                        iEntry = cpuCountTLB(pCPU, &nCount);
                        pCPU->anCP0[1] = iEntry;
                        cpuSetTLB(pCPU, iEntry);
                        break;
                    case 0x08: // tlbp
                        pCPU->anCP0[0] |= 0x80000000;
                        for (iEntry = 0; iEntry < 48; iEntry++) {
                            if ((pCPU->aTLB[iEntry][0] & 2) && pCPU->aTLB[iEntry][2] == pCPU->anCP0[10]) {
                                pCPU->anCP0[0] = iEntry;
                                break;
                            }
                        }
                        break;
                    case 0x18: // eret
                        if (pCPU->anCP0[12] & 4) {
                            pCPU->nPC = pCPU->anCP0[30];
                            pCPU->anCP0[12] &= ~4;
                        } else {
                            pCPU->nPC = pCPU->anCP0[14];
                            pCPU->anCP0[12] &= ~2;
                        }
                        pCPU->nMode |= 4;
                        pCPU->nMode |= 0x20;
                        break;
                    default:
                        switch (MIPS_RS(nOpcode)) {
                            case 0x00: // mfc0
                                if (cpuGetRegisterCP0(pCPU, MIPS_RD(nOpcode), &nData64)) {
                                    pCPU->aGPR[MIPS_RT(nOpcode)].s64 = nData64 & 0xFFFFFFFF;
                                }
                                break;
                            case 0x01: // dmfc0
                                if (cpuGetRegisterCP0(pCPU, MIPS_RD(nOpcode), &nData64)) {
                                    pCPU->aGPR[MIPS_RT(nOpcode)].s64 = nData64;
                                }
                                break;
                            case 0x02:
                                break;
                            case 0x04: // mtc0
                                cpuSetRegisterCP0(pCPU, MIPS_RD(nOpcode), pCPU->aGPR[MIPS_RT(nOpcode)].u32);
                                break;
                            case 0x05: // dmtc0
                                cpuSetRegisterCP0(pCPU, MIPS_RD(nOpcode), pCPU->aGPR[MIPS_RT(nOpcode)].u64);
                                break;
                            case 0x08:
                                break;
                        }
                        break;
                }
                break;
            case 0x11: // cop1
                if ((nOpcode & 0x7FF) == 0 && MIPS_FMT(nOpcode) < 0x10) {
                    switch ((u8)MIPS_FMT(nOpcode)) {
                        case 0x00: // mfc1
                            if (MIPS_FS(nOpcode) & 1) {
                                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode) - 1].u64 >> 32;
                            } else {
                                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                            }
                            break;
                        case 0x01: // dmfc1
                            pCPU->aGPR[MIPS_RT(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                            break;
                        case 0x02: // cfc1
                            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->anFCR[MIPS_FS(nOpcode)];
                            break;
                        case 0x04: // mtc1
                            if (MIPS_FS(nOpcode) & 1) {
                                pCPU->aFPR[MIPS_FS(nOpcode) - 1].s64 &= 0xFFFFFFFF;
                                pCPU->aFPR[MIPS_FS(nOpcode) - 1].s64 |= (u64)pCPU->aGPR[MIPS_RT(nOpcode)].u32 << 32;
                            } else {
                                pCPU->aFPR[MIPS_FS(nOpcode)].s32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                            }
                            break;
                        case 0x05: // dmtc1
                            pCPU->aFPR[MIPS_FS(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                            break;
                        case 0x06: // ctc1
                            pCPU->anFCR[MIPS_FS(nOpcode)] = pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                            break;
                    }
                } else if (MIPS_FMT(nOpcode) == 0x08) {
                    switch (MIPS_FT(nOpcode)) {
                        case 0x00: // bc1f
                            if (!(pCPU->anFCR[31] & 0x800000)) {
                                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                            }
                            break;
                        case 0x01: // bc1t
                            if (pCPU->anFCR[31] & 0x800000) {
                                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                            }
                            break;
                        case 0x02: // bc1fl
                            if (!(pCPU->anFCR[31] & 0x800000)) {
                                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                            } else {
                                pCPU->nMode |= 4;
                                pCPU->nPC += 4;
                            }
                            break;
                        case 0x03: // bc1tl
                            if (pCPU->anFCR[31] & 0x800000) {
                                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                            } else {
                                pCPU->nMode |= 4;
                                pCPU->nPC += 4;
                            }
                            break;
                    }
                } else {
                    switch ((u8)MIPS_FMT(nOpcode)) {
                        case 0x10: // s
                            switch (MIPS_FUNCT(nOpcode)) {
                                case 0x00: // add.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].f32 + pCPU->aFPR[MIPS_FT(nOpcode)].f32;
                                    break;
                                case 0x01: // sub.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].f32 - pCPU->aFPR[MIPS_FT(nOpcode)].f32;
                                    break;
                                case 0x02: // mul.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].f32 * pCPU->aFPR[MIPS_FT(nOpcode)].f32;
                                    break;
                                case 0x03: // div.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].f32 / pCPU->aFPR[MIPS_FT(nOpcode)].f32;
                                    break;
                                case 0x04: // sqrt.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 = sqrt(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                    break;
                                case 0x05: // abs.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 = fabs(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                    break;
                                case 0x06: // mov.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                    break;
                                case 0x07: // neg.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 = -pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                    break;
                                case 0x08: // round.l.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f32 + 0.5f;
                                    break;
                                case 0x09: // trunc.l.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                    break;
                                case 0x0A: // ceil.l.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                    break;
                                case 0x0B: // floor.l.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                    break;
                                case 0x0C: // round.w.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32 + 0.5f;
                                    break;
                                case 0x0D: // trunc.w.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                    break;
                                case 0x0E: // ceil.w.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                    break;
                                case 0x0F: // floor.w.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                    break;
                                case 0x20: // cvt.s.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                    break;
                                case 0x21: // cvt.d.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                    break;
                                case 0x24: // cvt.w.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                    break;
                                case 0x25: // cvt.l.s
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                    break;
                                case 0x30: // c.f.s
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x31: // c.un.s
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x32: // c.eq.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 == pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x33: // c.ueq.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 == pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x34: // c.olt.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 < pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x35: // c.ult.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 < pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x36: // c.ole.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x37: // c.ule.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x38: // c.sf.s
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x39: // c.ngle.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3A: // c.seq.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 == pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3B: // c.ngl.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 == pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3C: // c.lt.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 < pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3D: // c.nge.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 < pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3E: // c.le.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3F: // c.ngt.s
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                            }
                            break;
                        case 0x11: // d
                            switch (MIPS_FUNCT(nOpcode)) {
                                case 0x00: // add.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].f64 + pCPU->aFPR[MIPS_FT(nOpcode)].f64;
                                    break;
                                case 0x01: // sub.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].f64 - pCPU->aFPR[MIPS_FT(nOpcode)].f64;
                                    break;
                                case 0x02: // mul.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].f64 * pCPU->aFPR[MIPS_FT(nOpcode)].f64;
                                    break;
                                case 0x03: // div.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].f64 / pCPU->aFPR[MIPS_FT(nOpcode)].f64;
                                    break;
                                case 0x04: // sqrt.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 = sqrt(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                    break;
                                case 0x05: // abs.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 = fabs(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                    break;
                                case 0x06: // mov.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                    break;
                                case 0x07: // neg.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 = -pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                    break;
                                case 0x08: // round.l.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64 + 0.5f;
                                    break;
                                case 0x09: // trunc.l.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                    break;
                                case 0x0A: // ceil.l.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                    break;
                                case 0x0B: // floor.l.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                    break;
                                case 0x0C: // round.w.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f64 + 0.5f;
                                    break;
                                case 0x0D: // trunc.w.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                    break;
                                case 0x0E: // ceil.w.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                    break;
                                case 0x0F: // floor.w.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                    break;
                                case 0x20: // cvt.s.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                    break;
                                case 0x21: // cvt.d.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                    break;
                                case 0x24: // cvt.w.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                    break;
                                case 0x25: // cvt.l.d
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                    break;
                                case 0x30: // c.f.d
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x31: // c.un.d
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x32: // c.eq.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 == pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x33: // c.ueq.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 == pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x34: // c.olt.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 < pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x35: // c.ult.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 < pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x36: // c.ole.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x37: // c.ule.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x38: // c.sf.d
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x39: // c.ngle.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3A: // c.seq.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 == pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3B: // c.ngl.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 == pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3C: // c.lt.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 < pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3D: // c.nge.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 < pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3E: // c.le.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3F: // c.ngt.d
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                            }
                            break;
                        case 0x14: // w
                            switch (MIPS_FUNCT(nOpcode)) {
                                case 0x00: // add.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].s32 + pCPU->aFPR[MIPS_FT(nOpcode)].s32;
                                    break;
                                case 0x01: // sub.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].s32 - pCPU->aFPR[MIPS_FT(nOpcode)].s32;
                                    break;
                                case 0x02: // mul.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].s32 * pCPU->aFPR[MIPS_FT(nOpcode)].s32;
                                    break;
                                case 0x03: // div.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].s32 / pCPU->aFPR[MIPS_FT(nOpcode)].s32;
                                    break;
                                case 0x04: // sqrt.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = sqrt(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                    break;
                                case 0x05: // abs.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = fabs(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                    break;
                                case 0x06: // mov.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x07: // neg.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = -pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x08: // round.l.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x09: // trunc.l.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x0A: // ceil.l.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                    break;
                                case 0x0B: // floor.l.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                    break;
                                case 0x0C: // round.w.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x0D: // trunc.w.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x0E: // ceil.w.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                    break;
                                case 0x0F: // floor.w.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                    break;
                                case 0x20: // cvt.s.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x21: // cvt.d.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x24: // cvt.w.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x25: // cvt.l.w
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                    break;
                                case 0x30: // c.f.w
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x31: // c.un.w
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x32: // c.eq.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 == pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x33: // c.ueq.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 == pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x34: // c.olt.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 < pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x35: // c.ult.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 < pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x36: // c.ole.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x37: // c.ule.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x38: // c.sf.w
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x39: // c.ngle.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3A: // c.seq.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 == pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3B: // c.ngl.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 == pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3C: // c.lt.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 < pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3D: // c.nge.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 < pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3E: // c.le.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3F: // c.ngt.w
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                            }
                            break;
                        case 0x15: // l
                            switch (MIPS_FUNCT(nOpcode)) {
                                case 0x00: // add.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].s64 + pCPU->aFPR[MIPS_FT(nOpcode)].s64;
                                    break;
                                case 0x01: // sub.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].s64 - pCPU->aFPR[MIPS_FT(nOpcode)].s64;
                                    break;
                                case 0x02: // mul.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].s64 * pCPU->aFPR[MIPS_FT(nOpcode)].s64;
                                    break;
                                case 0x03: // div.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 =
                                        pCPU->aFPR[MIPS_FS(nOpcode)].s64 / pCPU->aFPR[MIPS_FT(nOpcode)].s64;
                                    break;
                                case 0x04: // sqrt.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = sqrt(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                    break;
                                case 0x05: // abs.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = fabs(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                    break;
                                case 0x06: // mov.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x07: // neg.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = -pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x08: // round.l.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x09: // trunc.l.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x0A: // ceil.l.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                    break;
                                case 0x0B: // floor.l.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                    break;
                                case 0x0C: // round.w.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x0D: // trunc.w.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x0E: // ceil.w.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                    break;
                                case 0x0F: // floor.w.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                    break;
                                case 0x20: // cvt.s.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x21: // cvt.d.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x24: // cvt.w.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x25: // cvt.l.l
                                    pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                    break;
                                case 0x30: // c.f.l
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x31: // c.un.l
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x32: // c.eq.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 == pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x33: // c.ueq.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 == pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x34: // c.olt.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 < pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x35: // c.ult.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 < pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x36: // c.ole.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x37: // c.ule.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x38: // c.sf.l
                                    pCPU->anFCR[31] &= ~0x800000;
                                    break;
                                case 0x39: // c.ngle.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3A: // c.seq.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 == pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3B: // c.ngl.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 == pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3C: // c.lt.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 < pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3D: // c.nge.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 < pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3E: // c.le.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                                case 0x3F: // c.ngt.l
                                    if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                        pCPU->anFCR[31] |= 0x800000;
                                    } else {
                                        pCPU->anFCR[31] &= ~0x800000;
                                    }
                                    break;
                            }
                            break;
                    }
                }
                break;
            case 0x14: // beq
                if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 == (s32)pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                    pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                } else {
                    pCPU->nMode |= 4;
                    pCPU->nPC += 4;
                }
                break;
            case 0x15: // bne
                if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 != (s32)pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                    pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                } else {
                    pCPU->nMode |= 4;
                    pCPU->nPC += 4;
                }
                break;
            case 0x16: // blez
                if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 <= 0) {
                    pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                } else {
                    pCPU->nMode |= 4;
                    pCPU->nPC += 4;
                }
                break;
            case 0x17: // bgtz
                if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 > 0) {
                    pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                } else {
                    pCPU->nMode |= 4;
                    pCPU->nPC += 4;
                }
                break;
            case 0x18: // daddi
                pCPU->aGPR[MIPS_RT(nOpcode)].s64 = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
                break;
            case 0x19: // daddiu
                pCPU->aGPR[MIPS_RT(nOpcode)].u64 = pCPU->aGPR[MIPS_RS(nOpcode)].u64 + MIPS_IMM_S16(nOpcode);
                break;
            case 0x1F: // library call
                if (!libraryCall(SYSTEM_LIBRARY(pCPU->pHost), pCPU, MIPS_IMM_S16(nOpcode))) {
                    return false;
                }
                break;
            case 0x1A: // ldl
                nCount = 0x38;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
                do {
                    if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                        nData64 = ((s64)nData8 & 0xFF) << nCount;
                        pCPU->aGPR[MIPS_RT(nOpcode)].s64 =
                            nData64 | (pCPU->aGPR[MIPS_RT(nOpcode)].s64 & ~((s64)0xFF << nCount));
                    }
                    nCount -= 8;
                } while ((nAddress++ & 7) != 0);
                break;
            case 0x1B: // ldr
                nCount = 0;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
                do {
                    if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                        nData64 = ((s64)nData8 & 0xFF) << nCount;
                        pCPU->aGPR[MIPS_RT(nOpcode)].s64 =
                            nData64 | (pCPU->aGPR[MIPS_RT(nOpcode)].s64 & ~((s64)0xFF << nCount));
                    }
                    nCount += 8;
                } while ((nAddress-- & 7) != 0);
                break;
            case 0x27: // lwu
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nData32)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].u64 = (u32)nData32;
                }
                break;
            case 0x20: // lb
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData8;
                }
                break;
            case 0x21: // lh
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET16(apDevice, aiDevice, nAddress, &nData16)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData16;
                }
                break;
            case 0x22: // lwl
                nCount = 0x18;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                do {
                    if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                        nData32 = ((u32)nData8 & 0xFF) << nCount;
                        pCPU->aGPR[MIPS_RT(nOpcode)].s32 =
                            nData32 | (pCPU->aGPR[MIPS_RT(nOpcode)].s32 & ~(0xFF << nCount));
                    }
                    nCount -= 8;
                } while ((nAddress++ & 3) != 0);
                break;
            case 0x23: // lw
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nData32)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData32;
                }
                break;
            case 0x24: // lbu
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].u32 = (u8)nData8;
                }
                break;
            case 0x25: // lhu
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (frameGetDepth(SYSTEM_FRAME(pCPU->pHost), (u16*)&nData16, nAddress)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].u32 = (u16)nData16;
                } else {
                    if (CPU_DEVICE_GET16(apDevice, aiDevice, nAddress, &nData16)) {
                        pCPU->aGPR[MIPS_RT(nOpcode)].u32 = (u16)nData16;
                    }
                }
                break;
            case 0x26: // lwr
                nCount = 0;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                do {
                    if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                        nData32 = ((u32)nData8 & 0xFF) << nCount;
                        pCPU->aGPR[MIPS_RT(nOpcode)].s32 =
                            nData32 | (pCPU->aGPR[MIPS_RT(nOpcode)].s32 & ~(0xFF << nCount));
                    }
                    nCount += 8;
                } while ((nAddress-- & 3) != 0);
                break;
            case 0x28: // sb
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &pCPU->aGPR[MIPS_RT(nOpcode)].s8);
                break;
            case 0x29: // sh
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                CPU_DEVICE_PUT16(apDevice, aiDevice, nAddress, &pCPU->aGPR[MIPS_RT(nOpcode)].s16);
                break;
            case 0x2A: // swl
                nCount = 0x18;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                do {
                    nData8 = (pCPU->aGPR[MIPS_RT(nOpcode)].u32 >> nCount) & 0xFF;
                    CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &nData8);
                    nCount -= 8;
                } while ((nAddress++ & 3) != 0);
                break;
            case 0x2B: // sw
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                CPU_DEVICE_PUT32(apDevice, aiDevice, nAddress, &pCPU->aGPR[MIPS_RT(nOpcode)].s32);
                break;
            case 0x2C: // sdl
                nCount = 0x38;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
                do {
                    nData8 = (pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> nCount) & 0xFF;
                    CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &nData8);
                    nCount -= 8;
                } while ((nAddress++ & 7) != 0);
                break;
            case 0x2D: // sdr
                nCount = 0;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                do {
                    nData8 = (pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> nCount) & 0xFF;
                    CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &nData8);
                    nCount += 8;
                } while ((nAddress-- & 7) != 0);
                break;
            case 0x2E: // swr
                nCount = 0;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                do {
                    nData8 = (pCPU->aGPR[MIPS_RT(nOpcode)].u32 >> nCount) & 0xFF;
                    CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &nData8);
                    nCount += 8;
                } while ((nAddress-- & 3) != 0);
                break;
            case 0x2F: // cache
                if (!cpuExecuteCacheInstruction(pCPU)) {
                    return false;
                }
                break;
            case 0x30: // ll
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nData32)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData32;
                }
                break;
            case 0x31: // lwc1
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nData32)) {
                    if (MIPS_RT(nOpcode) & 1) {
                        pCPU->aFPR[MIPS_RT(nOpcode) - 1].u64 &= 0xFFFFFFFF;
                        pCPU->aFPR[MIPS_RT(nOpcode) - 1].u64 |= (s64)nData32 << 32;
                    } else {
                        pCPU->aFPR[MIPS_RT(nOpcode)].s32 = nData32;
                    }
                }
                break;
            case 0x34: // lld
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET64(apDevice, aiDevice, nAddress, &nData64)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].s64 = nData64;
                }
                break;
            case 0x35: // ldc1
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET64(apDevice, aiDevice, nAddress, &nData64)) {
                    pCPU->aFPR[MIPS_RT(nOpcode)].s64 = nData64;
                }
                break;
            case 0x37: // ld
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (CPU_DEVICE_GET64(apDevice, aiDevice, nAddress, &nData64)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].s64 = nData64;
                }
                break;
            case 0x38: // sc
                nData32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = (CPU_DEVICE_PUT32(apDevice, aiDevice, nAddress, &nData32)) ? 1 : 0;
                break;
            case 0x39: // swc1
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                if (MIPS_RT(nOpcode) & 1) {
                    nData32 = pCPU->aFPR[MIPS_RT(nOpcode) - 1].u64 >> 32;
                } else {
                    nData32 = pCPU->aFPR[MIPS_RT(nOpcode)].s32;
                }
                CPU_DEVICE_PUT32(apDevice, aiDevice, nAddress, &nData32);
                break;
            case 0x3C: // scd
                nData64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
                pCPU->aGPR[MIPS_RT(nOpcode)].s64 = (CPU_DEVICE_PUT64(apDevice, aiDevice, nAddress, &nData64)) ? 1 : 0;
                break;
            case 0x3D: // sdc1
                nData64 = pCPU->aFPR[MIPS_RT(nOpcode)].s64;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                CPU_DEVICE_PUT64(apDevice, aiDevice, nAddress, &nData64);
                break;
            case 0x3F: // sd
                nData64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
                CPU_DEVICE_PUT64(apDevice, aiDevice, nAddress, &nData64);
                break;
        }
    }

    if (!cpuExecuteUpdate(pCPU, &nAddressGCN, nTick + 1)) {
        return 0;
    }
    if (restore) {
        pCPU->aGPR[31].u64 = save;
    }
    pCPU->nWaitPC = -1;
    pCPU->nTickLast = OSGetTick();

    PAD_STACK();
    PAD_STACK();
    return nAddressGCN;
}

static s32 cpuExecuteIdle(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    Rom* pROM;

    pROM = SYSTEM_ROM(pCPU->pHost);

#if VERSION != MQ_J
    if (!simulatorTestReset(false, false, false, true)) {
        return 0;
    }
#endif

    nCount = OSGetTick();
    if (pCPU->nWaitPC != 0) {
        pCPU->nMode |= 8;
    } else {
        pCPU->nMode &= ~8;
    }

    pCPU->nMode |= 0x80;
    pCPU->nPC = nAddressN64;
    if (!(pCPU->nMode & 0x40) && pROM->copy.nSize == 0) {
        videoForceRetrace(SYSTEM_VIDEO(pCPU->pHost), false);
    }

    if (!cpuExecuteUpdate(pCPU, &nAddressGCN, nCount)) {
        return 0;
    }

    pCPU->nTickLast = OSGetTick();
    return nAddressGCN;
}

static s32 cpuExecuteJump(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    nCount = OSGetTick();

    if (pCPU->nWaitPC != 0) {
        pCPU->nMode |= 8;
    } else {
        pCPU->nMode &= ~8;
    }

    pCPU->nMode |= 4;
    pCPU->nPC = nAddressN64;

    if (gpSystem->eTypeROM == SRT_ZELDA1 && pCPU->nPC == 0x81000000) {
        simulatorPlayMovie();
    }

    if (!cpuExecuteUpdate(pCPU, &nAddressGCN, nCount)) {
        return 0;
    }

    pCPU->nTickLast = OSGetTick();
    return nAddressGCN;
}

/**
 * @brief Executes a call from the dynamic recompiler environment
 *
 * @param pCPU The emulated VR4300.
 * @param nCount Latest tick count
 * @param nAddressN64 The N64 address of the call.
 * @param nAddressGCN The GameCube address after the call has completed.
 * @return s32 The address of the recompiled called function.
 */
static s32 cpuExecuteCall(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    s32 pad;
    s32 nReg;
    s32 count;
    s32* anCode;
    s32 saveGCN;
    CpuFunction* node;
    CpuCallerID* block;
    s32 nDeltaAddress;

    nCount = OSGetTick();
    if (pCPU->nWaitPC != 0) {
        pCPU->nMode |= 8;
    } else {
        pCPU->nMode &= ~8;
    }

    pCPU->nMode |= 4;
    pCPU->nPC = nAddressN64;

    pCPU->aGPR[31].s32 = nAddressGCN;
    saveGCN = nAddressGCN - 4;

    pCPU->survivalTimer++;

    cpuFindFunction(pCPU, pCPU->nReturnAddrLast - 8, &node);

    block = node->block;
    for (count = 0; count < node->callerID_total; count++) {
        if (block[count].N64address == nAddressN64 && block[count].GCNaddress == 0) {
            block[count].GCNaddress = saveGCN;
            break;
        }
    }

    saveGCN = (ganMapGPR[31] & 0x100) ? true : false;
    anCode = (s32*)nAddressGCN - (saveGCN ? 4 : 3);
    if (saveGCN) {
        anCode[0] = 0x3CA00000 | ((u32)nAddressGCN >> 16); // lis r5,nAddressGCN@h
        anCode[1] = 0x60A50000 | ((u32)nAddressGCN & 0xFFFF); // ori r5,r5,nAddressGCN@l
        DCStoreRange(anCode, 8);
        ICInvalidateRange(anCode, 8);
    } else {
        nReg = ganMapGPR[31];
        anCode[0] = 0x3C000000 | ((u32)nAddressGCN >> 16) | (nReg << 21); // lis ri,nAddressGCN@h
        anCode[1] = 0x60000000 | ((u32)nAddressGCN & 0xFFFF) | (nReg << 21) | (nReg << 16); // ori ri,ri,nAddressGCN@l
        DCStoreRange(anCode, 8);
        ICInvalidateRange(anCode, 8);
    }

    //! @bug: If cpuExecuteUpdate decides to delete the function we're trying to
    //! call here, our lis/ori will be reverted by treeCallerCheck since we've
    //! already marked this call site in the callerID for-loop above. The
    //! reverted lis/ori will store the return N64 address instead of a GCN
    //! address, so the next time this recompiled call is executed, the CPU will
    //! jump to that N64 return address in GCN address space and bad things
    //! happen (usually an invalid instruction or invalid load/store). This is
    //! known as a "VC crash".
    //!
    //! For more details, see https://pastebin.com/V6ANmXt8
    if (!cpuExecuteUpdate(pCPU, &nAddressGCN, nCount)) {
        return 0;
    }

    nDeltaAddress = (u8*)nAddressGCN - (u8*)&anCode[3];
    if (saveGCN) {
        anCode[3] = 0x48000000 | (nDeltaAddress & 0x03FFFFFC); // b nDeltaAddress
        DCStoreRange(anCode, 16);
        ICInvalidateRange(anCode, 16);
    } else {
        anCode[2] = 0x48000000 | (nDeltaAddress & 0x03FFFFFC); // b nDeltaAddress
        DCStoreRange(anCode, 12);
        ICInvalidateRange(anCode, 12);
    }

    pCPU->nTickLast = OSGetTick();

    return nAddressGCN;
}

/**
 * @brief Recompiles a VR4300 load/store instruction
 *
 * @param pCPU The emulated VR4300.
 * @param nCount Unused.
 * @param nAddressN64 The address of the Load/Store instruction.
 * @param nAddressGCN A pointer to the location where recompiled code should be stored.
 * @return s32 The address of the recompiled called function.
 */
static s32 cpuExecuteLoadStore(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    u32* opcode;
    s32 address;
    s32 iRegisterA;
    s32 iRegisterB;
    u8 device;
    s32 total;
    s32 count;
    s32 save;
    s32 interpret;
    s32* before;
    s32* after;
    s32 check2;
    s32* anCode;
    s32 pad;

    count = 0;
    save = 0;
    interpret = 0;
    check2 = 0x90C30000 + OFFSETOF(pCPU, nWaitPC);

    ramGetBuffer(SYSTEM_RAM(pCPU->pHost), (void**)&opcode, nAddressN64, NULL);

    address = pCPU->aGPR[MIPS_RS(*opcode)].s32 + MIPS_IMM_S16(*opcode);
    device = pCPU->aiDevice[(u32)(address) >> 16];

    if (pCPU->nCompileFlag & 0x100) {
        anCode = (s32*)nAddressGCN - 3;
        before = anCode - 2;
        after = (s32*)nAddressGCN + 3;
    } else {
        anCode = (s32*)nAddressGCN - 3;
        before = anCode - 2;
        after = (s32*)nAddressGCN + 2;
    }

    if (((u32)address >> 28) < 0x08) {
        interpret = 1;
    }

    if (!interpret && device >= 0x80) {
        switch (MIPS_OP(*opcode)) {
            case 0x20: // lb
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x88070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x7C000774 | (iRegisterA << 21) | (iRegisterA << 16);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x24: // lbu
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x88070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x21: // lh
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0xA0070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x7C000734 | (iRegisterA << 21) | (iRegisterA << 16);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x25: // lhu
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0xA0070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x23: // lw
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x80070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x28: // sb
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 7;
                    anCode[count++] = 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }
                anCode[count++] = 0x7CE04214 | (iRegisterB << 16);
                anCode[count++] = 0x98070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                break;
            case 0x29: // sh
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 7;
                    anCode[count++] = 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }
                anCode[count++] = 0x7CE04214 | (iRegisterB << 16);
                anCode[count++] = 0xB0070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                break;
            case 0x2B: // sw
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 7;
                    anCode[count++] = 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }
                anCode[count++] = 0x7CE04214 | (iRegisterB << 16);
                anCode[count++] = 0x90070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                break;
            default:
                OSPanic("_cpuGCN.c", LN(4721), "");
                break;
        }
    } else {
        interpret = 1;
        anCode[count++] = 0x3CA00000 | ((u32)nAddressN64 >> 16);
        anCode[count++] = 0x60A50000 | ((u32)nAddressN64 & 0xFFFF);
        anCode[count++] = 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[count]) & 0x03FFFFFC) | 1;
    }

    if (pCPU->nCompileFlag & 0x100) {
        if (6 - count >= 2) {
            save = count;
            anCode[count++] = 0x48000000 | (((u32)&anCode[6] - (u32)&anCode[count]) & 0xFFFF);
        }
        while (count <= 5) {
            anCode[count++] = 0x60000000;
        }
        total = 6;
    } else {
        if (5 - count >= 2) {
            save = count;
            anCode[count++] = 0x48000000 | (((u32)&anCode[5] - (u32)&anCode[count]) & 0xFFFF);
        }
        while (count <= 4) {
            anCode[count++] = 0x60000000;
        }
        total = 5;
    }

    if (!interpret && before[0] == 0x38C00000 && before[1] == check2) {
        before[0] = 0x48000000 | (((u32)&before[2] - (u32)&before[0]) & 0xFFFF);
        before[1] = 0x60000000;
        DCStoreRange(before, 8);
        ICInvalidateRange(before, 8);

        if (save != 0) {
            anCode[save] = 0x48000000 | (((u32)&after[2] - (u32)&anCode[save]) & 0xFFFF);
        }
        after[0] = 0x60000000;
        after[1] = 0x60000000;

        total += 2;
        pCPU->nWaitPC = -1;
    }

    DCStoreRange(anCode, total * 4);
    ICInvalidateRange(anCode, total * 4);
    return (s32)anCode;
}

/**
 * @brief Recompiles a VR4300 load/store instruction on COP1 or doubleword load/store.
 *
 * @param pCPU The emulated VR4300.
 * @param nCount Unused.
 * @param nAddressN64 The address of the Load/Store instruction.
 * @param nAddressGCN A pointer to the location where recompiled code should be stored.
 * @return s32 The address of the recompiled called function.
 */
static s32 cpuExecuteLoadStoreF(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    u32* opcode;
    s32 address;
    s32 iRegisterA;
    s32 iRegisterB;
    u8 device;
    s32 total;
    s32 count;
    s32 save;
    s32 interpret;
    s32* before;
    s32* after;
    s32 check2;
    s32* anCode;
    s32 rt;
    s32 pad;

    count = 0;
    save = 0;
    interpret = 0;
    check2 = 0x90C30000 + OFFSETOF(pCPU, nWaitPC);

    ramGetBuffer(SYSTEM_RAM(pCPU->pHost), (void**)&opcode, nAddressN64, NULL);

    address = pCPU->aGPR[MIPS_RS(*opcode)].s32 + MIPS_IMM_S16(*opcode);
    device = pCPU->aiDevice[(u32)(address) >> 16];

    if (pCPU->nCompileFlag & 0x100) {
        anCode = (s32*)nAddressGCN - 3;
        before = anCode - 2;
        after = (s32*)nAddressGCN + 4;
    } else {
        anCode = (s32*)nAddressGCN - 3;
        before = anCode - 2;
        after = (s32*)nAddressGCN + 3;
    }

    if (((u32)address >> 28) < 0x08) {
        interpret = 1;
    }

    if (!interpret && device >= 0x80) {
        rt = MIPS_RT(*opcode);
        switch (MIPS_OP(*opcode)) {
            case 0x31: // lwc1
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if ((pCPU->nCompileFlag & 0x100) && ((u32)address >> 28) >= 10) {
                    anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);

                if (rt % 2 == 1) {
                    anCode[count++] = 0x80A70000 | MIPS_IMM_U16(*opcode);
                    anCode[count++] = 0x90A30000 + OFFSETOF(pCPU, aFPR[rt - 1]);
                } else {
                    anCode[count++] = 0x80A70000 | MIPS_IMM_U16(*opcode);
                    anCode[count++] = 0x90A30000 + (OFFSETOF(pCPU, aFPR[rt]) + 4);
                }
                break;
            case 0x39: // swc1
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if ((pCPU->nCompileFlag & 0x100) && ((u32)address >> 28) >= 10) {
                    anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                if (rt % 2 == 1) {
                    anCode[count++] = 0x80A30000 + OFFSETOF(pCPU, aFPR[rt - 1]);
                } else {
                    anCode[count++] = 0x80A30000 + (OFFSETOF(pCPU, aFPR[rt]) + 4);
                }
                anCode[count++] = 0x90A70000 | MIPS_IMM_U16(*opcode);
                break;
            case 0x35: // ldc1
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if ((pCPU->nCompileFlag & 0x100) && ((u32)address >> 28) >= 10) {
                    anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x80A70000 | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x90A30000 + OFFSETOF(pCPU, aFPR[rt]);
                anCode[count++] = 0x80A70000 | (MIPS_IMM_U16(*opcode) + 4);
                anCode[count++] = 0x90A30000 + (OFFSETOF(pCPU, aFPR[rt]) + 4);
                break;
            case 0x3D: // sdc1
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if ((pCPU->nCompileFlag & 0x100) && ((u32)address >> 28) >= 10) {
                    anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x80A30000 + OFFSETOF(pCPU, aFPR[rt]);
                anCode[count++] = 0x90A70000 | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x80A30000 + (OFFSETOF(pCPU, aFPR[rt]) + 4);
                anCode[count++] = 0x90A70000 | (MIPS_IMM_U16(*opcode) + 4);
                break;
            case 0x37: // ld
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x80A70000 | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]);
                anCode[count++] = 0x80070000 | (iRegisterA << 21) | (MIPS_IMM_U16(*opcode) + 4);
                anCode[count++] = (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4);
                break;
            case 0x3F: // sd
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 7;
                    anCode[count++] = 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]);
                anCode[count++] = 0x90C70000 | MIPS_IMM_U16(*opcode);

                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 6;
                    anCode[count++] = 0x80C30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4);
                }
                anCode[count++] = 0x90070000 | (iRegisterA << 21) | (MIPS_IMM_U16(*opcode) + 4);
                break;
            default:
                OSPanic("_cpuGCN.c", LN(5177), "");
                break;
        }
    } else {
        interpret = 1;
        anCode[count++] = 0x3CA00000 | ((u32)nAddressN64 >> 16);
        anCode[count++] = 0x60A50000 | ((u32)nAddressN64 & 0xFFFF);
        anCode[count++] = 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[count]) & 0x03FFFFFC) | 1;
    }

    if (pCPU->nCompileFlag & 0x100) {
        if (7 - count >= 2) {
            save = count;
            anCode[count++] = 0x48000000 | (((u32)&anCode[7] - (u32)&anCode[count]) & 0xFFFF);
        }
        while (count <= 6) {
            anCode[count++] = 0x60000000;
        }
        total = 7;
    } else {
        if (6 - count >= 2) {
            save = count;
            anCode[count++] = 0x48000000 | (((u32)&anCode[6] - (u32)&anCode[count]) & 0xFFFF);
        }
        while (count <= 5) {
            anCode[count++] = 0x60000000;
        }
        total = 6;
    }

    if (!interpret && before[0] == 0x38C00000 && before[1] == check2) {
        before[0] = 0x48000000 | (((u32)&before[2] - (u32)&before[0]) & 0xFFFF);
        before[1] = 0x60000000;
        DCStoreRange(before, 8);
        ICInvalidateRange(before, 8);

        if (save != 0) {
            anCode[save] = 0x48000000 | (((u32)&after[2] - (u32)&anCode[save]) & 0xFFFF);
        }
        after[0] = 0x60000000;
        after[1] = 0x60000000;

        total += 2;
        pCPU->nWaitPC = -1;
    }

    DCStoreRange(anCode, total * 4);
    ICInvalidateRange(anCode, total * 4);
    return (s32)anCode;
}

/**
 * @brief Generates a call to a virtual-console function from within the dynarec envrionment
 * Dedicated PPC registers are saved to the cpu object, and restored once the virtual-console function has finished.
 * Jump to the return value of the virtual-console function
 *
 * @param pCPU The emulated VR4300.
 * @param ppfLink A pointer to store the generated PPC code.
 * @param pfFunction The virtual-console function to call.
 * @return bool true on success, false otherwise.
 */
static bool cpuMakeLink(Cpu* pCPU, CpuExecuteFunc* ppfLink, CpuExecuteFunc pfFunction) {
    s32 iGPR;
    s32* pnCode;
    s32 nData;
    s32 pad;

    if (!xlHeapTake((void**)&pnCode, 0x200 | 0x30000000)) {
        return false;
    }
    *ppfLink = (CpuExecuteFunc)pnCode;

    *pnCode++ = 0x7CC802A6;

    for (iGPR = 1; iGPR < 32; iGPR++) {
        if (!(ganMapGPR[iGPR] & 0x100)) {
            nData = (OFFSETOF(pCPU, aGPR[iGPR]) + 4);
            *pnCode++ = 0x90030000 | (ganMapGPR[iGPR] << 21) | nData; // lwz ri,(aGPR[i] + 4)(r3)
        }
    }

    *pnCode++ = 0x48000000 | (((u8*)pfFunction - (u8*)pnCode) & 0x03FFFFFC) | 1; // bl pfFunction
    *pnCode++ = 0x7C6803A6; // mtlr r3
    *pnCode++ = 0x3C600000 | ((u32)pCPU >> 16); // lis r3,pCPU@h
    *pnCode++ = 0x60630000 | ((u32)pCPU & 0xFFFF); // ori r3,r3,pCPU@l
    *pnCode++ = 0x80830000 + OFFSETOF(pCPU, survivalTimer); // lwz r4,survivalTimer(r3)

    nData = (u32)(SYSTEM_RAM(pCPU->pHost)->pBuffer) - 0x80000000;
    *pnCode++ = 0x3D000000 | ((u32)nData >> 16); // lis r8,ramOffset@h
    if (pCPU->nCompileFlag & 0x100) {
        *pnCode++ = 0x3D20DFFF; // lis r9,0xDFFF
        *pnCode++ = 0x61080000 | ((u32)nData & 0xFFFF); // ori r8,r8,ramOffset@l
        *pnCode++ = 0x6129FFFF; // ori r9,r9,0xFFFF
    } else if (pCPU->nCompileFlag & 1) {
        *pnCode++ = 0x39230000 + OFFSETOF(pCPU, aiDevice); // addi r9,r3,aiDevice
        *pnCode++ = 0x61080000 | ((u32)nData & 0xFFFF); // ori r8,r8,ramOffset@l
    }

    *pnCode++ = 0x38000000 | (ganMapGPR[0] << 21); // li r0,0
    for (iGPR = 1; iGPR < 32; iGPR++) {
        if (!(ganMapGPR[iGPR] & 0x100)) {
            nData = (OFFSETOF(pCPU, aGPR[iGPR]) + 4);
            *pnCode++ = 0x80030000 | (ganMapGPR[iGPR] << 21) | nData; // stw ri,(aGPR[i] + 4)(r3)
        }
    }

    *pnCode++ = 0x4E800020; // blr

    DCStoreRange(*ppfLink, 0x200);
    ICInvalidateRange(*ppfLink, 0x200);
    return true;
}

static inline bool cpuFreeLink(Cpu* pCPU, CpuExecuteFunc* ppfLink) {
    if (!xlHeapFree((void**)&ppfLink)) {
        return false;
    } else {
        *ppfLink = NULL;
        return true;
    }
}

/**
 * @brief Begins execution of the emulated VR4300
 *
 * @param pCPU The emulated VR4300.
 * @param nCount Unused.
 * @param nAddressBreak Unused.
 * @return bool true on success, false otherwise.
 */
bool cpuExecute(Cpu* pCPU, s32 nCount, u64 nAddressBreak) {
    s32 pad1;
    s32 iGPR;
    s32* pnCode;
    s32 nData;
    s32 pad2;
    CpuFunction* pFunction;
    void (*pfCode)(void);

    if (pCPU->nCompileFlag & 0x1000) {
        pCPU->nCompileFlag |= 0x100;
    }

    if (!cpuMakeLink(pCPU, &pCPU->pfStep, &cpuExecuteOpcode)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfJump, &cpuExecuteJump)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfCall, &cpuExecuteCall)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfIdle, &cpuExecuteIdle)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfRam, &cpuExecuteLoadStore)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfRamF, &cpuExecuteLoadStoreF)) {
        return false;
    }

    cpuCompile_DSLLV(pCPU, &cpuCompile_DSLLV_function);
    cpuCompile_DSRLV(pCPU, &cpuCompile_DSRLV_function);
    cpuCompile_DSRAV(pCPU, &cpuCompile_DSRAV_function);
    cpuCompile_DMULT(pCPU, &cpuCompile_DMULT_function);
    cpuCompile_DMULTU(pCPU, &cpuCompile_DMULTU_function);
    cpuCompile_DDIV(pCPU, &cpuCompile_DDIV_function);
    cpuCompile_DDIVU(pCPU, &cpuCompile_DDIVU_function);
    cpuCompile_DADD(pCPU, &cpuCompile_DADD_function);
    cpuCompile_DADDU(pCPU, &cpuCompile_DADDU_function);
    cpuCompile_DSUB(pCPU, &cpuCompile_DSUB_function);
    cpuCompile_DSUBU(pCPU, &cpuCompile_DSUBU_function);
    cpuCompile_S_SQRT(pCPU, &cpuCompile_S_SQRT_function);
    cpuCompile_D_SQRT(pCPU, &cpuCompile_D_SQRT_function);
    cpuCompile_W_CVT_SD(pCPU, &cpuCompile_W_CVT_SD_function);
    cpuCompile_L_CVT_SD(pCPU, &cpuCompile_L_CVT_SD_function);
    cpuCompile_CEIL_W(pCPU, &cpuCompile_CEIL_W_function);
    cpuCompile_FLOOR_W(pCPU, &cpuCompile_FLOOR_W_function);
    cpuCompile_ROUND_W(&cpuCompile_ROUND_W_function);
    cpuCompile_TRUNC_W(&cpuCompile_TRUNC_W_function);
    cpuCompile_LB(pCPU, &cpuCompile_LB_function);
    cpuCompile_LH(pCPU, &cpuCompile_LH_function);
    cpuCompile_LW(pCPU, &cpuCompile_LW_function);
    cpuCompile_LBU(pCPU, &cpuCompile_LBU_function);
    cpuCompile_LHU(pCPU, &cpuCompile_LHU_function);
    cpuCompile_SB(pCPU, &cpuCompile_SB_function);
    cpuCompile_SH(pCPU, &cpuCompile_SH_function);
    cpuCompile_SW(pCPU, &cpuCompile_SW_function);
    cpuCompile_LDC(pCPU, &cpuCompile_LDC_function);
    cpuCompile_SDC(pCPU, &cpuCompile_SDC_function);
    cpuCompile_LWL(pCPU, &cpuCompile_LWL_function);
    cpuCompile_LWR(pCPU, &cpuCompile_LWR_function);

    if (cpuMakeFunction(pCPU, &pFunction, pCPU->nPC)) {
        if (!xlHeapTake((void**)&pnCode, 0x100 | 0x30000000)) {
            return false;
        }

        pfCode = (void (*)(void))pnCode;

        *pnCode++ = 0x3C600000 | ((u32)pCPU >> 0x10); // lis r3,pCPU@h
        *pnCode++ = 0x60630000 | ((u32)pCPU & 0xFFFF); // ori r3,r3,pCPU@l

        *pnCode++ = 0x80830000 + OFFSETOF(pCPU, survivalTimer); // lwz r4,survivalTimer(r3)

        nData = (u32)(SYSTEM_RAM(pCPU->pHost)->pBuffer) - 0x80000000;
        *pnCode++ = 0x3D000000 | ((u32)nData >> 16); // lis r8,ramOffset@h
        *pnCode++ = 0x61080000 | ((u32)nData & 0xFFFF); // ori r8,r8,ramOffset@l

        if (pCPU->nCompileFlag & 0x100) {
            *pnCode++ = 0x3D20DFFF; // lis r9,0xDFFF
            *pnCode++ = 0x6129FFFF; // ori r9,r9,0xFFFF
        } else if (pCPU->nCompileFlag & 1) {
            *pnCode++ = 0x39230000 + OFFSETOF(pCPU, aiDevice); // addi r9,r3,aiDevice
        }

        for (iGPR = 0; iGPR < ARRAY_COUNT(ganMapGPR); iGPR++) {
            if (!(ganMapGPR[iGPR] & 0x100)) {
                nData = (OFFSETOF(pCPU, aGPR[iGPR]) + 4);
                *pnCode++ = 0x80030000 | (ganMapGPR[iGPR] << 21) | nData; // lwz ri,(aGPR[i] + 4)(r3)
            }
        }

        *pnCode++ = 0x48000000 | (((u32)pFunction->pfCode - (u32)pnCode) & 0x03FFFFFC); // b pFunction->pfCode

        DCStoreRange(pfCode, 0x100);
        ICInvalidateRange(pfCode, 0x100);

        pCPU->nRetrace = pCPU->nRetraceUsed = 0;

        VIWaitForRetrace();
        VISetPostRetraceCallback(&cpuRetraceCallback);

        pfCode();

        if (!xlHeapFree((void**)&pfCode)) {
            return false;
        }

        if (!cpuFreeLink(pCPU, &pCPU->pfIdle)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfCall)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfJump)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfStep)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfRam)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfRamF)) {
            return false;
        }

        if (!xlHeapFree((void**)&cpuCompile_DSLLV_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DSRLV_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DSRAV_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DMULT_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DMULTU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DDIV_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DDIVU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DADD_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DADDU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DSUB_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DSUBU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_S_SQRT_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_D_SQRT_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_W_CVT_SD_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_L_CVT_SD_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_CEIL_W_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_FLOOR_W_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_TRUNC_W_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_ROUND_W_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LB_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LH_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LW_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LBU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LHU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_SB_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_SH_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_SW_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LDC_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_SDC_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LWL_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LWR_function)) {
            return false;
        }
    }

    return true;
}
