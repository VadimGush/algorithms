#pragma once

#include "vector.h"

/**
 * LIFO queue (also known as stack)
 */
struct stack {
  struct vector data;
};

// TODO: We don't need a tail in queue and deque

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
 * Deque
 */
struct deque {
  struct vector data;
  size_t size;
  size_t head;
  size_t tail;
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
 * Creates an empty deque
 */
struct deque deque_create();

/**
 * Inserts an element to the back of the deque
 * Complexity: O(1)
 */
void deque_push_back(struct deque* deque, int value);

/**
 * Removes and returns an element from the back of deque
 * Complexity: O(1)
 */
int deque_pop_back(struct deque* deque);

/**
 * Inserts an element to the front of the deque
 * Complexity: O(1)
 */
void deque_push_front(struct deque* deque, int value);

/**
 * Removes and returns an element from the front of the deque
 */
int deque_pop_front(struct deque* deque);

/**
 * Returns size of the queue
 * 
 * @returns size of the queue
 */
size_t queue_size(struct queue*);

void queue_debug_print(struct queue*);


