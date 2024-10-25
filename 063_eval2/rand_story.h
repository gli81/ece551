#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
char** readAFile(const char* fileName);
char** replaceCategory(char** story);
int findCategory(catarray_t* cat, const char* cat_name);
void addValue(catarray_t* cat, int idx, const char* word);
catarray_t* buildCategory(char** lines);
#endif
