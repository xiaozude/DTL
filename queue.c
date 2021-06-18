/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: queue.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 队列（容器适配器）
 *
 *****************************************************************/

#include "queue.h"
#include <assert.h>

void queue_init(queue_t *pqueue, size_t size)
{
	assert(pqueue != NULL);
	assert(size > 0);

	deque_init(&pqueue->deque, size);
}

void queue_free(queue_t *pqueue)
{
	assert(pqueue != NULL);

	deque_free(&pqueue->deque);
}

void *queue_front(queue_t queue)
{
	return deque_front(queue.deque);
}

void *queue_back(queue_t queue)
{
	return deque_back(queue.deque);
}

bool queue_empty(queue_t queue)
{
	return deque_empty(queue.deque);
}

size_t queue_size(queue_t queue)
{
	return deque_size(queue.deque);
}

void queue_clear(queue_t *pqueue)
{
	assert(pqueue != NULL);

	deque_clear(&pqueue->deque);
}

void queue_push(queue_t *pqueue, const void *data)
{
	assert(pqueue != NULL);
	assert(data != NULL);

	deque_push_back(&pqueue->deque, data);
}

void queue_pop(queue_t *pqueue)
{
	assert(pqueue != NULL);

	deque_pop_front(&pqueue->deque);
}

