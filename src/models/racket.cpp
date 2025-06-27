#include "racket.hpp"
#include <algorithm>

Racket::Racket(const Vec2 &center, double width, double height) : Rectangle{center, width, height} {
}

void Racket::setCenterX(double x) {
  auto left = BORDER_THICKNESS + (width / 2);
  auto right = (BOARD_WIDTH + BORDER_THICKNESS) - (width / 2);
  x = std::clamp(x, left, right);

  center.x = x;
}
