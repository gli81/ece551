#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <iostream>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
//uint64_t * readFrequencies(const char * fname) {
//  std::ifstream f(fname);
//  if (!f.is_open()) {
//    std::cerr << "Error opening file" << std::endl;
//    exit(EXIT_FAILURE);
//  }
//  uint64_t* arr = new uint64_t[257]();
//  //for (size_t i = 0; i < 257; ++i) {
//  //  arr[i] = 0;
//  //}
//  char c;
//  while (f.get(c)) {
//    arr[(unsigned char)c]++;
//    //std::cout << c;
//  }
//  arr[256] = 1;
//  f.close();
//  return arr;
//}
uint64_t * readFrequencies(const char * fname) {
  int c;
  uint64_t* arr = new uint64_t[257]();
  FILE* f = fopen(fname, "r");
  if (f == NULL) {
    std::cerr << "Error opening file" << std::endl;
    exit(EXIT_FAILURE);
  }
  //for (size_t i = 0; i < 257; ++i) {
  //  arr[i] = 0;
  //}
  while ((c = fgetc(f)) != EOF) {
    arr[c]++;
    //std::cout << c;
  }
  arr[256] = 1;
  fclose(f);
  return arr;
}
