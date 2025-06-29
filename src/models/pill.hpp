#pragma once

#include "../shared/circle.hpp"
#include "../shared/rectangle.hpp"
#include <memory>

struct Pill final : Circle {
  Bonus bonus;

  Pill(const Vec2 &center, const Bonus &bonus);

  Pill(const Pill &) = delete;
  Pill(Pill &&) = delete;
  Pill &operator=(const Pill &) = delete;
  Pill &operator=(Pill &&) = delete;

  static shared_ptr<Pill> make(const Vec2 &center, const Bonus &bonus);

  bool checkCatching(const Rectangle &rect);
};
