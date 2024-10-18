#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
//#include <string>

int dealWithFile(std::istream& s) {
  std::vector<std::string> hold;
  std::string line;
  size_t sz = 0;
  while (std::getline(s, line)) {
    hold.push_back(line); // stores a copy
    sz++;
  }
  // sort and print
  std::sort(hold.begin(), hold.end());
  for (size_t i = 0; i < sz; ++i) {
    std::cout << hold[i] << std::endl;
  }
  return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    // stdin
    int rslt = dealWithFile(std::cin);
    if (rslt == EXIT_FAILURE) {
      std::cerr << "Error processing std::cin" << std::endl;
      exit(EXIT_FAILURE);
    }
  } else if (argc > 1) {
    // loop thru files
    for (int i = 1; i < argc; ++i) {
      std::ifstream cur_file(argv[i]);
      if (!cur_file.is_open()) {
        std::cerr << "Error opening file " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      int rslt = dealWithFile(cur_file);
      if (rslt == EXIT_FAILURE) {
        std::cerr << "Error processing file " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      // close file
      cur_file.close();
      //if (cur_file.fail()) {
      //  std::cerr << "Error closing file " << argv[i] << std::endl;
      //  exit(EXIT_FAILURE);
      //}
    }
  }
  return EXIT_SUCCESS;
}
