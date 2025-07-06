module;

#include <allegro5/allegro_primitives.h>

module models.ball;

import configs;

Ball::Ball(const Vec2 &center, double radius, const Vec2 &dirVec, double speed)
    : Circle(center, radius, dirVec, speed, BALL_COLOR) {
}

unique_ptr<Ball> Ball::make() {
  double x = BOARD_WIDTH / 2 + BORDER_THICKNESS;
  double y = RACKET_Y_POSITION + RACKET_HEIGHT / 2 + BALL_RADIUS;
  return make_unique<Ball>(Vec2{x, y});
}

Vec2 Ball::getCollPosOnRect(const Rectangle &rect) const {
  Vec2 dist = center - rect.center;
  Vec2 half{rect.width / 2, rect.height / 2};

  return dist.clamped(-half, half) + rect.center;
}

bool Ball::checkCollision(const Rectangle &rect) const {
  Vec2 pos = getCollPosOnRect(rect);
  double dx = pos.x - center.x;
  double dy = pos.y - center.y;
  return Vec2{dx, dy}.getModule() < radius;
}

double Ball::getCollDist(const Rectangle &rect) const {
  return (center - getCollPosOnRect(rect)).getModule() - radius;
}

void Ball::collide(const Bounceable &bounceable) {
  dirVec = bounceable.getDirVecAfterBounce(getCollPosOnRect(bounceable), dirVec);
}

void Ball::update(double dt) {
  if (stuck) return;
  Circle::update(dt);
}
