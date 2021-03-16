#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define STR_INITIAL_CAPACITY 10

struct string string_create_with_capacity(const int capacity) {
  struct string str;
  str.capacity = capacity;
  str.size = 1;
  str.data = malloc(str.capacity * sizeof(char));
  str.data[0] = 0;
  return str;
}

struct string string_create() {
  return string_create_with_capacity(STR_INITIAL_CAPACITY);
}

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

int string_len(const struct string* string) {
  return string->size - 1;
}

