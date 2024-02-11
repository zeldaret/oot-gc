// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// size: 0x10
struct _XL_OBJECTTYPE
{
	char *szName; // 0x0
	int nSizeObject; // 0x4
	_XL_OBJECTTYPE *pClassBase; // 0x8
	int (*pfEvent)(void */* unknown0 */, int /* unknown1 */, void */* unknown2 */); // 0xC
};

// Location: 0xCEB0E80
_XL_OBJECTTYPE gClassLibrary;

// Local to compilation unit
// Location: 0x1CEB0E80
static unsigned int __osRcpImTable[64];

// Local to compilation unit
// Location: 0x28531380
static float dtor$466;

// Local to compilation unit
// Location: 0x2C531380
static float dtor$480;

// Local to compilation unit
// Location: 0x30531380
static unsigned int nAddress$605;

// size: 0x8
struct __anon_0x78E87
{
	int nOffsetHost; // 0x0
	int nAddressN64; // 0x4
};

// size: 0x8
struct cpu_callerID
{
	int N64address; // 0x0
	int GCNaddress; // 0x4
};

// size: 0x48
struct cpu_function
{
	void *pnBase; // 0x0
	void *pfCode; // 0x4
	int nCountJump; // 0x8
	__anon_0x78E87 *aJump; // 0xC
	int nAddress0; // 0x10
	int nAddress1; // 0x14
	cpu_callerID *block; // 0x18
	int callerID_total; // 0x1C
	int callerID_flag; // 0x20
	unsigned int nChecksum; // 0x24
	int timeToLive; // 0x28
	int memory_size; // 0x2C
	int heapID; // 0x30
	int heapWhere; // 0x34
	int treeheapWhere; // 0x38
	cpu_function *prev; // 0x3C
	cpu_function *left; // 0x40
	cpu_function *right; // 0x44
};

// size: 0x8
union __anon_0x7923C
{
	char _0s8; // 0x0
	char _1s8; // 0x1
	char _2s8; // 0x2
	char _3s8; // 0x3
	char _4s8; // 0x4
	char _5s8; // 0x5
	char _6s8; // 0x6
	char s8; // 0x7
	signed short _0s16; // 0x0
	signed short _1s16; // 0x2
	signed short _2s16; // 0x4
	signed short s16; // 0x6
	int _0s32; // 0x0
	int s32; // 0x4
	signed long long s64; // 0x0
	unsigned char _0u8; // 0x0
	unsigned char _1u8; // 0x1
	unsigned char _2u8; // 0x2
	unsigned char _3u8; // 0x3
	unsigned char _4u8; // 0x4
	unsigned char _5u8; // 0x5
	unsigned char _6u8; // 0x6
	unsigned char u8; // 0x7
	unsigned short _0u16; // 0x0
	unsigned short _1u16; // 0x2
	unsigned short _2u16; // 0x4
	unsigned short u16; // 0x6
	unsigned int _0u32; // 0x0
	unsigned int u32; // 0x4
	unsigned long long u64; // 0x0
};

// size: 0x34
struct __anon_0x79A22
{
	int nType; // 0x0
	void *pObject; // 0x4
	int nOffsetAddress; // 0x8
	int (*pfGet8)(void */* unknown0 */, unsigned int /* unknown1 */, char */* unknown2 */); // 0xC
	int (*pfGet16)(void */* unknown0 */, unsigned int /* unknown1 */, signed short */* unknown2 */); // 0x10
	int (*pfGet32)(void */* unknown0 */, unsigned int /* unknown1 */, int */* unknown2 */); // 0x14
	int (*pfGet64)(void */* unknown0 */, unsigned int /* unknown1 */, signed long long */* unknown2 */); // 0x18
	int (*pfPut8)(void */* unknown0 */, unsigned int /* unknown1 */, char */* unknown2 */); // 0x1C
	int (*pfPut16)(void */* unknown0 */, unsigned int /* unknown1 */, signed short */* unknown2 */); // 0x20
	int (*pfPut32)(void */* unknown0 */, unsigned int /* unknown1 */, int */* unknown2 */); // 0x24
	int (*pfPut64)(void */* unknown0 */, unsigned int /* unknown1 */, signed long long */* unknown2 */); // 0x28
	unsigned int nAddressPhysical0; // 0x2C
	unsigned int nAddressPhysical1; // 0x30
};

// size: 0x84
struct cpu_treeRoot
{
	unsigned short total; // 0x0
	int total_memory; // 0x4
	int root_address; // 0x8
	int start_range; // 0xC
	int end_range; // 0x10
	int cache_miss; // 0x14
	int cache[20]; // 0x18
	cpu_function *left; // 0x68
	cpu_function *right; // 0x6C
	int kill_limit; // 0x70
	int kill_number; // 0x74
	int side; // 0x78
	cpu_function *restore; // 0x7C
	int restore_side; // 0x80
};

// size: 0xC
struct _CPU_ADDRESS
{
	int nN64; // 0x0
	int nHost; // 0x4
	cpu_function *pFunction; // 0x8
};

