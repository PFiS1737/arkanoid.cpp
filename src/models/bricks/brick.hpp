#pragma once

#include "../../shared/bounceable.hpp"
#include <memory>

struct Brick : Bounceable {
  Brick(const Vec2 &center, Color color, double width = BRICK_WIDTH, double height = BRICK_HEIGHT);

  Brick(const Brick &) = delete;
  Brick(Brick &&) = delete;
  Brick &operator=(const Brick &) = delete;
  Brick &operator=(Brick &&) = delete;

  template <typename T>
  static shared_ptr<T> make(const Vec2 &center) {
    return make_shared<T>(center);
  }

  template <typename T>
  static shared_ptr<T> make(const Vec2 &center, Color color) {
    return make_shared<T>(center, color);
  }

  virtual size_t getScore() const;
  virtual bool hit(); // returns true if the brick is destroyed, false otherwise
};
