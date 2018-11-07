#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

// https://leetcode.com/problems/gas-station/description/


int _canCompleteCircuit(int* gas, int* cost, int size, int index) {
  int tank = gas[index];
  int end = index;
  int last_index = size - 1;
  printf("last index %d\n", last_index);
  do {
    if (tank < cost[index]) {
      return 0;
    }
    tank = tank - cost[index];
    //index = (index + 1 + size) % size;
    index = (index == last_index ? 0 : index + 1);
    tank = tank + gas[index];
    printf("index: %d, tank: %d\n", index, tank);
  } while(index != end);
  return 1;
}

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
  for (int i = 0; i < gasSize; i++) {
    //printf("\n\ntest i : %d\n", i);
    if (_canCompleteCircuit(gas, cost, gasSize, i)){
      return i;
    };
  };
  return -1;
}


MU_TEST(test_check) {
  int gas[]  = {1,2,3,4,5};
  int cost[] = {3,4,5,1,2};
  mu_assert_int_eq(3, canCompleteCircuit(gas, 5, cost, 5));

  int gas1[]  = {2,3,4};
  int cost1[] = {3,4,3};
  mu_assert_int_eq(-1, canCompleteCircuit(gas1, 3, cost1, 3));

  int gas2[]  = {2};
  int cost2[] = {2};
  mu_assert_int_eq(0, canCompleteCircuit(gas2, 1, cost2, 1));

  int gas3[]  = {2};
  int cost3[] = {3};
  mu_assert_int_eq(-1, canCompleteCircuit(gas3, 1, cost3, 1));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
