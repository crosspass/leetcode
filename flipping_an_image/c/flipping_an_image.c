#include <stdlib>
#include <minunit>
// https://leetcode.com/problems/flipping-an-image/description/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** flipAndInvertImage(int** A, int ARowSize, int *AColSizes, int** columnSizes, int* returnSize) {
  int** p[ARowSize];
  int * row;
  for (int i = 0; i < ARowSize; i++) {
    row = malloc(AColSizes[i] * sizeof(int));
    p[i] = row;
    for (int k = 0, j = (AColSizes[i] - 1); j >= 0; k++, j--) {
      *row = (A[i][k] ^ 1);
    }
  }
  columnSizes = p;
  returnSize = AColSizes;
  return p;
}

MU_TEST(test_check) {
  mu_check([[1,0,0],[0,1,0],[1,1,1]] == flipAndInvertImage([[1,1,0],[1,0,1],[0,0,0]]));
  mu_check([[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]] == flipAndInvertImage([[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
