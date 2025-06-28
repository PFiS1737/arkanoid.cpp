#pragma once

#include "../configs.hpp"
#include "../vec2.hpp"

struct Rectangle {
  Vec2 center;
  double width;
  double height;
  Color color;

  Rectangle(const Vec2 &center, double width, double height, Color color = COLOR_WHITE);

  double getLeft() const;
  double getRight() const;
  double getBottom() const;
  double getTop() const;
  Vec2 getTopLeft() const;
  Vec2 getTopRight() const;
  Vec2 getBottomLeft() const;
  Vec2 getBottomRight() const;

  void draw() const;
};
