#pragma once

#include "../shared/bounceable.hpp"

struct Border final : Bounceable {
  Border(const Vec2 &topLeft, const Vec2 &bottomRight);

  Border(const Border &) = delete;
  Border(Border &&) = delete;
  Border &operator=(const Border &) = delete;
  Border &operator=(Border &&) = delete;
};
