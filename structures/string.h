#pragma once
#include "stdbool.h"

/**
 * Simple string
 */
struct string {
  char* data;
  int size;
  int capacity;
};

/**
 * Creates string with given capacity
 *
 * @param capacity capacity of a new string
 * @return new string
 */
struct string string_create_with_capacity(const int capacity);

/**
 * Creates empty string
 *
 * @return new string
 */
struct string string_create();

/**
 * Creates new string and copies given text to it
 *
 * @param text content of new string
 * @param size size of given text
 * @return new string
 */
struct string string_from(const char text[], const int size);

/**
 * Inserts given text to the back of the string
 *
 * @param th string
 * @param text text to insert
 * @param size size of given text
 */
void string_append(struct string* th, const char text[], const int size);

/**
 * Finds text inside the string
 * Time complexity: O(N*I) (where I is size of input text)
 *
 * @param th string
 * @param text text to find
 * @param size size of searched text
 * @return index or -1 if text is not found
 */
int string_find(const struct string* th, const char text[], const int size);


/**
 * Finds position of given substring in the current string
 *
 * @param th string
 * @param other substring to find
 * @return position of that string
 */
int string_find_string(const struct string* th, const struct string* other);

/**
 * Prints content of the string
 *
 * @param th string
 */
void string_print(const struct string* th);

/**
 * Print content of the string in HEX format
 */
void string_print_hex(const struct string* th);

void string_print_find_result(const struct string* th, const int index, const int size);

/**
 * Returns size of the string (number of characters)
 */
int string_len(const struct string*);

/**
 * Returns TRUE if char* is equal to NULL or contains zero characters
 */
bool str_is_empty(const char*);

