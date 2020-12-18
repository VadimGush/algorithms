// TODO: String should have it's own header file

#include <stdio.h>
#include <stdlib.h>
#define STR_INITIAL_CAPACITY 10


/**
 * just string without SSO
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
struct string string_create_with_capacity(const int capacity) {
  struct string str;
  str.capacity = capacity;
  str.size = 1;
  str.data = malloc(str.capacity * sizeof(char));
  str.data[0] = 0;
  return str;
}

/**
 * Creates empty string
 *
 * @return new string
 */
struct string string_create() {
  return string_create_with_capacity(STR_INITIAL_CAPACITY);
}

/**
 * Creates new string and copies given text to it
 *
 * @param text content of new string
 * @param size size of given text
 * @return new string
 */
struct string string_from(const char text[], const int size) {
  struct string str;
  str.capacity = size + 1;
  str.size = size + 1;
  str.data = malloc(str.capacity * sizeof(char));
  for (int i = 0; i < size; i++) {
    str.data[i] = text[i];
  }
  str.data[size] = 0;
  return str;
}

/**
 * Inserts given text to the back of the string
 *
 * @param this string
 * @param text text to insert
 * @param size size of given text
 */
void string_append(struct string* this, const char text[], const int size) {
  if (this->size + size > this->capacity) {
    int new_capacity = this->size + size;
    char* data = malloc(new_capacity * sizeof(char));
    for (int i = 0; i < this->size; ++i) {
      data[i] = this->data[i];
    }
    free(this->data);
    this->data = data;
    this->capacity = new_capacity;
  }

  for (int i = 0; i < size; i++) {
    this->data[this->size - 1 + i] = text[i];
  }
  this->data[this->size - 1 + size] = 0;
  this->size = this->size - 1 + size + 1;
}

/**
 * Finds text inside the string
 * Time complexity: O(N*I) (where I is size of input text)
 *
 * @param this string
 * @param text text to find
 * @param size size of searched text
 * @return index or -1 if text is not found
 */
int string_find(const struct string* this, const char text[], const int size) {
  for (int i = 0; i < this->size; ++i) {
    for (int c = 0; c < size; ++c) {
      if (this->data[i + c] != text[c]) break;
      if (c == size - 1) return i;
    }
  }
  return -1;
}

int string_find_string(const struct string* this, const struct string* other) {
  return string_find(this, other->data, other->size - 1);
}

/**
 * Prints content of the string
 *
 * @param this string
 */
void string_print(const struct string* this) {
  printf("%s [siz = %d, cap = %d] \n", this->data, this->size, this->capacity);
}

void string_print_hex(const struct string* this) {
  for (int i = 0; i < this->size; i++) {
    printf("%X ", this->data[i]);
  }
  printf("\n");
}

void string_print_find_result(const struct string* this, const int index, const int size) {
  for (int i = 0; i < this->size - 1; ++i) {
    if (i == index) printf("[[");
    printf("%c", this->data[i]);
    if (i == index + size - 1) printf("]]");
  }
  printf("\n");
}

void string_print_find_string_result(const struct string* this, const struct string* other, const int index) {
  string_print_find_result(this, index, other->size - 1);
}


