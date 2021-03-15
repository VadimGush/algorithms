/**
 * LIFO queue (stack), FIFO queue and deque
 */
#pragma once
#include "vector.h"

/**
 * LIFO queue
 */
struct stack {
  struct vector data;
};

struct stack stack_create();

void stack_push(struct stack*, int value);

int stack_pop(struct stack*);

size_t stack_size(struct stack*);

/**
 * FIFO queue
 */
struct queue {
  struct vector data;
  size_t size;
  size_t head;
  size_t tail;
};

struct queue queue_create();

void queue_push_back(struct queue*, int value);

/**
 * Returns an element from the front of the queue
 *
 * Moves head further:
 *
 * [] [] [] [] [] []
 *  ^
 *  head
 *
 * After insert:
 *
 * [] [] [] [] [] []
 *     ^
 *     head
 */
int queue_pop_front(struct queue*);

size_t queue_size(struct queue*);

void queue_debug_print(struct queue*);


