/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: stack.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 栈（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_STACK_H
#define DTL_STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "deque.h"

typedef struct stack {
	deque_t *deque;
} stack_t;

extern stack_t *stack_init(size_t size);
extern void stack_free(stack_t *this);

extern void *stack_top(stack_t *this);

extern bool stack_empty(stack_t *this);
extern size_t stack_size(stack_t *this);

extern void stack_clear(stack_t *this);
extern void stack_push(stack_t *this, const void *data);
extern void stack_pop(stack_t *this);

#endif // DTL_STACK_H

