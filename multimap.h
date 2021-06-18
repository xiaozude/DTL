/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: multimap.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 多重有序映射（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_MULTIMAP_H
#define DTL_MULTIMAP_H

#include <stdbool.h>
#include <stddef.h>
#include "avl_tree.h"
#include "iterator.h"

typedef struct multimap {
	size_t key_size;
	size_t val_size;
	avl_tree_t tree;
} multimap_t;

extern void multimap_init(multimap_t *pmap, size_t key_size, size_t val_size,
		int (*compar)(const void *, const void *));
extern void multimap_free(multimap_t *pmap);

extern size_t multimap_count(multimap_t map, const void *key);
extern void *multimap_value(multimap_t map, void *data);

extern bool multimap_empty(multimap_t map);
extern size_t multimap_size(multimap_t map);

extern void multimap_clear(multimap_t *pmap);
extern bool multimap_insert(multimap_t *pmap, const void *key, const void *val);
extern bool multimap_erase(multimap_t *pmap, const void *key);

extern iterator_t multimap_begin(multimap_t map);
extern iterator_t multimap_end(multimap_t map);
extern iterator_t multimap_rbegin(multimap_t map);
extern iterator_t multimap_rend(multimap_t map);

#endif // DTL_MULTIMAP_H

