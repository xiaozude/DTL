/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: stack.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 栈（容器适配器）
 *
 *****************************************************************/

#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

stack_t *stack_init(size_t size)
{
	assert(size > 0);

	stack_t *this = NULL;
	if ((this = (stack_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->deque = deque_init(size);
	return this;
}

void stack_free(stack_t *this)
{
	if (this == NULL) {
		return;
	}

	deque_free(this->deque);
	free(this);
}

void *stack_top(stack_t *this)
{
	assert(this != NULL);

	return deque_back(this->deque);
}

bool stack_empty(stack_t *this)
{
	assert(this != NULL);

	return deque_empty(this->deque);
}

size_t stack_size(stack_t *this)
{
	assert(this != NULL);

	return deque_size(this->deque);
}

void stack_clear(stack_t *this)
{
	assert(this != NULL);

	deque_clear(this->deque);
}

void stack_push(stack_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	deque_push_back(this->deque, data);
}

void stack_pop(stack_t *this)
{
	assert(this != NULL);
	assert(!stack_empty(this));

	deque_pop_back(this->deque);
}

