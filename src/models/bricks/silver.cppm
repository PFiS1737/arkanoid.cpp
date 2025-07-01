export module models.bricks.silver;

import models.brick;
import shared.bonus;
import shared.vec2;
import configs;
import std;

using namespace std;

export struct SilverBrick final : Brick {
  SilverBrick(const Vec2 &center, const Bonus &bonus);

  SilverBrick(const SilverBrick &) = delete;
  SilverBrick(SilverBrick &&) = delete;
  SilverBrick &operator=(const SilverBrick &) = delete;
  SilverBrick &operator=(SilverBrick &&) = delete;

  void hit() override;
  void draw() const override;

private:
  size_t durability = BRICK_SILVER_DURABILITY;
};
