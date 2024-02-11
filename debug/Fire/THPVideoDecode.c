// Local to compilation unit
// Location: 0x58561380
static long VideoDecodeThreadCreated;

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
struct OSThreadQueue
{
	OSThread *head; // 0x0
	OSThread *tail; // 0x4
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
// Location: 0x800FC5F0
static OSThread VideoDecodeThread;

// Local to compilation unit
// Location: 0x8C90F80
static unsigned char VideoDecodeThreadStack[4096];

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
// Location: 0x8D90F80
static OSMessageQueue FreeTextureSetQueue;

// Local to compilation unit
// Location: 0x28D90F80
static OSMessageQueue DecodedTextureSetQueue;

// Local to compilation unit
// Location: 0x48D90F80
static void *FreeTextureSetMessage[3];

// Local to compilation unit
// Location: 0x54D90F80
static void *DecodedTextureSetMessage[3];

// Local to compilation unit
// Location: 0x5C561380
static long First;

int CreateVideoDecodeThread(long priority, unsigned char *ptr)
{
	// References: First (0x5C561380)
	// References: VideoDecodeThreadCreated (0x58561380)
	// References: DecodedTextureSetMessage (0x54D90F80)
	// References: DecodedTextureSetQueue (0x28D90F80)
	// References: FreeTextureSetMessage (0x48D90F80)
	// References: FreeTextureSetQueue (0x8D90F80)
	// References: VideoDecodeThreadStack (0x8C90F80)
	// References: VideoDecodeThread (0x800FC5F0)
}

void VideoDecodeThreadStart()
{
	// References: VideoDecodeThread (0x800FC5F0)
	// References: VideoDecodeThreadCreated (0x58561380)
}

void VideoDecodeThreadCancel()
{
	// References: VideoDecodeThreadCreated (0x58561380)
	// References: VideoDecodeThread (0x800FC5F0)
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
struct __anon_0x19428
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
struct __anon_0x19654
{
	unsigned long numComponents; // 0x0
	unsigned char frameComp[16]; // 0x4
};

// size: 0xC
struct __anon_0x196BC
{
	unsigned long xSize; // 0x0
	unsigned long ySize; // 0x4
	unsigned long videoType; // 0x8
};

// size: 0x10
struct __anon_0x1973C
{
	unsigned long sndChannels; // 0x0
	unsigned long sndFrequency; // 0x4
	unsigned long sndNumSamples; // 0x8
	unsigned long sndNumTracks; // 0xC
};

// size: 0x10
struct __anon_0x197F6
{
	unsigned char *ytexture; // 0x0
	unsigned char *utexture; // 0x4
	unsigned char *vtexture; // 0x8
	long frameNumber; // 0xC
};

// size: 0xC
struct __anon_0x198AC
{
	signed short *buffer; // 0x0
	signed short *curPtr; // 0x4
	unsigned long validSample; // 0x8
};

// size: 0x1D0
struct __anon_0x1999C
{
	DVDFileInfo fileInfo; // 0x0
	__anon_0x19428 header; // 0x3C
	__anon_0x19654 compInfo; // 0x6C
	__anon_0x196BC videoInfo; // 0x80
	__anon_0x1973C audioInfo; // 0x8C
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
	__anon_0x197F6 *dispTextureSet; // 0xF8
	__anon_0x198AC *playAudioBuffer; // 0xFC
	__anon_0x19FA4 readBuffer[10]; // 0x100
	__anon_0x197F6 textureSet[3]; // 0x178
	__anon_0x198AC audioBuffer[3]; // 0x1A8
};

// Location: 0x800F9C80
__anon_0x1999C ActivePlayer;

// Local to compilation unit
static void *VideoDecoder()
{
	__anon_0x19FA4 *readBuffer;
	int old;
	// References: ActivePlayer (0x800F9C80)
}

// size: 0xC
struct __anon_0x19FA4
{
	unsigned char *ptr; // 0x0
	long frameNumber; // 0x4
	int isValid; // 0x8
};

// Local to compilation unit
static void *VideoDecoderForOnMemory(void *ptr)
{
	__anon_0x19FA4 readBuffer;
	int old;
	long tmp;
	long size;
	long readFrame;
	// References: VideoDecodeThread (0x800FC5F0)
	// References: ActivePlayer (0x800F9C80)
}

// Local to compilation unit
static void VideoDecode(__anon_0x19FA4 *readBuffer)
{
	__anon_0x197F6 *textureSet;
	unsigned long i;
	unsigned long *compSizePtr;
	unsigned char *ptr;
	int old;
	// References: First (0x5C561380)
	// References: ActivePlayer (0x800F9C80)
	// References: VideoDecodeThread (0x800FC5F0)
}

void *PopFreeTextureSet()
{
	void *msg;
	// References: FreeTextureSetQueue (0x8D90F80)
}

void PushFreeTextureSet(void *buffer)
{
	// References: FreeTextureSetQueue (0x8D90F80)
}

void *PopDecodedTextureSet(long flag)
{
	void *msg;
	// References: DecodedTextureSetQueue (0x28D90F80)
}

void PushDecodedTextureSet(void *buffer)
{
	// References: DecodedTextureSetQueue (0x28D90F80)
}

