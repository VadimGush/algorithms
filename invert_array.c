#include <stdio.h>
#include "functions.h"

/*
 * Inverts array of given size
 */
void invert_array(int array[], int size) {
  for (int i = 0; i < size / 2; i++) {
    swap(&array[i], &array[size - 1 - i]);
  }
}

int main(void) {

  int array[] = {1, 2, 3, 4, 5};
  invert_array(array, 5);
  print_int_array(array, 5);

  return 0;
}
