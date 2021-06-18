/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: forward_list.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 单向环状链表（容器）
 *
 *****************************************************************/

#include "forward_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct forward_list_node *forward_list_node_init(const void *data, size_t size)
{
	assert(size > 0);

	struct forward_list_node *p = NULL;
	if ((p = (struct forward_list_node *) calloc(1, sizeof(*p))) == NULL) {
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

static void forward_list_node_free(struct forward_list_node *p)
{
	if (p == NULL) {
		return;
	}
	
	free(p->data);
	free(p);
}

void forward_list_init(forward_list_t *plist, size_t size)
{
	assert(plist != NULL);
	assert(size > 0);

	plist->size = size;
	plist->count = 0;
	plist->root = forward_list_node_init(NULL, plist->size);
	plist->root->next = plist->root;
}

void forward_list_free(forward_list_t *plist)
{
	assert(plist != NULL);

	forward_list_clear(plist);
	forward_list_node_free(plist->root);

	plist->count = 0;
	plist->root = NULL;
}

void *forward_list_front(forward_list_t list)
{
	return list.root->next->data;
}

bool forward_list_empty(forward_list_t list)
{
	return list.root->next == list.root;
}

size_t forward_list_size(forward_list_t list)
{
	return list.count;
}

void forward_list_clear(forward_list_t *plist)
{
	assert(plist != NULL);

	struct forward_list_node *p = NULL;
	while ((p = plist->root->next) != plist->root) {
		plist->root->next = p->next;
		forward_list_node_free(p);
	}

	plist->count = 0;
	plist->root->next = plist->root;
}

void forward_list_insert_after(forward_list_t *plist, iterator_t it, const void *data)
{
	assert(plist != NULL);
	assert(data != NULL);
	
	struct forward_list_node *p = (struct forward_list_node *) it.current;
	struct forward_list_node *q = forward_list_node_init(data, plist->size);
	q->next = p->next;
	p->next = q;
	plist->count++;
}

void forward_list_erase_after(forward_list_t *plist, iterator_t it)
{
	assert(plist != NULL);
	
	struct forward_list_node *p = (struct forward_list_node *) it.current;
	struct forward_list_node *q = p->next;
	p->next = q->next;
	forward_list_node_free(q);
	plist->count--;
}

void forward_list_push_front(forward_list_t *plist, const void *data)
{
	assert(plist != NULL);
	assert(data != NULL);

	struct forward_list_node *p = forward_list_node_init(data, plist->size);
	p->next = plist->root->next;
	plist->root->next = p;
	plist->count++;
}

void forward_list_pop_front(forward_list_t *plist)
{
	assert(plist != NULL);

	struct forward_list_node *p = plist->root->next;
	plist->root->next = p->next;
	forward_list_node_free(p);
	plist->count--;
}

static void *forward_list_iterator_data(iterator_t it)
{
	return ((struct forward_list_node *) it.current)->data;
}

static iterator_t forward_list_iterator_next(iterator_t it)
{
	it.current = ((struct forward_list_node *) it.current)->next;
	return it;
}

static iterator_t forward_list_iterator(forward_list_t list, struct forward_list_node *current)
{
	iterator_t it;
	it.size = list.size;
	it.current = current;
	it.reverse = false;
	it.category = forward_iterator_tag;
	it.data = forward_list_iterator_data;
	it.prev = NULL;
	it.next = forward_list_iterator_next;
	return it;
}

iterator_t forward_list_begin_before(forward_list_t list)
{
	return forward_list_iterator(list, list.root);
}

iterator_t forward_list_begin(forward_list_t list)
{
	return forward_list_iterator(list, list.root->next);
}

iterator_t forward_list_end(forward_list_t list)
{
	return forward_list_iterator(list, list.root);
}

