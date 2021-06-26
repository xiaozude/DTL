/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: map.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 单重有序映射（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_MAP_H
#define DTL_MAP_H

#include <stdbool.h>
#include <stddef.h>
#include "avl_tree.h"

typedef struct map map_t;
typedef avl_tree_iter_t map_iter_t;

typedef struct map {
	size_t key_size;
	size_t val_size;
	avl_tree_t *tree;
} map_t;

extern map_t *map_init(size_t key_size, size_t val_size,
	int (*compar)(const void *, const void *));
extern void map_free(map_t *this);

extern void *map_index(map_t *this, const void *key);
extern void *map_value(map_t *this, void *data);

extern bool map_empty(map_t *this);
extern size_t map_size(map_t *this);

extern void map_clear(map_t *this);
extern bool map_insert(map_t *this, const void *key, const void *val);
extern bool map_erase(map_t *this, const void *key);

extern map_iter_t map_begin(map_t *this);
extern map_iter_t map_end(map_t *this);
extern map_iter_t map_rbegin(map_t *this);
extern map_iter_t map_rend(map_t *this);

extern void *map_data(map_iter_t iter);
extern bool map_equal(map_iter_t iter1, map_iter_t iter2);
extern ptrdiff_t map_distance(map_iter_t first, map_iter_t last);

extern map_iter_t map_prev(map_iter_t iter);
extern map_iter_t map_next(map_iter_t iter);
extern map_iter_t map_advance(map_iter_t iter, ptrdiff_t distance);

#endif // DTL_MAP_H

