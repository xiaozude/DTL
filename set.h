/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: set.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 单重有序集合（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_SET_H
#define DTL_SET_H

#include <stdbool.h>
#include <stddef.h>
#include "avl_tree.h"
#include "iterator.h"

typedef struct set {
	avl_tree_t tree;
} set_t;

extern void set_init(set_t *pset, size_t size,
		int (*compar)(const void *, const void *));
extern void set_free(set_t *pset);

extern size_t set_count(set_t set, const void *data);

extern bool set_empty(set_t set);
extern size_t set_size(set_t set);

extern void set_clear(set_t *pset);
extern bool set_insert(set_t *pset, const void *data);
extern bool set_erase(set_t *pset, const void *data);

extern iterator_t set_begin(set_t set);
extern iterator_t set_end(set_t set);
extern iterator_t set_rbegin(set_t set);
extern iterator_t set_rend(set_t set);

#endif // DTL_SET_H

