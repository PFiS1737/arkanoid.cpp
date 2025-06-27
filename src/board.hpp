#pragma once

#include "models/ball.hpp"
#include "models/border.hpp"
#include "models/brick.hpp"
#include "models/racket.hpp"
#include <memory>
#include <vector>

using namespace std;

class Board {
public:
  unsigned long score = 0;
  unsigned life = INITIAL_NUM_LIVES;

  shared_ptr<Racket> racket;
  vector<shared_ptr<Border>> borders;
  vector<shared_ptr<Brick>> bricks;
  shared_ptr<Ball> ball;

  Board();

  void update(double dt);
  void reset();
};
