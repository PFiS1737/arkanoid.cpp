#include "circle.hpp"
#include <allegro5/allegro_primitives.h>

Circle::Circle(const Vec2 &center, double radius, Vec2 dirVec, double speed, Color color)
    : center{center}, radius{radius}, dirVec{dirVec.normalized()}, speed{speed}, color{color} {
}

void Circle::draw() const {
  const float y = SCREEN_HEIGHT - center.y;

  al_draw_filled_circle(center.x, y, radius, color);
  al_draw_circle(center.x, y, radius, COLOR_BLACK, 1);
}

void Circle::update(double dt) {
  center += (dirVec * speed * dt);
}
