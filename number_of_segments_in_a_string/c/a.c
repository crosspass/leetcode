#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

// https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/

int countSegments(char* s) {
  int number = 0;
  int word_start = 1;
  for(; *s != '\0'; s++) {
    if (*s != ' ') {
      if (word_start) {
        number++;
      }
      word_start = 0;
    } else {
      word_start = 1;
    }
  }
  return number;
}

MU_TEST(test_check) {
  char * s = "Hello, my name is John";
  mu_assert_int_eq(5, countSegments(s));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
