#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include "ships.hpp"
#include <iostream>

void printErrorAndExit(const std::string err);
std::vector<std::string> readFile(const char* fName);
Ship* createShip(const std::string& line);
void printRoutes(const std::vector<Ship*>& ships);
Cargo* createCargo(const std::string& line);
/*
 * print a vector
 *
 * Params
 * ----------
 *     vec (const std::vector<T>&) : the vector
 *     delim (const char) : seperator after each element
 *
 * Returns
 * ----------
 *     None
 */
template <typename T>
void printVec(const std::vector<T>& vec, const char delim) {
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
    if (i != vec.size() - 1) {
      std::cout << delim;
    }
  }
  std::cout << std::endl;
}

/*
 * print a vector of pointers
 *
 * Params
 * ----------
 *     vec (const std::vector<T>&) : the vector of pointers
 *     delim (const char) : seperator after each element
 *
 * Returns
 * ----------
 *     None
 */
template <typename T>
void printPointerVec(const std::vector<T>& vec, const char delim) {
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << *(vec[i]);
    if (i != vec.size() - 1) {
      std::cout << delim;
    }
  }
  std::cout << std::endl;
}
#endif
