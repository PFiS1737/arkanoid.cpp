#pragma once

#include "models/ball.hpp"
#include "models/border.hpp"
#include "models/brick.hpp"
#include "models/racket.hpp"
#include <optional>
#include <variant>
#include <vector>

using namespace std;

class Board final {
  void solveBallCollisions(Ball &ball);

  using BrickIt = vector<shared_ptr<Brick>>::const_iterator;
  using BorderIt = vector<shared_ptr<Border>>::const_iterator;
  using findCollisionResult = optional<variant<BrickIt, BorderIt, shared_ptr<Racket>>>;
  findCollisionResult findCollision(Ball &ball);

public:
  unsigned long score = 0;
  unsigned life = INITIAL_NUM_LIVES;

  shared_ptr<Racket> racket;
  vector<shared_ptr<Border>> borders;
  vector<shared_ptr<Brick>> bricks;
  shared_ptr<Ball> ball;

  Board();

  Board(const Board &) = delete;
  Board(Board &&) = delete;
  Board &operator=(const Board &) = delete;
  Board &operator=(Board &&) = delete;

  void update(double dt);
  void reset();

  void draw() const;
};
