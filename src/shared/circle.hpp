#pragma once

#include "../../configs.hpp"
#include "moveable.hpp"

struct Circle : Moveable {
  double radius;
  Color color;

  Circle(const Vec2 &center, double radius, const Vec2 &dirVec, double speed, const Color &color = COLOR_WHITE);

  Circle(const Circle &) = delete;
  Circle(Circle &&) = delete;
  Circle &operator=(const Circle &) = delete;
  Circle &operator=(Circle &&) = delete;

  void draw() const;
};
