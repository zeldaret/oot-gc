// Local to compilation unit
// Location: 0x800EA1E8
static unsigned short VolumeTable[128];

// Local to compilation unit
// Location: 0x18561380
static int Initialized;

// Local to compilation unit
// Location: 0x800F96E0
static long WorkBuffer[16];

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
// Location: 0x20970F80
static OSMessageQueue PrepareReadyQueue;

// Local to compilation unit
// Location: 0x40970F80
static OSMessageQueue UsedTextureSetQueue;

// Local to compilation unit
// Location: 0x1C561380
static void *PrepareReadyMessage;

// Local to compilation unit
// Location: 0x60970F80
static void *UsedTextureSetMessage[3];

// Local to compilation unit
// Location: 0x20561380
static void (*OldVIPostCallback)(unsigned long /* unknown0 */);

// Local to compilation unit
// Location: 0x800F9780
static signed short SoundBuffer[2][320];

// Local to compilation unit
// Location: 0x24561380
static long SoundBufferIndex;

// Local to compilation unit
// Location: 0x28561380
static void (*OldAIDCallback)();

// Local to compilation unit
// Location: 0x2C561380
static signed short *LastAudioBuffer;

// Local to compilation unit
// Location: 0x30561380
static signed short *CurAudioBuffer;

// Local to compilation unit
// Location: 0x34561380
static long AudioSystem;

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
struct __anon_0x10576
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
struct __anon_0x107A2
{
	unsigned long numComponents; // 0x0
	unsigned char frameComp[16]; // 0x4
};

// size: 0xC
struct __anon_0x1080A
{
	unsigned long xSize; // 0x0
	unsigned long ySize; // 0x4
	unsigned long videoType; // 0x8
};

// size: 0x10
struct __anon_0x1088A
{
	unsigned long sndChannels; // 0x0
	unsigned long sndFrequency; // 0x4
	unsigned long sndNumSamples; // 0x8
	unsigned long sndNumTracks; // 0xC
};

// size: 0x10
struct __anon_0x10944
{
	unsigned char *ytexture; // 0x0
	unsigned char *utexture; // 0x4
	unsigned char *vtexture; // 0x8
	long frameNumber; // 0xC
};

// size: 0xC
struct __anon_0x109FA
{
	signed short *buffer; // 0x0
	signed short *curPtr; // 0x4
	unsigned long validSample; // 0x8
};

// size: 0xC
struct __anon_0x10A84
{
	unsigned char *ptr; // 0x0
	long frameNumber; // 0x4
	int isValid; // 0x8
};

// size: 0x1D0
struct __anon_0x10B6F
{
	DVDFileInfo fileInfo; // 0x0
	__anon_0x10576 header; // 0x3C
	__anon_0x107A2 compInfo; // 0x6C
	__anon_0x1080A videoInfo; // 0x80
	__anon_0x1088A audioInfo; // 0x8C
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
	__anon_0x10944 *dispTextureSet; // 0xF8
	__anon_0x109FA *playAudioBuffer; // 0xFC
	__anon_0x10A84 readBuffer[10]; // 0x100
	__anon_0x10944 textureSet[3]; // 0x178
	__anon_0x109FA audioBuffer[3]; // 0x1A8
};

// Location: 0x800F9C80
__anon_0x10B6F ActivePlayer;

int THPPlayerInit(long audioSystem)
{
	int old;
	// References: Initialized (0x18561380)
	// References: SoundBufferIndex (0x24561380)
	// References: SoundBuffer (0x800F9780)
	// References: AudioSystem (0x34561380)
	// References: OldAIDCallback (0x28561380)
	// References: CurAudioBuffer (0x30561380)
	// References: LastAudioBuffer (0x2C561380)
	// References: UsedTextureSetMessage (0x60970F80)
	// References: UsedTextureSetQueue (0x40970F80)
	// References: ActivePlayer (0x800F9C80)
}

void THPPlayerQuit()
{
	int old;
	// References: Initialized (0x18561380)
	// References: OldAIDCallback (0x28561380)
}

int THPPlayerOpen(char *fileName, int onMemory)
{
	long offset;
	long i;
	// References: ActivePlayer (0x800F9C80)
	// References: WorkBuffer (0x800F96E0)
	// References: Initialized (0x18561380)
}

int THPPlayerClose()
{
	// References: ActivePlayer (0x800F9C80)
}

unsigned long THPPlayerCalcNeedMemory()
{
	unsigned long size;
	// References: ActivePlayer (0x800F9C80)
}

int THPPlayerSetBuffer(unsigned char *buffer)
{
	unsigned long i;
	unsigned char *ptr;
	unsigned long ysize;
	unsigned long uvsize;
	// References: ActivePlayer (0x800F9C80)
}

// Local to compilation unit
static void InitAllMessageQueue()
{
	long i;
	__anon_0x10A84 *readBuffer;
	__anon_0x10944 *textureSet;
	__anon_0x109FA *audioBuffer;
	// References: PrepareReadyMessage (0x1C561380)
	// References: PrepareReadyQueue (0x20970F80)
	// References: ActivePlayer (0x800F9C80)
}

int WaitUntilPrepare()
{
	void *msg;
	// References: PrepareReadyQueue (0x20970F80)
}

void PrepareReady(int flag)
{
	// References: PrepareReadyQueue (0x20970F80)
}

