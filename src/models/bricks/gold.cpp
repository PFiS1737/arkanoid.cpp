#include "gold.hpp"

GoldBrick::GoldBrick(const Vec2 &center) : Brick{center, COLOR_GOLD} {
}

bool GoldBrick::hit() {
  return false;
}
