// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// Local to compilation unit
// Location: 0x40561380
static long ReadThreadCreated;

// size: 0x8
struct OSThreadQueue
{
	OSThread *head; // 0x0
	OSThread *tail; // 0x4
};

// size: 0x20
struct OSMessageQueue
{
	OSThreadQueue queueSend; // 0x0
	OSThreadQueue queueReceive; // 0x8
	void *msgArray; // 0x10
	long msgCount; // 0x14
	long firstIndex; // 0x18
	long usedCount; // 0x1C
};

// Local to compilation unit
// Location: 0x800FB1C0
static OSMessageQueue FreeReadBufferQueue;

// Local to compilation unit
// Location: 0x800FB1E0
static OSMessageQueue ReadedBufferQueue;

// Local to compilation unit
// Location: 0xB20F80
static OSMessageQueue ReadedBufferQueue2;

// Local to compilation unit
// Location: 0x20B20F80
static void *FreeReadBufferMessage[10];

// Local to compilation unit
// Location: 0x48B20F80
static void *ReadedBufferMessage[10];

// Local to compilation unit
// Location: 0x70B20F80
static void *ReadedBufferMessage2[10];

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

// size: 0x8
struct OSThreadLink
{
	OSThread *next; // 0x0
	OSThread *prev; // 0x4
};

// size: 0x8
struct OSMutexLink
{
	OSMutex *next; // 0x0
	OSMutex *prev; // 0x4
};

// size: 0x18
struct OSMutex
{
	OSThreadQueue queue; // 0x0
	OSThread *thread; // 0x8
	long count; // 0xC
	OSMutexLink link; // 0x10
};

// size: 0x8
struct OSMutexQueue
{
	OSMutex *head; // 0x0
	OSMutex *tail; // 0x4
};

// size: 0x318
struct OSThread
{
	OSContext context; // 0x0
	unsigned short state; // 0x2C8
	unsigned short attr; // 0x2CA
	long suspend; // 0x2CC
	long priority; // 0x2D0
	long base; // 0x2D4
	void *val; // 0x2D8
	OSThreadQueue *queue; // 0x2DC
	OSThreadLink link; // 0x2E0
	OSThreadQueue queueJoin; // 0x2E8
	OSMutex *mutex; // 0x2F0
	OSMutexQueue queueMutex; // 0x2F4
	OSThreadLink linkActive; // 0x2FC
	unsigned char *stackBase; // 0x304
	unsigned long *stackEnd; // 0x308
	long error; // 0x30C
	void *specific[2]; // 0x310
};

// Local to compilation unit
// Location: 0x800FB298
static OSThread ReadThread;

// Local to compilation unit
// Location: 0x800FB5B0
static unsigned char ReadThreadStack[4096];

// Local to compilation unit
// Location: 0x800FC5B0
static float gOrthoMtx[4][4];

// Location: 0x44561380
int gMovieErrorToggle;

// Local to compilation unit
// Location: 0x48561380
static int toggle$184;

// Local to compilation unit
// Location: 0x4C561380
static int gbReset;

// Local to compilation unit
// Location: 0x50561380
static unsigned int gnTickReset;

void PushReadedBuffer2(void *buffer)
{
	// References: ReadedBufferQueue2 (0xB20F80)
}

void *PopReadedBuffer2()
{
	void *msg;
	// References: ReadedBufferQueue2 (0xB20F80)
}

void PushFreeReadBuffer(void *buffer)
{
	// References: FreeReadBufferQueue (0x800FB1C0)
}

void *PopFreeReadBuffer()
{
	void *msg;
	// References: FreeReadBufferQueue (0x800FB1C0)
}

void PushReadedBuffer(void *buffer)
{
	// References: ReadedBufferQueue (0x800FB1E0)
}

void *PopReadedBuffer()
{
	void *msg;
	// References: ReadedBufferQueue (0x800FB1E0)
}

// size: 0x20
struct DVDDiskID
{
	char gameName[4]; // 0x0
	char company[2]; // 0x4
	unsigned char diskNumber; // 0x6
	unsigned char gameVersion; // 0x7
	unsigned char streaming; // 0x8
	unsigned char streamingBufSize; // 0x9
	unsigned char padding[22]; // 0xA
};

