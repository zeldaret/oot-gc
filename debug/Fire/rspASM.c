int rspDisassemble(__anon_0x5845E *pRSP, __anon_0x575BD *pTask)
{
	tXL_FILE *pIMEMFile;
	int i;
	int h;
	int nCodeAddress;
	int nDataAddress;
	int nFound;
	unsigned int nOutData;
	void *pCode;
	void *pData;
	unsigned int nRS;
	unsigned int nRT;
	unsigned int nRD;
	unsigned int nSA;
	unsigned int nOffset;
	unsigned int nTarget;
	unsigned int nE;
	unsigned int nVT;
	unsigned int nVS;
	unsigned int nVD;
	unsigned int nDE;
	unsigned int nBase;
	unsigned int nElement;
	unsigned int nSize;
	int nImmediate;
	int nCount;
	char acOp[8];
	char acTemp[8];
	char acOpString[8];
	char acTempString[128];
	char acOpList[500][8];
	int nFirst;
}

int rspDMAWrite(__anon_0x5845E *pRSP, int nDMEMAddress, int nRDRAMAddress, int nLength)
{
	int i;
	int nAddress;
	signed short *pDMEM;
	signed short *pRDRAM;
	void *pData;
}

int rspDMARead(__anon_0x5845E *pRSP, int nDMEMAddress, int nRDRAMAddress, int nLength)
{
	int i;
	int nAddress;
	signed short *pDMEM;
	signed short *pRDRAM;
	void *pData;
}

int rspAsmVSAR(__anon_0x5845E *pRSP, signed short nVD, signed short nE)
{
	signed short i;
}

