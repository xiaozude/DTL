/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: vector.c
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 动态数组（容器）
 *
 *****************************************************************/

#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector_t *vector_init(size_t size)
{
	assert(size > 0);

	vector_t *this = NULL;
	if ((this = (vector_t *) malloc(sizeof(*this))) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	void *elems = NULL;
	if ((elems = malloc(size)) == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	this->size = size;
	this->start = elems;
	this->finish = this->start;
	this->cliff = this->start + size;

	return this;
}

void vector_free(vector_t *this)
{
	if (this == NULL) {
		return;
	}

	free(this->start);
	free(this);
}

void *vector_front(vector_t *this)
{
	assert(this != NULL);
	assert(!vector_empty(this));

	return this->start;
}

void *vector_back(vector_t *this)
{
	assert(this != NULL);
	assert(!vector_empty(this));

	return this->finish - this->size;
}

void *vector_index(vector_t *this, size_t index)
{
	assert(this != NULL);
	assert(index < vector_size(this));

	return this->start + index * this->size;
}

bool vector_empty(vector_t *this)
{
	assert(this != NULL);

	return this->finish == this->start;
}

size_t vector_size(vector_t *this)
{
	assert(this != NULL);

	return (this->finish - this->start) / this->size;
}

size_t vector_capacity(vector_t *this)
{
	assert(this != NULL);

	return (this->cliff - this->start) / this->size;
}

void vector_clear(vector_t *this)
{
	assert(this != NULL);

	this->finish = this->start;
}

void vector_insert(vector_t *this, size_t index, const void *data)
{
	assert(this != NULL);
	assert(index <= vector_size(this));
	assert(data != NULL);

	size_t size = this->finish - this->start;
	size_t left_size = index * this->size;
	size_t right_size = size - left_size;
	
	if (this->finish == this->cliff) {	
		void *elems = NULL;
		if ((elems = malloc(size << 1)) == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		memcpy(elems, this->start, left_size);
		memcpy(elems + left_size, data, this->size);
		memcpy(elems + left_size + this->size, this->start + left_size, right_size);

		free(this->start);
		
		this->start = elems;
		this->finish = this->start + size + this->size;
		this->cliff = this->start + (size << 1);
		
		return;
	}
	
	memmove(this->start + left_size + this->size, this->start + left_size, right_size);
	memcpy(this->start + left_size, data, this->size);
	this->finish += this->size;
}

void vector_erase(vector_t *this, size_t index)
{
	assert(this != NULL);
	assert(index < vector_size(this));
	
	size_t size = this->finish - this->start;
	size_t left_size = index * this->size;
	size_t right_size = size - left_size - this->size;

	memmove(this->start + left_size, this->finish - right_size, right_size);
	this->finish -= this->size;
}

void vector_push_back(vector_t *this, const void *data)
{
	assert(this != NULL);
	assert(data != NULL);

	if (this->finish == this->cliff) {
		vector_insert(this, vector_size(this), data);
		return;
	}
	
	memcpy(this->finish, data, this->size);	
	this->finish += this->size;
}

void vector_pop_back(vector_t *this)
{
	assert(this != NULL);
	assert(!vector_empty(this));

	this->finish -= this->size;
}

vector_iter_t vector_begin(vector_t *this)
{
	assert(this != NULL);

	return (vector_iter_t) { this->size, this->start, false };
}

vector_iter_t vector_end(vector_t *this)
{
	assert(this != NULL);

	return (vector_iter_t) { this->size, this->finish, false };
}

vector_iter_t vector_rbegin(vector_t *this)
{
	assert(this != NULL);

	return (vector_iter_t) { this->size, this->finish, true };
}

vector_iter_t vector_rend(vector_t *this)
{
	assert(this != NULL);

	return (vector_iter_t) { this->size, this->start, true };
}

void *vector_data(vector_iter_t iter)
{
	if (!iter.reverse) {
		return iter.cursor;
	} else {
		return iter.cursor - iter.size;
	}
}

bool vector_equal(vector_iter_t iter1, vector_iter_t iter2)
{
	assert(iter1.size == iter2.size);
	assert(iter1.reverse == iter2.reverse);

	return vector_distance(iter1, iter2) == 0;
}

ptrdiff_t vector_distance(vector_iter_t first, vector_iter_t last)
{
	assert(first.size == last.size);
	assert(first.reverse == last.reverse);

	if (!first.reverse) {
		return (last.cursor - first.cursor) / first.size;
	} else {
		return (first.cursor - last.cursor) / first.size;
	}
}

vector_iter_t vector_prev(vector_iter_t iter)
{
	return vector_advance(iter, -1);
}

vector_iter_t vector_next(vector_iter_t iter)
{
	return vector_advance(iter, 1);
}

vector_iter_t vector_advance(vector_iter_t iter, ptrdiff_t distance)
{
	if (!iter.reverse) {
		iter.cursor += distance * iter.size;
	} else {
		iter.cursor -= distance * iter.size;
	}
	return iter;
}

