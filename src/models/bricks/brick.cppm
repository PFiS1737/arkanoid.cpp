export module models.brick;

import shared.bonus;
import shared.bounceable;
import shared.color;
import shared.vec2;
import configs;
import std;

using namespace std;

export struct Brick : Bounceable {
  Bonus bonus;

  bool destroyed = false;

  Brick(const Vec2 &center, const Color &color, const Bonus &bonus = BONUS_NONE);

  Brick(const Brick &) = delete;
  Brick(Brick &&) = delete;
  Brick &operator=(const Brick &) = delete;
  Brick &operator=(Brick &&) = delete;

  template <typename T>
  static shared_ptr<T> make(const Vec2 &center) {
    return make_shared<T>(center);
  }

  template <typename T>
  static shared_ptr<T> make(const Vec2 &center, const Bonus &bonus) {
    return make_shared<T>(center, bonus);
  }

  template <typename T>
  static shared_ptr<T> make(const Vec2 &center, const Color &color, const Bonus &bonus) {
    return make_shared<T>(center, color, bonus);
  }

  virtual size_t getScore() const;
  virtual void hit();

  virtual void draw() const override;
};