// size: 0x30
struct DVDCommandBlock
{
	DVDCommandBlock *next; // 0x0
	DVDCommandBlock *prev; // 0x4
	unsigned long command; // 0x8
	long state; // 0xC
	unsigned long offset; // 0x10
	unsigned long length; // 0x14
	void *addr; // 0x18
	unsigned long currTransferSize; // 0x1C
	unsigned long transferredSize; // 0x20
	DVDDiskID *id; // 0x24
	void (*callback)(long /* unknown0 */, DVDCommandBlock */* unknown1 */); // 0x28
	void *userData; // 0x2C
};

// size: 0x3C
struct DVDFileInfo
{
	DVDCommandBlock cb; // 0x0
	unsigned long startAddr; // 0x30
	unsigned long length; // 0x34
	void (*callback)(long /* unknown0 */, DVDFileInfo */* unknown1 */); // 0x38
};

// size: 0x30
struct __anon_0x16250
{
	char magic[4]; // 0x0
	unsigned long version; // 0x4
	unsigned long bufSize; // 0x8
	unsigned long audioMaxSamples; // 0xC
	float frameRate; // 0x10
	unsigned long numFrames; // 0x14
	unsigned long firstFrameSize; // 0x18
	unsigned long movieDataSize; // 0x1C
	unsigned long compInfoDataOffsets; // 0x20
	unsigned long offsetDataOffsets; // 0x24
	unsigned long movieDataOffsets; // 0x28
	unsigned long finalFrameDataOffsets; // 0x2C
};

// size: 0x14
struct __anon_0x1647C
{
	unsigned long numComponents; // 0x0
	unsigned char frameComp[16]; // 0x4
};

// size: 0xC
struct __anon_0x164E4
{
	unsigned long xSize; // 0x0
	unsigned long ySize; // 0x4
	unsigned long videoType; // 0x8
};

// size: 0x10
struct __anon_0x16564
{
	unsigned long sndChannels; // 0x0
	unsigned long sndFrequency; // 0x4
	unsigned long sndNumSamples; // 0x8
	unsigned long sndNumTracks; // 0xC
};

// size: 0x10
struct __anon_0x1661E
{
	unsigned char *ytexture; // 0x0
	unsigned char *utexture; // 0x4
	unsigned char *vtexture; // 0x8
	long frameNumber; // 0xC
};

// size: 0xC
struct __anon_0x166D4
{
	signed short *buffer; // 0x0
	signed short *curPtr; // 0x4
	unsigned long validSample; // 0x8
};

// size: 0xC
struct __anon_0x1675E
{
	unsigned char *ptr; // 0x0
	long frameNumber; // 0x4
	int isValid; // 0x8
};

// size: 0x1D0
struct __anon_0x16849
{
	DVDFileInfo fileInfo; // 0x0
	__anon_0x16250 header; // 0x3C
	__anon_0x1647C compInfo; // 0x6C
	__anon_0x164E4 videoInfo; // 0x80
	__anon_0x16564 audioInfo; // 0x8C
	void *thpWork; // 0x9C
	int open; // 0xA0
	unsigned char state; // 0xA4
	unsigned char internalState; // 0xA5
	unsigned char playFlag; // 0xA6
	unsigned char audioExist; // 0xA7
	long dvdError; // 0xA8
	long videoError; // 0xAC
	int onMemory; // 0xB0
	unsigned char *movieData; // 0xB4
	long initOffset; // 0xB8
	long initReadSize; // 0xBC
	long initReadFrame; // 0xC0
	signed long long retraceCount; // 0xC8
	long prevCount; // 0xD0
	long curCount; // 0xD4
	long videoAhead; // 0xD8
	float curVolume; // 0xDC
	float targetVolume; // 0xE0
	float deltaVolume; // 0xE4
	long rampCount; // 0xE8
	long curAudioTrack; // 0xEC
	long curVideoNumber; // 0xF0
	long curAudioNumber; // 0xF4
	__anon_0x1661E *dispTextureSet; // 0xF8
	__anon_0x166D4 *playAudioBuffer; // 0xFC
	__anon_0x1675E readBuffer[10]; // 0x100
	__anon_0x1661E textureSet[3]; // 0x178
	__anon_0x166D4 audioBuffer[3]; // 0x1A8
};

