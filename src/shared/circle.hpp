#pragma once

#include "../../configs.hpp"

struct Circle {
  Vec2 center;
  double radius;
  Vec2 dirVec; // normalized
  double speed;
  Color color;

  Circle(const Vec2 &center, double radius, Vec2 dirVec, double speed, Color color = COLOR_WHITE);

  Circle(const Circle &) = delete;
  Circle(Circle &&) = delete;
  Circle &operator=(const Circle &) = delete;
  Circle &operator=(Circle &&) = delete;

  void update(double dt);

  void draw() const;
};
