#include "brick.hpp"

Brick::Brick(const Vec2 &center, const Color &color, double width, double height)
    : Bounceable{center, width, height, color} {
}

size_t Brick::getScore() const {
  return color.score;
}

bool Brick::hit() {
  return true;
}
