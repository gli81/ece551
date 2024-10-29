#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"
#include <string.h>

//int main(int argc, char** argv) {
//    // check arg num
//    if (argc == 3) {
//      char** story_read = readAFile(argv[2]);
//      //@@@char** story_processed = replaceCategory(story_read);
//      char** kv_read = readAFile(argv[1]);
//      catarray_t* kv_processed = buildCategory(kv_read);
//      if (NULL == story_read) {
//        // no real story
//        // free everything in word and exit
//        if (NULL != kv_processed) {
//          freeKVs(kv_processed);
//        }
//        int i = 0;
//        if (NULL != kv_read) {
//          while (NULL != kv_read[i]) {
//            free(kv_read[i++]);
//          }
//          free(kv_read);
//        }
//        return EXIT_SUCCESS;
//      }
//      if (NULL == kv_processed) {
//        // there is a story, but no real word
//        // set up a empty catarray_t
//        catarray_t empty = {.arr=NULL, .n=0};
//        kv_processed = &empty;
//      }
//      char** story_processed = replaceWords(story_read, kv_processed);
//      int i = 0;
//      // freeing...
//      while (NULL != story_processed[i]) {
//        printf("%s", story_processed[i]);
//        free(story_processed[i]);
//        free(story_read[i]);
//        ++i;
//      }
//      free(story_read);
//      free(story_processed);
//      i = 0;
//      if (NULL != kv_read) {
//        while (NULL != kv_read[i]) {
//          free(kv_read[i++]);
//        }
//        free(kv_read);
//        freeKVs(kv_processed);
//      }
//    } else if (argc == 4 && strcmp(argv[1], "-n") == 0) {
//      // it has to be in order -n <kv_file> <story>
//      char** story_read = readAFile(argv[3]);
//      char** kv_read = readAFile(argv[2]);
//      catarray_t* kv_processed = buildCategory(kv_read);
//      if (NULL == story_read) {
//        // no real story
//        // free everything in word and exit
//        if (NULL != kv_processed) {
//          freeKVs(kv_processed);
//        }
//        int i = 0;
//        if (NULL != kv_read) {
//          while (NULL != kv_read[i]) {
//            free(kv_read[i++]);
//          }
//          free(kv_read);
//        }
//        return EXIT_SUCCESS;
//      }
//      if (NULL == kv_processed) {
//        // there is a story, but no real word
//        // set up a empty catarray_t
//        catarray_t empty = {.arr=NULL, .n=0};
//        kv_processed = &empty;
//      }
//      char** story_processed = replaceWords(story_read, kv_processed);
//      int i = 0;
//      // freeing...
//      while (NULL != story_processed[i]) {
//        printf("%s", story_processed[i]);
//        free(story_processed[i]);
//        free(story_read[i]);
//        ++i;
//      }
//      free(story_read);
//      free(story_processed);
//      i = 0;
//      if (NULL != kv_read) {
//        while (NULL != kv_read[i]) {
//          free(kv_read[i++]);
//        }
//        free(kv_read);
//        freeKVs(kv_processed);
//      }
//    } else {
//      fprintf(stderr, "Error -- worng arguments\n");
//      fprintf(stderr, "Usage: story-step4 [-n] <kv_file> <story_template>\n");
//      exit(EXIT_FAILURE);
//    }
//    return EXIT_SUCCESS;
//}
int main(int argc, char** argv) {
    // check arg num
    if (argc == 3 || (argc == 4 && strcmp(argv[1], "-n") == 0)) {
      int remove = argc - 3;
      char** story_read = readAFile(argv[2 + remove]);
      //@@@char** story_processed = replaceCategory(story_read);
      char** kv_read = readAFile(argv[1 + remove]);
      catarray_t* kv_processed = buildCategory(kv_read);
      if (NULL == story_read) {
        // no real story
        // free everything in word and exit
        if (NULL != kv_processed) {
          freeKVs(kv_processed);
        }
        int i = 0;
        if (NULL != kv_read) {
          while (NULL != kv_read[i]) {
            free(kv_read[i++]);
          }
          free(kv_read);
        }
        return EXIT_SUCCESS;
      }
      if (NULL == kv_processed) {
        // there is a story, but no real word
        // set up a empty catarray_t
        catarray_t empty = {.arr=NULL, .n=0};
        kv_processed = &empty;
      }
      char** story_processed = replaceWords(story_read, kv_processed, remove);
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
      if (NULL != kv_read) {
        while (NULL != kv_read[i]) {
          free(kv_read[i++]);
        }
        free(kv_read);
        freeKVs(kv_processed);
      }
    } else {
      fprintf(stderr, "Error -- worng arguments\n");
      fprintf(stderr, "Usage: story-step4 [-n] <kv_file> <story_template>\n");
      exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
