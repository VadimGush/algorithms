#include <stdio.h>
#include <stdbool.h>

void print_int_array(int array[], int size) {
  printf("[");
  for (int i = 0; i < size; ++i) {
    printf(" %d", array[i]);
  }
  printf(" ]");
}

void print_bool_array(bool array[], int size) {
  printf("[");
  for (int i = 0; i < size; ++i) {
    printf(" %d", array[i]);
  }
  printf(" ]");
}

void fill_with_zero(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    array[i] = 0;
  }
}

void fill_with_false(bool array[], int size) {
  for (int i = 0; i < size; ++i) {
    array[i] = 0;
  }
}

void fill_with_true(bool array[], int size) {
  for (int i = 0; i < size; ++i) {
    array[i] = 1;
  }
}

void swap(int* a, int* b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}
