/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: multiset.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 多重有序集合（容器适配器）
 *
 *****************************************************************/

#include "multiset.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

multiset_t *multiset_init(size_t size, int (*compar)(const void *, const void *))
{
	assert(size > 0);

	multiset_t *this = NULL;
	if ((this = (multiset_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->tree = avl_tree_init(size, compar);
	return this;
}

void multiset_free(multiset_t *this)
{
	if (this == NULL) {
		return;
	}

	avl_tree_free(this->tree);
	free(this);
}

size_t multiset_count(multiset_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	return avl_tree_count(this->tree, data);
}

bool multiset_empty(multiset_t *this)
{
	assert(this != NULL);

	return avl_tree_empty(this->tree);
}

size_t multiset_size(multiset_t *this)
{
	assert(this != NULL);

	return avl_tree_size(this->tree);
}

void multiset_clear(multiset_t *this)
{
	assert(this != NULL);

	avl_tree_clear(this->tree);
}

bool multiset_insert(multiset_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	return avl_tree_insert(this->tree, false, data);
}

bool multiset_erase(multiset_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	return avl_tree_erase(this->tree, data);
}

multiset_iter_t multiset_begin(multiset_t *this)
{
	return avl_tree_begin(this->tree);
}

multiset_iter_t multiset_end(multiset_t *this)
{
	return avl_tree_end(this->tree);
}

multiset_iter_t multiset_rbegin(multiset_t *this)
{
	return avl_tree_rbegin(this->tree);
}

multiset_iter_t multiset_rend(multiset_t *this)
{
	return avl_tree_rend(this->tree);
}

void *multiset_data(multiset_iter_t iter)
{
	return avl_tree_data(iter);
}

bool multiset_equal(multiset_iter_t iter1, multiset_iter_t iter2)
{
	return avl_tree_equal(iter1, iter2);
}

ptrdiff_t multiset_distance(multiset_iter_t first, multiset_iter_t last)
{
	return avl_tree_distance(first, last);
}

multiset_iter_t multiset_prev(multiset_iter_t iter)
{
	return avl_tree_prev(iter);
}

multiset_iter_t multiset_next(multiset_iter_t iter)
{
	return avl_tree_next(iter);
}

multiset_iter_t multiset_advance(multiset_iter_t iter, ptrdiff_t distance)
{
	return avl_tree_advance(iter, distance);
}

