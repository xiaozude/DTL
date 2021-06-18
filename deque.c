/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: deque.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 双端队列（容器）
 *
 *****************************************************************/

#include "deque.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void deque_expand(deque_t *pdeque, size_t times)
{
	assert(pdeque != NULL);

	if (times == 0) {
		return;
	}

	size_t length_size = (pdeque->cliff - pdeque->elems) << times;
	size_t count_size = pdeque->finish - pdeque->start;

	void *elems = malloc(length_size);
	if (elems == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	size_t length = length_size / pdeque->size;
	size_t count = count_size / pdeque->size;
	ptrdiff_t offset_size = ((length - count) >> 1) * pdeque->size;
	memcpy(elems + offset_size, pdeque->start, count_size);
	free(pdeque->elems);

	pdeque->elems = elems;
	pdeque->cliff = pdeque->elems + length_size;
	pdeque->start = pdeque->elems + offset_size;
	pdeque->finish = pdeque->start + count_size;
}

void deque_init(deque_t *pdeque, size_t size)
{
	assert(pdeque != NULL);
	assert(size > 0);

	void *elems = calloc(2, size);
	if (elems == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	pdeque->size = size;
	pdeque->elems = elems;
	pdeque->cliff = pdeque->elems + 2 * size;
	pdeque->start = pdeque->elems + size;
	pdeque->finish = pdeque->start;
}

void deque_free(deque_t *pdeque)
{
	assert(pdeque != NULL);

	free(pdeque->elems);
	
	pdeque->elems = NULL;
	pdeque->cliff = NULL;
	pdeque->start = NULL;
	pdeque->finish = NULL;
}

void *deque_front(deque_t deque)
{
	return deque.start;
}

void *deque_back(deque_t deque)
{
	return deque.finish - deque.size;
}

void *deque_index(deque_t deque, size_t index)
{
	return deque.start + index * deque.size;
}

bool deque_empty(deque_t deque)
{
	return deque.start == deque.finish;
}

size_t deque_size(deque_t deque)
{
	return (deque.finish - deque.start) / deque.size;
}

void deque_clear(deque_t *pdeque)
{
	assert(pdeque != NULL);

	size_t length = (pdeque->cliff - pdeque->elems) / pdeque->size;
	size_t count = (pdeque->finish - pdeque->start) / pdeque->size;
	ptrdiff_t offset_size = ((length - count) >> 1) * pdeque->size;
	pdeque->start = pdeque->elems + offset_size;
	pdeque->finish = pdeque->start;
}

void deque_insert(deque_t *pdeque, size_t index, const void *data)
{
	assert(pdeque != NULL);
	assert(data != NULL);

	if (pdeque->start == pdeque->elems && pdeque->finish == pdeque->cliff) {
		deque_expand(pdeque, 1);
	}

	if (pdeque->start - pdeque->elems > pdeque->cliff - pdeque->finish) {
		size_t move_size = index * pdeque->size;
		memmove(pdeque->start - pdeque->size, pdeque->start, move_size);
		pdeque->start -= pdeque->size;
	} else {
		void *cursor = pdeque->start + index * pdeque->size;
		size_t move_size = pdeque->finish - cursor;
		memmove(cursor + pdeque->size, cursor, move_size);
		pdeque->finish += pdeque->size;
	}

	memcpy(pdeque->start + index * pdeque->size, data, pdeque->size);
}

void deque_erase(deque_t *pdeque, size_t index)
{
	assert(pdeque != NULL);

	if (pdeque->start - pdeque->elems < pdeque->cliff - pdeque->finish) {
		size_t move_size = index * pdeque->size;
		memmove(pdeque->start + pdeque->size, pdeque->start, move_size);
		pdeque->start += pdeque->size;
	} else {
		void *cursor = pdeque->start + index * pdeque->size;
		size_t move_size = pdeque->finish - cursor - pdeque->size;
		memmove(cursor, cursor + pdeque->size, move_size);
		pdeque->finish -= pdeque->size;
	}
}

void deque_push_front(deque_t *pdeque, const void *data)
{
	assert(pdeque != NULL);
	assert(data != NULL);

	if (pdeque->start == pdeque->elems) {
		deque_expand(pdeque, 1);
	}

	memcpy(pdeque->start, data, pdeque->size);
	pdeque->start -= pdeque->size;
}

void deque_pop_front(deque_t *pdeque)
{
	assert(pdeque != NULL);
	
	pdeque->start += pdeque->size;
}

void deque_push_back(deque_t *pdeque, const void *data)
{
	assert(pdeque != NULL);
	assert(data != NULL);

	if (pdeque->finish == pdeque->cliff) {
		deque_expand(pdeque, 1);
	}

	memcpy(pdeque->finish, data, pdeque->size);
	pdeque->finish += pdeque->size;
}

void deque_pop_back(deque_t *pdeque)
{
	assert(pdeque != NULL);

	pdeque->finish -= pdeque->size;
}

static void *deque_iterator_data(iterator_t it)
{
	return !it.reverse ? it.current : it.current - it.size;
}

static iterator_t deque_iterator(deque_t deque, bool reverse, void *current)
{
	iterator_t it;
	it.size = deque.size;
	it.current = current;
	it.reverse = reverse;
	it.category = random_access_iterator_tag;
	it.data = deque_iterator_data;
	it.prev = NULL;
	it.next = NULL;
	return it;
}

iterator_t deque_begin(deque_t deque)
{
	return deque_iterator(deque, false, deque.start);
}

iterator_t deque_end(deque_t deque)
{
	return deque_iterator(deque, false, deque.finish);
}

iterator_t deque_rbegin(deque_t deque)
{
	return deque_iterator(deque, true, deque.finish);
}

iterator_t deque_rend(deque_t deque)
{
	return deque_iterator(deque, true, deque.start);
}

