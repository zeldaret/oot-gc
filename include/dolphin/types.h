#ifndef _DOLPHIN_TYPES_H_
#define _DOLPHIN_TYPES_H_

typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long int s64;
typedef unsigned long long int u64;

typedef float f32;
typedef double f64;

typedef int BOOL;

#define FALSE 0
#define TRUE 1

#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))

#define INT_MAX 2147483647

#define NULL (void*)0

#endif
