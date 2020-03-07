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

/**
 * Choice sort
 * Time complexity: O(N^2)
 *
 * @param this vector
 */
void vector_choice_sort(struct vector* this) {
  for (int i = 0; i < this->size - 1; i++) {
    for (int c = i + 1; c < this->size; c++) {
      if (this->data[c] < this->data[i])
        swap(&this->data[c], &this->data[i]);
    }
  }
}

/**
 * Bubble sort
 * Time complexity: O(N^2)
 *
 * @param this vector
 */
void vector_bubble_sort(struct vector* this) {
  for (int i = 0; i < this->size; i++) {
    bool was_swap = false;
    for (int c = 0; c < this->size - 1; c++) {
      if (this->data[c + 1] < this->data[c]) {
        swap(&this->data[c + 1], &this->data[c]);
        was_swap = true;
      }
    }
    if (!was_swap) return;
  }
}

/**
 * Finds value of maximum element in the vector
 * Time complexity: O(N)
 *
 * @param this vector
 * @return max value
 */
int vector_max(struct vector* this) {
  int max = this->data[0];
  for (int i = 1; i < this->size; ++i) {
    if (this->data[i] > max) max = this->data[i];
  }
  return max;
}

/**
 * Finds value of minimum element in the vector
 * Time complexity: O(N)
 *
 * @param this vector
 * @return min value
 */
int vector_min(struct vector* this) {
  int min = this->data[0];
  for (int i = 1; i < this->size; ++i) {
    if (this->data[i] < min) min = this->data[i];
  }
  return min;
}

/**
 * Count sort
 * Time complexity: O(N)
 * Space complexity: O(max - min)
 *
 * @param this vector
 */
void vector_count_sort(struct vector* this) {
  int min = vector_min(this);
  int max = vector_max(this);
  int stats_size = max - min + 1;
  int* stats = malloc(sizeof(int) * stats_size);

  // initialize array with zeros
  for (int i = 0; i < stats_size; ++i) {
    stats[i] = 0;
  }

  // calculate stats
  for (int i = 0; i < this->size; ++i) {
    stats[this->data[i] - min]++;
  }

  int last_insert = 0;
  for (int i = 0; i < stats_size; ++i) {
    for (int x = 0; x < stats[i]; x++) {
      this->data[last_insert] = min + i;
      last_insert++;
    }
  }
}
