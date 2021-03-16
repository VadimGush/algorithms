#include "functions.h"
#include <stdlib.h>

void array_print(const int array[], const size_t size) {
  printf("[");
  for (int i = 0; i < size; ++i) {
    printf(" %d", array[i]);
  }
  printf(" ]");
}

bool array_equals(const int left[], const int right[], const size_t size) {
  for (int i = 0; i < size; ++i) {
    if (left[i] != right[i]) return false;
  }
  return true;
}

int max(int first, int second) {
  return first > second ? first : second;
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

int slow_fib(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return slow_fib(n - 1) + slow_fib(n - 2);
}

int fast_fib(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;

  // We'll create just an array with all numbers
  // and iterate over it
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

bool data_compare(void* first, void* second, size_t size) {
  char* f = (char*) first;
  char* s = (char*) second;
  for (size_t id = 0; id < size; id++) {
    if (f[id] != s[id]) {
      return false;
    }
  }
  return true;
}

bool compare_str(char* first, char* second) {
  while (*first != 0) {
    if (*first != *second || *second == 0) {
      return false;
    }
    first++;
    second++;
  }
  return *second == 0;
}

size_t str_len(char* str) {
  size_t size = 0;
  for (; *str != 0; str++) {
    size++;
  }
  return size + 1;
}

size_t str_size(char* str) {
  size_t size = 0;
  for (; *str != 0; str++) {
    size++;
  }
  return size;

}
