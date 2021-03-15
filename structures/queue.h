#pragma once

#include "vector.h"

/**
 * LIFO queue (also known as stack)
 */
struct stack {
  struct vector data;
};

/**
 * Creates an empty stack
 *
 * @returns empty stack
 */
struct stack stack_create();

/**
 * Inserts a new value to the end (bottom) of the stack
 * Complexity: O(1)
 *
 * @param stack - stack to modify
 * @param value - value to insert
 */
void stack_push(struct stack* stack, int value);

/**
 * Reads and removes value from the end (bottom) of the stack
 * Complexity: O(1)
 *
 * @param stack - stack to read and remove value from
 * @returns a value
 */
int stack_pop(struct stack*);

/**
 * Returns a size of the stack
 *
 * @returns size of the stack
 */
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

/**
 * Creates a new empty queue
 *
 * @returns a new queue
 */
struct queue queue_create();

/**
 * Inserts value at the end of the queue
 * Complexity: O(1)
 *
 * @param queue - queue to insert value to
 * @param value - value to insert
 */
void queue_push_back(struct queue* queue, int value);

/**
 * Reads and removes value from the beginning of the queue 
 * Complexity: O(1)
 *
 * @param queue - queue to remove value from
 * @returns value from the beginning of the queue
 */
int queue_pop_front(struct queue* queue);

/**
 * Returns size of the queue
 * 
 * @returns size of the queue
 */
size_t queue_size(struct queue*);

void queue_debug_print(struct queue*);


