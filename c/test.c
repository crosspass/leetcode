#include <stdio.h>
#include <stdlib.h>

int main() {
  int *array = malloc(200 * sizeof(int));
  int * array_start = array;
  const int MAX = 10;
  /* for(int i = 0; i < MAX; i++) { */
  /*   *array++ = i; */
  /* } */
  for (int i = 0; i < MAX; i++) {
    printf("array[%d] => %d\n",i, *array_start++);
  }
}
