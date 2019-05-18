/*! \file */
#ifndef _CSTD_LIB_H_
#define _CSTD_LIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "list.h"
#include "tree.h"

/*!
 \def HEAPIFY(...) safe_memcpy(malloc(sizeof(__VA_ARGS__)),&__VA_ARGS__, sizeof(__VA_ARGS__))
 Allocates memory for the given value and copies the given value to said memory.
*/

#define HEAPIFY(...) safe_memcpy(malloc(sizeof(__VA_ARGS__)),&__VA_ARGS__, sizeof(__VA_ARGS__));

/*! \fn void * safe_memcpy(void * destination, const void* source, const size_t size)
    \brief Safe version of memcpy

    Should memcpy recive a null pointer, for either destination or source, it will produce a null pointer expection/segfault.
    This function works around this fact, by returning NULL should wither destination or souce be NULL.

    \param destination The destination of the for the copy.
    \param source The source from which to copy the data.
    \param size The size of the data which to copy.
*/

void * safe_memcpy(void * destination, const void* source, const size_t size);

#endif /* end of include guard: _CSTD_LIB_H_ */