// size: 0xC
struct __anon_0x79FE6
{
	unsigned int nAddress; // 0x0
	unsigned int nOpcodeOld; // 0x4
	unsigned int nOpcodeNew; // 0x8
};

// size: 0x2C8
struct OSContext
{
	unsigned long gpr[32]; // 0x0
	unsigned long cr; // 0x80
	unsigned long lr; // 0x84
	unsigned long ctr; // 0x88
	unsigned long xer; // 0x8C
	long float fpr[32]; // 0x90
	unsigned long fpscr_pad; // 0x190
	unsigned long fpscr; // 0x194
	unsigned long srr0; // 0x198
	unsigned long srr1; // 0x19C
	unsigned short mode; // 0x1A0
	unsigned short state; // 0x1A2
	unsigned long gqr[8]; // 0x1A4
	unsigned long psf_pad; // 0x1C4
	long float psf[32]; // 0x1C8
};

// size: 0x28
struct OSAlarm
{
	void (*handler)(OSAlarm */* unknown0 */, OSContext */* unknown1 */); // 0x0
	unsigned long tag; // 0x4
	signed long long fire; // 0x8
	OSAlarm *prev; // 0x10
	OSAlarm *next; // 0x14
	signed long long period; // 0x18
	signed long long start; // 0x20
};

// size: 0x28
struct cpu_optimize
{
	unsigned int validCheck; // 0x0
	unsigned int destGPR_check; // 0x4
	int destGPR; // 0x8
	int destGPR_mapping; // 0xC
	unsigned int destFPR_check; // 0x10
	int destFPR; // 0x14
	unsigned int addr_check; // 0x18
	int addr_last; // 0x1C
	unsigned int checkType; // 0x20
	unsigned int checkNext; // 0x24
};

// size: 0x12090
struct _CPU
{
	int nMode; // 0x0
	int nTick; // 0x4
	void *pHost; // 0x8
	signed long long nLo; // 0x10
	signed long long nHi; // 0x18
	int nCountAddress; // 0x20
	int iDeviceDefault; // 0x24
	unsigned int nPC; // 0x28
	unsigned int nWaitPC; // 0x2C
	unsigned int nCallLast; // 0x30
	cpu_function *pFunctionLast; // 0x34
	int nReturnAddrLast; // 0x38
	int survivalTimer; // 0x3C
	__anon_0x7923C aGPR[32]; // 0x40
	__anon_0x7D2DB aFPR[32]; // 0x140
	unsigned long long aTLB[48][5]; // 0x240
	int anFCR[32]; // 0x9C0
	signed long long anCP0[32]; // 0xA40
	int (*pfStep)(_CPU */* unknown0 */); // 0xB40
	int (*pfJump)(_CPU */* unknown0 */); // 0xB44
	int (*pfCall)(_CPU */* unknown0 */); // 0xB48
	int (*pfIdle)(_CPU */* unknown0 */); // 0xB4C
	int (*pfRam)(_CPU */* unknown0 */); // 0xB50
	int (*pfRamF)(_CPU */* unknown0 */); // 0xB54
	unsigned int nTickLast; // 0xB58
	unsigned int nRetrace; // 0xB5C
	unsigned int nRetraceUsed; // 0xB60
	__anon_0x79A22 *apDevice[256]; // 0xB64
	unsigned char aiDevice[65536]; // 0xF64
	void *gHeap1; // 0x10F64
	void *gHeap2; // 0x10F68
	unsigned int aHeap1Flag[192]; // 0x10F6C
	unsigned int aHeap2Flag[13]; // 0x1126C
	cpu_treeRoot *gTree; // 0x112A0
	_CPU_ADDRESS aAddressCache[256]; // 0x112A4
	int nCountCodeHack; // 0x11EA4
	__anon_0x79FE6 aCodeHack[32]; // 0x11EA8
	signed long long nTimeRetrace; // 0x12028
	OSAlarm alarmRetrace; // 0x12030
	unsigned int nFlagRAM; // 0x12058
	unsigned int nFlagCODE; // 0x1205C
	unsigned int nCompileFlag; // 0x12060
	cpu_optimize nOptimize; // 0x12064
};

// size: 0x4C
struct __anon_0x7AD10
{
	char *szName; // 0x0
	void (*pfLibrary)(_CPU */* unknown0 */); // 0x4
	unsigned int anData[17]; // 0x8
};

// Location: 0x2CEF0E80
__anon_0x7AD10 gaFunction[54];

// size: 0x68
struct __anon_0x7AE26
{
	int nFlag; // 0x0
	void *pHost; // 0x4
	int nAddStackSwap; // 0x8
	int nCountFunction; // 0xC
	int nAddressException; // 0x10
	__anon_0x7AD10 *aFunction; // 0x14
	void *apData[10]; // 0x18
	int anAddress[10]; // 0x40
};

int libraryEvent(__anon_0x7AE26 *pLibrary, int nEvent, void *pArgument)
{
	// References: gaFunction (0x2CEF0E80)
}

int libraryCall(__anon_0x7AE26 *pLibrary, _CPU *pCPU, int iFunction)
{
	// References: gaFunction (0x2CEF0E80)
}

int libraryFunctionReplaced(int iFunction)
{
	// References: gaFunction (0x2CEF0E80)
}

