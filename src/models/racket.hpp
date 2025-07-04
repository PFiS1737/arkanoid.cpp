#pragma once

#include "../shared/bounceable.hpp"
#include <memory>

struct Racket final : Bounceable {
  Racket(const Vec2 &center, double width, double height);

  Racket(const Racket &) = delete;
  Racket(Racket &&) = delete;
  Racket &operator=(const Racket &) = delete;
  Racket &operator=(Racket &&) = delete;

  static unique_ptr<Racket> make(const Vec2 &center, double width, double height);

  void setCenterX(double centerX);
  Vec2 getDirVecAfterBounce(const Vec2 &pos, const Vec2 &dirVec) const override;
};
