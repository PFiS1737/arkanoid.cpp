#pragma once

#include "rectangle.hpp"
#include <memory>

struct Brick : Rectangle {
  static unique_ptr<Brick> makeBrick(const Vec2 &center, double width, double height, Color color);

  Brick(const Vec2 &center, double width, double height, Color color);

  size_t getScore() const;
};
