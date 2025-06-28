#include "ball.hpp"
#include <allegro5/allegro_primitives.h>

Ball::Ball(const Vec2 &center, double radius, Vec2 dirVec, double speed)
    : center{center}, radius{radius}, dirVec{dirVec.normalized()}, speed{speed} {
}
std::shared_ptr<Ball> Ball::newBall() {
  double x = BOARD_WIDTH / 2 + BORDER_THICKNESS;
  double y = RACKET_Y_POSITION + RACKET_HEIGHT / 2 + BALL_RADIUS;
  return std ::make_shared<Ball>(Vec2{x, y});
}

void Ball::update(double dt) {
  center += (dirVec * speed * dt);
}

void Ball::draw() const {
  const float y = SCREEN_HEIGHT - center.y;

  al_draw_filled_circle(center.x, y, radius, COLOR_WHITE);
  al_draw_circle(center.x, y, radius, COLOR_BLACK, 1);
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
