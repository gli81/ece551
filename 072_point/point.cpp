#include "point.hpp"
#include <cmath>
#include <cstdio>

Point::Point(): x(0), y(0) {}

void Point::move(double dx, double dy) {
    this->x += dx;
    this->y += dy;
}

double Point::distanceFrom(const Point& p) {
  double dist_x = p.x - this->x;
  double dist_y = p.y - this->y;
  return std::sqrt(dist_x * dist_x + dist_y * dist_y);
}
