#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"

class Circle {
private:
  Point center;
  double const radius;


public:
  Circle(const Point& p, double radius);


  void move(double dx, double dy);

  double intersectionArea(const Circle& otherCircle) const;
};
#endif