int libraryUpdate(__anon_0x7AE26 *pLibrary)
{
	_CPU *pCPU;
	cpu_function *pFunction;
}

// Local to compilation unit
static int librarySearch(__anon_0x7AE26 *pLibrary, cpu_function *pFunction);

int libraryTestFunction(__anon_0x7AE26 *pLibrary, cpu_function *pFunction)
{
	int iFunction;
	int iData;
	int bFlag;
	int bDone;
	int bReturn;
	unsigned int iCode;
	unsigned int *pnCode;
	unsigned int *pnCodeTemp;
	unsigned int nSizeCode;
	unsigned int nChecksum;
	unsigned int nOpcode;
	unsigned int nAddress;
	// References: gaFunction (0x2CEF0E80)
}

int libraryCheckHandler(__anon_0x7AE26 *pLibrary, int bException);

// Local to compilation unit
static int libraryFindFunctions(__anon_0x7AE26 *pLibrary)
{
	_CPU *pCPU;
	int iFunction;
	__anon_0x79A22 **apDevice;
	unsigned char *aiDevice;
	unsigned int nOpcode;
	unsigned int *pnCode;
	unsigned int nAddress;
	unsigned int nAddressLast;
	unsigned int nAddressEnqueueThread;
	unsigned int nAddressDispatchThread;
	// References: gaFunction (0x2CEF0E80)
}

// Local to compilation unit
static int libraryFindVariables(__anon_0x7AE26 *pLibrary)
{
	_CPU *pCPU;
	__anon_0x79A22 **apDevice;
	unsigned char *aiDevice;
	unsigned int nAddress;
	unsigned int nAddressLast;
	unsigned int nOffset;
	unsigned int nOpcode;
	unsigned int anCode[6];
}

// Local to compilation unit
static int libraryFindException(__anon_0x7AE26 *pLibrary, int bException)
{
	_CPU *pCPU;
	__anon_0x79A22 **apDevice;
	unsigned char *aiDevice;
	unsigned int anCode[6];
}

int zeldaLoadSZS_Exit(_CPU *pCPU);

int zeldaLoadSZS_Entry(_CPU *pCPU);

int osViSwapBuffer_Entry(_CPU *pCPU)
{
	// References: nAddress$605 (0x30531380)
}

// size: 0x8
struct __anon_0x7BB81
{
	float f_odd; // 0x0
	float f_even; // 0x4
};

// size: 0x8
union __anon_0x7BBDC
{
	__anon_0x7BB81 f; // 0x0
	long float d; // 0x0
	signed long long u64; // 0x0
};

// size: 0x190
struct __anon_0x7BC50
{
	unsigned long long at; // 0x0
	unsigned long long v0; // 0x8
	unsigned long long v1; // 0x10
	unsigned long long a0; // 0x18
	unsigned long long a1; // 0x20
	unsigned long long a2; // 0x28
	unsigned long long a3; // 0x30
	unsigned long long t0; // 0x38
	unsigned long long t1; // 0x40
	unsigned long long t2; // 0x48
	unsigned long long t3; // 0x50
	unsigned long long t4; // 0x58
	unsigned long long t5; // 0x60
	unsigned long long t6; // 0x68
	unsigned long long t7; // 0x70
	unsigned long long s0; // 0x78
	unsigned long long s1; // 0x80
	unsigned long long s2; // 0x88
	unsigned long long s3; // 0x90
	unsigned long long s4; // 0x98
	unsigned long long s5; // 0xA0
	unsigned long long s6; // 0xA8
	unsigned long long s7; // 0xB0
	unsigned long long t8; // 0xB8
	unsigned long long t9; // 0xC0
	unsigned long long gp; // 0xC8
	unsigned long long sp; // 0xD0
	unsigned long long s8; // 0xD8
	unsigned long long ra; // 0xE0
	unsigned long long lo; // 0xE8
	unsigned long long hi; // 0xF0
	unsigned int sr; // 0xF8
	unsigned int pc; // 0xFC
	unsigned int cause; // 0x100
	unsigned int badvaddr; // 0x104
	unsigned int rcp; // 0x108
	unsigned int fpcsr; // 0x10C
	__anon_0x7BBDC fp0; // 0x110
	__anon_0x7BBDC fp2; // 0x118
	__anon_0x7BBDC fp4; // 0x120
	__anon_0x7BBDC fp6; // 0x128
	__anon_0x7BBDC fp8; // 0x130
	__anon_0x7BBDC fp10; // 0x138
	__anon_0x7BBDC fp12; // 0x140
	__anon_0x7BBDC fp14; // 0x148
	__anon_0x7BBDC fp16; // 0x150
	__anon_0x7BBDC fp18; // 0x158
	__anon_0x7BBDC fp20; // 0x160
	__anon_0x7BBDC fp22; // 0x168
	__anon_0x7BBDC fp24; // 0x170
	__anon_0x7BBDC fp26; // 0x178
	__anon_0x7BBDC fp28; // 0x180
	__anon_0x7BBDC fp30; // 0x188
};

