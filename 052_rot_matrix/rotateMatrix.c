#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char mat[][10]) {
  for (size_t i = 0; i < 5; ++i) {
    char tmp;
    for (size_t j = 0; j < 10 - 2 * i - 1; ++j) {
      tmp = mat[i][i + j];
      mat[i][i + j] = mat[9 - i - j][i];
      mat[9 - i - j][i] = mat[9 - i][9 - i - j];
      mat[9 - i][9 - i - j] = mat[i + j][9 - i];
      mat[i + j][9 - i] = tmp;
    }
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "INVALID ARGS\n");
    return EXIT_FAILURE;
  }
  // open file
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "ERROR READING FILE\n");
    return EXIT_FAILURE;
  }
  char line[12]; // 12 because one more new line, one more \0
  char mat[10][10];
  // read file
  int cur = 0;
  while (fgets(line, 12, f) != NULL) {
    if (cur == 10){
      fprintf(stderr, "INVALID INPUT - TOO MANY LINES\n");
      return EXIT_FAILURE;
    }
    if (strchr(line, '\n') != &line[10]) {
      fprintf(stderr, "INVALID INPUT - NOT 10 CHARS\n");
      return EXIT_FAILURE;
    }
    for (size_t i = 0; i < 10; i++) {
      mat[cur][i] = line[i];
    }
    cur++;
  }
  // close file
  if (fclose(f) != 0) {
    fprintf(stderr, "ERROR CLOSING FILE\n");
    return EXIT_FAILURE;
  }
  if (cur < 10) {
    fprintf(stderr, "INVALID INPUT - TOO FEW LINES\n");
    return EXIT_FAILURE;
  }
  rotate(mat);
  // print result
  for (size_t i = 0; i < 10; ++i) {
    for (size_t j = 0; j < 10; ++j) {
      printf("%c", mat[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
