#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  // open file
  FILE* cur = fopen(fname, "r");
  if (cur == NULL) {
    fprintf(stderr, "Error opening file %s\n", fname);
    return NULL;
  }
  kvarray_t* ans = NULL;
  // read each line
  size_t ln_ct = 0;
  size_t sz;
  char* line = NULL;
  kvpair_t* tmp = NULL;
  while (getline(&line, &sz, cur) >= 0) {
    if (ans == NULL) {
      ans = malloc(sizeof(*ans));
      ans->arr = NULL;
    }
    // reallocate space for larger array
    kvpair_t** tmp_arr = realloc(ans->arr, (ln_ct+1) * sizeof(*(ans->arr)));
    if (tmp_arr == NULL) {
      freeKVs(ans);
      fprintf(stderr, "Error reallocating memory\n");
      return NULL;
    }
    ans->arr = tmp_arr;
    tmp_arr = NULL;
    tmp = malloc(sizeof(*tmp)); // kvpair_t
    char* first_equal = strchr(line, '=');
    line[strlen(line) - 1] = '\0';
    *first_equal = '\0';
    tmp->key = line;
    line = NULL;
    tmp->value = first_equal + 1;
    // not line, change it @_@
    ans->arr[ln_ct++] = tmp;
    tmp = NULL;
    // don't free line, tmp.key and tmp.value points inside line
    // free tmp.key later
    //free(line);
  }
  free(line); // line is EOF for exiting while, it is not set to NULL, and is not in ans->arr
  ans->ct = ln_ct;
  // close file
  if (fclose(cur) != 0) {
    freeKVs(ans);
    fprintf(stderr, "Error closing file %s\n", fname);
    return NULL;
  }
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  // free every key
  // free every kvpair
  for (size_t i = 0; i < pairs->ct; ++i) {
    free(pairs->arr[i]->key);
    free(pairs->arr[i]);
  }
  // free kvarray_t->arr
  free(pairs->arr);
  // free kvarray_t
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  if (pairs == NULL) return;
  // printf("%ld KVs in array\n", pairs->ct);
  for (size_t i = 0; i < pairs->ct; ++i) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i]->key, pairs->arr[i]->value);
  }
  // printf("==========\n");
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->ct; ++i) {
    if (strcmp(pairs->arr[i]->key, key) == 0) {
      return pairs->arr[i]->value;
    }
  }
  return NULL;
}

