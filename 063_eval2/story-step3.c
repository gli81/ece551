#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"

int main(int argc, char** argv) {
    // check arg num
    if (argc == 3) {
      char** story_read = readAFile(argv[2]);
      //@@@char** story_processed = replaceCategory(story_read);
      if (NULL == story_read) return EXIT_SUCCESS;
      char** kv_read = readAFile(argv[1]);
      catarray_t* kv_processed = buildCategory(kv_read);
      if (NULL == kv_processed) return EXIT_SUCCESS;
    } else {
      fprintf(stderr, "Error -- worng arguments\n");
      fprintf(stderr, "Usage: story-step3 <story_template> <kv_file>\n");
      exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
