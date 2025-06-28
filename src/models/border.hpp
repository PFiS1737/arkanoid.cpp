#pragma once

#include "bounceable.hpp"

struct Border : Bounceable {
  Border(const Vec2 &topLeft, const Vec2 &bottomRight);
};
