#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define INITIAL_CAPACITY 4

/**
 * Vector of integers
 */
struct vector {
  int* data;
  int size;
  int capacity;
};

/**
 * View of vector
 */
struct vector_view {
  const int* data;
  const int size;
};

/**
 * Deletes content of given vector
 *
 * @param this vector
 */
void vector_delete(struct vector* this) {
  free(this->data);
  this->size = 0;
  this->capacity = 0;
}

/**
 * Creates a vector with initial capacity and returns it
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
 * Creates part of vector from given position with given size
 *
 * @param this vector
 * @param start start of a new part
 * @param size size of a new part
 * @return part of vector
 */
struct vector_view vector_get_part(struct vector* this, int start, int size) {
  struct vector_view result = { this->data + start, size};
  return result;
}

/**
 * Creates a vector with initial capacity and returns pointer to it
 *
 * @param capacity capacity of new vector
 * @return pointer to new vector
 */
struct vector* vector_create_with_capacity_ptr(int capacity) {
  struct vector* result = malloc(sizeof(struct vector));
  result->capacity = capacity;
  result->size = 0;
  result->data = malloc(result->capacity * sizeof(int));
  return result;
}

/**
 * Creates a vector and returns it
 *
 * @return new vector
 */
struct vector vector_create() {
  return vector_create_with_capacity(INITIAL_CAPACITY);
}

/**
 * Creates vector with given size (all elements are not initialized)
 *
 * @param size given size
 * @return new vector
 */
struct vector vector_create_with_size(int size) {
  struct vector result = vector_create_with_capacity(size);
  result.size = size;
  return result;
}

/**
 * Creates a vector and returns pointer to it
 *
 * @return pointer to new vector
 */
struct vector* vector_create_ptr() {
  return vector_create_with_capacity_ptr(INITIAL_CAPACITY);
}

/**
 * Inserts array of ints to the vector
 * @param vec vector
 * @param elements pointer to array of ints
 * @param size size of input array
 */
void vector_push_array(struct vector* vec, const int* const elements, const int size) {
  const int new_capacity = vec->size + size;
  if (new_capacity >= vec->capacity) {
    int* temp = malloc(sizeof(int) * new_capacity);
    for (int i = 0; i < vec->size; ++i) {
      temp[i] = vec->data[i];
    }
    free(vec->data);
    vec->data = temp;
    vec->capacity = new_capacity;
  }

  for (int i = 0; i < size; ++i) {
    vec->data[vec->size + i] = elements[i];
  }
  vec->size += size;
}

/**
 * Increase vector capacity
 * Time complexity: O(N)
 *
 * @param vec vector
 */
void vector_allocate_more(struct vector* vec) {
  int* temp = malloc(vec->capacity * 2 * sizeof(int));
  for (int i = 0; i < vec->capacity; i++) {
    temp[i] = vec->data[i];
  }
  free(vec->data);
  vec->data = temp;
  vec->capacity *= 2;
}

/**
 * Inserts an element at the back of the vector
 * Time complexity: O(1)
 *
 * @param vec vector
 * @param element new element
 */
void vector_push_back(struct vector* vec, int element) {
  if (vec->size == vec->capacity) {
    vector_allocate_more(vec);
  }

  vec->data[vec->size] = element;
  vec->size++;
}

/**
 * Inserts element in the given position
 * Time complexity: O(N)
 *
 * @param vec vector
 * @param element element to insert
 * @param id where to insert
 */
void vector_push(struct vector* const this, const int id, const int element) {
  if (this->size == this->capacity) {
    vector_allocate_more(this);
  }

  if (id == this->size) {
    vector_push_back(this, element);
    return;
  }

  int prev = element;
  for (int i = id; i <= this->size; ++i) {
    int temp = this->data[i];
    this->data[i] = prev;
    prev = temp;
  }
  this->size += 1;
}

/**
 * Removes last element from the back of the vector
 * Time complexity: O(1)
 *
 * @param vec vector
 */
void vector_pop_back(struct vector* vec) {
  if (vec->size > 0) {
    vec->size--;
  }
}

/**
 * Prints content of the vector
 *
 * @param this vector
 */
void vector_print(const struct vector* const this) {
  printf("[ ");
  for (int i = 0; i < this->size; ++i) {
    printf("%d ", this->data[i]);
  }
  printf("] siz = %d, cap = %d\n", this->size, this->capacity);
}

void vector_print_with_ids(const struct vector* const this) {
  vector_print(this);
  printf("[ ");
  for (int i = 0; i < this->size; ++i) {
    printf("%d ", i);
  }
  printf("]\n");
}

/**
 * Removes element from vector
 *
 * @param this vector
 * @param id id of an element
 */
void vector_remove(struct vector* const this, const int id) {
  for (int i = id; i < this->size - 1; ++i) {
    this->data[i] = this->data[i + 1];
  }
  this->size -= 1;
}

/**
 * Clears content of the vector
 *
 * @param this vector
 */
void vector_clear(struct vector* const this) {
  this->size = 0;
}

