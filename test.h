/**
 * Small test framework for C lang.
 *
 * TODO: Create a new counter for every set of tests
 */

unsigned int test_passed = 0;
unsigned int test_failed = 0;

#define print_fail_impl(file, function, line) \
  { printf(" - \e[1;31mFAILED\e[0m > %s() %s:%d > ", (function), (file), (line)); }
#define print_fail() \
  print_fail_impl(__FILE__, __FUNCTION__, __LINE__);

/**
 * assert(a, b)
 *
 * Asserts that two arguments are equal
 */
#define assert_imp(a, b) \
  { if ((a) == (b)) { test_passed++; } else \
  { print_fail(); printf("expected %d but was %d\n", (a), (b)); test_failed++; } }
#define assert(a, b) \
  assert_imp(a, b);


/**
 * assert_true(a)
 *
 * Asserts that given argument equals to True 
 */
#define assert_true_imp(a) \
  { if (a) { test_passed++; } else \
  { print_fail(); printf("expected true\n"); test_failed++; } }
#define assert_true(a) \
  assert_true_imp(a);


/**
 * assert_false(a)
 *
 * Asserts that given argument equals to False
 */
#define assert_false_imp(a) \
  { if (!a) { test_passed++; } else \
  { print_fail(); printf("expected false\n"); test_failed++; } }
#define assert_false(a) \
  assert_false_imp(a);

/**
 * passed()
 *
 * This macro should be inserted at the end of a test function. It checks that
 * there is no failed tests.
 */
#define passed_imp(function) \
  { if (test_failed == 0) printf(" > \e[1;32mpassed\e[0m %s() \n", (function)); }
#define passed() passed_imp(__FUNCTION__);

/**
 * result()
 *
 * Prints results of tests. How much tests passed and how much failed.
 * In case if the number of failed tests is greater than zero, exists with 1 exit code.
 */
#define result() \
  { printf("\n Test results: %d passed, %d failed\n", test_passed, test_failed); if (test_failed > 0) { exit(1); } }

