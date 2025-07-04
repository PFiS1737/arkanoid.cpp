#pragma once

#include "../shared/moveable.hpp"
#include "../shared/rectangle.hpp"
#include <memory>

struct Laser final : Moveable {
  Laser(const Vec2 &center);

  Laser(const Laser &) = delete;
  Laser(Laser &&) = delete;
  Laser &operator=(const Laser &) = delete;
  Laser &operator=(Laser &&) = delete;

  static unique_ptr<Laser> make(const Vec2 &center);

  bool checkHit(const Rectangle &rect);

  void draw() const;
};
