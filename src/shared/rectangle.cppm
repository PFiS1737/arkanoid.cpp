export module shared.rectangle;

import shared.color;
import shared.vec2;
import configs;

export struct Rectangle {
  Vec2 center;
  double width;
  double height;
  Color color;
  Color frameColor;

  Rectangle(const Vec2 &center, double width, double height, const Color &color = COLOR_WHITE,
            const Color &frameColor = COLOR_BLACK);

  Rectangle(const Rectangle &) = delete;
  Rectangle(Rectangle &&) = delete;
  Rectangle &operator=(const Rectangle &) = delete;
  Rectangle &operator=(Rectangle &&) = delete;

  double getLeft() const;
  double getRight() const;
  double getBottom() const;
  double getTop() const;
  Vec2 getTopLeft() const;
  Vec2 getTopRight() const;
  Vec2 getBottomLeft() const;
  Vec2 getBottomRight() const;

  virtual void draw() const;
};
