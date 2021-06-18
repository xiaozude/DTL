/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: array.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 静态数组（容器）
 *
 *****************************************************************/

#include "array.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void array_init(array_t *parray, size_t size, size_t count)
{
	assert(parray != NULL);
	assert(size > 0);

	void *elems = calloc(count, size);
	if (elems == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	parray->size = size;
	parray->elems = elems;
	parray->cliff = parray->elems + count * size;
	parray->start = parray->elems;
	parray->finish = parray->cliff;
}

void array_free(array_t *parray)
{
	assert(parray != NULL);

	free(parray->elems);
	
	parray->elems = NULL;
	parray->cliff = NULL;
	parray->start = NULL;
	parray->finish = NULL;
}

void *array_front(array_t array)
{
	return array.start;
}

void *array_back(array_t array)
{
	return array.finish - array.size;
}

void *array_index(array_t array, size_t index)
{
	return array.start + index * array.size;
}

bool array_empty(array_t array)
{
	return array.start == array.finish;
}

size_t array_size(array_t array)
{
	return (array.finish - array.start) / array.size;
}

static void *array_iterator_data(iterator_t it)
{
	return !it.reverse ? it.current : it.current - it.size;
}

static iterator_t array_iterator(array_t array, bool reverse, void *current)
{
	iterator_t it;
	it.size = array.size;
	it.current = current;
	it.reverse = reverse;
	it.category = random_access_iterator_tag;
	it.data = array_iterator_data;
	it.prev = NULL;
	it.next = NULL;
	return it;
}

iterator_t array_begin(array_t array)
{
	return array_iterator(array, false, array.start);
}

iterator_t array_end(array_t array)
{
	return array_iterator(array, false, array.finish);
}

iterator_t array_rbegin(array_t array)
{
	return array_iterator(array, true, array.finish);
}

iterator_t array_rend(array_t array)
{
	return array_iterator(array, true, array.start);
}

