#ifndef __T_POLY__
#define __T_POLY__

#include <ostream>

template<typename NumT>
class Polynomial {

public:
  Polynomial();
  Polynomial operator+(const Polynomial& rhs) const;
  Polynomial operator-() const;
  Polynomial operator-(const Polynomial& rhs) const;
  Polynomial operator*(cons NumT& n) const;
  Polynomial operator*(const Polynomial& rhs) const;
  bool operator!=(const Polynomial& rhs) const;
  bool operator==(const Polynomial& rhs) const;
  void addTerm(const NumT& c, unsigned p);
  Polynomial& operator+=(const Polynomial& rhs);
  Polynomial& operator-=(const Polynomial& rhs);
  Polynomial& operator*=(const Polynomial& rhs);
  Polynomial& operator*=(const NumT& rhs);
  template<N>
  friend std::ostream& operator<<(std::ostream& os, const Polynomial<N>& p);
}

#endif
