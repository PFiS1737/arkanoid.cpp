#pragma once

#include "models/ball.hpp"
#include "models/border.hpp"
#include "models/bricks/brick.hpp"
#include "models/laser.hpp"
#include "models/pill.hpp"
#include "models/racket.hpp"
#include <optional>
#include <unordered_map>
#include <variant>
#include <vector>

using namespace std;

class Board final : public enable_shared_from_this<Board> {
  vector<shared_ptr<Border>> borders;
  shared_ptr<Racket> racket;

  vector<unique_ptr<Brick>> bricks;
  vector<unique_ptr<Ball>> balls;
  vector<unique_ptr<Pill>> pills;
  vector<unique_ptr<Laser>> lasers;

  void solveBallCollisions(const unique_ptr<Ball> &ball);

  using findCollisionResult = optional<variant<Brick *, Border *, Racket *>>;
  findCollisionResult findCollision(const unique_ptr<Ball> &ball);

  unordered_map<Bonus::Type, double> bonuses;

  void applyBonus(const Bonus &bonus);
  void onBonusActivate(Bonus::Type bonus);
  void onBonusDeactivate(Bonus::Type bonus);

  bool sticky = false;
  bool laser = false;

  void setRacketWideRate(double rate);
  void setBallSlowRate(double rate);
  void splitBalls();

public:
  unsigned long score = 0;
  unsigned life = INITIAL_NUM_LIVES;

  Board();

  Board(const Board &) = delete;
  Board(Board &&) = delete;
  Board &operator=(const Board &) = delete;
  Board &operator=(Board &&) = delete;

  bool isWin();

  void setRacketX(double x);
  bool releaseBall(); // NOTE: Return true if actually released a ball
  void shootLaser();

  void update(double dt);
  void reset(vector<unique_ptr<Brick>> &bricks);

  void draw() const;
};
