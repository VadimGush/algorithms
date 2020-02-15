#include "vector.c"
#include "list.c"
#include "string.c"

int main() {
  struct string text = string_from("Hello world! How are you?", 25);
  string_print(&text);

  struct string find = string_from("world! How", 10);
  string_print_find_result(&text, string_find_string(&text, &find), find.size - 1);

  string_append(&text, " Maybe another time?", 20);

  string_print_find_result(&text, string_find(&text, "are", 3), 3);
  return 0;
}
