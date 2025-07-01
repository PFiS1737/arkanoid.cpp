export module models.bricks.gold;

import models.brick;
import shared.vec2;

export struct GoldBrick final : Brick {
  GoldBrick(const Vec2 &center);

  GoldBrick(const GoldBrick &) = delete;
  GoldBrick(GoldBrick &&) = delete;
  GoldBrick &operator=(const GoldBrick &) = delete;
  GoldBrick &operator=(GoldBrick &&) = delete;

  void hit() override;
};
