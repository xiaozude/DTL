/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: avl_tree.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-14
 *  Description: 平衡二叉树（容器）
 *
 *****************************************************************/

#include "avl_tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct avl_tree_node *avl_tree_node_init(size_t size, const void *data)
{
	assert(size > 0);

	struct avl_tree_node *p = NULL;
	if ((p = (struct avl_tree_node *) calloc(1, sizeof(*p))) == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	p->height = 1;

	vector_init(&p->vector, size);
	vector_push_back(&p->vector, data);

	return p;
}

static void avl_tree_node_free(struct avl_tree_node *p)
{
	if (p == NULL) {
		return;
	}

	vector_free(&p->vector);
	free(p);
}

static size_t avl_tree_node_height(struct avl_tree_node *p)
{
	if (p == NULL) {
		return 0;
	}

	return p->height;
}

static void avl_tree_node_clear(struct avl_tree_node **p)
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

static struct avl_tree_node *avl_tree_node_find(
		struct avl_tree_node *p, const void *data,
		int (*compar)(const void *, const void *),
		struct avl_tree_node **parent)
{
	assert(data != NULL);
	
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

static struct avl_tree_node *avl_tree_node_min(struct avl_tree_node *p)
{
	if (p == NULL || p->left == NULL) {
		return p;
	}

	while (p->left != NULL) {
		p = p->left;
	}

	return p;
}

static struct avl_tree_node *avl_tree_node_max(struct avl_tree_node *p)
{
	if (p == NULL || p->right == NULL) {
		return p;
	}

	while (p->right != NULL) {
		p = p->right;
	}

	return p;
}

static void avl_tree_node_rotate_left(struct avl_tree_node **p)
{
	assert(p != NULL);

	if (*p == NULL) {
		return;
	}

	struct avl_tree_node *q = *p;
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

static void avl_tree_node_rotate_right(struct avl_tree_node **p)
{
	assert(p != NULL);

	if (*p == NULL) {
		return;
	}

	struct avl_tree_node *q = *p;
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

static void avl_tree_node_balance(struct avl_tree_node **p)
{
	assert(p != NULL);

	if (*p == NULL) {
		return;
	}

	struct avl_tree_node *left = (*p)->left;
	struct avl_tree_node *right = (*p)->right;
	
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

static bool avl_tree_node_insert(struct avl_tree_node **root, bool unique, size_t size,
		const void *data, int (*compar)(const void *, const void *))
{
	assert(root != NULL);
	assert(data != NULL);
	assert(size > 0);
	
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
	struct avl_tree_node *parent = NULL;
	struct avl_tree_node *node = avl_tree_node_find((*root)->left, data, compar, &parent);
	if (parent == NULL) {
		return false;
	}

	// 节点存在
	if (node != NULL) {
		if (unique) {
			return false;
		}
		vector_push_back(&node->vector, data);
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
	for (struct avl_tree_node *p = parent; p != *root; p = p->parent) {
		if (p->parent->left == p) {
			avl_tree_node_balance(&p->parent->left);
		} else {
			avl_tree_node_balance(&p->parent->right);
		}
	}

	return true;
}

static bool avl_tree_node_erase(struct avl_tree_node **root, const void *data,
		int (*compar)(const void *, const void *))
{
	assert(root != NULL);
	assert(data != NULL);
	
	if (*root == NULL) {
		return false;
	}

	// 寻找删除位置
	struct avl_tree_node *node = avl_tree_node_find((*root)->left, data, compar, NULL);
	struct avl_tree_node *parent = NULL;
	if (node == NULL) {
		return false;
	}

	// 左子树不为空
	if (node->left != NULL) {
		// 寻找交换结点，交换数据
		parent = node;
		node = avl_tree_node_max(node->left);
		vector_t x = node->vector;
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
		vector_t x = node->vector;
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
	for (struct avl_tree_node *p = parent; p != *root; p = p->parent) {
		if (p->parent->left == p) {
			avl_tree_node_balance(&p->parent->left);
		} else {
			avl_tree_node_balance(&p->parent->right);
		}
	}

	return true;
}

void avl_tree_init(avl_tree_t *ptree, size_t size, int (*compar)(const void *, const void *))
{
	assert(ptree != NULL);

	ptree->size = size;
	ptree->count = 0;
	ptree->root = avl_tree_node_init(size, NULL);
	ptree->root->parent = ptree->root;
	ptree->compar = compar;
}

void avl_tree_free(avl_tree_t *ptree)
{
	assert(ptree != NULL);

	avl_tree_node_clear(&ptree->root->left);
	avl_tree_node_free(ptree->root);

	ptree->count = 0;
	ptree->root = NULL;
}

void *avl_tree_index(avl_tree_t tree, const void *data, size_t index)
{
	assert(data != NULL);

	struct avl_tree_node *node = avl_tree_node_find(tree.root->left, data, tree.compar, NULL);
	if (node == NULL) {
		return NULL;
	}
	return vector_index(node->vector, index) + index * tree.size;
}

size_t avl_tree_count(avl_tree_t tree, const void *data)
{
	assert(data != NULL);

	struct avl_tree_node *node = avl_tree_node_find(tree.root->left, data, tree.compar, NULL);
	if (node == NULL) {
		return 0;
	}
	return vector_size(node->vector);
}

bool avl_tree_empty(avl_tree_t tree)
{
	return tree.count <= 0;
}

size_t avl_tree_size(avl_tree_t tree)
{
	return tree.count;
}

void avl_tree_clear(avl_tree_t *ptree)
{
	assert(ptree != NULL);

	avl_tree_node_clear(&ptree->root->left);

	ptree->count = 0;
}

bool avl_tree_insert(avl_tree_t *ptree, bool unique, const void *data)
{
	assert(ptree != NULL);
	assert(data != NULL);

	if (avl_tree_node_insert(&ptree->root, unique, ptree->size, data, ptree->compar)) {
		ptree->count++;
		return true;
	}
	return false;
}

bool avl_tree_erase(avl_tree_t *ptree, const void *data)
{
	assert(ptree != NULL);
	assert(data != NULL);

	if (avl_tree_node_erase(&ptree->root, data, ptree->compar)) {
		ptree->count--;
		return true;
	}
	return false;
}

static void *avl_tree_iterator_data(iterator_t it)
{
	return vector_index(((struct avl_tree_node *) it.current)->vector, it.index);
}

static iterator_t avl_tree_iterator_prev(iterator_t it)
{
	struct avl_tree_node *current = (struct avl_tree_node *) it.current;

	// 当前结点为根节点
	if (current->parent == current) {
		it.current = avl_tree_node_max(current->left);
		it.index = 0;
		return it;
	}

	// 当前结点可继续索引
	if (it.index < vector_size(current->vector) - 1) {
		it.index++;
		return it;
	}
	
	// 当前结点有左子树
	if (current->left != NULL) {
		it.current = avl_tree_node_max(current->left);
		it.index = 0;
		return it;
	}

	// 当前结点无左子树
	while (current->parent->left == current) {
		current = current->parent;
	}
	it.current = current->parent;
	it.index = 0;
	return it;
}

static iterator_t avl_tree_iterator_next(iterator_t it)
{
	struct avl_tree_node *current = (struct avl_tree_node *) it.current;

	// 当前结点为根节点
	if (current->parent == current) {
		it.current = avl_tree_node_min(current->left);
		it.index = 0;
		return it;
	}

	// 当前结点可索引
	if (it.index < vector_size(current->vector) - 1) {
		it.index++;
		return it;
	}
	
	// 当前结点有右子树
	if (current->right != NULL) {
		it.current = avl_tree_node_min(current->right);
		it.index = 0;
		return it;
	}

	// 当前结点无右子树
	while (current->parent->right == current) {
		current = current->parent;
	}
	it.current = current->parent;
	it.index = 0;
	return it;
}

static iterator_t avl_tree_iterator(avl_tree_t tree, bool reverse, void *current)
{
	iterator_t it;
	it.size = tree.size;
	it.index = 0;
	it.current = current;
	it.reverse = reverse;
	it.category = bidirectional_iterator_tag;
	it.data = avl_tree_iterator_data;
	it.prev = avl_tree_iterator_prev;
	it.next = avl_tree_iterator_next;
	return it;
}

iterator_t avl_tree_begin(avl_tree_t tree)
{
	return avl_tree_iterator(tree, false, avl_tree_node_min(tree.root->left));
}

iterator_t avl_tree_end(avl_tree_t tree)
{
	return avl_tree_iterator(tree, false, tree.root);
}

iterator_t avl_tree_rbegin(avl_tree_t tree)
{
	return avl_tree_iterator(tree, true, avl_tree_node_max(tree.root->left));
}

iterator_t avl_tree_rend(avl_tree_t tree)
{
	return avl_tree_iterator(tree, true, tree.root);
}

