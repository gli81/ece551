#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"
#include "provided.h"

int main(int argc, char** argv) {
    // check arg num
    if (argc == 2) {
      char** kv_read = readAFile(argv[1]);
      catarray_t* kv_processed = buildCategory(kv_read);
      if (NULL == kv_processed) return EXIT_SUCCESS;

      printWords(kv_processed);
      int i = 0;
      while (kv_read[i] != NULL) {
        free(kv_read[i++]);
      }
      free(kv_read);
      // kv_processed is malloced
      // kv_processed->arr is malloced
      // kv_processed->arr[idx].words
      // kv_processed->arr[idx].words[i] is malloced
      for (size_t i = 0; i < kv_processed->n; ++i) {
        for (size_t j = 0; j < kv_processed->arr[i].n_words; ++j) {
          free(kv_processed->arr[i].words[j]);
        }
        free(kv_processed->arr[i].words);
        free(kv_processed->arr[i].name);
      }
      free(kv_processed->arr);
      free(kv_processed);
    } else {
      fprintf(stderr, "Error -- worng arguments\n");
      fprintf(stderr, "Usage: story-step2 <kv_file>\n");
      exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
