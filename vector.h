/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: vector.h
 *  Author: xiaozude
 *  Version: 5.2.0
 *  Date: 2021-06-20
 *  Description: 动态数组（容器）
 *
 *****************************************************************/

#ifndef DTL_VECTOR_H
#define DTL_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct vector vector_t;
typedef struct vector_iter vector_iter_t;

struct vector {
	size_t size;
	void *start;
	void *finish;
	void *cliff;
};

struct vector_iter {
	size_t size;
	void *cursor;
	bool reverse;
};

extern vector_t *vector_init(size_t size);
extern void vector_free(vector_t *this);

extern void *vector_front(vector_t *this);
extern void *vector_back(vector_t *this);
extern void *vector_index(vector_t *this, size_t index);

extern bool vector_empty(vector_t *this);
extern size_t vector_size(vector_t *this);
extern size_t vector_capacity(vector_t *this);

extern void vector_clear(vector_t *this);
extern void vector_insert(vector_t *this, size_t index, const void *data);
extern void vector_erase(vector_t *this, size_t index);
extern void vector_push_back(vector_t *this, const void *data);
extern void vector_pop_back(vector_t *this);

extern vector_iter_t vector_begin(vector_t *this);
extern vector_iter_t vector_end(vector_t *this);
extern vector_iter_t vector_rbegin(vector_t *this);
extern vector_iter_t vector_rend(vector_t *this);

extern void *vector_data(vector_iter_t iter);
extern bool vector_equal(vector_iter_t iter1, vector_iter_t iter2);
extern ptrdiff_t vector_distance(vector_iter_t first, vector_iter_t last);

extern vector_iter_t vector_prev(vector_iter_t iter);
extern vector_iter_t vector_next(vector_iter_t iter);
extern vector_iter_t vector_advance(vector_iter_t iter, ptrdiff_t distance);

#endif // DTL_VECTOR_H

