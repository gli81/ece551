#ifndef CARGO_HPP
#define CARGO_HPP

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

class Cargo {
protected:
  std::string name;
  std::string src;
  std::string dest;
  __uint64_t weight;
  std::vector<std::string> props;


public:
  Cargo(): name(""), src(""), dest(""), weight(0), props(std::vector<std::string>()) {}

  Cargo(
    std::string nm,
    std::string src_,
    std::string dest_,
    __uint64_t wt
  ): name(nm), src(src_), dest(dest_), weight(wt), props(std::vector<std::string>()) {}

  virtual ~Cargo() {}

  void addProperty(const std::string& prop) {
    if (prop.size() == 0) {
      // empty field
    }
    this->props.push_back(prop);
  }

  std::string getName() {
    return this->name;
  }

  std::string getName() const {
    return this->name;
  }

  std::string getSrc() {
    return this->src;
  }

  std::string getSrc() const {
    return this->src;
  }

  std::string getDest() {
    return this->dest;
  }

  std::string getDest() const {
    return this->dest;
  }

  virtual std::vector<std::string> getProperties() const {
    return this->props;
  }

  virtual __uint64_t getWt() const {
    return this->weight;
  }

  virtual std::string getRequiredShip() const {
    return "";
  };

  virtual std::string toString() const {
    std::ostringstream ss;
    ss << this->name << ": " << this->src << " -> " << this->dest;
    ss << ", weight: " << this->weight << std::endl;
    return ss.str();
  }

  friend std::ostream& operator<<(std::ostream& os, const Cargo& cargo);
};


class ContainerCargo : public Cargo {
public:
  ContainerCargo(): Cargo() {}

  ContainerCargo(
    std::string nm,
    std::string src_,
    std::string dest_,
    __uint64_t wt
  ): Cargo(nm, src_, dest_, wt) {}


  std::string getRequiredShip() const {
    return "container";
  }

  std::vector<std::string> getProperties() const {
    return this->props;
  }

  virtual std::string toString() const {
    std::ostringstream ss;
    ss << this->name << ": " << this->src << " -> " << this->dest;
    ss << ", weight: " << this->weight << std::endl;
    ss << "Properties: ";
    for (size_t i = 0; i < this->props.size(); ++i) {
      ss << this->props[i];
      if (i != props.size() - 1) {
        ss << ", ";
      }
    }
    ss << std::endl;
    return ss.str();
  }
};

#endif
