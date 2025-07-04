#pragma once

#include "vec2.hpp"

struct Moveable {
  Vec2 center;
  Vec2 dirVec; // normalized
  double speed;

  Moveable(const Vec2 &center, const Vec2 &dirVec, double speed);

  Moveable(const Moveable &) = delete;
  Moveable(Moveable &&) = delete;
  Moveable &operator=(const Moveable &) = delete;
  Moveable &operator=(Moveable &&) = delete;

  virtual void update(double dt);
};
