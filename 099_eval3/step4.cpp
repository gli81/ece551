

#include "utils.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include "avlmultimap03.hpp"

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Wrong number of arguments" << std::endl;
    std::cerr << "Usage: ships-step4 <ship_file> <cargo_file>" << std::endl;
    exit(EXIT_FAILURE);
  }
  // open, read, close ship file
  std::vector<std::string> ship_lines = readFile(argv[1]);
  std::vector<Ship*> ship_vec;
  std::set<std::string> ship_names;
  // no duplicate name
  for (size_t i = 0; i < ship_lines.size(); ++i) {
    Ship* new_ship = createShip(ship_lines[i]);
    if (ship_names.find(new_ship->getName()) != ship_names.end()) {
      printErrorAndExit("Invalid input - Duplicate names");
    }
    ship_vec.push_back(new_ship);
    ship_names.insert(new_ship->getName());
  }
  // build the tree
  AVLMultiMap<__uint64_t, Ship*> bst;
  for (size_t i = 0; i < ship_vec.size(); ++i) {
    bst.add(ship_vec[i]->getRemainingCap(), ship_vec[i]); // add() handles same key
  }
  // open, read, close cargo file
  std::vector<std::string> cargo_lines = readFile(argv[2]);
  std::vector<Cargo*> cargo_vec;
  for (size_t i = 0; i < cargo_lines.size(); ++i) {
    Cargo* new_cargo = createCargo(cargo_lines[i]);
    cargo_vec.push_back(new_cargo);
  }
  // sort the cargos
  std::stable_sort(cargo_vec.begin(), cargo_vec.end(), cmpCargoWtDesc);
  for (size_t i = 0; i < cargo_vec.size(); ++i) {
    // check which ship best fit
    Ship* load_ship = findBestShip(bst, cargo_vec[i]);
    if (load_ship != NULL) {
      // remove from the tree
      bst.remove(load_ship->getRemainingCap(), load_ship);
      // load to ship
      load_ship->load(cargo_vec[i], true);
      // add back to the tree based on new remaining capacity
      bst.add(load_ship->getRemainingCap(), load_ship);
    } else {
      std::cout << "No ships can carry the " << cargo_vec[i]->getName() << " from ";
      std::cout << cargo_vec[i]->getSrc() << " to " << cargo_vec[i]->getDest() << std::endl;
    }
  }
  // print ship info
  std::cout << "---Done Loading---Here are the ships---" << std::endl;
  for (size_t i = 0; i < ship_vec.size(); ++i) {
    std::cout << ship_vec[i]->toString();
  }
  // free ships
  while (!ship_vec.empty()) {
    delete ship_vec.back();
    ship_vec.pop_back();
  }
  // free cargos
  while (!cargo_vec.empty()) {
    delete cargo_vec.back();
    cargo_vec.pop_back();
  }
  return EXIT_SUCCESS;
}

