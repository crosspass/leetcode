# include <stdio.h>

void qsort(int  array[], int lo, int hi);
void qsort2(int  array[], int lo, int hi);
int partition(int array[], int lo, int hi);
int partition2(int array[], int lo, int hi);
void swap(int array[], int i, int j);
void lprintf(int array[], int size);

int main() {
  /* int array[] = { 7, 2, 6, 4, 5, 3, 7, 8 }; */
  int array[] = { 9, 2, 3, 4, 5, 6, 7, 10 };
  int array2[] = { 9, 2, 3, 4, 5, 6, 7, 10 };

  lprintf(array, 8);
  printf("\n");
  qsort(array, 0, 7);
  printf("--------\n");
  lprintf(array, 8);

  printf("********************************\n\n");
  lprintf(array2, 8);
  printf("\n");
  qsort2(array2, 0, 7);
  printf("--------\n");
  lprintf(array2, 8);
  return 1;
}

void qsort(int array[], int lo, int hi) {
  if (lo < hi) {
    int p = partition(array, lo, hi);
    lprintf(array, 8);
    qsort(array, lo, p - 1);
    qsort(array, p + 1, hi);
  }
}

int partition(int array[], int lo, int hi) {
  int pivot = array[hi];
  int i = lo;
  for(int j = lo; j < hi; j++) {
    if(array[j] < pivot) {
      if (i != j)
        swap(array, i, j);
      i++;
    }
  }
  swap(array, i, hi);
  return i;
}

void qsort2(int array[], int lo, int hi) {
  if (lo < hi) {
    int p = partition2(array, lo, hi);
    if ( lo < p && p < hi) {
      lprintf(array, 8);
      qsort2(array, lo, p);
      qsort2(array, p, hi);
    }
  }
}

int partition2(int array[], int lo, int hi) {
  int pivot = array[hi];
  int i = lo;
  int j = hi;
  for(;1;) {
    while(array[i] < pivot)
      i++;
    while(array[j] > pivot)
      j--;
    printf("i: %d, j: %d\n", i, j);
    if(i >= j)
      swap(array, j, hi);
      return j;
    swap(array, i, hi);
  }
}


void swap(int array[], int i, int j) {
  printf("swap %d %d\n", i, j);
  int tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

void lprintf(int array[], int size) {
  for(int i = 0; i < size; i++) {
    printf("%d\t", array[i]);
  }
  printf("\n");
}
