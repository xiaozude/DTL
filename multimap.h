/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: multimap.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 多重有序映射（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_MULTIMAP_H
#define DTL_MULTIMAP_H

#include <stdbool.h>
#include <stddef.h>
#include "avl_tree.h"

typedef struct multimap multimap_t;
typedef avl_tree_iter_t multimap_iter_t;

struct multimap {
	size_t key_size;
	size_t val_size;
	avl_tree_t *tree;
};

extern multimap_t *multimap_init(size_t key_size, size_t val_size,
	int (*compar)(const void *, const void *));
extern void multimap_free(multimap_t *this);

extern size_t multimap_count(multimap_t *this, const void *key);
extern void *multimap_value(multimap_t *this, void *data);

extern bool multimap_empty(multimap_t *this);
extern size_t multimap_size(multimap_t *this);

extern void multimap_clear(multimap_t *this);
extern bool multimap_insert(multimap_t *this, const void *key, const void *val);
extern bool multimap_erase(multimap_t *this, const void *key);

extern multimap_iter_t multimap_begin(multimap_t *this);
extern multimap_iter_t multimap_end(multimap_t *this);
extern multimap_iter_t multimap_rbegin(multimap_t *this);
extern multimap_iter_t multimap_rend(multimap_t *this);

extern void *multimap_data(multimap_iter_t iter);
extern bool multimap_equal(multimap_iter_t iter1, multimap_iter_t iter2);
extern ptrdiff_t multimap_distance(multimap_iter_t first, multimap_iter_t last);

extern multimap_iter_t multimap_prev(multimap_iter_t iter);
extern multimap_iter_t multimap_next(multimap_iter_t iter);
extern multimap_iter_t multimap_advance(multimap_iter_t iter, ptrdiff_t distance);

#endif // DTL_MULTIMAP_H

