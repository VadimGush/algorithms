#pragma once
#include <stdio.h>
#include <stdbool.h>

void array_print(int array[], int size) {
  printf("[");
  for (int i = 0; i < size; ++i) {
    printf(" %d", array[i]);
  }
  printf(" ]");
}

bool array_equals(const int left[], const int right[], const int size) {
  for (int i = 0; i < size; ++i) {
    if (left[i] != right[i]) return false;
  }
  return true;
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

/**
 * The slowest implementation of algorithm for calculating fib numbers
 * Time complexity: O(fib(n)) ~ O(N^2)
 *
 * @param n given number
 * @return fib number
 */
int slow_fib(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return slow_fib(n - 1) + slow_fib(n - 2);
}

/**
 * Fast algorithm for calculating fib numbers
 * Time complexity: O(N)
 * Space complexity: O(N)
 *
 * @param n given number
 * @return fib number
 */
int fast_fib(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;

  int* data = malloc(sizeof(int) * (n + 1));
  data[0] = 0;
  data[1] = 1;
  for (int i = 2; i <= n; ++i) {
    data[i] = data[i - 1] + data[i - 2];
  }
  const int result = data[n];
  free(data);
  return result;
}
