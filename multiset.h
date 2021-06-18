/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: multiset.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 多重有序集合（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_MULTISET_H
#define DTL_MULTISET_H

#include <stdbool.h>
#include <stddef.h>
#include "avl_tree.h"
#include "iterator.h"

typedef struct multiset {
	avl_tree_t tree;
} multiset_t;

extern void multiset_init(multiset_t *pset, size_t size,
		int (*compar)(const void *, const void *));
extern void multiset_free(multiset_t *pset);

extern size_t multiset_count(multiset_t set, const void *data);

extern bool multiset_empty(multiset_t set);
extern size_t multiset_size(multiset_t set);

extern void multiset_clear(multiset_t *pset);
extern bool multiset_insert(multiset_t *pset, const void *data);
extern bool multiset_erase(multiset_t *pset, const void *data);

extern iterator_t multiset_begin(multiset_t set);
extern iterator_t multiset_end(multiset_t set);
extern iterator_t multiset_rbegin(multiset_t set);
extern iterator_t multiset_rend(multiset_t set);

#endif // DTL_MULTISET_H

