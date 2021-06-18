/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: list.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 双向环状链表（容器）
 *
 *****************************************************************/

#ifndef DTL_LIST_H
#define DTL_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include "iterator.h"

struct list_node {
	void *data;
	struct list_node *prev;
	struct list_node *next;
};

typedef struct list {
	size_t size;
	size_t count;
	struct list_node *root;
} list_t;

extern void list_init(list_t *plist, size_t size);
extern void list_free(list_t *plist);

extern void *list_front(list_t list);
extern void *list_back(list_t list);

extern bool list_empty(list_t list);
extern size_t list_size(list_t list);

extern void list_clear(list_t *plist);
extern void list_insert(list_t *plist, iterator_t iterator, const void *data);
extern void list_erase(list_t *plist, iterator_t iterator);
extern void list_push_front(list_t *plist, const void *data);
extern void list_pop_front(list_t *plist);
extern void list_push_back(list_t *plist, const void *data);
extern void list_pop_back(list_t *plist);

extern iterator_t list_begin(list_t list);
extern iterator_t list_end(list_t list);
extern iterator_t list_rbegin(list_t list);
extern iterator_t list_rend(list_t list);

#endif // DTL_LIST_H

