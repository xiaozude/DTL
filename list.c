/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: list.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 双向环状链表（容器）
 *
 *****************************************************************/

#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static list_node_t *list_node_init(const void *data, size_t size)
{
	assert(size > 0);

	list_node_t *p = NULL;
	if ((p = (list_node_t *) malloc(sizeof(*p))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memset(p, 0, sizeof(*p));

	if ((p->data = malloc(size)) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	if (data == NULL) {
		memset(p->data, 0, size);
	} else {
		memcpy(p->data, data, size);
	}
	
	return p;
}

static void list_node_free(list_node_t *p)
{
	if (p == NULL) {
		return;
	}
	
	free(p->data);
	free(p);
}

list_t *list_init(size_t size)
{
	assert(size > 0);

	list_t *this = NULL;
	if ((this = (list_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	this->size = size;
	this->count = 0;
	this->root = list_node_init(NULL, this->size);
	this->root->prev = this->root;
	this->root->next = this->root;

	return this;
}

void list_free(list_t *this)
{
	if (this == NULL) {
		return;
	}

	list_clear(this);
	list_node_free(this->root);
	free(this);
}

void *list_front(list_t *this)
{
	assert(this != NULL);

	return this->root->next->data;
}

void *list_back(list_t *this)
{
	assert(this != NULL);

	return this->root->prev->data;
}

bool list_empty(list_t *this)
{
	assert(this != NULL);

	return this->count == 0;
}

size_t list_size(list_t *this)
{
	assert(this != NULL);

	return this->count;
}

void list_clear(list_t *this)
{
	assert(this != NULL);

	struct list_node *p = NULL;
	while ((p = this->root->next) != this->root) {
		this->root->next = p->next;
		list_node_free(p);
	}

	this->count = 0;
	this->root->prev = this->root;
	this->root->next = this->root;
}

void list_insert(list_t *this, list_iter_t iter, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);
	assert(this->size == iter.size);
	
	list_node_t *p = iter.cursor;
	list_node_t *q = list_node_init(data, this->size);
	q->prev = p->prev;
	q->next = p;
	p->prev->next = q;
	p->prev = q;
	this->count++;
}

void list_erase(list_t *this, list_iter_t iter)
{
	assert(this != NULL);
	assert(this->size == iter.size);
	assert(!list_empty(this));
	
	list_node_t *p = iter.cursor;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list_node_free(p);
	this->count--;
}

void list_push_front(list_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	list_node_t *p = list_node_init(data, this->size);
	p->prev = this->root;
	p->next = this->root->next;
	this->root->next->prev = p;
	this->root->next = p;
	this->count++;
}

void list_pop_front(list_t *this)
{
	assert(this != NULL);
	assert(!list_empty(this));

	list_node_t *p = this->root->next;
	p->next->prev = this->root;
	this->root->next = p->next;
	list_node_free(p);
	this->count--;
}

void list_push_back(list_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	list_node_t *p = list_node_init(data, this->size);
	p->prev = this->root->prev;
	p->next = this->root;
	this->root->prev->next = p;
	this->root->prev = p;
	this->count++;
}

void list_pop_back(list_t *this)
{
	assert(this != NULL);
	assert(!list_empty(this));

	list_node_t *p = this->root->prev;
	p->prev->next = this->root;
	this->root->prev = p->prev;
	list_node_free(p);
	this->count--;
}

list_iter_t list_begin(list_t *this)
{
	assert(this != NULL);

	return (list_iter_t) { this->size, this->root->next, false };
}

list_iter_t list_end(list_t *this)
{
	assert(this != NULL);

	return (list_iter_t) { this->size, this->root, false };
}

list_iter_t list_rbegin(list_t *this)
{
	assert(this != NULL);

	return (list_iter_t) { this->size, this->root->prev, true };
}

list_iter_t list_rend(list_t *this)
{
	assert(this != NULL);

	return (list_iter_t) { this->size, this->root, true };
}

void *list_data(list_iter_t iter)
{
	return iter.cursor->data;
}

bool list_equal(list_iter_t iter1, list_iter_t iter2)
{
	assert(iter1.size == iter2.size);
	assert(iter1.reverse == iter2.reverse);

	return list_distance(iter1, iter2) == 0;
}

ptrdiff_t list_distance(list_iter_t first, list_iter_t last)
{
	assert(first.size == last.size);
	assert(first.reverse == last.reverse);

	ptrdiff_t distance = 0;
	if (!first.reverse) {
		while (first.cursor != last.cursor) {
			first.cursor = first.cursor->next;
			distance++;
		}
	} else {
		while (first.cursor != last.cursor) {
			first.cursor = first.cursor->prev;
			distance++;
		}
	}
	return distance;
}

list_iter_t list_prev(list_iter_t iter)
{
	return list_advance(iter, -1);
}

list_iter_t list_next(list_iter_t iter)
{
	return list_advance(iter, 1);
}

list_iter_t list_advance(list_iter_t iter, ptrdiff_t distance)
{
	if (iter.reverse) {
		distance = -distance;
	}

	while (distance < 0) {
		iter.cursor = iter.cursor->prev;
		distance++;
	}

	while (distance > 0) {
		iter.cursor = iter.cursor->next;
		distance--;
	}

	return iter;
}

