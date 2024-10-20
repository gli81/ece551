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

class ArithmeticExpression : public Expression {
private:
  Expression* left;
  Expression* right;
  std::string m;
public:
  ArithmeticExpression(Expression* lhs, Expression* rhs): left(lhs), right(rhs) {}
  std::string toString() const;
  virtual ~ArithmeticExpression() {
    delete this->left;
    delete this->right;
  }
};

class PlusExpression : public ArithmeticExpression {
private:
  std::string m;
public:
  PlusExpression(Expression* lhs, Expression* rhs): ArithmeticExpression(lhs, rhs), m("+") {}
  //std::string toString() const;
};

class MinusExpression : public ArithmeticExpression {
private:
  std::string m;
public:
  MinusExpression(Expression* lhs, Expression* rhs): ArithmeticExpression(lhs, rhs), m("-") {}
};

class TimesExpression : public ArithmeticExpression {
private:
  std::string m;
public:
  TimesExpression(Expression* lhs, Expression* rhs): ArithmeticExpression(lhs, rhs), m("*") {}
};

class DivExpression : public ArithmeticExpression {
private:
  std::string m;
public:
  DivExpression(Expression* lhs, Expression* rhs): ArithmeticExpression(lhs, rhs), m("/") {}
};
#endif
