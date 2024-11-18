#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include "ships.hpp"

std::vector<std::string> readFile(const char* fName);
Ship* createContainer(std::string line);
void printRoutes(std::vector<Ship*> ships);

#endif
