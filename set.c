#include "vector.c"

/**
 * Naive implementation (and painfully slow) of ordered set based on dynamic array
 */
struct naive_set {
  struct vector data;
};

/**
 * Creates empty set
 * @return a new set
 */
struct naive_set set_create() {
  struct naive_set result;
  result.data = vector_create();
  return result;
}

/**
 * Inserts element into the set
 * Time complexity: O(N)
 *
 * @param this set
 * @param value value
 */
void set_insert(struct naive_set* this, int value) {
  const int lower = vector_lower_bound(&this->data, value);
  if (this->data.data[lower] == value)
    return;
  else
    vector_push(&this->data, lower, value);
}

/**
 * Finds element in the set
 * Time complexity: O(log N)
 *
 * @param this set
 * @param value value
 * @return if element is found then index of element otherwise size of the set
 */
int set_find(const struct naive_set* const this, const int value) {
  const int lower = vector_lower_bound(&this->data, value);
  if (lower < this->data.size && this->data.data[lower] == value) {
    return lower;
  } else {
    return this->data.size;
  }
}

/**
 * Removes element from the set
 * Time complexity: O(N)
 *
 * @param this set
 * @param value value of an element
 */
void set_remove(struct naive_set* const this, const int value) {
  const int id = set_find(this, value);
  if (id != this->data.size)
    vector_remove(&this->data, id);
}

/**
 * Check if set contains given element
 * Time complexity: O(log N)
 *
 * @param this set
 * @param value value
 * @return if set contains this element then true otherwise false
 */
bool set_contains(const struct naive_set* const this, const int value) {
  const int lower = vector_lower_bound(&this->data, value);
  return lower < this->data.size && this->data.data[lower] == value;
}

/**
 * Deletes all data
 * @param this set
 */
void set_delete(struct naive_set* this) {
  vector_delete(&this->data);
}

/**
 * Get size of the set
 * @param this set
 * @return size of the set
 */
int set_size(const struct naive_set* const this) {
  return this->data.size;
}

/**
 * Checks if set is empty
 * @param this set
 * @return if set is empty returns true otherwise false
 */
bool set_empty(const struct naive_set* const this) {
  return set_size(this) == 0;
}

void set_print(struct naive_set* set) {
  printf("set > ");
  vector_print(&set->data);
}

