/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: map.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 单重有序映射（容器适配器）
 *
 *****************************************************************/

#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void map_init(map_t *pmap, size_t key_size, size_t val_size, int (*compar)(const void *, const void *))
{
	assert(pmap != NULL);
	assert(key_size > 0);
	assert(val_size > 0);

	pmap->key_size = key_size;
	pmap->val_size = val_size;

	avl_tree_init(&pmap->tree, key_size + val_size, compar);
}

void map_free(map_t *pmap)
{
	assert(pmap != NULL);

	avl_tree_free(&pmap->tree);
}

void *map_index(map_t map, const void *key)
{
	assert(key != NULL);

	return avl_tree_index(map.tree, key, 0);
}

void *map_value(map_t map, void *data)
{
	assert(data != NULL);

	return data + map.key_size;
}

bool map_empty(map_t map)
{
	return avl_tree_empty(map.tree);
}

size_t map_size(map_t map)
{
	return avl_tree_size(map.tree);
}

void map_clear(map_t *pmap)
{
	assert(pmap != NULL);

	avl_tree_clear(&pmap->tree);
}

bool map_insert(map_t *pmap, const void *key, const void *val)
{
	assert(pmap != NULL);
	assert(key != NULL);
	assert(val != NULL);

	void *data = malloc(pmap->key_size + pmap->val_size);
	if (data == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memcpy(data, key, pmap->key_size);
	memcpy(data + pmap->key_size, val, pmap->val_size);
	bool res = avl_tree_insert(&pmap->tree, true, data);
	free(data);

	return res;
}

bool map_erase(map_t *pmap, const void *key)
{
	assert(pmap != NULL);
	assert(key != NULL);

	return avl_tree_erase(&pmap->tree, key);
}

iterator_t map_begin(map_t map)
{
	return avl_tree_begin(map.tree);
}

iterator_t map_end(map_t map)
{
	return avl_tree_end(map.tree);
}

iterator_t map_rbegin(map_t map)
{
	return avl_tree_rbegin(map.tree);
}

iterator_t map_rend(map_t map)
{
	return avl_tree_rend(map.tree);
}

