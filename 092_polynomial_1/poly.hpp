#ifndef __T_POLY__
#define __T_POLY__

#include <ostream>
#include <vector>
#include <iostream>
#include <cmath>
//#include <complex>

template<typename NumT>
class Polynomial {
private:
  std::vector<NumT> coeff;
public:
  Polynomial(): coeff(std::vector<NumT>()) {
    this->coeff.push_back(NumT());
  }

  Polynomial operator+(const Polynomial& rhs) const {
    Polynomial<NumT> ans;
    size_t max_ = std::max(this->coeff.size(), rhs.coeff.size());
    ans.coeff[0] = this->coeff[0] + rhs.coeff[0];
    for (size_t i = 1; i < max_; ++i) {
      if (i >= this->coeff.size()) {
        ans.addTerm(rhs.coeff[i], i);
      } else if (i >= rhs.coeff.size()) {
        ans.addTerm(this->coeff[i], i);
      } else {
        ans.addTerm(this->coeff[i] + rhs.coeff[i], i);
      }
    }
    return ans;
  }

  Polynomial operator-() const {
    Polynomial<NumT> ans;
    ans.coeff[0] = -this->coeff[0];
    for (size_t i = 1; i < this->coeff.size(); ++i) {
      ans.addTerm(-this->coeff[i], i);
    }
    return ans;
  }

  Polynomial operator-(const Polynomial& rhs) const {
    Polynomial<NumT> ans;
    size_t max_ = std::max(this->coeff.size(), rhs.coeff.size());
    ans.coeff[0] = this->coeff[0] - rhs.coeff[0];
    for (size_t i = 1; i < max_; ++i) {
      if (i >= this->coeff.size()) {
        ans.addTerm(-rhs.coeff[i], i);
      } else if (i >= rhs.coeff.size()) {
        ans.addTerm(this->coeff[i], i);
      } else {
        ans.addTerm(this->coeff[i] - rhs.coeff[i], i);
      }
    }
    return ans;
  }

  Polynomial operator*(const NumT& n) const {
    Polynomial<NumT> ans;
    ans.coeff[0] = this->coeff[0] * n;
    for (size_t i = 1; i < this->coeff.size(); ++i) {
      ans.addTerm(this->coeff[i] * n, i);
    }
    return ans;
  }
  
  Polynomial operator*(const Polynomial& rhs) const {
    if (this->coeff.size() == 1) {
      // this is a scalar
      return rhs * this->coeff[0];
    }
    if (rhs.coeff.size() == 1) {
      // rhs is a scalar
      return *this * rhs.coeff[0];
    }
    // create a new Polynomial
    Polynomial<NumT> ans;
    size_t highest = (this->coeff.size() - 1) + (rhs.coeff.size() - 1);
    ans.addTerm(NumT(), highest);
    for (size_t i = 0; i < this->coeff.size(); ++i) {
      for (size_t j = 0; j < rhs.coeff.size(); ++j) {
        ans.addTerm(this->coeff[i] * rhs.coeff[j], i + j);
      }
    }
    return ans;
  }

  bool operator!=(const Polynomial& rhs) const {
    //if (this->coeff.size() != rhs.coeff.size()) {
    //  return true;
    //}
    size_t this_len = this->coeff.size();
    size_t r_len = rhs.coeff.size();
    size_t min_ = std::min(this_len, r_len);
    for (size_t i = 0; i < min_; ++i) {
      if (this->coeff[i] != rhs.coeff[i]) {
        return true;
      }
    }
    if (this_len > r_len) {
      for (size_t i = r_len; i < this_len; ++i) {
        if (this->coeff[i] != -this->coeff[i]) {
          return true;
        }
      }
    } else {
      for (size_t i = this_len; i < r_len; ++i) {
        if (rhs.coeff[i] != -rhs.coeff[i]) {
          return true;
        }
      }
    }
    return false;
  }
  
  bool operator==(const Polynomial& rhs) const {
    //return !(*this != rhs);
    //if (this->coeff.size() != rhs.coeff.size()) {
    //  return false;
    //}
    size_t this_len = this->coeff.size();
    size_t r_len = rhs.coeff.size();
    size_t min_ = std::min(this_len, r_len);
    for (size_t i = 0; i < min_; ++i) {
      if (this->coeff[i] != rhs.coeff[i]) {
        return false;
      }
    }
    if (this_len > r_len) {
      for (size_t i = r_len; i < this_len; ++i) {
        if (this->coeff[i] != -this->coeff[i]) {
          return false;
        }
      }
    } else {
      for (size_t i = this_len; i < r_len; ++i) {
        if (rhs.coeff[i] - rhs.coeff[i] != rhs.coeff[i]) {
          return false;
        }
      }
    }
    return true;
  }
  
  void addTerm(const NumT& c, unsigned p) {
    size_t cur_len = this->coeff.size();
    if (p < cur_len) {
      this->coeff[p] += c;
    } else {
      while (cur_len < p) {
        this->coeff.push_back(NumT());
        cur_len++;
      }
      this->coeff.push_back(c);
    }
  }

  Polynomial& operator+=(const Polynomial& rhs) {
    *this = *this + rhs;
    return *this;
  }

  Polynomial& operator-=(const Polynomial& rhs) {
    *this = *this - rhs;
    return *this;
  }
  Polynomial& operator*=(const Polynomial& rhs) {
    *this = *this * rhs;
    return *this;
  }

  Polynomial& operator*=(const NumT& rhs) {
    *this = *this * rhs;
    return *this;
  }

  template<typename N>
  friend std::ostream& operator<<(std::ostream& os, const Polynomial<N>& p);

  NumT eval(const NumT& x) const {
    NumT ans = NumT();
    for (size_t i = 0; i < this->coeff.size(); ++i) {
      ans += this->coeff[i] * pow(x, i); // will pow work?
    }
    return ans;
  }

  Polynomial derivative() const {
    Polynomial<NumT> ans;
    if (this->coeff.size() == 1) {
      return ans;
    }
    ans.coeff[0] = this->coeff[1];
    for (size_t i = 2; i < this->coeff.size(); ++i) {
      ans.addTerm(NumT(i) * this->coeff[i], i - 1);
    }
    return ans;
  }

  NumT operator()(const NumT& x) const {
    return this->eval(x);
  }
};

template<typename N>
std::ostream& operator<<(std::ostream& os, const Polynomial<N>& p) {
  if (p.coeff.size() == 1 && p.coeff[0] == -p.coeff[0]) {
    return os << p.coeff[0];
  }
  bool first = true;
  for (size_t i = p.coeff.size() - 1; i > 0; --i) {
    if (p.coeff[i] - p.coeff[i] == p.coeff[i]) {continue;}
    if (!first) {
      os << " + ";
    }
    os << p.coeff[i] << "*x^" << i;
    first = false;
  }
  if (p.coeff[0] != p.coeff[0] - p.coeff[0]) {
    if (!first) {
      os << " + ";
    }
    os << p.coeff[0] << "*x^0";
  }  
  return os;
}

#endif
