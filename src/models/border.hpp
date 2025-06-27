#pragma once

#include "rectangle.hpp"

struct Border : Rectangle {
  Border(const Vec2 &topLeft, const Vec2 &bottomRight);
};
