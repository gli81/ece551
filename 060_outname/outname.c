#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  if (NULL == inputName) {
    return NULL;
  }
  size_t name_len = strlen(inputName);
  char* ans = malloc((name_len+1+7) * sizeof(*ans));
  strncpy(ans, inputName, name_len);
  strncpy(ans+name_len, ".counts", 8);
  return ans;
}
