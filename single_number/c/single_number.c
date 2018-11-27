#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

// https://leetcode.com/problems/single-number/description/

int singleNumber(int* nums, int numsSize) {
  int ret = nums[0];
  for (int i = 1; i < numsSize; i++) {
    ret ^= nums[i];
  }
  return ret;
}

MU_TEST(test_check) {
  int a[]  = {2,2,1};
  mu_assert_int_eq(1, singleNumber(a, 3));

  int a2[] = {4,1,2,1,2};
  mu_assert_int_eq(4, singleNumber(a2, 5 ));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
