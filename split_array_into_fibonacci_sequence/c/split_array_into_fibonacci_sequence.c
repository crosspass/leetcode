#include <minunit>

// https://leetcode.com/problems/split-array-into-fibonacci-sequence/description/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* splitIntoFibonacci(char* S, int* returnSize) {
  for(i = 1; i < 11;  i++) {
    
  }
}

int atoi(char *str) {
  unsigned long ret = 0;
  while((char c = *str++) != '\n') {
    int number = c - '0';
    ret = ret * 10 + number;
  }
  return ret;
}

MU_TEST(test_check) {
  mu_check([123,456,579] == splitIntoFibonacci("123456579"));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
