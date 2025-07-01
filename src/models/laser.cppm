export module models.laser;

import shared.moveable;
import shared.rectangle;
import shared.vec2;

export struct Laser final : Moveable {
  Laser(const Vec2 &center);

  bool checkHit(const Rectangle &rect);

  void draw() const;
};
