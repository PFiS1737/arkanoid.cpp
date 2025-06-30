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

void Board::init() {
  bonusManager = make_unique<BonusManager>(weak_from_this());
}

bool Board::isWin() {
  return bricks.empty() && life > 0;
}

void Board::setRacketX(double centerX) {
  auto dx = racket->center.x - ball->center.x;

  racket->setCenterX(centerX);

  if (ball->stuck) {
    ball->center.x = racket->center.x - dx;
  }
}

void Board::setRacketWideRate(double rate) {
  racket->width *= rate;
  racket->width = min(racket->width, BOARD_WIDTH);
}

void Board::setBallSlowRate(double rate) {
  ball->speed *= rate;
}

void Board::releaseBall() {
  ball->stuck = false;
}

void Board::update(double dt) {
  if (dt == 0) return;

  // NOTE: Make sure we handle collisions before updating the ball position,
  //       so that we have a right dirVec after the ball is released from stuck.
  solveBallCollisions(*ball);
  solvePillCatching();

  bonusManager->update(dt);
  ball->update(dt);
  for (auto &pill : pills) pill->update(dt);

  if (ball->center.y < -ball->radius) {
    if (--life > 0) {
      ball = Ball::make();
    }
  }
}

void Board::reset(vector<shared_ptr<Brick>> bricks) {
  life = INITIAL_NUM_LIVES;
  score = 0;
  ball = Ball::make();
  this->bricks = bricks;
  pills.clear();
}

void Board::draw() const {
  for (auto &border : borders) border->draw();
  for (auto &brick : bricks) brick->draw();
  for (auto &pill : pills) pill->draw();
  ball->draw();
  racket->draw();
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
    if (sticky) {
      ball.stuck = true;
      sticky = false;
    }
  }

  else if (holds_alternative<BrickIt>(value)) {
    auto it = get<BrickIt>(value);
    ball.collide(**it);
    if ((*it)->hit()) {
      score += (*it)->getScore();
      pills.push_back(Pill::make((*it)->center, (*it)->bonus));
      bricks.erase(it);
    }
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

void Board::solvePillCatching() {
  for (auto it : findPillCatching()) {
    bonusManager->push((*it)->bonus);
    pills.erase(it);
  }
}

vector<Board::PillIt> Board::findPillCatching() {
  vector<PillIt> res;

  for (auto it = pills.begin(); it != pills.end(); it++) {
    if ((*it)->checkCatching(*racket)) {
      res.push_back(it);
    }
  }

  return res;
}
