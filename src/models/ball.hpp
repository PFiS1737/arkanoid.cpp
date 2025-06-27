#pragma once

#include "../configs.hpp"
#include "../vec2.hpp"
#include <memory>

class Ball {
public:
  Vec2 center;
  double radius;
  Vec2 dirVec; // normalized
  double speed;

  Ball(const Vec2 &center, double radius = BALL_RADIUS, Vec2 dirVec = BALL_INITIAL_DIRECTION,
       double speed = BALL_SPEED);

  static std::shared_ptr<Ball> newBall();

  void update(double dt);
  void draw() const;
};
