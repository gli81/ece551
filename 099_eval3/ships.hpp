#ifndef SHIPS_HPP
#define SHIPS_HPP

#include <string>
#include <vector>
#include "cargo.hpp"
#include <sstream>
#include <set>
#include <map>
#include <iostream>

class Ship {
protected:
  std::string name;
  std::string src;
  std::string dest;
  unsigned cap;
  std::set<std::string> properties;
  std::vector<const Cargo*> loaded;
  unsigned loaded_wt;


public:
  Ship():
    name(std::string()),
    src(std::string()),
    dest(std::string()),
    cap(0),
    properties(std::set<std::string>()),
    loaded(std::vector<const Cargo*>()),
    loaded_wt(0) {}

  Ship(
    std::string nm,
    std::string src_,
    std::string dest_,
    unsigned cap_
  ):
    name(nm),
    src(src_),
    dest(dest_),
    cap(cap_),
    properties(std::set<std::string>()),
    loaded(std::vector<const Cargo*>()),
    loaded_wt(0) {}

  virtual ~Ship(){}


  void addProperty(std::string prop) {
    if (prop.size() == 0) {
      // empty field
    }
    this->properties.insert(prop);
  }

  std::string getName() {
    return this->name;
  }

  virtual std::string toString(bool verbose = false) const = 0;

  virtual bool canLoad(const Cargo* cargo) const {
    return false;
  }

  virtual void load(const Cargo* cargo) {
    return;
  }

  friend void printRoutes(const std::vector<Ship*>&);

  friend std::ostream& operator<<(std::ostream& os, const Ship&);
};


class ContainerShip : public Ship {
private:
  unsigned slots;


public:
  ContainerShip():
    Ship(),
    slots(0) {}

  ContainerShip(
    std::string nm,
    std::string src_,
    std::string dest_,
    unsigned cap_,
    unsigned slots_
  ):
    Ship(nm, src_, dest_, cap_),
    slots(slots_){}

  
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

  void load(const Cargo* cargo) {
    this->loaded_wt += cargo->getWt();
    this->loaded.push_back(cargo);
    std::cout << "  **Loading the cargo onto " << this->name << "**" << std::endl;
  }

  std::string toString(bool verbose = false) const {
    std::ostringstream ss;
    ss << "The Container Ship " << this->name << "(" << this->loaded_wt << "/";
    ss << this->cap << ") ";
    if (verbose) {
      ss << this->src << " -> " << this->dest << std::endl;
      ss << "  Types: ";
      std::set<std::string>::iterator it = this->properties.begin();
      while (it != this->properties.end()) {
        ss << *it;
        ++it;
        if (it != this->properties.end()) {
          ss << ", ";
        }
      }
      ss << std::endl;
      ss << "  Slots: " << this->slots;
      ss << "  Loaded: " << this->loaded.size() << std::endl << "  ";
    }
    ss << "is carrying : " << std::endl;
    for (size_t i = 0; i < this->loaded.size(); ++i) {
      ss << "  " << this->loaded[i]->getName() << "(" << this->loaded[i]->getWt() << ")" << std::endl;
    }
    ss << "  (" << this->slots - this->loaded.size() << ") slots remain" << std::endl;
    return ss.str();
  }
};


class TankerShip : public Ship {
private:
  unsigned num_tanks;
  signed min_temp;
  signed max_temp;
  unsigned tank_used;
  std::map<std::string, unsigned> cargo_wt;

public:
  TankerShip():
    Ship(),
    num_tanks(0),
    min_temp(0),
    max_temp(0),
    tank_used(0),
    cargo_wt(std::map<std::string, unsigned>()) {}

  TankerShip(
    std::string nm,
    std::string src_,
    std::string dest_,
    unsigned cap_,
    unsigned num_t,
    signed min_t,
    signed max_t
  ):
    Ship(nm, src_, dest_, cap_),
    num_tanks(num_t),
    min_temp(min_t),
    max_temp(max_t),
    tank_used(0),
    cargo_wt(std::map<std::string, unsigned>()) {}
  

