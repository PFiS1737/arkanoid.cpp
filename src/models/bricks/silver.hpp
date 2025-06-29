#pragma once

#include "normal.hpp"

struct SilverBrick final : NormalBrick {
  SilverBrick(const Vec2 &center); // TODO: support bonus

  SilverBrick(const SilverBrick &) = delete;
  SilverBrick(SilverBrick &&) = delete;
  SilverBrick &operator=(const SilverBrick &) = delete;
  SilverBrick &operator=(SilverBrick &&) = delete;

  bool hit() override;
  void draw() const override;

private:
  size_t durability = BRICK_SILVER_DURABILITY;
};
