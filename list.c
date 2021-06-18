/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: list.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 双向环状链表（容器）
 *
 *****************************************************************/

#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct list_node *list_node_init(const void *data, size_t size)
{
	assert(size > 0);

	struct list_node *p = NULL;
	if ((p = (struct list_node *) calloc(1, sizeof(*p))) == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	if ((p->data = calloc(1, size)) == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	
	if (data != NULL) {
		memcpy(p->data, data, size);
	}
	
	return p;
}

static void list_node_free(struct list_node *p)
{
	if (p == NULL) {
		return;
	}
	
	free(p->data);
	free(p);
}

void list_init(list_t *plist, size_t size)
{
	assert(plist != NULL);
	assert(size > 0);

	plist->size = size;
	plist->count = 0;
	plist->root = list_node_init(NULL, plist->size);
	plist->root->prev = plist->root;
	plist->root->next = plist->root;
}

void list_free(list_t *plist)
{
	assert(plist != NULL);

	list_clear(plist);
	list_node_free(plist->root);

	plist->count = 0;
	plist->root = NULL;
}

void *list_front(list_t list)
{
	return list.root->next->data;
}

void *list_back(list_t list)
{
	return list.root->prev->data;
}

bool list_empty(list_t list)
{
	return list.count <= 0;
}

size_t list_size(list_t list)
{
	return list.count;
}

void list_clear(list_t *plist)
{
	assert(plist != NULL);

	struct list_node *p = NULL;
	while ((p = plist->root->next) != plist->root) {
		plist->root->next = p->next;
		list_node_free(p);
	}

	plist->count = 0;
	plist->root->prev = plist->root;
	plist->root->next = plist->root;
}

void list_insert(list_t *plist, iterator_t iterator, const void *data)
{
	assert(plist != NULL);
	assert(data != NULL);
	
	struct list_node *p = (struct list_node *) iterator.current;
	struct list_node *q = list_node_init(data, plist->size);
	q->prev = p->prev;
	q->next = p;
	p->prev->next = q;
	p->prev = q;
	plist->count++;
}

void list_erase(list_t *plist, iterator_t iterator)
{
	assert(plist != NULL);
	
	struct list_node *p = (struct list_node *) iterator.current;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list_node_free(p);
	plist->count--;
}

void list_push_front(list_t *plist, const void *data)
{
	assert(plist != NULL);
	assert(data != NULL);

	struct list_node *p = list_node_init(data, plist->size);
	p->prev = plist->root;
	p->next = plist->root->next;
	plist->root->next->prev = p;
	plist->root->next = p;
	plist->count++;
}

void list_pop_front(list_t *plist)
{
	assert(plist != NULL);

	struct list_node *p = plist->root->next;
	p->next->prev = plist->root;
	plist->root->next = p->next;
	list_node_free(p);
	plist->count--;
}

void list_push_back(list_t *plist, const void *data)
{
	assert(plist != NULL);
	assert(data != NULL);

	struct list_node *p = list_node_init(data, plist->size);
	p->prev = plist->root->prev;
	p->next = plist->root;
	plist->root->prev->next = p;
	plist->root->prev = p;
	plist->count++;
}

void list_pop_back(list_t *plist)
{
	assert(plist != NULL);

	struct list_node *p = plist->root->prev;
	p->prev->next = plist->root;
	plist->root->prev = p->prev;
	list_node_free(p);
	plist->count--;
}

static void *list_iterator_data(iterator_t it)
{
	return ((struct list_node *) it.current)->data;
}

static iterator_t list_iterator_prev(iterator_t it)
{
	it.current = ((struct list_node *) it.current)->prev;
	return it;
}

static iterator_t list_iterator_next(iterator_t it)
{
	it.current = ((struct list_node *) it.current)->next;
	return it;
}

static iterator_t list_iterator(list_t list, bool reverse, void *current)
{
	iterator_t it;
	it.size = list.size;
	it.current = current;
	it.reverse = reverse;
	it.category = bidirectional_iterator_tag;
	it.data = list_iterator_data;
	it.prev = list_iterator_prev;
	it.next = list_iterator_next;
	return it;
}

iterator_t list_begin(list_t list)
{
	return list_iterator(list, false, list.root->next);
}

iterator_t list_end(list_t list)
{
	return list_iterator(list, false, list.root);
}

iterator_t list_rbegin(list_t list)
{
	return list_iterator(list, true, list.root->prev);
}

iterator_t list_rend(list_t list)
{
	return list_iterator(list, true, list.root);
}

