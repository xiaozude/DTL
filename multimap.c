/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: multimap.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 多重有序映射（容器适配器）
 *
 *****************************************************************/

#include "multimap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

multimap_t *multimap_init(size_t key_size, size_t val_size, int (*compar)(const void *, const void *))
{
	assert(key_size > 0);
	assert(val_size > 0);
	assert(compar != NULL);

	multimap_t *this = NULL;
	if ((this = (multimap_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->key_size = key_size;
	this->val_size = val_size;
	this->tree = avl_tree_init(key_size + val_size, compar);
	return this;
}

void multimap_free(multimap_t *this)
{
	if (this == NULL) {
		return;
	}

	avl_tree_free(this->tree);
	free(this);
}

size_t multimap_count(multimap_t *this, const void *key)
{
	assert(this != NULL);
	assert(key != NULL);

	return avl_tree_count(this->tree, key);
}

void *multimap_value(multimap_t *this, void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	return data + this->key_size;
}

bool multimap_empty(multimap_t *this)
{
	assert(this != NULL);

	return avl_tree_empty(this->tree);
}

size_t multimap_size(multimap_t *this)
{
	assert(this != NULL);

	return avl_tree_size(this->tree);
}

void multimap_clear(multimap_t *this)
{
	assert(this != NULL);

	avl_tree_clear(this->tree);
}

bool multimap_insert(multimap_t *this, const void *key, const void *val)
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
	bool res = avl_tree_insert(this->tree, data, false);
	free(data);

	return res;
}

bool multimap_erase(multimap_t *this, const void *key)
{
	assert(this != NULL);
	assert(key != NULL);
	
	return avl_tree_erase(this->tree, key);
}

multimap_iter_t multimap_begin(multimap_t *this)
{
	return avl_tree_begin(this->tree);
}

multimap_iter_t multimap_end(multimap_t *this)
{
	return avl_tree_end(this->tree);
}

multimap_iter_t multimap_rbegin(multimap_t *this)
{
	return avl_tree_rbegin(this->tree);
}

multimap_iter_t multimap_rend(multimap_t *this)
{
	return avl_tree_rend(this->tree);
}

void *multimap_data(multimap_iter_t iter)
{
	return avl_tree_data(iter);
}

bool multimap_equal(multimap_iter_t iter1, multimap_iter_t iter2)
{
	return avl_tree_equal(iter1, iter2);
}

ptrdiff_t multimap_distance(multimap_iter_t first, multimap_iter_t last)
{
	return avl_tree_distance(first, last);
}

multimap_iter_t multimap_prev(multimap_iter_t iter)
{
	return avl_tree_prev(iter);
}

multimap_iter_t multimap_next(multimap_iter_t iter)
{
	return avl_tree_next(iter);
}

multimap_iter_t multimap_advance(multimap_iter_t iter, ptrdiff_t distance)
{
	return avl_tree_advance(iter, distance);
}

