#pragma once
#include <stdio.h>
#include <stdbool.h>

void print_int_array(int array[], int size) {
  printf("[");
  for (int i = 0; i < size; ++i) {
    printf(" %d", array[i]);
  }
  printf(" ]");
}

int max(int first, int second) {
  return first > second ? first : second;
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

int factorial(int n) {
  if (n == 1) return 1;
  return factorial(n-1) * n;
}

int great_common_divisor(int a, int b) {
  if (a == b) return a;
  else if (a > b) return great_common_divisor(a - b, a);
  else return great_common_divisor(a, b - a);
}

float float_pow(float value, int power) {
  if (power == 0) return 1;
  if (power % 2 == 0) return float_pow(value * value, power / 2);
  else return float_pow(value, power - 1) * value;
}

int int_pow(int value, int power) {
  if (power == 0) return 1;
  if (power % 2 == 0) return int_pow(value * value, power / 2);
  else return int_pow(value, power - 1) * value;
}

void swap(int* a, int* b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}
