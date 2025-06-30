#include "laser.hpp"
#include "../../configs.hpp"
#include <allegro5/allegro_primitives.h>

Laser::Laser(const Vec2 &center) : Moveable(center, Vec2{0, 1}, LASER_SPEED) {
}

bool Laser::checkHit(const Rectangle &rect) {
  double x = center.x;
  double y = center.y + LASER_LENGTH;
  return x > rect.getLeft() && x < rect.getRight() && y > rect.getBottom() && y < rect.getTop();
}

void Laser::draw() const {
  double y = SCREEN_HEIGHT - center.y;
  al_draw_filled_rectangle(center.x - 1, y, center.x + 1, y - LASER_LENGTH, COLOR_RED);
}
