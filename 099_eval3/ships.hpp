#ifndef SHIPS_HPP
#define SHIPS_HPP

#include <string>
#include <vector>

class Ship {
//private:
private:
  std::string name;
  std::string src;
  std::string dest;
  unsigned cap;
public:
  Ship(
    std::string nm,
    std::string src_,
    std::string dest_,
    unsigned cap_
  ): name(nm), src(src_), dest(dest_), cap(cap_) {}

  std::string getName() {
    return this->name;
  }
  friend void printRoutes(std::vector<Ship*>);
};

/*
class ContainerShip : public Ship {

};
*/

#endif
