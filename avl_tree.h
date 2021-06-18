/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: avl_tree.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 平衡二叉树（容器）
 *
 *****************************************************************/

#ifndef DTL_AVL_TREE_H
#define DTL_AVL_TREE_H

#include <stdbool.h>
#include <stddef.h>
#include "vector.h"
#include "iterator.h"

struct avl_tree_node {
	size_t height;
	vector_t vector;
	struct avl_tree_node *parent;
	struct avl_tree_node *left;
	struct avl_tree_node *right;
};

typedef struct avl_tree {
	size_t size;
	size_t count;
	struct avl_tree_node *root;
	int (*compar)(const void *, const void *);
} avl_tree_t;

extern void avl_tree_init(avl_tree_t *ptree, size_t size,
		int (*compar)(const void *, const void *));
extern void avl_tree_free(avl_tree_t *ptree);

extern void *avl_tree_index(avl_tree_t tree, const void *data, size_t index);
extern size_t avl_tree_count(avl_tree_t tree, const void *data);

extern bool avl_tree_empty(avl_tree_t tree);
extern size_t avl_tree_size(avl_tree_t tree);

extern void avl_tree_clear(avl_tree_t *ptree);
extern bool avl_tree_insert(avl_tree_t *ptree, bool unique, const void *data);
extern bool avl_tree_erase(avl_tree_t *ptree, const void *data);

extern iterator_t avl_tree_begin(avl_tree_t tree);
extern iterator_t avl_tree_end(avl_tree_t tree);
extern iterator_t avl_tree_rbegin(avl_tree_t tree);
extern iterator_t avl_tree_rend(avl_tree_t tree);

#endif // DTL_AVL_TREE_H

