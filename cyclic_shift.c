
#include "functions.h"

void cyclic_shift_left(int array[], int size) {
  if (size == 0) return;

  int temp = array[0];
  for (int i = 0; i < size - 1; ++i) {
    array[i] = array[i+1];
  }
  array[size - 1] = temp;
}

void cyclic_shift_right(int array[], int size) {
  if (size == 0) return;

  int temp = array[size - 1];
  for (int i = size - 1; i >= 1; --i) {
    array[i] = array[i - 1];
  }
  array[0] = temp;
}

int main(void) {

  int array[] = {0, 1, 2, 3};
  cyclic_shift_left(array, 4);
  print_int_array(array, 4);

  printf("\n");

  int array2[] = {0, 1, 2, 3};
  cyclic_shift_right(array2, 4);
  print_int_array(array2, 4);
  
  return 0;
}