int rspAsmVMACF(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMULF(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMUDN(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMUDM(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMUDL(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMUDH(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMADL(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMADH(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMADN(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVMADM(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	int i;
	int j;
	signed long long product;
	signed short buffer[8];
}

int rspAsmVCL(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	signed short nLE;
	signed short nGE;
	signed short nEQ;
	signed short nCarry;
	signed short i;
	signed short j;
	signed short nDI;
}

int rspAsmVGE(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	signed short i;
	signed short j;
	int nResult;
}

int rspAsmVSUBC(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	signed short i;
	signed short j;
	int nResult;
}

int rspAsmVSUB(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	signed short i;
	signed short j;
	int nResult;
}

int rspAsmVADDC(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	signed short i;
	signed short j;
	int nResult;
}

int rspAsmVADD(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	signed short i;
	signed short j;
	int nResult;
}

int rspAsmVXOR(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	signed short i;
	signed short j;
	int nResult;
}

int rspAsmVAND(__anon_0x5845E *pRSP, signed short nVD, signed short nVS, signed short nVT, signed short nE)
{
	signed short i;
	signed short j;
	int nResult;
}

int rspAsmLRV(__anon_0x5845E *pRSP, signed short nVT, signed short nElement, signed short nOffset, signed short nBase)
{
	char *pVT;
	signed short i;
	signed short nStartAddress;
}

int rspAsmLQV(__anon_0x5845E *pRSP, signed short nVT, signed short nElement, signed short nOffset, signed short nBase)
{
	char *pVT;
	signed short i;
}

int rspAsmLPV(__anon_0x5845E *pRSP, signed short nVT, signed short nOffset, signed short nBase)
{
	int nAddress;
}

int rspAsmLDV(__anon_0x5845E *pRSP, signed short nVT, signed short nElement, signed short nOffset, signed short nBase)
{
	char *pVReg;
	char *pDMEM;
}

int rspAsmLSV(__anon_0x5845E *pRSP, signed short nVT, signed short nElement, signed short nOffset, signed short nBase);

int rspAsmSQV(__anon_0x5845E *pRSP, signed short nVT, signed short nElement, signed short nOffset, signed short nBase)
{
	char *pVT;
	signed short i;
}

int rspAsmSDV(__anon_0x5845E *pRSP, signed short nVT, signed short nElement, signed short nOffset, signed short nBase)
{
	char *pVT;
	char *pDMEM;
}

int rspAsmSLV(__anon_0x5845E *pRSP, signed short nVT, signed short nElement, signed short nOffset, signed short nBase)
{
	char *pVT;
	char *pDMEM;
}

int rspAsmSSV(__anon_0x5845E *pRSP, signed short nVT, signed short nElement, signed short nOffset, signed short nBase)
{
	char *pVT;
}

int rspAsmSW(__anon_0x5845E *pRSP, signed short rt, signed short offset, signed short nBase);

int rspAsmSUB(__anon_0x5845E *pRSP, signed short rd, signed short rs, signed short rt);

int rspAsmSRLV(__anon_0x5845E *pRSP, signed short rd, signed short rt, signed short rs);

int rspAsmSRL(__anon_0x5845E *pRSP, signed short rd, signed short rt, signed short sa);

int rspAsmSLL(__anon_0x5845E *pRSP, signed short rd, signed short rt, signed short sa);

int rspAsmSH(__anon_0x5845E *pRSP, signed short rt, signed short offset, signed short base);

int rspAsmORI(__anon_0x5845E *pRSP, signed short rt, signed short rs, signed short immediate);

int rspAsmOR(__anon_0x5845E *pRSP, signed short rd, signed short rs, signed short rt);

int rspAsmNOP();

int rspAsmMTC2(__anon_0x5845E *pRSP, signed short rt, signed short vd, signed short e);

int rspAsmMTC0(__anon_0x5845E *pRSP, signed short rt, signed short rd);

int rspAsmMFC0(__anon_0x5845E *pRSP, signed short rt, signed short rd);

int rspAsmLW(__anon_0x5845E *pRSP, signed short rt, signed short offset, signed short base);

int rspAsmLUI(__anon_0x5845E *pRSP, signed short rt, signed short immediate);

int rspAsmLHU(__anon_0x5845E *pRSP, signed short rt, signed short offset, signed short base);

int rspAsmLH(__anon_0x5845E *pRSP, signed short rt, signed short offset, signed short base);

int rspAsmLBU(__anon_0x5845E *pRSP, signed short rt, signed short offset, signed short base);

int rspAsmLB(__anon_0x5845E *pRSP, signed short rt, signed short offset, signed short base);

int rspAsmANDI(__anon_0x5845E *pRSP, signed short rt, signed short rs, signed short immediate);

int rspAsmAND(__anon_0x5845E *pRSP, signed short rd, signed short rs, signed short rt);

int rspAsmADDI(__anon_0x5845E *pRSP, signed short rt, signed short rs, signed short immediate);

int rspAsmADD(__anon_0x5845E *pRSP, signed short rd, signed short rs, signed short rt);

int rspVSAW(signed short *pResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	int element;
	unsigned short ri;
}

int rspVCL(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	unsigned short sf;
	unsigned short tf;
	int di;
	int i;
	int ge;
	int le;
	int vce;
	int eq;
	int carry;
	// References: rsp_VCE (0x0)
	// References: rsp_VCO (0x0)
	// References: rsp_VCC (0x0)
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVGE(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	signed short si;
	signed short ti;
	// References: rsp_VCO (0x0)
	// References: rsp_VCC (0x0)
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
	// References: vco_carry (0x0)
	// References: vco_equal (0x0)
}

int rspVSUBC(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	int di;
	// References: rsp_VCO (0x0)
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVADDC(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned int di;
	// References: rsp_VCO (0x0)
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVSUB(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	int borrow;
	int di;
	// References: rsp_VCO (0x0)
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVADD(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	int carry;
	int di;
	// References: rsp_VCO (0x0)
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVMADH(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

// Local to compilation unit
static int rspVMADN(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVMADM(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVMADL(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVMACF(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVMUDH(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

// Local to compilation unit
static int rspVMUDN(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVMUDM(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVMUDL(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

int rspVMULF(signed short *pVec1, signed short *pVec2, signed short *pVecResult, unsigned int nElement, signed long long *pAcc)
{
	int i;
	unsigned short du;
	signed long long taccum;
	signed long long clampMask;
	// References: cmask_tab (0x30E20E80)
	// References: emask_tab (0x50E20E80)
}

