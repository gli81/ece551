#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"


counts_t * createCounts(void) {
  //WRITE ME
  counts_t* ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->ct=0;
  return ans;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  for (size_t i = 0; i < c->ct; ++i) {
    if (
      (c->arr[i]->name == NULL && name == NULL) ||
      (c->arr[i]->name != NULL && name != NULL && strcmp(c->arr[i]->name, name) == 0)
    ) {
      c->arr[i]->ct++;
      return;
    }
  }
  // key not found, create
  one_count_t* tmp = malloc(sizeof(*tmp));
  if (name == NULL) {
    tmp->name = NULL;
  } else {
    tmp->name = malloc((strlen(name) + 1) * sizeof(*(tmp->name)));
    strncpy(tmp->name, name, strlen(name) + 1); // strlen() doesn't include \0
    // for (size_t i = 0; i < strlen(name) + 1; ++i) {
    //   if (*(tmp->name+i) == '\0') printf("\\0");
    //   else printf("%c", *(tmp->name + i));
    //   if (i == strlen(name)) printf("\n");
    // }
  }
  tmp->ct = 1;
  // realloc c->arr for larger arr
  one_count_t** tmp_arr = realloc(c->arr, (c->ct+1) * sizeof(*tmp_arr));
  if (NULL == tmp_arr) {
    // free everything
    // free(c);
    fprintf(stderr, "Error reallocating");
    exit(EXIT_FAILURE);
    return;
  }
  c->arr = tmp_arr;
  tmp_arr = NULL;
  c->arr[c->ct++] = tmp;
  tmp = NULL;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  // test with stdout first
  size_t null_ct = 0;
  for (size_t i = 0; i < c->ct; ++i) {
    if (c->arr[i]->name != NULL) {
      fprintf(outFile, "%s: %ld\n", c->arr[i]->name, c->arr[i]->ct);
    } else {
      null_ct = c->arr[i]->ct;
    }
  }
  if (null_ct != 0) {
    fprintf(outFile, "<unknown>: %ld\n", null_ct);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->ct; ++i) {
    if (c->arr[i]->name != NULL) {
      free(c->arr[i]->name);
    }
    free(c->arr[i]);
  }
  free(c->arr);
  free(c);
}

