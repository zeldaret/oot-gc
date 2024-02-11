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
// Location: 0x800F3FA0
static tXL_LIST gListList;

int xlListReset();

int xlListSetup()
{
	// References: gListList (0x800F3FA0)
}

int xlListMoveItemToTail(tXL_LIST *pList, void *pItem)
{
	void *pNode;
	void *pNodeLast;
	void *pNodeItem;
	void *pNodeItemLast;
}

int xlListMoveItemToHead(tXL_LIST *pList, void *pItem)
{
	void *pNode;
	void *pNodeLast;
}

int xlListNodeGetNext(tXL_LIST *pList, void *ppListNode)
{
	// References: gListList (0x800F3FA0)
}

int xlListNodeGetHead(tXL_LIST *pList, void *ppListNode)
{
	// References: gListList (0x800F3FA0)
}

int xlListEnumerate(tXL_LIST *pList, int (*pfCallback)(void */* unknown0 */))
{
	void *pNode;
}

int xlListFindItemIndex(tXL_LIST *pList, int *piItem, void *pItem)
{
	int iItem;
	void *pListNode;
}

int xlListFindItem(tXL_LIST *pList, int iItem, void *ppItem)
{
	int nItemCount;
	void *pListNode;
}

int xlListTestItem(tXL_LIST *pList, void *pItem)
{
	void *pListNode;
	// References: gListList (0x800F3FA0)
}

int xlListFreeItem(tXL_LIST *pList, void *ppItem)
{
	void *pNode;
	void *pNodeNext;
}

int xlListMakeItem(tXL_LIST *pList, void *ppItem)
{
	int nSize;
	void *pListNode;
	void *pNode;
	void *pNodeNext;
}

int xlListTest(tXL_LIST *pList)
{
	void *pNode;
	// References: gListList (0x800F3FA0)
}

int xlListFree(tXL_LIST **ppList)
{
	// References: gListList (0x800F3FA0)
}

int xlListMake(tXL_LIST **ppList, int nItemSize)
{
	// References: gListList (0x800F3FA0)
}

int xlListWipe(tXL_LIST *pList)
{
	void *pNode;
	void *pNodeNext;
}

