/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: set.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 单重有序集合（容器适配器）
 *
 *****************************************************************/

#include "set.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

set_t *set_init(size_t size, int (*compar)(const void *, const void *))
{
	assert(size > 0);

	set_t *this = NULL;
	if ((this = (set_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->tree = avl_tree_init(size, compar);
	return this;
}

void set_free(set_t *this)
{
	if (this == NULL) {
		return;
	}

	avl_tree_free(this->tree);
	free(this);
}

size_t set_count(set_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	return avl_tree_count(this->tree, data);
}

bool set_empty(set_t *this)
{
	assert(this != NULL);
	
	return avl_tree_empty(this->tree);
}

size_t set_size(set_t *this)
{
	assert(this != NULL);
	
	return avl_tree_size(this->tree);
}

void set_clear(set_t *this)
{
	assert(this != NULL);

	avl_tree_clear(this->tree);
}

bool set_insert(set_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	return avl_tree_insert(this->tree, data, true);
}

bool set_erase(set_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	return avl_tree_erase(this->tree, data);
}

set_iter_t set_begin(set_t *this)
{
	return avl_tree_begin(this->tree);
}

set_iter_t set_end(set_t *this)
{
	return avl_tree_end(this->tree);
}

set_iter_t set_rbegin(set_t *this)
{
	return avl_tree_rbegin(this->tree);
}

set_iter_t set_rend(set_t *this)
{
	return avl_tree_rend(this->tree);
}

void *set_data(set_iter_t iter)
{
	return avl_tree_data(iter);
}

bool set_equal(set_iter_t iter1, set_iter_t iter2)
{
	return avl_tree_equal(iter1, iter2);
}

ptrdiff_t set_distance(set_iter_t first, set_iter_t last)
{
	return avl_tree_distance(first, last);
}

set_iter_t set_prev(set_iter_t iter)
{
	return avl_tree_prev(iter);
}

set_iter_t set_next(set_iter_t iter)
{
	return avl_tree_next(iter);
}

set_iter_t set_advance(set_iter_t iter, ptrdiff_t distance)
{
	return avl_tree_advance(iter, distance);
}