// size: 0x1B0
struct __OSThread_s
{
	__OSThread_s *next; // 0x0
	int priority; // 0x4
	__OSThread_s **queue; // 0x8
	__OSThread_s *tlnext; // 0xC
	unsigned short state; // 0x10
	unsigned short flags; // 0x12
	int id; // 0x14
	int fp; // 0x18
	__anon_0x7BC50 context; // 0x20
};

// size: 0x18
struct OSMesgQueue_s
{
	__OSThread_s *mtqueue; // 0x0
	__OSThread_s *fullqueue; // 0x4
	int validCount; // 0x8
	int first; // 0xC
	int msgCount; // 0x10
	void *msg; // 0x14
};

// size: 0x8
struct __anon_0x7C589
{
	unsigned short type; // 0x0
	unsigned char pri; // 0x2
	unsigned char status; // 0x3
	OSMesgQueue_s *retQueue; // 0x4
};

// size: 0x18
struct __anon_0x7C62D
{
	__anon_0x7C589 hdr; // 0x0
	void *dramAddr; // 0x8
	unsigned long devAddr; // 0xC
	unsigned long size; // 0x10
	void *piHandle; // 0x14
};

int dmaSoundRomHandler_ZELDA1(_CPU *pCPU)
{
	void *pTarget;
	OSMesgQueue_s *mq;
	unsigned int *msg;
	__anon_0x7C62D *pIOMessage;
	int first;
	int msgCount;
	int validCount;
	int nSize;
	int nAddress;
	int nOffsetRAM;
	int nOffsetROM;
}

int pictureSnap_Zelda2(_CPU *pCPU);

int starfoxCopy(_CPU *pCPU)
{
	int *A0;
	int A1;
	int A2;
	int A3;
	int T0;
	int T1;
	int T2;
	int T3;
	int T8;
	int T9;
	signed short *pData16;
	char *source;
	char *target;
}

int osEepromLongWrite(_CPU *pCPU)
{
	int length;
	int ret;
	unsigned char address;
	unsigned char *buffer;
}

int osEepromLongRead(_CPU *pCPU)
{
	int length;
	int ret;
	unsigned char address;
	unsigned char *buffer;
}

int osEepromWrite(_CPU *pCPU)
{
	unsigned char address;
	unsigned char *buffer;
}

int osEepromRead(_CPU *pCPU)
{
	unsigned char address;
	unsigned char *buffer;
}

int __osEepStatus(_CPU *pCPU)
{
	int ret;
	int nSize;
	unsigned char *status;
}

int osAiSetNextBuffer(_CPU *pCPU)
{
	unsigned int size;
	unsigned int nData32;
}

int osAiSetFrequency(_CPU *pCPU)
{
	unsigned int dacRate;
	unsigned char bitRate;
	unsigned int nData32;
}

// size: 0xC
struct __anon_0x7D115
{
	unsigned char col[3]; // 0x0
	char pad1; // 0x3
	unsigned char colc[3]; // 0x4
	char pad2; // 0x7
	signed char dir[3]; // 0x8
	char pad3; // 0xB
};

// size: 0x10
union __anon_0x7D215
{
	__anon_0x7D115 l; // 0x0
	signed long long force_structure_alignment[2]; // 0x0
};

// size: 0x20
struct __anon_0x7D2A5
{
	__anon_0x7D215 l[2]; // 0x0
};

// size: 0x8
union __anon_0x7D2DB
{
	float _0f32; // 0x0
	float f32; // 0x4
	long float f64; // 0x0
	int _0s32; // 0x0
	int s32; // 0x4
	signed long long s64; // 0x0
	unsigned int _0u32; // 0x0
	unsigned int u32; // 0x4
	unsigned long long u64; // 0x0
};

void guLookAtReflect(_CPU *pCPU)
{
	__anon_0x7D2A5 *l;
	int i;
	int j;
	int e1;
	int e2;
	__anon_0x7D2DB data;
	float mf[4][4];
	unsigned int *m;
	unsigned int *sp;
	int *ai;
	int *af;
	float xEye;
	float yEye;
	float zEye;
	float xAt;
	float yAt;
	float zAt;
	float xUp;
	float yUp;
	float zUp;
	float len;
	float xLook;
	float yLook;
	float zLook;
	float xRight;
	float yRight;
	float zRight;
}

void guLookAtReflectF(_CPU *pCPU)
{
	__anon_0x7D2A5 *l;
	__anon_0x7D2DB data;
	unsigned int *mf;
	unsigned int *sp;
	float xEye;
	float yEye;
	float zEye;
	float xAt;
	float yAt;
	float zAt;
	float xUp;
	float yUp;
	float zUp;
	float len;
	float xLook;
	float yLook;
	float zLook;
	float xRight;
	float yRight;
	float zRight;
}

// size: 0x10
struct __anon_0x7DB47
{
	int x1; // 0x0
	int y1; // 0x4
	int x2; // 0x8
	int y2; // 0xC
};

// size: 0x10
union __anon_0x7DBF9
{
	__anon_0x7DB47 h; // 0x0
	long force_structure_alignment[4]; // 0x0
};

