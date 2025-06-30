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

  static shared_ptr<Ball> make();

  double getCollDist(const shared_ptr<Rectangle> &rect) const;
  bool checkCollision(const shared_ptr<Rectangle> &rect) const;
  void collide(const shared_ptr<Bounceable> &bounceable);

  void update(double dt) override;

private:
  Vec2 getCollPosOnRect(const shared_ptr<Rectangle> &rectangle) const;
};
