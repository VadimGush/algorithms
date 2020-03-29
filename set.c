#include "vector.c"

/**
 * Naive implementation (and painfully slow) of unordered set based on doubly-linked list
 */
struct set {
  struct vector data;
};

struct set set_create() {
  struct set result;
  result.data = vector_create();
  return result;
}


/**
 * Insert element to the set
 * Time complexity: O(N)
 *
 * @param set set
 * @param element element to insert
 */
void set_insert(struct set* set, int element) {

}

/**
 * Check if set contains given element
 * Time complexity: O(N)
 *
 * @param set set
 * @param element element to find
 * @return true if contains otherwise false
 */
bool set_contains(struct set* set, int element) {
  // in not-naive implementation this should work with O(log N) time complexity
  return false;
}

void set_print(struct set* set) {
  vector_print(&set->data);
}

