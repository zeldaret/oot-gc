#ifndef _LIMITS_H_
#define _LIMITS_H_

#define SCHAR_MAX 0x7F
#define UCHAR_MAX 0xFFU

#if defined(__MWERKS__) && __option(unsigned_char)
#define CHAR_MIN 0U
#define CHAR_MAX UCHAR_MAX
#else
#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX
#endif

#define SHRT_MAX 0x7FFF
#define USHRT_MAX 0xFFFFU

#define INT_MAX 0x7FFFFFFF
#define UINT_MAX 0xFFFFFFFFU

#define LONG_MAX 0x7FFFFFFFL
#define ULONG_MAX 0xFFFFFFFFUL

#endif
