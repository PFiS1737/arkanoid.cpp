#pragma once

#include "brick.hpp"

struct NormalBrick final : Brick {
  NormalBrick(const Vec2 &center, Color color = COLOR_RED);

  NormalBrick(const NormalBrick &) = delete;
  NormalBrick(NormalBrick &&) = delete;
  NormalBrick &operator=(const NormalBrick &) = delete;
  NormalBrick &operator=(NormalBrick &&) = delete;
};
