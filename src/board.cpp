#include "board.hpp"
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

void Board::update(double dt) {
  if (dt == 0) return;

  ball->update(dt);

  solveBallCollisions(*ball);

  if (ball->center.y < -ball->radius) {
    if (--life > 0) {
      ball = Ball::newBall();
    }
  }
}

void Board::reset() {
  life = INITIAL_NUM_LIVES;
  score = 0;
  ball = Ball::newBall();
  bricks.clear();
}

void Board::solveBallCollisions(Ball &ball) {
  auto coll = findCollision(ball);

  if (!coll.has_value()) {
    return;
  }

  auto value = coll.value();

  if (holds_alternative<shared_ptr<Racket>>(value)) {
    auto racket = get<shared_ptr<Racket>>(value);
    ball.collide(*racket);
  }

  else if (holds_alternative<BrickIt>(value)) {
    auto it = get<BrickIt>(value);
    ball.collide(**it);
    score += (*it)->getScore();
    bricks.erase(it);
  }

  else if (holds_alternative<BorderIt>(value)) {
    auto it = get<BorderIt>(value);
    ball.collide(**it);
  }
}

Board::findCollisionResult Board::findCollision(Ball &ball) {
  findCollisionResult res;
  double min = numeric_limits<double>::max();

  auto checkCollisions = [&](auto &seq) {
    for (auto it = seq.begin(); it != seq.end(); it++) {
      if (ball.checkCollision(**it)) {
        double dist = ball.getCollDistVec(**it).getModule();
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
    double dist = ball.getCollDistVec(*racket).getModule();
    if (dist < min) {
      res = racket;
      min = dist;
    }
  }

  return res;
}
