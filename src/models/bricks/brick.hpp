#pragma once

#include "../../shared/bounceable.hpp"
#include <memory>

struct Brick : Bounceable {
  Bonus bonus;

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
  virtual bool hit(); // NOTE: returns true if the brick is destroyed, otherwise false

  virtual void draw() const override;
};
