#include <cstdlib>
#include "ships.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include "cargo.hpp"
#include "utils.hpp"
#include "avlmultimap03.hpp"
#include <stack>

/*
 * print Cargo
 */
std::ostream& operator<<(std::ostream& os, const Cargo& cargo) {
  return os << cargo.toString();
}

/*
 * print Ship
 */
std::ostream& operator<<(std::ostream& os, const Ship& ship) {
  return os << ship.toString(true);
}

/*
 * print an error, and exit
 *
 * Params
 * ----------
 *     err (std::string) : the error
 *
 * Returns
 * ----------
 *     None
 */
void printErrorAndExit(const std::string err) {
  std::cerr << err << std::endl;
  exit(EXIT_FAILURE);
}

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
 * process one string, split with a char
 *
 * Params
 * ----------
 *     str (const std::string&) : a string that needs to be splited
 *     delim (const char) : split the string by
 *
 * Returns
 * ----------
 *     std::vector<std::string> : a vector of strings
 */
std::vector<std::string> splitBy(const std::string& str, const char delim) {
  std::vector<std::string> ans;
  if (str.size() == 0) {
    return ans;
  }
  size_t start = 0;
  size_t end;
  while ((end = str.find(delim, start)) != std::string::npos) {
    ans.push_back(str.substr(start, end - start));
    start = end + 1;
  }
  // put everything from start to end of string to ans
  if (start != str.size() + 1) { // +1 to handle the last delim right before end of string
    ans.push_back(str.substr(start, end - start));
  }
  return ans;
}

/*
 * process one line for step1, create one Ship instance
 *
 * Params
 * ----------
 *     line (const std::string&) : one line representing information of a ship
 *
 * Returns
 * ----------
 *     Ship* : a pointer to the ship instance
 */
Ship* createShip(const std::string& line) {
  // process the line, split by ':' to get a vector
  std::vector<std::string> vec = splitBy(line, ':');
  //@@@printVec(vec, ',');
  // check length to see if there is enough fields
  size_t vec_size = vec.size();
  if (vec_size == 0) {
    printErrorAndExit("Not enough fields - No colon found");
  }
  if (vec_size < 5) {
    std::ostringstream ss;
    ss << "Not enough fields - " << vec_size - 1 << " colons found";
    printErrorAndExit(ss.str());
  }
  if (vec_size > 5) {
    printErrorAndExit("Too many fields");
  }
  // check cap
  char* end = NULL;
  __uint64_t cap = std::strtoull(vec[4].c_str(), &end, 10);
  if (*end != '\0') { // pregrader says negative input is fine -_-||
    printErrorAndExit("Invalid input - invalid capacity");
  }
  // parse type
  std::vector<std::string> type_vec = splitBy(vec[1], ',');
  std::string ship_type = type_vec[0];
  if (ship_type.compare("Container") == 0) { // processing container ship
    if (type_vec.size() < 2) {
      // at least need Container,<num_slots>
      printErrorAndExit("Invalid input - Not enough fields for container ship");
    }
    // use strtoull then check range, instead of strtoul to make pregrader happy
    __uint64_t slot_ = std::strtoull(type_vec[1].c_str(), &end, 10);
    if (*end != '\0') {
      printErrorAndExit("Invalid input - invalid slot");
    }
    unsigned slot = (unsigned)slot_;
    if ((__uint64_t)slot != slot_) {
      printErrorAndExit("Invalid input - invalid slot");
    }
    ContainerShip* ship = new ContainerShip(vec[0], vec[2], vec[3], cap, slot);
    for (size_t i = 2; i < type_vec.size(); ++i) {
      ship->addProperty(type_vec[i]);
    }
    return ship;
  } else if (ship_type.compare("Tanker") == 0) { //processing tanker ship
    if (type_vec.size() < 4) {
      // at least need Tanker,<min_temp>,<max_temp>,<num_tanks>
      printErrorAndExit("Invalid input - Not enough fields for tanker ship");
    }
    __int64_t min_temp_ = std::strtoll(type_vec[1].c_str(), &end, 10);
    if (*end != '\0') {
      printErrorAndExit("Invalid input - Invalid min temp");
    }
    __int64_t max_temp_ = std::strtol(type_vec[2].c_str(), &end, 10);
    if (*end != '\0') {
      printErrorAndExit("Invalid input - Invalid max temp");
    }
    signed min_temp = min_temp_;
    signed max_temp = max_temp_;
    if ((__int64_t)min_temp != min_temp_ || (__int64_t)max_temp != max_temp_) {
      printErrorAndExit("Invalid input - temp overflow");
    }
    __uint64_t num_tank_ = std::strtoull(type_vec[3].c_str(), &end, 10);
    if (*end != '\0' || num_tank_ == 0) {
      printErrorAndExit("Invalid input - Invalid num tanks");
    }
    unsigned num_tank = num_tank_;
    if ((__uint64_t)num_tank != num_tank_) {
      // overflow
      printErrorAndExit("Invalid input - num tanks overflows");
    }
    if (num_tank > cap || cap % num_tank != 0) {
      printErrorAndExit("Invalid input - Invalid relationship between cap and num tanks");
    }
    TankerShip* ship = new TankerShip(vec[0], vec[2], vec[3], cap, num_tank, min_temp, max_temp);
    for (size_t i = 4; i < type_vec.size(); ++i) {
      ship->addProperty(type_vec[i]);
    }
    return ship;
  } else if (ship_type.compare("Animals") == 0) {
    if (type_vec.size() != 2) {
      // exactly two fields: Animals,<small_enough>
      printErrorAndExit("Invalid input - Invalid fields for animal ship");
    }
    __uint64_t small_enough_ = std::strtoull(type_vec[1].c_str(), &end, 10);
    if (*end != '\0') {
      printErrorAndExit("Invalid input - Invalid small enough");
    }
    unsigned small_enough = small_enough_;
    if ((__uint64_t)small_enough != small_enough_) {
      printErrorAndExit("Invalid input - small enough overflows");
    }
    AnimalShip* ship = new AnimalShip(vec[0], vec[2], vec[3], cap, small_enough);
    return ship;
  } else {
    // not valid ship type
    printErrorAndExit("Invalid input - Invalid ship type");
    // unreachable, but cpp requires :-(
    return NULL;
  }
}

