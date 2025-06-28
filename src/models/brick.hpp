#pragma once

#include "bounceable.hpp"
#include <memory>

struct Brick final : Bounceable {
  static unique_ptr<Brick> makeBrick(const Vec2 &center, double width, double height, Color color);

  Brick(const Vec2 &center, double width, double height, Color color);

  Brick(const Brick &) = delete;
  Brick(Brick &&) = delete;
  Brick &operator=(const Brick &) = delete;
  Brick &operator=(Brick &&) = delete;

  size_t getScore() const;
};
