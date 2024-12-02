#ifndef SHIPS_HPP
#define SHIPS_HPP

#include <string>
#include <vector>
#include "cargo.hpp"
#include <sstream>
#include <set>
#include <iostream>

class Ship {
protected:
  std::string name;
  std::string src;
  std::string dest;
  unsigned cap;


public:
  Ship(): name(std::string()), src(std::string()), dest(std::string()), cap(0) {}

  Ship(
    std::string nm,
    std::string src_,
    std::string dest_,
    unsigned cap_
  ): name(nm), src(src_), dest(dest_), cap(cap_) {}

  virtual ~Ship(){}

  std::string getName() {
    return this->name;
  }

  virtual std::string toString() const {
    std::ostringstream ss;
    ss << this->name << ": " << this->src << " -> " << this->dest;
    ss << ", " << this->cap << std::endl;
    return ss.str();
  }

  virtual bool canLoad(const Cargo* cargo) const {
    return false;
  }

  virtual void load(const Cargo* cargo) {
    return;
  }

  virtual void printShip() const {}

  friend void printRoutes(const std::vector<Ship*>&);

  friend std::ostream& operator<<(std::ostream& os, const Ship&);
};


class ContainerShip : public Ship {
private:
  std::set<std::string> properties;
  unsigned slots;
  std::vector<const Cargo*> loaded;
  unsigned loaded_wt;

public:
  ContainerShip():
    Ship(),
    properties(std::set<std::string>()),
    slots(0),
    loaded(std::vector<const Cargo*>()),
    loaded_wt(0) {}

  ContainerShip(
    std::string nm,
    std::string src_,
    std::string dest_,
    unsigned cap_,
    unsigned slots_
  ):
    Ship(nm, src_, dest_, cap_),
    properties(std::set<std::string>()),
    slots(slots_),
    loaded(std::vector<const Cargo*>()),
    loaded_wt(0) {}

  
  void addProperty(std::string prop) {
    if (prop.size() == 0) {
      // empty field
    }
    this->properties.insert(prop);
  }

  bool canLoad(const Cargo* cargo) const {
    if (cargo->getRequiredShip().compare("container") != 0) {
      return false;
    }
    if (cargo->getSrc().compare(this->src) != 0 || cargo->getDest().compare(this->dest) != 0) {
      return false;
    }
    for (size_t i = 0; i < cargo->getProperties().size(); ++i) {
      if (this->properties.find(cargo->getProperties()[i]) == this->properties.end()) {
        return false;
      }
    }
    if (this->loaded_wt + cargo->getWt() > this->cap) {
      return false;
    }
    if (this->slots == this->loaded.size()) {
      return false;
    }
    return true;
  }

  void printShip() const {
    std::ostringstream ss;
    ss << "The Container Ship " << this->name << "(" << this->loaded_wt << "/";
    ss << this->cap << ") is carrying : " << std::endl;
    for (size_t i = 0; i < this->loaded.size(); ++i) {
      ss << "  " << this->loaded[i]->getName() << "(" << this->loaded[i]->getWt() << ")" << std::endl;
    }
    ss << "  (" << this->slots - this->loaded.size() << ") slots remain" << std::endl;
    std::cout << ss.str();
  }

  void load(const Cargo* cargo) {
    this->loaded_wt += cargo->getWt();
    this->loaded.push_back(cargo);
    std::cout << "  **Loading the cargo onto " << this->name << "**" << std::endl;
  }

  std::string toString() const {
    std::ostringstream ss;
    ss << this->name << ": " << this->src << " -> " << this->dest;
    ss << ", capacity: " << this->loaded_wt << "/" << this->cap << std::endl << "Types: ";
    std::set<std::string>::iterator it = this->properties.begin();
    while (it != this->properties.end()) {
      ss << *it;
      ++it;
      if (it != this->properties.end()) {
        ss << ", ";
      }
    }
    ss << std::endl;
    ss << "Slots: " << slots << std::endl;
    ss << "Loaded: " << loaded.size() << std::endl;
    return ss.str();
  }
};


#endif
