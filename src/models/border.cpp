module models.border;

import configs;

Border::Border(const Vec2 &topLeft, const Vec2 &bottomRight)
    : Bounceable{
          Vec2{(topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2},
          abs(bottomRight.x - topLeft.x),
          abs(topLeft.y - bottomRight.y),
          BORDER_COLOR,
          BORDER_COLOR,
      } {
}

unique_ptr<Border> Border::make(const Vec2 &topLeft, const Vec2 &bottomRight) {
  return make_unique<Border>(topLeft, bottomRight);
}
