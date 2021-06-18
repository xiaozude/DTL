/*****************************************************************
 *
 *  Copyright (C) 2018-2021 XZD. All rights reserved.
 *
 *  Filename: queue.h
 *  Author: xiaozude
 *  Version: 5.0.0
 *  Date: 2021-06-12
 *  Description: 队列（容器适配器）
 *
 *****************************************************************/

#ifndef DTL_QUEUE_H
#define DTL_QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "deque.h"

typedef struct queue {
	deque_t deque;
} queue_t;

extern void queue_init(queue_t *pqueue, size_t size);
extern void queue_free(queue_t *pqueue);

extern void *queue_front(queue_t queue);
extern void *queue_back(queue_t queue);

extern bool queue_empty(queue_t queue);
extern size_t queue_size(queue_t queue);

extern void queue_clear(queue_t *pqueue);
extern void queue_push(queue_t *pqueue, const void *data);
extern void queue_pop(queue_t *pqueue);

#endif // DTL_QUEUE_H

