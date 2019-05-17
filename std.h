#ifndef _CSTD_LIB_H_
#define _CSTD_LIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define HEAPIFY(...) safe_memcpy(malloc(sizeof(__VA_ARGS__)),&__VA_ARGS__, sizeof(__VA_ARGS__));

void * safe_memcpy(void *, const void*, const size_t);

#endif /* end of include guard: _CSTD_LIB_H_ */
