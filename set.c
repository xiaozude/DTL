/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: set.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 单重有序集合（容器适配器）
 *
 *****************************************************************/

#include "set.h"
#include <assert.h>

void set_init(set_t *pset, size_t size, int (*compar)(const void *, const void *))
{
	assert(pset != NULL);
	assert(size > 0);

	avl_tree_init(&pset->tree, size, compar);
}

void set_free(set_t *pset)
{
	assert(pset != NULL);

	avl_tree_free(&pset->tree);
}

size_t set_count(set_t set, const void *data)
{
	assert(data != NULL);

	return avl_tree_count(set.tree, data);
}

bool set_empty(set_t set)
{
	return avl_tree_empty(set.tree);
}

size_t set_size(set_t set)
{
	return avl_tree_size(set.tree);
}

void set_clear(set_t *pset)
{
	assert(pset != NULL);

	avl_tree_clear(&pset->tree);
}

bool set_insert(set_t *pset, const void *data)
{
	assert(pset != NULL);
	assert(data != NULL);

	return avl_tree_insert(&pset->tree, true, data);
}

bool set_erase(set_t *pset, const void *data)
{
	assert(pset != NULL);
	assert(data != NULL);

	return avl_tree_erase(&pset->tree, data);
}

iterator_t set_begin(set_t set)
{
	return avl_tree_begin(set.tree);
}

iterator_t set_end(set_t set)
{
	return avl_tree_end(set.tree);
}

iterator_t set_rbegin(set_t set)
{
	return avl_tree_rbegin(set.tree);
}

iterator_t set_rend(set_t set)
{
	return avl_tree_rend(set.tree);
}

