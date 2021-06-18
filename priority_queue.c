/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: priority_queue.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 优先队列（容器适配器）
 *
 *****************************************************************/

#include "priority_queue.h"
#include <assert.h>

void priority_queue_init(priority_queue_t *pqueue, size_t size, int (*compar)(const void *, const void *))
{
	assert(pqueue != NULL);
	assert(size > 0);
	
	heap_init(&pqueue->heap, size, compar);
}

void priority_queue_free(priority_queue_t *pqueue)
{
	assert(pqueue != NULL);
	
	heap_free(&pqueue->heap);
}

void *priority_queue_top(priority_queue_t queue)
{
	return heap_top(queue.heap);
}

bool priority_queue_empty(priority_queue_t queue)
{
	return heap_empty(queue.heap);
}

size_t priority_queue_size(priority_queue_t queue)
{
	return heap_size(queue.heap);
}

void priority_queue_clear(priority_queue_t *pqueue)
{
	assert(pqueue != NULL);
	
	return heap_clear(&pqueue->heap);
}

void priority_queue_push(priority_queue_t *pqueue, const void *data)
{
	assert(pqueue != NULL);
	assert(data != NULL);
	
	heap_push(&pqueue->heap, data);
}

void priority_queue_pop(priority_queue_t *pqueue)
{
	assert(pqueue != NULL);
	
	heap_pop(&pqueue->heap);
}

