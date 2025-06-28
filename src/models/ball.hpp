#pragma once

#include "bounceable.hpp"
#include <memory>

class Ball final {
  Vec2 getCollPosOnRect(const Rectangle &rectangle) const;

public:
  Vec2 center;
  double radius;
  Vec2 dirVec; // normalized
  double speed;

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

  void update(double dt);
  void draw() const;
};
