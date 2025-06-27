#pragma once

#include "../configs.hpp"
#include "../vec2.hpp"

struct Rectangle {
  Vec2 center;
  double width;
  double height;
  ALLEGRO_COLOR color;

  Rectangle(const Vec2 &center, double width, double height, ALLEGRO_COLOR color = COLOR_WHITE);

  void draw() const;
};
