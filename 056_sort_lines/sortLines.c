#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int dealWithFile(FILE* input){//, int isFile) {
  char** lines = NULL;
  char* line = NULL;
  size_t sz;
  size_t line_num = 0;
  char** tmp = NULL;
  while (getline(&line, &sz, input) >= 0) {
    tmp = realloc(lines, (line_num + 1) * sizeof(*tmp));
    if (tmp == NULL) {
      // realloc fail
      fprintf(stderr, "realloc failure\n");
      free(line);
      free(lines);
      // free(tmp);
      return EXIT_FAILURE;
    }
    lines = tmp;
    tmp = NULL;
    // free(tmp); // don't free tmp here, lines is pointing at the same place!
    // copy the new line into lines
    lines[line_num++] = line;
    line = NULL;
  }
  free(line);
  // sort and print
  sortData(lines, line_num);
  for (size_t i = 0; i < line_num; ++i) {
    printf("%s", lines[i]);
  // }
  // for (size_t i = 0; i < line_num; ++i) {
    free(lines[i]);
  }
  free(lines);
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    // stdin
    int rslt = dealWithFile(stdin);
    if (rslt == EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
  }
  else {
    // loop through files
    for (size_t i = 1; i < argc; ++i) {
      FILE* cur_file = fopen(argv[i], "r");
      if (cur_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", argv[i]);
        return EXIT_FAILURE;
      }
      int rslt = dealWithFile(cur_file);
      if (rslt == EXIT_FAILURE) {
        fprintf(stderr, "Error processing file %s\n", argv[i]);
        return EXIT_FAILURE;
      }
      // close file
      if (fclose(cur_file) != 0) {
        fprintf(stderr, "Error closing file\n");
        return EXIT_FAILURE;
      }
    }
    printf("===== All file successfully processed =====\n");
  }
  return EXIT_SUCCESS;
}
