#include "pill.hpp"

Pill::Pill(const Vec2 &center, const Bonus &bonus)
    : Circle{center, PILL_RADIUS, Vec2{0, -1}, PILL_SPEED, bonus.color}, bonus{bonus} {
}

unique_ptr<Pill> Pill::make(const Vec2 &center, const Bonus &bonus) {
  return make_unique<Pill>(center, bonus);
}

bool Pill::checkCatching(const Rectangle &rect) {
  return center.x > rect.getLeft() && center.x < rect.getRight() && center.y > rect.getBottom() &&
         center.y < rect.getTop();
}
