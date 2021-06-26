/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: deque.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 双端队列（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_DEQUE_H
#define DTL_DEQUE_H

#include <stdbool.h>
#include <stddef.h>
#include "list.h"

typedef struct deque {
	list_t *list;
} deque_t;

extern deque_t *deque_init(size_t size);
extern void deque_free(deque_t *this);

extern void *deque_front(deque_t *this);
extern void *deque_back(deque_t *this);

extern bool deque_empty(deque_t *this);
extern size_t deque_size(deque_t *this);

extern void deque_clear(deque_t *this);
extern void deque_push_front(deque_t *this, const void *data);
extern void deque_pop_front(deque_t *this);
extern void deque_push_back(deque_t *this, const void *data);
extern void deque_pop_back(deque_t *this);

#endif // DTL_DEQUE_H