  bool canLoad(const Cargo* cargo) const {
    if (cargo->getRequiredShip().compare("tanker") != 0) {
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
    //if (this->slots == this->loaded.size()) {
    //  return false;
    //}
    return true;
  }

  void load(const Cargo* cargo) {
    this->loaded_wt += cargo->getWt();
    this->loaded.push_back(cargo);
    std::cout << "  **Loading the cargo onto " << this->name << "**" << std::endl;
  }

  std::string toString(bool verbose = false) const {
    std::ostringstream ss;
    ss << "The Tanker Ship " << this->name << "(" << this->loaded_wt << "/";
    ss << this->cap << ") ";
    if (verbose) {
      ss << this->src << " -> " << this->dest << std::endl;
      ss << "  Temp: " << this->min_temp << " ~ " << this->max_temp << std::endl;
      ss << "  Types: ";
      std::set<std::string>::iterator it = this->properties.begin();
      while (it != this->properties.end()) {
        ss << *it;
        ++it;
        if (it != this->properties.end()) {
          ss << ", ";
        }
      }
      ss << std::endl << "  ";
    }
    ss << "is carrying : " << std::endl;
    for (size_t i = 0; i < this->loaded.size(); ++i) {
      ss << "  " << this->loaded[i]->getName() << "(" << this->loaded[i]->getWt() << ")" << std::endl;
    }
    ss << "  (" << this->tank_used << "/" <<  this->num_tanks << ") tanks used" << std::endl;
    return ss.str();
  }
};


class AnimalShip : public Ship {
private:
  unsigned small_enough;
  bool has_roamer;


public:
  AnimalShip():
    Ship(),
    small_enough(0),
    has_roamer(false) {}

  AnimalShip(
    std::string nm,
    std::string src_,
    std::string dest_,
    unsigned cap_,
    unsigned small_enough_
  ):
    Ship(nm, src_, dest_, cap_),
    small_enough(small_enough_){}


  bool hasRoamer() const {return this->has_roamer;}

  bool canLoad(const Cargo* cargo) const {
    if (cargo->getRequiredShip().compare("tanker") == 0) {
      return false;
    }
    if (cargo->getSrc().compare(this->src) != 0 || cargo->getDest().compare(this->dest) != 0) {
      return false;
    }
    if (this->loaded_wt + cargo->getWt() > this->cap) {
      return false;
    }
    std::string type = cargo->getRequiredShip();
    // animal cargo
    if (type.compare("animal") == 0) {
      if (this->hasRoamer() && cargo->isRoamer()) {
        return false;
      }
    } else if (type.compare("container") == 0) {
      // container cargo
      // not hazardous
      if (cargo->getHazardous()) {return false;}
      // small enough
      if (cargo->getWt() > this->small_enough) {return false;}
    } else {
      // liquid or gas can't be loaded
      return false;
    }
    return true;
  }

  void load(const Cargo* cargo) {
    this->loaded_wt += cargo->getWt();
    if (cargo->isRoamer()) {
      this->has_roamer = true;
    }
    this->loaded.push_back(cargo);
    std::cout << "  **Loading the cargo onto " << this->name << "**" << std::endl;
  }

  std::string toString(bool verbose = false) const {
    std::ostringstream ss;
    ss << "The Animal Ship " << this->name << "(" << this->loaded_wt << "/";
    ss << this->cap << ") ";
    if (verbose) {
      ss << this->src << " -> " << this->dest << std::endl;
      ss << "  Small enough: " << this->small_enough << std::endl << "  ";
    }
    ss << "is carrying : " << std::endl;
    for (size_t i = 0; i < this->loaded.size(); ++i) {
      ss << "  " << this->loaded[i]->getName() << "(" << this->loaded[i]->getWt() << ")" << std::endl;
    }
    if (this->hasRoamer()) {ss << "  has a roamer";}
    else {ss << "  does not have a roamer";}
    ss << std::endl;
    return ss.str();
  }
};

#endif
