#pragma once

#include "color.hpp"

struct Bonus {
  // NOTE: the effects of the bonus are defined in `bonus_manager.cpp`
  enum class Type {
    None,
    ExtraLife,
    SlowBall,
    WideRacket,
  };

  Type type;
  Color color;
  double duration = 0;
  bool isStatic = false;

  Bonus(Type type);
  Bonus(Type type, const Color &color);
  Bonus(Type type, const Color &color, double duration);
  Bonus(const string &bonusName);

  bool operator==(const Bonus &other) const;
  operator Type() const;
  operator string() const;

private:
  static Bonus fromString(const string &bonusName);
};
