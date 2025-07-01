module;

class Board; // HACK: Forward declaration to avoid circular dependency

export module bonus_manager;

import shared.bonus;
import std;

using namespace std;

export class BonusManager {
  weak_ptr<Board> board;
  unordered_map<Bonus::Type, double> bonuses;

  void onActivate(Bonus::Type bonus);
  void onDeactivate(Bonus::Type bonus);

public:
  BonusManager(const weak_ptr<Board> &board);

  BonusManager(const BonusManager &) = delete;
  BonusManager(BonusManager &&) = delete;
  BonusManager &operator=(const BonusManager &) = delete;
  BonusManager &operator=(BonusManager &&) = delete;

  void push(const Bonus &bonus);

  void update(double dt);
};
