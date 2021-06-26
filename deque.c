/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: deque.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 双端队列（容器适配器）
 *
 *****************************************************************/

#include "deque.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

deque_t *deque_init(size_t size)
{
	assert(size > 0);

	deque_t *this = NULL;
	if ((this = (deque_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->list = list_init(size);
	return this;
}

void deque_free(deque_t *this)
{
	if (this == NULL) {
		return;
	}

	list_free(this->list);
	free(this);
}

void *deque_front(deque_t *this)
{
	assert(this != NULL);

	return list_front(this->list);
}

void *deque_back(deque_t *this)
{
	assert(this != NULL);

	return list_back(this->list);
}

bool deque_empty(deque_t *this)
{
	assert(this != NULL);

	return list_empty(this->list);
}

size_t deque_size(deque_t *this)
{
	assert(this != NULL);

	return list_size(this->list);
}

void deque_clear(deque_t *this)
{
	assert(this != NULL);

	list_clear(this->list);
}

void deque_push_front(deque_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	list_push_front(this->list, data);
}

void deque_pop_front(deque_t *this)
{
	assert(this != NULL);
	assert(!deque_empty(this));
	
	list_pop_front(this->list);
}

void deque_push_back(deque_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	list_push_back(this->list, data);
}

void deque_pop_back(deque_t *this)
{
	assert(this != NULL);
	assert(!deque_empty(this));

	list_pop_back(this->list);
}

