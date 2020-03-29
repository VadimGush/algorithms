
int test_passed = 0;
int test_failed = 0;

#define assert_imp(function, line, a, b) \
  { if ((a) == (b)) { test_passed++; } else \
  { printf(" - FAILED > %s() : line %d > expected %d but was %d\n", (function), (line), (a), (b)); test_failed++; } }

#define assert_true_imp(function, line, a) \
  { if (a) { test_passed++; } else \
  { printf(" - FAILED > %s() : line %d > expected true\n", (function), (line)); test_failed++; } }

#define assert_false_imp(function, line, a) \
  { if (!a) { test_passed++; } else \
  { printf(" - FAILED > %s() : line %d > expected false\n", (function), (line)); test_failed++; } }

#define passed_imp(function) \
  { if (test_failed == 0) printf(" > %s() passed\n", (function)); }

#define assert(a, b) \
  assert_imp(__FUNCTION__, __LINE__, a, b);

#define assert_true(a) \
  assert_true_imp(__FUNCTION__, __LINE__, a);

#define passed() passed_imp(__FUNCTION__);

#define assert_false(a) \
  assert_false_imp(__FUNCTION__, __LINE__, a);

#define result() \
  { printf("==> %d passed, %d failed\n", test_passed, test_failed); }
