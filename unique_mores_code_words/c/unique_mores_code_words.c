#include <stdio.h>
#include <minunit.h>

int unique_mores_representations(char** words, int wordsSize) {
  char *mores[] = {
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--.."
  };
  return 0;
}


MU_TEST(test_check) {
  /* int count = num_jewels_in_stones("aA", "aAAbbbb"); */
  /* mu_check(3 == count); */
  /* mu_assert(2 == num_jewels_in_stones("abcdef", "abz"), "(abcdef, abz) => 2"); */
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
