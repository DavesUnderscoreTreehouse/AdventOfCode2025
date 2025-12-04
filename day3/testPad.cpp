#include <iostream>

int array1[] = {1, 7, 3, 9, 5};
int array2[] = {5, 7, 8, 9, 5};

int compare (const void * a, const void * b) {
  int diff = array2[*(int*)b] - array2[*(int*)a];
  return  (0 < diff) - (diff < 0);
}

int main(void) {
  int perm[5], i;
  int res[5];
  // populate array
  for (i = 0 ; i != 5 ; i++) {
    perm[i] = i;
  }
  // sort based on array2
  qsort (perm, 5, sizeof(int), compare);
  for (i = 0 ; i != 5 ; i++) {
    res[i] = array1[perm[i]];
  }
  printf("Array2\t", array2[i]);
  printf("Array1\n", res[i]);
  for (i = 0 ; i != 5 ; i++) {
    printf("%d\t", array2[i]);
    printf("%d\n", res[i]);
  }
  return 0;
}