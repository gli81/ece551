#ifndef SHIPS_HPP
#define SHIPS_HPP

#include <string>
#include <vector>
#include "cargo.hpp"
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <limits>

class Ship {
protected:
  std::string name;
  std::string src;
  std::string dest;
  __uint64_t cap;
  std::set<std::string> properties;
  std::vector<const Cargo*> loaded;
  __uint64_t loaded_wt;


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
    __uint64_t cap_
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

  virtual bool canLoad(const Cargo* cargo) const = 0;

  virtual void load(const Cargo* cargo, bool step4=false) = 0;

  __uint64_t getRemainingCap() {return this->cap - this->loaded_wt;}

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
    __uint64_t cap_,
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

  void load(const Cargo* cargo, bool step4=false) {
    this->loaded_wt += cargo->getWt();
    this->loaded.push_back(cargo);
    if (step4) {
      std::cout << "Loading " << cargo->getName() << " onto " << this->name << " from ";
      std::cout << this->src << " to " << this->dest << " " << this->cap - this->loaded_wt;
      std::cout << " capacity remains" << std::endl;
    } else {
      std::cout << "  **Loading the cargo onto " << this->name << "**" << std::endl;
    }
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
  std::map<std::string, __uint64_t> cargo_wt;

public:
  TankerShip():
    Ship(),
    num_tanks(0),
    min_temp(0),
    max_temp(0),
    tank_used(0),
    cargo_wt(std::map<std::string, __uint64_t>()) {}

  TankerShip(
    std::string nm,
    std::string src_,
    std::string dest_,
    __uint64_t cap_,
    unsigned num_t,
    signed min_t,
    signed max_t
  ):
    Ship(nm, src_, dest_, cap_),
    num_tanks(num_t),
    min_temp(min_t),
    max_temp(max_t),
    tank_used(0),
    cargo_wt(std::map<std::string, __uint64_t>()) {}
  

  bool canLoad(const Cargo* cargo) const {
    if (cargo->getRequiredShip().compare("tanker") != 0) {
      return false;
    }
    if (cargo->getSrc().compare(this->src) != 0 || cargo->getDest().compare(this->dest) != 0) {
      return false;
    }
    std::vector<std::string> cargo_props = cargo->getProperties();
    for (size_t i = 0; i < cargo_props.size(); ++i) {
      if (this->properties.find(cargo_props[i]) == this->properties.end()) {
        return false;
      }
    }
    if (this->loaded_wt + cargo->getWt() > this->cap) {
      return false;
    }
    // check if there is enough tank
    __uint64_t per_tank = this->cap / this->num_tanks;
    //@@@std::cout << "gethere before check enough tank\n";
    if (this->cargo_wt.find(cargo->getName()) != this->cargo_wt.end()) {
      // there is some same item in a tank
      __uint64_t cur_wt = this->cargo_wt.at(cargo->getName());
      unsigned cur_tank = cur_wt / per_tank;// + (cur_wt % per_tank > 0);
      if (cur_wt % per_tank > 0) ++cur_tank;
      __uint64_t new_wt = cur_wt + cargo->getWt();
      unsigned extra_tank = new_wt / per_tank - cur_tank;// + (cur_wt % per_tank > 0) - cur_tank;
      if (new_wt % per_tank > 0) ++extra_tank;
      if (tank_used + extra_tank > num_tanks) {
        return false;
      }
    } else {
      // new item
      unsigned extra_tank = cargo->getWt() / per_tank;
      if (cargo->getWt() % per_tank > 0) ++extra_tank;
      if (tank_used + extra_tank > num_tanks) {
        return false;
      }
    }
    // check temperature
    //@@@std::cout << "gethere before check temperature\n";
    signed cargo_min_temp = std::numeric_limits<int>::min();
    signed cargo_max_temp = std::numeric_limits<int>::max();
    std::map<std::string, signed> cargo_pmap = cargo->getPropMap();
    if (cargo_pmap.find("mintemp") != cargo_pmap.end()) {
      cargo_min_temp = cargo_pmap["mintemp"];
    }
    if (cargo_pmap.find("maxtemp") != cargo_pmap.end()) {
      cargo_max_temp = cargo_pmap["maxtemp"];
    }
    if (cargo_max_temp < this->min_temp || cargo_min_temp > this->max_temp) {
      return false;
    }
    return true;
  }

  void load(const Cargo* cargo, bool step4=false) {
    this->loaded_wt += cargo->getWt();
    this->loaded.push_back(cargo);
    __uint64_t per_tank = this->cap / this->num_tanks;
    if (this->cargo_wt.find(cargo->getName()) != this->cargo_wt.end()) {
      // there is some same item in some tank
      __uint64_t cur_wt = this->cargo_wt.at(cargo->getName());
      unsigned cur_tank = cur_wt / per_tank;// + (cur_wt % per_tank > 0);
      if (cur_wt % per_tank > 0) ++cur_tank;
      //@@@std::cout << this->name << " current tank taken by " << cargo->getName() << ": " << cur_tank << std::endl;
      __uint64_t new_wt = cur_wt + cargo->getWt();
      unsigned extra_tank = new_wt / per_tank - cur_tank;// + (cur_wt % per_tank > 0) - cur_tank;
      if (new_wt % per_tank > 0) ++extra_tank;
      this->tank_used += extra_tank;
      this->cargo_wt[cargo->getName()] += cargo->getWt();
      //@@@std::cout << this->name << " after loading tank taken by " << cargo->getName() << ": " << cur_tank + extra_tank << std::endl;
      //@@@std::cout << "Extraa " << extra_tank << " taken\n" << num_tanks - tank_used << " left\n";
    } else {
      // new item
      //@@@std::cout << this->name << " current tank taken by " << cargo->getName() << ": 0" << std::endl;
      unsigned extra_tank = cargo->getWt() / per_tank;
      if (cargo->getWt() % per_tank > 0) ++extra_tank;
      this->tank_used += extra_tank;
      this->cargo_wt[cargo->getName()] = cargo->getWt();
      //@@@std::cout << this->name << " after loading tank taken by " << cargo->getName() << ": " << extra_tank << std::endl;
      //@@@std::cout << "Extrab " << extra_tank << " taken\n" << num_tanks - tank_used << "left\n";
    }
    if (step4) {
      std::cout << "Loading " << cargo->getName() << " onto " << this->name << " from ";
      std::cout << this->src << " to " << this->dest << " " << this->cap - this->loaded_wt;
      std::cout << " capacity remains" << std::endl;
    } else {
      std::cout << "  **Loading the cargo onto " << this->name << "**" << std::endl;
    }
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
    ss << "  " << this->tank_used << " / " <<  this->num_tanks << " tanks used" << std::endl;
    return ss.str();
  }
};


class AnimalShip : public Ship {
private:
  __uint64_t small_enough;
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
    __uint64_t cap_,
    __uint64_t small_enough_
  ):
    Ship(nm, src_, dest_, cap_),
    small_enough(small_enough_),
    has_roamer(false) {}


