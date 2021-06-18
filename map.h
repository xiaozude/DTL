/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: map.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 单重有序映射（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_MAP_H
#define DTL_MAP_H

#include <stdbool.h>
#include <stddef.h>
#include "avl_tree.h"
#include "iterator.h"

typedef struct map {
	size_t key_size;
	size_t val_size;
	avl_tree_t tree;
} map_t;

extern void map_init(map_t *pmap, size_t key_size, size_t val_size,
		int (*compar)(const void *, const void *));
extern void map_free(map_t *pmap);

extern void *map_index(map_t map, const void *key);
extern void *map_value(map_t map, void *data);

extern bool map_empty(map_t map);
extern size_t map_size(map_t map);

extern void map_clear(map_t *pmap);
extern bool map_insert(map_t *pmap, const void *key, const void *val);
extern bool map_erase(map_t *pmap, const void *key);

extern iterator_t map_begin(map_t map);
extern iterator_t map_end(map_t map);
extern iterator_t map_rbegin(map_t map);
extern iterator_t map_rend(map_t map);

#endif // DTL_MAP_H

