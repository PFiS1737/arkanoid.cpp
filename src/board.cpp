#include "board.hpp"
#include <algorithm>
#include <limits>

Board::Board() {
  racket =
      make_shared<Racket>(Vec2{BOARD_WIDTH / 2 + BORDER_THICKNESS, RACKET_Y_POSITION}, RACKET_WIDTH, RACKET_HEIGHT);

  // left
  borders.push_back(make_shared<Border>(Vec2{0, BOARD_HEIGHT}, Vec2{BORDER_THICKNESS, 0}));
  // right
  borders.push_back(make_shared<Border>(Vec2{SCREEN_WIDTH - BORDER_THICKNESS, BOARD_HEIGHT}, Vec2{SCREEN_WIDTH, 0}));
  // top
  borders.push_back(make_shared<Border>(Vec2{0, BOARD_HEIGHT},
                                        Vec2{BOARD_WIDTH + BORDER_THICKNESS, BOARD_HEIGHT - BORDER_THICKNESS}));
}

void Board::init() {
  bonusManager = make_unique<BonusManager>(weak_from_this());
}

bool Board::isWin() {
  return bricks.empty() && life > 0;
}

void Board::setRacketX(double centerX) {
  auto ox = racket->center.x;
  racket->setCenterX(centerX);

  for (auto &ball : balls) {
    if (ball->stuck) {
      double dx = ox - ball->center.x;
      ball->center.x = racket->center.x - dx;
    }
  }
}

void Board::setRacketWideRate(double rate) {
  racket->width *= rate;
  racket->width = min(racket->width, BOARD_WIDTH);
}

void Board::setBallSlowRate(double rate) {
  for (auto &ball : balls) ball->speed *= rate;
}

void Board::releaseBall() {
  for (auto &ball : balls) ball->stuck = false;
}

void Board::splitBalls() {
  vector<shared_ptr<Ball>> newBalls;

  for (auto &ball : balls) {
    if (ball->stuck) continue;

    Vec2 center = ball->center;
    double radius = ball->radius;
    Vec2 dirVec = ball->dirVec;
    double speed = ball->speed;

    // newBalls.push_back(make_shared<Ball>(center, radius, dirVec, speed));
    newBalls.push_back(make_shared<Ball>(center, radius, dirVec.rotated(30), speed));
    newBalls.push_back(make_shared<Ball>(center, radius, dirVec.rotated(-30), speed));
  }

  balls = newBalls;
}

void Board::update(double dt) {
  if (dt == 0) return;

  // NOTE: Make sure we handle collisions before updating the ball position,
  //       so that we have a right dirVec after the ball is released from stuck.
  solveBallCollisions();

  pills.erase(remove_if(pills.begin(), pills.end(),
                        [&](auto &pill) {
                          pill->update(dt);
                          if (pill->checkCatching(*racket)) {
                            bonusManager->push(pill->bonus);
                            return true;
                          }
                          return false;
                        }),
              pills.end());

  balls.erase(remove_if(balls.begin(), balls.end(),
                        [&](auto &ball) {
                          ball->update(dt);
                          return ball->center.y < -ball->radius;
                        }),
              balls.end());

  if (balls.empty() && --life > 0) {
    balls.push_back(Ball::make());
  }

  bonusManager->update(dt);
}

void Board::reset(vector<shared_ptr<Brick>> bricks) {
  life = INITIAL_NUM_LIVES;
  score = 0;
  this->bricks = bricks;
  pills.clear();
  balls.clear();
  balls.push_back(Ball::make());
}

void Board::draw() const {
  for (auto &border : borders) border->draw();
  for (auto &brick : bricks) brick->draw();
  for (auto &pill : pills) pill->draw();
  for (auto &ball : balls) ball->draw();
  racket->draw();
}

void Board::solveBallCollisions() {
  for (auto &ball : balls) {
    auto res = findCollision(*ball);

    if (!res.has_value()) {
      continue;
    }

    auto value = res.value();

    if (holds_alternative<shared_ptr<Racket>>(value)) {
      auto racket = get<shared_ptr<Racket>>(value);
      ball->collide(*racket);
      if (sticky) {
        ball->stuck = true;
        sticky = false;
      }
    }

    else if (holds_alternative<BrickIt>(value)) {
      auto it = get<BrickIt>(value);
      ball->collide(**it);
      if ((*it)->hit()) {
        score += (*it)->getScore();
        if ((*it)->bonus.type != Bonus::Type::None) {
          pills.push_back(Pill::make((*it)->center, (*it)->bonus));
        }
        bricks.erase(it);
      }
    }

    else if (holds_alternative<BorderIt>(value)) {
      auto it = get<BorderIt>(value);
      ball->collide(**it);
    }
  }
}

Board::findCollisionResult Board::findCollision(Ball &ball) {
  findCollisionResult res;
  double min = numeric_limits<double>::max();

  auto checkCollisions = [&](auto &seq) {
    for (auto it = seq.begin(); it != seq.end(); it++) {
      if (ball.checkCollision(**it)) {
        double dist = ball.getCollDist(**it);
        if (dist < min) {
          res = it;
          min = dist;
        }
      }
    }
  };

  checkCollisions(bricks);
  checkCollisions(borders);

  if (racket && ball.checkCollision(*racket)) {
    double dist = ball.getCollDist(*racket);
    if (dist < min) {
      res = racket;
      min = dist;
    }
  }

  return res;
}
