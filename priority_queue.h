/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: priority_queue.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 优先队列（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_PRIORITY_QUEUE_H
#define DTL_PRIORITY_QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "heap.h"

typedef struct priority_queue {
	heap_t heap;
} priority_queue_t;

extern void priority_queue_init(priority_queue_t *pqueue, size_t size,
		int (*compar)(const void *, const void *));
extern void priority_queue_free(priority_queue_t *pqueue);

extern void *priority_queue_top(priority_queue_t queue);

extern bool priority_queue_empty(priority_queue_t queue);
extern size_t priority_queue_size(priority_queue_t queue);

extern void priority_queue_clear(priority_queue_t *pqueue);
extern void priority_queue_push(priority_queue_t *pqueue, const void *data);
extern void priority_queue_pop(priority_queue_t *pqueue);

#endif // DTL_PRIORITY_QUEUE_H

