#pragma once

#include "rectangle.hpp"
#include <memory>

struct Brick : Rectangle {
  static std::unique_ptr<Brick> makeBrick(const Vec2 &center, double width, double height);

  Brick(const Vec2 &center, double width, double height);
};
