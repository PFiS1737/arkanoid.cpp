module board;

import shared.bonus;
import shared.vec2;
import configs;

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

bool Board::isWin() {
  return life > 0 && (bricks.empty() || all_of(bricks.begin(), bricks.end(),
                                               [](const auto &brick) { return brick->color == COLOR_GOLD; }));
}

void Board::update(double dt) {
  if (dt == 0) return;

  lasers.erase(remove_if(lasers.begin(), lasers.end(),
                         [&](const auto &laser) {
                           laser->update(dt);
                           // TODO: Maybe there is a better way to handle this?
                           // FIXME: We traverse all bricks for each laser here,
                           //        and we traverse them again every time we call `solveBallCollisions` later,
                           //        and finally again in `bricks.erase(remove_if)`.
                           for (const auto &brick : bricks) {
                             if (laser->checkHit(*brick)) {
                               brick->hit();
                               return true;
                             }
                           }
                           return laser->center.y + LASER_LENGTH > BOARD_HEIGHT;
                         }),
               lasers.end());

  pills.erase(remove_if(pills.begin(), pills.end(),
                        [&](const auto &pill) {
                          pill->update(dt);
                          if (pill->checkCatching(*racket)) {
                            applyBonus(pill->bonus);
                            return true;
                          }
                          return false;
                        }),
              pills.end());

  balls.erase(remove_if(balls.begin(), balls.end(),
                        [&](const auto &ball) {
                          // NOTE: Make sure we handle collisions before updating the ball position,
                          //       so that we have a right dirVec after the ball is released from stuck.
                          solveBallCollisions(ball);
                          ball->update(dt);
                          return ball->center.y < -ball->radius;
                        }),
              balls.end());

  bricks.erase(remove_if(bricks.begin(), bricks.end(),
                         [&](const auto &brick) {
                           if (brick->destroyed) {
                             score += brick->getScore();
                             if (brick->bonus.type != Bonus::Type::None) {
                               pills.push_back(Pill::make(brick->center, brick->bonus));
                             }
                             return true;
                           }
                           return false;
                         }),
               bricks.end());

  // NOTE: No need to remove deactivated bonuses.
  for (auto &[bonus, time] : bonuses) {
    time -= dt;
    if (time <= 0) {
      onBonusDeactivate(bonus);
    }
  }

  if (balls.empty() && --life > 0) {
    balls.push_back(Ball::make());
  }
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
  for (const auto &laser : lasers) laser->draw();
  for (const auto &pill : pills) pill->draw();
  for (const auto &ball : balls) ball->draw();
  for (const auto &brick : bricks) brick->draw();
  racket->draw();
  for (const auto &border : borders) border->draw();
}

void Board::solveBallCollisions(const shared_ptr<Ball> &ball) {
  auto res = findCollision(ball);

  if (!res.has_value()) {
    return;
  }

  auto value = res.value();

  if (holds_alternative<shared_ptr<Racket>>(value)) {
    auto racket = get<shared_ptr<Racket>>(value);
    ball->collide(racket);
    if (sticky) {
      ball->stuck = true;
      sticky = false;
    }
  }

  else if (holds_alternative<BrickIt>(value)) {
    auto brick = *get<BrickIt>(value);
    ball->collide(brick);
    brick->hit();
  }

  else if (holds_alternative<BorderIt>(value)) {
    auto border = *get<BorderIt>(value);
    ball->collide(border);
  }
}

Board::findCollisionResult Board::findCollision(const shared_ptr<Ball> &ball) {
  findCollisionResult res;
  double min = numeric_limits<double>::max();

  auto checkCollisions = [&](const auto &seq) {
    for (auto it = seq.begin(); it != seq.end(); it++) {
      if (ball->checkCollision(*it)) {
        double dist = ball->getCollDist(*it);
        if (dist < min) {
          res = it;
          min = dist;
        }
      }
    }
  };

  checkCollisions(bricks);
  checkCollisions(borders);

  if (racket && ball->checkCollision(racket)) {
    double dist = ball->getCollDist(racket);
    if (dist < min) {
      res = racket;
      min = dist;
    }
  }

  return res;
}

void Board::applyBonus(const Bonus &bonus) {
  if (bonus.type == Bonus::Type::None) return;

  if (bonus.isStatic) {
    onBonusActivate(bonus);
    return;
  }

  auto it = bonuses.find(bonus);
  if (it == bonuses.end()) {
    onBonusActivate(bonus);
  }

  bonuses[bonus] = bonus.duration;
}

void Board::onBonusActivate(Bonus::Type bonus) {
  switch (bonus) {
    case Bonus::Type::ExtraLife:
      life++;
      break;
    case Bonus::Type::SlowBall:
      setBallSlowRate(BONUS_SLOW_BALL_RATE);
      break;
    case Bonus::Type::WideRacket:
      setRacketWideRate(BONUS_WIDE_RACKET_RATE);
      break;
    case Bonus::Type::StickyRacket:
      sticky = true;
      break;
    case Bonus::Type::SplitBall:
      splitBalls();
      break;
    case Bonus::Type::Laser:
      laser = true;
      break;
    default:
      throw runtime_error("Unknown bonus type activated");
  }
}

void Board::onBonusDeactivate(Bonus::Type bonus) {
  switch (bonus) {
    case Bonus::Type::SlowBall:
      setBallSlowRate(1 / BONUS_SLOW_BALL_RATE);
      break;
    case Bonus::Type::WideRacket:
      setRacketWideRate(1 / BONUS_WIDE_RACKET_RATE);
      break;
    case Bonus::Type::Laser:
      laser = false;
      break;
    default:
      throw runtime_error("Unknown bonus type deactivated");
  }
}

void Board::setRacketX(double x) {
  auto ox = racket->center.x;
  racket->setCenterX(x);

  for (const auto &ball : balls) {
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
  for (const auto &ball : balls) ball->speed *= rate;
}

bool Board::releaseBall() {
  for (const auto &ball : balls) {
    if (ball->stuck) {
      ball->stuck = false;
      return true;
    }
  }
  return false;
}

void Board::splitBalls() {
  vector<shared_ptr<Ball>> newBalls;

  for (const auto &ball : balls) {
    if (ball->stuck) continue;

    Vec2 center = ball->center;
    double radius = ball->radius;
    Vec2 dirVec = ball->dirVec;
    double speed = ball->speed;

    // newBalls.push_back(make_shared<Ball>(center, radius, dirVec, speed));
    newBalls.push_back(make_shared<Ball>(center, radius, dirVec.rotated(30), speed)); // TODO: random?
    newBalls.push_back(make_shared<Ball>(center, radius, dirVec.rotated(-30), speed));
  }

  balls = newBalls;
}

void Board::shootLaser() {
  if (!laser) return;
  lasers.push_back(make_shared<Laser>(Vec2{racket->center.x, racket->center.y + RACKET_HEIGHT / 2}));
}
