/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: priority_queue.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 优先队列（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_PRIORITY_QUEUE_H
#define DTL_PRIORITY_QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "heap.h"

typedef struct priority_queue {
	heap_t *heap;
} priority_queue_t;

extern priority_queue_t *priority_queue_init(size_t size,
	int (*compar)(const void *, const void *));
extern void priority_queue_free(priority_queue_t *this);

extern void *priority_queue_top(priority_queue_t *this);

extern bool priority_queue_empty(priority_queue_t *this);
extern size_t priority_queue_size(priority_queue_t *this);

extern void priority_queue_clear(priority_queue_t *this);
extern void priority_queue_push(priority_queue_t *this, const void *data);
extern void priority_queue_pop(priority_queue_t *this);

#endif // DTL_PRIORITY_QUEUE_H

