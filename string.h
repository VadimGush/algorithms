#pragma once

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
 * @param this string
 * @param text text to insert
 * @param size size of given text
 */
void string_append(struct string* this, const char text[], const int size);

/**
 * Finds text inside the string
 * Time complexity: O(N*I) (where I is size of input text)
 *
 * @param this string
 * @param text text to find
 * @param size size of searched text
 * @return index or -1 if text is not found
 */
int string_find(const struct string* this, const char text[], const int size);


/**
 * Finds position of given substring in the current string
 *
 * @param this string
 * @param other substring to find
 * @return position of that string
 */
int string_find_string(const struct string* this, const struct string* other);

/**
 * Prints content of the string
 *
 * @param this string
 */
void string_print(const struct string* this);

/**
 * Print content of the string in HEX format
 */
void string_print_hex(const struct string* this);

void string_print_find_result(const struct string* this, const int index, const int size);

