/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: stack.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 栈（容器适配器）
 *
 *****************************************************************/

#include "stack.h"
#include <assert.h>

void stack_init(stack_t *pstack, size_t size)
{
	assert(pstack != NULL);
	assert(size > 0);

	vector_init(&pstack->vector, size);
}

void stack_free(stack_t *pstack)
{
	assert(pstack != NULL);

	vector_free(&pstack->vector);
}

void *stack_top(stack_t stack)
{
	return vector_back(stack.vector);
}

bool stack_empty(stack_t stack)
{
	return vector_empty(stack.vector);
}

size_t stack_size(stack_t stack)
{
	return vector_size(stack.vector);
}

void stack_clear(stack_t *pstack)
{
	assert(pstack != NULL);

	vector_clear(&pstack->vector);
}

void stack_push(stack_t *pstack, const void *data)
{
	assert(pstack != NULL);
	assert(data != NULL);

	vector_push_back(&pstack->vector, data);
}

void stack_pop(stack_t *pstack)
{
	assert(pstack != NULL);

	vector_pop_back(&pstack->vector);
}

