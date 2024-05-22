#ifndef INTRINSICS_H
#define INTRINSICS_H

int __cntlzw(unsigned int n);
double __fabs(double x);
double __frsqrte(double x);
int __rlwimi(int a, int b, int c, int d, int e);
void __sync(void);

#endif
