/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: multiset.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 多重有序集合（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_MULTISET_H
#define DTL_MULTISET_H

#include <stdbool.h>
#include <stddef.h>
#include "avl_tree.h"

typedef struct multiset multiset_t;
typedef avl_tree_iter_t multiset_iter_t;

struct multiset {
	avl_tree_t *tree;
};

extern multiset_t *multiset_init(size_t size,
	int (*compar)(const void *, const void *));
extern void multiset_free(multiset_t *this);

extern size_t multiset_count(multiset_t *this, const void *data);

extern bool multiset_empty(multiset_t *this);
extern size_t multiset_size(multiset_t *this);

extern void multiset_clear(multiset_t *this);
extern bool multiset_insert(multiset_t *this, const void *data);
extern bool multiset_erase(multiset_t *this, const void *data);

extern multiset_iter_t multiset_begin(multiset_t *this);
extern multiset_iter_t multiset_end(multiset_t *this);
extern multiset_iter_t multiset_rbegin(multiset_t *this);
extern multiset_iter_t multiset_rend(multiset_t *this);

extern void *multiset_data(multiset_iter_t iter);
extern bool multiset_equal(multiset_iter_t iter1, multiset_iter_t iter2);
extern ptrdiff_t multiset_distance(multiset_iter_t first, multiset_iter_t last);

extern multiset_iter_t multiset_prev(multiset_iter_t iter);
extern multiset_iter_t multiset_next(multiset_iter_t iter);
extern multiset_iter_t multiset_advance(multiset_iter_t iter, ptrdiff_t distance);

#endif // DTL_MULTISET_H

