/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: map.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 单重有序映射（容器适配器）
 *
 *****************************************************************/

#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

map_t *map_init(size_t key_size, size_t val_size, int (*compar)(const void *, const void *))
{
	assert(key_size > 0);
	assert(val_size > 0);
	assert(compar != NULL);

	map_t *this = NULL;
	if ((this = (map_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->key_size = key_size;
	this->val_size = val_size;
	this->tree = avl_tree_init(key_size + val_size, compar);
	return this;
}

void map_free(map_t *this)
{
	if (this == NULL) {
		return;
	}

	avl_tree_free(this->tree);
	free(this);
}

void *map_index(map_t *this, const void *key)
{
	assert(this != NULL);
	assert(key != NULL);

	return avl_tree_index(this->tree, key, 0);
}

void *map_value(map_t *this, void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	return data + this->key_size;
}

bool map_empty(map_t *this)
{
	assert(this != NULL);
	
	return avl_tree_empty(this->tree);
}

size_t map_size(map_t *this)
{
	assert(this != NULL);
	
	return avl_tree_size(this->tree);
}

void map_clear(map_t *this)
{
	assert(this != NULL);

	avl_tree_clear(this->tree);
}

bool map_insert(map_t *this, const void *key, const void *val)
{
	assert(this != NULL);
	assert(key != NULL);
	assert(val != NULL);

	void *data = NULL;
	if ((data = malloc(this->key_size + this->val_size)) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memcpy(data, key, this->key_size);
	memcpy(data + this->key_size, val, this->val_size);
	bool res = avl_tree_insert(this->tree, data, true);
	free(data);

	return res;
}

bool map_erase(map_t *this, const void *key)
{
	assert(this != NULL);
	assert(key != NULL);

	return avl_tree_erase(this->tree, key);
}

map_iter_t map_begin(map_t *this)
{
	return avl_tree_begin(this->tree);
}

map_iter_t map_end(map_t *this)
{
	return avl_tree_end(this->tree);
}

map_iter_t map_rbegin(map_t *this)
{
	return avl_tree_rbegin(this->tree);
}

map_iter_t map_rend(map_t *this)
{
	return avl_tree_rend(this->tree);
}

void *map_data(map_iter_t iter)
{
	return avl_tree_data(iter);
}

bool map_equal(map_iter_t iter1, map_iter_t iter2)
{
	return avl_tree_equal(iter1, iter2);
}

ptrdiff_t map_distance(map_iter_t first, map_iter_t last)
{
	return avl_tree_distance(first, last);
}

map_iter_t map_prev(map_iter_t iter)
{
	return avl_tree_prev(iter);
}

map_iter_t map_next(map_iter_t iter)
{
	return avl_tree_next(iter);
}

map_iter_t map_advance(map_iter_t iter, ptrdiff_t distance)
{
	return avl_tree_advance(iter, distance);
}

