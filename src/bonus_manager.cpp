#include "bonus_manager.hpp"
#include "board.hpp"
#include <stdexcept>

BonusManager::BonusManager(const weak_ptr<Board> &board) : board{board}, bonuses{} {
}

void BonusManager::push(const Bonus &bonus) {
  if (bonus.type == Bonus::Type::None) return;

  if (bonus.isStatic) {
    onActivate(bonus.type);
    return;
  }

  auto it = bonuses.find(bonus.type);
  if (it != bonuses.end()) {
    bonuses[bonus.type] = bonus.duration;
  } else {
    bonuses[bonus.type] = bonus.duration;
    onActivate(bonus.type);
  }
}

void BonusManager::update(double dt) {
  for (auto it = bonuses.begin(); it != bonuses.end();) {
    it->second -= dt;
    if (it->second <= 0) {
      onDeactivate(it->first);
      it = bonuses.erase(it);
    } else {
      it++;
    }
  }
}

void BonusManager::onActivate(Bonus::Type bonus) {
  if (auto board = this->board.lock()) {
    switch (bonus) {
      case Bonus::Type::ExtraLife:
        board->life++;
        break;
      case Bonus::Type::SlowBall:
        board->setBallSlowRate(BONUS_SLOW_BALL_RATE);
        break;
      case Bonus::Type::WideRacket:
        board->setRacketWideRate(BONUS_WIDE_RACKET_RATE);
        break;
      case Bonus::Type::StickyRacket:
        board->sticky = true;
        break;
      case Bonus::Type::SplitBall:
        board->splitBalls();
        break;
      case Bonus::Type::Laser:
        board->laser = true;
        break;
      default:
        throw runtime_error("Unknown bonus type activated");
    }
  } else {
    throw runtime_error("Board is no longer available");
  }
}

void BonusManager::onDeactivate(Bonus::Type bonus) {
  if (auto board = this->board.lock()) {
    switch (bonus) {
      case Bonus::Type::SlowBall:
        board->setBallSlowRate(1 / BONUS_SLOW_BALL_RATE);
        break;
      case Bonus::Type::WideRacket:
        board->setRacketWideRate(1 / BONUS_WIDE_RACKET_RATE);
        break;
      case Bonus::Type::Laser:
        board->laser = false;
        break;
      default:
        throw runtime_error("Unknown bonus type deactivated");
    }
  } else {
    throw runtime_error("Board is no longer available");
  }
}
