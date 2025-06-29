#include "bounceable.hpp"

Bounceable::Bounceable(const Vec2 &center, double width, double height) : Rectangle{center, width, height} {
}

Bounceable::Bounceable(const Vec2 &center, double width, double height, Color color)
    : Rectangle{center, width, height, color} {
}

Bounceable::Bounceable(const Vec2 &center, double width, double height, Color color, Color frameColor)
    : Rectangle{center, width, height, color, frameColor} {
}

Bounceable::BounceType Bounceable::getBounceType(const Vec2 &pos) const {
  if (pos == getTopLeft() || pos == getTopRight() || pos == getBottomLeft() || pos == getBottomRight()) {
    return BounceType::Corner;
  } else if (pos.y == getBottom() || pos.y == getTop()) {
    return BounceType::Horizontal;
  } else {
    return BounceType::Vertical;
  }
}

Vec2 Bounceable::getDirVecAfterBounce(const Vec2 &pos, const Vec2 &dirVec) const {
  BounceType bounceType = getBounceType(pos);

  Vec2 ret = dirVec;
  if (bounceType == BounceType::Horizontal) {
    ret.y = -ret.y;
  } else if (bounceType == BounceType::Vertical) {
    ret.x = -ret.x;
  } else if (bounceType == BounceType::Corner) {
    ret.y = -ret.y;
    ret.x = -ret.x;
  }

  return ret;
}
