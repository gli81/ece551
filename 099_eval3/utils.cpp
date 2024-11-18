#include <cstdlib>
#include "ships.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

/*
 * read a file, put every line into a vector, close file
 * 
 * Params
 * ----------
 *     fName (const char*) : the file to be opened
 *
 * Returns
 * ----------
 *     std::vector<std::string> : a vecotr of lines of the file
 */
std::vector<std::string> readFile(const char* fName) {
  std::ifstream f(fName);
  if (!f.is_open()) {
    std::cerr << "Error opening file " << std::string(fName) << std::endl;
    exit(EXIT_FAILURE);
  }
  // push each line into a vector
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(f, line)) {
    lines.push_back(line); // push_back() makes copies
  }
  f.close();
  return lines;
}

/*
 * process one line for step1, create one Ship (Container) instance
 *
 * Params
 * ----------
 *     line (std::string) : one line representing information of a ship
 *
 * Returns
 * ----------
 *     Ship* : the ship instance
 */
Ship* createContainer(std::string line) {
  // get name
  size_t name_end = line.find(':');
  //@@@std::cout << name_end << line[name_end] << std::endl;
  if (name_end == std::string::npos) {
    std::cerr << "Not enough fields - No colon found" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string name = line.substr(0, name_end);
  //@@@std::cout << "name: " << name << std::endl;
  size_t type_end = line.find(':', name_end + 1);
  //@@@std::cout << type_end << "check if same as " << name_end <<std::endl;
  if (type_end == std::string::npos) {
    std::cerr << "Not enough fields - One colon found" << std::endl;
    exit(EXIT_FAILURE);
  }
  //@@@std::cout << "type: " << line.substr(name_end + 1, type_end - name_end - 1) << std::endl;
  size_t src_end = line.find(':', type_end + 1);
  if (src_end == std::string::npos) {
    std::cerr << "Not enough fields - Two colons found" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string src = line.substr(type_end + 1, src_end - type_end - 1);
  //@@@std::cout << src << std::endl;
  size_t dest_end = line.find(':', src_end + 1);
  if (dest_end == std::string::npos) {
    std::cerr << "Not enough fields - Three colons found" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string dest = line.substr(src_end + 1, dest_end - src_end - 1);
  //@@@std::cout << dest << std::endl;
  std::string rest = line.substr(dest_end + 1);
  //size_t length = rest.size();
  char* end = NULL;
  //@@@std::cout << rest << " how long ? " << length << std::endl;
  unsigned cap = std::strtoul(rest.c_str(), &end, 10);
  //@@@std::cout << cap << std::endl;
  if (*end != '\0') {
    std::cerr << "Invalid input - invalid capacity" << std::endl;
    exit(EXIT_FAILURE);
  }
  return new Ship(name, src, dest, cap);
}

/*
 * print each route based on information in a list of ships
 *
 * Params
 * ----------
 *     ships (std::vector<Ship*>) : ship information
 *
 * Returns
 * ----------
 *     None
 */
void printRoutes(std::vector<Ship*> ships) {
  std::map<std::pair<std::string, std::string>, unsigned> m;
  for (size_t i = 0; i < ships.size(); ++i) {
    std::pair<std::string, std::string> tmp(ships[i]->src, ships[i]->dest);
    if (m.find(tmp) != m.end()) {
      // key found
      m[tmp] += ships[i]->cap;
    } else {
      m[tmp] = ships[i]->cap;
    }
  }
  // print with a iterator
  for (std::map<std::pair<std::string, std::string>, unsigned>::iterator it = m.begin(); it != m.end(); ++it) {
    std::cout << "(" << it->first.first << " -> " << it->first.second << ") has total capacity " << it->second << std::endl;
  }
}
