#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  if (NULL == kvPairs) {
    fprintf(stderr, "Invalid kv array\n");
    exit(EXIT_FAILURE);
  }
  counts_t* ans = createCounts();
  // read file
  FILE* f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  size_t sz;
  char* line = NULL;
  while (getline(&line, &sz, f) >= 0) {
    line[strlen(line)-1] = '\0'; // terminate the string early
    addCount(ans, lookupValue(kvPairs, line));
    free(line);
    line = NULL;
  }
  free(line);
  line = NULL;
  // close file
  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "Usage: <command> <filename1> <filename2>\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t* kvs = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (size_t i = 2; i < argc; ++i) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t* c = countFile(argv[i], kvs);
    //compute the output file name from argv[i] (call this outName)
    char* outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE* f = fopen(outName, "w");
    if (NULL == f) {
      fprintf(stderr, "Error opening output file %s\n", outName);
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Error closing output file %s\n", outName);
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    outName = NULL;
    freeCounts(c);
    c = NULL;
  }
 //free the memory for kv
  freeKVs(kvs);
  kvs = NULL;
  return EXIT_SUCCESS;
}
