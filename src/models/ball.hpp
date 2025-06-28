#pragma once

#include "../utilies/bounceable.hpp"
#include "../utilies/circle.hpp"
#include <memory>

struct Ball final : Circle {
  Ball(const Vec2 &center, double radius = BALL_RADIUS, Vec2 dirVec = BALL_INITIAL_DIRECTION,
       double speed = BALL_SPEED);

  Ball(const Ball &) = delete;
  Ball(Ball &&) = delete;
  Ball &operator=(const Ball &) = delete;
  Ball &operator=(Ball &&) = delete;

  static shared_ptr<Ball> newBall();

  double getCollDist(const Rectangle &rect) const;
  bool checkCollision(const Rectangle &rect) const;
  void collide(const Bounceable &bounceable);

private:
  Vec2 getCollPosOnRect(const Rectangle &rectangle) const;
};
