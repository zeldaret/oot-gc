// Location: 0x0
long float _half$localstatic0$sqrtf__Ff;

// Location: 0x0
long float _three$localstatic1$sqrtf__Ff;

// Location: 0x0
long float _half$localstatic0$sqrt__Ff;

// Location: 0x0
long float _three$localstatic1$sqrt__Ff;

// size: 0x10
struct tXL_LIST
{
	int nItemSize; // 0x0
	int nItemCount; // 0x4
	void *pNodeHead; // 0x8
	void *pNodeNext; // 0xC
};

// Local to compilation unit
// Location: 0x801355C8
static tXL_LIST *gpListData;

// size: 0x10
struct _XL_OBJECTTYPE
{
	char *szName; // 0x0
	int nSizeObject; // 0x4
	_XL_OBJECTTYPE *pClassBase; // 0x8
	int (*pfEvent)(void */* unknown0 */, int /* unknown1 */, void */* unknown2 */); // 0xC
};

// size: 0x8
struct __anon_0x5062
{
	tXL_LIST *pList; // 0x0
	_XL_OBJECTTYPE *pType; // 0x4
};

int xlObjectReset()
{
	__anon_0x5062 *pData;
	void *pListNode;
	// References: gpListData (0x801355C8)
}

int xlObjectSetup()
{
	// References: gpListData (0x801355C8)
}

int xlObjectEvent(void *pObject, int nEvent, void *pArgument)
{
	__anon_0x5062 *pData;
	// References: gpListData (0x801355C8)
}

int xlObjectFindType(void *pObject, _XL_OBJECTTYPE **ppType)
{
	__anon_0x5062 *pData;
	// References: gpListData (0x801355C8)
}

int xlObjectTest(void *pObject, _XL_OBJECTTYPE *pType)
{
	__anon_0x5062 *pData;
	// References: gpListData (0x801355C8)
}

int xlObjectFree(void *ppObject)
{
	__anon_0x5062 *pData;
}

int xlObjectMake(void *ppObject, void *pArgument, _XL_OBJECTTYPE *pType)
{
	int bFlag;
	__anon_0x5062 *pData;
	// References: gpListData (0x801355C8)
}

int xlObjectMakeData(__anon_0x5062 **ppData, _XL_OBJECTTYPE *pType)
{
	// References: gpListData (0x801355C8)
}

int xlObjectFindData(__anon_0x5062 **ppData, _XL_OBJECTTYPE *pType)
{
	void *pListNode;
	// References: gpListData (0x801355C8)
}

