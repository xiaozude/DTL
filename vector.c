/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: vector.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 动态数组（容器）
 *
 *****************************************************************/

#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void vector_expand(vector_t *pvector, size_t times)
{
	assert(pvector != NULL);

	if (times == 0) {
		return;
	}
	
	size_t length_size = (pvector->cliff - pvector->elems) << times;
	size_t count_size = pvector->finish - pvector->start;

	void *elems = realloc(pvector->elems, length_size);
	if (elems == NULL) {
		perror("realloc");
		exit(EXIT_FAILURE);
	}

	pvector->elems = elems;
	pvector->cliff = pvector->elems + length_size;
	pvector->start = pvector->elems;
	pvector->finish = pvector->start + count_size;
}

void vector_init(vector_t *pvector, size_t size)
{
	assert(pvector != NULL);
	assert(size > 0);

	void *elems = calloc(1, size);
	if (elems == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	pvector->size = size;
	pvector->elems = elems;
	pvector->cliff = pvector->elems + size;
	pvector->start = pvector->elems;
	pvector->finish = pvector->start;
}

void vector_free(vector_t *pvector)
{
	assert(pvector != NULL);

	free(pvector->elems);
	
	pvector->elems = NULL;
	pvector->cliff = NULL;
	pvector->start = NULL;
	pvector->finish = NULL;
}

void *vector_front(vector_t vector)
{
	return vector.start;
}

void *vector_back(vector_t vector)
{
	return vector.finish - vector.size;
}

void *vector_index(vector_t vector, size_t index)
{
	return vector.start + index * vector.size;
}

bool vector_empty(vector_t vector)
{
	return vector.start == vector.finish;
}

size_t vector_size(vector_t vector)
{
	return (vector.finish - vector.start) / vector.size;
}

void vector_clear(vector_t *pvector)
{
	assert(pvector != NULL);

	pvector->finish = pvector->start;
}

void vector_insert(vector_t *pvector, size_t index, const void *data)
{
	assert(pvector != NULL);
	assert(data != NULL);

	if (pvector->finish == pvector->cliff) {	
		vector_expand(pvector, 1);
	}

	void *cursor = pvector->start + index * pvector->size;
	memmove(cursor + pvector->size, cursor, pvector->finish - cursor);
	memcpy(cursor, data, pvector->size);
	pvector->finish += pvector->size;
}

void vector_erase(vector_t *pvector, size_t index)
{
	assert(pvector != NULL);
	
	void *cursor = pvector->start + index * pvector->size;
	size_t move_size = pvector->finish - cursor - pvector->size;
	memmove(cursor, cursor + pvector->size, move_size);
	pvector->finish -= pvector->size;
}

void vector_push_back(vector_t *pvector, const void *data)
{
	assert(pvector != NULL);
	assert(data != NULL);

	if (pvector->finish == pvector->cliff) {
		vector_expand(pvector, 1);
	}

	memcpy(pvector->finish, data, pvector->size);	
	pvector->finish += pvector->size;
}

void vector_pop_back(vector_t *pvector)
{
	assert(pvector != NULL);

	pvector->finish -= pvector->size;
}

static void *vector_iterator_data(iterator_t it)
{
	return !it.reverse ? it.current : it.current - it.size;
}

static iterator_t vector_iterator(vector_t vector, bool reverse, void *current)
{
	iterator_t it;
	it.size = vector.size;
	it.current = current;
	it.reverse = reverse;
	it.category = random_access_iterator_tag;
	it.data = vector_iterator_data;
	it.prev = NULL;
	it.next = NULL;
	return it;
}

iterator_t vector_begin(vector_t vector)
{
	return vector_iterator(vector, false, vector.start);
}

iterator_t vector_end(vector_t vector)
{
	return vector_iterator(vector, false, vector.finish);
}

iterator_t vector_rbegin(vector_t vector)
{
	return vector_iterator(vector, true, vector.finish);
}

iterator_t vector_rend(vector_t vector)
{
	return vector_iterator(vector, true, vector.start);
}

