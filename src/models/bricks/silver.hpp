#pragma once

#include "brick.hpp"

struct SilverBrick final : Brick {
  SilverBrick(const Vec2 &center);

  SilverBrick(const SilverBrick &) = delete;
  SilverBrick(SilverBrick &&) = delete;
  SilverBrick &operator=(const SilverBrick &) = delete;
  SilverBrick &operator=(SilverBrick &&) = delete;

  bool hit() override;
  void draw() const override;

private:
  size_t durability = BRICK_SILVER_DURABILITY;
};
