#pragma once

#include "../shared/bounceable.hpp"
#include "../shared/circle.hpp"
#include <memory>

struct Ball final : Circle {
  bool stuck = false;

  Ball(const Vec2 &center, double radius = BALL_RADIUS, const Vec2 &dirVec = BALL_INITIAL_DIRECTION,
       double speed = BALL_SPEED);

  Ball(const Ball &) = delete;
  Ball(Ball &&) = delete;
  Ball &operator=(const Ball &) = delete;
  Ball &operator=(Ball &&) = delete;

  static unique_ptr<Ball> make();
  static unique_ptr<Ball> make(const Ball &base, const Vec2 &dirVec);

  double getCollDist(const Rectangle &rect) const;
  bool checkCollision(const Rectangle &rect) const;
  void collide(const Bounceable &bounceable);

  void update(double dt) override;

private:
  Vec2 getCollPosOnRect(const Rectangle &rect) const;
};
