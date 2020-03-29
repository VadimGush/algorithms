#include <stdio.h>
#include <stdbool.h>
#include "vector.h"
#include "set.h"

struct naive_set set_create() {
  struct naive_set result;
  result.data = vector_create();
  return result;
}

void set_insert(struct naive_set* this, int value) {
  const size_t lower = vector_lower_bound(&this->data, value);
  if (this->data.data[lower] == value)
    return;
  else
    vector_insert(&this->data, lower, value);
}

size_t set_find(const struct naive_set* const this, const int value) {
  const size_t lower = vector_lower_bound(&this->data, value);
  if (lower < this->data.size && this->data.data[lower] == value) {
    return lower;
  } else {
    return this->data.size;
  }
}

void set_remove(struct naive_set* const this, const int value) {
  const int id = set_find(this, value);
  if (id != this->data.size)
    vector_remove(&this->data, id);
}

bool set_contains(const struct naive_set* const this, const int value) {
  const int lower = vector_lower_bound(&this->data, value);
  return lower < this->data.size && this->data.data[lower] == value;
}

void set_delete(struct naive_set* this) {
  vector_delete(&this->data);
}

size_t set_size(const struct naive_set* const this) {
  return this->data.size;
}

bool set_empty(const struct naive_set* const this) {
  return set_size(this) == 0;
}

void set_print(struct naive_set* set) {
  printf("set > ");
  vector_print(&set->data);
}