void guLookAtHilite(_CPU *pCPU)
{
	__anon_0x7D2A5 *l;
	__anon_0x7DBF9 *h;
	int i;
	int j;
	int e1;
	int e2;
	__anon_0x7D2DB data;
	float mf[4][4];
	unsigned int *m;
	unsigned int *sp;
	int *ai;
	int *af;
	float len;
	float xLook;
	float yLook;
	float zLook;
	float xRight;
	float yRight;
	float zRight;
	float xHilite;
	float yHilite;
	float zHilite;
	float xEye;
	float yEye;
	float zEye;
	float xAt;
	float yAt;
	float zAt;
	float xUp;
	float yUp;
	float zUp;
	float xl1;
	float yl1;
	float zl1;
	float xl2;
	float yl2;
	float zl2;
	int twidth;
	int theight;
}

void guLookAtHiliteF(_CPU *pCPU)
{
	__anon_0x7D2A5 *l;
	__anon_0x7DBF9 *h;
	__anon_0x7D2DB data;
	unsigned int *mf;
	unsigned int *sp;
	float len;
	float xLook;
	float yLook;
	float zLook;
	float xRight;
	float yRight;
	float zRight;
	float xHilite;
	float yHilite;
	float zHilite;
	float xEye;
	float yEye;
	float zEye;
	float xAt;
	float yAt;
	float zAt;
	float xUp;
	float yUp;
	float zUp;
	float xl1;
	float yl1;
	float zl1;
	float xl2;
	float yl2;
	float zl2;
	int twidth;
	int theight;
}

int __float2int(float x);

void guLookAt(_CPU *pCPU)
{
	float mf[4][4];
	int *m;
	unsigned int *sp;
	__anon_0x7D2DB data;
	int i;
	int j;
	int e1;
	int e2;
	int *ai;
	int *af;
	float len;
	float xLook;
	float yLook;
	float zLook;
	float xRight;
	float yRight;
	float zRight;
	float xEye;
	float yEye;
	float zEye;
	float xAt;
	float yAt;
	float zAt;
	float xUp;
	float yUp;
	float zUp;
}

void guLookAtF(_CPU *pCPU)
{
	float len;
	float xAt;
	float yAt;
	float zAt;
	float xUp;
	float yUp;
	float zUp;
	float xEye;
	float yEye;
	float zEye;
	unsigned int *mf;
	unsigned int *sp;
	float xLook;
	float yLook;
	float zLook;
	float xRight;
	float yRight;
	float zRight;
	__anon_0x7D2DB data;
	__anon_0x7D2DB data0;
	__anon_0x7D2DB data1;
}

void guRotate(_CPU *pCPU)
{
	int *m;
	unsigned int *sp;
	__anon_0x7D2DB data;
	int i;
	int j;
	int e1;
	int e2;
	float mf[4][4];
	float sine;
	float cosine;
	float a;
	float x;
	float y;
	float z;
	float ab;
	float bc;
	float ca;
	float t;
	float magnitude;
	int *ai;
	int *af;
	// References: dtor$480 (0x2C531380)
}

void guRotateF(_CPU *pCPU)
{
	float m;
	int i;
	int j;
	float a;
	float x;
	float y;
	float z;
	unsigned int *mf;
	unsigned int *sp;
	__anon_0x7D2DB data;
	__anon_0x7D2DB data0;
	__anon_0x7D2DB data1;
	float sine;
	float cosine;
	float ab;
	float bc;
	float ca;
	float t;
	// References: dtor$466 (0x28531380)
}

void guTranslate(_CPU *pCPU)
{
	int *m;
	int i;
	int j;
	int e1;
	int e2;
	__anon_0x7D2DB data;
	float mf[4][4];
	int *ai;
	int *af;
}

void guTranslateF(_CPU *pCPU)
{
	int i;
	int j;
	unsigned int *mf;
	__anon_0x7D2DB data0;
	__anon_0x7D2DB data1;
}

void guScale(_CPU *pCPU)
{
	float mf[4][4];
	int *m;
	int i;
	int j;
	int e1;
	int e2;
	__anon_0x7D2DB data;
	int *ai;
	int *af;
}

void guScaleF(_CPU *pCPU)
{
	int i;
	int j;
	unsigned int *mf;
	__anon_0x7D2DB data0;
	__anon_0x7D2DB data1;
}

// size: 0x10
struct __anon_0x7F9D8
{
	float rX; // 0x0
	float rY; // 0x4
	float rSizeX; // 0x8
	float rSizeY; // 0xC
};

// size: 0x14
struct __anon_0x7FA72
{
	int nSize; // 0x0
	int nWidth; // 0x4
	int nFormat; // 0x8
	void *pData; // 0xC
	int nAddress; // 0x10
};

// size: 0xC
struct __anon_0x7FBB3
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
};

// size: 0x3C
struct __anon_0x7FC23
{
	int bTransformed; // 0x0
	__anon_0x7FBB3 rVecOrigTowards; // 0x4
	float rColorR; // 0x10
	float rColorG; // 0x14
	float rColorB; // 0x18
	float rVectorX; // 0x1C
	float rVectorY; // 0x20
	float rVectorZ; // 0x24
	float kc; // 0x28
	float kl; // 0x2C
	float kq; // 0x30
	signed short coordX; // 0x34
	signed short coordY; // 0x36
	signed short coordZ; // 0x38
};

