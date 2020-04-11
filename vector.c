#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "vector.h"
#define INITIAL_CAPACITY 4

void vector_delete(struct vector* const this) {
  free(this->data);
  this->size = 0;
  this->capacity = 0;
}

struct vector vector_create_with_capacity(const size_t capacity) {
  struct vector result;
  result.capacity = capacity;
  result.size = 0;
  result.data = malloc(result.capacity * sizeof(int));
  return result;
}

struct vector* vector_create_with_capacity_ptr(int capacity) {
  struct vector* result = malloc(sizeof(struct vector));
  result->capacity = capacity;
  result->size = 0;
  result->data = malloc(result->capacity * sizeof(int));
  return result;
}

struct vector vector_create() {
  return vector_create_with_capacity(INITIAL_CAPACITY);
}

struct vector vector_create_with_size(const size_t size) {
  struct vector result = vector_create_with_capacity(size);
  result.size = size;
  return result;
}

void vector_push_array(struct vector* vec, const int* const elements, const size_t size) {
  const size_t new_capacity = vec->size + size;
  if (new_capacity >= vec->capacity) {
    int* temp = malloc(sizeof(int) * new_capacity);
    for (size_t i = 0; i < vec->size; ++i) {
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

static void vector_allocate_more(struct vector* const vec) {
  int* temp = malloc(vec->capacity * 2 * sizeof(int));
  for (size_t i = 0; i < vec->capacity; i++) {
    temp[i] = vec->data[i];
  }
  free(vec->data);
  vec->data = temp;
  vec->capacity *= 2;
}

void vector_push_back(struct vector* vec, int element) {
  if (vec->size == vec->capacity) {
    vector_allocate_more(vec);
  }

  vec->data[vec->size] = element;
  vec->size++;
}

void vector_insert(struct vector* const this, const size_t id, const int element) {
  if (id == this->size) {
    vector_push_back(this, element);
    return;
  }

  if (this->size == this->capacity) {
    vector_allocate_more(this);
  }

  int prev = element;
  for (size_t i = id; i <= this->size; ++i) {
    int temp = this->data[i];
    this->data[i] = prev;
    prev = temp;
  }
  this->size += 1;
}

void vector_pop_back(struct vector* vec) {
  if (vec->size > 0) {
    vec->size--;
  }
}

void vector_print(const struct vector* const this) {
  printf("[ ");
  for (int i = 0; i < this->size; ++i) {
    printf("%d ", this->data[i]);
  }
  printf("] siz = %ld, cap = %ld\n", this->size, this->capacity);
}

void vector_remove(struct vector* const this, const size_t id) {
  for (size_t i = id; i < this->size - 1; ++i) {
    this->data[i] = this->data[i + 1];
  }
  this->size -= 1;
}

void vector_clear(struct vector* const this) {
  this->size = 0;
}

size_t vector_find(struct vector* const this, const int element) {
  for (size_t i = 0; i < this->size; ++i) {
    if (this->data[i] == element) return i;
  }
  return -1;
}

void vector_invert(struct vector* this) {
  for (size_t i = 0; i < this->size / 2; i++) {
    swap(&this->data[i], &this->data[this->size - 1 - i]);
  }
}

void vector_shift_left(struct vector* const this) {
  if (this->size == 0) return;

  int temp = this->data[0];
  for (size_t i = 0; i < this->size - 1; ++i) {
    this->data[i] = this->data[i + 1];
  }
  this->data[this->size - 1] = temp;
}

void vector_shift_right(struct vector* const this) {
  const size_t size = this->size;
  if (size == 0) return;

  int temp = this->data[size-1];
  for (size_t i = size-1; i >= 1; --i) {
      this->data[i] = this->data[i-1];
  }
  this->data[0] = temp;
}

void vector_insert_sort(struct vector* const this) {
  for (size_t i = 0; i < this->size; i++) {
    for (size_t c = i; c >= 1; c--) {
      if (this->data[c] < this->data[c - 1])
        swap(&this->data[c], &this->data[c - 1]);
      else break;
    }
  }
}

void vector_choice_sort(struct vector* const this) {
  for (size_t i = 0; i < this->size - 1; i++) {
    for (size_t c = i + 1; c < this->size; c++) {
      if (this->data[c] < this->data[i])
        swap(&this->data[c], &this->data[i]);
    }
  }
}

void vector_bubble_sort(struct vector* this) {
  for (size_t i = 0; i < this->size; i++) {
    bool was_swap = false;
    for (size_t c = 0; c < this->size - 1; c++) {
      if (this->data[c + 1] < this->data[c]) {
        swap(&this->data[c + 1], &this->data[c]);
        was_swap = true;
      }
    }
    if (!was_swap) return;
  }
}

static void __merge(struct vector* this, size_t start, size_t end) {
  const size_t size = end - start + 1;
  if (size == 1) {
    return;
  }
  if (size == 2) {
    if (this->data[start] > this->data[end]) {
      int temp = this->data[start];
      this->data[start] = this->data[end];
      this->data[end] = temp;
    }
    return;
  }

  const size_t middle = start + size / 2;
  __merge(this, start, middle - 1);
  __merge(this, middle, end);

  size_t ai = 0;
  size_t bi = 0;
  const size_t left_size = middle - 1 - start + 1;
  const size_t right_size = end - middle + 1;

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

  for (size_t i = start; i <= end; ++i) {
    this->data[i] = temp.data[i - start];
  }
  vector_delete(&temp);
}

void vector_merge_sort(struct vector* this) {
  __merge(this, 0, this->size - 1);
}

size_t vector_lower_bound(const struct vector* const this, const int value) {
  size_t left = 0;
  size_t size = this->size;
  while (size > 0) {
    size_t step = size / 2;
    size_t middle = left + step;
    if (this->data[middle] < value && middle < this->size) {
      left = middle + 1;
    }
    size = step;
  }
  return left;
}

size_t vector_upper_bound(const struct vector* const this, const int value) {
  size_t left = 0;
  size_t size = this->size;
  while (size > 0) {
    size_t step = size / 2;
    size_t middle = left + step;
    if (this->data[middle] <= value && middle < this->size) {
      left = middle + 1;
    }
    size = step;
  }
  return left;
}

int vector_max(const struct vector* const this) {
  int max = this->data[0];
  for (size_t i = 1; i < this->size; ++i) {
    if (this->data[i] > max) max = this->data[i];
  }
  return max;
}

bool vector_sorted(const struct vector* this) {
  for (size_t i = 1; i < this->size; ++i) {
    if (this->data[i - 1] > this->data[i])
      return false;
  }
  return true;
}

size_t vector_max_id(const struct vector* this) {
  size_t id = 0;
  for (size_t i = 1; i < this->size; ++i) {
    if (this->data[i] > this->data[id]) id = i;
  }
  return id;
}

int vector_min(const struct vector* this) {
  int min = this->data[0];
  for (size_t i = 1; i < this->size; ++i) {
    if (this->data[i] < min) min = this->data[i];
  }
  return min;
}

size_t vector_min_id(const struct vector* this) {
  size_t min = 0;
  for (size_t i = 1; i < this->size; ++i) {
    if (this->data[i] < min) min = i;
  }
  return min;
}

bool vector_contains(const struct vector* this, int element) {
  for (size_t i = 0; i < this->size; ++i)
    if (this->data[i] == element) return true;
  return false;
}

bool vector_contains_duplicates(const struct vector* this) {
  for (size_t i = 0; i < this->size; i++) {
    for (size_t x = 0; x < this->size; x++) {
      if (x != i && this->data[i] == this->data[x])
        return true;
    }
  }
  return false;
}

void vector_count_sort(struct vector* this) {
  int min = vector_min(this);
  int max = vector_max(this);
  int stats_size = max - min + 1;
  int* stats = malloc(sizeof(int) * stats_size);

  for (size_t i = 0; i < stats_size; ++i) {
    stats[i] = 0;
  }

  for (size_t i = 0; i < this->size; ++i) {
    stats[this->data[i] - min]++;
  }

  size_t last_insert = 0;
  for (int i = 0; i < stats_size; ++i) {
    for (int x = 0; x < stats[i]; x++) {
      this->data[last_insert] = min + i;
      last_insert++;
    }
  }
}

static void __vector_print_permutations(const struct vector* this, struct vector* exclude) {
  if (exclude->size == this->size) {
    vector_print(exclude);
    return;
  }

  for (size_t i = 0; i < this->size; ++i) {
    if (!vector_contains(exclude, this->data[i])) {
      vector_push_back(exclude, this->data[i]);
      __vector_print_permutations(this, exclude);
      vector_pop_back(exclude);
    }
  }
}

void vector_print_permutations(const struct vector* this) {
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

size_t vector_find_first(const struct vector* const this, const int value) {
  const int lower = vector_lower_bound(this, value);
  if (lower < this->size && this->data[lower] == value)
    return lower;
  else
    return this->size;
}

size_t vector_find_last(const struct vector* const this, const int value) {
  const int upper = vector_upper_bound(this, value);
  if (upper != 0 && this->data[upper - 1] == value)
    return upper - 1;
  else
    return this->size;
}

size_t vector_size_of_largest_subsequence(const struct vector* const this, const struct vector* const other) {
  struct vector2d grid = vector2d_create(this->size + 1, other->size + 1);
  // fill rows
  for (size_t x = 0; x <= this->size; ++x) {
    vector2d_push(&grid, x, 0, 0);
  }
  // fill columns
  for (size_t y = 0; y <= other->size; ++y) {
    vector2d_push(&grid, 0, y, 0);
  }

  for (size_t y = 1; y <= other->size; y++) {
    for (size_t x = 1; x <= this->size; x++) {
      if (this->data[x - 1] == other->data[y - 1]) {
        int result = 1 + vector2d_get(&grid, x - 1, y - 1);
        vector2d_push(&grid, x, y, result);
      } else {
        int result = max(
            vector2d_get(&grid, x - 1, y),
            vector2d_get(&grid, x, y - 1));
        vector2d_push(&grid, x, y, result);
      }
    }
  }

  int result = vector2d_get(&grid, this->size, other->size);
  vector2d_delete(&grid);
  return result;
}

struct vector2d vector2d_create(const size_t columns, const size_t rows) {
  struct vector2d result = { vector_create_with_size(rows * columns), columns, rows};
  return result;
}

int vector2d_get(const struct vector2d* const this, const size_t column, const size_t row) {
  return this->vector.data[row * this->columns + column];
}

void vector2d_push(struct vector2d* const this, const size_t column, const size_t row, const int value) {
  this->vector.data[row * this->columns + column] = value;
}

void vector2d_delete(struct vector2d* const this) {
  vector_delete(&this->vector);
}

void vector2d_print(const struct vector2d* const this) {
  for (size_t y = 0; y < this->rows; y++) {
    for (size_t x = 0; x < this->columns; x++) {
      printf("%d ", vector2d_get(this, x, y));
    }
    printf("\n");
  }
}


