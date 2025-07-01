module models.pill;

import configs;

Pill::Pill(const Vec2 &center, const Bonus &bonus)
    : Circle{center, PILL_RADIUS, Vec2{0, -1}, PILL_SPEED, bonus.color}, bonus{bonus} {
}

shared_ptr<Pill> Pill::make(const Vec2 &center, const Bonus &bonus) {
  return make_shared<Pill>(center, bonus);
}

bool Pill::checkCatching(const Rectangle &rect) {
  return center.x > rect.getLeft() && center.x < rect.getRight() && center.y > rect.getBottom() &&
         center.y < rect.getTop();
}