// size: 0x34
struct __anon_0x7FE53
{
	int bTransformed; // 0x0
	__anon_0x7FBB3 rS; // 0x4
	__anon_0x7FBB3 rT; // 0x10
	__anon_0x7FBB3 rSRaw; // 0x1C
	__anon_0x7FBB3 rTRaw; // 0x28
};

// size: 0x1C
struct __anon_0x7FF3C
{
	float rSum; // 0x0
	float rS; // 0x4
	float rT; // 0x8
	__anon_0x7FBB3 vec; // 0xC
	unsigned char anColor[4]; // 0x18
};

// size: 0x1000
union __anon_0x8009B
{
	unsigned char u8[4096]; // 0x0
	unsigned short u16[2048]; // 0x0
	unsigned int u32[1024]; // 0x0
	unsigned long long u64[512]; // 0x0
};

// size: 0x1000
struct __anon_0x80138
{
	__anon_0x8009B data; // 0x0
};

// size: 0x4
enum _GXTexFmt
{
	GX_TF_I4 = 0,
	GX_TF_I8 = 1,
	GX_TF_IA4 = 2,
	GX_TF_IA8 = 3,
	GX_TF_RGB565 = 4,
	GX_TF_RGB5A3 = 5,
	GX_TF_RGBA8 = 6,
	GX_TF_CMPR = 14,
	GX_CTF_R4 = 32,
	GX_CTF_RA4 = 34,
	GX_CTF_RA8 = 35,
	GX_CTF_YUVA8 = 38,
	GX_CTF_A8 = 39,
	GX_CTF_R8 = 40,
	GX_CTF_G8 = 41,
	GX_CTF_B8 = 42,
	GX_CTF_RG8 = 43,
	GX_CTF_GB8 = 44,
	GX_TF_Z8 = 17,
	GX_TF_Z16 = 19,
	GX_TF_Z24X8 = 22,
	GX_CTF_Z4 = 48,
	GX_CTF_Z8M = 57,
	GX_CTF_Z8L = 58,
	GX_CTF_Z16L = 60,
	GX_TF_A8 = 39
};

// size: 0xC
struct _GXTlutObj
{
	unsigned long dummy[3]; // 0x0
};

// size: 0x20
struct _GXTexObj
{
	unsigned long dummy[8]; // 0x0
};

// size: 0x4
enum _GXTexWrapMode
{
	GX_CLAMP = 0,
	GX_REPEAT = 1,
	GX_MIRROR = 2,
	GX_MAX_TEXWRAPMODE = 3
};

// size: 0x6C
struct _FRAME_TEXTURE
{
	int nMode; // 0x0
	int iPackPixel; // 0x4
	int iPackColor; // 0x8
	int nFrameLast; // 0xC
	signed short nSizeX; // 0x10
	signed short nSizeY; // 0x12
	unsigned int nAddress; // 0x14
	unsigned int nCodePixel; // 0x18
	unsigned int nCodeColor; // 0x1C
	_FRAME_TEXTURE *pTextureNext; // 0x20
	unsigned int nData0; // 0x24
	unsigned int nData1; // 0x28
	unsigned int nData2; // 0x2C
	unsigned int nData3; // 0x30
	_GXTexFmt eFormat; // 0x34
	_GXTlutObj objectTLUT; // 0x38
	_GXTexObj objectTexture; // 0x44
	_GXTexWrapMode eWrapS; // 0x64
	_GXTexWrapMode eWrapT; // 0x68
};

// size: 0x2C
struct __anon_0x80806
{
	int nSize; // 0x0
	int nTMEM; // 0x4
	int iTLUT; // 0x8
	int nSizeX; // 0xC
	int nFormat; // 0x10
	signed short nMaskS; // 0x14
	signed short nMaskT; // 0x16
	signed short nModeS; // 0x18
	signed short nModeT; // 0x1A
	signed short nShiftS; // 0x1C
	signed short nShiftT; // 0x1E
	signed short nX0; // 0x20
	signed short nY0; // 0x22
	signed short nX1; // 0x24
	signed short nY1; // 0x26
	unsigned int nCodePixel; // 0x28
};

// size: 0x4
enum __anon_0x80AE8
{
	FMP_NONE = 4294967295,
	FMP_PERSPECTIVE = 0,
	FMP_ORTHOGRAPHIC = 1
};

// size: 0x24
struct __anon_0x80B6D
{
	int nCount; // 0x0
	float rScale; // 0x4
	float rAspect; // 0x8
	float rFieldOfViewY; // 0xC
	float rClipNear; // 0x10
	float rClipFar; // 0x14
	unsigned int nAddressFloat; // 0x18
	unsigned int nAddressFixed; // 0x1C
	__anon_0x80AE8 eProjection; // 0x20
};

// size: 0x4
struct _GXColor
{
	unsigned char r; // 0x0
	unsigned char g; // 0x1
	unsigned char b; // 0x2
	unsigned char a; // 0x3
};