/**
 * Returns an index of given element or -1 if the element is not found
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
 * Inverts a vector
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
 * Shifts all elements of the vector to left
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

void __merge(struct vector* this, int start, int end) {
  const int size = end - start + 1;
  if (size == 1) {
    return;
  } else if (size == 2) {
    if (this->data[start] > this->data[end]) {
      int temp = this->data[start];
      this->data[start] = this->data[end];
      this->data[end] = temp;
    }
    return;
  }

  const int middle = start + size / 2;
  __merge(this, start, middle - 1);
  __merge(this, middle, end);

  int ai = 0;
  int bi = 0;
  const int left_size = middle - 1 - start + 1;
  const int right_size = end - middle + 1;

  struct vector temp = vector_create_with_capacity(size);
  while (ai < left_size && bi < right_size) {
    if (this->data[start + ai] <= this->data[middle + bi]) {
      vector_push_back(&temp, this->data[start + ai]);
      ++ai;
    } else {
      vector_push_back(&temp, this->data[middle + bi]);
      ++bi;
    }
  }
  while (ai < left_size) {
    vector_push_back(&temp, this->data[start + ai]);
    ++ai;
  }
  while (bi < right_size) {
    vector_push_back(&temp, this->data[middle + bi]);
    ++bi;
  }

  // in case when start = 0 and end = end of array
  // we can just swap pointer to the data between this and temp
  for (int i = start; i <= end; ++i) {
    this->data[i] = temp.data[i - start];
  }
  vector_delete(&temp);
}

/**
 * Merge sort
 * Time complexity: O(N*log N)
 * Space complexity: O(N)
 *
 * @param this vector
 */
void vector_merge_sort(struct vector* this) {
  __merge(this, 0, this->size - 1);
}

/**
 * Finds id of an element that equal or greater than given element
 * Time complexity: O(log N)
 *
 * @param this vector
 * @param value value
 * @return index of an element
 */
int vector_lower_bound(const struct vector* const this, const int value) {
  int left = 0;
  int size = this->size;
  while (size > 0) {
    int step = size / 2;
    int middle = left + step;
    if (this->data[middle] < value && middle < this->size) {
      left = middle + 1;
    }
    size = step;
  }
  return left;
}

/**
 * Finds id of an element that greater than given element
 * Time complexity: O(log N)
 *
 * @param this vector
 * @param value value
 * @return index of an element
 */
int vector_upper_bound(const struct vector* const this, const int value) {
  int left = 0;
  int size = this->size;
  while (size > 0) {
    int step = size / 2;
    int middle = left + step;
    if (this->data[middle] <= value && middle < this->size) {
      left = middle + 1;
    }
    size = step;
  }
  return left;
}

/**
 * Returns a value of maximum element
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
 * Checks if vector is sorted
 * Time complexity: O(N)
 *
 * @param this vector
 * @return true if sorted otherwise false
 */
bool vector_is_sorted(const struct vector* this) {
  for (int i = 1; i < this->size; ++i) {
    if (this->data[i - 1] > this->data[i])
      return false;
  }
  return true;
}

/**
 * Returns index of max element in the vector
 *
 * @param this vector
 * @return index of max element
 */
int vector_max_id(struct vector* this) {
  int id = 0;
  for (int i = 1; i < this->size; ++i) {
    if (this->data[i] > this->data[id]) id = i;
  }
  return id;
}

/**
 * Returns a value of minimum element
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
 * Returns an index to minimum element in the vector
 *
 * @param this vector
 * @return index to the smallest element
 */
int vector_min_id(struct vector* this) {
  int min = 0;
  for (int i = 1; i < this->size; ++i) {
    if (this->data[i] < min) min = i;
  }
  return min;
}

/**
 * Check if vector contains passed element
 *
 * @param this vector
 * @param element element
 * @return true if contains otherwise false
 */
bool vector_contains(struct vector* this, int element) {
  for (int i = 0; i < this->size; ++i)
    if (this->data[i] == element) return true;
  return false;
}

/**
 * Check if vector contains duplicate elements
 * Time complexity: O(N^2)
 *
 * @param this vector
 * @return true if contains otherwise false
 */
bool vector_contains_duplicates(struct vector* this) {
  for (int i = 0; i < this->size; i++) {
    for (int x = 0; x < this->size; x++) {
      if (x != i && this->data[i] == this->data[x])
        return true;
    }
  }
  return false;
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

void __vector_print_permutations(struct vector* this, struct vector* exclude) {
  if (exclude->size == this->size) {
    vector_print(exclude);
    return;
  }

  for (int i = 0; i < this->size; ++i) {
    if (!vector_contains(exclude, this->data[i])) {
      vector_push_back(exclude, this->data[i]);
      __vector_print_permutations(this, exclude);
      vector_pop_back(exclude);
    }
  }
}

/**
 * Prints all possible permutations of given numbers
 *
 * @param this vector
 */
void vector_print_permutations(struct vector* this) {
  // permutations works only with sets
  if (vector_contains_duplicates(this)) {
    printf("Error: vector contains duplicate elements!");
    return;
  }

  // for generating permutations we need some collection
  // for storing prefix of previous positions
  struct vector prefix = vector_create();
  __vector_print_permutations(this, &prefix);
  vector_delete(&prefix);
}

