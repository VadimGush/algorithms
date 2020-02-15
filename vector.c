#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define INITIAL_CAPACITY 4

/*
 * Dynamic array of integers
 */
struct vector {
  int* data;
  int size;
  int capacity;
};

/**
 * Creates vector with given capacity
 *
 * @param capacity capacity of new vector
 * @return new vector with given capacity
 */
struct vector vector_create_with_capacity(int capacity) {
  struct vector result;
  
  result.capacity = capacity;
  result.size = 0;
  result.data = malloc(result.capacity * sizeof(int));

  return result;
}

/**
 * Creates vector
 *
 * @return new vector
 */
struct vector vector_create() {
  return vector_create_with_capacity(INITIAL_CAPACITY);
}

/**
 * Inserts an element at the back of the vector
 * Time complexity: O(1)
 *
 * @param vec vector
 * @param element new element
 */
void vector_push(struct vector* vec, int element) {
  if (vec->size == vec->capacity) {
    int* temp = malloc(vec->capacity * 2 * sizeof(int));
    for (int i = 0; i < vec->capacity; i++) {
      temp[i] = vec->data[i];
    }
    free(vec->data);
    vec->data = temp;
    vec->capacity *= 2;
  }

  vec->data[vec->size] = element;
  vec->size++;
}

/**
 * Removes last element from the back of the vector
 * Time complexity: O(1)
 *
 * @param vec vector
 */
void vector_pop(struct vector* vec) {
  if (vec->size > 0) {
    vec->size--;
  }
}

/**
 * Prints content of the vector
 *
 * @param vec vector
 */
void vector_print(struct vector* vec) {
  printf("[ ");
  for (int i = 0; i < vec->size; ++i) {
    printf("%d ", vec->data[i]);
  }
  printf("] siz = %d, cap = %d\n", vec->size, vec->capacity);
}

/**
 * Returns index of given element or -1 if element is not found
 * Time complexity: O(N)
 *
 * @param this vector
 * @param element searched element
 * @return index of element in vector
 */
int vector_find(struct vector* this, int element) {
    for (int i = 0; i < this->size; ++i) {
        if (this->data[i] == element)
            return i;
    }
    return -1;
}

/**
 * Inverts vector
 * Time complexity: O(N/2)
 *
 * @param this vector
 */
void vector_invert(struct vector* this) {
    for (int i = 0; i < this->size / 2; i++) {
        swap(&this->data[i], &this->data[this->size - 1 - i]);
    }
}

/**
 * Shifts all elements of vector to left
 * Time complexity: O(N)
 *
 * @param this vector
 */
void vector_shift_left(struct vector* this) {
    if (this->size == 0) return;

    int temp = this->data[0];
    for (int i = 0; i < this->size - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    this->data[this->size - 1] = temp;
}

/**
 * Shifts all elements of vector to right
 * Time complexity: O(N)
 *
 * @param this vector
 */
void vector_shift_right(struct vector* this) {
    int size = this->size;
    if (size == 0) return;

    int temp = this->data[size-1];
    for (int i = size-1; i >= 1; --i) {
        this->data[i] = this->data[i-1];
    }
    this->data[0] = temp;
}

/**
 * Insert sort
 * Time complexity: O(N^2)
 *
 * @param this vector
 */
void vector_insert_sort(struct vector* this) {
  for (int i = 0; i < this->size; i++) {
    for (int c = i; c >= 1; c--) {
      if (this->data[c] < this->data[c - 1])
        swap(&this->data[c], &this->data[c - 1]);
      else break;
    }
  }
}
