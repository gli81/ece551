#include <cstdlib>
#include <assert.h>
#include "function.h"
#include <cstdio>
#include <cmath>

class CountedIntFn : public Function<int, int> {
protected:
  unsigned remaining;
  Function<int, int>* f;
  const char* mesg;
public:
  CountedIntFn(unsigned n, Function<int, int>* fn, const char* m): remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invcations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};


int binarySearchForZero(Function<int, int>* f, int low, int high);

class SinFunction : public Function<int, int> {
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg / 100000.0) - 0.5);
  }
};


void check(Function<int, int>* f, int low, int high, int expected_ans, const char* mesg) {
  // compute max number of invocations of f
  int max_;
  if (low == high) {
    max_ = 1;
  } else {
    max_ = std::log(high - low) / std::log(2) + 1;
  }
  CountedIntFn ct(max_, f, mesg);
  int rslt = binarySearchForZero(&ct, low, high);
  assert(rslt == expected_ans);
}

class Inc: public Function<int, int> {
  virtual int invoke(int arg) {
    return arg+1;
  }
};


int main() {
  SinFunction sin_;
  check(&sin_, 0, 150000, 52359, "sin function\n");
  // all positive
  Inc pos;
  check(&pos, 0, 100000, 0, "all positive function\n");
  // all negative
  check(&pos, -100, -10, -11, "all negative function\n");
  // no element
  check(&pos, 0, 0, 0, "nothing\n");
  //
  check(&pos, -100, 100, -1, "increasing\n");
  return EXIT_SUCCESS;
}