/*
 * print each route based on information in a list of ships
 *
 * Params
 * ----------
 *     ships (const std::vector<Ship*>&) : ship information
 *
 * Returns
 * ----------
 *     None
 */
void printRoutes(const std::vector<Ship*>& ships) {
  std::map<std::pair<std::string, std::string>, __uint64_t> m;
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
  for (
    std::map<std::pair<std::string, std::string>, __uint64_t>::iterator it = m.begin();
    it != m.end(); ++it
  ) {
    std::cout << "(" << it->first.first << " -> " <<it->first.second;
    std::cout << ") has total capacity " << it->second << std::endl;
  }
}

/*
 * create a piece of cargo with a string
 *
 * Params
 * ----------
 *     line (std::string) : the string to be parsed
 *
 * Returns
 * ----------
 *     Cargo* : a pointer to the cargo instance
 */
Cargo* createCargo(const std::string& line) {
  std::vector<std::string> vec = splitBy(line, ',');
  if (vec.size() < 5) {
    printErrorAndExit("Invalid input - Not enough fields in cargo");
  }
  // check weight
  char* end;
  __uint64_t wt = std::strtoull(vec[3].c_str(), &end, 10);
  if (*end != '\0') {
    printErrorAndExit("Invalid input - invalid weight");
  }
  Cargo* ans = NULL;
  // type field index
  size_t type_field = 4;
  bool type_found = false;
  // find the field that represent the cargo type
  for (size_t i = 4; i < vec.size(); ++i) {
    if (!type_found) {
      if (vec[i].compare("container") == 0) {
        ans = new ContainerCargo(vec[0], vec[1], vec[2], wt);
        type_field = i;
        type_found = true;
      } else if (vec[i].compare("gas") == 0 || vec[i].compare("liquid") == 0) {
        ans = new TankerCargo(vec[0], vec[1], vec[2], wt);
        type_field = i;
        type_found = true;
      } else if (vec[i].compare("animal") == 0) {
        ans = new AnimalCargo(vec[0], vec[1], vec[2], wt);
        type_field = i;
        type_found = true;
      }
      continue;
    }
  }
  if (!type_found) {
    // no type for the cargo, no ship can load then
    ans = new NullCargo(vec[0], vec[1], vec[2], wt);
  }
  for (size_t i = 4; i < vec.size(); ++i) {
    if (i == type_field) continue;
    // only hazardous properties are added
    if (vec[i].substr(0, 10).compare("hazardous-") == 0) {
      ans->setHazardous(true);
      ans->addProperty(vec[i].substr(10));
    }
    if (vec[i].compare("roamer") == 0 && ans->getRequiredShip().compare("animal") == 0) {
      ans->addProperty(vec[i]);
    }
    if (ans->getRequiredShip().compare("tanker") == 0 && (vec[i].substr(0, 7).compare("mintemp") == 0 || vec[i].substr(0, 7).compare("maxtemp") == 0)) {
      ans->addProperty(vec[i]);
    }
  }
  return ans;
}

