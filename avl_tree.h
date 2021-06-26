/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: avl_tree.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 平衡二叉树（容器）
 *
 *****************************************************************/

#ifndef DTL_AVL_TREE_H
#define DTL_AVL_TREE_H

#include <stdbool.h>
#include <stddef.h>
#include "vector.h"

typedef struct avl_tree avl_tree_t;
typedef struct avl_tree_node avl_tree_node_t;
typedef struct avl_tree_iter avl_tree_iter_t;

struct avl_tree {
	size_t size;
	size_t count;
	avl_tree_node_t *root;
	int (*compar)(const void *, const void *);
};

struct avl_tree_node {
	size_t height;
	vector_t *vector;
	avl_tree_node_t *parent;
	avl_tree_node_t *left;
	avl_tree_node_t *right;
};

struct avl_tree_iter {
	size_t size;
	avl_tree_node_t *cursor;
	size_t index;
	bool reverse;
};

extern avl_tree_t *avl_tree_init(size_t size,
	int (*compar)(const void *, const void *));
extern void avl_tree_free(avl_tree_t *this);

extern void *avl_tree_index(avl_tree_t *this, const void *data, size_t index);
extern size_t avl_tree_count(avl_tree_t *this, const void *data);

extern bool avl_tree_empty(avl_tree_t *this);
extern size_t avl_tree_size(avl_tree_t *this);

extern void avl_tree_clear(avl_tree_t *this);
extern bool avl_tree_insert(avl_tree_t *this, const void *data, bool unique);
extern bool avl_tree_erase(avl_tree_t *this, const void *data);

extern avl_tree_iter_t avl_tree_begin(avl_tree_t *this);
extern avl_tree_iter_t avl_tree_end(avl_tree_t *this);
extern avl_tree_iter_t avl_tree_rbegin(avl_tree_t *this);
extern avl_tree_iter_t avl_tree_rend(avl_tree_t *this);

extern void *avl_tree_data(avl_tree_iter_t iter);
extern bool avl_tree_equal(avl_tree_iter_t iter1, avl_tree_iter_t iter2);
extern ptrdiff_t avl_tree_distance(avl_tree_iter_t first, avl_tree_iter_t last);

extern avl_tree_iter_t avl_tree_prev(avl_tree_iter_t iter);
extern avl_tree_iter_t avl_tree_next(avl_tree_iter_t iter);
extern avl_tree_iter_t avl_tree_advance(avl_tree_iter_t iter, ptrdiff_t distance);

#endif // DTL_AVL_TREE_H

