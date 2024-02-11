// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// Local to compilation unit
// Location: 0x801355A8
static unsigned int *gpHeap;

// Local to compilation unit
// Location: 0x801355AC
static unsigned int *gpHeapBlockFirst;

// Local to compilation unit
// Location: 0x801355B0
static unsigned int *gpHeapBlockLast;

// Local to compilation unit
// Location: 0x801355B4
static int gnHeapTakeCount;

// Local to compilation unit
// Location: 0x801355B8
static int gnHeapFreeCount;

// Local to compilation unit
// Location: 0x801355BC
static int gnHeapTakeCacheCount;

// Local to compilation unit
// Location: 0x800F3FB0
static unsigned int  *gapHeapBlockCache[11][32];

// Location: 0x801355C0
int gnSizeHeap;

int xlHeapReset()
{
	int nBlockSize;
	// References: gpHeapBlockLast (0x801355B0)
	// References: gpHeapBlockFirst (0x801355AC)
	// References: gpHeap (0x801355A8)
	// References: gnSizeHeap (0x801355C0)
}

int xlHeapSetup(void *pHeap, int nSizeBytes)
{
	int nSizeWords;
	// References: gpHeapBlockLast (0x801355B0)
	// References: gpHeapBlockFirst (0x801355AC)
	// References: gpHeap (0x801355A8)
	// References: gnSizeHeap (0x801355C0)
}

int xlHeapGetFree(int *pnFreeBytes)
{
	int nBlockSize;
	int nFree;
	int nCount;
	unsigned int *pBlock;
	unsigned int nBlock;
	// References: gpHeapBlockLast (0x801355B0)
	// References: gpHeapBlockFirst (0x801355AC)
}

int xlHeapFill32(void *pHeap, int nByteCount, unsigned int nData)
{
	unsigned int *pnTarget;
}

int xlHeapFill16(void *pHeap, int nByteCount, unsigned short nData)
{
	unsigned short *pnTarget;
}

int xlHeapFill8(void *pHeap, int nByteCount, unsigned char nData)
{
	unsigned char *pnTarget;
}

int xlHeapCopy(void *pHeapTarget, void *pHeapSource, int nByteCount)
{
	unsigned char *pSource8;
	unsigned char *pTarget8;
	unsigned int *pSource32;
	unsigned int *pTarget32;
}

int xlHeapCompact()
{
	int nCount;
	int nBlockLarge;
	int nBlockSize;
	int nBlockNextSize;
	int anBlockLarge[6];
	unsigned int nBlock;
	unsigned int *pBlock;
	unsigned int *pBlockPrevious;
	unsigned int nBlockNext;
	unsigned int *pBlockNext;
	// References: gpHeapBlockFirst (0x801355AC)
}

int xlHeapTest(void *pHeap)
{
	unsigned int *pBlock;
}

int xlHeapFree(void *ppHeap)
{
	int nBlockSize;
	int nBlockNextSize;
	unsigned int *pBlock;
	unsigned int *pBlockNext;
	// References: gnHeapFreeCount (0x801355B8)
	// References: gpHeapBlockLast (0x801355B0)
	// References: gpHeapBlockFirst (0x801355AC)
}

int xlHeapTake(void *ppHeap, int nByteCount)
{
	int bValid;
	unsigned int nSizeExtra;
	unsigned int iTry;
	int nSize;
	int nBlockSize;
	int nBlockNextSize;
	int nBlockNextNextSize;
	unsigned int nBlock;
	unsigned int *pBlock;
	unsigned int *pBlockNext;
	unsigned int *pBlockNextNext;
	// References: gnHeapTakeCount (0x801355B4)
	// References: gpHeapBlockLast (0x801355B0)
	// References: gpHeapBlockFirst (0x801355AC)
}

// Local to compilation unit
static int xlHeapFindUpperBlock(int nSize, unsigned int **ppBlock, int *pnBlockSize)
{
	int nBlockSize;
	unsigned int nBlock;
	unsigned int *pBlock;
	unsigned int *pBlockBest;
	unsigned int *pBlockNext;
	// References: gpHeapBlockLast (0x801355B0)
	// References: gpHeapBlockFirst (0x801355AC)
}

// Local to compilation unit
static int xlHeapBlockCacheReset()
{
	int nBlockSize;
	unsigned int *pBlock;
	unsigned int nBlock;
	// References: gpHeapBlockFirst (0x801355AC)
	// References: gapHeapBlockCache (0x800F3FB0)
	// References: gnHeapFreeCount (0x801355B8)
	// References: gnHeapTakeCount (0x801355B4)
	// References: gnHeapTakeCacheCount (0x801355BC)
}

// Local to compilation unit
static int xlHeapBlockCacheClear(unsigned int *pBlock)
{
	int nSize;
	int nBlock;
	int nBlockSize;
	// References: gapHeapBlockCache (0x800F3FB0)
}

// Local to compilation unit
static int xlHeapBlockCacheAdd(unsigned int *pBlock)
{
	int nSize;
	int nBlock;
	int nBlockSize;
	int nBlockCachedSize;
	unsigned int *pBlockCached;
	// References: gapHeapBlockCache (0x800F3FB0)
}

// Local to compilation unit
static int xlHeapBlockCacheGet(int nSize, unsigned int **ppBlock, int *pnBlockSize)
{
	int nBlockCachedSize;
	int nBlock;
	int nBlockSize;
	int nBlockBest;
	int nBlockBestSize;
	unsigned int *pBlock;
	// References: gnHeapTakeCacheCount (0x801355BC)
	// References: gapHeapBlockCache (0x800F3FB0)
}

void xlHeapStatisticsReset()
{
	// References: gnHeapFreeCount (0x801355B8)
	// References: gnHeapTakeCount (0x801355B4)
	// References: gnHeapTakeCacheCount (0x801355BC)
}

void xlHeapShowStatistics();

int xlHeapTestBlock(unsigned int nBlock);

