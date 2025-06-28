#pragma once

#include "../utilies/bounceable.hpp"

struct Racket final : Bounceable {
  Racket(const Vec2 &center, double width, double height);

  Racket(const Racket &) = delete;
  Racket(Racket &&) = delete;
  Racket &operator=(const Racket &) = delete;
  Racket &operator=(Racket &&) = delete;

  void setCenterX(double centerX);
  Vec2 getDirVecAfterBounce(const Vec2 &pos, const Vec2 &dirVec) const override;
};
