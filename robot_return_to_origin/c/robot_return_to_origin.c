#include <minunit.h>

// https://leetcode.com/problems/robot-return-to-origin/description/

int judgeCircle(char * str) {
  int l_count = 0;
  int r_count = 0;
  int u_count = 0;
  int d_count = 0;
  char c;
  while((c = *str++) != '\0') {
    switch(c) {
    case 'L':
      l_count++;
      break;
    case 'R':
      r_count++;
      break;
    case 'U':
      u_count++;
      break;
    case 'D':
      d_count++;
      break;
    }
  }
  return l_count == r_count && u_count == d_count;
}

MU_TEST(test_check) {
  mu_check(judgeCircle("UD"));
  printf("%d",judgeCircle("LL"));
  mu_check(-1 == judgeCircle("LL"));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