  bool hasRoamer() const {return this->has_roamer;}

  bool canLoad(const Cargo* cargo) const {
    //if (cargo->getRequiredShip().compare("tanker") == 0) {
    //  return false;
    //}
    if (cargo->getSrc().compare(this->src) != 0 || cargo->getDest().compare(this->dest) != 0) {
      //@@@if (this->name.compare("The Dawn Boat") == 0) std::cout << "lane wrong\n";
      return false;
    }
    if (this->loaded_wt + cargo->getWt() > this->cap) {
      //@@@if (this->name.compare("The Dawn Boat") == 0) std::cout << "weight wrong\n";
      return false;
    }
    std::string type = cargo->getRequiredShip();
    // animal cargo
    if (type.compare("animal") == 0) {
      if (this->hasRoamer() && cargo->isRoamer()) {
        //@@@if (this->name.compare("The Dawn Boat") == 0) std::cout << "roamer wrong\n";
        return false;
      }
    } else if (type.compare("container") == 0) {
      // container cargo
      // not hazardous
      if (cargo->getHazardous()) {
        //@@@if (this->name.compare("The Dawn Boat") == 0) std::cout << "hazardous wrong\n";
        return false;
      }
      // small enough
      if (cargo->getWt() > this->small_enough) {
        //@@@if (this->name.compare("The Dawn Boat") == 0) std::cout << "small enough wrong\n";
        return false;
      }
    } else {
      // liquid or gas can't be loaded
      return false;
    }
    return true;
  }

  void load(const Cargo* cargo, bool step4=false) {
    this->loaded_wt += cargo->getWt();
    if (cargo->isRoamer()) {
      this->has_roamer = true;
    }
    this->loaded.push_back(cargo);
    if (step4) {
      std::cout << "Loading " << cargo->getName() << " onto " << this->name << " from ";
      std::cout << this->src << " to " << this->dest << " " << this->cap - this->loaded_wt;
      std::cout << " capacity remains" << std::endl;
    } else {
      std::cout << "  **Loading the cargo onto " << this->name << "**" << std::endl;
    }
  }

  std::string toString(bool verbose = false) const {
    std::ostringstream ss;
    ss << "The Animals Ship " << this->name << "(" << this->loaded_wt << "/";
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
