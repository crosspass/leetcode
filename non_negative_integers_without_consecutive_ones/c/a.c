#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

// https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/

int findIntegers(int num) {
}

MU_TEST(test_check) {
  int a = 5;
  mu_assert_int_eq(5, findIntegers(a));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
