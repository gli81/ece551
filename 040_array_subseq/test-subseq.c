#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int* array, size_t n);

void test_max_seq(int* array, size_t n, size_t exp) {
  if (maxSeq(array, n) != exp) {
    exit(EXIT_FAILURE);
  }
}    

int main() {
  test_max_seq(NULL, 0, 0);
  test_max_seq((int[]){1, 2, 3}, 3, 3);
  test_max_seq((int[]){1, -1, 1, 2, 3}, 5, 4);
  test_max_seq((int[]){3, 2, 1}, 3, 1);
  test_max_seq((int[]){1, 2, 3, 3}, 4, 3);
  test_max_seq((int[]){1, 1, 2, 3}, 4, 3);
  test_max_seq((int[]){1, -2, 3}, 3, 2);
  test_max_seq((int[]){0, 0, 0}, 3, 1);
  exit(EXIT_SUCCESS);
}
