#include <stdio.h>

/*
 * Returns index of given element or -1 if element is not found
 */
int linear_find(int array[], int size, int element) {
  for (int i = 0; i < size; ++i) {
    if (array[i] == element)
      return i;
  }
  return -1;
}

int main(void) {

  int array[] = {1, 2, -40, 50, 3};

  int result = linear_find(array, 5, -40);
  if (result == -1) {
    printf("Element not found");
  } else {
    printf("ID: %d", result);
  }
  printf("\n");

  return 0;
}
