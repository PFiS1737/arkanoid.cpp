#include "laser.hpp"
#include <allegro5/allegro_primitives.h>

Laser::Laser(const Vec2 &center) : Moveable(center, Vec2{0, 1}, LASER_SPEED) {
}

unique_ptr<Laser> Laser::make(const Vec2 &center) {
  return make_unique<Laser>(center);
}

bool Laser::checkHit(const Rectangle &rect) {
  double x = center.x;
  double y = center.y + LASER_LENGTH;
  return x > rect.getLeft() && x < rect.getRight() && y > rect.getBottom() && y < rect.getTop();
}

void Laser::draw() const {
  const float y = SCREEN_HEIGHT - center.y;
  al_draw_filled_rectangle(center.x - 1, y, center.x + 1, y - LASER_LENGTH, COLOR_RED);
}
