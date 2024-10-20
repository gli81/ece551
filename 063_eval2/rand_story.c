#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"

/*
 * read the file specified by fileName
 * 
 * Params
 * ----------
 * fileName (const char*): name of the file wish to read
 *
 * Returns:
 *     char**: array of lines in the file, each malloced
 */
char** readAFile(const char* fileName) {
  // open file
  FILE* f = fopen(fileName, "r");
  if (NULL == f) {
    fprintf(stderr, "Error opening file %s\n", fileName);
    exit(EXIT_FAILURE);
  }
  char* line = NULL;
  size_t sz;
  char** ans = NULL;
  size_t ct = 0;
  while (getline(&line, &sz, f) >= 0) {
    // create a larger ans
    ans = realloc(ans, (++ct+1) * sizeof(*ans));
    // set the last element of the array to be NULL
    ans[ct] = NULL;
    ans[ct - 1] = line;
    line = NULL;
  }
  free(line);
  // close file
  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file %s\n", fileName);
    exit(EXIT_FAILURE);
  }
  return ans;
}

/*
 * step1, replace _stuff_ with cat
 *
 * Params
 * ----------
 *      (char**): story template put in an array
 *
 * Returns:
 *     char**: processed story
 */
char** replaceCategory(char** story) {
  size_t ct = 0;
  if (NULL == story) {
    // empty file
    return NULL;
  }
  while (NULL != story[ct]) {
    ct++;
  }
  char** ans = malloc((ct+1) * sizeof(*ans));
  ans[ct] = NULL;
  for (size_t i = 0; i < ct; ++i) {
    char* cur = story[i];
    ans[i] = malloc(sizeof(*ans[i]));
    *ans[i] = '\0'; // initialize ans[i] to be empty string
    while (NULL != cur) {
      //@@@printf("cur is %p, %s\n", cur, cur);
      char* temp = strsep(&cur, "_");
      size_t follow = 0;
      if (NULL != cur) {
        while (NULL != cur && cur[follow] != '_') {
          if (cur[follow] == '\n') {
            // reach end of line, didn't find matching '_'
            // fail the program
            fprintf(stderr, "Invalid story -- unmatched '_'\n");
            exit(EXIT_FAILURE);
          }
          follow++;
        }
        cur[follow] = '\0';
        char* category = cur;
        //@@@printf("%s->", category);
        const char* selected = chooseWord(category, NULL);
        //@@@printf("%s\n", selected);
        // add temp and parsed "cat" to ans
        // make sure enough space for them
        ans[i] = realloc(
          ans[i],
          (
            strlen(ans[i]) + 1 + strlen(selected) + strlen(temp)
          ) * sizeof(*ans[i])
        );
        // copy temp into ans[i]
        strncat(ans[i], temp, strlen(temp));
        // copy selected into ans[i]
        strncat(ans[i], selected, strlen(selected));
        cur += follow + 1;
      } else {
        // no more '_' found
        // add temp to ans
        ans[i] = realloc(
          ans[i],
          (
            strlen(ans[i]) + 1 + strlen(temp)
          ) * sizeof(*ans[i])
        );
        strncat(ans[i], temp, strlen(temp));
      }
      //@@@printf("temp is %p, %s\n", temp, temp);
      //@@@printf("ans[%ld]: %s\n", i, ans[i]);
      //@@@printf("length of temp is %ld\n", strlen(temp));
    }
  }
  return ans;
}

//int main(int argc, char** argv) {
//    char** test = readAFile(argv[1]);
//    int i = 0;
//    //@@@while (NULL != test[i]) {printf("%s", test[i]); free(test[i++]);}
//    //while (NULL != test[i]) {
//    //  char* cur = test[i];
//    //  while (NULL != cur) {
//    //    printf("test[i] is %p, %s\n", test[i], test[i]);
//    //    printf("cur is %p, %s\n", cur, cur);
//    //    char* temp = strsep(&cur, " ");
//    //    printf("temp is %p, %s\n", temp, temp);
//    //  }
//    //  free(test[i++]);
//    //}
//    char** rslt = replaceCategory(test);
//    //free(test);
//    while (NULL != test[i]) {free(test[i]);free(rslt[i++]);}
//    free(test);free(rslt);
//    return EXIT_SUCCESS;
//}
