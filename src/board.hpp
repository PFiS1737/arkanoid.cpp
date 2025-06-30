#pragma once

#include "bonus_manager.hpp"
#include "models/ball.hpp"
#include "models/border.hpp"
#include "models/bricks/brick.hpp"
#include "models/laser.hpp"
#include "models/pill.hpp"
#include "models/racket.hpp"
#include <optional>
#include <variant>
#include <vector>

using namespace std;

class Board final : public enable_shared_from_this<Board> {
  vector<shared_ptr<Border>> borders;
  shared_ptr<Racket> racket;

  vector<shared_ptr<Brick>> bricks;
  vector<shared_ptr<Pill>> pills;
  vector<shared_ptr<Ball>> balls;
  vector<shared_ptr<Laser>> lasers;

  unique_ptr<BonusManager> bonusManager;

  void solveBallCollisions(const shared_ptr<Ball> &ball);

  using BrickIt = vector<shared_ptr<Brick>>::const_iterator;
  using BorderIt = vector<shared_ptr<Border>>::const_iterator;
  using findCollisionResult = optional<variant<BrickIt, BorderIt, shared_ptr<Racket>>>;
  findCollisionResult findCollision(const shared_ptr<Ball> &ball);

public:
  unsigned long score = 0;
  unsigned life = INITIAL_NUM_LIVES;

  bool sticky = false;
  bool laser = false;

  Board();
  void init();

  Board(const Board &) = delete;
  Board(Board &&) = delete;
  Board &operator=(const Board &) = delete;
  Board &operator=(Board &&) = delete;

  bool isWin();

  void setRacketX(double centerX);
  void setRacketWideRate(double rate);
  void setBallSlowRate(double rate);
  bool releaseBall(); // Return true if actually released a ball
  void splitBalls();
  void shootLaser();

  void update(double dt);
  void reset(vector<shared_ptr<Brick>> bricks);

  void draw() const;
};
