#include "functions.h"

void sieve(bool array[], int size) {
  if (size < 2) return;

  array[0] = false;
  array[1] = false;
  for (int i = 2; i < size; ++i) {
    if (array[i]) {
      for (int k = 2 * i; k < size; k += i) {
        array[k] = false;
      }
    }
  }

}

int main(void) {
  const int size = 20;
  bool array[size];
  fill_with_true(array, size);

  sieve(array, size);

  for (int i = 0; i < size; ++i) {
    if (array[i])
      printf("%d ", i);
  }
  printf("\n");
  return 0;
}

