#include <minunit.h>
#include "../src/num_jewels_in_stones.h"

MU_TEST(test_check) {
  int count = num_jewels_in_stones("aA", "aAAbbbb");
  mu_check(3 == count);
  mu_assert(2 == num_jewels_in_stones("abcdef", "abz"), "(abcdef, abz) => 2");
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
