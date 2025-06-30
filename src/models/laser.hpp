#pragma once

#include "../shared/moveable.hpp"
#include "../shared/rectangle.hpp"

struct Laser : Moveable {
  Laser(const Vec2 &center);

  bool checkHit(const Rectangle &rect);

  void draw() const;
};
