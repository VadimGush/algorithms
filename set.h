#ifndef ALGORITHMS_SET_H
#define ALGORITHMS_SET_H

#include <stdbool.h>
#include "vector.h"

/**
 * Naive implementation (and painfully slow) of ordered
 * set based on dynamic array
 */
struct naive_set {
  struct vector data;
};

/**
 * Creates an empty set
 * @return new set
 */
struct naive_set set_create();

/**
 * Inserts element into the set
 * Time complexity: O(N)
 *
 * @param this set
 * @param value value
 */
void set_insert(struct naive_set* this, int);

/**
 * Finds element in the set
 * Time complexity: O(log N)
 *
 * @param this set
 * @param value value
 * @return if element is found then index of element otherwise size of the set
 */
size_t set_find(const struct naive_set*, int);

/**
 * Removes element from the set
 * Time complexity: O(N)
 *
 * @param this set
 * @param value value of an element
 */
void set_remove(struct naive_set*, int);

/**
 * Check if set contains given element
 * Time complexity: O(log N)
 *
 * @param this set
 * @param value value
 * @return if set contains this element then true otherwise false
 */
bool set_contains(const struct naive_set*, int);

/**
 * Deletes all set data
 */
void set_delete(struct naive_set*);

/**
 * Returns size of the set
 * @return size of the set
 */
size_t set_size(const struct naive_set*);

/**
 * @return true if set is empty otherwise false
 */
bool set_empty(const struct naive_set*);

/**
 * Prints content of the set
 */
void set_print(struct naive_set* set);

#endif //ALGORITHMS_SET_H
