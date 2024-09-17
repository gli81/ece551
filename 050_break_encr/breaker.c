#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Please input file name and file name only\n");
    return EXIT_FAILURE;
  }
  // count
  int ct[26] = {0};
  //for (int i = 0; i < 26; i++){printf("%d",ct[i]);}
  // read file
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr,"Could not open file\n");
    return EXIT_FAILURE;
  }
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      ct[c - 'a']++;
    }
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "Could not close file\n");
    return EXIT_FAILURE;
  }
  // find largest
  int ans = 0;
  int largest = ct[ans];
  for (size_t i = 1; i < 26; ++i) {
    if (ct[i] > largest) {
      ans = i;
      largest = ct[ans];
    }
  }
  printf("%d\n", ans - 4 >= 0 ? ans - 4 : ans +26 - 4);
  return EXIT_SUCCESS;
}
