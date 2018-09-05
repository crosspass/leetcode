#include <stdio.h>
#include <minunit.h>
#include "../src/to_lowercase.h"

MU_TEST(test_string_eq){
  char s[] = "A HERO";
  mu_assert_string_eq("a hero", to_lowercase(s));
  char s2[] = "a [hero";
  mu_assert_string_eq("a [hero", to_lowercase(s2));
  char s3[] = "a hero";
  mu_assert_string_eq("a hero", to_lowercase(s3));
  char s4[] = "a hero ";
  mu_assert_string_eq("a hero ", to_lowercase(s4));
  char s5[] = " a hero";
  mu_assert_string_eq(" a hero", to_lowercase(s5));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_string_eq);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return 0;
}
