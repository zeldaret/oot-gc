#ifndef _STRING_H_
#define _STRING_H_

#include "mem_funcs.h"
#include "stddef.h"

size_t strlen(const char* s);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t num);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
char* strncat(char* dest, const char* src, size_t n);

#endif
