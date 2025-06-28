#pragma once

#include "bounceable.hpp"

struct Racket : Bounceable {
  Racket(const Vec2 &center, double width, double height);

  void setCenterX(double centerX);
};