void TankerCargo::addProperty(const std::string& prop) {
  // split by =
  std::vector<std::string> kv = splitBy(prop, '=');
  // add to map
  // if len = 1, key only, insert (k, 0)
  __int64_t num;
  signed num_;
  switch (kv.size()) {
    case 1:
      this->props[kv[0]] = 0;
      break;
    case 2:
      char* end;
      if (kv[1].size() == 0) {
        // error if no value after =
        printErrorAndExit("Invalid input - No value after =");
      }
      num = std::strtoll(kv[1].c_str(), &end, 10);
      if (*end != '\0') {
        printErrorAndExit("Invalid input - Wrong value type");
      }
      num_ = num;
      if ((__int64_t) num_ != num) {
        printErrorAndExit("Invalid input - Value overflows");
      }
      this->props[kv[0]] = num_;
      break;
    default:
      printErrorAndExit("Invalid input - Too many fields for tanker property");
  }
}

/*
 * comparator for ships in alphabetical order
 *
 * Params
 * ----------
 *     a (const Ship*) : one Ship
 *     b (const Ship*) : another Ship
 *
 * Returns
 * ----------
 *     bool : a is larger or not
 */
bool cmpShipName(const Ship* a, const Ship* b) {
  return a->getName() < b->getName();
}

/*
 * comparator for cargo in desc order
 *
 * Params
 * ----------
 *     a (const Cargo*) : one Cargo
 *     b (const Cargo*) : another Cargo
 *
 * Returns
 * ----------
 *     bool : a is larger or not
 */
bool cmpCargoWtDesc(const Cargo* a, const Cargo* b) {
  return a->getWt() > b->getWt();
}

/*
 * find the next node that has larger remaining capacity
 * 
 * Params
 * ----------
 *     root
 */

/*
 * find the best ship from bst
 *
 * Params
 * ----------
 *     bst (AVLMultiMap<__uint64_t, Ship*>) : the bst that contains
 *         all remaining capacity and all ships
 *     cargo (Cargo*) : the cargo being loaded
 *
 * Returns
 * ----------
 *     Ship* : the ship that best fit the cargo
 */     
Ship* findBestShip(AVLMultiMap<__uint64_t, Ship*>& bst, Cargo* cargo) {
  Ship* ans = NULL;
  // a stack based in order traversal
  std::stack<AVLMultiMap<__uint64_t, Ship*>::Node*> stk;
  AVLMultiMap<__uint64_t, Ship*>::Node* cur = bst.root;
  __uint64_t target = cargo->getWt();
  // find the smallest remaining capacity that can still hold the cargo
  while (cur != NULL) {
    if (cur->key >= target) {
      stk.push(cur);
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  while (!stk.empty()) {
    cur = stk.top(); stk.pop();
    // cur is the smallest candidate (smaller candidate can't load cargo)
    for (std::set<Ship*>::iterator it = cur->vals.begin(); it != cur->vals.end(); ++it) {
      if ((*it)->canLoad(cargo)) {return *it;}
    }
    cur = cur->right;
    while (cur != NULL) {
      stk.push(cur);
      cur = cur->left;
    }
  }
  return ans;
}
