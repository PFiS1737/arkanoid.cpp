#include "vec2.hpp"
#include <algorithm>
#include <cmath>

using namespace std;

Vec2::Vec2(double x, double y) : x{x}, y{y} {
}

double Vec2::getModule() const {
  return sqrt(pow(x, 2) + pow(y, 2));
}

const Vec2 &Vec2::normalize() {
  double vecLength = getModule();

  x /= vecLength;
  y /= vecLength;

  return *this;
}

Vec2 Vec2::normalized() const {
  return Vec2(*this).normalize();
}

Vec2 Vec2::clamped(const Vec2 &min, const Vec2 &max) const {
  return Vec2{clamp(x, min.x, max.x), clamp(y, min.y, max.y)};
}

bool Vec2::operator==(const Vec2 &other) const {
  return static_cast<int>(x) == static_cast<int>(other.x) && static_cast<int>(y) == static_cast<int>(other.y);
}

Vec2 Vec2::operator+(const Vec2 &vec) const {
  return Vec2{x, y} += vec;
}

Vec2 &Vec2::operator+=(const Vec2 &vec) {
  x += vec.x;
  y += vec.y;
  return *this;
}

Vec2 Vec2::operator-(const Vec2 &vec) const {
  return Vec2{x, y} -= vec;
}

Vec2 &Vec2::operator-=(const Vec2 &vec) {
  x -= vec.x;
  y -= vec.y;
  return *this;
}

Vec2 Vec2::operator-() const {
  return Vec2{-x, -y};
}

Vec2 Vec2::operator*(double scalar) const {
  return Vec2{x, y} *= scalar;
}

Vec2 &Vec2::operator*=(double scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}