// Location: 0x800F9C80
__anon_0x16849 ActivePlayer;

// Local to compilation unit
static void *Reader()
{
	__anon_0x1675E *readBuffer;
	long offset;
	long size;
	long readFrame;
	// References: ReadThread (0x800FB298)
	// References: ActivePlayer (0x800F9C80)
	// References: ReadedBufferQueue (0x800FB1E0)
	// References: gMovieErrorToggle (0x44561380)
	// References: FreeReadBufferQueue (0x800FB1C0)
}

void ReadThreadCancel()
{
	// References: ReadThreadCreated (0x40561380)
	// References: ReadThread (0x800FB298)
}

void ReadThreadStart()
{
	// References: ReadThread (0x800FB298)
	// References: ReadThreadCreated (0x40561380)
}

int CreateReadThread(long priority)
{
	// References: ReadThreadCreated (0x40561380)
	// References: ReadedBufferMessage2 (0x70B20F80)
	// References: ReadedBufferQueue2 (0xB20F80)
	// References: ReadedBufferMessage (0x48B20F80)
	// References: ReadedBufferQueue (0x800FB1E0)
	// References: FreeReadBufferMessage (0x20B20F80)
	// References: FreeReadBufferQueue (0x800FB1C0)
	// References: ReadThreadStack (0x800FB5B0)
	// References: ReadThread (0x800FB298)
}

void movieReset(int IPL, int forceMenu);

// size: 0xC
struct PADStatus
{
	unsigned short button; // 0x0
	signed char stickX; // 0x2
	signed char stickY; // 0x3
	signed char substickX; // 0x4
	signed char substickY; // 0x5
	unsigned char triggerLeft; // 0x6
	unsigned char triggerRight; // 0x7
	unsigned char analogA; // 0x8
	unsigned char analogB; // 0x9
	signed char err; // 0xA
};

// size: 0x1E
struct __anon_0x171A2
{
	PADStatus pst; // 0x0
	unsigned short buttonDown; // 0xC
	unsigned short buttonUp; // 0xE
	unsigned short dirs; // 0x10
	unsigned short dirsNew; // 0x12
	unsigned short dirsReleased; // 0x14
	signed short stickDeltaX; // 0x16
	signed short stickDeltaY; // 0x18
	signed short substickDeltaX; // 0x1A
	signed short substickDeltaY; // 0x1C
};

// Location: 0x58271380
__anon_0x171A2 DemoPad[4];

int movieTestReset(int IPL, int forceMenu)
{
	unsigned int bFlag;
	unsigned int nTick;
	// References: gnTickReset (0x50561380)
	// References: gbReset (0x4C561380)
	// References: DemoPad (0x58271380)
}

int movieDVDRead(DVDFileInfo *pFileInfo, void *anData, long nSizeRead, long nOffset)
{
	int nStatus;
	int bRetry;
	// References: gMovieErrorToggle (0x44561380)
}

// size: 0x4
enum __anon_0x17564
{
	M_M_NONE = 4294967295,
	M_M_DISK_COVER_OPEN = 0,
	M_M_DISK_WRONG_DISK = 1,
	M_M_DISK_READING_DISK = 2,
	M_M_DISK_FATAL_ERROR = 3,
	M_M_DISK_RETRY_ERROR = 4,
	M_M_DISK_NO_DISK = 5,
	M_M_DISK_DEFAULT_ERROR = 6
};

int movieDVDShowError(int nStatus)
{
	__anon_0x17564 nMessage;
	// References: gnTickReset (0x50561380)
	// References: gbReset (0x4C561380)
	// References: DemoPad (0x58271380)
	// References: toggle$184 (0x48561380)
	// References: gMovieErrorToggle (0x44561380)
}

