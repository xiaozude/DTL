/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: heap.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 堆（容器适配器）
 *
 *****************************************************************/

#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void heap_adjust(heap_t *pheap, size_t root)
{
	assert(pheap != NULL);

	void *root_data = malloc(pheap->vector.size);
	if (root_data == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memcpy(root_data, vector_index(pheap->vector, root), pheap->vector.size);

	size_t count = vector_size(pheap->vector);
	for (size_t index = ((root + 1) << 1) - 1; index < count;
			root = index, index = ((index + 1) << 1) - 1) {
		void *left_data = vector_index(pheap->vector, index);
		void *right_data = NULL;
		if (index + 1 < count) {
			right_data = vector_index(pheap->vector, index + 1);
		}

		void *index_data = left_data;
		if (right_data != NULL && pheap->compar(left_data, right_data) < 0) {
			index_data = right_data;
			index++;
		}

		if (pheap->compar(root_data, index_data) >= 0) {
			break;
		}

		memcpy(vector_index(pheap->vector, root), index_data, pheap->vector.size);
	}
	
	memcpy(vector_index(pheap->vector, root), root_data, pheap->vector.size);
	free(root_data);
}

void heap_init(heap_t *pheap, size_t size, int (*compar)(const void *, const void *))
{
	assert(pheap != NULL);
	assert(size > 0);

	vector_init(&pheap->vector, size);
	pheap->compar = compar;
}

void heap_free(heap_t *pheap)
{
	assert(pheap != NULL);

	vector_free(&pheap->vector);
}

void *heap_top(heap_t heap)
{
	return vector_front(heap.vector);
}

bool heap_empty(heap_t heap)
{
	return vector_empty(heap.vector);
}

size_t heap_size(heap_t heap)
{
	return vector_size(heap.vector);
}

void heap_clear(heap_t *pheap)
{
	assert(pheap != NULL);

	vector_clear(&pheap->vector);
}

void heap_push(heap_t *pheap, const void *data)
{
	assert(pheap != NULL);
	assert(data != NULL);

	vector_push_back(&pheap->vector, data);
	
	size_t count = vector_size(pheap->vector);
	if (count <= 1) {
		return;
	}
	
	for (size_t root = (count >> 1) - 1; root >= 0; root = (root - 1) >> 1) {
		heap_adjust(pheap, root);
		if (root == 0) break;
	}
}

void heap_pop(heap_t *pheap)
{
	assert(pheap != NULL);

	void *front_data = vector_front(pheap->vector);
	void *back_data = vector_back(pheap->vector);
	memcpy(front_data, back_data, pheap->vector.size);
	vector_pop_back(&pheap->vector);
	
	heap_adjust(pheap, 0);
}

