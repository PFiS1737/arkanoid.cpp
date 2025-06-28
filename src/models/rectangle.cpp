#include "rectangle.hpp"
#include "../../configs.hpp"
#include <allegro5/allegro_primitives.h>

Rectangle::Rectangle(const Vec2 &center, double width, double height, Color color)
    : center(center), width{width}, height{height}, color{color} {
}

double Rectangle::getLeft() const {
  return center.x - width / 2;
}

double Rectangle::getRight() const {
  return center.x + width / 2;
}

double Rectangle::getBottom() const {
  return center.y - height / 2;
}

double Rectangle::getTop() const {
  return center.y + height / 2;
}

Vec2 Rectangle::getTopLeft() const {
  return Vec2{getLeft(), getTop()};
}

Vec2 Rectangle::getTopRight() const {
  return Vec2{getRight(), getTop()};
}

Vec2 Rectangle::getBottomLeft() const {
  return Vec2{getLeft(), getBottom()};
}

Vec2 Rectangle::getBottomRight() const {
  return Vec2{getRight(), getBottom()};
}

void Rectangle::draw() const {
  const float y = SCREEN_HEIGHT - center.y;

  const float x1 = getLeft();
  const float y1 = y - height / 2;
  const float x2 = getRight();
  const float y2 = y + height / 2;

  al_draw_filled_rectangle(x1, y1, x2, y2, color);
  al_draw_rectangle(x1, y1, x2, y2, COLOR_BLACK, 1);
}
