#ifndef ALGORITHMS_VECTOR_H
#define ALGORITHMS_VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

struct vector {
  int* data;
  size_t size;
  size_t capacity;
};

/**
 * Deletes all vector data
 */
void vector_delete(struct vector*);

/**
 * Creates a new vector with given capacity
 * @return new vector
 */
struct vector vector_create_with_capacity(size_t);

/**
 * Creates a new vector
 * @return new vector
 */
struct vector vector_create();

/**
 * Creates a new vector with given size (all elements are equal to 0)
 * @return
 */
struct vector vector_create_with_size(size_t);

/**
 * Inserts array at the end of the vector
 * Time complexity: O(N)
 */
void vector_push_array(struct vector*, const int*, size_t);

/**
 * Inserts one element at the end of the vector
 * Time complexity: O(1)
 */
void vector_push_back(struct vector*, int);

/**
 * Removes one element from the end of the vector
 * Time complexity: O(1)
 */
void vector_pop_back(struct vector*);

/**
 * Inserts element at the given position and shift all elements after this
 * position to right
 * Time complexity: O(N)
 */
void vector_insert(struct vector*, size_t position, int value);

/**
 * Prints content of the vector
 */
void vector_print(const struct vector*);

/**
 * Removes element from the given position and shifts all elements after this
 * position to left
 * Time complexity: O(N)
 */
void vector_remove(struct vector*, size_t position);

/**
 * Clears content of the vector
 * Time complexity: O(1)
 */
void vector_clear(struct vector*);

/**
 * Finds element in the vector
 * Time complexity: O(N)
 * @return index of searched element
 */
size_t vector_find(struct vector*, int value);

/**
 * Inverts the vector
 * Time complexity: O(N)
 */
void vector_invert(struct vector*);

/**
 * Shifts all elements of the vector to the right
 * Time complexity: O(N)
 */
void vector_shift_left(struct vector*);

/**
 * Shifts all element of the vector to the left
 * Time complexity: O(N)
 */
void vector_shift_right(struct vector*);

/**
 * Insert sort
 * Time complexity: O(N^2)
 */
void vector_insert_sort(struct vector*);

/**
 * Choice sort
 * Time complexity: O(N^2)
 */
void vector_choice_sort(struct vector*);

/**
 * Bubble sort
 * Time complexity: O(N^2)
 */
void vector_bubble_sort(struct vector*);

/**
 * Merge sort
 * Time complexity: O(N*log N)
 * Space complexity: O(N)
 */
void vector_merge_sort(struct vector*);

/**
 * Count sort
 * Time complexity: O(N)
 * Space complexity: O(max - min)
 */
void vector_count_sort(struct vector*);

/**
 * Finds first element that equal or greater than given element
 * Time complexity: O(log N)
 * @return first element that equal or greater than given element otherwise index of element
 * that located after the last
 */
size_t vector_lower_bound(const struct vector*, int);

/**
 * Finds first element that greater than given element
 * Time complexity: O(log N)
 * @return first element that greater than given element otherwise index of element
 * that located after the last
 */
size_t vector_upper_bound(const struct vector*, int);

/**
 * Finds first element in the vector
 * @return index of element otherwise index of element that located after the last
 */
size_t vector_find_first(const struct vector*, int);

/**
 * Finds last element in the vector
 * @return index of element otherwise index of element that located after the last
 */
size_t vector_find_last(const struct vector*, int);

/**
 * Finds max element in the vector
 * Requirements: vector must be not empty
 * Time complexity: O(N)
 * @return value of max element in the vector
 */
int vector_max(const struct vector*);

/**
 * Finds min element in the vector
 * Requirements: vector must be not empty
 * Time complexity: O(N)
 * @return value of min element in the vector
 */
int vector_min(const struct vector*);

/**
 * Finds max element in the vector and returns ID of that element
 * Requirements: vector must be not empty
 * Time complexity: O(N)
 * @return id of max element
 */
size_t vector_max_id(const struct vector*);

/**
 * Finds min element in the vector and returns ID of that element
 * Requirements: vector must be not empty
 * Time complexity: O(N)
 * @return id of min element
 */
size_t vector_min_id(const struct vector*);

/**
 * Checks if vector is sorted
 * Time complexity: O(N)
 * @return true if vector is sorted otherwise false
 */
bool vector_sorted(const struct vector*);

/**
 * Checks if vector contains given element
 * Time complexity: O(N)
 * @return true if contains otherwise false
 */
bool vector_contains(const struct vector*, int);

/**
 * Checks if vector contains duplicate values
 * Time complexity: O(N^2)
 * @return true if contains otherwise false
 */
bool vector_contains_duplicates(const struct vector*);

/**
 * Prints all possible permutations of given numbers
 * Requirements: vector should not contain any duplicates
 * Time complexity: O(N)
 * Space complexity: O(N)
 */
void vector_print_permutations(const struct vector*);

/**
 * Two-dimensional array of ints
 */
struct vector2d {
  struct vector vector;
  size_t columns;
  size_t rows;
};

/**
 * Creates 2-dimensional vector with given number of columns and rows
 * @param columns columns
 * @param rows rows
 * @return new vector
 */
struct vector2d vector2d_create(size_t columns, size_t rows);

/**
 * Gets element from 2-dimensional vector
 * @return value of an element
 */
int vector2d_get(const struct vector2d*, size_t, size_t);

/**
 * Inserts an element in the given position
 */
void vector2d_push(struct vector2d*, size_t, size_t, int);

/**
 * Deletes all vector data
 */
void vector2d_delete(struct vector2d*);

/**
 * Prints content of 2-dimensional vector
 */
void vector2d_print(const struct vector2d*);

/**
 * Finds size of largest common subsequence
 * As an example of dynamic programming
 *
 * @return size of largest common subsequence
 */
size_t vector_size_of_largest_subsequence(const struct vector*, const struct vector*);

#endif //ALGORITHMS_VECTOR_H
