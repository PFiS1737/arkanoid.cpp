#include "brick.hpp"

Brick::Brick(const Vec2 &center, double width, double height, Color color) : Bounceable{center, width, height, color} {
}

unique_ptr<Brick> Brick::makeBrick(const Vec2 &center, double width, double height, Color color) {
  return make_unique<Brick>(center, width, height, color);
}

size_t Brick::getScore() const {
  return color.score;
}
