#include "rectangle.hpp"
#include "../configs.hpp"
#include <allegro5/allegro_primitives.h>

Rectangle::Rectangle(const Vec2 &center, double width, double height, ALLEGRO_COLOR color)
    : center(center), width{width}, height{height}, color{color} {
}

void Rectangle::draw() const {
  const float y = SCREEN_HEIGHT - center.y;
  const float x1 = center.x - width / 2;
  const float y1 = y - height / 2;
  const float x2 = center.x + width / 2;
  const float y2 = y + height / 2;

  al_draw_filled_rectangle(x1, y1, x2, y2, color);
  al_draw_rectangle(x1, y1, x2, y2, COLOR_BLACK, 1);
}
