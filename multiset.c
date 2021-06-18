/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: multiset.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 多重有序集合（容器适配器）
 *
 *****************************************************************/

#include "multiset.h"
#include <assert.h>

void multiset_init(multiset_t *pset, size_t size, int (*compar)(const void *, const void *))
{
	assert(pset != NULL);
	assert(size > 0);

	avl_tree_init(&pset->tree, size, compar);
}

void multiset_free(multiset_t *pset)
{
	assert(pset != NULL);

	avl_tree_free(&pset->tree);
}

size_t multiset_count(multiset_t set, const void *data)
{
	assert(data != NULL);

	return avl_tree_count(set.tree, data);
}

bool multiset_empty(multiset_t set)
{
	return avl_tree_empty(set.tree);
}

size_t multiset_size(multiset_t set)
{
	return avl_tree_size(set.tree);
}

void multiset_clear(multiset_t *pset)
{
	assert(pset != NULL);

	avl_tree_clear(&pset->tree);
}

bool multiset_insert(multiset_t *pset, const void *data)
{
	assert(pset != NULL);
	assert(data != NULL);

	return avl_tree_insert(&pset->tree, false, data);
}

bool multiset_erase(multiset_t *pset, const void *data)
{
	assert(pset != NULL);
	assert(data != NULL);

	return avl_tree_erase(&pset->tree, data);
}

iterator_t multiset_begin(multiset_t set)
{
	return avl_tree_begin(set.tree);
}

iterator_t multiset_end(multiset_t set)
{
	return avl_tree_end(set.tree);
}

iterator_t multiset_rbegin(multiset_t set)
{
	return avl_tree_rbegin(set.tree);
}

iterator_t multiset_rend(multiset_t set)
{
	return avl_tree_rend(set.tree);
}

