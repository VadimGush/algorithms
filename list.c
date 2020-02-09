#include <stdio.h>
#include <stdlib.h>

struct node {
  struct node* next;
  struct node* prev;
  int value;
};

struct list {
  struct node* first;
  struct node* last;
};

struct list list_create() {
  struct list result;
  result.first = NULL;
  result.last = NULL;
  return result;
}

/**
 * Creates new node
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

  return node;
}

/**
 * Removes element from the list and returns next node
 * Time complexity: O(1)
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
 */
void list_pop_back(struct list* list) {
  list_remove(list, list->last);
}

/**
 * Removes first element from the list
 * Time complexity: O(1)
 */
void list_pop_front(struct list* list) {
  list_remove(list, list->first);
}


/**
 * Get node by index
 * If node doesn't exists then returns NULL
 * Time complexity: O(N)
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
void print_list(struct list* list) {
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
void print_list_reverse(struct list* list) {
  printf("[ ");
  struct node* current = list->last;
  while (current != NULL) {
    printf("%d ", current->value);
    current = current->prev;
  }
  printf("] reverse order\n");
}

int main(void) {
  struct list list = list_create();
  print_list(&list);

  list_push_back(&list, 5);
  print_list(&list);

  list_push_back(&list, -3);
  list_push_back(&list, -10);
  list_push_front(&list, 122);
  
  list_insert_after(&list, list_get(&list, 0), 333);
  print_list(&list);

  struct node* next_node = list_get(&list, 0);
  next_node = list_remove(&list, next_node);
  next_node = node_step(next_node, 3);
  list_remove(&list, next_node);
  list_remove(&list, list_get(&list, 1));

  print_list(&list);
  printf("\n");
  print_list_reverse(&list);


  list_pop_front(&list);
  print_list(&list);
  list_pop_back(&list);
  print_list(&list);

  struct node* node = list_get(&list, 2);
  if (node != NULL) 
    printf("Value is: %d\n", node->value);
  else
    printf("Element not found");

  return 0;
}
