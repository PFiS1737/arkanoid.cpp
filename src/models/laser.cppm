export module models.laser;

import shared.moveable;
import shared.rectangle;
import shared.vec2;
import std;

using namespace std;

export struct Laser final : Moveable {
  Laser(const Vec2 &center);

  Laser(const Laser &) = delete;
  Laser(Laser &&) = delete;
  Laser &operator=(const Laser &) = delete;
  Laser &operator=(Laser &&) = delete;

  static unique_ptr<Laser> make(const Vec2 &center);

  bool checkHit(const Rectangle &rect);

  void draw() const;
};