// size: 0x3D150
struct __anon_0x80DBD
{
	unsigned int anCIMGAddresses[8]; // 0x0
	unsigned short nNumCIMGAddresses; // 0x20
	int bBlurOn; // 0x24
	int bHackPause; // 0x28
	int nHackCount; // 0x2C
	int nFrameCounter; // 0x30
	int bPauseThisFrame; // 0x34
	int bCameFromBomberNotes; // 0x38
	int bInBomberNotes; // 0x3C
	int bShrinking; // 0x40
	int bSnapShot; // 0x44
	int bUsingLens; // 0x48
	unsigned char cBlurAlpha; // 0x4C
	int bBlurredThisFrame; // 0x50
	int nFrameCIMGCalls; // 0x54
	int bModifyZBuffer; // 0x58
	int bOverrideDepth; // 0x5C
	int nZBufferSets; // 0x60
	int nLastFrameZSets; // 0x64
	int bPauseBGDrawn; // 0x68
	int bFrameOn; // 0x6C
	int bBackBufferDrawn; // 0x70
	int bGrabbedFrame; // 0x74
	unsigned long long *pnGBI; // 0x78
	unsigned int nFlag; // 0x7C
	float rScaleX; // 0x80
	float rScaleY; // 0x84
	unsigned int nCountFrames; // 0x88
	unsigned int nMode; // 0x8C
	unsigned int aMode[10]; // 0x90
	__anon_0x7F9D8 viewport; // 0xB8
	__anon_0x7FA72 aBuffer[4]; // 0xC8
	unsigned int nOffsetDepth0; // 0x118
	unsigned int nOffsetDepth1; // 0x11C
	int nWidthLine; // 0x120
	float rDepth; // 0x124
	float rDelta; // 0x128
	int (*aDraw[4])(void */* unknown0 */, void */* unknown1 */); // 0x12C
	int nCountLight; // 0x13C
	__anon_0x7FC23 aLight[8]; // 0x140
	__anon_0x7FE53 lookAt; // 0x320
	int nCountVertex; // 0x354
	__anon_0x7FF3C aVertex[80]; // 0x358
	__anon_0x80138 TMEM; // 0xC18
	void *aPixelData; // 0x1C18
	void *aColorData; // 0x1C1C
	int nBlocksPixel; // 0x1C20
	int nBlocksMaxPixel; // 0x1C24
	int nBlocksColor; // 0x1C28
	int nBlocksMaxColor; // 0x1C2C
	int nBlocksTexture; // 0x1C30
	int nBlocksMaxTexture; // 0x1C34
	unsigned int anPackPixel[48]; // 0x1C38
	unsigned int anPackColor[320]; // 0x1CF8
	unsigned int nAddressLoad; // 0x21F8
	unsigned int nCodePixel; // 0x21FC
	unsigned int nTlutCode[16]; // 0x2200
	_FRAME_TEXTURE aTexture[2048]; // 0x2240
	unsigned int anTextureUsed[64]; // 0x38240
	_FRAME_TEXTURE *apTextureCached[4096]; // 0x38340
	int iTileLoad; // 0x3C340
	unsigned int n2dLoadTexType; // 0x3C344
	int nLastX0; // 0x3C348
	int nLastY0; // 0x3C34C
	int nLastX1; // 0x3C350
	int nLastY1; // 0x3C354
	__anon_0x80806 aTile[8]; // 0x3C358
	int anSizeX[2]; // 0x3C4B8
	int anSizeY[2]; // 0x3C4C0
	int iHintMatrix; // 0x3C4C8
	int iMatrixModel; // 0x3C4CC
	int iHintProjection; // 0x3C4D0
	float matrixView[4][4]; // 0x3C4D4
	int iHintLast; // 0x3C514
	int iHintHack; // 0x3C518
	__anon_0x80AE8 eTypeProjection; // 0x3C51C
	float aMatrixModel[10][4][4]; // 0x3C520
	float matrixProjection[4][4]; // 0x3C7A0
	float matrixProjectionExtra[4][4]; // 0x3C7E0
	__anon_0x80B6D aMatrixHint[64]; // 0x3C820
	unsigned char primLODmin; // 0x3D120
	unsigned char primLODfrac; // 0x3D121
	unsigned char lastTile; // 0x3D122
	unsigned char iTileDrawn; // 0x3D123
	_GXColor aColor[5]; // 0x3D124
	unsigned int nModeVtx; // 0x3D138
	unsigned short *nTempBuffer; // 0x3D13C
	unsigned short *nCopyBuffer; // 0x3D140
	unsigned int *nLensBuffer; // 0x3D144
	unsigned short *nCameraBuffer; // 0x3D148
};

void GenPerspective_1080(_CPU *pCPU)
{
	__anon_0x7D2DB data;
	unsigned int *mf;
	unsigned int *sp;
	float fovy;
	float aspect;
	float rNear;
	float rFar;
	__anon_0x80DBD *pFrame;
}

void guPerspective(_CPU *pCPU)
{
	int *m;
	float fovy;
	float aspect;
	float rNear;
	float rFar;
	float scale;
	float _cot;
	int i;
	int j;
	__anon_0x7D2DB data;
	float mf[4][4];
	int e1;
	int e2;
	unsigned int *sp;
	int *ai;
	int *af;
}

