/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: list.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 双向环状链表（容器）
 *
 *****************************************************************/

#ifndef DTL_LIST_H
#define DTL_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct list list_t;
typedef struct list_node list_node_t;
typedef struct list_iter list_iter_t;

struct list {
	size_t size;
	size_t count;
	list_node_t *root;
};

struct list_node {
	void *data;
	list_node_t *prev;
	list_node_t *next;
};

struct list_iter {
	size_t size;
	list_node_t *cursor;
	bool reverse;
};

extern list_t *list_init(size_t size);
extern void list_free(list_t *this);

extern void *list_front(list_t *this);
extern void *list_back(list_t *this);

extern bool list_empty(list_t *this);
extern size_t list_size(list_t *this);

extern void list_clear(list_t *this);
extern void list_insert(list_t *this, list_iter_t iter, const void *data);
extern void list_erase(list_t *this, list_iter_t iter);
extern void list_push_front(list_t *this, const void *data);
extern void list_pop_front(list_t *this);
extern void list_push_back(list_t *this, const void *data);
extern void list_pop_back(list_t *this);

extern list_iter_t list_begin(list_t *this);
extern list_iter_t list_end(list_t *this);
extern list_iter_t list_rbegin(list_t *this);
extern list_iter_t list_rend(list_t *this);

extern void *list_data(list_iter_t iter);
extern bool list_equal(list_iter_t iter1, list_iter_t iter2);
extern ptrdiff_t list_distance(list_iter_t first, list_iter_t last);

extern list_iter_t list_prev(list_iter_t iter);
extern list_iter_t list_next(list_iter_t iter);
extern list_iter_t list_advance(list_iter_t iter, ptrdiff_t distance);

#endif // DTL_LIST_H

