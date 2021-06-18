/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: forward_list.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 单向环状链表（容器）
 *
 *****************************************************************/

#ifndef DTL_FORWARD_LIST_H
#define DTL_FORWARD_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include "iterator.h"

struct forward_list_node {
	void *data;
	struct forward_list_node *next;
};

typedef struct forward_list {
	size_t size;
	size_t count;
	struct forward_list_node *root;
} forward_list_t;

extern void forward_list_init(forward_list_t *list, size_t size);
extern void forward_list_free(forward_list_t *list);

extern void *forward_list_front(forward_list_t list);

extern bool forward_list_empty(forward_list_t list);
extern size_t forward_list_size(forward_list_t list);

extern void forward_list_clear(forward_list_t *list);
extern void forward_list_insert_after(forward_list_t *list, iterator_t it, const void *data);
extern void forward_list_erase_after(forward_list_t *list, iterator_t it);
extern void forward_list_push_front(forward_list_t *list, const void *data);
extern void forward_list_pop_front(forward_list_t *list);

extern iterator_t forward_list_begin_before(forward_list_t list);
extern iterator_t forward_list_begin(forward_list_t list);
extern iterator_t forward_list_end(forward_list_t list);

#endif // DTL_FORWARD_LIST_H