int THPPlayerPrepare(long frameNum, long playFlag, long audioTrack)
{
	long offset;
	unsigned char *ptr;
	// References: OldVIPostCallback (0x20561380)
	// References: ActivePlayer (0x800F9C80)
	// References: PrepareReadyQueue (0x20970F80)
	// References: WorkBuffer (0x800F96E0)
}

int THPPlayerPlay()
{
	// References: ActivePlayer (0x800F9C80)
}

void THPPlayerStop()
{
	void *texture;
	// References: ActivePlayer (0x800F9C80)
	// References: OldVIPostCallback (0x20561380)
}

int THPPlayerPause()
{
	// References: ActivePlayer (0x800F9C80)
}

int THPPlayerSkip()
{
	int old;
	long frameNumber;
	long audioGet;
	long videoGet;
	// References: ActivePlayer (0x800F9C80)
}

// Local to compilation unit
static void PlayControl(unsigned long retraceCount)
{
	long diff;
	long frameNumber;
	__anon_0x10944 *textureSet;
	// References: ActivePlayer (0x800F9C80)
	// References: OldVIPostCallback (0x20561380)
}

// Local to compilation unit
static int ProperTimingForStart()
{
	// References: ActivePlayer (0x800F9C80)
}

// Local to compilation unit
static int ProperTimingForGettingNextFrame()
{
	long frameRate;
	// References: ActivePlayer (0x800F9C80)
}

// size: 0x4
enum __anon_0x119E9
{
	VI_TVMODE_NTSC_INT = 0,
	VI_TVMODE_NTSC_DS = 1,
	VI_TVMODE_NTSC_PROG = 2,
	VI_TVMODE_PAL_INT = 4,
	VI_TVMODE_PAL_DS = 5,
	VI_TVMODE_EURGB60_INT = 20,
	VI_TVMODE_EURGB60_DS = 21,
	VI_TVMODE_MPAL_INT = 8,
	VI_TVMODE_MPAL_DS = 9,
	VI_TVMODE_DEBUG_INT = 12,
	VI_TVMODE_DEBUG_PAL_INT = 16,
	VI_TVMODE_DEBUG_PAL_DS = 17
};

// size: 0x4
enum __anon_0x11B35
{
	VI_XFBMODE_SF = 0,
	VI_XFBMODE_DF = 1
};

// size: 0x3C
struct _GXRenderModeObj
{
	__anon_0x119E9 viTVmode; // 0x0
	unsigned short fbWidth; // 0x4
	unsigned short efbHeight; // 0x6
	unsigned short xfbHeight; // 0x8
	unsigned short viXOrigin; // 0xA
	unsigned short viYOrigin; // 0xC
	unsigned short viWidth; // 0xE
	unsigned short viHeight; // 0x10
	__anon_0x11B35 xFBmode; // 0x14
	unsigned char field_rendering; // 0x18
	unsigned char aa; // 0x19
	unsigned char sample_pattern[12][2]; // 0x1A
	unsigned char vfilter[7]; // 0x32
};

long THPPlayerDrawCurrentFrame(_GXRenderModeObj *rmode, unsigned long x, unsigned long y, unsigned long polygonW, unsigned long polygonH)
{
	// References: ActivePlayer (0x800F9C80)
}

int THPPlayerGetVideoInfo(__anon_0x1080A *videoInfo)
{
	// References: ActivePlayer (0x800F9C80)
}

int THPPlayerGetAudioInfo(__anon_0x1088A *audioInfo)
{
	// References: ActivePlayer (0x800F9C80)
}

float THPPlayerGetFrameRate()
{
	// References: ActivePlayer (0x800F9C80)
}

unsigned long THPPlayerGetTotalFrame()
{
	// References: ActivePlayer (0x800F9C80)
}

long THPPlayerGetState()
{
	// References: ActivePlayer (0x800F9C80)
}

// Local to compilation unit
static void PushUsedTextureSet(void *buffer)
{
	// References: UsedTextureSetQueue (0x40970F80)
}

void *PopUsedTextureSet()
{
	void *msg;
	// References: UsedTextureSetQueue (0x40970F80)
}

void THPPlayerDrawDone()
{
	void *textureSet;
	// References: UsedTextureSetQueue (0x40970F80)
	// References: Initialized (0x18561380)
}

// Local to compilation unit
static void THPAudioMixCallback()
{
	int old;
	// References: SoundBufferIndex (0x24561380)
	// References: SoundBuffer (0x800F9780)
	// References: CurAudioBuffer (0x30561380)
	// References: OldAIDCallback (0x28561380)
	// References: LastAudioBuffer (0x2C561380)
	// References: AudioSystem (0x34561380)
}

// Local to compilation unit
static void MixAudio(signed short *destination, signed short *source, unsigned long sample)
{
	unsigned long sampleNum;
	unsigned long requestSample;
	unsigned long i;
	long mix;
	signed short *dst;
	signed short *libsrc;
	signed short *thpsrc;
	unsigned short attenuation;
	// References: ActivePlayer (0x800F9C80)
	// References: VolumeTable (0x800EA1E8)
}

int THPPlayerSetVolume(long vol, long time)
{
	int old;
	long samplePerMs;
	// References: ActivePlayer (0x800F9C80)
}

long THPPlayerGetVolume()
{
	// References: ActivePlayer (0x800F9C80)
}

