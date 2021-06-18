/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: heap.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 堆（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_HEAP_H
#define DTL_HEAP_H

#include <stdbool.h>
#include <stddef.h>
#include "vector.h"

typedef struct heap {
	vector_t vector;
	int (*compar)(const void *, const void *);
} heap_t;

extern void heap_init(heap_t *phead, size_t size,
		int (*compar)(const void *, const void *));
extern void heap_free(heap_t *pheap);

extern void *heap_top(heap_t heap);

extern bool heap_empty(heap_t heap);
extern size_t heap_size(heap_t heap);

extern void heap_clear(heap_t *pheap);
extern void heap_push(heap_t *pheap, const void *data);
extern void heap_pop(heap_t *pheap);

#endif // DTL_HEAP_H

