#pragma once

#include "brick.hpp"

struct NormalBrick : Brick {
  NormalBrick(const Vec2 &center, const Color &color = COLOR_RED, const Bonus &bonus = BONUS_NONE);

  NormalBrick(const NormalBrick &) = delete;
  NormalBrick(NormalBrick &&) = delete;
  NormalBrick &operator=(const NormalBrick &) = delete;
  NormalBrick &operator=(NormalBrick &&) = delete;
};
