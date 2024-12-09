#include <cstdlib>
#include <iostream>
#include <string>
#include "utils.hpp"
#include "ships.hpp"
#include <set>

int main (int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Wrong number of arguments" << std::endl;
    std::cerr << "Usage: ships-step1 <ship_file>" << std::endl;
    exit(EXIT_FAILURE);
  }
  // open, read, close the file
  std::vector<std::string> lines = readFile(argv[1]); 
  std::vector<Ship*> ship_vec;
  std::set<std::string> ship_names;
  for (size_t i = 0; i < lines.size(); ++i) {
    // parse each line
    Ship* new_ship = createShip(lines[i]);
    if (ship_names.find(new_ship->getName()) != ship_names.end()) {
      // name exists
      printErrorAndExit("Invalid input - Duplicate ship names");
    }
    ship_vec.push_back(new_ship);
    ship_names.insert(new_ship->getName());
  }
  // print every route
  printRoutes(ship_vec);
  // free ships
  while (!ship_vec.empty()) {
    delete ship_vec.back();
    ship_vec.pop_back();
  }
  return EXIT_SUCCESS;
}
