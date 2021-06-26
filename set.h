/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: set.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 单重有序集合（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_SET_H
#define DTL_SET_H

#include <stdbool.h>
#include <stddef.h>
#include "avl_tree.h"

typedef struct set set_t;
typedef avl_tree_iter_t set_iter_t;

struct set {
	avl_tree_t *tree;
};

extern set_t *set_init(size_t size,
	int (*compar)(const void *, const void *));
extern void set_free(set_t *this);

extern size_t set_count(set_t *this, const void *data);

extern bool set_empty(set_t *this);
extern size_t set_size(set_t *this);

extern void set_clear(set_t *this);
extern bool set_insert(set_t *this, const void *data);
extern bool set_erase(set_t *this, const void *data);

extern set_iter_t set_begin(set_t *this);
extern set_iter_t set_end(set_t *this);
extern set_iter_t set_rbegin(set_t *this);
extern set_iter_t set_rend(set_t *this);

extern void *set_data(set_iter_t iter);
extern bool set_equal(set_iter_t iter1, set_iter_t iter2);
extern ptrdiff_t set_distance(set_iter_t first, set_iter_t last);

extern set_iter_t set_prev(set_iter_t iter);
extern set_iter_t set_next(set_iter_t iter);
extern set_iter_t set_advance(set_iter_t iter, ptrdiff_t distance);

#endif // DTL_SET_H

