#include <minunit.h>
#include "../src/to_lowercase.h"

MU_TEST(test_string_eq){
  mu_assert_string_eq("A HERO", to_lowercase("a hero"));
  mu_assert_string_eq("A [HERO", to_lowercase("a [hero"));
  mu_assert_string_eq("A HERO", to_lowercase("A hero"));
  mu_assert_string_eq("A HERO ", to_lowercase("a hero "));
  mu_assert_string_eq("A HERO", to_lowercase("A HERO"));
  mu_assert_string_eq("A, HERO", to_lowercase("a, hero"));
  mu_assert_string_eq("A HERO,", to_lowercase("a hero,"));
  mu_assert_string_eq(" A HERO", to_lowercase(" a hero"));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_string_eq);
}

int mian(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return 0;
}
