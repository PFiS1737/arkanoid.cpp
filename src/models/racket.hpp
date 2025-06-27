#pragma once

#include "rectangle.hpp"

struct Racket : Rectangle {
  Racket(const Vec2 &center, double width, double height);

  void setCenterX(double centerX);
};