void guPerspectiveF(_CPU *pCPU)
{
	int i;
	int j;
	float cot;
	signed short *perspNorm;
	unsigned int *mf;
	unsigned int *sp;
	__anon_0x7D2DB data0;
	__anon_0x7D2DB data1;
	__anon_0x7D2DB data;
	float fovy;
	float aspect;
	float rNear;
	float rFar;
	float scale;
}

void guOrtho(_CPU *pCPU)
{
	int *m;
	int i;
	int j;
	int e1;
	int e2;
	__anon_0x7D2DB data;
	float mf[4][4];
	unsigned int *sp;
	int *ai;
	int *af;
	float l;
	float r;
	float b;
	float t;
	float n;
	float f;
	float scale;
}

void guOrthoF(_CPU *pCPU)
{
	int i;
	int j;
	unsigned int *mf;
	unsigned int *sp;
	float l;
	float r;
	float b;
	float t;
	float n;
	float f;
	float scale;
	__anon_0x7D2DB data0;
	__anon_0x7D2DB data1;
	__anon_0x7D2DB data;
}

void guMtxIdent(_CPU *pCPU)
{
	int *m;
}

void guMtxIdentF(_CPU *pCPU)
{
	float *mf;
	int i;
	int j;
	__anon_0x7D2DB data1;
	__anon_0x7D2DB data0;
}

void guMtxF2L(_CPU *pCPU)
{
	float *mf;
	int e1;
	int e2;
	int i;
	int j;
	int *m;
	__anon_0x7D2DB data;
	int *ai;
	int *af;
}

void guMtxCatF(_CPU *pCPU)
{
	int i;
	int j;
	float temp[4][4];
	__anon_0x7D2DB data1;
	__anon_0x7D2DB data2;
	unsigned int *mf;
	unsigned int *nf;
	unsigned int *res;
}

void osVirtualToPhysical(_CPU *pCPU);

void osPhysicalToVirtual(_CPU *pCPU);

void _memcpy(_CPU *pCPU)
{
	int nSize;
	void *pSource;
	void *pTarget;
}

void _bcopy(_CPU *pCPU)
{
	int nSize;
	void *pSource;
	void *pTarget;
}

void _bzero(_CPU *pCPU)
{
	int nSize;
	void *pBuffer;
}

// Local to compilation unit
static void __sinf(_CPU *pCPU);

// Local to compilation unit
static void __cosf(_CPU *pCPU);

// Local to compilation unit
static int __osSpSetStatus(_CPU *pCPU)
{
	unsigned int nData32;
}

// Local to compilation unit
static int __osRestoreInt(_CPU *pCPU)
{
	unsigned long long nStatus;
}

// Local to compilation unit
static int __osDisableInt(_CPU *pCPU)
{
	unsigned int nStatus;
	unsigned long long nData64;
}

// Local to compilation unit
static int osInvalICache(_CPU *pCPU)
{
	unsigned int nAddress;
	unsigned int nSize;
}

// Local to compilation unit
static int osGetMemSize(_CPU *pCPU)
{
	unsigned int nSize;
}

int __ptException();

// Local to compilation unit
static int __osDispatchThread(_CPU *pCPU)
{
	__anon_0x7AE26 *pLibrary;
	unsigned int nAddress;
	unsigned long long nData64;
	__OSThread_s *__osRunningThread;
	unsigned int nData32;
	unsigned int __OSGlobalIntMask;
	unsigned int nStatus;
	unsigned int nMask;
	// References: __osRcpImTable (0x1CEB0E80)
}

// Local to compilation unit
static int __osPopThread(_CPU *pCPU)
{
	__anon_0x79A22 **apDevice;
	unsigned char *aiDevice;
}

// Local to compilation unit
static int __osEnqueueThread(_CPU *pCPU)
{
	__anon_0x79A22 **apDevice;
	unsigned char *aiDevice;
}

// Local to compilation unit
static int __osEnqueueAndYield(_CPU *pCPU)
{
	signed long long nData64;
	__anon_0x7AE26 *pLibrary;
	__OSThread_s *__osRunningThread;
	unsigned int __OSGlobalIntMask;
	unsigned int nStatus;
	unsigned int nData32;
	unsigned int nMask;
	__anon_0x79A22 **apDevice;
	unsigned char *aiDevice;
}

// Local to compilation unit
static int send_mesg(_CPU *pCPU)
{
	__anon_0x7AE26 *pLibrary;
	__anon_0x79A22 **apDevice;
	unsigned char *aiDevice;
}

// Local to compilation unit
static int __osException(_CPU *pCPU)
{
	int iBit;
	__anon_0x7AE26 *pLibrary;
	signed long long nData64;
	signed long long nCause;
	__OSThread_s *__osRunningThread;
	__anon_0x79A22 **apDevice;
	unsigned char *aiDevice;
	unsigned int nStatus;
	unsigned int nStatusRSP;
	unsigned int nData32;
	unsigned int __OSGlobalIntMask;
	unsigned int nS0;
	unsigned int nS1;
	unsigned int nMask;
}

