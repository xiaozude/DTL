/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: deque.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 双端队列（容器）
 *
 *****************************************************************/

#ifndef DTL_DEQUE_H
#define DTL_DEQUE_H

#include <stdbool.h>
#include <stddef.h>
#include "iterator.h"

typedef struct deque {
	size_t size;
	void *elems;
	void *cliff;
	void *start;
	void *finish;
} deque_t;

extern void deque_init(deque_t *pdeque, size_t size);
extern void deque_free(deque_t *pdeque);

extern void *deque_front(deque_t deque);
extern void *deque_back(deque_t deque);
extern void *deque_index(deque_t deque, size_t index);

extern bool deque_empty(deque_t deque);
extern size_t deque_size(deque_t deque);

extern void deque_clear(deque_t *pdeque);
extern void deque_insert(deque_t *pdeque, size_t index, const void *data);
extern void deque_erase(deque_t *pdeque, size_t index);
extern void deque_push_front(deque_t *pdeque, const void *data);
extern void deque_pop_front(deque_t *pdeque);
extern void deque_push_back(deque_t *pdeque, const void *data);
extern void deque_pop_back(deque_t *pdeque);

extern iterator_t deque_begin(deque_t deque);
extern iterator_t deque_end(deque_t deque);
extern iterator_t deque_rbegin(deque_t deque);
extern iterator_t deque_rend(deque_t deque);

#endif // DTL_DEQUE_H

