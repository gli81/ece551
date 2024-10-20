#ifndef _EXPR_H_
#define _EXPR_H_

#include <string>
#include <ostream>

class Expression {
public:
  // abstract func must be virtual
  virtual std::string toString() const = 0;
  virtual ~Expression(){}
};

class NumExpression : public Expression {
private:
  long num;
public:
  NumExpression(long input_num): num(input_num) {}
  std::string toString() const;
};

class PlusExpression : public Expression {
private:
  Expression* left;
  Expression* right;
public:
  PlusExpression(Expression* lhs, Expression* rhs): left(lhs), right(rhs){}
  std::string toString() const;
  ~PlusExpression() {
    delete this->left;
    delete this->right;
  }
};

#endif
