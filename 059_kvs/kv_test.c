#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

#define NUM_LOOKUPS 5
int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: kv_test <fileName>\n");
    return EXIT_FAILURE;
  }
  kvarray_t * array = readKVs(argv[1]);
  printf("Printing all keys\n\n");
  printKVs(array);
  char *tests[NUM_LOOKUPS] = {"banana", "grapes", "cantaloupe", "lettuce", "orange"};
  for (int i = 0; i < NUM_LOOKUPS; i++) {
    printf("lookupValue('%s')=%s\n", tests[i], lookupValue(array,tests[i]));
  }
  freeKVs(array);
  return EXIT_SUCCESS;
}
