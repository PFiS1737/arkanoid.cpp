export module board;

import models.ball;
import models.border;
import models.brick;
import models.laser;
import models.pill;
import models.racket;
import shared.bonus;
import configs;
import std;

using namespace std;

export class Board final : public enable_shared_from_this<Board> {
  vector<shared_ptr<Border>> borders;
  shared_ptr<Racket> racket;

  vector<shared_ptr<Brick>> bricks;
  vector<shared_ptr<Ball>> balls;
  vector<shared_ptr<Pill>> pills;
  vector<shared_ptr<Laser>> lasers;

  void solveBallCollisions(const shared_ptr<Ball> &ball);

  using BrickIt = vector<shared_ptr<Brick>>::const_iterator;
  using BorderIt = vector<shared_ptr<Border>>::const_iterator;
  using findCollisionResult = optional<variant<BrickIt, BorderIt, shared_ptr<Racket>>>;
  findCollisionResult findCollision(const shared_ptr<Ball> &ball);

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
  void reset(vector<shared_ptr<Brick>> bricks);

  void draw() const;
};
