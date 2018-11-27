#include <minunit.h>

int countBit(int x);

int hammingDistance(int x, int y) {
  int dist = 0;
  unsigned  val = x ^ y;

  // Count the number of bits set
  while (val != 0)
    {
      // A bit is set, so increment the count and clear the bit
      dist++;
      val &= val - 1;
    }

  // Return the number of differing bits
  return dist;
}

MU_TEST(test_check) {
  mu_assert_int_eq(2, hammingDistance(1,4));
  mu_assert_int_eq(0, hammingDistance(1,1));
  mu_assert_int_eq(3, hammingDistance(0,7));
  mu_assert_int_eq(0, hammingDistance(0,0));
  mu_assert_int_eq(0, hammingDistance(0,0));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
