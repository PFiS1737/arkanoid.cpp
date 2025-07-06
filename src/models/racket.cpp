module models.racket;

import configs;

Racket::Racket(const Vec2 &center, double width, double height) : Bounceable{center, width, height, RACKET_COLOR} {
}

unique_ptr<Racket> Racket::make(const Vec2 &center, double width, double height) {
  return make_unique<Racket>(center, width, height);
}

void Racket::setCenterX(double x) {
  auto left = BORDER_THICKNESS + (width / 2);
  auto right = (BOARD_WIDTH + BORDER_THICKNESS) - (width / 2);
  x = clamp(x, left, right);

  center.x = x;
}

Vec2 Racket::getDirVecAfterBounce(const Vec2 &pos, const Vec2 &dirVec) const {
  BounceType bounceType = getBounceType(pos);

  if (bounceType == BounceType::Horizontal && pos.y == getTop()) {
    double fromLeft = pos.x - (center.x - width / 2);

    double theta = (30 + 120 * (1 - (fromLeft / width))) * numbers::pi / 180;

    return Vec2{cos(theta), sin(theta)}.normalize();
  }

  return Bounceable::getDirVecAfterBounce(pos, dirVec);
}
