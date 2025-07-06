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
  virtual ~Brick() = default;

  Brick(const Brick &) = delete;
  Brick(Brick &&) = delete;
  Brick &operator=(const Brick &) = delete;
  Brick &operator=(Brick &&) = delete;

  template <derived_from<Brick> T>
  static unique_ptr<T> make(const Vec2 &center) {
    return make_unique<T>(center);
  }

  template <derived_from<Brick> T>
  static unique_ptr<T> make(const Vec2 &center, const Bonus &bonus) {
    return make_unique<T>(center, bonus);
  }

  template <derived_from<Brick> T>
  static unique_ptr<T> make(const Vec2 &center, const Color &color, const Bonus &bonus) {
    return make_unique<T>(center, color, bonus);
  }

  virtual size_t getScore() const;
  virtual void hit();

  virtual void draw() const override;
};
