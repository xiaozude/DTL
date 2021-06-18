/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: iterator.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 迭代器
 *
 *****************************************************************/

#ifndef DTL_ITERATOR_H
#define DTL_ITERATOR_H

#include <stdbool.h>
#include <stddef.h>

enum iterator_category {
	forward_iterator_tag = 0x01,
	bidirectional_iterator_tag = 0x03,
	random_access_iterator_tag = 0x07
};

typedef struct iterator {
	size_t size;
	size_t index;
	void *current;
	bool reverse;
	enum iterator_category category;
	void *(*data)(struct iterator);
	struct iterator (*prev)(struct iterator);
	struct iterator (*next)(struct iterator);
} iterator_t;

extern void *iterator_data(iterator_t iterator);
extern bool iterator_equal(iterator_t iterator1, iterator_t iterator2);
extern ptrdiff_t iterator_distance(iterator_t first, iterator_t last);

extern iterator_t iterator_advance(iterator_t iterator, ptrdiff_t distance);
extern iterator_t iterator_prev(iterator_t iterator);
extern iterator_t iterator_next(iterator_t iterator);

#endif // DTL_ITERATOR_H

