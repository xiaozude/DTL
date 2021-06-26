/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: avl_tree.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 平衡二叉树（容器）
 *
 *****************************************************************/

#include "avl_tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static avl_tree_node_t *avl_tree_node_init(size_t size, const void *data)
{
	assert(size > 0);

	avl_tree_node_t *p = NULL;
	if ((p = (avl_tree_node_t *) malloc(sizeof(*p))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	p->height = 1;
	p->vector = vector_init(size);
	if (data != NULL) {
		vector_push_back(p->vector, data);
	}
	return p;
}

static void avl_tree_node_free(avl_tree_node_t *p)
{
	if (p == NULL) {
		return;
	}

	vector_free(p->vector);
	free(p);
}

static size_t avl_tree_node_height(avl_tree_node_t *p)
{
	if (p == NULL) {
		return 0;
	}

	return p->height;
}

static void avl_tree_node_clear(avl_tree_node_t **p)
{
	assert(p != NULL);

	if (*p == NULL) {
		return;
	}

	avl_tree_node_clear(&(*p)->left);
	avl_tree_node_clear(&(*p)->right);

	avl_tree_node_free(*p);

	*p = NULL;
}

static avl_tree_node_t *avl_tree_node_find(
		avl_tree_node_t *p, const void *data,
		int (*compar)(const void *, const void *),
		avl_tree_node_t **parent)
{
	assert(data != NULL);
	assert(compar != NULL);
	
	if (p == NULL) {
		return NULL;
	}

	int compare = compar(data, vector_front(p->vector));

	if (parent != NULL) {
		*parent = compare == 0 ? p->parent : p;
	}
	
	if (compare == 0) {
		return p;
	} else if (compare < 0) {
		return avl_tree_node_find(p->left, data, compar, parent);
	} else {
		return avl_tree_node_find(p->right, data, compar, parent);
	}
}

static avl_tree_node_t *avl_tree_node_min(avl_tree_node_t *p)
{
	if (p == NULL || p->left == NULL) {
		return p;
	}

	while (p->left != NULL) {
		p = p->left;
	}

	return p;
}

static avl_tree_node_t *avl_tree_node_max(avl_tree_node_t *p)
{
	if (p == NULL || p->right == NULL) {
		return p;
	}

	while (p->right != NULL) {
		p = p->right;
	}

	return p;
}

static void avl_tree_node_rotate_left(avl_tree_node_t **p)
{
	assert(p != NULL);

	if (*p == NULL) {
		return;
	}

	avl_tree_node_t *q = *p;
	*p = q->right;
	(*p)->parent = q->parent;
	q->parent = *p;
	q->right = (*p)->left;
	(*p)->left = q;
	
	size_t left_height = avl_tree_node_height(q->left);
	size_t right_height = avl_tree_node_height(q->right);
	q->height = (left_height > right_height ? left_height : right_height) + 1;
	
	left_height = avl_tree_node_height((*p)->left);
	right_height = avl_tree_node_height((*p)->right);
	(*p)->height = (left_height > right_height ? left_height : right_height) + 1;
}

static void avl_tree_node_rotate_right(avl_tree_node_t **p)
{
	assert(p != NULL);

	if (*p == NULL) {
		return;
	}

	avl_tree_node_t *q = *p;
	*p = q->left;
	(*p)->parent = q->parent;
	q->parent = *p;
	q->left = (*p)->right;
	(*p)->right = q;
	
	size_t left_height = avl_tree_node_height(q->left);
	size_t right_height = avl_tree_node_height(q->right);
	q->height = (left_height > right_height ? left_height : right_height) + 1;
	
	left_height = avl_tree_node_height((*p)->left);
	right_height = avl_tree_node_height((*p)->right);
	(*p)->height = (left_height > right_height ? left_height : right_height) + 1;
}

static void avl_tree_node_balance(avl_tree_node_t **p)
{
	assert(p != NULL);

	if (*p == NULL) {
		return;
	}

	avl_tree_node_t *left = (*p)->left;
	avl_tree_node_t *right = (*p)->right;
	
	// 左子树不平衡
	if (avl_tree_node_height(left) > avl_tree_node_height(right) + 1) {
		// 左子树的右子树不平衡
		if (left != NULL && avl_tree_node_height(left->right)
				> avl_tree_node_height(left->left) + 1) {
			// 调整左子树的右子树
			avl_tree_node_rotate_left(&(*p)->left);
		}
		// 调整左子树
		avl_tree_node_rotate_right(p);
	// 右子树不平衡
	} else if (avl_tree_node_height(left) + 1 < avl_tree_node_height(right)) {
		// 右子树的左子树不平衡
		if (right != NULL && avl_tree_node_height(right->left)
				> avl_tree_node_height(right->right) + 1) {
			// 调整右子树的左子树
			avl_tree_node_rotate_right(&(*p)->right);
		}
		// 调整右子树
		avl_tree_node_rotate_left(p);
	}
	
	// 调整当前节点高度
	size_t left_height = avl_tree_node_height(left);
	size_t right_height = avl_tree_node_height(right);
	(*p)->height = (left_height > right_height ? left_height : right_height) + 1;
}

static bool avl_tree_node_insert(avl_tree_node_t **root, size_t size, const void *data,
		int (*compar)(const void *, const void *), bool unique)
{
	assert(root != NULL);
	assert(size > 0);
	assert(data != NULL);
	assert(compar != NULL);
	
	if (*root == NULL) {
		return false;
	}

	// 树空，直接插入节点
	if ((*root)->left == NULL) {
		(*root)->left = avl_tree_node_init(size, data);
		(*root)->left->parent = *root;
		(*root)->right = (*root)->left;
		return true;
	}

	// 树非空，寻找插入位置
	avl_tree_node_t *parent = NULL;
	avl_tree_node_t *node = avl_tree_node_find((*root)->left, data, compar, &parent);
	if (parent == NULL) {
		return false;
	}

	// 节点存在
	if (node != NULL) {
		if (unique) {
			return false;
		}
		vector_push_back(node->vector, data);
		return true;
	}

	// 节点不存在，插入节点
	if (compar(data, vector_front(parent->vector)) < 0) {
		parent->left = avl_tree_node_init(size, data);
		parent->left->parent = parent;
	} else {
		parent->right = avl_tree_node_init(size, data);
		parent->right->parent = parent;
	}

	// 调整所有父节点的高度
	for (avl_tree_node_t *p = parent; p != *root; p = p->parent) {
		if (p->parent->left == p) {
			avl_tree_node_balance(&p->parent->left);
		} else {
			avl_tree_node_balance(&p->parent->right);
		}
	}

	return true;
}

static bool avl_tree_node_erase(avl_tree_node_t **root, const void *data,
		int (*compar)(const void *, const void *))
{
	assert(root != NULL);
	assert(data != NULL);
	assert(compar != NULL);
	
	if (*root == NULL) {
		return false;
	}

	// 寻找删除位置
	avl_tree_node_t *node = avl_tree_node_find((*root)->left, data, compar, NULL);
	avl_tree_node_t *parent = NULL;
	if (node == NULL) {
		return false;
	}

	// 左子树不为空
	if (node->left != NULL) {
		// 寻找交换结点，交换数据
		parent = node;
		node = avl_tree_node_max(node->left);
		vector_t *x = node->vector;
		node->vector = parent->vector;
		parent->vector = x;
		
		// 交换节点无右子树
		if (parent->left == node) {
			parent->left = node->left;
		// 交换节点有右子树
		} else {
			parent = node->parent;
			parent->right = node->left;
		}
		
		// 交换结点有左子树
		if (node->left != NULL) {
			node->left->parent = parent;
		}
	// 右子树不为空
	} else if (node->right != NULL) {
		// 寻找交换结点，交换数据
		parent = node;
		node = avl_tree_node_min(node->right);
		vector_t *x = node->vector;
		node->vector = parent->vector;
		parent->vector = x;

		// 交换节点无左子树
		if (parent->right == node) {
			parent->right = node->right;
		// 交换节点有左子树
		} else {
			parent = node->parent;
			parent->left = node->right;
		}

		// 交换结点有右子树
		if (node->right != NULL) {
			node->right->parent = parent;
		}
	// 左右子树均为空
	} else {
		parent = node->parent;
		if (parent->left == node) {
			parent->left = NULL;
		} else {
			parent->right = NULL;
		}
	}
	
	// 销毁节点
	avl_tree_node_free(node);
	
	// 调整所有父节点的高度
	for (avl_tree_node_t *p = parent; p != *root; p = p->parent) {
		if (p->parent->left == p) {
			avl_tree_node_balance(&p->parent->left);
		} else {
			avl_tree_node_balance(&p->parent->right);
		}
	}

	return true;
}

avl_tree_t *avl_tree_init(size_t size, int (*compar)(const void *, const void *))
{
	assert(size > 0);
	assert(compar != NULL);

	avl_tree_t *this = NULL;
	if ((this = (avl_tree_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->size = size;
	this->count = 0;
	this->root = avl_tree_node_init(size, NULL);
	this->root->parent = this->root;
	this->compar = compar;
	return this;
}

void avl_tree_free(avl_tree_t *this)
{
	if (this == NULL) {
		return;
	}

	avl_tree_node_clear(&this->root->left);
	avl_tree_node_free(this->root);
	free(this);
}

void *avl_tree_index(avl_tree_t *this, const void *data, size_t index)
{
	assert(this != NULL);
	assert(data != NULL);

	avl_tree_node_t *node = NULL;
	if ((node = avl_tree_node_find(this->root->left, data, this->compar, NULL)) == NULL) {
		return NULL;
	}
	return vector_index(node->vector, index);
}

size_t avl_tree_count(avl_tree_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	avl_tree_node_t *node = NULL;
	if ((node = avl_tree_node_find(this->root->left, data, this->compar, NULL)) == NULL) {
		return 0;
	}
	return vector_size(node->vector);
}

bool avl_tree_empty(avl_tree_t *this)
{
	assert(this != NULL);

	return this->count == 0;
}

size_t avl_tree_size(avl_tree_t *this)
{
	assert(this != NULL);

	return this->count;
}

void avl_tree_clear(avl_tree_t *this)
{
	assert(this != NULL);

	avl_tree_node_clear(&this->root->left);

	this->count = 0;
}

bool avl_tree_insert(avl_tree_t *this, const void *data, bool unique)
{
	assert(this != NULL);
	assert(data != NULL);

	if (avl_tree_node_insert(&this->root, this->size, data, this->compar, unique)) {
		this->count++;
		return true;
	}
	return false;
}

bool avl_tree_erase(avl_tree_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	if (avl_tree_node_erase(&this->root, data, this->compar)) {
		this->count--;
		return true;
	}
	return false;
}

avl_tree_iter_t avl_tree_begin(avl_tree_t *this)
{
	assert(this != NULL);

	return (avl_tree_iter_t) { this->size, avl_tree_node_min(this->root->left), 0, false };
}

avl_tree_iter_t avl_tree_end(avl_tree_t *this)
{
	assert(this != NULL);

	return (avl_tree_iter_t) { this->size, this->root, 0, false };
}

avl_tree_iter_t avl_tree_rbegin(avl_tree_t *this)
{
	assert(this != NULL);

	return (avl_tree_iter_t) { this->size, avl_tree_node_max(this->root->left), 0, true };
}

avl_tree_iter_t avl_tree_rend(avl_tree_t *this)
{
	assert(this != NULL);

	return (avl_tree_iter_t) { this->size, this->root, 0, true };
}

void *avl_tree_data(avl_tree_iter_t iter)
{
	return vector_index(iter.cursor->vector, iter.index);
}

bool avl_tree_equal(avl_tree_iter_t iter1, avl_tree_iter_t iter2)
{
	assert(iter1.size == iter2.size);
	assert(iter1.reverse == iter2.reverse);

	return avl_tree_distance(iter1, iter2) == 0;
}

ptrdiff_t avl_tree_distance(avl_tree_iter_t first, avl_tree_iter_t last)
{
	assert(first.size == last.size);
	assert(first.reverse == last.reverse);

	ptrdiff_t distance = 0;
	if (!first.reverse) {
		while (first.cursor != last.cursor) {
			first = avl_tree_next(first);
			distance++;
		}
	} else {
		while (first.cursor != last.cursor) {
			first = avl_tree_prev(first);
			distance++;
		}
	}
	return distance;
}

static avl_tree_iter_t avl_tree_node_prev(avl_tree_iter_t iter)
{
	// 当前结点为根节点
	if (iter.cursor->parent == iter.cursor) {
		iter.cursor = avl_tree_node_max(iter.cursor->left);
		iter.index = 0;
		return iter;
	}

	// 当前结点可继续索引
	if (iter.index < vector_size(iter.cursor->vector) - 1) {
		iter.index++;
		return iter;
	}
	
	// 当前结点有左子树
	if (iter.cursor->left != NULL) {
		iter.cursor = avl_tree_node_max(iter.cursor->left);
		iter.index = 0;
		return iter;
	}

	// 当前结点无左子树
	while (iter.cursor->parent->left == iter.cursor) {
		iter.cursor = iter.cursor->parent;
	}
	iter.cursor = iter.cursor->parent;
	iter.index = 0;
	return iter;
}

static avl_tree_iter_t avl_tree_node_next(avl_tree_iter_t iter)
{
	// 当前结点为根节点
	if (iter.cursor->parent == iter.cursor) {
		iter.cursor = avl_tree_node_min(iter.cursor->left);
		iter.index = 0;
		return iter;
	}

	// 当前结点可索引
	if (iter.index < vector_size(iter.cursor->vector) - 1) {
		iter.index++;
		return iter;
	}
	
	// 当前结点有右子树
	if (iter.cursor->right != NULL) {
		iter.cursor = avl_tree_node_min(iter.cursor->right);
		iter.index = 0;
		return iter;
	}

	// 当前结点无右子树
	while (iter.cursor->parent->right == iter.cursor) {
		iter.cursor = iter.cursor->parent;
	}
	iter.cursor = iter.cursor->parent;
	iter.index = 0;
	return iter;
}

avl_tree_iter_t avl_tree_prev(avl_tree_iter_t iter)
{
	if (!iter.reverse) {
		return avl_tree_node_prev(iter);
	} else {
		return avl_tree_node_next(iter);
	}
}

avl_tree_iter_t avl_tree_next(avl_tree_iter_t iter)
{
	if (!iter.reverse) {
		return avl_tree_node_next(iter);
	} else {
		return avl_tree_node_prev(iter);
	}
}

avl_tree_iter_t avl_tree_advance(avl_tree_iter_t iter, ptrdiff_t distance)
{
	if (iter.reverse) {
		distance = -distance;
	}

	while (distance < 0) {
		iter = avl_tree_node_prev(iter);
		distance++;
	}

	while (distance > 0) {
		iter = avl_tree_node_next(iter);
		distance--;
	}

	return iter;
}

