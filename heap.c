/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: heap.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 堆（容器适配器）
 *
 *****************************************************************/

#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

heap_t *heap_init(size_t size, int (*compar)(const void *, const void *))
{
	assert(size > 0);
	assert(compar != NULL);

	heap_t *this = NULL;
	if ((this = (heap_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	this->vector = vector_init(size);
	this->compar = compar;
	return this;
}

void heap_free(heap_t *this)
{
	if (this == NULL) {
		return;
	}

	vector_free(this->vector);
	free(this);
}

void *heap_top(heap_t *this)
{
	assert(this != NULL);

	return vector_front(this->vector);
}

bool heap_empty(heap_t *this)
{
	assert(this != NULL);

	return heap_size(this) == 0;
}

size_t heap_size(heap_t *this)
{
	assert(this != NULL);

	return vector_size(this->vector);
}

void heap_clear(heap_t *this)
{
	assert(this != NULL);

	vector_clear(this->vector);
}

static void heap_adjust(heap_t *this, size_t root)
{
	assert(this != NULL);

	void *root_data = malloc(this->vector->size);
	if (root_data == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memcpy(root_data, vector_index(this->vector, root), this->vector->size);

	size_t count = vector_size(this->vector);
	for (size_t index = ((root + 1) << 1) - 1; index < count;
			root = index, index = ((index + 1) << 1) - 1) {
		void *left_data = vector_index(this->vector, index);
		void *right_data = NULL;
		if (index + 1 < count) {
			right_data = vector_index(this->vector, index + 1);
		}

		void *index_data = left_data;
		if (right_data != NULL && this->compar(left_data, right_data) < 0) {
			index_data = right_data;
			index++;
		}

		if (this->compar(root_data, index_data) >= 0) {
			break;
		}

		memcpy(vector_index(this->vector, root), index_data, this->vector->size);
	}
	
	memcpy(vector_index(this->vector, root), root_data, this->vector->size);
	free(root_data);
}

void heap_push(heap_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	vector_push_back(this->vector, data);
	
	size_t count = vector_size(this->vector);
	if (count <= 1) {
		return;
	}
	
	for (size_t root = (count >> 1) - 1; root >= 0; root = (root - 1) >> 1) {
		heap_adjust(this, root);
		if (root == 0) break;
	}
}

void heap_pop(heap_t *this)
{
	assert(this != NULL);
	assert(!heap_empty(this));

	void *front_data = vector_front(this->vector);
	void *back_data = vector_back(this->vector);
	memcpy(front_data, back_data, this->vector->size);
	vector_pop_back(this->vector);
	
	heap_adjust(this, 0);
}

