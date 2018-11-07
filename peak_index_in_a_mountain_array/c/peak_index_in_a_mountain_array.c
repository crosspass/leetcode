#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

// https://leetcode.com/problems/peak-index-in-a-mountain-array/description/

/* 3 <= A.length <= 10000 */
/* 0 <= A[i] <= 10^6 */
/* A is a mountain, as defined above. */

int peakIndexInMountainArray(int* A, int ASize) {
  for(int i = 1; i < ASize; i++) {
    if (A[i] < A[i-1]) {
      return i - 1;
    }
  }
  return -1;
}

MU_TEST(test_check) {
  int a[] = {0,1,0};

  mu_assert_int_eq(1, peakIndexInMountainArray(a, 3));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}

