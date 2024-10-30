#include <cstdlib>
#include "function.h"

int binarySearchForZero(Function<int, int>* f, int low, int high) {
  int left = low;
  int right = high - 1;
  int ans = low; 
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (f->invoke(mid) <= 0) {
      ans = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  // all pos
  //if (ans == -1) {return low;}
  //if (f->invoke(high-1) < 0) {return high-1;}
  return ans;
}
