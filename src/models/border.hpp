#pragma once

#include "../shared/bounceable.hpp"
#include <memory>

struct Border final : Bounceable {
  Border(const Vec2 &topLeft, const Vec2 &bottomRight);

  Border(const Border &) = delete;
  Border(Border &&) = delete;
  Border &operator=(const Border &) = delete;
  Border &operator=(Border &&) = delete;

  static unique_ptr<Border> make(const Vec2 &topLeft, const Vec2 &bottomRight);
};
