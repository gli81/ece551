#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"
#include <ctype.h>

/*
 * read the file specified by fileName
 * 
 * Params
 * ----------
 * fileName (const char*) : name of the file wish to read
 *
 * Returns:
 *     char** : array of lines in the file, each malloced
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
 *      story (char**) : story template put in an array
 *
 * Returns:
 *     char** : processed story
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

/* 
 * helper function to find a category_t by name
 * 
 * Params
 * ----------
 *     cat (catarray_t*): where to search for the category
 *     cat_name (const char*): name being searched
 *
 * Returns
 * ----------
 *     int: index of the category struct; create if not found
 */
int findCategory(catarray_t* cat, const char* cat_name) {
  for (size_t i = 0; i < cat->n; ++i) {
    if (strcmp(cat->arr[i].name, cat_name) == 0) {
      return i;
    }
  }
  // not found, put a new category_t struct in cat->arr
  int num_cat = cat->n;
  cat->arr = realloc(cat->arr, (num_cat + 1) * sizeof(*cat->arr));
  // cat->arr[num_cat];
  size_t name_len = strlen(cat_name);
  cat->arr[num_cat].name = malloc(
    (name_len+1) * sizeof(*cat->arr[num_cat].name)
  );
  strncpy(cat->arr[num_cat].name, cat_name,  name_len+1); // also copy '\0'
  cat->arr[num_cat].words = NULL;
  cat->arr[num_cat].n_words = 0;
  cat->n++;
  return num_cat;
}

/* 
 * helper function to add a new category struct to category array
 * 
 * Params
 * ----------
 *     cat (catarray_t*): where to search for the category
 *     cat_name (const char*): name being searched
 *
 * Returns
 * ----------
 *     category_t*: a pointer to the category struct
 *         NULL if not found
 *
void addCategory(catarray_t* cat, const char* cat_name) {

}
*/

/*
 * helper function to add a word to cat->arr[idx]->words
 *
 * Params
 * ----------
 *     cat (catarray_t*) : the categories
 *     idx (int) : the index of the category to be added to
 *     word (const char*) : the word to be added
 * 
 * Returns
 * ----------
 *     None
 */
void addValue(catarray_t* cat, int idx, const char* word) {
  // realloc larger space for cat->arr[idx].words
  size_t new_word_idx = cat->arr[idx].n_words;
  cat->arr[idx].words = realloc(
    cat->arr[idx].words, (new_word_idx + 1) * sizeof(*cat->arr[idx].words)
  );
  // word ends with \n\0
  size_t word_len = strlen(word);
  cat->arr[idx].words[new_word_idx] = malloc(
    word_len * sizeof(cat->arr[idx].words[new_word_idx])
  );
  strncpy(cat->arr[idx].words[new_word_idx], word, word_len);
  // change '\n' to '\0'
  cat->arr[idx].words[new_word_idx][word_len - 1] = '\0';
  cat->arr[idx].n_words++;
}

/*
 * step 2, build category array struct based on input
 * 
 * Params
 * ----------
 *     lines (char**) : an array of lines in the file
 *
 * Returns
 * ----------
 *     catarray_t* : a pointer to the struct
 */
catarray_t* buildCategory(char** lines) {
  if (NULL == lines) {
    // empty file
    return NULL;
  }
  catarray_t* ans = NULL;
  size_t ct = 0;
  while (NULL != lines[ct]) {
    if (NULL == ans) {
      ans = malloc(sizeof(*ans));
      ans->n=0;
      ans->arr=NULL;
    }
    // parse line
    // find first colon
    //@@@printf("%s\n", lines[ct]);
    char* first_colon = strchr(lines[ct], ':');
    if (NULL == first_colon) {
      fprintf(stderr, "Invalid kv -- No ':' found\n");
      exit(EXIT_FAILURE);
    }
    char* after_first_colon = first_colon + 1;
    //@@@printf("%s\n", first_colon);
    // check if there is another colon
    //char* second_colon = strchr(after_first_colon, ':');
    //if (NULL != second_colon) {
    //  fprintf(stderr, "Invalid kv -- More than one ':' found\n");
    //  exit(EXIT_FAILURE);
    //}
    *first_colon = '\0'; // now lines[ct] is key, after_first_colon is value
    int cat_found_idx = findCategory(ans, lines[ct]);
    // add value to cat_found
    addValue(ans, cat_found_idx, after_first_colon);
    ct++;
  }
  return ans;
}

/*
 * helper function to check if a category is a positive integer or not
 * for back reference
 *
 * Params
 * ----------
 *     str (char*) : the string being checked
 *
 * Returns
 * ----------
 *     int : 0 for not qualify (no back reference)
 *         other number for transformed num
 */
int isPosNum(char* str) {
  if (NULL == str) return 0;
  if (*str == '\0') return 0;
  size_t i = 0;
  while (str[i] != '\0') {
    if (!isdigit(str[i++])) {
      return 0;
    }
  }
  return atoi(str);
}

/*
 * step3, replace _stuff_ with random word, or back reference
 *
 * Params
 * ----------
 *      story (char**) : story template put in an array
 *      words (catarray_t*) : the words options
 *
 * Returns:
 *     char** : processed story
 */
char** replaceWords(char** story, catarray_t* words) {
  size_t ct = 0;
  while (NULL != story[ct]) {
    ct++;
  }
  char** ans = malloc((ct+1) * sizeof(*ans));
  ans[ct] = NULL;
  // track used word with a array
  char** used_word = malloc(sizeof(*used_word));
  size_t sz = 0;
  used_word[0] = NULL;
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
        cur[follow] = '\0'; // a new category found
        char* category = cur;
        //@@@printf("%s->", category);
        // determine if it is a number of not
        int isBackReference = isPosNum(category);
        const char* selected;
        if (isBackReference > 0) {
          // backreference
          selected = used_word[sz - isBackReference];
        } else {
          selected = chooseWord(category, words);
        }
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
        // make more space in used_word
        used_word = realloc(used_word, (sz+2)*sizeof(*used_word));
        used_word[sz+1] = NULL;
        used_word[sz] = realloc(used_word[sz], (strlen(selected)+1) * sizeof(*used_word[sz]));
        strncpy(used_word[sz], selected, strlen(selected)+1);
        ++sz;
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
  //@@@printf("%ld\n", sz);
  for (size_t i = 0; i < sz; ++i) {
    //@@@printf("%s\n", used_word[i]);
    free(used_word[i]);
  }
  free(used_word);
  return ans;
}

/*
 * helper function to free a catarray_t
 *
 * Params
 * ----------
 *     cat (catarray_t*) : the catarray_t to be freed
 *
 * Returns
 * ----------
 *     None
 */
void freeKVs(catarray_t* cat) {
  for (size_t i = 0; i < cat->n; ++i) {
    for (size_t j = 0; j < cat->arr[i].n_words; ++j) {
      free(cat->arr[i].words[j]);
    }
    free(cat->arr[i].words);
    free(cat->arr[i].name);
  }
  free(cat->arr);
  free(cat);
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
