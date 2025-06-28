#pragma once

#include "brick.hpp"

struct GoldBrick final : Brick {
  GoldBrick(const Vec2 &center);

  GoldBrick(const GoldBrick &) = delete;
  GoldBrick(GoldBrick &&) = delete;
  GoldBrick &operator=(const GoldBrick &) = delete;
  GoldBrick &operator=(GoldBrick &&) = delete;

  bool hit() override;
};
