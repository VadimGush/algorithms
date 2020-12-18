#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "vector.h"
#include "set.h"
#include "test.h"
#include "string.h"

void test_vector() {
  struct vector vector = vector_create();
  assert(0, vector.size);

  vector_push_back(&vector, 3);
  assert(1, vector.size);

  assert(3, vector.data[0])
  vector_push_back(&vector, 4);
  assert(2, vector.size);
  assert(4, vector.data[1])
  vector_push_back(&vector, 2);
  vector_push_back(&vector, 1);
  int array[] = {3, 4, 2, 1};
  assert_true(array_equals(array, vector.data, vector.size))
  int sorted[] = {1, 2, 3, 4};
  vector_merge_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size))
  vector_remove(&vector, 1);
  int removed[] = {1, 3, 4};
  assert_true(array_equals(removed, vector.data, vector.size))
  assert(3, vector.size)

  passed()
}

void test_sort() {
  const int random[] = {3, 4, 2, 1, 5};
  const int sorted[] = {1, 2, 3, 4, 5};
  struct vector vector = vector_create();
  vector_push_array(&vector, random, 5);

  vector_bubble_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size))
  vector_clear(&vector);

  vector_push_array(&vector, random, 5);
  vector_choice_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size))
  vector_clear(&vector);

  vector_push_array(&vector, random, 5);
  vector_insert_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size))
  vector_clear(&vector);

  vector_push_array(&vector, random, 5);
  vector_merge_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size));
  vector_clear(&vector);

  passed();
}

void test_set() {
  struct naive_set set = set_create();
  assert(0, set_size(&set))
  set_insert(&set, 3);
  assert(1, set_size(&set))
  assert_true(set_contains(&set, 3))
  set_insert(&set, 3);
  assert(1, set_size(&set))
  set_insert(&set, 4);
  set_insert(&set, 1);
  assert(3, set_size(&set))
  assert_true(set_contains(&set, 3))
  assert_true(set_contains(&set, 4))
  assert_true(set_contains(&set, 1))
  set_remove(&set, 3);
  assert(2, set_size(&set))
  assert_true(set_contains(&set, 4))
  assert_true(set_contains(&set, 1))
  assert_false(set_contains(&set, 3))
  set_remove(&set, 1);
  set_remove(&set, 4);
  assert_true(set_empty(&set))
  assert_false(set_contains(&set, 4))
  assert_false(set_contains(&set, 1))
  passed()
}

void test_binary_search() {
  const int sorted[] = {1, 2, 2, 3, 6, 6, 7};
  struct vector vector = vector_create();
  vector_push_array(&vector, sorted, 7);

  assert(0, vector_lower_bound(&vector, -2))
  assert(0, vector_lower_bound(&vector, 0))
  assert(0, vector_lower_bound(&vector, 1))
  assert(1, vector_lower_bound(&vector, 2))
  assert(3, vector_lower_bound(&vector, 3))
  assert(4, vector_lower_bound(&vector, 4))
  assert(4, vector_lower_bound(&vector, 5))
  assert(4, vector_lower_bound(&vector, 6))
  assert(6, vector_lower_bound(&vector, 7))
  assert(7, vector_lower_bound(&vector, 8))
  assert(7, vector_lower_bound(&vector, 10))

  assert(0, vector_upper_bound(&vector, -5))
  assert(1,vector_upper_bound(&vector, 1))
  assert(3, vector_upper_bound(&vector, 2))
  assert(4, vector_upper_bound(&vector, 4))
  assert(4, vector_upper_bound(&vector, 5))
  assert(7, vector_upper_bound(&vector, 7))
  assert(7, vector_upper_bound(&vector, 10))

  assert(4, vector_find_first(&vector, 6))
  assert(5, vector_find_last(&vector, 6))
  assert(7, vector_find_first(&vector, 4))
  assert(7, vector_find_last(&vector, 4))
  assert(7, vector_find_first(&vector, -1))
  assert(7, vector_find_last(&vector, -1))

  passed()
}

void test_size_lseq() {

  {
    int array[] = {1, 3, 7, 9, 0, 4, 11};
    struct vector first = vector_create();
    vector_push_array(&first, array, 7);

    int other[] = {1, 7, 11};
    struct vector second = vector_create();
    vector_push_array(&second, other, 3);

    int result = vector_size_of_largest_subsequence(&first, &second);
    assert(3, result);
  }

  {
    int array[] = {1, 3, 4, 6};
    struct vector first = vector_create();
    vector_push_array(&first, array, 4);

    int other[] = {1, 7, 11, 0, -1, 3, 6, 7, 7, 4};
    struct vector second = vector_create();
    vector_push_array(&second, other, 10);

    int result = vector_size_of_largest_subsequence(&first, &second);
    assert(3, result);
  }

  passed();
}

void test_string() {
  struct string string = string_create();
  assert(0, string.size);
  assert_true(0);
  assert_false(1);
  
  passed();
}

void run_tests() {
  test_vector();
  test_set();
  test_sort();
  test_binary_search();
  test_size_lseq();
  test_string();

  result();
}

int main() {
  run_tests();

  return 0;
}
