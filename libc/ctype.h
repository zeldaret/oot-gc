#ifndef _CTYPE_H_
#define _CTYPE_H_

#include "dolphin/types.h"

extern const u8 __ctype_map[];
extern const u8 __lower_map[];
extern const u8 __upper_map[];

#define __control_char 0x01
#define __motion_char 0x02
#define __space_char 0x04
#define __punctuation 0x08
#define __digit 0x10
#define __hex_digit 0x20
#define __lower_case 0x40
#define __upper_case 0x80

#define __letter (__lower_case | __upper_case)
#define __alphanumeric (__letter | __digit)
#define __graphic (__alphanumeric | __punctuation)
#define __printable (__graphic | __space_char)
#define __whitespace (__motion_char | __space_char)
#define __control (__motion_char | __control_char)
#define __zero_fill(c) ((int)(u8)(c))

static inline int isalnum(int c) { return __ctype_map[__zero_fill(c)] & __alphanumeric; }
static inline int isalpha(int c) { return __ctype_map[__zero_fill(c)] & __letter; }
static inline int iscntrl(int c) { return __ctype_map[__zero_fill(c)] & __control; }
static inline int isdigit(int c) { return __ctype_map[__zero_fill(c)] & __digit; }
static inline int isgraph(int c) { return __ctype_map[__zero_fill(c)] & __graphic; }
static inline int islower(int c) { return __ctype_map[__zero_fill(c)] & __lower_case; }
static inline int isprint(int c) { return __ctype_map[__zero_fill(c)] & __printable; }
static inline int ispunct(int c) { return __ctype_map[__zero_fill(c)] & __punctuation; }
static inline int isspace(int c) { return __ctype_map[__zero_fill(c)] & __whitespace; }
static inline int isupper(int c) { return __ctype_map[__zero_fill(c)] & __upper_case; }
static inline int isxdigit(int c) { return __ctype_map[__zero_fill(c)] & __hex_digit; }
static inline int iswblank(int c) { return ((c == (int)L' ') || (c == (int)L'\t')); }

int tolower(int c);
int toupper(int c);

#endif
