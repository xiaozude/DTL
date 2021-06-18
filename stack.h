/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: stack.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 栈（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_STACK_H
#define DTL_STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "vector.h"

typedef struct stack {
	vector_t vector;
} stack_t;

extern void stack_init(stack_t *pstack, size_t size);
extern void stack_free(stack_t *pstack);

extern void *stack_top(stack_t stack);

extern bool stack_empty(stack_t stack);
extern size_t stack_size(stack_t stack);

extern void stack_clear(stack_t *pstack);
extern void stack_push(stack_t *pstack, const void *data);
extern void stack_pop(stack_t *pstack);

#endif // DTL_STACK_H

