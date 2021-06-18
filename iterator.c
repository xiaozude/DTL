/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: iterator.c
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 正向迭代器（迭代器）
 *
 *****************************************************************/

#include "iterator.h"
#include <assert.h>

void *iterator_data(iterator_t iterator)
{
	return iterator.data(iterator);
}

bool iterator_equal(iterator_t iterator1, iterator_t iterator2)
{
	return iterator1.current == iterator2.current;
}

static ptrdiff_t forward_iterator_distance(iterator_t first, iterator_t last)
{
	ptrdiff_t distance = 0;
	for (iterator_t it = first; !iterator_equal(it, last); it = first.next(first)) {
		distance++;
	}
	return distance;
}

static ptrdiff_t random_access_iterator_distance(iterator_t first, iterator_t last)
{
	return (last.current - first.current) / first.size;
}

ptrdiff_t iterator_distance(iterator_t first, iterator_t last)
{
	if (!first.reverse) {
		void *current = first.current;
		first.current = last.current;
		last.current = current;
	}

	ptrdiff_t distance = 0;
	switch (first.category) {
		case forward_iterator_tag:
		case bidirectional_iterator_tag:
			distance = forward_iterator_distance(first, last);
			break;
		case random_access_iterator_tag:
			distance = random_access_iterator_distance(first, last);
			break;
	}
	return distance;
}

static iterator_t forward_iterator_advance(iterator_t iterator, ptrdiff_t advance)
{
	assert(advance >= 0);

	while (advance > 0) {
		iterator = iterator.next(iterator);
		advance--;
	}

	return iterator;
}

static iterator_t bidirectional_iterator_advance(iterator_t iterator, ptrdiff_t advance)
{
	while (advance < 0) {
		iterator = iterator.prev(iterator);
		advance++;
	}

	while (advance > 0) {
		iterator = iterator.next(iterator);
		advance--;
	}

	return iterator;
}

static iterator_t random_access_iterator_advance(iterator_t iterator, ptrdiff_t advance)
{
	iterator.current += advance * iterator.size;
	return iterator;
}

iterator_t iterator_advance(iterator_t iterator, ptrdiff_t advance)
{
	if (iterator.reverse) {
		advance = -advance;
	}

	switch (iterator.category) {
		case forward_iterator_tag:
			iterator = forward_iterator_advance(iterator, advance);
			break;
		case bidirectional_iterator_tag:
			iterator = bidirectional_iterator_advance(iterator, advance);
			break;
		case random_access_iterator_tag:
			iterator = random_access_iterator_advance(iterator, advance);
			break;
	}
	
	return iterator;
}

iterator_t iterator_prev(iterator_t iterator)
{
	return iterator_advance(iterator, -1);
}

iterator_t iterator_next(iterator_t iterator)
{
	return iterator_advance(iterator, 1);
}

