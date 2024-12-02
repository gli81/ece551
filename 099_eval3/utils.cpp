#include <cstdlib>
#include "ships.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include "cargo.hpp"

/*
 * print Cargo
 */
std::ostream& operator<<(std::ostream& os, const Cargo& cargo) {
  return os << cargo.toString();
  //os << cargo.name << ": " << cargo.src << " -> " << cargo.dest;
  //os << ", weight: " << cargo.weight << std::endl;
  //for (size_t i = 0; i < cargo.props.size(); ++i) {
  //  os << cargo.props[i];
  //  if (i != cargo.props.size() - 1) {
  //    os << ", ";
  //  }
  //}
  //os << std::endl;
  //return os;
}

/*
 * print Ship
 */
std::ostream& operator<<(std::ostream& os, const Ship& ship) {
  return os << ship.toString();
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
  ans.push_back(str.substr(start, end - start));
  return ans;
}

/*
 * parse container type
 * 
 * Params
 * ----------
 *     types_str (std::string) : type string
 *
 * Returns
 * ----------
 *     std::vector<std::string> : a vector of property strings
 */
/*
std::vector<std::string> parseContainerType(std::string& types_str) {
  //@@@std::cout << types_str << std::endl;
  std::vector<std::string> ans;
  if (types_str.size() == 0) {
    return ans;
  }
  size_t start = 0;
  size_t end = 0;
  while ((end = types_str.find(',', start)) != std::string::npos) {
    ans.push_back(types_str.substr(start, end - start));
    start = end + 1;
  }
  ans.push_back(types_str.substr(start, end - start));
  //@@@printVec(ans);
  return ans;
}
*/
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
  if (vec_size > 6) {
    printErrorAndExit("Too many fields");
  }
  // check cap
  char* end = NULL;
  unsigned cap = std::strtoul(vec[4].c_str(), &end, 10);
  if (*end != '\0') {
    printErrorAndExit("Invalid input - invalid capacity");
  }
  // parse type
  std::vector<std::string> type_vec = splitBy(vec[1], ',');
  std::string ship_type = type_vec[0];
  if (ship_type.compare("Container") == 0) {
    unsigned slot = std::strtoul(type_vec[1].c_str(), &end, 10);
    if (*end != '\0') {
      printErrorAndExit("Invalid input - invalid slot");
    }
    ContainerShip* ship = new ContainerShip(vec[0], vec[2], vec[3], cap, slot);
    for (size_t i = 2; i < type_vec.size(); ++i) {
      ship->addProperty(type_vec[i]);
    }
    return ship;
  } else {
    return new Ship(vec[0], vec[2], vec[3], cap);
  }
  //size_t name_end = line.find(':');
  ////@@@std::cout << name_end << line[name_end] << std::endl;
  //if (name_end == std::string::npos) {
  //  std::cerr << "Not enough fields - No colon found" << std::endl;
  //  exit(EXIT_FAILURE);
  //}
  //std::string name = line.substr(0, name_end);
  ////@@@std::cout << "name: " << name << std::endl;
  //size_t type_end = line.find(':', name_end + 1);
  ////@@@std::cout << type_end << "check if same as " << name_end <<std::endl;
  //if (type_end == std::string::npos) {
  //  std::cerr << "Not enough fields - One colon found" << std::endl;
  //  exit(EXIT_FAILURE);
  //}
  ////@@@std::cout << "type: " << line.substr(name_end + 1, type_end - name_end - 1) << std::endl;
  //// process types
  //std::string type = line.substr(name_end + 1, type_end - name_end - 1);
  //std::vector<std::string> container_type = parseContainerType(type);
  //if (container_type.size() < 2) {
  //  // at least need two fields
  //  std::cerr << "Invalid types - At least need two fields" << std::endl;
  //  exit(EXIT_FAILURE);
  //}
  //size_t src_end = line.find(':', type_end + 1);
  //if (src_end == std::string::npos) {
  //  std::cerr << "Not enough fields - Two colons found" << std::endl;
  //  exit(EXIT_FAILURE);
  //}
  //std::string src = line.substr(type_end + 1, src_end - type_end - 1);
  ////@@@std::cout << src << std::endl;
  //size_t dest_end = line.find(':', src_end + 1);
  //if (dest_end == std::string::npos) {
  //  std::cerr << "Not enough fields - Three colons found" << std::endl;
  //  exit(EXIT_FAILURE);
  //}
  //std::string dest = line.substr(src_end + 1, dest_end - src_end - 1);
  ////@@@std::cout << dest << std::endl;
  //std::string rest = line.substr(dest_end + 1);
  ////size_t length = rest.size();
  //// return new Ship(name, src, dest, cap);
  //if (container_type[0] == "Container") {
  //  // check slot
  //  unsigned slot = std::strtoul(container_type[1].c_str(), &end, 10);
  //  if (*end != '\0') {
  //    std::cerr << "Invalid input - invalid slot" << std::endl;
  //    exit(EXIT_FAILURE);
  //  }
  //  ContainerShip* ans = new ContainerShip(name, src, dest, cap, slot);
  //  for (size_t i = 3; i < container_type.size(); ++i) {
  //    ans->addProperty(container_type[i]);
  //  }
  //  return ans;
  //}
  //return new Ship(name, src, dest, cap);
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
  for (
    std::map<std::pair<std::string, std::string>, unsigned>::iterator it = m.begin();
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
  __uint64_t wt = std::strtoul(vec[3].c_str(), &end, 10);
  if (*end != '\0') {
    printErrorAndExit("Invalid input - invalid weight");
  }
  Cargo* ans = new Cargo(vec[0], vec[1], vec[2], wt);
  // type field index
  size_t type_field = 4;
  bool type_found = false;
  for (size_t i = 4; i < vec.size(); ++i) {
    if (!type_found) {
      if (vec[i].compare("container") == 0) {
        delete ans;
        ans = new ContainerCargo(vec[0], vec[1], vec[2], wt);
        type_field = i;
        type_found = true;
      }
      continue;
    } else {
      if (vec[i].compare("container") == 0) {
        printErrorAndExit("Invalid input - Multiple cargo type");
      }
    }
  }
  for (size_t i = 4; i < vec.size(); ++i) {
    //@@@std::cout << vec[i].substr(0, 10) << std::endl;
    if (i != type_field && vec[i].substr(0, 10).compare("hazardous-") == 0) {
      ans->addProperty(vec[i].substr(10));
    }
  }
  return ans;
}


/*
 * checks if a ship can load a cargo
 *
 * Params:
 * ----------
 *     ship (Ship*) : the ship
 *     cargo (Cargo*) : the cargo
 *
 * Returns:
 * ----------
 *     bool : whether the cargo can be loaded to the ship or not
 */
/*
bool canLoad(Ship* ship, Cargo* cargo) {
  // check if ship's property have all   
}
*/
