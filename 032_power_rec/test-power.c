#include <stdio.h>
#include <stdlib.h>


unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned exp) {
  if (power(x, y) != exp) {
    printf("Fail case power(%u, %u) == %u", x, y, exp);
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(2, 3, 8);
  run_check(1, 2, 1);
  run_check(-100, 1, 4294967196);
  exit(EXIT_SUCCESS);
}

