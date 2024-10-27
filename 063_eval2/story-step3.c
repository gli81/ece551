#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"

int main(int argc, char** argv) {
    // check arg num
    if (argc == 3) {
      char** story_read = readAFile(argv[2]);
      //@@@char** story_processed = replaceCategory(story_read);
      char** kv_read = readAFile(argv[1]);
      catarray_t* kv_processed = buildCategory(kv_read);
      if (NULL == story_read) {
        // no real story
        // free everything in word and exit
        return EXIT_SUCCESS;
      }
      if (NULL == kv_processed) {
        // there is a story, but no real word
        // set up a empty catarray_t
        catarray_t empty = {.arr=NULL, .n=0};
        kv_processed = &empty;
      }
      char** story_processed = replaceWords(story_read, kv_processed);
      int i = 0;
      // freeing...
      while (NULL != story_processed[i]) {
        printf("%s", story_processed[i]);
        free(story_processed[i]);
        free(story_read[i]);
        ++i;
      }
      free(story_read);
      free(story_processed);
      i = 0;
      while (NULL != kv_read[i]) {
        free(kv_read[i++]);
      }
      free(kv_read);
      freeKVs(kv_processed);
    } else {
      fprintf(stderr, "Error -- worng arguments\n");
      fprintf(stderr, "Usage: story-step3 <kv_file> <story_template>\n");
      exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
