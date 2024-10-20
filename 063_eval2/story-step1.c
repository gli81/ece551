#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"

int main(int argc, char** argv) {
    // check arg num
    if (argc == 2) {
      char** story_read = readAFile(argv[1]);
      char** story_processed = replaceCategory(story_read);
      if (NULL == story_processed) return EXIT_SUCCESS;
      int i = 0;
      while (story_read[i] != NULL) {
        printf("%s", story_processed[i]);
        free(story_processed[i]);
        free(story_read[i++]);
      }
      free(story_processed);
      free(story_read);
    } else {
      fprintf(stderr, "Error -- worng arguments\n");
      fprintf(stderr, "Usage: story-step1 <story_template>\n");
      exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
