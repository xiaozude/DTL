/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: priority_queue.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 优先队列（容器适配器）
 *
 *****************************************************************/

#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

priority_queue_t *priority_queue_init(size_t size, int (*compar)(const void *, const void *))
{
	assert(size > 0);
	assert(compar != NULL);
	
	priority_queue_t *this = NULL;
	if ((this = (priority_queue_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->heap = heap_init(size, compar);
	return this;
}

void priority_queue_free(priority_queue_t *this)
{
	if (this == NULL) {
		return;
	}
	
	heap_free(this->heap);
	free(this);
}

void *priority_queue_top(priority_queue_t *this)
{
	assert(this != NULL);

	return heap_top(this->heap);
}

bool priority_queue_empty(priority_queue_t *this)
{
	assert(this != NULL);

	return heap_empty(this->heap);
}

size_t priority_queue_size(priority_queue_t *this)
{
	assert(this != NULL);

	return heap_size(this->heap);
}

void priority_queue_clear(priority_queue_t *this)
{
	assert(this != NULL);
	
	heap_clear(this->heap);
}

void priority_queue_push(priority_queue_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);
	
	heap_push(this->heap, data);
}

void priority_queue_pop(priority_queue_t *this)
{
	assert(this != NULL);
	assert(!priority_queue_empty(this));
	
	heap_pop(this->heap);
}

