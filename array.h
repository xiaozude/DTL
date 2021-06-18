/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: array.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 静态数组（容器）
 *
 *****************************************************************/

#ifndef DTL_ARRAY_H
#define DTL_ARRAY_H

#include <stdbool.h>
#include <stddef.h>
#include "iterator.h"

typedef struct array {
	size_t size;
	void *elems;
	void *cliff;
	void *start;
	void *finish;
} array_t;

extern void array_init(array_t *parray, size_t size, size_t count);
extern void array_free(array_t *parray);

extern void *array_front(array_t array);
extern void *array_back(array_t array);
extern void *array_index(array_t array, size_t index);

extern bool array_empty(array_t array);
extern size_t array_size(array_t array);

extern iterator_t array_begin(array_t array);
extern iterator_t array_end(array_t array);
extern iterator_t array_rbegin(array_t array);
extern iterator_t array_rend(array_t array);

#endif // DTL_ARRAY_H

