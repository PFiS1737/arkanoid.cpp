#pragma once

#include "bounceable.hpp"

struct Racket : Bounceable {
  Racket(const Vec2 &center, double width, double height);

  void setCenterX(double centerX);
  Vec2 getDirVecAfterBounce(const Vec2 &pos, const Vec2 &dirVec) const override;
};
