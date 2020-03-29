#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
  struct node* next;
  struct node* prev;
  int value;
};

struct list {
  struct node* first;
  struct node* last;
};

/**
 * Creates empty list
 *
 * @return new list
 */
struct list list_create() {
  struct list result;
  result.first = NULL;
  result.last = NULL;
  return result;
}

/**
 * Creates new node
 *
 * @param next next node
 * @param prev previous node
 * @param value value of current node
 * @return new node with given value
 */
struct node* node_create(struct node* next, struct node* prev, int value) {
  struct node* result = malloc(sizeof(struct node));
  result->next = next;
  result->prev = prev;
  result->value = value;
  return result;
}

/**
 * Inserts an element at the back of the list
 * Time complexity: O(1)
 *
 * @param list list
 * @param value value of element
 */
void list_push_back(struct list* list, int value) {
  // if list is empty
  if (list->first == NULL && list->first == list->last) {
    struct node* node = node_create(NULL, NULL, value);
    list->first = node;
    list->last = node;
    return;
  }

  struct node* prev_node = list->last;
  struct node* next_node = node_create(NULL, prev_node, value);
  prev_node->next = next_node;
  list->last = next_node;
}

/**
 * Inserts an element at the front of the list
 * Time complexity: O(1)
 *
 * @param list list
 * @param value value of element
 */
void list_push_front(struct list* list, int value) {
  // if list is empty
  if (list->first == NULL && list->first == list->last) {
    struct node* node = node_create(NULL, NULL, value);
    list->first = node;
    list->last = node;
    return;
  }

  struct node* prev_node = node_create(list->first, NULL, value);
  struct node* next_node = list->first;
  next_node->prev = prev_node;
  list->first = prev_node;
}

/**
 * Inserts element after this node and returns new node
 * Time complexity: O(1)
 *
 * @param list list
 * @param node current node
 * @param value value of new node
 * @return pointer to new node
 */
struct node* list_insert_after(struct list* list, struct node* node, int value) {
  struct node* new_node = node_create(node->next, node, value);
  if (node->next != NULL) {
    struct node* next_node = node->next;
    next_node->prev = new_node;
  }
  node->next = new_node;

  if (node == list->last) {
    list->last = new_node;
  }

  return new_node;
}

/**
 * Finds element in the list
 * Time complexity: O(N)
 *
 * @param list list
 * @param element element to find
 * @return true if found otherwise false
 */
bool list_contains(struct list* list, int element) {
  struct node* current = list->first;
  while (current != NULL) {
    if (current->value == element) return true;
    current = current->next;
  }
  return false;
}

/**
 * Inserts element before this node and returns new node
 * Time complexity: O(1)
 *
 * @param list list
 * @param node current node
 * @param value value of new node
 * @return pointer to the new node
 */
struct node* list_insert_before(struct list* list, struct node* node, int value) {
  struct node* new_node = node_create(node, node->prev, value);
  if (new_node->prev != NULL) {
    struct node* prev_node = new_node->prev;
    prev_node->next = new_node;
  }
  node->prev = new_node;

  if (node == list->first) {
    list->first = new_node;
  }

  return new_node;
}

/**
 * Removes element from the list and returns next node
 * Time complexity: O(1)
 *
 * @param list list
 * @param node node to delete
 * @return pointer to next node after deleted
 */
struct node* list_remove(struct list* list, struct node* node) {
  struct node* prev_node = node->prev;
  struct node* next_node = node->next;

  if (prev_node != NULL) {
    prev_node->next = next_node;
  }
  if (next_node != NULL) {
    next_node->prev = prev_node;
  }

  if (node == list->first) {
    list->first = next_node;
  }

  if (node == list->last) {
    list->last = prev_node;
  }

  free(node);
  return next_node;
}

/**
 * Removes last element from the list
 * Time complexity: O(1)
 *
 * @param list list
 */
void list_pop_back(struct list* list) {
  list_remove(list, list->last);
}

/**
 * Removes first element from the list
 * Time complexity: O(1)
 *
 * @param list list
 */
void list_pop_front(struct list* list) {
  list_remove(list, list->first);
}


/**
 * Get node by index
 * If node doesn't exists then returns NULL
 * Time complexity: O(N)
 *
 * @param list list
 * @param index index
 * @return pointer to the node with given index
 */
struct node* list_get(struct list* list, int index) {
  struct node* current = list->first;
  for (int i = 1; i <= index; ++i) {
    if (current == NULL) return NULL;
    current = current->next;
  }
  return current;
}

/**
 * Returns node after N steps
 * or returns NULL if node doesn't exist
 * Time complexity: O(N)
 *
 * @param node node
 * @param steps number of steps
 * @return pointer to the node
 */
struct node* node_step(struct node* node, int steps) {
  struct node* current = node;
  for (int i = 1; i <= steps; ++i) {
    if (current == NULL) return NULL;
    current = current->next;
  }
  return current;
}

/**
 * Returns node after N steps backwards
 * or returns NULL if node doesn't exist
 * Time complexity: O(N)
 *
 * @param node node
 * @param steps number of steps
 * @return pointer to the node
 */
struct node* node_step_backwards(struct node* node, int steps) {
  struct node* current = node;
  for (int i = 1; i <= steps; ++i) {
    if (current == NULL) return NULL;
    current = current->prev;
  }
  return current;
}

/**
 * Prints list
 */
void list_print(struct list* list) {
  printf("[ ");
  struct node* current = list->first;
  while (current != NULL) {
    printf("%d ", current->value);
    current = current->next;
  }
  printf("]\n");
}

/**
 * Prints list in reverse order
 */
void list_print_reverse(struct list* list) {
  printf("[ ");
  struct node *current = list->last;
  while (current != NULL) {
    printf("%d ", current->value);
    current = current->prev;
  }
  printf("] reverse order\n");
}

