/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: heap.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 堆（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_HEAP_H
#define DTL_HEAP_H

#include <stdbool.h>
#include <stddef.h>
#include "vector.h"

typedef struct heap {
	vector_t *vector;
	int (*compar)(const void *, const void *);
} heap_t;

extern heap_t *heap_init(size_t size,
	int (*compar)(const void *, const void *));
extern void heap_free(heap_t *this);

extern void *heap_top(heap_t *this);

extern bool heap_empty(heap_t *this);
extern size_t heap_size(heap_t *this);

extern void heap_clear(heap_t *this);
extern void heap_push(heap_t *this, const void *data);
extern void heap_pop(heap_t *this);

#endif // DTL_HEAP_H