// Location: 0xB80D80
unsigned char gcoverOpen[];

// Location: 0x60570E80
unsigned char gwrongDisk[];

// Location: 0x800E7680
unsigned char greadingDisk[];

// Location: 0xE80
unsigned char gretryErr[];

// Location: 0x60240E80
unsigned char gfatalErr[];

// Location: 0x800DE0E0
unsigned char gnoDisk[];

int movieDrawErrorMessage(__anon_0x17564 movieMessage)
{
	// References: gfatalErr (0x60240E80)
	// References: gnoDisk (0x800DE0E0)
	// References: gretryErr (0xE80)
	// References: greadingDisk (0x800E7680)
	// References: gwrongDisk (0x60570E80)
	// References: gcoverOpen (0xB80D80)
}

// Location: 0x60990E80
signed short Vert_s16[];

// Location: 0x9A0E80
unsigned long Colors_u32[];

// Location: 0x209A0E80
unsigned char TexCoords_u8[];

// size: 0x4
enum _GXTexWrapMode
{
	GX_CLAMP = 0,
	GX_REPEAT = 1,
	GX_MIRROR = 2,
	GX_MAX_TEXWRAPMODE = 3
};

// size: 0x4
enum _GXTexFilter
{
	GX_NEAR = 0,
	GX_LINEAR = 1,
	GX_NEAR_MIP_NEAR = 2,
	GX_LIN_MIP_NEAR = 3,
	GX_NEAR_MIP_LIN = 4,
	GX_LIN_MIP_LIN = 5
};

// size: 0x24
struct __anon_0x17AF5
{
	unsigned short height; // 0x0
	unsigned short width; // 0x2
	unsigned long format; // 0x4
	char *data; // 0x8
	_GXTexWrapMode wrapS; // 0xC
	_GXTexWrapMode wrapT; // 0x10
	_GXTexFilter minFilter; // 0x14
	_GXTexFilter magFilter; // 0x18
	float LODBias; // 0x1C
	unsigned char edgeLODEnable; // 0x20
	unsigned char minLOD; // 0x21
	unsigned char maxLOD; // 0x22
	unsigned char unpacked; // 0x23
};

// size: 0x4
enum _GXTlutFmt
{
	GX_TL_IA8 = 0,
	GX_TL_RGB565 = 1,
	GX_TL_RGB5A3 = 2,
	GX_MAX_TLUTFMT = 3
};

// size: 0xC
struct __anon_0x17D50
{
	unsigned short numEntries; // 0x0
	unsigned char unpacked; // 0x2
	unsigned char pad8; // 0x3
	_GXTlutFmt format; // 0x4
	char *data; // 0x8
};

// size: 0x8
struct __anon_0x17E1C
{
	__anon_0x17AF5 *textureHeader; // 0x0
	__anon_0x17D50 *CLUTHeader; // 0x4
};

// size: 0xC
struct __anon_0x17E8D
{
	unsigned long versionNumber; // 0x0
	unsigned long numDescriptors; // 0x4
	__anon_0x17E1C *descriptorArray; // 0x8
};

// size: 0x20
struct _GXTexObj
{
	unsigned long dummy[8]; // 0x0
};

// size: 0x4
struct _GXColor
{
	unsigned char r; // 0x0
	unsigned char g; // 0x1
	unsigned char b; // 0x2
	unsigned char a; // 0x3
};

int movieDrawImage(__anon_0x17E8D *tpl, signed short nX0, signed short nY0)
{
	_GXTexObj texObj;
	_GXColor color;
	float identity_mtx[3][4];
	float g2DviewMtx[3][4];
	float g2[3][4];
	// References: TexCoords_u8 (0x209A0E80)
	// References: Colors_u32 (0x9A0E80)
	// References: Vert_s16 (0x60990E80)
	// References: gOrthoMtx (0x800FC5B0)
}

int movieGXInit()
{
	int i;
	_GXColor GX_DEFAULT_BG;
	_GXColor BLACK;
	_GXColor WHITE;
	float identity_mtx[3][4];
}

