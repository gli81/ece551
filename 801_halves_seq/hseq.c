#include <stdio.h>
#include <stdlib.h>

unsigned hseq(unsigned n) {
  return n;  //REPLACE this with your code!
}

// you should not need to modify main
int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage ./hseq start end\n");
    return EXIT_FAILURE;
  }
  unsigned start = atoi(argv[1]);
  unsigned end = atoi(argv[2]);
  for (unsigned i = start; i <= end; i++) {
    printf("%u: %u\n", i, hseq(i));
  }
  return EXIT_SUCCESS;
}
