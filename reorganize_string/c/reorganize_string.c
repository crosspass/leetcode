#include <minunit.h>
#include <stdio.h>

// https://leetcode.com/problems/reorganize-string/description/

char* reorganizeString(char* S) {
}

MU_TEST(test_check) {
  mu_check(mu_check_array(ret3, e, 6));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
