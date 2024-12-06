

#include "utils.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Wrong number of arguments" << std::endl;
    std::cerr << "Usage: ships-step2 <ship_file> <cargo_file>" << std::endl;
    exit(EXIT_FAILURE);
  }
  // open, read, close ship file
  std::vector<std::string> ship_lines = readFile(argv[1]);
  std::vector<Ship*> ship_vec;
  std::set<std::string> ship_names;
  for (size_t i = 0; i < ship_lines.size(); ++i) {
    Ship* new_ship = createShip(ship_lines[i]);
    if (ship_names.find(new_ship->getName()) != ship_names.end()) {
      printErrorAndExit("Invalid input - Duplicate names");
    }
    ship_vec.push_back(new_ship);
    ship_names.insert(new_ship->getName());
  }
  // printPointerVec<Ship*>(ship_vec, '\n');
  // open, read, close cargo file
  std::vector<std::string> cargo_lines = readFile(argv[2]);
  //@@@printVec<std::string>(cargo_lines, '\n');
  std::vector<Cargo*> cargo_vec;
  for (size_t i = 0; i < cargo_lines.size(); ++i) {
    Cargo* new_cargo = createCargo(cargo_lines[i]);
    cargo_vec.push_back(new_cargo);
  }
  //@@@printPointerVec<Cargo*>(cargo_vec, '\n');
  //for (size_t i = 0; i < cargo_vec.size(); ++i) {
  //  std::cout << cargo_vec[i]->getName() << std::endl;
  //  std::cout << cargo_vec[i]->getRequiredShip() << std::endl;
  //}
  for (size_t i = 0; i < cargo_vec.size(); ++i) {
    std::vector<Ship*> can_load_vec;
    std::vector<std::string> name_vec;
    // check which ship can have
    for (size_t j = 0; j < ship_vec.size(); ++j) {
      if (ship_vec[j]->canLoad(cargo_vec[i])) {
        // add to the vector
        can_load_vec.push_back(ship_vec[j]);
        name_vec.push_back(ship_vec[j]->getName());
      }
    }
    if (can_load_vec.size() != 0) {
      std::cout << can_load_vec.size() << " ships can carry the ";
      std::cout << cargo_vec[i]->getName() << " from ";
      std::cout << cargo_vec[i]->getSrc() << " to ";
      std::cout << cargo_vec[i]->getDest() << std::endl;
      std::sort(name_vec.begin(), name_vec.end());
      //@@@printVec<std::string>(name_vec, '\n');
      for (size_t idx = 0; idx < name_vec.size(); ++idx) {
        std::cout << "  " << name_vec[idx] << std::endl;
      }
      // load the cargo to the first available ship
      //@@@std::cout << *(can_load_vec[0]);
      can_load_vec[0]->load(cargo_vec[i]);
    } else {
      std::cout << "No ships can carry the " << cargo_vec[i]->getName() << " from ";
      std::cout << cargo_vec[i]->getSrc() << " to " << cargo_vec[i]->getDest() << std::endl;
    }
    //std::cout << std::endl;
    //printPointerVec<Ship*>(ship_vec, '\n');
    //std::cout << std::endl;
  }
  std::cout << "---Done Loading---Here are the ships---" << std::endl;
  for (size_t i = 0; i < ship_vec.size(); ++i) {
    std::cout << ship_vec[i]->toString();
  }
  // free ships
  while (!ship_vec.empty()) {
    delete ship_vec.back();
    ship_vec.pop_back();
  }
  while (!cargo_vec.empty()) {
    delete cargo_vec.back();
    cargo_vec.pop_back();
  }
  return EXIT_SUCCESS;
}

