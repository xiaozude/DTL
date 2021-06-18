/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: vector.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 动态数组（容器）
 *
 *****************************************************************/

#ifndef DTL_VECTOR_H
#define DTL_VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include "iterator.h"

typedef struct vector {
	size_t size;
	void *elems;
	void *cliff;
	void *start;
	void *finish;
} vector_t;

extern void vector_init(vector_t *pvector, size_t size);
extern void vector_free(vector_t *pvector);

extern void *vector_front(vector_t vector);
extern void *vector_back(vector_t vector);
extern void *vector_index(vector_t vector, size_t index);

extern bool vector_empty(vector_t vector);
extern size_t vector_size(vector_t vector);

extern void vector_clear(vector_t *pvector);
extern void vector_insert(vector_t *pvector, size_t index, const void *data);
extern void vector_erase(vector_t *pvector, size_t index);
extern void vector_push_back(vector_t *pvector, const void *data);
extern void vector_pop_back(vector_t *pvector);

extern iterator_t vector_begin(vector_t vector);
extern iterator_t vector_end(vector_t vector);
extern iterator_t vector_rbegin(vector_t vector);
extern iterator_t vector_rend(vector_t vector);

#endif // DTL_VECTOR_H

