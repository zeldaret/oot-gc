#ifndef _STDDEF_H_
#define _STDDEF_H_

typedef unsigned long size_t;
typedef long ptrdiff_t;

#define offsetof(type, member) ((size_t) & (((type*)0)->member))

#endif
