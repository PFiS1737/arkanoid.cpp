export module shared.bounceable;

import shared.color;
import shared.rectangle;
import shared.vec2;

export struct Bounceable : Rectangle {
  enum class BounceType { Vertical, Horizontal, Corner };

  Bounceable(const Vec2 &center, double width, double height);
  Bounceable(const Vec2 &center, double width, double height, const Color &color);
  Bounceable(const Vec2 &center, double width, double height, const Color &color, const Color &frameColor);

  Bounceable(const Bounceable &) = delete;
  Bounceable(Bounceable &&) = delete;
  Bounceable &operator=(const Bounceable &) = delete;
  Bounceable &operator=(Bounceable &&) = delete;

  virtual Vec2 getDirVecAfterBounce(const Vec2 &pos, const Vec2 &dirVec) const;

  BounceType getBounceType(const Vec2 &pos) const;
};
