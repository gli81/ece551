#include "circle.hpp"
#include <cmath>
#include <algorithm>

Circle::Circle(const Point& p, double radius): center(p), radius(radius){}

void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle& otherCircle) const{
  double d = center.distanceFrom(otherCircle.center);
  double r1 = radius;
  double r2 = otherCircle.radius;
  if (d >= r1 + r2) {
    return 0;
  }
  else if (d <= fabs(r1 - r2)) {
    return M_PI * std::pow(std::min(r1, r2), 2);
  }

  double r1Sq = r1 * r1;
  double r2Sq = r2 * r2;
  double part1 = r1Sq * acos((d*d + r1Sq - r2Sq) / (2 * d * r1));
  double part2 = r2Sq * acos((d*d + r2Sq - r1Sq) / (2 * d * r2));
  double part3 = 0.5 * sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2));
  return part1 + part2 - part3;
}
