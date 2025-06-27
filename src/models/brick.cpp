#include "brick.hpp"

Brick::Brick(const Vec2 &center, double width, double height)
    : Rectangle{center, width, height, ALLEGRO_COLOR{1, 0, 0, 1}} {
}

std::unique_ptr<Brick> Brick::makeBrick(const Vec2 &center, double width, double height) {
  return std::make_unique<Brick>(center, width, height);
}
