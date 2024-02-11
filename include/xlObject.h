#ifndef _XL_OBJECT_H
#define _XL_OBJECT_H

typedef struct _XL_OBJECTTYPE _XL_OBJECTTYPE;

// size: 0x10
struct _XL_OBJECTTYPE {
    char* szName; // 0x0
    int nSizeObject; // 0x4
    _XL_OBJECTTYPE* pClassBase; // 0x8
    int (*pfEvent)(void* /* unknown0 */, int /* unknown1 */, void* /* unknown2 */); // 0xC
};

int xlObjectReset(void);
int xlObjectSetup(void);
int xlObjectEvent(void* pObject, int nEvent, void* pArgument);
int xlObjectTest(void* pObject, _XL_OBJECTTYPE* pType);
int xlObjectFree(void** ppObject);
int xlObjectMake(void** ppObject, void* pArgument, _XL_OBJECTTYPE* pType);

#endif
