#ifndef CARGO_HPP
#define CARGO_HPP

#include <string>
#include <vector>
#include <ostream>
#include <sstream>
#include <iostream>
#include <map>
#include <cstdlib>

class Cargo {
protected:
  std::string name;
  std::string src;
  std::string dest;
  __uint64_t weight;
  bool hazardous;


public:
  Cargo(): name(""), src(""), dest(""), weight(0), hazardous(false) {}

  Cargo(
    std::string nm,
    std::string src_,
    std::string dest_,
    __uint64_t wt
  ): name(nm), src(src_), dest(dest_), weight(wt), hazardous(false) {}

  virtual ~Cargo() {}

  virtual bool isRoamer() const {return false;}

  virtual void addProperty(const std::string& prop) = 0;

  virtual std::vector<std::string> getProperties() const = 0;

  std::string& getName() {return this->name;};

  std::string getName() const {return this->name;}

  std::string& getSrc() {return this->src;}

  std::string getSrc() const {return this->src;}

  std::string& getDest() {return this->dest;}

  std::string getDest() const {return this->dest;}

  virtual __uint64_t getWt() const {return this->weight;}

  virtual std::string getRequiredShip() const = 0;

  virtual std::string toString() const = 0;

  virtual void setHazardous(bool haz_) {this->hazardous = haz_;}
  
  bool getHazardous() const {return this->hazardous;}
  
  virtual std::map<std::string, signed> getPropMap() const {return std::map<std::string, signed>();}

  friend std::ostream& operator<<(std::ostream& os, const Cargo& cargo);
};


class ContainerCargo : public Cargo {
private:
  std::vector<std::string> props;
public:
  ContainerCargo(): Cargo(), props(std::vector<std::string>()) {}

  ContainerCargo(
    std::string nm,
    std::string src_,
    std::string dest_,
    __uint64_t wt
  ):
    Cargo(nm, src_, dest_, wt),
    props(std::vector<std::string>()) {}


  std::string getRequiredShip() const {return "container";}

  void addProperty(const std::string& prop) {
    if (prop.size() == 0) {
      // empty field
    }
    this->props.push_back(prop);
  }

  std::vector<std::string> getProperties() const {return this->props;}

  std::string toString() const {
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


class TankerCargo : public Cargo {
private:
  std::map<std::string, signed> props;
public:
  TankerCargo() : Cargo(), props(std::map<std::string, signed>()) {}

  TankerCargo(
    std::string nm,
    std::string src_,
    std::string dest_,
    __uint64_t wt
  ): Cargo(nm, src_, dest_, wt), props(std::map<std::string, signed>()) {}


  std::string getRequiredShip() const {return "tanker";}

  void addProperty(const std::string& prop);

  std::vector<std::string> getProperties() const {
    std::vector<std::string> ans;
    for (std::map<std::string, signed>::const_iterator it = this->props.begin(); it != this->props.end(); ++it) {
      if (it->first.compare("maxtemp") != 0 && it->first.compare("mintemp") != 0) {
        ans.push_back(it->first);
      }
    }
    return ans;
  }
  
  std::map<std::string, signed> getPropMap() const {return this->props;}

  std::string toString() const {
    std::ostringstream ss;
    ss << this->name << ": " << this->src << " -> " << this->dest;
    ss << ", weight: " << this->weight << std::endl;
    ss << "min temp: ";
    if (this->props.find("mintemp") != this->props.end()) {
      ss << this->props.at("mintemp");
    } else {
      ss << "not specified";
    }
    ss << "  max temp: ";
    if (this->props.find("maxtemp") != this->props.end()) {
      ss << this->props.at("maxtemp");
    } else {
      ss << "not specified";
    }
    
    ss << std::endl;
    ss << "properties: ";
    for (size_t i = 0; i < this->getProperties().size(); ++i) {
      ss << this->getProperties()[i];
      if (i != this->getProperties().size() - 1) {
        ss << ", ";
      }
    }
    ss << std::endl;
    return ss.str();
  }
};


class AnimalCargo : public Cargo {
private:
  std::vector<std::string> props;
  bool roamer;
public:
  AnimalCargo(): Cargo(), props(std::vector<std::string>()), roamer(false) {}

  AnimalCargo(
    std::string nm,
    std::string src_,
    std::string dest_,
    __uint64_t wt
  ): Cargo(nm, src_, dest_, wt), props(std::vector<std::string>()), roamer(false) {}
  

  std::string getRequiredShip() const {return "animal";}
  
  bool isRoamer() const {return this->roamer;}

  void addProperty(const std::string& prop) {
    if (prop.size() == 0) {
      // empty field
    }
    if (prop.compare("roamer") == 0) {
      this->roamer = true;
      return;
    }
    this->props.push_back(prop);
  }

  std::vector<std::string> getProperties() const {return this->props;}

  //animal can be hazardous according to pregrader

  std::string toString() const {
    std::ostringstream ss;
    ss << this->name << ": " << this->src << " -> " << this->dest;
    ss << ", weight: " << this->weight << std::endl;
    ss << "roamer: ";
    if (this->roamer) {ss << "yes";} else {ss << "no";}
    ss << std::endl;
    ss << "properties: ";
    for (size_t i = 0; i < this->props.size(); ++i) {
      ss << this->props[i];
      if (i != this->props.size() - 1) {
        ss << ", ";
      }
    }
    ss << std::endl;
    return ss.str();
  }
};


class NullCargo : public Cargo {
public:
  NullCargo(): Cargo() {}

  NullCargo(
    std::string nm,
    std::string src_,
    std::string dest_,
    __uint64_t wt
  ): Cargo(nm, src_, dest_, wt) {}
  

  void addProperty(const std::string& prop) {}

  std::vector<std::string> getProperties() const {return std::vector<std::string>();}

  std::string getRequiredShip() const {return "";}

  std::string toString() const {
    std::ostringstream ss;
    ss << this->name << ": " << this->src << " -> " << this->dest;
    ss << ", weight: " << this->weight << std::endl;
    return ss.str();
  }
};

#endif
