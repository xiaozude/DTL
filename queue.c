/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: queue.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 队列（容器适配器）
 *
 *****************************************************************/

#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

queue_t *queue_init(size_t size)
{
	assert(size > 0);

	queue_t *this = NULL;
	if ((this = (queue_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->deque = deque_init(size);
	return this;
}

void queue_free(queue_t *this)
{
	if (this == NULL) {
		return;
	}

	deque_free(this->deque);
	free(this);
}

void *queue_front(queue_t *this)
{
	assert(this != NULL);
	assert(!queue_empty(this));

	return deque_front(this->deque);
}

void *queue_back(queue_t *this)
{
	assert(this != NULL);
	assert(!queue_empty(this));

	return deque_back(this->deque);
}

bool queue_empty(queue_t *this)
{
	assert(this != NULL);

	return deque_empty(this->deque);
}

size_t queue_size(queue_t *this)
{
	assert(this != NULL);

	return deque_size(this->deque);
}

void queue_clear(queue_t *this)
{
	assert(this != NULL);

	deque_clear(this->deque);
}

void queue_push(queue_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	deque_push_back(this->deque, data);
}

void queue_pop(queue_t *this)
{
	assert(this != NULL);
	assert(!queue_empty(this));

	deque_pop_front(this->deque);
}

