#pragma once

#include "rectangle.hpp"

struct Bounceable : Rectangle {
  enum class BounceType { Vertical, Horizontal, Corner };

  Bounceable(const Vec2 &center, double width, double height);
  Bounceable(const Vec2 &center, double width, double height, Color color);

  virtual Vec2 getDirVecAfterBounce(const Vec2 &pos, const Vec2 &dirVec) const;

  BounceType getBounceType(const Vec2 &pos) const;
};
