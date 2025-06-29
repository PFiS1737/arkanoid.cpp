#pragma once

#include "shared/bonus.hpp"
#include <memory>
#include <unordered_map>

class Board; // HACK: avoid circular dependency

class BonusManager {
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
