#include <minunit.h>
#include <stdio.h>

// https://leetcode.com/problems/merge-sorted-array/description/

void merge(int* nums1, int m, int* nums2, int n) {
  int end =  n + m -1;
  m--;
  n--;
  while(n != -1 && m != -1) {
    if (nums2[n] >= nums1[m]) {
      nums1[end--] = nums2[n--];
    } else {
      nums1[end--] = nums1[m--];
    }
  }
  if (n != -1) {
    while (n != -1) {
      nums1[end--] = nums2[n--];
    }
  }
}

int mu_check_array(int* nums1,  int* nums2, int size) {
  for (int i = 0; i < size; i++) {
    if (*nums1++ != *nums2++) {
      return 0;
    }
  }
  return 1;
}

MU_TEST(test_check) {
  int a[] = {1,2,3,0,0,0};
  int b[] = {2,5,6};
  merge(a, 3, b, 3);
  int ret[] = {1,2,2,3,5,6};
  mu_check(mu_check_array(ret, a, 6));
  int c[] = {4,5,6,0,0,0};
  int d[] = {1,2,3};
  merge(c, 3, d, 3);
  int ret2[] = {1,2,3,4,5,6};
  mu_check(mu_check_array(ret2, c, 6));
  int e[] = {1,2,3,0,0,0};
  int f[] = {4,5,6};
  merge(e, 3, f, 3);
  int ret3[] = {1,2,3,4,5,6};
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
